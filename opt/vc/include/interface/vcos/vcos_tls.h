/*
 * Copyright (c) 2010-2011 Broadcom. All rights reserved.
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

/*=============================================================================
VideoCore OS Abstraction Layer - thread local storage
=============================================================================*/

#ifndef VCOS_TLS_H
#define VCOS_TLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"


/** Create a new thread local storage data key visible to all threads in
  * the current process.
  *
  * @param key    The key to create
  */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_tls_create(VCOS_TLS_KEY_T *key);

/** Delete an existing TLS data key.
  */
VCOS_INLINE_DECL
void vcos_tls_delete(VCOS_TLS_KEY_T tls);

/** Set the value seen by the current thread.
  *
  * @param key    The key to update
  * @param v      The value to set for the current thread.
  *
  * @return VCOS_SUCCESS, or VCOS_ENOMEM if memory for this slot
  * could not be allocated.
  *
  * If TLS is being emulated via VCOS then the memory required
  * can be preallocated at thread creation time
  */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_tls_set(VCOS_TLS_KEY_T tls, void *v);

/** Get the value for the current thread.
  *
  * @param key    The key to update
  *
  * @return The current value for this thread.
  */
VCOS_INLINE_DECL
void *vcos_tls_get(VCOS_TLS_KEY_T tls);

#ifdef __cplusplus
}
#endif

#endif

