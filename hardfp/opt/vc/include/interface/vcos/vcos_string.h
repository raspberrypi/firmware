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

/*=============================================================================
VideoCore OS Abstraction Layer - public header file
=============================================================================*/

#ifndef VCOS_STRING_H
#define VCOS_STRING_H

/**
  * \file
  *
  * String functions.
  *
  */

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

#ifdef __KERNEL__
#include <linux/string.h>
#else
#include <string.h>
#endif

/** Case insensitive string comparison.
  *
  */

VCOS_INLINE_DECL
int vcos_strcasecmp(const char *s1, const char *s2);

VCOS_INLINE_DECL
int vcos_strncasecmp(const char *s1, const char *s2, size_t n);

VCOSPRE_ int VCOSPOST_ vcos_vsnprintf( char *buf, size_t buflen, const char *fmt, va_list ap );

VCOSPRE_ int VCOSPOST_ vcos_snprintf(char *buf, size_t buflen, const char *fmt, ...);

VCOS_STATIC_INLINE
int vcos_strlen(const char *s) { return (int)strlen(s); }

VCOS_STATIC_INLINE
int vcos_strcmp(const char *s1, const char *s2) { return strcmp(s1,s2); }

VCOS_STATIC_INLINE
int vcos_strncmp(const char *cs, const char *ct, size_t count) { return strncmp(cs, ct, count); }

VCOS_STATIC_INLINE
char *vcos_strcpy(char *dst, const char *src) { return strcpy(dst, src); }

VCOS_STATIC_INLINE
char *vcos_strncpy(char *dst, const char *src, size_t count) { return strncpy(dst, src, count); }

VCOS_STATIC_INLINE
void *vcos_memcpy(void *dst, const void *src, size_t n) {  memcpy(dst, src, n);  return dst;  }

VCOS_STATIC_INLINE
void *vcos_memset(void *p, int c, size_t n) { return memset(p, c, n); }

VCOS_STATIC_INLINE
int vcos_memcmp(const void *ptr1, const void *ptr2, size_t count) { return memcmp(ptr1, ptr2, count); }

#ifdef __cplusplus
}
#endif
#endif
