/*
BCM2835 "GPU_FFT" release 2.0
Copyright (c) 2014, Andrew Holme.
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

#include "gpu_fft.h"
#include "mailbox.h"

#define PERI_BASE 0x20000000
#define PERI_SIZE 0x02000000

// V3D spec: http://www.broadcom.com/docs/support/videocore/VideoCoreIV-AG100-R.pdf
#define V3D_L2CACTL (0xC00020>>2)
#define V3D_SLCACTL (0xC00024>>2)
#define V3D_SRQPC   (0xC00430>>2)
#define V3D_SRQUA   (0xC00434>>2)
#define V3D_SRQCS   (0xC0043c>>2)
#define V3D_DBCFG   (0xC00e00>>2)
#define V3D_DBQITE  (0xC00e2c>>2)
#define V3D_DBQITC  (0xC00e30>>2)

#define GPU_FFT_MEM_FLG 0xC // cached=0xC; direct=0x4
#define GPU_FFT_MEM_MAP 0x0 // cached=0x0; direct=0x20000000

#define GPU_FFT_NO_FLUSH 1
#define GPU_FFT_TIMEOUT 2000 // ms

unsigned gpu_fft_base_exec_direct (
    struct GPU_FFT_BASE *base,
    int num_qpus) {

    unsigned q, t;

    base->peri[V3D_DBCFG] = 0; // Disallow IRQ
    base->peri[V3D_DBQITE] = 0; // Disable IRQ
    base->peri[V3D_DBQITC] = -1; // Resets IRQ flags

    base->peri[V3D_L2CACTL] =  1<<2; // Clear L2 cache
    base->peri[V3D_SLCACTL] = -1; // Clear other caches

    base->peri[V3D_SRQCS] = (1<<7) | (1<<8) | (1<<16); // Reset error bit and counts

    for (q=0; q<num_qpus; q++) { // Launch shader(s)
        base->peri[V3D_SRQUA] = base->vc_unifs[q];
        base->peri[V3D_SRQPC] = base->vc_code;
    }

    // Busy wait polling
    for (;;) {
        if (((base->peri[V3D_SRQCS]>>16) & 0xff) == num_qpus) break; // All done?
    }

    return 0;
}

unsigned gpu_fft_base_exec(
    struct GPU_FFT_BASE *base,
    int num_qpus) {

    if (base->vc_msg) {
        // Use mailbox
        // Returns: 0x0 for success; 0x80000000 for timeout
        return execute_qpu(base->mb, num_qpus, base->vc_msg, GPU_FFT_NO_FLUSH, GPU_FFT_TIMEOUT);
    }
    else {
        // Direct register poking
        return gpu_fft_base_exec_direct(base, num_qpus);
    }
}

int gpu_fft_alloc (
    int mb,
    unsigned size,
    struct GPU_FFT_PTR *ptr) {

    struct GPU_FFT_BASE *base;
    volatile unsigned *peri;
    unsigned handle;

    if (qpu_enable(mb, 1)) return -1;

    // Shared memory
    handle = mem_alloc(mb, size, 4096, GPU_FFT_MEM_FLG);
    if (!handle) {
        qpu_enable(mb, 0);
        return -3;
    }

    peri = (volatile unsigned *) mapmem(PERI_BASE, PERI_SIZE);
    if (!peri) {
        mem_free(mb, handle);
        qpu_enable(mb, 0);
        return -4;
    }

    ptr->vc = mem_lock(mb, handle);
    ptr->arm.vptr = mapmem(ptr->vc+GPU_FFT_MEM_MAP, size);

    base = (struct GPU_FFT_BASE *) ptr->arm.vptr;
    base->peri   = peri;
    base->mb     = mb;
    base->handle = handle;
    base->size   = size;

    return 0;
}

void gpu_fft_base_release(struct GPU_FFT_BASE *base) {
    int mb = base->mb;
    unsigned handle = base->handle, size = base->size;
    unmapmem((void*)base->peri, PERI_SIZE);
    unmapmem((void*)base, size);
    mem_unlock(mb, handle);
    mem_free(mb, handle);
    qpu_enable(mb, 0);
}

unsigned gpu_fft_ptr_inc (
    struct GPU_FFT_PTR *ptr,
    int bytes) {

    unsigned vc = ptr->vc;
    ptr->vc += bytes;
    ptr->arm.bptr += bytes;
    return vc;
}
