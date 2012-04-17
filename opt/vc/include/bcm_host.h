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
 * Header file with useful bits from other headers
 */

#ifndef BCM_HOST_H
#define BCM_HOST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VCHPOST_
#define VCHPOST_
#endif
#ifndef VCHPRE_
#define VCHPRE_  extern
#endif

void bcm_host_init(void);
void bcm_host_deinit(void);

typedef struct tag_VC_RECT_T {
   int32_t x;
   int32_t y;
   int32_t width;
   int32_t height;
} VC_RECT_T;

/* Opaque handles */
typedef uint32_t DISPMANX_DISPLAY_HANDLE_T;
typedef uint32_t DISPMANX_UPDATE_HANDLE_T;
typedef uint32_t DISPMANX_ELEMENT_HANDLE_T;
typedef uint32_t DISPMANX_RESOURCE_HANDLE_T;

typedef uint32_t DISPMANX_PROTECTION_T;

#define DISPMANX_PROTECTION_MAX   0x0f
#define DISPMANX_PROTECTION_NONE  0
#define DISPMANX_PROTECTION_HDCP  11

#define DISPMANX_NO_HANDLE 0

/* Default display IDs.
   Note: if you overwrite with you own dispmanx_platfrom_init function, you
   should use IDs you provided during dispmanx_display_attach.
*/
#define DISPMANX_ID_MAIN_LCD  0
#define DISPMANX_ID_AUX_LCD   1
#define DISPMANX_ID_HDMI      2
#define DISPMANX_ID_SDTV      3


/* Return codes. Nonzero ones indicate failure. */
typedef enum {
  DISPMANX_SUCCESS      = 0,
  DISPMANX_INVALID      = -1
  /* XXX others TBA */
} DISPMANX_STATUS_T;

typedef enum {
  /* Bottom 2 bits sets the orientation */
  DISPMANX_NO_ROTATE = 0,
  DISPMANX_ROTATE_90 = 1,
  DISPMANX_ROTATE_180 = 2,
  DISPMANX_ROTATE_270 = 3,

  DISPMANX_FLIP_HRIZ = 1 << 16,
  DISPMANX_FLIP_VERT = 1 << 17
} DISPMANX_TRANSFORM_T;

typedef enum {
  /* Bottom 2 bits sets the alpha mode */
  DISPMANX_FLAGS_ALPHA_FROM_SOURCE = 0,
  DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS = 1,
  DISPMANX_FLAGS_ALPHA_FIXED_NON_ZERO = 2,
  DISPMANX_FLAGS_ALPHA_FIXED_EXCEED_0X07 = 3,

  DISPMANX_FLAGS_ALPHA_PREMULT = 1 << 16,
  DISPMANX_FLAGS_ALPHA_MIX = 1 << 17
} DISPMANX_FLAGS_ALPHA_T;

typedef struct {
  DISPMANX_FLAGS_ALPHA_T flags;
  uint32_t opacity;
  struct VC_IMAGE_T *mask;
} DISPMANX_ALPHA_T;

typedef struct {
  DISPMANX_FLAGS_ALPHA_T flags;
  uint32_t opacity;
  DISPMANX_RESOURCE_HANDLE_T mask;
} VC_DISPMANX_ALPHA_T;  /* for use with vmcs_host */

typedef enum {
  DISPMANX_FLAGS_CLAMP_NONE = 0,
  DISPMANX_FLAGS_CLAMP_LUMA_TRANSPARENT = 1,
  DISPMANX_FLAGS_CLAMP_TRANSPARENT = 2,
  DISPMANX_FLAGS_CLAMP_REPLACE = 3
} DISPMANX_FLAGS_CLAMP_T;

typedef enum {
  DISPMANX_FLAGS_KEYMASK_OVERRIDE = 1,
  DISPMANX_FLAGS_KEYMASK_SMOOTH = 1 << 1,
  DISPMANX_FLAGS_KEYMASK_CR_INV = 1 << 2,
  DISPMANX_FLAGS_KEYMASK_CB_INV = 1 << 3,
  DISPMANX_FLAGS_KEYMASK_YY_INV = 1 << 4
} DISPMANX_FLAGS_KEYMASK_T;

typedef union {
  struct {
    uint8_t yy_upper;
    uint8_t yy_lower;
    uint8_t cr_upper;
    uint8_t cr_lower;
    uint8_t cb_upper;
    uint8_t cb_lower;
  } yuv;
  struct {
    uint8_t red_upper;
    uint8_t red_lower;
    uint8_t blue_upper;
    uint8_t blue_lower;
    uint8_t green_upper;
    uint8_t green_lower;
  } rgb;
} DISPMANX_CLAMP_KEYS_T;

typedef struct {
  DISPMANX_FLAGS_CLAMP_T mode;
  DISPMANX_FLAGS_KEYMASK_T key_mask;
  DISPMANX_CLAMP_KEYS_T key_value;
  uint32_t replace_value;
} DISPMANX_CLAMP_T;

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

typedef struct tag_DISPMANX_MODEINFO_T {
  int32_t width;
  int32_t height;
  VC_IMAGE_TRANSFORM_T transform;
  DISPLAY_INPUT_FORMAT_T input_format;
} DISPMANX_MODEINFO_T;

typedef enum {
   HDMI_MODE_OFF,  /**< Off! */
   HDMI_MODE_DVI,  /**< DVI */
   HDMI_MODE_HDMI, /**< Normal HDMI */
   HDMI_MODE_3D    /**< HDMI 1.4a 3D */
} HDMI_MODE_T;

typedef enum {
   HDMI_RES_GROUP_INVALID = 0, /**< Initialised value */
   HDMI_RES_GROUP_CEA     = 1, /**< CEA - HDMI device */
   HDMI_RES_GROUP_DMT     = 2, /**< DMT - computer monitors */
   HDMI_RES_GROUP_CEA_3D  = 3  /**< CEA 3D mode (for 3D displays only) */
} HDMI_RES_GROUP_T;

typedef enum {
   HDMI_MODE_MATCH_NONE          = 0x0, /**<No mode*/
   HDMI_MODE_MATCH_FRAMERATE     = 0x1, /**<Match based on frame rate */
   HDMI_MODE_MATCH_RESOLUTION    = 0x2, /**<Match based on resolution */
   HDMI_MODE_MATCH_SCANMODE      = 0x4  /**<Match based on scan mode */
} EDID_MODE_MATCH_FLAG_T;

typedef enum {
   HDMI_NONINTERLACED,
   HDMI_INTERLACED
} HDMI_INTERLACED_T;

/**
 * These are CEA mode numbers (sent in AVI infoframe) for different resolutions as define in CEA-861
 * 1080i at 100/120Hz (40,46) are supported by HDMI H/W but note we cannot 
 * display the debug overlay under these modes. 
 * Some modes have two codes, the first one has aspect ratio 4:3 and 
 * the second one (with "H" suffix") 16:9.
 * The modes with "4x", etc. are the same the corresponding "non-multiplied" modes 
 * but clocked at a higher pixel clock.
 */
typedef enum {
   HDMI_CEA_VGA             =  1,
   HDMI_CEA_480p60          =  2,
   HDMI_CEA_480p60H         =  3,
   HDMI_CEA_720p60          =  4,
   HDMI_CEA_1080i60         =  5,
   HDMI_CEA_480i60          =  6,
   HDMI_CEA_480i60H         =  7,
   HDMI_CEA_240p60          =  8,
   HDMI_CEA_240p60H         =  9,
   HDMI_CEA_480i60_4x       = 10,
   HDMI_CEA_480i60_4xH      = 11,
   HDMI_CEA_240p60_4x       = 12,
   HDMI_CEA_240p60_4xH      = 13,
   HDMI_CEA_480p60_2x       = 14,
   HDMI_CEA_480p60_2xH      = 15,
   HDMI_CEA_1080p60         = 16,
   HDMI_CEA_576p50          = 17,
   HDMI_CEA_576p50H         = 18,
   HDMI_CEA_720p50          = 19,
   HDMI_CEA_1080i50         = 20,
   HDMI_CEA_576i50          = 21,
   HDMI_CEA_576i50H         = 22,
   HDMI_CEA_288p50          = 23,
   HDMI_CEA_288p50H         = 24,
   HDMI_CEA_576i50_4x       = 25,
   HDMI_CEA_576i50_4xH      = 26,
   HDMI_CEA_288p50_4x       = 27,
   HDMI_CEA_288p50_4xH      = 28,
   HDMI_CEA_576p50_2x       = 29,
   HDMI_CEA_576p50_2xH      = 30,
   HDMI_CEA_1080p50         = 31,
   HDMI_CEA_1080p24         = 32,
   HDMI_CEA_1080p25         = 33,
   HDMI_CEA_1080p30         = 34,
   HDMI_CEA_480p60_4x       = 35,
   HDMI_CEA_480p60_4xH      = 36,
   HDMI_CEA_576p50_4x       = 37,
   HDMI_CEA_576p50_4xH      = 38,
   HDMI_CEA_1080i50_rb      = 39,
   HDMI_CEA_1080i100        = 40, 
   HDMI_CEA_720p100         = 41,
   HDMI_CEA_576p100         = 42,
   HDMI_CEA_576p100H        = 43,
   HDMI_CEA_576i100         = 44,
   HDMI_CEA_576i100H        = 45,
   HDMI_CEA_1080i120        = 46,
   HDMI_CEA_720p120         = 47,
   HDMI_CEA_480p120         = 48,
   HDMI_CEA_480p120H        = 49,
   HDMI_CEA_480i120         = 50,
   HDMI_CEA_480i120H        = 51,
   HDMI_CEA_576p200         = 52,
   HDMI_CEA_576p200H        = 53,
   HDMI_CEA_576i200         = 54,
   HDMI_CEA_576i200H        = 55,
   HDMI_CEA_480p240         = 56,
   HDMI_CEA_480p240H        = 57,
   HDMI_CEA_480i240         = 58,
   HDMI_CEA_480i240H        = 59,
   //Put more CEA codes here if we support in the future

   HDMI_CEA_OFF = 0xff /**<Special code to shutdown HDMI */

} HDMI_CEA_RES_CODE_T;

/**
 * These are the DMT modes from VESA. They are used for powering up
 * HDMI in DMT resolutions and are not sent in AVI infoframes.
 * Enum is ordered as ascending order of DMT id. 
 * All reduced blanking formats are 60Hz unless stated otherwise. 
 */
typedef enum {
   HDMI_DMT_640x350_85      = 0x1,  /**<640x350 */
   HDMI_DMT_640x400_85      = 0x2,  /**<640x400 */
   HDMI_DMT_IBM_VGA_85      = 0x3,  /**<720x400 */
   HDMI_DMT_VGA_60          = 0x4,  /**<640x480 (60Hz is same as VGA above) */
   HDMI_DMT_VGA_72          = 0x5,
   HDMI_DMT_VGA_75          = 0x6,
   HDMI_DMT_VGA_85          = 0x7,
   HDMI_DMT_SVGA_56         = 0x8,  /**<800x600 */
   HDMI_DMT_SVGA_60         = 0x9,
   HDMI_DMT_SVGA_72         = 0xA,
   HDMI_DMT_SVGA_75         = 0xB,
   HDMI_DMT_SVGA_85         = 0xC,
   HDMI_DMT_SVGA_120        = 0xD,
   HDMI_DMT_848x480_60      = 0xE,  /**<848x480 */
   HDMI_DMT_XGA_60          = 0x10, /**<1024x768 */
   HDMI_DMT_XGA_70          = 0x11,
   HDMI_DMT_XGA_75          = 0x12,
   HDMI_DMT_XGA_85          = 0x13,
   HDMI_DMT_XGA_120         = 0x14,
   HDMI_DMT_XGAP_75         = 0x15, /**<1152x864 */
   HDMI_DMT_WXGA_RB         = 0x16, /**<1280x768 reduced blanking */
   HDMI_DMT_WXGA_60         = 0x17, 
   HDMI_DMT_WXGA_75         = 0x18, 
   HDMI_DMT_WXGA_85         = 0x19, 
   HDMI_DMT_WXGA_120        = 0x1A, /**<120Hz with reduced blanking */
   HDMI_DMT_1280x800_RB     = 0x1B, /**<1280x800 reduced blanking */
   HDMI_DMT_1280x800_60     = 0x1C, 
   HDMI_DMT_1280x960_60     = 0x20, /**<1280x960 */
   HDMI_DMT_1280x960_85     = 0x21,
   HDMI_DMT_SXGA_60         = 0x23, /**<1280x1024 */
   HDMI_DMT_SXGA_75         = 0x24, 
   HDMI_DMT_SXGA_85         = 0x25,
   HDMI_DMT_1360x768_60     = 0x27, /**<1360x768 */
   HDMI_DMT_1360x768_120    = 0x28, /**<120 Hz with reduced blanking */
   HDMI_DMT_SXGAP_RB        = 0x29, /**<1400x1050 reduced blanking */
   HDMI_DMT_SXGAP_60        = 0x2A, 
   HDMI_DMT_SXGAP_75        = 0x2B,
   HDMI_DMT_1440x900_RB     = 0x2E, /**<1440x900 reduced blanking */
   HDMI_DMT_1440x900_60     = 0x2F,
   HDMI_DMT_1440x900_75     = 0x30,  
   HDMI_DMT_1440x900_85     = 0x31, 
   HDMI_DMT_UXGA_60         = 0x33, /**<1600x1200 60Hz */
   HDMI_DMT_SWXGAP_RB       = 0x39, /**<1680x1050 reduced blanking */
   HDMI_DMT_SWXGAP_60       = 0x3A, /**<1680x1050 60Hz */
   HDMI_DMT_WUXGA_RB        = 0x44, /**<1920x1200 reduced blanking */
   HDMI_DMT_1366x768_60     = 0x51, /**<1366x768 60Hz */
   HDMI_DMT_1080p_60        = 0x52, /**<Same as 1080p60 above */
   HDMI_DMT_1600x900_RB     = 0x53, /**<1600x900 reduced blanking */
   HDMI_DMT_720p_60         = 0x55, /**<Same as 720p60 above */
   HDMI_DMT_1366x768_RB     = 0x56, /**<1366x768 reduced blanking */
   //Put more DMT codes here if we support in the future

   HDMI_DMT_OFF = 0xff
} HDMI_DMT_RES_CODE_T;

VCHPRE_ DISPMANX_DISPLAY_HANDLE_T VCHPOST_ vc_dispmanx_display_open( uint32_t device );
VCHPRE_ DISPMANX_UPDATE_HANDLE_T VCHPOST_ vc_dispmanx_update_start( int32_t priority );
VCHPRE_ DISPMANX_ELEMENT_HANDLE_T VCHPOST_ vc_dispmanx_element_add ( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_DISPLAY_HANDLE_T display,
                                                                     int32_t layer, const VC_RECT_T *dest_rect, DISPMANX_RESOURCE_HANDLE_T src,
                                                                     const VC_RECT_T *src_rect, DISPMANX_PROTECTION_T protection, 
                                                                     VC_DISPMANX_ALPHA_T *alpha,
                                                                     DISPMANX_CLAMP_T *clamp, DISPMANX_TRANSFORM_T transform );
VCHPRE_ int VCHPOST_ vc_dispmanx_update_submit_sync( DISPMANX_UPDATE_HANDLE_T update );
VCHPRE_ int VCHPOST_ vc_dispmanx_element_remove( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element );
VCHPRE_ int VCHPOST_ vc_dispmanx_display_close( DISPMANX_DISPLAY_HANDLE_T display );

VCHPRE_ int32_t VCHPOST_ graphics_get_display_size( const uint16_t display_number,
                                                    uint32_t *width,
                                                    uint32_t *height);
VCHPRE_ int VCHPOST_ vc_dispmanx_display_get_info( DISPMANX_DISPLAY_HANDLE_T display, DISPMANX_MODEINFO_T * pinfo );

VCHPRE_ int VCHPOST_ vc_dispmanx_display_set_background( DISPMANX_UPDATE_HANDLE_T update, DISPMANX_DISPLAY_HANDLE_T display,
                                                                       uint8_t red, uint8_t green, uint8_t blue );

VCHPRE_ int VCHPOST_ vc_tv_hdmi_power_on_best(uint32_t width, uint32_t height, uint32_t frame_rate,
                                             HDMI_INTERLACED_T scan_mode, EDID_MODE_MATCH_FLAG_T match_flags);

VCHPRE_ int VCHPOST_ vc_tv_hdmi_power_on_best_3d(uint32_t width, uint32_t height, uint32_t frame_rate,
                                             HDMI_INTERLACED_T scan_mode, EDID_MODE_MATCH_FLAG_T match_flags);

typedef struct {
  uint32_t state;     /**<TV state is a union of bitmask of
VC_HDMI_NOTIFY_T and VC_SDTV_NOTIFY_T */
  uint32_t width;     /**<Current display width if TV is on */
  uint32_t height;    /**<Current display height if TV is on */
  uint16_t frame_rate;/**<Current refresh rate is TV is on */
  uint16_t scan_mode; /**<Current scanmode 0 for progressive, 1 for
interlaced */
} TV_GET_STATE_RESP_T;

VCHPRE_ int VCHPOST_ vc_tv_get_state(TV_GET_STATE_RESP_T *tvstate);

typedef enum {
  VC_HDMI_UNPLUGGED          = (1 << 0),  /**<HDMI cable is detached */
  VC_HDMI_STANDBY            = (1 << 1),  /**<HDMI cable is attached but not powered on */
  VC_HDMI_DVI                = (1 << 2),  /**<HDMI is on but in DVI mode (no audio) */
  VC_HDMI_HDMI               = (1 << 3),  /**<HDMI is on and HDMI mode is active */
  VC_HDMI_HDCP_UNAUTH        = (1 << 4),  /**<HDCP authentication is broken (e.g. Ri mismatched) or not active */
  VC_HDMI_HDCP_AUTH          = (1 << 5),  /**<HDCP is active */
  VC_HDMI_HDCP_KEY_DOWNLOAD  = (1 << 6),  /**<HDCP key download successful/fail */
  VC_HDMI_HDCP_SRM_DOWNLOAD  = (1 << 7),  /**<HDCP revocation list download successful/fail */
  VC_HDMI_CHANGING_MODE      = (1 << 8),  /**<HDMI is starting to change mode, clock has not yet been set */
  VC_HDMI_HDMI_3D            = (1 << 15), /**<3D mode is active */
} VC_HDMI_NOTIFY_T;

typedef enum
{
  VC_SDTV_UNPLUGGED          = 1 << 16, /**<SDTV cable unplugged,
subject to platform support */
  VC_SDTV_STANDBY            = 1 << 17, /**<SDTV cable is plugged in */
  VC_SDTV_NTSC               = 1 << 18, /**<SDTV is in NTSC mode */
  VC_SDTV_PAL                = 1 << 19, /**<SDTV is in PAL mode */
  VC_SDTV_CP_INACTIVE        = 1 << 20, /**<Copy protection disabled */
  VC_SDTV_CP_ACTIVE          = 1 << 21  /**<Copy protection enabled */
} VC_SDTV_NOTIFY_T;

VCHPRE_ int VCHPOST_ vc_tv_show_info(uint32_t show);

VCHPRE_ int VCHPOST_ vc_tv_hdmi_get_av_latency( void );

//TV service commands
typedef enum {
   VC_TV_GET_STATE = 0,
   VC_TV_HDMI_ON_PREFERRED,
   VC_TV_HDMI_ON_BEST,
   VC_TV_HDMI_ON_EXPLICIT,
   VC_TV_SDTV_ON,
   VC_TV_OFF,
   VC_TV_QUERY_SUPPORTED_MODES,
   VC_TV_QUERY_MODE_SUPPORT,
   VC_TV_QUERY_AUDIO_SUPPORT,
   VC_TV_ENABLE_COPY_PROTECT,
   VC_TV_DISABLE_COPY_PROTECT,
   VC_TV_SHOW_INFO,
   VC_TV_GET_AV_LATENCY,
   VC_TV_HDCP_SET_KEY,
   VC_TV_HDCP_SET_SRM,
   VC_TV_SET_SPD,
   VC_TV_SET_DISPLAY_OPTIONS,
   VC_TV_TEST_MODE_START,
   VC_TV_TEST_MODE_STOP,
   VC_TV_DDC_READ,
   //Add more commands here 
   VC_TV_END_OF_LIST
} VC_TV_CMD_CODE_T;

typedef struct {
   uint16_t scan_mode : 1; /**<1 is interlaced, 0 for progressive */
   uint16_t native    : 1; /**<1 means native mode, 0 otherwise */
   uint16_t code      : 7; /**<mode code */
   uint16_t frame_rate;    /**<frame rate */
   uint16_t width;         /**<frame width */
   uint16_t height;        /**<frame height */
} TV_SUPPORTED_MODE_T;

VCHPRE_ int VCHPOST_ vc_tv_hdmi_get_supported_modes(HDMI_RES_GROUP_T group,
                                                    TV_SUPPORTED_MODE_T *supported_modes,
                                                    uint32_t max_supported_modes,
                                                    HDMI_RES_GROUP_T *preferred_group,
                                                    uint32_t *preferred_mode);

VCHPRE_ int VCHPOST_ vc_tv_hdmi_power_on_explicit(HDMI_MODE_T mode, HDMI_RES_GROUP_T group, uint32_t code);

VCHPRE_ int VCHPOST_ vc_tv_power_off( void );

typedef void (*TVSERVICE_CALLBACK_T)(void *callback_data, uint32_t reason, uint32_t param1, uint32_t param2);
VCHPRE_ void VCHPOST_ vc_tv_register_callback(TVSERVICE_CALLBACK_T callback, void *callback_data);
VCHPRE_ void vc_tv_unregister_callback(TVSERVICE_CALLBACK_T callback);

typedef int bool_t;

/**
 * Button code for <User Control Pressed>
 */
typedef enum {
   CEC_User_Control_Select                      = 0x00,
   CEC_User_Control_Up                          = 0x01,
   CEC_User_Control_Down                        = 0x02,
   CEC_User_Control_Left                        = 0x03,
   CEC_User_Control_Right                       = 0x04,
   CEC_User_Control_RightUp                     = 0x05,
   CEC_User_Control_RightDown                   = 0x06,
   CEC_User_Control_LeftUp                      = 0x07,
   CEC_User_Control_LeftDown                    = 0x08,
   CEC_User_Control_RootMenu                    = 0x09,
   CEC_User_Control_SetupMenu                   = 0x0A,
   CEC_User_Control_ContentsMenu                = 0x0B,
   CEC_User_Control_FavoriteMenu                = 0x0C,
   CEC_User_Control_Exit                        = 0x0D,
   CEC_User_Control_Number0                     = 0x20,
   CEC_User_Control_Number1                     = 0x21,
   CEC_User_Control_Number2                     = 0x22,
   CEC_User_Control_Number3                     = 0x23,
   CEC_User_Control_Number4                     = 0x24,
   CEC_User_Control_Number5                     = 0x25,
   CEC_User_Control_Number6                     = 0x26,
   CEC_User_Control_Number7                     = 0x27,
   CEC_User_Control_Number8                     = 0x28,
   CEC_User_Control_Number9                     = 0x29,
   CEC_User_Control_Dot                         = 0x2A,
   CEC_User_Control_Enter                       = 0x2B,
   CEC_User_Control_Clear                       = 0x2C,
   CEC_User_Control_ChannelUp                   = 0x30,
   CEC_User_Control_ChannelDown                 = 0x31,
   CEC_User_Control_PreviousChannel             = 0x32,
   CEC_User_Control_SoundSelect                 = 0x33,
   CEC_User_Control_InputSelect                 = 0x34,
   CEC_User_Control_DisplayInformation          = 0x35,
   CEC_User_Control_Help                        = 0x36,
   CEC_User_Control_PageUp                      = 0x37,
   CEC_User_Control_PageDown                    = 0x38,
   CEC_User_Control_Power                       = 0x40,
   CEC_User_Control_VolumeUp                    = 0x41,
   CEC_User_Control_VolumeDown                  = 0x42,
   CEC_User_Control_Mute                        = 0x43,
   CEC_User_Control_Play                        = 0x44,
   CEC_User_Control_Stop                        = 0x45,
   CEC_User_Control_Pause                       = 0x46,
   CEC_User_Control_Record                      = 0x47,
   CEC_User_Control_Rewind                      = 0x48,
   CEC_User_Control_FastForward                 = 0x49,
   CEC_User_Control_Eject                       = 0x4A,
   CEC_User_Control_Forward                     = 0x4B,
   CEC_User_Control_Backward                    = 0x4C,
   CEC_User_Control_Angle                       = 0x50,
   CEC_User_Control_Subpicture                  = 0x51,
   CEC_User_Control_VideoOnDemand               = 0x52,
   CEC_User_Control_EPG                         = 0x53,
   CEC_User_Control_TimerProgramming            = 0x54,
   CEC_User_Control_InitialConfig               = 0x55,
   CEC_User_Control_PlayFunction                = 0x60,
   CEC_User_Control_PausePlayFunction           = 0x61,
   CEC_User_Control_RecordFunction              = 0x62,
   CEC_User_Control_PauseRecordFunction         = 0x63,
   CEC_User_Control_StopFunction                = 0x64,
   CEC_User_Control_MuteFunction                = 0x65,
   CEC_User_Control_RestoreVolumeFunction       = 0x66,
   CEC_User_Control_TuneFunction                = 0x67,
   CEC_User_Control_SelectDiskFunction          = 0x68,
   CEC_User_Control_SelectAVInputFunction       = 0x69,
   CEC_User_Control_SelectAudioInputFunction    = 0x6A,
   CEC_User_Control_F1Blue                      = 0x71,
   CEC_User_Control_F2Red                       = 0x72,
   CEC_User_Control_F3Green                     = 0x73,
   CEC_User_Control_F4Yellow                    = 0x74,
   CEC_User_Control_F5                          = 0x75
} CEC_USER_CONTROL_T;

/**
 * CEC related notification
 */
typedef enum {
   VC_CEC_NOTIFY_NONE     = 0,        //Reserved - NOT TO BE USED
   VC_CEC_TX              = (1 << 0), /**<A message has been transmitted */
   VC_CEC_RX              = (1 << 1), /**<A message has arrived (only for registered commands) */
   VC_CEC_BUTTON_PRESSED  = (1 << 2), /**<<User Control Pressed> */
   VC_CEC_BUTTON_RELEASE  = (1 << 3), /**<<User Control Release> */
   VC_CEC_REMOTE_PRESSED  = (1 << 4), /**<<Vendor Remote Button Down> */
   VC_CEC_REMOTE_RELEASE  = (1 << 5), /**<<Vendor Remote Button Up> */
   VC_CEC_LOGICAL_ADDR    = (1 << 6), /**<New logical address allocated or released */
   VC_CEC_TOPOLOGY        = (1 << 7), /**<Topology is available */
   VC_CEC_RX_LONG         = (1 << 8)  /**<A long message has arrived (only for registered commands) */
} VC_CEC_NOTIFY_T;


/**
 * \file
 * This API defines the controls for CEC. HDMI must be powered on before
 * CEC is available (subject to CEC support in TV). 
 *
 */
/**
 * Generic CEC opcode
 */
typedef enum {
   CEC_Opcode_FeatureAbort 	            = 0x00,
   CEC_Opcode_ImageViewOn 	            = 0x04,
   CEC_Opcode_TunerStepIncrement    	    = 0x05,
   CEC_Opcode_TunerStepDecrement    	    = 0x06,
   CEC_Opcode_TunerDeviceStatus 	    = 0x07,
   CEC_Opcode_GiveTunerDeviceStatus 	    = 0x08,
   CEC_Opcode_RecordOn 	                    = 0x09,
   CEC_Opcode_RecordStatus 	            = 0x0A,
   CEC_Opcode_RecordOff 	            = 0x0B,
   CEC_Opcode_TextViewOn 	            = 0x0D,
   CEC_Opcode_RecordTVScreen                = 0x0F,
   CEC_Opcode_GiveDeckStatus        	    = 0x1A,
   CEC_Opcode_DeckStatus 	            = 0x1B,
   CEC_Opcode_SetMenuLanguage               = 0x32,
   CEC_Opcode_ClearAnalogTimer              = 0x33,
   CEC_Opcode_SetAnalogTimer                = 0x34,
   CEC_Opcode_TimerStatus                   = 0x35,
   CEC_Opcode_Standby 	                    = 0x36,
   CEC_Opcode_Play                  	    = 0x41,
   CEC_Opcode_DeckControl 	            = 0x42,
   CEC_Opcode_TimerClearedStatus            = 0x43,
   CEC_Opcode_UserControlPressed 	    = 0x44,
   CEC_Opcode_UserControlReleased 	    = 0x45,
   CEC_Opcode_GiveOSDName           	    = 0x46,
   CEC_Opcode_SetOSDName 	            = 0x47,
   CEC_Opcode_SetOSDString 	            = 0x64,
   CEC_Opcode_SetTimerProgramTitle          = 0x67,
   CEC_Opcode_SystemAudioModeRequest        = 0x70,
   CEC_Opcode_GiveAudioStatus               = 0x71,
   CEC_Opcode_SetSystemAudioMode            = 0x72,
   CEC_Opcode_ReportAudioStatus             = 0x7A,
   CEC_Opcode_GiveSystemAudioModeStatus     = 0x7D,
   CEC_Opcode_SystemAudioModeStatus         = 0x7E,
   CEC_Opcode_RoutingChange 	            = 0x80,
   CEC_Opcode_RoutingInformation 	    = 0x81,
   CEC_Opcode_ActiveSource 	            = 0x82,
   CEC_Opcode_GivePhysicalAddress           = 0x83,
   CEC_Opcode_ReportPhysicalAddress         = 0x84,
   CEC_Opcode_RequestActiveSource 	    = 0x85,
   CEC_Opcode_SetStreamPath 	            = 0x86,
   CEC_Opcode_DeviceVendorID 	            = 0x87,
   CEC_Opcode_VendorCommand         	    = 0x89,
   CEC_Opcode_VendorRemoteButtonDown 	    = 0x8A,
   CEC_Opcode_VendorRemoteButtonUp    	    = 0x8B,
   CEC_Opcode_GiveDeviceVendorID    	    = 0x8C,
   CEC_Opcode_MenuRequest 	            = 0x8D,
   CEC_Opcode_MenuStatus 	            = 0x8E,
   CEC_Opcode_GiveDevicePowerStatus 	    = 0x8F,
   CEC_Opcode_ReportPowerStatus 	    = 0x90,
   CEC_Opcode_GetMenuLanguage               = 0x91,
   CEC_Opcode_SelectAnalogService           = 0x92,
   CEC_Opcode_SelectDigitalService   	    = 0x93,
   CEC_Opcode_SetDigitalTimer               = 0x97,
   CEC_Opcode_ClearDigitalTimer             = 0x99,
   CEC_Opcode_SetAudioRate                  = 0x9A,
   CEC_Opcode_InactiveSource        	    = 0x9D,
   CEC_Opcode_CECVersion                    = 0x9E,
   CEC_Opcode_GetCECVersion                 = 0x9F,
   CEC_Opcode_VendorCommandWithID           = 0xA0,
   CEC_Opcode_ClearExternalTimer            = 0xA1,
   CEC_Opcode_SetExternalTimer              = 0xA2,
   CEC_Opcode_ReportShortAudioDescriptor    = 0xA3,
   CEC_Opcode_RequestShortAudioDescriptor   = 0xA4,
   CEC_Opcode_InitARC                       = 0xC0,
   CEC_Opcode_ReportARCInited               = 0xC1,
   CEC_Opcode_ReportARCTerminated           = 0xC2,
   CEC_Opcode_RequestARCInit                = 0xC3,
   CEC_Opcode_RequestARCTermination         = 0xC4,
   CEC_Opcode_TerminateARC                  = 0xC5,
   CEC_Opcode_CDC                           = 0xF8,
   CEC_Opcode_Abort        	            = 0xFF
} CEC_OPCODE_T;

/**
 * Reason parameter for <Feature Abort>
 */
typedef enum {
   CEC_Abort_Reason_Unrecognised_Opcode   = 0,
   CEC_Abort_Reason_Wrong_Mode            = 1,
   CEC_Abort_Reason_Cannot_Provide_Source = 2,
   CEC_Abort_Reason_Invalid_Operand       = 3,
   CEC_Abort_Reason_Refused               = 4,
   CEC_Abort_Reason_Undetermined          = 5
} CEC_ABORT_REASON_T;

/**
 * Display control parameter for <Set OSD string>
 */
typedef enum {
   CEC_DISPLAY_CONTROL_DEFAULT_TIME       = 0,
   CEC_DISPLAY_CONTROL_UNTIL_CLEARED      = (1<<6),
   CEC_DISPLAY_CONTROL_CLEAR_PREV_MSG     = (1<<7)
} CEC_DISPLAY_CONTROL_T;

/**
 * Menu state parameter for <Menu Status>
 */
typedef enum {
   CEC_MENU_STATE_ACTIVATED               = 0,
   CEC_MENU_STATE_DEACTIVATED             = 1,
   CEC_MENU_STATE_QUERY                   = 2
} CEC_MENU_STATE_T;

/**
 * These are the logical addresses for all possible attached devices
 */
typedef enum CEC_AllDevices {
   CEC_AllDevices_eTV = 0,            /**<TV only */
   CEC_AllDevices_eRecDevice1,        /**<Address for 1st Recording Device */
   CEC_AllDevices_eRecDevice2,        /**<Address for 2nd Recording Device */
   CEC_AllDevices_eSTB1,              /**<Address for 1st SetTop Box Device */
   CEC_AllDevices_eDVD1,              /**<Address for 1st DVD Device */
   CEC_AllDevices_eAudioSystem,       /**<Address for Audio Device */
   CEC_AllDevices_eSTB2,              /**<Address for 2nd SetTop Box Device */
   CEC_AllDevices_eSTB3,              /**<Address for 3rd SetTop Box Device */
   CEC_AllDevices_eDVD2,              /**<Address for 2nd DVD Device */
   CEC_AllDevices_eRecDevice3,        /**<Address for 3rd Recording Device */
   CEC_AllDevices_eSTB4,              /**<10 Address for 4th Tuner Device */
   CEC_AllDevices_eDVD3,              /**<11 Address for 3rd DVD Device */
   CEC_AllDevices_eRsvd3,             /**<Reserved and cannot be used */
   CEC_AllDevices_eRsvd4,             /**<Reserved and cannot be used */
   CEC_AllDevices_eFreeUse,           /**<Free Address, use for any device */
   CEC_AllDevices_eUnRegistered = 15  /**<UnRegistered Devices */
} CEC_AllDevices_T;

/**
 *CEC topology struct
 *
 * Meaning of device_attr is as follows (one per active logical device)
 * bit 3-0 logical address (see CEC_AllDevices_T above)
 * bit 7-4 device type (see CEC_DEVICE_TYPE_T above)
 * bit 11-8 index to upstream device
 * bit 15-12 number of downstream device
 * bit 31-16 index of first 4 downstream devices
 * 
 * To keep life simple we only show the first 4 connected downstream devices
 *
 */
typedef struct {
   uint16_t active_mask;       /**<bit n is set if logical device n is active */
   uint16_t num_devices;       /**<no. of bits set above, save us from counting */
   uint32_t device_attr[16];   /**<Device attribute, see above for explanation */
} VC_CEC_TOPOLOGY_T;


/**
 * Callback function for host side notification 
 * Host applications register a single callback for all CEC related notifications.
 * See vc_cec.h for meanings of param1 and param2
 *
 * @param callback_data is the context passed in by user in <DFN>vc_cec_register_callback</DFN>
 *
 * @param reason is VC_CEC_NOTIFY_T in vc_cec.h
 *
 * @param param1 is the first parameter
 * 
 * @param param2 is the second parameter
 * 
 * @return void
 */
typedef void (*CECSERVICE_CALLBACK_T)(void *callback_data, uint32_t reason, uint32_t param1, uint32_t param2);

/**
 * Host applications use <DFN>vc_cec_register_callaback</DFN> to register
 * callback to handle all CEC notifications. If more than one applications 
 * need to use CEC, there should be ONE central application which acts on
 * behalf of all clients and handles all communications with CEC services.
 *
 * @param callback function 
 * @param context to be passed when function is called
 * @return void
 ***********************************************************/
VCHPRE_ void vc_cec_register_callback(CECSERVICE_CALLBACK_T callback, void *callback_data);

//Service API
/**
 * Use <DFN>vc_cec_register_command</DFN> to register an opcode to
 * to forwarded to the host application. By default <Feature Abort> 
 * is always forwarded. Once an opcode is registered, it is left to
 * the host application to reply to a CEC message (where appropriate).
 * It is recommended NOT to register the following commands as they 
 * are replied to automatically by CEC middleware:
 * <Give Physical Address>, <Give Device Vendor ID>, <Give OSD Name>,
 * <Get CEC Version>, <Give Device Power Status>, <Menu Request>,
 * and <Get Menu Language>
 * In addition, the following opcodes cannot be registered:
 * <User Control Pressed>, <User Control Released>, 
 * <Vendor Remote Button Down>, <Vendor Remote Button Up>,
 * and <Abort>.
 * <Feature Abort> is always forwarded if it is the reply
 * of a command the host sent.
 *
 * @param opcode to be registered.
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_register_command(CEC_OPCODE_T opcode);

/**
 * <DFN>vc_cec_register_all</DFN> registers all opcodes except <Abort>
 *  to be forwarded as CEC_RX notification.
 * Button presses <User Control Pressed>, etc. will still be forwarded 
 * separately as VC_CEC_BUTTON_PRESSED etc. notification.
 *
 * @param None
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_register_all( void );

/**
 * Use <DFN>vc_cec_deregister_command</DFN> to remove an opcode from
 * the filter for forwarding. By default <Feature Abort> is always forwarded.
 * The following opcode cannot be deregistered:
 * <User Control Pressed>, <User Control Released>, 
 * <Vendor Remote Button Down>, <Vendor Remote Button Up>,
 * and <Abort>.
 *
 * @param opcode to be deregistered
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_deregister_command(CEC_OPCODE_T opcode);

/**
 * <DFN>vc_cec_deregister_all</DFN> removes all registered opcodes,
 * except the ones (e.g. button presses) which are always forwarded.
 *
 * @param None
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_deregister_all( void );

/**
 * <DFN>vc_cec_send_message</DFN> allows a host application to 
 * send a CEC message to another device. There are several 
 * built-in functions for sending command messages. The host
 * application MUST have a valid logical address (between 1 and
 * 14 inclusive) before it can send a message.
 * (For poll message set payload to NULL and length to zero).
 *
 * @param Follower's logical address
 *
 * @param Message payload WITHOUT the header byte (can be NULL)
 *
 * @param Payload length WITHOUT the header byte (can be zero)
 *
 * @param VC_TRUE if the message is a reply to an incoming message
 *
 * @return zero if the command is successful, non-zero otherwise
 *         If the command is successful, there will be a Tx callback
 *         in due course to indicate whether the message has been
 *         acknowledged by the recipient or not
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_message(uint32_t follower,
                                         const uint8_t *payload,
                                         uint32_t length,
                                         bool_t is_reply);

/**
 * <DFN>vc_cec_receive_message</DFN>  retrieves the most recent 
 * message. If there is no pending message, both initiator and 
 * follower will be set to 0xF, otherwise length is set to length 
 * of message minus the header byte. Call the function a second 
 * time will have the same effect. If the message is less than
 * 7 bytes (including header), the entire message will appear in
 * RX callback and this function does not need to be called.
 * Note that the message returned by this function does not 
 * necessary argee with what comes back from RX callback, because
 * another message might have arrived by the time the host 
 * application handles the RX callback. The host application will
 * get a new RX callback corresponding to the new message but it
 * is recommended the host application calls this function as soon
 * as possible if the RX callback indicates the incoming message
 * is longer than 7 bytes.
 *
 * @param pointer to initiator logical address
 *
 * @param pointer to follower logical address
 *
 * @param buffer to hold payload (max. 15 bytes)
 *
 * @param pointer to length (set to length of whole message - 1)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         command is deemed successful even if there is no
 *         pending message
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_receive_message(uint32_t *initiator,
                                            uint32_t *follower,
                                            uint8_t *buffer,
                                            uint32_t *length);


/**
 * <DFN>vc_cec_get_logical_address</DFN> gets the logical address, 
 * If one is being allocated 0xF (unregistered) will be set.
 * A address value of 0xF also means CEC system is not yet ready
 * to send or receive any messages.
 *
 * @param pointer to logical address (set to allocated address)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         logical_address is not modified if command failed
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_get_logical_address(CEC_AllDevices_T *logical_address);

/**
 * <DFN>vc_cec_alloc_logical_address</DFN> starts the allocation 
 * of a logical address. Logical address is automatically allocated
 * after HDMI power on is complete and AV mute is deassert.
 * The host only needs to call this if the 
 * initial allocation failed (logical address being 0xF and 
 * physical address is NOT 0xFFFF from <DFN>VC_CEC_LOGICAL_ADDR</DFN>
 * notification), or if the host explicitly released its logical 
 * address.
 *
 * @param none
 *
 * @return zero if the command is successful, non-zero otherwise
 *         If successful, there will be a callback notification
 *         <DFN>VC_CEC_LOGICAL_ADDR</DFN>. 
 *         The host should wait for this before calling this 
 *         function again.
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_alloc_logical_address( void );

/**
 * Normally <DFN>vc_cec_release_logical_address</DFN> will not 
 * be called by the host application. It is used to release 
 * our logical address. This effectively disables CEC.
 * The host will need to allocate a new logical address before
 * doing any CEC calls (send/receive message, get topology, etc.). 
 *
 * @param none
 *
 * @return zero if the command is successful, non-zero otherwise
 *         The host should get a callback <DFN>VC_CEC_LOGICAL_ADDR</DFN>
 *         with 0xF being the logical address and 0xFFFF 
 *         being the physical address.
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_release_logical_address( void );

/**
 * Use <DFN>vc_cec_get_topology</DFN> to get the topology.
 *
 * @param pointer to <DFN>VC_CEC_TOPOLOGY_T</DFN>
 *
 * @return zero if the command is successful, non-zero otherwise
 *         If successful, the topology will be set, otherwise it is unchanged
 *         A topology with only 1 device (us) means CEC is not supported.
 *         If there is no topology available, this also returns a failure.
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_get_topology( VC_CEC_TOPOLOGY_T* topology);

/**
 * Use <DFN>vc_cec_set_vendor_id</DFN> to 
 * set the response to <Give Device Vendor ID>
 *
 * @param 24-bit IEEE vendor id
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_set_vendor_id( uint32_t id );

/**
 * Use <DFN>vc_cec_set_osd_name</DFN> to
 * set the response to <Give OSD Name>
 * 
 * @param OSD name (14 byte char array)
 *
 * @return zero if the command is successful, non-zero otherwise
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_set_osd_name( const char* name );

/**
 * <DFN>vc_cec_get_physical_address</DFN> gets our physical address
 *
 * @param pointer to physical address (returned as 16-bit packed value)
 *
 * @return zero if the command is successful, non-zero otherwise
 *          If failed, physical address argument will not be changed
 *          A physical address of 0xFFFF means CEC is not supported
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_get_physical_address(uint16_t *physical_address);

//API for some common CEC messages
/** 
 * Functions beginning with vc_cec_send_xxx make it easier for the 
 * host application to send CEC message xxx to other devices
 */
/**
 * <DFN>vc_cec_send_FeatureAbort</DFN> sends <Feature Abort> 
 * for a received command.
 *
 * @param follower (cannot be 0xF)
 *
 * @param rejected opcode
 *
 * @param reject reason <DFN>CEC_ABORT_REASON_T</DFN>
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_FeatureAbort(uint32_t follower, 
                                              CEC_OPCODE_T opcode, 
                                              CEC_ABORT_REASON_T reason);

/**
 * <DFN>vc_cec_send_ActiveSource</DFN> broadcasts
 * <Active Source> to all devices
 *
 * @param physical address (16-bit packed)
 *
 * @param reply or not (normally not)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_ActiveSource(uint16_t physical_address, bool_t is_reply);

/**
 * <DFN>vc_cec_send_ImageViewOn</DFN> sends <Image View On>
 * 
 * @param follower
 *
 * @param reply or not (normally not)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_ImageViewOn(uint32_t follower, bool_t is_reply);

/**
 * <DFN>vc_cec_send_SetOSDString</DFN> sends <Set OSD String>
 *
 * @param follower 
 *
 * @param string (char[13]) 
 *
 * @param display control <DFN>CEC_DISPLAY_CONTROL_T</DFN>
 *
 * @param reply or not (normally not)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_SetOSDString(uint32_t follower, 
                                              CEC_DISPLAY_CONTROL_T disp_ctrl, 
                                              const char* string,
                                              bool_t is_reply);

/**
 * <DFN>vc_cec_send_Standby</DFN> sends <Standby>.
 * This will put any/all devices to standby if they support
 * this CEC message.
 *
 * @param follower (can be 0xF)
 *
 * @param reply or not (normally not)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_Standby(uint32_t follower, bool_t is_reply);

/**
 * <DFN>vc_cec_send_MenuStatus</DFN> sends <Menu Status> 
 * (response to <Menu Request>)
 *
 * @param follower
 * 
 * @param menu state <DFN>CEC_MENU_STATE_T</DFN> but NOT CEC_MENU_STATE_QUERY
 *
 * @param reply or not (should always be yes)
 *
 * @return zero if the command is successful, non-zero otherwise
 *         Tx callback if successful
 ***********************************************************/
VCHPRE_ int VCHPOST_ vc_cec_send_MenuStatus(uint32_t follower, 
                                            CEC_MENU_STATE_T menu_state, 
                                            bool_t is_reply);

VCHPRE_ int VCHPOST_ vc_gencmd(char *response, int maxlen, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

