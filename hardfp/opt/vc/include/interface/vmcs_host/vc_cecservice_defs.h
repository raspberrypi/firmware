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
* CEC service command enumeration.
*/

#ifndef _VC_CECSERVICE_DEFS_H_
#define _VC_CECSERVICE_DEFS_H_
#include "vcinclude/common.h"
#include "interface/vchi/message_drivers/message.h"

#define CECSERVICE_MSGFIFO_SIZE 1024
#define CECSERVICE_CLIENT_NAME MAKE_FOURCC("CECS")
#define CECSERVICE_NOTIFY_NAME MAKE_FOURCC("CECN")

//CEC service commands
typedef enum {
   VC_CEC_REGISTER_CMD = 0,
   VC_CEC_REGISTER_ALL,
   VC_CEC_DEREGISTER_CMD,
   VC_CEC_DEREGISTER_ALL,
   VC_CEC_SEND_MSG,
   VC_CEC_GET_LOGICAL_ADDR,
   VC_CEC_ALLOC_LOGICAL_ADDR,
   VC_CEC_RELEASE_LOGICAL_ADDR,
   VC_CEC_GET_TOPOLOGY,
   VC_CEC_SET_VENDOR_ID,
   VC_CEC_SET_OSD_NAME,
   VC_CEC_GET_PHYSICAL_ADDR,
   VC_CEC_GET_VENDOR_ID,
   //Add more commands here
   VC_CEC_END_OF_LIST
} VC_CEC_CMD_CODE_T;

//See vc_cec.h for details
//REGISTER_CMD
//Parameters: opcode to register (CEC_OPCODE_T sent as uint32)
//Reply: none

//REGISTER_ALL
//Parameters: none
//Reply: none

//DEREGISTER_CMD
//Parameters: opcode to deregister (CEC_OPCODE_T sent as uint32)
//Reply: none

//DEREGISTER_ALL
//Parameters: none
//Reply: none

//SEND_MSG
//Parameters: destination, length, 16 bytes buffer (message can only be at most 15 bytes however)
//Reply: none (callback)
typedef struct {
   uint32_t follower;
   uint32_t length;
   uint8_t payload[16]; //max. 15 bytes padded to 16
   uint32_t is_reply;   //non-zero if this is a reply, zero otherwise
} CEC_SEND_MSG_PARAM_T;

//GET_LOGICAL_ADDR
//Parameters: none
//Reply: logical address (uint8 returned as uint32)

//ALLOC_LOGICAL_ADDR
//Parameters: none
//Reply: none (callback)

//GET_TOPOLOGY
//Parameters: none
//Reply: topology (see VC_TOPOLOGY_T)

//SET_VENDOR_ID
//Parameters: vendor id (uint32)
//Reply: none

//Set OSD name
//Parameters: 14 byte char
//Reply: none
#define OSD_NAME_LENGTH 14

//GET_PHYSICAL_ADDR
//Parameter: none
//Reply: packed physical address returned as uint16

//GET_VENDOR_ID
//Parameter: logical address (CEC_AllDevices_T sent as uint32_t)
//Reply: (uint32_t vendor id)

#endif
