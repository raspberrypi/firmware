/* $Revision: 6810 $ on $Date:: 2008-10-29 07:31:37 -0700 #$ */

/*------------------------------------------------------------------------
 *
 * VG platform specific header Reference Implementation
 * ----------------------------------------------------
 *
 * Copyright (c) 2008 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and /or associated documentation files
 * (the "Materials "), to deal in the Materials without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Materials,
 * and to permit persons to whom the Materials are furnished to do so,
 * subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Materials. 
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR
 * THE USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 *//**
 * \file
 * \brief VG platform specific header
 *//*-------------------------------------------------------------------*/

#ifndef _VGPLATFORM_H
#define _VGPLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VG_API_CALL 
#if defined(OPENVG_STATIC_LIBRARY)
#	define VG_API_CALL
#else
#	if defined(_WIN32) || defined(__VC32__)				/* Win32 */
#		if defined (OPENVG_DLL_EXPORTS)
#			define VG_API_CALL __declspec(dllexport)
#		else
#			define VG_API_CALL __declspec(dllimport)
#		endif
#	else 
#		define VG_API_CALL extern
#	endif /* defined(_WIN32) ||... */
#endif /* defined OPENVG_STATIC_LIBRARY */
#endif /* ifndef VG_API_CALL */

#ifndef VGU_API_CALL 
#if defined(OPENVG_STATIC_LIBRARY)
#	define VGU_API_CALL
#else
#	if defined(_WIN32) || defined(__VC32__)				/* Win32 */
#		if defined (OPENVG_DLL_EXPORTS)
#			define VGU_API_CALL __declspec(dllexport)
#		else
#			define VGU_API_CALL __declspec(dllimport)
#		endif
#	else 
#		define VGU_API_CALL extern
#	endif /* defined(_WIN32) ||... */
#endif /* defined OPENVG_STATIC_LIBRARY */
#endif /* ifndef VGU_API_CALL */


#ifndef VG_API_ENTRY
#define VG_API_ENTRY
#endif

#ifndef VG_API_EXIT
#define VG_API_EXIT
#endif

#ifndef VGU_API_ENTRY
#define VGU_API_ENTRY
#endif

#ifndef VGU_API_EXIT
#define VGU_API_EXIT
#endif

typedef float          VGfloat;
typedef signed char    VGbyte;
typedef unsigned char  VGubyte;
typedef signed short   VGshort;
typedef signed int     VGint;
typedef unsigned int   VGuint;
typedef unsigned int   VGbitfield;

#ifndef VG_VGEXT_PROTOTYPES
#define VG_VGEXT_PROTOTYPES
#endif 

#ifdef __cplusplus 
} /* extern "C" */
#endif

#endif /* _VGPLATFORM_H */
