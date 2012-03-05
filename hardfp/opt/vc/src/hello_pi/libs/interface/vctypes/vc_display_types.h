/*=============================================================================
Copyright (c) 2006 Broadcom Europe Limited.
Copyright (c) 2005 Alphamosaic Limited.
All rights reserved.

Project  :  VideoCore
Module   :  VideoCore specific header (vc_image_types)

FILE DESCRIPTION
Common image types used by the vc_image library.
=============================================================================*/

#ifndef INTERFACE_VC_DISPLAY_TYPES_H
#define INTERFACE_VC_DISPLAY_TYPES_H

//enums of display input format
typedef enum
{
   VCOS_DISPLAY_INPUT_FORMAT_INVALID = 0,
   VCOS_DISPLAY_INPUT_FORMAT_RGB888,
   VCOS_DISPLAY_INPUT_FORMAT_RGB565
}
VCOS_DISPLAY_INPUT_FORMAT_T;

/** For backward compatibility */
#define DISPLAY_INPUT_FORMAT_INVALID VCOS_DISPLAY_INPUT_FORMAT_INVALID
#define DISPLAY_INPUT_FORMAT_RGB888  VCOS_DISPLAY_INPUT_FORMAT_RGB888
#define DISPLAY_INPUT_FORMAT_RGB565  VCOS_DISPLAY_INPUT_FORMAT_RGB565
typedef VCOS_DISPLAY_INPUT_FORMAT_T DISPLAY_INPUT_FORMAT_T;

// Enum determining how image data for 3D displays has to be supplied
typedef enum
{
   DISPLAY_3D_UNSUPPORTED = 0,   // default
   DISPLAY_3D_INTERLEAVED,       // For autosteroscopic displays
   DISPLAY_3D_SBS_FULL_AUTO,     // Side-By-Side, Full Width (also used by some autostereoscopic displays)
   DISPLAY_3D_SBS_HALF_HORIZ,    // Side-By-Side, Half Width, Horizontal Subsampling (see HDMI spec)
   DISPLAY_3D_FORMAT_MAX
} DISPLAY_3D_FORMAT_T;

#endif /* __VC_INCLUDE_IMAGE_TYPES_H__ */


