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
* Contains global defs used by submodules within vchi.
*/

#ifndef VCHI_COMMON_H_
#define VCHI_COMMON_H_


//flags used when sending messages (must be bitmapped)
typedef enum
{
   VCHI_FLAGS_NONE                      = 0x0,
   VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE   = 0x1,   // waits for message to be received, or sent (NB. not the same as being seen on other side)
   VCHI_FLAGS_CALLBACK_WHEN_OP_COMPLETE = 0x2,   // run a callback when message sent
   VCHI_FLAGS_BLOCK_UNTIL_QUEUED        = 0x4,   // return once the transfer is in a queue ready to go
   VCHI_FLAGS_ALLOW_PARTIAL             = 0x8,
   VCHI_FLAGS_BLOCK_UNTIL_DATA_READ     = 0x10,
   VCHI_FLAGS_CALLBACK_WHEN_DATA_READ   = 0x20,

   VCHI_FLAGS_ALIGN_SLOT            = 0x000080,  // internal use only
   VCHI_FLAGS_BULK_AUX_QUEUED       = 0x010000,  // internal use only
   VCHI_FLAGS_BULK_AUX_COMPLETE     = 0x020000,  // internal use only
   VCHI_FLAGS_BULK_DATA_QUEUED      = 0x040000,  // internal use only
   VCHI_FLAGS_BULK_DATA_COMPLETE    = 0x080000,  // internal use only
   VCHI_FLAGS_INTERNAL              = 0xFF0000
} VCHI_FLAGS_T;

// constants for vchi_crc_control()
typedef enum {
   VCHI_CRC_NOTHING = -1,
   VCHI_CRC_PER_SERVICE = 0,
   VCHI_CRC_EVERYTHING = 1,
} VCHI_CRC_CONTROL_T;

//callback reasons when an event occurs on a service
typedef enum
{
   VCHI_CALLBACK_REASON_MIN,

   //This indicates that there is data available
   //handle is the msg id that was transmitted with the data
   //    When a message is received and there was no FULL message available previously, send callback
   //    Tasks get kicked by the callback, reset their event and try and read from the fifo until it fails
   VCHI_CALLBACK_MSG_AVAILABLE,
   VCHI_CALLBACK_MSG_SENT,
   VCHI_CALLBACK_MSG_SPACE_AVAILABLE, // XXX not yet implemented

   // This indicates that a transfer from the other side has completed
   VCHI_CALLBACK_BULK_RECEIVED,
   //This indicates that data queued up to be sent has now gone
   //handle is the msg id that was used when sending the data
   VCHI_CALLBACK_BULK_SENT,
   VCHI_CALLBACK_BULK_RX_SPACE_AVAILABLE, // XXX not yet implemented
   VCHI_CALLBACK_BULK_TX_SPACE_AVAILABLE, // XXX not yet implemented

   VCHI_CALLBACK_SERVICE_CLOSED,

   // this side has sent XOFF to peer due to lack of data consumption by service
   // (suggests the service may need to take some recovery action if it has
   // been deliberately holding off consuming data)
   VCHI_CALLBACK_SENT_XOFF,
   VCHI_CALLBACK_SENT_XON,

   // indicates that a bulk transfer has finished reading the source buffer
   VCHI_CALLBACK_BULK_DATA_READ,

   // power notification events (currently host side only)
   VCHI_CALLBACK_PEER_OFF,
   VCHI_CALLBACK_PEER_SUSPENDED,
   VCHI_CALLBACK_PEER_ON,
   VCHI_CALLBACK_PEER_RESUMED,
   VCHI_CALLBACK_FORCED_POWER_OFF,

#ifdef USE_VCHIQ_ARM
   // some extra notifications provided by vchiq_arm
   VCHI_CALLBACK_SERVICE_OPENED,
   VCHI_CALLBACK_BULK_RECEIVE_ABORTED,
   VCHI_CALLBACK_BULK_TRANSMIT_ABORTED,
#endif

   VCHI_CALLBACK_REASON_MAX
} VCHI_CALLBACK_REASON_T;

//Calback used by all services / bulk transfers
typedef void (*VCHI_CALLBACK_T)( void *callback_param, //my service local param
                                 VCHI_CALLBACK_REASON_T reason,
                                 void *handle ); //for transmitting msg's only



/*
 * Define vector struct for scatter-gather (vector) operations
 * Vectors can be nested - if a vector element has negative length, then
 * the data pointer is treated as pointing to another vector array, with
 * '-vec_len' elements. Thus to append a header onto an existing vector,
 * you can do this:
 *
 * void foo(const VCHI_MSG_VECTOR_T *v, int n)
 * {
 *    VCHI_MSG_VECTOR_T nv[2];
 *    nv[0].vec_base = my_header;
 *    nv[0].vec_len = sizeof my_header;
 *    nv[1].vec_base = v;
 *    nv[1].vec_len = -n;
 *    ...
 *
 */
typedef struct vchi_msg_vector {
   const void *vec_base;
   int32_t vec_len;
} VCHI_MSG_VECTOR_T;

// Opaque type for a connection API
typedef struct opaque_vchi_connection_api_t VCHI_CONNECTION_API_T;

// Opaque type for a message driver
typedef struct opaque_vchi_message_driver_t VCHI_MESSAGE_DRIVER_T;


// Iterator structure for reading ahead through received message queue. Allocated by client,
// initialised by vchi_msg_look_ahead. Fields are for internal VCHI use only.
// Iterates over messages in queue at the instant of the call to vchi_msg_lookahead -
// will not proceed to messages received since. Behaviour is undefined if an iterator
// is used again after messages for that service are removed/dequeued by any
// means other than vchi_msg_iter_... calls on the iterator itself.
typedef struct {
   struct opaque_vchi_service_t *service;
   void *last;
   void *next;
   void *remove;
} VCHI_MSG_ITER_T;


#endif // VCHI_COMMON_H_
