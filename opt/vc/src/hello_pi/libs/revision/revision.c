/*
Copyright (c) 2019, Raspberry Pi (Trading) Ltd
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "revision.h"

static unsigned int get_revision_code()
{
   FILE *fin;
   char str[256];
   unsigned int revision_num = 0;

   fin = fopen("/proc/cpuinfo", "rt");

   if (fin == NULL)
      return 0;

   while (fgets(str, sizeof(str), fin) != NULL)
   {
      if (sscanf(str, "Revision : %x", &revision_num) == 1)
         break;
   }

   fclose(fin);

   return revision_num;
}

/* Returns the type of the Pi being used
*/
int get_model_type(void)
{
   unsigned int revision_num = get_revision_code();

   if (!revision_num)
      return 0;

   // Check for old/new style revision code. Bit 23 will be guaranteed one for new style
   if (revision_num & 0x800000)
      return (revision_num & 0xff0) >> 4;
   else
   {
      // Mask off warrantee and overclock bits.
      revision_num &= 0xffffff;

      // Map old style to new Type code
      if (revision_num < 2 || revision_num > 21)
         return 0;

      static const unsigned char type_map[] =
      {
         1,   // B rev 1.0  2
         1,   // B rev 1.0  3
         1,   // B rev 2.0  4
         1,   // B rev 2.0  5
         1,   // B rev 2.0  6
         0,   // A rev 2    7
         0,   // A rev 2    8
         0,   // A rev 2    9
         0, 0, 0,  // unused  a,b,c
         1,   // B  rev 2.0  d
         1,   // B rev 2.0  e
         1,   // B rev 2.0  f
         3,   // B+ rev 1.2 10
         6,   // CM1        11
         2,   // A+ rev1.1  12
         3,   // B+ rev 1.2 13 
         6,   // CM1        14
         2    // A+         15
      };
      return type_map[revision_num-2];
   }

   return 0;
}

/* Returns the type of the Pi being used
*/
int is_model_pi4(void)
{
   return get_model_type() == 0x11 ? 1 : 0;
}

/* returns the processor ID
*/
int get_processor_id(void)
{
   unsigned int revision_num = get_revision_code();

   if (revision_num & 0x800000)
   {
      return (revision_num & 0xf000) >> 12;
   }
   else
   {
      // Old style number only used 2835
      return PROCESSOR_BCM2835;
   }
}

