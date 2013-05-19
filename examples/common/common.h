/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include "dbg.h"

#if 0
#	define BX_TRACE(_format, ...) \
		do { \
			DBG(BX_FILE_LINE_LITERAL "BGFX " _format "\n", ##__VA_ARGS__); \
		} while(0)

#	define BX_WARN(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				DBG("WARN " _format, ##__VA_ARGS__); \
			} \
		} while(0)

#	define BX_CHECK(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				DBG("CHECK " _format, ##__VA_ARGS__); \
				bx::debugBreak(); \
			} \
		} while(0)
#endif // 0

#include <bx/bx.h>
#include <bx/debug.h>

#endif // __COMMON_H__
