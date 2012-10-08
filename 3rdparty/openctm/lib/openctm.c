//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        openctm.c
// Description: API functions.
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
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "openctm.h"
#include "internal.h"


// The C99 macro isfinite() is not supported on all platforms (specifically,
// MS Visual Studio does not support C99)
#if !defined(isfinite) && defined(_MSC_VER)
  #include <float.h>
  #define isfinite(x) _finite(x)
#endif


//-----------------------------------------------------------------------------
// _ctmFreeMapList() - Free a float map list.
//-----------------------------------------------------------------------------
static void _ctmFreeMapList(_CTMcontext * self, _CTMfloatmap * aMapList)
{
  _CTMfloatmap * map, * nextMap;
  map = aMapList;
  while(map)
  {
    // Free internally allocated array (if we are in import mode)
    if((self->mMode == CTM_IMPORT) && map->mValues)
      free(map->mValues);

    // Free map name
    if(map->mName)
      free(map->mName);

    // Free file name
    if(map->mFileName)
      free(map->mFileName);

    nextMap = map->mNext;
    free(map);
    map = nextMap;
  }
}

//-----------------------------------------------------------------------------
// _ctmClearMesh() - Clear the mesh in a CTM context.
//-----------------------------------------------------------------------------
static void _ctmClearMesh(_CTMcontext * self)
{
  // Free internally allocated mesh arrays
  if(self->mMode == CTM_IMPORT)
  {
    if(self->mVertices)
      free(self->mVertices);
    if(self->mIndices)
      free(self->mIndices);
    if(self->mNormals)
      free(self->mNormals);
  }

  // Clear externally assigned mesh arrays
  self->mVertices = (CTMfloat *) 0;
  self->mVertexCount = 0;
  self->mIndices = (CTMuint *) 0;
  self->mTriangleCount = 0;
  self->mNormals = (CTMfloat *) 0;

  // Free UV coordinate map list
  _ctmFreeMapList(self, self->mUVMaps);
  self->mUVMaps = (_CTMfloatmap *) 0;
  self->mUVMapCount = 0;

  // Free attribute map list
  _ctmFreeMapList(self, self->mAttribMaps);
  self->mAttribMaps = (_CTMfloatmap *) 0;
  self->mAttribMapCount = 0;
}

//-----------------------------------------------------------------------------
// _ctmCheckMeshIntegrity() - Check if a mesh is valid (i.e. is non-empty, and
// contains valid data).
//-----------------------------------------------------------------------------

static CTMint _ctmCheckMeshIntegrity(_CTMcontext * self)
{
  CTMuint i;
  _CTMfloatmap * map;

  // Check that we have all the mandatory data
  if(!self->mVertices || !self->mIndices || (self->mVertexCount < 1) ||
     (self->mTriangleCount < 1))
  {
    return CTM_FALSE;
  }

  // Check that all indices are within range
  for(i = 0; i < (self->mTriangleCount * 3); ++ i)
  {
    if(self->mIndices[i] >= self->mVertexCount)
    {
      return CTM_FALSE;
    }
  }

  // Check that all vertices are finite (non-NaN, non-inf)
  for(i = 0; i < self->mVertexCount * 3; ++ i)
  {
    if(!isfinite(self->mVertices[i]))
    {
      return CTM_FALSE;
    }
  }

  // Check that all normals are finite (non-NaN, non-inf)
  if(self->mNormals)
  {
    for(i = 0; i < self->mVertexCount * 3; ++ i)
    {
      if(!isfinite(self->mNormals[i]))
      {
        return CTM_FALSE;
      }
    }
  }

  // Check that all UV maps are finite (non-NaN, non-inf)
  map = self->mUVMaps;
  while(map)
  {
    for(i = 0; i < self->mVertexCount * 2; ++ i)
    {
      if(!isfinite(map->mValues[i]))
      {
        return CTM_FALSE;
      }
    }
    map = map->mNext;
  }

  // Check that all attribute maps are finite (non-NaN, non-inf)
  map = self->mAttribMaps;
  while(map)
  {
    for(i = 0; i < self->mVertexCount * 4; ++ i)
    {
      if(!isfinite(map->mValues[i]))
      {
        return CTM_FALSE;
      }
    }
    map = map->mNext;
  }

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// ctmNewContext()
//-----------------------------------------------------------------------------
CTMEXPORT CTMcontext CTMCALL ctmNewContext(CTMenum aMode)
{
  _CTMcontext * self;

  // Allocate memory for the new structure
  self = (_CTMcontext *) malloc(sizeof(_CTMcontext));

  // Initialize structure (set null pointers and zero array lengths)
  memset(self, 0, sizeof(_CTMcontext));
  self->mMode = aMode;
  self->mError = CTM_NONE;
  self->mMethod = CTM_METHOD_MG1;
  self->mCompressionLevel = 1;
  self->mVertexPrecision = 1.0f / 1024.0f;
  self->mNormalPrecision = 1.0f / 256.0f;

  return (CTMcontext) self;
}

//-----------------------------------------------------------------------------
// ctmFreeContext()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmFreeContext(CTMcontext aContext)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // Free all mesh resources
  _ctmClearMesh(self);

  // Free the file comment
  if(self->mFileComment)
    free(self->mFileComment);

  // Free the context
  free(self);
}

//-----------------------------------------------------------------------------
// ctmGetError()
//-----------------------------------------------------------------------------
CTMEXPORT CTMenum CTMCALL ctmGetError(CTMcontext aContext)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  CTMenum err;

  if(!self) return CTM_INVALID_CONTEXT;

  // Get error code and reset error state
  err = self->mError;
  self->mError = CTM_NONE;
  return err;
}

//-----------------------------------------------------------------------------
// ctmErrorString()
//-----------------------------------------------------------------------------
CTMEXPORT const char * CTMCALL ctmErrorString(CTMenum aError)
{
  switch(aError)
  {
    case CTM_INVALID_CONTEXT:
      return "CTM_INVALID_CONTEXT";
    case CTM_INVALID_ARGUMENT:
      return "CTM_INVALID_ARGUMENT";
    case CTM_INVALID_OPERATION:
      return "CTM_INVALID_OPERATION";
    case CTM_INVALID_MESH:
      return "CTM_INVALID_MESH";
    case CTM_OUT_OF_MEMORY:
      return "CTM_OUT_OF_MEMORY";
    case CTM_FILE_ERROR:
      return "CTM_FILE_ERROR";
    case CTM_BAD_FORMAT:
      return "CTM_BAD_FORMAT";
    case CTM_LZMA_ERROR:
      return "CTM_LZMA_ERROR";
    case CTM_INTERNAL_ERROR:
      return "CTM_INTERNAL_ERROR";
    case CTM_UNSUPPORTED_FORMAT_VERSION:
      return "CTM_UNSUPPORTED_FORMAT_VERSION";
    default:
      return "Unknown error code";
  }
}

//-----------------------------------------------------------------------------
// ctmGetInteger()
//-----------------------------------------------------------------------------
CTMEXPORT CTMuint CTMCALL ctmGetInteger(CTMcontext aContext, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return 0;

  switch(aProperty)
  {
    case CTM_VERTEX_COUNT:
      return self->mVertexCount;

    case CTM_TRIANGLE_COUNT:
      return self->mTriangleCount;

    case CTM_UV_MAP_COUNT:
      return self->mUVMapCount;

    case CTM_ATTRIB_MAP_COUNT:
      return self->mAttribMapCount;

    case CTM_HAS_NORMALS:
      return self->mNormals ? CTM_TRUE : CTM_FALSE;

    case CTM_COMPRESSION_METHOD:
      return (CTMuint) self->mMethod;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return 0;
}

//-----------------------------------------------------------------------------
// ctmGetFloat()
//-----------------------------------------------------------------------------
CTMEXPORT CTMfloat CTMCALL ctmGetFloat(CTMcontext aContext, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return 0.0f;

  switch(aProperty)
  {
    case CTM_VERTEX_PRECISION:
      return self->mVertexPrecision;

    case CTM_NORMAL_PRECISION:
      return self->mNormalPrecision;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return 0.0f;
}

//-----------------------------------------------------------------------------
// ctmGetIntegerArray()
//-----------------------------------------------------------------------------
CTMEXPORT const CTMuint * CTMCALL ctmGetIntegerArray(CTMcontext aContext,
  CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return (CTMuint *) 0;

  switch(aProperty)
  {
    case CTM_INDICES:
      return self->mIndices;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return (CTMuint *) 0;
}

//-----------------------------------------------------------------------------
// ctmGetFloatArray()
//-----------------------------------------------------------------------------
CTMEXPORT const CTMfloat * CTMCALL ctmGetFloatArray(CTMcontext aContext,
  CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return (CTMfloat *) 0;

  // Did the user request a UV map?
  if((aProperty >= CTM_UV_MAP_1) &&
     ((CTMuint)(aProperty - CTM_UV_MAP_1) < self->mUVMapCount))
  {
    map = self->mUVMaps;
    i = CTM_UV_MAP_1;
    while(map && (i != aProperty))
    {
      map = map->mNext;
      ++ i;
    }
    if(!map)
    {
      self->mError = CTM_INTERNAL_ERROR;
      return (CTMfloat *) 0;
    }
    return map->mValues;
  }

  // Did the user request an attribute map?
  if((aProperty >= CTM_ATTRIB_MAP_1) &&
     ((CTMuint)(aProperty - CTM_ATTRIB_MAP_1) < self->mAttribMapCount))
  {
    map = self->mAttribMaps;
    i = CTM_ATTRIB_MAP_1;
    while(map && (i != aProperty))
    {
      map = map->mNext;
      ++ i;
    }
    if(!map)
    {
      self->mError = CTM_INTERNAL_ERROR;
      return (CTMfloat *) 0;
    }
    return map->mValues;
  }

  switch(aProperty)
  {
    case CTM_VERTICES:
      return self->mVertices;

    case CTM_NORMALS:
      return self->mNormals;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return (CTMfloat *) 0;
}

//-----------------------------------------------------------------------------
// ctmGetNamedUVMap()
//-----------------------------------------------------------------------------
CTMEXPORT CTMenum CTMCALL ctmGetNamedUVMap(CTMcontext aContext,
  const char * aName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint result;
  if(!self) return CTM_NONE;

  map = self->mUVMaps;
  result = CTM_UV_MAP_1;
  while(map && (strcmp(aName, map->mName) != 0))
  {
    map = map->mNext;
    ++ result;
  }
  if(!map)
  {
    return CTM_NONE;
  }
  return result;
}

//-----------------------------------------------------------------------------
// ctmGetUVMapString()
//-----------------------------------------------------------------------------
CTMEXPORT const char * CTMCALL ctmGetUVMapString(CTMcontext aContext,
  CTMenum aUVMap, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return (const char *) 0;

  // Find the indicated map
  map = self->mUVMaps;
  i = CTM_UV_MAP_1;
  while(map && (i != aUVMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return (const char *) 0;
  }

  // Get the requested string
  switch(aProperty)
  {
    case CTM_NAME:
      return (const char *) map->mName;

    case CTM_FILE_NAME:
      return (const char *) map->mFileName;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return (const char *) 0;
}

//-----------------------------------------------------------------------------
// ctmGetUVMapFloat()
//-----------------------------------------------------------------------------
CTMEXPORT CTMfloat CTMCALL ctmGetUVMapFloat(CTMcontext aContext,
  CTMenum aUVMap, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return 0.0f;

  // Find the indicated map
  map = self->mUVMaps;
  i = CTM_UV_MAP_1;
  while(map && (i != aUVMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return 0.0f;
  }

  // Get the requested string
  switch(aProperty)
  {
    case CTM_PRECISION:
      return map->mPrecision;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return 0.0f;
}

//-----------------------------------------------------------------------------
// ctmGetAttribMapString()
//-----------------------------------------------------------------------------
CTMEXPORT const char * CTMCALL ctmGetAttribMapString(CTMcontext aContext,
  CTMenum aAttribMap, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return (const char *) 0;

  // Find the indicated map
  map = self->mAttribMaps;
  i = CTM_ATTRIB_MAP_1;
  while(map && (i != aAttribMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return (const char *) 0;
  }

  // Get the requested string
  switch(aProperty)
  {
    case CTM_NAME:
      return (const char *) map->mName;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return (const char *) 0;
}

//-----------------------------------------------------------------------------
// ctmGetAttribMapFloat()
//-----------------------------------------------------------------------------
CTMEXPORT CTMfloat CTMCALL ctmGetAttribMapFloat(CTMcontext aContext,
  CTMenum aAttribMap, CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return 0.0f;

  // Find the indicated map
  map = self->mAttribMaps;
  i = CTM_ATTRIB_MAP_1;
  while(map && (i != aAttribMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return 0.0f;
  }

  // Get the requested string
  switch(aProperty)
  {
    case CTM_PRECISION:
      return map->mPrecision;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return 0.0f;
}

//-----------------------------------------------------------------------------
// ctmGetNamedAttribMap()
//-----------------------------------------------------------------------------
CTMEXPORT CTMenum CTMCALL ctmGetNamedAttribMap(CTMcontext aContext,
  const char * aName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint result;
  if(!self) return CTM_NONE;

  map = self->mAttribMaps;
  result = CTM_ATTRIB_MAP_1;
  while(map && (strcmp(aName, map->mName) != 0))
  {
    map = map->mNext;
    ++ result;
  }
  if(!map)
  {
    return CTM_NONE;
  }
  return result;
}

//-----------------------------------------------------------------------------
// ctmGetString()
//-----------------------------------------------------------------------------
CTMEXPORT const char * CTMCALL ctmGetString(CTMcontext aContext,
  CTMenum aProperty)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return 0;

  switch(aProperty)
  {
    case CTM_FILE_COMMENT:
      return (const char *) self->mFileComment;

    default:
      self->mError = CTM_INVALID_ARGUMENT;
  }

  return (const char *) 0;
}

//-----------------------------------------------------------------------------
// ctmCompressionMethod()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmCompressionMethod(CTMcontext aContext,
  CTMenum aMethod)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if((aMethod != CTM_METHOD_RAW) && (aMethod != CTM_METHOD_MG1) &&
     (aMethod != CTM_METHOD_MG2))
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Set method
  self->mMethod = aMethod;
}

//-----------------------------------------------------------------------------
// ctmCompressionLevel()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmCompressionLevel(CTMcontext aContext,
  CTMuint aLevel)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aLevel > 9)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Set the compression level
  self->mCompressionLevel = aLevel;
}

//-----------------------------------------------------------------------------
// ctmVertexPrecision()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmVertexPrecision(CTMcontext aContext,
  CTMfloat aPrecision)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aPrecision <= 0.0f)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Set precision
  self->mVertexPrecision = aPrecision;
}

//-----------------------------------------------------------------------------
// ctmVertexPrecisionRel()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmVertexPrecisionRel(CTMcontext aContext,
  CTMfloat aRelPrecision)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  CTMfloat avgEdgeLength, * p1, * p2;
  CTMuint edgeCount, i, j;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aRelPrecision <= 0.0f)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Calculate the average edge length (Note: we actually sum up all the half-
  // edges, so in a proper solid mesh all connected edges are counted twice)
  avgEdgeLength = 0.0f;
  edgeCount = 0;
  for(i = 0; i < self->mTriangleCount; ++ i)
  {
    p1 = &self->mVertices[self->mIndices[i * 3 + 2] * 3];
    for(j = 0; j < 3; ++ j)
    {
      p2 = &self->mVertices[self->mIndices[i * 3 + j] * 3];
      avgEdgeLength += sqrtf((p2[0] - p1[0]) * (p2[0] - p1[0]) +
                             (p2[1] - p1[1]) * (p2[1] - p1[1]) +
                             (p2[2] - p1[2]) * (p2[2] - p1[2]));
      p1 = p2;
      ++ edgeCount;
    }
  }
  if(edgeCount == 0)
  {
    self->mError = CTM_INVALID_MESH;
    return;
  }
  avgEdgeLength /= (CTMfloat) edgeCount;

  // Set precision
  self->mVertexPrecision = aRelPrecision * avgEdgeLength;
}

//-----------------------------------------------------------------------------
// ctmNormalPrecision()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmNormalPrecision(CTMcontext aContext,
  CTMfloat aPrecision)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aPrecision <= 0.0f)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Set precision
  self->mNormalPrecision = aPrecision;
}

//-----------------------------------------------------------------------------
// ctmUVCoordPrecision()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmUVCoordPrecision(CTMcontext aContext,
  CTMenum aUVMap, CTMfloat aPrecision)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aPrecision <= 0.0f)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Find the indicated map
  map = self->mUVMaps;
  i = CTM_UV_MAP_1;
  while(map && (i != aUVMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Update the precision
  map->mPrecision = aPrecision;
}

//-----------------------------------------------------------------------------
// ctmAttribPrecision()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmAttribPrecision(CTMcontext aContext,
  CTMenum aAttribMap, CTMfloat aPrecision)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  CTMuint i;
  if(!self) return;

  // You are only allowed to change compression attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(aPrecision <= 0.0f)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Find the indicated map
  map = self->mAttribMaps;
  i = CTM_ATTRIB_MAP_1;
  while(map && (i != aAttribMap))
  {
    ++ i;
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Update the precision
  map->mPrecision = aPrecision;
}

//-----------------------------------------------------------------------------
// ctmFileComment()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmFileComment(CTMcontext aContext,
  const char * aFileComment)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  int len;
  if(!self) return;

  // You are only allowed to change file attributes in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Free the old comment string, if necessary
  if(self->mFileComment)
  {
    free(self->mFileComment);
    self->mFileComment = (char *) 0;
  }

  // Get length of string (if empty, do nothing)
  if(!aFileComment)
    return;
  len = strlen(aFileComment);
  if(!len)
    return;

  // Copy the string
  self->mFileComment = (char *) malloc(len + 1);
  if(!self->mFileComment)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return;
  }
  strcpy(self->mFileComment, aFileComment);
}

//-----------------------------------------------------------------------------
// ctmDefineMesh()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmDefineMesh(CTMcontext aContext,
  const CTMfloat * aVertices, CTMuint aVertexCount, const CTMuint * aIndices,
  CTMuint aTriangleCount, const CTMfloat * aNormals)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  if(!self) return;

  // You are only allowed to (re)define the mesh in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check arguments
  if(!aVertices || !aIndices || !aVertexCount || !aTriangleCount)
  {
    self->mError = CTM_INVALID_ARGUMENT;
    return;
  }

  // Clear the old mesh, if any
  _ctmClearMesh(self);

  // Set vertex array pointer
  self->mVertices = (CTMfloat *) aVertices;
  self->mVertexCount = aVertexCount;

  // Set index array pointer
  self->mIndices = (CTMuint *) aIndices;
  self->mTriangleCount = aTriangleCount;

  // Set normal array pointer
  self->mNormals = (CTMfloat *) aNormals;
}

//-----------------------------------------------------------------------------
// _ctmAddFloatMap()
//-----------------------------------------------------------------------------
static _CTMfloatmap * _ctmAddFloatMap(_CTMcontext * self,
  const CTMfloat * aValues, const char * aName, const char * aFileName,
  _CTMfloatmap ** aList)
{
  _CTMfloatmap * map;
  CTMuint len;

  // Allocate memory for a new map list item and append it to the list
  if(!*aList)
  {
    *aList = (_CTMfloatmap *) malloc(sizeof(_CTMfloatmap));
    map = *aList;
  }
  else
  {
    map = *aList;
    while(map->mNext)
      map = map->mNext;
    map->mNext = (_CTMfloatmap *) malloc(sizeof(_CTMfloatmap));
    map = map->mNext;
  }
  if(!map)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return (_CTMfloatmap *) 0;
  }

  // Init the map item
  memset(map, 0, sizeof(_CTMfloatmap));
  map->mPrecision = 1.0f / 1024.0f;
  map->mValues = (CTMfloat *) aValues;

  // Set name of the map
  if(aName)
  {
    // Get length of string (if empty, do nothing)
    len = strlen(aName);
    if(len)
    {
      // Copy the string
      map->mName = (char *) malloc(len + 1);
      if(!map->mName)
      {
        self->mError = CTM_OUT_OF_MEMORY;
        free(map);
        return (_CTMfloatmap *) 0;
      }
      strcpy(map->mName, aName);
    }
  }

  // Set file name reference for the map
  if(aFileName)
  {
    // Get length of string (if empty, do nothing)
    len = strlen(aFileName);
    if(len)
    {
      // Copy the string
      map->mFileName = (char *) malloc(len + 1);
      if(!map->mFileName)
      {
        self->mError = CTM_OUT_OF_MEMORY;
        if(map->mName)
          free(map->mName);
        free(map);
        return (_CTMfloatmap *) 0;
      }
      strcpy(map->mFileName, aFileName);
    }
  }

  return map;
}

//-----------------------------------------------------------------------------
// ctmAddUVMap()
//-----------------------------------------------------------------------------
CTMEXPORT CTMenum CTMCALL ctmAddUVMap(CTMcontext aContext,
  const CTMfloat * aUVCoords, const char * aName, const char * aFileName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  if(!self) return CTM_NONE;

  // Add a new UV map to the UV map list
  map = _ctmAddFloatMap(self, aUVCoords, aName, aFileName, &self->mUVMaps);
  if(!map)
    return CTM_NONE;
  else
  {
    // The default UV coordinate precision is 2^-12
    map->mPrecision = 1.0f / 4096.0f;
    ++ self->mUVMapCount;
    return CTM_UV_MAP_1 + self->mUVMapCount - 1;
  }
}

//-----------------------------------------------------------------------------
// ctmAddAttribMap()
//-----------------------------------------------------------------------------
CTMEXPORT CTMenum CTMCALL ctmAddAttribMap(CTMcontext aContext,
  const CTMfloat * aAttribValues, const char * aName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  _CTMfloatmap * map;
  if(!self) return CTM_NONE;

  // Add a new attribute map to the attribute map list
  map = _ctmAddFloatMap(self, aAttribValues, aName, (const char *) 0,
                        &self->mAttribMaps);
  if(!map)
    return CTM_NONE;
  else
  {
    // The default vertex attribute precision is 2^-8
    map->mPrecision = 1.0f / 256.0f;
    ++ self->mAttribMapCount;
    return CTM_ATTRIB_MAP_1 + self->mAttribMapCount - 1;
  }
}

//-----------------------------------------------------------------------------
// _ctmDefaultRead()
//-----------------------------------------------------------------------------
static CTMuint CTMCALL _ctmDefaultRead(void * aBuf, CTMuint aCount,
  void * aUserData)
{
  return (CTMuint) fread(aBuf, 1, (size_t) aCount, (FILE *) aUserData);
}

//-----------------------------------------------------------------------------
// ctmLoad()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmLoad(CTMcontext aContext, const char * aFileName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  FILE * f;
  if(!self) return;

  // You are only allowed to load data in import mode
  if(self->mMode != CTM_IMPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Open file stream
  f = fopen(aFileName, "rb");
  if(!f)
  {
    self->mError = CTM_FILE_ERROR;
    return;
  }

  // Load the file
  ctmLoadCustom(self, _ctmDefaultRead, (void *) f);

  // Close file stream
  fclose(f);
}

//-----------------------------------------------------------------------------
// _ctmAllocateFloatMaps()
//-----------------------------------------------------------------------------
static CTMuint _ctmAllocateFloatMaps(_CTMcontext * self,
  _CTMfloatmap ** aMapListPtr, CTMuint aCount, CTMuint aChannels)
{
  _CTMfloatmap ** mapListPtr;
  CTMuint i, size;

  mapListPtr = aMapListPtr;
  for(i = 0; i < aCount; ++ i)
  {
    // Allocate & clear memory for this map
    *mapListPtr = (_CTMfloatmap *) malloc(sizeof(_CTMfloatmap));
    if(!*mapListPtr)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      return CTM_FALSE;
    }
    memset(*mapListPtr, 0, sizeof(_CTMfloatmap));

    // Allocate & clear memory for the float array
    size = aChannels * sizeof(CTMfloat) * self->mVertexCount;
    (*mapListPtr)->mValues = (CTMfloat *) malloc(size);
    if(!(*mapListPtr)->mValues)
    {
      self->mError = CTM_OUT_OF_MEMORY;
      return CTM_FALSE;
    }
    memset((*mapListPtr)->mValues, 0, size);

    // Next map...
    mapListPtr = &(*mapListPtr)->mNext;
  }

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// ctmLoadCustom()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmLoadCustom(CTMcontext aContext, CTMreadfn aReadFn,
  void * aUserData)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  CTMuint formatVersion, flags, method;
  if(!self) return;

  // You are only allowed to load data in import mode
  if(self->mMode != CTM_IMPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Initialize stream
  self->mReadFn = aReadFn;
  self->mUserData = aUserData;

  // Clear any old mesh arrays
  _ctmClearMesh(self);

  // Read header from stream
  if(_ctmStreamReadUINT(self) != FOURCC("OCTM"))
  {
    self->mError = CTM_BAD_FORMAT;
    return;
  }
  formatVersion = _ctmStreamReadUINT(self);
  if(formatVersion != _CTM_FORMAT_VERSION)
  {
    self->mError = CTM_UNSUPPORTED_FORMAT_VERSION;
    return;
  }
  method = _ctmStreamReadUINT(self);
  if(method == FOURCC("RAW\0"))
    self->mMethod = CTM_METHOD_RAW;
  else if(method == FOURCC("MG1\0"))
    self->mMethod = CTM_METHOD_MG1;
  else if(method == FOURCC("MG2\0"))
    self->mMethod = CTM_METHOD_MG2;
  else
  {
    self->mError = CTM_BAD_FORMAT;
    return;
  }
  self->mVertexCount = _ctmStreamReadUINT(self);
  if(self->mVertexCount == 0)
  {
    self->mError = CTM_BAD_FORMAT;
    return;
  }
  self->mTriangleCount = _ctmStreamReadUINT(self);
  if(self->mTriangleCount == 0)
  {
    self->mError = CTM_BAD_FORMAT;
    return;
  }
  self->mUVMapCount = _ctmStreamReadUINT(self);
  self->mAttribMapCount = _ctmStreamReadUINT(self);
  flags = _ctmStreamReadUINT(self);
  _ctmStreamReadSTRING(self, &self->mFileComment);

  // Allocate memory for the mesh arrays
  self->mVertices = (CTMfloat *) malloc(self->mVertexCount * sizeof(CTMfloat) * 3);
  if(!self->mVertices)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return;
  }
  self->mIndices = (CTMuint *) malloc(self->mTriangleCount * sizeof(CTMuint) * 3);
  if(!self->mIndices)
  {
    _ctmClearMesh(self);
    self->mError = CTM_OUT_OF_MEMORY;
    return;
  }
  if(flags & _CTM_HAS_NORMALS_BIT)
  {
    self->mNormals = (CTMfloat *) malloc(self->mVertexCount * sizeof(CTMfloat) * 3);
    if(!self->mNormals)
    {
      _ctmClearMesh(self);
      self->mError = CTM_OUT_OF_MEMORY;
      return;
    }
  }

  // Allocate memory for the UV and attribute maps (if any)
  if(!_ctmAllocateFloatMaps(self, &self->mUVMaps, self->mUVMapCount, 2))
  {
    _ctmClearMesh(self);
    self->mError = CTM_OUT_OF_MEMORY;
    return;
  }
  if(!_ctmAllocateFloatMaps(self, &self->mAttribMaps, self->mAttribMapCount, 4))
  {
    _ctmClearMesh(self);
    self->mError = CTM_OUT_OF_MEMORY;
    return;
  }

  // Uncompress from stream
  switch(self->mMethod)
  {
    case CTM_METHOD_RAW:
      _ctmUncompressMesh_RAW(self);
      break;

    case CTM_METHOD_MG1:
      _ctmUncompressMesh_MG1(self);
      break;

    case CTM_METHOD_MG2:
      _ctmUncompressMesh_MG2(self);
      break;

    default:
      self->mError = CTM_INTERNAL_ERROR;
  }

  // Check mesh integrity
  if(!_ctmCheckMeshIntegrity(self))
  {
    self->mError = CTM_INVALID_MESH;
    return;
  }
}

//-----------------------------------------------------------------------------
// _ctmDefaultWrite()
//-----------------------------------------------------------------------------
static CTMuint CTMCALL _ctmDefaultWrite(const void * aBuf, CTMuint aCount,
  void * aUserData)
{
  return (CTMuint) fwrite(aBuf, 1, (size_t) aCount, (FILE *) aUserData);
}

//-----------------------------------------------------------------------------
// ctmSave()
//-----------------------------------------------------------------------------
CTMEXPORT void CTMCALL ctmSave(CTMcontext aContext, const char * aFileName)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  FILE * f;
  if(!self) return;

  // You are only allowed to save data in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Open file stream
  f = fopen(aFileName, "wb");
  if(!f)
  {
    self->mError = CTM_FILE_ERROR;
    return;
  }

  // Save the file
  ctmSaveCustom(self, _ctmDefaultWrite, (void *) f);

  // Close file stream
  fclose(f);
}

//-----------------------------------------------------------------------------
// ctmSaveCustom()
//-----------------------------------------------------------------------------
void CTMCALL ctmSaveCustom(CTMcontext aContext, CTMwritefn aWriteFn,
  void * aUserData)
{
  _CTMcontext * self = (_CTMcontext *) aContext;
  CTMuint flags;
  if(!self) return;

  // You are only allowed to save data in export mode
  if(self->mMode != CTM_EXPORT)
  {
    self->mError = CTM_INVALID_OPERATION;
    return;
  }

  // Check mesh integrity
  if(!_ctmCheckMeshIntegrity(self))
  {
    self->mError = CTM_INVALID_MESH;
    return;
  }

  // Initialize stream
  self->mWriteFn = aWriteFn;
  self->mUserData = aUserData;

  // Determine flags
  flags = 0;
  if(self->mNormals)
    flags |= _CTM_HAS_NORMALS_BIT;

  // Write header to stream
  _ctmStreamWrite(self, (void *) "OCTM", 4);
  _ctmStreamWriteUINT(self, _CTM_FORMAT_VERSION);
  switch(self->mMethod)
  {
    case CTM_METHOD_RAW:
      _ctmStreamWrite(self, (void *) "RAW\0", 4);
      break;

    case CTM_METHOD_MG1:
      _ctmStreamWrite(self, (void *) "MG1\0", 4);
      break;

    case CTM_METHOD_MG2:
      _ctmStreamWrite(self, (void *) "MG2\0", 4);
      break;

    default:
      self->mError = CTM_INTERNAL_ERROR;
      return;
  }
  _ctmStreamWriteUINT(self, self->mVertexCount);
  _ctmStreamWriteUINT(self, self->mTriangleCount);
  _ctmStreamWriteUINT(self, self->mUVMapCount);
  _ctmStreamWriteUINT(self, self->mAttribMapCount);
  _ctmStreamWriteUINT(self, flags);
  _ctmStreamWriteSTRING(self, self->mFileComment);

  // Compress to stream
  switch(self->mMethod)
  {
    case CTM_METHOD_RAW:
      _ctmCompressMesh_RAW(self);
      break;

    case CTM_METHOD_MG1:
      _ctmCompressMesh_MG1(self);
      break;

    case CTM_METHOD_MG2:
      _ctmCompressMesh_MG2(self);
      break;

    default:
      self->mError = CTM_INTERNAL_ERROR;
      return;
  }
}
