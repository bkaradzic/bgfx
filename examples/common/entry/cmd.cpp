/*
 * Copyright 2010-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <ctype.h>  // isspace
#include <stdint.h>
#include <stdlib.h> // size_t
#include <string.h> // strlen
#include <bx/hash.h>

#include "dbg.h"
#include "cmd.h"
#include <string>
#include <unordered_map>

// Reference:
// http://msdn.microsoft.com/en-us/library/a1y7w461.aspx
static const char* tokenizeCommandLine(const char* _commandLine, char* _buffer, uint32_t& _bufferSize, int& _argc, char* _argv[], int _maxArgvs, char _term)
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
			for (; isspace(*curr); ++curr) {}; // skip whitespace
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
				for (; '\\' == *curr; ++curr) {};

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

struct CmdContext
{
	CmdContext()
	{
	}

	~CmdContext()
	{
	}

	void add(const char* _name, ConsoleFn _fn, void* _userData)
	{
		uint32_t cmd = bx::hashMurmur2A(_name, (uint32_t)strlen(_name) );
		BX_CHECK(m_lookup.end() == m_lookup.find(cmd), "Command \"%s\" already exist.", _name);
		Func fn = { _fn, _userData };
		m_lookup.insert(std::make_pair(cmd, fn) );
	}

	void exec(const char* _cmd)
	{
		for (const char* next = _cmd; '\0' != *next; _cmd = next)
		{
			char commandLine[1024];
			uint32_t size = sizeof(commandLine);
			int argc;
			char* argv[64];
			next = tokenizeCommandLine(_cmd, commandLine, size, argc, argv, BX_COUNTOF(argv), '\n');
			if (argc > 0)
			{
				int err = -1;
				uint32_t cmd = bx::hashMurmur2A(argv[0], (uint32_t)strlen(argv[0]) );
				CmdLookup::iterator it = m_lookup.find(cmd);
				if (it != m_lookup.end() )
				{
					Func& fn = it->second;
					err = fn.m_fn(this, fn.m_userData, argc, argv);
				}

				switch (err)
				{
				case 0:
					break;

				case -1:
					{
						std::string tmp(_cmd, next-_cmd - (*next == '\0' ? 0 : 1) );
						DBG("Command '%s' doesn't exist.", tmp.c_str() );
					}
					break;

				default:
					{
						std::string tmp(_cmd, next-_cmd - (*next == '\0' ? 0 : 1) );
						DBG("Failed '%s' err: %d.", tmp.c_str(), err);
					}
					break;
				}
			}
		}
	}

	struct Func
	{
		ConsoleFn m_fn;
		void* m_userData;
	};

	typedef std::unordered_map<uint32_t, Func> CmdLookup;
	CmdLookup m_lookup;
};

static CmdContext s_cmdContext;

void cmdAdd(const char* _name, ConsoleFn _fn, void* _userData)
{
	s_cmdContext.add(_name, _fn, _userData);
}

void cmdExec(const char* _cmd)
{
	s_cmdContext.exec(_cmd);
}
