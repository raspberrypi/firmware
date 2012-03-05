//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// MipMap2D
//
//    This is a simple example that demonstrates generating a mipmap chain
//    and rendering with it
//

package com.openglesbook.simpletexturecubemap;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.openglesbook.common.ESShader;
import com.openglesbook.common.ESShapes;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

public class SimpleTextureCubemapRenderer implements GLSurfaceView.Renderer
{
    ///
    // Constructor
    //
    public SimpleTextureCubemapRenderer(Context context)
    {
    }
    
    ///
    // Create a simple cubemap with a 1x1 face with a different
    // color for each face
    private int createSimpleTextureCubemap( )
    {
        int[] textureId = new int[1];

        // Face 0 - Red        
        byte[] cubePixels0 = { 127, 0, 0 };
        // Face 1 - Green
        byte[] cubePixels1 = { 0, 127, 0 }; 
        // Face 2 - Blue
        byte[] cubePixels2 = { 0, 0, 127 };
        // Face 3 - Yellow
        byte[] cubePixels3 = { 127, 127, 0 };
        // Face 4 - Purple
        byte[] cubePixels4 = { 127, 0, 127 };
        // Face 5 - White
        byte[] cubePixels5 = { 127, 127, 127 };
                
        ByteBuffer cubePixels = ByteBuffer.allocateDirect(3);
    
        // Generate a texture object
        GLES20.glGenTextures ( 1, textureId, 0 );

        // Bind the texture object
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_CUBE_MAP, textureId[0] );
    
        // Load the cube face - Positive X
        cubePixels.put(cubePixels0).position(0);
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Load the cube face - Negative X
        cubePixels.put(cubePixels1).position(0);
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Load the cube face - Positive Y
        cubePixels.put(cubePixels2).position(0);        
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Load the cube face - Negative Y
        cubePixels.put(cubePixels3).position(0);
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Load the cube face - Positive Z
        cubePixels.put(cubePixels4).position(0);        
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Load the cube face - Negative Z
        cubePixels.put(cubePixels5).position(0);
        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GLES20.GL_RGB, 1, 1, 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, cubePixels );

        // Set the filtering mode
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_CUBE_MAP, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST );
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_CUBE_MAP, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST );

        return textureId[0];
    }

    ///
    // Initialize the shader and program object
    //
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config)
    {
        String vShaderStr =
            "attribute vec4 a_position;   \n" +
            "attribute vec3 a_normal;     \n" +
            "varying vec3 v_normal;       \n" +
            "void main()                  \n" +
            "{                            \n" +
            "   gl_Position = a_position; \n" +
            "   v_normal = a_normal;      \n" +
            "}                            \n";

        String fShaderStr = 
            "precision mediump float;                            \n" +
            "varying vec3 v_normal;                              \n" +
            "uniform samplerCube s_texture;                      \n" +
            "void main()                                         \n" +
            "{                                                   \n" +
            "  gl_FragColor = textureCube( s_texture, v_normal );\n" +
            "}                                                   \n";

        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_position");
        mNormalLoc = GLES20.glGetAttribLocation(mProgramObject, "a_normal" );
        
        // Get the sampler location
        mSamplerLoc = GLES20.glGetUniformLocation ( mProgramObject, "s_texture" );

        // Load the texture
        mTextureId = createSimpleTextureCubemap ();
        
        // Generate the vertex data
        mSphere.genSphere( 20, 0.75f );
        
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    ///
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    public void onDrawFrame(GL10 glUnused)
    {
        // Set the viewport
        GLES20.glViewport(0, 0, mWidth, mHeight);

        // Clear the color buffer
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        
        GLES20.glCullFace(GLES20.GL_BACK);
        GLES20.glEnable(GLES20.GL_CULL_FACE);

        // Use the program object
        GLES20.glUseProgram(mProgramObject);

        // Load the vertex position        
        GLES20.glVertexAttribPointer ( mPositionLoc, 3, GLES20.GL_FLOAT, 
                                       false, 0, mSphere.getVertices());
        // Load the texture coordinate
        
        GLES20.glVertexAttribPointer ( mNormalLoc, 3, GLES20.GL_FLOAT,
                                       false, 0, mSphere.getNormals());
        
        GLES20.glEnableVertexAttribArray(mPositionLoc);
        GLES20.glEnableVertexAttribArray(mNormalLoc);

        // Bind the texture
        GLES20.glActiveTexture ( GLES20.GL_TEXTURE0 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_CUBE_MAP, mTextureId );

        // Set the sampler texture unit to 0
        GLES20.glUniform1i ( mSamplerLoc, 0 );

        GLES20.glDrawElements ( GLES20.GL_TRIANGLES, mSphere.getNumIndices(), GLES20.GL_UNSIGNED_SHORT, mSphere.getIndices() );
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
    private int mNormalLoc;
    
    // Sampler location
    private int mSamplerLoc;
        
    // Texture ID
    private int mTextureId;
    
    // Vertex data
    private ESShapes mSphere = new ESShapes();

    // Additional member variables
    private int mWidth;
    private int mHeight;
}
