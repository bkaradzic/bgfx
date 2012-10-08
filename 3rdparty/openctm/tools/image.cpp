//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        image.cpp
// Description: Implementation of the Image class.
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
#include <cstdio>
#include <jpeglib.h>
#include <pnglite.h>
#include "image.h"
#include "common.h"

using namespace std;


/// Flip the image vertically.
void Image::FlipVertically()
{
  if((mWidth <= 0) || (mHeight <= 0))
    return;

  for(int y = 0; y < mHeight / 2; ++ y)
  {
    for(int x = 0; x < mWidth; ++ x)
    {
      for(int k = 0; k < mComponents; ++ k)
      {
        unsigned char tmp = mData[(y * mWidth + x) * mComponents + k];
        mData[(y * mWidth + x) * mComponents + k] = mData[((mHeight - 1 - y) * mWidth + x) * mComponents + k];
        mData[((mHeight - 1 - y) * mWidth + x) * mComponents + k] = tmp;
      }
    }
  }
}

/// Load image from a JPEG file.
void Image::LoadJPEG(const char * aFileName)
{
  FILE * inFile = fopen(aFileName, "rb");
  if(inFile != NULL)
  {
    // Init libjpeg resources
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, inFile);

    // Read JPEG header
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    SetSize(cinfo.output_width, cinfo.output_height, cinfo.output_components);

    // Read pixel data
    for(int i = 0; i < mHeight; ++ i)
    {
      unsigned char * scanLines[1];
      scanLines[0] = &mData[(mHeight - 1 - i) * mWidth * mComponents];
      jpeg_read_scanlines(&cinfo, scanLines, 1);
    }

    // Finalize libjpeg resources
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    // Close input file
    fclose(inFile);
  }
}

/// Load image from a PNG file.
void Image::LoadPNG(const char * aFileName)
{
  bool success = false;
  png_t p;
  png_init(0, 0);
  if(png_open_file(&p, aFileName) == PNG_NO_ERROR)
  {
    if((p.depth == 8) && ((p.color_type == PNG_GREYSCALE) ||
       (p.color_type == PNG_TRUECOLOR) ||
       (p.color_type == PNG_TRUECOLOR_ALPHA)) && (p.width > 0) &&
       (p.height > 0) && (p.bpp >= 1) && (p.bpp <= 4))
    {
      SetSize(p.width, p.height, p.bpp);
      if(png_get_data(&p, &mData[0]) == PNG_NO_ERROR)
      {
        FlipVertically();
        success = true;
      }
    }
    png_close_file(&p);
  }

  // Did we have an error?
  if(!success)
  {
    Clear();
    throw runtime_error("Unable to load PNG file.");
  }
}

/// Load an image from a file (any supported format).
void Image::LoadFromFile(const char * aFileName)
{
  string fileExt = UpperCase(ExtractFileExt(string(aFileName)));
  if((fileExt == string(".JPG")) || (fileExt == string(".JPEG")))
    LoadJPEG(aFileName);
  else if(fileExt == string(".PNG"))
    LoadPNG(aFileName);
  else
    throw runtime_error("Unknown input file extension.");
}
