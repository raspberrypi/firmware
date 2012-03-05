//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// ParticleSystem
//
//    This is an example that demonstrates rendering a particle system
//    using a vertex shader and point sprites.
//

package com.openglesbook.particlesystem;

import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.Random;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.openglesbook.common.ESShader;
import com.openglesbook.particlesystem.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;


public class ParticleSystemRenderer implements GLSurfaceView.Renderer
{

    ///
    // Constructor
    //
    public ParticleSystemRenderer(Context context)
    {
        mContext = context;
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
            "uniform float u_time;                                \n" +
            "uniform vec3 u_centerPosition;                       \n" +
            "attribute float a_lifetime;                          \n" +
            "attribute vec3 a_startPosition;                      \n" +
            "attribute vec3 a_endPosition;                        \n" +
            "varying float v_lifetime;                            \n" +
            "void main()                                          \n" +
            "{                                                    \n" +
            "  if ( u_time <= a_lifetime )                        \n" +
            "  {                                                  \n" +
            "    gl_Position.xyz = a_startPosition +              \n" +
            "                      (u_time * a_endPosition);      \n" +
            "    gl_Position.xyz += u_centerPosition;             \n" +
            "    gl_Position.w = 1.0;                             \n" +
            "  }                                                  \n" +
            "  else                                               \n" +
            "     gl_Position = vec4( -1000, -1000, 0, 0 );       \n" +
            "  v_lifetime = 1.0 - ( u_time / a_lifetime );        \n" +
            "  v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );       \n" +
            "  gl_PointSize = ( v_lifetime * v_lifetime ) * 40.0; \n" +
            "}";


        String fShaderStr =
            "precision mediump float;                             \n" +
            "uniform vec4 u_color;                                \n" +
            "varying float v_lifetime;                            \n" +
            "uniform sampler2D s_texture;                         \n" +
            "void main()                                          \n" +
            "{                                                    \n" +
            "  vec4 texColor;                                     \n" +
            "  texColor = texture2D( s_texture, gl_PointCoord );  \n" +
            "  gl_FragColor = vec4( u_color ) * texColor;         \n" +
            "  gl_FragColor.a *= v_lifetime;                      \n" +
            "}                                                    \n";
                
        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mLifetimeLoc = GLES20.glGetAttribLocation(mProgramObject, "a_lifetime");
        mStartPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_startPosition" );
        mEndPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_endPosition" );
        
        // Get the uniform locations
        mTimeLoc = GLES20.glGetUniformLocation ( mProgramObject, "u_time" );
        mCenterPositionLoc = GLES20.glGetUniformLocation ( mProgramObject, "u_centerPosition" );
        mColorLoc = GLES20.glGetUniformLocation ( mProgramObject, "u_color" );
        mSamplerLoc = GLES20.glGetUniformLocation ( mProgramObject, "s_texture" );

        GLES20.glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

        // Fill in particle data array
        Random generator = new Random();
        
        for ( int i = 0; i < NUM_PARTICLES; i++ )
        {        
           // Lifetime of particle
           mParticleData[i * 7 + 0] = generator.nextFloat();

           // End position of particle
           mParticleData[i * 7 + 1] = generator.nextFloat() * 2.0f - 1.0f;
           mParticleData[i * 7 + 2] = generator.nextFloat() * 2.0f - 1.0f;
           mParticleData[i * 7 + 3] = generator.nextFloat() * 2.0f - 1.0f;
           
           // Start position of particle
           mParticleData[i * 7 + 4] = generator.nextFloat() * 0.25f - 0.125f;
           mParticleData[i * 7 + 5] = generator.nextFloat() * 0.25f - 0.125f;
           mParticleData[i * 7 + 6] = generator.nextFloat() * 0.25f - 0.125f;                   
        }
        mParticles = ByteBuffer.allocateDirect(mParticleData.length * 4)
            .order(ByteOrder.nativeOrder()).asFloatBuffer();
        mParticles.put(mParticleData).position(0);        

        // Initialize time to cause reset on first update
        mTime = 1.0f;

        // Load particle texture
        mTextureId = loadTexture ( mContext.getResources().openRawResource( R.raw.smoke ) );              
    }

    private void update()
    {
        if (mLastTime == 0)
            mLastTime = SystemClock.uptimeMillis();
        long curTime = SystemClock.uptimeMillis();
        long elapsedTime = curTime - mLastTime;
        float deltaTime = elapsedTime / 1000.0f;
        mLastTime = curTime;
        
        mTime += deltaTime;

        if ( mTime >= 1.0f )
        {
            Random generator = new Random();
            float[] centerPos = new float[3];
            float[] color = new float[4];

            mTime = 0.0f;

            // Pick a new start location and color
            centerPos[0] = generator.nextFloat() * 1.0f - 0.5f;
            centerPos[1] = generator.nextFloat() * 1.0f - 0.5f;
            centerPos[2] = generator.nextFloat() * 1.0f - 0.5f;
           
            GLES20.glUniform3f ( mCenterPositionLoc, centerPos[0], centerPos[1], centerPos[2]);

            // Random color
            color[0] = generator.nextFloat() * 0.5f + 0.5f;
            color[1] = generator.nextFloat() * 0.5f + 0.5f;
            color[2] = generator.nextFloat() * 0.5f + 0.5f;
            color[3] = 0.5f;

            GLES20.glUniform4f ( mColorLoc, color[0], color[1], color[2], color[3] );
        }

        // Load uniform time variable
        GLES20.glUniform1f ( mTimeLoc, mTime );
    }
    
    ///
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    public void onDrawFrame(GL10 glUnused)
    {
        update();
        
        // Set the viewport
        GLES20.glViewport ( 0, 0, mWidth, mHeight );
        
        // Clear the color buffer
        GLES20.glClear ( GLES20.GL_COLOR_BUFFER_BIT );

        // Use the program object
        GLES20.glUseProgram ( mProgramObject );

        // Load the vertex attributes
        mParticles.position(0);
        GLES20.glVertexAttribPointer ( mLifetimeLoc, 1, GLES20.GL_FLOAT, 
                                       false, PARTICLE_SIZE * 4, 
                                       mParticles );
        
        mParticles.position(1);
        GLES20.glVertexAttribPointer ( mEndPositionLoc, 3, GLES20.GL_FLOAT,
                                       false, PARTICLE_SIZE * 4,
                                       mParticles );

        mParticles.position(4);
        GLES20.glVertexAttribPointer ( mStartPositionLoc, 3, GLES20.GL_FLOAT,
                                       false, PARTICLE_SIZE * 4,
                                       mParticles );

        
        GLES20.glEnableVertexAttribArray ( mLifetimeLoc );
        GLES20.glEnableVertexAttribArray ( mEndPositionLoc );
        GLES20.glEnableVertexAttribArray ( mStartPositionLoc );

        // Blend particles
        GLES20.glEnable ( GLES20.GL_BLEND );
        GLES20.glBlendFunc ( GLES20.GL_SRC_ALPHA, GLES20.GL_ONE );

        // Bind the texture
        GLES20.glActiveTexture ( GLES20.GL_TEXTURE0 );
        GLES20.glBindTexture ( GLES20.GL_TEXTURE_2D, mTextureId );
        GLES20.glEnable ( GLES20.GL_TEXTURE_2D );

        // Set the sampler texture unit to 0
        GLES20.glUniform1i ( mSamplerLoc, 0 );

        GLES20.glDrawArrays( GLES20.GL_POINTS, 0, NUM_PARTICLES );        
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
    private int mLifetimeLoc;
    private int mStartPositionLoc;
    private int mEndPositionLoc;

    // Uniform location
    private int mTimeLoc;
    private int mColorLoc;
    private int mCenterPositionLoc;
    private int mSamplerLoc;

    // Texture handle
    private int mTextureId;
    
    // Update time
    private float mTime;
    private long mLastTime;
        
    // Additional member variables
    private int mWidth;
    private int mHeight;
    private FloatBuffer mParticles;
    private Context mContext;
    
    private final int NUM_PARTICLES = 1000;
    private final int PARTICLE_SIZE = 7;

    private final float[] mParticleData = new float[NUM_PARTICLES * PARTICLE_SIZE]; 
    
        
}
