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

/** Statistics for image conversion to foreign image types
 */
typedef struct
{
   uint32_t magic;
   uint32_t size;                   /**< Size of this structure, in bytes */
   uint32_t conversions;            /**< Total conversions so far */
   uint32_t async_conversions;      /**< Asyncrhonous conversions */
   uint32_t duplicate_conversions;  /**< Duplicate conversions (same image twice) */
   uint32_t size_requests;          /**< Num calls to get_converted_size */
   uint32_t consumed_count;         /**< How many converted images were consumed */
   uint32_t total_allocs;           /**< Incremented when converted images are allocated */
   uint32_t total_frees;            /**< Incremented when converted images are freed */
   uint32_t failures;               /**< Failed conversions */
   uint32_t time_spent;             /**< Time spent converting, us */
   uint32_t alloc_time_spent;       /**< Time spent waiting for mem_alloc */
   uint32_t max_alloc_delay;        /**< The max time waiting for mem_alloc */
   uint32_t max_vrf_delay;          /**< The max time waiting for the VRF */
   uint32_t vrf_wait_time;          /**< Total time waiting for the VRF */
   uint32_t last_mem_handle;        /**< Last mem handle converted */
   uint32_t first_image_ts;         /**< Timestamp of first image */
   uint32_t last_image_ts;          /**< Timestamp of first image */
   uint32_t max_delay;              /**< Jitter */
} IMAGECONV_STATS_T;

#define IMAGECONV_STATS_MAGIC 0x494D454C

