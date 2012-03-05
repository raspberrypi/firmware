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

#ifndef _VC_VCHI_PERFSTAT_H_
#define _VC_VCHI_PERFSTAT_H_

#include "vchost_config.h"
#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"
#include "interface/vmcs_host/vc_perfstat_defs.h"

typedef struct opaque_vc_vchi_perfstat_handle_t *VC_VCHI_PERFSTAT_HANDLE_T;

VC_VCHI_PERFSTAT_HANDLE_T vc_vchi_perfstat_init( VCHI_INSTANCE_T vchi_instance,
                                                 VCHI_CONNECTION_T **vchi_connections,
                                                 uint32_t num_connections );

VCOS_STATUS_T vc_vchi_perfstat_stop( VC_VCHI_PERFSTAT_HANDLE_T *handle );

VCOS_STATUS_T vc_vchi_perfstat_enable( VC_VCHI_PERFSTAT_HANDLE_T handle );

VCOS_STATUS_T vc_vchi_perfstat_disable( VC_VCHI_PERFSTAT_HANDLE_T handle );

VCOS_STATUS_T vc_vchi_perfstat_set_avg_mode( VC_VCHI_PERFSTAT_HANDLE_T handle,
                                             VC_PERFSTAT_AVG_MODE_T avg_mode );

VCOS_STATUS_T vc_vchi_perfstat_get_stat( VC_VCHI_PERFSTAT_HANDLE_T handle,
                                         VC_PERFSTAT_BLK_T blk,
                                         void *stat );

VCOS_STATUS_T vc_vchi_perfstat_reset_stat( VC_VCHI_PERFSTAT_HANDLE_T handle );

#endif // _VC_VCHI_PERFSTAT_H_
