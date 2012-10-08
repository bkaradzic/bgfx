//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        bin2c.cpp
// Description: Binary to C source code file converter (used for building the
///             tools).
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

#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char ** argv)
{
  // Check arguments
  if(argc != 3)
  {
    cerr << "Usage: " << argv[0] << " file varname" << endl;
    return 0;
  }

  // Open input file
  ifstream f(argv[1], ios::binary | ios::in);
  if(f.fail())
  {
    cerr << "Unable to open file: " << argv[1] << endl;
    return 0;
  }

  // Read & translate input file and print to standard out...
  cout << "static const unsigned char " << argv[2] << "[] = {" << endl;
  while(!f.eof())
  {
    unsigned char buf[19];
    f.read((char *) buf, 19);
    unsigned int count = f.gcount();
    if(count > 0)
    {
      cout << "  ";
      for(unsigned int i = 0; i < count; ++ i)
        cout << int(buf[i]) << ",";
      cout << endl;
    }
  }
  cout << "  0" << endl;
  cout << "};" << endl;

  // Close input file
  f.close();

  return 0;
}
