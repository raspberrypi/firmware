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
* File service required types.
*/

#ifndef VCFILESYS_DEFS_H
#define VCFILESYS_DEFS_H

#include <time.h>  // for time_t

/* Define type fattributes_t and struct dirent for use in file system functions */

typedef int fattributes_t;
//enum {ATTR_RDONLY=1, ATTR_DIRENT=2};
#define ATTR_RDONLY     0x01        /* Read only file attributes */
#define ATTR_HIDDEN     0x02        /* Hidden file attributes */
#define ATTR_SYSTEM     0x04        /* System file attributes */
#define ATTR_VOLUME     0x08        /* Volume Label file attributes */
#define ATTR_DIRENT     0x10        /* Dirrectory file attributes */
#define ATTR_ARCHIVE     0x20        /* Archives file attributes */
#define ATTR_NORMAL     0x00        /* Normal file attributes */

#define D_NAME_MAX_SIZE 256

#ifndef _DIRENT_H  // This should really be in a dirent.h header to avoid conflicts
struct dirent
{
   char d_name[D_NAME_MAX_SIZE];
   unsigned int d_size;
   fattributes_t d_attrib;
   time_t d_creatime;
   time_t d_modtime;
};
#endif // ifndef _DIRENT_H

#define FS_MAX_PATH 256   // The maximum length of a pathname
/* Although not used in the API, this value is required on the host and
VC01 sides of the file system, even if there is no host side. Putting it in
vc_fileservice_defs.h is not appropriate as it would only be included if there
was a host side. */

/* File system error codes */
#define FS_BAD_USER  -7000     // The task isn't registered as a file system user

#define FS_BAD_FILE  -7001     // The path or filename or file descriptor is invalid
#define FS_BAD_PARM  -7002     // Invalid parameter given
#define FS_ACCESS    -7003     // File access conflict
#define FS_MAX_FILES -7004     // Maximum number of files already open
#define FS_NOEMPTY   -7005     // Directory isn't empty
#define FS_MAX_SIZE  -7006     // File is over the maximum file size

#define FS_NO_DISK   -7007     // No disk is present, or the disk has not been opened
#define FS_DISK_ERR  -7008     // There is a problem with the disk

#define FS_IO_ERROR  -7009     // Driver level error

#define FS_FMT_ERR   -7010     // Format error

#define FS_NO_BUFFER -7011     // Internal Nucleus File buffer not available
#define FS_NUF_INT   -7012     // Internal Nucleus File error

#define FS_UNSPEC_ERR -7013    // Unspecified error

#endif
