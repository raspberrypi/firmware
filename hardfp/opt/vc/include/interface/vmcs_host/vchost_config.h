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
* Platform dependent functions. Every different hardware platform will need to
* implement these functions.
*/

/*=============================================================================
Platform specific configuration parameters.
=============================================================================*/

#ifndef VCHOST_CONFIG_H
#define VCHOST_CONFIG_H

#include "interface/vcos/vcos.h"

#if 0
/* Types that map onto VideoCore's types of the same name. */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

#ifndef vc_assert
#define vc_assert(cond) vcos_assert(cond)
#endif
#endif

/* On this platform we need to be able to release the host-side software resources. */
extern void vc_os_close(void);

#ifndef VCHPRE_
#define VCHPRE_     extern
#endif
#ifndef VCHPOST_
#define VCHPOST_
#endif
#ifndef VCCPRE_
#define VCCPRE_     
#endif

#endif
