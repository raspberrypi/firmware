//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
// Additional contributions copyright (c) 2011 Research In Motion Limited

// esUtil_qnx.h
//
//   API-neutral interface for creating windows.  Implementation needs to be provided per-platform.

#ifndef ESUTIL_QNX_H_
#define ESUTIL_QNX_H_

///
//  Includes
//

#ifdef __cplusplus

extern "C" {
#endif

///
//  Public Functions
//

///
//  WinCreate()
//
//      Create window
//
GLboolean CreateWindow ( ESContext *esContext, const char *title, GLuint flags);

///
//  WinLoop()
//
//      Start main loop
//
void MainLoop ( ESContext *esContext );

///
//  LoadTGA()
//
//      TGA loader QNX implementation
//
int LoadTGA(const char *fileName, char **buffer, int *width, int *height);

#ifdef __cplusplus
}
#endif

#endif
