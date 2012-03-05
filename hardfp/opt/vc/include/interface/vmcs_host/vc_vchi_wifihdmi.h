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

#ifndef __VC_VCHI_WIFIHDMI_H__INCLUDED__
#define __VC_VCHI_WIFIHDMI_H__INCLUDED__

#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"

#include "vc_wifihdmi_defs.h"

/* Forward declare.
*/
typedef struct opaque_vc_vchi_wifihdmi_handle_t *VC_VCHI_WIFIHDMI_HANDLE_T;

/* Initialize the wifi over hdmi service, opens up vchi connection to talk to it.
*/
VC_VCHI_WIFIHDMI_HANDLE_T vc_vchi_wifihdmi_init( VCHI_INSTANCE_T vchi_instance,
                                                 VCHI_CONNECTION_T **vchi_connections,
                                                 uint32_t num_connections );

/* Terminates the wifi over hdmi service.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_end( VC_VCHI_WIFIHDMI_HANDLE_T *handle );

/* Initialize a pool of shared memory buffers for use by the data-pump.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_tx_pool( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                        uint32_t pool_size, 
                                        uint32_t unit_size );

/* Tell wifi-hdmi service to use a given buffer for a specific task.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_set( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                    VC_WIFIHDMI_SET_T *set,
                                    VC_WIFIHDMI_RESULT_T *result,
                                    uint32_t *trans_id );

/* Tell wifi-hdmi service to stop using a given buffer for a specific task.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_unset( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                      VC_WIFIHDMI_SET_T *set,
                                      VC_WIFIHDMI_RESULT_T *result,
                                      uint32_t *trans_id );

/* Tell wifi-hdmi service to recycle use of a given resource, typically means the
** resource processing at the host layer is done.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_rec( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                    VC_WIFIHDMI_REC_T *rec,
                                    VC_WIFIHDMI_RESULT_T *result,
                                    uint32_t *trans_id );

/* Tell wifi-hdmi service to start its data-pumping.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_start( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                      VC_WIFIHDMI_MODE_T *mode, 
                                      VC_WIFIHDMI_RESULT_T *result,
                                      uint32_t *trans_id );

/* Tell wifi-hdmi service to stop its data-pumping.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_stop( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                     VC_WIFIHDMI_MODE_T *mode,
                                     VC_WIFIHDMI_RESULT_T *result,
                                     uint32_t *trans_id );

/* Gets statistics information from the wifi-hdmi service to report to host.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_stats( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                      VC_WIFIHDMI_MODE_T *mode,
                                      VC_WIFIHDMI_STATS_T *stats,
                                      uint32_t *trans_id );

/* Checks the status of an audio stream associated with the wifi-hdmi service.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_audio_status( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                             VC_WIFIHDMI_STREAM_T *stream,
                                             VC_WIFIHDMI_STR_STA_RES_T *status,
                                             uint32_t *trans_id );

/* Tell wifi-hdmi service of an incoming socket connection request.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_skt_in( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                       VC_WIFIHDMI_SKT_T *skt,
                                       VC_WIFIHDMI_SKT_RES_T *skt_res,
                                       uint32_t *trans_id );

/* Tell wifi-hdmi service a socket has been disconnected.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_skt_dsc( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                        VC_WIFIHDMI_SKT_T *skt,
                                        VC_WIFIHDMI_RESULT_T *result,
                                        uint32_t *trans_id );

/* Tell wifi-hdmi service a socket has been closed.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_skt_end( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                        VC_WIFIHDMI_SKT_T *skt,
                                        VC_WIFIHDMI_RESULT_T *result,
                                        uint32_t *trans_id );

/* Tell wifi-hdmi service some data is available for a given socket connection.
*/
VCOS_STATUS_T vc_vchi_wifihdmi_skt_data( VC_VCHI_WIFIHDMI_HANDLE_T handle,
                                         VC_WIFIHDMI_SKT_DATA_T *skt_data,
                                         VC_WIFIHDMI_RESULT_T *result,
                                         uint32_t *trans_id );

#endif /* __VC_VCHI_WIFIHDMI_H__INCLUDED__ */
