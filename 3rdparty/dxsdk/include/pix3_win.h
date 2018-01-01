/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       PIX3_win.h
 *  Content:    PIX include file
 *              Don't include this file directly - use pix3.h
 *
 ****************************************************************************/

#pragma once

#ifndef _PIX3_H_
#error "Don't include this file directly - use pix3.h"
#endif

#ifndef _PIX3_WIN_H_
#define _PIX3_WIN_H_

struct PIXEventsBlockInfo
{
};

struct PIXEventsThreadInfo
{
    PIXEventsBlockInfo* block;
    UINT64* biasedLimit;
    UINT64* destination;
    UINT64* limit;
    UINT64 id;
};

// The following defines denote the different metadata values that have been used
// by tools to denote how to parse pix marker event data. The first two values
// are legacy values.
#define WINPIX_EVENT_UNICODE_VERSION 0
#define WINPIX_EVENT_ANSI_VERSION 1
#define WINPIX_EVENT_PIX3BLOB_VERSION 2

#define D3D12_EVENT_METADATA WINPIX_EVENT_PIX3BLOB_VERSION

__forceinline UINT64 PIXGetTimestampCounter()
{
    LARGE_INTEGER time = {};
    QueryPerformanceCounter(&time);
    return time.QuadPart;
}

#define PIXSetCPUMarkerOnContext(context, metadata, ...) MakeCPUSetMarkerForContext(metadata, context, __VA_ARGS__)
#define PIXBeginCPUEventOnContext(context, metadata, ...) MakeCPUBeginEventForContext(metadata, context, __VA_ARGS__)
#define PIXEndCPUEventOnContext(context) MakeCPUEndEventForContext(context)

#endif //_PIX3_WIN_H_
