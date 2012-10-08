//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        compressMG1.c
// Description: Implementation of the MG1 compression method.
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include "openctm.h"
#include "internal.h"

#ifdef __DEBUG_
#include <stdio.h>
#endif


//-----------------------------------------------------------------------------
// _compareTriangle() - Comparator for the triangle sorting.
//-----------------------------------------------------------------------------
static int _compareTriangle(const void * elem1, const void * elem2)
{
  CTMuint * tri1 = (CTMuint *) elem1;
  CTMuint * tri2 = (CTMuint *) elem2;
  if(tri1[0] != tri2[0])
    return tri1[0] - tri2[0];
  else
    return tri1[1] - tri2[1];
}

//-----------------------------------------------------------------------------
// _ctmReArrangeTriangles() - Re-arrange all triangles for optimal
// compression.
//-----------------------------------------------------------------------------
static void _ctmReArrangeTriangles(_CTMcontext * self, CTMuint * aIndices)
{
  CTMuint * tri, tmp, i;

  // Step 1: Make sure that the first index of each triangle is the smallest
  // one (rotate triangle nodes if necessary)
  for(i = 0; i < self->mTriangleCount; ++ i)
  {
    tri = &aIndices[i * 3];
    if((tri[1] < tri[0]) && (tri[1] < tri[2]))
    {
      tmp = tri[0];
      tri[0] = tri[1];
      tri[1] = tri[2];
      tri[2] = tmp;
    }
    else if((tri[2] < tri[0]) && (tri[2] < tri[1]))
    {
      tmp = tri[0];
      tri[0] = tri[2];
      tri[2] = tri[1];
      tri[1] = tmp;
    }
  }

  // Step 2: Sort the triangles based on the first triangle index
  qsort((void *) aIndices, self->mTriangleCount, sizeof(CTMuint) * 3, _compareTriangle);
}

//-----------------------------------------------------------------------------
// _ctmMakeIndexDeltas() - Calculate various forms of derivatives in order to
// reduce data entropy.
//-----------------------------------------------------------------------------
static void _ctmMakeIndexDeltas(_CTMcontext * self, CTMuint * aIndices)
{
  CTMint i;
  for(i = self->mTriangleCount - 1; i >= 0; -- i)
  {
    // Step 1: Calculate delta from second triangle index to the previous
    // second triangle index, if the previous triangle shares the same first
    // index, otherwise calculate the delta to the first triangle index
    if((i >= 1) && (aIndices[i * 3] == aIndices[(i - 1) * 3]))
      aIndices[i * 3 + 1] -= aIndices[(i - 1) * 3 + 1];
    else
      aIndices[i * 3 + 1] -= aIndices[i * 3];

    // Step 2: Calculate delta from third triangle index to the first triangle
    // index
    aIndices[i * 3 + 2] -= aIndices[i * 3];

    // Step 3: Calculate derivative of the first triangle index
    if(i >= 1)
      aIndices[i * 3] -= aIndices[(i - 1) * 3];
  }
}

//-----------------------------------------------------------------------------
// _ctmRestoreIndices() - Restore original indices (inverse derivative
// operation).
//-----------------------------------------------------------------------------
static void _ctmRestoreIndices(_CTMcontext * self, CTMuint * aIndices)
{
  CTMuint i;

  for(i = 0; i < self->mTriangleCount; ++ i)
  {
    // Step 1: Reverse derivative of the first triangle index
    if(i >= 1)
      aIndices[i * 3] += aIndices[(i - 1) * 3];

    // Step 2: Reverse delta from third triangle index to the first triangle
    // index
    aIndices[i * 3 + 2] += aIndices[i * 3];

    // Step 3: Reverse delta from second triangle index to the previous
    // second triangle index, if the previous triangle shares the same first
    // index, otherwise reverse the delta to the first triangle index
    if((i >= 1) && (aIndices[i * 3] == aIndices[(i - 1) * 3]))
      aIndices[i * 3 + 1] += aIndices[(i - 1) * 3 + 1];
    else
      aIndices[i * 3 + 1] += aIndices[i * 3];
  }
}

//-----------------------------------------------------------------------------
// _ctmCompressMesh_MG1() - Compress the mesh that is stored in the CTM
// context, and write it the the output stream in the CTM context.
//-----------------------------------------------------------------------------
int _ctmCompressMesh_MG1(_CTMcontext * self)
{
  CTMuint * indices;
  _CTMfloatmap * map;
  CTMuint i;

#ifdef __DEBUG_
  printf("COMPRESSION METHOD: MG1\n");
#endif

  // Perpare (sort) indices
  indices = (CTMuint *) malloc(sizeof(CTMuint) * self->mTriangleCount * 3);
  if(!indices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  for(i = 0; i < self->mTriangleCount * 3; ++ i)
    indices[i] = self->mIndices[i];
  _ctmReArrangeTriangles(self, indices);

  // Calculate index deltas (entropy-reduction)
  _ctmMakeIndexDeltas(self, indices);

  // Write triangle indices
#ifdef __DEBUG_
  printf("Inidices: ");
#endif
  _ctmStreamWrite(self, (void *) "INDX", 4);
  if(!_ctmStreamWritePackedInts(self, (CTMint *) indices, self->mTriangleCount, 3, CTM_FALSE))
  {
    free((void *) indices);
    return CTM_FALSE;
  }

  // Free temporary resources
  free((void *) indices);

  // Write vertices
#ifdef __DEBUG_
  printf("Vertices: ");
#endif
  _ctmStreamWrite(self, (void *) "VERT", 4);
  if(!_ctmStreamWritePackedFloats(self, self->mVertices, self->mVertexCount * 3, 1))
  {
    free((void *) indices);
    return CTM_FALSE;
  }

  // Write normals
  if(self->mNormals)
  {
#ifdef __DEBUG_
    printf("Normals: ");
#endif
    _ctmStreamWrite(self, (void *) "NORM", 4);
    if(!_ctmStreamWritePackedFloats(self, self->mNormals, self->mVertexCount, 3))
      return CTM_FALSE;
  }

  // Write UV maps
  map = self->mUVMaps;
  while(map)
  {
#ifdef __DEBUG_
    printf("UV coordinates (%s): ", map->mName ? map->mName : "no name");
#endif
    _ctmStreamWrite(self, (void *) "TEXC", 4);
    _ctmStreamWriteSTRING(self, map->mName);
    _ctmStreamWriteSTRING(self, map->mFileName);
    if(!_ctmStreamWritePackedFloats(self, map->mValues, self->mVertexCount, 2))
      return CTM_FALSE;
    map = map->mNext;
  }

  // Write attribute maps
  map = self->mAttribMaps;
  while(map)
  {
#ifdef __DEBUG_
    printf("Vertex attributes (%s): ", map->mName ? map->mName : "no name");
#endif
    _ctmStreamWrite(self, (void *) "ATTR", 4);
    _ctmStreamWriteSTRING(self, map->mName);
    if(!_ctmStreamWritePackedFloats(self, map->mValues, self->mVertexCount, 4))
      return CTM_FALSE;
    map = map->mNext;
  }

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmUncompressMesh_MG1() - Uncmpress the mesh from the input stream in the
// CTM context, and store the resulting mesh in the CTM context.
//-----------------------------------------------------------------------------
int _ctmUncompressMesh_MG1(_CTMcontext * self)
{
  CTMuint * indices;
  _CTMfloatmap * map;
  CTMuint i;

  // Allocate memory for the indices
  indices = (CTMuint *) malloc(sizeof(CTMuint) * self->mTriangleCount * 3);
  if(!indices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Read triangle indices
  if(_ctmStreamReadUINT(self) != FOURCC("INDX"))
  {
    self->mError = CTM_BAD_FORMAT;
    free(indices);
    return CTM_FALSE;
  }
  if(!_ctmStreamReadPackedInts(self, (CTMint *) indices, self->mTriangleCount, 3, CTM_FALSE))
    return CTM_FALSE;

  // Restore indices
  _ctmRestoreIndices(self, indices);
  for(i = 0; i < self->mTriangleCount * 3; ++ i)
    self->mIndices[i] = indices[i];

  // Free temporary resources
  free(indices);

  // Read vertices
  if(_ctmStreamReadUINT(self) != FOURCC("VERT"))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  if(!_ctmStreamReadPackedFloats(self, self->mVertices, self->mVertexCount * 3, 1))
    return CTM_FALSE;

  // Read normals
  if(self->mNormals)
  {
    if(_ctmStreamReadUINT(self) != FOURCC("NORM"))
    {
      self->mError = CTM_BAD_FORMAT;
      return CTM_FALSE;
    }
    if(!_ctmStreamReadPackedFloats(self, self->mNormals, self->mVertexCount, 3))
      return CTM_FALSE;
  }

  // Read UV maps
  map = self->mUVMaps;
  while(map)
  {
    if(_ctmStreamReadUINT(self) != FOURCC("TEXC"))
    {
      self->mError = CTM_BAD_FORMAT;
      return 0;
    }
    _ctmStreamReadSTRING(self, &map->mName);
    _ctmStreamReadSTRING(self, &map->mFileName);
    if(!_ctmStreamReadPackedFloats(self, map->mValues, self->mVertexCount, 2))
      return CTM_FALSE;
    map = map->mNext;
  }

  // Read vertex attribute maps
  map = self->mAttribMaps;
  while(map)
  {
    if(_ctmStreamReadUINT(self) != FOURCC("ATTR"))
    {
      self->mError = CTM_BAD_FORMAT;
      return 0;
    }
    _ctmStreamReadSTRING(self, &map->mName);
    if(!_ctmStreamReadPackedFloats(self, map->mValues, self->mVertexCount, 4))
      return CTM_FALSE;
    map = map->mNext;
  }

  return CTM_TRUE;
}
