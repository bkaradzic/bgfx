/*
 * Copyright 2010-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __CMD_H__
#define __CMD_H__

struct CmdContext;
typedef int (*ConsoleFn)(CmdContext* _context, void* _userData, int _argc, char const* const* _argv);

void cmdAdd(const char* _name, ConsoleFn _fn, void* _userData = NULL);
void cmdExec(const char* _cmd);

#endif // __CMD_H__
