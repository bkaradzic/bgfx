/*
 * Copyright 2010-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/allocator.h>
#include <bx/commandline.h>
#include <bx/hash.h>
#include <bx/string.h>

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
		const uint32_t cmd = bx::hash<bx::HashMurmur2A>(_name, (uint32_t)bx::strLen(_name) );
		BX_ASSERT(m_lookup.end() == m_lookup.find(cmd), "Command \"%s\" already exist.", _name);

		Func fn = { _fn, _userData };
		m_lookup.insert(stl::make_pair(cmd, fn) );
	}

	void remove(const char* _name)
	{
		const uint32_t cmd = bx::hash<bx::HashMurmur2A>(_name, (uint32_t)bx::strLen(_name) );

		CmdLookup::iterator it = m_lookup.find(cmd);
		if (it != m_lookup.end() )
		{
			m_lookup.erase(it);
		}
	}

	void exec(const char* _cmd)
	{
		for (bx::StringView next(_cmd); !next.isEmpty(); _cmd = next.getPtr() )
		{
			char commandLine[1024];
			uint32_t size = sizeof(commandLine);
			int argc;
			char* argv[64];
			next = bx::tokenizeCommandLine(_cmd, commandLine, size, argc, argv, BX_COUNTOF(argv), '\n');
			if (argc > 0)
			{
				int err = -1;
				uint32_t cmd = bx::hash<bx::HashMurmur2A>(argv[0], (uint32_t)bx::strLen(argv[0]) );
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
						stl::string tmp(_cmd, next.getPtr()-_cmd - (next.isEmpty() ? 0 : 1) );
						DBG("Command '%s' doesn't exist.", tmp.c_str() );
					}
					break;

				default:
					{
						stl::string tmp(_cmd, next.getPtr()-_cmd - (next.isEmpty() ? 0 : 1) );
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

void cmdRemove(const char* _name)
{
	s_cmdContext->remove(_name);
}

void cmdExec(const char* _format, ...)
{
	char tmp[2048];

	va_list argList;
	va_start(argList, _format);
	bx::vsnprintf(tmp, BX_COUNTOF(tmp), _format, argList);
	va_end(argList);

	s_cmdContext->exec(tmp);
}
