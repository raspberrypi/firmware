//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Simple_Texture2D
//
//    This is a simple example that draws a quad with a 2D
//    texture image. The purpose of this example is to demonstrate 
//    the basics of 2D texturing
//

package com.openglesbook.simpletexture2d;

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

public class SimpleTexture2DRenderer implements GLSurfaceView.Renderer
{

    ///
    // Constructor
    //
    public SimpleTexture2DRenderer(Context context)
    {
        
        mVertices = ByteBuffer.allocateDirect(mVerticesData.length * 4)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mVertices.put(mVerticesData).position(0);
        mIndices = ByteBuffer.allocateDirect(mIndicesData.length * 2)
                .order(ByteOrder.nativeOrder()).asShortBuffer();
        mIndices.put(mIndicesData).position(0);
    }

    //
    // Create a simple 2x2 texture image with four different colors
    //
    private int createSimpleTexture2D( )
    {
        // Texture object handle
        int[] textureId = new int[1];
        
        // 2x2 Image, 3 bytes per pixel (R, G, B)
        byte[] pixels = 
            {  
                127,   0,   0, // Red
                0, 127,   0, // Green
                0,   0, 127, // Blue
                127, 127,   0  // Yellow
            };
        ByteBuffer pixelBuffer = ByteBuffer.allocateDirect(4*3);
        pixelBuffer.put(pixels).position(0);

        // Use tightly packed data
        GLES20.glPixelStorei ( GLES20.GL_UNPACK_ALIGNMENT, 1 );

        //  Generate a texture object
        GLES20.glGenTextures ( 1, textureId, 0 );

        // Bind the texture object
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, textureId[0] );

        //  Load the texture
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGB, 2, 2, 0, GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, pixelBuffer );

        // Set the filtering mode
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST );
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST );

        return textureId[0];        
    }
 
    ///
    // Initialize the shader and program object
    //
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config)
    {
        String vShaderStr =
                  "attribute vec4 a_position;   \n"
                + "attribute vec2 a_texCoord;   \n"
                + "varying vec2 v_texCoord;     \n"
                + "void main()                  \n"
                + "{                            \n"
                + "   gl_Position = a_position; \n"
                + "   v_texCoord = a_texCoord;  \n"
                + "}                            \n";

        String fShaderStr = 
                  "precision mediump float;                            \n"
                + "varying vec2 v_texCoord;                            \n"
                + "uniform sampler2D s_texture;                        \n"
                + "void main()                                         \n"
                + "{                                                   \n"
                + "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
                + "}                                                   \n";

        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_position");
        mTexCoordLoc = GLES20.glGetAttribLocation(mProgramObject, "a_texCoord" );
        
        // Get the sampler location
        mSamplerLoc = GLES20.glGetUniformLocation ( mProgramObject, "s_texture" );

        // Load the texture
        mTextureId = createSimpleTexture2D ();

        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    // /
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    public void onDrawFrame(GL10 glUnused)
    {
        // Set the viewport
        GLES20.glViewport(0, 0, mWidth, mHeight);

        // Clear the color buffer
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        // Use the program object
        GLES20.glUseProgram(mProgramObject);

        // Load the vertex position
        mVertices.position(0);
        GLES20.glVertexAttribPointer ( mPositionLoc, 3, GLES20.GL_FLOAT, 
                                       false, 
                                       5 * 4, mVertices );
        // Load the texture coordinate
        mVertices.position(3);
        GLES20.glVertexAttribPointer ( mTexCoordLoc, 2, GLES20.GL_FLOAT,
                                       false, 
                                       5 * 4, 
                                       mVertices );

        GLES20.glEnableVertexAttribArray ( mPositionLoc );
        GLES20.glEnableVertexAttribArray ( mTexCoordLoc );

        // Bind the texture
        GLES20.glActiveTexture ( GLES20.GL_TEXTURE0 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, mTextureId );

        // Set the sampler texture unit to 0
        GLES20.glUniform1i ( mSamplerLoc, 0 );

        GLES20.glDrawElements ( GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, mIndices );
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
    private int mTexCoordLoc;
    
    // Sampler location
    private int mSamplerLoc;
    
    // Texture handle
    private int mTextureId;
    
    // Additional member variables
    private int mWidth;
    private int mHeight;
    private FloatBuffer mVertices;
    private ShortBuffer mIndices;
    
    private final float[] mVerticesData =
    { 
            -0.5f, 0.5f, 0.0f, // Position 0
            0.0f, 0.0f, // TexCoord 0
            -0.5f, -0.5f, 0.0f, // Position 1
            0.0f, 1.0f, // TexCoord 1
            0.5f, -0.5f, 0.0f, // Position 2
            1.0f, 1.0f, // TexCoord 2
            0.5f, 0.5f, 0.0f, // Position 3
            1.0f, 0.0f // TexCoord 3
    };

    private final short[] mIndicesData =
    { 
            0, 1, 2, 0, 2, 3 
    };
    
}
