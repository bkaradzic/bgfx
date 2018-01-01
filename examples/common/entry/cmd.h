/*
 * Copyright 2010-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef CMD_H_HEADER_GUARD
#define CMD_H_HEADER_GUARD

struct CmdContext;
typedef int (*ConsoleFn)(CmdContext* _context, void* _userData, int _argc, char const* const* _argv);

///
void cmdInit();

///
void cmdShutdown();

///
void cmdAdd(const char* _name, ConsoleFn _fn, void* _userData = NULL);

///
void cmdExec(const char* _format, ...);

#endif // CMD_H_HEADER_GUARD
