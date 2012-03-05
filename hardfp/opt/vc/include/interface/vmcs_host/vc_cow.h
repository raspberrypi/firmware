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
* General "CEC OVER WIFI" common definitions.
*/

#ifndef VC_COW_H
#define VC_COW_H

#define COW_MSG_PAYLOAD_SIZE_MAX    16   //Maximum CEC msg is 16 bytes long (incl. hdr and len)
#define COW_MSG_SIZE_MAX            (COW_MSG_PAYLOAD_SIZE_MAX+sizeof(COW_MSG_HEADER_T))

// define cow msg types send over clc link
typedef enum {
    COW_SERVER_CTRL_MSG      = 0,
    COW_CLIENT_CTRL_MSG,
    COW_DEVICE_CTRL_MSG,  
} COW_MSG_TYPE_T;

// common header shared by all types of cow msgs
typedef struct {
    COW_MSG_TYPE_T      type;
    int32_t             size;   // payload size in bytes, including cec msg header but not cec msg len
} COW_MSG_HEADER_T;

// define cow msg, data size limited by COW_MSG_SIZE_MAX
typedef struct {
    COW_MSG_HEADER_T    header;

    // Payload of a cow msg can be a standard cec msg: |hdr|opcode|params...|
    uint8_t             data[COW_MSG_PAYLOAD_SIZE_MAX]; 
} COW_MSG_T;


#endif // VC_COW_H
