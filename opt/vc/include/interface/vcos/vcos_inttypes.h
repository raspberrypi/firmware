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

#ifndef VCOS_INTTYPES_H
#define VCOS_INTTYPES_H

/* Attempt to provide the support for fixed width integer types as per inttypes.h.
 *
 * Ideally this would either call out to a platform-specific header file (e.g.
 * inttypes.h) or define the types on a per-architecture/compiler basis. But for
 * now we just use #ifdefs.
 *
 * Initially this just provides the most common printf() macros.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_stdint.h"

#ifdef __SYMBIAN32__

# define VCOS_INTTYPES_ILP32

#elif defined(__STDC__) && __STDC_VERSION__ >= 199901L

# include <inttypes.h>

#elif defined(__GNUC__)

# include <inttypes.h>

#elif defined(_MSC_VER)                     /* Visual C define equivalent types */

# define VCOS_INTTYPES_ILP32

#elif defined(__VIDEOCORE__)

# define VCOS_INTTYPES_ILP32

#elif defined (__HIGHC__) && defined(_I386)

# include <inttypes.h>

#else
# error Unknown platform
#endif

/* VCOS_INTTYPES_ILP32 = ILP32 architecture, with 32-bit types defined as long int */
#ifdef VCOS_INTTYPES_ILP32

# define PRId8    "d"
# define PRId16   "d"
# define PRId32   "ld"
# ifndef PRId64
#  define PRId64  "lld"
# endif
# define PRIdMAX  "lld"
# define PRIdPTR  "ld"

# define PRIi8    "i"
# define PRIi16   "i"
# define PRIi32   "li"
# ifndef PRIi64
#  define PRIi64  "lli"
# endif
# define PRIiMAX  "lli"
# define PRIiPTR  "li"

# define PRIo8    "o"
# define PRIo16   "o"
# define PRIo32   "lo"
# ifndef PRIo64
#  define PRIo64  "llo"
# endif
# define PRIoMAX  "llo"
# define PRIoPTR  "lo"

# define PRIu8    "u"
# define PRIu16   "u"
# define PRIu32   "lu"
# ifndef PRIu64
#  define PRIu64  "llu"
# endif
# define PRIuMAX  "llu"
# define PRIuPTR  "lu"

# define PRIx8    "x"
# define PRIx16   "x"
# define PRIx32   "lx"
# ifndef PRIx64
#  define PRIx64  "llx"
# endif
# define PRIxMAX  "llx"
# define PRIxPTR  "lx"

# define PRIX8    "X"
# define PRIX16   "X"
# define PRIX32   "lX"
# ifndef PRIX64
#  define PRIX64  "llX"
# endif
# define PRIXMAX  "llX"
# define PRIXPTR  "lX"

#endif

#ifdef __cplusplus
}
#endif

#endif /* VCOS_INTTYPES_H */
