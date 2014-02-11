/*
 * Copyright 2010-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef CMD_H_HEADER_GUARD
#define CMD_H_HEADER_GUARD

struct CmdContext;
typedef int (*ConsoleFn)(CmdContext* _context, void* _userData, int _argc, char const* const* _argv);

void cmdAdd(const char* _name, ConsoleFn _fn, void* _userData = NULL);
void cmdExec(const char* _cmd);

#endif // CMD_H_HEADER_GUARD
