"""
OpenCTM Exporter for Maya.
"""
import maya.OpenMaya as OpenMaya 
import maya.OpenMayaMPx as OpenMayaMPx
import maya.cmds as mc
import sys, math 
import os
import ctypes
from ctypes import *
import openctm

__author__ = "Jonas Innala"
__version__ = "0.1"

kPluginTranslatorTypeName = "OpenCTM Exporter"
class OpemCTMExporter(OpenMayaMPx.MPxFileTranslator):
        def __init__(self):
                OpenMayaMPx.MPxFileTranslator.__init__(self)
        def haveWriteMethod(self):
                return True
        def haveReadMethod(self):
                return False
        def filter(self):
                return "*.ctm"
        def defaultExtension(self):
                return "ctm"
        def writer( self, fileObject, optionString, accessMode ):
            fileName = fileObject.fullName()
            selection = OpenMaya.MSelectionList()
            all = (accessMode == self.kExportAccessMode  or  accessMode == self.kSaveAccessMode)
            dagIterator = None
            if(all):
                dagIterator = OpenMaya.MItDag(OpenMaya.MItDag.kBreadthFirst, OpenMaya.MFn.kGeometric)
            else:
            	OpenMaya.MGlobal.getActiveSelectionList( selection )
                dagIterator = OpenMaya.MItSelectionList ( selection, OpenMaya.MFn.kGeometric )
            ctmindices = []
            ctmvertices = []
            ctmnormals = []
            ctmtexcoords = []
            indicesOffset = 0
            while not dagIterator.isDone():
                dagPath = OpenMaya.MDagPath()
                if (all):
                    dagIterator.getPath(dagPath)
                else:
                    dagIterator.getDagPath(dagPath)
                fnMesh = None
                try:
                    fnMesh = OpenMaya.MFnMesh( dagPath )
                except:
                    dagIterator.next()
                    continue
                meshPoints = OpenMaya.MPointArray()
                fnMesh.getPoints( meshPoints,OpenMaya.MSpace.kWorld  )

                meshNormals = OpenMaya.MFloatVectorArray()
                fnMesh.getNormals(meshNormals)

                UVSets = []
                fnMesh.getUVSetNames( UVSets )

                                
                u = OpenMaya.MFloatArray()
                v = OpenMaya.MFloatArray()
                fnMesh.getUVs( u, v, UVSets[0] )
                iterPolys = OpenMaya.MItMeshPolygon( dagPath )
                offset = 0
                maxPoints = 0
                normals = {}
                uvs = {}
                while not iterPolys.isDone():
                    if not iterPolys.hasValidTriangulation():
                            return OpenMaya.MStatus.kFailiure
                    
                    uvSet = []
                    iterPolys.getUVSetNames(uvSet)

                    polygonVertices = OpenMaya.MIntArray()
                    iterPolys.getVertices( polygonVertices )


                    numTrianglesPx = OpenMaya.MScriptUtil()
                    numTrianglesPx.createFromInt(0)
                    numTrianglesPtr = numTrianglesPx.asIntPtr()

                    iterPolys.numTriangles(numTrianglesPtr)

                    numTriangles = OpenMaya.MScriptUtil(numTrianglesPtr).asInt()
                    offset = len(ctmvertices)
                    localindices = []
                    for i in range( numTriangles ):

                         points = OpenMaya.MPointArray()
                         indices = OpenMaya.MIntArray()
                         iterPolys.getTriangle( i, points,indices)
                         ctmindices.append (indicesOffset)
                         indicesOffset += 1
                         ctmindices.append (indicesOffset)
                         indicesOffset += 1
                         ctmindices.append (indicesOffset)
                         indicesOffset += 1
                         localindices.append(int(indices[0]))
                         localindices.append(int(indices[1]))
                         localindices.append(int(indices[2]))

                         localIndex = []
                         for  gt in range(indices.length()) : 
                                for  gv in range( polygonVertices.length() ):
                                        if indices[gt] == polygonVertices[gv]:
                                                localIndex.append( gv )
                                                break

                         normals[int(indices[0])] = (float(meshNormals[iterPolys.normalIndex(localIndex[0])].x),float(meshNormals[iterPolys.normalIndex(localIndex[0])].y),float(meshNormals[iterPolys.normalIndex(localIndex[0])].z))
                         normals[int(indices[1])] = (float(meshNormals[iterPolys.normalIndex(localIndex[1])].x),float(meshNormals[iterPolys.normalIndex(localIndex[1])].y),float(meshNormals[iterPolys.normalIndex(localIndex[1])].z))
                         normals[int(indices[2])] = (float(meshNormals[iterPolys.normalIndex(localIndex[2])].x),float(meshNormals[iterPolys.normalIndex(localIndex[2])].y),float(meshNormals[iterPolys.normalIndex(localIndex[2])].z))
                         uvID = [0,0,0]

                         for vtxInPolygon in range(3):
                                 uvIDPx = OpenMaya.MScriptUtil()
                                 uvIDPx.createFromInt(0)
                                 uvIDPtr = numTrianglesPx.asIntPtr()
                                 iterPolys.getUVIndex( localIndex[vtxInPolygon], uvIDPtr, UVSets[0] )
                                 uvID[vtxInPolygon] =  OpenMaya.MScriptUtil(uvIDPtr).asInt()
                         if (iterPolys.hasUVs()):
                                 uvs[int(indices[0])] = (u[uvID[0]], v[uvID[0]])
                                 uvs[int(indices[1])] = (u[uvID[1]], v[uvID[1]])
                                 uvs[int(indices[2])] = (u[uvID[2]], v[uvID[2]])

                    for i in localindices:
                        ctmvertices.append (float(meshPoints[i].x))
                        ctmvertices.append (float(meshPoints[i].y))
                        ctmvertices.append (float(meshPoints[i].z))
                        ctmnormals.append(normals[i][0])
                        ctmnormals.append(normals[i][1])
                        ctmnormals.append(normals[i][2])
                        if (iterPolys.hasUVs()):
                            ctmtexcoords.append(uvs[i][0])
                            ctmtexcoords.append(uvs[i][1])

                    iterPolys.next()
                dagIterator.next()

            pindices = cast((openctm.CTMuint * len(ctmindices))(), POINTER(openctm.CTMuint))
            pvertices = cast((openctm.CTMfloat * len(ctmvertices))(), POINTER(openctm.CTMfloat))
            pnormals = cast((openctm.CTMfloat * len(ctmnormals))(), POINTER(openctm.CTMfloat))
            ptexcoords = cast((openctm.CTMfloat * len(ctmtexcoords))(), POINTER(openctm.CTMfloat))
            for i in range(len(ctmindices)):
                pindices[i] = openctm.CTMuint(ctmindices[i])
            for i in range(len(ctmvertices)):
                pvertices[i] = openctm.CTMfloat(ctmvertices[i])
                pnormals[i] = openctm.CTMfloat(ctmnormals[i])
            for i in range(len(ctmtexcoords)):
                ptexcoords[i] = openctm.CTMfloat(ctmtexcoords[i])   
            
            context = openctm.ctmNewContext(openctm.CTM_EXPORT)
            comment = "Exported with OpenCTM exporter using Maya " + OpenMaya.MGlobal.mayaVersion()
            openctm.ctmFileComment(context, c_char_p(comment))
            openctm.ctmDefineMesh(context, pvertices, openctm.CTMuint(len(ctmvertices)/3), pindices, openctm.CTMuint(len(ctmindices)/3), pnormals)
            openctm.ctmAddUVMap (context, ptexcoords,c_char_p() , c_char_p())
            openctm.ctmSave(context, c_char_p(fileName))
            openctm.ctmFreeContext(context)
            e = openctm.ctmGetError(context)
            if e != 0:
                s = openctm.ctmErrorString(e)
                print s
                return OpenMaya.MStatus.kFailiure
            else:
                return OpenMaya.MStatus.kSuccess
        
        def reader( self, fileObject, optionString, accessMode ):
        		return OpenMaya.MStatus.kFailiure


def translatorCreator():
        return OpenMayaMPx.asMPxPtr( OpemCTMExporter() )

def initializePlugin(mobject): 
        mplugin = OpenMayaMPx.MFnPlugin(mobject, "Autodesk", "10.0", "Any")
        
        try: 
                mplugin.registerFileTranslator( kPluginTranslatorTypeName, None, translatorCreator )
        except: 
                sys.stderr.write( "Failed to register command: %s\n" % kPluginTranslatorTypeName ) 
                raise 
 

def uninitializePlugin(mobject): 
        mplugin = OpenMayaMPx.MFnPlugin(mobject)
        print "Plug-in OpenCTM Exporter uninitialized"
        try: 
                mplugin.deregisterFileTranslator( kPluginTranslatorTypeName )
        except: 
                sys.stderr.write( "Failed to unregister command: %s\n" % kPluginCmdName ) 
                raise 
