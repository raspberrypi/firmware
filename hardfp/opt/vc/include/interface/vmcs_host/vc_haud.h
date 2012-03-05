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

#ifndef VC_HAUD_H
#define VC_HAUD_H

#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h"

/* Useful block sizes */
#define VC_HAUD_BLOCK_SIZE_DD             1536
#define VC_HAUD_BLOCK_SIZE_DDP            6144

/* HDMI Audio Handle */
typedef void* VC_HAUD_HANDLE_T;

/* Supported codecs */
typedef enum
{
   VC_HAUD_CODEC_INVALID = 0, /* Invalid */ 
   VC_HAUD_CODEC_PCM16,       /* LPCM 16-bit */ 
   VC_HAUD_CODEC_PCM20,       /* LPCM 20-bit */ 
   VC_HAUD_CODEC_PCM24,       /* LPCM 24-bit */ 
   VC_HAUD_CODEC_DD,          /* Dolby Digital/AC3 */ 
   VC_HAUD_CODEC_DDP          /* Dolby Digital Plus/E-AC3 */ 

} VC_HAUD_CODEC_T;

/* PCM Configuration */
typedef struct
{
   uint32_t frame_period_ms;       /* Frame period in ms */

} VC_HAUD_PCM_CONFIG_T;

/* Query information */
typedef struct
{
   uint32_t encoding;            /* Encoding used (VC_HAUD_CODEC_T) */
   uint32_t sample_rate;         /* Sample rate in Hz */
   uint32_t num_chans;           /* Number of channels */
   uint32_t chan_mask;           /* Channel Mask */
   uint32_t samples_per_period;  /* Number of samples expected per period */
   uint32_t block_size;          /* Output buffer size */

   /* PCM Specific */
   uint32_t frame_period_ms;     /* Frame period in ms */
   
} VC_HAUD_INFO_T;

/* Debug query */
typedef struct
{
   uint32_t dma_index;     /* Current active DMA SCB */
   uint32_t write_index;   /* Write pointer into DMA SCB */
   uint32_t underrun;      /* Write underruns (silence filled) */ 

} VC_HAUD_DBG_T;

/* HDMI Audio data request callback */
typedef void (*VC_HAUD_DATA_REQ_CBK)( uint32_t buf_avail );

#define CODEC_IS_PCM( codec ) ((codec == VC_HAUD_CODEC_PCM16) || (codec == VC_HAUD_CODEC_PCM20) || (codec == VC_HAUD_CODEC_PCM24))
#define CODEC_IS_COMPRESSED( codec ) ((codec == VC_HAUD_CODEC_DD) || (codec == VC_HAUD_CODEC_DDP))

#endif /* VC_HAUD_H */
