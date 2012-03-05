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

#ifndef _VC_PERFSTAT_PROFILE_H_
#define _VC_PERFSTAT_PROFILE_H_

/* Perfstat profile block is an extension to perfstats that allow blocks
 * of code to be profiled.
 *
 * To profile a block of code, simply surround the code with a start and
 * stop call.  For example,
 *
 * #include "applications/vmcs/perfstat/perfstat_profile.h"
 *
 * PERFSTAT_PROFILE_START( "unique string" );
 *
 * ... code ...
 *
 * PERFSTAT_PROFILE_STOP( "unique string" );
 *
 * Ensure that your profile point contains a unique string like "vid_dec".
 * This unique string is used to identify the profile point.  Note the
 * maximum string length is 15 characters.
 *
 * This module reports the max, min, and average cycles spent between
 * the start and stop points.  In addition, it reports a period max,
 * min, and avg.  A period is defined to be the perfstat profiling interval
 * which is 500ms.  By linking the profile point to a sense of time,
 * it allows us to determine how much time is spent in the profiled block.
 * It also reports how many iterations of the block is executed in a period.
 *
 * The results are retrieved via the perfstat interface.
 */

// ---- Constants and Types -------------------------------------------------

/* Max length of stored name
 */
#define PERFSTAT_PROFILE_NAME_LEN   16

/* Number of profile points that can be registerd
 */
#define PERFSTAT_PROFILE_NUM_BLOCKS 10

/* Profile block state and stats
 */
typedef struct
{
   char     name[PERFSTAT_PROFILE_NAME_LEN];  /* Name of block */
   uint32_t iter;        /* Iterations */
   uint32_t max;         /* Max cycle count */
   uint32_t min;         /* Min cycle count */
   uint32_t avg;         /* Avg cycle count */

   uint32_t periods;     /* Number of profile periods */
   uint32_t period_iter; /* Iterations per period */
   uint32_t period_max;  /* Max cycle count in a period */
   uint32_t period_min;  /* Min cycle count in a period */
   uint32_t period_avg;  /* Avg cycle count in a period */

} PERFSTAT_PROFILE_BLOCK;

// ---- Function Prototypes -------------------------------------------------

#endif /* _VC_PERFSTAT_PROFILE_H_ */
