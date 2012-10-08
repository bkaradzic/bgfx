//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        ctmbench.cpp
// Description: Load/save benchmark tool. This tools is actually just a quick
//              hack used for development and testing. To change the compression
//              parameters for the save benchmarks, a recompile is required.
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

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <openctm.h>
#include "systimer.h"

using namespace std;


//-----------------------------------------------------------------------------
// BenchmarkLoads() - Benchmark function for loading OpenCTM files.
//-----------------------------------------------------------------------------

void BenchmarkLoads(int aIterations, const char * aFileName, double &tMin,
  double &tMax, double &tTotal)
{
  SysTimer timer;

  // Iterate...
  cout << "Doing " << aIterations << " load iterations..." << endl << flush;
  for(int i = 0; i < aIterations; ++ i)
  {
    CTMimporter ctm;

    // Start the timer
    timer.Push();

    // Load the file
    ctm.Load(aFileName);

    // Stop the timer
    double t = timer.PopDelta();
    if(i == 0)
    {
      tMin = t;
      tMax = t;
    }
    else
    {
      if(t < tMin) tMin = t;
      if(t > tMax) tMax = t;
    }
    tTotal += t;
  }
}


//-----------------------------------------------------------------------------
// BenchmarkSaves() - Benchmark function for saving OpenCTM files.
//-----------------------------------------------------------------------------

void BenchmarkSaves(int aIterations, const char * aInFile, const char * aOutFile,
  double &tMin, double &tMax, double &tTotal)
{
  SysTimer timer;

  // Load the file
  CTMimporter in;
  in.Load(aInFile);

  // Extract mesh definition
  CTMint triCount = in.GetInteger(CTM_TRIANGLE_COUNT);
  CTMint vertCount = in.GetInteger(CTM_VERTEX_COUNT);
  const CTMuint * indx = in.GetIntegerArray(CTM_INDICES);
  const CTMfloat * vert = in.GetFloatArray(CTM_VERTICES);
  const CTMfloat * norm = 0;
  if(in.GetInteger(CTM_HAS_NORMALS))
    norm = in.GetFloatArray(CTM_NORMALS);

  // Iterate...
  cout << "Doing " << aIterations << " save iterations..." << endl << flush;
  for(int i = 0; i < aIterations; ++ i)
  {
    // Define the mesh
    CTMexporter out;
    out.DefineMesh(vert, vertCount, indx, triCount, norm);

    int uvCount = in.GetInteger(CTM_UV_MAP_COUNT);
    for(int k = 0; k < uvCount; ++ k)
    {
      const CTMfloat * uvMap = in.GetFloatArray(CTMenum(CTM_UV_MAP_1 + k));
      const char * name = in.GetUVMapString(CTMenum(CTM_UV_MAP_1 + k), CTM_NAME);
      const char * fileName = in.GetUVMapString(CTMenum(CTM_UV_MAP_1 + k), CTM_FILE_NAME);
      out.AddUVMap(uvMap, name, fileName);
    }

    int attrCount = in.GetInteger(CTM_ATTRIB_MAP_COUNT);
    for(int k = 0; k < attrCount; ++ k)
    {
      const CTMfloat * attrMap = in.GetFloatArray(CTMenum(CTM_ATTRIB_MAP_1 + k));
      const char * name = in.GetAttribMapString(CTMenum(CTM_ATTRIB_MAP_1 + k), CTM_NAME);
      out.AddAttribMap(attrMap, name);
    }

    // Select compression parameters
    out.CompressionMethod(CTM_METHOD_MG1);

    // Start the timer
    timer.Push();

    // Save the file
    out.Save(aOutFile);

    // Stop the timer
    double t = timer.PopDelta();
    if(i == 0)
    {
      tMin = t;
      tMax = t;
    }
    else
    {
      if(t < tMin) tMin = t;
      if(t > tMax) tMax = t;
    }
    tTotal += t;
  }
}


//-----------------------------------------------------------------------------
// main() - Program entry.
//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
  // Usage?
  if((argc < 3) || (argc > 4))
  {
    cout << "Usage: ctmbench iterations infile [outfile]" << endl;
    return 0;
  }

  // Get the number of iterations
  int iterations;
  iterations = atoi(argv[1]);
  if(iterations < 1)
    iterations = 1;

  // Should we do load benchmarking or save benchmarking?
  bool benchSave = (argc == 4);

  try
  {
    double tMin = 0.0, tMax = 0.0, tTotal = 0.0;
    if(benchSave)
      BenchmarkSaves(iterations, argv[2], argv[3], tMin, tMax, tTotal);
    else
      BenchmarkLoads(iterations, argv[2], tMin, tMax, tTotal);

    // Print report
    cout << " Min: " << tMin * 1000.0 << " ms" << endl;
    cout << " Max: " << tMax * 1000.0 << " ms" << endl;
    cout << "Avg.: " << (tTotal / iterations) * 1000.0 << " ms" << endl;
  }
  catch(exception &e)
  {
    cout << "Error: " << e.what() << endl;
  }
}
