//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        mesh.h
// Description: Interface for the 3D triangle mesh class.
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

#ifndef __MESH_H_
#define __MESH_H_

#include <vector>
#include <string>
#include <cmath>

class Vector2 {
  public:
    Vector2()
    {
      u = 0.0f; v = 0.0f;
    }

    Vector2(float a, float b)
    {
      u = a; v = b;
    }

    Vector2(const Vector2 &a)
    {
      u = a.u; v = a.v;
    }

    float u, v;
};

class Vector3 {
  public:
    Vector3()
    {
      x = 0.0f; y = 0.0f; z = 0.0f;
    }

    Vector3(float a, float b, float c)
    {
      x = a; y = b; z = c;
    }

    Vector3(const Vector3 &a)
    {
      x = a.x; y = a.y; z = a.z;
    }

    inline Vector3 operator+(const Vector3 &v) const
    {
      return Vector3(x + v.x,  y + v.y,  z + v.z);
    }

    inline Vector3 operator-(const Vector3 &v) const
    {
      return Vector3(x - v.x,  y - v.y,  z - v.z);
    }

    inline Vector3 operator*(const float &aScale) const
    {
      return Vector3(aScale * x, aScale * y, aScale * z);
    }

    inline void operator+=(const Vector3 &v)
    {
      x += v.x;
      y += v.y;
      z += v.z;
    }

    float Abs()
    {
      return sqrtf(x * x + y * y + z * z);
    }

    float x, y, z;
};

class Vector4 {
  public:
    Vector4()
    {
      x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
    }

    Vector4(float a, float b, float c, float d)
    {
      x = a; y = b; z = c; w = d;
    }

    Vector4(const Vector4 &a)
    {
      x = a.x; y = a.y; z = a.z; w = a.w;
    }

    Vector4(const Vector3 &a)
    {
      x = a.x; y = a.y; z = a.z; w = 1.0;
    }

    float x, y, z, w;
};

class Options;

class Mesh {
  public:
    /// Normal calculation algorithm
    enum NormalCalcAlgo {
      ncaAuto,     ///< Auto detect optimal algorithm
      ncaOrganic,  ///< Optimized for "organic" models (e.g. scanned objects)
      ncaCAD       ///< Optimized for CAD models (varying triangle sizes etc)
    };

    /// Constructor
    Mesh()
    {
      mOriginalNormals = true;
    }

    /// Clear the mesh
    void Clear();

    /// Calculate smooth per-vertex normals
    void CalculateNormals(NormalCalcAlgo aAlgo = ncaAuto);

    /// Calculate the bounding box for the mesh
    void BoundingBox(Vector3 &aMin, Vector3 &aMax);

    /// Set to true if the mesh contains the original normals from the imported
    /// file. This flag is set to false by the CalculateNormals() method.
    bool mOriginalNormals;

    /// Check if the mesh has normals
    bool HasNormals()
    {
      return (mNormals.size() > 0) && (mNormals.size() == mVertices.size());
    }

    /// Check if the mesh has colors
    bool HasColors()
    {
      return (mColors.size() > 0) && (mColors.size() == mVertices.size());
    }

    /// Check if the mesh has texture coordinates
    bool HasTexCoords()
    {
      return (mTexCoords.size() > 0) && (mTexCoords.size() == mVertices.size());
    }

    std::string mComment;
    std::string mTexFileName;
    std::vector<int> mIndices;
    std::vector<Vector3> mVertices;
    std::vector<Vector3> mNormals;
    std::vector<Vector4> mColors;
    std::vector<Vector2> mTexCoords;

  private:
    /// Automatic detection of the optimal normal calculation method
    NormalCalcAlgo DetectNormalCalculationMethod();
};


/// Compute the cross product of two vectors
Vector3 Cross(Vector3 &v1, Vector3 &v2);

/// Normalize a vector
Vector3 Normalize(Vector3 v);

#endif // __MESH_H_
