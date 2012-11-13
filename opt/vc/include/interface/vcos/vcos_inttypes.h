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
