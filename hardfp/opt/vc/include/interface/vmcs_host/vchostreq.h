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
* Platform/Application specific implementations of host request functions.
*/

#ifndef VCHOSTREQ_H
#define VCHOSTREQ_H

#include "vc_hostreq_defs.h"
#include "vchost_config.h"
#include <time.h>

#include "interface/vchi/vchi.h"

VCHPRE_ void VCHPOST_ vc_vchi_hostreq_init(VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections );
//These are originally in vchostmem.c, we only provide them here for backward compatibility
//Host apps should be using bufman service to read/write host memory
VCHPRE_ int VCHPOST_ vchostreq_readmem( void* host_addr, void *vc_addr, int len );
VCHPRE_ int VCHPOST_ vchostreq_writemem( void* host_addr, void *vc_addr, int len, int channel );


VCHPRE_ int VCHPOST_ vc_hostreq_init (void);

VCHPRE_ void VCHPOST_ vc_hostreq_stop (void);

/* Supplies current key settings (preferably when there is a change) */
VCHPRE_ void VCHPOST_ vc_hostreq_keychange(keys_t keys);

/* Sets a user notify function to be called for the given notify event */
VCHPRE_ int32_t VCHPOST_ vc_hostreq_set_notify( const VC_HRNOTIFY_T notify_event, VC_HRNOTIFY_CALLBACK_T notifyfunc );

/* Sets a user callback to be called for the given hostreq event */
VCHPRE_ int32_t VCHPOST_ vc_hostreq_set_data_callback( const int cmd, VC_HRDATA_CALLBACK_T callback, void *userdata );

/*---------------------------------------------------------------------------*/
/*** The following require a host/application specific implementation ***/

/* Change key capture settings (might be ignored) */
VCHPRE_ void VCHPOST_ vc_hostreq_capturekeys(keys_t keymask);


/* Play a zero terminated sequence on the vibrator */
VCHPRE_ void VCHPOST_ vc_hostreq_vibratorplay(const int *sequence);


/* Stop the vibrator sequence immediately */
VCHPRE_ void VCHPOST_ vc_hostreq_vibratorstop(void);


/* Switch backlight on or off. */
VCHPRE_ void VCHPOST_ vc_hostreq_keylight(int state);


/* Set LEDs to specific brightness and colour levels. */
VCHPRE_ void VCHPOST_ vc_hostreq_setleds(led_t ledvalues);


/* Returns seconds since midnight (00:00.00) Jan 1 1970, local time. */
VCHPRE_ time_t VCHPOST_ vc_hostreq_time(void);


/* Send an event with the given eventcode to the host. */
VCHPRE_ void VCHPOST_ vc_hostreq_notify(int eventcode, int param);

/* Receive config data for subsequent hostreq_rendertext events. */
VCHPRE_ void VCHPOST_ vc_hostreq_configtext(char *config_data, int len);

/* Render a text string as a bitmap and then return it to VideoCore. */
VCHPRE_ void VCHPOST_ vc_hostreq_rendertext(char *text, int len);

/* Receive link information from a media file. */
VCHPRE_ void VCHPOST_ vc_hostreq_linkdata(char *link_data, int len);

/* Receive DMB FIC data */
VCHPRE_ void VCHPOST_ vc_hostreq_dmb_fic(char *data, int len);

/* Receive DMB PAD data */
VCHPRE_ void VCHPOST_ vc_hostreq_dmb_pad(char *data, int len);

/* Receive DMB DATA data */
VCHPRE_ void VCHPOST_ vc_hostreq_dmb_data(char *data, int len);

/* Request keypress info (from RTSP server). */
VCHPRE_ void VCHPOST_ vc_hostreq_keyin(void);

#endif
