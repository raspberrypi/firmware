/*
 * Copyright (c) 2010-11 Broadcom Corporation. All rights reserved.
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

#ifndef VCHIQ_VC_DMA_XFERS_H
#define VCHIQ_VC_DMA_XFERS_H

/* Opaque declaration for clients of this library */
typedef struct dma_transfer dma_transfer_t;

extern VCHIQ_STATUS_T
init_dma_xfers(int max_fragments, FRAGMENTS_T *fragments);

extern void
uninit_dma_xfers(void);

extern dma_transfer_t *
alloc_dma_xfer(void);

extern void
free_dma_xfer(dma_transfer_t *xfer);

extern int
dma_memcpy_pagelist(char *vcptr, const PAGELIST_T *pagelist);

#endif /* VCHIQ_VC_DMA_XFERS */
