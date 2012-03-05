/*=============================================================================
Copyright (c) 2006 Broadcom Europe Limited.
Copyright (c) 2005 Alphamosaic Limited.
All rights reserved.

Project  :  VideoCore
Module   :  VideoCore specific header (common)

FILE DESCRIPTION
Common types and helper macros for C/C++.
=============================================================================*/

#ifndef __VC_INCLUDE_COMMON_H__
#define __VC_INCLUDE_COMMON_H__

#include "interface/vcos/vcos_stdint.h"
#include "interface/vctypes/vc_image_types.h"

#if defined(__HIGHC__) && defined(_VIDEOCORE) && !defined(_I386)
// __HIGHC__ is only available with MW
// The scvc plugins are compiled (bizarrely) on an x86 with _VIDEOCORE set!
#include <vc/intrinsics.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __SYMBIAN32__
# ifndef INLINE
#  define INLINE __inline
# endif

/* Align a pointer/integer by rounding up/down */
#define ALIGN_DOWN(p, n)   ((uint32_t)(p) - ( (uint32_t)(p) % (uint32_t)(n) ))
#define ALIGN_UP(p, n)     ALIGN_DOWN((uint32_t)(p) + (uint32_t)(n) - 1, (n))

#elif defined (VCMODS_LCC)
#include <limits.h>


#elif !defined(__KERNEL__)
#include <limits.h>

#endif


/*}}}*/

/* Fixed-point types */
typedef unsigned short uint8p8_t;
typedef signed short sint8p8_t;
typedef unsigned short uint4p12_t;
typedef signed short sint4p12_t;
typedef signed short sint0p16_t;
typedef signed char sint8p0_t;
typedef unsigned char uint0p8_t;
typedef signed long int24p8_t;

/*{{{ Common typedefs */

typedef enum bool_e
{
   VC_FALSE = 0,
   VC_TRUE = 1,
} bool_t;

/*}}}*/

/*{{{ Common macros */


/* Align a pointer/integer by rounding up/down */
#define ALIGN_DOWN(p, n)   ((uintptr_t)(p) - ( (uintptr_t)(p) % (uintptr_t)(n) ))
#define ALIGN_UP(p, n)     ALIGN_DOWN((uintptr_t)(p) + (uintptr_t)(n) - 1, (n))

#define CLIP(lower, n, upper) _min((upper), _max((lower), (n)))

/*}}}*/

/*{{{ Debugging and profiling macros */

#if 0
/* There's already an assert_once in <logging/logging.h> */
#ifdef DEBUG
#define assert_once(x) \
   { \
      static uint8_t ignore = 0; \
      if(!ignore) \
      { \
         assert(x); \
         ignore++; \
      } \
   }
#else
#define assert_once(x) (void)0
#endif
#endif /* 0 */

#if defined(__HIGHC__) && !defined(NDEBUG)
/* HighC lacks a __FUNCTION__ preproc symbol... :( */
#define profile_rename(name) _ASM(".global " name "\n" name ":\n")
#else
#define profile_rename(name) (void)0
#endif

/*}}}*/
#ifdef __cplusplus
 }
#endif
#endif /* __VCINCLUDE_COMMON_H__ */

