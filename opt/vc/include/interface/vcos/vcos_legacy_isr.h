/*
 * Copyright (c) 2010-2011 Broadcom. All rights reserved.
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

/*=============================================================================
VideoCore OS Abstraction Layer - legacy (Nucleus) IRQ support
=============================================================================*/

#ifndef VCOS_LEGACY_ISR_H
#define VCOS_LEGACY_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "interface/vcos/vcos_types.h"
#include "vcos_platform.h"

/** \file vcos_legacy_isr.h
  *
  * API for dispatching interrupts the Nucleus way, via a LISR and HISR.
  * New code should use the single-dispatch scheme - the LISR/HISR
  * distinction is not necessary.
  *
  * Under ThreadX, a HISR is implemented as a high-priority thread which 
  * waits on a counting semaphore to call the HISR function. Although this
  * provides a good approximation to the Nucleus semantics, it is potentially
  * slow if all you are trying to do is to wake a thread from LISR context.
  */

/** Register a LISR. This is identical to the NU_Register_LISR API.
  */
VCOS_INLINE_DECL
VCOS_STATUS_T vcos_register_legacy_lisr(VCOS_UNSIGNED vecnum,
                                        void (*lisr)(VCOS_INT),
                                        void (**old_lisr)(VCOS_INT));

VCOS_INLINE_DECL
VCOS_STATUS_T vcos_legacy_hisr_create(VCOS_HISR_T *hisr, const char *name,
                                      void (*entry)(void),
                                      VCOS_UNSIGNED pri,
                                      void *stack, VCOS_UNSIGNED stack_size);

/** Activate a HISR. On an OS which has no distinction between a HISR and LISR,
  * this may use some kind of emulation, which could well be less efficient than
  * a normal ISR.`
  *
  * @param hisr HISR to activate.
  */
VCOS_INLINE_DECL
void vcos_legacy_hisr_activate(VCOS_HISR_T *hisr);

/** Delete a HISR. 
  *
  * @param hisr HISR to delete.
  */
VCOS_INLINE_DECL
void vcos_legacy_hisr_delete(VCOS_HISR_T *hisr);

/** Are we in a legacy LISR?
  *
  * @return On Nucleus, non-zero if in a LISR. On other platforms, non-zero if
  * in an interrupt.
  */
VCOS_INLINE_DECL
int vcos_in_legacy_lisr(void);

/** Is the current thread actually a fake HISR thread? Only implemented
  * on platforms that fake up HISRs.
  */

#ifndef VCOS_LISRS_NEED_HISRS
VCOSPRE_ int VCOSPOST_ vcos_current_thread_is_fake_hisr_thread(VCOS_HISR_T *);
#endif

#ifdef __cplusplus
}
#endif
#endif
