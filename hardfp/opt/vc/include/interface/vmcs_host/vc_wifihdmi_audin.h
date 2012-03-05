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

#ifndef VC_WIFIHDMI_AUDIN_H
#define VC_WIFIHDMI_AUDIN_H

#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"

void *vc_wifihdmi_audin_init( VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **ppCnxs, uint32_t num_cnxs );
int32_t vc_wifihdmi_audin_exit( void *handle );
uint32_t vc_wifihdmi_audin_send( void *handle, int8_t *buffer, uint32_t size );
uint32_t vc_wifihdmi_audin_space( void *handle );

#endif /* VC_WIFIHDMI_AUDIN_H */
