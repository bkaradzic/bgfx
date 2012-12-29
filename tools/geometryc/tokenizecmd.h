/*
 * Copyright 2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __TOKENIZE_CMD_H__
#define __TOKENIZE_CMD_H__

const char* tokenizeCommandLine(const char* _commandLine, char* _buffer, uint32_t& _bufferSize, int& _argc, char* _argv[], int _maxArgvs, char _term = '\0');

#endif // __TOKENIZE_CMD_H__
