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
* Host-side service providing interaction with the power management unit,
* for handling battery charging and USB connection and disconnection
*/

#ifndef VC_VCHI_PMU_H
#define VC_VCHI_PMU_H

#include "vchost_config.h"
#include "interface/vchi/vchi.h"

#if !defined(VCHPRE_)
#error VCHPRE_ not defined!
#endif
#if !defined(VCHPOST_)
#error VCHPOST_ not defined!
#endif

/*-----------------------------------------------------------------------------*/
// Values returned by vc_pmu_get_battery_status()
typedef enum
{
   BATT_NONE,
   BATT_LOW,
   BATT_VERY_LOW,
   BATT_OK,
   BATT_CHARGED
} PMU_BATTERY_STATE_T;

/*-----------------------------------------------------------------------------*/

VCHPRE_ void VCHPOST_ vc_vchi_pmu_init
   (VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections);

VCHPRE_ int32_t VCHPOST_ vc_pmu_enable_usb(uint32_t enable);
VCHPRE_ int32_t VCHPOST_ vc_pmu_usb_connected(void);
VCHPRE_ uint32_t VCHPOST_ vc_pmu_get_battery_status(void);

#endif /* VC_VCHI_PMU_H */
/* End of file */
/*-----------------------------------------------------------------------------*/
