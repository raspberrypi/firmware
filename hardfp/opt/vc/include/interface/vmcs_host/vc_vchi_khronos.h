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
* Khronos Service host side API
*/

#ifndef VC_VCHI_KHRONOS_H
#define VC_VCHI_KHRONOS_H

#include "vchost_config.h"
#include "interface/vchi/vchi.h"


/* Initialise Khronos service. This initialises the host side of the interface, 
   it does not send anything to VideoCore. */
VCHPRE_ void VCHPOST_ vc_vchi_khronos_init( VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections );

#endif // ifndef VC_VCHI_KHRONOS_H
