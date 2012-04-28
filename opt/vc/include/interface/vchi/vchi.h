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
* Temporary file with some needed types
*/


#ifndef VCHI_H
#define VCHI_H

// Opaque handle for a VCHI instance
typedef struct opaque_vchi_instance_handle_t *VCHI_INSTANCE_T;

// Opaque handle for a server or client
typedef struct opaque_vchi_service_handle_t *VCHI_SERVICE_HANDLE_T;

// Opaque handle for a connection / service pair
typedef struct opaque_vchi_connection_connected_service_handle_t *VCHI_CONNECTION_SERVICE_HANDLE_T;

// opaque handle to the connection state information
typedef struct opaque_vchi_connection_info_t VCHI_CONNECTION_STATE_T;

typedef struct vchi_connection_t VCHI_CONNECTION_T;

typedef int32_t VCHI_MEM_HANDLE_T;
#define VCHI_MEM_HANDLE_INVALID 0

#endif
