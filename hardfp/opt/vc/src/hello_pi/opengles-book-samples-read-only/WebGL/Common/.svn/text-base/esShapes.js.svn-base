
//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// esShapes.js
//
//    Utility functions for generating shapes
//

ESShape = function()
{
    this.vertices = null;
    this.normals = null;
    this.texCoords = null;
    this.indices = null;
    this.numIndices = 0;
}

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
/// \brief Generates geometry for a sphere.  Allocates memory for the vertex data and stores
///        the results in the arrays.  Generate index list for a TRIANGLES
/// \param vertices Boolean for whether to generate vertices
/// \param normals Boolean for whether to generate normals
/// \param texCoords Boolean for whether to generate texture coordinates
/// \param indices Boolean for whether to generate an index buffer
/// \return ESShape object containing the generated geometry
//
function esGenSphere( numSlices, radius, vertices, normals, texCoords, indices )
{
   var shape = new ESShape();
   var i;
   var j;
   var numParallels = numSlices;
   var numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
   var numIndices = numParallels * numSlices * 6;
   var angleStep = (2.0 * Math.PI) / numSlices;

   // Allocate memory for buffers
   if ( vertices  )
       shape.vertices = new Float32Array( 3 * numVertices );
      
   if ( normals )
       shape.normals = new Float32Array( 3 * numVertices );

   if ( texCoords )
      shape.texCoords = new Float32Array( 2 * numVertices );

   if ( indices )
      shape.indices = new Uint16Array( numIndices );

   for ( i = 0; i < numParallels + 1; i++ )
   {
      for ( j = 0; j < numSlices + 1; j++ )
      {
         var vertex = ( i * (numSlices + 1) + j ) * 3;

         if ( vertices )
         {
            shape.vertices[vertex + 0] = radius * Math.sin ( angleStep * i ) *
                                                  Math.sin ( angleStep * j );
            shape.vertices[vertex + 1] = radius * Math.cos ( angleStep * i );
            shape.vertices[vertex + 2] = radius * Math.sin ( angleStep * i ) *
                                                  Math.cos ( angleStep * j );
         }

         if ( normals )
         {
            shape.normals[vertex + 0] = shape.vertices[vertex + 0] / radius;
            shape.normals[vertex + 1] = shape.vertices[vertex + 1] / radius;
            shape.normals[vertex + 2] = shape.vertices[vertex + 2] / radius;
         }

         if ( texCoords )
         {
            var texIndex = ( i * (numSlices + 1) + j ) * 2;
            shape.texCoords[texIndex + 0] =  j / numSlices;
            shape.texCoords[texIndex + 1] = ( 1.0 -  i ) / (numParallels - 1 );
         }
      }
   }

   // Generate the indices
   if ( indices )
   {
      var curIdx = 0;
      
      for ( i = 0; i < numParallels ; i++ )
      {
         for ( j = 0; j < numSlices; j++ )
         {
            shape.indices[curIdx++]  = i * ( numSlices + 1 ) + j;
            shape.indices[curIdx++] = ( i + 1 ) * ( numSlices + 1 ) + j;
            shape.indices[curIdx++] = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );

            shape.indices[curIdx++] = i * ( numSlices + 1 ) + j;
            shape.indices[curIdx++] = ( i + 1 ) * ( numSlices + 1 ) + ( j + 1 );
            shape.indices[curIdx++] = i * ( numSlices + 1 ) + ( j + 1 );
         }
      }
   }
   shape.numIndices = numIndices;
   return shape;
}

//
/// \brief Generates geometry for a cube.  Allocates memory for the vertex data and stores
///        the results in the arrays.  Generate index list for a TRIANGLES
/// \param scale The size of the cube, use 1.0 for a unit cube.
/// \param vertices Boolean for whether to generate vertices
/// \param normals Boolean for whether to generate normals
/// \param texCoords Boolean for whether to generate texture coordinates
/// \param indices Boolean for whether to generate an index buffer
/// \return ESShape object containing the generated geometry
//
function esGenCube ( scale, vertices, normals,
                     texCoords, indices )
{
   var shape = new ESShape();
   var i;
   var numVertices = 24;
   var numIndices = 36;

   var cubeVerts =
   [
      -0.5, -0.5, -0.5,
      -0.5, -0.5,  0.5,
      0.5, -0.5,  0.5,
      0.5, -0.5, -0.5,
      -0.5,  0.5, -0.5,
      -0.5,  0.5,  0.5,
      0.5,  0.5,  0.5,
      0.5,  0.5, -0.5,
      -0.5, -0.5, -0.5,
      -0.5,  0.5, -0.5,
      0.5,  0.5, -0.5,
      0.5, -0.5, -0.5,
      -0.5, -0.5, 0.5,
      -0.5,  0.5, 0.5,
      0.5,  0.5, 0.5,
      0.5, -0.5, 0.5,
      -0.5, -0.5, -0.5,
      -0.5, -0.5,  0.5,
      -0.5,  0.5,  0.5,
      -0.5,  0.5, -0.5,
      0.5, -0.5, -0.5,
      0.5, -0.5,  0.5,
      0.5,  0.5,  0.5,
      0.5,  0.5, -0.5,
   ];
   
   var cubeNormals =
   [
      0.0, -1.0, 0.0,
      0.0, -1.0, 0.0,
      0.0, -1.0, 0.0,
      0.0, -1.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 1.0, 0.0,
      0.0, 0.0, -1.0,
      0.0, 0.0, -1.0,
      0.0, 0.0, -1.0,
      0.0, 0.0, -1.0,
      0.0, 0.0, 1.0,
      0.0, 0.0, 1.0,
      0.0, 0.0, 1.0,
      0.0, 0.0, 1.0,
      -1.0, 0.0, 0.0,
      -1.0, 0.0, 0.0,
      -1.0, 0.0, 0.0,
      -1.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
      1.0, 0.0, 0.0,
   ];

   var cubeTex =
   [
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
      0.0, 0.0,
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
   ];

   // Allocate memory for buffers
   if ( vertices )
   {
      shape.vertices = new Float32Array(cubeVerts.length);
      for ( i = 0; i < cubeVerts.length; i++)
      {
         shape.vertices[i] = cubeVerts[i];
         shape.vertices[i] *= scale;
      }
   }

   if ( normals )
   {
      shape.normals = new Float32Array(cubeNormals.length);
      for ( i = 0; i < cubeNormals.length; i++)
      {
         shape.normals[i] = cubeNormals[i];
      }
   }

   if ( texCoords )
   {
      shape.texCoords = new Float32Array(cubeTex.length);
      for ( i = 0; i < cubeTex.length; i++)
      {
          shape.texCoords[i] = cubeTex[i];
      }
   }


   // Generate the indices
   if ( indices  )
   {
      var cubeIndices =
      [
         0, 2, 1,
         0, 3, 2,
         4, 5, 6,
         4, 6, 7,
         8, 9, 10,
         8, 10, 11,
         12, 15, 14,
         12, 14, 13,
         16, 17, 18,
         16, 18, 19,
         20, 23, 22,
         20, 22, 21
      ]

      shape.indices = new Uint16Array(cubeIndices.length);
      for ( i = 0; i < cubeIndices.length; i++)
      {
          shape.indices[i] = cubeIndices[i];
      }
      shape.numIndices = cubeIndices.length;
   }

   return shape;
}

