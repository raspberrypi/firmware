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


#ifndef MMAL_CLOCK_H
#define MMAL_CLOCK_H

#include "mmal_types.h"
#include "mmal_common.h"

/** \defgroup MmalClock Clock Framework
 * The MMAL clock framework provides scheduling facilities to the rest of
 * MMAL.
 *
 * The framework consists mainly of clock ports and a clock module. Client
 * applications and components interact directly with clock ports, while
 * the clock module is only used internally by clock ports.
 *
 * Clock ports ensure that the local media-time for each component is
 * synchronised across all components. This is done by passing buffers between
 * clock ports which contain clock-specific data.
 *
 * One clock port will normally act as the reference clock for the rest of the
 * system. This is usually chosen to be the clock port of the audio render
 * component, but is configurable by the client and could potentially be any
 * other clock port (or even the client application itself).
 *
 * Components that are responsible for timed delivery of frames, do so by
 * registering callback requests for a particular time-stamp with the clock
 * port. These requests are scheduled using the clock module which maintains
 * an internal media-time.
 *
 * The clock framework also provides the ability to perform playback at different
 * speeds. This is achieved with a clock scale factor which determines the speed
 * at which the media-time advances relative to real-time, with:
 *   scale = 1.0 -> normal playback speed
 *   scale = 0   -> playback paused
 *   scale > 1.0 -> fast-forward
 *   scale < 1.0 -> slow motion
 */

/** Clock payload magic */
#define MMAL_CLOCK_PAYLOAD_MAGIC     MMAL_FOURCC('C','K','L','M')

/** Clock reference update */
#define MMAL_CLOCK_PAYLOAD_REFERENCE MMAL_FOURCC('C','R','E','F')

/** Clock state update */
#define MMAL_CLOCK_PAYLOAD_ACTIVE    MMAL_FOURCC('C','A','C','T')

/** Clock scale update */
#define MMAL_CLOCK_PAYLOAD_SCALE     MMAL_FOURCC('C','S','C','A')

/** Clock media-time update */
#define MMAL_CLOCK_PAYLOAD_TIME      MMAL_FOURCC('C','T','I','M')

/** Clock payload not valid */
#define MMAL_CLOCK_PAYLOAD_INVALID   0

/** Clock buffer payload type used to pass data between clock ports
 * and for signalling a clock event to a client. */
typedef struct MMAL_CLOCK_PAYLOAD_T
{
   uint32_t id;                 /**< 4cc payload id */
   uint32_t magic;              /**< 4cc payload magic */
   int64_t time;                /**< media-time at which the event ocurred */
   union
   {
      MMAL_BOOL_T enable;       /**< clock reference or clock active */
      MMAL_RATIONAL_T scale;    /**< new clock scale */
   } data;
} MMAL_CLOCK_PAYLOAD_T;

#endif /* MMAL_CLOCK_H */
