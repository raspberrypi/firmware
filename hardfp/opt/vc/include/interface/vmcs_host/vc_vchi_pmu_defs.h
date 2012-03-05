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
* Definitions used by both the client and server sides
*/

#ifndef PMUSERV_DEFS_H
#define PMUSERV_DEFS_H

#include "interface/vchi/vchi.h"

//==============================================================================

#define PMU_NAME  MAKE_FOURCC("PMU_")

typedef enum
{
   PMU_MSG_ENABLE_USB,
   PMU_MSG_USB_CONNECTED,
   PMU_MSG_GET_BATTERY_STATUS
} PMU_MSG_ID_T;

typedef struct
{
   uint32_t msg_id;
   uint32_t data;
} PMU_MSG_T;

#endif /* PMUSERV_DEFS_H */

//==============================================================================
