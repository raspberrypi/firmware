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
* HDCP2 service definitions. Define ENABLE_HDCP2_LOOPBACK_TEST to test HDCP2 local loopback.
*/

#ifndef _VC_HDCP2SERVICE_DEFS_H_
#define _VC_HDCP2SERVICE_DEFS_H_
#include "vcinclude/common.h"
#include "interface/vmcs_host/vc_hdcp2.h"
#include "middleware/hdcp2/common/hdcp2_common.h"

#define HDCP2SERVICE_MSGFIFO_SIZE 4096
#define HDCP2SERVICE_TX_CLIENT_NAME MAKE_FOURCC("HDTS")
#define HDCP2SERVICE_TX_NOTIFY_NAME MAKE_FOURCC("HDTN")
#define HDCP2SERVICE_RX_CLIENT_NAME MAKE_FOURCC("HDRS")
#define HDCP2SERVICE_RX_NOTIFY_NAME MAKE_FOURCC("HDRN")

/**
 * HDCP2 service commands (Host <-> VC)
 * Unless otherwise stated, most of these commands do not have replies
 */
typedef enum {
   /* Only the first two messages are essential for HDCP protocol */
   VC_HDCP2_CMD_MSG = 0,            //Normal HDCP2 messages (HDCP2_MSG_T) Tx and Rx both H<->V
   VC_HDCP2_CMD_HPD = 1,            //Hotplug (Rx side V->H, Tx side H->V)

   /* These messages are for debugging purposes */
   VC_HDCP2_CMD_NOTIFY = 2,         //Notification from state machine to host side (both Tx and Rx, V->H only)
   VC_HDCP2_CMD_GET_AUTH_STATE = 3, //Get authentication state, has reply (Both Tx and Rx, H->V)
   VC_HDCP2_CMD_ABORT = 4,          //Aborting authentication (Tx -> Rx host to host only). This is to let Rx host side know we have lost our link

   /* These are for host control HDCP2 Tx state machine H->V only */
   VC_HDCP2_CMD_START = 5,          //Start authentication
   VC_HDCP2_CMD_RESET_CTR = 6,      //Reset counter
   VC_HDCP2_CMD_GET_CTR = 7,        //Get counter (64-bit reply)
   VC_HDCP2_CMD_SHUTDOWN = 8,       //Shutdown the link (debug only)
   VC_HDCP2_CMD_EXPUNGE = 9,        //Expunge a receiver id (debug only)

#ifdef ENABLE_HDCP2_LOOPBACK_TEST
   VC_HDCP2_CMD_LOOPBACK,           //For loopback test
#endif

   VC_HDCP2_CMD_END_OF_LIST         //Place holder
} VC_HDCP2_CMD_CODE_T;


/**
 * Command type
 */
typedef struct {
   VC_HDCP2_CMD_CODE_T code;
} VC_HDCP2_CMD_TYPE_T;

/**
 * Sending/receiving HDCP2 message Tx<->Rx
 * @param HDCP2 message (variable size) in a compacted form (continuous stream of bytes)
 */
typedef struct {
   uint32_t msg_size;
   uint8_t msg[sizeof(HDCP2_MSG_T)];
} VC_HDCP2_MSG_PARAM_T;

/**
 * Communicate hotplug state Rx->Tx only
 * @param hotplug state
 */
typedef struct {
   uint32_t status;  /**<zero for HPD deassert, non-zero for HPD assert */
} VC_HDCP2_HPD_PARAM_T;

/**
 * Notification: Tx side: V->H
 * @param reason
 * @param param1
 * @param param2
 */
typedef struct {
   uint32_t reason;
   uint32_t param1;
   uint32_t param2;
} VC_HDCP2_NOTIFY_PARAM_T;

/**
 * Start authentication. Tx only. Allows the host to kick the authentication process
 * Reply will be if the authentication process can be started or not.
 * @param none
 */

/**
 * Get auth state message. Tx and Rx local (uint32_t reply, non-zero means the link is authenticated)
 * @param none
 */
  
/**
 * Aborting HDCP2 transaction Tx->Rx only
 * This is intended for Tx to tell Rx that the link is broken so the Rx side
 * host application can log. There is no provision in the HDCP2 protocol to Rx
 * to be notified of broken link.
 * @param abort reason
 */
typedef struct {
   HDCP2_ERROR_T reason;
} VC_HDCP2_ABORT_PARAM_T;

/**
 * Resetting inputCtr
 * Reply will be if the counter is reset successfully (zero) or not (non-zero)
 * @param stream to reset 
 *
 * @param counter value to reset to (64-bit big endian)
 */
typedef struct {
   uint32_t stream_id;
   uint64_t inputCtr;
} VC_HDCP2_RESET_CTR_PARAM_T;

/**
 * Get the current counter (64-bit reply of inputCtr in big endian)
 * @param stream id
 */
typedef struct {
   uint32_t stream_id;
} VC_HDCP2_GET_CTR_PARAM_T;

/**
 * Shuwdown. No reply, but there will be a notification saying the authentication 
 * link is now broken with no error.
 * @param none
 */

/**
 * Deleting pairing info, no reply.
 *
 * @param receiver id
 */
typedef struct {
   uint8_t id[HDCP2_ID_SIZE];
} VC_HDCP2_EXPUNGE_PARAM_T;

#ifdef ENABLE_HDCP2_LOOPBACK_TEST
/**
 * Loopback test message Tx->Rx only
 * @param time stamp of transmitted message
 *
 * @param actual message size in arrays below
 *
 * @param streamCtr
 *
 * @param inputCtr
 *
 * @param encrypted message (fixed size array)
 *
 * @param plain text message (fixed size array)
 */

//Max. size of message - must be a multiple of 16 bytes
#define MAX_LOOPBACK_PACKET_SIZE ((HDCP2SERVICE_MSGFIFO_SIZE >> 2) & ~0xF)

typedef struct {
   uint32_t stc;
   uint32_t buffer_size;
   uint32_t streamCtr;
   uint64_t inputCtr;
   uint8_t encrypted_buffer[MAX_LOOPBACK_PACKET_SIZE];
   uint8_t plaintext_buffer[MAX_LOOPBACK_PACKET_SIZE];
   uint32_t last_packet;
} VC_HDCP2_LOOPBACK_PARAM_T;

/**
 * This is reply for loopback message
 * 
 * @param time stamp of the decrypted message
 *
 * @param buffer size
 *
 * @param bytes in error 
 */
typedef struct {
   uint32_t stc;
   uint32_t buffer_size;
   uint32_t bytes_error;
} VC_HDCP2_LOOPBACK_REPLY_T;

#endif //ENABLE_HDCP2_LOOPBACK_TEST

/**
 * HDCP2SERVICE_CALLBACK_T is the callback function which gets called when a message
 * arrives from Videocore to host side, or vice versa.
 * Some messages are expected to be forwarded between Tx and Rx over whatever link there is.
 * This is the responsibility of the host application.
 *
 * @param callback_data is the callback data passed in callback_register function
 *
 * @param buffer is the message buffer
 *
 * @param size is the total size of message (including the size of msg_type)
 *
 * @return zero if successful, non-zero otherwise
 */

typedef int32_t (*HDCP2SERVICE_CALLBACK_T)(void *callback_data, const void *buffer, uint32_t size);
#endif
