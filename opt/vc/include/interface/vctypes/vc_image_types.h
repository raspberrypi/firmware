/*
* Copyright (c) 2012 Broadcom Europe Ltd
*
* Licensed to the Apache Software Foundation (ASF) under one or more
* contributor license agreements.  See the NOTICE file distributed with
* this work for additional information regarding copyright ownership.
* The ASF licenses this file to You under the Apache License, Version 2.0
* (the "License"); you may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Common image types used by the vc_image library.
*/

#ifndef INTERFACE_VC_IMAGE_TYPES_H
#define INTERFACE_VC_IMAGE_TYPES_H

/* This file gets included by the VCE compiler, which gets confused
 * easily by the VCOS headers. So cannot include vcos.h here.
 */
#include "interface/vcos/vcos_stdint.h"

/* We have so many rectangle types; let's try to introduce a common one. */
typedef struct tag_VC_RECT_T {
   int32_t x;
   int32_t y;
   int32_t width;
   int32_t height;
} VC_RECT_T;

struct VC_IMAGE_T;
typedef struct VC_IMAGE_T VC_IMAGE_T;

/* Types of image supported. */
/* Please add any new types to the *end* of this list.  Also update
 * case_VC_IMAGE_ANY_xxx macros (below), and the vc_image_type_info table in
 * vc_image/vc_image_helper.c.
 */
typedef enum
{
   VC_IMAGE_MIN = 0, //bounds for error checking

   VC_IMAGE_RGB565 = 1,
   VC_IMAGE_1BPP,
   VC_IMAGE_YUV420,
   VC_IMAGE_48BPP,
   VC_IMAGE_RGB888,
   VC_IMAGE_8BPP,
   VC_IMAGE_4BPP,    // 4bpp palettised image
   VC_IMAGE_3D32,    /* A separated format of 16 colour/light shorts followed by 16 z values */
   VC_IMAGE_3D32B,   /* 16 colours followed by 16 z values */
   VC_IMAGE_3D32MAT, /* A separated format of 16 material/colour/light shorts followed by 16 z values */
   VC_IMAGE_RGB2X9,   /* 32 bit format containing 18 bits of 6.6.6 RGB, 9 bits per short */
   VC_IMAGE_RGB666,   /* 32-bit format holding 18 bits of 6.6.6 RGB */
   VC_IMAGE_PAL4_OBSOLETE,     // 4bpp palettised image with embedded palette
   VC_IMAGE_PAL8_OBSOLETE,     // 8bpp palettised image with embedded palette
   VC_IMAGE_RGBA32,   /* RGB888 with an alpha byte after each pixel */ /* xxx: isn't it BEFORE each pixel? */
   VC_IMAGE_YUV422,   /* a line of Y (32-byte padded), a line of U (16-byte padded), and a line of V (16-byte padded) */
   VC_IMAGE_RGBA565,  /* RGB565 with a transparent patch */
   VC_IMAGE_RGBA16,   /* Compressed (4444) version of RGBA32 */
   VC_IMAGE_YUV_UV,   /* VCIII codec format */
   VC_IMAGE_TF_RGBA32, /* VCIII T-format RGBA8888 */
   VC_IMAGE_TF_RGBX32,  /* VCIII T-format RGBx8888 */
   VC_IMAGE_TF_FLOAT, /* VCIII T-format float */
   VC_IMAGE_TF_RGBA16, /* VCIII T-format RGBA4444 */
   VC_IMAGE_TF_RGBA5551, /* VCIII T-format RGB5551 */
   VC_IMAGE_TF_RGB565, /* VCIII T-format RGB565 */
   VC_IMAGE_TF_YA88, /* VCIII T-format 8-bit luma and 8-bit alpha */
   VC_IMAGE_TF_BYTE, /* VCIII T-format 8 bit generic sample */
   VC_IMAGE_TF_PAL8, /* VCIII T-format 8-bit palette */
   VC_IMAGE_TF_PAL4, /* VCIII T-format 4-bit palette */
   VC_IMAGE_TF_ETC1, /* VCIII T-format Ericsson Texture Compressed */
   VC_IMAGE_BGR888,  /* RGB888 with R & B swapped */
   VC_IMAGE_BGR888_NP,  /* RGB888 with R & B swapped, but with no pitch, i.e. no padding after each row of pixels */
   VC_IMAGE_BAYER,  /* Bayer image, extra defines which variant is being used */
   VC_IMAGE_CODEC,  /* General wrapper for codec images e.g. JPEG from camera */
   VC_IMAGE_YUV_UV32,   /* VCIII codec format */
   VC_IMAGE_TF_Y8,   /* VCIII T-format 8-bit luma */
   VC_IMAGE_TF_A8,   /* VCIII T-format 8-bit alpha */
   VC_IMAGE_TF_SHORT,/* VCIII T-format 16-bit generic sample */
   VC_IMAGE_TF_1BPP, /* VCIII T-format 1bpp black/white */
   VC_IMAGE_OPENGL,
   VC_IMAGE_YUV444I, /* VCIII-B0 HVS YUV 4:4:4 interleaved samples */
   VC_IMAGE_YUV422PLANAR,  /* Y, U, & V planes separately (VC_IMAGE_YUV422 has them interleaved on a per line basis) */
   VC_IMAGE_ARGB8888,   /* 32bpp with 8bit alpha at MS byte, with R, G, B (LS byte) */
   VC_IMAGE_XRGB8888,   /* 32bpp with 8bit unused at MS byte, with R, G, B (LS byte) */

   VC_IMAGE_YUV422YUYV,  /* interleaved 8 bit samples of Y, U, Y, V */
   VC_IMAGE_YUV422YVYU,  /* interleaved 8 bit samples of Y, V, Y, U */
   VC_IMAGE_YUV422UYVY,  /* interleaved 8 bit samples of U, Y, V, Y */
   VC_IMAGE_YUV422VYUY,  /* interleaved 8 bit samples of V, Y, U, Y */

   VC_IMAGE_RGBX32,      /* 32bpp like RGBA32 but with unused alpha */
   VC_IMAGE_RGBX8888,    /* 32bpp, corresponding to RGBA with unused alpha */
   VC_IMAGE_BGRX8888,    /* 32bpp, corresponding to BGRA with unused alpha */

   VC_IMAGE_YUV420SP,    /* Y as a plane, then UV byte interleaved in plane with with same pitch, half height */
   
   VC_IMAGE_YUV444PLANAR,  /* Y, U, & V planes separately 4:4:4 */
   
   VC_IMAGE_MAX,     //bounds for error checking
   VC_IMAGE_FORCE_ENUM_16BIT = 0xffff,
} VC_IMAGE_TYPE_T;

/* Image transformations (flips and 90 degree rotations).
   These are made out of 3 primitives (transpose is done first).
   These must match the DISPMAN and Media Player definitions. */

#define TRANSFORM_HFLIP     (1<<0)
#define TRANSFORM_VFLIP     (1<<1)
#define TRANSFORM_TRANSPOSE (1<<2)

typedef enum {
   VC_IMAGE_ROT0           = 0,
   VC_IMAGE_MIRROR_ROT0    = TRANSFORM_HFLIP,
   VC_IMAGE_MIRROR_ROT180  = TRANSFORM_VFLIP,
   VC_IMAGE_ROT180         = TRANSFORM_HFLIP|TRANSFORM_VFLIP,
   VC_IMAGE_MIRROR_ROT90   = TRANSFORM_TRANSPOSE,
   VC_IMAGE_ROT270         = TRANSFORM_TRANSPOSE|TRANSFORM_HFLIP,
   VC_IMAGE_ROT90          = TRANSFORM_TRANSPOSE|TRANSFORM_VFLIP,
   VC_IMAGE_MIRROR_ROT270  = TRANSFORM_TRANSPOSE|TRANSFORM_HFLIP|TRANSFORM_VFLIP,
} VC_IMAGE_TRANSFORM_T;

typedef enum
{ //defined to be identical to register bits
   VC_IMAGE_BAYER_RGGB     = 0,
   VC_IMAGE_BAYER_GBRG     = 1,
   VC_IMAGE_BAYER_BGGR     = 2,
   VC_IMAGE_BAYER_GRBG     = 3
} VC_IMAGE_BAYER_ORDER_T;

typedef enum
{ //defined to be identical to register bits
   VC_IMAGE_BAYER_RAW6     = 0,
   VC_IMAGE_BAYER_RAW7     = 1,
   VC_IMAGE_BAYER_RAW8     = 2,
   VC_IMAGE_BAYER_RAW10    = 3,
   VC_IMAGE_BAYER_RAW12    = 4,
   VC_IMAGE_BAYER_RAW14    = 5,
   VC_IMAGE_BAYER_RAW16    = 6,
   VC_IMAGE_BAYER_RAW10_8  = 7,
   VC_IMAGE_BAYER_RAW12_8  = 8,
   VC_IMAGE_BAYER_RAW14_8  = 9,
   VC_IMAGE_BAYER_RAW10L   = 11,
   VC_IMAGE_BAYER_RAW12L   = 12,
   VC_IMAGE_BAYER_RAW14L   = 13,
   VC_IMAGE_BAYER_RAW16_BIG_ENDIAN = 14, 
   VC_IMAGE_BAYER_RAW4    = 15,
} VC_IMAGE_BAYER_FORMAT_T;

#endif /* __VC_INCLUDE_IMAGE_TYPES_H__ */

