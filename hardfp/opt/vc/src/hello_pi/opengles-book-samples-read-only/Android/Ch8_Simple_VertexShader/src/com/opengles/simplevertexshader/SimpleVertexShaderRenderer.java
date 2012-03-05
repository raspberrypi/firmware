//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Simple_VertexShader
//
//    This is a simple example that draws a rotating cube in perspective
//    using a vertex shader to transform the object
//

package com.opengles.simplevertexshader;

import com.openglesbook.common.ESShapes;
import com.openglesbook.common.ESShader;
import com.openglesbook.common.ESTransform;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.SystemClock;

public class SimpleVertexShaderRenderer implements GLSurfaceView.Renderer
{

    ///
    // Constructor
    //
    public SimpleVertexShaderRenderer(Context context)
    {

    }

    ///
    // Initialize the shader and program object
    //
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config)
    {
        String vShaderStr = "uniform mat4 u_mvpMatrix;                   \n"
                + "attribute vec4 a_position;                  \n"
                + "void main()                                 \n"
                + "{                                           \n"
                + "   gl_Position = u_mvpMatrix * a_position;  \n"
                + "}                                           \n";

        String fShaderStr = "precision mediump float;                            \n"
                + "void main()                                         \n"
                + "{                                                   \n"
                + "  gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );        \n"
                + "}                                                   \n";

        // Load the shaders and get a linked program object
        mProgramObject = ESShader.loadProgram(vShaderStr, fShaderStr);

        // Get the attribute locations
        mPositionLoc = GLES20.glGetAttribLocation(mProgramObject, "a_position");

        // Get the uniform locations
        mMVPLoc = GLES20.glGetUniformLocation(mProgramObject, "u_mvpMatrix");

        // Generate the vertex data
        mCube.genCube(1.0f);

        // Starting rotation angle for the cube
        mAngle = 45.0f;

        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    }

    private void update()
    {
        if (mLastTime == 0)
            mLastTime = SystemClock.uptimeMillis();
        long curTime = SystemClock.uptimeMillis();
        long elapsedTime = curTime - mLastTime;
        float deltaTime = elapsedTime / 1000.0f;
        mLastTime = curTime;

        ESTransform perspective = new ESTransform();
        ESTransform modelview = new ESTransform();
        float aspect;

        // Compute a rotation angle based on time to rotate the cube
        mAngle += (deltaTime * 40.0f);
        if (mAngle >= 360.0f)
            mAngle -= 360.0f;

        // Compute the window aspect ratio
        aspect = (float) mWidth / (float) mHeight;

        // Generate a perspective matrix with a 60 degree FOV
        perspective.matrixLoadIdentity();
        perspective.perspective(60.0f, aspect, 1.0f, 20.0f);

        // Generate a model view matrix to rotate/translate the cube
        modelview.matrixLoadIdentity();

        // Translate away from the viewer
        modelview.translate(0.0f, 0.0f, -2.0f);

        // Rotate the cube
        modelview.rotate(mAngle, 1.0f, 0.0f, 1.0f);

        // Compute the final MVP by multiplying the
        // modevleiw and perspective matrices together
        mMVPMatrix.matrixMultiply(modelview.get(), perspective.get());
    }

    ///
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    public void onDrawFrame(GL10 glUnused)
    {
        update();

        // Set the viewport
        GLES20.glViewport(0, 0, mWidth, mHeight);

        // Clear the color buffer
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        // Use the program object
        GLES20.glUseProgram(mProgramObject);

        // Load the vertex data
        GLES20.glVertexAttribPointer(mPositionLoc, 3, GLES20.GL_FLOAT, false,
                0, mCube.getVertices());
        GLES20.glEnableVertexAttribArray(mPositionLoc);

        // Load the MVP matrix
        GLES20.glUniformMatrix4fv(mMVPLoc, 1, false,
                mMVPMatrix.getAsFloatBuffer());

        // Draw the cube
        GLES20.glDrawElements(GLES20.GL_TRIANGLES, mCube.getNumIndices(),
                GLES20.GL_UNSIGNED_SHORT, mCube.getIndices());
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

    // Uniform locations
    private int mMVPLoc;

    // Vertex data
    private ESShapes mCube = new ESShapes();

    // Rotation angle
    private float mAngle;

    // MVP matrix
    private ESTransform mMVPMatrix = new ESTransform();

    // Additional Member variables
    private int mWidth;
    private int mHeight;
    private long mLastTime = 0;
}
