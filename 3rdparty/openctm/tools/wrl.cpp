//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        wrl.cpp
// Description: Implementation of the VRML 2.0 file format importer/exporter.
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
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include "wrl.h"
#include "common.h"

using namespace std;


/// VRML reader class
class VRMLReader {
  private:
    /// Read buffer
    char * mBuffer;
    int mBufSize;
    int mBufActual;
    int mBufPos;
    bool mEndOfFile;

    /// File comment(s)
    string mComment;

    /// Read one character from the file stream - via the read buffer
    char GetNextChar()
    {
      if(!mStream)
        throw_runtime_error("VRML input stream undefined.");
      if(mBufPos >= mBufActual)
      {
        mBufPos = 0;
        if(!mStream->eof())
        {
          mStream->read(mBuffer, mBufSize);
          mBufActual = (int)(mStream->gcount());
        }
        else
          mBufActual = 0;
        mEndOfFile = (mBufActual < 1);
      }
      if(!mEndOfFile)
      {
        char c = mBuffer[mBufPos];
        ++ mBufPos;
        return c;
      }
      else
        return ' ';
    }

    /// Read the next line from file
    string GetNextLine()
    {
      // Read the token (until the next new line)
      stringstream sstr;
      char c = GetNextChar();
      while((!mEndOfFile) && (!IsEOL(c)))
      {
        sstr << c;
        c = GetNextChar();
      }
      return sstr.str();
    }

    /// Read a line comment from the stream, and append it to the global
    /// comment string
    void ReadComment()
    {
      // Extract the line comment
      string newComment = TrimString(GetNextLine());

      // Append the line comment to the global comment string
      if(newComment.size() > 0)
      {
        if(mComment.size() > 0)
          mComment = mComment + string(" ");
        mComment = mComment + newComment;
      }
    }

    /// Read the next token from file (skip comments and whitespaces)
    string GetNextToken()
    {
      char c = ' ';

      // Iterate until we find the first character of a token
      while(!mEndOfFile)
      {
        while(!mEndOfFile)
        {
          c = GetNextChar();
          if(!IsWhiteSpace(c))
            break;
        }

        // End of file?
        if(mEndOfFile)
          return string("");

        // Was this a comment?
        if(c == '#')
          ReadComment();
        else
          break;
      }

      // Read the token (until the next white space)
      stringstream sstr;
      while((!mEndOfFile) && (!IsWhiteSpace(c)))
      {
        sstr << c;
        c = GetNextChar();
      }
      return sstr.str();
    }

  public:
    /// Constructor
    VRMLReader()
    {
      // Init read buffer
      mBufSize = 1024;
      mBuffer = new char[mBufSize];
      mBufActual = 0;
      mBufPos = 0;
      mEndOfFile = false;

      // Clear state
      mStream = 0;
      mComment = string("");
    }

    /// Destructor
    ~VRMLReader()
    {
      delete [] mBuffer;
    }

    /// Read the mesh from a file
    void ReadMesh(Mesh * aMesh)
    {
      // Read the header
      string header = GetNextLine();
      if(header.substr(0, 10) != string("#VRML V2.0"))
        throw_runtime_error("Not a valid VRML 2.0 file.");

      // Read the rest of the file
      while(!mEndOfFile)
      {
        string token = GetNextToken();
        if(token == string("geometry"))
        {
          token = GetNextToken();
          if(token == string("IndexedFaceSet"))
          {
            // ...FIXME
          }
        }
      }

      // Set mesh comment (if any)
      aMesh->mComment = mComment;
    }

    /// Input file stream
    ifstream * mStream;
};


/// Import a mesh from a VRML 2.0 file.
void Import_WRL(const char * aFileName, Mesh * aMesh)
{
  // FIXME: The import functionality has not yet been fully implemented
  throw_runtime_error("VRML import is not yet supported.");

  // Clear the mesh
  aMesh->Clear();

  // Open the input file
  ifstream f(aFileName, ios::in);
  if(f.fail())
    throw_runtime_error("Could not open input file.");

  // Initialize the reader object
  VRMLReader reader;
  reader.mStream = &f;

  // Read the entire file...
  reader.ReadMesh(aMesh);

  // Close the input file
  f.close();
}

/// Export a mesh to a VRML 2.0 file.
void Export_WRL(const char * aFileName, Mesh * aMesh, Options &aOptions)
{
  // Open the output file
  ofstream f(aFileName, ios::out);
  if(f.fail())
    throw_runtime_error("Could not open output file.");

  // Set floating point precision
  f << setprecision(8);

  // Write VRML file header ID
  f << "#VRML V2.0 utf8" << endl;

  // Write comment
  if(aMesh->mComment.size() > 0)
  {
    stringstream sstr(aMesh->mComment);
    sstr.seekg(0);
    while(!sstr.eof())
    {
      string line;
      getline(sstr, line);
      line = TrimString(line);
      if(line.size() > 0)
        f << "# " << line << endl;
    }
  }
  f << endl;

  // Write shape header
  f << "Group {" << endl;
  f << "\tchildren [" << endl;
  f << "\t\tShape {" << endl;
  f << "\t\t\tappearance Appearance {" << endl;
  f << "\t\t\t\tmaterial Material {" << endl;
  f << "\t\t\t\t\tdiffuseColor 1.0 1.0 1.0" << endl;
  f << "\t\t\t\t\tambientIntensity 0.2" << endl;
  f << "\t\t\t\t\tspecularColor 0.8 0.8 0.8" << endl;
  f << "\t\t\t\t\tshininess 0.4" << endl;
  f << "\t\t\t\t\ttransparency 0" << endl;
  f << "\t\t\t\t}" << endl;
  f << "\t\t\t}" << endl;
  f << "\t\t\tgeometry IndexedFaceSet {" << endl;
  f << "\t\t\t\tccw TRUE" << endl;
  f << "\t\t\t\tsolid FALSE" << endl;

  // Write vertices
  f << "\t\t\t\tcoord DEF co Coordinate {" << endl;
  f << "\t\t\t\t\tpoint [" << endl;
  for(unsigned int i = 0; i < aMesh->mVertices.size(); ++ i)
  {
    f << "\t\t\t\t\t\t" <<
         aMesh->mVertices[i].x << " " <<
         aMesh->mVertices[i].y << " " <<
         aMesh->mVertices[i].z << "," << endl;
  }
  f << "\t\t\t\t\t]" << endl;
  f << "\t\t\t\t}" << endl;

  // Write faces
  f << "\t\t\t\tcoordIndex [" << endl;
  unsigned int triCount = (unsigned int)(aMesh->mIndices.size() / 3);
  for(unsigned int i = 0; i < triCount; ++ i)
  {
    f << "\t\t\t\t\t" <<
         aMesh->mIndices[i * 3] << ", " <<
         aMesh->mIndices[i * 3 + 1] << ", " <<
         aMesh->mIndices[i * 3 + 2] << ", -1," << endl;
  }
  f << "\t\t\t\t]" << endl;

  // Write shape footer
  f << "\t\t\t}" << endl;
  f << "\t\t}" << endl;
  f << "\t]" << endl;
  f << "}" << endl;

  // Close the output file
  f.close();
}
