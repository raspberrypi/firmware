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
* Host request service command enumeration & misc types & defines.

*** ENTRIES MUST ONLY BE ADDED TO THE END OF AN ENUM LIST ***

* Please mark unwanted entries as invalid rather than reusing the enum entry.
*/

#ifndef VC_HOSTREQ_DEFS_H
#define VC_HOSTREQ_DEFS_H

#include "vcinclude/common.h"

/* Types and constants common across the both ends of the interface */
#define VC_HRMAX_CMD_DATA        512
#define VC_HRMAX_VIBRATOR_SEQ    (VC_HRMAX_CMD_DATA/4)

typedef unsigned int keys_t;
typedef unsigned int led_t;

/* Error codes used in responses and in the API */
enum
{
   VC_HRERR_OK          =  0,    /* Success */
   VC_HRERR_NOTREADY    =  1,
   VC_HRERR_UNSUPPORTED =  10,   /* Unsupported or inappropriate request */
   VC_HRERR_MEMADDR     =  20,   /* Trying to read protected host memory */
};

/* Key bit enumerations */
typedef enum
{
   // ENTRIES MUST ONLY BE ADDED TO THE END OF THIS ENUM LIST

   VC_KEY_0 =        (1<<0),
   VC_KEY_1 =        (1<<1),
   VC_KEY_2 =        (1<<2),
   VC_KEY_3 =        (1<<3),
   VC_KEY_4 =        (1<<4),
   VC_KEY_5 =        (1<<5),
   VC_KEY_6 =        (1<<6),
   VC_KEY_7 =        (1<<7),
   VC_KEY_8 =        (1<<8),
   VC_KEY_9 =        (1<<9),
   VC_KEY_UP =       (1<<10),
   VC_KEY_DOWN =     (1<<11),
   VC_KEY_LEFT =     (1<<12),
   VC_KEY_RIGHT =    (1<<13),
   VC_KEY_ENTER =    (1<<14),
   VC_KEY_SEND =     (1<<15),
   VC_KEY_END =      (1<<16),
   VC_KEY_MENU =     (1<<17),
   VC_KEY_VOLUP =    (1<<18),
   VC_KEY_VOLDOWN =  (1<<19),
   VC_KEY_STAR =     (1<<20),
   VC_KEY_HASH =     (1<<21),
   VC_KEY_CANCEL =   (1<<22),
   VC_KEY_CAMERA =   (1<<23),
   VC_KEY_RECORD =   (1<<24),
   VC_KEY_INFO =     (1<<25),
   VC_KEY_DVB =      (1<<26),
   VC_KEY_ANY =      (1<<27)-1  // change this if any more keys are added
} VC_HOSTKEYS_T;

/* Add notify events here */
typedef enum
{
   // ENTRIES MUST ONLY BE ADDED TO THE END OF THIS ENUM LIST

   VC_HRNOTIFY_START = 0,
   VC_HRNOTIFY_GAME_ACCEPT,
   VC_HRNOTIFY_GAME_REJECT,
   VC_HRNOTIFY_GAME_SAVE,
   VC_HRNOTIFY_GAME_LOAD,
   VC_HRNOTIFY_GAME_EXIT,
   VC_HRNOTIFY_MELODY_END,
   VC_HRNOTIFY_DISK_INSERTED,
   VC_HRNOTIFY_DISK_REMOVED,
   VC_HRNOTIFY_RINGTONE_END,
   VC_HRNOTIFY_KEYTONE_END,
   VC_HRNOTIFY_GAME_ABORT,
   VC_HRNOTIFY_PCM_END,
   VC_HRNOTIFY_FS_INUSE,
   VC_HRNOTIFY_FS_NOT_INUSE,
   VC_HRNOTIFY_APP_STATUS,    /* app's status has changed (excluding things like elapsed times) - mainly errors or status changed */
   VC_HRNOTIFY_CAMERA_EVENT,
   VC_HRNOTIFY_END

} VC_HRNOTIFY_T;

//typedef of the callback from a HRNOTIFY function
typedef void (* VC_HRNOTIFY_CALLBACK_T)( const VC_HRNOTIFY_T notify_event, const uint32_t param );

//typedef of the callback from a RENDERTEXT/CONGIFTEXT/LINKDATA/DMB* function
typedef void (* VC_HRDATA_CALLBACK_T)( int cmd, void *userdata, uint8_t *data, int len );

/* Enum host request commands here rather than in vcinterface */
/*
   NB There is overlap of command enumerations with other services
   - but this does not matter
*/
enum
{
   // ENTRIES MUST ONLY BE ADDED TO THE END OF THIS ENUM LIST

   /* Host request service commands, vc->host */
   VC_HOSTREQ_RESET = 64,
   VC_HOSTREQ_CAPTUREKEYS,
   VC_HOSTREQ_VIBRATORPLAY,
   VC_HOSTREQ_VIBRATORSTOP,
   VC_HOSTREQ_KEYLIGHT,
   VC_HOSTREQ_SETLEDS,
   VC_HOSTREQ_TIME,
   VC_HOSTREQ_NOTIFY,
   VC_HOSTREQ_READMEM,
   VC_HOSTREQ_CONFIGTEXT,
   VC_HOSTREQ_RENDERTEXT,
   VC_HOSTREQ_LINKDATA,
   VC_HOSTREQ_MALLOC,
   VC_HOSTREQ_FREE,
   VC_HOSTREQ_MEMMOVE,
   VC_HOSTREQ_WRITEMEM,
   VC_HOSTREQ_KEYIN,
   VC_HOSTREQ_DISPLAYDEV,
   VC_HOSTREQ_ACCESSURL,
   VC_HOSTREQ_DMB_FIC,
   VC_HOSTREQ_DMB_PAD,
   VC_HOSTREQ_DMB_DATA,
   VC_HOSTREQ_READMEM_3D,
   VC_HOSTREQ_SEND_PCM,
   VC_HOSTREQ_AUDIODEVREQUEST,
   VC_HOSTREQ_AUDIODEVCONFIG,
   VC_HOSTREQ_AUDIODEVRELEASE,
   VC_HOSTREQ_PHOTOROW,
   VC_HOSTREQ_COPYCONTROL,
   VC_HOSTREQ_READPIXELS,   /* Batch read of photo data from host */
   VC_HOSTREQ_REPORT_AV_STATS,
   VC_HOSTREQ_GPIO,

   /* Host request service key messages */
   VC_HOSTREQ_KEYEVENT = 96,
   VC_HOSTREQ_KEYACK
};

#endif
