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

/**
*
*  @file    vc_logservice_defs.h
*
*  @brief   A VCHI service for retrieving messages from the videocore logs
*
****************************************************************************/

#ifndef _VC_LOGSERVICE_DEFS_H_
#define _VC_LOGSERVICE_DEFS_H_

#include "interface/vcos/vcos_stdint.h"

#define LOG_SERVER_NAME         MAKE_FOURCC("LOGS")
#define LOG_SERVER_NOTIFY_NAME  MAKE_FOURCC("LOGN")

#define LOG_SERVER_MAX_MSG_LEN  VCHI_MAX_MSG_SIZE

typedef enum
{
    VC_LOGSERVICE_REQUEST_MESSAGES,
    VC_LOGSERVICE_MESSAGES,
    VC_LOGSERVICE_UPDATE_HOST_MSG_FILTER,
    VC_LOGSERVICE_UPDATE_VC_MSG_FILTER,
    VC_LOGSERVICE_FLUSH_MESSAGES,
    VC_LOGSERVICE_SET_CONFIG_FLAG,
    VC_LOGSERVICE_GET_CONFIG,

    VC_LOGSERVICE_NOTIFY_NEW_MSGS       = 50,

    VC_LOGSERVICE_TEST_LOG              = 100,
    VC_LOGSERVICE_TEST_ASSERT,
    VC_LOGSERVICE_TEST_NOTIFY,
    VC_LOGSERVICE_TEST_REPLY,
    VC_LOGSERVICE_TEST_REPLY2,

} VC_LOGSERVICE_CMD_CODE_T;

typedef struct
{
    uint32_t    cmd;
    uint32_t    maxReplyLen;

} VC_LOGSERVICE_REQUEST_MESSAGES_T;

// The following mirrors LOG_FORMAT_T from logging.h

typedef enum
{
    VC_LOGSERVICE_FIFO_LOG          = 1,
    VC_LOGSERVICE_ASSERTION_LOG     = 2,
    VC_LOGSERVICE_TASK_LOG          = 3,

    vc_LOGSERVICE_FORMAT_DUMMY      = 0x7fffffff    // Forces enum to be 32-bits

} VC_LOGSERVICE_LOG_FORMAT_T;

typedef struct
{
    VC_LOGSERVICE_LOG_FORMAT_T  logFormat;
    uint32_t                    time;
    uint16_t                    seqNum;
    uint16_t                    size;

    // The null terminated C string follows after this header.
    char            logStr[0];

} VC_LOGSERVICE_LOG_HDR_T;

typedef struct
{
    uint32_t        cmd;
    uint32_t        flags;
    uint32_t        numLogEntries;

    // This structure is followed by 'numLogEntries' log messages. Each log message
    // consists of a header followed by some variable length message data.

} VC_LOGSERVICE_MESSAGES_T;

typedef struct
{
    uint32_t        cmd;
    uint32_t        filter_enable_mask;
    uint32_t        filter_disable_mask;

} VC_LOGSERVICE_FILTER_T;

#define VC_LOGSERVICE_CONFIG_FLAG_CONNECTED         ( 1 << 0 )
#define VC_LOGSERVICE_CONFIG_FLAG_PAUSED            ( 1 << 1 )
#define VC_LOGSERVICE_CONFIG_FLAG_SHOW_TIMESTAMP    ( 1 << 2 )
#define VC_LOGSERVICE_CONFIG_FLAG_SHOW_DELTATIME    ( 1 << 3 )

typedef struct
{
    uint32_t    cmd;
    uint32_t    vc_msg_filter;
    uint32_t    host_msg_filter;
    uint32_t    flags;

} VC_LOGSERVICE_CONFIG_T;

typedef struct
{
    uint32_t    cmd;
    uint32_t    flag_mask;
    uint32_t    value;      // 0 or 1

} VC_LOGSERVICE_SET_CONFIG_FLAG_T;

#endif // _VC_LOGSERVICE_DEFS_H_

