//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        3ds.cpp
// Description: Implementation of the 3DS file format importer/exporter.
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
#include <vector>
#include <list>
#include "3ds.h"

#ifdef _MSC_VER
typedef unsigned short uint16;
typedef unsigned int uint32;
#else
#include <stdint.h>
typedef uint16_t uint16;
typedef uint32_t uint32;
#endif

using namespace std;


// Known 3DS chunks
#define CHUNK_MAIN          0x4d4d
#define CHUNK_M3D_VERSION   0x0002
#define CHUNK_3DEDIT        0x3d3d
#define CHUNK_MESH_VERSION  0x3d3e
#define CHUNK_OBJECT        0x4000
#define CHUNK_TRIMESH       0x4100
#define CHUNK_VERTEXLIST    0x4110
#define CHUNK_MAPPINGCOORDS 0x4140
#define CHUNK_FACES         0x4120
#define CHUNK_MSH_MAT_GROUP 0x4130
#define CHUNK_MAT_ENTRY     0xafff
#define CHUNK_MAT_NAME      0xa000
#define CHUNK_MAT_TEXMAP    0xa200
#define CHUNK_MAT_MAPNAME   0xa300

// 3DS object class
class Obj3DS {
  public:
    vector<uint16> mIndices;
    vector<Vector3> mVertices;
    vector<Vector2> mUVCoords;
};


/// Read a 16-bit integer, endian independent.
static uint16 ReadInt16(istream &aStream)
{
  unsigned char buf[2];
  aStream.read((char *) buf, 2);
  return ((uint16) buf[0]) | (((uint16) buf[1]) << 8);
}

/// Write a 16-bit integer, endian independent.
static void WriteInt16(ostream &aStream, uint16 aValue)
{
  unsigned char buf[2];
  buf[0] = aValue & 255;
  buf[1] = (aValue >> 8) & 255;
  aStream.write((char *) buf, 2);
}

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

/// Read a Vector2, endian independent.
static Vector2 ReadVector2(istream &aStream)
{
  union {
    uint32 i;
    float  f;
  } val;
  Vector2 result;
  val.i = ReadInt32(aStream);
  result.u = val.f;
  val.i = ReadInt32(aStream);
  result.v = val.f;
  return result;
}

/// Write a Vector2, endian independent.
static void WriteVector2(ostream &aStream, Vector2 aValue)
{
  union {
    uint32 i;
    float  f;
  } val;
  val.f = aValue.u;
  WriteInt32(aStream, val.i);
  val.f = aValue.v;
  WriteInt32(aStream, val.i);
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

/// Import a 3DS file from a file.
void Import_3DS(const char * aFileName, Mesh * aMesh)
{
  // Clear the mesh
  aMesh->Clear();

  // Open the input file
  ifstream f(aFileName, ios::in | ios::binary);
  if(f.fail())
    throw runtime_error("Could not open input file.");

  // Get file size
  f.seekg(0, ios::end);
  uint32 fileSize = f.tellg();
  f.seekg(0, ios::beg);

  // Check file size (rough initial check)
  if(fileSize < 6)
    throw runtime_error("Invalid 3DS file format.");

  uint16 chunk, count;
  uint32 chunkLen;

  // Read & check file header identifier
  chunk = ReadInt16(f);
  chunkLen = ReadInt32(f);
  if((chunk != CHUNK_MAIN) || (chunkLen != fileSize))
    throw runtime_error("Invalid 3DS file format.");

  // Parse chunks, and store the data in a temporary list, objList...
  Obj3DS * obj = 0;
  list<Obj3DS> objList;
  bool hasUVCoords = false;
  while(uint32(f.tellg()) < fileSize)
  {
    // Read next chunk
    chunk = ReadInt16(f);
    chunkLen = ReadInt32(f);

    // What chunk did we get?
    switch(chunk)
    {
      // 3D Edit -> Step into
      case CHUNK_3DEDIT:
        break;

      // Object -> Step into
      case CHUNK_OBJECT:
        // Skip object name (null terminated string)
        while((uint32(f.tellg()) < fileSize) && f.get()) {};

        // Create a new object
        objList.push_back(Obj3DS());
        obj = &objList.back();
        break;

      // Triangle mesh -> Step into
      case CHUNK_TRIMESH:
        break;

      // Vertex list (point coordinates)
      case CHUNK_VERTEXLIST:
        count = ReadInt16(f);
        if((!obj) || ((obj->mVertices.size() > 0) && (obj->mVertices.size() != count)))
        {
          f.seekg(count * 12, ios::cur);
          break;
        }
        if(obj->mVertices.size() == 0)
          obj->mVertices.resize(count);
        for(uint16 i = 0; i < count; ++ i)
          obj->mVertices[i] = ReadVector3(f);
        break;

      // Texture map coordinates (UV coordinates)
      case CHUNK_MAPPINGCOORDS:
        count = ReadInt16(f);
        if((!obj) || ((obj->mUVCoords.size() > 0) && (obj->mUVCoords.size() != count)))
        {
          f.seekg(count * 8, ios::cur);
          break;
        }
        if(obj->mUVCoords.size() == 0)
          obj->mUVCoords.resize(count);
        for(uint16 i = 0; i < count; ++ i)
          obj->mUVCoords[i] = ReadVector2(f);
        if(count > 0)
          hasUVCoords = true;
        break;

      // Face description (triangle indices)
      case CHUNK_FACES:
        count = ReadInt16(f);
        if(!obj)
        {
          f.seekg(count * 8, ios::cur);
          break;
        }
        if(obj->mIndices.size() == 0)
          obj->mIndices.resize(3 * count);
        for(uint32 i = 0; i < count; ++ i)
        {
          obj->mIndices[i * 3] = ReadInt16(f);
          obj->mIndices[i * 3 + 1] = ReadInt16(f);
          obj->mIndices[i * 3 + 2] = ReadInt16(f);
          ReadInt16(f); // Skip face flag
        }
        break;
        
      default:      // Unknown/ignored - skip past this one
        f.seekg(chunkLen - 6, ios::cur);
    }
  }

  // Close the input file
  f.close();

  // Convert the loaded object list to the mesh structore (merge all geometries)
  aMesh->Clear();
  for(list<Obj3DS>::iterator o = objList.begin(); o != objList.end(); ++ o)
  {
    // Append...
    uint32 idxOffset = aMesh->mIndices.size();
    uint32 vertOffset = aMesh->mVertices.size();
    aMesh->mIndices.resize(idxOffset + (*o).mIndices.size());
    aMesh->mVertices.resize(vertOffset + (*o).mVertices.size());
    if(hasUVCoords)
      aMesh->mTexCoords.resize(vertOffset + (*o).mVertices.size());

    // Transcode the data
    for(uint32 i = 0; i < (*o).mIndices.size(); ++ i)
      aMesh->mIndices[idxOffset + i] = vertOffset + uint32((*o).mIndices[i]);
    for(uint32 i = 0; i < (*o).mVertices.size(); ++ i)
      aMesh->mVertices[vertOffset + i] = (*o).mVertices[i];
    if(hasUVCoords)
    {
      if((*o).mUVCoords.size() == (*o).mVertices.size())
        for(uint32 i = 0; i < (*o).mVertices.size(); ++ i)
          aMesh->mTexCoords[vertOffset + i] = (*o).mUVCoords[i];
      else
        for(uint32 i = 0; i < (*o).mVertices.size(); ++ i)
          aMesh->mTexCoords[vertOffset + i] = Vector2(0.0f, 0.0f);
    }
  }
}

/// Export a 3DS file to a file.
void Export_3DS(const char * aFileName, Mesh * aMesh, Options &aOptions)
{
  // First, check that the mesh fits in a 3DS file (at most 65535 triangles
  // and 65535 vertices are supported).
  if((aMesh->mIndices.size() > (3*65535)) || (aMesh->mVertices.size() > 65535))
    throw runtime_error("The mesh is too large to fit in a 3DS file.");

  // What should we export?
  bool exportTexCoords = aMesh->HasTexCoords() && !aOptions.mNoTexCoords;

  // Predefined names / strings
  string objName("Object1");
  string matName("Material0");

  // Get mesh properties
  uint32 triCount = aMesh->mIndices.size() / 3;
  uint32 vertCount = aMesh->mVertices.size();

  // Calculate the material chunk size
  uint32 materialSize = 0;
  uint32 matGroupSize = 0;
  if(exportTexCoords && aMesh->mTexFileName.size() > 0)
  {
    materialSize += 24 + matName.size() + 1 + aMesh->mTexFileName.size() + 1;
    matGroupSize += 8 + matName.size() + 1 + 2 * triCount;
  }

  // Calculate the mesh chunk size
  uint32 triMeshSize = 22 + 8 * triCount + 12 * vertCount + matGroupSize;
  if(exportTexCoords)
    triMeshSize += 8 + 8 * vertCount;

  // Calculate the total file size
  uint32 fileSize = 38 + objName.size() + 1 + materialSize + triMeshSize;

  // Open the output file
  ofstream f(aFileName, ios::out | ios::binary);
  if(f.fail())
    throw runtime_error("Could not open output file.");

  // Write file header
  WriteInt16(f, CHUNK_MAIN);
  WriteInt32(f, fileSize);
  WriteInt16(f, CHUNK_M3D_VERSION);
  WriteInt32(f, 6 + 4);
  WriteInt32(f, 0x00000003);

  // 3D Edit chunk
  WriteInt16(f, CHUNK_3DEDIT);
  WriteInt32(f, 16 + materialSize + objName.size() + 1 + triMeshSize);
  WriteInt16(f, CHUNK_MESH_VERSION);
  WriteInt32(f, 6 + 4);
  WriteInt32(f, 0x00000003);

  // Material chunk
  if(materialSize > 0)
  {
    WriteInt16(f, CHUNK_MAT_ENTRY);
    WriteInt32(f, materialSize);
    WriteInt16(f, CHUNK_MAT_NAME);
    WriteInt32(f, 6 + matName.size() + 1);
    f.write(matName.c_str(), matName.size() + 1);
    WriteInt16(f, CHUNK_MAT_TEXMAP);
    WriteInt32(f, 12 + aMesh->mTexFileName.size() + 1);
    WriteInt16(f, CHUNK_MAT_MAPNAME);
    WriteInt32(f, 6 + aMesh->mTexFileName.size() + 1);
    f.write(aMesh->mTexFileName.c_str(), aMesh->mTexFileName.size() + 1);
  }

  // Object chunk
  WriteInt16(f, CHUNK_OBJECT);
  WriteInt32(f, 6 + objName.size() + 1 + triMeshSize);
  f.write(objName.c_str(), objName.size() + 1);

  // Triangle Mesh chunk
  WriteInt16(f, CHUNK_TRIMESH);
  WriteInt32(f, triMeshSize);

  // Vertex List chunk
  WriteInt16(f, CHUNK_VERTEXLIST);
  WriteInt32(f, 8 + 12 * vertCount);
  WriteInt16(f, vertCount);
  for(uint32 i = 0; i < vertCount; ++ i)
    WriteVector3(f, aMesh->mVertices[i]);

  // Mapping Coordinates chunk
  if(exportTexCoords)
  {
    WriteInt16(f, CHUNK_MAPPINGCOORDS);
    WriteInt32(f, 8 + 8 * vertCount);
    WriteInt16(f, vertCount);
    for(uint32 i = 0; i < vertCount; ++ i)
      WriteVector2(f, aMesh->mTexCoords[i]);
  }

  // Faces chunk
  WriteInt16(f, CHUNK_FACES);
  WriteInt32(f, 8 + 8 * triCount);
  WriteInt16(f, triCount);
  for(uint32 i = 0; i < triCount; ++ i)
  {
    WriteInt16(f, uint16(aMesh->mIndices[i * 3]));
    WriteInt16(f, uint16(aMesh->mIndices[i * 3 + 1]));
    WriteInt16(f, uint16(aMesh->mIndices[i * 3 + 2]));
    WriteInt16(f, 0);
  }

  // Material Group chunk
  if(matGroupSize > 0)
  {
    WriteInt16(f, CHUNK_MSH_MAT_GROUP);
    WriteInt32(f, matGroupSize);
    f.write(matName.c_str(), matName.size() + 1);
    WriteInt16(f, triCount);
    for(uint16 i = 0; i < triCount; ++ i)
      WriteInt16(f, i);
  }
}
