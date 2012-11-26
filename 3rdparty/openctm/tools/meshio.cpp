//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        meshio.cpp
// Description: Mesh I/O using different file format loaders/savers.
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

#include "common.h"
#include <string>
#include <list>
#include "mesh.h"
#include "meshio.h"
#include "convoptions.h"
#include "ctm.h"
#include "ply.h"
#include "stl.h"
#include "3ds.h"
#include "dae.h"
#include "obj.h"
#include "lwo.h"
#include "off.h"
#include "wrl.h"
#include "common.h"

using namespace std;


/// Import a mesh from a file.
void ImportMesh(const char * aFileName, Mesh * aMesh)
{
  string fileExt = UpperCase(ExtractFileExt(string(aFileName)));
  if(fileExt == string(".CTM"))
    Import_CTM(aFileName, aMesh);
  else if(fileExt == string(".PLY"))
    Import_PLY(aFileName, aMesh);
  else if(fileExt == string(".STL"))
    Import_STL(aFileName, aMesh);
  else if(fileExt == string(".3DS"))
    Import_3DS(aFileName, aMesh);
  else if(fileExt == string(".DAE"))
    Import_DAE(aFileName, aMesh);
  else if(fileExt == string(".OBJ"))
    Import_OBJ(aFileName, aMesh);
  else if(fileExt == string(".LWO"))
    Import_LWO(aFileName, aMesh);
  else if(fileExt == string(".OFF"))
    Import_OFF(aFileName, aMesh);
  else if(fileExt == string(".WRL"))
    Import_WRL(aFileName, aMesh);
  else
    throw_runtime_error("Unknown input file extension.");
}

/// Export a mesh to a file.
void ExportMesh(const char * aFileName, Mesh * aMesh, Options &aOptions)
{
  string fileExt = UpperCase(ExtractFileExt(string(aFileName)));
  if(fileExt == string(".CTM"))
    Export_CTM(aFileName, aMesh, aOptions);
  else if(fileExt == string(".PLY"))
    Export_PLY(aFileName, aMesh, aOptions);
  else if(fileExt == string(".STL"))
    Export_STL(aFileName, aMesh, aOptions);
  else if(fileExt == string(".3DS"))
    Export_3DS(aFileName, aMesh, aOptions);
  else if(fileExt == string(".DAE"))
    Export_DAE(aFileName, aMesh, aOptions);
  else if(fileExt == string(".OBJ"))
    Export_OBJ(aFileName, aMesh, aOptions);
  else if(fileExt == string(".LWO"))
    Export_LWO(aFileName, aMesh, aOptions);
  else if(fileExt == string(".OFF"))
    Export_OFF(aFileName, aMesh, aOptions);
  else if(fileExt == string(".WRL"))
    Export_WRL(aFileName, aMesh, aOptions);
  else
    throw_runtime_error("Unknown output file extension.");
}

/// Return a list of supported formats.
void SupportedFormats(list<string> &aList)
{
  aList.push_back(string("OpenCTM (.ctm)"));
  aList.push_back(string("Stanford triangle format (.ply)"));
  aList.push_back(string("Stereolithography (.stl)"));
  aList.push_back(string("3D Studio (.3ds)"));
  aList.push_back(string("COLLADA 1.4/1.5 (.dae)"));
  aList.push_back(string("Wavefront geometry file (.obj)"));
  aList.push_back(string("LightWave object (.lwo)"));
  aList.push_back(string("Geomview object file format (.off)"));
  aList.push_back(string("VRML 2.0 (.wrl) - export only"));
}
