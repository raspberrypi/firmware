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

#ifndef VGFT_H
#define VGFT_H

#include "interface/vcos/vcos.h"
#include <VG/openvg.h>
#include <ft2build.h>

typedef int VGFT_BOOL;
#define VGFT_FALSE 0
#define VGFT_TRUE (!VGFT_FALSE)

#include FT_FREETYPE_H

/* Returns 0 on success */
extern int vgft_init(void);
extern void vgft_term(void);

typedef struct {
   VGFont vg_font;
   FT_Face ft_face;
} VGFT_FONT_T;

/** Initialise a FT->VG font */
VCOS_STATUS_T vgft_font_init(VGFT_FONT_T *font);

/** Load a font file from memory */
VCOS_STATUS_T vgft_font_load_mem(VGFT_FONT_T *font, void *mem, size_t len);

/** Convert a font into VG glyphs */
VCOS_STATUS_T vgft_font_convert_glyphs(VGFT_FONT_T *font, unsigned int char_height, unsigned int dpi_x, unsigned int dpi_y);

/** Release a font. */
void vgft_font_term(VGFT_FONT_T *font);

void vgft_font_draw(VGFT_FONT_T *font, VGfloat x, VGfloat y, const char *text, unsigned text_length, VGbitfield paint_modes);

void vgft_get_text_extents(VGFT_FONT_T *font, const char *text, unsigned text_length, VGfloat x, VGfloat y,
                           VGfloat *w, VGfloat *h);

#endif
