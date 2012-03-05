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
* A rotating cube rendered with OpenGL|ES. Three images used as textures on the cube faces.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>

#include "bcm_host.h"

#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"

#ifndef M_PI
   #define M_PI 3.141592654
#endif
	

typedef struct
{
   uint32_t screen_width;
   uint32_t screen_height;
// OpenGL|ES objects
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
   GLuint tex[6];
// model rotation vector and direction
   GLfloat rot_angle_x_inc;
   GLfloat rot_angle_y_inc;
   GLfloat rot_angle_z_inc;
// current model rotation angles
   GLfloat rot_angle_x;
   GLfloat rot_angle_y;
   GLfloat rot_angle_z;
// current distance from camera
   GLfloat distance;
   GLfloat distance_inc;
// pointers to texture buffers
   char *tex_buf1;
   char *tex_buf2;
   char *tex_buf3;
   GLuint vshader, fshader, program;
   unsigned int attr_vertex;
   unsigned int unif_color;
   unsigned int unif_offset;
   unsigned int unif_scale;
   unsigned int unif_tex;
} CUBE_STATE_T;

static CUBE_STATE_T _state, *state=&_state;


/***********************************************************
 * Name: init_ogl
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description: Sets the display, OpenGL|ES context and screen stuff
 *
 * Returns: void
 *
 ***********************************************************/
static void init_ogl(CUBE_STATE_T *state)
{
   int32_t success = 0;
   EGLBoolean result;
   EGLint num_config;

   static EGL_DISPMANX_WINDOW_T nativewindow;

   DISPMANX_ELEMENT_HANDLE_T dispman_element;
   DISPMANX_DISPLAY_HANDLE_T dispman_display;
   DISPMANX_UPDATE_HANDLE_T dispman_update;
   VC_RECT_T dst_rect;
   VC_RECT_T src_rect;

   static const EGLint attribute_list[] =
   {
      EGL_RED_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_BLUE_SIZE, 8,
      EGL_ALPHA_SIZE, 8,
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_NONE
   };
   EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
   
   EGLConfig config;

   // get an EGL display connection
   state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   assert(state->display!=EGL_NO_DISPLAY);

   // initialize the EGL display connection
   result = eglInitialize(state->display, NULL, NULL);
   assert(EGL_FALSE != result);

   // get an appropriate EGL frame buffer configuration
   result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
   assert(EGL_FALSE != result);

   result = eglBindAPI(EGL_OPENGL_ES_API);
   assert(EGL_FALSE != result);

   // create an EGL rendering context
   state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, context_attribs);
   assert(state->context!=EGL_NO_CONTEXT);

   // create an EGL window surface
   success = graphics_get_display_size(0 /* LCD */, &state->screen_width, &state->screen_height);
   assert( success >= 0 );

   dst_rect.x = 0;
   dst_rect.y = 0;
   dst_rect.width = state->screen_width;
   dst_rect.height = state->screen_height;
      
   src_rect.x = 0;
   src_rect.y = 0;
   src_rect.width = state->screen_width << 16;
   src_rect.height = state->screen_height << 16;        

   dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
   dispman_update = vc_dispmanx_update_start( 0 );
         
   dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
      0/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
      
   nativewindow.element = dispman_element;
   nativewindow.width = state->screen_width;
   nativewindow.height = state->screen_height;
   vc_dispmanx_update_submit_sync( dispman_update );
      
   state->surface = eglCreateWindowSurface( state->display, config, &nativewindow, NULL );
   assert(state->surface != EGL_NO_SURFACE);

   // connect the context to the surface
   result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
   assert(EGL_FALSE != result);
}

static const char *vshader_source =
      "attribute vec4 vertex;"
      "uniform vec2 offset;"
      "uniform vec2 scale;"
      "varying vec2 tcoord;"
      "void main(void) {"
      "  vec4 pos = vertex;"
      "  pos.xy = pos.xy*scale + offset;"
      "  gl_Position = pos;"
      "  tcoord = vertex.xy;"
      "}";
      
static const char *fshader_source =
      "uniform vec4 color;"
      "uniform sampler2D tex;"
      "varying vec2 tcoord;"
      "void main(void) {"
      "   gl_FragColor = color * texture2D(tex, tcoord);"
      "}";

static float vertex_data[] =
{
   0.0f, 0.0f, 0.5f, 1.0f,
    1.0f, 0.0f, 0.5f, 1.0f,
    1.0f,  1.0f, 0.5f, 1.0f,
    0.0f,  1.0f, 0.5f, 1.0f,
};

/* Initialize the shaders */
int init_shaders( CUBE_STATE_T *state )
{
   state->vshader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(state->vshader, 1, &vshader_source, 0);
   glCompileShader(state->vshader);

   state->fshader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(state->fshader, 1, &fshader_source, 0);
   glCompileShader(state->fshader);

   state->program = glCreateProgram();
   glAttachShader(state->program, state->vshader);
   glAttachShader(state->program, state->fshader);
   glLinkProgram(state->program);

   state->attr_vertex = glGetAttribLocation(state->program, "vertex");
   state->unif_color = glGetUniformLocation(state->program, "color");
   state->unif_offset = glGetUniformLocation(state->program, "offset");
   state->unif_scale = glGetUniformLocation(state->program, "scale");
   state->unif_tex = glGetUniformLocation(state->program, "tex");

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}

/***********************************************************
 * Name: load_tex_images
 *
 * Arguments:
 *       void
 *
 * Description: Loads three raw images to use as textures on faces
 *
 * Returns: void
 *
 ***********************************************************/
static void load_tex_images(CUBE_STATE_T *state)
{
   #define PATH "./"
   #define IMAGE_SIZE 128

   FILE *tex_file1 = NULL, *tex_file2=NULL, *tex_file3 = NULL;
   int bytes_read, image_sz = IMAGE_SIZE*IMAGE_SIZE*3;

   state->tex_buf1 = malloc(image_sz);
   state->tex_buf2 = malloc(image_sz);
   state->tex_buf3 = malloc(image_sz);

   tex_file1 = fopen(PATH "Lucca_128_128.raw", "rb");
   if (tex_file1 && state->tex_buf1)
   {
      bytes_read=fread(state->tex_buf1, 1, image_sz, tex_file1);
      assert(bytes_read == image_sz);  // some problem with file?
      fclose(tex_file1);
   }

   tex_file2 = fopen(PATH "Djenne_128_128.raw", "rb");
   if (tex_file2 && state->tex_buf2)
   {
      bytes_read=fread(state->tex_buf2, 1, image_sz, tex_file2);
      assert(bytes_read == image_sz);  // some problem with file?
      fclose(tex_file2);      
   }

   tex_file3 = fopen(PATH "Gaudi_128_128.raw", "rb");
   if (tex_file3 && state->tex_buf3)
   {
      bytes_read=fread(state->tex_buf3, 1, image_sz, tex_file3);
      assert(bytes_read == image_sz);  // some problem with file?
      fclose(tex_file3);
   }   
}

/***********************************************************
 * Name: init_textures
 *
 * Arguments:
 *       CUBE_STATE_T *state - holds OGLES model info
 *
 * Description:   Initialise OGL|ES texture surfaces to use image
 *                buffers
 *
 * Returns: void
 *
 ***********************************************************/
static void init_textures(CUBE_STATE_T *state)
{
   // load three texture buffers but use them on six OGL|ES texture surfaces
   load_tex_images(state);
   glGenTextures(6, &state->tex[0]);

   // setup first texture
   glBindTexture(GL_TEXTURE_2D, state->tex[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf1);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // setup second texture - reuse first image
   glBindTexture(GL_TEXTURE_2D, state->tex[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf1);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // third texture
   glBindTexture(GL_TEXTURE_2D, state->tex[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf2);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // fourth texture  - reuse second image
   glBindTexture(GL_TEXTURE_2D, state->tex[3]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf2);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   //fifth texture
   glBindTexture(GL_TEXTURE_2D, state->tex[4]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf3);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

   // sixth texture  - reuse third image
   glBindTexture(GL_TEXTURE_2D, state->tex[5]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_SIZE, IMAGE_SIZE, 0,
                GL_RGB, GL_UNSIGNED_BYTE, state->tex_buf3);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_NEAREST);

}


/* draw trinagles */

void draw_triangles ( CUBE_STATE_T *state )
{
   // Set the viewport
   glViewport ( 0, 0, state->screen_width, state->screen_height );
   
   // Use the program object
   glUseProgram ( state->program );

   glBindBuffer(GL_ARRAY_BUFFER, 1);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
   glVertexAttribPointer(state->attr_vertex, 4, GL_FLOAT, GL_FALSE, 16, 0);
   glEnableVertexAttribArray(state->attr_vertex);

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   int i;
   for(i=0;i<10;i++)
   {
      float r, g, b, a;
      r = 0.5; g = 1.0f; b = 0.5f; a = 1.0;
      float aspect = 1.0f, sc = 0.1f;;
      float x = -1.0f + sc*i + 0.1f*sc;
      float y = -(sc/2.0f - 0.1f*sc)*aspect;
      float w = sc*0.8f;
      float h = sc*0.8f*aspect;

   glBindTexture(GL_TEXTURE_2D, state->tex[0]);
   glUniform1i(state->unif_tex, 0);
   glUniform4f(state->unif_color, r, g, b, a);
   glUniform2f(state->unif_offset, x, y);
   glUniform2f(state->unif_scale, w, h);

   glDrawArrays ( GL_TRIANGLE_FAN, 0, 4 );
   }
   eglSwapBuffers(state->display, state->surface);
}

//------------------------------------------------------------------------------

static void exit_func(void)
// Function to be passed to atexit().
{
   // clear screen
   glClear( GL_COLOR_BUFFER_BIT );
   eglSwapBuffers(state->display, state->surface);

   glDeleteProgram(state->program);
 
   // Release OpenGL resources
   eglMakeCurrent( state->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
   eglDestroySurface( state->display, state->surface );
   eglDestroyContext( state->display, state->context );
   eglTerminate( state->display );

} // exit_func()


int main ()
{
   int terminate = 0;
   bcm_host_init();

   // Clear application state
   memset( state, 0, sizeof( *state ) );
      
   // Start OGLES
   init_ogl(state);

   // load_textures
   init_textures(state);

   // Set up the shaders
   init_shaders(state);

   while (!terminate)
   {
      //usleep(5*1000);
      draw_triangles(state);
   }
   exit_func();
   return 0;
}

