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

#ifndef MMAL_PORT_PRIVATE_H
#define MMAL_PORT_PRIVATE_H

#include "interface/mmal/mmal.h"
#include "interface/mmal/mmal_clock.h"

/** Definition of a port. */
typedef struct MMAL_PORT_PRIVATE_T
{
   /** Pointer to the private data of the core */
   struct MMAL_PORT_PRIVATE_CORE_T *core;
   /** Pointer to the private data of the module in use */
   struct MMAL_PORT_MODULE_T *module;

   MMAL_STATUS_T (*pf_set_format)(MMAL_PORT_T *port);
   MMAL_STATUS_T (*pf_enable)(MMAL_PORT_T *port, MMAL_PORT_BH_CB_T);
   MMAL_STATUS_T (*pf_disable)(MMAL_PORT_T *port);
   MMAL_STATUS_T (*pf_send)(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *);
   MMAL_STATUS_T (*pf_flush)(MMAL_PORT_T *port);
   MMAL_STATUS_T (*pf_parameter_set)(MMAL_PORT_T *port, const MMAL_PARAMETER_HEADER_T *param);
   MMAL_STATUS_T (*pf_parameter_get)(MMAL_PORT_T *port, MMAL_PARAMETER_HEADER_T *param);
   MMAL_STATUS_T (*pf_connect)(MMAL_PORT_T *port, MMAL_PORT_T *other_port);

   uint8_t *(*pf_payload_alloc)(MMAL_PORT_T *port, uint32_t payload_size);
   void     (*pf_payload_free)(MMAL_PORT_T *port, uint8_t *payload);

} MMAL_PORT_PRIVATE_T;

/** Callback called by components when a \ref MMAL_BUFFER_HEADER_T needs to be sent back to the
 * user */
void mmal_port_buffer_header_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer);

/** Callback called by components when an event \ref MMAL_BUFFER_HEADER_T needs to be sent to the
 * user. Events differ from ordinary buffer headers because they originate from the component
 * and do not return data from the client to the component. */
void mmal_port_event_send(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer);

/** Allocate a port structure */
MMAL_PORT_T *mmal_port_alloc(MMAL_COMPONENT_T *, MMAL_PORT_TYPE_T type, unsigned int extra_size);
/** Free a port structure */
void mmal_port_free(MMAL_PORT_T *port);
/** Allocate an array of ports */
MMAL_PORT_T **mmal_ports_alloc(MMAL_COMPONENT_T *, unsigned int ports_num, MMAL_PORT_TYPE_T type,
                               unsigned int extra_size);
/** Free an array of ports */
void mmal_ports_free(MMAL_PORT_T **ports, unsigned int ports_num);

/** Acquire a reference on a port */
void mmal_port_acquire(MMAL_PORT_T *port);

/** Release a reference on a port */
MMAL_STATUS_T mmal_port_release(MMAL_PORT_T *port);

/** Pause processing on a port */
MMAL_STATUS_T mmal_port_pause(MMAL_PORT_T *port, MMAL_BOOL_T pause);

/*****************************************************************************
 * Clock Port API
 *****************************************************************************/
/** Definition of a clock port event callback.
 * Used to inform the client of a clock event that has occurred.
 *
 * @param port       The clock port where the event occurred
 * @param event      The event that has occurred
 */
typedef void (*MMAL_PORT_CLOCK_EVENT_CB)(MMAL_PORT_T *port, const MMAL_CLOCK_PAYLOAD_T *event);

/** Allocate a clock port.
 *
 * @param component  The component requesting the alloc
 * @param event_cb   Clock event callback
 *
 * @return Pointer to new clock port or NULL on failure.
 */
MMAL_PORT_T* mmal_port_clock_alloc(MMAL_COMPONENT_T *component, MMAL_PORT_CLOCK_EVENT_CB event_cb);

/** Free a clock port.
 *
 * @param port       The clock port to free
 */
void mmal_port_clock_free(MMAL_PORT_T *port);

/** Allocate an array of clock ports.
 *
 * @param component  The component requesting the alloc
 * @param ports_num  Number of ports to allocate
 * @param event_cb   Clock event callback
 *
 * @return Pointer to a new array of clock ports or NULL on failure.
 */
MMAL_PORT_T **mmal_ports_clock_alloc(MMAL_COMPONENT_T *component, unsigned int ports_num, MMAL_PORT_CLOCK_EVENT_CB event_cb);

/** Free an array of clock ports.
 *
 * @param ports      The clock ports to free
 * @param ports_num  Number of ports to free
 */
void mmal_ports_clock_free(MMAL_PORT_T **ports, unsigned int ports_num);

/** Definition of a clock port request callback.
 * This is invoked when the media-time requested by the client is reached.
 *
 * @param port       The clock port which serviced the request
 * @param media_time The current media-time
 * @param cb_data    Client-supplied data
 */
typedef void (*MMAL_PORT_CLOCK_REQUEST_CB)(MMAL_PORT_T *port, int64_t media_time, void *cb_data);

/** Register a request with the clock port.
 * When the specified media-time is reached, the clock port will invoke the supplied callback.
 *
 * @param port       The clock port
 * @param media_time The media-time at which the callback should be invoked (microseconds)
 * @param offset     Time offset (in microseconds) applied to the media-time. This can be used
 *                   to schedule the request slightly in advance of the media-time.
 * @param cb         Callback to invoke
 * @param cb_data    Client-supplied callback data
 *
 * @return MMAL_SUCCESS on success
 */
MMAL_STATUS_T mmal_port_clock_request_add(MMAL_PORT_T *port, int64_t media_time, int64_t offset,
                                          MMAL_PORT_CLOCK_REQUEST_CB cb, void *cb_data);

/** Remove all previously registered clock port requests.
 *
 * @param port       The clock port
 *
 * @return MMAL_SUCCESS on success
 */
MMAL_STATUS_T mmal_port_clock_request_flush(MMAL_PORT_T *port);

/** Update the clock port's media-time.
 *
 * @param port       The clock port to update
 * @param media_time New media-time to be applied (microseconds)
 *
 * @return MMAL_SUCCESS on success
 */
MMAL_STATUS_T mmal_port_clock_media_time_set(MMAL_PORT_T *port, int64_t media_time);

/** Set an offset for the port's media-time.
 *
 * @param port       The clock port to update
 * @param offset     Media-time offset (microseconds)
 *
 * @return MMAL_SUCCESS on success
 */
MMAL_STATUS_T mmal_port_clock_media_time_offset_set(MMAL_PORT_T *port, int64_t offset);

/** Get the clock port's current media-time.
 * This takes the clock port's scale and media-time offset into account.
 *
 * @param port       The clock port to query
 *
 * @return Current media-time in microseconds
 */
int64_t mmal_port_clock_media_time_get(MMAL_PORT_T *port);

/** Get the clock port's media-time offset.
 *
 * @param port       The clock port to query
 *
 * @return Media-time offset in microseconds
 */
int64_t mmal_port_clock_media_time_offset_get(MMAL_PORT_T *port);

/** Set the clock port's scale.
 *
 * @param port       The clock port
 * @param scale      Scale factor in Q16 format
 *
 * @return MMAL_SUCCESS on success
 */
MMAL_STATUS_T mmal_port_clock_scale_set(MMAL_PORT_T *port, MMAL_RATIONAL_T scale);

/** Get the clock port's scale.
 *
 * @param port       The clock port
 *
 * @return Current clock port scale factor
 */
MMAL_RATIONAL_T mmal_port_clock_scale_get(MMAL_PORT_T *port);

/** Get the clock port's state.
 *
 * @param port       The clock port to query
 *
 * @return TRUE if clock port is active (i.e. local media-time is advancing)
 */
MMAL_BOOL_T mmal_port_clock_is_active(MMAL_PORT_T *port);

#endif /* MMAL_PORT_PRIVATE_H */
