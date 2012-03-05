
//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// esShader.js
//
//    Utility functions for loading shaders and creating program objects.
//

//////////////////////////////////////////////////////////////////
//
//  Private Functions
//
//



//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

//
///
/// \brief Load a shader, check for compile errors, print error messages to output log
/// \param type Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
/// \param shaderSrc Shader source string
/// \return A new shader object on success, 0 on failure
//
function esLoadShader ( type, shaderSrc )
{
   var shader;
   var compiled;

   // Create the shader object
   shader = gl.createShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   gl.shaderSource ( shader, shaderSrc );

   // Compile the shader
   gl.compileShader ( shader );

   // Check the compile status
   compiled = gl.getShaderParameter ( shader, gl.COMPILE_STATUS );

   if ( !compiled )
   {
       alert( gl.getShaderInfoLog( shader ));
       gl.deleteShader( shader );
       return 0;
   }

   return shader;

}


//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
function esLoadProgram ( vertShaderSrc, fragShaderSrc )
{
   var vertexShader;
   var fragmentShader;
   var programObject;
   var linked;

   // Load the vertex/fragment shaders
   vertexShader = esLoadShader ( gl.VERTEX_SHADER, vertShaderSrc );
   if ( vertexShader == 0 )
      return 0;

   fragmentShader = esLoadShader ( gl.FRAGMENT_SHADER, fragShaderSrc );
   if ( fragmentShader == 0 )
   {
      gl.deleteShader( vertexShader );
      return 0;
   }

   // Create the program object
   programObject = gl.createProgram ( );

   if ( programObject == 0 )
      return 0;

   gl.attachShader ( programObject, vertexShader );
   gl.attachShader ( programObject, fragmentShader );

   // Link the program
   gl.linkProgram ( programObject );

   // Check the link status
   linked = gl.getProgramParameter ( programObject, gl.LINK_STATUS );

   if ( !linked )
   {
       alert( gl.getProgramInfoLog ( programObject ) );
       gl.deleteProgram ( programObject );
       return 0;
   }

   // Free up no longer needed shader resources
   gl.deleteShader ( vertexShader );
   gl.deleteShader ( fragmentShader );

   return programObject;
}

