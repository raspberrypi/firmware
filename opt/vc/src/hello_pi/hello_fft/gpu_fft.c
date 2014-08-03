/*
Copyright (c) 2013, Andrew Holme.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string.h>
#include <stdio.h>

#include "gpu_fft.h"
#include "mailbox.h"

#define GPU_FFT_MEM_FLG 0xC // cached=0xC; direct=0x4
#define GPU_FFT_MEM_MAP 0x0 // cached=0x0; direct=0x20000000

typedef struct GPU_FFT_COMPLEX COMPLEX;

struct GPU_FFT_PTR {
    unsigned vc;
    union { COMPLEX  *cptr;
            void     *vptr;
            char     *bptr;
            float    *fptr;
            unsigned *uptr; } arm;
};

static unsigned advance (
    struct GPU_FFT_PTR *ptr,
    int bytes) {

    unsigned vc = ptr->vc;
    ptr->vc += bytes;
    ptr->arm.bptr += bytes;
    return vc;
}

int gpu_fft_prepare(
    int mb,         // mailbox file_desc
    int log2_N,     // log2(FFT_length) = 8...17
    int direction,  // GPU_FFT_FWD: fft(); GPU_FFT_REV: ifft()
    int jobs,       // number of transforms in batch
    struct GPU_FFT **fft) {

    unsigned info_bytes, twid_bytes, data_bytes, code_bytes, unif_bytes, mail_bytes;
    unsigned size, handle, *uptr, vc_tw, vc_code, vc_data, vc_unifs[GPU_FFT_QPUS];
    int i, q, shared, unique, passes;

    struct GPU_FFT_PTR ptr;
    struct GPU_FFT *info;

    if (qpu_enable(mb, 1)) return -1;

    if (gpu_fft_twiddle_size(log2_N, &shared, &unique, &passes)) return -2;

    data_bytes = (1+((sizeof(COMPLEX)<<log2_N)|4095));
    code_bytes = gpu_fft_shader_size(log2_N);
    twid_bytes = sizeof(COMPLEX)*16*(shared+GPU_FFT_QPUS*unique);
    unif_bytes = sizeof(int)*GPU_FFT_QPUS*(5+jobs*2);
    mail_bytes = sizeof(int)*GPU_FFT_QPUS*2;
    info_bytes = sizeof(struct GPU_FFT);

    size  = data_bytes*jobs*2 + // ping-pong data, aligned
            code_bytes +        // shader, aligned
            twid_bytes +        // twiddles
            unif_bytes +        // uniforms
            mail_bytes +        // mailbox message
            info_bytes;         // control

    // Shared memory
    handle = mem_alloc(mb, size, 4096, GPU_FFT_MEM_FLG);
    if (!handle) return -3;

    ptr.vc = mem_lock(mb, handle);
    ptr.arm.vptr = mapmem(ptr.vc+GPU_FFT_MEM_MAP, size);

    // Control header
    info = (struct GPU_FFT *) (ptr.arm.bptr + size - info_bytes);

    // Ping-pong buffers leave results in or out of place
    info->in = info->out = ptr.arm.cptr;
    info->step = data_bytes / sizeof(COMPLEX);
    if (passes&1) info->out += info->step * jobs; // odd => out of place
    vc_data = advance(&ptr, data_bytes*jobs*2);

    // Shader code
    memcpy(ptr.arm.vptr, gpu_fft_shader_code(log2_N), code_bytes);
    vc_code = advance(&ptr, code_bytes);

    // Twiddles
    gpu_fft_twiddle_data(log2_N, direction, ptr.arm.fptr);
    vc_tw = advance(&ptr, twid_bytes);

    uptr = ptr.arm.uptr;

    // Uniforms
    for (q=0; q<GPU_FFT_QPUS; q++) {
        *uptr++ = vc_tw;
        *uptr++ = vc_tw + sizeof(COMPLEX)*16*(shared + q*unique);
        *uptr++ = q;
        for (i=0; i<jobs; i++) {
            *uptr++ = vc_data + data_bytes*i;
            *uptr++ = vc_data + data_bytes*i + data_bytes*jobs;
        }
        *uptr++ = 0;
        *uptr++ = (q==0); // IRQ enable, master only

        vc_unifs[q] = advance(&ptr, sizeof(int)*(5+jobs*2));
    }

    // Mailbox message
    for (q=0; q<GPU_FFT_QPUS; q++) {
        *uptr++ = vc_unifs[q];
        *uptr++ = vc_code;
    }
    info->vc_msg = ptr.vc;

    info->mb      = mb;
    info->handle  = handle;
    info->size    = size;
    info->noflush = 1;
    info->timeout = 1000; // ms

    *fft = info;
    return 0;
}

unsigned gpu_fft_execute(struct GPU_FFT *info) {
    return execute_qpu(info->mb, GPU_FFT_QPUS, info->vc_msg, info->noflush, info->timeout);
}

void gpu_fft_release(struct GPU_FFT *info) {
    int mb = info->mb;
    unsigned handle = info->handle;
    unmapmem(info->in, info->size);
    mem_unlock(mb, handle);
    mem_free(mb, handle);
    qpu_enable(mb, 0);
};
