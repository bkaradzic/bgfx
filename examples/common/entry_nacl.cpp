/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_NACL

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <ppapi/c/pp_errors.h>
#include <ppapi/c/pp_module.h>
#include <ppapi/c/ppb.h>
#include <ppapi/c/ppb_graphics_3d.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppp.h>
#include <ppapi/c/ppp_instance.h>
#include <ppapi/gles2/gl2ext_ppapi.h>

#include <bgfxplatform.h>
#include "dbg.h"

#include "entry.h"

namespace entry
{
	Event::Enum poll()
	{
		return Event::Nop;
	}

} // namespace entry

extern int _main_(int _argc, char** _argv);

static void* _entry_(void*)
{
	const char* argv[1] = { "nacl.nexe" };
	_main_(1, const_cast<char**>(argv) );
	return NULL;
}

struct NaclContext
{
	NaclContext()
		: m_thread(0)
	{
	}

	const PPB_Instance* m_instInterface;
	const PPB_Graphics3D* m_graphicsInterface;

	pthread_t m_thread;
	PP_Module m_module;
	PP_Instance m_instance;
};

static NaclContext s_ctx;

static PP_Bool naclInstanceDidCreate(PP_Instance _instance, uint32_t _argc, const char* _argn[], const char* _argv[])
{
	s_ctx.m_instance = _instance;

	bgfx::naclSetIntefraces(s_ctx.m_instance, s_ctx.m_instInterface, s_ctx.m_graphicsInterface, NULL);
	pthread_create(&s_ctx.m_thread, NULL, _entry_, NULL);

	return PP_TRUE;
}

static void naclInstanceDidDestroy(PP_Instance _instance)
{
	if (s_ctx.m_thread)
	{
		pthread_join(s_ctx.m_thread, NULL);
	}
}

static void naclInstanceDidChangeView(PP_Instance _instance, PP_Resource _view)
{
}

static void naclInstanceDidChangeFocus(PP_Instance _instance, PP_Bool _focus)
{
}

static PP_Bool naclInstanceHandleDocumentLoad(PP_Instance _instance, PP_Resource _urlLoader)
{
	return PP_FALSE;
}

PP_EXPORT const void* PPP_GetInterface(const char* _name)
{
	if (0 == strcmp(_name, PPP_INSTANCE_INTERFACE) )
	{
		static PPP_Instance instanceInterface =
		{
			&naclInstanceDidCreate,
			&naclInstanceDidDestroy,
			&naclInstanceDidChangeView,
			&naclInstanceDidChangeFocus,
			&naclInstanceHandleDocumentLoad,
		};

		return &instanceInterface;
	}

	return NULL;
}

template<typename Type>
bool initializeInterface(const Type*& _result, PPB_GetInterface _interface, const char* _name)
{
	_result = reinterpret_cast<const Type*>(_interface(_name) );
	return NULL != _result;
}

PP_EXPORT int32_t PPP_InitializeModule(PP_Module _module, PPB_GetInterface _interface)
{
	s_ctx.m_module = _module;

	bool result = true;
	result &= initializeInterface(s_ctx.m_instInterface, _interface, PPB_INSTANCE_INTERFACE);
	result &= initializeInterface(s_ctx.m_graphicsInterface, _interface, PPB_GRAPHICS_3D_INTERFACE);
	result &= glInitializePPAPI(_interface);

	return result ? PP_OK : PP_ERROR_NOINTERFACE;
}

PP_EXPORT void PPP_ShutdownModule()
{
}

#endif // BX_PLATFROM_NACL
