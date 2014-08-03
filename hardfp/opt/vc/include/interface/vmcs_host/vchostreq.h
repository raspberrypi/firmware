/*
Copyright (c) 2012, Broadcom Europe Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
