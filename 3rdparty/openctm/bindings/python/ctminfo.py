#! /usr/bin/env python
#------------------------------------------------------------------------------
# Program:     ctminfo.py
# Description: Show information about an OpenCTM file
# License:     Public domain
#------------------------------------------------------------------------------

import sys
import openctm
from openctm import *

# Check arguments
if len(sys.argv) != 2:
    print("Usage: " + sys.argv[0] + " file")
    sys.exit()

# Create an OpenCTM context, and load the file
ctm = ctmNewContext(CTM_IMPORT)
ctmLoad(ctm, sys.argv[1])
err = ctmGetError(ctm)
if err != CTM_NONE:
    print("Error loading file: " + str(ctmErrorString(err)))
    sys.exit()

# Interpret information
if ctmGetInteger(ctm, CTM_HAS_NORMALS) == CTM_TRUE:
    hasNormals = "yes"
else:
    hasNormals = "no";
method = ctmGetInteger(ctm, CTM_COMPRESSION_METHOD)
if method == CTM_METHOD_RAW:
    methodStr = "RAW"
elif method == CTM_METHOD_MG1:
    methodStr = "MG1"
elif method == CTM_METHOD_MG2:
    methodStr = "MG2"
else:
    methodStr = "Unknown"

# Print information
print("          File: " + sys.argv[1])
print("       Comment: " + str(ctmGetString(ctm, CTM_FILE_COMMENT)))
print("Triangle count: " + str(ctmGetInteger(ctm, CTM_TRIANGLE_COUNT)))
print("  Vertex count: " + str(ctmGetInteger(ctm, CTM_VERTEX_COUNT)))
print("   Has normals: " + hasNormals)
print("        Method: " + methodStr)

# List UV maps
uvMapCount = ctmGetInteger(ctm, CTM_UV_MAP_COUNT)
print("       UV maps: " + str(uvMapCount))
for i in range(uvMapCount):
    print("                CTM_UV_MAP_" + str(i+1) + ": \"" + str(ctmGetUVMapString(ctm, CTM_UV_MAP_1 + i, CTM_NAME)) + "\", ref = \"" + str(ctmGetUVMapString(ctm, CTM_UV_MAP_1 + i, CTM_FILE_NAME)) + "\"")

# List attrib maps
attribMapCount = ctmGetInteger(ctm, CTM_ATTRIB_MAP_COUNT)
print("Attribute maps: " + str(attribMapCount))
for i in range(attribMapCount):
    print("                CTM_ATTRIB_MAP_" + str(i+1) + ": \"" + str(ctmGetAttribMapString(ctm, CTM_ATTRIB_MAP_1 + i, CTM_NAME)) + "\"")

# Free the OpenCTM context
ctmFreeContext(ctm)
