//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// esUtil.js
//
//    A utility library for OpenGL ES.  This library provides a
//    basic common framework for the example applications in the
//    OpenGL ES 2.0 Programming Guide.
//


// Global OpenGL context used through all of the code, assigned in 
// esInitContext
var gl;

ESContext = function()
{
    /// Put your user data here
    this.userData = null;

    /// Window width
    this.width = 0;

    /// Window height
    this.height = 0;

    /// Callbacks
    this.drawFunc = null;
    this.keyFunc = null;
    this.updateFunc = null;

    /// GL context
    this.gl = null;
}


//////////////////////////////////////////////////////////////////
//
//  Private Functions
//
//

///
//  The main callback function used by esMainLoop() called on
//  each tick to update the application
//
var lastTime = 0;
function mainLoopCallback( esContext )
{
    if ( esContext.updateFunc != null)
    {
        var curTime = new Date().getTime();
        if (lastTime != 0)
        {
            var elapsedTime = curTime - lastTime;
            esContext.updateFunc( esContext, elapsedTime );
        }
        lastTime = curTime;
    }

    if ( esContext.keyFunc != null )
    {
        // TODO: revisit this
        esContext.keyFunc( esContext );
    }

    if ( esContext.drawFunc != null )
    {
        esContext.drawFunc( esContext );
    }
    
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
function esInitContext ( esContext, canvas, contextAttributes )
{
    try
    {
        if ( contextAttributes == null)
            esContext.gl = canvas.getContext("experimental-webgl");
        else
            esContext.gl = canvas.getContext("experimental-webgl",
                                             contextAttributes );
        esContext.width = canvas.width;
        esContext.height = canvas.height;
    } catch(e) { }

    if (!esContext.gl)
    {
        alert('WebGL initialization failed.  Please make sure your browser supports WebGL.');
    }

    gl = esContext.gl;
}

///
//  esMainLoop()
//
//    Start the main loop for the OpenGL ES application
//
function esMainLoop ( esContext )
{
    setInterval ( function() { mainLoopCallback (esContext) }, 15 );
}


///
//  esRegisterDrawFunc()
//
function esRegisterDrawFunc ( esContext, drawFunc )
{
   esContext.drawFunc = drawFunc;
}


///
//  esRegisterUpdateFunc()
//
function esRegisterUpdateFunc ( esContext, updateFunc )
{
   esContext.updateFunc = updateFunc;
}


///
//  esRegisterKeyFunc()
//
function esRegisterKeyFunc ( esContext, keyFunc )
{
   esContext.keyFunc = keyFunc;
}


///
// esLogMessage()
//
//    Log an error message to the debug output for the platform
//
function esLogMessage ( msg )
{
    console.log( msg )
}


