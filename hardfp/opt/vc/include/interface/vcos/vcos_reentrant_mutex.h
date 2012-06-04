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
VideoCore OS Abstraction Layer - reentrant mutex public header file
=============================================================================*/

#ifndef VCOS_REENTRANT_MUTEX_H
#define VCOS_REENTRANT_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/**
 * \file
 *
 * Reentrant Mutex API. You can take one of these mutexes even if you've already
 * taken it. Just to make sure.
 *
 * A re-entrant mutex may be slower on some platforms than a regular one.
 *
 * \sa vcos_mutex.h
 *
 */

/** Create a mutex.
  *
  * @param m      Filled in with mutex on return
  * @param name   A non-null name for the mutex, used for diagnostics.
  *
  * @return VCOS_SUCCESS if mutex was created, or error code.
  */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_reentrant_mutex_create(VCOS_REENTRANT_MUTEX_T *m, const char *name);

/** Delete the mutex.
  */
VCOS_INLINE_DECL
void vcos_reentrant_mutex_delete(VCOS_REENTRANT_MUTEX_T *m);

/** Wait to claim the mutex. Must not have already been claimed by the current thread.
  */
#ifndef vcos_reentrant_mutexlock
VCOS_INLINE_DECL
void vcos_reentrant_mutex_lock(VCOS_REENTRANT_MUTEX_T *m);

/** Release the mutex.
  */
VCOS_INLINE_DECL
void vcos_reentrant_mutex_unlock(VCOS_REENTRANT_MUTEX_T *m);
#endif


#ifdef __cplusplus
}
#endif
#endif

