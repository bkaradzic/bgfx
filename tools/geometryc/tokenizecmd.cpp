/*
 * Copyright 2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include "tokenizecmd.h"

// Reference:
// http://msdn.microsoft.com/en-us/library/a1y7w461.aspx
const char* tokenizeCommandLine(const char* _commandLine, char* _buffer, uint32_t& _bufferSize, int& _argc, char* _argv[], int _maxArgvs, char _term)
{
	int argc = 0;
	const char* curr = _commandLine;
	char* currOut = _buffer;
	char term = ' ';
	bool sub = false;
	
	enum ParserState
	{
		SkipWhitespace,
		SetTerm,
		Copy,
		Escape,
		End,
	};

	ParserState state = SkipWhitespace;
	
	while ('\0' != *curr
	&&     _term != *curr
	&&     argc < _maxArgvs)
	{
		switch (state)
		{
			case SkipWhitespace:
				for (; isspace(*curr); ++curr); // skip whitespace
				state = SetTerm;
				break;
				
			case SetTerm:
				if ('"' == *curr)
				{
					term = '"';
					++curr; // skip begining quote
				}
				else
				{
					term = ' ';
				}
				
				_argv[argc] = currOut;
				++argc;
				
				state = Copy;
				break;
				
			case Copy:
				if ('\\' == *curr)
				{
					state = Escape;
				}
				else if ('"' == *curr
					 &&  '"' != term)
				{
					sub = !sub;
				}
				else if (isspace(*curr) && !sub)
				{
					state = End;
				}
				else if (term != *curr || sub)
				{
					*currOut = *curr;
					++currOut;
				}
				else
				{
					state = End;
				}
				++curr;
				break;
				
			case Escape:
				{
					const char* start = --curr;
					for (; '\\' == *curr; ++curr);

					if ('"' != *curr)
					{
						int count = (int)(curr-start);

						curr = start;
						for (int ii = 0; ii < count; ++ii)
						{
							*currOut = *curr;
							++currOut;
							++curr;
						}
					}
					else
					{
						curr = start+1;
						*currOut = *curr;
						++currOut;
						++curr;
					}
				}
				state = Copy;
				break;
				
			case End:
				*currOut = '\0';
				++currOut;
				state = SkipWhitespace;
				break;
		}
	}
	
	*currOut = '\0';
	if (0 < argc
	&&  '\0' == _argv[argc-1][0])
	{
		--argc;
	}

	_bufferSize = (uint32_t)(currOut - _buffer);
	_argc = argc;

	if ('\0' != *curr)
	{
		++curr;
	}

	return curr;
}

#if 0

#include <string.h>

int main(int _argc, const char** _argv)
{
	const char* input[7] =
	{
		"       ",
		"\\",
		"\"a b c\" d e",
		"\"ab\\\"c\" \"\\\\\" d",
		"a\\\\\\b d\"e f\"g h",
		"a\\\\\\\"b c d",
		"a\\\\\\\\\"b c\" d e",
	};

	const int expected_argc[7] =
	{
		0, 0, 3, 3, 3, 3, 3
	};

	const char* expected_results[] =
	{
		"a b c", "d", "e",
		"ab\"c", "\\", "d",
		"a\\\\\\b", "de fg", "h",
		"a\\\"b", "c", "d",
		"a\\\\b c", "d", "e",
	};

	const char** expected_argv[7] =
	{
		NULL,
		NULL,
		&expected_results[0],
		&expected_results[3],
		&expected_results[6],
		&expected_results[9],
		&expected_results[12],
	};

	for (int ii = 0; ii < 7; ++ii)
	{
		char commandLine[1024];
		unsigned int size = 1023;
		char* argv[50];
		int argc = tokenizeCommandLine(input[ii], commandLine, size, argv, 50);
		printf("\n%d (%d): %s %s\n", ii, argc, input[ii], expected_argc[ii]==argc?"":"FAILED!");
		for (int jj = 0; jj < argc; ++jj)
		{
			printf("\t%d: {%s} %s\n"
					, jj
					, argv[jj]
					, jj<argc?(0==strcmp(argv[jj], expected_argv[ii][jj])?"":"FAILED!"):"FAILED!"
					);
		}
	}

	return 0;
}
#endif // 0
