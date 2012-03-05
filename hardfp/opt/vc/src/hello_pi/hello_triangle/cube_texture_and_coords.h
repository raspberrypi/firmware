/*
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
*/
// Spatial coordinates for the cube

static const GLbyte quadx[6*4*3] = {
   /* FRONT */
   -10, -10,  10,
   10, -10,  10,
   -10,  10,  10,
   10,  10,  10,

   /* BACK */
   -10, -10, -10,
   -10,  10, -10,
   10, -10, -10,
   10,  10, -10,

   /* LEFT */
   -10, -10,  10,
   -10,  10,  10,
   -10, -10, -10,
   -10,  10, -10,

   /* RIGHT */
   10, -10, -10,
   10,  10, -10,
   10, -10,  10,
   10,  10,  10,

   /* TOP */
   -10,  10,  10,
   10,  10,  10,
   -10,  10, -10,
   10,  10, -10,

   /* BOTTOM */
   -10, -10,  10,
   -10, -10, -10,
   10, -10,  10,
   10, -10, -10,
};

/** Texture coordinates for the quad. */
static const GLfloat texCoords[6 * 4 * 2] = {
   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f,

   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f,

   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f,

   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f,

   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f,

   0.f,  0.f,
   0.f,  1.f,
   1.f,  0.f,
   1.f,  1.f
};

// Colors are invisible when textures appear on all 6 faces.
// If textures are disabled, e.g. by commenting out glEnable(GL_TEXTURE_2D),
// the colours will appear.

static const GLfloat colorsf[6*4*4] = {
   1.f,  0.f,  0.f,  1.f,  //red
   1.f,  0.f,  0.f,  1.f,
   1.f,  0.f,  0.f,  1.f,
   1.f,  0.f,  0.f,  1.f,

   0.f,  1.f,  0.f,  1.f,  // blue
   0.f,  1.f,  0.f,  1.f,
   0.f,  1.f,  0.f,  1.f,
   0.f,  1.f,  0.f,  1.f,

   0.f,  0.f,  1.f,  1.f, // green
   0.f,  0.f,  1.f,  1.f,
   0.f,  0.f,  1.f,  1.f,
   0.f,  0.f,  1.f,  1.f,

   0.f, 0.5f, 0.5f,  1.f, // teal
   0.f, 0.5f, 0.5f,  1.f,
   0.f, 0.5f, 0.5f,  1.f,
   0.f, 0.5f, 0.5f,  1.f,

   0.5f, 0.5f,  0.f,  1.f, // yellow
   0.5f, 0.5f,  0.f,  1.f,
   0.5f, 0.5f,  0.f,  1.f,
   0.5f, 0.5f,  0.f,  1.f,

   0.5f,  0.f, 0.5f,  1.f, // purple
   0.5f,  0.f, 0.5f,  1.f,
   0.5f,  0.f, 0.5f,  1.f,
   0.5f,  0.f, 0.5f,  1.f
};
