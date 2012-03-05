//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// esTransform.js
//
//    Matrix transformation functions providing much of the
//    functionality of the fixed-function matrix functions in OpenGL

ESMatrix = function()
{
    // Create a 2D 4x4 array representing
    // the matrix
    this.m = new Array(4);
    for(var i = 0; i < 4; i++)
    {
        this.m[i] = new Array(4);
    }
}

// Return the matrix as a flat Float32Array for
// loading as a uniform
function getAsFloat32Array(mat)
{    
    var result = new Float32Array(16);
    for ( var i = 0; i < 4; i++ )
    {
        for ( var j = 0; j < 4; j++ )
        {
            result[i * 4 + j] = mat.m[i][j];
        }
    }
    return result;
}


function esScale(result, sx, sy, sz)
{
    result.m[0][0] *= sx;
    result.m[0][1] *= sx;
    result.m[0][2] *= sx;
    result.m[0][3] *= sx;

    result.m[1][0] *= sy;
    result.m[1][1] *= sy;
    result.m[1][2] *= sy;
    result.m[1][3] *= sy;

    result.m[2][0] *= sz;
    result.m[2][1] *= sz;
    result.m[2][2] *= sz;
    result.m[2][3] *= sz;
}


function esTranslate(result, tx, ty, tz)
{
    result.m[3][0] += (result.m[0][0] * tx + result.m[1][0] * ty + result.m[2][0] * tz);
    result.m[3][1] += (result.m[0][1] * tx + result.m[1][1] * ty + result.m[2][1] * tz);
    result.m[3][2] += (result.m[0][2] * tx + result.m[1][2] * ty + result.m[2][2] * tz);
    result.m[3][3] += (result.m[0][3] * tx + result.m[1][3] * ty + result.m[2][3] * tz);
}

function esRotate(result, angle, x, y, z)
{
   var sinAngle, cosAngle;
   var mag = Math.sqrt(x * x + y * y + z * z);

   sinAngle = Math.sin ( angle * Math.PI / 180.0 );
   cosAngle = Math.cos ( angle * Math.PI / 180.0 );
   if ( mag > 0.0 )
   {
      var xx, yy, zz, xy, yz, zx, xs, ys, zs;
      var oneMinusCos;
      var rotMat = new ESMatrix();

      x /= mag;
      y /= mag;
      z /= mag;

      xx = x * x;
      yy = y * y;
      zz = z * z;
      xy = x * y;
      yz = y * z;
      zx = z * x;
      xs = x * sinAngle;
      ys = y * sinAngle;
      zs = z * sinAngle;
      oneMinusCos = 1.0 - cosAngle;

      rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
      rotMat.m[0][1] = (oneMinusCos * xy) - zs;
      rotMat.m[0][2] = (oneMinusCos * zx) + ys;
      rotMat.m[0][3] = 0.0;

      rotMat.m[1][0] = (oneMinusCos * xy) + zs;
      rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
      rotMat.m[1][2] = (oneMinusCos * yz) - xs;
      rotMat.m[1][3] = 0.0;

      rotMat.m[2][0] = (oneMinusCos * zx) - ys;
      rotMat.m[2][1] = (oneMinusCos * yz) + xs;
      rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
      rotMat.m[2][3] = 0.0;

      rotMat.m[3][0] = 0.0;
      rotMat.m[3][1] = 0.0;
      rotMat.m[3][2] = 0.0;
      rotMat.m[3][3] = 1.0;

      esMatrixMultiply( result, rotMat, result );
   }
}

function esFrustum(result, left, right, bottom, top, nearZ, farZ)
{
    var       deltaX = right - left;
    var       deltaY = top - bottom;
    var       deltaZ = farZ - nearZ;
    var       frust = new ESMatrix();

    if ( (nearZ <= 0.0) || (farZ <= 0.0) ||
         (deltaX <= 0.0) || (deltaY <= 0.0) || (deltaZ <= 0.0) )
         return;

    frust.m[0][0] = 2.0 * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0;

    frust.m[1][1] = 2.0 * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0;

    frust.m[3][2] = -2.0 * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0;

    esMatrixMultiply(result, frust, result);
}


function esPerspective(result, fovy, aspect, nearZ, farZ)
{
   var frustumW, frustumH;

   frustumH = Math.tan( fovy / 360.0 * Math.PI ) * nearZ;
   frustumW = frustumH * aspect;

   esFrustum( result, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}


function esOrtho(result, left, right, bottom, top, nearZ, farZ)
{
    var       deltaX = right - left;
    var       deltaY = top - bottom;
    var       deltaZ = farZ - nearZ;
    var       ortho;

    if ( (deltaX == 0.0) || (deltaY == 0.0) || (deltaZ == 0.0) )
        return;

    esMatrixLoadIdentity(ortho);
    ortho.m[0][0] = 2.0 / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0 / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0 / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

    esMatrixMultiply(result, ortho, result);
}


function esMatrixMultiply(result, srcA, srcB)
{
    var    tmp = new ESMatrix();
    var    i;

    for (i=0; i<4; i++)
    {
        tmp.m[i][0] =	(srcA.m[i][0] * srcB.m[0][0]) +
                        (srcA.m[i][1] * srcB.m[1][0]) +
                        (srcA.m[i][2] * srcB.m[2][0]) +
                        (srcA.m[i][3] * srcB.m[3][0]) ;

        tmp.m[i][1] =	(srcA.m[i][0] * srcB.m[0][1]) +
                        (srcA.m[i][1] * srcB.m[1][1]) +
                        (srcA.m[i][2] * srcB.m[2][1]) +
                        (srcA.m[i][3] * srcB.m[3][1]) ;

        tmp.m[i][2] =	(srcA.m[i][0] * srcB.m[0][2]) +
                        (srcA.m[i][1] * srcB.m[1][2]) +
                        (srcA.m[i][2] * srcB.m[2][2]) +
                        (srcA.m[i][3] * srcB.m[3][2]) ;

        tmp.m[i][3] =	(srcA.m[i][0] * srcB.m[0][3]) +
                        (srcA.m[i][1] * srcB.m[1][3]) +
                        (srcA.m[i][2] * srcB.m[2][3]) +
                        (srcA.m[i][3] * srcB.m[3][3]) ;
    }

    for (i = 0; i < 4; i++)
    {
        for (var j = 0; j < 4; j++)
        {
            result.m[i][j] = tmp.m[i][j];
        }
    }
        
}


function esMatrixLoadIdentity(result)
{
    for (var i = 0; i < 4; i++)
    {
        for (var j = 0; j < 4; j++)
        {
            if (i == j)
            {
                result.m[i][j] = 1.0;
            }
            else
            {
                result.m[i][j] = 0.0;
            }
        }
    }
}


