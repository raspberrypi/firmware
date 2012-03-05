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

#ifndef VC_VCHI_HAUD_H
#define VC_VCHI_HAUD_H

#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"
#include "interface/vmcs_host/vc_haud.h"

VCHPRE_ VC_HAUD_HANDLE_T VCHPOST_ vc_vchi_haud_init( VC_HAUD_DATA_REQ_CBK cbk, VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **ppCnxs, uint32_t num_cnxs );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_exit( VC_HAUD_HANDLE_T hdl );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_open( VC_HAUD_HANDLE_T hdl, VC_HAUD_CODEC_T encoding, uint32_t sample_rate, uint32_t num_chans, uint32_t chan_mask, void *pCodecCfg );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_close( VC_HAUD_HANDLE_T hdl );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_start( VC_HAUD_HANDLE_T hdl );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_stop( VC_HAUD_HANDLE_T hdl );
VCHPRE_ uint32_t VCHPOST_ vc_vchi_haud_get_available_space( VC_HAUD_HANDLE_T hdl );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_sine( VC_HAUD_HANDLE_T hdl, uint32_t enable, uint32_t freq, uint32_t chanmask );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_write( VC_HAUD_HANDLE_T hdl, int8_t *pBuf, uint32_t size );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_query_info( VC_HAUD_HANDLE_T hdl, VC_HAUD_INFO_T *pInfo );
VCHPRE_ int32_t VCHPOST_ vc_vchi_haud_query_dbg( VC_HAUD_HANDLE_T hdl, VC_HAUD_DBG_T *pDbg );

#endif /* VC_VCHI_HAUD_H */
