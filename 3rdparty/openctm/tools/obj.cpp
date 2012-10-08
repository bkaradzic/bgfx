//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        obj.cpp
// Description: Implementation of the OBJ file format importer/exporter.
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
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "obj.h"
#include "common.h"

using namespace std;

class OBJFaceNode {
  public:
    OBJFaceNode()
    {
      v = vt = vn = 0;
    }

    void Set(int aIndex, int aValue)
    {
      if(aIndex == 0)
        v = aValue;
      else if(aIndex == 1)
        vt = aValue;
      else
        vn = aValue;
    }

    int v, vt, vn;
};

// OBJ file face description class (three triangle corners, with one vertex,
// texcoord and normal index each).
class OBJFace {
  public:
    OBJFace()
    {
    }

    // Contruct a face (one triangle) from an OBJ face description string
    OBJFace(const string aStr)
    {
      // Start by finding the first and last non-whitespace char (trim)
      size_t l = aStr.size();
      size_t pos = 0, strEnd = l - 1;
      while((pos < strEnd) && ((aStr[pos] == ' ') || (aStr[pos] == '\t')))
        ++ pos;
      while((strEnd > pos) && ((aStr[strEnd] == ' ') || (aStr[strEnd] == '\t')))
        -- strEnd;

      // Extract three face corners (one triangle)
      while((pos <= strEnd) && (aStr[pos] != ' ') && (aStr[pos] != '\t'))
      {
        // Extract three /-separated strings (v/vt/vn)
        string v_s[3];
        int j = 0;
        while((pos <= strEnd) && (aStr[pos] != ' ') && (aStr[pos] != '\t') && (j < 3))
        {
          if(aStr[pos] != '/')
            v_s[j] += aStr[pos];
          else
            ++ j;
          ++ pos;
        }

        // Skip whitespaces
        while((pos <= strEnd) && ((aStr[pos] == ' ') || (aStr[pos] == '\t')))
          ++ pos;

        // Convert the strings to integers
        mNodes.push_back(OBJFaceNode());
        OBJFaceNode &n = mNodes.back();
        for(int j = 0; j < 3; ++ j)
        {
          int value = 0;
          if(v_s[j].size() > 0)
          {
            istringstream ss(v_s[j]);
            ss >> value;
            if(value > 0)
              value --;
            else if(value < 0)
              throw runtime_error("Negative vertex references in OBJ files are not supported.");
            else
              throw runtime_error("Invalid index (zero) in OBJ file.");
          }
          n.Set(j, value);
        }
      }
    }

    list<OBJFaceNode> mNodes;
};

// Parse a 2 x float string as a Vector2
static Vector2 ParseVector2(const string aString)
{
  Vector2 result;
  istringstream sstr(aString);
  sstr >> result.u;
  sstr >> result.v;
  return result;
}

// Parse a 3 x float string as a Vector3
static Vector3 ParseVector3(const string aString)
{
  Vector3 result;
  istringstream sstr(aString);
  sstr >> result.x;
  sstr >> result.y;
  sstr >> result.z;
  return result;
}

/// Import a mesh from an OBJ file.
void Import_OBJ(const char * aFileName, Mesh * aMesh)
{
  // Clear the mesh
  aMesh->Clear();

  // Open the input file
  ifstream inFile(aFileName, ios::in);
  if(inFile.fail())
    throw runtime_error("Could not open input file.");

  // Mesh description - parsed from the OBJ file
  list<Vector3> vertices;
  list<Vector2> texCoords;
  list<Vector3> normals;
  list<OBJFace> faces;

  // Parse the file
  while(!inFile.eof())
  {
    // Read one line from the file (concatenate lines that end with "\")
    string line;
    getline(inFile, line);
    while((line.size() > 0) && (line[line.size() - 1] == '\\') && !inFile.eof())
    {
      string nextLine;
      getline(inFile, nextLine);
      line = line.substr(0, line.size() - 1) + string(" ") + nextLine;
    }

    // Parse the line, if it is non-empty
    if(line.size() >= 1)
    {
      if(line.substr(0, 2) == string("v "))
        vertices.push_back(ParseVector3(line.substr(2)));
      else if(line.substr(0, 3) == string("vt "))
        texCoords.push_back(ParseVector2(line.substr(3)));
      else if(line.substr(0, 3) == string("vn "))
        normals.push_back(ParseVector3(line.substr(3)));
      else if(line.substr(0, 2) == string("f "))
        faces.push_back(OBJFace(line.substr(2)));
    }
  }

  // Convert lists to vectors (for random element access)
  vector<Vector3> verticesArray(vertices.begin(), vertices.end());
  vector<Vector2> texCoordsArray(texCoords.begin(), texCoords.end());
  vector<Vector3> normalsArray(normals.begin(), normals.end());

  // Prepare vertices
  aMesh->mVertices.resize(verticesArray.size());
  if(texCoordsArray.size() > 0)
    aMesh->mTexCoords.resize(verticesArray.size());
  if(normalsArray.size() > 0)
    aMesh->mNormals.resize(verticesArray.size());

  // Prepare indices
  int triCount = 0;
  for(list<OBJFace>::iterator i = faces.begin(); i != faces.end(); ++ i)
  {
    int nodeCount = (*i).mNodes.size();
    if(nodeCount >= 3)
      triCount += (nodeCount - 2);
  }
  aMesh->mIndices.resize(triCount * 3);

  // Iterate faces and extract vertex data
  unsigned int idx = 0;
  for(list<OBJFace>::iterator i = faces.begin(); i != faces.end(); ++ i)
  {
    OBJFace &f = (*i);
    int nodes[3][3];
    int nodeCount = 0;
    for(list<OBJFaceNode>::iterator n = f.mNodes.begin(); n != f.mNodes.end(); ++ n)
    {
      // Collect polygon nodes for this face, turning it into triangles
      if(nodeCount < 3)
      {
        nodes[nodeCount][0] = (*n).v;
        nodes[nodeCount][1] = (*n).vt;
        nodes[nodeCount][2] = (*n).vn;
      }
      else
      {
        nodes[1][0] = nodes[2][0];
        nodes[1][1] = nodes[2][1];
        nodes[1][2] = nodes[2][2];
        nodes[2][0] = (*n).v;
        nodes[2][1] = (*n).vt;
        nodes[2][2] = (*n).vn;
      }
      ++ nodeCount;

      // Emit one triangle?
      if(nodeCount >= 3)
      {
        aMesh->mIndices[idx ++] = nodes[0][0];
        aMesh->mIndices[idx ++] = nodes[1][0];
        aMesh->mIndices[idx ++] = nodes[2][0];
        aMesh->mVertices[nodes[0][0]] = verticesArray[nodes[0][0]];
        aMesh->mVertices[nodes[1][0]] = verticesArray[nodes[1][0]];
        aMesh->mVertices[nodes[2][0]] = verticesArray[nodes[2][0]];
        if(texCoordsArray.size() > 0)
        {
          aMesh->mTexCoords[nodes[0][0]] = texCoordsArray[nodes[0][1]];
          aMesh->mTexCoords[nodes[1][0]] = texCoordsArray[nodes[1][1]];
          aMesh->mTexCoords[nodes[2][0]] = texCoordsArray[nodes[2][1]];
        }
        if(normalsArray.size() > 0)
        {
          aMesh->mNormals[nodes[0][0]] = normalsArray[nodes[0][2]];
          aMesh->mNormals[nodes[1][0]] = normalsArray[nodes[1][2]];
          aMesh->mNormals[nodes[2][0]] = normalsArray[nodes[2][2]];
        }
      }
    }
  }

  // Close the input file
  inFile.close();
}

/// Export a mesh to an OBJ file.
void Export_OBJ(const char * aFileName, Mesh * aMesh, Options &aOptions)
{
  // Open the output file
  ofstream f(aFileName, ios::out);
  if(f.fail())
    throw runtime_error("Could not open output file.");

  // What should we export?
  bool exportTexCoords = aMesh->HasTexCoords() && !aOptions.mNoTexCoords;
  bool exportNormals = aMesh->HasNormals() && !aOptions.mNoNormals;

  // Set floating point precision
  f << setprecision(8);

  // Write comment
  if(aMesh->mComment.size() > 0)
  {
    stringstream sstr(aMesh->mComment);
    sstr.seekg(0);
    while(!sstr.eof())
    {
      string line;
      getline(sstr, line);
      line = TrimString(line);
      if(line.size() > 0)
        f << "# " << line << endl;
    }
  }

  // Write vertices
  for(unsigned int i = 0; i < aMesh->mVertices.size(); ++ i)
    f << "v " << aMesh->mVertices[i].x << " " << aMesh->mVertices[i].y << " " << aMesh->mVertices[i].z << endl;

  // Write UV coordinates
  if(exportTexCoords)
  {
    for(unsigned int i = 0; i < aMesh->mTexCoords.size(); ++ i)
      f << "vt " << aMesh->mTexCoords[i].u << " " << aMesh->mTexCoords[i].v << endl;
  }

  // Write normals
  if(exportNormals)
  {
    for(unsigned int i = 0; i < aMesh->mNormals.size(); ++ i)
      f << "vn " << aMesh->mNormals[i].x << " " << aMesh->mNormals[i].y << " " << aMesh->mNormals[i].z << endl;
  }

  // Write faces
  unsigned int triCount = aMesh->mIndices.size() / 3;
  f << "s 1" << endl; // Put all faces in the same smoothing group
  for(unsigned int i = 0; i < triCount; ++ i)
  {
    unsigned int idx = aMesh->mIndices[i * 3] + 1;
    f << "f " << idx << "/";
    if(exportTexCoords)
      f << idx;
    f << "/";
    if(exportNormals)
      f << idx;

    idx = aMesh->mIndices[i * 3 + 1] + 1;
    f << " " << idx << "/";
    if(exportTexCoords)
      f << idx;
    f << "/";
    if(exportNormals)
      f << idx;

    idx = aMesh->mIndices[i * 3 + 2] + 1;
    f << " " << idx << "/";
    if(exportTexCoords)
      f << idx;
    f << "/";
    if(exportNormals)
      f << idx;
    f << endl;
  }

  // Close the output file
  f.close();
}
