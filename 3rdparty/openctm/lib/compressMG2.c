//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        compressMG2.c
// Description: Implementation of the MG2 compression method.
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

// We need PI
#ifndef PI
#define PI 3.141592653589793238462643f
#endif


//-----------------------------------------------------------------------------
// _CTMgrid - 3D space subdivision grid.
//-----------------------------------------------------------------------------
typedef struct {
  // Axis-aligned boudning box for the grid.
  CTMfloat mMin[3];
  CTMfloat mMax[3];

  // How many divisions per axis (minimum 1).
  CTMuint mDivision[3];

  // Size of each grid box.
  CTMfloat mSize[3];
} _CTMgrid;

//-----------------------------------------------------------------------------
// _CTMsortvertex - Vertex information.
//-----------------------------------------------------------------------------
typedef struct {
  // Vertex X coordinate (used for sorting).
  CTMfloat x;

  // Grid index. This is the index into the 3D space subdivision grid.
  CTMuint mGridIndex;

  // Original index (before sorting).
  CTMuint mOriginalIndex;
} _CTMsortvertex;

//-----------------------------------------------------------------------------
// _ctmSetupGrid() - Setup the 3D space subdivision grid.
//-----------------------------------------------------------------------------
static void _ctmSetupGrid(_CTMcontext * self, _CTMgrid * aGrid)
{
  CTMuint i;
  CTMfloat factor[3], sum, wantedGrids;

  // Calculate the mesh bounding box
  aGrid->mMin[0] = aGrid->mMax[0] = self->mVertices[0];
  aGrid->mMin[1] = aGrid->mMax[1] = self->mVertices[1];
  aGrid->mMin[2] = aGrid->mMax[2] = self->mVertices[2];
  for(i = 1; i < self->mVertexCount; ++ i)
  {
    if(self->mVertices[i * 3] < aGrid->mMin[0])
      aGrid->mMin[0] = self->mVertices[i * 3];
    else if(self->mVertices[i * 3] > aGrid->mMax[0])
      aGrid->mMax[0] = self->mVertices[i * 3];
    if(self->mVertices[i * 3 + 1] < aGrid->mMin[1])
      aGrid->mMin[1] = self->mVertices[i * 3 + 1];
    else if(self->mVertices[i * 3 + 1] > aGrid->mMax[1])
      aGrid->mMax[1] = self->mVertices[i * 3 + 1];
    if(self->mVertices[i * 3 + 2] < aGrid->mMin[2])
      aGrid->mMin[2] = self->mVertices[i * 3 + 2];
    else if(self->mVertices[i * 3 + 2] > aGrid->mMax[2])
      aGrid->mMax[2] = self->mVertices[i * 3 + 2];
  }

  // Determine optimal grid resolution, based on the number of vertices and
  // the bounding box.
  // NOTE: This algorithm is quite crude, and could very well be optimized for
  // better compression levels in the future without affecting the file format
  // or backward compatibility at all.
  for(i = 0; i < 3; ++ i)
    factor[i] = aGrid->mMax[i] - aGrid->mMin[i];
  sum = factor[0] + factor[1] + factor[2];
  if(sum > 1e-30f)
  {
    sum = 1.0f / sum;
    for(i = 0; i < 3; ++ i)
      factor[i] *= sum;
    wantedGrids = powf(100.0f * self->mVertexCount, 1.0f / 3.0f);
    for(i = 0; i < 3; ++ i)
    {
      aGrid->mDivision[i] = (CTMuint) ceilf(wantedGrids * factor[i]);
      if(aGrid->mDivision[i] < 1)
        aGrid->mDivision[i] = 1;
    }
  }
  else
  {
    aGrid->mDivision[0] = 4;
    aGrid->mDivision[1] = 4;
    aGrid->mDivision[2] = 4;
  }
#ifdef __DEBUG_
  printf("Division: (%d %d %d)\n", aGrid->mDivision[0], aGrid->mDivision[1], aGrid->mDivision[2]);
#endif

  // Calculate grid sizes
  for(i = 0; i < 3; ++ i)
    aGrid->mSize[i] = (aGrid->mMax[i] - aGrid->mMin[i]) / aGrid->mDivision[i];
}

//-----------------------------------------------------------------------------
// _ctmPointToGridIdx() - Convert a point to a grid index.
//-----------------------------------------------------------------------------
static CTMuint _ctmPointToGridIdx(_CTMgrid * aGrid, CTMfloat * aPoint)
{
  CTMuint i, idx[3];

  for(i = 0; i < 3; ++ i)
  {
    idx[i] = (CTMuint) floorf((aPoint[i] - aGrid->mMin[i]) / aGrid->mSize[i]);
    if(idx[i] >= aGrid->mDivision[i])
      idx[i] = aGrid->mDivision[i] - 1;
  }

  return idx[0] + aGrid->mDivision[0] * (idx[1] + aGrid->mDivision[1] * idx[2]);
}

//-----------------------------------------------------------------------------
// _ctmGridIdxToPoint() - Convert a grid index to a point (the min x/y/z for
// the given grid box).
//-----------------------------------------------------------------------------
static void _ctmGridIdxToPoint(_CTMgrid * aGrid, CTMuint aIdx, CTMfloat * aPoint)
{
  CTMuint gridIdx[3], zdiv, ydiv, i;

  zdiv = aGrid->mDivision[0] * aGrid->mDivision[1];
  ydiv = aGrid->mDivision[0];

  gridIdx[2] =  aIdx / zdiv;
  aIdx -= gridIdx[2] * zdiv;
  gridIdx[1] =  aIdx / ydiv;
  aIdx -= gridIdx[1] * ydiv;
  gridIdx[0] = aIdx;

  for(i = 0; i < 3; ++ i)
    aPoint[i] = gridIdx[i] * aGrid->mSize[i] + aGrid->mMin[i];
}

//-----------------------------------------------------------------------------
// _compareVertex() - Comparator for the vertex sorting.
//-----------------------------------------------------------------------------
static int _compareVertex(const void * elem1, const void * elem2)
{
  _CTMsortvertex * v1 = (_CTMsortvertex *) elem1;
  _CTMsortvertex * v2 = (_CTMsortvertex *) elem2;
  if(v1->mGridIndex != v2->mGridIndex)
    return v1->mGridIndex - v2->mGridIndex;
  else if(v1->x < v2->x)
    return -1;
  else if(v1->x > v2->x)
    return 1;
  else
    return 0;
}

//-----------------------------------------------------------------------------
// _ctmSortVertices() - Setup the vertex array. Assign each vertex to a grid
// box, and sort all vertices.
//-----------------------------------------------------------------------------
static void _ctmSortVertices(_CTMcontext * self, _CTMsortvertex * aSortVertices,
  _CTMgrid * aGrid)
{
  CTMuint i;

  // Prepare sort vertex array
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Store vertex properties in the sort vertex array
    aSortVertices[i].x = self->mVertices[i * 3];
    aSortVertices[i].mGridIndex = _ctmPointToGridIdx(aGrid, &self->mVertices[i * 3]);
    aSortVertices[i].mOriginalIndex = i;
  }

  // Sort vertices. The elements are first sorted by their grid indices, and
  // scondly by their x coordinates.
  qsort((void *) aSortVertices, self->mVertexCount, sizeof(_CTMsortvertex), _compareVertex);
}

//-----------------------------------------------------------------------------
// _ctmReIndexIndices() - Re-index all indices, based on the sorted vertices.
//-----------------------------------------------------------------------------
static int _ctmReIndexIndices(_CTMcontext * self, _CTMsortvertex * aSortVertices,
  CTMuint * aIndices)
{
  CTMuint i, * indexLUT;

  // Create temporary lookup-array, O(n)
  indexLUT = (CTMuint *) malloc(sizeof(CTMuint) * self->mVertexCount);
  if(!indexLUT)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  for(i = 0; i < self->mVertexCount; ++ i)
    indexLUT[aSortVertices[i].mOriginalIndex] = i;

  // Convert old indices to new indices, O(n)
  for(i = 0; i < self->mTriangleCount * 3; ++ i)
    aIndices[i] = indexLUT[self->mIndices[i]];

  // Free temporary lookup-array
  free((void *) indexLUT);

  return CTM_TRUE;
}

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
// _ctmMakeVertexDeltas() - Calculate various forms of derivatives in order to
// reduce data entropy.
//-----------------------------------------------------------------------------
static void _ctmMakeVertexDeltas(_CTMcontext * self, CTMint * aIntVertices,
  _CTMsortvertex * aSortVertices, _CTMgrid * aGrid)
{
  CTMuint i, gridIdx, prevGridIndex, oldIdx;
  CTMfloat gridOrigin[3], scale;
  CTMint deltaX, prevDeltaX;

  // Vertex scaling factor
  scale = 1.0f / self->mVertexPrecision;

  prevGridIndex = 0x7fffffff;
  prevDeltaX = 0;
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get grid box origin
    gridIdx = aSortVertices[i].mGridIndex;
    _ctmGridIdxToPoint(aGrid, gridIdx, gridOrigin);

    // Get old vertex coordinate index (before vertex sorting)
    oldIdx = aSortVertices[i].mOriginalIndex;

    // Store delta to the grid box origin in the integer vertex array. For the
    // X axis (which is sorted) we also do the delta to the previous coordinate
    // in the box.
    deltaX = (CTMint) floorf(scale * (self->mVertices[oldIdx * 3] - gridOrigin[0]) + 0.5f);
    if(gridIdx == prevGridIndex)
      aIntVertices[i * 3] = deltaX - prevDeltaX;
    else
      aIntVertices[i * 3] = deltaX;
    aIntVertices[i * 3 + 1] = (CTMint) floorf(scale * (self->mVertices[oldIdx * 3 + 1] - gridOrigin[1]) + 0.5f);
    aIntVertices[i * 3 + 2] = (CTMint) floorf(scale * (self->mVertices[oldIdx * 3 + 2] - gridOrigin[2]) + 0.5f);

    prevGridIndex = gridIdx;
    prevDeltaX = deltaX;
  }
}

//-----------------------------------------------------------------------------
// _ctmRestoreVertices() - Calculate inverse derivatives of the vertices.
//-----------------------------------------------------------------------------
static void _ctmRestoreVertices(_CTMcontext * self, CTMint * aIntVertices,
  CTMuint * aGridIndices, _CTMgrid * aGrid, CTMfloat * aVertices)
{
  CTMuint i, gridIdx, prevGridIndex;
  CTMfloat gridOrigin[3], scale;
  CTMint deltaX, prevDeltaX;

  scale = self->mVertexPrecision;

  prevGridIndex = 0x7fffffff;
  prevDeltaX = 0;
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get grid box origin
    gridIdx = aGridIndices[i];
    _ctmGridIdxToPoint(aGrid, gridIdx, gridOrigin);

    // Restore original point
    deltaX = aIntVertices[i * 3];
    if(gridIdx == prevGridIndex)
      deltaX += prevDeltaX;
    aVertices[i * 3] = scale * deltaX + gridOrigin[0];
    aVertices[i * 3 + 1] = scale * aIntVertices[i * 3 + 1] + gridOrigin[1];
    aVertices[i * 3 + 2] = scale * aIntVertices[i * 3 + 2] + gridOrigin[2];

    prevGridIndex = gridIdx;
    prevDeltaX = deltaX;
  }
}

//-----------------------------------------------------------------------------
// _ctmCalcSmoothNormals() - Calculate the smooth normals for a given mesh.
// These are used as the nominal normals for normal deltas & reconstruction.
//-----------------------------------------------------------------------------
static void _ctmCalcSmoothNormals(_CTMcontext * self, CTMfloat * aVertices,
  CTMuint * aIndices, CTMfloat * aSmoothNormals)
{
  CTMuint i, j, k, tri[3];
  CTMfloat len;
  CTMfloat v1[3], v2[3], n[3];

  // Clear smooth normals array
  for(i = 0; i < 3 * self->mVertexCount; ++ i)
    aSmoothNormals[i] = 0.0f;

  // Calculate sums of all neigbouring triangle normals for each vertex
  for(i = 0; i < self->mTriangleCount; ++ i)
  {
    // Get triangle corner indices
    for(j = 0; j < 3; ++ j)
      tri[j] = aIndices[i * 3 + j];

    // Calculate the normalized cross product of two triangle edges (i.e. the
    // flat triangle normal)
    for(j = 0; j < 3; ++ j)
    {
      v1[j] = aVertices[tri[1] * 3 + j] - aVertices[tri[0] * 3 + j];
      v2[j] = aVertices[tri[2] * 3 + j] - aVertices[tri[0] * 3 + j];
    }
    n[0] = v1[1] * v2[2] - v1[2] * v2[1];
    n[1] = v1[2] * v2[0] - v1[0] * v2[2];
    n[2] = v1[0] * v2[1] - v1[1] * v2[0];
    len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if(len > 1e-10f)
      len = 1.0f / len;
    else
      len = 1.0f;
    for(j = 0; j < 3; ++ j)
      n[j] *= len;

    // Add the flat normal to all three triangle vertices
    for(k = 0; k < 3; ++ k)
      for(j = 0; j < 3; ++ j)
        aSmoothNormals[tri[k] * 3 + j] += n[j];
  }

  // Normalize the normal sums, which gives the unit length smooth normals
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    len = sqrtf(aSmoothNormals[i * 3] * aSmoothNormals[i * 3] + 
                aSmoothNormals[i * 3 + 1] * aSmoothNormals[i * 3 + 1] +
                aSmoothNormals[i * 3 + 2] * aSmoothNormals[i * 3 + 2]);
    if(len > 1e-10f)
      len = 1.0f / len;
    else
      len = 1.0f;
    for(j = 0; j < 3; ++ j)
      aSmoothNormals[i * 3 + j] *= len;
  }
}

//-----------------------------------------------------------------------------
// _ctmMakeNormalCoordSys() - Create an ortho-normalized coordinate system
// where the Z-axis is aligned with the given normal.
// Note 1: This function is central to how the compressed normal data is
//  interpreted, and it can not be changed (mathematically) without making the
//  coder/decoder incompatible with other versions of the library!
// Note 2: Since we do this for every single normal, this routine needs to be
//  fast. The current implementation uses: 12 MUL, 1 DIV, 1 SQRT, ~6 ADD.
//-----------------------------------------------------------------------------
static void _ctmMakeNormalCoordSys(CTMfloat * aNormal, CTMfloat * aBasisAxes)
{
  CTMfloat len, * x, * y, * z;
  CTMuint i;

  // Pointers to the basis axes (aBasisAxes is a 3x3 matrix)
  x = aBasisAxes;
  y = &aBasisAxes[3];
  z = &aBasisAxes[6];

  // Z = normal (must be unit length!)
  for(i = 0; i < 3; ++ i)
    z[i] = aNormal[i];

  // Calculate a vector that is guaranteed to be orthogonal to the normal, non-
  // zero, and a continuous function of the normal (no discrete jumps):
  // X = (0,0,1) x normal + (1,0,0) x normal
  x[0] =  -aNormal[1];
  x[1] =  aNormal[0] - aNormal[2];
  x[2] =  aNormal[1];

  // Normalize the new X axis (note: |x[2]| = |x[0]|)
  len = sqrtf(2.0 * x[0] * x[0] + x[1] * x[1]);
  if(len > 1.0e-20f)
  {
    len = 1.0f / len;
    x[0] *= len;
    x[1] *= len;
    x[2] *= len;
  }

  // Let Y = Z x X  (no normalization needed, since |Z| = |X| = 1)
  y[0] = z[1] * x[2] - z[2] * x[1];
  y[1] = z[2] * x[0] - z[0] * x[2];
  y[2] = z[0] * x[1] - z[1] * x[0];
}

//-----------------------------------------------------------------------------
// _ctmMakeNormalDeltas() - Convert the normals to a new coordinate system:
// magnitude, phi, theta (relative to predicted smooth normals).
//-----------------------------------------------------------------------------
static CTMint _ctmMakeNormalDeltas(_CTMcontext * self, CTMint * aIntNormals,
  CTMfloat * aVertices, CTMuint * aIndices, _CTMsortvertex * aSortVertices)
{
  CTMuint i, j, oldIdx, intPhi;
  CTMfloat magn, phi, theta, scale, thetaScale;
  CTMfloat * smoothNormals, n[3], n2[3], basisAxes[9];

  // Allocate temporary memory for the nominal vertex normals
  smoothNormals = (CTMfloat *) malloc(3 * sizeof(CTMfloat) * self->mVertexCount);
  if(!smoothNormals)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Calculate smooth normals (Note: aVertices and aIndices use the sorted
  // index space, so smoothNormals will too)
  _ctmCalcSmoothNormals(self, aVertices, aIndices, smoothNormals);

  // Normal scaling factor
  scale = 1.0f / self->mNormalPrecision;

  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get old normal index (before vertex sorting)
    oldIdx = aSortVertices[i].mOriginalIndex;

    // Calculate normal magnitude (should always be 1.0 for unit length normals)
    magn = sqrtf(self->mNormals[oldIdx * 3] * self->mNormals[oldIdx * 3] +
                 self->mNormals[oldIdx * 3 + 1] * self->mNormals[oldIdx * 3 + 1] +
                 self->mNormals[oldIdx * 3 + 2] * self->mNormals[oldIdx * 3 + 2]);
    if(magn < 1e-10f)
      magn = 1.0f;

    // Invert magnitude if the normal is negative compared to the predicted
    // smooth normal
    if((smoothNormals[i * 3] * self->mNormals[oldIdx * 3] +
        smoothNormals[i * 3 + 1] * self->mNormals[oldIdx * 3 + 1] +
        smoothNormals[i * 3 + 2] * self->mNormals[oldIdx * 3 + 2]) < 0.0f)
      magn = -magn;

    // Store the magnitude in the first element of the three normal elements
    aIntNormals[i * 3] = (CTMint) floorf(scale * magn + 0.5f);

    // Normalize the normal (1 / magn) - and flip it if magn < 0
    magn = 1.0f / magn;
    for(j = 0; j < 3; ++ j)
      n[j] = self->mNormals[oldIdx * 3 + j] * magn;

    // Convert the normal to angular representation (phi, theta) in a coordinate
    // system where the nominal (smooth) normal is the Z-axis
    _ctmMakeNormalCoordSys(&smoothNormals[i * 3], basisAxes);
    for(j = 0; j < 3; ++ j)
      n2[j] = basisAxes[j * 3] * n[0] +
              basisAxes[j * 3 + 1] * n[1] +
              basisAxes[j * 3 + 2] * n[2];
    if(n2[2] >= 1.0f)
      phi = 0.0f;
    else
      phi = acosf(n2[2]);
    theta = atan2f(n2[1], n2[0]);

    // Round phi and theta (spherical coordinates) to integers. Note: We let the
    // theta resolution vary with the x/y circumference (roughly phi).
    intPhi = (CTMint) floorf(phi * (scale / (0.5f * PI)) + 0.5f);
    if(intPhi == 0)
      thetaScale = 0.0f;
    else if(intPhi <= 4)
      thetaScale = 2.0f / PI;
    else
      thetaScale = ((CTMfloat) intPhi) / (2.0f * PI);
    aIntNormals[i * 3 + 1] = intPhi;
    aIntNormals[i * 3 + 2] = (CTMint) floorf((theta + PI) * thetaScale + 0.5f);
  }

  // Free temporary resources
  free(smoothNormals);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmRestoreNormals() - Convert the normals back to cartesian coordinates.
//-----------------------------------------------------------------------------
static CTMint _ctmRestoreNormals(_CTMcontext * self, CTMint * aIntNormals)
{
  CTMuint i, j, intPhi;
  CTMfloat magn, phi, theta, scale, thetaScale;
  CTMfloat * smoothNormals, n[3], n2[3], basisAxes[9];

  // Allocate temporary memory for the nominal vertex normals
  smoothNormals = (CTMfloat *) malloc(3 * sizeof(CTMfloat) * self->mVertexCount);
  if(!smoothNormals)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Calculate smooth normals (nominal normals)
  _ctmCalcSmoothNormals(self, self->mVertices, self->mIndices, smoothNormals);

  // Normal scaling factor
  scale = self->mNormalPrecision;

  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get the normal magnitude from the first of the three normal elements
    magn = aIntNormals[i * 3] * scale;

    // Get phi and theta (spherical coordinates, relative to the smooth normal).
    intPhi = aIntNormals[i * 3 + 1];
    phi = intPhi * (0.5f * PI) * scale;
    if(intPhi == 0)
      thetaScale = 0.0f;
    else if(intPhi <= 4)
      thetaScale = PI / 2.0f;
    else
      thetaScale = (2.0f * PI) / ((CTMfloat) intPhi);
    theta = aIntNormals[i * 3 + 2] * thetaScale - PI;

    // Convert the normal from the angular representation (phi, theta) back to
    // cartesian coordinates
    n2[0] = sinf(phi) * cosf(theta);
    n2[1] = sinf(phi) * sinf(theta);
    n2[2] = cosf(phi);
    _ctmMakeNormalCoordSys(&smoothNormals[i * 3], basisAxes);
    for(j = 0; j < 3; ++ j)
      n[j] = basisAxes[j] * n2[0] +
             basisAxes[3 + j] * n2[1] +
             basisAxes[6 + j] * n2[2];

    // Apply normal magnitude, and output to the normals array
    for(j = 0; j < 3; ++ j)
      self->mNormals[i * 3 + j] = n[j] * magn;
  }

  // Free temporary resources
  free(smoothNormals);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmMakeUVCoordDeltas() - Calculate various forms of derivatives in order
// to reduce data entropy.
//-----------------------------------------------------------------------------
static void _ctmMakeUVCoordDeltas(_CTMcontext * self, _CTMfloatmap * aMap,
  CTMint * aIntUVCoords, _CTMsortvertex * aSortVertices)
{
  CTMuint i, oldIdx;
  CTMint u, v, prevU, prevV;
  CTMfloat scale;

  // UV coordinate scaling factor
  scale = 1.0f / aMap->mPrecision;

  prevU = prevV = 0;
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get old UV coordinate index (before vertex sorting)
    oldIdx = aSortVertices[i].mOriginalIndex;

    // Convert to fixed point
    u = (CTMint) floorf(scale * aMap->mValues[oldIdx * 2] + 0.5f);
    v = (CTMint) floorf(scale * aMap->mValues[oldIdx * 2 + 1] + 0.5f);

    // Calculate delta and store it in the converted array. NOTE: Here we rely
    // on the fact that vertices are sorted, and usually close to each other,
    // which means that UV coordinates should also be close to each other...
    aIntUVCoords[i * 2] = u - prevU;
    aIntUVCoords[i * 2 + 1] = v - prevV;

    prevU = u;
    prevV = v;
  }
}

//-----------------------------------------------------------------------------
// _ctmRestoreUVCoords() - Calculate inverse derivatives of the UV
// coordinates.
//-----------------------------------------------------------------------------
static void _ctmRestoreUVCoords(_CTMcontext * self, _CTMfloatmap * aMap,
  CTMint * aIntUVCoords)
{
  CTMuint i;
  CTMint u, v, prevU, prevV;
  CTMfloat scale;

  // UV coordinate scaling factor
  scale = aMap->mPrecision;

  prevU = prevV = 0;
  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Calculate inverse delta
    u = aIntUVCoords[i * 2] + prevU;
    v = aIntUVCoords[i * 2 + 1] + prevV;

    // Convert to floating point
    aMap->mValues[i * 2] = (CTMfloat) u * scale;
    aMap->mValues[i * 2 + 1] = (CTMfloat) v * scale;

    prevU = u;
    prevV = v;
  }
}

//-----------------------------------------------------------------------------
// _ctmMakeAttribDeltas() - Calculate various forms of derivatives in order
// to reduce data entropy.
//-----------------------------------------------------------------------------
static void _ctmMakeAttribDeltas(_CTMcontext * self, _CTMfloatmap * aMap,
  CTMint * aIntAttribs, _CTMsortvertex * aSortVertices)
{
  CTMuint i, j, oldIdx;
  CTMint value[4], prev[4];
  CTMfloat scale;

  // Attribute scaling factor
  scale = 1.0f / aMap->mPrecision;

  for(j = 0; j < 4; ++ j)
    prev[j] = 0;

  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Get old attribute index (before vertex sorting)
    oldIdx = aSortVertices[i].mOriginalIndex;

    // Convert to fixed point, and calculate delta and store it in the converted
    // array. NOTE: Here we rely on the fact that vertices are sorted, and
    // usually close to each other, which means that attributes should also
    // be close to each other (and we assume that they somehow vary slowly with
    // the geometry)...
    for(j = 0; j < 4; ++ j)
    {
      value[j] = (CTMint) floorf(scale * aMap->mValues[oldIdx * 4 + j] + 0.5f);
      aIntAttribs[i * 4 + j] = value[j] - prev[j];
      prev[j] = value[j];
    }
  }
}

//-----------------------------------------------------------------------------
// _ctmRestoreAttribs() - Calculate inverse derivatives of the vertex
// attributes.
//-----------------------------------------------------------------------------
static void _ctmRestoreAttribs(_CTMcontext * self, _CTMfloatmap * aMap,
  CTMint * aIntAttribs)
{
  CTMuint i, j;
  CTMint value[4], prev[4];
  CTMfloat scale;

  // Attribute scaling factor
  scale = aMap->mPrecision;

  for(j = 0; j < 4; ++ j)
    prev[j] = 0;

  for(i = 0; i < self->mVertexCount; ++ i)
  {
    // Calculate inverse delta, and convert to floating point
    for(j = 0; j < 4; ++ j)
    {
      value[j] = aIntAttribs[i * 4 + j] + prev[j];
      aMap->mValues[i * 4 + j] = (CTMfloat) value[j] * scale;
      prev[j] = value[j];
    }
  }
}

//-----------------------------------------------------------------------------
// _ctmCompressMesh_MG2() - Compress the mesh that is stored in the CTM
// context, and write it the the output stream in the CTM context.
//-----------------------------------------------------------------------------
int _ctmCompressMesh_MG2(_CTMcontext * self)
{
  _CTMgrid grid;
  _CTMsortvertex * sortVertices;
  _CTMfloatmap * map;
  CTMuint * indices, * deltaIndices, * gridIndices;
  CTMint * intVertices, * intNormals, * intUVCoords, * intAttribs;
  CTMfloat * restoredVertices;
  CTMuint i;

#ifdef __DEBUG_
  printf("COMPRESSION METHOD: MG2\n");
#endif

  // Setup 3D space subdivision grid
  _ctmSetupGrid(self, &grid);

  // Write MG2-specific header information to the stream
  _ctmStreamWrite(self, (void *) "MG2H", 4);
  _ctmStreamWriteFLOAT(self, self->mVertexPrecision);
  _ctmStreamWriteFLOAT(self, self->mNormalPrecision);
  _ctmStreamWriteFLOAT(self, grid.mMin[0]);
  _ctmStreamWriteFLOAT(self, grid.mMin[1]);
  _ctmStreamWriteFLOAT(self, grid.mMin[2]);
  _ctmStreamWriteFLOAT(self, grid.mMax[0]);
  _ctmStreamWriteFLOAT(self, grid.mMax[1]);
  _ctmStreamWriteFLOAT(self, grid.mMax[2]);
  _ctmStreamWriteUINT(self, grid.mDivision[0]);
  _ctmStreamWriteUINT(self, grid.mDivision[1]);
  _ctmStreamWriteUINT(self, grid.mDivision[2]);

  // Prepare (sort) vertices
  sortVertices = (_CTMsortvertex *) malloc(sizeof(_CTMsortvertex) * self->mVertexCount);
  if(!sortVertices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  _ctmSortVertices(self, sortVertices, &grid);

  // Convert vertices to integers and calculate vertex deltas (entropy-reduction)
  intVertices = (CTMint *) malloc(sizeof(CTMint) * 3 * self->mVertexCount);
  if(!intVertices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  _ctmMakeVertexDeltas(self, intVertices, sortVertices, &grid);

  // Write vertices
#ifdef __DEBUG_
  printf("Vertices: ");
#endif
  _ctmStreamWrite(self, (void *) "VERT", 4);
  if(!_ctmStreamWritePackedInts(self, intVertices, self->mVertexCount, 3, CTM_FALSE))
  {
    free((void *) intVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }

  // Prepare grid indices (deltas)
  gridIndices = (CTMuint *) malloc(sizeof(CTMuint) * self->mVertexCount);
  if(!gridIndices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) intVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  gridIndices[0] = sortVertices[0].mGridIndex;
  for(i = 1; i < self->mVertexCount; ++ i)
    gridIndices[i] = sortVertices[i].mGridIndex - sortVertices[i - 1].mGridIndex;
  
  // Write grid indices
#ifdef __DEBUG_
  printf("Grid indices: ");
#endif
  _ctmStreamWrite(self, (void *) "GIDX", 4);
  if(!_ctmStreamWritePackedInts(self, (CTMint *) gridIndices, self->mVertexCount, 1, CTM_FALSE))
  {
    free((void *) gridIndices);
    free((void *) intVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }

  // Calculate the result of the compressed -> decompressed vertices, in order
  // to use the same vertex data for calculating nominal normals as the
  // decompression routine (i.e. compensate for the vertex error when
  // calculating the normals)
  restoredVertices = (CTMfloat *) malloc(sizeof(CTMfloat) * 3 * self->mVertexCount);
  if(!restoredVertices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) gridIndices);
    free((void *) intVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  for(i = 1; i < self->mVertexCount; ++ i)
    gridIndices[i] += gridIndices[i - 1];
  _ctmRestoreVertices(self, intVertices, gridIndices, &grid, restoredVertices);

  // Free temporary resources
  free((void *) gridIndices);
  free((void *) intVertices);

  // Perpare (sort) indices
  indices = (CTMuint *) malloc(sizeof(CTMuint) * self->mTriangleCount * 3);
  if(!indices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) restoredVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  if(!_ctmReIndexIndices(self, sortVertices, indices))
  {
    free((void *) indices);
    free((void *) restoredVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  _ctmReArrangeTriangles(self, indices);

  // Calculate index deltas (entropy-reduction)
  deltaIndices = (CTMuint *) malloc(sizeof(CTMuint) * self->mTriangleCount * 3);
  if(!indices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) indices);
    free((void *) restoredVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }
  for(i = 0; i < self->mTriangleCount * 3; ++ i)
    deltaIndices[i] = indices[i];
  _ctmMakeIndexDeltas(self, deltaIndices);

  // Write triangle indices
#ifdef __DEBUG_
  printf("Indices: ");
#endif
  _ctmStreamWrite(self, (void *) "INDX", 4);
  if(!_ctmStreamWritePackedInts(self, (CTMint *) deltaIndices, self->mTriangleCount, 3, CTM_FALSE))
  {
    free((void *) deltaIndices);
    free((void *) indices);
    free((void *) restoredVertices);
    free((void *) sortVertices);
    return CTM_FALSE;
  }

  // Free temporary data for the indices
  free((void *) deltaIndices);

  if(self->mNormals)
  {
    // Convert normals to integers and calculate deltas (entropy-reduction)
    intNormals = (CTMint *) malloc(sizeof(CTMint) * 3 * self->mVertexCount);
    if(!intNormals)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      free((void *) indices);
      free((void *) restoredVertices);
      free((void *) sortVertices);
      return CTM_FALSE;
    }
    if(!_ctmMakeNormalDeltas(self, intNormals, restoredVertices, indices, sortVertices))
    {
      free((void *) indices);
      free((void *) intNormals);
      free((void *) restoredVertices);
      free((void *) sortVertices);
      return CTM_FALSE;
    }

    // Write normals
#ifdef __DEBUG_
    printf("Normals: ");
#endif
    _ctmStreamWrite(self, (void *) "NORM", 4);
    if(!_ctmStreamWritePackedInts(self, intNormals, self->mVertexCount, 3, CTM_FALSE))
    {
      free((void *) indices);
      free((void *) intNormals);
      free((void *) restoredVertices);
      free((void *) sortVertices);
      return CTM_FALSE;
    }

    // Free temporary normal data
    free((void *) intNormals);
  }

  // Free restored indices and vertices
  free((void *) indices);
  free((void *) restoredVertices);

  // Write UV maps
  map = self->mUVMaps;
  while(map)
  {
    // Convert UV coordinates to integers and calculate deltas (entropy-reduction)
    intUVCoords = (CTMint *) malloc(sizeof(CTMint) * 2 * self->mVertexCount);
    if(!intUVCoords)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      free((void *) sortVertices);
      return CTM_FALSE;
    }
    _ctmMakeUVCoordDeltas(self, map, intUVCoords, sortVertices);

    // Write UV coordinates
#ifdef __DEBUG_
    printf("Texture coordinates (%s): ", map->mName ? map->mName : "no name");
#endif
    _ctmStreamWrite(self, (void *) "TEXC", 4);
    _ctmStreamWriteSTRING(self, map->mName);
    _ctmStreamWriteSTRING(self, map->mFileName);
    _ctmStreamWriteFLOAT(self, map->mPrecision);
    if(!_ctmStreamWritePackedInts(self, intUVCoords, self->mVertexCount, 2, CTM_TRUE))
    {
      free((void *) intUVCoords);
      free((void *) sortVertices);
      return CTM_FALSE;
    }

    // Free temporary UV coordinate data
    free((void *) intUVCoords);

    map = map->mNext;
  }

  // Write vertex attribute maps
  map = self->mAttribMaps;
  while(map)
  {
    // Convert vertex attributes to integers and calculate deltas (entropy-reduction)
    intAttribs = (CTMint *) malloc(sizeof(CTMint) * 4 * self->mVertexCount);
    if(!intAttribs)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      free((void *) sortVertices);
      return CTM_FALSE;
    }
    _ctmMakeAttribDeltas(self, map, intAttribs, sortVertices);

    // Write vertex attributes
#ifdef __DEBUG_
    printf("Vertex attributes (%s): ", map->mName ? map->mName : "no name");
#endif
    _ctmStreamWrite(self, (void *) "ATTR", 4);
    _ctmStreamWriteSTRING(self, map->mName);
    _ctmStreamWriteFLOAT(self, map->mPrecision);
    if(!_ctmStreamWritePackedInts(self, intAttribs, self->mVertexCount, 4, CTM_TRUE))
    {
      free((void *) intAttribs);
      free((void *) sortVertices);
      return CTM_FALSE;
    }

    // Free temporary vertex attribute data
    free((void *) intAttribs);

    map = map->mNext;
  }

  // Free temporary data
  free((void *) sortVertices);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmUncompressMesh_MG2() - Uncmpress the mesh from the input stream in the
// CTM context, and store the resulting mesh in the CTM context.
//-----------------------------------------------------------------------------
int _ctmUncompressMesh_MG2(_CTMcontext * self)
{
  CTMuint * gridIndices, i;
  CTMint * intVertices, * intNormals, * intUVCoords, * intAttribs;
  _CTMfloatmap * map;
  _CTMgrid grid;

  // Read MG2-specific header information from the stream
  if(_ctmStreamReadUINT(self) != FOURCC("MG2H"))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  self->mVertexPrecision = _ctmStreamReadFLOAT(self);
  if(self->mVertexPrecision <= 0.0f)
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  self->mNormalPrecision = _ctmStreamReadFLOAT(self);
  if(self->mNormalPrecision <= 0.0f)
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  grid.mMin[0] = _ctmStreamReadFLOAT(self);
  grid.mMin[1] = _ctmStreamReadFLOAT(self);
  grid.mMin[2] = _ctmStreamReadFLOAT(self);
  grid.mMax[0] = _ctmStreamReadFLOAT(self);
  grid.mMax[1] = _ctmStreamReadFLOAT(self);
  grid.mMax[2] = _ctmStreamReadFLOAT(self);
  if((grid.mMax[0] < grid.mMin[0]) ||
     (grid.mMax[1] < grid.mMin[1]) ||
     (grid.mMax[2] < grid.mMin[2]))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  grid.mDivision[0] = _ctmStreamReadUINT(self);
  grid.mDivision[1] = _ctmStreamReadUINT(self);
  grid.mDivision[2] = _ctmStreamReadUINT(self);
  if((grid.mDivision[0] < 1) || (grid.mDivision[1] < 1) || (grid.mDivision[2] < 1))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }

  // Initialize 3D space subdivision grid
  for(i = 0; i < 3; ++ i)
    grid.mSize[i] = (grid.mMax[i] - grid.mMin[i]) / grid.mDivision[i];

  // Read vertices
  if(_ctmStreamReadUINT(self) != FOURCC("VERT"))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  intVertices = (CTMint *) malloc(sizeof(CTMint) * self->mVertexCount * 3);
  if(!intVertices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  if(!_ctmStreamReadPackedInts(self, intVertices, self->mVertexCount, 3, CTM_FALSE))
  {
    free((void *) intVertices);
    return CTM_FALSE;
  }

  // Read grid indices
  if(_ctmStreamReadUINT(self) != FOURCC("GIDX"))
  {
    free((void *) intVertices);
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  gridIndices = (CTMuint *) malloc(sizeof(CTMuint) * self->mVertexCount);
  if(!gridIndices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    free((void *) intVertices);
    return CTM_FALSE;
  }
  if(!_ctmStreamReadPackedInts(self, (CTMint *) gridIndices, self->mVertexCount, 1, CTM_FALSE))
  {
    free((void *) gridIndices);
    free((void *) intVertices);
    return CTM_FALSE;
  }

  // Restore grid indices (deltas)
  for(i = 1; i < self->mVertexCount; ++ i)
    gridIndices[i] += gridIndices[i - 1];

  // Restore vertices
  _ctmRestoreVertices(self, intVertices, gridIndices, &grid, self->mVertices);

  // Free temporary resources
  free((void *) gridIndices);
  free((void *) intVertices);

  // Read triangle indices
  if(_ctmStreamReadUINT(self) != FOURCC("INDX"))
  {
    self->mError = CTM_BAD_FORMAT;
    return CTM_FALSE;
  }
  if(!_ctmStreamReadPackedInts(self, (CTMint *) self->mIndices, self->mTriangleCount, 3, CTM_FALSE))
    return CTM_FALSE;

  // Restore indices
  _ctmRestoreIndices(self, self->mIndices);

  // Check that all indices are within range
  for(i = 0; i < (self->mTriangleCount * 3); ++ i)
  {
    if(self->mIndices[i] >= self->mVertexCount)
    {
      self->mError = CTM_INVALID_MESH;
      return CTM_FALSE;
    }
  }

  // Read normals
  if(self->mNormals)
  {
    intNormals = (CTMint *) malloc(sizeof(CTMint) * self->mVertexCount * 3);
    if(!intNormals)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      return CTM_FALSE;
    }
    if(_ctmStreamReadUINT(self) != FOURCC("NORM"))
    {
      self->mError = CTM_BAD_FORMAT;
      free((void *) intNormals);
      return CTM_FALSE;
    }
    if(!_ctmStreamReadPackedInts(self, intNormals, self->mVertexCount, 3, CTM_FALSE))
    {
      free((void *) intNormals);
      return CTM_FALSE;
    }

    // Restore normals
    if(!_ctmRestoreNormals(self, intNormals))
    {
      free((void *) intNormals);
      return CTM_FALSE;
    }

    // Free temporary normals data
    free((void *) intNormals);
  }

  // Read UV maps
  map = self->mUVMaps;
  while(map)
  {
    intUVCoords = (CTMint *) malloc(sizeof(CTMint) * self->mVertexCount * 2);
    if(!intUVCoords)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      return CTM_FALSE;
    }
    if(_ctmStreamReadUINT(self) != FOURCC("TEXC"))
    {
      self->mError = CTM_BAD_FORMAT;
      free((void *) intUVCoords);
      return CTM_FALSE;
    }
    _ctmStreamReadSTRING(self, &map->mName);
    _ctmStreamReadSTRING(self, &map->mFileName);
    map->mPrecision = _ctmStreamReadFLOAT(self);
    if(map->mPrecision <= 0.0f)
    {
      self->mError = CTM_BAD_FORMAT;
      free((void *) intUVCoords);
      return CTM_FALSE;
    }
    if(!_ctmStreamReadPackedInts(self, intUVCoords, self->mVertexCount, 2, CTM_TRUE))
    {
      free((void *) intUVCoords);
      return CTM_FALSE;
    }

    // Restore UV coordinates
    _ctmRestoreUVCoords(self, map, intUVCoords);

    // Free temporary UV coordinate data
    free((void *) intUVCoords);

    map = map->mNext;
  }

  // Read vertex attribute maps
  map = self->mAttribMaps;
  while(map)
  {
    intAttribs = (CTMint *) malloc(sizeof(CTMint) * self->mVertexCount * 4);
    if(!intAttribs)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      return CTM_FALSE;
    }
    if(_ctmStreamReadUINT(self) != FOURCC("ATTR"))
    {
      self->mError = CTM_BAD_FORMAT;
      free((void *) intAttribs);
      return CTM_FALSE;
    }
    _ctmStreamReadSTRING(self, &map->mName);
    map->mPrecision = _ctmStreamReadFLOAT(self);
    if(map->mPrecision <= 0.0f)
    {
      self->mError = CTM_BAD_FORMAT;
      free((void *) intAttribs);
      return CTM_FALSE;
    }
    if(!_ctmStreamReadPackedInts(self, intAttribs, self->mVertexCount, 4, CTM_TRUE))
    {
      free((void *) intAttribs);
      return CTM_FALSE;
    }

    // Restore vertex attributes
    _ctmRestoreAttribs(self, map, intAttribs);

    // Free temporary vertex attribute data
    free((void *) intAttribs);

    map = map->mNext;
  }

  return CTM_TRUE;
}
