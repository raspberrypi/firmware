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
* Service for controlling the touch screen and videocore-hosted buttons
*/


#ifndef _VC_VCHI_TOUCH_H
#define _VC_VCHI_TOUCH_H

#include "vchost_config.h"
#include "interface/vchi/vchi.h"
#include "interface/vcos/vcos.h" /* for VCHPRE_ and VCHPOST_ */
#include "interface/peer/vc_touch_api_types.h"
  

/*===========================================================================*/
/*  Touch Service Lifetime Control                                           */
/*===========================================================================*/

/*! Initialise touch service. Returns it's interface number. This
 *  initialises the host side of the interface, it does not send anything to
 *  VideoCore.
 */
VCHPRE_ int VCHPOST_
vc_touch_init(void);


/*! Initialise the general command service for use by a single client.
 *  A negative return value indicates failure (which may mean it has not been
 *  started on VideoCore).
 */
VCHPRE_ int32_t /*rc*/ VCHPOST_
vc_vchi_touch_client_init(TOUCH_SERVICE_T *new_client_state,
                          VCHI_INSTANCE_T initialise_instance,
                          VCHI_CONNECTION_T **connections,
                          uint32_t num_connections);

/*! Stop the service from being used.
 */
VCHPRE_ void VCHPOST_ vc_touch_end(TOUCH_SERVICE_T *client_state);


/*===========================================================================*/
/*  Touchscreen Service Access                                               */
/*===========================================================================*/

/* The functions below send and receive messages to the touchscreen service.
   All of them send a request and then suspend until a response is received.
   If an event message occurs before the response it is ignored and
   handled by a service callback.

   Each of the request/response functions provides a return code that indicates
   succesful operation of the service access protocol.  (Zero is success,
   non-zero indicates a problem.)
*/


/*! This function services any event messages received from the service
 *  Event messages are handled both by this function and during any of the
 *  other operations supported by the API.
 *  It does not suspend awaiting messages.
 *  This function (as the other API functions) should be called in task context.
 *  Returns zero iff one or more events were found and handled correctly.
 */
extern int32_t /*rc*/
vc_touch_poll(TOUCH_SERVICE_T *touchserv);




/*===========================================================================*/
/*  Touchscreen Fingers                                                      */
/*===========================================================================*/

/*! Return the properties of the touch device
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_properties(TOUCH_SERVICE_T *touchserv,
                    vc_touch_properties_t *out_properties);

/*! Set the size of the screen in an alternative coordinate system.
 *     \param scaled_width - scaled X width of the touch screen area
 *     \param scaled_height - scaled Y height of the touch screen area
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_set_scale(TOUCH_SERVICE_T *touchserv,
                   int scaled_width, int scaled_height);


/*! Return the locations of the fingers currently in contact with the  
 *  touchscreen.
 *  Up to \c max_fingers finger positions will be returned - further finger
 *  positions will be ignored.  Finger records that are returned with pressure
 *  zero are unused.  Present fingers (pressure != 0) will always be recorded
 *  earlier in the array of values than absent ones.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_finger_event(TOUCH_SERVICE_T *touchserv, 
                      vc_touch_point_t *out_posns, int max_fingers);

/*! Return the scaled location of the fingers currently in contact with the  
 *  touchscreen.
 *  Other than returning X and Y values that are in scaled coordinates
 *  this function is identical to \c vc_touch_finger_event.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_finger_pos(TOUCH_SERVICE_T *touchserv, 
                    vc_touch_point_t *out_posns, int max_fingers);
   
/*! Return the scaled location of the fingers currently in contact with the  
 *  touchscreen.
 *  Other than returning X and Y values that are in scaled coordinates
 *  this function is identical to \c vc_touch_finger_event.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_finger_scaled_pos(TOUCH_SERVICE_T *touchserv, 
                           vc_touch_point_t *out_posns, int max_fingers);


/*! Begin generating events from the touchscreen at a rate no greater than
 *  once every \c period_ms.  The events result in the callback of the \c event
 *  function which is supplied with \c open_arg.
 *  Note that the context in which \c event is called may not be suitable for
 *  sustained processing operations.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_finger_events_open(TOUCH_SERVICE_T *touchserv, 
                            int period_ms, int max_fingers,
                            vc_touch_event_fn_t *event_fn, void *open_arg);


/*! Stop generating events using the given function and argument
 */
#define vc_touch_finger_events_close(touchserv, event_fn, open_arg)      \
   vc_touch_finger_events_open(touchserv, 0, event_fn, open_arg)
 
 
/*===========================================================================*/
/*  Buttons                                                                  */
/*===========================================================================*/


/*! Make an existing hardware button available for use.
 *  The \c button_id integer identifies the hardware button to use.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_button_new(TOUCH_SERVICE_T *touchserv, 
              vc_button_handle_t *button_handle,
              vc_button_id_t button_id,
              vc_key_name_t key_name);

/*! Set the repeat rate for all key buttons (not touch or IR buttons)
 *  Setting a repeat period of zero will disable key repeats
 *  The previous repeat rate will be returned if out_old_repeat_rate_ms
 *  is non-NULL.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_buttons_repeat_rate(TOUCH_SERVICE_T *touchserv,
                       uint32_t repeat_rate_in_ms,
                       uint32_t *out_old_repeat_rate_ms);

/*! Create a new soft button operated via Infra Red and name it
 *  with the \c button_id integer.
 *  This name will be returned by the server in order to identify the new
 *  button.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_ir_button_new(TOUCH_SERVICE_T *touchserv, 
                 vc_button_handle_t *button_handle,
                 vc_button_id_t button_id /* other IR arguments? */);
  
/*! Create a new soft button defined by the given coordinates and name it
 *  with the \c button_id integer.
 *  This name will be returned by the server in order to identify the new
 *  button.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_touch_button_new(TOUCH_SERVICE_T *touchserv, 
                    vc_button_handle_t *button_handle,
                    vc_button_id_t button_id,
                    vc_touch_button_type_t kind,
                    int left_x, int bottom_y,
                    int width, int height);

/*! Remove a button from further use
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_button_delete(TOUCH_SERVICE_T *touchserv, 
                 vc_button_handle_t button_handle);

/*! Retrieve the state of all the buttons so far defined
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_buttons_get_state(TOUCH_SERVICE_T *touchserv, 
                     vc_button_state_t *out_state);
 
/*! Begin generating events from the buttons at a rate no greater than
 *  once every \c period_ms.  The events result in the callback of the \c event
 *  function which is supplied with \c open_arg.
 *  A new event will be generated whenever button state changes.
 *  Note that the context in which \c event is called may not be suitable for
 *  sustained processing operations.
 */
VCHPRE_ int /*rc*/ VCHPOST_
vc_buttons_events_open(TOUCH_SERVICE_T *touchserv, int period_ms,
                       vc_button_event_fn_t *event, void *open_arg);


/*! Stop generating events using the given function and argument */
#define vc_button_events_close(touchserv,  event_fn, open_arg)       \
   vc_button_events_open(touchserv, /*ms*/0, event_fn, open_arg)
  


#endif /* _VC_VCHI_TOUCH_H */
