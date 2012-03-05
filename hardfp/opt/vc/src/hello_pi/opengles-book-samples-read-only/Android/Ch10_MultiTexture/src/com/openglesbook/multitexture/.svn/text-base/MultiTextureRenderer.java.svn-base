//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// MultiTexture
//
//    This is an example that draws a quad with a basemap and
//    lightmap to demonstrate multitexturing.
//

package com.openglesbook.multitexture;

import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.openglesbook.common.ESShader;
import com.openglesbook.multitexture.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;


public class MultiTextureRenderer implements GLSurfaceView.Renderer
{

    ///
    // Constructor
    //
    public MultiTextureRenderer(Context context)
    {
        mContext = context;
        mVertices = ByteBuffer.allocateDirect(mVerticesData.length * 4)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mVertices.put(mVerticesData).position(0);
        mIndices = ByteBuffer.allocateDirect(mIndicesData.length * 2)
                .order(ByteOrder.nativeOrder()).asShortBuffer();
        mIndices.put(mIndicesData).position(0);
    }

    ///
    //  Load texture from resource
    //
    private int loadTexture ( InputStream is )
    {
        int[] textureId = new int[1];
        Bitmap bitmap;
        bitmap = BitmapFactory.decodeStream(is);
        byte[] buffer = new byte[bitmap.getWidth() * bitmap.getHeight() * 3];
        
        for ( int y = 0; y < bitmap.getHeight(); y++ )
            for ( int x = 0; x < bitmap.getWidth(); x++ )
            {
                int pixel = bitmap.getPixel(x, y);
                buffer[(y * bitmap.getWidth() + x) * 3 + 0] = (byte)((pixel >> 16) & 0xFF);
                buffer[(y * bitmap.getWidth() + x) * 3 + 1] = (byte)((pixel >> 8) & 0xFF);
                buffer[(y * bitmap.getWidth() + x) * 3 + 2] = (byte)((pixel >> 0) & 0xFF);
            }
        
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(bitmap.getWidth() * bitmap.getHeight() * 3);
        byteBuffer.put(buffer).position(0);
            
        GLES20.glGenTextures ( 1, textureId, 0 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, textureId[0] );

        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGB, bitmap.getWidth(), bitmap.getHeight(), 0, 
                              GLES20.GL_RGB, GLES20.GL_UNSIGNED_BYTE, byteBuffer );
    
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR );
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR );
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE );
        GLES20.glTexParameteri ( GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE );
        
        return textureId[0];
    }
 
 
    ///
    // Initialize the shader and program object
    //
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config)
    {
        String vShaderStr =
             "attribute vec4 a_position;   \n" +
             "attribute vec2 a_texCoord;   \n" +
             "varying vec2 v_texCoord;     \n" +
             "void main()                  \n" +
             "{                            \n" +
             "   gl_Position = a_position; \n" +
             "   v_texCoord = a_texCoord;  \n" +
             "}                            \n";

        String fShaderStr =
            "precision mediump float;                            \n" +
            "varying vec2 v_texCoord;                            \n" +
            "uniform sampler2D s_baseMap;                        \n" +
            "uniform sampler2D s_lightMap;                       \n" +
            "void main()                                         \n" +
            "{                                                   \n" +
            "  vec4 baseColor;                                   \n" +
            "  vec4 lightColor;                                  \n" +
            "                                                    \n" +
            "  baseColor = texture2D( s_baseMap, v_texCoord );   \n" +
            "  lightColor = texture2D( s_lightMap, v_texCoord ); \n" +
            "  gl_FragColor = baseColor * (lightColor + 0.25);   \n" +
            "}                                                   \n";                                                 
                
        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_position");
        mTexCoordLoc = GLES20.glGetAttribLocation(mProgramObject, "a_texCoord" );
        
        // Get the sampler locations
        mBaseMapLoc = GLES20.glGetUniformLocation ( mProgramObject, "s_baseMap" );
        mLightMapLoc = GLES20.glGetUniformLocation ( mProgramObject, "s_lightMap" );

        // Load the texture
        mBaseMapTexId = loadTexture(mContext.getResources().openRawResource(R.raw.basemap));
        mLightMapTexId = loadTexture(mContext.getResources().openRawResource(R.raw.lightmap));

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


        // Bind the base map
        GLES20.glActiveTexture ( GLES20.GL_TEXTURE0 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, mBaseMapTexId );

        // Set the base map sampler to texture unit to 0
        GLES20.glUniform1i ( mBaseMapLoc, 0 );

        // Bind the light map
        GLES20.glActiveTexture ( GLES20.GL_TEXTURE1 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, mLightMapTexId );
        
        // Set the light map sampler to texture unit 1
        GLES20.glUniform1i ( mLightMapLoc, 1 );

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
    private int mBaseMapLoc;
    private int mLightMapLoc;
    
    // Texture handle
    private int mBaseMapTexId;
    private int mLightMapTexId;
    
    // Additional member variables
    private int mWidth;
    private int mHeight;
    private FloatBuffer mVertices;
    private ShortBuffer mIndices;
    private Context mContext;
    
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
