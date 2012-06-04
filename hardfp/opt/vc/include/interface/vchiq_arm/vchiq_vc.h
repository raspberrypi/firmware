/*
 * Copyright (c) 2010-2011 Broadcom Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef VCHIQ_VC_H
#define VCHIQ_VC_H

#include "vchiq_core.h"

extern char _frdata[];

#define VCHIQ_IS_SAFE_DATA(x) ((char *)RTOS_ALIAS_NORMAL(x) >= _frdata)

#define VCOS_LOG_CATEGORY (&vchiq_vc_log_category)

#define VC_MEMCPY(d,s,l) do { if (l < DMA_MEMCPY_THRESHOLD) memcpy(d,s,l); else dma_memcpy(d,s,l); } while (0)

extern VCOS_LOG_CAT_T vchiq_vc_log_category;

typedef struct vchiq_instance_struct
{
   VCHIQ_STATE_T state;
   int connected;
} VCHIQ_INSTANCE_STRUCT_T;


typedef struct vchiq_vc_state_struct {
   VCOS_EVENT_T                remote_use_active;
   VCHIQ_REMOTE_USE_CALLBACK_T remote_use_callback;
   void*                       remote_use_cb_arg;
   int                         remote_use_sent;
} VCHIQ_VC_STATE_T;


extern VCHIQ_INSTANCE_STRUCT_T vchiq_instances[];
extern int vchiq_num_instances;

extern VCHIQ_STATUS_T
vchiq_platform_init(void);

extern VCHIQ_STATUS_T
vchiq_vc_init_state(VCHIQ_VC_STATE_T* vc_state);

extern VCHIQ_VC_STATE_T*
vchiq_platform_get_vc_state(VCHIQ_STATE_T *state);

#endif
