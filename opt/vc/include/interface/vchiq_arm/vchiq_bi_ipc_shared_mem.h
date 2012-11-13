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

//  Header file for core VCHIQ logic

#if !defined( IPC_SHARED_MEM_H )
#define IPC_SHARED_MEM_H

/****************************************************************************
*
*   Shared memory offsets
* 
*   On big island, we have 160K of shared memory which is used for
*   communicating between the host and the videocore.
* 
*   These constants are used as offsets into that area and as such, need
*   to go into some shared header file.
* 
*   The places which use these constants:
* 
*   vc4/src/interface/vchiq_arm_bi/big_island/vchiq_bi_vc.c
*   vc4/src/interface/vchiq_arm_bi/vchiq_memdrv.c
*   vc4/src/vcfw/platform/broadcom/bcm911160-tablet/platform.c (for gpio)
*   vc4/src/vcfw/drivers/chip/vciv/2708/clock_bigisland.c
* 
*   The shared memory is 160K or 0x28000
* 
***************************************************************************/

/*
 * The PM stuff uses the low 32K of SRAM. 
 *  
 * Any changes to IPC_SHARED_MEM_VC_OFFSET must also be made to 
 * BCMHANA_ARAM_VC_OFFSET in linux/target/kernel/added/arch/arm/mach-bcmhana/include/mach/aram_layout.h 
 */


#define IPC_SHARED_MEM_VC_OFFSET            0x08000 /* 32K used for PM suspend/resume */

/*
 * The following offsets are relative to SRAM-BASE + IPC_SHARED_MEM_VC_OFFSET
 */

#define IPC_SHARED_MEM_CHANNEL_VC_OFFSET    ( 0 )
#define IPC_SHARED_MEM_CHANNEL_VC_SIZE      0x8000 /* 32K */

#define IPC_SHARED_MEM_CHANNEL_ARM_OFFSET   ( IPC_SHARED_MEM_CHANNEL_VC_OFFSET + IPC_SHARED_MEM_CHANNEL_VC_SIZE )
#define IPC_SHARED_MEM_CHANNEL_ARM_SIZE     0x8000 /* 32K */ 

#define IPC_SHARED_MEM_FRAGMENTS_OFFSET     ( IPC_SHARED_MEM_CHANNEL_ARM_OFFSET + IPC_SHARED_MEM_CHANNEL_ARM_SIZE )
#define IPC_SHARED_MEM_FRAGMENTS_SIZE       0x01000 /* 4K */

#define IPC_SHARED_MEM_CLOCK_DEBUG_OFFSET   ( 0x26000 - IPC_SHARED_MEM_VC_OFFSET ) /* 4 bytes */
#define IPC_SHARED_MEM_GPIO_WRITE_OFFSET    ( 0x26200 - IPC_SHARED_MEM_VC_OFFSET ) /* 4 bytes */
#define IPC_SHARED_MEM_GPIO_READ_OFFSET     ( 0x26204 - IPC_SHARED_MEM_VC_OFFSET ) /* 4 bytes */

#endif /* IPC_SHARED_MEM_H */
