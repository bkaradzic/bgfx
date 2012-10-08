//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        openctm.h
// Description: OpenCTM API definition.
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

#ifndef __OPENCTM_H_
#define __OPENCTM_H_

/*! @mainpage OpenCTM API Reference
 *
 * @section intro_sec Introduction
 *
 * OpenCTM is an open file format for storing compressed triangle meshes.
 * In order to easily read and write OpenCTM files (usually suffixed .ctm) an
 * API (Application Program Interface) is provided that can easily be used from
 * most modern programming languages.
 *
 * The OpenCTM functionality itself is written in highly portable standard C
 * (C99).
 *
 * @section usage_sec Usage
 *
 * For information about how to use the OpenCTM API, see openctm.h.
 *
 * For information about the C++ wrapper classes, see CTMimporter and
 * CTMexporter.
 *
 * @section example_sec Example usage
 *
 * @subsection example_load_sec Loading a CTM file
 *
 * Here is a simple example of loading a CTM file:
 *
 * @code
 *   CTMcontext context;
 *   CTMuint    vertCount, triCount, * indices;
 *   CTMfloat   * vertices;
 *
 *   // Create a new context
 *   context = ctmNewContext(CTM_IMPORT);
 *
 *   // Load the OpenCTM file
 *   ctmLoad(context, "mymesh.ctm");
 *   if(ctmGetError(context) == CTM_NONE)
 *   {
 *     // Access the mesh data
 *     vertCount = ctmGetInteger(context, CTM_VERTEX_COUNT);
 *     vertices = ctmGetFloatArray(context, CTM_VERTICES);
 *     triCount = ctmGetInteger(context, CTM_TRIANGLE_COUNT);
 *     indices = ctmGetIntegerArray(context, CTM_INDICES);
 *
 *     // Deal with the mesh (e.g. transcode it to our internal representation)
 *     // ...
 *   }
 *
 *   // Free the context
 *   ctmFreeContext(context);
 * @endcode
 *
 * @subsection example_create_sec Creating a CTM file
 *
 * Here is a simple example of creating a CTM file:
 *
 * @code
 *   CTMcontext context;
 *   CTMuint    vertCount, triCount, * indices;
 *   CTMfloat   * vertices;
 *
 *   // Create our mesh in memory
 *   vertCount = 100;
 *   triCount = 120;
 *   vertices = (CTMfloat *) malloc(3 * sizeof(CTMfloat) * vertCount);
 *   indices = (CTMuint *) malloc(3 * sizeof(CTMuint) * triCount);
 *   // ...
 *
 *   // Create a new context
 *   context = ctmNewContext(CTM_EXPORT);
 *
 *   // Define our mesh representation to OpenCTM (store references to it in
 *   // the context)
 *   ctmDefineMesh(context, vertices, vertCount, indices, triCount, NULL);
 *
 *   // Save the OpenCTM file
 *   ctmSave(context, "mymesh.ctm");
 *
 *   // Free the context
 *   ctmFreeContext(context);
 *
 *   // Free our mesh
 *   free(indices);
 *   free(vertices);
 * @endcode
 */

#ifdef __cplusplus
extern "C" {
#endif


// Declare calling conventions etc.
#if defined(WIN32) || defined(_WIN32)
  // Windows
  #if defined(OPENCTM_STATIC)
    #define CTMEXPORT
  #else
    #if defined(OPENCTM_BUILD)
      #define CTMEXPORT __declspec(dllexport)
    #else
      #define CTMEXPORT __declspec(dllimport)
    #endif
  #endif
  #if defined(__MINGW32__)
    #define CTMCALL __attribute__ ((__stdcall__))
  #elif (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
    #define CTMCALL __stdcall
  #else
    #define CTMCALL
  #endif
#else
  // Unix
  #if !defined(OPENCTM_STATIC) && !defined(OPENCTM_BUILD)
    #define CTMEXPORT extern
  #else
    #if defined(OPENCTM_BUILD) && defined(__GNUC__) && (__GNUC__ >= 4)
      #define CTMEXPORT __attribute__ ((visibility("default")))
    #else
      #define CTMEXPORT
    #endif
  #endif
  #define CTMCALL
#endif


// Get system specific type definitions for sized integers. We use the C99
// standard stdint.h for this.
#ifdef _MSC_VER
  // MS Visual Studio does not support C99
  typedef int int32_t;
  typedef unsigned int uint32_t;
#else
  #include <stdint.h>
#endif


/// OpenCTM API version (1.0).
#define CTM_API_VERSION 0x00000100

/// Boolean TRUE.
#define CTM_TRUE 1

/// Boolean FALSE.
#define CTM_FALSE 0

/// Single precision floating point type (IEEE 754 32 bits wide).
typedef float CTMfloat;

/// Signed integer (32 bits wide).
typedef int32_t CTMint;

/// Unsigned integer (32 bits wide).
typedef uint32_t CTMuint;

/// OpenCTM context handle.
typedef void * CTMcontext;

/// OpenCTM specific enumerators.
/// @note For the information query functions, it is an error to query a value
///       of the wrong type (e.g. to query a string value with the
///       ctmGetInteger() function).
typedef enum {
  // Error codes (see ctmGetError())
  CTM_NONE              = 0x0000, ///< No error has occured (everything is OK).
                                  ///  Also used as an error return value for
                                  ///  functions that should return a CTMenum
                                  ///  value.
  CTM_INVALID_CONTEXT   = 0x0001, ///< The OpenCTM context was invalid (e.g. NULL).
  CTM_INVALID_ARGUMENT  = 0x0002, ///< A function argument was invalid.
  CTM_INVALID_OPERATION = 0x0003, ///< The operation is not allowed.
  CTM_INVALID_MESH      = 0x0004, ///< The mesh was invalid (e.g. no vertices).
  CTM_OUT_OF_MEMORY     = 0x0005, ///< Not enough memory to proceed.
  CTM_FILE_ERROR        = 0x0006, ///< File I/O error.
  CTM_BAD_FORMAT        = 0x0007, ///< File format error (e.g. unrecognized format or corrupted file).
  CTM_LZMA_ERROR        = 0x0008, ///< An error occured within the LZMA library.
  CTM_INTERNAL_ERROR    = 0x0009, ///< An internal error occured (indicates a bug).
  CTM_UNSUPPORTED_FORMAT_VERSION = 0x000A, ///< Unsupported file format version.

  // OpenCTM context modes
  CTM_IMPORT            = 0x0101, ///< The OpenCTM context will be used for importing data.
  CTM_EXPORT            = 0x0102, ///< The OpenCTM context will be used for exporting data.

  // Compression methods
  CTM_METHOD_RAW        = 0x0201, ///< Just store the raw data.
  CTM_METHOD_MG1        = 0x0202, ///< Lossless compression (floating point).
  CTM_METHOD_MG2        = 0x0203, ///< Lossless compression (fixed point).

  // Context queries
  CTM_VERTEX_COUNT      = 0x0301, ///< Number of vertices in the mesh (integer).
  CTM_TRIANGLE_COUNT    = 0x0302, ///< Number of triangles in the mesh (integer).
  CTM_HAS_NORMALS       = 0x0303, ///< CTM_TRUE if the mesh has normals (integer).
  CTM_UV_MAP_COUNT      = 0x0304, ///< Number of UV coordinate sets (integer).
  CTM_ATTRIB_MAP_COUNT  = 0x0305, ///< Number of custom attribute sets (integer).
  CTM_VERTEX_PRECISION  = 0x0306, ///< Vertex precision - for MG2 (float).
  CTM_NORMAL_PRECISION  = 0x0307, ///< Normal precision - for MG2 (float).
  CTM_COMPRESSION_METHOD = 0x0308, ///< Compression method (integer).
  CTM_FILE_COMMENT      = 0x0309, ///< File comment (string).

  // UV/attribute map queries
  CTM_NAME              = 0x0501, ///< Unique name (UV/attrib map string).
  CTM_FILE_NAME         = 0x0502, ///< File name reference (UV map string).
  CTM_PRECISION         = 0x0503, ///< Value precision (UV/attrib map float).

  // Array queries
  CTM_INDICES           = 0x0601, ///< Triangle indices (integer array).
  CTM_VERTICES          = 0x0602, ///< Vertex point coordinates (float array).
  CTM_NORMALS           = 0x0603, ///< Per vertex normals (float array).
  CTM_UV_MAP_1          = 0x0700, ///< Per vertex UV map 1 (float array).
  CTM_UV_MAP_2          = 0x0701, ///< Per vertex UV map 2 (float array).
  CTM_UV_MAP_3          = 0x0702, ///< Per vertex UV map 3 (float array).
  CTM_UV_MAP_4          = 0x0703, ///< Per vertex UV map 4 (float array).
  CTM_UV_MAP_5          = 0x0704, ///< Per vertex UV map 5 (float array).
  CTM_UV_MAP_6          = 0x0705, ///< Per vertex UV map 6 (float array).
  CTM_UV_MAP_7          = 0x0706, ///< Per vertex UV map 7 (float array).
  CTM_UV_MAP_8          = 0x0707, ///< Per vertex UV map 8 (float array).
  CTM_ATTRIB_MAP_1      = 0x0800, ///< Per vertex attribute map 1 (float array).
  CTM_ATTRIB_MAP_2      = 0x0801, ///< Per vertex attribute map 2 (float array).
  CTM_ATTRIB_MAP_3      = 0x0802, ///< Per vertex attribute map 3 (float array).
  CTM_ATTRIB_MAP_4      = 0x0803, ///< Per vertex attribute map 4 (float array).
  CTM_ATTRIB_MAP_5      = 0x0804, ///< Per vertex attribute map 5 (float array).
  CTM_ATTRIB_MAP_6      = 0x0805, ///< Per vertex attribute map 6 (float array).
  CTM_ATTRIB_MAP_7      = 0x0806, ///< Per vertex attribute map 7 (float array).
  CTM_ATTRIB_MAP_8      = 0x0807  ///< Per vertex attribute map 8 (float array).
} CTMenum;

/// Stream read() function pointer.
/// @param[in] aBuf Pointer to the memory buffer to which data should be read.
/// @param[in] aCount The number of bytes to read.
/// @param[in] aUserData The custom user data that was passed to the
///            ctmLoadCustom() function.
/// @return The number of bytes actually read (if this is less than aCount, it
///         indicates that an error occured or the end of file was reached
///         before all bytes were read).
typedef CTMuint (CTMCALL * CTMreadfn)(void * aBuf, CTMuint aCount, void * aUserData);

/// Stream write() function pointer.
/// @param[in] aBuf Pointer to the memory buffer from which data should be written.
/// @param[in] aCount The number of bytes to write.
/// @param[in] aUserData The custom user data that was passed to the
///            ctmSaveCustom() function.
/// @return The number of bytes actually written (if this is less than aCount, it
///         indicates that an error occured).
typedef CTMuint (CTMCALL * CTMwritefn)(const void * aBuf, CTMuint aCount, void * aUserData);

/// Create a new OpenCTM context. The context is used for all subsequent
/// OpenCTM function calls. Several contexts can coexist at the same time.
/// @param[in] aMode An OpenCTM context mode. Set this to CTM_IMPORT if the
///            context will be used for importing data, or set it to CTM_EXPORT
///            if it will be used for exporting data.
/// @return An OpenCTM context handle (or NULL if no context could be created).
CTMEXPORT CTMcontext CTMCALL ctmNewContext(CTMenum aMode);

/// Free an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @see ctmNewContext()
CTMEXPORT void CTMCALL ctmFreeContext(CTMcontext aContext);

/// Returns the latest error. Calling this function will return the last
/// produced error code, or CTM_NO_ERROR (zero) if no error has occured since
/// the last call to ctmGetError(). When this function is called, the internal
/// error varibale will be reset to CTM_NONE.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @return An OpenCTM error code.
/// @see CTMenum
CTMEXPORT CTMenum CTMCALL ctmGetError(CTMcontext aContext);

/// Converts an OpenCTM error code to a zero-terminated string. 
/// @param[in] aError An OpenCTM error code, as returned by ctmGetError().
/// @return A zero terminated string that describes the error. For instance,
///         if \c aError is CTM_INVALID_OPERATION, then the return value will
///         be "CTM_INVALID_OPERATION".
/// @see CTMenum
CTMEXPORT const char * CTMCALL ctmErrorString(CTMenum aError);

/// Get information about an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aProperty Which property to return.
/// @return An integer value, representing the OpenCTM context property given
///         by \c aProperty.
/// @see CTMenum
CTMEXPORT CTMuint CTMCALL ctmGetInteger(CTMcontext aContext, CTMenum aProperty);

/// Get information about an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aProperty Which property to return.
/// @return A floating point value, representing the OpenCTM context property
///         given by \c aProperty.
/// @see CTMenum
CTMEXPORT CTMfloat CTMCALL ctmGetFloat(CTMcontext aContext, CTMenum aProperty);

/// Get an integer array from an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///             ctmNewContext().
/// @param[in] aProperty Which array to return.
/// @return An integer array. If the requested array does not exist, or
///         if \c aProperty does not indicate an integer array, the function
///         returns NULL.
/// @note The array is only valid as long as the OpenCTM context is valid, or
///       until the corresponding array changes within the OpenCTM context.
///       Trying to access an invalid array will result in undefined
///       behaviour. Therefor it is recommended that the array is copied to
///       a new variable if it is to be used other than directly after the call
///       to ctmGetIntegerArray().
/// @see CTMenum
CTMEXPORT const CTMuint * CTMCALL ctmGetIntegerArray(CTMcontext aContext,
  CTMenum aProperty);

/// Get a floating point array from an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aProperty Which array to return.
/// @return A floating point array. If the requested array does not exist, or
///         if \c aProperty does not indicate a float array, the function
///         returns NULL.
/// @note The array is only valid as long as the OpenCTM context is valid, or
///       until the corresponding array changes within the OpenCTM context.
///       Trying to access an invalid array will result in undefined
///       behaviour. Therefor it is recommended that the array is copied to
///       a new variable if it is to be used other than directly after the call
///       to ctmGetFloatArray().
/// @see CTMenum
CTMEXPORT const CTMfloat * CTMCALL ctmGetFloatArray(CTMcontext aContext,
  CTMenum aProperty);

/// Get a reference to the named UV map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aName The name of the UV map that should be returned.
/// @return A reference to a UV map. If the UV map was found, a value of
///         CTM_UV_MAP_1 or higher is returned, otherwise CTM_NONE is
///         returned.
CTMEXPORT CTMenum CTMCALL ctmGetNamedUVMap(CTMcontext aContext,
  const char * aName);

/// Get information about a UV map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aUVMap Which UV map to query (CTM_UV_MAP_1 or higher).
/// @param[in] aProperty Which UV map property to return.
/// @return A string value, representing the UV map property given
///         by \c aProperty.
/// @note The string is only valid as long as the UV map within the OpenCTM
///       context is valid. Trying to access an invalid string will result in
///       undefined behaviour. Therefor it is recommended that the string is
///       copied to a new variable if it is to be used other than directly after
///       the call to ctmGetUVMapString().
/// @see CTMenum
CTMEXPORT const char * CTMCALL ctmGetUVMapString(CTMcontext aContext,
  CTMenum aUVMap, CTMenum aProperty);

/// Get information about a UV map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aUVMap Which UV map to query (CTM_UV_MAP_1 or higher).
/// @param[in] aProperty Which UV map property to return.
/// @return A floating point value, representing the UV map property given
///         by \c aProperty.
/// @see CTMenum
CTMEXPORT CTMfloat CTMCALL ctmGetUVMapFloat(CTMcontext aContext,
  CTMenum aUVMap, CTMenum aProperty);

/// Get a reference to the named vertex attribute map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aName The name of the attribute map that should be returned.
/// @return A reference to an attribute map. If the attribute map was found,
///         a value of CTM_ATTRIB_MAP_1 or higher is returned, otherwise
///         CTM_NONE is returned.
CTMEXPORT CTMenum CTMCALL ctmGetNamedAttribMap(CTMcontext aContext,
  const char * aName);

/// Get information about a vertex attribute map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aAttribMap Which vertex attribute map to query (CTM_ATTRIB_MAP_1
///            or higher).
/// @param[in] aProperty Which vertex attribute map property to return.
/// @return A string value, representing the vertex attribute map property given
///         by \c aProperty.
/// @note The string is only valid as long as the vertex attribute map within
///       the OpenCTM context is valid. Trying to access an invalid string will
///       result in undefined behaviour. Therefor it is recommended that the
///       string is copied to a new variable if it is to be used other than
///       directly after the call to ctmGetAttribMapString().
/// @see CTMenum
CTMEXPORT const char * CTMCALL ctmGetAttribMapString(CTMcontext aContext,
  CTMenum aAttribMap, CTMenum aProperty);

/// Get information about a vertex attribute map.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aAttribMap Which vertex attribute map to query (CTM_ATTRIB_MAP_1
///            or higher).
/// @param[in] aProperty Which vertex attribute map property to return.
/// @return A floating point value, representing the vertex attribute map
///         property given by \c aProperty.
/// @see CTMenum
CTMEXPORT CTMfloat CTMCALL ctmGetAttribMapFloat(CTMcontext aContext,
  CTMenum aAttribMap, CTMenum aProperty);

/// Get information about an OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aProperty Which property to return.
/// @return A string value, representing the OpenCTM context property given
///         by \c aProperty.
/// @note The string is only valid as long as the OpenCTM context is valid, or
///       until the corresponding string changes within the OpenCTM context
///       (e.g. calling ctmFileComment() invalidates the CTM_FILE_COMMENT
///       string). Trying to access an invalid string will result in undefined
///       behaviour. Therefor it is recommended that the string is copied to
///       a new variable if it is to be used other than directly after the call
///       to ctmGetString().
/// @see CTMenum
CTMEXPORT const char * CTMCALL ctmGetString(CTMcontext aContext,
  CTMenum aProperty);

/// Set which compression method to use for the given OpenCTM context.
/// The selected compression method will be used when calling the ctmSave()
/// function.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aMethod Which compression method to use: CTM_METHOD_RAW,
///            CTM_METHOD_MG1 or CTM_METHOD_MG2 (the default method is
///            CTM_METHOD_MG1).
/// @see CTM_METHOD_RAW, CTM_METHOD_MG1, CTM_METHOD_MG2
CTMEXPORT void CTMCALL ctmCompressionMethod(CTMcontext aContext,
  CTMenum aMethod);

/// Set which LZMA compression level to use for the given OpenCTM context.
/// The compression level can be between 0 (fastest) and 9 (best). The higher
/// the compression level, the more memory is required for compression and
/// decompression. The default compression level is 1.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aLevel Which compression level to use (0 to 9).
CTMEXPORT void CTMCALL ctmCompressionLevel(CTMcontext aContext,
  CTMuint aLevel);

/// Set the vertex coordinate precision (only used by the MG2 compression
/// method).
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aPrecision Fixed point precision. For instance, if this value is
///            0.001, all vertex coordinates will be rounded to three decimals.
///            The default vertex coordinate precision is 2^-10 ~= 0.00098.
CTMEXPORT void CTMCALL ctmVertexPrecision(CTMcontext aContext,
  CTMfloat aPrecision);

/// Set the vertex coordinate precision, relative to the mesh dimensions (only
/// used by the MG2 compression method).
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aRelPrecision Relative precision. This factor is multiplied by the
///            average triangle edge length in the mesh in order to obtain the
///            final, fixed point precision. For instance, if aRelPrecision is 
///            0.01, and the average edge length is 3.7, then the fixed point
///            precision is set to 0.037.
/// @note The mesh must have been defined using the ctmDefineMesh() function
///       before calling this function.
/// @see ctmVertexPrecision().
CTMEXPORT void CTMCALL ctmVertexPrecisionRel(CTMcontext aContext,
  CTMfloat aRelPrecision);

/// Set the normal precision (only used by the MG2 compression method). The
/// normal is represented in spherical coordinates in the MG2 compression
/// method, and the normal precision controls the angular and radial resolution.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aPrecision Fixed point precision. For the angular information,
///            this value represents the angular precision. For the radial
///            information, this value is the linear resolution. For instance,
///            0.01 means that the circle is divided into 100 steps, and the
///            normal magnitude is rounded to 2 decimals. The default normal
///            precision is 2^-8 ~= 0.0039.
CTMEXPORT void CTMCALL ctmNormalPrecision(CTMcontext aContext,
  CTMfloat aPrecision);

/// Set the coordinate precision for the specified UV map (only used by the
/// MG2 compression method).
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aUVMap A UV map specifier for a defined UV map
///            (CTM_UV_MAP_1, ...).
/// @param[in] aPrecision Fixed point precision. For instance, if this value is
///            0.001, all UV coordinates will be rounded to three decimals.
///            The default UV coordinate precision is 2^-12 ~= 0.00024.
/// @see ctmAddUVMap().
CTMEXPORT void CTMCALL ctmUVCoordPrecision(CTMcontext aContext,
  CTMenum aUVMap, CTMfloat aPrecision);

/// Set the attribute value precision for the specified attribute map (only
/// used by the MG2 compression method).
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aAttribMap An attribute map specifier for a defined attribute map
///            (CTM_ATTRIB_MAP_1, ...).
/// @param[in] aPrecision Fixed point precision. For instance, if this value is
///            0.001, all attribute values will be rounded to three decimals.
///            If the attributes represent integer values, set the precision
///            to 1.0. The default attribute precision is 2^-8 ~= 0.0039.
/// @see ctmAddAttribMap().
CTMEXPORT void CTMCALL ctmAttribPrecision(CTMcontext aContext,
  CTMenum aAttribMap, CTMfloat aPrecision);

/// Set the file comment for the given OpenCTM context.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aFileComment The file comment (zero terminated UTF-8 string).
CTMEXPORT void CTMCALL ctmFileComment(CTMcontext aContext,
  const char * aFileComment);

/// Define a triangle mesh.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aVertices An array of vertices (three consecutive floats make
///            one vertex).
/// @param[in] aVertexCount The number of vertices in \c aVertices (and
///            optionally \c aTexCoords).
/// @param[in] aIndices An array of vertex indices (three consecutive integers
///            make one triangle).
/// @param[in] aTriangleCount The number of triangles in \c aIndices (there
///            must be exactly 3 x \c aTriangleCount indices in \c aIndices).
/// @param[in] aNormals An array of per-vertex normals (or NULL if there are
///            no normals). Each normal is made up by three consecutive floats,
///            and there must be \c aVertexCount normals.
/// @see ctmAddUVMap(), ctmAddAttribMap(), ctmSave(), ctmSaveCustom().
CTMEXPORT void CTMCALL ctmDefineMesh(CTMcontext aContext,
  const CTMfloat * aVertices, CTMuint aVertexCount, const CTMuint * aIndices,
  CTMuint aTriangleCount, const CTMfloat * aNormals);

/// Define a UV map. There can be several UV maps in a mesh. A UV map is
/// typically used for 2D texture mapping.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aUVCoords An array of UV coordinates. Each UV coordinate is made
///            up by two consecutive floats, and there must be as many
///            coordinates as there are vertices in the mesh.
/// @param[in] aName A unique name for this UV map (zero terminated UTF-8
///            string).
/// @param[in] aFileName A reference to a image file (zero terminated
///            UTF-8 string). If no file name reference exists, pass NULL.
/// @return A UV map index (CTM_UV_MAP_1 and higher). If the function
///         failed, it will return the zero valued CTM_NONE (use ctmGetError()
///         to determine the cause of the error).
/// @note A triangle mesh must have been defined before calling this function,
///       since the number of vertices is defined by the triangle mesh.
/// @see ctmDefineMesh().
CTMEXPORT CTMenum CTMCALL ctmAddUVMap(CTMcontext aContext,
  const CTMfloat * aUVCoords, const char * aName, const char * aFileName);

/// Define a custom vertex attribute map. Custom vertex attributes can be used
/// for defining special per-vertex attributes, such as color, weight, ambient
/// occlusion factor, etc.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aAttribValues An array of attribute values. Each attribute value
///            is made up by four consecutive floats, and there must be as many
///            values as there are vertices in the mesh.
/// @param[in] aName A unique name for this attribute map (zero terminated UTF-8
///            string).
/// @return A attribute map index (CTM_ATTRIB_MAP_1 and higher). If the function
///         failed, it will return the zero valued CTM_NONE (use ctmGetError()
///         to determine the cause of the error).
/// @note A triangle mesh must have been defined before calling this function,
///       since the number of vertices is defined by the triangle mesh.
/// @see ctmDefineMesh().
CTMEXPORT CTMenum CTMCALL ctmAddAttribMap(CTMcontext aContext,
  const CTMfloat * aAttribValues, const char * aName);

/// Load an OpenCTM format file into the context. The mesh data can be retrieved
/// with the various ctmGet functions.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aFileName The name of the file to be loaded.
CTMEXPORT void CTMCALL ctmLoad(CTMcontext aContext, const char * aFileName);

/// Load an OpenCTM format file using a custom stream read function. The mesh
/// data can be retrieved with the various ctmGet functions.
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aReadFn Pointer to a custom stream read function.
/// @param[in] aUserData Custom user data, which can be a C language FILE
///            handle, C++ istream object, or a custom object pointer
///            of any type. The user data pointer will be passed to the
///            custom stream read function.
/// @see CTMreadfn.
CTMEXPORT void CTMCALL ctmLoadCustom(CTMcontext aContext, CTMreadfn aReadFn,
  void * aUserData);

/// Save an OpenCTM format file. The mesh must have been defined by
/// ctmDefineMesh().
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aFileName The name of the file to be saved.
CTMEXPORT void CTMCALL ctmSave(CTMcontext aContext, const char * aFileName);

/// Save an OpenCTM format file using a custom stream write function. The mesh
/// must have been defined by ctmDefineMesh().
/// @param[in] aContext An OpenCTM context that has been created by
///            ctmNewContext().
/// @param[in] aWriteFn Pointer to a custom stream write function.
/// @param[in] aUserData Custom user data, which can be a C language FILE
///            handle, C++ ostream object, or a custom object pointer
///            of any type. The user data pointer will be passed to the
///            custom stream write function.
/// @see CTMwritefn.
CTMEXPORT void CTMCALL ctmSaveCustom(CTMcontext aContext, CTMwritefn aWriteFn,
  void * aUserData);

#ifdef __cplusplus
}
#endif


// C++ extensions to the API (to disable C++ extensions, define OPENCTM_NO_CPP)
#if defined(__cplusplus) && !defined(OPENCTM_NO_CPP)
  #include "openctmpp.h"
#endif

#endif // __OPENCTM_H_
