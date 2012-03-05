//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// esUtil_qnx.c
//
//    This file contains the QNX implementation of the windowing functions.
//

#include <assert.h>
#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "esUtil.h"
#include "esUtil_qnx.h"

#define WINDOW_VSYNC 1

//////////////////////////////////////////////////////////////////
//
// Globals
//

// QNX global data
struct
{
    screen_context_t screenContext;
    screen_window_t screenWindow;
    screen_event_t screenEvent;
    int screenWindowSize[2];
    const char* glExtensions;
}__qnx;

// Time global variables
struct
{
    int elapsed;
    int last;
    int start;
    int total;
}__time;

//////////////////////////////////////////////////////////////////
//
//  Private Functions
//
//
static EGLenum checkErrorEGL(const char* msg)
{
    static const char* errmsg[] =
    {
        "EGL function succeeded",
        "EGL is not initialized, or could not be initialized, for the specified display",
        "EGL cannot access a requested resource",
        "EGL failed to allocate resources for the requested operation",
        "EGL fail to access an unrecognized attribute or attribute value was passed in an attribute list",
        "EGLConfig argument does not name a valid EGLConfig",
        "EGLContext argument does not name a valid EGLContext",
        "EGL current surface of the calling thread is no longer valid",
        "EGLDisplay argument does not name a valid EGLDisplay",
        "EGL arguments are inconsistent",
        "EGLNativePixmapType argument does not refer to a valid native pixmap",
        "EGLNativeWindowType argument does not refer to a valid native window",
        "EGL one or more argument values are invalid",
        "EGLSurface argument does not name a valid surface configured for rendering",
        "EGL power management event has occurred",
    };
    EGLenum error = eglGetError();
    fprintf(stderr, "%s: %s\n", msg, errmsg[error - EGL_SUCCESS]);
    return error;
}

// Creates QNX window and initializes EGL stuff
static GLboolean qnxCreate(ESContext *esContext, GLuint flags)
{
    int rc = 0;
    int screenFormat = SCREEN_FORMAT_RGBA8888;
    int screenUsage = SCREEN_USAGE_OPENGL_ES2;
    int screenSwapInterval = 1;
    int screenTransparency = SCREEN_TRANSPARENCY_NONE;
    EGLConfig __eglConfig = 0;

    // hard-coded to (0,0)
    int windowPosition[] = { 0, 0 };

    EGLint eglConfigCount;

    // hard-coded to 32-bit/OpenGL ES 2.0
    const EGLint eglConfigAttrs[] =
    {
        EGL_RED_SIZE,           8,
        EGL_GREEN_SIZE,         8,
        EGL_BLUE_SIZE,          8,
        EGL_ALPHA_SIZE,         (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE,         (flags & ES_WINDOW_DEPTH) ? 24 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE,       (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
        EGL_SAMPLE_BUFFERS,     (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    const EGLint eglContextAttrs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    const EGLint eglSurfaceAttrs[] =
    {
        EGL_RENDER_BUFFER,  EGL_BACK_BUFFER,
        EGL_NONE
    };

    // Create the screen context
    rc = screen_create_context(&__qnx.screenContext, 0);
    if (rc)
    {
        perror("screen_create_context");
        return GL_FALSE;
    }

    // Create the screen window
    rc = screen_create_window(&__qnx.screenWindow, __qnx.screenContext);
    if (rc)
    {
        perror("screen_create_window");
        return GL_FALSE;
    }

    // Set/Get any window prooperties.
    rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_FORMAT, &screenFormat);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
        return GL_FALSE;
    }

    rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_USAGE, &screenUsage);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
        return GL_FALSE;
    }

    if (esContext->width > 0 && esContext->height > 0)
    {
        rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_SIZE, __qnx.screenWindowSize);
        if (rc)
        {
            perror("screen_set_window_property_iv(SCREEN_PROPERTY_SIZE)");
            return GL_FALSE;
        }
    }
    else
    {
        rc = screen_get_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_SIZE, __qnx.screenWindowSize);
        if (rc)
        {
            perror("screen_get_window_property_iv(SCREEN_PROPERTY_SIZE)");
            return GL_FALSE;
        }
    }

    if (windowPosition[0] != 0 || windowPosition[1] != 0)
    {
        rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_POSITION, windowPosition);
        if (rc)
        {
            perror("screen_set_window_property_iv(SCREEN_PROPERTY_POSITION)");
            return GL_FALSE;
        }
    }

    rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_TRANSPARENCY, &screenTransparency);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_TRANSPARENCY)");
        return GL_FALSE;
    }

    rc = screen_set_window_property_iv(__qnx.screenWindow, SCREEN_PROPERTY_SWAP_INTERVAL, &screenSwapInterval);
    if (rc)
    {
        perror("screen_set_window_property_iv(SCREEN_PROPERTY_SWAP_INTERVAL)");
        return GL_FALSE;
    }

    // Double buffered.
    rc = screen_create_window_buffers(__qnx.screenWindow, 2);
    if (rc)
    {
        perror("screen_create_window_buffers");
        return GL_FALSE;
    }

    // Create screen event object
    rc = screen_create_event(&__qnx.screenEvent);
    if (rc)
    {
        perror("screen_create_event");
        return GL_FALSE;
    }

    // Get the EGL display and initialize
    esContext->eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (esContext->eglDisplay == EGL_NO_DISPLAY)
    {
        perror("eglGetDisplay");
        return GL_FALSE;
    }
    if (eglInitialize(esContext->eglDisplay, NULL, NULL) != EGL_TRUE)
    {
        perror("eglInitialize");
        return GL_FALSE;
    }

    if (eglChooseConfig(esContext->eglDisplay, eglConfigAttrs, &__eglConfig, 1, &eglConfigCount) != EGL_TRUE || eglConfigCount == 0)
    {
        checkErrorEGL("eglChooseConfig");
        return GL_FALSE;
    }

    esContext->eglContext = eglCreateContext(esContext->eglDisplay, __eglConfig, EGL_NO_CONTEXT, eglContextAttrs);
    if (esContext->eglContext == EGL_NO_CONTEXT)
    {
        checkErrorEGL("eglCreateContext");
        return GL_FALSE;
    }

    esContext->eglSurface = eglCreateWindowSurface(esContext->eglDisplay, __eglConfig, __qnx.screenWindow, eglSurfaceAttrs);
    if (esContext->eglSurface == EGL_NO_SURFACE)
    {
        checkErrorEGL("eglCreateWindowSurface");
        return GL_FALSE;
    }

    if (eglMakeCurrent(esContext->eglDisplay, esContext->eglSurface, esContext->eglSurface, esContext->eglContext) != EGL_TRUE)
    {
        checkErrorEGL("eglMakeCurrent");
        return GL_FALSE;
    }

    // Use vsync
    if (WINDOW_VSYNC)
        eglSwapInterval(esContext->eglDisplay, 1);

    // Initialize OpenGL ES extensions
    __qnx.glExtensions = (const char*)glGetString(GL_EXTENSIONS);
    if (strstr(__qnx.glExtensions, "GL_OES_vertex_array_object") || strstr(__qnx.glExtensions, "GL_ARB_vertex_array_object"))
    {
        //glBindVertexArray = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
        //glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glBindVertexArrayOES");
        //glGenVertexArrays = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
        //glIsVertexArray = (PFNGLISVERTEXARRAYOESPROC)eglGetProcAddress("glIsVertexArrayOES");
    }
    return GL_TRUE;
}

static void handleScreenEvent(bps_event_t *event)
{
    screen_event_t screen_event = screen_event_get_event(event);

    int screen_val;
    screen_get_event_property_iv(screen_event, SCREEN_PROPERTY_TYPE, &screen_val);

    switch (screen_val)
    {
    case SCREEN_EVENT_MTOUCH_TOUCH:
    case SCREEN_EVENT_MTOUCH_MOVE:
    case SCREEN_EVENT_MTOUCH_RELEASE:
        break;
    }
}

static void handleNavigatorEvent(bps_event_t *event)
{
	switch (bps_event_get_code(event))
	{
	case NAVIGATOR_SWIPE_DOWN:
		break;
	case NAVIGATOR_EXIT:
		break;
	}
}

static void handle_events()
{
	int screen_domain = screen_get_domain();
	int navigator_domain = navigator_get_domain();

	int rc;

	//Request and process available BPS events
	for (;;)
	{
		bps_event_t *event = NULL;
		rc = bps_get_event(&event, 0);
		assert(rc == BPS_SUCCESS);

		if (event)
		{
			int domain = bps_event_get_domain(event);

			if (domain == screen_domain)
			{
				handleScreenEvent(event);
			}
			else if (domain == navigator_domain)
			{
				handleNavigatorEvent(event);
			}
		}
		else
		{
			//No more events in the queue
			break;
		}
	}
}

static void terminateGraphics(ESContext *esContext)
{
    //Typical egl cleanup
    eglMakeCurrent(esContext->eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(esContext->eglDisplay, esContext->eglSurface);
    screen_destroy_window(esContext->screen_win);
    eglDestroyContext(esContext->eglDisplay, esContext->eglContext);
    eglTerminate(esContext->eglDisplay);
    eglReleaseThread();
}

static long initTime()
{
    struct timespec n;
    clock_gettime(CLOCK_REALTIME, &n);
    return __time.start = __time.last = n.tv_sec * 1000 + n.tv_nsec / 1000000;
}

static long getElapsedTime()
{
    struct timespec n;
    clock_gettime(CLOCK_REALTIME, &n);
    long nowt = n.tv_sec * 1000 + n.tv_nsec / 1000000;

    __time.elapsed = nowt - __time.last;
    __time.last = nowt;

    __time.total += __time.elapsed;
    return __time.elapsed;
}

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  CreateWindow()
//
//      Create the window
//
GLboolean CreateWindow(ESContext *esContext, const char *title, GLuint flags)
{
    qnxCreate(esContext, flags);
    bps_initialize();
    screen_request_events(__qnx.screenContext);

    initTime();

    // Query the width and height
    eglQuerySurface(esContext->eglDisplay, esContext->eglSurface, EGL_WIDTH, &esContext->width);
    eglQuerySurface(esContext->eglDisplay, esContext->eglSurface, EGL_HEIGHT, &esContext->height);

    return GL_TRUE;
}

///
//  MainLoop()
//
//      Start the main loop
//
void MainLoop(ESContext *esContext)
{
    for (;;)
    {
    	handle_events();
        // Call update function if registered
        if (esContext->updateFunc != NULL)
            esContext->updateFunc(esContext, getElapsedTime() / 1000.0f);
        if (esContext && esContext->drawFunc)
            esContext->drawFunc(esContext);
    }

    screen_stop_events((screen_context_t) esContext->screen_context);

    terminateGraphics(esContext);

    bps_shutdown();

    screen_destroy_context((screen_context_t) esContext->screen_context);
}
