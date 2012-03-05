//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Stencil_Test
//
//    This example shows various stencil buffer
//    operations.
//

package com.openglesbook.stenciltest;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.openglesbook.common.ESShader;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;


public class StencilTestRenderer implements GLSurfaceView.Renderer
{

    ///
    // Constructor
    //
    public StencilTestRenderer(Context context)
    {
        mVertices = ByteBuffer.allocateDirect(mVerticesData.length * 4)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mVertices.put(mVerticesData).position(0);
        mIndices = ByteBuffer.allocateDirect(mIndicesData.length * 2)
                .order(ByteOrder.nativeOrder()).asShortBuffer();
        mIndices.put(mIndicesData).position(0);
    } 
 
    ///
    // Initialize the shader and program object
    //
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config)
    {
        String vShaderStr =
            "attribute vec4 a_position;   \n" +
            "void main()                  \n" +
            "{                            \n" +
            "   gl_Position = a_position; \n" +
            "}                            \n";
        
        String fShaderStr =
            "precision mediump float;  \n" +
            "uniform vec4  u_color;    \n" +
            "void main()               \n" +
            "{                         \n" +
            "  gl_FragColor = u_color; \n" +
            "}                         \n";
                                             
                
        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_position");
        
        // Get the sampler location
        mColorLoc = GLES20.glGetUniformLocation ( mProgramObject, "u_color" );

        // Set the clear color
        GLES20.glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
        
        // Set the stencil clear value
        GLES20.glClearStencil ( 0x1 );

        // Set the depth clear value
        GLES20.glClearDepthf( 0.75f );

        // Enable the depth and stencil tests
        GLES20.glEnable( GLES20.GL_DEPTH_TEST );
        GLES20.glEnable( GLES20.GL_STENCIL_TEST );

        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    // /
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    public void onDrawFrame(GL10 glUnused)
    {
        float[][]  colors = { 
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f, 0.0f }
        };

        int[]  numStencilBits = new int[1];
        int[]  stencilValues = { 
           0x7, // Result of test 0
           0x0, // Result of test 1
           0x2, // Result of test 2
           0xff // Result of test 3.  We need to fill this
                //  value in a run-time
        };

        // Set the viewport
        GLES20.glViewport ( 0, 0, mWidth, mHeight );
        
        // Clear the color, depth, and stencil buffers.  At this
        //   point, the stencil buffer will be 0x1 for all pixels
        GLES20.glClear ( GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_STENCIL_BUFFER_BIT );

        // Use the program object
        GLES20.glUseProgram ( mProgramObject );

        // Load the vertex position
        GLES20.glVertexAttribPointer ( mPositionLoc, 3, GLES20.GL_FLOAT, 
                                       false, 0, mVertices );
       
        GLES20.glEnableVertexAttribArray ( mPositionLoc );

        // Test 0:
        //
        // Initialize upper-left region.  In this case, the
        //   stencil-buffer values will be replaced because the
        //   stencil test for the rendered pixels will fail the
        //   stencil test, which is
        //
        //        ref   mask   stencil  mask
        //      ( 0x7 & 0x3 ) < ( 0x1 & 0x7 )
        //
        //   The value in the stencil buffer for these pixels will
        //   be 0x7.
        //
        GLES20.glStencilFunc( GLES20.GL_LESS, 0x7, 0x3 );
        GLES20.glStencilOp( GLES20.GL_REPLACE, GLES20.GL_DECR, GLES20.GL_DECR );
        mIndices.position(0);
        GLES20.glDrawElements( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices);
      
        // Test 1:
        //
        // Initialize the upper-right region.  Here, we'll decrement
        //   the stencil-buffer values where the stencil test passes
        //   but the depth test fails.  The stencil test is
        //
        //        ref  mask    stencil  mask
        //      ( 0x3 & 0x3 ) > ( 0x1 & 0x3 )
        //
        //    but where the geometry fails the depth test.  The
        //    stencil values for these pixels will be 0x0.
        //
        GLES20.glStencilFunc( GLES20.GL_GREATER, 0x3, 0x3 );
        GLES20.glStencilOp( GLES20.GL_KEEP, GLES20.GL_DECR, GLES20.GL_KEEP );
        mIndices.position(6);
        GLES20.glDrawElements( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices );

        // Test 2:
        //
        // Initialize the lower-left region.  Here we'll increment 
        //   (with saturation) the stencil value where both the
        //   stencil and depth tests pass.  The stencil test for
        //   these pixels will be
        //
        //        ref  mask     stencil  mask
        //      ( 0x1 & 0x3 ) == ( 0x1 & 0x3 )
        //
        //   The stencil values for these pixels will be 0x2.
        //
        GLES20.glStencilFunc( GLES20.GL_EQUAL, 0x1, 0x3 );
        GLES20.glStencilOp( GLES20.GL_KEEP, GLES20.GL_INCR, GLES20.GL_INCR );
        mIndices.position(12);
        GLES20.glDrawElements( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices );

        // Test 3:
        //
        // Finally, initialize the lower-right region.  We'll invert
        //   the stencil value where the stencil tests fails.  The
        //   stencil test for these pixels will be
        //
        //        ref   mask    stencil  mask
        //      ( 0x2 & 0x1 ) == ( 0x1 & 0x1 )
        //
        //   The stencil value here will be set to ~((2^s-1) & 0x1),
        //   (with the 0x1 being from the stencil clear value),
        //   where 's' is the number of bits in the stencil buffer
        //
        GLES20.glStencilFunc( GLES20.GL_EQUAL, 0x2, 0x1 );
        GLES20.glStencilOp( GLES20.GL_INVERT, GLES20.GL_KEEP, GLES20.GL_KEEP );
        mIndices.position(18);
        GLES20.glDrawElements( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices );
        
        // Since we don't know at compile time how many stecil bits are present,
        //   we'll query, and update the value correct value in the
        //   stencilValues arrays for the fourth tests.  We'll use this value
        //   later in rendering.
        
        GLES20.glGetIntegerv( GLES20.GL_STENCIL_BITS, numStencilBits, 0 );
        
        stencilValues[3] = ~(((1 << numStencilBits[0]) - 1) & 0x1) & 0xff;

        // Use the stencil buffer for controlling where rendering will
        //   occur.  We diable writing to the stencil buffer so we
        //   can test against them without modifying the values we
        //   generated.
        GLES20.glStencilMask( 0x0 );
        
        for ( int i = 0; i < 4; ++i )
        {
            GLES20.glStencilFunc( GLES20.GL_EQUAL, stencilValues[i], 0xff );
            GLES20.glUniform4f( mColorLoc, colors[i][0], colors[i][1], colors[i][2], colors[i][3]);
            mIndices.position(24);
            GLES20.glDrawElements( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices );
        }
    }

    ///
    // Handle surface changes
    //
    public void onSurfaceChanged(GL10 glUnused, int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

    
    // Handle to a program object
    private int mProgramObject;
    
    // Attribute locations
    private int mPositionLoc;
    
    // Uniform location
    private int mColorLoc;
    
    // Additional member variables
    private int mWidth;
    private int mHeight;
    private FloatBuffer mVertices;
    private ShortBuffer mIndices;
    
    private final float[] mVerticesData =
    { 
            -0.75f,  0.25f,  0.50f, // Quad #0
            -0.25f,  0.25f,  0.50f,
            -0.25f,  0.75f,  0.50f,
            -0.75f,  0.75f,  0.50f,
             0.25f,  0.25f,  0.90f, // Quad #1
             0.75f,  0.25f,  0.90f,
             0.75f,  0.75f,  0.90f,
             0.25f,  0.75f,  0.90f,
            -0.75f, -0.75f,  0.50f, // Quad #2
            -0.25f, -0.75f,  0.50f,
            -0.25f, -0.25f,  0.50f,
            -0.75f, -0.25f,  0.50f,
             0.25f, -0.75f,  0.50f, // Quad #3
             0.75f, -0.75f,  0.50f,
             0.75f, -0.25f,  0.50f,
             0.25f, -0.25f,  0.50f,
            -1.00f, -1.00f,  0.00f, // Big Quad
             1.00f, -1.00f,  0.00f,
             1.00f,  1.00f,  0.00f,
            -1.00f,  1.00f,  0.00f
    };

    private final short[] mIndicesData =
    { 
            0,  1,  2,  0,  2,  3,  // Quad #0
            4,  5,  6,  4,  6,  7,  // Quad #1
            8,  9, 10,  8, 10, 11,  // Quad #2
            12, 13, 14, 12, 14, 15, // Quad #3
            16, 17, 18, 16, 18, 19  // Big Quad
    };
    
}
