//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        mesh.cpp
// Description: Implementation of the 3D triangle mesh class.
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

#include "common.h"
#include <openctm.h>
#include <cmath>
#include "mesh.h"
#include "convoptions.h"


using namespace std;


/// Compute the cross product of two vectors
Vector3 Cross(Vector3 &v1, Vector3 &v2)
{
  return Vector3(
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x
  );
}

/// Normalize a vector
Vector3 Normalize(Vector3 v)
{
  float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  if(len > 1e-20f)
    len = 1.0f / len;
  else
    len = 1.0f;
  return Vector3(v.x * len, v.y * len, v.z * len);
}


/// Clear the mesh
void Mesh::Clear()
{
  mComment = string("");
  mTexFileName = string("");
  mIndices.clear();
  mVertices.clear();
  mNormals.clear();
  mColors.clear();
  mTexCoords.clear();
  mOriginalNormals = true;
}

/// Automatic detection of the optimal normal calculation method
Mesh::NormalCalcAlgo Mesh::DetectNormalCalculationMethod()
{
  unsigned int triCount = (unsigned int)(mIndices.size() / 3);
  unsigned int vertexCount = (unsigned int)(mVertices.size() );

  // Calculate the mean edge length
  double meanEdgeLen = 0;
  for(unsigned int i = 0; i < triCount; ++ i)
  {
    meanEdgeLen += (mVertices[mIndices[i * 3 + 1]] - mVertices[mIndices[i * 3]]).Abs();
    meanEdgeLen += (mVertices[mIndices[i * 3 + 2]] - mVertices[mIndices[i * 3 + 1]]).Abs();
    meanEdgeLen += (mVertices[mIndices[i * 3]] - mVertices[mIndices[i * 3 + 2]]).Abs();
  }
  if(triCount > 0)
    meanEdgeLen = meanEdgeLen / (3 * triCount);

  // Calculate the standard deviation of the edge length
  double stdDevEdgeLen = 0;
  for(unsigned int i = 0; i < triCount; ++ i)
  {
    double len = (mVertices[mIndices[i * 3 + 1]] - mVertices[mIndices[i * 3]]).Abs();
    stdDevEdgeLen += (len - meanEdgeLen) * (len - meanEdgeLen);
    len = (mVertices[mIndices[i * 3 + 2]] - mVertices[mIndices[i * 3 + 1]]).Abs();
    stdDevEdgeLen += (len - meanEdgeLen) * (len - meanEdgeLen);
    len = (mVertices[mIndices[i * 3]] - mVertices[mIndices[i * 3 + 2]]).Abs();
    stdDevEdgeLen += (len - meanEdgeLen) * (len - meanEdgeLen);
  }
  if(triCount > 0)
    stdDevEdgeLen = sqrt(stdDevEdgeLen / (3 * triCount));

  // Calculate the number of triangles that connect to each vertex
  vector<int> connectCount;
  connectCount.resize(vertexCount);
  for(unsigned int i = 0; i < vertexCount; ++ i)
    connectCount[i] = 0;
  for(unsigned int i = 0; i < mIndices.size(); ++ i)
  {
    unsigned int idx = mIndices[i];
    if(idx < vertexCount)
      ++ connectCount[idx];
  }

  // First analysis: how much variation is there in the triangle edge lengths?
  double edgeVariation = 0.0;
  if(meanEdgeLen > 0.0)
    edgeVariation = stdDevEdgeLen / meanEdgeLen;

  // Calculate the mean number of triangle connections
  double meanConnectCount = 0;
  for(unsigned int i = 0; i < vertexCount; ++ i)
    meanConnectCount += connectCount[i];
  if(vertexCount > 0)
    meanConnectCount = meanConnectCount / vertexCount;

  // Calculate the standard deviation of the number of triangle connections
  double stdDevConnectCount = 0;
  for(unsigned int i = 0; i < vertexCount; ++ i)
    stdDevConnectCount += (connectCount[i] - meanConnectCount) * (connectCount[i] - meanConnectCount);
  if(vertexCount > 0)
    stdDevConnectCount = sqrt(stdDevConnectCount / vertexCount);

  // Second analysis: how much variation is there in the number of connections
  // per vertex?
  double connectVariation = 0.0;
  if(meanConnectCount > 0.0)
    connectVariation = stdDevConnectCount / meanConnectCount;

  // Normalize the different measures to their respective threshold values
  edgeVariation /= 0.7;
  connectVariation /= 0.3;

  // Is this a CAD-like object or a organic-like object?
  NormalCalcAlgo algo = ncaOrganic;
  if(edgeVariation * connectVariation > 1.0)
    algo = ncaCAD;

  return algo;
}

/// Calculate smooth per-vertex normals
void Mesh::CalculateNormals(NormalCalcAlgo aAlgo)
{
  // Determine which normal calculation algorithm to use
  NormalCalcAlgo algo;
  if(aAlgo == ncaAuto)
    algo = DetectNormalCalculationMethod();
  else
    algo = aAlgo;

  // The original normals are no longer preserved
  mOriginalNormals = false;

  // Clear the smooth normals
  mNormals.resize(mVertices.size());
  for(unsigned int i = 0; i < mNormals.size(); ++ i)
    mNormals[i] = Vector3(0.0f, 0.0f, 0.0f);

  // Calculate sum of the flat normals of the neighbouring triangles
  unsigned int triCount = (unsigned int)(mIndices.size() / 3);
  for(unsigned int i = 0; i < triCount; ++ i)
  {
    // Calculate the weighted flat normal for this triangle
    Vector3 v1 = mVertices[mIndices[i * 3 + 1]] - mVertices[mIndices[i * 3]];
    Vector3 v2 = mVertices[mIndices[i * 3 + 2]] - mVertices[mIndices[i * 3]];
    Vector3 flatNormal = Cross(v1, v2);
    if(algo == ncaOrganic)
      flatNormal = Normalize(flatNormal);

    // ...and add it to all three triangle vertices' smooth normals
    for(unsigned int j = 0; j < 3; ++ j)
      mNormals[mIndices[i * 3 + j]] += flatNormal;
  }

  // Normalize all the smooth normals
  for(unsigned int i = 0; i < mNormals.size(); ++ i)
    mNormals[i] = Normalize(mNormals[i]);
}

/// Calculate the bounding box for the mesh
void Mesh::BoundingBox(Vector3 &aMin, Vector3 &aMax)
{
  if(mVertices.size() < 1)
    aMin = aMax = Vector3(0.0f, 0.0f, 0.0f);
  else
    aMin = aMax = mVertices[0];
  for(unsigned int i = 1; i < mVertices.size(); ++ i)
  {
    if(mVertices[i].x < aMin.x)
      aMin.x = mVertices[i].x;
    else if(mVertices[i].x > aMax.x)
      aMax.x = mVertices[i].x;
    if(mVertices[i].y < aMin.y)
      aMin.y = mVertices[i].y;
    else if(mVertices[i].y > aMax.y)
      aMax.y = mVertices[i].y;
    if(mVertices[i].z < aMin.z)
      aMin.z = mVertices[i].z;
    else if(mVertices[i].z > aMax.z)
      aMax.z = mVertices[i].z;
  }
}
