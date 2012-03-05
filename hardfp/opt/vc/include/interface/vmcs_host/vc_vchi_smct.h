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
*/

#ifndef __VC_VCHI_SMCT_H__INCLUDED__
#define __VC_VCHI_SMCT_H__INCLUDED__

#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"

#include "vc_smct_defs.h"

/* Forward declare.
*/
typedef struct opaque_vc_vchi_smct_handle_t *VC_VCHI_SMCT_HANDLE_T;

/* Initialize the shared memory cache test service, opens up vchi connection to talk to it.
*/
VC_VCHI_SMCT_HANDLE_T vc_vchi_smct_init( VCHI_INSTANCE_T vchi_instance,
                                         VCHI_CONNECTION_T **vchi_connections,
                                         uint32_t num_connections );

/* Terminates the shared memory cache test service.
*/
VCOS_STATUS_T vc_vchi_smct_stop( VC_VCHI_SMCT_HANDLE_T *handle );

/* Ask the shared memory cache test service to take ownership of a resource block
** identified and apply its test scenario onto it.
*/
VCOS_STATUS_T vc_vchi_smct_take( VC_VCHI_SMCT_HANDLE_T handle,
                                 VC_SMCT_TAKE_T *take,
                                 VC_SMCT_TAKE_RESULT_T *take_result,
                                 uint32_t *trans_id );

#endif /* __VC_VCHI_SMCT_H__INCLUDED__ */
