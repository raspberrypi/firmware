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
*
* Font handling for graphicsx
*/

#ifndef VCFTLIB_H
#define VCFTLIB_H

#include <stdint.h>
#include "interface/vmcs_host/vc_dispservice_x_defs.h"
#include "interface/vctypes/vc_image_types.h"
#include "interface/vcos/vcos.h"

//Definitions which in certain functions can be used to mean the actual width and height of a resource, without
//having to know the data implicitly.
#define GRAPHICS_RESOURCE_WIDTH  0xFFFF
#define GRAPHICS_RESOURCE_HEIGHT 0xFFFF

#define R_888_MASK      (0x00FF0000)
#define G_888_MASK      (0x0000FF00)
#define B_888_MASK      (0x000000FF)
#define ALPHA_888_MASK  (0xFF000000)
#define GRAPHICS_RGBA32( r, g, b, a ) GRAPHICS_RGBA888( r, g, b, a )
#define GRAPHICS_RGBA888( r, g, b, a ) ( (((a) << (8+8+8)) & ALPHA_888_MASK) | (((b) << (8+8)) & R_888_MASK) | (((g) << 8) & G_888_MASK) | ((r) & B_888_MASK) )
#define GRAPHICS_TRANSPARENT_COLOUR 0x00000001UL

//resource defs

typedef enum
{
   GRAPHICS_RESOURCE_HANDLE_TYPE_MIN,

   GRAPHICS_RESOURCE_RGB565,
   GRAPHICS_RESOURCE_RGB888, /*  888 format is ONLY used when loading bitmaps
                                 - you can't create or delete bitmaps with this format */
   GRAPHICS_RESOURCE_RGBA32,
   GRAPHICS_RESOURCE_TF_RGB32A,
   GRAPHICS_RESOURCE_TF_RGB565,
   GRAPHICS_RESOURCE_YUV420,

   GRAPHICS_RESOURCE_HANDLE_TYPE_MAX

} GRAPHICS_RESOURCE_TYPE_T;


typedef struct GRAPHICS_RESOURCE_HANDLE_TABLE_T *GRAPHICS_RESOURCE_HANDLE;

VCOS_STATUS_T gx_graphics_init(const char *font_dir);
int32_t graphics_delete_resource( GRAPHICS_RESOURCE_HANDLE res );
VCOS_STATUS_T gx_create_window( uint32_t screen_id,
                                uint32_t width,
                                uint32_t height,
                                GRAPHICS_RESOURCE_TYPE_T image_type,
                                GRAPHICS_RESOURCE_HANDLE *resource_handle );

int32_t graphics_display_resource( GRAPHICS_RESOURCE_HANDLE res,
                                   const uint16_t screen_number,
                                   const int16_t z_order,
                                   const uint16_t offset_x,
                                   const uint16_t offset_y,
                                   const uint16_t dest_width,
                                   const uint16_t dest_height,
                                   const VC_DISPMAN_TRANSFORM_T transform,
                                   const uint8_t display );

int32_t graphics_resource_fill(GRAPHICS_RESOURCE_HANDLE res,
                               uint32_t x,
                               uint32_t y,
                               uint32_t width,
                               uint32_t height,
                               uint32_t fill_colour );

int32_t graphics_update_displayed_resource(GRAPHICS_RESOURCE_HANDLE res,
                                           const uint32_t x_offset,
                                           const uint32_t y_offset,
                                           const uint32_t width,
                                           const uint32_t height );

int32_t graphics_resource_render_text_ext( GRAPHICS_RESOURCE_HANDLE res,
                                           const uint32_t x,
                                           const uint32_t y,
                                           const uint32_t width,
                                           const uint32_t height,
                                           const uint32_t fg_colour,
                                           const uint32_t bg_colour,
                                           const char *text,
                                           const uint32_t text_length,
                                           const uint32_t text_size );

int32_t graphics_resource_text_dimensions_ext(GRAPHICS_RESOURCE_HANDLE res,
                                              const char *text,
                                              const uint32_t text_length,
                                              uint32_t *width,
                                              uint32_t *height,
                                              const uint32_t text_size );

int32_t graphics_get_resource_size(
   const GRAPHICS_RESOURCE_HANDLE res,
   uint32_t *w,
   uint32_t *h);

int32_t graphics_update_start(void);

int32_t graphics_update_end( void );

int32_t graphics_resource_text_dimensions( GRAPHICS_RESOURCE_HANDLE resource_handle,
                                           const char *text,
                                           const uint32_t text_length,
                                           uint32_t *width,
                                           uint32_t *height );

#endif
