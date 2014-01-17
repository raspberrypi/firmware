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

#ifndef MMAL_METADATA_H
#define MMAL_METADATA_H

#include "mmal_common.h"

/** \defgroup MmalMetadata List of pre-defined metadata types
 * This defines a list of standard metadata types. Components can still define proprietary
 * metadata types by using their own FourCC and defining their own metadata structures. */
/* @{ */

/** \name Pre-defined metadata FourCCs */
/* @{ */
#define MMAL_METADATA_HELLO_WORLD             MMAL_FOURCC('H','E','L','O')
/* @} */

/** Generic metadata type. All metadata structures need to begin with these fields. */
typedef struct MMAL_METATDATA_T
{
   uint32_t id;    /**< Metadata id. This is a FourCC */
   uint32_t size;  /**< Size in bytes of the following metadata (not including id and size) */
} MMAL_METADATA_T;

/** Hello World metadata. */
typedef struct MMAL_METATDATA_HELLO_WORLD_T
{
   uint32_t id;    /**< Metadata id. This is a FourCC */
   uint32_t size;  /**< Size in bytes of the following metadata (not including id and size) */

   uint32_t myvalue; /**< Metadata value */
} MMAL_METADATA_HELLO_WORLD_T;

/** Get metadata item from buffer header.
 * This will search through all the metadata in the buffer header and return a pointer to the
 * first instance of the requested metadata id.
 *
 * @param header buffer header containing the metadata
 * @param id     requested metadata id
 *
 * @return Pointer to metadata requested or NULL if not found.
 */
MMAL_METADATA_T *mmal_metadata_get(MMAL_BUFFER_HEADER_T *header, uint32_t id);

/** Set metadata item in buffer header.
 * This will store the metadata item into the buffer header. This operation can fail if not
 * enough memory is available in the data section of the buffer header.
 *
 * @param header   buffer header to store the metadata into
 * @param metadata metadata item to store in buffer header
 *
 * @return MMAL_SUCCESS on success or MMAL_ENOMEM if not enough memory is available for storing
 * the metadata
 */
MMAL_STATUS_T mmal_metadata_set(MMAL_BUFFER_HEADER_T *header, MMAL_METADATA_T *metadata);

/* @} */

#endif /* MMAL_METADATA_H */
