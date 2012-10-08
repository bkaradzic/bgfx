//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        common.h
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

#ifndef __COMMON_H_
#define __COMMON_H_

#include <string>

// Convert a string to upper case.
std::string UpperCase(const std::string &aString);

// Trim heading and trailing white spaces of a string
std::string TrimString(const std::string &aString);

// Extract the file name of a file path (excluding the path).
std::string ExtractFileName(const std::string &aString);

// Extract the file path of a file path (excluding the file name).
std::string ExtractFilePath(const std::string &aString);

// Extract the file extension of a file name.
std::string ExtractFileExt(const std::string &aString);

// Check if a character is an end-of-line marker or not
bool IsEOL(const char c);

// Check if a character is a white space or not
bool IsWhiteSpace(const char c);

#endif // __COMMON_H_
