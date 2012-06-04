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
VideoCore OS Abstraction Layer - platform-specific types and defines
=============================================================================*/

#ifndef VCOS_PLATFORM_TYPES_H
#define VCOS_PLATFORM_TYPES_H

#include <inttypes.h> /* for PRId64, PRIi64, etc */
#include <stdint.h>

#define VCOSPRE_ extern
#define VCOSPOST_

#if defined(__GNUC__) && (( __GNUC__ > 2 ) || (( __GNUC__ == 2 ) && ( __GNUC_MINOR__ >= 3 )))
#define VCOS_FORMAT_ATTR_(ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)  __attribute__ ((format (ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)))
#else
#define VCOS_FORMAT_ATTR_(ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)
#endif

/*#define VCOS_BKPT vcos_abort() */

#define VCOS_ASSERT_LOGGING         1
#define VCOS_ASSERT_LOGGING_DISABLE 0

extern void
vcos_pthreads_logging_assert(const char *file, const char *func, unsigned int line, const char *fmt, ...);

#define VCOS_ASSERT_MSG(...) ((VCOS_ASSERT_LOGGING && !VCOS_ASSERT_LOGGING_DISABLE) ? vcos_pthreads_logging_assert(__FILE__, __func__, __LINE__, __VA_ARGS__) : (void)0)

#define VCOS_INLINE_BODIES
#define VCOS_INLINE_DECL extern __inline__
#define VCOS_INLINE_IMPL static __inline__

#if !defined( PRId64 )
#define PRId64 "lld"
#endif
#if !defined( PRIi64 )
#define PRIi64 "lli"
#endif
#if !defined( PRIo64 )
#define PRIo64 "llo"
#endif
#if !defined( PRIu64 )
#define PRIu64 "llu"
#endif
#if !defined( PRIx64 )
#define PRIx64 "llx"
#endif

#endif
