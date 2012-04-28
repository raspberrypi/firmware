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
 *
 * Header file with useful bits from other headers
 */

#ifndef BCM_HOST_H
#define BCM_HOST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void bcm_host_init(void);
void bcm_host_deinit(void);

int32_t graphics_get_display_size( const uint16_t display_number,
                                                    uint32_t *width,
                                                    uint32_t *height);

#include "interface/vmcs_host/vc_dispmanx.h"
#include "interface/vmcs_host/vc_tvservice.h"
#include "interface/vmcs_host/vc_cec.h"
#include "interface/vmcs_host/vc_cecservice.h"
#include "interface/vmcs_host/vcgencmd.h"

#ifdef __cplusplus
}
#endif

#endif

