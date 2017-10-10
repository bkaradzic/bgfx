/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2017, assimp team


All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  ImageExtractor.cpp
 *  @brief Implementation of the 'assimp extract' utility
 */

#include "Main.h"
#include <../code/fast_atof.h>
#include <../code/StringComparison.h>

const char* AICMD_MSG_DUMP_HELP_E = 
"assimp extract <model> [<out>] [-t<n>] [-f<fmt>] [-ba] [-s] [common parameters]\n"
"\t -ba   Writes BMP's with alpha channel\n"
"\t -t<n> Zero-based index of the texture to be extracted \n"
"\t -f<f> Specify the file format if <out> is omitted  \n"
"\t[See the assimp_cmd docs for a full list of all common parameters]  \n"
"\t -cfast    Fast post processing preset, runs just a few important steps \n"
"\t -cdefault Default post processing: runs all recommended steps\n"
"\t -cfull    Fires almost all post processing steps \n"
;

#define AI_EXTRACT_WRITE_BMP_ALPHA 0x1
#include <assimp/Compiler/pushpack1.h>

// -----------------------------------------------------------------------------------
// Data structure for the first header of a BMP
struct BITMAPFILEHEADER 
{
    uint16_t  bfType ;
    uint32_t  bfSize;
    uint16_t  bfReserved1 ;
    uint16_t  bfReserved2; 
    uint32_t  bfOffBits; 
} PACK_STRUCT;

// -----------------------------------------------------------------------------------
// Data structure for the second header of a BMP
struct BITMAPINFOHEADER
{
    int32_t        biSize;
    int32_t        biWidth;
    int32_t        biHeight;
    int16_t        biPlanes;
    int16_t        biBitCount;
    uint32_t       biCompression;
    int32_t        biSizeImage;
    int32_t        biXPelsPerMeter;
    int32_t        biYPelsPerMeter;
    int32_t        biClrUsed;
    int32_t        biClrImportant;

    // pixel data follows header
} PACK_STRUCT;

// -----------------------------------------------------------------------------------
// Data structure for the header of a TGA
struct TGA_HEADER
{
    uint8_t  identsize;          // size of ID field that follows 18 byte header (0 usually)
    uint8_t  colourmaptype;      // type of colour map 0=none, 1=has palette
    uint8_t  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

    uint16_t colourmapstart;     // first colour map entry in palette
    uint16_t colourmaplength;    // number of colours in palette
    uint8_t  colourmapbits;      // number of bits per palette entry 15,16,24,32

    uint16_t xstart;             // image x origin
    uint16_t ystart;             // image y origin
    uint16_t width;              // image width in pixels
    uint16_t height;             // image height in pixels
    uint8_t  bits;               // image bits per pixel 8,16,24,32
    uint8_t  descriptor;         // image descriptor bits (vh flip bits)
    
    // pixel data follows header
} PACK_STRUCT;


#include <assimp/Compiler/poppack1.h>

// -----------------------------------------------------------------------------------
// Save a texture as bitmap
int SaveAsBMP (FILE* file, const aiTexel* data, unsigned int width, unsigned int height, bool SaveAlpha = false)
{
    if (!file || !data) {
        return 1;
    }

    const unsigned int numc = (SaveAlpha ? 4 : 3);
    unsigned char* buffer = new unsigned char[width*height*numc];

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {

            unsigned char* s = &buffer[(y*width+x) * numc];
            const aiTexel* t = &data  [ y*width+x];
            s[0] = t->b;
            s[1] = t->g;
            s[2] = t->r;
            if (4 == numc)
                s[3] = t->a;
        }
    }

    BITMAPFILEHEADER header;
    header.bfType      = 'B' | (int('M') << 8u);
    header.bfOffBits   = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    header.bfSize      = header.bfOffBits+width*height*numc;
    header.bfReserved1 = header.bfReserved2 = 0;

    fwrite(&header,sizeof(BITMAPFILEHEADER),1,file);

    BITMAPINFOHEADER info;
    info.biSize     = 40;
    info.biWidth    = width;
    info.biHeight   = height;
    info.biPlanes   = 1;
    info.biBitCount = numc<<3;
    info.biCompression = 0;
    info.biSizeImage   = width*height*numc;
    info.biXPelsPerMeter = 1; // dummy
    info.biYPelsPerMeter = 1; // dummy
    info.biClrUsed = 0;
    info.biClrImportant = 0;

    fwrite(&info,sizeof(BITMAPINFOHEADER),1,file);

    unsigned char* temp = buffer+info.biSizeImage;
    const unsigned int row = width*numc;

    for (int y = 0; temp -= row,y < info.biHeight;++y)	{
        fwrite(temp,row,1,file);
    }

    // delete the buffer
    delete[] buffer;
    return 0;
}

// -----------------------------------------------------------------------------------
// Save a texture as tga
int SaveAsTGA (FILE* file, const aiTexel* data, unsigned int width, unsigned int height)
{
    if (!file || !data) {
        return 1;
    }

    TGA_HEADER head;
    memset(&head, 0, sizeof(head));
    head.bits   = 32;
    head.height = (uint16_t)height;
    head.width  = (uint16_t)width;
    head.descriptor |= (1u<<5);

    head.imagetype = 2; // actually it's RGBA
    fwrite(&head,sizeof(TGA_HEADER),1,file);

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            fwrite(data + y*width+x,4,1,file);
        }
    }

    return 0;
}

// -----------------------------------------------------------------------------------
// Do the texture import for a given aiTexture
int DoExport(const aiTexture* tx, FILE* p, const std::string& extension,
    unsigned int flags) 
{
    // export the image to the appropriate decoder
    if (extension == "bmp") {
        SaveAsBMP(p,tx->pcData,tx->mWidth,tx->mHeight,
            (0 != (flags & AI_EXTRACT_WRITE_BMP_ALPHA)));
    }
    else if (extension == "tga") {
        SaveAsTGA(p,tx->pcData,tx->mWidth,tx->mHeight);
    }
    else {
        printf("assimp extract: No available texture encoder found for %s\n", extension.c_str());
        return 1;
    }
    return 0;
}

// -----------------------------------------------------------------------------------
// Implementation of the assimp extract utility
int Assimp_Extract (const char* const* params, unsigned int num)
{
    const char* const invalid = "assimp extract: Invalid number of arguments. See \'assimp extract --help\'\n"; 
    if (num < 1) {
        printf(invalid);
        return 1;
    }

    // --help
    if (!strcmp( params[0], "-h") || !strcmp( params[0], "--help") || !strcmp( params[0], "-?") ) {
        printf("%s",AICMD_MSG_DUMP_HELP_E);
        return 0;
    }

    // asssimp extract in out [options]
    if (num < 1) {
        printf(invalid);
        return 1;
    }

    std::string in  = std::string(params[0]);
    std::string out = (num > 1 ? std::string(params[1]) : "-");

    // get import flags
    ImportData import;
    ProcessStandardArguments(import,params+1,num-1);

    bool nosuffix = false;
    unsigned int texIdx  = 0xffffffff, flags = 0;

    // process other flags
    std::string extension = "bmp";
    for (unsigned int i = (out[0] == '-' ? 1 : 2); i < num;++i)		{
        if (!params[i]) {
            continue;
        }

        if (!strncmp( params[i], "-f",2)) {
            extension = std::string(params[i]+2);
        }
        else if ( !strncmp( params[i], "--format=",9)) {
            extension = std::string(params[i]+9);
        }
        else if ( !strcmp( params[i], "--nosuffix") || !strcmp(params[i],"-s")) {
            nosuffix = true;
        }
        else if ( !strncmp( params[i], "--texture=",10)) {
            texIdx = Assimp::strtoul10(params[i]+10);
        }
        else if ( !strncmp( params[i], "-t",2)) {
            texIdx = Assimp::strtoul10(params[i]+2);
        }
        else if ( !strcmp( params[i], "-ba") ||  !strcmp( params[i], "--bmp-with-alpha")) {
            flags |= AI_EXTRACT_WRITE_BMP_ALPHA;
        }
#if 0
        else {
            printf("Unknown parameter: %s\n",params[i]);
            return 10;
        }
#endif
    }

    std::transform(extension.begin(),extension.end(),extension.begin(),::tolower);
    
    if (out[0] == '-') {
        // take file name from input file
        std::string::size_type s = in.find_last_of('.');
        if (s == std::string::npos)
            s = in.length();

        out = in.substr(0,s);
    }

    // take file extension from file name, if given
    std::string::size_type s = out.find_last_of('.');
    if (s != std::string::npos) {
        extension = out.substr(s+1,in.length()-(s+1));
        out = out.substr(0,s);
    }

    // import the main model
    const aiScene* scene = ImportModel(import,in);
    if (!scene) {
        printf("assimp extract: Unable to load input file %s\n",in.c_str());
        return 5;
    }

    // get the texture(s) to be exported
    if (texIdx != 0xffffffff) {

        // check whether the requested texture is existing
        if (texIdx >= scene->mNumTextures) {
            ::printf("assimp extract: Texture %i requested, but there are just %i textures\n",
                texIdx, scene->mNumTextures);
            return 6;
        }
    }
    else {
        ::printf("assimp extract: Exporting %i textures\n",scene->mNumTextures);
    }

    // now write all output textures
    for (unsigned int i = 0; i < scene->mNumTextures;++i)	{
        if (texIdx != 0xffffffff && texIdx != i) {
            continue;
        }

        const aiTexture* tex = scene->mTextures[i];
        std::string out_cpy = out, out_ext = extension;

        // append suffix if necessary - always if all textures are exported
        if (!nosuffix || (texIdx == 0xffffffff)) {
            out_cpy.append  ("_img");
            char tmp[10];
            Assimp::ASSIMP_itoa10(tmp,i);

            out_cpy.append(std::string(tmp));
        }

        // if the texture is a compressed one, we'll export
        // it to its native file format
        if (!tex->mHeight) {
            printf("assimp extract: Texture %i is compressed (%s). Writing native file format.\n",
                i,tex->achFormatHint);

            // modify file extension
            out_ext = std::string(tex->achFormatHint);
        }
        out_cpy.append("."+out_ext);

        // open output file
        FILE* p = ::fopen(out_cpy.c_str(),"wb");
        if (!p)  {
            printf("assimp extract: Unable to open output file %s\n",out_cpy.c_str());
            return 7;
        }
        int m;

        if (!tex->mHeight) {
            m = (1 != fwrite(tex->pcData,tex->mWidth,1,p));
        }
        else m = DoExport(tex,p,extension,flags);
        ::fclose(p);

        printf("assimp extract: Wrote texture %i to %s\n",i, out_cpy.c_str());
        if (texIdx != 0xffffffff)
            return m;
    }
    return 0;
}
