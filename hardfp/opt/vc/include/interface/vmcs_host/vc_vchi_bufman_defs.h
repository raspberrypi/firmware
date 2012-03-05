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
* Bufman service using VCHI
*/

#ifndef VC_VCHI_BUFMAN_DEFS_H
#define VC_VCHI_BUFMAN_DEFSH

#ifdef __SYMBIAN32__
typedef uint32_t DISPMANX_RESOURCE_HANDLE_T;
namespace BufManX {
#else
#include "interface/vmcs_host/vc_dispmanx.h"
#endif

typedef enum {
   // Insert extra frame types here
   FRAME_HOST_IMAGE_BASE = 0x20000, // Base for host format images
   FRAME_HOST_IMAGE_EFormatYuv420P,
   FRAME_HOST_IMAGE_EFormatYuv422P,
   FRAME_HOST_IMAGE_EFormatYuv422LE,
   FRAME_HOST_IMAGE_EFormatRgb565,
   FRAME_HOST_IMAGE_EFormatRgb888,
   FRAME_HOST_IMAGE_EFormatRgbU32,
   FRAME_HOST_IMAGE_EFormatRgbA32,
   FRAME_HOST_IMAGE_EFormatRgbA32LE,
   FRAME_HOST_IMAGE_EFormatRgbU32LE,

   FRAME_FORCE_FIELD_WIDTH = 0xFFFFFFFF
} buf_frame_type_t;

typedef enum {
    //host to videocore
    VC_BUFMAN_CONVERT_UNUSED = 0,
    VC_BUFMAN_PULL_FRAME,
    VC_BUFMAN_PUSH_FRAME,
    VC_BUFMAN_MESSAGE_RESPONSE,
    VC_BUFMAN_SYNC,
    VC_BUFMAN_ALLOC_BUF,
    VC_BUFMAN_FREE_BUF,
    VC_BUFMAN_PULL_MULTI,
    VC_BUFMAN_PUSH_MULTI,
    VC_BUFMAN_PUSH_MULTI_STREAM,
    //vc to host
    VC_BUFMAN_FRAME_SENT_CALLBACK,
    VC_BUFMAN_FORCE_WIDTH = 0x7fffffff,
} buf_command_t;

/* A header used for all messages sent and received by bufman.
 */
typedef struct {
   buf_command_t command;
} BUF_MSG_HDR_T;

/* General remotely call this bufman operation commands */
typedef struct {
   uint32_t resource_handle;
   buf_frame_type_t type;
   int32_t size, width, height, pitch;
   VC_RECT_T src_rect;  // in 16.16 units
   VC_RECT_T dest_rect; // in 32.0 units
} BUF_MSG_REMOTE_FUNCTION_FRAME_T;

typedef struct {
   int32_t status;
   int32_t total_stripes;
   // normal stipe height and size
   int32_t stripe_height, stripe_size;
   // last stripe size (if height not a mulitple of stripe height, last stripe nay be smaller)
   int32_t last_stripe_height, last_stripe_size;
} BUF_MSG_RESPONSE_T;

typedef struct
{
   uint32_t stream;
   uint32_t num_of_buffers;
   buf_frame_type_t type;
   uint32_t width;
   uint32_t height;
} BUF_MSG_ALLOC_BUF_FRAME_T;

typedef struct
{
   uint32_t stream;
   uint32_t num_of_buffers;
} BUF_MSG_FREE_BUF_FRAME_T;

typedef struct {
   BUF_MSG_HDR_T hdr;
   union {
      BUF_MSG_REMOTE_FUNCTION_FRAME_T frame;
      BUF_MSG_RESPONSE_T message_response;
      BUF_MSG_ALLOC_BUF_FRAME_T alloc_buf_frame;
      BUF_MSG_FREE_BUF_FRAME_T free_buf_frame;
   } u;
} BUF_MSG_T;

enum {
   //host to videocore
   VC_BUFMAN_ERROR_NONE = 0,
   VC_BUFMAN_ERROR_BAD_GENERALLY = -1,
   VC_BUFMAN_ERROR_BAD_RESOURCE = -2,
   VC_BUFMAN_ERROR_BAD_TRANSFORM = -3,
   VC_BUFMAN_ERROR_BAD_RESIZE = -4,
   VC_BUFMAN_ERROR_BAD_HOST_FORMAT = -5,
   VC_BUFMAN_ERROR_BAD_VC_FORMAT = -6,
   VC_BUFMAN_ERROR_BAD_SIZE = -7,
};

#ifdef __SYMBIAN32__
} // namespace BufManX
#endif

#endif /* VC_VCHI_BUFMAN_DEFS_H */
