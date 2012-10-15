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

// VMCS framework - autoregistering VCHI services.

#ifndef VMCS_VCHI_SERVICE_H
#define VMCS_VCHI_SERVICE_H

#ifdef USE_VCHIQ_ARM
#include "vchiq.h"
#endif
#include "interface/vchi/vchi.h"

/** Provides for autoregistering of VCHIQ and VCHI services.
  *
  * Note that this relies on the fact that VCHI and VCHIQ startup
  * functions actually have the same signature, even though the
  * types are subtly different.
  */

/** Function to initialise a VCHIQ service
 * @param vchiq The VCHIQ handle.
 * @return 0 on success
 */
#ifdef USE_VCHIQ_ARM
typedef int32_t (*VCHIQ_SERVICE_AUTOINIT)(VCHIQ_INSTANCE_T vchiq);
typedef struct vchiq_service_info_tag {
   /* Service initialisation function */
   VCHIQ_SERVICE_AUTOINIT init;

   /* Name of service for debugging */
   const char* name;

} VCHIQ_SERVICE_INFO_T;
#endif

typedef int32_t (*VCHI_SERVICE_AUTOINIT)(VCHI_INSTANCE_T vchiq);
typedef struct vchi_service_info_tag {
   /* Service initialisation function */
   VCHI_SERVICE_AUTOINIT init;

   /* Name of service for debugging */
   const char* name;

} VCHI_SERVICE_INFO_T;

/** 
 * Declare one of these statically.
 *
 * To stop the linker 'optimizing' out the auto registration structures
 * there must be a reference to
 * <init>_info_p in dldummy.c
 * Create this by specifying this as the prototype in applications/vmcs/components/other.mk
 */
#define VCHIQ_AUTO_REGISTER_SERVICE(name,init)      \
   pragma Data(LIT, ".vchiq_services");                   \
   static const VCHIQ_SERVICE_INFO_T init##_info = {init,name};   \
   pragma Data; \
   const VCHIQ_SERVICE_INFO_T *init##_info_p(void) { return &init##_info; }

#define VCHI_AUTO_REGISTER_SERVICE(name)      \
   pragma Data(LIT, ".vchiq_services");                   \
   const const VCHI_SERVICE_INFO_T init##_info = {init,name};   \
   pragma Data; \
   const VCHI_SERVICE_INFO_T *init##_info_p(void) { return &init##_info; }

#endif

