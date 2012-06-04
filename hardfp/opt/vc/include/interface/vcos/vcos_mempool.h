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
VideoCore OS Abstraction Layer - memory pool support
=============================================================================*/

#ifndef VCOS_MEMPOOL_H
#define VCOS_MEMPOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/** \file
  *
  * Memory pools - variable sized allocator.
  *
  * A very basic memory pool API.
  *
  * This interface is deliberately not thread safe - clients should add
  * their own locking, if required.
  *
  *
  * \fixme: Add fixed-size allocator.
  *
  */


/** Initialize a memory pool. The control data is taken from the memory
  * supplied itself.
  *
  * Note: the dmalloc pool uses the memory supplied for its control
  * area. This is probably a bit broken, as it stops you creating
  * a pool in some "special" area of memory, while leaving the control
  * information in normal memory.
  *
  * @param pool  Pointer to pool object.
  *
  * @param name  Name for the pool. Used for diagnostics.
  *
  * @param start Starting address. Must be at least 8byte aligned.
  *
  * @param size  Size of pool in bytes.
  *
  * @return VCOS_SUCCESS if pool was created.
  */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_mempool_create(VCOS_MEMPOOL_T *pool, const char *name, void *start, VCOS_UNSIGNED size);

/** Allocate some memory from a pool. If no memory is available, it
  * returns NULL.
  *
  * @param pool Pool to allocate from
  * @param len  Length of memory to allocate
  *
  */
VCOS_INLINE_DECL
void *vcos_mempool_alloc(VCOS_MEMPOOL_T *pool, VCOS_UNSIGNED len);

/** Free some memory back to a pool.
  *
  * @param pool Pool to return to
  * @param mem Memory to return
  */
VCOS_INLINE_DECL
void vcos_mempool_free(VCOS_MEMPOOL_T *pool, void *mem);

/** Deinitialize a memory pool.
  *
  * @param pool Pool to return to
  */
VCOS_INLINE_DECL
void vcos_mempool_delete(VCOS_MEMPOOL_T *pool);

#ifdef __cplusplus
}
#endif
#endif



