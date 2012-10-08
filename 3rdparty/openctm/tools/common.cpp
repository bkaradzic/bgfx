//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        common.cpp
// Description: Miscellaneous helper functions.
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

using namespace std;

// Convert a string to upper case.
string UpperCase(const string &aString)
{
  string result(aString);
  for(unsigned int i = 0; i < result.size(); ++ i)
    result[i] = toupper(result[i]);
  return result;
}

// Trim heading and trailing white spaces of a string
string TrimString(const string &aString)
{
  size_t l = aString.size();
  size_t p1 = 0, p2 = l - 1;
  while((p1 < p2) && IsWhiteSpace(aString[p1]))
    ++ p1;
  while((p2 > p1) && IsWhiteSpace(aString[p2]))
    -- p2;
  return aString.substr(p1, p2 - p1 + 1);
}

// Extract the file name of a file path (excluding the path).
string ExtractFileName(const string &aString)
{
  string result = "";
  size_t pathPos = aString.rfind("/");
  if(pathPos == string::npos)
    pathPos = aString.rfind("\\");
  if(pathPos != string::npos)
    result = aString.substr(pathPos + 1);
  return result;
}

// Extract the file path of a file path (excluding the file name).
string ExtractFilePath(const string &aString)
{
  string result = "";
  size_t pathPos = aString.rfind("/");
  if(pathPos == string::npos)
    pathPos = aString.rfind("\\");
  if(pathPos != string::npos)
    result = aString.substr(0, pathPos);
  return result;
}

// Extract the file extension of a file name.
string ExtractFileExt(const string &aString)
{
  string result = "";
  size_t extPos = aString.rfind(".");
  if(extPos != string::npos)
    result = aString.substr(extPos);
  return result;
}

// Check if a character is an end-of-line marker or not
bool IsEOL(const char c)
{
  return (c == '\n') || (c == '\r');
}

// Check if a character is a white space or not
bool IsWhiteSpace(const char c)
{
  return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}
