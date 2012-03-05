//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// esUtil.c
//
//    A utility library for OpenGL ES.  This library provides a
//    basic common framework for the example applications in the
//    OpenGL ES 2.0 Programming Guide.
//

///
//  Includes
//
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "esUtil.h"
#include "esUtil_qnx.h"

///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay* eglDisplay, EGLContext* eglContext,
        EGLSurface* eglSurface, EGLint attribList[])
{
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLint contextAttribs[] =
    { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

    // Get Display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY)
    {
        return EGL_FALSE;
    }

    // Initialize EGL
    if (!eglInitialize(display, &majorVersion, &minorVersion))
    {
        return EGL_FALSE;
    }

    // Get configs
    if (!eglGetConfigs(display, NULL, 0, &numConfigs))
    {
        return EGL_FALSE;
    }

    // Choose config
    if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
    {
        return EGL_FALSE;
    }

    // Create a surface
    surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType) hWnd, NULL);
    if (surface == EGL_NO_SURFACE)
    {
        return EGL_FALSE;
    }

    // Create a GL context
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT)
    {
        return EGL_FALSE;
    }

    // Make the context current
    if (!eglMakeCurrent(display, surface, surface, context))
    {
        return EGL_FALSE;
    }

    *eglDisplay = display;
    *eglSurface = surface;
    *eglContext = context;
    return EGL_TRUE;
}

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  esInitContext()
//
//      Initialize ES utility context.  This must be called before calling any other
//      functions.
//
void ESUTIL_API esInitContext(ESContext *esContext)
{
    if (esContext != NULL)
    {
        memset(esContext, 0, sizeof(ESContext));
    }
}

///
//  esCreateWindow()
//
//      title - name for title bar of window
//      width - width of window to create
//      height - height of window to create
//      flags  - bitwise or of window creation flags
//          ES_WINDOW_ALPHA       - specifies that the framebuffer should have alpha
//          ES_WINDOW_DEPTH       - specifies that a depth buffer should be created
//          ES_WINDOW_STENCIL     - specifies that a stencil buffer should be created
//          ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
//
GLboolean ESUTIL_API esCreateWindow(ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags)
{
    if (esContext == NULL)
    {
        return GL_FALSE;
    }

    // hard-coded to fullscreen
    esContext->width = -1;
    esContext->height = -1;

    if (!CreateWindow(esContext, title, flags))
    {
        return GL_FALSE;
    }

    return GL_TRUE;
}

///
//  esMainLoop()
//
//    Start the main loop for the OpenGL ES application
//
void ESUTIL_API esMainLoop(ESContext *esContext)
{
    MainLoop(esContext);
}

///
//  esRegisterDrawFunc()
//
void ESUTIL_API esRegisterDrawFunc(ESContext *esContext, void(ESCALLBACK *drawFunc)(ESContext*))
{
    esContext->drawFunc = (void*) drawFunc;
}


///
//  esRegisterUpdateFunc()
//
void ESUTIL_API esRegisterUpdateFunc(ESContext *esContext, void(ESCALLBACK *updateFunc)(ESContext*, float))
{
    esContext->updateFunc = (void*) updateFunc;
}


///
//  esRegisterKeyFunc()
//
void ESUTIL_API esRegisterKeyFunc(ESContext *esContext, void(ESCALLBACK *keyFunc)(ESContext*, unsigned char, int, int))
{
    esContext->keyFunc = (void*) keyFunc;
}


///
// esLogMessage()
//
//    Log an error message to the debug output for the platform
//
void ESUTIL_API esLogMessage(const char *formatStr, ...)
{
    va_list params;
    char buf[BUFSIZ];

    va_start ( params, formatStr );
    //vsprintf_s ( buf, sizeof(buf),  formatStr, params );

    printf("%s", buf);

    va_end ( params );
}


///
// esLoadTGA()
//
//    Loads a 24-bit TGA image from a file
//
char* ESUTIL_API esLoadTGA(char *fileName, int *width, int *height)
{
    char *buffer;

    if (LoadTGA(fileName, &buffer, width, height))
    {
        return buffer;
    }

    return NULL;
}
