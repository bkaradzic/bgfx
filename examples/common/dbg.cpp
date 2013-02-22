/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h> // isprint

#include "dbg.h"
#include <bx/string.h>

#if BX_COMPILER_MSVC
#	define snprintf _snprintf
#endif // BX_COMPILER_MSVC

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_XBOX360
extern "C"
{
	__declspec(dllimport) void __stdcall OutputDebugStringA(const char* _str);
}
#endif // BX_PLATFORM_WINDOWS

void dbgOutput(const char* _out)
{
#if BX_PLATFORM_WINDOWS || BX_PLATFORM_XBOX360
	OutputDebugStringA(_out);
#elif BX_PLATFORM_NACL || BX_PLATFORM_LINUX || BX_PLATFORM_OSX
	fputs(_out, stderr);
	fflush(stderr);
#endif // BX_PLATFORM_
}

void dbgPrintfVargs(const char* _format, va_list _argList)
{
	char temp[8192];
	char* out = temp;
	int32_t len = bx::vsnprintf(out, sizeof(temp), _format, _argList);
	if ( (int32_t)sizeof(temp) < len)
	{
		out = (char*)alloca(len+1);
		len = bx::vsnprintf(out, len, _format, _argList);
	}
	out[len] = '\0';
	dbgOutput(out);
}

void dbgPrintf(const char* _format, ...)
{
	va_list argList;
	va_start(argList, _format);
	dbgPrintfVargs(_format, argList);
	va_end(argList);
}

#define DBG_ADDRESS "%" PRIxPTR

void dbgPrintfData(const void* _data, uint32_t _size, const char* _format, ...)
{
#define HEX_DUMP_WIDTH 16
#define HEX_DUMP_SPACE_WIDTH 48
#define HEX_DUMP_FORMAT "%-" DBG_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "." DBG_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "s"

	va_list argList;
	va_start(argList, _format);
	dbgPrintfVargs(_format, argList);
	va_end(argList);

	dbgPrintf("\ndata: " DBG_ADDRESS ", size: %d\n", _data, _size);

	if (NULL != _data)
	{
		const uint8_t* data = reinterpret_cast<const uint8_t*>(_data);
		char hex[HEX_DUMP_WIDTH*3+1];
		char ascii[HEX_DUMP_WIDTH+1];
		uint32_t hexPos = 0;
		uint32_t asciiPos = 0;
		for (uint32_t ii = 0; ii < _size; ++ii)
		{
			snprintf(&hex[hexPos], sizeof(hex)-hexPos, "%02x ", data[asciiPos]);
			hexPos += 3;

			ascii[asciiPos] = isprint(data[asciiPos]) ? data[asciiPos] : '.';
			asciiPos++;

			if (HEX_DUMP_WIDTH == asciiPos)
			{
				ascii[asciiPos] = '\0';
				dbgPrintf("\t" DBG_ADDRESS "\t" HEX_DUMP_FORMAT "\t%s\n", data, hex, ascii);
				data += asciiPos;
				hexPos = 0;
				asciiPos = 0;
			}
		}

		if (0 != asciiPos)
		{
			ascii[asciiPos] = '\0';
			dbgPrintf("\t" DBG_ADDRESS "\t" HEX_DUMP_FORMAT "\t%s\n", data, hex, ascii);
		}
	}

#undef HEX_DUMP_WIDTH
#undef HEX_DUMP_SPACE_WIDTH
#undef HEX_DUMP_FORMAT
}
