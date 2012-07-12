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

#ifndef VCHIQ_ARM_H
#define VCHIQ_ARM_H

#include "vchiq_core.h"


typedef struct vchiq_arm_state_struct {

   VCOS_THREAD_T lp_thread;            /* processes low priority messages (eg suspend) */
   VCOS_THREAD_T hp_thread;            /* processes high priority messages (eg resume) */

   VCOS_EVENT_T lp_evt;
   VCOS_EVENT_T hp_evt;

   VCOS_MUTEX_T use_count_mutex;
   VCOS_MUTEX_T suspend_resume_mutex;

   int suspend_pending;

   /* Global use count for videocore.
    * This is equal to the sum of the use counts for all services.  When this hits
    * zero the videocore suspend procedure will be initiated. */
   int videocore_use_count;

   /* Use count to track requests from videocore peer.
    * This use count is not associated with a service, so needs to be tracked separately
    * with the state.
    */
   int peer_use_count;

   /* Flag to indicate whether videocore is currently suspended */
   int videocore_suspended;

   /* Flag to indicate whether a notification is pending back to videocore that it's
    * "remote use request" has been actioned */
   int use_notify_pending;
} VCHIQ_ARM_STATE_T;


extern VCOS_LOG_CAT_T vchiq_arm_log_category;

extern int __init
vchiq_platform_vcos_init(void);

extern int __init
vchiq_platform_init(VCHIQ_STATE_T *state);

extern void __exit
vchiq_platform_exit(VCHIQ_STATE_T *state);

extern VCHIQ_STATE_T *
vchiq_get_state(void);

extern VCHIQ_STATUS_T
vchiq_arm_vcsuspend(VCHIQ_STATE_T *state);

extern VCHIQ_STATUS_T
vchiq_arm_vcresume(VCHIQ_STATE_T *state);

extern VCHIQ_STATUS_T
vchiq_arm_init_state(VCHIQ_STATE_T *state, VCHIQ_ARM_STATE_T *arm_state);

extern void
vchiq_check_resume(VCHIQ_STATE_T* state);

extern void
vchiq_check_suspend(VCHIQ_STATE_T* state);

extern VCHIQ_STATUS_T
vchiq_use_service(VCHIQ_SERVICE_HANDLE_T handle);

extern VCHIQ_STATUS_T
vchiq_release_service(VCHIQ_SERVICE_HANDLE_T handle);

extern VCHIQ_STATUS_T
vchiq_check_service(VCHIQ_SERVICE_T * service);

extern VCHIQ_STATUS_T
vchiq_platform_suspend(VCHIQ_STATE_T *state);

extern VCHIQ_STATUS_T
vchiq_platform_resume(VCHIQ_STATE_T *state);

extern int
vchiq_platform_videocore_wanted(VCHIQ_STATE_T* state);

extern int
vchiq_platform_use_suspend_timer(void);

extern void
vchiq_dump_platform_use_state(VCHIQ_STATE_T *state);

extern void
vchiq_dump_service_use_state(VCHIQ_STATE_T *state);

extern VCHIQ_ARM_STATE_T*
vchiq_platform_get_arm_state(VCHIQ_STATE_T *state);


#endif /* VCHIQ_ARM_H */
