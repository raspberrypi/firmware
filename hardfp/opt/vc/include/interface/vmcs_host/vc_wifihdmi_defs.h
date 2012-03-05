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

#ifndef __VC_WIFIHDMI_DEFS_H__INCLUDED__
#define __VC_WIFIHDMI_DEFS_H__INCLUDED__

typedef void* (*SOCKET_CALLBACK) (int socket_handle, void *data);

// FourCC code used for VCHI connection
#define VC_WIFIHDMI_SERVER_NAME       MAKE_FOURCC("WHSV")
#define VC_WIFIHDMI_SERVER_FAST_NAME  MAKE_FOURCC("WHSF")
#define VC_WIFIHDMI_NOTIFY_CTRL_NAME  MAKE_FOURCC("WHNS")
#define VC_WIFIHDMI_NOTIFY_DATA_NAME  MAKE_FOURCC("WHND")
#define VC_WIFIHDMI_NOTIFY_AUDIN_NAME MAKE_FOURCC("WHAI")

// Maximum message length
#define VC_WIFIHDMI_MAX_MSG_LEN (sizeof( VC_WIFIHDMI_MSG_UNION_T ) + \
                                 sizeof( VC_WIFIHDMI_MSG_HDR_T ))
#define VC_WIFIHDMI_MAX_RSP_LEN (sizeof( VC_WIFIHDMI_MSG_UNION_T ))

#define VC_WIFIHDMI_MAX_DATA_LEN  2048 
#define VC_WIFIHDMI_RESOURCE_NAME 32

// All message types supported
typedef enum
{
   // HOST->VC
   VC_WIFIHDMI_MSG_TYPE_SET,
   VC_WIFIHDMI_MSG_TYPE_UNSET,
   VC_WIFIHDMI_MSG_TYPE_REC,
   VC_WIFIHDMI_MSG_TYPE_STATS,

   VC_WIFIHDMI_MSG_TYPE_SKT_IN,
   VC_WIFIHDMI_MSG_TYPE_SKT_DSC,
   VC_WIFIHDMI_MSG_TYPE_SKT_DATA,
   VC_WIFIHDMI_MSG_TYPE_SKT_END,

   VC_WIFIHDMI_MSG_TYPE_START,
   VC_WIFIHDMI_MSG_TYPE_STOP,

   VC_WIFIHDMI_MSG_TYPE_AUDIO_STREAM_STAT,
   VC_WIFIHDMI_MSG_TYPE_AUDIO_DATA,

   // VC->HOST
   VC_WIFIHDMI_MSG_TYPE_SKT_OPEN,
   VC_WIFIHDMI_MSG_TYPE_SKT_CLOSE,
   VC_WIFIHDMI_MSG_TYPE_SKT_LISTEN,
   VC_WIFIHDMI_MSG_TYPE_TX_DATA,
   VC_WIFIHDMI_MSG_TYPE_FRAME_TOGGLE,

   VC_WIFIHDMI_MSG_TYPE_MAX

} VC_WIFIHDMI_MSG_TYPE;

typedef enum
{
   VC_WIFIHDMI_RESERVED_NONE,
   VC_WIFIHDMI_RESERVED_AUDIO,
   VC_WIFIHDMI_RESERVED_VIDEO

} VC_WIFIHDMI_RESERVED;

// Message header for all messages in HOST->VC direction
typedef struct
{
   int32_t type;      // Message type (VC_SMCT_MSG_TYPE)
   uint32_t trans_id; // Transaction identifier (unique)
   uint8_t body[0];   // Pointer to message body (if exists)

} VC_WIFIHDMI_MSG_HDR_T;

// Generic result for a request (VC->HOST)
typedef struct
{
   uint32_t trans_id;       // Transaction identifier
   int32_t success;         // Action status

} VC_WIFIHDMI_RESULT_T;

// Socket operation result for a request (VC->HOST)
typedef struct
{
   uint32_t trans_id;       // Transaction identifier
   int32_t  success;        // Action status
   uint32_t handle;

} VC_WIFIHDMI_SKT_RES_T;

// Stream status result for a request (VC->HOST)
typedef struct
{
   uint32_t trans_id;       // Transaction identifier
   int32_t  success;        // Action status
   uint32_t enabled;

} VC_WIFIHDMI_STR_STA_RES_T;

// Request to set a buffer for a specific purpose (HOST->VC)
typedef struct
{
   uint32_t res_handle;             // Handle reference
   uint32_t res_inthdl;             // Internal handle reference
   uint32_t res_size;               // Size of resource

} VC_WIFIHDMI_SET_T;

// Request to recycle a buffer for a specific purpose (HOST->VC)
typedef struct
{
   uint32_t res_handle;             // Handle reference

} VC_WIFIHDMI_REC_T;

// Audio data available on specific handle (HOST->VC)
typedef struct
{
   uint32_t res_handle;             // Handle reference
   uint32_t res_payload;            // Size of payload data in handle

} VC_WIFIHDMI_AUD_IN_T;

// Request to process a notification (VC->HOST)
typedef struct
{
   uint32_t res_handle;             // Handle reference
   uint32_t res_size;               // Payload to ship out
   uint32_t res_socket;             // "Socket" on which to send this payload
   uint32_t res_rem_addr;           // Remote address to send this payload to
   uint32_t res_rem_port;           // Remote port to send this payload to

} VC_WIFIHDMI_TX_DATA_T;

// Mode request used with start/stop command (HOST->VC)
typedef struct
{
   uint32_t loopback;
   uint32_t wifihdmi;

} VC_WIFIHDMI_MODE_T;

// Socket connection information (HOST->VC)
typedef struct
{
   uint32_t handle;
   uint32_t address;
   uint16_t port;

} VC_WIFIHDMI_SKT_T;

// Socket connection data (HOST->VC)
typedef struct
{
   uint32_t handle;
   uint32_t data_len;
   uint32_t data_handle;

} VC_WIFIHDMI_SKT_DATA_T;

// Stream identifier (HOST->VC)
typedef struct
{
   uint32_t handle;

} VC_WIFIHDMI_STREAM_T;

// Socket action information (VC->HOST)
typedef struct
{
   uint32_t socket_handle;
   uint16_t socket_port;
   uint16_t socket_send_only;

} VC_WIFIHDMI_SKT_ACTION_T;

// Miscellaneous stats collected on VC to be queried by HOST
typedef struct
{
   uint32_t trans_id;       // Transaction identifier
   
   uint32_t tx_pool;
   uint32_t tx_aud_pool;
   uint32_t tx_vid_pool;
   uint32_t tx_misc_pool;

   uint32_t tx_snd;         // Transmit (asked to be sent)
   uint32_t tx_cnt;         // Transmit (queued up and signaled to host)
   uint32_t tx_dst_cnt;     // Transmit (with destination) counter (queued up and signaled to host)
   uint32_t tx_miss_cnt;    // Transmit miss
   uint32_t tx_retry_cnt;   // Transmit retry
   uint32_t tx_retry2_cnt;  // Transmit retry (second counter)
   uint32_t tx_frame_cnt;   // Transmit frame counter (reported by application)
   uint32_t tx_rec_cnt;     // Transmit recycled counter
   uint32_t tx_busy_cnt;    // Transmit busied counter

   uint32_t tx_aud_cnt;     // Transmit audio packet
   uint32_t tx_aud_ret_cnt; // Transmit audio packet retried
   uint32_t tx_vid_cnt;     // Transmit video packet
   uint32_t tx_vid_ret_cnt; // Transmit video packet retried

} VC_WIFIHDMI_STATS_T;

// Union of ALL messages
typedef union
{
   VC_WIFIHDMI_SET_T         set;
   VC_WIFIHDMI_REC_T         rec;
   VC_WIFIHDMI_TX_DATA_T     txdata;
   VC_WIFIHDMI_STATS_T       stats;
   VC_WIFIHDMI_RESULT_T      result;
   VC_WIFIHDMI_MODE_T        mode;
   VC_WIFIHDMI_SKT_RES_T     skt_res;
   VC_WIFIHDMI_SKT_T         skt;
   VC_WIFIHDMI_SKT_DATA_T    skt_data;
   VC_WIFIHDMI_SKT_ACTION_T  skt_action;
   VC_WIFIHDMI_STREAM_T      stream;
   VC_WIFIHDMI_STR_STA_RES_T stream_res;
   VC_WIFIHDMI_AUD_IN_T      audio_in;

} VC_WIFIHDMI_MSG_UNION_T;

#endif /* __VC_WIFIHDMI_DEFS_H__INCLUDED__ */

