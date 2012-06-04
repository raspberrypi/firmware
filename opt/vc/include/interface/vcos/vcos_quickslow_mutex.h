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
VideoCore OS Abstraction Layer - mutex public header file
=============================================================================*/

#ifndef VCOS_QUICKSLOW_MUTEX_H
#define VCOS_QUICKSLOW_MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/**
 * \file vcos_quickslow_mutex.h
 *
 * "Quick/Slow" Mutex API. This is a mutex which supports an additional "quick"
 * (spinlock-based) locking mechanism. While in this quick locked state, other
 * operating system commands will be unavailable and the caller should complete
 * whatever it has to do in a short, bounded length of time (as the spinlock
 * completely locks out other system activity).
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
VCOS_STATUS_T vcos_quickslow_mutex_create(VCOS_QUICKSLOW_MUTEX_T *m, const char *name);

/** Delete the mutex.
  */
VCOS_INLINE_DECL
void vcos_quickslow_mutex_delete(VCOS_QUICKSLOW_MUTEX_T *m);

/**
  * \brief Wait to claim the mutex ("slow" mode).
  *
  * Obtain the mutex.
  */
VCOS_INLINE_DECL
void vcos_quickslow_mutex_lock(VCOS_QUICKSLOW_MUTEX_T *m);

/** Release the mutex ("slow" mode).
  */
VCOS_INLINE_DECL
void vcos_quickslow_mutex_unlock(VCOS_QUICKSLOW_MUTEX_T *m);

/**
  * \brief Wait to claim the mutex ("quick" mode).
  *
  * Obtain the mutex. The caller must not call any OS functions or do anything
  * "slow" before the corresponding call to vcos_mutex_quickslow_unlock_quick.
  */
VCOS_INLINE_DECL
void vcos_quickslow_mutex_lock_quick(VCOS_QUICKSLOW_MUTEX_T *m);

/** Release the mutex ("quick" mode).
  */
VCOS_INLINE_DECL
void vcos_quickslow_mutex_unlock_quick(VCOS_QUICKSLOW_MUTEX_T *m);


#ifdef __cplusplus
}
#endif
#endif
