/*
 * Copyright 2010-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <ctype.h>  // isspace
#include <stdint.h>
#include <stdlib.h> // size_t
#include <string.h> // strlen

#include <bx/allocator.h>
#include <bx/hash.h>
#include <bx/tokenizecmd.h>

#include "dbg.h"
#include "cmd.h"
#include "entry_p.h"

#include <tinystl/allocator.h>
#include <tinystl/string.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

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
		m_lookup.insert(stl::make_pair(cmd, fn) );
	}

	void exec(const char* _cmd)
	{
		for (const char* next = _cmd; '\0' != *next; _cmd = next)
		{
			char commandLine[1024];
			uint32_t size = sizeof(commandLine);
			int argc;
			char* argv[64];
			next = bx::tokenizeCommandLine(_cmd, commandLine, size, argc, argv, BX_COUNTOF(argv), '\n');
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
						stl::string tmp(_cmd, next-_cmd - (*next == '\0' ? 0 : 1) );
						DBG("Command '%s' doesn't exist.", tmp.c_str() );
					}
					break;

				default:
					{
						stl::string tmp(_cmd, next-_cmd - (*next == '\0' ? 0 : 1) );
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

	typedef stl::unordered_map<uint32_t, Func> CmdLookup;
	CmdLookup m_lookup;
};

static CmdContext* s_cmdContext;

void cmdInit()
{
	s_cmdContext = BX_NEW(entry::getAllocator(), CmdContext);
}

void cmdShutdown()
{
	BX_DELETE(entry::getAllocator(), s_cmdContext);
}

void cmdAdd(const char* _name, ConsoleFn _fn, void* _userData)
{
	s_cmdContext->add(_name, _fn, _userData);
}

void cmdExec(const char* _cmd)
{
	s_cmdContext->exec(_cmd);
}
