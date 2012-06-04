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
* OpenMAX IL Component Service definitions
*/

#ifndef ILCS_H
#define ILCS_H

#include "IL/OMX_Component.h"
#include "interface/vmcs_host/vc_ilcs_defs.h"

struct ILCS_SERVICE_T;
typedef struct ILCS_SERVICE_T ILCS_SERVICE_T;

struct ILCS_COMMON_T;
typedef struct ILCS_COMMON_T ILCS_COMMON_T;

typedef void (*IL_FN_T)(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen);

typedef struct {
   IL_FN_T *fns;
   ILCS_COMMON_T *(*ilcs_common_init)(ILCS_SERVICE_T *);
   void (*ilcs_common_deinit)(ILCS_COMMON_T *st);
   void (*ilcs_thread_init)(ILCS_COMMON_T *st);
   unsigned char *(*ilcs_mem_lock)(OMX_BUFFERHEADERTYPE *buffer);
   void (*ilcs_mem_unlock)(OMX_BUFFERHEADERTYPE *buffer);
} ILCS_CONFIG_T;

// initialise the VideoCore IL Component service
// returns pointer to state on success, NULL on failure
#ifdef USE_VCHIQ_ARM
VCHPRE_ ILCS_SERVICE_T VCHPOST_ *ilcs_init(VCHIQ_INSTANCE_T state, void **connection, ILCS_CONFIG_T *config, int use_memmgr);
#else
VCHPRE_ ILCS_SERVICE_T VCHPOST_ *ilcs_init(VCHIQ_STATE_T *state, void **connection, ILCS_CONFIG_T *config, int use_memmgr);
#endif

// deinitialises the IL Component service
VCHPRE_ void VCHPOST_ ilcs_deinit(ILCS_SERVICE_T *ilcs);

// returns 1 if the current thread is the ilcs thread, 0 otherwise
VCHPRE_ int VCHPOST_ ilcs_thread_current(void *param);

// returns pointer to shared state
VCHPRE_ ILCS_COMMON_T *ilcs_get_common(ILCS_SERVICE_T *ilcs);

VCHPRE_ int VCHPOST_ ilcs_execute_function(ILCS_SERVICE_T *ilcs, IL_FUNCTION_T func, void *data, int len, void *resp, int *rlen);
VCHPRE_ OMX_ERRORTYPE VCHPOST_ ilcs_pass_buffer(ILCS_SERVICE_T *ilcs, IL_FUNCTION_T func, void *reference, OMX_BUFFERHEADERTYPE *pBuffer);
VCHPRE_ OMX_BUFFERHEADERTYPE * VCHPOST_ ilcs_receive_buffer(ILCS_SERVICE_T *ilcs, void *call, int clen, OMX_COMPONENTTYPE **pComp);

// bulks are 16 bytes aligned, implicit in use of vchiq
#define ILCS_ALIGN   16

#define ILCS_ROUND_UP(x) ((((unsigned long)(x))+ILCS_ALIGN-1) & ~(ILCS_ALIGN-1))
#define ILCS_ROUND_DOWN(x) (((unsigned long)(x)) & ~(ILCS_ALIGN-1))
#define ILCS_ALIGNED(x) (((unsigned long)(x) & (ILCS_ALIGN-1)) == 0)


#ifdef _VIDEOCORE
#include "vcfw/logging/logging.h"

#ifdef ILCS_LOGGING

#define LOG_MSG ILCS_LOGGING
extern void ilcs_log_event_handler(OMX_HANDLETYPE hComponent, OMX_PTR pAppData, OMX_EVENTTYPE eEvent,
                                   OMX_U32 nData1,OMX_U32 nData2,OMX_PTR pEventData);

#else

#define LOG_MSG LOGGING_GENERAL
#define ilcs_log_event_handler(...)
extern void dummy_logging_message(int level, const char *format, ...);
#undef logging_message
#define logging_message if (1) {} else dummy_logging_message

#endif // ILCS_LOGGING
#endif // _VIDEOCORE

#endif // ILCS_H

