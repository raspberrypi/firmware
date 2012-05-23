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
* Display manager service API.
*/

#ifndef _VC_DISPMANX_H_
#define _VC_DISPMANX_H_

#include "interface/vcos/vcos.h"
#include "interface/vctypes/vc_image_types.h"
#include "vc_dispservice_x_defs.h"
#include "interface/vmcs_host/vc_dispmanx_types.h"
#include "interface/vchi/vchi.h"

#ifdef __cplusplus
extern "C" {
#endif
// Same function as above, to aid migration of code.
VCHPRE_ int VCHPOST_ vc_dispman_init( void );
// Stop the service from being used
VCHPRE_ void VCHPOST_ vc_dispmanx_stop( void );
// Set the entries in the rect structure
VCHPRE_ int VCHPOST_ vc_dispmanx_rect_set( VC_RECT_T *rect, uint32_t x_offset, uint32_t y_offset, uint32_t width, uint32_t height );
// Resources
// Create a new resource
VCHPRE_ DISPMANX_RESOURCE_HANDLE_T VCHPOST_ vc_dispmanx_resource_create( VC_IMAGE_TYPE_T type, uint32_t width, uint32_t height, uint32_t *native_image_handle );
// Write the bitmap data to VideoCore memory
VCHPRE_ int VCHPOST_ vc_dispmanx_resource_write_data( DISPMANX_RESOURCE_HANDLE_T res, VC_IMAGE_TYPE_T src_type, int src_pitch, void * src_address, const VC_RECT_T * rect );
VCHPRE_ int VCHPOST_ vc_dispmanx_resource_write_data_handle( DISPMANX_RESOURCE_HANDLE_T res, VC_IMAGE_TYPE_T src_type, int src_pitch, VCHI_MEM_HANDLE_T handle, uint32_t offset, const VC_RECT_T * rect );
VCHPRE_ int VCHPOST_ vc_dispmanx_resource_read_data(
                              DISPMANX_RESOURCE_HANDLE_T handle,
                              const VC_RECT_T* p_rect,
                              void *   dst_address,
                              uint32_t dst_pitch );
// Delete a resource
VCHPRE_ int VCHPOST_ vc_dispmanx_resource_delete( DISPMANX_RESOURCE_HANDLE_T res );

// Displays
// Opens a display on the given device
VCHPRE_ DISPMANX_DISPLAY_HANDLE_T VCHPOST_ vc_dispmanx_display_open( uint32_t device );
// Opens a display on the given device in the request mode
VCHPRE_ DISPMANX_DISPLAY_HANDLE_T VCHPOST_ vc_dispmanx_display_open_mode( uint32_t device, uint32_t mode );
// Open an offscreen display
VCHPRE_ DISPMANX_DISPLAY_HANDLE_T VCHPOST_ vc_dispmanx_display_open_offscreen( DISPMANX_RESOURCE_HANDLE_T dest, VC_IMAGE_TRANSFORM_T orientation );
// Change the mode of a display
VCHPRE_ int VCHPOST_ vc_dispmanx_display_reconfigure( DISPMANX_DISPLAY_HANDLE_T display, uint32_t mode );
// Sets the desstination of the display to be the given resource
VCHPRE_ int VCHPOST_ vc_dispmanx_display_set_destination( DISPMANX_DISPLAY_HANDLE_T display, DISPMANX_RESOURCE_HANDLE_T dest );
// Set the background colour of the display
VCHPRE_ int VCHPOST_ vc_dispmanx_display_set_background( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_DISPLAY_HANDLE_T display,
                                                                       uint8_t red, uint8_t green, uint8_t blue );
// get the width, height, frame rate and aspect ratio of the display
VCHPRE_ int VCHPOST_ vc_dispmanx_display_get_info( DISPMANX_DISPLAY_HANDLE_T display, DISPMANX_MODEINFO_T * pinfo );
// Closes a display
VCHPRE_ int VCHPOST_ vc_dispmanx_display_close( DISPMANX_DISPLAY_HANDLE_T display );

// Updates
// Start a new update, DISPMANX_NO_HANDLE on error
VCHPRE_ DISPMANX_UPDATE_HANDLE_T VCHPOST_ vc_dispmanx_update_start( int32_t priority );
// Add an elment to a display as part of an update
VCHPRE_ DISPMANX_ELEMENT_HANDLE_T VCHPOST_ vc_dispmanx_element_add ( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_DISPLAY_HANDLE_T display,
                                                                     int32_t layer, const VC_RECT_T *dest_rect, DISPMANX_RESOURCE_HANDLE_T src,
                                                                     const VC_RECT_T *src_rect, DISPMANX_PROTECTION_T protection, 
                                                                     VC_DISPMANX_ALPHA_T *alpha,
                                                                     DISPMANX_CLAMP_T *clamp, DISPMANX_TRANSFORM_T transform );
// Change the source image of a display element
VCHPRE_ int VCHPOST_ vc_dispmanx_element_change_source( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element,
                                                        DISPMANX_RESOURCE_HANDLE_T src );
// Change the layer number of a display element
VCHPRE_ int VCHPOST_ vc_dispmanx_element_change_layer ( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element,
                                                        int32_t layer );
// Signal that a region of the bitmap has been modified
VCHPRE_ int VCHPOST_ vc_dispmanx_element_modified( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element, const VC_RECT_T * rect );
// Remove a display element from its display
VCHPRE_ int VCHPOST_ vc_dispmanx_element_remove( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element );
// Ends an update
VCHPRE_ int VCHPOST_ vc_dispmanx_update_submit( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_CALLBACK_FUNC_T cb_func, void *cb_arg );
// End an update and wait for it to complete
VCHPRE_ int VCHPOST_ vc_dispmanx_update_submit_sync( DISPMANX_UPDATE_HANDLE_T update );
// Query the image formats supported in the VMCS build
VCHPRE_ int VCHPOST_ vc_dispmanx_query_image_formats( uint32_t *supported_formats );

//New function added to VCHI to change attributes, set_opacity does not work there.
VCHPRE_ int VCHPOST_ vc_dispmanx_element_change_attributes( DISPMANX_UPDATE_HANDLE_T update, 
                                                            DISPMANX_ELEMENT_HANDLE_T element,
                                                            uint32_t change_flags,
                                                            int32_t layer,
                                                            uint8_t opacity,
                                                            const VC_RECT_T *dest_rect,
                                                            const VC_RECT_T *src_rect,
                                                            DISPMANX_RESOURCE_HANDLE_T mask,
                                                            VC_IMAGE_TRANSFORM_T transform );

//xxx hack to get the image pointer from a resource handle, will be obsolete real soon
VCHPRE_ uint32_t VCHPOST_ vc_dispmanx_resource_get_image_handle( DISPMANX_RESOURCE_HANDLE_T res);

//Call this instead of vc_dispman_init
VCHPRE_ void VCHPOST_ vc_vchi_dispmanx_init (VCHI_INSTANCE_T initialise_instance, VCHI_CONNECTION_T **connections, uint32_t num_connections );

// Take a snapshot of a display in its current state.
// This call may block for a time; when it completes, the snapshot is ready.
VCHPRE_ int VCHPOST_ vc_dispmanx_snapshot( DISPMANX_DISPLAY_HANDLE_T display, 
                                           DISPMANX_RESOURCE_HANDLE_T snapshot_resource, 
                                           VC_IMAGE_TRANSFORM_T transform );
#ifdef __cplusplus
}
#endif

#endif // _VC_DISPMANX_H_
