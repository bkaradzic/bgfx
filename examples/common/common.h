/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <bx/timer.h>
#include <bx/fpumath.h>

#include "entry/entry.h"

#ifndef COMMON_RUNTIME
#	if BX_PLATFORM_EMSCRIPTEN
#		define COMMON_RUNTIME "/examples/runtime/"
#	else
#		define COMMON_RUNTIME ""
#	endif
#endif

#endif // COMMON_H_HEADER_GUARD
