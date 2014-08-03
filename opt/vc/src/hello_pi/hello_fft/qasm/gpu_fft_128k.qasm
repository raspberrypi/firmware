#
# BCM2835 "GPU_FFT"
#
# Copyright (c) 2013, Andrew Holme.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the copyright holder nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

.set STAGES, 17

.include "gpu_fft.qinc"

##############################################################################
# Twiddles

.set TW_SHARED,     5
.set TW_UNIQUE,     1

.set TW32_P1_BASE,  0
.set TW16_P1_BASE,  1
.set TW16_P2_BASE,  TW16_P1_BASE
.set TW16_P3_BASE,  TW16_P1_BASE
.set TW16_P2_STEP,  2
.set TW16_P3_STEP,  3
.set TW16_P4_STEP,  4

.set TW16_P4_BASE,  5

.set TW32_ACTIVE,   TW_SHARED+TW_UNIQUE
.set TW16_ACTIVE,   TW_SHARED+TW_UNIQUE+1

##############################################################################
# Registers

.set ra_link_0,         ra0
.set rb_vdw_16,         rb0
.set ra_save_ptr,       ra1
.set rb_vdw_32,         rb1
.set ra_temp,           ra2
.set rb_vpm_lo,         rb2
.set ra_addr_x,         ra3
.set rb_addr_y,         rb3
.set ra_save_16,        ra4
.set rx_save_slave_16,  rb4
.set ra_load_idx,       ra5
.set rb_inst,           rb5
.set ra_sync,           ra6
.set rx_sync_slave,     rb6
.set ra_points,         ra7
.set rb_vpm_hi,         rb7
.set ra_link_1,         ra8
.set rb_STAGES,         rb8
.set ra_32_re,          ra9
.set rb_32_im,          rb9
.set ra_save_32,        ra10
.set rx_save_slave_32,  rb10

.set ra_tw_re,          ra11 # 11
.set rb_tw_im,          rb11 # 11

.set ra_vpm_lo,         ra25
.set ra_vpm_hi,         ra26
.set ra_vdw_16,         ra27
.set ra_vdw_32,         ra28

.set rx_0x55555555,     ra29
.set rx_0x33333333,     ra30
.set rx_0x0F0F0F0F,     ra31
.set rx_0x00FF00FF,     rb24
.set rx_0x0000FFFF,     rb25

.set rb_0x10,           rb26
.set rb_0x40,           rb27
.set rb_0x80,           rb28
.set rb_0xF0,           rb29
.set rb_0x100,          rb30
.set rb_0xFFF,          rb31

##############################################################################
# Constants

mov rb_STAGES,  STAGES

mov rb_0x10,    0x10
mov rb_0x40,    0x40
mov rb_0x80,    0x80
mov rb_0xF0,    0xF0
mov rb_0x100,   0x100
mov rb_0xFFF,   0xFFF

mov rx_0x55555555, 0x55555555
mov rx_0x33333333, 0x33333333
mov rx_0x0F0F0F0F, 0x0F0F0F0F
mov rx_0x00FF00FF, 0x00FF00FF
mov rx_0x0000FFFF, 0x0000FFFF

mov ra_vdw_16, vdw_setup_0(16, 16, dma_h32( 0,0))
mov rb_vdw_16, vdw_setup_0(16, 16, dma_h32(32,0))
mov ra_vdw_32, vdw_setup_0(32, 16, dma_h32( 0,0))
mov rb_vdw_32, vdw_setup_0(32, 16, dma_h32(32,0))

##############################################################################
# Load twiddle factors

load_tw rb_0x80,         0, TW_SHARED, unif
load_tw rb_0x80, TW_SHARED, TW_UNIQUE, unif

##############################################################################
# Instance

mov rb_inst, unif
inst_vpm rb_inst, ra_vpm_lo, ra_vpm_hi, rb_vpm_lo, rb_vpm_hi

##############################################################################
# Macros

.macro swizzle
.endm

.macro init_stage, tw16, tw32
    init_stage_32 tw32
    init_stage_16 tw16, 5
.endm

##############################################################################
# Master/slave procedures

proc ra_save_16, r:1f
body_ra_save_16 ra_vpm_lo, ra_vdw_16
:1

proc rx_save_slave_16, r:1f
body_rx_save_slave_16 ra_vpm_lo
:1

proc ra_save_32, r:1f
body_ra_save_32
:1

proc rx_save_slave_32, r:1f
body_rx_save_slave_32
:1

proc ra_sync, r:1f
body_ra_sync
:1

proc rx_sync_slave, r:main
body_rx_sync_slave

##############################################################################
# Redefining this macro

.macro read_rev, stride
    add ra_load_idx, ra_load_idx, stride; mov r0, ra_load_idx

    bit_rev 1,       rx_0x55555555  # 16 SIMD
    bit_rev 2,       rx_0x33333333
    bit_rev 4,       rx_0x0F0F0F0F
    bit_rev 8,       rx_0x00FF00FF
    bit_rev rb_0x10, rx_0x0000FFFF

    shr r0, r0, 12          # r0 = re = {idx[0:STAGES-1], 1'b0, 2'b0}
    add r1, r0, 4           # r1 = im = {idx[0:STAGES-1], 1'b1, 2'b0}

    interleave

    add t0s, ra_addr_x, r0
    add t0s, ra_addr_x, r1
.endm

##############################################################################
# Subroutines

:fft_16
    body_fft_16

:pass_1
    body_pass_32 LOAD_REVERSED

:pass_2
:pass_3
:pass_4
    body_pass_16 LOAD_STRAIGHT

##############################################################################
# Top level

:main
    mov.setf r0, rb_inst
    sub r0, r0, 1
    shl r0, r0, 5
    add.ifnz ra_sync, rx_sync_slave, r0
    mov.ifnz ra_save_16, rx_save_slave_16
    mov.ifnz ra_save_32, rx_save_slave_32

:loop
    mov.setf ra_addr_x, unif # Ping buffer or null
    mov      rb_addr_y, unif # Pong buffer or IRQ enable

    brr.allz -, r:end

##############################################################################
# Pass 1

    init_stage TW16_P1_BASE, TW32_P1_BASE
    read_rev rb_0x10

        brr ra_link_1, r:pass_1
        nop
        nop
        add ra_points, ra_points, rb_0x100

        shr.setf -, ra_points, rb_STAGES

        brr.allz -, r:pass_1
        nop
        nop
        add ra_points, ra_points, rb_0x100

    bra ra_link_1, ra_sync
    nop
    ldtmu0
    ldtmu0

##############################################################################
# Pass 2

    swap_buffers
    init_stage_16 TW16_P2_BASE, 4
    read_lin rb_0x80

        brr ra_link_1, r:pass_2
        nop
        nop
        add ra_points, ra_points, rb_0x80

        and.setf -, ra_points, rb_0xFFF

        brr.allnz -, r:pass_2
        nop
        nop
        add.ifnz ra_points, ra_points, rb_0x80

        next_twiddles_16 TW16_P2_STEP

        shr.setf -, ra_points, rb_STAGES

        brr.allz -, r:pass_2
        nop
        nop
        add ra_points, ra_points, rb_0x80

    bra ra_link_1, ra_sync
    nop
    ldtmu0
    ldtmu0

##############################################################################
# Pass 3

    swap_buffers
    init_stage_16 TW16_P3_BASE, 4
    read_lin rb_0x80

    .rep i, 2
        brr ra_link_1, r:pass_3
        nop
        nop
        add ra_points, ra_points, rb_0x80
    .endr

        next_twiddles_16 TW16_P3_STEP

        shr.setf -, ra_points, rb_STAGES

        brr.allz -, r:pass_3
        mov r0, 4*8
        sub ra_link_1, ra_link_1, r0
        add ra_points, ra_points, rb_0x80

    bra ra_link_1, ra_sync
    nop
    ldtmu0
    ldtmu0

##############################################################################
# Pass 4

    swap_buffers
    init_stage_16 TW16_P4_BASE, 4
    read_lin rb_0x80

        brr ra_link_1, r:pass_4
        nop
        nop
        add ra_points, ra_points, rb_0x80

        next_twiddles_16 TW16_P4_STEP

        shr.setf -, ra_points, rb_STAGES

        brr.allz -, r:pass_4
        nop
        nop
        add ra_points, ra_points, rb_0x80

    bra ra_link_1, ra_sync
    nop
    ldtmu0
    ldtmu0

##############################################################################

    brr -, r:loop
    nop
    nop
    nop

:end
    exit rb_addr_y
