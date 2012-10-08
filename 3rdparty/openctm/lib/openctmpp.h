//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        openctmpp.h
// Description: C++ wrapper for the OpenCTM API.
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

// To disable C++ extensions, define OPENCTM_NO_CPP
#ifndef OPENCTM_NO_CPP

#ifndef __OPENCTMPP_H_
#define __OPENCTMPP_H_

// Just in case (if this file was included from outside openctm.h)...
#ifndef __OPENCTM_H_
#include "openctm.h"
#endif

#include <exception>

/// OpenCTM exception. When an error occurs, a \c ctm_error exception is
/// thrown. Its what() function returns the name of the OpenCTM error code
/// (for instance "CTM_INVALID_OPERATION").
class ctm_error: public std::exception
{
  private:
    CTMenum mErrorCode;

  public:
    explicit ctm_error(CTMenum aError)
    {
      mErrorCode = aError;
    }

    virtual const char* what() const throw()
    {
      return ctmErrorString(mErrorCode);
    }

    CTMenum error_code() const throw()
    {
      return mErrorCode;
    }
};


/// OpenCTM importer class. This is a C++ wrapper class for an OpenCTM import
/// context. Usage example:
///
/// @code
///   // Create a new OpenCTM importer object
///   CTMimporter ctm;
///
///   // Load the OpenCTM file
///   ctm.Load("mymesh.ctm");
///
///   // Access the mesh data
///   vertCount = ctm.GetInteger(CTM_VERTEX_COUNT);
///   vertices = ctm.GetFloatArray(CTM_VERTICES);
///   triCount = ctm.GetInteger(CTM_TRIANGLE_COUNT);
///   indices = ctm.GetIntegerArray(CTM_INDICES);
///
///   // Deal with the mesh (e.g. transcode it to our internal representation)
///   // ...
/// @endcode

class CTMimporter {
  private:
    /// The OpenCTM context handle.
    CTMcontext mContext;

    /// Check for OpenCTM errors, and throw an exception if an error has
    /// occured.
    void CheckError()
    {
      CTMenum err = ctmGetError(mContext);
      if(err != CTM_NONE)
        throw ctm_error(err);
    }

  public:
    /// Constructor
    CTMimporter()
    {
      mContext = ctmNewContext(CTM_IMPORT);
    }

    /// Destructor
    ~CTMimporter()
    {
      ctmFreeContext(mContext);
    }

    /// Wrapper for ctmGetInteger()
    CTMuint GetInteger(CTMenum aProperty)
    {
      CTMuint res = ctmGetInteger(mContext, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetFloat()
    CTMfloat GetFloat(CTMenum aProperty)
    {
      CTMfloat res = ctmGetFloat(mContext, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetIntegerArray()
    const CTMuint * GetIntegerArray(CTMenum aProperty)
    {
      const CTMuint * res = ctmGetIntegerArray(mContext, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetFloatArray()
    const CTMfloat * GetFloatArray(CTMenum aProperty)
    {
      const CTMfloat * res = ctmGetFloatArray(mContext, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetNamedUVMap()
    CTMenum GetNamedUVMap(const char * aName)
    {
      CTMenum res = ctmGetNamedUVMap(mContext, aName);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetUVMapString()
    const char * GetUVMapString(CTMenum aUVMap, CTMenum aProperty)
    {
      const char * res = ctmGetUVMapString(mContext, aUVMap, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetUVMapFloat()
    CTMfloat GetUVMapFloat(CTMenum aUVMap, CTMenum aProperty)
    {
      CTMfloat res = ctmGetUVMapFloat(mContext, aUVMap, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetNamedAttribMap()
    CTMenum GetNamedAttribMap(const char * aName)
    {
      CTMenum res = ctmGetNamedAttribMap(mContext, aName);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetAttribMapString()
    const char * GetAttribMapString(CTMenum aAttribMap, CTMenum aProperty)
    {
      const char * res = ctmGetAttribMapString(mContext, aAttribMap, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetAttribMapFloat()
    CTMfloat GetAttribMapFloat(CTMenum aAttribMap, CTMenum aProperty)
    {
      CTMfloat res = ctmGetAttribMapFloat(mContext, aAttribMap, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmGetString()
    const char * GetString(CTMenum aProperty)
    {
      const char * res = ctmGetString(mContext, aProperty);
      CheckError();
      return res;
    }

    /// Wrapper for ctmLoad()
    void Load(const char * aFileName)
    {
      ctmLoad(mContext, aFileName);
      CheckError();
    }

    /// Wrapper for ctmLoadCustom()
    void LoadCustom(CTMreadfn aReadFn, void * aUserData)
    {
      ctmLoadCustom(mContext, aReadFn, aUserData);
      CheckError();
    }

    // You can not copy nor assign from one CTMimporter object to another, since
    // the object contains hidden state. By declaring these dummy prototypes
    // without an implementation, you will at least get linker errors if you try
    // to copy or assign a CTMimporter object.
    CTMimporter(const CTMimporter& v);
    CTMimporter& operator=(const CTMimporter& v);
};


/// OpenCTM exporter class. This is a C++ wrapper class for an OpenCTM export
/// context. Usage example:
/// @code
/// void MySaveFile(CTMuint aVertCount, CTMuint aTriCount, CTMfloat * aVertices,
///   CTMuint * aIndices, const char * aFileName)
/// {
///   // Create a new OpenCTM exporter object
///   CTMexporter ctm;
///
///   // Define our mesh representation to OpenCTM (store references to it in
///   // the context)
///   ctm.DefineMesh(aVertices, aVertCount, aIndices, aTriCount, NULL);
///
///   // Save the OpenCTM file
///   ctm.Save(aFileName);
/// }
/// @endcode

class CTMexporter {
  private:
    /// The OpenCTM context handle.
    CTMcontext mContext;

    /// Check for OpenCTM errors, and throw an exception if an error has
    /// occured.
    void CheckError()
    {
      CTMenum err = ctmGetError(mContext);
      if(err != CTM_NONE)
        throw ctm_error(err);
    }

  public:
    /// Constructor
    CTMexporter()
    {
      mContext = ctmNewContext(CTM_EXPORT);
    }

    /// Destructor
    ~CTMexporter()
    {
      ctmFreeContext(mContext);
    }

    /// Wrapper for ctmCompressionMethod()
    void CompressionMethod(CTMenum aMethod)
    {
      ctmCompressionMethod(mContext, aMethod);
      CheckError();
    }

    /// Wrapper for ctmCompressionLevel()
    void CompressionLevel(CTMuint aLevel)
    {
      ctmCompressionLevel(mContext, aLevel);
      CheckError();
    }

    /// Wrapper for ctmVertexPrecision()
    void VertexPrecision(CTMfloat aPrecision)
    {
      ctmVertexPrecision(mContext, aPrecision);
      CheckError();
    }

    /// Wrapper for ctmVertexPrecisionRel()
    void VertexPrecisionRel(CTMfloat aRelPrecision)
    {
      ctmVertexPrecisionRel(mContext, aRelPrecision);
      CheckError();
    }

    /// Wrapper for ctmNormalPrecision()
    void NormalPrecision(CTMfloat aPrecision)
    {
      ctmNormalPrecision(mContext, aPrecision);
      CheckError();
    }

    /// Wrapper for ctmUVCoordPrecision()
    void UVCoordPrecision(CTMenum aUVMap, CTMfloat aPrecision)
    {
      ctmUVCoordPrecision(mContext, aUVMap, aPrecision);
      CheckError();
    }

    /// Wrapper for ctmAttribPrecision()
    void AttribPrecision(CTMenum aAttribMap, CTMfloat aPrecision)
    {
      ctmAttribPrecision(mContext, aAttribMap, aPrecision);
      CheckError();
    }

    /// Wrapper for ctmFileComment()
    void FileComment(const char * aFileComment)
    {
      ctmFileComment(mContext, aFileComment);
      CheckError();
    }

    /// Wrapper for ctmDefineMesh()
    void DefineMesh(const CTMfloat * aVertices, CTMuint aVertexCount, 
      const CTMuint * aIndices, CTMuint aTriangleCount,
      const CTMfloat * aNormals)
    {
      ctmDefineMesh(mContext, aVertices, aVertexCount, aIndices, aTriangleCount,
                    aNormals);
      CheckError();
    }

    /// Wrapper for ctmAddUVMap()
    CTMenum AddUVMap(const CTMfloat * aUVCoords, const char * aName,
      const char * aFileName)
    {
      CTMenum res = ctmAddUVMap(mContext, aUVCoords, aName, aFileName);
      CheckError();
      return res;
    }

    /// Wrapper for ctmAddAttribMap()
    CTMenum AddAttribMap(const CTMfloat * aAttribValues, const char * aName)
    {
      CTMenum res = ctmAddAttribMap(mContext, aAttribValues, aName);
      CheckError();
      return res;
    }

    /// Wrapper for ctmSave()
    void Save(const char * aFileName)
    {
      ctmSave(mContext, aFileName);
      CheckError();
    }

    /// Wrapper for ctmSaveCustom()
    void SaveCustom(CTMwritefn aWriteFn, void * aUserData)
    {
      ctmSaveCustom(mContext, aWriteFn, aUserData);
      CheckError();
    }

    // You can not copy nor assign from one CTMexporter object to another, since
    // the object contains hidden state. By declaring these dummy prototypes
    // without an implementation, you will at least get linker errors if you try
    // to copy or assign a CTMexporter object.
    CTMexporter(const CTMexporter& v);
    CTMexporter& operator=(const CTMexporter& v);
};

#endif // __OPENCTMPP_H_

#endif // OPENCTM_NO_CPP
