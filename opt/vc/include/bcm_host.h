/*
Copyright (c) 2012, Broadcom Europe Ltd
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

// Header file with useful bits from other headers

#ifndef BCM_HOST_H
#define BCM_HOST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void bcm_host_init(void);
void bcm_host_deinit(void);

int32_t graphics_get_display_size( const uint16_t display_number,
                                                    uint32_t *width,
                                                    uint32_t *height);

unsigned bcm_host_get_peripheral_address(void);
unsigned bcm_host_get_peripheral_size(void);
unsigned bcm_host_get_sdram_address(void);

#include "interface/vmcs_host/vc_dispmanx.h"
#include "interface/vmcs_host/vc_tvservice.h"
#include "interface/vmcs_host/vc_cec.h"
#include "interface/vmcs_host/vc_cecservice.h"
#include "interface/vmcs_host/vcgencmd.h"

/* Returns the type of the Pi being used
*/
#define BCM_HOST_BOARD_TYPE_MODELA 0
#define BCM_HOST_BOARD_TYPE_MODELB 1
#define BCM_HOST_BOARD_TYPE_MODELAPLUS 2
#define BCM_HOST_BOARD_TYPE_MODELBPLUS 3
#define BCM_HOST_BOARD_TYPE_PI2MODELB 4
#define BCM_HOST_BOARD_TYPE_ALPHA 5
#define BCM_HOST_BOARD_TYPE_CM 6
#define BCM_HOST_BOARD_TYPE_CM2 7
#define BCM_HOST_BOARD_TYPE_PI3MODELB 8
#define BCM_HOST_BOARD_TYPE_PI0 9
#define BCM_HOST_BOARD_TYPE_CM3 0xa
#define BCM_HOST_BOARD_TYPE_CUSTOM 0xb
#define BCM_HOST_BOARD_TYPE_PI0W 0xc
#define BCM_HOST_BOARD_TYPE_PI3MODELBPLUS 0xd
#define BCM_HOST_BOARD_TYPE_PI3MODELAPLUS 0xe
#define BCM_HOST_BOARD_TYPE_FPGA 0xf
#define BCM_HOST_BOARD_TYPE_CM3PLUS 0x10
#define BCM_HOST_BOARD_TYPE_PI4MODELB 0x11

extern int bcm_host_get_model_type(void);

/* Returns 1 if model is  Pi4
*/
extern int bcm_host_is_model_pi4(void);

/* Returns 1 if fkms is active (dtoverlay=v3d-fkms-vc4)
*/
extern int bcm_host_is_fkms_active(void);

/* Returns 1 if kms is active (dtoverlay=v3d-kms-vc4)
*/
extern int bcm_host_is_kms_active(void);

/* returns the processor ID
*/
#define BCM_HOST_PROCESSOR_BCM2835 0
#define BCM_HOST_PROCESSOR_BCM2836 1
#define BCM_HOST_PROCESSOR_BCM2837 2
#define BCM_HOST_PROCESSOR_BCM2838 3

extern int bcm_host_get_processor_id(void);

#ifdef __cplusplus
}
#endif

#endif

