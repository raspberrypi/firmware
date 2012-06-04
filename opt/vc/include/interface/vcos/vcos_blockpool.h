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
VideoCore OS Abstraction Layer - fixed size allocator support
=============================================================================*/

#ifndef VCOS_BLOCKPOOL_H
#define VCOS_BLOCKPOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/** \file
  *
  * Thread safe, fixed size allocator API.
  *
  */

/** Initialises a block pool to use already allocated (e.g. statically)
 * allocated memory.
 *
 * Different implementations will incur different overheads. Use
 * VCOS_BLOCKPOOL_SIZE(num_blocks, block_size) to calculate the number
 * of bytes required including overheads for the desired pools.
 *
 * @param pool        Pointer to pool object
 * @param num_blocks  The number of blocks required.
 * @param block_size  The size of an individual block.
 * @param start       The address of the start of the pool.
 * @param pool_size   The size of the pool in bytes.
 * @param align       Alignment for block data. Use VCOS_BLOCKPOOL_ALIGN_DEFAULT
 *                    for default word alignment.
 * @param flags       Reserved for future use.
 * @param name        Name of the pool. Used for diagnostics.
 *
 * @return VCOS_SUCCESS if the pool was created.
 */

VCOS_INLINE_DECL
VCOS_STATUS_T vcos_blockpool_init(VCOS_BLOCKPOOL_T *pool,
      VCOS_UNSIGNED num_blocks, VCOS_UNSIGNED block_size,
      void *start, VCOS_UNSIGNED pool_size, VCOS_UNSIGNED align,
      VCOS_UNSIGNED flags, const char *name);

/** Creates a pool of blocks of a given size within a buffer allocated on
 * the heap.
 *
 * The heap memory is freed when the block pool is destroyed by
 * calling vcos_blockpool_delete.
 *
 * @param pool        Pointer to pool object
 * @param num_blocks  The number of blocks required.
 * @param block_size  The size of an individual block.
 * @param align       Alignment for block data. Use VCOS_BLOCKPOOL_ALIGN_DEFAULT
 *                    for default word alignment.
 * @param flags       Reserved for future use.
 * @param name        Name of the pool. Used for diagnostics.
 *
 * @return VCOS_SUCCESS if the pool was created.
 */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_blockpool_create_on_heap(VCOS_BLOCKPOOL_T *pool,
      VCOS_UNSIGNED num_blocks, VCOS_UNSIGNED block_size,
      VCOS_UNSIGNED align, VCOS_UNSIGNED flags,
      const char *name);

/** Allocate a block from the pool
 *
 * @param pool Pointer to the pool to allocate from.
 * @return a pointer to the newly allocated block or NULL if no blocks were
 * available.
 */
VCOS_INLINE_DECL
void *vcos_blockpool_alloc(VCOS_BLOCKPOOL_T *pool);

/** Allocate a block from the pool and zero it.
 *
 * @param pool Pointer to the pool to allocate from.
 * @return a pointer to the newly allocated block or NULL if no blocks were
 * available.
 */
VCOS_INLINE_DECL
void *vcos_blockpool_calloc(VCOS_BLOCKPOOL_T *pool);

/** Returns a block to the pool.
 *
 * @param block The block to free.
 */
VCOS_INLINE_DECL
void vcos_blockpool_free(void *block);

/** Queries the number of available blocks in the pool.
 * @param pool The pool to query.
 */
VCOS_INLINE_IMPL
   VCOS_UNSIGNED vcos_blockpool_available_count(VCOS_BLOCKPOOL_T *pool);

/** Queries the number of used blocks in the pool.
 * @param pool The pool to query.
 */
VCOS_INLINE_IMPL
   VCOS_UNSIGNED vcos_blockpool_used_count(VCOS_BLOCKPOOL_T *pool);

/** Deinitialize a memory pool.
 *
 * @param pool The pool to de-initialize.
 */
VCOS_INLINE_DECL
void vcos_blockpool_delete(VCOS_BLOCKPOOL_T *pool);

/** Return an integer handle for a given allocated block. */
VCOS_INLINE_DECL
uint32_t vcos_blockpool_elem_to_handle(void *block);

/** Convert an integer handle back into a pointer.
  * Returns NULL if invalid. */
VCOS_INLINE_DECL
void *vcos_blockpool_elem_from_handle(VCOS_BLOCKPOOL_T *pool, uint32_t handle);

/** Checks whether a pointer is an allocated block within the specified pool.
  * Returns true if the block is valid, otherwise, false is returned. */
VCOS_INLINE_DECL
uint32_t vcos_blockpool_is_valid_elem(
      VCOS_BLOCKPOOL_T *pool, const void *block);

/** May be called once to allow the block pool to be extended by dynamically
 * adding subpools. The block size cannot be altered.
 *
 * @param num_extensions The number of extensions that may be created.
 *                       The maximum is (VCOS_BLOCKPOOL_MAX_SUBPOOLS - 1)
 * @param num_blocks     The number of blocks to allocate in each in each
 *                       dynamically allocated subpool.
 * @return VCOS_SUCCESS if successful.
 */
VCOS_INLINE_DECL
   VCOS_STATUS_T vcos_blockpool_extend(VCOS_BLOCKPOOL_T *pool,
         VCOS_UNSIGNED num_extensions, VCOS_UNSIGNED num_blocks);

#ifdef __cplusplus
}
#endif
#endif
