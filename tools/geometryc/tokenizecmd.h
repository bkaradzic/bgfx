/*
 * Copyright 2012-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef TOKENIZE_CMD_H_HEADER_GUARD
#define TOKENIZE_CMD_H_HEADER_GUARD

const char* tokenizeCommandLine(const char* _commandLine, char* _buffer, uint32_t& _bufferSize, int& _argc, char* _argv[], int _maxArgvs, char _term = '\0');

#endif // TOKENIZE_CMD_H_HEADER_GUARD
