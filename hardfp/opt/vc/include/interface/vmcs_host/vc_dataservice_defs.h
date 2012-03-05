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
* Dataservice defs
*/

#ifndef VC_DS_DEFS_H
#define VC_DS_DEFS_H

// whether to include PPP routing
#define VC_DATASERVICE_PPP

/* Error codes used in responses and in the API */

enum {
   VC_SOCK_OK          =  0,  /* Success */
   VC_SOCK_WOULDBLOCK  = -1,  /* Not really an error, means no data available*/
   VC_SOCK_NOTSOCK     = -2,  /* Not a valid socket handle, or socket closed */
   VC_SOCK_NOTCONNECTED = -3, /* Attempt to read/write non-connected socket  */
   VC_SOCK_EOF         = -4,  /* No more data may be read/written            */
   VC_SOCK_MSGSIZE     = -5,  /* Attempt to send too many bytes for UDP      */
   VC_SOCK_ADDRINUSE   = -6,  /* Could not bind: address already in use      */
   VC_SOCK_CONNREFUSED = -7,  /* TCP connection refused or UDP port not ready*/
   VC_SOCK_TIMEDOUT    = -8,  /* TCP connection timed out                    */
   VC_SOCK_UNREACHABLE = -9,  /* Peer unreachable                            */
   VC_SOCK_TOOMANY     = -10, /* Too many or not enough of something         */
   VC_SOCK_IO          = -11, /* Something else went wrong                   */
   VC_SOCK_UNSUPPORTED = -12, /* Unsupported or inappropriate request        */
   VC_PPP_REFUSED      = -64, /* PPP packet not wanted by VC */
   VC_NO_NET_DEV       = -13, /* Network device was not able to be initialised */
   VC_SOCK_NOMEM       = -14, /* Out of memory                                */
};


/* Protocol (not used by API) version 1.1 */

enum {
   /* Requests (VC->Host->VC) */
   VC_DSPRO_START        = 64,
   VC_DSPRO_STOP         = 65,
   VC_DSPRO_CLOSE        = 66,
   VC_DSPRO_UDPSOCK      = 67,
   VC_DSPRO_RECVFROM     = 68,
   VC_DSPRO_SENDTO       = 69,
   VC_DSPRO_CONNECT      = 70,
   VC_DSPRO_READ         = 71,
   VC_DSPRO_WRITE        = 72,
   VC_DSPRO_LISTEN       = 73,
   VC_DSPRO_ACCEPT       = 74,
   VC_DSPRO_DEBUG        = 75,
   VC_DSPRO_LOCAL_ADDR   = 76,
   /* Notification (Host->VC) */
   VC_DSPRO_ASYNC        = 96,
   VC_DSPRO_NETWORK_DOWN = 97,

   /* PPP data (VC->Host) */
   VC_DSPRO_PPP_FROM_VC = 128, // all PPP packets when in request state
   VC_DSPRO_PPP_RETURNED= 129, // an unwanted PPP packet when in request state
   VC_REQUEST_PPP       = 136, // move to PPP request state (following download/streaming request)
   VC_REFUSE_PPP        = 137, // move out of PPP request state (end of download/streaming request)
   VC_OPEN_PPP          = 138, // PPP open (for testing only)

   /* PPP data (Host->VC) */
   VC_DSPRO_PPP_TO_VC   = 160,

   /* Read/write flags in responses and notifications */
   VC_DSPRO_RFLAG  =   1,
   VC_DSPRO_WFLAG  =   2,
   VC_DSPRO_RWMASK =   3,
   VC_DSPRO_RRESP  =  16,
   VC_DSPRO_WRESP  =  32,
   VC_DSPRO_CREATE = 128,

   /* Protocol major version. Only the lowest 16 bits need match exactly. */
   VC_DSPRO_VERSION = 1,
   VC_DSPRO_VER_MASK = 65535,

   /* Protocol host options. The host puts these in the top 16 bits. */
   VC_DSPRO_HOPT_LOCALADDR = (1<<16),
   VC_DSPRO_HOPT_LISTEN    = (1<<17),
   VC_DSPRO_HOPT_DEBUG     = (1<<18),
   VC_DSPRO_HOPT_WRAGAIN   = (1<<19)
};

#endif
