/*
Copyright (c) 2014 - 2015, Syoyo Fujita
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __TINYEXR_H__
#define __TINYEXR_H__

//
//
//   Do this:
//    #define TINYEXR_IMPLEMENTATION
//   before you include this file in *one* C or C++ file to create the
//   implementation.
//
//   // i.e. it should look like this:
//   #include ...
//   #include ...
//   #include ...
//   #define TINYEXR_IMPLEMENTATION
//   #include "tinyexr.h"
//
//

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif

// pixel type: possible values are: UINT = 0 HALF = 1 FLOAT = 2
#define TINYEXR_PIXELTYPE_UINT (0)
#define TINYEXR_PIXELTYPE_HALF (1)
#define TINYEXR_PIXELTYPE_FLOAT (2)

#define TINYEXR_MAX_ATTRIBUTES (128)

#define TINYEXR_COMPRESSIONTYPE_NONE (0)
//#define TINYEXR_COMPRESSIONTYPE_RLE  (1)  // not supported yet
#define TINYEXR_COMPRESSIONTYPE_ZIPS (2)
#define TINYEXR_COMPRESSIONTYPE_ZIP (3)
#define TINYEXR_COMPRESSIONTYPE_PIZ (4)

typedef struct _EXRAttribute {
  char *name;
  char *type;
  int size;
  unsigned char *value; // uint8_t*
} EXRAttribute;

typedef struct _EXRImage {
  // Custom attributes(exludes required attributes(e.g. `channels`,
  // `compression`, etc)
  EXRAttribute custom_attributes[TINYEXR_MAX_ATTRIBUTES];
  int num_custom_attributes;

  int num_channels;
  const char **channel_names;

  unsigned char **images; // image[channels][pixels]
  int *pixel_types; // Loaded pixel type(TINYEXR_PIXELTYPE_*) of `images` for
                    // each channel

  int *requested_pixel_types; // Filled initially by
                              // ParseEXRHeaderFrom(Meomory|File), then users
                              // can edit it(only valid for HALF pixel type
                              // channel)

  int width;
  int height;
  float pixel_aspect_ratio;
  int compression; // compression type(TINYEXR_COMPRESSIONTYPE_*)
  int line_order;
  int data_window[4];
  int display_window[4];
  float screen_window_center[2];
  float screen_window_width;
} EXRImage;

typedef struct _DeepImage {
  int num_channels;
  const char **channel_names;
  float ***image;     // image[channels][scanlines][samples]
  int **offset_table; // offset_table[scanline][offsets]
  int width;
  int height;
} DeepImage;

// @deprecated { to be removed. }
// Loads single-frame OpenEXR image. Assume EXR image contains RGB(A) channels.
// Application must free image data as returned by `out_rgba`
// Result image format is: float x RGBA x width x hight
// Return 0 if success
// Returns error string in `err` when there's an error
extern int LoadEXR(float **out_rgba, int *width, int *height,
                   const char *filename, const char **err);

// Parse single-frame OpenEXR header from a file and initialize `EXRImage`
// struct.
// Users then call LoadMultiChannelEXRFromFile to actually load image data into
// `EXRImage`
extern int ParseMultiChannelEXRHeaderFromFile(EXRImage *image,
                                              const char *filename,
                                              const char **err);

// Parse single-frame OpenEXR header from a memory and initialize `EXRImage`
// struct.
// Users then call LoadMultiChannelEXRFromMemory to actually load image data
// into `EXRImage`
extern int ParseMultiChannelEXRHeaderFromMemory(EXRImage *image,
                                                const unsigned char *memory,
                                                const char **err);

// Loads multi-channel, single-frame OpenEXR image from a file.
// Application must setup `ParseMultiChannelEXRHeaderFromFile` before calling
// `LoadMultiChannelEXRFromFile`.
// Application can free EXRImage using `FreeExrImage`
// Return 0 if success
// Returns error string in `err` when there's an error
extern int LoadMultiChannelEXRFromFile(EXRImage *image, const char *filename,
                                       const char **err);

// Loads multi-channel, single-frame OpenEXR image from a memory.
// Application must setup `EXRImage` with `ParseMultiChannelEXRHeaderFromMemory`
// before calling `LoadMultiChannelEXRFromMemory`.
// Application can free EXRImage using `FreeExrImage`
// Return 0 if success
// Returns error string in `err` when there's an error
extern int LoadMultiChannelEXRFromMemory(EXRImage *image,
                                         const unsigned char *memory,
                                         const char **err);

// Saves floating point RGBA image as OpenEXR.
// Image is compressed using EXRImage.compression value.
// Return 0 if success
// Returns error string in `err` when there's an error
// extern int SaveEXR(const float *in_rgba, int width, int height,
//                   const char *filename, const char **err);

// Saves multi-channel, single-frame OpenEXR image to a file.
// `compression_type` is one of TINYEXR_COMPRESSIONTYPE_*.
// Returns 0 if success
// Returns error string in `err` when there's an error
extern int SaveMultiChannelEXRToFile(const EXRImage *image,
                                     const char *filename, const char **err);

// Saves multi-channel, single-frame OpenEXR image to a memory.
// Image is compressed using EXRImage.compression value.
// Return the number of bytes if succes.
// Retruns 0 if success, negative number when failed.
// Returns error string in `err` when there's an error
extern size_t SaveMultiChannelEXRToMemory(const EXRImage *image,
                                          unsigned char **memory,
                                          const char **err);

// Loads single-frame OpenEXR deep image.
// Application must free memory of variables in DeepImage(image, offset_table)
// Returns 0 if success
// Returns error string in `err` when there's an error
extern int LoadDeepEXR(DeepImage *out_image, const char *filename,
                       const char **err);

// NOT YET IMPLEMENTED:
// Saves single-frame OpenEXR deep image.
// Return 0 if success
// Returns error string in `err` when there's an error
// extern int SaveDeepEXR(const DeepImage *in_image, const char *filename,
//                       const char **err);

// NOT YET IMPLEMENTED:
// Loads multi-part OpenEXR deep image.
// Application must free memory of variables in DeepImage(image, offset_table)
// extern int LoadMultiPartDeepEXR(DeepImage **out_image, int num_parts, const
// char *filename,
//                       const char **err);

// Initialize of EXRImage struct
extern void InitEXRImage(EXRImage *exrImage);

// Free's internal data of EXRImage struct
// Returns 0 if success.
extern int FreeEXRImage(EXRImage *exrImage);

// For emscripten.
// Parse single-frame OpenEXR header from memory.
// Return 0 if success
extern int ParseEXRHeaderFromMemory(EXRAttribute *customAttributes,
                                    int *numCustomAttributes, int *width,
                                    int *height, const unsigned char *memory);

// For emscripten.
// Loads single-frame OpenEXR image from memory. Assume EXR image contains
// RGB(A) channels.
// `out_rgba` must have enough memory(at least sizeof(float) x 4(RGBA) x width x
// hight)
// Return 0 if success
// Returns error string in `err` when there's an error
extern int LoadEXRFromMemory(float *out_rgba, const unsigned char *memory,
                             const char **err);

#ifdef __cplusplus
}
#endif

#ifdef TINYEXR_IMPLEMENTATION
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <algorithm>

#include <string>
#include <vector>

#include "tinyexr.h"

#ifdef _OPENMP
#include <omp.h>
#endif

namespace {

namespace miniz {

/* miniz.c v1.15 - public domain deflate/inflate, zlib-subset, ZIP
   reading/writing/appending, PNG writing
   See "unlicense" statement at the end of this file.
   Rich Geldreich <richgel99@gmail.com>, last updated Oct. 13, 2013
   Implements RFC 1950: http://www.ietf.org/rfc/rfc1950.txt and RFC 1951:
   http://www.ietf.org/rfc/rfc1951.txt

   Most API's defined in miniz.c are optional. For example, to disable the
   archive related functions just define
   MINIZ_NO_ARCHIVE_APIS, or to get rid of all stdio usage define MINIZ_NO_STDIO
   (see the list below for more macros).

   * Change History
     10/13/13 v1.15 r4 - Interim bugfix release while I work on the next major
   release with Zip64 support (almost there!):
       - Critical fix for the MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY bug
   (thanks kahmyong.moon@hp.com) which could cause locate files to not find
   files. This bug
        would only have occured in earlier versions if you explicitly used this
   flag, OR if you used mz_zip_extract_archive_file_to_heap() or
   mz_zip_add_mem_to_archive_file_in_place()
        (which used this flag). If you can't switch to v1.15 but want to fix
   this bug, just remove the uses of this flag from both helper funcs (and of
   course don't use the flag).
       - Bugfix in mz_zip_reader_extract_to_mem_no_alloc() from kymoon when
   pUser_read_buf is not NULL and compressed size is > uncompressed size
       - Fixing mz_zip_reader_extract_*() funcs so they don't try to extract
   compressed data from directory entries, to account for weird zipfiles which
   contain zero-size compressed data on dir entries.
         Hopefully this fix won't cause any issues on weird zip archives,
   because it assumes the low 16-bits of zip external attributes are DOS
   attributes (which I believe they always are in practice).
       - Fixing mz_zip_reader_is_file_a_directory() so it doesn't check the
   internal attributes, just the filename and external attributes
       - mz_zip_reader_init_file() - missing MZ_FCLOSE() call if the seek failed
       - Added cmake support for Linux builds which builds all the examples,
   tested with clang v3.3 and gcc v4.6.
       - Clang fix for tdefl_write_image_to_png_file_in_memory() from toffaletti
       - Merged MZ_FORCEINLINE fix from hdeanclark
       - Fix <time.h> include before config #ifdef, thanks emil.brink
       - Added tdefl_write_image_to_png_file_in_memory_ex(): supports Y flipping
   (super useful for OpenGL apps), and explicit control over the compression
   level (so you can
        set it to 1 for real-time compression).
       - Merged in some compiler fixes from paulharris's github repro.
       - Retested this build under Windows (VS 2010, including static analysis),
   tcc  0.9.26, gcc v4.6 and clang v3.3.
       - Added example6.c, which dumps an image of the mandelbrot set to a PNG
   file.
       - Modified example2 to help test the
   MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY flag more.
       - In r3: Bugfix to mz_zip_writer_add_file() found during merge: Fix
   possible src file fclose() leak if alignment bytes+local header file write
   faiiled
                 - In r4: Minor bugfix to mz_zip_writer_add_from_zip_reader():
   Was pushing the wrong central dir header offset, appears harmless in this
   release, but it became a problem in the zip64 branch
     5/20/12 v1.14 - MinGW32/64 GCC 4.6.1 compiler fixes: added MZ_FORCEINLINE,
   #include <time.h> (thanks fermtect).
     5/19/12 v1.13 - From jason@cornsyrup.org and kelwert@mtu.edu - Fix
   mz_crc32() so it doesn't compute the wrong CRC-32's when mz_ulong is 64-bit.
       - Temporarily/locally slammed in "typedef unsigned long mz_ulong" and
   re-ran a randomized regression test on ~500k files.
       - Eliminated a bunch of warnings when compiling with GCC 32-bit/64.
       - Ran all examples, miniz.c, and tinfl.c through MSVC 2008's /analyze
   (static analysis) option and fixed all warnings (except for the silly
        "Use of the comma-operator in a tested expression.." analysis warning,
   which I purposely use to work around a MSVC compiler warning).
       - Created 32-bit and 64-bit Codeblocks projects/workspace. Built and
   tested Linux executables. The codeblocks workspace is compatible with
   Linux+Win32/x64.
       - Added miniz_tester solution/project, which is a useful little app
   derived from LZHAM's tester app that I use as part of the regression test.
       - Ran miniz.c and tinfl.c through another series of regression testing on
   ~500,000 files and archives.
       - Modified example5.c so it purposely disables a bunch of high-level
   functionality (MINIZ_NO_STDIO, etc.). (Thanks to corysama for the
   MINIZ_NO_STDIO bug report.)
       - Fix ftell() usage in examples so they exit with an error on files which
   are too large (a limitation of the examples, not miniz itself).
     4/12/12 v1.12 - More comments, added low-level example5.c, fixed a couple
   minor level_and_flags issues in the archive API's.
      level_and_flags can now be set to MZ_DEFAULT_COMPRESSION. Thanks to Bruce
   Dawson <bruced@valvesoftware.com> for the feedback/bug report.
     5/28/11 v1.11 - Added statement from unlicense.org
     5/27/11 v1.10 - Substantial compressor optimizations:
      - Level 1 is now ~4x faster than before. The L1 compressor's throughput
   now varies between 70-110MB/sec. on a
      - Core i7 (actual throughput varies depending on the type of data, and x64
   vs. x86).
      - Improved baseline L2-L9 compression perf. Also, greatly improved
   compression perf. issues on some file types.
      - Refactored the compression code for better readability and
   maintainability.
      - Added level 10 compression level (L10 has slightly better ratio than
   level 9, but could have a potentially large
       drop in throughput on some files).
     5/15/11 v1.09 - Initial stable release.

   * Low-level Deflate/Inflate implementation notes:

     Compression: Use the "tdefl" API's. The compressor supports raw, static,
   and dynamic blocks, lazy or
     greedy parsing, match length filtering, RLE-only, and Huffman-only streams.
   It performs and compresses
     approximately as well as zlib.

     Decompression: Use the "tinfl" API's. The entire decompressor is
   implemented as a single function
     coroutine: see tinfl_decompress(). It supports decompression into a 32KB
   (or larger power of 2) wrapping buffer, or into a memory
     block large enough to hold the entire file.

     The low-level tdefl/tinfl API's do not make any use of dynamic memory
   allocation.

   * zlib-style API notes:

     miniz.c implements a fairly large subset of zlib. There's enough
   functionality present for it to be a drop-in
     zlib replacement in many apps:
        The z_stream struct, optional memory allocation callbacks
        deflateInit/deflateInit2/deflate/deflateReset/deflateEnd/deflateBound
        inflateInit/inflateInit2/inflate/inflateEnd
        compress, compress2, compressBound, uncompress
        CRC-32, Adler-32 - Using modern, minimal code size, CPU cache friendly
   routines.
        Supports raw deflate streams or standard zlib streams with adler-32
   checking.

     Limitations:
      The callback API's are not implemented yet. No support for gzip headers or
   zlib static dictionaries.
      I've tried to closely emulate zlib's various flavors of stream flushing
   and return status codes, but
      there are no guarantees that miniz.c pulls this off perfectly.

   * PNG writing: See the tdefl_write_image_to_png_file_in_memory() function,
   originally written by
     Alex Evans. Supports 1-4 bytes/pixel images.

   * ZIP archive API notes:

     The ZIP archive API's where designed with simplicity and efficiency in
   mind, with just enough abstraction to
     get the job done with minimal fuss. There are simple API's to retrieve file
   information, read files from
     existing archives, create new archives, append new files to existing
   archives, or clone archive data from
     one archive to another. It supports archives located in memory or the heap,
   on disk (using stdio.h),
     or you can specify custom file read/write callbacks.

     - Archive reading: Just call this function to read a single file from a
   disk archive:

      void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const
   char *pArchive_name,
        size_t *pSize, mz_uint zip_flags);

     For more complex cases, use the "mz_zip_reader" functions. Upon opening an
   archive, the entire central
     directory is located and read as-is into memory, and subsequent file access
   only occurs when reading individual files.

     - Archives file scanning: The simple way is to use this function to scan a
   loaded archive for a specific file:

     int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName,
   const char *pComment, mz_uint flags);

     The locate operation can optionally check file comments too, which (as one
   example) can be used to identify
     multiple versions of the same file in an archive. This function uses a
   simple linear search through the central
     directory, so it's not very fast.

     Alternately, you can iterate through all the files in an archive (using
   mz_zip_reader_get_num_files()) and
     retrieve detailed info on each file by calling mz_zip_reader_file_stat().

     - Archive creation: Use the "mz_zip_writer" functions. The ZIP writer
   immediately writes compressed file data
     to disk and builds an exact image of the central directory in memory. The
   central directory image is written
     all at once at the end of the archive file when the archive is finalized.

     The archive writer can optionally align each file's local header and file
   data to any power of 2 alignment,
     which can be useful when the archive will be read from optical media. Also,
   the writer supports placing
     arbitrary data blobs at the very beginning of ZIP archives. Archives
   written using either feature are still
     readable by any ZIP tool.

     - Archive appending: The simple way to add a single file to an archive is
   to call this function:

      mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename,
   const char *pArchive_name,
        const void *pBuf, size_t buf_size, const void *pComment, mz_uint16
   comment_size, mz_uint level_and_flags);

     The archive will be created if it doesn't already exist, otherwise it'll be
   appended to.
     Note the appending is done in-place and is not an atomic operation, so if
   something goes wrong
     during the operation it's possible the archive could be left without a
   central directory (although the local
     file headers and file data will be fine, so the archive will be
   recoverable).

     For more complex archive modification scenarios:
     1. The safest way is to use a mz_zip_reader to read the existing archive,
   cloning only those bits you want to
     preserve into a new archive using using the
   mz_zip_writer_add_from_zip_reader() function (which compiles the
     compressed file data as-is). When you're done, delete the old archive and
   rename the newly written archive, and
     you're done. This is safe but requires a bunch of temporary disk space or
   heap memory.

     2. Or, you can convert an mz_zip_reader in-place to an mz_zip_writer using
   mz_zip_writer_init_from_reader(),
     append new files as needed, then finalize the archive which will write an
   updated central directory to the
     original archive. (This is basically what
   mz_zip_add_mem_to_archive_file_in_place() does.) There's a
     possibility that the archive's central directory could be lost with this
   method if anything goes wrong, though.

     - ZIP archive support limitations:
     No zip64 or spanning support. Extraction functions can only handle
   unencrypted, stored or deflated files.
     Requires streams capable of seeking.

   * This is a header file library, like stb_image.c. To get only a header file,
   either cut and paste the
     below header, or create miniz.h, #define MINIZ_HEADER_FILE_ONLY, and then
   include miniz.c from it.

   * Important: For best perf. be sure to customize the below macros for your
   target platform:
     #define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
     #define MINIZ_LITTLE_ENDIAN 1
     #define MINIZ_HAS_64BIT_REGISTERS 1

   * On platforms using glibc, Be sure to "#define _LARGEFILE64_SOURCE 1" before
   including miniz.c to ensure miniz
     uses the 64-bit variants: fopen64(), stat64(), etc. Otherwise you won't be
   able to process large files
     (i.e. 32-bit stat() fails for me on files > 0x7FFFFFFF bytes).
*/

#ifndef MINIZ_HEADER_INCLUDED
#define MINIZ_HEADER_INCLUDED

#include <stdlib.h>

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be
// CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on
// stdio for file I/O.
//#define MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able
// to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be
// called.
// The current downside is the times written to your archives will be from 1979.
//#define MINIZ_NO_TIME

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
//#define MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive
// API's.
//#define MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression
// API's.
//#define MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent
// conflicts against stock zlib.
//#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom
// user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's
// which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and
// tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC

#if defined(__TINYC__) && (defined(__linux) || defined(__linux__))
// TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc
// on Linux
#define MINIZ_NO_TIME
#endif

#if !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
#include <time.h>
#endif

#if defined(_M_IX86) || defined(_M_X64) || defined(__i386__) ||                \
    defined(__i386) || defined(__i486__) || defined(__i486) ||                 \
    defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#define MINIZ_X86_OR_X64_CPU 1
#endif

#if defined(__sparcv9)
// Big endian
#else
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#define MINIZ_LITTLE_ENDIAN 1
#endif
#endif

#if MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient
// integer loads and stores from unaligned addresses.
//#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES                                   \
  0 // disable to suppress compiler warnings
#endif

#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) ||              \
    defined(_LP64) || defined(__LP64__) || defined(__ia64__) ||                \
    defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are
// reasonably fast (and don't involve compiler generated calls to helper
// functions).
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some
// parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
typedef unsigned long mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free()
// unless you've modified the MZ_MALLOC macro) to release a block allocated from
// the heap.
void mz_free(void *p);

#define MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with
// ptr==NULL.
mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with
// ptr==NULL.
mz_ulong mz_crc32(mz_ulong crc, const unsigned char *ptr, size_t buf_len);

// Compression strategies.
enum {
  MZ_DEFAULT_STRATEGY = 0,
  MZ_FILTERED = 1,
  MZ_HUFFMAN_ONLY = 2,
  MZ_RLE = 3,
  MZ_FIXED = 4
};

// Method
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's:
// items/size is size_t, not unsigned long.
typedef void *(*mz_alloc_func)(void *opaque, size_t items, size_t size);
typedef void (*mz_free_func)(void *opaque, void *address);
typedef void *(*mz_realloc_func)(void *opaque, void *address, size_t items,
                                 size_t size);

#define MZ_VERSION "9.1.15"
#define MZ_VERNUM 0x91F0
#define MZ_VER_MAJOR 9
#define MZ_VER_MINOR 1
#define MZ_VER_REVISION 15
#define MZ_VER_SUBREVISION 0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The
// other values are for advanced use (refer to the zlib docs).
enum {
  MZ_NO_FLUSH = 0,
  MZ_PARTIAL_FLUSH = 1,
  MZ_SYNC_FLUSH = 2,
  MZ_FULL_FLUSH = 3,
  MZ_FINISH = 4,
  MZ_BLOCK = 5
};

// Return status codes. MZ_PARAM_ERROR is non-standard.
enum {
  MZ_OK = 0,
  MZ_STREAM_END = 1,
  MZ_NEED_DICT = 2,
  MZ_ERRNO = -1,
  MZ_STREAM_ERROR = -2,
  MZ_DATA_ERROR = -3,
  MZ_MEM_ERROR = -4,
  MZ_BUF_ERROR = -5,
  MZ_VERSION_ERROR = -6,
  MZ_PARAM_ERROR = -10000
};

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best
// possible compression (not zlib compatible, and may be very slow),
// MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
enum {
  MZ_NO_COMPRESSION = 0,
  MZ_BEST_SPEED = 1,
  MZ_BEST_COMPRESSION = 9,
  MZ_UBER_COMPRESSION = 10,
  MZ_DEFAULT_LEVEL = 6,
  MZ_DEFAULT_COMPRESSION = -1
};

// Window bits
#define MZ_DEFAULT_WINDOW_BITS 15

struct mz_internal_state;

// Compression/decompression stream struct.
typedef struct mz_stream_s {
  const unsigned char *next_in; // pointer to next byte to read
  unsigned int avail_in;        // number of bytes available at next_in
  mz_ulong total_in;            // total number of bytes consumed so far

  unsigned char *next_out; // pointer to next byte to write
  unsigned int avail_out;  // number of bytes that can be written to next_out
  mz_ulong total_out;      // total number of bytes produced so far

  char *msg;                       // error msg (unused)
  struct mz_internal_state *state; // internal state, allocated by zalloc/zfree

  mz_alloc_func
      zalloc;         // optional heap allocation function (defaults to malloc)
  mz_free_func zfree; // optional heap free function (defaults to free)
  void *opaque;       // heap alloc function user pointer

  int data_type;     // data_type (unused)
  mz_ulong adler;    // adler32 of the source or uncompressed data
  mz_ulong reserved; // not used
} mz_stream;

typedef mz_stream *mz_streamp;

// Returns the version string of miniz.c.
const char *mz_version(void);

// mz_deflateInit() initializes a compressor with default options:
// Parameters:
//  pStream must point to an initialized mz_stream struct.
//  level must be between [MZ_NO_COMPRESSION, MZ_BEST_COMPRESSION].
//  level 1 enables a specially optimized compression function that's been
//  optimized purely for performance, not ratio.
//  (This special func. is currently only enabled when
//  MINIZ_USE_UNALIGNED_LOADS_AND_STORES and MINIZ_LITTLE_ENDIAN are defined.)
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
//  MZ_PARAM_ERROR if the input parameters are bogus.
//  MZ_MEM_ERROR on out of memory.
int mz_deflateInit(mz_streamp pStream, int level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with
//   zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no
//   header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits,
                    int mem_level, int strategy);

// Quickly resets a compressor without having to reallocate anything. Same as
// calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
int mz_deflateReset(mz_streamp pStream);

// mz_deflate() compresses the input to output, consuming as much of the input
// and producing as much output as possible.
// Parameters:
//   pStream is the stream to read from and write to. You must initialize/update
//   the next_in, avail_in, next_out, and avail_out members.
//   flush may be MZ_NO_FLUSH, MZ_PARTIAL_FLUSH/MZ_SYNC_FLUSH, MZ_FULL_FLUSH, or
//   MZ_FINISH.
// Return values:
//   MZ_OK on success (when flushing, or if more input is needed but not
//   available, and/or there's more output to be written but the output buffer
//   is full).
//   MZ_STREAM_END if all input has been consumed and all output bytes have been
//   written. Don't call mz_deflate() on the stream anymore.
//   MZ_STREAM_ERROR if the stream is bogus.
//   MZ_PARAM_ERROR if one of the parameters is invalid.
//   MZ_BUF_ERROR if no forward progress is possible because the input and/or
//   output buffers are empty. (Fill up the input buffer or free up some output
//   space and try again.)
int mz_deflate(mz_streamp pStream, int flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
int mz_deflateEnd(mz_streamp pStream);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of
// data that could be generated by deflate(), assuming flush is set to only
// MZ_NO_FLUSH or MZ_FINISH.
mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on
// failure.
int mz_compress(unsigned char *pDest, mz_ulong *pDest_len,
                const unsigned char *pSource, mz_ulong source_len);
int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len,
                 const unsigned char *pSource, mz_ulong source_len, int level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of
// data that could be generated by calling mz_compress().
mz_ulong mz_compressBound(mz_ulong source_len);

// Initializes a decompressor.
int mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that
// controls the window size and whether or not the stream has been wrapped with
// a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or
// -MZ_DEFAULT_WINDOW_BITS (raw deflate).
int mz_inflateInit2(mz_streamp pStream, int window_bits);

// Decompresses the input stream to the output, consuming only as much of the
// input as needed, and writing as much to the output as possible.
// Parameters:
//   pStream is the stream to read from and write to. You must initialize/update
//   the next_in, avail_in, next_out, and avail_out members.
//   flush may be MZ_NO_FLUSH, MZ_SYNC_FLUSH, or MZ_FINISH.
//   On the first call, if flush is MZ_FINISH it's assumed the input and output
//   buffers are both sized large enough to decompress the entire stream in a
//   single call (this is slightly faster).
//   MZ_FINISH implies that there are no more source bytes available beside
//   what's already in the input buffer, and that the output buffer is large
//   enough to hold the rest of the decompressed data.
// Return values:
//   MZ_OK on success. Either more input is needed but not available, and/or
//   there's more output to be written but the output buffer is full.
//   MZ_STREAM_END if all needed input has been consumed and all output bytes
//   have been written. For zlib streams, the adler-32 of the decompressed data
//   has also been verified.
//   MZ_STREAM_ERROR if the stream is bogus.
//   MZ_DATA_ERROR if the deflate stream is invalid.
//   MZ_PARAM_ERROR if one of the parameters is invalid.
//   MZ_BUF_ERROR if no forward progress is possible because the input buffer is
//   empty but the inflater needs more input to continue, or if the output
//   buffer is not large enough. Call mz_inflate() again
//   with more input data, or with more room in the output buffer (except when
//   using single call decompression, described above).
int mz_inflate(mz_streamp pStream, int flush);

// Deinitializes a decompressor.
int mz_inflateEnd(mz_streamp pStream);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on
// failure.
int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len,
                  const unsigned char *pSource, mz_ulong source_len);

// Returns a string description of the specified error code, or NULL if the
// error code is invalid.
const char *mz_error(int err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used
// as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you
// use zlib in the same project.
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef mz_ulong uLong;
typedef Byte Bytef;
typedef uInt uIntf;
typedef char charf;
typedef int intf;
typedef void *voidpf;
typedef uLong uLongf;
typedef void *voidp;
typedef void *const voidpc;
#define Z_NULL 0
#define Z_NO_FLUSH MZ_NO_FLUSH
#define Z_PARTIAL_FLUSH MZ_PARTIAL_FLUSH
#define Z_SYNC_FLUSH MZ_SYNC_FLUSH
#define Z_FULL_FLUSH MZ_FULL_FLUSH
#define Z_FINISH MZ_FINISH
#define Z_BLOCK MZ_BLOCK
#define Z_OK MZ_OK
#define Z_STREAM_END MZ_STREAM_END
#define Z_NEED_DICT MZ_NEED_DICT
#define Z_ERRNO MZ_ERRNO
#define Z_STREAM_ERROR MZ_STREAM_ERROR
#define Z_DATA_ERROR MZ_DATA_ERROR
#define Z_MEM_ERROR MZ_MEM_ERROR
#define Z_BUF_ERROR MZ_BUF_ERROR
#define Z_VERSION_ERROR MZ_VERSION_ERROR
#define Z_PARAM_ERROR MZ_PARAM_ERROR
#define Z_NO_COMPRESSION MZ_NO_COMPRESSION
#define Z_BEST_SPEED MZ_BEST_SPEED
#define Z_BEST_COMPRESSION MZ_BEST_COMPRESSION
#define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
#define Z_DEFAULT_STRATEGY MZ_DEFAULT_STRATEGY
#define Z_FILTERED MZ_FILTERED
#define Z_HUFFMAN_ONLY MZ_HUFFMAN_ONLY
#define Z_RLE MZ_RLE
#define Z_FIXED MZ_FIXED
#define Z_DEFLATED MZ_DEFLATED
#define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
#define alloc_func mz_alloc_func
#define free_func mz_free_func
#define internal_state mz_internal_state
#define z_stream mz_stream
#define deflateInit mz_deflateInit
#define deflateInit2 mz_deflateInit2
#define deflateReset mz_deflateReset
#define deflate mz_deflate
#define deflateEnd mz_deflateEnd
#define deflateBound mz_deflateBound
#define compress mz_compress
#define compress2 mz_compress2
#define compressBound mz_compressBound
#define inflateInit mz_inflateInit
#define inflateInit2 mz_inflateInit2
#define inflate mz_inflate
#define inflateEnd mz_inflateEnd
#define uncompress mz_uncompress
#define crc32 mz_crc32
#define adler32 mz_adler32
#define MAX_WBITS 15
#define MAX_MEM_LEVEL 9
#define zError mz_error
#define ZLIB_VERSION MZ_VERSION
#define ZLIB_VERNUM MZ_VERNUM
#define ZLIB_VER_MAJOR MZ_VER_MAJOR
#define ZLIB_VER_MINOR MZ_VER_MINOR
#define ZLIB_VER_REVISION MZ_VER_REVISION
#define ZLIB_VER_SUBREVISION MZ_VER_SUBREVISION
#define zlibVersion mz_version
#define zlib_version mz_version()
#endif // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#endif // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

typedef unsigned char mz_uint8;
typedef signed short mz_int16;
typedef unsigned short mz_uint16;
typedef unsigned int mz_uint32;
typedef unsigned int mz_uint;
typedef long long mz_int64;
typedef unsigned long long mz_uint64;
typedef int mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional
// expression is constant" message.
#ifdef _MSC_VER
#define MZ_MACRO_END while (0, 0)
#else
#define MZ_MACRO_END while (0)
#endif

// ------------------- ZIP archive reading/writing

#ifndef MINIZ_NO_ARCHIVE_APIS

enum {
  MZ_ZIP_MAX_IO_BUF_SIZE = 64 * 1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 256
};

typedef struct {
  mz_uint32 m_file_index;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;
#ifndef MINIZ_NO_TIME
  time_t m_time;
#endif
  mz_uint32 m_crc32;
  mz_uint64 m_comp_size;
  mz_uint64 m_uncomp_size;
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_header_ofs;
  mz_uint32 m_comment_size;
  char m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];
  char m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];
} mz_zip_archive_file_stat;

typedef size_t (*mz_file_read_func)(void *pOpaque, mz_uint64 file_ofs,
                                    void *pBuf, size_t n);
typedef size_t (*mz_file_write_func)(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n);

struct mz_zip_internal_state_tag;
typedef struct mz_zip_internal_state_tag mz_zip_internal_state;

typedef enum {
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

typedef struct mz_zip_archive_tag {
  mz_uint64 m_archive_size;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_total_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  void *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  void *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

typedef enum {
  MZ_ZIP_FLAG_CASE_SENSITIVE = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_DATA = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size,
                           mz_uint32 flags);
mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem,
                               size_t size, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint32 flags);
#endif

// Returns the total number of files in the archive.
mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index,
                                mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip,
                                          mz_uint file_index);
mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip,
                                        mz_uint file_index);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is
// 0 this function returns the number of bytes needed to fully store the
// filename.
mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index,
                                   char *pFilename, mz_uint filename_buf_size);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName,
                              const char *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip,
                                              mz_uint file_index, void *pBuf,
                                              size_t buf_size, mz_uint flags,
                                              void *pUser_read_buf,
                                              size_t user_read_buf_size);
mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(
    mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size);

// Extracts a archive file to a memory buffer.
mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index,
                                     void *pBuf, size_t buf_size,
                                     mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip,
                                          const char *pFilename, void *pBuf,
                                          size_t buf_size, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index,
                                    size_t *pSize, mz_uint flags);
void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip,
                                         const char *pFilename, size_t *pSize,
                                         mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip,
                                          mz_uint file_index,
                                          mz_file_write_func pCallback,
                                          void *pOpaque, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip,
                                               const char *pFilename,
                                               mz_file_write_func pCallback,
                                               void *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and
// modified times.
// This function only extracts files, not archive directory records.
mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index,
                                      const char *pDst_filename, mz_uint flags);
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip,
                                           const char *pArchive_filename,
                                           const char *pDst_filename,
                                           mz_uint flags);
#endif

// Ends archive reading, freeing all allocations, and closing the input archive
// file if mz_zip_reader_init_file() was used.
mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip,
                                size_t size_to_reserve_at_beginning,
                                size_t initial_allocation_size);

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint64 size_to_reserve_at_beginning);
#endif

// Converts a ZIP archive reader object into a writer object, to allow efficient
// in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the
// archive's filename so it can be reopened for writing. If the file can't be
// reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be
// growable using the realloc callback (which defaults to realloc unless you've
// overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's
// user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what
// you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip,
                                       const char *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record
// the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a
// forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
// MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or
// just set to MZ_DEFAULT_COMPRESSION.
mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name,
                              const void *pBuf, size_t buf_size,
                              mz_uint level_and_flags);
mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip,
                                 const char *pArchive_name, const void *pBuf,
                                 size_t buf_size, const void *pComment,
                                 mz_uint16 comment_size,
                                 mz_uint level_and_flags, mz_uint64 uncomp_size,
                                 mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records
// the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
// MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or
// just set to MZ_DEFAULT_COMPRESSION.
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name,
                               const char *pSrc_filename, const void *pComment,
                               mz_uint16 comment_size, mz_uint level_and_flags);
#endif

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no
// recompression), along with its full filename, extra data, and comment fields.
mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip,
                                          mz_zip_archive *pSource_zip,
                                          mz_uint file_index);

// Finalizes the archive by writing the central directory records followed by
// the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive
// struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be
// valid.
mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **pBuf,
                                            size_t *pSize);

// Ends archive writing, freeing all allocations, and closing the output file if
// mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically)
// appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED,
// MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or
// just set to MZ_DEFAULT_COMPRESSION.
mz_bool mz_zip_add_mem_to_archive_file_in_place(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename,
                                          const char *pArchive_name,
                                          size_t *pSize, mz_uint zip_flags);

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and
// ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the
// input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available
// beyond the end of the supplied input buffer. If clear, the input buffer
// contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large
// enough to hold the entire decompressed stream. If clear, the output buffer is
// at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the
// decompressed bytes.
enum {
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_INPUT = 2,
  TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
  TINFL_FLAG_COMPUTE_ADLER32 = 8
};

// High level decompression functions:
// tinfl_decompress_mem_to_heap() decompresses a block in memory to a heap block
// allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of the Deflate or zlib source data
//  to decompress.
// On return:
//  Function returns a pointer to the decompressed data, or NULL on failure.
//  *pOut_len will be set to the decompressed data's size, which could be larger
//  than src_buf_len on uncompressible data.
//  The caller must call mz_free() on the returned block when it's no longer
//  needed.
void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                   size_t *pOut_len, int flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block
// in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes
// written on success.
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                   const void *pSrc_buf, size_t src_buf_len,
                                   int flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an
// internal 32KB buffer, and a user provided callback function will be called to
// flush the buffer.
// Returns 1 on success or 0 on failure.
typedef int (*tinfl_put_buf_func_ptr)(const void *pBuf, int len, void *pUser);
int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size,
                                     tinfl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags);

struct tinfl_decompressor_tag;
typedef struct tinfl_decompressor_tag tinfl_decompressor;

// Max size of LZ dictionary.
#define TINFL_LZ_DICT_SIZE 32768

// Return status.
typedef enum {
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_INPUT = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// Initializes the decompressor to its initial state.
#define tinfl_init(r)                                                          \
  do {                                                                         \
    (r)->m_state = 0;                                                          \
  }                                                                            \
  MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function
// actually needed for decompression. All the other functions are just
// high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any
// desired higher level decompression API. In the limit case, it can be called
// once per every byte input or output.
tinfl_status tinfl_decompress(tinfl_decompressor *r,
                              const mz_uint8 *pIn_buf_next,
                              size_t *pIn_buf_size, mz_uint8 *pOut_buf_start,
                              mz_uint8 *pOut_buf_next, size_t *pOut_buf_size,
                              const mz_uint32 decomp_flags);

// Internal/private bits follow.
enum {
  TINFL_MAX_HUFF_TABLES = 3,
  TINFL_MAX_HUFF_SYMBOLS_0 = 288,
  TINFL_MAX_HUFF_SYMBOLS_1 = 32,
  TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10,
  TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

typedef struct {
  mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE],
      m_tree[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;


#ifndef MINIZ_HAS_64BIT_REGISTERS
#	define MINIZ_HAS_64BIT_REGISTERS 0
#endif

#ifndef TINFL_USE_64BIT_BITBUF
#	if MINIZ_HAS_64BIT_REGISTERS
#		define TINFL_USE_64BIT_BITBUF 1
#	else
#		define TINFL_USE_64BIT_BITBUF 0
#	endif
#endif

#if TINFL_USE_64BIT_BITBUF
typedef mz_uint64 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (64)
#else
typedef mz_uint32 tinfl_bit_buf_t;
#define TINFL_BITBUF_SIZE (32)
#endif

struct tinfl_decompressor_tag {
  mz_uint32 m_state, m_num_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type,
      m_check_adler32, m_dist, m_counter, m_num_extra,
      m_table_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_bit_buf_t m_bit_buf;
  size_t m_dist_from_out_buf_start;
  tinfl_huff_table m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_header[4],
      m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};

// ------------------- Low-level Compression API Definitions

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly
// slower, and raw/dynamic blocks will be output more frequently).
#define TDEFL_LESS_MEMORY 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain
// the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes
// per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap
// compression), 4095=Huffman+LZ (slowest/best compression).
enum {
  TDEFL_HUFFMAN_ONLY = 0,
  TDEFL_DEFAULT_MAX_PROBES = 128,
  TDEFL_MAX_PROBES_MASK = 0xFFF
};

// TDEFL_WRITE_ZLIB_HEADER: If set, the compressor outputs a zlib header before
// the deflate data, and the Adler-32 of the source data at the end. Otherwise,
// you'll get raw deflate data.
// TDEFL_COMPUTE_ADLER32: Always compute the adler-32 of the input data (even
// when not writing zlib headers).
// TDEFL_GREEDY_PARSING_FLAG: Set to use faster greedy parsing, instead of more
// efficient lazy parsing.
// TDEFL_NONDETERMINISTIC_PARSING_FLAG: Enable to decrease the compressor's
// initialization time to the minimum, but the output may vary from run to run
// given the same input (depending on the contents of memory).
// TDEFL_RLE_MATCHES: Only look for RLE matches (matches with a distance of 1)
// TDEFL_FILTER_MATCHES: Discards matches <= 5 chars if enabled.
// TDEFL_FORCE_ALL_STATIC_BLOCKS: Disable usage of optimized Huffman tables.
// TDEFL_FORCE_ALL_RAW_BLOCKS: Only use raw (uncompressed) deflate blocks.
// The low 12 bits are reserved to control the max # of hash probes per
// dictionary lookup (see TDEFL_MAX_PROBES_MASK).
enum {
  TDEFL_WRITE_ZLIB_HEADER = 0x01000,
  TDEFL_COMPUTE_ADLER32 = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES = 0x10000,
  TDEFL_FILTER_MATCHES = 0x20000,
  TDEFL_FORCE_ALL_STATIC_BLOCKS = 0x40000,
  TDEFL_FORCE_ALL_RAW_BLOCKS = 0x80000
};

// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block
// allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against
//  the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger
//  than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                 size_t *pOut_len, int flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in
// memory.
// Returns 0 on failure.
size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                 const void *pSrc_buf, size_t src_buf_len,
                                 int flags);

// Compresses an image to a compressed PNG file in memory.
// On entry:
//  pImage, w, h, and num_chans describe the image to compress. num_chans may be
//  1, 2, 3, or 4.
//  The image pitch in bytes per scanline will be w*num_chans. The leftmost
//  pixel on the top scanline is stored first in memory.
//  level may range from [0,10], use MZ_NO_COMPRESSION, MZ_BEST_SPEED,
//  MZ_BEST_COMPRESSION, etc. or a decent default is MZ_DEFAULT_LEVEL
//  If flip is true, the image will be flipped on the Y axis (useful for OpenGL
//  apps).
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pLen_out will be set to the size of the PNG image file.
//  The caller must mz_free() the returned heap block (which will typically be
//  larger than *pLen_out) when it's no longer needed.
void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w,
                                                 int h, int num_chans,
                                                 size_t *pLen_out,
                                                 mz_uint level, mz_bool flip);
void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h,
                                              int num_chans, size_t *pLen_out);

// Output stream interface. The compressor uses this interface to write
// compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
typedef mz_bool (*tdefl_put_buf_func_ptr)(const void *pBuf, int len,
                                          void *pUser);

// tdefl_compress_mem_to_output() compresses a block to an output stream. The
// above helpers use this function internally.
mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len,
                                     tdefl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags);

enum {
  TDEFL_MAX_HUFF_TABLES = 3,
  TDEFL_MAX_HUFF_SYMBOLS_0 = 288,
  TDEFL_MAX_HUFF_SYMBOLS_1 = 32,
  TDEFL_MAX_HUFF_SYMBOLS_2 = 19,
  TDEFL_LZ_DICT_SIZE = 32768,
  TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1,
  TDEFL_MIN_MATCH_LEN = 3,
  TDEFL_MAX_MATCH_LEN = 258
};

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed
// output block (using static/fixed Huffman codes).
#if TDEFL_LESS_MEMORY
enum {
  TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024,
  TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
  TDEFL_MAX_HUFF_SYMBOLS = 288,
  TDEFL_LZ_HASH_BITS = 12,
  TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
  TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
  TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#else
enum {
  TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024,
  TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13) / 10,
  TDEFL_MAX_HUFF_SYMBOLS = 288,
  TDEFL_LZ_HASH_BITS = 15,
  TDEFL_LEVEL1_HASH_SIZE_MASK = 4095,
  TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3,
  TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS
};
#endif

// The low-level tdefl functions below may be used directly if the above helper
// functions aren't flexible enough. The low-level functions don't make any heap
// allocations, unlike the above helper functions.
typedef enum {
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
typedef enum {
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
typedef struct {
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  void *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  int m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_num_flags_left, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in,
      m_bit_buffer;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit,
      m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index,
      m_wants_to_finish;
  tdefl_status m_prev_return_status;
  const void *m_pIn_buf;
  void *m_pOut_buf;
  size_t *m_pIn_buf_size, *m_pOut_buf_size;
  tdefl_flush m_flush;
  const mz_uint8 *m_pSrc;
  size_t m_src_buf_left, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_count[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE];
  mz_uint16 m_next[TDEFL_LZ_DICT_SIZE];
  mz_uint16 m_hash[TDEFL_LZ_HASH_SIZE];
  mz_uint8 m_output_buf[TDEFL_OUT_BUF_SIZE];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not
// dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified
// callback. In this case, the user should call the tdefl_compress_buffer() API
// for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress()
// API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER,
// etc.)
tdefl_status tdefl_init(tdefl_compressor *d,
                        tdefl_put_buf_func_ptr pPut_buf_func,
                        void *pPut_buf_user, int flags);

// Compresses a block of data, consuming as much of the specified input buffer
// as possible, and writing as much compressed data to the specified output
// buffer as possible.
tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf,
                            size_t *pIn_buf_size, void *pOut_buf,
                            size_t *pOut_buf_size, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a
// non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf,
                                   size_t in_buf_size, tdefl_flush flush);

tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
mz_uint32 tdefl_get_adler32(tdefl_compressor *d);

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't
// defined, because it uses some of its macros.
#ifndef MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be
// much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY,
// MZ_RLE, or MZ_FIXED
mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits,
                                                int strategy);
#endif // #ifndef MINIZ_NO_ZLIB_APIS

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want
// the header, define MINIZ_HEADER_FILE_ONLY.)

#ifndef MINIZ_HEADER_FILE_ONLY

typedef unsigned char mz_validate_uint16[sizeof(mz_uint16) == 2 ? 1 : -1];
typedef unsigned char mz_validate_uint32[sizeof(mz_uint32) == 4 ? 1 : -1];
typedef unsigned char mz_validate_uint64[sizeof(mz_uint64) == 8 ? 1 : -1];

#include <string.h>
#include <assert.h>

#define MZ_ASSERT(x) assert(x)

#ifdef MINIZ_NO_MALLOC
#define MZ_MALLOC(x) NULL
#define MZ_FREE(x) (void) x, ((void)0)
#define MZ_REALLOC(p, x) NULL
#else
#define MZ_MALLOC(x) malloc(x)
#define MZ_FREE(x) free(x)
#define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MZ_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, sizeof(obj))

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
#define MZ_READ_LE16(p) *((const mz_uint16 *)(p))
#define MZ_READ_LE32(p) *((const mz_uint32 *)(p))
#else
#define MZ_READ_LE16(p)                                                        \
  ((mz_uint32)(((const mz_uint8 *)(p))[0]) |                                   \
   ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U))
#define MZ_READ_LE32(p)                                                        \
  ((mz_uint32)(((const mz_uint8 *)(p))[0]) |                                   \
   ((mz_uint32)(((const mz_uint8 *)(p))[1]) << 8U) |                           \
   ((mz_uint32)(((const mz_uint8 *)(p))[2]) << 16U) |                          \
   ((mz_uint32)(((const mz_uint8 *)(p))[3]) << 24U))
#endif

#ifdef _MSC_VER
#define MZ_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define MZ_FORCEINLINE inline __attribute__((__always_inline__))
#else
#define MZ_FORCEINLINE inline
#endif

#ifdef __cplusplus
extern "C" {
#endif

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, const unsigned char *ptr, size_t buf_len) {
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16);
  size_t block_len = buf_len % 5552;
  if (!ptr)
    return MZ_ADLER32_INIT;
  while (buf_len) {
    for (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0], s2 += s1;
      s1 += ptr[1], s2 += s1;
      s1 += ptr[2], s2 += s1;
      s1 += ptr[3], s2 += s1;
      s1 += ptr[4], s2 += s1;
      s1 += ptr[5], s2 += s1;
      s1 += ptr[6], s2 += s1;
      s1 += ptr[7], s2 += s1;
    }
    for (; i < block_len; ++i)
      s1 += *ptr++, s2 += s1;
    s1 %= 65521U, s2 %= 65521U;
    buf_len -= block_len;
    block_len = 5552;
  }
  return (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C
// implementation that balances processor cache usage against speed":
// http://www.geocities.com/malbrain/
mz_ulong mz_crc32(mz_ulong crc, const mz_uint8 *ptr, size_t buf_len) {
  static const mz_uint32 s_crc32[16] = {
      0,          0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4,
      0x4db26158, 0x5005713c, 0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
      0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c};
  mz_uint32 crcu32 = (mz_uint32)crc;
  if (!ptr)
    return MZ_CRC32_INIT;
  crcu32 = ~crcu32;
  while (buf_len--) {
    mz_uint8 b = *ptr++;
    crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)];
    crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)];
  }
  return ~crcu32;
}

void mz_free(void *p) { MZ_FREE(p); }

#ifndef MINIZ_NO_ZLIB_APIS

static void *def_alloc_func(void *opaque, size_t items, size_t size) {
  (void)opaque, (void)items, (void)size;
  return MZ_MALLOC(items * size);
}
static void def_free_func(void *opaque, void *address) {
  (void)opaque, (void)address;
  MZ_FREE(address);
}
static void *def_realloc_func(void *opaque, void *address, size_t items,
                              size_t size) {
  (void)opaque, (void)address, (void)items, (void)size;
  return MZ_REALLOC(address, items * size);
}

const char *mz_version(void) { return MZ_VERSION; }

int mz_deflateInit(mz_streamp pStream, int level) {
  return mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9,
                         MZ_DEFAULT_STRATEGY);
}

int mz_deflateInit2(mz_streamp pStream, int level, int method, int window_bits,
                    int mem_level, int strategy) {
  tdefl_compressor *pComp;
  mz_uint comp_flags =
      TDEFL_COMPUTE_ADLER32 |
      tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  if (!pStream)
    return MZ_STREAM_ERROR;
  if ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) ||
      ((window_bits != MZ_DEFAULT_WINDOW_BITS) &&
       (-window_bits != MZ_DEFAULT_WINDOW_BITS)))
    return MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->msg = NULL;
  pStream->reserved = 0;
  pStream->total_in = 0;
  pStream->total_out = 0;
  if (!pStream->zalloc)
    pStream->zalloc = def_alloc_func;
  if (!pStream->zfree)
    pStream->zfree = def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1,
                                              sizeof(tdefl_compressor));
  if (!pComp)
    return MZ_MEM_ERROR;

  pStream->state = (struct mz_internal_state *)pComp;

  if (tdefl_init(pComp, NULL, NULL, comp_flags) != TDEFL_STATUS_OKAY) {
    mz_deflateEnd(pStream);
    return MZ_PARAM_ERROR;
  }

  return MZ_OK;
}

int mz_deflateReset(mz_streamp pStream) {
  if ((!pStream) || (!pStream->state) || (!pStream->zalloc) ||
      (!pStream->zfree))
    return MZ_STREAM_ERROR;
  pStream->total_in = pStream->total_out = 0;
  tdefl_init((tdefl_compressor *)pStream->state, NULL, NULL,
             ((tdefl_compressor *)pStream->state)->m_flags);
  return MZ_OK;
}

int mz_deflate(mz_streamp pStream, int flush) {
  size_t in_bytes, out_bytes;
  mz_ulong orig_total_in, orig_total_out;
  int mz_status = MZ_OK;

  if ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) ||
      (!pStream->next_out))
    return MZ_STREAM_ERROR;
  if (!pStream->avail_out)
    return MZ_BUF_ERROR;

  if (flush == MZ_PARTIAL_FLUSH)
    flush = MZ_SYNC_FLUSH;

  if (((tdefl_compressor *)pStream->state)->m_prev_return_status ==
      TDEFL_STATUS_DONE)
    return (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_total_in = pStream->total_in;
  orig_total_out = pStream->total_out;
  for (;;) {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in;
    out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor *)pStream->state,
                                 pStream->next_in, &in_bytes, pStream->next_out,
                                 &out_bytes, (tdefl_flush)flush);
    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tdefl_get_adler32((tdefl_compressor *)pStream->state);

    pStream->next_out += (mz_uint)out_bytes;
    pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    if (defl_status < 0) {
      mz_status = MZ_STREAM_ERROR;
      break;
    } else if (defl_status == TDEFL_STATUS_DONE) {
      mz_status = MZ_STREAM_END;
      break;
    } else if (!pStream->avail_out)
      break;
    else if ((!pStream->avail_in) && (flush != MZ_FINISH)) {
      if ((flush) || (pStream->total_in != orig_total_in) ||
          (pStream->total_out != orig_total_out))
        break;
      return MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  return mz_status;
}

int mz_deflateEnd(mz_streamp pStream) {
  if (!pStream)
    return MZ_STREAM_ERROR;
  if (pStream->state) {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = NULL;
  }
  return MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len) {
  (void)pStream;
  // This is really over conservative. (And lame, but it's actually pretty
  // tricky to compute a true upper bound given the way tdefl's blocking works.)
  return MZ_MAX(128 + (source_len * 110) / 100,
                128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len,
                 const unsigned char *pSource, mz_ulong source_len, int level) {
  int status;
  mz_stream stream;
  memset(&stream, 0, sizeof(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  if ((source_len | *pDest_len) > 0xFFFFFFFFU)
    return MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  if (status != MZ_OK)
    return status;

  status = mz_deflate(&stream, MZ_FINISH);
  if (status != MZ_STREAM_END) {
    mz_deflateEnd(&stream);
    return (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.total_out;
  return mz_deflateEnd(&stream);
}

int mz_compress(unsigned char *pDest, mz_ulong *pDest_len,
                const unsigned char *pSource, mz_ulong source_len) {
  return mz_compress2(pDest, pDest_len, pSource, source_len,
                      MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len) {
  return mz_deflateBound(NULL, source_len);
}

typedef struct {
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed;
  int m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_SIZE];
  tinfl_status m_last_status;
} inflate_state;

int mz_inflateInit2(mz_streamp pStream, int window_bits) {
  inflate_state *pDecomp;
  if (!pStream)
    return MZ_STREAM_ERROR;
  if ((window_bits != MZ_DEFAULT_WINDOW_BITS) &&
      (-window_bits != MZ_DEFAULT_WINDOW_BITS))
    return MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = 0;
  pStream->msg = NULL;
  pStream->total_in = 0;
  pStream->total_out = 0;
  pStream->reserved = 0;
  if (!pStream->zalloc)
    pStream->zalloc = def_alloc_func;
  if (!pStream->zfree)
    pStream->zfree = def_free_func;

  pDecomp = (inflate_state *)pStream->zalloc(pStream->opaque, 1,
                                             sizeof(inflate_state));
  if (!pDecomp)
    return MZ_MEM_ERROR;

  pStream->state = (struct mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_INPUT;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  return MZ_OK;
}

int mz_inflateInit(mz_streamp pStream) {
  return mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

int mz_inflate(mz_streamp pStream, int flush) {
  inflate_state *pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  if ((!pStream) || (!pStream->state))
    return MZ_STREAM_ERROR;
  if (flush == MZ_PARTIAL_FLUSH)
    flush = MZ_SYNC_FLUSH;
  if ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH))
    return MZ_STREAM_ERROR;

  pState = (inflate_state *)pStream->state;
  if (pState->m_window_bits > 0)
    decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call;
  pState->m_first_call = 0;
  if (pState->m_last_status < 0)
    return MZ_DATA_ERROR;

  if (pState->m_has_flushed && (flush != MZ_FINISH))
    return MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  if ((flush == MZ_FINISH) && (first_call)) {
    // MZ_FINISH on the first call implies that the input and output buffers are
    // large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in;
    out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes,
                              pStream->next_out, pStream->next_out, &out_bytes,
                              decomp_flags);
    pState->m_last_status = status;
    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->next_out += (mz_uint)out_bytes;
    pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    if (status < 0)
      return MZ_DATA_ERROR;
    else if (status != TINFL_STATUS_DONE) {
      pState->m_last_status = TINFL_STATUS_FAILED;
      return MZ_BUF_ERROR;
    }
    return MZ_STREAM_END;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  if (flush != MZ_FINISH)
    decomp_flags |= TINFL_FLAG_HAS_MORE_INPUT;

  if (pState->m_dict_avail) {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n;
    pStream->avail_out -= n;
    pStream->total_out += n;
    pState->m_dict_avail -= n;
    pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);
    return ((pState->m_last_status == TINFL_STATUS_DONE) &&
            (!pState->m_dict_avail))
               ? MZ_STREAM_END
               : MZ_OK;
  }

  for (;;) {
    in_bytes = pStream->avail_in;
    out_bytes = TINFL_LZ_DICT_SIZE - pState->m_dict_ofs;

    status = tinfl_decompress(
        &pState->m_decomp, pStream->next_in, &in_bytes, pState->m_dict,
        pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
    pState->m_last_status = status;

    pStream->next_in += (mz_uint)in_bytes;
    pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)out_bytes;

    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n;
    pStream->avail_out -= n;
    pStream->total_out += n;
    pState->m_dict_avail -= n;
    pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);

    if (status < 0)
      return MZ_DATA_ERROR; // Stream is corrupted (there could be some
                            // uncompressed data left in the output dictionary -
                            // oh well).
    else if ((status == TINFL_STATUS_NEEDS_MORE_INPUT) && (!orig_avail_in))
      return MZ_BUF_ERROR; // Signal caller that we can't make forward progress
                           // without supplying more input or by setting flush
                           // to MZ_FINISH.
    else if (flush == MZ_FINISH) {
      // The output buffer MUST be large to hold the remaining uncompressed data
      // when flush==MZ_FINISH.
      if (status == TINFL_STATUS_DONE)
        return pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
      // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's
      // at least 1 more byte on the way. If there's no more room left in the
      // output buffer then something is wrong.
      else if (!pStream->avail_out)
        return MZ_BUF_ERROR;
    } else if ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) ||
               (!pStream->avail_out) || (pState->m_dict_avail))
      break;
  }

  return ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail))
             ? MZ_STREAM_END
             : MZ_OK;
}

int mz_inflateEnd(mz_streamp pStream) {
  if (!pStream)
    return MZ_STREAM_ERROR;
  if (pStream->state) {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = NULL;
  }
  return MZ_OK;
}

int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len,
                  const unsigned char *pSource, mz_ulong source_len) {
  mz_stream stream;
  int status;
  memset(&stream, 0, sizeof(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  if ((source_len | *pDest_len) > 0xFFFFFFFFU)
    return MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  if (status != MZ_OK)
    return status;

  status = mz_inflate(&stream, MZ_FINISH);
  if (status != MZ_STREAM_END) {
    mz_inflateEnd(&stream);
    return ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_DATA_ERROR
                                                            : status;
  }
  *pDest_len = stream.total_out;

  return mz_inflateEnd(&stream);
}

const char *mz_error(int err) {
  static struct {
    int m_err;
    const char *m_pDesc;
  } s_error_descs[] = {{MZ_OK, ""},
                       {MZ_STREAM_END, "stream end"},
                       {MZ_NEED_DICT, "need dictionary"},
                       {MZ_ERRNO, "file error"},
                       {MZ_STREAM_ERROR, "stream error"},
                       {MZ_DATA_ERROR, "data error"},
                       {MZ_MEM_ERROR, "out of memory"},
                       {MZ_BUF_ERROR, "buf error"},
                       {MZ_VERSION_ERROR, "version error"},
                       {MZ_PARAM_ERROR, "parameter error"}};
  mz_uint i;
  for (i = 0; i < sizeof(s_error_descs) / sizeof(s_error_descs[0]); ++i)
    if (s_error_descs[i].m_err == err)
      return s_error_descs[i].m_pDesc;
  return NULL;
}

#endif // MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all
// compression API's)

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN                                                         \
  switch (r->m_state) {                                                        \
  case 0:
#define TINFL_CR_RETURN(state_index, result)                                   \
  do {                                                                         \
    status = result;                                                           \
    r->m_state = state_index;                                                  \
    goto common_exit;                                                          \
  case state_index:                                                            \
    ;                                                                          \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_index, result)                           \
  do {                                                                         \
    for (;;) {                                                                 \
      TINFL_CR_RETURN(state_index, result);                                    \
    }                                                                          \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt
// to read beyond the input buf, then something is wrong with the input because
// the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of
// the stream with 0's in this scenario.
#define TINFL_GET_BYTE(state_index, c)                                         \
  do {                                                                         \
    if (pIn_buf_cur >= pIn_buf_end) {                                          \
      for (;;) {                                                               \
        if (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT) {                        \
          TINFL_CR_RETURN(state_index, TINFL_STATUS_NEEDS_MORE_INPUT);         \
          if (pIn_buf_cur < pIn_buf_end) {                                     \
            c = *pIn_buf_cur++;                                                \
            break;                                                             \
          }                                                                    \
        } else {                                                               \
          c = 0;                                                               \
          break;                                                               \
        }                                                                      \
      }                                                                        \
    } else                                                                     \
      c = *pIn_buf_cur++;                                                      \
  }                                                                            \
  MZ_MACRO_END

#define TINFL_NEED_BITS(state_index, n)                                        \
  do {                                                                         \
    mz_uint c;                                                                 \
    TINFL_GET_BYTE(state_index, c);                                            \
    bit_buf |= (((tinfl_bit_buf_t)c) << num_bits);                             \
    num_bits += 8;                                                             \
  } while (num_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_index, n)                                        \
  do {                                                                         \
    if (num_bits < (mz_uint)(n)) {                                             \
      TINFL_NEED_BITS(state_index, n);                                         \
    }                                                                          \
    bit_buf >>= (n);                                                           \
    num_bits -= (n);                                                           \
  }                                                                            \
  MZ_MACRO_END
#define TINFL_GET_BITS(state_index, b, n)                                      \
  do {                                                                         \
    if (num_bits < (mz_uint)(n)) {                                             \
      TINFL_NEED_BITS(state_index, n);                                         \
    }                                                                          \
    b = bit_buf & ((1 << (n)) - 1);                                            \
    bit_buf >>= (n);                                                           \
    num_bits -= (n);                                                           \
  }                                                                            \
  MZ_MACRO_END

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes
// remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode
// the next Huffman code (and absolutely no more). It works by trying to fully
// decode a
// Huffman code by using whatever bits are currently present in the bit buffer.
// If this fails, it reads another byte, and tries again until it succeeds or
// until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#define TINFL_HUFF_BITBUF_FILL(state_index, pHuff)                             \
  do {                                                                         \
    temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)];         \
    if (temp >= 0) {                                                           \
      code_len = temp >> 9;                                                    \
      if ((code_len) && (num_bits >= code_len))                                \
        break;                                                                 \
    } else if (num_bits > TINFL_FAST_LOOKUP_BITS) {                            \
      code_len = TINFL_FAST_LOOKUP_BITS;                                       \
      do {                                                                     \
        temp = (pHuff)->m_tree[~temp + ((bit_buf >> code_len++) & 1)];         \
      } while ((temp < 0) && (num_bits >= (code_len + 1)));                    \
      if (temp >= 0)                                                           \
        break;                                                                 \
    }                                                                          \
    TINFL_GET_BYTE(state_index, c);                                            \
    bit_buf |= (((tinfl_bit_buf_t)c) << num_bits);                             \
    num_bits += 8;                                                             \
  } while (num_bits < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex
// than you would initially expect because the zlib API expects the decompressor
// to never read
// beyond the final byte of the deflate stream. (In other words, when this macro
// wants to read another byte from the input, it REALLY needs another byte in
// order to fully
// decode the next Huffman code.) Handling this properly is particularly
// important on raw deflate (non-zlib) streams, which aren't followed by a byte
// aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#define TINFL_HUFF_DECODE(state_index, sym, pHuff)                             \
  do {                                                                         \
    int temp;                                                                  \
    mz_uint code_len, c;                                                       \
    if (num_bits < 15) {                                                       \
      if ((pIn_buf_end - pIn_buf_cur) < 2) {                                   \
        TINFL_HUFF_BITBUF_FILL(state_index, pHuff);                            \
      } else {                                                                 \
        bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << num_bits) |           \
                   (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (num_bits + 8));      \
        pIn_buf_cur += 2;                                                      \
        num_bits += 16;                                                        \
      }                                                                        \
    }                                                                          \
    if ((temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= \
        0)                                                                     \
      code_len = temp >> 9, temp &= 511;                                       \
    else {                                                                     \
      code_len = TINFL_FAST_LOOKUP_BITS;                                       \
      do {                                                                     \
        temp = (pHuff)->m_tree[~temp + ((bit_buf >> code_len++) & 1)];         \
      } while (temp < 0);                                                      \
    }                                                                          \
    sym = temp;                                                                \
    bit_buf >>= code_len;                                                      \
    num_bits -= code_len;                                                      \
  }                                                                            \
  MZ_MACRO_END

tinfl_status tinfl_decompress(tinfl_decompressor *r,
                              const mz_uint8 *pIn_buf_next,
                              size_t *pIn_buf_size, mz_uint8 *pOut_buf_start,
                              mz_uint8 *pOut_buf_next, size_t *pOut_buf_size,
                              const mz_uint32 decomp_flags) {
  static const int s_length_base[31] = {
      3,  4,  5,  6,  7,  8,  9,  10,  11,  13,  15,  17,  19,  23, 27, 31,
      35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0,  0};
  static const int s_length_extra[31] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                         1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
                                         4, 4, 5, 5, 5, 5, 0, 0, 0};
  static const int s_dist_base[32] = {
      1,    2,    3,    4,    5,    7,     9,     13,    17,  25,   33,
      49,   65,   97,   129,  193,  257,   385,   513,   769, 1025, 1537,
      2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0,   0};
  static const int s_dist_extra[32] = {0, 0, 0,  0,  1,  1,  2,  2,  3,  3,
                                       4, 4, 5,  5,  6,  6,  7,  7,  8,  8,
                                       9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  static const mz_uint8 s_length_dezigzag[19] = {
      16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  static const int s_min_table_sizes[3] = {257, 1, 4};

  tinfl_status status = TINFL_STATUS_FAILED;
  mz_uint32 num_bits, dist, counter, num_extra;
  tinfl_bit_buf_t bit_buf;
  const mz_uint8 *pIn_buf_cur = pIn_buf_next,
                 *const pIn_buf_end = pIn_buf_next + *pIn_buf_size;
  mz_uint8 *pOut_buf_cur = pOut_buf_next,
           *const pOut_buf_end = pOut_buf_next + *pOut_buf_size;
  size_t out_buf_size_mask =
             (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)
                 ? (size_t)-1
                 : ((pOut_buf_next - pOut_buf_start) + *pOut_buf_size) - 1,
         dist_from_out_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer
  // is large enough to hold the entire output file (in which case it doesn't
  // matter).
  if (((out_buf_size_mask + 1) & out_buf_size_mask) ||
      (pOut_buf_next < pOut_buf_start)) {
    *pIn_buf_size = *pOut_buf_size = 0;
    return TINFL_STATUS_BAD_PARAM;
  }

  num_bits = r->m_num_bits;
  bit_buf = r->m_bit_buf;
  dist = r->m_dist;
  counter = r->m_counter;
  num_extra = r->m_num_extra;
  dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = num_bits = dist = counter = num_extra = r->m_zhdr0 = r->m_zhdr1 = 0;
  r->m_z_adler32 = r->m_check_adler32 = 1;
  if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) {
    TINFL_GET_BYTE(1, r->m_zhdr0);
    TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) ||
               (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    if (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
      counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) ||
                  ((out_buf_size_mask + 1) <
                   (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    if (counter) {
      TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED);
    }
  }

  do {
    TINFL_GET_BITS(3, r->m_final, 3);
    r->m_type = r->m_final >> 1;
    if (r->m_type == 0) {
      TINFL_SKIP_BITS(5, num_bits & 7);
      for (counter = 0; counter < 4; ++counter) {
        if (num_bits)
          TINFL_GET_BITS(6, r->m_raw_header[counter], 8);
        else
          TINFL_GET_BYTE(7, r->m_raw_header[counter]);
      }
      if ((counter = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) !=
          (mz_uint)(0xFFFF ^
                    (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) {
        TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED);
      }
      while ((counter) && (num_bits)) {
        TINFL_GET_BITS(51, dist, 8);
        while (pOut_buf_cur >= pOut_buf_end) {
          TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT);
        }
        *pOut_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      while (counter) {
        size_t n;
        while (pOut_buf_cur >= pOut_buf_end) {
          TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT);
        }
        while (pIn_buf_cur >= pIn_buf_end) {
          if (decomp_flags & TINFL_FLAG_HAS_MORE_INPUT) {
            TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_INPUT);
          } else {
            TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur),
                          (size_t)(pIn_buf_end - pIn_buf_cur)),
                   counter);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n);
        pIn_buf_cur += n;
        pOut_buf_cur += n;
        counter -= (mz_uint)n;
      }
    } else if (r->m_type == 3) {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    } else {
      if (r->m_type == 1) {
        mz_uint8 *p = r->m_tables[0].m_code_size;
        mz_uint i;
        r->m_table_sizes[0] = 288;
        r->m_table_sizes[1] = 32;
        TINFL_MEMSET(r->m_tables[1].m_code_size, 5, 32);
        for (i = 0; i <= 143; ++i)
          *p++ = 8;
        for (; i <= 255; ++i)
          *p++ = 9;
        for (; i <= 279; ++i)
          *p++ = 7;
        for (; i <= 287; ++i)
          *p++ = 8;
      } else {
        for (counter = 0; counter < 3; counter++) {
          TINFL_GET_BITS(11, r->m_table_sizes[counter], "\05\05\04"[counter]);
          r->m_table_sizes[counter] += s_min_table_sizes[counter];
        }
        MZ_CLEAR_OBJ(r->m_tables[2].m_code_size);
        for (counter = 0; counter < r->m_table_sizes[2]; counter++) {
          mz_uint s;
          TINFL_GET_BITS(14, s, 3);
          r->m_tables[2].m_code_size[s_length_dezigzag[counter]] = (mz_uint8)s;
        }
        r->m_table_sizes[2] = 19;
      }
      for (; (int)r->m_type >= 0; r->m_type--) {
        int tree_next, tree_cur;
        tinfl_huff_table *pTable;
        mz_uint i, j, used_syms, total, sym_index, next_code[17],
            total_syms[16];
        pTable = &r->m_tables[r->m_type];
        MZ_CLEAR_OBJ(total_syms);
        MZ_CLEAR_OBJ(pTable->m_look_up);
        MZ_CLEAR_OBJ(pTable->m_tree);
        for (i = 0; i < r->m_table_sizes[r->m_type]; ++i)
          total_syms[pTable->m_code_size[i]]++;
        used_syms = 0, total = 0;
        next_code[0] = next_code[1] = 0;
        for (i = 1; i <= 15; ++i) {
          used_syms += total_syms[i];
          next_code[i + 1] = (total = ((total + total_syms[i]) << 1));
        }
        if ((65536 != total) && (used_syms > 1)) {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        for (tree_next = -1, sym_index = 0;
             sym_index < r->m_table_sizes[r->m_type]; ++sym_index) {
          mz_uint rev_code = 0, l, cur_code,
                  code_size = pTable->m_code_size[sym_index];
          if (!code_size)
            continue;
          cur_code = next_code[code_size]++;
          for (l = code_size; l > 0; l--, cur_code >>= 1)
            rev_code = (rev_code << 1) | (cur_code & 1);
          if (code_size <= TINFL_FAST_LOOKUP_BITS) {
            mz_int16 k = (mz_int16)((code_size << 9) | sym_index);
            while (rev_code < TINFL_FAST_LOOKUP_SIZE) {
              pTable->m_look_up[rev_code] = k;
              rev_code += (1 << code_size);
            }
            continue;
          }
          if (0 ==
              (tree_cur = pTable->m_look_up[rev_code &
                                            (TINFL_FAST_LOOKUP_SIZE - 1)])) {
            pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)] =
                (mz_int16)tree_next;
            tree_cur = tree_next;
            tree_next -= 2;
          }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          for (j = code_size; j > (TINFL_FAST_LOOKUP_BITS + 1); j--) {
            tree_cur -= ((rev_code >>= 1) & 1);
            if (!pTable->m_tree[-tree_cur - 1]) {
              pTable->m_tree[-tree_cur - 1] = (mz_int16)tree_next;
              tree_cur = tree_next;
              tree_next -= 2;
            } else
              tree_cur = pTable->m_tree[-tree_cur - 1];
          }
          tree_cur -= ((rev_code >>= 1) & 1);
          pTable->m_tree[-tree_cur - 1] = (mz_int16)sym_index;
        }
        if (r->m_type == 2) {
          for (counter = 0;
               counter < (r->m_table_sizes[0] + r->m_table_sizes[1]);) {
            mz_uint s;
            TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]);
            if (dist < 16) {
              r->m_len_codes[counter++] = (mz_uint8)dist;
              continue;
            }
            if ((dist == 16) && (!counter)) {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            num_extra = "\02\03\07"[dist - 16];
            TINFL_GET_BITS(18, s, num_extra);
            s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter,
                         (dist == 16) ? r->m_len_codes[counter - 1] : 0, s);
            counter += s;
          }
          if ((r->m_table_sizes[0] + r->m_table_sizes[1]) != counter) {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_code_size, r->m_len_codes,
                       r->m_table_sizes[0]);
          TINFL_MEMCPY(r->m_tables[1].m_code_size,
                       r->m_len_codes + r->m_table_sizes[0],
                       r->m_table_sizes[1]);
        }
      }
      for (;;) {
        mz_uint8 *pSrc;
        for (;;) {
          if (((pIn_buf_end - pIn_buf_cur) < 4) ||
              ((pOut_buf_end - pOut_buf_cur) < 2)) {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            if (counter >= 256)
              break;
            while (pOut_buf_cur >= pOut_buf_end) {
              TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT);
            }
            *pOut_buf_cur++ = (mz_uint8)counter;
          } else {
            int sym2;
            mz_uint code_len;
#if TINFL_USE_64BIT_BITBUF
            if (num_bits < 30) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 4;
              num_bits += 32;
            }
#else
            if (num_bits < 15) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 2;
              num_bits += 16;
            }
#endif
            if ((sym2 =
                     r->m_tables[0]
                         .m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >=
                0)
              code_len = sym2 >> 9;
            else {
              code_len = TINFL_FAST_LOOKUP_BITS;
              do {
                sym2 = r->m_tables[0]
                           .m_tree[~sym2 + ((bit_buf >> code_len++) & 1)];
              } while (sym2 < 0);
            }
            counter = sym2;
            bit_buf >>= code_len;
            num_bits -= code_len;
            if (counter & 256)
              break;

#if !TINFL_USE_64BIT_BITBUF
            if (num_bits < 15) {
              bit_buf |=
                  (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << num_bits);
              pIn_buf_cur += 2;
              num_bits += 16;
            }
#endif
            if ((sym2 =
                     r->m_tables[0]
                         .m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >=
                0)
              code_len = sym2 >> 9;
            else {
              code_len = TINFL_FAST_LOOKUP_BITS;
              do {
                sym2 = r->m_tables[0]
                           .m_tree[~sym2 + ((bit_buf >> code_len++) & 1)];
              } while (sym2 < 0);
            }
            bit_buf >>= code_len;
            num_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)counter;
            if (sym2 & 256) {
              pOut_buf_cur++;
              counter = sym2;
              break;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        if ((counter &= 511) == 256)
          break;

        num_extra = s_length_extra[counter - 257];
        counter = s_length_base[counter - 257];
        if (num_extra) {
          mz_uint extra_bits;
          TINFL_GET_BITS(25, extra_bits, num_extra);
          counter += extra_bits;
        }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        num_extra = s_dist_extra[dist];
        dist = s_dist_base[dist];
        if (num_extra) {
          mz_uint extra_bits;
          TINFL_GET_BITS(27, extra_bits, num_extra);
          dist += extra_bits;
        }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        if ((dist > dist_from_out_buf_start) &&
            (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start +
               ((dist_from_out_buf_start - dist) & out_buf_size_mask);

        if ((MZ_MAX(pOut_buf_cur, pSrc) + counter) > pOut_buf_end) {
          while (counter--) {
            while (pOut_buf_cur >= pOut_buf_end) {
              TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT);
            }
            *pOut_buf_cur++ =
                pOut_buf_start[(dist_from_out_buf_start++ - dist) &
                               out_buf_size_mask];
          }
          continue;
        }
#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        else if ((counter >= 9) && (counter <= dist)) {
          const mz_uint8 *pSrc_end = pSrc + (counter & ~7);
          do {
            ((mz_uint32 *)pOut_buf_cur)[0] = ((const mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((const mz_uint32 *)pSrc)[1];
            pOut_buf_cur += 8;
          } while ((pSrc += 8) < pSrc_end);
          if ((counter &= 7) < 3) {
            if (counter) {
              pOut_buf_cur[0] = pSrc[0];
              if (counter > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += counter;
            }
            continue;
          }
        }
#endif
        do {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3;
          pSrc += 3;
        } while ((int)(counter -= 3) > 2);
        if ((int)counter > 0) {
          pOut_buf_cur[0] = pSrc[0];
          if ((int)counter > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += counter;
        }
      }
    }
  } while (!(r->m_final & 1));
  if (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) {
    TINFL_SKIP_BITS(32, num_bits & 7);
    for (counter = 0; counter < 4; ++counter) {
      mz_uint s;
      if (num_bits)
        TINFL_GET_BITS(41, s, 8);
      else
        TINFL_GET_BYTE(42, s);
      r->m_z_adler32 = (r->m_z_adler32 << 8) | s;
    }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
  TINFL_CR_FINISH

common_exit:
  r->m_num_bits = num_bits;
  r->m_bit_buf = bit_buf;
  r->m_dist = dist;
  r->m_counter = counter;
  r->m_num_extra = num_extra;
  r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *pIn_buf_size = pIn_buf_cur - pIn_buf_next;
  *pOut_buf_size = pOut_buf_cur - pOut_buf_next;
  if ((decomp_flags &
       (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) &&
      (status >= 0)) {
    const mz_uint8 *ptr = pOut_buf_next;
    size_t buf_len = *pOut_buf_size;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff,
                 s2 = r->m_check_adler32 >> 16;
    size_t block_len = buf_len % 5552;
    while (buf_len) {
      for (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
        s1 += ptr[0], s2 += s1;
        s1 += ptr[1], s2 += s1;
        s1 += ptr[2], s2 += s1;
        s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1;
        s1 += ptr[5], s2 += s1;
        s1 += ptr[6], s2 += s1;
        s1 += ptr[7], s2 += s1;
      }
      for (; i < block_len; ++i)
        s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U;
      buf_len -= block_len;
      block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1;
    if ((status == TINFL_STATUS_DONE) &&
        (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) &&
        (r->m_check_adler32 != r->m_z_adler32))
      status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  return status;
}

// Higher level helper functions.
void *tinfl_decompress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                   size_t *pOut_len, int flags) {
  tinfl_decompressor decomp;
  void *pBuf = NULL, *pNew_buf;
  size_t src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  for (;;) {
    size_t src_buf_size = src_buf_len - src_buf_ofs,
           dst_buf_size = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(
        &decomp, (const mz_uint8 *)pSrc_buf + src_buf_ofs, &src_buf_size,
        (mz_uint8 *)pBuf, pBuf ? (mz_uint8 *)pBuf + *pOut_len : NULL,
        &dst_buf_size, (flags & ~TINFL_FLAG_HAS_MORE_INPUT) |
                           TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    if ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_INPUT)) {
      MZ_FREE(pBuf);
      *pOut_len = 0;
      return NULL;
    }
    src_buf_ofs += src_buf_size;
    *pOut_len += dst_buf_size;
    if (status == TINFL_STATUS_DONE)
      break;
    new_out_buf_capacity = out_buf_capacity * 2;
    if (new_out_buf_capacity < 128)
      new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    if (!pNew_buf) {
      MZ_FREE(pBuf);
      *pOut_len = 0;
      return NULL;
    }
    pBuf = pNew_buf;
    out_buf_capacity = new_out_buf_capacity;
  }
  return pBuf;
}

size_t tinfl_decompress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                   const void *pSrc_buf, size_t src_buf_len,
                                   int flags) {
  tinfl_decompressor decomp;
  tinfl_status status;
  tinfl_init(&decomp);
  status =
      tinfl_decompress(&decomp, (const mz_uint8 *)pSrc_buf, &src_buf_len,
                       (mz_uint8 *)pOut_buf, (mz_uint8 *)pOut_buf, &out_buf_len,
                       (flags & ~TINFL_FLAG_HAS_MORE_INPUT) |
                           TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  return (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED
                                       : out_buf_len;
}

int tinfl_decompress_mem_to_callback(const void *pIn_buf, size_t *pIn_buf_size,
                                     tinfl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags) {
  int result = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8 *)MZ_MALLOC(TINFL_LZ_DICT_SIZE);
  size_t in_buf_ofs = 0, dict_ofs = 0;
  if (!pDict)
    return TINFL_STATUS_FAILED;
  tinfl_init(&decomp);
  for (;;) {
    size_t in_buf_size = *pIn_buf_size - in_buf_ofs,
           dst_buf_size = TINFL_LZ_DICT_SIZE - dict_ofs;
    tinfl_status status =
        tinfl_decompress(&decomp, (const mz_uint8 *)pIn_buf + in_buf_ofs,
                         &in_buf_size, pDict, pDict + dict_ofs, &dst_buf_size,
                         (flags &
                          ~(TINFL_FLAG_HAS_MORE_INPUT |
                            TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_size;
    if ((dst_buf_size) &&
        (!(*pPut_buf_func)(pDict + dict_ofs, (int)dst_buf_size, pPut_buf_user)))
      break;
    if (status != TINFL_STATUS_HAS_MORE_OUTPUT) {
      result = (status == TINFL_STATUS_DONE);
      break;
    }
    dict_ofs = (dict_ofs + dst_buf_size) & (TINFL_LZ_DICT_SIZE - 1);
  }
  MZ_FREE(pDict);
  *pIn_buf_size = in_buf_ofs;
  return result;
}

// ------------------- Low-level Compression (independent from all decompression
// API's)

// Purposely making these tables static for faster init and thread safety.
static const mz_uint16 s_tdefl_len_sym[256] = {
    257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268,
    268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272,
    272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274,
    274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276,
    276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277,
    277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278,
    278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279,
    279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280,
    280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
    285};

static const mz_uint8 s_tdefl_len_extra[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};

static const mz_uint8 s_tdefl_small_dist_sym[512] = {
    0,  1,  2,  3,  4,  4,  5,  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,
    8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,  10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17};

static const mz_uint8 s_tdefl_small_dist_extra[512] = {
    0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

static const mz_uint8 s_tdefl_large_dist_sym[128] = {
    0,  0,  18, 19, 20, 20, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
    24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26,
    26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
    28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29};

static const mz_uint8 s_tdefl_large_dist_extra[128] = {
    0,  0,  8,  8,  9,  9,  9,  9,  10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
    13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13};

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted
// values.
typedef struct { mz_uint16 m_key, m_sym_index; } tdefl_sym_freq;
static tdefl_sym_freq *tdefl_radix_sort_syms(mz_uint num_syms,
                                             tdefl_sym_freq *pSyms0,
                                             tdefl_sym_freq *pSyms1) {
  mz_uint32 total_passes = 2, pass_shift, pass, i, hist[256 * 2];
  tdefl_sym_freq *pCur_syms = pSyms0, *pNew_syms = pSyms1;
  MZ_CLEAR_OBJ(hist);
  for (i = 0; i < num_syms; i++) {
    mz_uint freq = pSyms0[i].m_key;
    hist[freq & 0xFF]++;
    hist[256 + ((freq >> 8) & 0xFF)]++;
  }
  while ((total_passes > 1) && (num_syms == hist[(total_passes - 1) * 256]))
    total_passes--;
  for (pass_shift = 0, pass = 0; pass < total_passes; pass++, pass_shift += 8) {
    const mz_uint32 *pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    for (i = 0; i < 256; i++) {
      offsets[i] = cur_ofs;
      cur_ofs += pHist[i];
    }
    for (i = 0; i < num_syms; i++)
      pNew_syms[offsets[(pCur_syms[i].m_key >> pass_shift) & 0xFF]++] =
          pCur_syms[i];
    {
      tdefl_sym_freq *t = pCur_syms;
      pCur_syms = pNew_syms;
      pNew_syms = t;
    }
  }
  return pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat,
// alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
static void tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, int n) {
  int root, leaf, next, avbl, used, dpth;
  if (n == 0)
    return;
  else if (n == 1) {
    A[0].m_key = 1;
    return;
  }
  A[0].m_key += A[1].m_key;
  root = 0;
  leaf = 2;
  for (next = 1; next < n - 1; next++) {
    if (leaf >= n || A[root].m_key < A[leaf].m_key) {
      A[next].m_key = A[root].m_key;
      A[root++].m_key = (mz_uint16)next;
    } else
      A[next].m_key = A[leaf++].m_key;
    if (leaf >= n || (root < next && A[root].m_key < A[leaf].m_key)) {
      A[next].m_key = (mz_uint16)(A[next].m_key + A[root].m_key);
      A[root++].m_key = (mz_uint16)next;
    } else
      A[next].m_key = (mz_uint16)(A[next].m_key + A[leaf++].m_key);
  }
  A[n - 2].m_key = 0;
  for (next = n - 3; next >= 0; next--)
    A[next].m_key = A[A[next].m_key].m_key + 1;
  avbl = 1;
  used = dpth = 0;
  root = n - 2;
  next = n - 1;
  while (avbl > 0) {
    while (root >= 0 && (int)A[root].m_key == dpth) {
      used++;
      root--;
    }
    while (avbl > used) {
      A[next--].m_key = (mz_uint16)(dpth);
      avbl--;
    }
    avbl = 2 * used;
    dpth++;
    used = 0;
  }
}

// Limits canonical Huffman code table's max code size.
enum { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
static void tdefl_huffman_enforce_max_code_size(int *pNum_codes,
                                                int code_list_len,
                                                int max_code_size) {
  int i;
  mz_uint32 total = 0;
  if (code_list_len <= 1)
    return;
  for (i = max_code_size + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++)
    pNum_codes[max_code_size] += pNum_codes[i];
  for (i = max_code_size; i > 0; i--)
    total += (((mz_uint32)pNum_codes[i]) << (max_code_size - i));
  while (total != (1UL << max_code_size)) {
    pNum_codes[max_code_size]--;
    for (i = max_code_size - 1; i > 0; i--)
      if (pNum_codes[i]) {
        pNum_codes[i]--;
        pNum_codes[i + 1] += 2;
        break;
      }
    total--;
  }
}

static void tdefl_optimize_huffman_table(tdefl_compressor *d, int table_num,
                                         int table_len, int code_size_limit,
                                         int static_table) {
  int i, j, l, num_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE];
  mz_uint next_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1];
  MZ_CLEAR_OBJ(num_codes);
  if (static_table) {
    for (i = 0; i < table_len; i++)
      num_codes[d->m_huff_code_sizes[table_num][i]]++;
  } else {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS],
        *pSyms;
    int num_used_syms = 0;
    const mz_uint16 *pSym_count = &d->m_huff_count[table_num][0];
    for (i = 0; i < table_len; i++)
      if (pSym_count[i]) {
        syms0[num_used_syms].m_key = (mz_uint16)pSym_count[i];
        syms0[num_used_syms++].m_sym_index = (mz_uint16)i;
      }

    pSyms = tdefl_radix_sort_syms(num_used_syms, syms0, syms1);
    tdefl_calculate_minimum_redundancy(pSyms, num_used_syms);

    for (i = 0; i < num_used_syms; i++)
      num_codes[pSyms[i].m_key]++;

    tdefl_huffman_enforce_max_code_size(num_codes, num_used_syms,
                                        code_size_limit);

    MZ_CLEAR_OBJ(d->m_huff_code_sizes[table_num]);
    MZ_CLEAR_OBJ(d->m_huff_codes[table_num]);
    for (i = 1, j = num_used_syms; i <= code_size_limit; i++)
      for (l = num_codes[i]; l > 0; l--)
        d->m_huff_code_sizes[table_num][pSyms[--j].m_sym_index] = (mz_uint8)(i);
  }

  next_code[1] = 0;
  for (j = 0, i = 2; i <= code_size_limit; i++)
    next_code[i] = j = ((j + num_codes[i - 1]) << 1);

  for (i = 0; i < table_len; i++) {
    mz_uint rev_code = 0, code, code_size;
    if ((code_size = d->m_huff_code_sizes[table_num][i]) == 0)
      continue;
    code = next_code[code_size]++;
    for (l = code_size; l > 0; l--, code >>= 1)
      rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_num][i] = (mz_uint16)rev_code;
  }
}

#define TDEFL_PUT_BITS(b, l)                                                   \
  do {                                                                         \
    mz_uint bits = b;                                                          \
    mz_uint len = l;                                                           \
    MZ_ASSERT(bits <= ((1U << len) - 1U));                                     \
    d->m_bit_buffer |= (bits << d->m_bits_in);                                 \
    d->m_bits_in += len;                                                       \
    while (d->m_bits_in >= 8) {                                                \
      if (d->m_pOutput_buf < d->m_pOutput_buf_end)                             \
        *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_buffer);                     \
      d->m_bit_buffer >>= 8;                                                   \
      d->m_bits_in -= 8;                                                       \
    }                                                                          \
  }                                                                            \
  MZ_MACRO_END

#define TDEFL_RLE_PREV_CODE_SIZE()                                             \
  {                                                                            \
    if (rle_repeat_count) {                                                    \
      if (rle_repeat_count < 3) {                                              \
        d->m_huff_count[2][prev_code_size] = (mz_uint16)(                      \
            d->m_huff_count[2][prev_code_size] + rle_repeat_count);            \
        while (rle_repeat_count--)                                             \
          packed_code_sizes[num_packed_code_sizes++] = prev_code_size;         \
      } else {                                                                 \
        d->m_huff_count[2][16] = (mz_uint16)(d->m_huff_count[2][16] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 16;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_repeat_count - 3);                                  \
      }                                                                        \
      rle_repeat_count = 0;                                                    \
    }                                                                          \
  }

#define TDEFL_RLE_ZERO_CODE_SIZE()                                             \
  {                                                                            \
    if (rle_z_count) {                                                         \
      if (rle_z_count < 3) {                                                   \
        d->m_huff_count[2][0] =                                                \
            (mz_uint16)(d->m_huff_count[2][0] + rle_z_count);                  \
        while (rle_z_count--)                                                  \
          packed_code_sizes[num_packed_code_sizes++] = 0;                      \
      } else if (rle_z_count <= 10) {                                          \
        d->m_huff_count[2][17] = (mz_uint16)(d->m_huff_count[2][17] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 17;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_z_count - 3);                                       \
      } else {                                                                 \
        d->m_huff_count[2][18] = (mz_uint16)(d->m_huff_count[2][18] + 1);      \
        packed_code_sizes[num_packed_code_sizes++] = 18;                       \
        packed_code_sizes[num_packed_code_sizes++] =                           \
            (mz_uint8)(rle_z_count - 11);                                      \
      }                                                                        \
      rle_z_count = 0;                                                         \
    }                                                                          \
  }

static mz_uint8 s_tdefl_packed_code_size_syms_swizzle[] = {
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

static void tdefl_start_dynamic_block(tdefl_compressor *d) {
  int num_lit_codes, num_dist_codes, num_bit_lengths;
  mz_uint i, total_code_sizes_to_pack, num_packed_code_sizes, rle_z_count,
      rle_repeat_count, packed_code_sizes_index;
  mz_uint8
      code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1],
      packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1],
      prev_code_size = 0xFF;

  d->m_huff_count[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  for (num_lit_codes = 286; num_lit_codes > 257; num_lit_codes--)
    if (d->m_huff_code_sizes[0][num_lit_codes - 1])
      break;
  for (num_dist_codes = 30; num_dist_codes > 1; num_dist_codes--)
    if (d->m_huff_code_sizes[1][num_dist_codes - 1])
      break;

  memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], num_lit_codes);
  memcpy(code_sizes_to_pack + num_lit_codes, &d->m_huff_code_sizes[1][0],
         num_dist_codes);
  total_code_sizes_to_pack = num_lit_codes + num_dist_codes;
  num_packed_code_sizes = 0;
  rle_z_count = 0;
  rle_repeat_count = 0;

  memset(&d->m_huff_count[2][0], 0,
         sizeof(d->m_huff_count[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  for (i = 0; i < total_code_sizes_to_pack; i++) {
    mz_uint8 code_size = code_sizes_to_pack[i];
    if (!code_size) {
      TDEFL_RLE_PREV_CODE_SIZE();
      if (++rle_z_count == 138) {
        TDEFL_RLE_ZERO_CODE_SIZE();
      }
    } else {
      TDEFL_RLE_ZERO_CODE_SIZE();
      if (code_size != prev_code_size) {
        TDEFL_RLE_PREV_CODE_SIZE();
        d->m_huff_count[2][code_size] =
            (mz_uint16)(d->m_huff_count[2][code_size] + 1);
        packed_code_sizes[num_packed_code_sizes++] = code_size;
      } else if (++rle_repeat_count == 6) {
        TDEFL_RLE_PREV_CODE_SIZE();
      }
    }
    prev_code_size = code_size;
  }
  if (rle_repeat_count) {
    TDEFL_RLE_PREV_CODE_SIZE();
  } else {
    TDEFL_RLE_ZERO_CODE_SIZE();
  }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(num_lit_codes - 257, 5);
  TDEFL_PUT_BITS(num_dist_codes - 1, 5);

  for (num_bit_lengths = 18; num_bit_lengths >= 0; num_bit_lengths--)
    if (d->m_huff_code_sizes
            [2][s_tdefl_packed_code_size_syms_swizzle[num_bit_lengths]])
      break;
  num_bit_lengths = MZ_MAX(4, (num_bit_lengths + 1));
  TDEFL_PUT_BITS(num_bit_lengths - 4, 4);
  for (i = 0; (int)i < num_bit_lengths; i++)
    TDEFL_PUT_BITS(
        d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[i]], 3);

  for (packed_code_sizes_index = 0;
       packed_code_sizes_index < num_packed_code_sizes;) {
    mz_uint code = packed_code_sizes[packed_code_sizes_index++];
    MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    if (code >= 16)
      TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_index++],
                     "\02\03\07"[code - 16]);
  }
}

static void tdefl_start_static_block(tdefl_compressor *d) {
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  for (i = 0; i <= 143; ++i)
    *p++ = 8;
  for (; i <= 255; ++i)
    *p++ = 9;
  for (; i <= 279; ++i)
    *p++ = 7;
  for (; i <= 287; ++i)
    *p++ = 8;

  memset(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

static const mz_uint mz_bitmasks[17] = {
    0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF,
    0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF};

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN &&             \
    MINIZ_HAS_64BIT_REGISTERS
static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d) {
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_buffer = d->m_bit_buffer;
  mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l)                                              \
  {                                                                            \
    bit_buffer |= (((mz_uint64)(b)) << bits_in);                               \
    bits_in += (l);                                                            \
  }

  flags = 1;
  for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end;
       flags >>= 1) {
    if (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    if (flags & 1) {
      mz_uint s0, s1, n0, n1, sym, num_extra_bits;
      mz_uint match_len = pLZ_codes[0],
              match_dist = *(const mz_uint16 *)(pLZ_codes + 1);
      pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]],
                          d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]],
                          s_tdefl_len_extra[match_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      num_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym],
                          d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[num_extra_bits],
                          num_extra_bits);
    } else {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                          d->m_huff_code_sizes[0][lit]);

      if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end)) {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                            d->m_huff_code_sizes[0][lit]);

        if (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end)) {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit],
                              d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    if (pOutput_buf >= d->m_pOutput_buf_end)
      return MZ_FALSE;

    *(mz_uint64 *)pOutput_buf = bit_buffer;
    pOutput_buf += (bits_in >> 3);
    bit_buffer >>= (bits_in & ~7);
    bits_in &= 7;
  }

#undef TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_buffer = 0;

  while (bits_in) {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_buffer & mz_bitmasks[n], n);
    bit_buffer >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  return (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#else
static mz_bool tdefl_compress_lz_codes(tdefl_compressor *d) {
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  for (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf;
       flags >>= 1) {
    if (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    if (flags & 1) {
      mz_uint sym, num_extra_bits;
      mz_uint match_len = pLZ_codes[0],
              match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8));
      pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]],
                     d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]],
                     s_tdefl_len_extra[match_len]);

      if (match_dist < 512) {
        sym = s_tdefl_small_dist_sym[match_dist];
        num_extra_bits = s_tdefl_small_dist_extra[match_dist];
      } else {
        sym = s_tdefl_large_dist_sym[match_dist >> 8];
        num_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[num_extra_bits], num_extra_bits);
    } else {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  return (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN &&
       // MINIZ_HAS_64BIT_REGISTERS

static mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block) {
  if (static_block)
    tdefl_start_static_block(d);
  else
    tdefl_start_dynamic_block(d);
  return tdefl_compress_lz_codes(d);
}

static int tdefl_flush_block(tdefl_compressor *d, int flush) {
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  int n, use_raw_block =
             ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) &&
             (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size;
  mz_uint8 *pOutput_buf_start =
      ((d->m_pPut_buf_func == NULL) &&
       ((*d->m_pOut_buf_size - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_SIZE))
          ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs)
          : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_SIZE - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_num_flags_left);
  d->m_pLZ_code_buf -= (d->m_num_flags_left == 8);

  if ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_index)) {
    TDEFL_PUT_BITS(0x78, 8);
    TDEFL_PUT_BITS(0x01, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf;
  saved_bit_buf = d->m_bit_buffer;
  saved_bits_in = d->m_bits_in;

  if (!use_raw_block)
    comp_block_succeeded =
        tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) ||
                                    (d->m_total_lz_bytes < 48));

  // If the block gets expanded, forget the current contents of the output
  // buffer and send a raw block instead.
  if (((use_raw_block) ||
       ((d->m_total_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >=
                                  d->m_total_lz_bytes))) &&
      ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size)) {
    mz_uint i;
    d->m_pOutput_buf = pSaved_output_buf;
    d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    if (d->m_bits_in) {
      TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
    }
    for (i = 2; i; --i, d->m_total_lz_bytes ^= 0xFFFF) {
      TDEFL_PUT_BITS(d->m_total_lz_bytes & 0xFFFF, 16);
    }
    for (i = 0; i < d->m_total_lz_bytes; ++i) {
      TDEFL_PUT_BITS(
          d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_SIZE_MASK],
          8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed
  // block not fitting into the output buffer when using dynamic codes.
  else if (!comp_block_succeeded) {
    d->m_pOutput_buf = pSaved_output_buf;
    d->m_bit_buffer = saved_bit_buf, d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  if (flush) {
    if (flush == TDEFL_FINISH) {
      if (d->m_bits_in) {
        TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
      }
      if (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) {
        mz_uint i, a = d->m_adler32;
        for (i = 0; i < 4; i++) {
          TDEFL_PUT_BITS((a >> 24) & 0xFF, 8);
          a <<= 8;
        }
      }
    } else {
      mz_uint i, z = 0;
      TDEFL_PUT_BITS(0, 3);
      if (d->m_bits_in) {
        TDEFL_PUT_BITS(0, 8 - d->m_bits_in);
      }
      for (i = 2; i; --i, z ^= 0xFFFF) {
        TDEFL_PUT_BITS(z & 0xFFFF, 16);
      }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  memset(&d->m_huff_count[0][0], 0,
         sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_count[1][0], 0,
         sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1;
  d->m_pLZ_flags = d->m_lz_code_buf;
  d->m_num_flags_left = 8;
  d->m_lz_code_buf_dict_pos += d->m_total_lz_bytes;
  d->m_total_lz_bytes = 0;
  d->m_block_index++;

  if ((n = (int)(d->m_pOutput_buf - pOutput_buf_start)) != 0) {
    if (d->m_pPut_buf_func) {
      *d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
      if (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        return (d->m_prev_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    } else if (pOutput_buf_start == d->m_output_buf) {
      int bytes_to_copy = (int)MZ_MIN(
          (size_t)n, (size_t)(*d->m_pOut_buf_size - d->m_out_buf_ofs));
      memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf,
             bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      if ((n -= bytes_to_copy) != 0) {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    } else {
      d->m_out_buf_ofs += n;
    }
  }

  return d->m_output_flush_remaining;
}

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#define TDEFL_READ_UNALIGNED_WORD(p) *(const mz_uint16 *)(p)
static MZ_FORCEINLINE void
tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist,
                 mz_uint max_match_len, mz_uint *pMatch_dist,
                 mz_uint *pMatch_len) {
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK,
                match_len = *pMatch_len, probe_pos = pos, next_probe_pos,
                probe_len;
  mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
  const mz_uint16 *s = (const mz_uint16 *)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]),
            s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN);
  if (max_match_len <= match_len)
    return;
  for (;;) {
    for (;;) {
      if (--num_probes_left == 0)
        return;
#define TDEFL_PROBE                                                            \
  next_probe_pos = d->m_next[probe_pos];                                       \
  if ((!next_probe_pos) ||                                                     \
      ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist))       \
    return;                                                                    \
  probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK;                        \
  if (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) \
    break;
      TDEFL_PROBE;
      TDEFL_PROBE;
      TDEFL_PROBE;
    }
    if (!dist)
      break;
    q = (const mz_uint16 *)(d->m_dict + probe_pos);
    if (TDEFL_READ_UNALIGNED_WORD(q) != s01)
      continue;
    p = s;
    probe_len = 32;
    do {
    } while (
        (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
        (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
        (--probe_len > 0));
    if (!probe_len) {
      *pMatch_dist = dist;
      *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN);
      break;
    } else if ((probe_len = ((mz_uint)(p - s) * 2) +
                            (mz_uint)(*(const mz_uint8 *)p ==
                                      *(const mz_uint8 *)q)) > match_len) {
      *pMatch_dist = dist;
      if ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) ==
          max_match_len)
        break;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#else
static MZ_FORCEINLINE void
tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist,
                 mz_uint max_match_len, mz_uint *pMatch_dist,
                 mz_uint *pMatch_len) {
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK,
                match_len = *pMatch_len, probe_pos = pos, next_probe_pos,
                probe_len;
  mz_uint num_probes_left = d->m_max_probes[match_len >= 32];
  const mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN);
  if (max_match_len <= match_len)
    return;
  for (;;) {
    for (;;) {
      if (--num_probes_left == 0)
        return;
#define TDEFL_PROBE                                                            \
  next_probe_pos = d->m_next[probe_pos];                                       \
  if ((!next_probe_pos) ||                                                     \
      ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist))       \
    return;                                                                    \
  probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK;                        \
  if ((d->m_dict[probe_pos + match_len] == c0) &&                              \
      (d->m_dict[probe_pos + match_len - 1] == c1))                            \
    break;
      TDEFL_PROBE;
      TDEFL_PROBE;
      TDEFL_PROBE;
    }
    if (!dist)
      break;
    p = s;
    q = d->m_dict + probe_pos;
    for (probe_len = 0; probe_len < max_match_len; probe_len++)
      if (*p++ != *q++)
        break;
    if (probe_len > match_len) {
      *pMatch_dist = dist;
      if ((*pMatch_len = match_len = probe_len) == max_match_len)
        return;
      c0 = d->m_dict[pos + match_len];
      c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
static mz_bool tdefl_compress_fast(tdefl_compressor *d) {
  // Faster, minimally featured LZRW1-style match+parse loop with better
  // register utilization. Intended for applications where raw throughput is
  // valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos,
          lookahead_size = d->m_lookahead_size, dict_size = d->m_dict_size,
          total_lz_bytes = d->m_total_lz_bytes,
          num_flags_left = d->m_num_flags_left;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;

  while ((d->m_src_buf_left) || ((d->m_flush) && (lookahead_size))) {
    const mz_uint TDEFL_COMP_FAST_LOOKAHEAD_SIZE = 4096;
    mz_uint dst_pos =
        (lookahead_pos + lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
    mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(
        d->m_src_buf_left, TDEFL_COMP_FAST_LOOKAHEAD_SIZE - lookahead_size);
    d->m_src_buf_left -= num_bytes_to_process;
    lookahead_size += num_bytes_to_process;

    while (num_bytes_to_process) {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_SIZE - dst_pos, num_bytes_to_process);
      memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
      if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        memcpy(d->m_dict + TDEFL_LZ_DICT_SIZE + dst_pos, d->m_pSrc,
               MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_SIZE_MASK;
      num_bytes_to_process -= n;
    }

    dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - lookahead_size, dict_size);
    if ((!d->m_flush) && (lookahead_size < TDEFL_COMP_FAST_LOOKAHEAD_SIZE))
      break;

    while (lookahead_size >= 4) {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(const mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash =
          (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) &
          TDEFL_LEVEL1_HASH_SIZE_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      if (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <=
           dict_size) &&
          ((*(const mz_uint32 *)(d->m_dict +
                                 (probe_pos &= TDEFL_LZ_DICT_SIZE_MASK)) &
            0xFFFFFF) == first_trigram)) {
        const mz_uint16 *p = (const mz_uint16 *)pCur_dict;
        const mz_uint16 *q = (const mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        do {
        } while ((TDEFL_READ_UNALIGNED_WORD(++p) ==
                  TDEFL_READ_UNALIGNED_WORD(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD(++p) ==
                  TDEFL_READ_UNALIGNED_WORD(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD(++p) ==
                  TDEFL_READ_UNALIGNED_WORD(++q)) &&
                 (TDEFL_READ_UNALIGNED_WORD(++p) ==
                  TDEFL_READ_UNALIGNED_WORD(++q)) &&
                 (--probe_len > 0));
        cur_match_len = ((mz_uint)(p - (const mz_uint16 *)pCur_dict) * 2) +
                        (mz_uint)(*(const mz_uint8 *)p == *(const mz_uint8 *)q);
        if (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        if ((cur_match_len < TDEFL_MIN_MATCH_LEN) ||
            ((cur_match_len == TDEFL_MIN_MATCH_LEN) &&
             (cur_match_dist >= 8U * 1024U))) {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_count[0][(mz_uint8)first_trigram]++;
        } else {
          mz_uint32 s0, s1;
          cur_match_len = MZ_MIN(cur_match_len, lookahead_size);

          MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) &&
                    (cur_match_dist >= 1) &&
                    (cur_match_dist <= TDEFL_LZ_DICT_SIZE));

          cur_match_dist--;

          pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
          *(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
          pLZ_code_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
          d->m_huff_count[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_count[0][s_tdefl_len_sym[cur_match_len -
                                             TDEFL_MIN_MATCH_LEN]]++;
        }
      } else {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_count[0][(mz_uint8)first_trigram]++;
      }

      if (--num_flags_left == 0) {
        num_flags_left = 8;
        pLZ_flags = pLZ_code_buf++;
      }

      total_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_size = MZ_MIN(dict_size + cur_match_len, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_SIZE_MASK;
      MZ_ASSERT(lookahead_size >= cur_match_len);
      lookahead_size -= cur_match_len;

      if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) {
        int n;
        d->m_lookahead_pos = lookahead_pos;
        d->m_lookahead_size = lookahead_size;
        d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes;
        d->m_pLZ_code_buf = pLZ_code_buf;
        d->m_pLZ_flags = pLZ_flags;
        d->m_num_flags_left = num_flags_left;
        if ((n = tdefl_flush_block(d, 0)) != 0)
          return (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes;
        pLZ_code_buf = d->m_pLZ_code_buf;
        pLZ_flags = d->m_pLZ_flags;
        num_flags_left = d->m_num_flags_left;
      }
    }

    while (lookahead_size) {
      mz_uint8 lit = d->m_dict[cur_pos];

      total_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      if (--num_flags_left == 0) {
        num_flags_left = 8;
        pLZ_flags = pLZ_code_buf++;
      }

      d->m_huff_count[0][lit]++;

      lookahead_pos++;
      dict_size = MZ_MIN(dict_size + 1, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
      lookahead_size--;

      if (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) {
        int n;
        d->m_lookahead_pos = lookahead_pos;
        d->m_lookahead_size = lookahead_size;
        d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes;
        d->m_pLZ_code_buf = pLZ_code_buf;
        d->m_pLZ_flags = pLZ_flags;
        d->m_num_flags_left = num_flags_left;
        if ((n = tdefl_flush_block(d, 0)) != 0)
          return (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes;
        pLZ_code_buf = d->m_pLZ_code_buf;
        pLZ_flags = d->m_pLZ_flags;
        num_flags_left = d->m_num_flags_left;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos;
  d->m_lookahead_size = lookahead_size;
  d->m_dict_size = dict_size;
  d->m_total_lz_bytes = total_lz_bytes;
  d->m_pLZ_code_buf = pLZ_code_buf;
  d->m_pLZ_flags = pLZ_flags;
  d->m_num_flags_left = num_flags_left;
  return MZ_TRUE;
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

static MZ_FORCEINLINE void tdefl_record_literal(tdefl_compressor *d,
                                                mz_uint8 lit) {
  d->m_total_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1);
  if (--d->m_num_flags_left == 0) {
    d->m_num_flags_left = 8;
    d->m_pLZ_flags = d->m_pLZ_code_buf++;
  }
  d->m_huff_count[0][lit]++;
}

static MZ_FORCEINLINE void
tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist) {
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) &&
            (match_dist <= TDEFL_LZ_DICT_SIZE));

  d->m_total_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8);
  d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80);
  if (--d->m_num_flags_left == 0) {
    d->m_num_flags_left = 8;
    d->m_pLZ_flags = d->m_pLZ_code_buf++;
  }

  s0 = s_tdefl_small_dist_sym[match_dist & 511];
  s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_count[1][(match_dist < 512) ? s0 : s1]++;

  if (match_len >= TDEFL_MIN_MATCH_LEN)
    d->m_huff_count[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

static mz_bool tdefl_compress_normal(tdefl_compressor *d) {
  const mz_uint8 *pSrc = d->m_pSrc;
  size_t src_buf_left = d->m_src_buf_left;
  tdefl_flush flush = d->m_flush;

  while ((src_buf_left) || ((flush) && (d->m_lookahead_size))) {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to
    // TDEFL_MAX_MATCH_LEN.
    if ((d->m_lookahead_size + d->m_dict_size) >= (TDEFL_MIN_MATCH_LEN - 1)) {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) &
                        TDEFL_LZ_DICT_SIZE_MASK,
              ins_pos = d->m_lookahead_pos + d->m_lookahead_size - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK]
                      << TDEFL_LZ_HASH_SHIFT) ^
                     d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK];
      mz_uint num_bytes_to_process = (mz_uint)MZ_MIN(
          src_buf_left, TDEFL_MAX_MATCH_LEN - d->m_lookahead_size);
      const mz_uint8 *pSrc_end = pSrc + num_bytes_to_process;
      src_buf_left -= num_bytes_to_process;
      d->m_lookahead_size += num_bytes_to_process;
      while (pSrc != pSrc_end) {
        mz_uint8 c = *pSrc++;
        d->m_dict[dst_pos] = c;
        if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
        d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash];
        d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
        ins_pos++;
      }
    } else {
      while ((src_buf_left) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN)) {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) &
                          TDEFL_LZ_DICT_SIZE_MASK;
        src_buf_left--;
        d->m_dict[dst_pos] = c;
        if (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        if ((++d->m_lookahead_size + d->m_dict_size) >= TDEFL_MIN_MATCH_LEN) {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_size - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK]
                           << (TDEFL_LZ_HASH_SHIFT * 2)) ^
                          (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK]
                           << TDEFL_LZ_HASH_SHIFT) ^
                          c) &
                         (TDEFL_LZ_HASH_SIZE - 1);
          d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash];
          d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_size =
        MZ_MIN(TDEFL_LZ_DICT_SIZE - d->m_lookahead_size, d->m_dict_size);
    if ((!flush) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      break;

    // Simple lazy/greedy parsing state machine.
    len_to_move = 1;
    cur_match_dist = 0;
    cur_match_len =
        d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1);
    cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;
    if (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS)) {
      if ((d->m_dict_size) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_SIZE_MASK];
        cur_match_len = 0;
        while (cur_match_len < d->m_lookahead_size) {
          if (d->m_dict[cur_pos + cur_match_len] != c)
            break;
          cur_match_len++;
        }
        if (cur_match_len < TDEFL_MIN_MATCH_LEN)
          cur_match_len = 0;
        else
          cur_match_dist = 1;
      }
    } else {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_size,
                       d->m_lookahead_size, &cur_match_dist, &cur_match_len);
    }
    if (((cur_match_len == TDEFL_MIN_MATCH_LEN) &&
         (cur_match_dist >= 8U * 1024U)) ||
        (cur_pos == cur_match_dist) ||
        ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5))) {
      cur_match_dist = cur_match_len = 0;
    }
    if (d->m_saved_match_len) {
      if (cur_match_len > d->m_saved_match_len) {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        if (cur_match_len >= 128) {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0;
          len_to_move = cur_match_len;
        } else {
          d->m_saved_lit = d->m_dict[cur_pos];
          d->m_saved_match_dist = cur_match_dist;
          d->m_saved_match_len = cur_match_len;
        }
      } else {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1;
        d->m_saved_match_len = 0;
      }
    } else if (!cur_match_dist)
      tdefl_record_literal(d,
                           d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)]);
    else if ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) ||
             (cur_match_len >= 128)) {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    } else {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, sizeof(d->m_dict) - 1)];
      d->m_saved_match_dist = cur_match_dist;
      d->m_saved_match_len = cur_match_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_size >= len_to_move);
    d->m_lookahead_size -= len_to_move;
    d->m_dict_size = MZ_MIN(d->m_dict_size + len_to_move, (mz_uint)TDEFL_LZ_DICT_SIZE);
    // Check if it's time to flush the current LZ codes to the internal output
    // buffer.
    if ((d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) ||
        ((d->m_total_lz_bytes > 31 * 1024) &&
         (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >=
           d->m_total_lz_bytes) ||
          (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))) {
      int n;
      d->m_pSrc = pSrc;
      d->m_src_buf_left = src_buf_left;
      if ((n = tdefl_flush_block(d, 0)) != 0)
        return (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc;
  d->m_src_buf_left = src_buf_left;
  return MZ_TRUE;
}

static tdefl_status tdefl_flush_output_buffer(tdefl_compressor *d) {
  if (d->m_pIn_buf_size) {
    *d->m_pIn_buf_size = d->m_pSrc - (const mz_uint8 *)d->m_pIn_buf;
  }

  if (d->m_pOut_buf_size) {
    size_t n = MZ_MIN(*d->m_pOut_buf_size - d->m_out_buf_ofs,
                      d->m_output_flush_remaining);
    memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs,
           d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_pOut_buf_size = d->m_out_buf_ofs;
  }

  return (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE
                                                         : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, const void *pIn_buf,
                            size_t *pIn_buf_size, void *pOut_buf,
                            size_t *pOut_buf_size, tdefl_flush flush) {
  if (!d) {
    if (pIn_buf_size)
      *pIn_buf_size = 0;
    if (pOut_buf_size)
      *pOut_buf_size = 0;
    return TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf;
  d->m_pIn_buf_size = pIn_buf_size;
  d->m_pOut_buf = pOut_buf;
  d->m_pOut_buf_size = pOut_buf_size;
  d->m_pSrc = (const mz_uint8 *)(pIn_buf);
  d->m_src_buf_left = pIn_buf_size ? *pIn_buf_size : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  if (((d->m_pPut_buf_func != NULL) ==
       ((pOut_buf != NULL) || (pOut_buf_size != NULL))) ||
      (d->m_prev_return_status != TDEFL_STATUS_OKAY) ||
      (d->m_wants_to_finish && (flush != TDEFL_FINISH)) ||
      (pIn_buf_size && *pIn_buf_size && !pIn_buf) ||
      (pOut_buf_size && *pOut_buf_size && !pOut_buf)) {
    if (pIn_buf_size)
      *pIn_buf_size = 0;
    if (pOut_buf_size)
      *pOut_buf_size = 0;
    return (d->m_prev_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  if ((d->m_output_flush_remaining) || (d->m_finished))
    return (d->m_prev_return_status = tdefl_flush_output_buffer(d));

#if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  if (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS |
                      TDEFL_RLE_MATCHES)) == 0)) {
    if (!tdefl_compress_fast(d))
      return d->m_prev_return_status;
  } else
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    if (!tdefl_compress_normal(d))
      return d->m_prev_return_status;
  }

  if ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) &&
      (pIn_buf))
    d->m_adler32 =
        (mz_uint32)mz_adler32(d->m_adler32, (const mz_uint8 *)pIn_buf,
                              d->m_pSrc - (const mz_uint8 *)pIn_buf);

  if ((flush) && (!d->m_lookahead_size) && (!d->m_src_buf_left) &&
      (!d->m_output_flush_remaining)) {
    if (tdefl_flush_block(d, flush) < 0)
      return d->m_prev_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    if (flush == TDEFL_FULL_FLUSH) {
      MZ_CLEAR_OBJ(d->m_hash);
      MZ_CLEAR_OBJ(d->m_next);
      d->m_dict_size = 0;
    }
  }

  return (d->m_prev_return_status = tdefl_flush_output_buffer(d));
}

tdefl_status tdefl_compress_buffer(tdefl_compressor *d, const void *pIn_buf,
                                   size_t in_buf_size, tdefl_flush flush) {
  MZ_ASSERT(d->m_pPut_buf_func);
  return tdefl_compress(d, pIn_buf, &in_buf_size, NULL, NULL, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d,
                        tdefl_put_buf_func_ptr pPut_buf_func,
                        void *pPut_buf_user, int flags) {
  d->m_pPut_buf_func = pPut_buf_func;
  d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags);
  d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3;
  d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  if (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG))
    MZ_CLEAR_OBJ(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_size = d->m_dict_size =
      d->m_total_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished =
      d->m_block_index = d->m_bit_buffer = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1;
  d->m_pLZ_flags = d->m_lz_code_buf;
  d->m_num_flags_left = 8;
  d->m_pOutput_buf = d->m_output_buf;
  d->m_pOutput_buf_end = d->m_output_buf;
  d->m_prev_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0;
  d->m_adler32 = 1;
  d->m_pIn_buf = NULL;
  d->m_pOut_buf = NULL;
  d->m_pIn_buf_size = NULL;
  d->m_pOut_buf_size = NULL;
  d->m_flush = TDEFL_NO_FLUSH;
  d->m_pSrc = NULL;
  d->m_src_buf_left = 0;
  d->m_out_buf_ofs = 0;
  memset(&d->m_huff_count[0][0], 0,
         sizeof(d->m_huff_count[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_count[1][0], 0,
         sizeof(d->m_huff_count[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  return TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d) {
  return d->m_prev_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d) { return d->m_adler32; }

mz_bool tdefl_compress_mem_to_output(const void *pBuf, size_t buf_len,
                                     tdefl_put_buf_func_ptr pPut_buf_func,
                                     void *pPut_buf_user, int flags) {
  tdefl_compressor *pComp;
  mz_bool succeeded;
  if (((buf_len) && (!pBuf)) || (!pPut_buf_func))
    return MZ_FALSE;
  pComp = (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor));
  if (!pComp)
    return MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) ==
               TDEFL_STATUS_OKAY);
  succeeded =
      succeeded && (tdefl_compress_buffer(pComp, pBuf, buf_len, TDEFL_FINISH) ==
                    TDEFL_STATUS_DONE);
  MZ_FREE(pComp);
  return succeeded;
}

typedef struct {
  size_t m_size, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_buffer;

static mz_bool tdefl_output_buffer_putter(const void *pBuf, int len,
                                          void *pUser) {
  tdefl_output_buffer *p = (tdefl_output_buffer *)pUser;
  size_t new_size = p->m_size + len;
  if (new_size > p->m_capacity) {
    size_t new_capacity = p->m_capacity;
    mz_uint8 *pNew_buf;
    if (!p->m_expandable)
      return MZ_FALSE;
    do {
      new_capacity = MZ_MAX(128U, new_capacity << 1U);
    } while (new_size > new_capacity);
    pNew_buf = (mz_uint8 *)MZ_REALLOC(p->m_pBuf, new_capacity);
    if (!pNew_buf)
      return MZ_FALSE;
    p->m_pBuf = pNew_buf;
    p->m_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)p->m_pBuf + p->m_size, pBuf, len);
  p->m_size = new_size;
  return MZ_TRUE;
}

void *tdefl_compress_mem_to_heap(const void *pSrc_buf, size_t src_buf_len,
                                 size_t *pOut_len, int flags) {
  tdefl_output_buffer out_buf;
  MZ_CLEAR_OBJ(out_buf);
  if (!pOut_len)
    return MZ_FALSE;
  else
    *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  if (!tdefl_compress_mem_to_output(
          pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags))
    return NULL;
  *pOut_len = out_buf.m_size;
  return out_buf.m_pBuf;
}

size_t tdefl_compress_mem_to_mem(void *pOut_buf, size_t out_buf_len,
                                 const void *pSrc_buf, size_t src_buf_len,
                                 int flags) {
  tdefl_output_buffer out_buf;
  MZ_CLEAR_OBJ(out_buf);
  if (!pOut_buf)
    return 0;
  out_buf.m_pBuf = (mz_uint8 *)pOut_buf;
  out_buf.m_capacity = out_buf_len;
  if (!tdefl_compress_mem_to_output(
          pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags))
    return 0;
  return out_buf.m_size;
}

#ifndef MINIZ_NO_ZLIB_APIS
static const mz_uint s_tdefl_num_probes[11] = {0,   1,   6,   32,  16,  32,
                                               128, 256, 512, 768, 1500};

// level may actually range from [0,10] (10 is a "hidden" max level, where we
// want a bit more compression and it's fine if throughput to fall off a cliff
// on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(int level, int window_bits,
                                                int strategy) {
  mz_uint comp_flags =
      s_tdefl_num_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] |
      ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  if (window_bits > 0)
    comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  if (!level)
    comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  else if (strategy == MZ_FILTERED)
    comp_flags |= TDEFL_FILTER_MATCHES;
  else if (strategy == MZ_HUFFMAN_ONLY)
    comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  else if (strategy == MZ_FIXED)
    comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  else if (strategy == MZ_RLE)
    comp_flags |= TDEFL_RLE_MATCHES;

  return comp_flags;
}
#endif // MINIZ_NO_ZLIB_APIS

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4204) // nonstandard extension used : non-constant
                                // aggregate initializer (also supported by GNU
                                // C and C99, so no big deal)
#pragma warning(disable : 4244) // 'initializing': conversion from '__int64' to
                                // 'int', possible loss of data
#pragma warning(disable : 4267) // 'argument': conversion from '__int64' to 'int',
                                // possible loss of data
#pragma warning(disable : 4996) // 'strdup': The POSIX name for this item is
                                // deprecated. Instead, use the ISO C and C++
                                // conformant name: _strdup.
#endif

// Simple PNG writer function by Alex Evans, 2011. Released into the public
// domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files
// generated by this function pass pngcheck.
void *tdefl_write_image_to_png_file_in_memory_ex(const void *pImage, int w,
                                                 int h, int num_chans,
                                                 size_t *pLen_out,
                                                 mz_uint level, mz_bool flip) {
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was
  // defined.
  static const mz_uint s_tdefl_png_num_probes[11] = {
      0, 1, 6, 32, 16, 32, 128, 256, 512, 768, 1500};
  tdefl_compressor *pComp =
      (tdefl_compressor *)MZ_MALLOC(sizeof(tdefl_compressor));
  tdefl_output_buffer out_buf;
  int i, bpl = w * num_chans, y, z;
  mz_uint32 c;
  *pLen_out = 0;
  if (!pComp)
    return NULL;
  MZ_CLEAR_OBJ(out_buf);
  out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57 + MZ_MAX(64, (1 + bpl) * h);
  if (NULL == (out_buf.m_pBuf = (mz_uint8 *)MZ_MALLOC(out_buf.m_capacity))) {
    MZ_FREE(pComp);
    return NULL;
  }
  // write dummy header
  for (z = 41; z; --z)
    tdefl_output_buffer_putter(&z, 1, &out_buf);
  // compress image data
  tdefl_init(pComp, tdefl_output_buffer_putter, &out_buf,
             s_tdefl_png_num_probes[MZ_MIN(10, level)] |
                 TDEFL_WRITE_ZLIB_HEADER);
  for (y = 0; y < h; ++y) {
    tdefl_compress_buffer(pComp, &z, 1, TDEFL_NO_FLUSH);
    tdefl_compress_buffer(pComp,
                          (mz_uint8 *)pImage + (flip ? (h - 1 - y) : y) * bpl,
                          bpl, TDEFL_NO_FLUSH);
  }
  if (tdefl_compress_buffer(pComp, NULL, 0, TDEFL_FINISH) !=
      TDEFL_STATUS_DONE) {
    MZ_FREE(pComp);
    MZ_FREE(out_buf.m_pBuf);
    return NULL;
  }
  // write real header
  *pLen_out = out_buf.m_size - 41;
  {
    static const mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};
    mz_uint8 pnghdr[41] = {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
        0x49, 0x48, 0x44, 0x52, 0, 0, (mz_uint8)(w >> 8), (mz_uint8)w, 0, 0,
        (mz_uint8)(h >> 8), (mz_uint8)h, 8, chans[num_chans], 0, 0, 0, 0, 0, 0,
        0, (mz_uint8)(*pLen_out >> 24), (mz_uint8)(*pLen_out >> 16),
        (mz_uint8)(*pLen_out >> 8), (mz_uint8)*pLen_out, 0x49, 0x44, 0x41,
        0x54};
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, pnghdr + 12, 17);
    for (i = 0; i < 4; ++i, c <<= 8)
      ((mz_uint8 *)(pnghdr + 29))[i] = (mz_uint8)(c >> 24);
    memcpy(out_buf.m_pBuf, pnghdr, 41);
  }
  // write footer (IDAT CRC-32, followed by IEND chunk)
  if (!tdefl_output_buffer_putter(
          "\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) {
    *pLen_out = 0;
    MZ_FREE(pComp);
    MZ_FREE(out_buf.m_pBuf);
    return NULL;
  }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT, out_buf.m_pBuf + 41 - 4,
                          *pLen_out + 4);
  for (i = 0; i < 4; ++i, c <<= 8)
    (out_buf.m_pBuf + out_buf.m_size - 16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *pLen_out += 57;
  MZ_FREE(pComp);
  return out_buf.m_pBuf;
}
void *tdefl_write_image_to_png_file_in_memory(const void *pImage, int w, int h,
                                              int num_chans, size_t *pLen_out) {
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we
  // can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's
  // where #defined out)
  return tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, num_chans,
                                                    pLen_out, 6, MZ_FALSE);
}

// ------------------- .ZIP archive reading

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef MINIZ_NO_STDIO
#define MZ_FILE void *
#else
#include <stdio.h>
#include <sys/stat.h>

#if defined(_MSC_VER) //|| defined(__MINGW64__)
static FILE *mz_fopen(const char *pFilename, const char *pMode) {
  FILE *pFile = NULL;
  fopen_s(&pFile, pFilename, pMode);
  return pFile;
}
static FILE *mz_freopen(const char *pPath, const char *pMode, FILE *pStream) {
  FILE *pFile = NULL;
  if (freopen_s(&pFile, pPath, pMode, pStream))
    return NULL;
  return pFile;
}
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN mz_fopen
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 _ftelli64
#define MZ_FSEEK64 _fseeki64
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT _stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN mz_freopen
#define MZ_DELETE_FILE remove
#elif defined(__MINGW32__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello64
#define MZ_FSEEK64 fseeko64
#define MZ_FILE_STAT_STRUCT _stat
#define MZ_FILE_STAT _stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#elif defined(__TINYC__)
#ifndef MINIZ_NO_TIME
#include <sys/utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftell
#define MZ_FSEEK64 fseek
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#elif defined(__GNUC__) && defined(_LARGEFILE64_SOURCE) && _LARGEFILE64_SOURCE
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen64(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello64
#define MZ_FSEEK64 fseeko64
#define MZ_FILE_STAT_STRUCT stat64
#define MZ_FILE_STAT stat64
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(p, m, s) freopen64(p, m, s)
#define MZ_DELETE_FILE remove
#else
#ifndef MINIZ_NO_TIME
#include <utime.h>
#endif
#define MZ_FILE FILE
#define MZ_FOPEN(f, m) fopen(f, m)
#define MZ_FCLOSE fclose
#define MZ_FREAD fread
#define MZ_FWRITE fwrite
#define MZ_FTELL64 ftello
#define MZ_FSEEK64 fseeko
#define MZ_FILE_STAT_STRUCT stat
#define MZ_FILE_STAT stat
#define MZ_FFLUSH fflush
#define MZ_FREOPEN(f, m, s) freopen(f, m, s)
#define MZ_DELETE_FILE remove
#endif // #ifdef _MSC_VER
#endif // #ifdef MINIZ_NO_STDIO

#define MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler
// alignment and platform endian issues, miniz.c doesn't use structs for any of
// this stuff.
enum {
  // ZIP archive identifiers and record sizes
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50,
  MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50,
  MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_HEADER_SIZE = 30,
  MZ_ZIP_CENTRAL_DIR_HEADER_SIZE = 46,
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0,
  MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4,
  MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6,
  MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_METHOD_OFS = 10,
  MZ_ZIP_CDH_FILE_TIME_OFS = 12,
  MZ_ZIP_CDH_FILE_DATE_OFS = 14,
  MZ_ZIP_CDH_CRC32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_SIZE_OFS = 20,
  MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS = 24,
  MZ_ZIP_CDH_FILENAME_LEN_OFS = 28,
  MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32,
  MZ_ZIP_CDH_DISK_START_OFS = 34,
  MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36,
  MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38,
  MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0,
  MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4,
  MZ_ZIP_LDH_BIT_FLAG_OFS = 6,
  MZ_ZIP_LDH_METHOD_OFS = 8,
  MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12,
  MZ_ZIP_LDH_CRC32_OFS = 14,
  MZ_ZIP_LDH_COMPRESSED_SIZE_OFS = 18,
  MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26,
  MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0,
  MZ_ZIP_ECDH_NUM_THIS_DISK_OFS = 4,
  MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS = 6,
  MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS = 10,
  MZ_ZIP_ECDH_CDIR_SIZE_OFS = 12,
  MZ_ZIP_ECDH_CDIR_OFS_OFS = 16,
  MZ_ZIP_ECDH_COMMENT_SIZE_OFS = 20,
};

typedef struct {
  void *m_p;
  size_t m_size, m_capacity;
  mz_uint m_element_size;
} mz_zip_array;

struct mz_zip_internal_state_tag {
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  void *m_pMem;
  size_t m_mem_size;
  size_t m_mem_capacity;
};

#define MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(array_ptr, element_size)                 \
  (array_ptr)->m_element_size = element_size
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index)                   \
  ((element_type *)((array_ptr)->m_p))[index]

static MZ_FORCEINLINE void mz_zip_array_clear(mz_zip_archive *pZip,
                                              mz_zip_array *pArray) {
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, sizeof(mz_zip_array));
}

static mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip,
                                            mz_zip_array *pArray,
                                            size_t min_new_capacity,
                                            mz_uint growing) {
  void *pNew_p;
  size_t new_capacity = min_new_capacity;
  MZ_ASSERT(pArray->m_element_size);
  if (pArray->m_capacity >= min_new_capacity)
    return MZ_TRUE;
  if (growing) {
    new_capacity = MZ_MAX(1, pArray->m_capacity);
    while (new_capacity < min_new_capacity)
      new_capacity *= 2;
  }
  if (NULL == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p,
                                         pArray->m_element_size, new_capacity)))
    return MZ_FALSE;
  pArray->m_p = pNew_p;
  pArray->m_capacity = new_capacity;
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool
mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray,
                     size_t new_capacity, mz_uint growing) {
  if (new_capacity > pArray->m_capacity) {
    if (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing))
      return MZ_FALSE;
  }
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool
mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_size,
                    mz_uint growing) {
  if (new_size > pArray->m_capacity) {
    if (!mz_zip_array_ensure_capacity(pZip, pArray, new_size, growing))
      return MZ_FALSE;
  }
  pArray->m_size = new_size;
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool
mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n) {
  return mz_zip_array_reserve(pZip, pArray, pArray->m_size + n, MZ_TRUE);
}

static MZ_FORCEINLINE mz_bool
mz_zip_array_push_back(mz_zip_archive *pZip, mz_zip_array *pArray,
                       const void *pElements, size_t n) {
  size_t orig_size = pArray->m_size;
  if (!mz_zip_array_resize(pZip, pArray, orig_size + n, MZ_TRUE))
    return MZ_FALSE;
  memcpy((mz_uint8 *)pArray->m_p + orig_size * pArray->m_element_size,
         pElements, n * pArray->m_element_size);
  return MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
static time_t mz_zip_dos_to_time_t(int dos_time, int dos_date) {
  struct tm tm;
  memset(&tm, 0, sizeof(tm));
  tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900;
  tm.tm_mon = ((dos_date >> 5) & 15) - 1;
  tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31;
  tm.tm_min = (dos_time >> 5) & 63;
  tm.tm_sec = (dos_time << 1) & 62;
  return mktime(&tm);
}

static void mz_zip_time_to_dos_time(time_t time, mz_uint16 *pDOS_time,
                                    mz_uint16 *pDOS_date) {
#ifdef _MSC_VER
  struct tm tm_struct;
  struct tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  if (err) {
    *pDOS_date = 0;
    *pDOS_time = 0;
    return;
  }
#else
  struct tm *tm = localtime(&time);
#endif
  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) +
                           ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) +
                           ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#endif

#ifndef MINIZ_NO_STDIO
static mz_bool mz_zip_get_file_modified_time(const char *pFilename,
                                             mz_uint16 *pDOS_time,
                                             mz_uint16 *pDOS_date) {
#ifdef MINIZ_NO_TIME
  (void)pFilename;
  *pDOS_date = *pDOS_time = 0;
#else
  struct MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000
  // bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  if (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    return MZ_FALSE;
  mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#endif // #ifdef MINIZ_NO_TIME
  return MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
static mz_bool mz_zip_set_file_times(const char *pFilename, time_t access_time,
                                     time_t modified_time) {
  struct utimbuf t;
  t.actime = access_time;
  t.modtime = modified_time;
  return !utime(pFilename, &t);
}
#endif // #ifndef MINIZ_NO_TIME
#endif // #ifndef MINIZ_NO_STDIO

static mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip,
                                           mz_uint32 flags) {
  (void)flags;
  if ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    return MZ_FALSE;

  if (!pZip->m_pAlloc)
    pZip->m_pAlloc = def_alloc_func;
  if (!pZip->m_pFree)
    pZip->m_pFree = def_free_func;
  if (!pZip->m_pRealloc)
    pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;
  pZip->m_archive_size = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(
                   pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
    return MZ_FALSE;
  memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir,
                                sizeof(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets,
                                sizeof(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets,
                                sizeof(mz_uint32));
  return MZ_TRUE;
}

static MZ_FORCEINLINE mz_bool
mz_zip_reader_filename_less(const mz_zip_array *pCentral_dir_array,
                            const mz_zip_array *pCentral_dir_offsets,
                            mz_uint l_index, mz_uint r_index) {
  const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(
                           pCentral_dir_array, mz_uint8,
                           MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32,
                                                l_index)),
                 *pE;
  const mz_uint8 *pR =
      &MZ_ZIP_ARRAY_ELEMENT(
          pCentral_dir_array, mz_uint8,
          MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_index));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS),
          r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pR += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  while (pL < pE) {
    if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      break;
    pL++;
    pR++;
  }
  return (pL == pE) ? (l_len < r_len) : (l < r);
}

#define MZ_SWAP_UINT32(a, b)                                                   \
  do {                                                                         \
    mz_uint32 t = a;                                                           \
    a = b;                                                                     \
    b = t;                                                                     \
  }                                                                            \
  MZ_MACRO_END

// Heap sort of lowercased filenames, used to help accelerate plain central
// directory searches by mz_zip_reader_locate_file(). (Could also use qsort(),
// but it could allocate memory.)
static void
mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip) {
  mz_zip_internal_state *pState = pZip->m_pState;
  const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  const mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices =
      &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32,
                            0);
  const int size = pZip->m_total_files;
  int start = (size - 2) >> 1, end;
  while (start >= 0) {
    int child, root = start;
    for (;;) {
      if ((child = (root << 1) + 1) >= size)
        break;
      child +=
          (((child + 1) < size) &&
           (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                        pIndices[child], pIndices[child + 1])));
      if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[root], pIndices[child]))
        break;
      MZ_SWAP_UINT32(pIndices[root], pIndices[child]);
      root = child;
    }
    start--;
  }

  end = size - 1;
  while (end > 0) {
    int child, root = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    for (;;) {
      if ((child = (root << 1) + 1) >= end)
        break;
      child +=
          (((child + 1) < end) &&
           mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[child], pIndices[child + 1]));
      if (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets,
                                       pIndices[root], pIndices[child]))
        break;
      MZ_SWAP_UINT32(pIndices[root], pIndices[child]);
      root = child;
    }
    end--;
  }
}

static mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip,
                                              mz_uint32 flags) {
  mz_uint cdir_size, num_this_disk, cdir_disk_index;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  const mz_uint8 *p;
  mz_uint32 buf_u32[4096 / sizeof(mz_uint32)];
  mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir =
      ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first
  // 4 bytes of the file to make sure a local header is there.
  if (pZip->m_archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end
  // towards the beginning.
  cur_file_ofs =
      MZ_MAX((mz_int64)pZip->m_archive_size - (mz_int64)sizeof(buf_u32), 0);
  for (;;) {
    int i,
        n = (int)MZ_MIN(sizeof(buf_u32), pZip->m_archive_size - cur_file_ofs);
    if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      return MZ_FALSE;
    for (i = n - 4; i >= 0; --i)
      if (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
        break;
    if (i >= 0) {
      cur_file_ofs += i;
      break;
    }
    if ((!cur_file_ofs) || ((pZip->m_archive_size - cur_file_ofs) >=
                            (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)))
      return MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (sizeof(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf,
                    MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  if ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) !=
       MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
      ((pZip->m_total_files =
            MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS)) !=
       MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS)))
    return MZ_FALSE;

  num_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_THIS_DISK_OFS);
  cdir_disk_index = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_NUM_DISK_CDIR_OFS);
  if (((num_this_disk | cdir_disk_index) != 0) &&
      ((num_this_disk != 1) || (cdir_disk_index != 1)))
    return MZ_FALSE;

  if ((cdir_size = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_SIZE_OFS)) <
      pZip->m_total_files * MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)
    return MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  if ((cdir_ofs + (mz_uint64)cdir_size) > pZip->m_archive_size)
    return MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  if (pZip->m_total_files) {
    mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another
    // heap block to hold the unsorted central dir file record offsets, and
    // another to hold the sorted indices.
    if ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_size,
                              MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets,
                              pZip->m_total_files, MZ_FALSE)))
      return MZ_FALSE;

    if (sort_central_dir) {
      if (!mz_zip_array_resize(pZip,
                               &pZip->m_pState->m_sorted_central_dir_offsets,
                               pZip->m_total_files, MZ_FALSE))
        return MZ_FALSE;
    }

    if (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs,
                      pZip->m_pState->m_central_dir.m_p,
                      cdir_size) != cdir_size)
      return MZ_FALSE;

    // Now create an index into the central directory file records, do some
    // basic sanity checking on each record, and check for zip64 entries (which
    // are not yet supported).
    p = (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    for (n = cdir_size, i = 0; i < pZip->m_total_files; ++i) {
      mz_uint total_header_size, comp_size, decomp_size, disk_index;
      if ((n < MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) ||
          (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        return MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32,
                           i) =
          (mz_uint32)(p - (const mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      if (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets,
                             mz_uint32, i) = i;
      comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
      decomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
      if (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) &&
           (decomp_size != comp_size)) ||
          (decomp_size && !comp_size) || (decomp_size == 0xFFFFFFFF) ||
          (comp_size == 0xFFFFFFFF))
        return MZ_FALSE;
      disk_index = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      if ((disk_index != num_this_disk) && (disk_index != 1))
        return MZ_FALSE;
      if (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) +
           MZ_ZIP_LOCAL_DIR_HEADER_SIZE + comp_size) > pZip->m_archive_size)
        return MZ_FALSE;
      if ((total_header_size = MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) >
          n)
        return MZ_FALSE;
      n -= total_header_size;
      p += total_header_size;
    }
  }

  if (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  return MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size,
                           mz_uint32 flags) {
  if ((!pZip) || (!pZip->m_pRead))
    return MZ_FALSE;
  if (!mz_zip_reader_init_internal(pZip, flags))
    return MZ_FALSE;
  pZip->m_archive_size = size;
  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end(pZip);
    return MZ_FALSE;
  }
  return MZ_TRUE;
}

static size_t mz_zip_mem_read_func(void *pOpaque, mz_uint64 file_ofs,
                                   void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_size)
                 ? 0
                 : (size_t)MZ_MIN(pZip->m_archive_size - file_ofs, n);
  memcpy(pBuf, (const mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  return s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, const void *pMem,
                               size_t size, mz_uint32 flags) {
  if (!mz_zip_reader_init_internal(pZip, flags))
    return MZ_FALSE;
  pZip->m_archive_size = size;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ifdef __cplusplus
  pZip->m_pState->m_pMem = const_cast<void *>(pMem);
#else
  pZip->m_pState->m_pMem = (void *)pMem;
#endif
  pZip->m_pState->m_mem_size = size;
  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end(pZip);
    return MZ_FALSE;
  }
  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_read_func(void *pOpaque, mz_uint64 file_ofs,
                                    void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  if (((mz_int64)file_ofs < 0) ||
      (((cur_ofs != (mz_int64)file_ofs)) &&
       (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    return 0;
  return MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint32 flags) {
  mz_uint64 file_size;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  if (!pFile)
    return MZ_FALSE;
  if (MZ_FSEEK64(pFile, 0, SEEK_END)) {
    MZ_FCLOSE(pFile);
    return MZ_FALSE;
  }
  file_size = MZ_FTELL64(pFile);
  if (!mz_zip_reader_init_internal(pZip, flags)) {
    MZ_FCLOSE(pFile);
    return MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_size = file_size;
  if (!mz_zip_reader_read_central_dir(pZip, flags)) {
    mz_zip_reader_end(pZip);
    return MZ_FALSE;
  }
  return MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_num_files(mz_zip_archive *pZip) {
  return pZip ? pZip->m_total_files : 0;
}

static MZ_FORCEINLINE const mz_uint8 *
mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_index) {
  if ((!pZip) || (!pZip->m_pState) || (file_index >= pZip->m_total_files) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    return NULL;
  return &MZ_ZIP_ARRAY_ELEMENT(
             &pZip->m_pState->m_central_dir, mz_uint8,
             MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets,
                                  mz_uint32, file_index));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip,
                                        mz_uint file_index) {
  mz_uint m_bit_flag;
  const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  if (!p)
    return MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  return (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip,
                                          mz_uint file_index) {
  mz_uint filename_len, external_attr;
  const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  if (!p)
    return MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  if (filename_len) {
    if (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_len - 1) == '/')
      return MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero,
  // which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the
  // low 16-bits, so check for the DOS directory flag and ignore the source OS
  // ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  if ((external_attr & 0x10) != 0)
    return MZ_TRUE;

  return MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index,
                                mz_zip_archive_file_stat *pStat) {
  mz_uint n;
  const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  if ((!p) || (!pStat))
    return MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_index = file_index;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(
      &pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index);
  pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
  pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#ifndef MINIZ_NO_TIME
  pStat->m_time =
      mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS),
                           MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#endif
  pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
  pStat->m_comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  pStat->m_uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
  pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - 1);
  memcpy(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
  pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE - 1);
  pStat->m_comment_size = n;
  memcpy(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) +
                               MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS),
         n);
  pStat->m_comment[n] = '\0';

  return MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index,
                                   char *pFilename, mz_uint filename_buf_size) {
  mz_uint n;
  const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  if (!p) {
    if (filename_buf_size)
      pFilename[0] = '\0';
    return 0;
  }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  if (filename_buf_size) {
    n = MZ_MIN(n, filename_buf_size - 1);
    memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
    pFilename[n] = '\0';
  }
  return n + 1;
}

static MZ_FORCEINLINE mz_bool
mz_zip_reader_string_equal(const char *pA, const char *pB, mz_uint len,
                           mz_uint flags) {
  mz_uint i;
  if (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    return 0 == memcmp(pA, pB, len);
  for (i = 0; i < len; ++i)
    if (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      return MZ_FALSE;
  return MZ_TRUE;
}

static MZ_FORCEINLINE int
mz_zip_reader_filename_compare(const mz_zip_array *pCentral_dir_array,
                               const mz_zip_array *pCentral_dir_offsets,
                               mz_uint l_index, const char *pR, mz_uint r_len) {
  const mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(
                           pCentral_dir_array, mz_uint8,
                           MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32,
                                                l_index)),
                 *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  while (pL < pE) {
    if ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      break;
    pL++;
    pR++;
  }
  return (pL == pE) ? (int)(l_len - r_len) : (l - r);
}

static int mz_zip_reader_locate_file_binary_search(mz_zip_archive *pZip,
                                                   const char *pFilename) {
  mz_zip_internal_state *pState = pZip->m_pState;
  const mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  const mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices =
      &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32,
                            0);
  const int size = pZip->m_total_files;
  const mz_uint filename_len = (mz_uint)strlen(pFilename);
  int l = 0, h = size - 1;
  while (l <= h) {
    int m = (l + h) >> 1, file_index = pIndices[m],
        comp =
            mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets,
                                           file_index, pFilename, filename_len);
    if (!comp)
      return file_index;
    else if (comp < 0)
      l = m + 1;
    else
      h = m - 1;
  }
  return -1;
}

int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName,
                              const char *pComment, mz_uint flags) {
  mz_uint file_index;
  size_t name_len, comment_len;
  if ((!pZip) || (!pZip->m_pState) || (!pName) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    return -1;
  if (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) &&
      (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_size))
    return mz_zip_reader_locate_file_binary_search(pZip, pName);
  name_len = strlen(pName);
  if (name_len > 0xFFFF)
    return -1;
  comment_len = pComment ? strlen(pComment) : 0;
  if (comment_len > 0xFFFF)
    return -1;
  for (file_index = 0; file_index < pZip->m_total_files; file_index++) {
    const mz_uint8 *pHeader =
        &MZ_ZIP_ARRAY_ELEMENT(
            &pZip->m_pState->m_central_dir, mz_uint8,
            MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets,
                                 mz_uint32, file_index));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    const char *pFilename =
        (const char *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
    if (filename_len < name_len)
      continue;
    if (comment_len) {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS),
              file_comment_len =
                  MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      const char *pFile_comment = pFilename + filename_len + file_extra_len;
      if ((file_comment_len != comment_len) ||
          (!mz_zip_reader_string_equal(pComment, pFile_comment,
                                       file_comment_len, flags)))
        continue;
    }
    if ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len)) {
      int ofs = filename_len - 1;
      do {
        if ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') ||
            (pFilename[ofs] == ':'))
          break;
      } while (--ofs >= 0);
      ofs++;
      pFilename += ofs;
      filename_len -= ofs;
    }
    if ((filename_len == name_len) &&
        (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      return file_index;
  }
  return -1;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip,
                                              mz_uint file_index, void *pBuf,
                                              size_t buf_size, mz_uint flags,
                                              void *pUser_read_buf,
                                              size_t user_read_buf_size) {
  int status = TINFL_STATUS_DONE;
  mz_uint64 needed_size, cur_file_ofs, comp_remaining,
      out_buf_ofs = 0, read_buf_size, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  void *pRead_buf;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  if ((buf_size) && (!pBuf))
    return MZ_FALSE;

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips
  // with directories that have compressed data which inflates to 0 bytes)
  if (!file_stat.m_comp_size)
    return MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have
  // compressed deflate data which inflates to 0 bytes, but these entries claim
  // to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  if (mz_zip_reader_is_file_a_directory(pZip, file_index))
    return MZ_TRUE;

  // Encryption and patch files are not supported.
  if (file_stat.m_bit_flag & (1 | 32))
    return MZ_FALSE;

  // This function only supports stored and deflate.
  if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) &&
      (file_stat.m_method != MZ_DEFLATED))
    return MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size
                                                      : file_stat.m_uncomp_size;
  if (buf_size < needed_size)
    return MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    return MZ_FALSE;

  if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method)) {
    // The file is stored or the caller has requested the compressed data.
    if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf,
                      (size_t)needed_size) != needed_size)
      return MZ_FALSE;
    return ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) != 0) ||
           (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf,
                     (size_t)file_stat.m_uncomp_size) == file_stat.m_crc32);
  }

  // Decompress the file either directly from memory or from a file input
  // buffer.
  tinfl_init(&inflator);

  if (pZip->m_pState->m_pMem) {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  } else if (pUser_read_buf) {
    // Use a user provided read buffer.
    if (!user_read_buf_size)
      return MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_size = user_read_buf_size;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  } else {
    // Temporarily allocate a read buffer.
    read_buf_size = MZ_MIN(file_stat.m_comp_size, (mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE);
#ifdef _MSC_VER
    if (((0, sizeof(size_t) == sizeof(mz_uint32))) &&
        (read_buf_size > 0x7FFFFFFF))
#else
    if (((sizeof(size_t) == sizeof(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#endif
      return MZ_FALSE;
    if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                            (size_t)read_buf_size)))
      return MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  do {
    size_t in_buf_size,
        out_buf_size = (size_t)(file_stat.m_uncomp_size - out_buf_ofs);
    if ((!read_buf_avail) && (!pZip->m_pState->m_pMem)) {
      read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
      if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                        (size_t)read_buf_avail) != read_buf_avail) {
        status = TINFL_STATUS_FAILED;
        break;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_size = (size_t)read_buf_avail;
    status = tinfl_decompress(
        &inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size,
        (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_size,
        TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF |
            (comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0));
    read_buf_avail -= in_buf_size;
    read_buf_ofs += in_buf_size;
    out_buf_ofs += out_buf_size;
  } while (status == TINFL_STATUS_NEEDS_MORE_INPUT);

  if (status == TINFL_STATUS_DONE) {
    // Make sure the entire file was decompressed, and check its CRC.
    if ((out_buf_ofs != file_stat.m_uncomp_size) ||
        (mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf,
                  (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  if ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  return status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(
    mz_zip_archive *pZip, const char *pFilename, void *pBuf, size_t buf_size,
    mz_uint flags, void *pUser_read_buf, size_t user_read_buf_size) {
  int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
  if (file_index < 0)
    return MZ_FALSE;
  return mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size,
                                               flags, pUser_read_buf,
                                               user_read_buf_size);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index,
                                     void *pBuf, size_t buf_size,
                                     mz_uint flags) {
  return mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size,
                                               flags, NULL, 0);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip,
                                          const char *pFilename, void *pBuf,
                                          size_t buf_size, mz_uint flags) {
  return mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf,
                                                    buf_size, flags, NULL, 0);
}

void *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index,
                                    size_t *pSize, mz_uint flags) {
  mz_uint64 comp_size, uncomp_size, alloc_size;
  const mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  void *pBuf;

  if (pSize)
    *pSize = 0;
  if (!p)
    return NULL;

  comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);

  alloc_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? comp_size : uncomp_size;
#ifdef _MSC_VER
  if (((0, sizeof(size_t) == sizeof(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#else
  if (((sizeof(size_t) == sizeof(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#endif
    return NULL;
  if (NULL ==
      (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_size)))
    return NULL;

  if (!mz_zip_reader_extract_to_mem(pZip, file_index, pBuf, (size_t)alloc_size,
                                    flags)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    return NULL;
  }

  if (pSize)
    *pSize = (size_t)alloc_size;
  return pBuf;
}

void *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip,
                                         const char *pFilename, size_t *pSize,
                                         mz_uint flags) {
  int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
  if (file_index < 0) {
    if (pSize)
      *pSize = 0;
    return MZ_FALSE;
  }
  return mz_zip_reader_extract_to_heap(pZip, file_index, pSize, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip,
                                          mz_uint file_index,
                                          mz_file_write_func pCallback,
                                          void *pOpaque, mz_uint flags) {
  int status = TINFL_STATUS_DONE;
  mz_uint file_crc32 = MZ_CRC32_INIT;
  mz_uint64 read_buf_size, read_buf_ofs = 0, read_buf_avail, comp_remaining,
                           out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  void *pRead_buf = NULL;
  void *pWrite_buf = NULL;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips
  // with directories that have compressed data which inflates to 0 bytes)
  if (!file_stat.m_comp_size)
    return MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have
  // compressed deflate data which inflates to 0 bytes, but these entries claim
  // to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  if (mz_zip_reader_is_file_a_directory(pZip, file_index))
    return MZ_TRUE;

  // Encryption and patch files are not supported.
  if (file_stat.m_bit_flag & (1 | 32))
    return MZ_FALSE;

  // This function only supports stored and deflate.
  if ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) &&
      (file_stat.m_method != MZ_DEFLATED))
    return MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header,
                    MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
                  MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  if ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    return MZ_FALSE;

  // Decompress the file either directly from memory or from a file input
  // buffer.
  if (pZip->m_pState->m_pMem) {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  } else {
    read_buf_size = MZ_MIN(file_stat.m_comp_size, (mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE);
    if (NULL == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                            (size_t)read_buf_size)))
      return MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  if ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method)) {
    // The file is stored or the caller has requested the compressed data.
    if (pZip->m_pState->m_pMem) {
#ifdef _MSC_VER
      if (((0, sizeof(size_t) == sizeof(mz_uint32))) &&
          (file_stat.m_comp_size > 0xFFFFFFFF))
#else
      if (((sizeof(size_t) == sizeof(mz_uint32))) &&
          (file_stat.m_comp_size > 0xFFFFFFFF))
#endif
        return MZ_FALSE;
      if (pCallback(pOpaque, out_buf_ofs, pRead_buf,
                    (size_t)file_stat.m_comp_size) != file_stat.m_comp_size)
        status = TINFL_STATUS_FAILED;
      else if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
        file_crc32 =
            (mz_uint32)mz_crc32(file_crc32, (const mz_uint8 *)pRead_buf,
                                (size_t)file_stat.m_comp_size);
      cur_file_ofs += file_stat.m_comp_size;
      out_buf_ofs += file_stat.m_comp_size;
      comp_remaining = 0;
    } else {
      while (comp_remaining) {
        read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
        if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                          (size_t)read_buf_avail) != read_buf_avail) {
          status = TINFL_STATUS_FAILED;
          break;
        }

        if (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
          file_crc32 = (mz_uint32)mz_crc32(
              file_crc32, (const mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        if (pCallback(pOpaque, out_buf_ofs, pRead_buf,
                      (size_t)read_buf_avail) != read_buf_avail) {
          status = TINFL_STATUS_FAILED;
          break;
        }
        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  } else {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    if (NULL == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                                             TINFL_LZ_DICT_SIZE)))
      status = TINFL_STATUS_FAILED;
    else {
      do {
        mz_uint8 *pWrite_buf_cur =
            (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        size_t in_buf_size,
            out_buf_size =
                TINFL_LZ_DICT_SIZE - (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        if ((!read_buf_avail) && (!pZip->m_pState->m_pMem)) {
          read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
          if (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf,
                            (size_t)read_buf_avail) != read_buf_avail) {
            status = TINFL_STATUS_FAILED;
            break;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_size = (size_t)read_buf_avail;
        status = tinfl_decompress(
            &inflator, (const mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size,
            (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_size,
            comp_remaining ? TINFL_FLAG_HAS_MORE_INPUT : 0);
        read_buf_avail -= in_buf_size;
        read_buf_ofs += in_buf_size;

        if (out_buf_size) {
          if (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_size) !=
              out_buf_size) {
            status = TINFL_STATUS_FAILED;
            break;
          }
          file_crc32 =
              (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_size);
          if ((out_buf_ofs += out_buf_size) > file_stat.m_uncomp_size) {
            status = TINFL_STATUS_FAILED;
            break;
          }
        }
      } while ((status == TINFL_STATUS_NEEDS_MORE_INPUT) ||
               (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  if ((status == TINFL_STATUS_DONE) &&
      (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))) {
    // Make sure the entire file was decompressed, and check its CRC.
    if ((out_buf_ofs != file_stat.m_uncomp_size) ||
        (file_crc32 != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  if (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  if (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  return status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip,
                                               const char *pFilename,
                                               mz_file_write_func pCallback,
                                               void *pOpaque, mz_uint flags) {
  int file_index = mz_zip_reader_locate_file(pZip, pFilename, NULL, flags);
  if (file_index < 0)
    return MZ_FALSE;
  return mz_zip_reader_extract_to_callback(pZip, file_index, pCallback, pOpaque,
                                           flags);
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_write_callback(void *pOpaque, mz_uint64 ofs,
                                         const void *pBuf, size_t n) {
  (void)ofs;
  return MZ_FWRITE(pBuf, 1, n, (MZ_FILE *)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index,
                                      const char *pDst_filename,
                                      mz_uint flags) {
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  if (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    return MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  if (!pFile)
    return MZ_FALSE;
  status = mz_zip_reader_extract_to_callback(
      pZip, file_index, mz_zip_file_write_callback, pFile, flags);
  if (MZ_FCLOSE(pFile) == EOF)
    return MZ_FALSE;
#ifndef MINIZ_NO_TIME
  if (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif
  return status;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_end(mz_zip_archive *pZip) {
  if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    return MZ_FALSE;

  if (pZip->m_pState) {
    mz_zip_internal_state *pState = pZip->m_pState;
    pZip->m_pState = NULL;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
    if (pState->m_pFile) {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = NULL;
    }
#endif // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip,
                                           const char *pArchive_filename,
                                           const char *pDst_filename,
                                           mz_uint flags) {
  int file_index =
      mz_zip_reader_locate_file(pZip, pArchive_filename, NULL, flags);
  if (file_index < 0)
    return MZ_FALSE;
  return mz_zip_reader_extract_to_file(pZip, file_index, pDst_filename, flags);
}
#endif

// ------------------- .ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

static void mz_write_le16(mz_uint8 *p, mz_uint16 v) {
  p[0] = (mz_uint8)v;
  p[1] = (mz_uint8)(v >> 8);
}
static void mz_write_le32(mz_uint8 *p, mz_uint32 v) {
  p[0] = (mz_uint8)v;
  p[1] = (mz_uint8)(v >> 8);
  p[2] = (mz_uint8)(v >> 16);
  p[3] = (mz_uint8)(v >> 24);
}
#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size) {
  if ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    return MZ_FALSE;

  if (pZip->m_file_offset_alignment) {
    // Ensure user specified file offset alignment is a power of 2.
    if (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      return MZ_FALSE;
  }

  if (!pZip->m_pAlloc)
    pZip->m_pAlloc = def_alloc_func;
  if (!pZip->m_pFree)
    pZip->m_pFree = def_free_func;
  if (!pZip->m_pRealloc)
    pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_archive_size = existing_size;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  if (NULL == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(
                   pZip->m_pAlloc_opaque, 1, sizeof(mz_zip_internal_state))))
    return MZ_FALSE;
  memset(pZip->m_pState, 0, sizeof(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir,
                                sizeof(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets,
                                sizeof(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets,
                                sizeof(mz_uint32));
  return MZ_TRUE;
}

static size_t mz_zip_heap_write_func(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_size = MZ_MAX(file_ofs + n, pState->m_mem_size);
#ifdef _MSC_VER
  if ((!n) ||
      ((0, sizeof(size_t) == sizeof(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#else
  if ((!n) ||
      ((sizeof(size_t) == sizeof(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#endif
    return 0;
  if (new_size > pState->m_mem_capacity) {
    void *pNew_block;
    size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity);
    while (new_capacity < new_size)
      new_capacity *= 2;
    if (NULL == (pNew_block = pZip->m_pRealloc(
                     pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
      return 0;
    pState->m_pMem = pNew_block;
    pState->m_mem_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_size = (size_t)new_size;
  return n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip,
                                size_t size_to_reserve_at_beginning,
                                size_t initial_allocation_size) {
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  if (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    return MZ_FALSE;
  if (0 != (initial_allocation_size = MZ_MAX(initial_allocation_size,
                                             size_to_reserve_at_beginning))) {
    if (NULL == (pZip->m_pState->m_pMem = pZip->m_pAlloc(
                     pZip->m_pAlloc_opaque, 1, initial_allocation_size))) {
      mz_zip_writer_end(pZip);
      return MZ_FALSE;
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_size;
  }
  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
static size_t mz_zip_file_write_func(void *pOpaque, mz_uint64 file_ofs,
                                     const void *pBuf, size_t n) {
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  if (((mz_int64)file_ofs < 0) ||
      (((cur_ofs != (mz_int64)file_ofs)) &&
       (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    return 0;
  return MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, const char *pFilename,
                                mz_uint64 size_to_reserve_at_beginning) {
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  if (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    return MZ_FALSE;
  if (NULL == (pFile = MZ_FOPEN(pFilename, "wb"))) {
    mz_zip_writer_end(pZip);
    return MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  if (size_to_reserve_at_beginning) {
    mz_uint64 cur_ofs = 0;
    char buf[4096];
    MZ_CLEAR_OBJ(buf);
    do {
      size_t n = (size_t)MZ_MIN(sizeof(buf), size_to_reserve_at_beginning);
      if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n) {
        mz_zip_writer_end(pZip);
        return MZ_FALSE;
      }
      cur_ofs += n;
      size_to_reserve_at_beginning -= n;
    } while (size_to_reserve_at_beginning);
  }
  return MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip,
                                       const char *pFilename) {
  mz_zip_internal_state *pState;
  if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    return MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max
  // size
  if ((pZip->m_total_files == 0xFFFF) ||
      ((pZip->m_archive_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
        MZ_ZIP_LOCAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    return MZ_FALSE;

  pState = pZip->m_pState;

  if (pState->m_pFile) {
#ifdef MINIZ_NO_STDIO
    pFilename;
    return MZ_FALSE;
#else
    // Archive is being read from stdio - try to reopen as writable.
    if (pZip->m_pIO_opaque != pZip)
      return MZ_FALSE;
    if (!pFilename)
      return MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    if (NULL ==
        (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile))) {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is
      // NULL, so just close it.
      mz_zip_reader_end(pZip);
      return MZ_FALSE;
    }
#endif // #ifdef MINIZ_NO_STDIO
  } else if (pState->m_pMem) {
    // Archive lives in a memory block. Assume it's from the heap that we can
    // resize using the realloc callback.
    if (pZip->m_pIO_opaque != pZip)
      return MZ_FALSE;
    pState->m_mem_capacity = pState->m_mem_size;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the
  // user has specified a write function too.
  else if (!pZip->m_pWrite)
    return MZ_FALSE;

  // Start writing new files at the archive's current central directory
  // location.
  pZip->m_archive_size = pZip->m_central_directory_file_ofs;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, const char *pArchive_name,
                              const void *pBuf, size_t buf_size,
                              mz_uint level_and_flags) {
  return mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_size, NULL, 0,
                                  level_and_flags, 0, 0);
}

typedef struct {
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_size;
} mz_zip_writer_add_state;

static mz_bool mz_zip_writer_add_put_buf_callback(const void *pBuf, int len,
                                                  void *pUser) {
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  if ((int)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque,
                                    pState->m_cur_archive_file_ofs, pBuf,
                                    len) != len)
    return MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_size += len;
  return MZ_TRUE;
}

static mz_bool mz_zip_writer_create_local_dir_header(
    mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size,
    mz_uint16 extra_size, mz_uint64 uncomp_size, mz_uint64 comp_size,
    mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags,
    mz_uint16 dos_time, mz_uint16 dos_date) {
  (void)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS, comp_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_size);
  return MZ_TRUE;
}

static mz_bool mz_zip_writer_create_central_dir_header(
    mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size,
    mz_uint16 extra_size, mz_uint16 comment_size, mz_uint64 uncomp_size,
    mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method,
    mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date,
    mz_uint64 local_header_ofs, mz_uint32 ext_attributes) {
  (void)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS, comp_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_header_ofs);
  return MZ_TRUE;
}

static mz_bool mz_zip_writer_add_to_central_dir(
    mz_zip_archive *pZip, const char *pFilename, mz_uint16 filename_size,
    const void *pExtra, mz_uint16 extra_size, const void *pComment,
    mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size,
    mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags,
    mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs,
    mz_uint32 ext_attributes) {
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_size;
  size_t orig_central_dir_size = pState->m_central_dir.m_size;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];

  // No zip64 support yet
  if ((local_header_ofs > 0xFFFFFFFF) ||
      (((mz_uint64)pState->m_central_dir.m_size +
        MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + extra_size +
        comment_size) > 0xFFFFFFFF))
    return MZ_FALSE;

  if (!mz_zip_writer_create_central_dir_header(
          pZip, central_dir_header, filename_size, extra_size, comment_size,
          uncomp_size, comp_size, uncomp_crc32, method, bit_flags, dos_time,
          dos_date, local_header_ofs, ext_attributes))
    return MZ_FALSE;

  if ((!mz_zip_array_push_back(pZip, &pState->m_central_dir, central_dir_header,
                               MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pFilename,
                               filename_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pExtra,
                               extra_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir, pComment,
                               comment_size)) ||
      (!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets,
                               &central_dir_ofs, 1))) {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return MZ_FALSE;
  }

  return MZ_TRUE;
}

static mz_bool mz_zip_writer_validate_archive_name(const char *pArchive_name) {
  // Basic ZIP archive filename validity checks: Valid filenames cannot start
  // with a forward slash, cannot contain a drive letter, and cannot use
  // DOS-style backward slashes.
  if (*pArchive_name == '/')
    return MZ_FALSE;
  while (*pArchive_name) {
    if ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      return MZ_FALSE;
    pArchive_name++;
  }
  return MZ_TRUE;
}

static mz_uint
mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip) {
  mz_uint32 n;
  if (!pZip->m_file_offset_alignment)
    return 0;
  n = (mz_uint32)(pZip->m_archive_size & (pZip->m_file_offset_alignment - 1));
  return (pZip->m_file_offset_alignment - n) &
         (pZip->m_file_offset_alignment - 1);
}

static mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip,
                                         mz_uint64 cur_file_ofs, mz_uint32 n) {
  char buf[4096];
  memset(buf, 0, MZ_MIN(sizeof(buf), n));
  while (n) {
    mz_uint32 s = MZ_MIN(sizeof(buf), n);
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      return MZ_FALSE;
    cur_file_ofs += s;
    n -= s;
  }
  return MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip,
                                 const char *pArchive_name, const void *pBuf,
                                 size_t buf_size, const void *pComment,
                                 mz_uint16 comment_size,
                                 mz_uint level_and_flags, mz_uint64 uncomp_size,
                                 mz_uint32 uncomp_crc32) {
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, num_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size,
            cur_archive_file_ofs = pZip->m_archive_size, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  tdefl_compressor *pComp = NULL;
  mz_bool store_data_uncompressed;
  mz_zip_internal_state *pState;

  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_data_uncompressed =
      ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA));

  if ((!pZip) || (!pZip->m_pState) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_size) && (!pBuf)) ||
      (!pArchive_name) || ((comment_size) && (!pComment)) ||
      (pZip->m_total_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    return MZ_FALSE;

  pState = pZip->m_pState;

  if ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (uncomp_size))
    return MZ_FALSE;
  // No zip64 support yet
  if ((buf_size > 0xFFFFFFFF) || (uncomp_size > 0xFFFFFFFF))
    return MZ_FALSE;
  if (!mz_zip_writer_validate_archive_name(pArchive_name))
    return MZ_FALSE;

#ifndef MINIZ_NO_TIME
  {
    time_t cur_time;
    time(&cur_time);
    mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#endif // #ifndef MINIZ_NO_TIME

  archive_name_size = strlen(pArchive_name);
  if (archive_name_size > 0xFFFF)
    return MZ_FALSE;

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  if ((pZip->m_total_files == 0xFFFF) ||
      ((pZip->m_archive_size + num_alignment_padding_bytes +
        MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
        comment_size + archive_name_size) > 0xFFFFFFFF))
    return MZ_FALSE;

  if ((archive_name_size) && (pArchive_name[archive_name_size - 1] == '/')) {
    // Set DOS Subdirectory attribute bit.
    ext_attributes |= 0x10;
    // Subdirectories cannot contain data.
    if ((buf_size) || (uncomp_size))
      return MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an
  // allocation fails the file remains unmodified. (A good idea if we're doing
  // an in-place modification.)
  if ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir,
                                 MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
                                     archive_name_size + comment_size)) ||
      (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    return MZ_FALSE;

  if ((!store_data_uncompressed) && (buf_size)) {
    if (NULL == (pComp = (tdefl_compressor *)pZip->m_pAlloc(
                     pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor))))
      return MZ_FALSE;
  }

  if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs,
                                 num_alignment_padding_bytes +
                                     sizeof(local_dir_header))) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    return MZ_FALSE;
  }
  local_dir_header_ofs += num_alignment_padding_bytes;
  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }
  cur_archive_file_ofs +=
      num_alignment_padding_bytes + sizeof(local_dir_header);

  MZ_CLEAR_OBJ(local_dir_header);
  if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                     archive_name_size) != archive_name_size) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    return MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  if (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) {
    uncomp_crc32 =
        (mz_uint32)mz_crc32(MZ_CRC32_INIT, (const mz_uint8 *)pBuf, buf_size);
    uncomp_size = buf_size;
    if (uncomp_size <= 3) {
      level = 0;
      store_data_uncompressed = MZ_TRUE;
    }
  }

  if (store_data_uncompressed) {
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf,
                       buf_size) != buf_size) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return MZ_FALSE;
    }

    cur_archive_file_ofs += buf_size;
    comp_size = buf_size;

    if (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
      method = MZ_DEFLATED;
  } else if (buf_size) {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_size = 0;

    if ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state,
                    tdefl_create_comp_flags_from_zip_params(
                        level, -15, MZ_DEFAULT_STRATEGY)) !=
         TDEFL_STATUS_OKAY) ||
        (tdefl_compress_buffer(pComp, pBuf, buf_size, TDEFL_FINISH) !=
         TDEFL_STATUS_DONE)) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      return MZ_FALSE;
    }

    comp_size = state.m_comp_size;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    method = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = NULL;

  // no zip64 support yet
  if ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    return MZ_FALSE;

  if (!mz_zip_writer_create_local_dir_header(
          pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size,
          comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    return MZ_FALSE;

  if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header,
                     sizeof(local_dir_header)) != sizeof(local_dir_header))
    return MZ_FALSE;

  if (!mz_zip_writer_add_to_central_dir(
          pZip, pArchive_name, (mz_uint16)archive_name_size, NULL, 0, pComment,
          comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0,
          dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    return MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  return MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, const char *pArchive_name,
                               const char *pSrc_filename, const void *pComment,
                               mz_uint16 comment_size,
                               mz_uint level_and_flags) {
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, num_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size,
            cur_archive_file_ofs = pZip->m_archive_size, uncomp_size = 0,
            comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  MZ_FILE *pSrc_file = NULL;

  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  if ((!pZip) || (!pZip->m_pState) ||
      (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) ||
      ((comment_size) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    return MZ_FALSE;
  if (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
    return MZ_FALSE;
  if (!mz_zip_writer_validate_archive_name(pArchive_name))
    return MZ_FALSE;

  archive_name_size = strlen(pArchive_name);
  if (archive_name_size > 0xFFFF)
    return MZ_FALSE;

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  if ((pZip->m_total_files == 0xFFFF) ||
      ((pZip->m_archive_size + num_alignment_padding_bytes +
        MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE +
        comment_size + archive_name_size) > 0xFFFFFFFF))
    return MZ_FALSE;

  if (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    return MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  if (!pSrc_file)
    return MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_size = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  if (uncomp_size > 0xFFFFFFFF) {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    return MZ_FALSE;
  }
  if (uncomp_size <= 3)
    level = 0;

  if (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs,
                                 num_alignment_padding_bytes +
                                     sizeof(local_dir_header))) {
    MZ_FCLOSE(pSrc_file);
    return MZ_FALSE;
  }
  local_dir_header_ofs += num_alignment_padding_bytes;
  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }
  cur_archive_file_ofs +=
      num_alignment_padding_bytes + sizeof(local_dir_header);

  MZ_CLEAR_OBJ(local_dir_header);
  if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name,
                     archive_name_size) != archive_name_size) {
    MZ_FCLOSE(pSrc_file);
    return MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  if (uncomp_size) {
    mz_uint64 uncomp_remaining = uncomp_size;
    void *pRead_buf =
        pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_SIZE);
    if (!pRead_buf) {
      MZ_FCLOSE(pSrc_file);
      return MZ_FALSE;
    }

    if (!level) {
      while (uncomp_remaining) {
        mz_uint n = (mz_uint)MZ_MIN((mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE, uncomp_remaining);
        if ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) ||
            (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf,
                            n) != n)) {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          return MZ_FALSE;
        }
        uncomp_crc32 =
            (mz_uint32)mz_crc32(uncomp_crc32, (const mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_size = uncomp_size;
    } else {
      mz_bool result = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(
          pZip->m_pAlloc_opaque, 1, sizeof(tdefl_compressor));
      if (!pComp) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        return MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_size = 0;

      if (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state,
                     tdefl_create_comp_flags_from_zip_params(
                         level, -15, MZ_DEFAULT_STRATEGY)) !=
          TDEFL_STATUS_OKAY) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        return MZ_FALSE;
      }

      for (;;) {
        size_t in_buf_size =
            (mz_uint32)MZ_MIN(uncomp_remaining, (mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE);
        tdefl_status status;

        if (MZ_FREAD(pRead_buf, 1, in_buf_size, pSrc_file) != in_buf_size)
          break;

        uncomp_crc32 = (mz_uint32)mz_crc32(
            uncomp_crc32, (const mz_uint8 *)pRead_buf, in_buf_size);
        uncomp_remaining -= in_buf_size;

        status = tdefl_compress_buffer(pComp, pRead_buf, in_buf_size,
                                       uncomp_remaining ? TDEFL_NO_FLUSH
                                                        : TDEFL_FINISH);
        if (status == TDEFL_STATUS_DONE) {
          result = MZ_TRUE;
          break;
        } else if (status != TDEFL_STATUS_OKAY)
          break;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      if (!result) {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        return MZ_FALSE;
      }

      comp_size = state.m_comp_size;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      method = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file);
  pSrc_file = NULL;

  // no zip64 support yet
  if ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    return MZ_FALSE;

  if (!mz_zip_writer_create_local_dir_header(
          pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size,
          comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    return MZ_FALSE;

  if (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header,
                     sizeof(local_dir_header)) != sizeof(local_dir_header))
    return MZ_FALSE;

  if (!mz_zip_writer_add_to_central_dir(
          pZip, pArchive_name, (mz_uint16)archive_name_size, NULL, 0, pComment,
          comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0,
          dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    return MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  return MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip,
                                          mz_zip_archive *pSource_zip,
                                          mz_uint file_index) {
  mz_uint n, bit_flags, num_alignment_padding_bytes;
  mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32
      local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + sizeof(mz_uint32) - 1) /
                       sizeof(mz_uint32)];
  mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];
  size_t orig_central_dir_size;
  mz_zip_internal_state *pState;
  void *pBuf;
  const mz_uint8 *pSrc_central_header;

  if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    return MZ_FALSE;
  if (NULL ==
      (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_index)))
    return MZ_FALSE;
  pState = pZip->m_pState;

  num_alignment_padding_bytes =
      mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  if ((pZip->m_total_files == 0xFFFF) ||
      ((pZip->m_archive_size + num_alignment_padding_bytes +
        MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) >
       0xFFFFFFFF))
    return MZ_FALSE;

  cur_src_file_ofs =
      MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
  cur_dst_file_ofs = pZip->m_archive_size;

  if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs,
                           pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  if (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    return MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  if (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs,
                                 num_alignment_padding_bytes))
    return MZ_FALSE;
  cur_dst_file_ofs += num_alignment_padding_bytes;
  local_dir_header_ofs = cur_dst_file_ofs;
  if (pZip->m_file_offset_alignment) {
    MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) ==
              0);
  }

  if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header,
                     MZ_ZIP_LOCAL_DIR_HEADER_SIZE) !=
      MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    return MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) +
      MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_bytes_remaining =
      n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);

  if (NULL ==
      (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1,
                             (size_t)MZ_MAX(sizeof(mz_uint32) * 4,
                                            MZ_MIN((mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE,
                                                   comp_bytes_remaining)))))
    return MZ_FALSE;

  while (comp_bytes_remaining) {
    n = (mz_uint)MZ_MIN((mz_uint)MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining);
    if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf,
                             n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return MZ_FALSE;
    }
    cur_src_file_ofs += n;

    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_bytes_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  if (bit_flags & 8) {
    // Copy data descriptor
    if (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf,
                             sizeof(mz_uint32) * 4) != sizeof(mz_uint32) * 4) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return MZ_FALSE;
    }

    n = sizeof(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    if (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n) {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      return MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  if (cur_dst_file_ofs > 0xFFFFFFFF)
    return MZ_FALSE;

  orig_central_dir_size = pState->m_central_dir.m_size;

  memcpy(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS,
                local_dir_header_ofs);
  if (!mz_zip_array_push_back(pZip, &pState->m_central_dir, central_header,
                              MZ_ZIP_CENTRAL_DIR_HEADER_SIZE))
    return MZ_FALSE;

  n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) +
      MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) +
      MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  if (!mz_zip_array_push_back(
          pZip, &pState->m_central_dir,
          pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n)) {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return MZ_FALSE;
  }

  if (pState->m_central_dir.m_size > 0xFFFFFFFF)
    return MZ_FALSE;
  n = (mz_uint32)orig_central_dir_size;
  if (!mz_zip_array_push_back(pZip, &pState->m_central_dir_offsets, &n, 1)) {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size,
                        MZ_FALSE);
    return MZ_FALSE;
  }

  pZip->m_total_files++;
  pZip->m_archive_size = cur_dst_file_ofs;

  return MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip) {
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_size;
  mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE];

  if ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    return MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  if ((pZip->m_total_files > 0xFFFF) ||
      ((pZip->m_archive_size + pState->m_central_dir.m_size +
        MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    return MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_size = 0;
  if (pZip->m_total_files) {
    // Write central directory
    central_dir_ofs = pZip->m_archive_size;
    central_dir_size = pState->m_central_dir.m_size;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    if (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs,
                       pState->m_central_dir.m_p,
                       (size_t)central_dir_size) != central_dir_size)
      return MZ_FALSE;
    pZip->m_archive_size += central_dir_size;
  }

  // Write end of central directory record
  MZ_CLEAR_OBJ(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS,
                MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_NUM_ENTRIES_ON_DISK_OFS,
                pZip->m_total_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS, pZip->m_total_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_SIZE_OFS, central_dir_size);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  if (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr,
                     sizeof(hdr)) != sizeof(hdr))
    return MZ_FALSE;
#ifndef MINIZ_NO_STDIO
  if ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    return MZ_FALSE;
#endif // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_size += sizeof(hdr);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  return MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, void **pBuf,
                                            size_t *pSize) {
  if ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!pSize))
    return MZ_FALSE;
  if (pZip->m_pWrite != mz_zip_heap_write_func)
    return MZ_FALSE;
  if (!mz_zip_writer_finalize_archive(pZip))
    return MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *pSize = pZip->m_pState->m_mem_size;
  pZip->m_pState->m_pMem = NULL;
  pZip->m_pState->m_mem_size = pZip->m_pState->m_mem_capacity = 0;
  return MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip) {
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;
  if ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) ||
      ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) &&
       (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
    return MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = NULL;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
  if (pState->m_pFile) {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = NULL;
  }
#endif // #ifndef MINIZ_NO_STDIO

  if ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem)) {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = NULL;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  return status;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(
    const char *pZip_filename, const char *pArchive_name, const void *pBuf,
    size_t buf_size, const void *pComment, mz_uint16 comment_size,
    mz_uint level_and_flags) {
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  struct MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  if ((int)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  if ((!pZip_filename) || (!pArchive_name) || ((buf_size) && (!pBuf)) ||
      ((comment_size) && (!pComment)) ||
      ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    return MZ_FALSE;
  if (!mz_zip_writer_validate_archive_name(pArchive_name))
    return MZ_FALSE;
  if (MZ_FILE_STAT(pZip_filename, &file_stat) != 0) {
    // Create a new archive.
    if (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      return MZ_FALSE;
    created_new_archive = MZ_TRUE;
  } else {
    // Append to an existing archive.
    if (!mz_zip_reader_init_file(&zip_archive, pZip_filename,
                                 level_and_flags |
                                     MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
      return MZ_FALSE;
    if (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename)) {
      mz_zip_reader_end(&zip_archive);
      return MZ_FALSE;
    }
  }
  status =
      mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_size,
                               pComment, comment_size, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid
  // central directory. (This may not always succeed, but we can try.)
  if (!mz_zip_writer_finalize_archive(&zip_archive))
    status = MZ_FALSE;
  if (!mz_zip_writer_end(&zip_archive))
    status = MZ_FALSE;
  if ((!status) && (created_new_archive)) {
    // It's a new archive and something went wrong, so just delete it.
    int ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (void)ignoredStatus;
  }
  return status;
}

void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename,
                                          const char *pArchive_name,
                                          size_t *pSize, mz_uint flags) {
  int file_index;
  mz_zip_archive zip_archive;
  void *p = NULL;

  if (pSize)
    *pSize = 0;

  if ((!pZip_filename) || (!pArchive_name))
    return NULL;

  MZ_CLEAR_OBJ(zip_archive);
  if (!mz_zip_reader_init_file(&zip_archive, pZip_filename,
                               flags |
                                   MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
    return NULL;

  if ((file_index = mz_zip_reader_locate_file(&zip_archive, pArchive_name, NULL,
                                              flags)) >= 0)
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_index, pSize, flags);

  mz_zip_reader_end(&zip_archive);
  return p;
}

#endif // #ifndef MINIZ_NO_STDIO

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_FILE_ONLY

/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/

// ---------------------- end of miniz ----------------------------------------
}

bool IsBigEndian(void) {
  union {
    unsigned int i;
    char c[4];
  } bint = {0x01020304};

  return bint.c[0] == 1;
}

void swap2(unsigned short *val) {
  unsigned short tmp = *val;
  unsigned char *dst = (unsigned char *)val;
  unsigned char *src = (unsigned char *)&tmp;

  dst[0] = src[1];
  dst[1] = src[0];
}

void swap4(unsigned int *val) {
  unsigned int tmp = *val;
  unsigned char *dst = (unsigned char *)val;
  unsigned char *src = (unsigned char *)&tmp;

  dst[0] = src[3];
  dst[1] = src[2];
  dst[2] = src[1];
  dst[3] = src[0];
}

void swap8(unsigned long long *val) {
  unsigned long long tmp = (*val);
  unsigned char *dst = (unsigned char *)val;
  unsigned char *src = (unsigned char *)&tmp;

  dst[0] = src[7];
  dst[1] = src[6];
  dst[2] = src[5];
  dst[3] = src[4];
  dst[4] = src[3];
  dst[5] = src[2];
  dst[6] = src[1];
  dst[7] = src[0];
}

// https://gist.github.com/rygorous/2156668
// Reuse MINIZ_LITTLE_ENDIAN flag from miniz.
union FP32 {
  unsigned int u;
  float f;
  struct {
#if MINIZ_LITTLE_ENDIAN
    unsigned int Mantissa : 23;
    unsigned int Exponent : 8;
    unsigned int Sign : 1;
#else
    unsigned int Sign : 1;
    unsigned int Exponent : 8;
    unsigned int Mantissa : 23;
#endif
  } s;
};

union FP16 {
  unsigned short u;
  struct {
#if MINIZ_LITTLE_ENDIAN
    unsigned int Mantissa : 10;
    unsigned int Exponent : 5;
    unsigned int Sign : 1;
#else
    unsigned int Sign : 1;
    unsigned int Exponent : 5;
    unsigned int Mantissa : 10;
#endif
  } s;
};

FP32 half_to_float(FP16 h) {
  static const FP32 magic = {113 << 23};
  static const unsigned int shifted_exp = 0x7c00
                                          << 13; // exponent mask after shift
  FP32 o;

  o.u = (h.u & 0x7fff) << 13;            // exponent/mantissa bits
  unsigned int exp_ = shifted_exp & o.u; // just the exponent
  o.u += (127 - 15) << 23;               // exponent adjust

  // handle exponent special cases
  if (exp_ == shifted_exp)   // Inf/NaN?
    o.u += (128 - 16) << 23; // extra exp adjust
  else if (exp_ == 0)        // Zero/Denormal?
  {
    o.u += 1 << 23; // extra exp adjust
    o.f -= magic.f; // renormalize
  }

  o.u |= (h.u & 0x8000) << 16; // sign bit
  return o;
}

FP16 float_to_half_full(FP32 f) {
  FP16 o = {0};

  // Based on ISPC reference code (with minor modifications)
  if (f.s.Exponent == 0) // Signed zero/denormal (which will underflow)
    o.s.Exponent = 0;
  else if (f.s.Exponent == 255) // Inf or NaN (all exponent bits set)
  {
    o.s.Exponent = 31;
    o.s.Mantissa = f.s.Mantissa ? 0x200 : 0; // NaN->qNaN and Inf->Inf
  } else                                     // Normalized number
  {
    // Exponent unbias the single, then bias the halfp
    int newexp = f.s.Exponent - 127 + 15;
    if (newexp >= 31) // Overflow, return signed infinity
      o.s.Exponent = 31;
    else if (newexp <= 0) // Underflow
    {
      if ((14 - newexp) <= 24) // Mantissa might be non-zero
      {
        unsigned int mant = f.s.Mantissa | 0x800000; // Hidden 1 bit
        o.s.Mantissa = mant >> (14 - newexp);
        if ((mant >> (13 - newexp)) & 1) // Check for rounding
          o.u++; // Round, might overflow into exp bit, but this is OK
      }
    } else {
      o.s.Exponent = newexp;
      o.s.Mantissa = f.s.Mantissa >> 13;
      if (f.s.Mantissa & 0x1000) // Check for rounding
        o.u++;                   // Round, might overflow to inf, this is OK
    }
  }

  o.s.Sign = f.s.Sign;
  return o;
}

// NOTE: From OpenEXR code
// #define IMF_INCREASING_Y  0
// #define IMF_DECREASING_Y  1
// #define IMF_RAMDOM_Y    2
//
// #define IMF_NO_COMPRESSION  0
// #define IMF_RLE_COMPRESSION 1
// #define IMF_ZIPS_COMPRESSION  2
// #define IMF_ZIP_COMPRESSION 3
// #define IMF_PIZ_COMPRESSION 4
// #define IMF_PXR24_COMPRESSION 5
// #define IMF_B44_COMPRESSION 6
// #define IMF_B44A_COMPRESSION  7

const char *ReadString(std::string &s, const char *ptr) {
  // Read untile NULL(\0).
  const char *p = ptr;
  const char *q = ptr;
  while ((*q) != 0)
    q++;

  s = std::string(p, q);

  return q + 1; // skip '\0'
}

const char *ReadAttribute(std::string &name, std::string &ty,
                          std::vector<unsigned char> &data, const char *ptr) {

  if ((*ptr) == 0) {
    // end of attribute.
    return NULL;
  }

  const char *p = ReadString(name, ptr);

  p = ReadString(ty, p);

  int dataLen;
  memcpy(&dataLen, p, sizeof(int));
  p += 4;

  if (IsBigEndian()) {
    swap4(reinterpret_cast<unsigned int *>(&dataLen));
  }

  data.resize(dataLen);
  memcpy(&data.at(0), p, dataLen);
  p += dataLen;

  return p;
}

void WriteAttribute(FILE *fp, const char *name, const char *type,
                    const unsigned char *data, int len) {
  size_t n = fwrite(name, 1, strlen(name) + 1, fp);
  assert(n == strlen(name) + 1);

  n = fwrite(type, 1, strlen(type) + 1, fp);
  assert(n == strlen(type) + 1);

  int outLen = len;
  if (IsBigEndian()) {
    swap4(reinterpret_cast<unsigned int *>(&outLen));
  }
  n = fwrite(&outLen, 1, sizeof(int), fp);
  assert(n == sizeof(int));

  n = fwrite(data, 1, len, fp);
  assert(n == (size_t)len);

  (void)n;
}

void WriteAttributeToMemory(std::vector<unsigned char> &out, const char *name,
                            const char *type, const unsigned char *data,
                            int len) {
  out.insert(out.end(), name, name + strlen(name) + 1);
  out.insert(out.end(), type, type + strlen(type) + 1);

  int outLen = len;
  if (IsBigEndian()) {
    swap4(reinterpret_cast<unsigned int *>(&outLen));
  }
  out.insert(out.end(), reinterpret_cast<unsigned char *>(&outLen),
             reinterpret_cast<unsigned char *>(&outLen) + sizeof(int));
  out.insert(out.end(), data, data + len);
}

typedef struct {
  std::string name; // less than 255 bytes long
  int pixelType;
  unsigned char pLinear;
  int xSampling;
  int ySampling;
} ChannelInfo;

void ReadChannelInfo(std::vector<ChannelInfo> &channels,
                     const std::vector<unsigned char> &data) {
  const char *p = reinterpret_cast<const char *>(&data.at(0));

  for (;;) {
    if ((*p) == 0) {
      break;
    }
    ChannelInfo info;
    p = ReadString(info.name, p);

    memcpy(&info.pixelType, p, sizeof(int));
    p += 4;
    info.pLinear = p[0];                     // uchar
    p += 1 + 3;                              // reserved: uchar[3]
    memcpy(&info.xSampling, p, sizeof(int)); // int
    p += 4;
    memcpy(&info.ySampling, p, sizeof(int)); // int
    p += 4;

    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&info.pixelType));
      swap4(reinterpret_cast<unsigned int *>(&info.xSampling));
      swap4(reinterpret_cast<unsigned int *>(&info.ySampling));
    }

    channels.push_back(info);
  }
}

void WriteChannelInfo(std::vector<unsigned char> &data,
                      const std::vector<ChannelInfo> &channels) {

  size_t sz = 0;

  // Calculate total size.
  for (size_t c = 0; c < channels.size(); c++) {
    sz += strlen(channels[c].name.c_str()) + 1; // +1 for \0
    sz += 16;                                   // 4 * int
  }
  data.resize(sz + 1);

  unsigned char *p = &data.at(0);

  for (size_t c = 0; c < channels.size(); c++) {
    memcpy(p, channels[c].name.c_str(), strlen(channels[c].name.c_str()));
    p += strlen(channels[c].name.c_str());
    (*p) = '\0';
    p++;

    int pixelType = channels[c].pixelType;
    int xSampling = channels[c].xSampling;
    int ySampling = channels[c].ySampling;
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&pixelType));
      swap4(reinterpret_cast<unsigned int *>(&xSampling));
      swap4(reinterpret_cast<unsigned int *>(&ySampling));
    }

    memcpy(p, &pixelType, sizeof(int));
    p += sizeof(int);

    (*p) = channels[c].pLinear;
    p += 4;

    memcpy(p, &xSampling, sizeof(int));
    p += sizeof(int);

    memcpy(p, &ySampling, sizeof(int));
    p += sizeof(int);
  }

  (*p) = '\0';
}

void CompressZip(unsigned char *dst, unsigned long long &compressedSize,
                 const unsigned char *src, unsigned long srcSize) {

  std::vector<unsigned char> tmpBuf(srcSize);

  //
  // Apply EXR-specific? postprocess. Grabbed from OpenEXR's
  // ImfZipCompressor.cpp
  //

  //
  // Reorder the pixel data.
  //

  {
    char *t1 = (char *)&tmpBuf.at(0);
    char *t2 = (char *)&tmpBuf.at(0) + (srcSize + 1) / 2;
    const char *stop = (const char *)src + srcSize;

    while (true) {
      if ((const char *)src < stop)
        *(t1++) = *(src++);
      else
        break;

      if ((const char *)src < stop)
        *(t2++) = *(src++);
      else
        break;
    }
  }

  //
  // Predictor.
  //

  {
    unsigned char *t = &tmpBuf.at(0) + 1;
    unsigned char *stop = &tmpBuf.at(0) + srcSize;
    int p = t[-1];

    while (t < stop) {
      int d = int(t[0]) - p + (128 + 256);
      p = t[0];
      t[0] = d;
      ++t;
    }
  }

  //
  // Compress the data using miniz
  //

  miniz::mz_ulong outSize = miniz::mz_compressBound(srcSize);
  int ret = miniz::mz_compress(dst, &outSize,
                               (const unsigned char *)&tmpBuf.at(0), srcSize);
  assert(ret == miniz::MZ_OK);
  (void)ret;

  compressedSize = outSize;
}

void DecompressZip(unsigned char *dst, unsigned long &uncompressedSize,
                   const unsigned char *src, unsigned long srcSize) {
  std::vector<unsigned char> tmpBuf(uncompressedSize);

  int ret =
      miniz::mz_uncompress(&tmpBuf.at(0), &uncompressedSize, src, srcSize);
  assert(ret == miniz::MZ_OK);
  (void)ret;

  //
  // Apply EXR-specific? postprocess. Grabbed from OpenEXR's
  // ImfZipCompressor.cpp
  //

  // Predictor.
  {
    unsigned char *t = &tmpBuf.at(0) + 1;
    unsigned char *stop = &tmpBuf.at(0) + uncompressedSize;

    while (t < stop) {
      int d = int(t[-1]) + int(t[0]) - 128;
      t[0] = d;
      ++t;
    }
  }

  // Reorder the pixel data.
  {
    const char *t1 = reinterpret_cast<const char *>(&tmpBuf.at(0));
    const char *t2 = reinterpret_cast<const char *>(&tmpBuf.at(0)) +
                     (uncompressedSize + 1) / 2;
    char *s = reinterpret_cast<char *>(dst);
    char *stop = s + uncompressedSize;

    while (true) {
      if (s < stop)
        *(s++) = *(t1++);
      else
        break;

      if (s < stop)
        *(s++) = *(t2++);
      else
        break;
    }
  }
}

//
// PIZ compress/uncompress, based on OpenEXR's ImfPizCompressor.cpp
//
// -----------------------------------------------------------------
// Copyright (c) 2004, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC)
// (3 clause BSD license)
//

struct PIZChannelData {
  unsigned short *start;
  unsigned short *end;
  int nx;
  int ny;
  int ys;
  int size;
};

//-----------------------------------------------------------------------------
//
//  16-bit Haar Wavelet encoding and decoding
//
//  The source code in this file is derived from the encoding
//  and decoding routines written by Christian Rouet for his
//  PIZ image file format.
//
//-----------------------------------------------------------------------------

//
// Wavelet basis functions without modulo arithmetic; they produce
// the best compression ratios when the wavelet-transformed data are
// Huffman-encoded, but the wavelet transform works only for 14-bit
// data (untransformed data values must be less than (1 << 14)).
//

#if 0 // @todo
inline void wenc14(unsigned short a, unsigned short b, unsigned short &l,
                   unsigned short &h) {
  short as = a;
  short bs = b;

  short ms = (as + bs) >> 1;
  short ds = as - bs;

  l = ms;
  h = ds;
}
#endif

inline void wdec14(unsigned short l, unsigned short h, unsigned short &a,
                   unsigned short &b) {
  short ls = l;
  short hs = h;

  int hi = hs;
  int ai = ls + (hi & 1) + (hi >> 1);

  short as = ai;
  short bs = ai - hi;

  a = as;
  b = bs;
}

//
// Wavelet basis functions with modulo arithmetic; they work with full
// 16-bit data, but Huffman-encoding the wavelet-transformed data doesn't
// compress the data quite as well.
//

const int NBITS = 16;
const int A_OFFSET = 1 << (NBITS - 1);
// const int M_OFFSET = 1 << (NBITS - 1);
const int MOD_MASK = (1 << NBITS) - 1;

#if 0 // @ood
inline void wenc16(unsigned short a, unsigned short b, unsigned short &l,
                   unsigned short &h) {
  int ao = (a + A_OFFSET) & MOD_MASK;
  int m = ((ao + b) >> 1);
  int d = ao - b;

  if (d < 0)
    m = (m + M_OFFSET) & MOD_MASK;

  d &= MOD_MASK;

  l = m;
  h = d;
}
#endif

inline void wdec16(unsigned short l, unsigned short h, unsigned short &a,
                   unsigned short &b) {
  int m = l;
  int d = h;
  int bb = (m - (d >> 1)) & MOD_MASK;
  int aa = (d + bb - A_OFFSET) & MOD_MASK;
  b = bb;
  a = aa;
}

//
// 2D Wavelet encoding:
//

#if 0 // @todo
void wav2Encode(unsigned short *in, // io: values are transformed in place
                int nx,             // i : x size
                int ox,             // i : x offset
                int ny,             // i : y size
                int oy,             // i : y offset
                unsigned short mx)  // i : maximum in[x][y] value
{
  bool w14 = (mx < (1 << 14));
  int n = (nx > ny) ? ny : nx;
  int p = 1;  // == 1 <<  level
  int p2 = 2; // == 1 << (level+1)

  //
  // Hierachical loop on smaller dimension n
  //

  while (p2 <= n) {
    unsigned short *py = in;
    unsigned short *ey = in + oy * (ny - p2);
    int oy1 = oy * p;
    int oy2 = oy * p2;
    int ox1 = ox * p;
    int ox2 = ox * p2;
    unsigned short i00, i01, i10, i11;

    //
    // Y loop
    //

    for (; py <= ey; py += oy2) {
      unsigned short *px = py;
      unsigned short *ex = py + ox * (nx - p2);

      //
      // X loop
      //

      for (; px <= ex; px += ox2) {
        unsigned short *p01 = px + ox1;
        unsigned short *p10 = px + oy1;
        unsigned short *p11 = p10 + ox1;

        //
        // 2D wavelet encoding
        //

        if (w14) {
          wenc14(*px, *p01, i00, i01);
          wenc14(*p10, *p11, i10, i11);
          wenc14(i00, i10, *px, *p10);
          wenc14(i01, i11, *p01, *p11);
        } else {
          wenc16(*px, *p01, i00, i01);
          wenc16(*p10, *p11, i10, i11);
          wenc16(i00, i10, *px, *p10);
          wenc16(i01, i11, *p01, *p11);
        }
      }

      //
      // Encode (1D) odd column (still in Y loop)
      //

      if (nx & p) {
        unsigned short *p10 = px + oy1;

        if (w14)
          wenc14(*px, *p10, i00, *p10);
        else
          wenc16(*px, *p10, i00, *p10);

        *px = i00;
      }
    }

    //
    // Encode (1D) odd line (must loop in X)
    //

    if (ny & p) {
      unsigned short *px = py;
      unsigned short *ex = py + ox * (nx - p2);

      for (; px <= ex; px += ox2) {
        unsigned short *p01 = px + ox1;

        if (w14)
          wenc14(*px, *p01, i00, *p01);
        else
          wenc16(*px, *p01, i00, *p01);

        *px = i00;
      }
    }

    //
    // Next level
    //

    p = p2;
    p2 <<= 1;
  }
}
#endif

//
// 2D Wavelet decoding:
//

void wav2Decode(unsigned short *in, // io: values are transformed in place
                int nx,             // i : x size
                int ox,             // i : x offset
                int ny,             // i : y size
                int oy,             // i : y offset
                unsigned short mx)  // i : maximum in[x][y] value
{
  bool w14 = (mx < (1 << 14));
  int n = (nx > ny) ? ny : nx;
  int p = 1;
  int p2;

  //
  // Search max level
  //

  while (p <= n)
    p <<= 1;

  p >>= 1;
  p2 = p;
  p >>= 1;

  //
  // Hierarchical loop on smaller dimension n
  //

  while (p >= 1) {
    unsigned short *py = in;
    unsigned short *ey = in + oy * (ny - p2);
    int oy1 = oy * p;
    int oy2 = oy * p2;
    int ox1 = ox * p;
    int ox2 = ox * p2;
    unsigned short i00, i01, i10, i11;

    //
    // Y loop
    //

    for (; py <= ey; py += oy2) {
      unsigned short *px = py;
      unsigned short *ex = py + ox * (nx - p2);

      //
      // X loop
      //

      for (; px <= ex; px += ox2) {
        unsigned short *p01 = px + ox1;
        unsigned short *p10 = px + oy1;
        unsigned short *p11 = p10 + ox1;

        //
        // 2D wavelet decoding
        //

        if (w14) {
          wdec14(*px, *p10, i00, i10);
          wdec14(*p01, *p11, i01, i11);
          wdec14(i00, i01, *px, *p01);
          wdec14(i10, i11, *p10, *p11);
        } else {
          wdec16(*px, *p10, i00, i10);
          wdec16(*p01, *p11, i01, i11);
          wdec16(i00, i01, *px, *p01);
          wdec16(i10, i11, *p10, *p11);
        }
      }

      //
      // Decode (1D) odd column (still in Y loop)
      //

      if (nx & p) {
        unsigned short *p10 = px + oy1;

        if (w14)
          wdec14(*px, *p10, i00, *p10);
        else
          wdec16(*px, *p10, i00, *p10);

        *px = i00;
      }
    }

    //
    // Decode (1D) odd line (must loop in X)
    //

    if (ny & p) {
      unsigned short *px = py;
      unsigned short *ex = py + ox * (nx - p2);

      for (; px <= ex; px += ox2) {
        unsigned short *p01 = px + ox1;

        if (w14)
          wdec14(*px, *p01, i00, *p01);
        else
          wdec16(*px, *p01, i00, *p01);

        *px = i00;
      }
    }

    //
    // Next level
    //

    p2 = p;
    p >>= 1;
  }
}

//-----------------------------------------------------------------------------
//
//	16-bit Huffman compression and decompression.
//
//	The source code in this file is derived from the 8-bit
//	Huffman compression and decompression routines written
//	by Christian Rouet for his PIZ image file format.
//
//-----------------------------------------------------------------------------

// Adds some modification for tinyexr.

const int HUF_ENCBITS = 16; // literal (value) bit length
const int HUF_DECBITS = 14; // decoding bit size (>= 8)

const int HUF_ENCSIZE = (1 << HUF_ENCBITS) + 1; // encoding table size
const int HUF_DECSIZE = 1 << HUF_DECBITS;       // decoding table size
const int HUF_DECMASK = HUF_DECSIZE - 1;

struct HufDec { // short code		long code
  //-------------------------------
  int len : 8;  // code length		0
  int lit : 24; // lit			p size
  int *p;       // 0			lits
};

inline long long hufLength(long long code) { return code & 63; }

inline long long hufCode(long long code) { return code >> 6; }

#if 0  
inline void outputBits(int nBits, long long bits, long long &c, int &lc,
                       char *&out) {
  c <<= nBits;
  lc += nBits;

  c |= bits;

  while (lc >= 8)
    *out++ = (c >> (lc -= 8));
}
#endif

inline long long getBits(int nBits, long long &c, int &lc, const char *&in) {
  while (lc < nBits) {
    c = (c << 8) | *(unsigned char *)(in++);
    lc += 8;
  }

  lc -= nBits;
  return (c >> lc) & ((1 << nBits) - 1);
}

//
// ENCODING TABLE BUILDING & (UN)PACKING
//

//
// Build a "canonical" Huffman code table:
//	- for each (uncompressed) symbol, hcode contains the length
//	  of the corresponding code (in the compressed data)
//	- canonical codes are computed and stored in hcode
//	- the rules for constructing canonical codes are as follows:
//	  * shorter codes (if filled with zeroes to the right)
//	    have a numerically higher value than longer codes
//	  * for codes with the same length, numerical values
//	    increase with numerical symbol values
//	- because the canonical code table can be constructed from
//	  symbol lengths alone, the code table can be transmitted
//	  without sending the actual code values
//	- see http://www.compressconsult.com/huffman/
//

void hufCanonicalCodeTable(long long hcode[HUF_ENCSIZE]) {
  long long n[59];

  //
  // For each i from 0 through 58, count the
  // number of different codes of length i, and
  // store the count in n[i].
  //

  for (int i = 0; i <= 58; ++i)
    n[i] = 0;

  for (int i = 0; i < HUF_ENCSIZE; ++i)
    n[hcode[i]] += 1;

  //
  // For each i from 58 through 1, compute the
  // numerically lowest code with length i, and
  // store that code in n[i].
  //

  long long c = 0;

  for (int i = 58; i > 0; --i) {
    long long nc = ((c + n[i]) >> 1);
    n[i] = c;
    c = nc;
  }

  //
  // hcode[i] contains the length, l, of the
  // code for symbol i.  Assign the next available
  // code of length l to the symbol and store both
  // l and the code in hcode[i].
  //

  for (int i = 0; i < HUF_ENCSIZE; ++i) {
    int l = hcode[i];

    if (l > 0)
      hcode[i] = l | (n[l]++ << 6);
  }
}

//
// Compute Huffman codes (based on frq input) and store them in frq:
//	- code structure is : [63:lsb - 6:msb] | [5-0: bit length];
//	- max code length is 58 bits;
//	- codes outside the range [im-iM] have a null length (unused values);
//	- original frequencies are destroyed;
//	- encoding tables are used by hufEncode() and hufBuildDecTable();
//
#if 0 // @todo

struct FHeapCompare {
  bool operator()(long long *a, long long *b) { return *a > *b; }
};

void hufBuildEncTable(
    long long *frq, // io: input frequencies [HUF_ENCSIZE], output table
    int *im,        //  o: min frq index
    int *iM)        //  o: max frq index
{
  //
  // This function assumes that when it is called, array frq
  // indicates the frequency of all possible symbols in the data
  // that are to be Huffman-encoded.  (frq[i] contains the number
  // of occurrences of symbol i in the data.)
  //
  // The loop below does three things:
  //
  // 1) Finds the minimum and maximum indices that point
  //    to non-zero entries in frq:
  //
  //     frq[im] != 0, and frq[i] == 0 for all i < im
  //     frq[iM] != 0, and frq[i] == 0 for all i > iM
  //
  // 2) Fills array fHeap with pointers to all non-zero
  //    entries in frq.
  //
  // 3) Initializes array hlink such that hlink[i] == i
  //    for all array entries.
  //

  int hlink[HUF_ENCSIZE];
  long long *fHeap[HUF_ENCSIZE];

  *im = 0;

  while (!frq[*im])
    (*im)++;

  int nf = 0;

  for (int i = *im; i < HUF_ENCSIZE; i++) {
    hlink[i] = i;

    if (frq[i]) {
      fHeap[nf] = &frq[i];
      nf++;
      *iM = i;
    }
  }

  //
  // Add a pseudo-symbol, with a frequency count of 1, to frq;
  // adjust the fHeap and hlink array accordingly.  Function
  // hufEncode() uses the pseudo-symbol for run-length encoding.
  //

  (*iM)++;
  frq[*iM] = 1;
  fHeap[nf] = &frq[*iM];
  nf++;

  //
  // Build an array, scode, such that scode[i] contains the number
  // of bits assigned to symbol i.  Conceptually this is done by
  // constructing a tree whose leaves are the symbols with non-zero
  // frequency:
  //
  //     Make a heap that contains all symbols with a non-zero frequency,
  //     with the least frequent symbol on top.
  //
  //     Repeat until only one symbol is left on the heap:
  //
  //         Take the two least frequent symbols off the top of the heap.
  //         Create a new node that has first two nodes as children, and
  //         whose frequency is the sum of the frequencies of the first
  //         two nodes.  Put the new node back into the heap.
  //
  // The last node left on the heap is the root of the tree.  For each
  // leaf node, the distance between the root and the leaf is the length
  // of the code for the corresponding symbol.
  //
  // The loop below doesn't actually build the tree; instead we compute
  // the distances of the leaves from the root on the fly.  When a new
  // node is added to the heap, then that node's descendants are linked
  // into a single linear list that starts at the new node, and the code
  // lengths of the descendants (that is, their distance from the root
  // of the tree) are incremented by one.
  //

  std::make_heap(&fHeap[0], &fHeap[nf], FHeapCompare());

  long long scode[HUF_ENCSIZE];
  memset(scode, 0, sizeof(long long) * HUF_ENCSIZE);

  while (nf > 1) {
    //
    // Find the indices, mm and m, of the two smallest non-zero frq
    // values in fHeap, add the smallest frq to the second-smallest
    // frq, and remove the smallest frq value from fHeap.
    //

    int mm = fHeap[0] - frq;
    std::pop_heap(&fHeap[0], &fHeap[nf], FHeapCompare());
    --nf;

    int m = fHeap[0] - frq;
    std::pop_heap(&fHeap[0], &fHeap[nf], FHeapCompare());

    frq[m] += frq[mm];
    std::push_heap(&fHeap[0], &fHeap[nf], FHeapCompare());

    //
    // The entries in scode are linked into lists with the
    // entries in hlink serving as "next" pointers and with
    // the end of a list marked by hlink[j] == j.
    //
    // Traverse the lists that start at scode[m] and scode[mm].
    // For each element visited, increment the length of the
    // corresponding code by one bit. (If we visit scode[j]
    // during the traversal, then the code for symbol j becomes
    // one bit longer.)
    //
    // Merge the lists that start at scode[m] and scode[mm]
    // into a single list that starts at scode[m].
    //

    //
    // Add a bit to all codes in the first list.
    //

    for (int j = m; true; j = hlink[j]) {
      scode[j]++;

      assert(scode[j] <= 58);

      if (hlink[j] == j) {
        //
        // Merge the two lists.
        //

        hlink[j] = mm;
        break;
      }
    }

    //
    // Add a bit to all codes in the second list
    //

    for (int j = mm; true; j = hlink[j]) {
      scode[j]++;

      assert(scode[j] <= 58);

      if (hlink[j] == j)
        break;
    }
  }

  //
  // Build a canonical Huffman code table, replacing the code
  // lengths in scode with (code, code length) pairs.  Copy the
  // code table from scode into frq.
  //

  hufCanonicalCodeTable(scode);
  memcpy(frq, scode, sizeof(long long) * HUF_ENCSIZE);
}
#endif

//
// Pack an encoding table:
//	- only code lengths, not actual codes, are stored
//	- runs of zeroes are compressed as follows:
//
//	  unpacked		packed
//	  --------------------------------
//	  1 zero		0	(6 bits)
//	  2 zeroes		59
//	  3 zeroes		60
//	  4 zeroes		61
//	  5 zeroes		62
//	  n zeroes (6 or more)	63 n-6	(6 + 8 bits)
//

const int SHORT_ZEROCODE_RUN = 59;
const int LONG_ZEROCODE_RUN = 63;
const int SHORTEST_LONG_RUN = 2 + LONG_ZEROCODE_RUN - SHORT_ZEROCODE_RUN;
// const int LONGEST_LONG_RUN = 255 + SHORTEST_LONG_RUN;

#if 0
void hufPackEncTable(const long long *hcode, // i : encoding table [HUF_ENCSIZE]
                     int im,                 // i : min hcode index
                     int iM,                 // i : max hcode index
                     char **pcode) //  o: ptr to packed table (updated)
{
  char *p = *pcode;
  long long c = 0;
  int lc = 0;

  for (; im <= iM; im++) {
    int l = hufLength(hcode[im]);

    if (l == 0) {
      int zerun = 1;

      while ((im < iM) && (zerun < LONGEST_LONG_RUN)) {
        if (hufLength(hcode[im + 1]) > 0)
          break;
        im++;
        zerun++;
      }

      if (zerun >= 2) {
        if (zerun >= SHORTEST_LONG_RUN) {
          outputBits(6, LONG_ZEROCODE_RUN, c, lc, p);
          outputBits(8, zerun - SHORTEST_LONG_RUN, c, lc, p);
        } else {
          outputBits(6, SHORT_ZEROCODE_RUN + zerun - 2, c, lc, p);
        }
        continue;
      }
    }

    outputBits(6, l, c, lc, p);
  }

  if (lc > 0)
    *p++ = (unsigned char)(c << (8 - lc));

  *pcode = p;
}
#endif

//
// Unpack an encoding table packed by hufPackEncTable():
//

bool hufUnpackEncTable(const char **pcode, // io: ptr to packed table (updated)
                       int ni,             // i : input size (in bytes)
                       int im,             // i : min hcode index
                       int iM,             // i : max hcode index
                       long long *hcode)   //  o: encoding table [HUF_ENCSIZE]
{
  memset(hcode, 0, sizeof(long long) * HUF_ENCSIZE);

  const char *p = *pcode;
  long long c = 0;
  int lc = 0;

  for (; im <= iM; im++) {
    if (p - *pcode > ni) {
      return false;
    }

    long long l = hcode[im] = getBits(6, c, lc, p); // code length

    if (l == (long long)LONG_ZEROCODE_RUN) {
      if (p - *pcode > ni) {
        return false;
      }

      int zerun = getBits(8, c, lc, p) + SHORTEST_LONG_RUN;

      if (im + zerun > iM + 1) {
        return false;
      }

      while (zerun--)
        hcode[im++] = 0;

      im--;
    } else if (l >= (long long)SHORT_ZEROCODE_RUN) {
      int zerun = l - SHORT_ZEROCODE_RUN + 2;

      if (im + zerun > iM + 1) {
        return false;
      }

      while (zerun--)
        hcode[im++] = 0;

      im--;
    }
  }

  *pcode = const_cast<char *>(p);

  hufCanonicalCodeTable(hcode);

  return true;
}

//
// DECODING TABLE BUILDING
//

//
// Clear a newly allocated decoding table so that it contains only zeroes.
//

void hufClearDecTable(HufDec *hdecod) // io: (allocated by caller)
                                      //     decoding table [HUF_DECSIZE]
{
  for (int i = 0; i < HUF_DECSIZE; i++) {
    hdecod[i].len = 0;
    hdecod[i].lit = 0;
    hdecod[i].p = NULL;
  }
  // memset(hdecod, 0, sizeof(HufDec) * HUF_DECSIZE);
}

//
// Build a decoding hash table based on the encoding table hcode:
//	- short codes (<= HUF_DECBITS) are resolved with a single table access;
//	- long code entry allocations are not optimized, because long codes are
//	  unfrequent;
//	- decoding tables are used by hufDecode();
//

bool hufBuildDecTable(const long long *hcode, // i : encoding table
                      int im,                 // i : min index in hcode
                      int iM,                 // i : max index in hcode
                      HufDec *hdecod)         //  o: (allocated by caller)
//     decoding table [HUF_DECSIZE]
{
  //
  // Init hashtable & loop on all codes.
  // Assumes that hufClearDecTable(hdecod) has already been called.
  //

  for (; im <= iM; im++) {
    long long c = hufCode(hcode[im]);
    int l = hufLength(hcode[im]);

    if (c >> l) {
      //
      // Error: c is supposed to be an l-bit code,
      // but c contains a value that is greater
      // than the largest l-bit number.
      //

      // invalidTableEntry();
      return false;
    }

    if (l > HUF_DECBITS) {
      //
      // Long code: add a secondary entry
      //

      HufDec *pl = hdecod + (c >> (l - HUF_DECBITS));

      if (pl->len) {
        //
        // Error: a short code has already
        // been stored in table entry *pl.
        //

        // invalidTableEntry();
        return false;
      }

      pl->lit++;

      if (pl->p) {
        int *p = pl->p;
        pl->p = new int[pl->lit];

        for (int i = 0; i < pl->lit - 1; ++i)
          pl->p[i] = p[i];

        delete[] p;
      } else {
        pl->p = new int[1];
      }

      pl->p[pl->lit - 1] = im;
    } else if (l) {
      //
      // Short code: init all primary entries
      //

      HufDec *pl = hdecod + (c << (HUF_DECBITS - l));

      for (long long i = 1 << (HUF_DECBITS - l); i > 0; i--, pl++) {
        if (pl->len || pl->p) {
          //
          // Error: a short code or a long code has
          // already been stored in table entry *pl.
          //

          // invalidTableEntry();
          return false;
        }

        pl->len = l;
        pl->lit = im;
      }
    }
  }

  return true;
}

//
// Free the long code entries of a decoding table built by hufBuildDecTable()
//

void hufFreeDecTable(HufDec *hdecod) // io: Decoding table
{
  for (int i = 0; i < HUF_DECSIZE; i++) {
    if (hdecod[i].p) {
      delete[] hdecod[i].p;
      hdecod[i].p = 0;
    }
  }
}

//
// ENCODING
//

#if 0 // @todo
inline void outputCode(long long code, long long &c, int &lc, char *&out) {
  outputBits(hufLength(code), hufCode(code), c, lc, out);
}

inline void sendCode(long long sCode, int runCount, long long runCode,
                     long long &c, int &lc, char *&out) {
  //
  // Output a run of runCount instances of the symbol sCount.
  // Output the symbols explicitly, or if that is shorter, output
  // the sCode symbol once followed by a runCode symbol and runCount
  // expressed as an 8-bit number.
  //

  if (hufLength(sCode) + hufLength(runCode) + 8 < hufLength(sCode) * runCount) {
    outputCode(sCode, c, lc, out);
    outputCode(runCode, c, lc, out);
    outputBits(8, runCount, c, lc, out);
  } else {
    while (runCount-- >= 0)
      outputCode(sCode, c, lc, out);
  }
}

//
// Encode (compress) ni values based on the Huffman encoding table hcode:
//

int hufEncode                  // return: output size (in bits)
    (const long long *hcode,   // i : encoding table
     const unsigned short *in, // i : uncompressed input buffer
     const int ni,             // i : input buffer size (in bytes)
     int rlc,                  // i : rl code
     char *out)                //  o: compressed output buffer
{
  char *outStart = out;
  long long c = 0; // bits not yet written to out
  int lc = 0;      // number of valid bits in c (LSB)
  int s = in[0];
  int cs = 0;

  //
  // Loop on input values
  //

  for (int i = 1; i < ni; i++) {
    //
    // Count same values or send code
    //

    if (s == in[i] && cs < 255) {
      cs++;
    } else {
      sendCode(hcode[s], cs, hcode[rlc], c, lc, out);
      cs = 0;
    }

    s = in[i];
  }

  //
  // Send remaining code
  //

  sendCode(hcode[s], cs, hcode[rlc], c, lc, out);

  if (lc)
    *out = (c << (8 - lc)) & 0xff;

  return (out - outStart) * 8 + lc;
}
#endif

//
// DECODING
//

//
// In order to force the compiler to inline them,
// getChar() and getCode() are implemented as macros
// instead of "inline" functions.
//

#define getChar(c, lc, in)                                                     \
  {                                                                            \
    c = (c << 8) | *(unsigned char *)(in++);                                   \
    lc += 8;                                                                   \
  }

#define getCode(po, rlc, c, lc, in, out, oe)                                   \
  {                                                                            \
    if (po == rlc) {                                                           \
      if (lc < 8)                                                              \
        getChar(c, lc, in);                                                    \
                                                                               \
      lc -= 8;                                                                 \
                                                                               \
      unsigned char cs = (c >> lc);                                            \
                                                                               \
      if (out + cs > oe)                                                       \
        return false;                                                          \
                                                                               \
      unsigned short s = out[-1];                                              \
                                                                               \
      while (cs-- > 0)                                                         \
        *out++ = s;                                                            \
    } else if (out < oe) {                                                     \
      *out++ = po;                                                             \
    } else {                                                                   \
      return false;                                                            \
    }                                                                          \
  }

//
// Decode (uncompress) ni bits based on encoding & decoding tables:
//

bool hufDecode(const long long *hcode, // i : encoding table
               const HufDec *hdecod,   // i : decoding table
               const char *in,         // i : compressed input buffer
               int ni,                 // i : input size (in bits)
               int rlc,                // i : run-length code
               int no,                 // i : expected output size (in bytes)
               unsigned short *out)    //  o: uncompressed output buffer
{
  long long c = 0;
  int lc = 0;
  unsigned short *outb = out;
  unsigned short *oe = out + no;
  const char *ie = in + (ni + 7) / 8; // input byte size

  //
  // Loop on input bytes
  //

  while (in < ie) {
    getChar(c, lc, in);

    //
    // Access decoding table
    //

    while (lc >= HUF_DECBITS) {
      const HufDec pl = hdecod[(c >> (lc - HUF_DECBITS)) & HUF_DECMASK];

      if (pl.len) {
        //
        // Get short code
        //

        lc -= pl.len;
        getCode(pl.lit, rlc, c, lc, in, out, oe);
      } else {
        if (!pl.p) {
          return false;
        }
        // invalidCode(); // wrong code

        //
        // Search long code
        //

        int j;

        for (j = 0; j < pl.lit; j++) {
          int l = hufLength(hcode[pl.p[j]]);

          while (lc < l && in < ie) // get more bits
            getChar(c, lc, in);

          if (lc >= l) {
            if (hufCode(hcode[pl.p[j]]) ==
                ((c >> (lc - l)) & (((long long)(1) << l) - 1))) {
              //
              // Found : get long code
              //

              lc -= l;
              getCode(pl.p[j], rlc, c, lc, in, out, oe);
              break;
            }
          }
        }

        if (j == pl.lit) {
          return false;
          // invalidCode(); // Not found
        }
      }
    }
  }

  //
  // Get remaining (short) codes
  //

  int i = (8 - ni) & 7;
  c >>= i;
  lc -= i;

  while (lc > 0) {
    const HufDec pl = hdecod[(c << (HUF_DECBITS - lc)) & HUF_DECMASK];

    if (pl.len) {
      lc -= pl.len;
      getCode(pl.lit, rlc, c, lc, in, out, oe);
    } else {
      return false;
      // invalidCode(); // wrong (long) code
    }
  }

  if (out - outb != no) {
    return false;
  }
  // notEnoughData ();

  return true;
}

#if 0 // @todo
void countFrequencies(long long freq[HUF_ENCSIZE],
                      const unsigned short data[/*n*/], int n) {
  for (int i = 0; i < HUF_ENCSIZE; ++i)
    freq[i] = 0;

  for (int i = 0; i < n; ++i)
    ++freq[data[i]];
}

void writeUInt(char buf[4], unsigned int i) {
  unsigned char *b = (unsigned char *)buf;

  b[0] = i;
  b[1] = i >> 8;
  b[2] = i >> 16;
  b[3] = i >> 24;
}
#endif

unsigned int readUInt(const char buf[4]) {
  const unsigned char *b = (const unsigned char *)buf;

  return (b[0] & 0x000000ff) | ((b[1] << 8) & 0x0000ff00) |
         ((b[2] << 16) & 0x00ff0000) | ((b[3] << 24) & 0xff000000);
}

//
// EXTERNAL INTERFACE
//

#if 0 // @todo
int hufCompress(const unsigned short raw[], int nRaw, char compressed[]) {
  if (nRaw == 0)
    return 0;

  long long freq[HUF_ENCSIZE];

  countFrequencies(freq, raw, nRaw);

  int im = 0;
  int iM = 0;
  hufBuildEncTable(freq, &im, &iM);

  char *tableStart = compressed + 20;
  char *tableEnd = tableStart;
  hufPackEncTable(freq, im, iM, &tableEnd);
  int tableLength = tableEnd - tableStart;

  char *dataStart = tableEnd;
  int nBits = hufEncode(freq, raw, nRaw, iM, dataStart);
  int dataLength = (nBits + 7) / 8;

  writeUInt(compressed, im);
  writeUInt(compressed + 4, iM);
  writeUInt(compressed + 8, tableLength);
  writeUInt(compressed + 12, nBits);
  writeUInt(compressed + 16, 0); // room for future extensions

  return dataStart + dataLength - compressed;
}
#endif

bool hufUncompress(const char compressed[], int nCompressed,
                   unsigned short raw[], int nRaw) {
  if (nCompressed == 0) {
    if (nRaw != 0)
      return false;

    return false;
  }

  int im = readUInt(compressed);
  int iM = readUInt(compressed + 4);
  // int tableLength = readUInt (compressed + 8);
  int nBits = readUInt(compressed + 12);

  if (im < 0 || im >= HUF_ENCSIZE || iM < 0 || iM >= HUF_ENCSIZE)
    return false;

  const char *ptr = compressed + 20;

  //
  // Fast decoder needs at least 2x64-bits of compressed data, and
  // needs to be run-able on this platform. Otherwise, fall back
  // to the original decoder
  //

  // if (FastHufDecoder::enabled() && nBits > 128)
  //{
  //    FastHufDecoder fhd (ptr, nCompressed - (ptr - compressed), im, iM, iM);
  //    fhd.decode ((unsigned char*)ptr, nBits, raw, nRaw);
  //}
  // else
  {
    std::vector<long long> freq(HUF_ENCSIZE);
    std::vector<HufDec> hdec(HUF_DECSIZE);

    hufClearDecTable(&hdec.at(0));

    hufUnpackEncTable(&ptr, nCompressed - (ptr - compressed), im, iM,
                      &freq.at(0));

    {
      if (nBits > 8 * (nCompressed - (ptr - compressed))) {
        return false;
      }

      hufBuildDecTable(&freq.at(0), im, iM, &hdec.at(0));
      hufDecode(&freq.at(0), &hdec.at(0), ptr, nBits, iM, nRaw, raw);
    }
    // catch (...)
    //{
    //    hufFreeDecTable (hdec);
    //    throw;
    //}

    hufFreeDecTable(&hdec.at(0));
  }

  return true;
}

//
// Functions to compress the range of values in the pixel data
//

const int USHORT_RANGE = (1 << 16);
const int BITMAP_SIZE = (USHORT_RANGE >> 3);

#if 0 // @todo

void bitmapFromData(const unsigned short data[/*nData*/], int nData,
                    unsigned char bitmap[BITMAP_SIZE],
                    unsigned short &minNonZero, unsigned short &maxNonZero) {
  for (int i = 0; i < BITMAP_SIZE; ++i)
    bitmap[i] = 0;

  for (int i = 0; i < nData; ++i)
    bitmap[data[i] >> 3] |= (1 << (data[i] & 7));

  bitmap[0] &= ~1; // zero is not explicitly stored in
                   // the bitmap; we assume that the
                   // data always contain zeroes
  minNonZero = BITMAP_SIZE - 1;
  maxNonZero = 0;

  for (int i = 0; i < BITMAP_SIZE; ++i) {
    if (bitmap[i]) {
      if (minNonZero > i)
        minNonZero = i;
      if (maxNonZero < i)
        maxNonZero = i;
    }
  }
}

unsigned short forwardLutFromBitmap(const unsigned char bitmap[BITMAP_SIZE],
                                    unsigned short lut[USHORT_RANGE]) {
  int k = 0;

  for (int i = 0; i < USHORT_RANGE; ++i) {
    if ((i == 0) || (bitmap[i >> 3] & (1 << (i & 7))))
      lut[i] = k++;
    else
      lut[i] = 0;
  }

  return k - 1; // maximum value stored in lut[],
} // i.e. number of ones in bitmap minus 1
#endif

unsigned short reverseLutFromBitmap(const unsigned char bitmap[BITMAP_SIZE],
                                    unsigned short lut[USHORT_RANGE]) {
  int k = 0;

  for (int i = 0; i < USHORT_RANGE; ++i) {
    if ((i == 0) || (bitmap[i >> 3] & (1 << (i & 7))))
      lut[k++] = i;
  }

  int n = k - 1;

  while (k < USHORT_RANGE)
    lut[k++] = 0;

  return n; // maximum k where lut[k] is non-zero,
} // i.e. number of ones in bitmap minus 1

void applyLut(const unsigned short lut[USHORT_RANGE],
              unsigned short data[/*nData*/], int nData) {
  for (int i = 0; i < nData; ++i)
    data[i] = lut[data[i]];
}

#if 0 // @todo
bool CompressPiz(unsigned char *outPtr, unsigned int &outSize) {
  unsigned char bitmap[BITMAP_SIZE];
  unsigned short minNonZero;
  unsigned short maxNonZero;

  if (IsBigEndian()) {
    // @todo { PIZ compression on BigEndian architecture. }
    assert(0);
    return false;
  }

  std::vector<unsigned short> tmpBuffer;
  int nData = tmpBuffer.size();

  bitmapFromData(&tmpBuffer.at(0), nData, bitmap, minNonZero, maxNonZero);

  unsigned short lut[USHORT_RANGE];
  //unsigned short maxValue = forwardLutFromBitmap(bitmap, lut);
  applyLut(lut, &tmpBuffer.at(0), nData);

  //
  // Store range compression info in _outBuffer
  //

  char *buf = reinterpret_cast<char *>(outPtr);

  memcpy(buf, &minNonZero, sizeof(unsigned short));
  buf += sizeof(unsigned short);
  memcpy(buf, &maxNonZero, sizeof(unsigned short));
  buf += sizeof(unsigned short);

  if (minNonZero <= maxNonZero) {
    memcpy(buf, (char *)&bitmap[0] + minNonZero, maxNonZero - minNonZero + 1);
    buf += maxNonZero - minNonZero + 1;
  }

#if 0 // @todo
    //
    // Apply wavelet encoding
    //

    for (int i = 0; i < channels; ++i)
    {
      ChannelData &cd = _channelData[i];

      for (int j = 0; j < cd.size; ++j)
      {
          wav2Encode (cd.start + j,
              cd.nx, cd.size,
              cd.ny, cd.nx * cd.size,
              maxValue);
      }
    }

    //
    // Apply Huffman encoding; append the result to _outBuffer
    //

    char *lengthPtr = buf;
    int zero = 0;
    memcpy(buf, &zero, sizeof(int)); buf += sizeof(int);

    int length = hufCompress (_tmpBuffer, tmpBufferEnd - _tmpBuffer, buf);
    memcpy(lengthPtr, tmpBuffer, length);
    //Xdr::write <CharPtrIO> (lengthPtr, length);

    outPtr = _outBuffer;
    return buf - _outBuffer + length;
#endif
  assert(0);

  return true;
}
#endif

bool DecompressPiz(unsigned char *outPtr, unsigned int &,
                   const unsigned char *inPtr, size_t tmpBufSize,
                   const std::vector<ChannelInfo> &channelInfo, int dataWidth,
                   int numLines) {
  unsigned char bitmap[BITMAP_SIZE];
  unsigned short minNonZero;
  unsigned short maxNonZero;

  if (IsBigEndian()) {
    // @todo { PIZ compression on BigEndian architecture. }
    assert(0);
    return false;
  }

  memset(bitmap, 0, BITMAP_SIZE);

  const unsigned char *ptr = inPtr;
  minNonZero = *(reinterpret_cast<const unsigned short *>(ptr));
  maxNonZero = *(reinterpret_cast<const unsigned short *>(ptr + 2));
  ptr += 4;

  if (maxNonZero >= BITMAP_SIZE) {
    return false;
  }

  if (minNonZero <= maxNonZero) {
    memcpy((char *)&bitmap[0] + minNonZero, ptr, maxNonZero - minNonZero + 1);
    ptr += maxNonZero - minNonZero + 1;
  }

  unsigned short lut[USHORT_RANGE];
  memset(lut, 0, sizeof(unsigned short) * USHORT_RANGE);
  unsigned short maxValue = reverseLutFromBitmap(bitmap, lut);

  //
  // Huffman decoding
  //

  int length;

  length = *(reinterpret_cast<const int *>(ptr));
  ptr += sizeof(int);

  std::vector<unsigned short> tmpBuffer(tmpBufSize);
  hufUncompress(reinterpret_cast<const char *>(ptr), length, &tmpBuffer.at(0),
                tmpBufSize);

  //
  // Wavelet decoding
  //

  std::vector<PIZChannelData> channelData(channelInfo.size());

  unsigned short *tmpBufferEnd = &tmpBuffer.at(0);

  for (size_t i = 0; i < channelInfo.size(); ++i) {
    const ChannelInfo &chan = channelInfo[i];

    int pixelSize = sizeof(int); // UINT and FLOAT
    if (chan.pixelType == TINYEXR_PIXELTYPE_HALF) {
      pixelSize = sizeof(short);
    }

    channelData[i].start = tmpBufferEnd;
    channelData[i].end = channelData[i].start;
    channelData[i].nx = dataWidth;
    channelData[i].ny = numLines;
    // channelData[i].ys = 1;
    channelData[i].size = pixelSize / sizeof(short);

    tmpBufferEnd += channelData[i].nx * channelData[i].ny * channelData[i].size;
  }

  for (size_t i = 0; i < channelData.size(); ++i) {
    PIZChannelData &cd = channelData[i];

    for (int j = 0; j < cd.size; ++j) {
      wav2Decode(cd.start + j, cd.nx, cd.size, cd.ny, cd.nx * cd.size,
                 maxValue);
    }
  }

  //
  // Expand the pixel data to their original range
  //

  applyLut(lut, &tmpBuffer.at(0), tmpBufSize);

  // @todo { Xdr }

  for (int y = 0; y < numLines; y++) {
    for (size_t i = 0; i < channelData.size(); ++i) {
      PIZChannelData &cd = channelData[i];

      // if (modp (y, cd.ys) != 0)
      //    continue;

      int n = cd.nx * cd.size;
      memcpy(outPtr, cd.end, n * sizeof(unsigned short));
      outPtr += n * sizeof(unsigned short);
      cd.end += n;
    }
  }

  return true;
}
//
// -----------------------------------------------------------------
//

} // namespace

int LoadEXR(float **out_rgba, int *width, int *height, const char *filename,
            const char **err) {

  if (out_rgba == NULL) {
    if (err) {
      (*err) = "Invalid argument.\n";
    }
    return -1;
  }

  EXRImage exrImage;
  InitEXRImage(&exrImage);

  {
    int ret = ParseMultiChannelEXRHeaderFromFile(&exrImage, filename, err);
    if (ret != 0) {
      return ret;
    }
  }

  // Read HALF channel as FLOAT.
  for (int i = 0; i < exrImage.num_channels; i++) {
    if (exrImage.pixel_types[i] == TINYEXR_PIXELTYPE_HALF) {
      exrImage.requested_pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT;
    }
  }

  {
    int ret = LoadMultiChannelEXRFromFile(&exrImage, filename, err);
    if (ret != 0) {
      return ret;
    }
  }

  // RGBA
  int idxR = -1;
  int idxG = -1;
  int idxB = -1;
  int idxA = -1;
  for (int c = 0; c < exrImage.num_channels; c++) {
    if (strcmp(exrImage.channel_names[c], "R") == 0) {
      idxR = c;
    } else if (strcmp(exrImage.channel_names[c], "G") == 0) {
      idxG = c;
    } else if (strcmp(exrImage.channel_names[c], "B") == 0) {
      idxB = c;
    } else if (strcmp(exrImage.channel_names[c], "A") == 0) {
      idxA = c;
    }
  }

  if (idxR == -1) {
    if (err) {
      (*err) = "R channel not found\n";
    }

    // @todo { free exrImage }
    return -1;
  }

  if (idxG == -1) {
    if (err) {
      (*err) = "G channel not found\n";
    }
    // @todo { free exrImage }
    return -1;
  }

  if (idxB == -1) {
    if (err) {
      (*err) = "B channel not found\n";
    }
    // @todo { free exrImage }
    return -1;
  }

  (*out_rgba) =
      (float *)malloc(4 * sizeof(float) * exrImage.width * exrImage.height);
  for (int i = 0; i < exrImage.width * exrImage.height; i++) {
    (*out_rgba)[4 * i + 0] =
        reinterpret_cast<float **>(exrImage.images)[idxR][i];
    (*out_rgba)[4 * i + 1] =
        reinterpret_cast<float **>(exrImage.images)[idxG][i];
    (*out_rgba)[4 * i + 2] =
        reinterpret_cast<float **>(exrImage.images)[idxB][i];
    if (idxA > 0) {
      (*out_rgba)[4 * i + 3] =
          reinterpret_cast<float **>(exrImage.images)[idxA][i];
    } else {
      (*out_rgba)[4 * i + 3] = 1.0;
    }
  }

  (*width) = exrImage.width;
  (*height) = exrImage.height;

  // @todo { free exrImage }
  return 0;
}

int ParseEXRHeaderFromMemory(EXRAttribute *customAttributes,
                             int *numCustomAttributes, int *width, int *height,
                             const unsigned char *memory) {

  if (memory == NULL) {
    // Invalid argument
    return -1;
  }

  const char *buf = reinterpret_cast<const char *>(memory);

  const char *marker = &buf[0];

  // Header check.
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};

    if (memcmp(marker, header, 4) != 0) {
      // if (err) {
      //  (*err) = "Header mismatch.";
      //}
      return -3;
    }
    marker += 4;
  }

  // Version, scanline.
  {
    // must be [2, 0, 0, 0]
    if (marker[0] != 2 || marker[1] != 0 || marker[2] != 0 || marker[3] != 0) {
      // if (err) {
      //  (*err) = "Unsupported version or scanline.";
      //}
      return -4;
    }

    marker += 4;
  }

  int dx = -1;
  int dy = -1;
  int dw = -1;
  int dh = -1;
  int lineOrder = 0;                          // @fixme
  int displayWindow[4] = {-1, -1, -1, -1};    // @fixme
  float screenWindowCenter[2] = {0.0f, 0.0f}; // @fixme
  float screenWindowWidth = 1.0f;             // @fixme
  int numChannels = -1;
  float pixelAspectRatio = 1.0f; // @fixme
  std::vector<ChannelInfo> channels;
  std::vector<EXRAttribute> attribs;

  if (numCustomAttributes) {
    (*numCustomAttributes) = 0;
  }

  // Read attributes
  for (;;) {
    std::string attrName;
    std::string attrType;
    std::vector<unsigned char> data;
    const char *marker_next = ReadAttribute(attrName, attrType, data, marker);
    if (marker_next == NULL) {
      marker++; // skip '\0'
      break;
    }

    if (attrName.compare("compression") == TINYEXR_COMPRESSIONTYPE_NONE) {
      //	mwkm
      //	0 : NO_COMPRESSION
      //	1 : RLE
      //	2 : ZIPS (Single scanline)
      //	3 : ZIP (16-line block)
      //	4 : PIZ (32-line block)
      if (data[0] > TINYEXR_COMPRESSIONTYPE_PIZ) {
        // if (err) {
        //  (*err) = "Unsupported compression type.";
        //}
        return -5;
      }

    } else if (attrName.compare("channels") == 0) {

      // name: zero-terminated string, from 1 to 255 bytes long
      // pixel type: int, possible values are: UINT = 0 HALF = 1 FLOAT = 2
      // pLinear: unsigned char, possible values are 0 and 1
      // reserved: three chars, should be zero
      // xSampling: int
      // ySampling: int

      ReadChannelInfo(channels, data);

      numChannels = channels.size();

      if (numChannels < 1) {
        // if (err) {
        //  (*err) = "Invalid channels format.";
        //}
        return -6;
      }

    } else if (attrName.compare("dataWindow") == 0) {
      memcpy(&dx, &data.at(0), sizeof(int));
      memcpy(&dy, &data.at(4), sizeof(int));
      memcpy(&dw, &data.at(8), sizeof(int));
      memcpy(&dh, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&dx));
        swap4(reinterpret_cast<unsigned int *>(&dy));
        swap4(reinterpret_cast<unsigned int *>(&dw));
        swap4(reinterpret_cast<unsigned int *>(&dh));
      }
    } else if (attrName.compare("displayWindow") == 0) {
      memcpy(&displayWindow[0], &data.at(0), sizeof(int));
      memcpy(&displayWindow[1], &data.at(4), sizeof(int));
      memcpy(&displayWindow[2], &data.at(8), sizeof(int));
      memcpy(&displayWindow[3], &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[0]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[1]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[2]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[3]));
      }
    } else if (attrName.compare("lineOrder") == 0) {
      memcpy(&lineOrder, &data.at(0), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&lineOrder));
      }
    } else if (attrName.compare("pixelAspectRatio") == 0) {
      memcpy(&pixelAspectRatio, &data.at(0), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&pixelAspectRatio));
      }
    } else if (attrName.compare("screenWindowCenter") == 0) {
      memcpy(&screenWindowCenter[0], &data.at(0), sizeof(float));
      memcpy(&screenWindowCenter[1], &data.at(4), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&screenWindowCenter[0]));
        swap4(reinterpret_cast<unsigned int *>(&screenWindowCenter[1]));
      }
    } else if (attrName.compare("screenWindowWidth") == 0) {
      memcpy(&screenWindowWidth, &data.at(0), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&screenWindowWidth));
      }

    } else {
      // Custom attribute(up to TINYEXR_MAX_ATTRIBUTES)
      if (numCustomAttributes &&
          ((*numCustomAttributes) < TINYEXR_MAX_ATTRIBUTES)) {
        EXRAttribute attrib;
        attrib.name = strdup(attrName.c_str());
        attrib.type = strdup(attrType.c_str());
        attrib.size = data.size();
        attrib.value = (unsigned char *)malloc(data.size());
        memcpy((char *)attrib.value, &data.at(0), data.size());
        attribs.push_back(attrib);
      }
    }

    marker = marker_next;
  }

  assert(dx >= 0);
  assert(dy >= 0);
  assert(dw >= 0);
  assert(dh >= 0);
  assert(numChannels >= 1);

  int dataWidth = dw - dx + 1;
  int dataHeight = dh - dy + 1;

  (*width) = dataWidth;
  (*height) = dataHeight;

  if (numCustomAttributes) {
    assert(attribs.size() < TINYEXR_MAX_ATTRIBUTES);
    (*numCustomAttributes) = attribs.size();

    // Assume the pointer to customAttributes has enough memory to store.
    for (int i = 0; i < (int)attribs.size(); i++) {
      customAttributes[i] = attribs[i];
    }
  }

  return 0;
}

int LoadEXRFromMemory(float *out_rgba, const unsigned char *memory,
                      const char **err) {

  if (out_rgba == NULL || memory == NULL) {
    if (err) {
      (*err) = "Invalid argument.\n";
    }
    return -1;
  }

  EXRImage exrImage;
  InitEXRImage(&exrImage);
  int ret = LoadMultiChannelEXRFromMemory(&exrImage, memory, err);
  if (ret != 0) {
    return ret;
  }

  // RGBA
  int idxR = -1;
  int idxG = -1;
  int idxB = -1;
  int idxA = -1;
  for (int c = 0; c < exrImage.num_channels; c++) {
    if (strcmp(exrImage.channel_names[c], "R") == 0) {
      idxR = c;
    } else if (strcmp(exrImage.channel_names[c], "G") == 0) {
      idxG = c;
    } else if (strcmp(exrImage.channel_names[c], "B") == 0) {
      idxB = c;
    } else if (strcmp(exrImage.channel_names[c], "A") == 0) {
      idxA = c;
    }
  }

  if (idxR == -1) {
    if (err) {
      (*err) = "R channel not found\n";
    }

    // @todo { free exrImage }
    return -1;
  }

  if (idxG == -1) {
    if (err) {
      (*err) = "G channel not found\n";
    }
    // @todo { free exrImage }
    return -1;
  }

  if (idxB == -1) {
    if (err) {
      (*err) = "B channel not found\n";
    }
    // @todo { free exrImage }
    return -1;
  }

  // Assume `out_rgba` have enough memory allocated.
  for (int i = 0; i < exrImage.width * exrImage.height; i++) {
    out_rgba[4 * i + 0] = reinterpret_cast<float **>(exrImage.images)[idxR][i];
    out_rgba[4 * i + 1] = reinterpret_cast<float **>(exrImage.images)[idxG][i];
    out_rgba[4 * i + 2] = reinterpret_cast<float **>(exrImage.images)[idxB][i];
    if (idxA > 0) {
      out_rgba[4 * i + 3] =
          reinterpret_cast<float **>(exrImage.images)[idxA][i];
    } else {
      out_rgba[4 * i + 3] = 1.0;
    }
  }

  return 0;
}

int LoadMultiChannelEXRFromFile(EXRImage *exrImage, const char *filename,
                                const char **err) {
  if (exrImage == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot read file.";
    }
    return -1;
  }

  size_t filesize;
  // Compute size
  fseek(fp, 0, SEEK_END);
  filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::vector<unsigned char> buf(filesize); // @todo { use mmap }
  {
    size_t ret;
    ret = fread(&buf[0], 1, filesize, fp);
    assert(ret == filesize);
    fclose(fp);
    (void)ret;
  }

  return LoadMultiChannelEXRFromMemory(exrImage, &buf.at(0), err);
}

int LoadMultiChannelEXRFromMemory(EXRImage *exrImage,
                                  const unsigned char *memory,
                                  const char **err) {
  if (exrImage == NULL || memory == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  const char *buf = reinterpret_cast<const char *>(memory);

  const char *head = &buf[0];
  const char *marker = &buf[0];

  // Header check.
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};

    if (memcmp(marker, header, 4) != 0) {
      if (err) {
        (*err) = "Header mismatch.";
      }
      return -3;
    }
    marker += 4;
  }

  // Version, scanline.
  {
    // must be [2, 0, 0, 0]
    if (marker[0] != 2 || marker[1] != 0 || marker[2] != 0 || marker[3] != 0) {
      if (err) {
        (*err) = "Unsupported version or scanline.";
      }
      return -4;
    }

    marker += 4;
  }

  int dx = -1;
  int dy = -1;
  int dw = -1;
  int dh = -1;
  int numScanlineBlocks = 1; // 16 for ZIP compression.
  int compressionType = -1;
  int numChannels = -1;
  unsigned char lineOrder = 0; // 0 -> increasing y; 1 -> decreasing
  std::vector<ChannelInfo> channels;

  // Read attributes
  for (;;) {
    std::string attrName;
    std::string attrType;
    std::vector<unsigned char> data;
    const char *marker_next = ReadAttribute(attrName, attrType, data, marker);
    if (marker_next == NULL) {
      marker++; // skip '\0'
      break;
    }

    if (attrName.compare("compression") == 0) {
      //	mwkm
      //	0 : NO_COMPRESSION
      //	1 : RLE
      //	2 : ZIPS (Single scanline)
      //	3 : ZIP (16-line block)
      //	4 : PIZ (32-line block)
      if (data[0] != TINYEXR_COMPRESSIONTYPE_NONE &&
          data[0] != TINYEXR_COMPRESSIONTYPE_ZIPS &&
          data[0] != TINYEXR_COMPRESSIONTYPE_ZIP &&
          data[0] != TINYEXR_COMPRESSIONTYPE_PIZ) {

        if (err) {
          (*err) = "Unsupported compression type.";
        }
        return -5;
      }

      compressionType = data[0];

      if (compressionType == TINYEXR_COMPRESSIONTYPE_ZIP) {
        numScanlineBlocks = 16;
      } else if (compressionType == TINYEXR_COMPRESSIONTYPE_PIZ) {
        numScanlineBlocks = 32;
      }

    } else if (attrName.compare("channels") == 0) {

      // name: zero-terminated string, from 1 to 255 bytes long
      // pixel type: int, possible values are: UINT = 0 HALF = 1 FLOAT = 2
      // pLinear: unsigned char, possible values are 0 and 1
      // reserved: three chars, should be zero
      // xSampling: int
      // ySampling: int

      ReadChannelInfo(channels, data);

      numChannels = channels.size();

      if (numChannels < 1) {
        if (err) {
          (*err) = "Invalid channels format.";
        }
        return -6;
      }

    } else if (attrName.compare("dataWindow") == 0) {
      memcpy(&dx, &data.at(0), sizeof(int));
      memcpy(&dy, &data.at(4), sizeof(int));
      memcpy(&dw, &data.at(8), sizeof(int));
      memcpy(&dh, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&dx));
        swap4(reinterpret_cast<unsigned int *>(&dy));
        swap4(reinterpret_cast<unsigned int *>(&dw));
        swap4(reinterpret_cast<unsigned int *>(&dh));
      }
    } else if (attrName.compare("displayWindow") == 0) {
      int x, y, w, h;
      memcpy(&x, &data.at(0), sizeof(int));
      memcpy(&y, &data.at(4), sizeof(int));
      memcpy(&w, &data.at(8), sizeof(int));
      memcpy(&h, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&x));
        swap4(reinterpret_cast<unsigned int *>(&y));
        swap4(reinterpret_cast<unsigned int *>(&w));
        swap4(reinterpret_cast<unsigned int *>(&h));
      }
    } else if (attrName.compare("lineOrder") == 0) {
      memcpy(&lineOrder, &data.at(0), sizeof(lineOrder));
    }

    marker = marker_next;
  }

  assert(dx >= 0);
  assert(dy >= 0);
  assert(dw >= 0);
  assert(dh >= 0);
  assert(numChannels >= 1);

  int dataWidth = dw - dx + 1;
  int dataHeight = dh - dy + 1;

  // Read offset tables.
  int numBlocks = dataHeight / numScanlineBlocks;
  if (numBlocks * numScanlineBlocks < dataHeight) {
    numBlocks++;
  }

  std::vector<long long> offsets(numBlocks);

  for (int y = 0; y < numBlocks; y++) {
    long long offset;
    memcpy(&offset, marker, sizeof(long long));
    if (IsBigEndian()) {
      swap8(reinterpret_cast<unsigned long long *>(&offset));
    }
    marker += sizeof(long long); // = 8
    offsets[y] = offset;
  }

  exrImage->images = reinterpret_cast<unsigned char **>(
      (float **)malloc(sizeof(float *) * numChannels));

  std::vector<size_t> channelOffsetList(numChannels);
  int pixelDataSize = 0;
  size_t channelOffset = 0;
  for (int c = 0; c < numChannels; c++) {
    channelOffsetList[c] = channelOffset;
    if (channels[c].pixelType == TINYEXR_PIXELTYPE_HALF) {
      pixelDataSize += sizeof(unsigned short);
      channelOffset += sizeof(unsigned short);
      // Alloc internal image for half type.
      if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_HALF) {
        exrImage->images[c] =
            reinterpret_cast<unsigned char *>((unsigned short *)malloc(
                sizeof(unsigned short) * dataWidth * dataHeight));
      } else if (exrImage->requested_pixel_types[c] ==
                 TINYEXR_PIXELTYPE_FLOAT) {
        exrImage->images[c] = reinterpret_cast<unsigned char *>(
            (float *)malloc(sizeof(float) * dataWidth * dataHeight));
      } else {
        assert(0);
      }
    } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_FLOAT) {
      pixelDataSize += sizeof(float);
      channelOffset += sizeof(float);
      exrImage->images[c] = reinterpret_cast<unsigned char *>(
          (float *)malloc(sizeof(float) * dataWidth * dataHeight));
    } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_UINT) {
      pixelDataSize += sizeof(unsigned int);
      channelOffset += sizeof(unsigned int);
      exrImage->images[c] = reinterpret_cast<unsigned char *>((
          unsigned int *)malloc(sizeof(unsigned int) * dataWidth * dataHeight));
    } else {
      assert(0);
    }
  }

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int y = 0; y < numBlocks; y++) {
    const unsigned char *dataPtr =
        reinterpret_cast<const unsigned char *>(head + offsets[y]);
    // 4 byte: scan line
    // 4 byte: data size
    // ~     : pixel data(uncompressed or compressed)
    int lineNo;
    memcpy(&lineNo, dataPtr, sizeof(int));
    int dataLen;
    memcpy(&dataLen, dataPtr + 4, sizeof(int));
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&lineNo));
      swap4(reinterpret_cast<unsigned int *>(&dataLen));
    }

    int endLineNo = (std::min)(lineNo + numScanlineBlocks, dataHeight);

    int numLines = endLineNo - lineNo;

    if (compressionType == 4) { // PIZ
      // Allocate original data size.
      std::vector<unsigned char> outBuf(dataWidth * numLines * pixelDataSize);
      unsigned int dstLen;
      size_t tmpBufLen = dataWidth * numLines * pixelDataSize;

      DecompressPiz(reinterpret_cast<unsigned char *>(&outBuf.at(0)), dstLen,
                    dataPtr + 8, tmpBufLen, channels, dataWidth, numLines);

      bool isBigEndian = IsBigEndian();

      // For ZIP_COMPRESSION:
      //   pixel sample data for channel 0 for scanline 0
      //   pixel sample data for channel 1 for scanline 0
      //   pixel sample data for channel ... for scanline 0
      //   pixel sample data for channel n for scanline 0
      //   pixel sample data for channel 0 for scanline 1
      //   pixel sample data for channel 1 for scanline 1
      //   pixel sample data for channel ... for scanline 1
      //   pixel sample data for channel n for scanline 1
      //   ...
      for (int c = 0; c < numChannels; c++) {

        if (channels[c].pixelType == TINYEXR_PIXELTYPE_HALF) {
          for (int v = 0; v < numLines; v++) {
            const unsigned short *linePtr = reinterpret_cast<unsigned short *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {
              FP16 hf;

              hf.u = linePtr[u];

              if (isBigEndian) {
                swap2(reinterpret_cast<unsigned short *>(&hf.u));
              }

              if (exrImage->requested_pixel_types[c] ==
                  TINYEXR_PIXELTYPE_HALF) {
                unsigned short *image =
                    reinterpret_cast<unsigned short **>(exrImage->images)[c];
                if (lineOrder == 0) {
                  image += (lineNo + v) * dataWidth + u;
                } else {
                  image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
                }
                *image = hf.u;
              } else { // HALF -> FLOAT
                FP32 f32 = half_to_float(hf);
                float *image = reinterpret_cast<float **>(exrImage->images)[c];
                if (lineOrder == 0) {
                  image += (lineNo + v) * dataWidth + u;
                } else {
                  image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
                }
                *image = f32.f;
              }
            }
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_UINT) {

          assert(exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_UINT);

          for (int v = 0; v < numLines; v++) {
            const unsigned int *linePtr = reinterpret_cast<unsigned int *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {

              unsigned int val = linePtr[u];

              if (isBigEndian) {
                swap4(&val);
              }

              unsigned int *image =
                  reinterpret_cast<unsigned int **>(exrImage->images)[c];
              if (lineOrder == 0) {
                image += (lineNo + v) * dataWidth + u;
              } else {
                image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
              }
              *image = val;
            }
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_FLOAT) {
          assert(exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_FLOAT);
          for (int v = 0; v < numLines; v++) {
            const float *linePtr = reinterpret_cast<float *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {

              float val = linePtr[u];

              if (isBigEndian) {
                swap4(reinterpret_cast<unsigned int *>(&val));
              }

              float *image = reinterpret_cast<float **>(exrImage->images)[c];
              if (lineOrder == 0) {
                image += (lineNo + v) * dataWidth + u;
              } else {
                image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
              }
              *image = val;
            }
          }
        } else {
          assert(0);
        }
      }

      //	mwkm, ZIPS or ZIP both good to go
    } else if (compressionType == 2 || compressionType == 3) { // ZIP

      // Allocate original data size.
      std::vector<unsigned char> outBuf(dataWidth * numLines * pixelDataSize);

      unsigned long dstLen = outBuf.size();
      DecompressZip(reinterpret_cast<unsigned char *>(&outBuf.at(0)), dstLen,
                    dataPtr + 8, dataLen);


      bool isBigEndian = IsBigEndian();

      // For ZIP_COMPRESSION:
      //   pixel sample data for channel 0 for scanline 0
      //   pixel sample data for channel 1 for scanline 0
      //   pixel sample data for channel ... for scanline 0
      //   pixel sample data for channel n for scanline 0
      //   pixel sample data for channel 0 for scanline 1
      //   pixel sample data for channel 1 for scanline 1
      //   pixel sample data for channel ... for scanline 1
      //   pixel sample data for channel n for scanline 1
      //   ...
      for (int c = 0; c < numChannels; c++) {

        if (channels[c].pixelType == TINYEXR_PIXELTYPE_HALF) {
          for (int v = 0; v < numLines; v++) {
            const unsigned short *linePtr = reinterpret_cast<unsigned short *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {
              FP16 hf;

              hf.u = linePtr[u];

              if (isBigEndian) {
                swap2(reinterpret_cast<unsigned short *>(&hf.u));
              }

              if (exrImage->requested_pixel_types[c] ==
                  TINYEXR_PIXELTYPE_HALF) {
                unsigned short *image =
                    reinterpret_cast<unsigned short **>(exrImage->images)[c];
                if (lineOrder == 0) {
                  image += (lineNo + v) * dataWidth + u;
                } else {
                  image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
                }
                *image = hf.u;
              } else { // HALF -> FLOAT
                FP32 f32 = half_to_float(hf);
                float *image = reinterpret_cast<float **>(exrImage->images)[c];
                if (lineOrder == 0) {
                  image += (lineNo + v) * dataWidth + u;
                } else {
                  image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
                }
                *image = f32.f;
              }
            }
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_UINT) {

          assert(exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_UINT);

          for (int v = 0; v < numLines; v++) {
            const unsigned int *linePtr = reinterpret_cast<unsigned int *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {

              unsigned int val = linePtr[u];

              if (isBigEndian) {
                swap4(&val);
              }

              unsigned int *image =
                  reinterpret_cast<unsigned int **>(exrImage->images)[c];
              if (lineOrder == 0) {
                image += (lineNo + v) * dataWidth + u;
              } else {
                image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
              }
              *image = val;
            }
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_FLOAT) {
          assert(exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_FLOAT);
          for (int v = 0; v < numLines; v++) {
            const float *linePtr = reinterpret_cast<float *>(
                &outBuf.at(v * pixelDataSize * dataWidth +
                           channelOffsetList[c] * dataWidth));
            for (int u = 0; u < dataWidth; u++) {

              float val = linePtr[u];

              if (isBigEndian) {
                swap4(reinterpret_cast<unsigned int *>(&val));
              }

              float *image = reinterpret_cast<float **>(exrImage->images)[c];
              if (lineOrder == 0) {
                image += (lineNo + v) * dataWidth + u;
              } else {
                image += (dataHeight - 1 - (lineNo + v)) * dataWidth + u;
              }
              *image = val;
            }
          }
        } else {
          assert(0);
        }
      }

    } else if (compressionType == 0) { // No compression

      bool isBigEndian = IsBigEndian();

      for (int c = 0; c < numChannels; c++) {

        if (channels[c].pixelType == TINYEXR_PIXELTYPE_HALF) {

          const unsigned short *linePtr =
              reinterpret_cast<const unsigned short *>(
                  dataPtr + 8 + c * dataWidth * sizeof(unsigned short));

          if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_HALF) {
            unsigned short *outLine =
                reinterpret_cast<unsigned short *>(exrImage->images[c]);
            if (lineOrder == 0) {
              outLine += y * dataWidth;
            } else {
              outLine += (dataHeight - 1 - y) * dataWidth;
            }

            for (int u = 0; u < dataWidth; u++) {
              FP16 hf;

              hf.u = linePtr[u];

              if (isBigEndian) {
                swap2(reinterpret_cast<unsigned short *>(&hf.u));
              }

              outLine[u] = hf.u;
            }
          } else if (exrImage->requested_pixel_types[c] ==
                     TINYEXR_PIXELTYPE_FLOAT) {
            float *outLine = reinterpret_cast<float *>(exrImage->images[c]);
            if (lineOrder == 0) {
              outLine += y * dataWidth;
            } else {
              outLine += (dataHeight - 1 - y) * dataWidth;
            }

            for (int u = 0; u < dataWidth; u++) {
              FP16 hf;

              hf.u = linePtr[u];

              if (isBigEndian) {
                swap2(reinterpret_cast<unsigned short *>(&hf.u));
              }

              FP32 f32 = half_to_float(hf);

              outLine[u] = f32.f;
            }
          } else {
            assert(0);
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_FLOAT) {

          const float *linePtr = reinterpret_cast<const float *>(
              dataPtr + 8 + c * dataWidth * sizeof(float));

          float *outLine = reinterpret_cast<float *>(exrImage->images[c]);
          if (lineOrder == 0) {
            outLine += y * dataWidth;
          } else {
            outLine += (dataHeight - 1 - y) * dataWidth;
          }

          for (int u = 0; u < dataWidth; u++) {
            float val = linePtr[u];

            if (isBigEndian) {
              swap4(reinterpret_cast<unsigned int *>(&val));
            }

            outLine[u] = val;
          }
        } else if (channels[c].pixelType == TINYEXR_PIXELTYPE_UINT) {

          const unsigned int *linePtr = reinterpret_cast<const unsigned int *>(
              dataPtr + 8 + c * dataWidth * sizeof(unsigned int));

          unsigned int *outLine =
              reinterpret_cast<unsigned int *>(exrImage->images[c]);
          if (lineOrder == 0) {
            outLine += y * dataWidth;
          } else {
            outLine += (dataHeight - 1 - y) * dataWidth;
          }

          for (int u = 0; u < dataWidth; u++) {
            unsigned int val = linePtr[u];

            if (isBigEndian) {
              swap4(reinterpret_cast<unsigned int *>(&val));
            }

            outLine[u] = val;
          }
        }
      }
    }
  } // omp parallel

  {
    exrImage->channel_names =
        (const char **)malloc(sizeof(const char *) * numChannels);
    for (int c = 0; c < numChannels; c++) {
#ifdef _WIN32
      exrImage->channel_names[c] = _strdup(channels[c].name.c_str());
#else
      exrImage->channel_names[c] = strdup(channels[c].name.c_str());
#endif
    }
    exrImage->num_channels = numChannels;

    exrImage->width = dataWidth;
    exrImage->height = dataHeight;

    // Fill with requested_pixel_types.
    exrImage->pixel_types = (int *)malloc(sizeof(int *) * numChannels);
    for (int c = 0; c < numChannels; c++) {
      exrImage->pixel_types[c] = exrImage->requested_pixel_types[c];
    }
  }

  return 0; // OK
}

// @deprecated
#if 0
int SaveEXR(const float *in_rgba, int width, int height, const char *filename,
            const char **err) {
  if (in_rgba == NULL || filename == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot write a file.";
    }
    return -1;
  }

  // Header
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};
    size_t n = fwrite(header, 1, 4, fp);
    assert(n == 4);
  }

  // Version, scanline.
  {
    const char marker[] = {2, 0, 0, 0};
    size_t n = fwrite(marker, 1, 4, fp);
    assert(n == 4);
  }

  int numScanlineBlocks = 16; // 16 for ZIP compression.

  // Write attributes.
  {
    unsigned char data[] = {
        'A', 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,   0,   'B',
        0,   1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,   'G', 0,
        1,   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 'R', 0,   1,
        0,   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}; // last 0 =
                                                           // terminator.

    WriteAttribute(fp, "channels", "chlist", data, 18 * 4 + 1); // +1 = null
  }

  {
    int compressionType = 3; // ZIP compression
    WriteAttribute(fp, "compression", "compression",
                   reinterpret_cast<const unsigned char *>(&compressionType),
                   1);
  }

  {
    int data[4] = {0, 0, width - 1, height - 1};
    WriteAttribute(fp, "dataWindow", "box2i",
                   reinterpret_cast<const unsigned char *>(data),
                   sizeof(int) * 4);
    WriteAttribute(fp, "displayWindow", "box2i",
                   reinterpret_cast<const unsigned char *>(data),
                   sizeof(int) * 4);
  }

  {
    unsigned char lineOrder = 0; // increasingY
    WriteAttribute(fp, "lineOrder", "lineOrder", &lineOrder, 1);
  }

  {
    float aspectRatio = 1.0f;
    WriteAttribute(fp, "pixelAspectRatio", "float",
                   reinterpret_cast<const unsigned char *>(&aspectRatio),
                   sizeof(float));
  }

  {
    float center[2] = {0.0f, 0.0f};
    WriteAttribute(fp, "screenWindowCenter", "v2f",
                   reinterpret_cast<const unsigned char *>(center),
                   2 * sizeof(float));
  }

  {
    float w = (float)width;
    WriteAttribute(fp, "screenWindowWidth", "float",
                   reinterpret_cast<const unsigned char *>(&w), sizeof(float));
  }

  { // end of header
    unsigned char e = 0;
    fwrite(&e, 1, 1, fp);
  }

  int numBlocks = height / numScanlineBlocks;
  if (numBlocks * numScanlineBlocks < height) {
    numBlocks++;
  }

  std::vector<long long> offsets(numBlocks);

  size_t headerSize = ftell(fp); // sizeof(header)
  long long offset =
      headerSize +
      numBlocks * sizeof(long long); // sizeof(header) + sizeof(offsetTable)

  std::vector<unsigned char> data;

  for (int i = 0; i < numBlocks; i++) {
    int startY = numScanlineBlocks * i;
    int endY = (std::min)(numScanlineBlocks * (i + 1), height);
    int h = endY - startY;

    std::vector<unsigned short> buf(4 * width * h);

    for (int y = 0; y < h; y++) {
      for (int x = 0; x < width; x++) {
        FP32 r, g, b, a;
        r.f = in_rgba[4 * ((y + startY) * width + x) + 0];
        g.f = in_rgba[4 * ((y + startY) * width + x) + 1];
        b.f = in_rgba[4 * ((y + startY) * width + x) + 2];
        a.f = in_rgba[4 * ((y + startY) * width + x) + 3];

        FP16 hr, hg, hb, ha;
        hr = float_to_half_full(r);
        hg = float_to_half_full(g);
        hb = float_to_half_full(b);
        ha = float_to_half_full(a);

        // Assume increasing Y
        buf[4 * y * width + 3 * width + x] = hr.u;
        buf[4 * y * width + 2 * width + x] = hg.u;
        buf[4 * y * width + 1 * width + x] = hb.u;
        buf[4 * y * width + 0 * width + x] = ha.u;
      }
    }

    int bound = miniz::mz_compressBound(buf.size() * sizeof(unsigned short));

    std::vector<unsigned char> block(
        miniz::mz_compressBound(buf.size() * sizeof(unsigned short)));
    unsigned long long outSize = block.size();

    CompressZip(&block.at(0), outSize,
                reinterpret_cast<const unsigned char *>(&buf.at(0)),
                buf.size() * sizeof(unsigned short));

    // 4 byte: scan line
    // 4 byte: data size
    // ~     : pixel data(compressed)
    std::vector<unsigned char> header(8);
    unsigned int dataLen = outSize; // truncate
    memcpy(&header.at(0), &startY, sizeof(int));
    memcpy(&header.at(4), &dataLen, sizeof(unsigned int));

    data.insert(data.end(), header.begin(), header.end());
    data.insert(data.end(), block.begin(), block.begin() + dataLen);

    offsets[i] = offset;
    offset += dataLen + 8; // 8 = sizeof(blockHeader)
  }

  fwrite(&offsets.at(0), 1, sizeof(unsigned long long) * numBlocks, fp);

  fwrite(&data.at(0), 1, data.size(), fp);

  fclose(fp);

  return 0; // OK
}
#endif

size_t SaveMultiChannelEXRToMemory(const EXRImage *exrImage,
                                   unsigned char **memory_out,
                                   const char **err) {
  if (exrImage == NULL || memory_out == NULL || exrImage->compression < 0 ||
      exrImage->compression > TINYEXR_COMPRESSIONTYPE_PIZ) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return 0;
  }

  std::vector<unsigned char> memory;

  // Header
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};
    memory.insert(memory.end(), header, header + 4);
  }

  // Version, scanline.
  {
    const char marker[] = {2, 0, 0, 0};
    memory.insert(memory.end(), marker, marker + 4);
  }

  int numScanlineBlocks = 1;
  if (exrImage->compression == TINYEXR_COMPRESSIONTYPE_ZIP) {
    numScanlineBlocks = 16;
  } else if (exrImage->compression == TINYEXR_COMPRESSIONTYPE_PIZ) {
    numScanlineBlocks = 32;
  }

  // Write attributes.
  {
    std::vector<unsigned char> data;

    std::vector<ChannelInfo> channels;
    for (int c = 0; c < exrImage->num_channels; c++) {
      ChannelInfo info;
      info.pLinear = 0;
      info.pixelType = exrImage->requested_pixel_types[c];
      info.xSampling = 1;
      info.ySampling = 1;
      info.name = std::string(exrImage->channel_names[c]);
      channels.push_back(info);
    }

    WriteChannelInfo(data, channels);

    WriteAttributeToMemory(memory, "channels", "chlist", &data.at(0),
                           data.size()); // +1 = null
  }

  {
    int comp = exrImage->compression;
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&comp));
    }
    WriteAttributeToMemory(memory, "compression", "compression",
                           reinterpret_cast<const unsigned char *>(&comp), 1);
  }

  {
    int data[4] = {0, 0, exrImage->width - 1, exrImage->height - 1};
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&data[0]));
      swap4(reinterpret_cast<unsigned int *>(&data[1]));
      swap4(reinterpret_cast<unsigned int *>(&data[2]));
      swap4(reinterpret_cast<unsigned int *>(&data[3]));
    }
    WriteAttributeToMemory(memory, "dataWindow", "box2i",
                           reinterpret_cast<const unsigned char *>(data),
                           sizeof(int) * 4);
    WriteAttributeToMemory(memory, "displayWindow", "box2i",
                           reinterpret_cast<const unsigned char *>(data),
                           sizeof(int) * 4);
  }

  {
    unsigned char lineOrder = 0; // increasingY
    WriteAttributeToMemory(memory, "lineOrder", "lineOrder", &lineOrder, 1);
  }

  {
    float aspectRatio = 1.0f;
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&aspectRatio));
    }
    WriteAttributeToMemory(
        memory, "pixelAspectRatio", "float",
        reinterpret_cast<const unsigned char *>(&aspectRatio), sizeof(float));
  }

  {
    float center[2] = {0.0f, 0.0f};
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&center[0]));
      swap4(reinterpret_cast<unsigned int *>(&center[1]));
    }
    WriteAttributeToMemory(memory, "screenWindowCenter", "v2f",
                           reinterpret_cast<const unsigned char *>(center),
                           2 * sizeof(float));
  }

  {
    float w = (float)exrImage->width;
    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&w));
    }
    WriteAttributeToMemory(memory, "screenWindowWidth", "float",
                           reinterpret_cast<const unsigned char *>(&w),
                           sizeof(float));
  }

  // Custom attributes
  if (exrImage->num_custom_attributes > 0) {
    // @todo { endian }
    for (int i = 0; i < exrImage->num_custom_attributes; i++) {
      WriteAttributeToMemory(memory, exrImage->custom_attributes[i].name,
                             exrImage->custom_attributes[i].type,
                             reinterpret_cast<const unsigned char *>(
                                 &exrImage->custom_attributes[i].value),
                             exrImage->custom_attributes[i].size);
    }
  }

  { // end of header
    unsigned char e = 0;
    memory.push_back(e);
  }

  int numBlocks = exrImage->height / numScanlineBlocks;
  if (numBlocks * numScanlineBlocks < exrImage->height) {
    numBlocks++;
  }

  std::vector<long long> offsets(numBlocks);

  size_t headerSize = memory.size();
  long long offset =
      headerSize +
      numBlocks * sizeof(long long); // sizeof(header) + sizeof(offsetTable)

  std::vector<unsigned char> data;

  bool isBigEndian = IsBigEndian();

  std::vector<std::vector<unsigned char> > dataList(numBlocks);
  std::vector<size_t> channelOffsetList(exrImage->num_channels);

  int pixelDataSize = 0;
  size_t channelOffset = 0;
  for (int c = 0; c < exrImage->num_channels; c++) {
    channelOffsetList[c] = channelOffset;
    if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_HALF) {
      pixelDataSize += sizeof(unsigned short);
      channelOffset += sizeof(unsigned short);
    } else if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_FLOAT) {
      pixelDataSize += sizeof(float);
      channelOffset += sizeof(float);
    } else if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_UINT) {
      pixelDataSize += sizeof(unsigned int);
      channelOffset += sizeof(unsigned int);
    } else {
      assert(0);
    }
  }

#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (int i = 0; i < numBlocks; i++) {
    int startY = numScanlineBlocks * i;
    int endY = (std::min)(numScanlineBlocks * (i + 1), exrImage->height);
    int h = endY - startY;

    std::vector<unsigned char> buf(exrImage->width * h * pixelDataSize);

    for (int c = 0; c < exrImage->num_channels; c++) {
      if (exrImage->pixel_types[c] == TINYEXR_PIXELTYPE_HALF) {

        if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_FLOAT) {
          for (int y = 0; y < h; y++) {
            for (int x = 0; x < exrImage->width; x++) {
              FP16 h16;
              h16.u = reinterpret_cast<unsigned short **>(
                  exrImage->images)[c][(y + startY) * exrImage->width + x];

              FP32 f32 = half_to_float(h16);

              if (isBigEndian) {
                swap4(reinterpret_cast<unsigned int *>(&f32.f));
              }

              // Assume increasing Y
              float *linePtr = reinterpret_cast<float *>(
                  &buf.at(pixelDataSize * y * exrImage->width +
                          channelOffsetList[c] * exrImage->width));
              linePtr[x] = f32.f;
            }
          }
        } else if (exrImage->requested_pixel_types[c] ==
                   TINYEXR_PIXELTYPE_HALF) {
          for (int y = 0; y < h; y++) {
            for (int x = 0; x < exrImage->width; x++) {
              unsigned short val = reinterpret_cast<unsigned short **>(
                  exrImage->images)[c][(y + startY) * exrImage->width + x];

              if (isBigEndian) {
                swap2(&val);
              }

              // Assume increasing Y
              unsigned short *linePtr = reinterpret_cast<unsigned short *>(
                  &buf.at(pixelDataSize * y * exrImage->width +
                          channelOffsetList[c] * exrImage->width));
              linePtr[x] = val;
            }
          }
        } else {
          assert(0);
        }

      } else if (exrImage->pixel_types[c] == TINYEXR_PIXELTYPE_FLOAT) {

        if (exrImage->requested_pixel_types[c] == TINYEXR_PIXELTYPE_HALF) {
          for (int y = 0; y < h; y++) {
            for (int x = 0; x < exrImage->width; x++) {
              FP32 f32;
              f32.f = reinterpret_cast<float **>(
                  exrImage->images)[c][(y + startY) * exrImage->width + x];

              FP16 h16;
              h16 = float_to_half_full(f32);

              if (isBigEndian) {
                swap2(reinterpret_cast<unsigned short *>(&h16.u));
              }

              // Assume increasing Y
              unsigned short *linePtr = reinterpret_cast<unsigned short *>(
                  &buf.at(pixelDataSize * y * exrImage->width +
                          channelOffsetList[c] * exrImage->width));
              linePtr[x] = h16.u;
            }
          }
        } else if (exrImage->requested_pixel_types[c] ==
                   TINYEXR_PIXELTYPE_FLOAT) {
          for (int y = 0; y < h; y++) {
            for (int x = 0; x < exrImage->width; x++) {
              float val = reinterpret_cast<float **>(
                  exrImage->images)[c][(y + startY) * exrImage->width + x];

              if (isBigEndian) {
                swap4(reinterpret_cast<unsigned int *>(&val));
              }

              // Assume increasing Y
              float *linePtr = reinterpret_cast<float *>(
                  &buf.at(pixelDataSize * y * exrImage->width +
                          channelOffsetList[c] * exrImage->width));
              linePtr[x] = val;
            }
          }
        } else {
          assert(0);
        }
      } else if (exrImage->pixel_types[c] == TINYEXR_PIXELTYPE_UINT) {

        for (int y = 0; y < h; y++) {
          for (int x = 0; x < exrImage->width; x++) {
            unsigned int val = reinterpret_cast<unsigned int **>(
                exrImage->images)[c][(y + startY) * exrImage->width + x];

            if (isBigEndian) {
              swap4(&val);
            }

            // Assume increasing Y
            unsigned int *linePtr = reinterpret_cast<unsigned int *>(
                &buf.at(pixelDataSize * y * exrImage->width +
                        channelOffsetList[c] * exrImage->width));
            linePtr[x] = val;
          }
        }
      }
    }

    if (exrImage->compression == TINYEXR_COMPRESSIONTYPE_NONE) {

      // 4 byte: scan line
      // 4 byte: data size
      // ~     : pixel data(uncompressed)
      std::vector<unsigned char> header(8);
      unsigned int dataLen = (unsigned int)buf.size();
      memcpy(&header.at(0), &startY, sizeof(int));
      memcpy(&header.at(4), &dataLen, sizeof(unsigned int));

      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&header.at(0)));
        swap4(reinterpret_cast<unsigned int *>(&header.at(4)));
      }

      dataList[i].insert(dataList[i].end(), header.begin(), header.end());
      dataList[i].insert(dataList[i].end(), buf.begin(), buf.begin() + dataLen);

    } else if ((exrImage->compression == TINYEXR_COMPRESSIONTYPE_ZIPS) ||
               (exrImage->compression == TINYEXR_COMPRESSIONTYPE_ZIP)) {

      std::vector<unsigned char> block(miniz::mz_compressBound(buf.size()));
      unsigned long long outSize = block.size();

      CompressZip(&block.at(0), outSize,
                  reinterpret_cast<const unsigned char *>(&buf.at(0)),
                  buf.size());

      // 4 byte: scan line
      // 4 byte: data size
      // ~     : pixel data(compressed)
      std::vector<unsigned char> header(8);
      unsigned int dataLen = outSize; // truncate
      memcpy(&header.at(0), &startY, sizeof(int));
      memcpy(&header.at(4), &dataLen, sizeof(unsigned int));

      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&header.at(0)));
        swap4(reinterpret_cast<unsigned int *>(&header.at(4)));
      }

      dataList[i].insert(dataList[i].end(), header.begin(), header.end());
      dataList[i].insert(dataList[i].end(), block.begin(),
                         block.begin() + dataLen);

    } else if (exrImage->compression == TINYEXR_COMPRESSIONTYPE_PIZ) {
      // @todo
      assert(0);
    } else {
      assert(0);
    }

  } // omp parallel

  for (int i = 0; i < numBlocks; i++) {

    data.insert(data.end(), dataList[i].begin(), dataList[i].end());

    offsets[i] = offset;
    if (IsBigEndian()) {
      swap8(reinterpret_cast<unsigned long long *>(&offsets[i]));
    }
    offset += dataList[i].size();
  }

  {
    memory.insert(memory.end(),
                  reinterpret_cast<unsigned char *>(&offsets.at(0)),
                  reinterpret_cast<unsigned char *>(&offsets.at(0)) +
                      sizeof(unsigned long long) * numBlocks);
  }

  { memory.insert(memory.end(), data.begin(), data.end()); }

  assert(memory.size() > 0);

  (*memory_out) = (unsigned char *)malloc(memory.size());
  memcpy((*memory_out), &memory.at(0), memory.size());

  return memory.size(); // OK
}

int SaveMultiChannelEXRToFile(const EXRImage *exrImage, const char *filename,
                              const char **err) {
  if (exrImage == NULL || filename == NULL || exrImage->compression < 0 ||
      exrImage->compression > TINYEXR_COMPRESSIONTYPE_PIZ) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot write a file.";
    }
    return -1;
  }

  unsigned char *mem = NULL;
  size_t mem_size = SaveMultiChannelEXRToMemory(exrImage, &mem, err);

  if ((mem_size > 0) && mem) {

    fwrite(mem, 1, mem_size, fp);
  }
  free(mem);

  fclose(fp);

  return 0; // OK
}

int LoadDeepEXR(DeepImage *deepImage, const char *filename, const char **err) {
  if (deepImage == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot read file.";
    }
    return -1;
  }

  size_t filesize;
  // Compute size
  fseek(fp, 0, SEEK_END);
  filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  if (filesize == 0) {
    fclose(fp);
    if (err) {
      (*err) = "File size is zero.";
    }
    return -1;
  }

  std::vector<char> buf(filesize); // @todo { use mmap }
  {
    size_t ret;
    ret = fread(&buf[0], 1, filesize, fp);
    assert(ret == filesize);
    (void)ret;
  }
  fclose(fp);

  const char *head = &buf[0];
  const char *marker = &buf[0];

  // Header check.
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};

    if (memcmp(marker, header, 4) != 0) {
      if (err) {
        (*err) = "Header mismatch.";
      }
      return -3;
    }
    marker += 4;
  }

  // Version, scanline.
  {
    // ver 2.0, scanline, deep bit on(0x800)
    // must be [2, 0, 0, 0]
    if (marker[0] != 2 || marker[1] != 8 || marker[2] != 0 || marker[3] != 0) {
      if (err) {
        (*err) = "Unsupported version or scanline.";
      }
      return -4;
    }

    marker += 4;
  }

  int dx = -1;
  int dy = -1;
  int dw = -1;
  int dh = -1;
  int numScanlineBlocks = 1; // 16 for ZIP compression.
  int compressionType = -1;
  int numChannels = -1;
  std::vector<ChannelInfo> channels;

  // Read attributes
  for (;;) {
    std::string attrName;
    std::string attrType;
    std::vector<unsigned char> data;
    const char *marker_next = ReadAttribute(attrName, attrType, data, marker);
    if (marker_next == NULL) {
      marker++; // skip '\0'
      break;
    }

    if (attrName.compare("compression") == 0) {
      // must be 0:No compression, 1: RLE, 2: ZIPs or 3: ZIP
      if (data[0] > 3) {
        if (err) {
          (*err) = "Unsupported compression type.";
        }
        return -5;
      }

      compressionType = data[0];

      if (compressionType == 3) { // ZIP
        numScanlineBlocks = 16;
      }

    } else if (attrName.compare("channels") == 0) {

      // name: zero-terminated string, from 1 to 255 bytes long
      // pixel type: int, possible values are: UINT = 0 HALF = 1 FLOAT = 2
      // pLinear: unsigned char, possible values are 0 and 1
      // reserved: three chars, should be zero
      // xSampling: int
      // ySampling: int

      ReadChannelInfo(channels, data);

      numChannels = channels.size();

      if (numChannels < 1) {
        if (err) {
          (*err) = "Invalid channels format.";
        }
        return -6;
      }

    } else if (attrName.compare("dataWindow") == 0) {
      memcpy(&dx, &data.at(0), sizeof(int));
      memcpy(&dy, &data.at(4), sizeof(int));
      memcpy(&dw, &data.at(8), sizeof(int));
      memcpy(&dh, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&dx));
        swap4(reinterpret_cast<unsigned int *>(&dy));
        swap4(reinterpret_cast<unsigned int *>(&dw));
        swap4(reinterpret_cast<unsigned int *>(&dh));
      }

    } else if (attrName.compare("displayWindow") == 0) {
      int x;
      int y;
      int w;
      int h;
      memcpy(&x, &data.at(0), sizeof(int));
      memcpy(&y, &data.at(4), sizeof(int));
      memcpy(&w, &data.at(8), sizeof(int));
      memcpy(&h, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&x));
        swap4(reinterpret_cast<unsigned int *>(&y));
        swap4(reinterpret_cast<unsigned int *>(&w));
        swap4(reinterpret_cast<unsigned int *>(&h));
      }
    }

    marker = marker_next;
  }

  assert(dx >= 0);
  assert(dy >= 0);
  assert(dw >= 0);
  assert(dh >= 0);
  assert(numChannels >= 1);

  int dataWidth = dw - dx + 1;
  int dataHeight = dh - dy + 1;

  std::vector<float> image(dataWidth * dataHeight * 4); // 4 = RGBA

  // Read offset tables.
  int numBlocks = dataHeight / numScanlineBlocks;
  if (numBlocks * numScanlineBlocks < dataHeight) {
    numBlocks++;
  }

  std::vector<long long> offsets(numBlocks);

  for (int y = 0; y < numBlocks; y++) {
    long long offset;
    memcpy(&offset, marker, sizeof(long long));
    if (IsBigEndian()) {
      swap8(reinterpret_cast<unsigned long long *>(&offset));
    }
    marker += sizeof(long long); // = 8
    offsets[y] = offset;
  }

  if (compressionType != 0 && compressionType != 2 && compressionType != 3) {
    if (err) {
      (*err) = "Unsupported format.";
    }
    return -10;
  }

  deepImage->image = (float ***)malloc(sizeof(float **) * numChannels);
  for (int c = 0; c < numChannels; c++) {
    deepImage->image[c] = (float **)malloc(sizeof(float *) * dataHeight);
    for (int y = 0; y < dataHeight; y++) {
    }
  }

  deepImage->offset_table = (int **)malloc(sizeof(int *) * dataHeight);
  for (int y = 0; y < dataHeight; y++) {
    deepImage->offset_table[y] = (int *)malloc(sizeof(int) * dataWidth);
  }

  for (int y = 0; y < numBlocks; y++) {
    const unsigned char *dataPtr =
        reinterpret_cast<const unsigned char *>(head + offsets[y]);

    // int: y coordinate
    // int64: packed size of pixel offset table
    // int64: packed size of sample data
    // int64: unpacked size of sample data
    // compressed pixel offset table
    // compressed sample data
    int lineNo;
    long long packedOffsetTableSize;
    long long packedSampleDataSize;
    long long unpackedSampleDataSize;
    memcpy(&lineNo, dataPtr, sizeof(int));
    memcpy(&packedOffsetTableSize, dataPtr + 4, sizeof(long long));
    memcpy(&packedSampleDataSize, dataPtr + 12, sizeof(long long));
    memcpy(&unpackedSampleDataSize, dataPtr + 20, sizeof(long long));

    if (IsBigEndian()) {
      swap4(reinterpret_cast<unsigned int *>(&lineNo));
      swap8(reinterpret_cast<unsigned long long *>(&packedOffsetTableSize));
      swap8(reinterpret_cast<unsigned long long *>(&packedSampleDataSize));
      swap8(reinterpret_cast<unsigned long long *>(&unpackedSampleDataSize));
    }

    std::vector<int> pixelOffsetTable(dataWidth);

    // decode pixel offset table.
    {
      unsigned long dstLen = pixelOffsetTable.size() * sizeof(int);
      DecompressZip(reinterpret_cast<unsigned char *>(&pixelOffsetTable.at(0)),
                    dstLen, dataPtr + 28, packedOffsetTableSize);

      assert(dstLen == pixelOffsetTable.size() * sizeof(int));
      for (int i = 0; i < dataWidth; i++) {
        deepImage->offset_table[y][i] = pixelOffsetTable[i];
      }
    }

    std::vector<unsigned char> sampleData(unpackedSampleDataSize);

    // decode sample data.
    {
      unsigned long dstLen = unpackedSampleDataSize;
      DecompressZip(reinterpret_cast<unsigned char *>(&sampleData.at(0)),
                    dstLen, dataPtr + 28 + packedOffsetTableSize,
                    packedSampleDataSize);
      assert(dstLen == (unsigned long)unpackedSampleDataSize);
    }

    // decode sample
    int sampleSize = -1;
    std::vector<int> channelOffsetList(numChannels);
    {
      int channelOffset = 0;
      for (int i = 0; i < numChannels; i++) {
        channelOffsetList[i] = channelOffset;
        if (channels[i].pixelType == TINYEXR_PIXELTYPE_UINT) { // UINT
          channelOffset += 4;
        } else if (channels[i].pixelType == TINYEXR_PIXELTYPE_HALF) { // half
          channelOffset += 2;
        } else if (channels[i].pixelType == TINYEXR_PIXELTYPE_FLOAT) { // float
          channelOffset += 4;
        } else {
          assert(0);
        }
      }
      sampleSize = channelOffset;
    }
    assert(sampleSize >= 2);

    assert((size_t)(pixelOffsetTable[dataWidth - 1] * sampleSize) ==
           sampleData.size());
    int samplesPerLine = sampleData.size() / sampleSize;

    //
    // Alloc memory
    //

    //
    // pixel data is stored as image[channels][pixel_samples]
    //
    {
      unsigned long long dataOffset = 0;
      for (int c = 0; c < numChannels; c++) {

        deepImage->image[c][y] =
            (float *)malloc(sizeof(float) * samplesPerLine);

        if (channels[c].pixelType == 0) { // UINT
          for (int x = 0; x < samplesPerLine; x++) {
            unsigned int ui = *reinterpret_cast<unsigned int *>(
                                  &sampleData.at(dataOffset + x * sizeof(int)));
            deepImage->image[c][y][x] = (float)ui; // @fixme
          }
          dataOffset += sizeof(unsigned int) * samplesPerLine;
        } else if (channels[c].pixelType == 1) { // half
          for (int x = 0; x < samplesPerLine; x++) {
            FP16 f16;
            f16.u = *reinterpret_cast<unsigned short *>(
                        &sampleData.at(dataOffset + x * sizeof(short)));
            FP32 f32 = half_to_float(f16);
            deepImage->image[c][y][x] = f32.f;
          }
          dataOffset += sizeof(short) * samplesPerLine;
        } else { // float
          for (int x = 0; x < samplesPerLine; x++) {
            float f = *reinterpret_cast<float *>(
                          &sampleData.at(dataOffset + x * sizeof(float)));
            deepImage->image[c][y][x] = f;
          }
          dataOffset += sizeof(float) * samplesPerLine;
        }
      }
    }

  } // y

  deepImage->width = dataWidth;
  deepImage->height = dataHeight;

  deepImage->channel_names =
      (const char **)malloc(sizeof(const char *) * numChannels);
  for (int c = 0; c < numChannels; c++) {
#ifdef _WIN32
    deepImage->channel_names[c] = _strdup(channels[c].name.c_str());
#else
    deepImage->channel_names[c] = strdup(channels[c].name.c_str());
#endif
  }
  deepImage->num_channels = numChannels;

  return 0; // OK
}

int SaveDeepEXR(const DeepImage *deepImage, const char *filename,
                const char **err) {
  if (deepImage == NULL || filename == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot write file.";
    }
    return -1;
  }

  // Write header check.
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};
    size_t n = fwrite(header, 1, 4, fp);
    if (n != 4) {
      if (err) {
        (*err) = "Header write failed.";
      }
      fclose(fp);
      return -3;
    }
  }

  // Version, scanline.
  {
    // ver 2.0, scanline, deep bit on(0x800)
    const char data[] = {2, 8, 0, 0};
    size_t n = fwrite(data, 1, 4, fp);
    if (n != 4) {
      if (err) {
        (*err) = "Flag write failed.";
      }
      fclose(fp);
      return -3;
    }
  }

  // Write attributes.
  {
    int data = 2; // ZIPS
    WriteAttribute(fp, "compression", "compression",
                   reinterpret_cast<const unsigned char *>(&data), sizeof(int));
  }

  {
    int data[4] = {0, 0, deepImage->width - 1, deepImage->height - 1};
    WriteAttribute(fp, "dataWindow", "box2i",
                   reinterpret_cast<const unsigned char *>(data),
                   sizeof(int) * 4);
    WriteAttribute(fp, "displayWindow", "box2i",
                   reinterpret_cast<const unsigned char *>(data),
                   sizeof(int) * 4);
  }

  int numScanlineBlocks = 1;
  // Write offset tables.
  int numBlocks = deepImage->height / numScanlineBlocks;
  if (numBlocks * numScanlineBlocks < deepImage->height) {
    numBlocks++;
  }

#if 0 // @todo
  std::vector<long long> offsets(numBlocks);

  //std::vector<int> pixelOffsetTable(dataWidth);

  // compress pixel offset table.
  {
      unsigned long dstLen = pixelOffsetTable.size() * sizeof(int);
      Compresses(reinterpret_cast<unsigned char *>(&pixelOffsetTable.at(0)),
                    dstLen, dataPtr + 28, packedOffsetTableSize);

      assert(dstLen == pixelOffsetTable.size() * sizeof(int));
      //      int ret =
      //          miniz::mz_uncompress(reinterpret_cast<unsigned char
      //          *>(&pixelOffsetTable.at(0)), &dstLen, dataPtr + 28,
      //          packedOffsetTableSize);
      //      printf("ret = %d, dstLen = %d\n", ret, (int)dstLen);
      //
      for (int i = 0; i < dataWidth; i++) {
        // printf("offt[%d] = %d\n", i, pixelOffsetTable[i]);
        deepImage->offset_table[y][i] = pixelOffsetTable[i];
      }
    }


  for (int y = 0; y < numBlocks; y++) {
    //long long offset = *(reinterpret_cast<const long long *>(marker));
    // printf("offset[%d] = %lld\n", y, offset);
    //marker += sizeof(long long); // = 8
    offsets[y] = offset;
  }

  // Write offset table.
  fwrite(&offsets.at(0), sizeof(long long), numBlocks, fp);

  for (int y = 0; y < numBlocks; y++) {
    const unsigned char *dataPtr =
        reinterpret_cast<const unsigned char *>(head + offsets[y]);

    // int: y coordinate
    // int64: packed size of pixel offset table
    // int64: packed size of sample data
    // int64: unpacked size of sample data
    // compressed pixel offset table
    // compressed sample data
    int lineNo = *reinterpret_cast<const int *>(dataPtr);
    long long packedOffsetTableSize =
        *reinterpret_cast<const long long *>(dataPtr + 4);
    long long packedSampleDataSize =
        *reinterpret_cast<const long long *>(dataPtr + 12);
    long long unpackedSampleDataSize =
        *reinterpret_cast<const long long *>(dataPtr + 20);
    // printf("line: %d, %lld/%lld/%lld\n", lineNo, packedOffsetTableSize,
    // packedSampleDataSize, unpackedSampleDataSize);

    int endLineNo = (std::min)(lineNo + numScanlineBlocks, dataHeight);

    int numLines = endLineNo - lineNo;
    // printf("numLines: %d\n", numLines);

    std::vector<int> pixelOffsetTable(dataWidth);

    // decode pixel offset table.
    {
      unsigned long dstLen = pixelOffsetTable.size() * sizeof(int);
      DecompressZip(reinterpret_cast<unsigned char *>(&pixelOffsetTable.at(0)),
                    dstLen, dataPtr + 28, packedOffsetTableSize);

      assert(dstLen == pixelOffsetTable.size() * sizeof(int));
      //      int ret =
      //          miniz::mz_uncompress(reinterpret_cast<unsigned char
      //          *>(&pixelOffsetTable.at(0)), &dstLen, dataPtr + 28,
      //          packedOffsetTableSize);
      //      printf("ret = %d, dstLen = %d\n", ret, (int)dstLen);
      //
      for (int i = 0; i < dataWidth; i++) {
        // printf("offt[%d] = %d\n", i, pixelOffsetTable[i]);
        deepImage->offset_table[y][i] = pixelOffsetTable[i];
      }
    }

    std::vector<unsigned char> sampleData(unpackedSampleDataSize);

    // decode sample data.
    {
      unsigned long dstLen = unpackedSampleDataSize;
      // printf("dstLen = %d\n", dstLen);
      // printf("srcLen = %d\n", packedSampleDataSize);
      DecompressZip(reinterpret_cast<unsigned char *>(&sampleData.at(0)),
                    dstLen, dataPtr + 28 + packedOffsetTableSize,
                    packedSampleDataSize);
      assert(dstLen == unpackedSampleDataSize);
    }

    // decode sample
    int sampleSize = -1;
    std::vector<int> channelOffsetList(numChannels);
    {
      int channelOffset = 0;
      for (int i = 0; i < numChannels; i++) {
        // printf("offt[%d] = %d\n", i, channelOffset);
        channelOffsetList[i] = channelOffset;
        if (channels[i].pixelType == 0) { // UINT
          channelOffset += 4;
        } else if (channels[i].pixelType == 1) { // half
          channelOffset += 2;
        } else if (channels[i].pixelType == 2) { // float
          channelOffset += 4;
        } else {
          assert(0);
        }
      }
      sampleSize = channelOffset;
    }
    assert(sampleSize >= 2);

    assert(pixelOffsetTable[dataWidth - 1] * sampleSize == sampleData.size());
    int samplesPerLine = sampleData.size() / sampleSize;

    //
    // Alloc memory
    //

    //
    // pixel data is stored as image[channels][pixel_samples]
    //
    {
      unsigned long long dataOffset = 0;
      for (int c = 0; c < numChannels; c++) {

        deepImage->image[c][y] =
            (float *)malloc(sizeof(float) * samplesPerLine);

        // unsigned int channelOffset = channelOffsetList[c];
        // unsigned int i = channelOffset;
        // printf("channel = %d. name = %s. ty = %d\n", c,
        // channels[c].name.c_str(), channels[c].pixelType);

        // printf("dataOffset = %d\n", (int)dataOffset);

        if (channels[c].pixelType == 0) { // UINT
          for (int x = 0; x < samplesPerLine; x++) {
            unsigned int ui = *reinterpret_cast<unsigned int *>(
                                  &sampleData.at(dataOffset + x * sizeof(int)));
            deepImage->image[c][y][x] = (float)ui; // @fixme
          }
          dataOffset += sizeof(unsigned int) * samplesPerLine;
        } else if (channels[c].pixelType == 1) { // half
          for (int x = 0; x < samplesPerLine; x++) {
            FP16 f16;
            f16.u = *reinterpret_cast<unsigned short *>(
                        &sampleData.at(dataOffset + x * sizeof(short)));
            FP32 f32 = half_to_float(f16);
            deepImage->image[c][y][x] = f32.f;
            // printf("c[%d]  f(half) = %f (0x%08x)\n", c, f32.f, f16.u);
          }
          dataOffset += sizeof(short) * samplesPerLine;
        } else { // float
          for (int x = 0; x < samplesPerLine; x++) {
            float f = *reinterpret_cast<float *>(
                          &sampleData.at(dataOffset + x * sizeof(float)));
            // printf("  f = %f(0x%08x)\n", f, *((unsigned int *)&f));
            deepImage->image[c][y][x] = f;
          }
          dataOffset += sizeof(float) * samplesPerLine;
        }
      }
      // printf("total: %d\n", dataOffset);
    }

  } // y
#endif
  fclose(fp);

  return 0; // OK
}

void InitEXRImage(EXRImage *exrImage) {
  if (exrImage == NULL) {
    return;
  }

  exrImage->num_custom_attributes = 0;
  exrImage->num_channels = 0;
  exrImage->channel_names = NULL;
  exrImage->images = NULL;
  exrImage->pixel_types = NULL;
  exrImage->requested_pixel_types = NULL;
  exrImage->compression = TINYEXR_COMPRESSIONTYPE_ZIP;
}

int FreeEXRImage(EXRImage *exrImage) {

  if (exrImage == NULL) {
    return -1; // Err
  }

  for (int i = 0; i < exrImage->num_channels; i++) {

    if (exrImage->channel_names && exrImage->channel_names[i]) {
      free((char *)exrImage->channel_names[i]); // remove const
    }

    if (exrImage->images && exrImage->images[i]) {
      free(exrImage->images[i]);
    }
  }

  if (exrImage->channel_names) {
    free(exrImage->channel_names);
  }

  if (exrImage->images) {
    free(exrImage->images);
  }

  if (exrImage->pixel_types) {
    free(exrImage->pixel_types);
  }

  if (exrImage->requested_pixel_types) {
    free(exrImage->requested_pixel_types);
  }

  for (int i = 0; i < exrImage->num_custom_attributes; i++) {
    if (exrImage->custom_attributes[i].name) {
      free(exrImage->custom_attributes[i].name);
    }
    if (exrImage->custom_attributes[i].type) {
      free(exrImage->custom_attributes[i].type);
    }
    if (exrImage->custom_attributes[i].value) {
      free(exrImage->custom_attributes[i].value);
    }
  }

  return 0;
}

int ParseMultiChannelEXRHeaderFromFile(EXRImage *exrImage, const char *filename,
                                       const char **err) {
  if (exrImage == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  FILE *fp = fopen(filename, "rb");
  if (!fp) {
    if (err) {
      (*err) = "Cannot read file.";
    }
    return -1;
  }

  size_t filesize;
  // Compute size
  fseek(fp, 0, SEEK_END);
  filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::vector<unsigned char> buf(filesize); // @todo { use mmap }
  {
    size_t ret;
    ret = fread(&buf[0], 1, filesize, fp);
    assert(ret == filesize);
    fclose(fp);
    (void)ret;
  }

  return ParseMultiChannelEXRHeaderFromMemory(exrImage, &buf.at(0), err);
}

int ParseMultiChannelEXRHeaderFromMemory(EXRImage *exrImage,
                                         const unsigned char *memory,
                                         const char **err) {
  if (exrImage == NULL || memory == NULL) {
    if (err) {
      (*err) = "Invalid argument.";
    }
    return -1;
  }

  const char *buf = reinterpret_cast<const char *>(memory);

  const char *marker = &buf[0];

  // Header check.
  {
    const char header[] = {0x76, 0x2f, 0x31, 0x01};

    if (memcmp(marker, header, 4) != 0) {
      if (err) {
        (*err) = "Header mismatch.";
      }
      return -3;
    }
    marker += 4;
  }

  // Version, scanline.
  {
    // must be [2, 0, 0, 0]
    if (marker[0] != 2 || marker[1] != 0 || marker[2] != 0 || marker[3] != 0) {
      if (err) {
        (*err) = "Unsupported version or scanline.";
      }
      return -4;
    }

    marker += 4;
  }

  int dx = -1;
  int dy = -1;
  int dw = -1;
  int dh = -1;
  int numChannels = -1;
  int displayWindow[4] = {-1, -1, -1, -1};    // @fixme.
  float screenWindowCenter[2] = {0.0f, 0.0f}; // @fixme
  float screenWindowWidth = 1.0f;             // @fixme
  float pixelAspectRatio = 1.0f;
  unsigned char lineOrder = 0; // 0 -> increasing y; 1 -> decreasing
  std::vector<ChannelInfo> channels;
  int compressionType = 0; // @fixme

  int numCustomAttributes = 0;
  std::vector<EXRAttribute> customAttribs;

  // Read attributes
  for (;;) {
    std::string attrName;
    std::string attrType;
    std::vector<unsigned char> data;
    const char *marker_next = ReadAttribute(attrName, attrType, data, marker);
    if (marker_next == NULL) {
      marker++; // skip '\0'
      break;
    }

    if (attrName.compare("compression") == 0) {
      // must be 0:No compression, 1: RLE, 2: ZIPs, 3: ZIP or 4: PIZ
      if (data[0] > TINYEXR_COMPRESSIONTYPE_PIZ) {
        if (err) {
          (*err) = "Unsupported compression type.";
        }
        return -5;
      }

      compressionType = data[0];

    } else if (attrName.compare("channels") == 0) {

      // name: zero-terminated string, from 1 to 255 bytes long
      // pixel type: int, possible values are: UINT = 0 HALF = 1 FLOAT = 2
      // pLinear: unsigned char, possible values are 0 and 1
      // reserved: three chars, should be zero
      // xSampling: int
      // ySampling: int

      ReadChannelInfo(channels, data);

      numChannels = channels.size();

      if (numChannels < 1) {
        if (err) {
          (*err) = "Invalid channels format.";
        }
        return -6;
      }

    } else if (attrName.compare("dataWindow") == 0) {
      memcpy(&dx, &data.at(0), sizeof(int));
      memcpy(&dy, &data.at(4), sizeof(int));
      memcpy(&dw, &data.at(8), sizeof(int));
      memcpy(&dh, &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&dx));
        swap4(reinterpret_cast<unsigned int *>(&dy));
        swap4(reinterpret_cast<unsigned int *>(&dw));
        swap4(reinterpret_cast<unsigned int *>(&dh));
      }
    } else if (attrName.compare("displayWindow") == 0) {
      memcpy(&displayWindow[0], &data.at(0), sizeof(int));
      memcpy(&displayWindow[1], &data.at(4), sizeof(int));
      memcpy(&displayWindow[2], &data.at(8), sizeof(int));
      memcpy(&displayWindow[3], &data.at(12), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[0]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[1]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[2]));
        swap4(reinterpret_cast<unsigned int *>(&displayWindow[3]));
      }
    } else if (attrName.compare("lineOrder") == 0) {
      int order;
      memcpy(&order, &data.at(0), sizeof(int));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&order));
      }
      lineOrder = (unsigned char)order;
    } else if (attrName.compare("pixelAspectRatio") == 0) {
      memcpy(&pixelAspectRatio, &data.at(0), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&pixelAspectRatio));
      }
    } else if (attrName.compare("screenWindowCenter") == 0) {
      memcpy(&screenWindowCenter[0], &data.at(0), sizeof(float));
      memcpy(&screenWindowCenter[1], &data.at(4), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&screenWindowCenter[0]));
        swap4(reinterpret_cast<unsigned int *>(&screenWindowCenter[1]));
      }
    } else if (attrName.compare("screenWindowWidth") == 0) {
      memcpy(&screenWindowWidth, &data.at(0), sizeof(float));
      if (IsBigEndian()) {
        swap4(reinterpret_cast<unsigned int *>(&screenWindowWidth));
      }
    } else {
      // Custom attribute(up to TINYEXR_MAX_ATTRIBUTES)
      if (numCustomAttributes < TINYEXR_MAX_ATTRIBUTES) {
        EXRAttribute attrib;
        attrib.name = strdup(attrName.c_str());
        attrib.type = strdup(attrType.c_str());
        attrib.size = data.size();
        attrib.value = (unsigned char *)malloc(data.size());
        memcpy((char *)attrib.value, &data.at(0), data.size());
        customAttribs.push_back(attrib);
      }
    }

    marker = marker_next;
  }

  assert(dx >= 0);
  assert(dy >= 0);
  assert(dw >= 0);
  assert(dh >= 0);
  assert(numChannels >= 1);

  int dataWidth = dw - dx + 1;
  int dataHeight = dh - dy + 1;

  {
    exrImage->channel_names =
        (const char **)malloc(sizeof(const char *) * numChannels);
    for (int c = 0; c < numChannels; c++) {
#ifdef _WIN32
      exrImage->channel_names[c] = _strdup(channels[c].name.c_str());
#else
      exrImage->channel_names[c] = strdup(channels[c].name.c_str());
#endif
    }
    exrImage->num_channels = numChannels;

    exrImage->width = dataWidth;
    exrImage->height = dataHeight;
    exrImage->pixel_aspect_ratio = pixelAspectRatio;
    exrImage->screen_window_center[0] = screenWindowCenter[0];
    exrImage->screen_window_center[1] = screenWindowCenter[1];
    exrImage->screen_window_width = screenWindowWidth;
    exrImage->display_window[0] = displayWindow[0];
    exrImage->display_window[1] = displayWindow[1];
    exrImage->display_window[2] = displayWindow[2];
    exrImage->display_window[3] = displayWindow[3];
    exrImage->data_window[0] = dx;
    exrImage->data_window[1] = dy;
    exrImage->data_window[2] = dw;
    exrImage->data_window[3] = dh;
    exrImage->line_order = lineOrder;
    exrImage->compression = compressionType;

    exrImage->pixel_types = (int *)malloc(sizeof(int) * numChannels);
    for (int c = 0; c < numChannels; c++) {
      exrImage->pixel_types[c] = channels[c].pixelType;
    }

    // Initially fill with values of `pixel-types`
    exrImage->requested_pixel_types = (int *)malloc(sizeof(int) * numChannels);
    for (int c = 0; c < numChannels; c++) {
      exrImage->requested_pixel_types[c] = channels[c].pixelType;
    }
  }

  if (numCustomAttributes > 0) {
    assert(customAttribs.size() < TINYEXR_MAX_ATTRIBUTES);
    exrImage->num_custom_attributes = numCustomAttributes;

    for (int i = 0; i < (int)customAttribs.size(); i++) {
      exrImage->custom_attributes[i] = customAttribs[i];
    }
  }

  return 0; // OK
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

#endif // __TINYEXR_H__
