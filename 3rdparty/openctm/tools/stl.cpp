//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        stl.cpp
// Description: Implementation of the STL file format importer/exporter.
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

#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "stl.h"

#ifdef _MSC_VER
typedef unsigned int uint32;
#else
#include <stdint.h>
typedef uint32_t uint32;
#endif

using namespace std;


/// Read a 32-bit integer, endian independent.
static uint32 ReadInt32(istream &aStream)
{
  unsigned char buf[4];
  aStream.read((char *) buf, 4);
  return ((uint32) buf[0]) | (((uint32) buf[1]) << 8) |
         (((uint32) buf[2]) << 16) | (((uint32) buf[3]) << 24);
}

/// Write a 32-bit integer, endian independent.
static void WriteInt32(ostream &aStream, uint32 aValue)
{
  unsigned char buf[4];
  buf[0] = aValue & 255;
  buf[1] = (aValue >> 8) & 255;
  buf[2] = (aValue >> 16) & 255;
  buf[3] = (aValue >> 24) & 255;
  aStream.write((char *) buf, 4);
}

/// Read a Vector3, endian independent.
static Vector3 ReadVector3(istream &aStream)
{
  union {
    uint32 i;
    float  f;
  } val;
  Vector3 result;
  val.i = ReadInt32(aStream);
  result.x = val.f;
  val.i = ReadInt32(aStream);
  result.y = val.f;
  val.i = ReadInt32(aStream);
  result.z = val.f;
  return result;
}

/// Write a Vector3, endian independent.
static void WriteVector3(ostream &aStream, Vector3 aValue)
{
  union {
    uint32 i;
    float  f;
  } val;
  val.f = aValue.x;
  WriteInt32(aStream, val.i);
  val.f = aValue.y;
  WriteInt32(aStream, val.i);
  val.f = aValue.z;
  WriteInt32(aStream, val.i);
}

/// Vertex class used when reading and joining the triangle vertices.
class SortVertex {
  public:
    float x, y, z;
    uint32 mOldIndex;

    bool operator<(const SortVertex &v) const
    {
      return (x < v.x) || ((x == v.x) && ((y < v.y) || ((y == v.y) && (z < v.z))));
    }
};

/// Import an STL file from a file.
void Import_STL(const char * aFileName, Mesh * aMesh)
{
  // Clear the mesh
  aMesh->Clear();

  // Open the input file
  ifstream f(aFileName, ios::in | ios::binary);
  if(f.fail())
    throw runtime_error("Could not open input file.");

  // Get the file size
  f.seekg(0, ios::end);
  uint32 fileSize = (uint32) f.tellg();
  f.seekg(0, ios::beg);
  if(fileSize < 84)
    throw runtime_error("Invalid format - not a valid STL file.");

  // Read header (80 character comment + triangle count)
  char comment[81];
  f.read(comment, 80);
  comment[80] = 0;
  aMesh->mComment = string(comment);
  uint32 triangleCount = ReadInt32(f);
  if(fileSize != (84 + triangleCount * 50))
    throw runtime_error("Invalid format - not a valid STL file.");

  if(triangleCount > 0)
  {
    // Read all the triangle data
    vector<SortVertex> vertices;
    vertices.resize(triangleCount * 3);
    for(uint32 i = 0; i < triangleCount; ++ i)
    {
      // Skip the flat normal
      f.seekg(12, ios::cur);

      // Read the three triangle vertices
      for(uint32 j = 0; j < 3; ++ j)
      {
        Vector3 v = ReadVector3(f);
        uint32 index = i * 3 + j;
        vertices[index].x = v.x;
        vertices[index].y = v.y;
        vertices[index].z = v.z;
        vertices[index].mOldIndex = index;
      }

      // Ignore the two fill bytes
      f.seekg(2, ios::cur);
    }

    // Make sure that no redundant copies of vertices exist (STL files are full
    // of vertex duplicates, so remove the redundancy), and store the data in
    // the mesh object
    sort(vertices.begin(), vertices.end());
    aMesh->mVertices.resize(vertices.size());
    aMesh->mIndices.resize(vertices.size());
    SortVertex * firstEqual = &vertices[0];
    int vertIdx = -1;
    for(uint32 i = 0; i < vertices.size(); ++ i)
    {
      if((i == 0) ||
         (vertices[i].z != firstEqual->z) ||
         (vertices[i].y != firstEqual->y) ||
         (vertices[i].x != firstEqual->x))
      {
        firstEqual = &vertices[i];
        ++ vertIdx;
        aMesh->mVertices[vertIdx] = Vector3(firstEqual->x, firstEqual->y, firstEqual->z);
      }
      aMesh->mIndices[vertices[i].mOldIndex] = vertIdx;
    }
    aMesh->mVertices.resize(vertIdx + 1);
  }

  // Close the input file
  f.close();
}

/// Export an STL file to a file.
void Export_STL(const char * aFileName, Mesh * aMesh, Options &aOptions)
{
  // Open the output file
  ofstream f(aFileName, ios::out | ios::binary);
  if(f.fail())
    throw runtime_error("Could not open output file.");

  // Write header (80-character comment + triangle count)
  char comment[80];
  for(uint32 i = 0; i < 80; ++ i)
  {
    if(i < aMesh->mComment.size())
      comment[i] = aMesh->mComment[i];
    else
      comment[i] = 0;
  }
  f.write(comment, 80);
  uint32 triangleCount = aMesh->mIndices.size() / 3;
  WriteInt32(f, triangleCount);

  // Write the triangle data
  for(uint32 i = 0; i < triangleCount; ++ i)
  {
    // Get the triangle vertices
    Vector3 v1 = aMesh->mVertices[aMesh->mIndices[i * 3]];
    Vector3 v2 = aMesh->mVertices[aMesh->mIndices[i * 3 + 1]];
    Vector3 v3 = aMesh->mVertices[aMesh->mIndices[i * 3 + 2]];

    // Calculate the triangle normal
    Vector3 n1 = v2 - v1;
    Vector3 n2 = v3 - v1;
    Vector3 n = Normalize(Cross(n1, n2));

    // Write the triangle normal
    WriteVector3(f, n);

    // Coordinates
    WriteVector3(f, v1);
    WriteVector3(f, v2);
    WriteVector3(f, v3);

    // Set the two fill bytes to zero
    f.put(0);
    f.put(0);
  }

  // Close the output file
  f.close();
}
