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

#ifndef __VC_SMCT_DEFS_H__INCLUDED__
#define __VC_SMCT_DEFS_H__INCLUDED__

// FourCC code used for VCHI connection
#define VC_SMCT_SERVER_NAME MAKE_FOURCC("SMCT")

// Maximum message length
#define VC_SMCT_MAX_MSG_LEN (sizeof( VC_SMCT_MSG_UNION_T ) + \
                             sizeof( VC_SMCT_MSG_HDR_T ))
#define VC_SMCT_MAX_RSP_LEN (sizeof( VC_SMCT_MSG_UNION_T ))

// Resource name maximum size
#define VC_SMCT_RESOURCE_NAME 32

// All message types supported for HOST->VC direction
typedef enum
{
   VC_SMCT_MSG_TYPE_TAKE,              // Take ownership of the buffer, apply test.

   VC_SMCT_MSG_TYPE_MAX

} VC_SMCT_MSG_TYPE;

// Message header for all messages in HOST->VC direction
typedef struct
{
   int32_t type;      // Message type (VC_SMCT_MSG_TYPE)
   uint32_t trans_id; // Transaction identifier (unique)
   uint8_t body[0];   // Pointer to message body (if exists)

} VC_SMCT_MSG_HDR_T;

// Request to take ownership of the buffer (HOST->VC)
typedef struct
{
   uint32_t res_handle;    // Resource handle
   uint32_t res_size;      // Size given

   uint32_t in_chksum;     // Checksum calculated by host for data passed in

} VC_SMCT_TAKE_T;

// Generic result for a request (VC->HOST)
typedef struct
{
   uint32_t trans_id;       // Transaction identifier
   int32_t success;         // Action status

} VC_SMCT_RESULT_T;

// Result of a 'take' operation (VC->HOST)
typedef struct
{
   uint32_t trans_id;      // Transaction identifier
   int32_t success;        // Action status

   uint32_t out_chksum;    // Checksum calculated by videocore for data passed out
   uint32_t in_checked;    // Whether or not videocore checksum on data passed in
                           // was in agreement with the host checksum.

} VC_SMCT_TAKE_RESULT_T;

// Union of ALL messages
typedef union
{
   VC_SMCT_TAKE_T        take;
   VC_SMCT_TAKE_RESULT_T take_result;
   VC_SMCT_RESULT_T      result;

} VC_SMCT_MSG_UNION_T;

#endif /* __VC_SMCT_DEFS_H__INCLUDED__ */

