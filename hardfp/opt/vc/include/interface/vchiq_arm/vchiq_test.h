/*
 * Copyright (c) 2010-2011 Broadcom Corporation. All rights reserved.
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

#ifndef VCHIQ_TEST_H
#define VCHIQ_TEST_H

#include "vchiq_test_if.h"

#define VCOS_LOG_CATEGORY (&vchiq_test_log_category)

#define VERBOSE_TRACE 1

#define FUNC_FOURCC VCHIQ_MAKE_FOURCC('f','u','n','c')
#define FUN2_FOURCC VCHIQ_MAKE_FOURCC('f','u','n','2')

#define SERVICE1_DATA_SIZE 1024
#define SERVICE2_DATA_SIZE 2048
#define FUN2_MAX_DATA_SIZE 16384
#define FUN2_MAX_ALIGN     4096
#define BULK_ALIGN_SIZE    4096

enum {
   MSG_ERROR,
   MSG_ONEWAY,
   MSG_ASYNC,
   MSG_SYNC,
   MSG_CONFIG,
   MSG_ECHO
};

struct test_params
{
   int magic; /* = MSG_CONFIG */
   int blocksize;
   int iters;
   int verify;
   int echo;
   int align_size;
   int client_align;
   int server_align;
   int client_message_quota;
   int server_message_quota;
};

#if VERBOSE_TRACE

#define EXPECT(_e, _v) if (_e != _v) { vcos_log_error("%d: " #_e " != " #_v, __LINE__); VCOS_BKPT; goto error_exit; } else { vcos_log_trace("%d: " #_e " == " #_v, __LINE__); }

#define START_CALLBACK(_r, _u) \
   if (++callback_index == callback_count) { \
      if (reason != _r) { \
         vcos_log_error("%d: expected callback reason " #_r ", got %d", __LINE__, reason); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)VCHIQ_GET_SERVICE_USERDATA(service) != _u) { \
         vcos_log_error("%d: expected userdata %d, got %d", __LINE__, _u, (int)VCHIQ_GET_SERVICE_USERDATA(service)); VCOS_BKPT; goto error_exit; \
      } \
      else \
      { \
         vcos_log_trace("%d: " #_r ", " #_u, __LINE__); \
      }

#define START_BULK_CALLBACK(_r, _u, _bu)   \
   if (++bulk_index == bulk_count) {  \
      if (reason != _r) { \
         vcos_log_error("%d: expected callback reason " #_r ", got %d", __LINE__, reason); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)VCHIQ_GET_SERVICE_USERDATA(service) != _u) { \
         vcos_log_error("%d: expected userdata %d, got %d", __LINE__, _u, (int)VCHIQ_GET_SERVICE_USERDATA(service)); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)bulk_userdata != _bu) { \
         vcos_log_error("%d: expected bulk_userdata %d, got %d", __LINE__, _bu, (int)bulk_userdata); VCOS_BKPT; goto error_exit; \
      } \
      else \
      { \
         vcos_log_trace("%d: " #_r ", " #_u ", " #_bu, __LINE__); \
      }

#else

#define EXPECT(_e, _v) if (_e != _v) { vcos_log_trace("%d: " #_e " != " #_v, __LINE__); VCOS_BKPT; goto error_exit; }

#define START_CALLBACK(_r, _u) \
   if (++callback_index == callback_count) { \
      if (reason != _r) { \
         vcos_log_error("%d: expected callback reason " #_r ", got %d", __LINE__, reason); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)VCHIQ_GET_SERVICE_USERDATA(service) != _u) { \
         vcos_log_error("%d: expected userdata %d, got %d", __LINE__, _u, (int)VCHIQ_GET_SERVICE_USERDATA(service)); VCOS_BKPT; goto error_exit; \
      }

#define START_BULK_CALLBACK(_r, _u, _bu)   \
   if (++bulk_index == bulk_count) {  \
      if (reason != _r) { \
         vcos_log_error("%d: expected callback reason " #_r ", got %d", __LINE__, reason); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)VCHIQ_GET_SERVICE_USERDATA(service) != _u) { \
         vcos_log_error("%d: expected userdata %d, got %d", __LINE__, _u, (int)VCHIQ_GET_SERVICE_USERDATA(service)); VCOS_BKPT; goto error_exit; \
      } \
      else if ((int)bulk_userdata != _bu) { \
         vcos_log_error("%d: expected bulkuserdata %d, got %d", __LINE__, _bu, (int)bulk_userdata); VCOS_BKPT; goto error_exit; \
      }

#endif

#define END_CALLBACK(_s) \
      return _s; \
   }

#endif
