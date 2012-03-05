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
* HDCP2 service API (Tx)
* See vc_hdcp2.h typedefs
*/

#ifndef _VC_HDCP2_TX_SERVICE_H_
#define _VC_HDCP2_TX_SERVICE_H_

#include "vcinclude/common.h"
#include "interface/vcos/vcos.h"
#include "interface/vchi/vchi.h"
#include "interface/vmcs_host/vc_hdcp2service_defs.h"


/**
 * \file
 *
 * This API defines the Tx host side HDCP2 service.
 * Define ENABLE_HDCP2_LOOPBACK_TEST in HDCP2 Tx/Rx services/state machine
 * to test HDCP2 local loopback.
 */

/**
 * <DFN>vc_vchi_hdcp2_tx_init</DFN> is called at the beginning of the application
 * to initialise the client to Tx side HDCP2 service
 * 
 * @param initialise_instance is the VCHI instance [in]
 *
 * @param connections is the array of pointers of connections [in]
 * 
 * @param num_connections is the length of the array [in]
 *
 * @return void
 */
VCHPRE_ void VCHPOST_ vc_vchi_hdcp2_tx_init(VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections );

/**
 * <DFN>vc_vchi_hdcp2_tx_stop</DNF> stops the Tx host side HDCP2 service
 *
 * @param none
 *
 * @return void
 */
VCHPRE_ void VCHPOST_ vc_vchi_hdcp2_tx_stop( void );

/**
 * Host applications must call <DFN>vc_hdcp2_tx_register_callback</DNF> at 
 * the beginning to register a function to handle all outgoing message
 * from HDCP2 Tx state machine. Note that notifications from 
 * state machine also come in the form of outgoing message, so you have
 * to look at the message type.
 *
 * @param callback function [in]
 *
 * @param callback_data is the context to be passed when function is called [in]
 *
 * @return void
 */
VCHPRE_ void VCHPOST_ vc_hdcp2_tx_register_callback(HDCP2SERVICE_CALLBACK_T callback, void *callback_data);

/**
 * Use <DFN>vc_hdcp2_tx_send_message</DFN> to send message [from Rx] to
 * HDCP2 Tx state machine. You should only use this to send genuine 
 * HDCP2 message.
 *
 * @param buffer is the message buffer [in]
 *
 * @param buffer_size is the size [in]
 *
 * @return zero if message is successfully transmitted, non-zero otherwise
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_send_message(const void *buffer, uint32_t buffer_size); 

/**
 * Use <DFN>vc_hdcp2_tx_set_hpd</DFN> to set the hotplug status on Tx side.
 * HDCP2 can only start if hotplug is asserted.
 * In practise this is triggered by HDCP2 Rx state machine via HDCP2 Rx service.
 *
 * @param hotplug status [in] (non-zero means attached, zero means detached)
 * 
 * @return zero if command is successfully sent, non-zero otherwise
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_set_hpd(VC_HDCP2_HP_STATUS_T hpd_status);

/**
 * Use <DFN>vc_hdcp2_tx_begin_authentication</DFN> to start authentication.
 * If an authentication has already started, this will restart it.
 * If the link is already authenticated, this will reset the authentication
 * and start a new one. 
 *
 * @param none
 *
 * @return zero if authentication successfully start, non-zero otherwise
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_begin_authentication(void);

/**
 * <DFN>vc_hdcp2_tx_is_authenticated</DFN> returns whether there is 
 * currently an authenticated link or not.
 *
 * @param pointer to auth [out], non-zero if the link is authenticated, zero otherwise
 *
 * @return zero if the command is sent successfully, auth is also set to zero if 
 *         command failed 
 *
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_is_authenticated(uint32_t *auth);

/**
 * <DFN>vc_hdcp2_tx_reset_ctr</DFN> resets the counter of a particular stream.
 * stream_id is converted into big endian streamCtr internally. This
 * function is only for debug.
 *
 * @param stream_id is the stream id  [in]
 *
 * @param inputCtr is the counter value (64-bit big endian) [in]
 *
 * @return zero if command is sent successfully
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_reset_ctr(uint32_t stream_id, uint64_t inputCtr);

/**
 * <DFN>vc_hdcp2_tx_get_ctr</DFN> returns the current counter of a particular stream.
 * stream_id is converted into big endian streamCtr internally. This
 * function is only for debug.
 *
 * @param stream_id is the stream id [in]
 *
 * @param pointer to inputCtr is the counter value (64-bit big endian) [out]
 *
 * @return zero if command is sent successfully, if failed, inputCtr is not modified
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_get_ctr(uint32_t stream_id, uint64_t *inputCtr);

/**
 * <DFN>vc_hdcp2_tx_shutdown</DFN> explicitly shutdown an authenticated link.
 * By default an authenticated link will stay authenticated until Tx side
 * is notified the Rx is no longer there. You will get a notification callback
 * with no error
 *
 * @param none
 *
 * @return zero if command is sent successfully,
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_shutdown(void);

/**
 * <DFN>vc_hdcp2_tx_expunge_id</DFN> deletes a receiver id from Tx pairing store.
 *
 * @param receiver id
 *
 * @return zero if id is deleted successfully
 */
VCHPRE_ int VCHPOST_ vc_hdcp2_tx_expunge_id(const uint8_t *id);

#endif
