//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        convoptions.cpp
// Description: Implementation of the conversion options class.
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
#include <sstream>
#include "convoptions.h"

using namespace std;


/// Constructor
Options::Options()
{
  // Set default values
  mScale = 1.0f;
  mUpAxis = uaZ;
  mFlipTriangles = false;
  mCalcNormals = false;
  mNoNormals = false;
  mNoTexCoords = false;
  mNoColors = false;

  mMethod = CTM_METHOD_MG2;
  mLevel = 1;
  mVertexPrecision = 0.0f;
  mVertexPrecisionRel = 0.01f;
  mNormalPrecision = 1.0f / 256.0f;
  mTexMapPrecision = 1.0f / 4096.0f;
  mColorPrecision = 1.0f / 256.0f;
  mComment = string("");
  mTexFileName = string("");
}

/// Convert a string to a floating point value
static CTMfloat GetFloatArg(char * aFloatString)
{
  stringstream s;
  s << aFloatString;
  s.seekg(0);
  CTMfloat f;
  s >> f;
  return f;
}

/// Convert a string to an integer value
static CTMint GetIntArg(char * aIntString)
{
  stringstream s;
  s << aIntString;
  s.seekg(0);
  CTMint i;
  s >> i;
  return i;
}

/// Get options from the command line arguments
void Options::GetFromArgs(int argc, char **argv, int aStartIdx)
{
  for(int i = aStartIdx; i < argc; ++ i)
  {
    string cmd(argv[i]);
    if((cmd == string("--scale")) && (i < (argc - 1)))
    {
      mScale = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--upaxis")) && (i < (argc - 1)))
    {
      string upaxis(argv[i + 1]);
      ++ i;
      if(upaxis == string("X"))
        mUpAxis = uaX;
      else if(upaxis == string("Y"))
        mUpAxis = uaY;
      else if(upaxis == string("Z"))
        mUpAxis = uaZ;
      else if(upaxis == string("-X"))
        mUpAxis = uaNX;
      else if(upaxis == string("-Y"))
        mUpAxis = uaNY;
      else if(upaxis == string("-Z"))
        mUpAxis = uaNZ;
      else
        throw_runtime_error("Invalid up axis (use X, Y, Z, -X, -Y or -Z).");
    }
    else if(cmd == string("--flip"))
    {
      mFlipTriangles = true;
    }
    else if(cmd == string("--calc-normals"))
    {
      mCalcNormals = true;
    }
    else if(cmd == string("--no-normals"))
    {
      mNoNormals = true;
    }
    else if(cmd == string("--no-texcoords"))
    {
      mNoTexCoords = true;
    }
    else if(cmd == string("--no-colors"))
    {
      mNoColors = true;
    }
    else if((cmd == string("--method")) && (i < (argc - 1)))
    {
      string method(argv[i + 1]);
      ++ i;
      if(method == string("RAW"))
        mMethod = CTM_METHOD_RAW;
      else if(method == string("MG1"))
        mMethod = CTM_METHOD_MG1;
      else if(method == string("MG2"))
        mMethod = CTM_METHOD_MG2;
      else
        throw_runtime_error("Invalid method (use RAW, MG1 or MG2).");
    }
    else if((cmd == string("--level")) && (i < (argc - 1)))
    {
      CTMint val = GetIntArg(argv[i + 1]);
      if( (val < 0) || (val > 9) )
        throw_runtime_error("Invalid compression level (it must be in the range 0 - 9).");
      mLevel = CTMuint(val);
      ++ i;
    }
    else if((cmd == string("--vprec")) && (i < (argc - 1)))
    {
      mVertexPrecision = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--vprecrel")) && (i < (argc - 1)))
    {
      mVertexPrecisionRel = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--nprec")) && (i < (argc - 1)))
    {
      mNormalPrecision = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--tprec")) && (i < (argc - 1)))
    {
      mTexMapPrecision = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--cprec")) && (i < (argc - 1)))
    {
      mColorPrecision = GetFloatArg(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--comment")) && (i < (argc - 1)))
    {
      mComment = string(argv[i + 1]);
      ++ i;
    }
    else if((cmd == string("--texfile")) && (i < (argc - 1)))
    {
      mTexFileName = string(argv[i + 1]);
      ++ i;
    }
    else
      throw_runtime_error(string("Invalid argument: ") + cmd);
  }
}
