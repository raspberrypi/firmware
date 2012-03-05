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

#ifndef _VC_VCHI_LOGSERVER_H_
#define _VC_VCHI_LOGSERVER_H_

/* ---- Include Files ---------------------------------------------------- */

#include "vchost_config.h"
#include "interface/vchi/vchi.h"
#include "interface/vmcs_host/vc_logservice_defs.h"

/* ---- Public Constants and Types --------------------------------------- */

typedef void (*logserver_messages_callback_t)( VC_LOGSERVICE_MESSAGES_T *messages, uint32_t msgLen, void *user_data );

typedef struct opaque_logserver_service_t *VC_LOGSERVER_SERVICE_HANDLE_T;

typedef enum {
   VC_VCHI_LOGSERVER_STATE_UNKNOWN,
   VC_VCHI_LOGSERVER_STATE_RUNNING,
   VC_VCHI_LOGSERVER_STATE_PAUSED,
   VC_VCHI_LOGSERVER_STATE_STOPPED
} VC_VCHI_LOGSERVER_STATE;

/* ---- Public Variables ------------------------------------------------- */

/* ---- Functions -------------------------------------------------------- */

VC_LOGSERVER_SERVICE_HANDLE_T vc_vchi_logserver_init( VCHI_INSTANCE_T vchi_instance,
                                                      VCHI_CONNECTION_T **vchi_connection,
                                                      uint32_t num_connections,
                                                      uint32_t target );

int32_t vc_vchi_logserver_start( VC_LOGSERVER_SERVICE_HANDLE_T instance );

int32_t vc_vchi_logserver_stop( VC_LOGSERVER_SERVICE_HANDLE_T instance );

int32_t vc_vchi_logserver_pause( VC_LOGSERVER_SERVICE_HANDLE_T instance );

int32_t vc_vchi_logserver_resume( VC_LOGSERVER_SERVICE_HANDLE_T instance );

VC_VCHI_LOGSERVER_STATE vc_vchi_logserver_get_state( VC_LOGSERVER_SERVICE_HANDLE_T instance );

int32_t vc_vchi_logserver_set_log_file( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                        FILE *pFileDesc );

void logserver_set_message_callback( VC_LOGSERVER_SERVICE_HANDLE_T instance, logserver_messages_callback_t callback, void *user_data );

void logserver_request_messages( VC_LOGSERVER_SERVICE_HANDLE_T instance, size_t maxReplySize );

void logserver_flush_messages( VC_LOGSERVER_SERVICE_HANDLE_T instance );

int32_t vc_vchi_logserver_send_test_msg( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                         int msgNum );

int32_t vc_vchi_logserver_get_config( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                      VC_LOGSERVICE_CONFIG_T       *config );

int32_t vc_vchi_logserver_modify_host_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                                  uint32_t enable_mask,
                                                  uint32_t disable_mask );

int32_t vc_vchi_logserver_set_host_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                               uint32_t filter );

int32_t vc_vchi_logserver_get_host_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                               uint32_t *filter );

int32_t vc_vchi_logserver_modify_vc_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                                uint32_t enable_mask,
                                                uint32_t disable_mask );

int32_t vc_vchi_logserver_set_vc_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                             uint32_t filter );

int32_t vc_vchi_logserver_get_vc_msg_filter( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                             uint32_t *filter );

int32_t vc_vchi_logserver_get_show_timestamp( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                              int32_t *show_timestamp );

int32_t vc_vchi_logserver_set_show_timestamp( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                               int32_t show_timestamp );

int32_t vc_vchi_logserver_get_show_delta_time( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                               int32_t *show_delta_time );

int32_t vc_vchi_logserver_set_show_delta_time( VC_LOGSERVER_SERVICE_HANDLE_T instance,
                                               int32_t show_deltatime );

#endif  // _VC_VCHI_LOGSERVER_H_
