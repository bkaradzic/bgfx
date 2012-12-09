/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_OSX

extern int _main_(int _argc, char** _argv);

int main(int _argc, char** _argv)
{
	return _main_(_argc, _argv);
}

#endif // BX_PLATFORM_OSX
