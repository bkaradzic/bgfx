unit OpenCTM;
//------------------------------------------------------------------------------
// Product:     OpenCTM
// File:        OpenCTM.pas
// Description: Delphi API bindings.
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
//------------------------------------------------------------------------------

interface

//------------------------------------------------------------------------------
// Types
//------------------------------------------------------------------------------

type
  // Basic types
  TCTMfloat = Single;
  TCTMint = Integer;
  TCTMuint = Cardinal;
  TCTMcontext = Pointer;
  TCTMenum = Cardinal;

  // Pointer types
  PCTMfloat = ^TCTMfloat;
  PCTMint = ^TCTMint;
  PCTMuint = ^TCTMuint;

  // Callback function pointer types
  TCTMreadfn = function (ABuf: Pointer; ACount: TCTMuint; AUserData: Pointer): TCTMuint; stdcall;
  TCTMwritefn = function (ABuf: Pointer; ACount: TCTMuint; AUserData: Pointer): TCTMuint; stdcall;


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

const
  CTM_API_VERSION = $00000100;
  CTM_TRUE  = 1;
  CTM_FALSE = 0;

  // TCTMenum
  CTM_NONE              = $0000;
  CTM_INVALID_CONTEXT   = $0001;
  CTM_INVALID_ARGUMENT  = $0002;
  CTM_INVALID_OPERATION = $0003;
  CTM_INVALID_MESH      = $0004;
  CTM_OUT_OF_MEMORY     = $0005;
  CTM_FILE_ERROR        = $0006;
  CTM_BAD_FORMAT        = $0007;
  CTM_LZMA_ERROR        = $0008;
  CTM_INTERNAL_ERROR    = $0009;
  CTM_UNSUPPORTED_FORMAT_VERSION = $000A;
  CTM_IMPORT            = $0101;
  CTM_EXPORT            = $0102;
  CTM_METHOD_RAW        = $0201;
  CTM_METHOD_MG1        = $0202;
  CTM_METHOD_MG2        = $0203;
  CTM_VERTEX_COUNT      = $0301;
  CTM_TRIANGLE_COUNT    = $0302;
  CTM_HAS_NORMALS       = $0303;
  CTM_UV_MAP_COUNT      = $0304;
  CTM_ATTRIB_MAP_COUNT  = $0305;
  CTM_VERTEX_PRECISION  = $0306;
  CTM_NORMAL_PRECISION  = $0307;
  CTM_COMPRESSION_METHOD = $0308;
  CTM_FILE_COMMENT      = $0309;
  CTM_NAME              = $0501;
  CTM_FILE_NAME         = $0502;
  CTM_PRECISION         = $0503;
  CTM_INDICES           = $0601;
  CTM_VERTICES          = $0602;
  CTM_NORMALS           = $0603;
  CTM_UV_MAP_1          = $0700;
  CTM_UV_MAP_2          = $0701;
  CTM_UV_MAP_3          = $0702;
  CTM_UV_MAP_4          = $0703;
  CTM_UV_MAP_5          = $0704;
  CTM_UV_MAP_6          = $0705;
  CTM_UV_MAP_7          = $0706;
  CTM_UV_MAP_8          = $0707;
  CTM_ATTRIB_MAP_1      = $0800;
  CTM_ATTRIB_MAP_2      = $0801;
  CTM_ATTRIB_MAP_3      = $0802;
  CTM_ATTRIB_MAP_4      = $0803;
  CTM_ATTRIB_MAP_5      = $0804;
  CTM_ATTRIB_MAP_6      = $0805;
  CTM_ATTRIB_MAP_7      = $0806;
  CTM_ATTRIB_MAP_8      = $0807;


//------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------

function ctmNewContext(AMode: TCTMenum): TCTMcontext; stdcall;
procedure ctmFreeContext(AContext: TCTMcontext); stdcall;
function ctmGetError(AContext: TCTMcontext): TCTMenum; stdcall;
function ctmErrorString(AError: TCTMenum): PChar; stdcall;
function ctmGetInteger(AContext: TCTMcontext; AProperty: TCTMenum): TCTMuint; stdcall;
function ctmGetFloat(AContext: TCTMcontext; AProperty: TCTMenum): TCTMfloat; stdcall;
function ctmGetIntegerArray(AContext: TCTMcontext; AProperty: TCTMenum): PCTMuint; stdcall;
function ctmGetFloatArray(AContext: TCTMcontext; AProperty: TCTMenum): PCTMfloat; stdcall;
function ctmGetNamedUVMap(AContext: TCTMcontext; AName: PChar): TCTMenum; stdcall;
function ctmGetUVMapString(AContext: TCTMcontext; AUVMap: TCTMenum; AProperty: TCTMenum): PChar; stdcall;
function ctmGetUVMapFloat(AContext: TCTMcontext; AUVMap: TCTMenum; AProperty: TCTMenum): TCTMfloat; stdcall;
function ctmGetNamedAttribMap(AContext: TCTMcontext; AName: PChar): TCTMenum; stdcall;
function ctmGetAttribMapString(AContext: TCTMcontext; AAttribMap: TCTMenum; AProperty: TCTMenum): PChar; stdcall;
function ctmGetAttribMapFloat(AContext: TCTMcontext; AAttribMap: TCTMenum; AProperty: TCTMenum): TCTMfloat; stdcall;
function ctmGetString(AContext: TCTMcontext; AProperty: TCTMenum): PChar; stdcall;
procedure ctmCompressionMethod(AContext: TCTMcontext; AMethod: TCTMenum); stdcall;
procedure ctmCompressionLevel(AContext: TCTMcontext; ALevel: TCTMuint); stdcall;
procedure ctmVertexPrecision(AContext: TCTMcontext; APrecision: TCTMfloat); stdcall;
procedure ctmVertexPrecisionRel(AContext: TCTMcontext; ARelPrecision: TCTMfloat); stdcall;
procedure ctmNormalPrecision(AContext: TCTMcontext; APrecision: TCTMfloat); stdcall;
procedure ctmUVCoordPrecision(AContext: TCTMcontext; AUVMap: TCTMenum; APrecision: TCTMfloat); stdcall;
procedure ctmAttribPrecision(AContext: TCTMcontext; AAttribMap: TCTMenum; APrecision: TCTMfloat); stdcall;
procedure ctmFileComment(AContext: TCTMcontext; AFileComment: PChar); stdcall;
procedure ctmDefineMesh(AContext: TCTMcontext; AVertices: PCTMfloat; AVertexCount: TCTMuint; AIndices: PCTMuint; ATriangleCount: TCTMuint; ANormals: PCTMfloat); stdcall;
function ctmAddUVMap(AContext: TCTMcontext; AUVCoords: PCTMfloat; AName: PChar; AFileName: PChar): TCTMenum; stdcall;
function ctmAddAttribMap(AContext: TCTMcontext; AAttribValues: PCTMfloat; AName: PChar): TCTMenum; stdcall;
procedure ctmLoad(AContext: TCTMcontext; AFileName: PChar); stdcall;
procedure ctmLoadCustom(AContext: TCTMcontext; AReadFn: TCTMreadfn; AUserData: Pointer); stdcall;
procedure ctmSave(AContext: TCTMcontext; AFileName: PChar); stdcall;
procedure ctmSaveCustom(AContext: TCTMcontext; AWriteFn: TCTMwritefn; AUserData: Pointer); stdcall;


implementation

//------------------------------------------------------------------------------
// DLL interface
//------------------------------------------------------------------------------

const
  DLLNAME = 'openctm.dll';

function ctmNewContext; external DLLNAME;
procedure ctmFreeContext; external DLLNAME;
function ctmGetError; external DLLNAME;
function ctmErrorString; external DLLNAME;
function ctmGetInteger; external DLLNAME;
function ctmGetFloat; external DLLNAME;
function ctmGetIntegerArray; external DLLNAME;
function ctmGetFloatArray; external DLLNAME;
function ctmGetNamedUVMap; external DLLNAME;
function ctmGetUVMapString; external DLLNAME;
function ctmGetUVMapFloat; external DLLNAME;
function ctmGetNamedAttribMap; external DLLNAME;
function ctmGetAttribMapString; external DLLNAME;
function ctmGetAttribMapFloat; external DLLNAME;
function ctmGetString; external DLLNAME;
procedure ctmCompressionMethod; external DLLNAME;
procedure ctmCompressionLevel; external DLLNAME;
procedure ctmVertexPrecision; external DLLNAME;
procedure ctmVertexPrecisionRel; external DLLNAME;
procedure ctmNormalPrecision; external DLLNAME;
procedure ctmUVCoordPrecision; external DLLNAME;
procedure ctmAttribPrecision; external DLLNAME;
procedure ctmFileComment; external DLLNAME;
procedure ctmDefineMesh; external DLLNAME;
function ctmAddUVMap; external DLLNAME;
function ctmAddAttribMap; external DLLNAME;
procedure ctmLoad; external DLLNAME;
procedure ctmLoadCustom; external DLLNAME;
procedure ctmSave; external DLLNAME;
procedure ctmSaveCustom; external DLLNAME;

end.

