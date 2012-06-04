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
*/

#ifndef VCHI_CFG_INTERNAL_H_
#define VCHI_CFG_INTERNAL_H_

/****************************************************************************************
 * Control optimisation attempts.
 ***************************************************************************************/

// Don't use lots of short-term locks - use great long ones, reducing the overall locks-per-second
#define VCHI_COARSE_LOCKING

// Avoid lock then unlock on exit from blocking queue operations (msg tx, bulk rx/tx)
// (only relevant if VCHI_COARSE_LOCKING)
#define VCHI_ELIDE_BLOCK_EXIT_LOCK

// Avoid lock on non-blocking peek
// (only relevant if VCHI_COARSE_LOCKING)
#define VCHI_AVOID_PEEK_LOCK

// Use one slot-handler thread per connection, rather than 1 thread dealing with all connections in rotation.
#define VCHI_MULTIPLE_HANDLER_THREADS

// Put free descriptors onto the head of the free queue, rather than the tail, so that we don't thrash
// our way through the pool of descriptors.
#define VCHI_PUSH_FREE_DESCRIPTORS_ONTO_HEAD

// Don't issue a MSG_AVAILABLE callback for every single message. Possibly only safe if VCHI_COARSE_LOCKING.
#define VCHI_FEWER_MSG_AVAILABLE_CALLBACKS

// Don't use message descriptors for TX messages that don't need them
#define VCHI_MINIMISE_TX_MSG_DESCRIPTORS

// Nano-locks for multiqueue
//#define VCHI_MQUEUE_NANOLOCKS

// Lock-free(er) dequeuing
//#define VCHI_RX_NANOLOCKS

#endif /*VCHI_CFG_INTERNAL_H_*/
