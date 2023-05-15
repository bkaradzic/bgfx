/*
 * Copyright 2010-2023 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
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
void cmdRemove(const char* _name);

///
void cmdExec(const char* _format, ...);

#endif // CMD_H_HEADER_GUARD
