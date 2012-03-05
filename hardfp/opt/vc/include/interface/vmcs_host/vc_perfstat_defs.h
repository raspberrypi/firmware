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

#ifndef _VC_PERFSTAT_DEFS_H_
#define _VC_PERFSTAT_DEFS_H_

#include "interface/vmcs_host/vc_perfstat_profile.h"

// FourCC code used for VCHI connection
#define VC_PERFSTAT_SERVER_NAME  MAKE_FOURCC("PERF")

// Maximum message length (header + body)
#define VC_PERFSTAT_MAX_MSG_LEN  (sizeof( VC_PERFSTAT_MSG_HDR_T ) + \
                                  sizeof( VC_PERFSTAT_MSG_UNION_T ))

// Number of VPUs
#define VC_PERFSTAT_NUM_VPU  (2)

// Number of HVSs
#define VC_PERFSTAT_NUM_HVS  (3)

// All message types supported for HOST->VC direction
typedef enum
{
   VC_PERFSTAT_MSG_TYPE_CTRL = 0,      // Control the service (enable/disable)
   VC_PERFSTAT_MSG_TYPE_SET_AVG_MODE,  // Set the averaging mode
   VC_PERFSTAT_MSG_TYPE_GET_STAT,      // Get the stats
   VC_PERFSTAT_MSG_TYPE_RESET_STAT,    // Reset the stats of all blocks
   VC_PERFSTAT_MSG_TYPE_MAX

} VC_PERFSTAT_MSG_TYPE_T;

// Message header for all messages
typedef struct
{
   union
   {
      uint32_t type;    // HOST->VC: Message type (VC_PERFSTAT_MSG_TYPE_T)
      int32_t  status;  // VC->HOST: Request status (VCOS_STATUS_T)
                        //    VCOS_SUCCESS -> Success
                        //    VCOS_EAGAIN  -> Service disabled (try again)
                        //    VCOS_EINVAL  -> Invalid parameters
                        //    VCOS_ENOSYS  -> Unsupported message/request
   } u;

   uint8_t body[0];     // Pointer to message body (if exists)

} VC_PERFSTAT_MSG_HDR_T;

// Control the server state (enable/disable) (HOST->VC)
typedef struct
{
   uint32_t target_state;  // Target service state {0:disable, 1:enable}

} VC_PERFSTAT_CTRL_T;

// Averaging modes
typedef enum
{
   VC_PERFSTAT_AVG_MODE_LINEAR = 0,
   VC_PERFSTAT_AVG_MODE_EXP,
   VC_PERFSTAT_AVG_MODE_MAX

} VC_PERFSTAT_AVG_MODE_T;

// Set the averaging mode used (HOST->VC)
typedef struct
{
   uint32_t avg_mode;   // Averaging mode to use (VC_PERFSTAT_AVG_MODE_T)

} VC_PERFSTAT_SET_AVG;

// List of blocks that have statistics
typedef enum
{
   VC_PERFSTAT_BLK_SYSMEM = 0,   // System (non heap) memory
   VC_PERFSTAT_BLK_HEAP,         // Heap memory
   VC_PERFSTAT_BLK_MBUS,         // Memory bus
   VC_PERFSTAT_BLK_VPU,          // VPU usage
   VC_PERFSTAT_BLK_HVS_CPLX,     // HVS complexities
   VC_PERFSTAT_BLK_HVS_LBM,      // HVS LBM
   VC_PERFSTAT_BLK_PROFILE,      // Profiles
   VC_PERFSTAT_BLK_ALL

} VC_PERFSTAT_BLK_T;

// Get statistics of a block
typedef struct
{
   uint32_t target_blk;  // Target block to get statistics from (VC_PERFSTAT_BLK_T)

} VC_PERFSTAT_GET_STAT_T;

// System memory stats
typedef struct
{
   uint32_t free;    // Current free system memory available (MB x10)
   uint32_t size;    // Total size of system memory (MB x10)

} VC_PERFSTAT_SYSMEM_STAT_T;

// Heap memory stats
typedef struct
{
   uint32_t free;    // Current free heap memory available (MB x10)
   uint32_t size;    // Total size of heap memory (MB x10)

} VC_PERFSTAT_HEAP_STAT_T;

// Memory bus cycles record
typedef struct
{
   uint32_t pg_hit_dcycles;      // Page hit data cycles
   uint32_t pg_miss_dcycles;     // Page miss data cycles
   uint32_t auto_ref_cycles;     // Auto-refresh cycles
   uint32_t bank_act_cycles;     // Bank activate cycles

   uint32_t total_cycles;        // Total cycles

} VC_PERFSTAT_MBUS_CYCLES_T;

// Memory bus stats
typedef struct
{
   VC_PERFSTAT_MBUS_CYCLES_T cur;
   VC_PERFSTAT_MBUS_CYCLES_T min;
   VC_PERFSTAT_MBUS_CYCLES_T max;
   VC_PERFSTAT_MBUS_CYCLES_T avg;
   uint32_t                  iter;   // Number of interations of collection
   uint32_t                  period; // Number of cycles in a period

} VC_PERFSTAT_MBUS_STAT_T;

// VPU usage stats
typedef struct
{
   struct
   {
      uint32_t cur;     // Current VPU usage (% x10)
      uint32_t avg;     // Average VPU usage (% x10)
      uint32_t peak;    // Peak VPU usage (% x10)
   } n[VC_PERFSTAT_NUM_VPU];

} VC_PERFSTAT_VPU_STAT_T;

// HVS complexities stats
typedef struct
{
   struct
   {
      uint32_t cur;     // Current HVS complexity (KHz x10)
      uint32_t peak;    // Peak HVS complexity (KHz x10)
   } n[VC_PERFSTAT_NUM_HVS];

} VC_PERFSTAT_HVS_CPLX_STAT_T;

// HVS LBM stats
typedef struct
{
   struct
   {
      uint32_t cur;     // Current HVS LBM (bytes)
      uint32_t peak;    // Peak HVS LBM (bytes)
   } n[VC_PERFSTAT_NUM_HVS];

} VC_PERFSTAT_HVS_LBM_STAT_T;

// Profile blocks
typedef struct
{
   uint32_t                    num_profile_blocks;
   PERFSTAT_PROFILE_BLOCK      block[PERFSTAT_PROFILE_NUM_BLOCKS];

} VC_PERFSTAT_PROFILE_STAT_T;

// Common stats
typedef struct
{
   VC_PERFSTAT_SYSMEM_STAT_T   mem;
   VC_PERFSTAT_HEAP_STAT_T     heap;
   VC_PERFSTAT_MBUS_STAT_T     mbus;
   VC_PERFSTAT_VPU_STAT_T      vpu;
   VC_PERFSTAT_HVS_CPLX_STAT_T hvs_cplx;
   VC_PERFSTAT_HVS_LBM_STAT_T  hvs_lbm;
   VC_PERFSTAT_PROFILE_STAT_T  profile;

} VC_PERFSTAT_ALL_STAT_T;

// Union of ALL messages (used to calculate maximum message length)
typedef union
{
   VC_PERFSTAT_CTRL_T          ctrl;
   VC_PERFSTAT_AVG_MODE_T      avg_mode;
   VC_PERFSTAT_SET_AVG         set_avg;
   VC_PERFSTAT_SYSMEM_STAT_T   mem_stat;
   VC_PERFSTAT_HEAP_STAT_T     heap_stat;
   VC_PERFSTAT_MBUS_STAT_T     mbus_stat;
   VC_PERFSTAT_VPU_STAT_T      vpu_stat;
   VC_PERFSTAT_HVS_CPLX_STAT_T hvs_cplx_stat;
   VC_PERFSTAT_HVS_LBM_STAT_T  hvs_lbm_stat;
   VC_PERFSTAT_PROFILE_STAT_T  profile_stat;
   VC_PERFSTAT_ALL_STAT_T      all_stat;

} VC_PERFSTAT_MSG_UNION_T;

#endif // _VC_PERFSTAT_DEFS_H_
