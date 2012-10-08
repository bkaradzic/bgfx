//-----------------------------------------------------------------------------
// Product:     OpenCTM
// File:        stream.c
// Description: Stream I/O functions.
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

#include <stdlib.h>
#include <string.h>
#include <LzmaLib.h>
#include "openctm.h"
#include "internal.h"

#ifdef __DEBUG_
#include <stdio.h>
#endif

//-----------------------------------------------------------------------------
// _ctmStreamRead() - Read data from a stream.
//-----------------------------------------------------------------------------
CTMuint _ctmStreamRead(_CTMcontext * self, void * aBuf, CTMuint aCount)
{
  if(!self->mUserData || !self->mReadFn)
    return 0;

  return self->mReadFn(aBuf, aCount, self->mUserData);
}

//-----------------------------------------------------------------------------
// _ctmStreamWrite() - Write data to a stream.
//-----------------------------------------------------------------------------
CTMuint _ctmStreamWrite(_CTMcontext * self, void * aBuf, CTMuint aCount)
{
  if(!self->mUserData || !self->mWriteFn)
    return 0;

  return self->mWriteFn(aBuf, aCount, self->mUserData);
}

//-----------------------------------------------------------------------------
// _ctmStreamReadUINT() - Read an unsigned integer from a stream in a machine
// endian independent manner (for portability).
//-----------------------------------------------------------------------------
CTMuint _ctmStreamReadUINT(_CTMcontext * self)
{
  unsigned char buf[4];
  _ctmStreamRead(self, (void *) buf, 4);
  return ((CTMuint) buf[0]) |
         (((CTMuint) buf[1]) << 8) |
         (((CTMuint) buf[2]) << 16) |
         (((CTMuint) buf[3]) << 24);
}

//-----------------------------------------------------------------------------
// _ctmStreamWriteUINT() - Write an unsigned integer to a stream in a machine
// endian independent manner (for portability).
//-----------------------------------------------------------------------------
void _ctmStreamWriteUINT(_CTMcontext * self, CTMuint aValue)
{
  unsigned char buf[4];
  buf[0] = aValue & 0x000000ff;
  buf[1] = (aValue >> 8) & 0x000000ff;
  buf[2] = (aValue >> 16) & 0x000000ff;
  buf[3] = (aValue >> 24) & 0x000000ff;
  _ctmStreamWrite(self, (void *) buf, 4);
}

//-----------------------------------------------------------------------------
// _ctmStreamReadFLOAT() - Read a floating point value from a stream in a
// machine endian independent manner (for portability).
//-----------------------------------------------------------------------------
CTMfloat _ctmStreamReadFLOAT(_CTMcontext * self)
{
  union {
    CTMfloat f;
    CTMuint  i;
  } u;
  u.i = _ctmStreamReadUINT(self);
  return u.f;
}

//-----------------------------------------------------------------------------
// _ctmStreamWriteFLOAT() - Write a floating point value to a stream in a
// machine endian independent manner (for portability).
//-----------------------------------------------------------------------------
void _ctmStreamWriteFLOAT(_CTMcontext * self, CTMfloat aValue)
{
  union {
    CTMfloat f;
    CTMuint  i;
  } u;
  u.f = aValue;
  _ctmStreamWriteUINT(self, u.i);
}

//-----------------------------------------------------------------------------
// _ctmStreamReadSTRING() - Read a string value from a stream. The format of
// the string in the stream is: an unsigned integer (string length) followed by
// the string (without null termination).
//-----------------------------------------------------------------------------
void _ctmStreamReadSTRING(_CTMcontext * self, char ** aValue)
{
  CTMuint len;

  // Clear the old string
  if(*aValue)
  {
    free(*aValue);
    *aValue = (char *) 0;
  }

  // Get string length
  len = _ctmStreamReadUINT(self);

  // Read string
  if(len > 0)
  {
    *aValue = (char *) malloc(len + 1);
    if(*aValue)
    {
      _ctmStreamRead(self, (void *) *aValue, len);
      (*aValue)[len] = 0;
    }
  }
}

//-----------------------------------------------------------------------------
// _ctmStreamWriteSTRING() - Write a string value to a stream. The format of
// the string in the stream is: an unsigned integer (string length) followed by
// the string (without null termination).
//-----------------------------------------------------------------------------
void _ctmStreamWriteSTRING(_CTMcontext * self, const char * aValue)
{
  CTMuint len;

  // Get string length
  if(aValue)
    len = strlen(aValue);
  else
    len = 0;

  // Write string length
  _ctmStreamWriteUINT(self, len);

  // Write string
  if(len > 0)
    _ctmStreamWrite(self, (void *) aValue, len);
}

//-----------------------------------------------------------------------------
// _ctmStreamReadPackedInts() - Read an compressed binary integer data array
// from a stream, and uncompress it.
//-----------------------------------------------------------------------------
int _ctmStreamReadPackedInts(_CTMcontext * self, CTMint * aData,
  CTMuint aCount, CTMuint aSize, CTMint aSignedInts)
{
  size_t packedSize, unpackedSize;
  CTMuint i, k, x;
  CTMint value;
  unsigned char * packed, * tmp;
  unsigned char props[5];
  int lzmaRes;

  // Read packed data size from the stream
  packedSize = (size_t) _ctmStreamReadUINT(self);

  // Read LZMA compression props from the stream
  _ctmStreamRead(self, (void *) props, 5);

  // Allocate memory and read the packed data from the stream
  packed = (unsigned char *) malloc(packedSize);
  if(!packed)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  _ctmStreamRead(self, (void *) packed, packedSize);

  // Allocate memory for interleaved array
  tmp = (unsigned char *) malloc(aCount * aSize * 4);
  if(!tmp)
  {
    free(packed);
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Uncompress
  unpackedSize = aCount * aSize * 4;
  lzmaRes = LzmaUncompress(tmp, &unpackedSize, packed,
                           &packedSize, props, 5);

  // Free the packed array
  free(packed);

  // Error?
  if((lzmaRes != SZ_OK) || (unpackedSize != aCount * aSize * 4))
  {
    self->mError = CTM_LZMA_ERROR;
    free(tmp);
    return CTM_FALSE;
  }

  // Convert interleaved array to integers
  for(i = 0; i < aCount; ++ i)
  {
    for(k = 0; k < aSize; ++ k)
    {
      value = (CTMint) tmp[i + k * aCount + 3 * aCount * aSize] |
              (((CTMint) tmp[i + k * aCount + 2 * aCount * aSize]) << 8) |
              (((CTMint) tmp[i + k * aCount + aCount * aSize]) << 16) |
              (((CTMint) tmp[i + k * aCount]) << 24);
      // Convert signed magnitude to two's complement?
      if(aSignedInts)
      {
        x = (CTMuint) value;
        value = (x & 1) ? -(CTMint)((x + 1) >> 1) : (CTMint)(x >> 1);
      }
      aData[i * aSize + k] = value;
    }
  }

  // Free the interleaved array
  free(tmp);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmStreamWritePackedInts() - Compress a binary integer data array, and
// write it to a stream.
//-----------------------------------------------------------------------------
int _ctmStreamWritePackedInts(_CTMcontext * self, CTMint * aData,
  CTMuint aCount, CTMuint aSize, CTMint aSignedInts)
{
  int lzmaRes, lzmaAlgo;
  CTMuint i, k;
  CTMint value;
  size_t bufSize, outPropsSize;
  unsigned char * packed, outProps[5], *tmp;
#ifdef __DEBUG_
  CTMuint negCount = 0;  
#endif

  // Allocate memory for interleaved array
  tmp = (unsigned char *) malloc(aCount * aSize * 4);
  if(!tmp)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Convert integers to an interleaved array
  for(i = 0; i < aCount; ++ i)
  {
    for(k = 0; k < aSize; ++ k)
    {
      value = aData[i * aSize + k];
      // Convert two's complement to signed magnitude?
      if(aSignedInts)
        value = value < 0 ? -1 - (value << 1) : value << 1;
#ifdef __DEBUG_
      else if(value < 0)
        ++ negCount;
#endif
      tmp[i + k * aCount + 3 * aCount * aSize] = value & 0x000000ff;
      tmp[i + k * aCount + 2 * aCount * aSize] = (value >> 8) & 0x000000ff;
      tmp[i + k * aCount + aCount * aSize] = (value >> 16) & 0x000000ff;
      tmp[i + k * aCount] = (value >> 24) & 0x000000ff;
    }
  }

  // Allocate memory for the packed data
  bufSize = 1000 + aCount * aSize * 4;
  packed = (unsigned char *) malloc(bufSize);
  if(!packed)
  {
    free(tmp);
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Call LZMA to compress
  outPropsSize = 5;
  lzmaAlgo = (self->mCompressionLevel < 1 ? 0 : 1);
  lzmaRes = LzmaCompress(packed,
                         &bufSize,
                         (const unsigned char *) tmp,
                         aCount * aSize * 4,
                         outProps,
                         &outPropsSize,
                         self->mCompressionLevel, // Level (0-9)
                         0, -1, -1, -1, -1, -1,   // Default values (set by level)
                         lzmaAlgo                 // Algorithm (0 = fast, 1 = normal)
                        );

  // Free temporary array
  free(tmp);

  // Error?
  if(lzmaRes != SZ_OK)
  {
    self->mError = CTM_LZMA_ERROR;
    free(packed);
    return CTM_FALSE;
  }

#ifdef __DEBUG_
  printf("%d->%d bytes (%d negative words)\n", aCount * aSize * 4, (int) bufSize, negCount);
#endif

  // Write packed data size to the stream
  _ctmStreamWriteUINT(self, (CTMuint) bufSize);

  // Write LZMA compression props to the stream
  _ctmStreamWrite(self, (void *) outProps, 5);

  // Write the packed data to the stream
  _ctmStreamWrite(self, (void *) packed, (CTMuint) bufSize);

  // Free the packed data
  free(packed);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmStreamReadPackedFloats() - Read an compressed binary float data array
// from a stream, and uncompress it.
//-----------------------------------------------------------------------------
int _ctmStreamReadPackedFloats(_CTMcontext * self, CTMfloat * aData,
  CTMuint aCount, CTMuint aSize)
{
  CTMuint i, k;
  size_t packedSize, unpackedSize;
  union {
    CTMfloat f;
    CTMint i;
  } value;
  unsigned char * packed, * tmp;
  unsigned char props[5];
  int lzmaRes;

  // Read packed data size from the stream
  packedSize = (size_t) _ctmStreamReadUINT(self);

  // Read LZMA compression props from the stream
  _ctmStreamRead(self, (void *) props, 5);

  // Allocate memory and read the packed data from the stream
  packed = (unsigned char *) malloc(packedSize);
  if(!packed)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }
  _ctmStreamRead(self, (void *) packed, packedSize);

  // Allocate memory for interleaved array
  tmp = (unsigned char *) malloc(aCount * aSize * 4);
  if(!tmp)
  {
    free(packed);
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Uncompress
  unpackedSize = aCount * aSize * 4;
  lzmaRes = LzmaUncompress(tmp, &unpackedSize, packed,
                           &packedSize, props, 5);

  // Free the packed array
  free(packed);

  // Error?
  if((lzmaRes != SZ_OK) || (unpackedSize != aCount * aSize * 4))
  {
    self->mError = CTM_LZMA_ERROR;
    free(tmp);
    return CTM_FALSE;
  }

  // Convert interleaved array to floats
  for(i = 0; i < aCount; ++ i)
  {
    for(k = 0; k < aSize; ++ k)
    {
      value.i = (CTMint) tmp[i + k * aCount + 3 * aCount * aSize] |
                (((CTMint) tmp[i + k * aCount + 2 * aCount * aSize]) << 8) |
                (((CTMint) tmp[i + k * aCount + aCount * aSize]) << 16) |
                (((CTMint) tmp[i + k * aCount]) << 24);
      aData[i * aSize + k] = value.f;
    }
  }

  // Free the interleaved array
  free(tmp);

  return CTM_TRUE;
}

//-----------------------------------------------------------------------------
// _ctmStreamWritePackedFloats() - Compress a binary float data array, and
// write it to a stream.
//-----------------------------------------------------------------------------
int _ctmStreamWritePackedFloats(_CTMcontext * self, CTMfloat * aData,
  CTMuint aCount, CTMuint aSize)
{
  int lzmaRes, lzmaAlgo;
  CTMuint i, k;
  union {
    CTMfloat f;
    CTMint i;
  } value;
  size_t bufSize, outPropsSize;
  unsigned char * packed, outProps[5], *tmp;

  // Allocate memory for interleaved array
  tmp = (unsigned char *) malloc(aCount * aSize * 4);
  if(!tmp)
  {
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Convert floats to an interleaved array
  for(i = 0; i < aCount; ++ i)
  {
    for(k = 0; k < aSize; ++ k)
    {
      value.f = aData[i * aSize + k];
      tmp[i + k * aCount + 3 * aCount * aSize] = value.i & 0x000000ff;
      tmp[i + k * aCount + 2 * aCount * aSize] = (value.i >> 8) & 0x000000ff;
      tmp[i + k * aCount + aCount * aSize] = (value.i >> 16) & 0x000000ff;
      tmp[i + k * aCount] = (value.i >> 24) & 0x000000ff;
    }
  }

  // Allocate memory for the packed data
  bufSize = 1000 + aCount * aSize * 4;
  packed = (unsigned char *) malloc(bufSize);
  if(!packed)
  {
    free(tmp);
    self->mError = CTM_OUT_OF_MEMORY;
    return CTM_FALSE;
  }

  // Call LZMA to compress
  outPropsSize = 5;
  lzmaAlgo = (self->mCompressionLevel < 1 ? 0 : 1);
  lzmaRes = LzmaCompress(packed,
                         &bufSize,
                         (const unsigned char *) tmp,
                         aCount * aSize * 4,
                         outProps,
                         &outPropsSize,
                         self->mCompressionLevel, // Level (0-9)
                         0, -1, -1, -1, -1, -1,   // Default values (set by level)
                         lzmaAlgo                 // Algorithm (0 = fast, 1 = normal)
                        );

  // Free temporary array
  free(tmp);

  // Error?
  if(lzmaRes != SZ_OK)
  {
    self->mError = CTM_LZMA_ERROR;
    free(packed);
    return CTM_FALSE;
  }

#ifdef __DEBUG_
  printf("%d->%d bytes\n", aCount * aSize * 4, (int) bufSize);
#endif

  // Write packed data size to the stream
  _ctmStreamWriteUINT(self, (CTMuint) bufSize);

  // Write LZMA compression props to the stream
  _ctmStreamWrite(self, (void *) outProps, 5);

  // Write the packed data to the stream
  _ctmStreamWrite(self, (void *) packed, (CTMuint) bufSize);

  // Free the packed data
  free(packed);

  return CTM_TRUE;
}
