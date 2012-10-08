#------------------------------------------------------------------------------
# Product:     OpenCTM
# File:        openctm.py
# Description: Python API bindings (tested with Python 2.5.2 and Python 3.0)
#------------------------------------------------------------------------------
# Copyright (c) 2009-2010 Marcus Geelnard
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not
#     be misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source
#     distribution.
#------------------------------------------------------------------------------

import os
import ctypes
from ctypes import *
from ctypes.util import find_library

# Types
CTMfloat = c_float
CTMint = c_int32
CTMuint = c_uint32
CTMcontext = c_void_p
CTMenum = c_uint32

# Constants
CTM_API_VERSION = 0x00000100
CTM_TRUE = 1
CTM_FALSE = 0

# CTMenum
CTM_NONE = 0x0000
CTM_INVALID_CONTEXT = 0x0001
CTM_INVALID_ARGUMENT = 0x0002
CTM_INVALID_OPERATION = 0x0003
CTM_INVALID_MESH = 0x0004
CTM_OUT_OF_MEMORY = 0x0005
CTM_FILE_ERROR = 0x0006
CTM_BAD_FORMAT = 0x0007
CTM_LZMA_ERROR = 0x0008
CTM_INTERNAL_ERROR = 0x0009
CTM_UNSUPPORTED_FORMAT_VERSION = 0x000A
CTM_IMPORT = 0x0101
CTM_EXPORT = 0x0102
CTM_METHOD_RAW = 0x0201
CTM_METHOD_MG1 = 0x0202
CTM_METHOD_MG2 = 0x0203
CTM_VERTEX_COUNT = 0x0301
CTM_TRIANGLE_COUNT = 0x0302
CTM_HAS_NORMALS = 0x0303
CTM_UV_MAP_COUNT = 0x0304
CTM_ATTRIB_MAP_COUNT = 0x0305
CTM_VERTEX_PRECISION = 0x0306
CTM_NORMAL_PRECISION = 0x0307
CTM_COMPRESSION_METHOD = 0x0308
CTM_FILE_COMMENT = 0x0309
CTM_NAME = 0x0501
CTM_FILE_NAME = 0x0502
CTM_PRECISION = 0x0503
CTM_INDICES = 0x0601
CTM_VERTICES = 0x0602
CTM_NORMALS = 0x0603
CTM_UV_MAP_1 = 0x0700
CTM_UV_MAP_2 = 0x0701
CTM_UV_MAP_3 = 0x0702
CTM_UV_MAP_4 = 0x0703
CTM_UV_MAP_5 = 0x0704
CTM_UV_MAP_6 = 0x0705
CTM_UV_MAP_7 = 0x0706
CTM_UV_MAP_8 = 0x0707
CTM_ATTRIB_MAP_1 = 0x0800
CTM_ATTRIB_MAP_2 = 0x0801
CTM_ATTRIB_MAP_3 = 0x0802
CTM_ATTRIB_MAP_4 = 0x0803
CTM_ATTRIB_MAP_5 = 0x0804
CTM_ATTRIB_MAP_6 = 0x0805
CTM_ATTRIB_MAP_7 = 0x0806
CTM_ATTRIB_MAP_8 = 0x0807

# Load the OpenCTM shared library
if os.name == 'nt':
    _lib = WinDLL('openctm.dll')
else:
    _libName = find_library('openctm')
    if not _libName:
        raise Exception('Could not find the OpenCTM shared library.')
    _lib = CDLL(_libName)
if not _lib:
    raise Exception('Could not open the OpenCTM shared library.')

# Functions
ctmNewContext = _lib.ctmNewContext
ctmNewContext.argtypes = [CTMenum]
ctmNewContext.restype = CTMcontext

ctmFreeContext = _lib.ctmFreeContext
ctmFreeContext.argtypes = [CTMcontext]

ctmGetError = _lib.ctmGetError
ctmGetError.argtypes = [CTMcontext]
ctmGetError.restype = CTMenum

ctmErrorString = _lib.ctmErrorString
ctmErrorString.argtypes = [CTMenum]
ctmErrorString.restype = c_char_p

ctmGetInteger = _lib.ctmGetInteger
ctmGetInteger.argtypes = [CTMcontext, CTMenum]
ctmGetInteger.restype = CTMint

ctmGetFloat = _lib.ctmGetFloat
ctmGetFloat.argtypes = [CTMcontext, CTMenum]
ctmGetFloat.restype = CTMfloat

ctmGetIntegerArray = _lib.ctmGetIntegerArray
ctmGetIntegerArray.argtypes = [CTMcontext, CTMenum]
ctmGetIntegerArray.restype = POINTER(CTMuint)

ctmGetFloatArray = _lib.ctmGetFloatArray
ctmGetFloatArray.argtypes = [CTMcontext, CTMenum]
ctmGetFloatArray.restype = POINTER(CTMfloat)

ctmGetNamedUVMap = _lib.ctmGetNamedUVMap
ctmGetNamedUVMap.argtypes = [CTMcontext, c_char_p]
ctmGetNamedUVMap.restype = CTMenum

ctmGetUVMapString = _lib.ctmGetUVMapString
ctmGetUVMapString.argtypes = [CTMcontext, CTMenum, CTMenum]
ctmGetUVMapString.restype = c_char_p

ctmGetUVMapFloat = _lib.ctmGetUVMapFloat
ctmGetUVMapFloat.argtypes = [CTMcontext, CTMenum, CTMenum]
ctmGetUVMapFloat.restype = CTMfloat

ctmGetNamedAttribMap = _lib.ctmGetNamedAttribMap
ctmGetNamedAttribMap.argtypes = [CTMcontext, c_char_p]
ctmGetNamedAttribMap.restype = CTMenum

ctmGetAttribMapString = _lib.ctmGetAttribMapString
ctmGetAttribMapString.argtypes = [CTMcontext, CTMenum, CTMenum]
ctmGetAttribMapString.restype = c_char_p

ctmGetAttribMapFloat = _lib.ctmGetAttribMapFloat
ctmGetAttribMapFloat.argtypes = [CTMcontext, CTMenum, CTMenum]
ctmGetAttribMapFloat.restype = CTMfloat

ctmGetString = _lib.ctmGetString
ctmGetString.argtypes = [CTMcontext, CTMenum]
ctmGetString.restype = c_char_p

ctmCompressionMethod = _lib.ctmCompressionMethod
ctmCompressionMethod.argtypes = [CTMcontext, CTMenum]

ctmCompressionLevel = _lib.ctmCompressionLevel
ctmCompressionLevel.argtypes = [CTMcontext, CTMuint]

ctmVertexPrecision = _lib.ctmVertexPrecision
ctmVertexPrecision.argtypes = [CTMcontext, CTMfloat]

ctmVertexPrecisionRel = _lib.ctmVertexPrecisionRel
ctmVertexPrecisionRel.argtypes = [CTMcontext, CTMfloat]

ctmNormalPrecision = _lib.ctmNormalPrecision
ctmNormalPrecision.argtypes = [CTMcontext, CTMfloat]

ctmUVCoordPrecision = _lib.ctmUVCoordPrecision
ctmUVCoordPrecision.argtypes = [CTMcontext, CTMenum, CTMfloat]

ctmAttribPrecision = _lib.ctmAttribPrecision
ctmAttribPrecision.argtypes = [CTMcontext, CTMenum, CTMfloat]

ctmFileComment = _lib.ctmFileComment
ctmFileComment.argtypes = [CTMcontext, c_char_p]

ctmDefineMesh = _lib.ctmDefineMesh
ctmDefineMesh.argtypes = [CTMcontext, POINTER(CTMfloat), CTMuint, POINTER(CTMuint), CTMuint, POINTER(CTMfloat)]

ctmAddUVMap = _lib.ctmAddUVMap
ctmAddUVMap.argtypes = [CTMcontext, POINTER(CTMfloat), c_char_p, c_char_p]
ctmAddUVMap.restype = CTMenum

ctmAddAttribMap = _lib.ctmAddAttribMap
ctmAddAttribMap.argtypes = [CTMcontext, POINTER(CTMfloat), c_char_p]
ctmAddAttribMap.restype = CTMenum

ctmLoad = _lib.ctmLoad
ctmLoad.argtypes = [CTMcontext, c_char_p]

ctmSave = _lib.ctmSave
ctmSave.argtypes = [CTMcontext, c_char_p]
