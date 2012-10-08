#!BPY

"""
Name: 'OpenCTM (*.ctm)...'
Blender: 248
Group: 'Export'
Tooltip: 'Export active object to OpenCTM (compressed) format'
"""

import bpy
import Blender
from Blender import Mesh, Scene, Window, sys, Image, Draw
import BPyMesh
import ctypes
from ctypes import *
from ctypes.util import find_library
import os


__author__ = "Marcus Geelnard"
__version__ = "0.4"
__bpydoc__ = """\
This script exports OpenCTM files from Blender. It supports normals,
colours, and UV coordinates per vertex. Only one mesh can be exported
at a time.
"""

# Copyright (C) 2009-2010: Marcus Geelnard
#
# This program is released to the public domain.
#
# Portions of this code are taken from ply_export.py in Blender
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
#    - Added precision settings for MG2 export
#    - Added some error checking
#
# v0.1, 2009-05-31
#    - First test version with an alpha version of the OpenCTM API
#


def file_callback(filename):
	
	if not filename.lower().endswith('.ctm'):
		filename += '.ctm'

	# Get object mesh from the selected object
	scn = bpy.data.scenes.active
	ob = scn.objects.active
	if not ob:
		Blender.Draw.PupMenu('Error%t|Select 1 active object')
		return
	mesh = BPyMesh.getMeshFromObject(ob, None, False, False, scn)
	if not mesh:
		Blender.Draw.PupMenu('Error%t|Could not get mesh data from active object')
		return

	# Check which mesh properties are present...
	hasVertexUV = mesh.vertexUV or mesh.faceUV
	hasVertexColors = mesh.vertexColors

	# Show a GUI for the export settings
	pupBlock = []
	EXPORT_APPLY_MODIFIERS = Draw.Create(1)
	pupBlock.append(('Apply Modifiers', EXPORT_APPLY_MODIFIERS, 'Use transformed mesh data.'))
	EXPORT_NORMALS = Draw.Create(1)
	pupBlock.append(('Normals', EXPORT_NORMALS, 'Export vertex normal data.'))
	if hasVertexUV:
		EXPORT_UV = Draw.Create(1)
		pupBlock.append(('UVs', EXPORT_UV, 'Export texface UV coords.'))
	if hasVertexColors:
		EXPORT_COLORS = Draw.Create(1)
		pupBlock.append(('Colors', EXPORT_COLORS, 'Export vertex Colors.'))
	EXPORT_MG2 = Draw.Create(0)
	pupBlock.append(('Fixed Point', EXPORT_MG2, 'Use limited precision algorithm (MG2 method = better compression).'))
	if not Draw.PupBlock('Export...', pupBlock):
		return

	# Adjust export settings according to GUI selections
	EXPORT_APPLY_MODIFIERS = EXPORT_APPLY_MODIFIERS.val
	EXPORT_NORMALS = EXPORT_NORMALS.val
	if hasVertexUV:
		EXPORT_UV = EXPORT_UV.val
	else:
		EXPORT_UV = False
	if hasVertexColors:
		EXPORT_COLORS = EXPORT_COLORS.val
	else:
		EXPORT_COLORS = False
	EXPORT_MG2 = EXPORT_MG2.val

	# If the user wants to export MG2, then show another GUI...
	if EXPORT_MG2:
		pupBlock = []
		EXPORT_VPREC = Draw.Create(0.01)
		pupBlock.append(('Vertex', EXPORT_VPREC, 0.0001, 1.0, 'Relative vertex precision (fixed point).'))
		if EXPORT_NORMALS:
			EXPORT_NPREC = Draw.Create(1.0/256.0)
			pupBlock.append(('Normal', EXPORT_NPREC, 0.0001, 1.0, 'Normal precision (fixed point).'))
		if EXPORT_UV:
			EXPORT_UVPREC = Draw.Create(1.0/1024.0)
			pupBlock.append(('UV', EXPORT_UVPREC, 0.0001, 1.0, 'UV precision (fixed point).'))
		if EXPORT_COLORS:
			EXPORT_CPREC = Draw.Create(1.0/256.0)
			pupBlock.append(('Color', EXPORT_CPREC, 0.0001, 1.0, 'Color precision (fixed point).'))
		if not Draw.PupBlock('Fixed point precision...', pupBlock):
			return

	# Adjust export settings according to GUI selections
	if EXPORT_MG2:
		EXPORT_VPREC = EXPORT_VPREC.val
	else:
		EXPORT_VPREC = 0.1
	if EXPORT_MG2 and EXPORT_NORMALS:
		EXPORT_NPREC = EXPORT_NPREC.val
	else:
		EXPORT_NPREC = 0.1
	if EXPORT_MG2 and EXPORT_UV:
		EXPORT_UVPREC = EXPORT_UVPREC.val
	else:
		EXPORT_UVPREC = 0.1
	if EXPORT_MG2 and EXPORT_COLORS:
		EXPORT_CPREC = EXPORT_CPREC.val
	else:
		EXPORT_CPREC = 0.1

	is_editmode = Blender.Window.EditMode()
	if is_editmode:
		Blender.Window.EditMode(0, '', 0)
	Window.WaitCursor(1)
	try:
		# Get the mesh, again, if we wanted modifiers (from GUI selection)
		if EXPORT_APPLY_MODIFIERS:
			mesh = BPyMesh.getMeshFromObject(ob, None, EXPORT_APPLY_MODIFIERS, False, scn)
			if not mesh:
				Blender.Draw.PupMenu('Error%t|Could not get mesh data from active object')
				return
			mesh.transform(ob.matrixWorld, True)

		# Count triangles (quads count as two triangles)
		triangleCount = 0
		for f in mesh.faces:
			if len(f.v) == 4:
				triangleCount += 2
			else:
				triangleCount += 1

		# Extract indices from the Blender mesh (quads are split into two triangles)
		pindices = cast((c_int * 3 * triangleCount)(), POINTER(c_int))
		i = 0
		for f in mesh.faces:
			pindices[i] = c_int(f.v[0].index)
			pindices[i + 1] = c_int(f.v[1].index)
			pindices[i + 2] = c_int(f.v[2].index)
			i += 3
			if len(f.v) == 4:
				pindices[i] = c_int(f.v[0].index)
				pindices[i + 1] = c_int(f.v[2].index)
				pindices[i + 2] = c_int(f.v[3].index)
				i += 3

		# Extract vertex array from the Blender mesh
		vertexCount = len(mesh.verts)
		pvertices = cast((c_float * 3 * vertexCount)(), POINTER(c_float))
		i = 0
		for v in mesh.verts:
			pvertices[i] = c_float(v.co.x)
			pvertices[i + 1] = c_float(v.co.y)
			pvertices[i + 2] = c_float(v.co.z)
			i += 3

		# Extract normals
		if EXPORT_NORMALS:
			pnormals = cast((c_float * 3 * vertexCount)(), POINTER(c_float))
			i = 0
			for v in mesh.verts:
				pnormals[i] = c_float(v.no.x)
				pnormals[i + 1] = c_float(v.no.y)
				pnormals[i + 2] = c_float(v.no.z)
				i += 3
		else:
			pnormals = POINTER(c_float)()

		# Extract UVs
		if EXPORT_UV:
			ptexCoords = cast((c_float * 2 * vertexCount)(), POINTER(c_float))
			if mesh.faceUV:
				for f in mesh.faces:
					for j, v in enumerate(f.v):
						k = v.index
						if k < vertexCount:
							uv = f.uv[j]
							ptexCoords[k * 2] = uv[0]
							ptexCoords[k * 2 + 1] = uv[1]
			else:
				i = 0
				for v in mesh.verts:
					ptexCoords[i] = c_float(v.uvco[0])
					ptexCoords[i + 1] = c_float(v.uvco[1])
					i += 2
		else:
			ptexCoords = POINTER(c_float)()

		# Extract colors
		if EXPORT_COLORS:
			pcolors = cast((c_float * 4 * vertexCount)(), POINTER(c_float))
			for f in mesh.faces:
				for j, v in enumerate(f.v):
					k = v.index
					if k < vertexCount:
						col = f.col[j]
						pcolors[k * 4] = col.r / 255.0
						pcolors[k * 4 + 1] = col.g / 255.0
						pcolors[k * 4 + 2] = col.b / 255.0
						pcolors[k * 4 + 3] = 1.0
		else:
			pcolors = POINTER(c_float)()

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
		ctmFileComment = libHDL.ctmFileComment
		ctmFileComment.argtypes = [c_void_p, c_char_p]
		ctmDefineMesh = libHDL.ctmDefineMesh
		ctmDefineMesh.argtypes = [c_void_p, POINTER(c_float), c_int, POINTER(c_int), c_int, POINTER(c_float)]
		ctmSave = libHDL.ctmSave
		ctmSave.argtypes = [c_void_p, c_char_p]
		ctmAddUVMap = libHDL.ctmAddUVMap
		ctmAddUVMap.argtypes = [c_void_p, POINTER(c_float), c_char_p, c_char_p]
		ctmAddUVMap.restype = c_int
		ctmAddAttribMap = libHDL.ctmAddAttribMap
		ctmAddAttribMap.argtypes = [c_void_p, POINTER(c_float), c_char_p]
		ctmAddAttribMap.restype = c_int
		ctmCompressionMethod = libHDL.ctmCompressionMethod
		ctmCompressionMethod.argtypes = [c_void_p, c_int]
		ctmVertexPrecisionRel = libHDL.ctmVertexPrecisionRel
		ctmVertexPrecisionRel.argtypes = [c_void_p, c_float]
		ctmNormalPrecision = libHDL.ctmNormalPrecision
		ctmNormalPrecision.argtypes = [c_void_p, c_float]
		ctmUVCoordPrecision = libHDL.ctmUVCoordPrecision
		ctmUVCoordPrecision.argtypes = [c_void_p, c_int, c_float]
		ctmAttribPrecision = libHDL.ctmAttribPrecision
		ctmAttribPrecision.argtypes = [c_void_p, c_int, c_float]

		# Create an OpenCTM context
		ctm = ctmNewContext(0x0102)  # CTM_EXPORT
		try:
			# Set the file comment
			ctmFileComment(ctm, c_char_p('%s - created by Blender %s (www.blender.org)' % (ob.getName(), Blender.Get('version'))))

			# Define the mesh
			ctmDefineMesh(ctm, pvertices, c_int(vertexCount), pindices, c_int(triangleCount), pnormals)

			# Add UV coordinates?
			if EXPORT_UV:
				tm = ctmAddUVMap(ctm, ptexCoords, c_char_p(), c_char_p())
				if EXPORT_MG2:
					ctmUVCoordPrecision(ctm, tm, EXPORT_UVPREC)

			# Add colors?
			if EXPORT_COLORS:
				cm = ctmAddAttribMap(ctm, pcolors, c_char_p('Color'))
				if EXPORT_MG2:
					ctmAttribPrecision(ctm, cm, EXPORT_CPREC)

			# Set compression method
			if EXPORT_MG2:
				ctmCompressionMethod(ctm, 0x0203)  # CTM_METHOD_MG2
				ctmVertexPrecisionRel(ctm, EXPORT_VPREC)
				if EXPORT_NORMALS:
					ctmNormalPrecision(ctm, EXPORT_NPREC)

			else:
				ctmCompressionMethod(ctm, 0x0202)  # CTM_METHOD_MG1

			# Save the file
			ctmSave(ctm, c_char_p(filename))

			# Check for errors
			e = ctmGetError(ctm)
			if e != 0:
				s = ctmErrorString(e)
				Blender.Draw.PupMenu('Error%t|Could not save the file: ' + s)

		finally:
			# Free the OpenCTM context
			ctmFreeContext(ctm)

	finally:
		Window.WaitCursor(0)
		if is_editmode:
			Blender.Window.EditMode(1, '', 0)

def main():
	Blender.Window.FileSelector(file_callback, 'Export OpenCTM', Blender.sys.makename(ext='.ctm'))

if __name__=='__main__':
	main()