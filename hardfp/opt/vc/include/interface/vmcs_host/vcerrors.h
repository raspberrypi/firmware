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
* Enum to aid interpreting errors from VideoCore.
*/

#ifndef VCERRORS_H
#define VCERRORS_H

// Enum to aid interpreting errors returned by VideoCore in general command responses.
// Their meanings are indicated in the comments, but only a few of them are ever likely
// to be of interest to end users. The error number should be returned in
// a "error=<number>" field of the response.

typedef enum {
   VC_ERR_NONE = 0,    // no error has occurred

   VC_ERR_NO_CMD,      // no such command exists
   VC_ERR_BAD_PARAMS,  // command parameters were bad in some way
   VC_ERR_BAD_CMD,     // command is inappropriate in some way

   VC_ERR_NO_MEMORY,   // insufficient memory to continue with request
   VC_ERR_NO_VLL,      // a required VLL is missing
   VC_ERR_BAD_VLL,     // VLL is bad in some way

   VC_ERR_NO_SOURCE,     // a named file/url does not appear to exist
   VC_ERR_UNIMPL_SOURCE, // the data in the source is unsupported/unimplemented
   VC_ERR_BAD_SOURCE,    // the file/url is incomplete or invalid in some way

   VC_ERR_AUDIO_BUSY,  // VideoCore audio was required but is in use

   VC_ERR_INTERRUPTED, // some operation has been interrupted

   VC_ERR_NO_SPACE,    // insufficient space on filesystem or similar

   VC_ERR_NO_SIGNAL,   // used by DMB to indicate a transmission signal failure

   VC_ERR_MAX_FILE_SIZE, // file write has reached the max file size allowed

   // New error types of error should be added right here:
   // ...

   VC_ERR_UNKNOWN=9999 // another kind of error has occurred
} VC_ERR_T;

#endif
