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
FIXME: This code should be moved to 'linux', it is linux-specific and not generic
on 'pthreads'.
============================================================================*/

#ifndef VCOS_MUTEX_FROM_FUTEX_H
#define VCOS_MUTEX_FROM_FUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

typedef struct VCOS_FUTEX_T
{
   volatile int value;
} VCOS_FUTEX_T;

typedef VCOS_FUTEX_T VCOS_MUTEX_T;

VCOSPRE_ VCOS_STATUS_T VCOSPOST_ vcos_futex_init(VCOS_FUTEX_T *futex);
VCOSPRE_ void VCOSPOST_ vcos_futex_delete(VCOS_FUTEX_T *futex);
VCOSPRE_ VCOS_STATUS_T VCOSPOST_ vcos_futex_lock(VCOS_FUTEX_T *futex);
VCOSPRE_ void VCOSPOST_ vcos_futex_unlock(VCOS_FUTEX_T *futex);
VCOSPRE_ VCOS_STATUS_T VCOSPOST_ vcos_futex_trylock(VCOS_FUTEX_T *futex);

#if defined(VCOS_INLINE_BODIES)

VCOS_INLINE_IMPL
VCOS_STATUS_T vcos_mutex_create(VCOS_MUTEX_T *latch, const char *name) {
   vcos_unused(name);
   return vcos_futex_init(latch);
}

VCOS_INLINE_IMPL
void vcos_mutex_delete(VCOS_MUTEX_T *latch) {
   vcos_futex_delete(latch);
}

VCOS_INLINE_IMPL
VCOS_STATUS_T vcos_mutex_lock(VCOS_MUTEX_T *latch) {
   return vcos_futex_lock(latch);
}

VCOS_INLINE_IMPL
void vcos_mutex_unlock(VCOS_MUTEX_T *latch) {
   vcos_futex_unlock(latch);
}

VCOS_INLINE_IMPL
int vcos_mutex_is_locked(VCOS_MUTEX_T *latch) {
   int rc = latch->value;
   if (!rc) {
      /* it wasn't locked */
      return 0;
   }
   else {
      return 1; /* it was locked */
   }
}

VCOS_INLINE_IMPL
VCOS_STATUS_T vcos_mutex_trylock(VCOS_MUTEX_T *m) {
   return vcos_futex_trylock(m);
}

#endif /* VCOS_INLINE_BODIES */

#ifdef __cplusplus
}
#endif
#endif /* VCOS_MUTEX_FROM_FUTEX_H */

