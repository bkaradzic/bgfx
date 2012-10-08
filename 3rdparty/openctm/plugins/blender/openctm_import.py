#!BPY

"""
Name: 'OpenCTM (*.ctm)...'
Blender: 248
Group: 'Import'
Tooltip: 'Import an OpenCTM file'
"""

import bpy
import Blender
from Blender import Mesh, Scene, Window, sys, Image, Draw
import BPyMesh
import math
import ctypes
from ctypes import *
from ctypes.util import find_library
import os


__author__ = "Marcus Geelnard"
__version__ = "0.4"
__bpydoc__ = """\
This script imports OpenCTM files into Blender. It supports normals,
colours, and UV coordinates per vertex.
"""

# Copyright (C) 2009-2010: Marcus Geelnard
#
# This program is released to the public domain.
#
# Portions of this code are taken from ply_import.py in Blender
# 2.48.
#
# The script uses the OpenCTM shared library (.so, .dll, etc). If no
# such library can be found, the script will exit with an error
# message.
#
# v0.4, 2009-09-14
#    - Updated to OpenCTM API version 0.8 (texture maps are now called UV maps)
#
# v0.3, 2009-08-09
#    - Changed vertex color attribute name to "Color"
#
# v0.2, 2009-06-30
#    - Better error reporting
#
# v0.1, 2009-05-31
#    - First test version with an alpha version of the OpenCTM API
#

def file_callback(filename):

	Window.WaitCursor(1)
	try:
		# Load the OpenCTM shared library
		if os.name == 'nt':
			libHDL = WinDLL('openctm.dll')
		else:
			libName = find_library('openctm')
			if not libName:
				Blender.Draw.PupMenu('Could not find the OpenCTM shared library')
				return
			libHDL = CDLL(libName)
		if not libHDL:
			Blender.Draw.PupMenu('Could not open the OpenCTM shared library')
			return

		# Get all the functions from the shared library that we need
		ctmNewContext = libHDL.ctmNewContext
		ctmNewContext.argtypes = [c_int]
		ctmNewContext.restype = c_void_p
		ctmFreeContext = libHDL.ctmFreeContext
		ctmFreeContext.argtypes = [c_void_p]
		ctmGetError = libHDL.ctmGetError
		ctmGetError.argtypes = [c_void_p]
		ctmGetError.restype = c_int
		ctmErrorString = libHDL.ctmErrorString
		ctmErrorString.argtypes = [c_int]
		ctmErrorString.restype = c_char_p
		ctmLoad = libHDL.ctmLoad
		ctmLoad.argtypes = [c_void_p, c_char_p]
		ctmGetInteger = libHDL.ctmGetInteger
		ctmGetInteger.argtypes = [c_void_p, c_int]
		ctmGetInteger.restype = c_int
		ctmGetString = libHDL.ctmGetString
		ctmGetString.argtypes = [c_void_p, c_int]
		ctmGetString.restype = c_char_p
		ctmGetIntegerArray = libHDL.ctmGetIntegerArray
		ctmGetIntegerArray.argtypes = [c_void_p, c_int]
		ctmGetIntegerArray.restype = POINTER(c_int)
		ctmGetFloatArray = libHDL.ctmGetFloatArray
		ctmGetFloatArray.argtypes = [c_void_p, c_int]
		ctmGetFloatArray.restype = POINTER(c_float)
		ctmGetNamedAttribMap = libHDL.ctmGetNamedAttribMap
		ctmGetNamedAttribMap.argtypes = [c_void_p, c_char_p]
		ctmGetNamedAttribMap.restype = c_int

		# Create an OpenCTM context
		ctm = ctmNewContext(0x0101)  # CTM_IMPORT
		try:
			# Load the file
			ctmLoad(ctm, c_char_p(filename))
			err = ctmGetError(ctm)
			if err != 0:
				s = ctmErrorString(err)
				Blender.Draw.PupMenu('Could not load the file: ' + s)
				return

			# Get the mesh properties
			vertexCount = ctmGetInteger(ctm, 0x0301)   # CTM_VERTEX_COUNT
			triangleCount = ctmGetInteger(ctm, 0x0302) # CTM_TRIANGLE_COUNT
			hasNormals = ctmGetInteger(ctm, 0x0303)    # CTM_HAS_NORMALS
			texMapCount = ctmGetInteger(ctm, 0x0304)   # CTM_UV_MAP_COUNT

			# Get indices
			pindices = ctmGetIntegerArray(ctm, 0x0601) # CTM_INDICES

			# Get vertices
			pvertices = ctmGetFloatArray(ctm, 0x0602)  # CTM_VERTICES

			# Get normals
			if hasNormals == 1:
				pnormals = ctmGetFloatArray(ctm, 0x0603) # CTM_NORMALS
			else:
				pnormals = None

			# Get texture coordinates
			if texMapCount > 0:
				ptexCoords = ctmGetFloatArray(ctm, 0x0700) # CTM_UV_MAP_1
			else:
				ptexCoords = None

			# Get colors
			colorMap = ctmGetNamedAttribMap(ctm, c_char_p('Color'))
			if colorMap != 0:
				pcolors = ctmGetFloatArray(ctm, colorMap)
			else:
				pcolors = None

			# We will be creating vectors...
			Vector = Blender.Mathutils.Vector

			# Create Blender verts and faces
			verts = []
			for i in range(vertexCount):
				verts.append(Vector(pvertices[i * 3], pvertices[i * 3 + 1], pvertices[i * 3 + 2]))
			faces = []
			for i in range(triangleCount):
				faces.append((pindices[i * 3], pindices[i * 3 + 1], pindices[i * 3 + 2]))

			# Create a new Blender mesh from the loaded mesh data
			objName = Blender.sys.splitext(Blender.sys.basename(filename))[0]
			mesh = bpy.data.meshes.new(objName)
			mesh.verts.extend(verts)
			mesh.faces.extend(faces)

			# Add normals?
			if pnormals:
				i = 0
				for v in mesh.verts:
					n = Vector(pnormals[i], pnormals[i + 1], pnormals[i + 2])
					v.no = n
					i += 3
			else:
				mesh.calcNormals()

			# Always use smooth normals - regardless if they are defined or calculated
			for f in mesh.faces:
				f.smooth = 1

			# Add texture coordinates?
			if ptexCoords:
				mesh.faceUV = 1
				for f in mesh.faces:
					for j, v in enumerate(f.v):
						k = v.index
						if k < vertexCount:
							uv = f.uv[j]
							uv[0] = ptexCoords[k * 2]
							uv[1] = ptexCoords[k * 2 + 1]

			# Add colors?
			if pcolors:
				mesh.vertexColors = 1
				for f in mesh.faces:
					for j, v in enumerate(f.v):
						k = v.index
						if k < vertexCount:
							col = f.col[j]
							r = int(round(pcolors[k * 4] * 255.0))
							if r < 0: r = 0
							if r > 255: r = 255
							g = int(round(pcolors[k * 4 + 1] * 255.0))
							if g < 0: g = 0
							if g > 255: g = 255
							b = int(round(pcolors[k * 4 + 2] * 255.0))
							if b < 0: b = 0
							if b > 255: b = 255
							col.r = r
							col.g = g
							col.b = b

			# Select all vertices in the mesh
			mesh.sel = True
		
			# Create a new object with the new mesh
			scn = bpy.data.scenes.active
			scn.objects.selected = []
			obj = scn.objects.new(mesh, objName)
			scn.objects.active = obj

		finally:
			# Free the OpenCTM context
			ctmFreeContext(ctm)

	finally:
		Window.WaitCursor(0)

	Blender.Redraw()

def main():
	Blender.Window.FileSelector(file_callback, 'Import OpenCTM', '*.ctm')

if __name__=='__main__':
	main()