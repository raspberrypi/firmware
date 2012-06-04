/*
* Copyright (c) 2012 Broadcom Europe Ltd
*
* Licensed to the Apache Software Foundation (ASF) under one or more
* contributor license agreements.  See the NOTICE file distributed with
* this work for additional information regarding copyright ownership.
* The ASF licenses this file to You under the Apache License, Version 2.0
* (the "License"); you may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*
* VMCS framework - autoregistering VCHI services.
*/

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

