/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#if BX_PLATFORM_NACL

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <string>

#include <ppapi/c/pp_errors.h>
#include <ppapi/c/pp_module.h>
#include <ppapi/c/ppb.h>
#include <ppapi/c/ppb_core.h>
#include <ppapi/c/ppb_graphics_3d.h>
#include <ppapi/c/ppb_instance.h>
#include <ppapi/c/ppb_message_loop.h>
#include <ppapi/c/ppb_url_loader.h>
#include <ppapi/c/ppb_url_request_info.h>
#include <ppapi/c/ppb_url_response_info.h>
#include <ppapi/c/ppb_var.h>
#include <ppapi/c/ppp.h>
#include <ppapi/c/ppp_instance.h>
#include <ppapi/gles2/gl2ext_ppapi.h>

#include <bgfxplatform.h>
#include <bx/thread.h>

#include "entry.h"

extern int _main_(int _argc, char** _argv);

namespace entry
{
	const PPB_Core* g_coreInterface;
	const PPB_Instance* g_instInterface;
	const PPB_Graphics3D* g_graphicsInterface;
	const PPB_MessageLoop* g_messageLoopInterface;
	const PPB_URLLoader* g_urlLoaderInterface;
	const PPB_URLRequestInfo* g_urlRequestInterface;
	const PPB_URLResponseInfo* g_urlResponseInterface;
	const PPB_Var* g_varInterface;
	PP_Instance g_instance;

	const Event* poll()
	{
		return NULL;
	}

	void release(const Event* _event)
	{
	}

	void setWindowSize(uint32_t _width, uint32_t _height)
	{
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
	}

	template<typename Type>
	bool initializeInterface(PPB_GetInterface _interface, const char* _name, const Type*& _result)
	{
		_result = reinterpret_cast<const Type*>(_interface(_name) );
		return NULL != _result;
	}

	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData);
	};

	struct NaclContext
	{
		NaclContext()
		{
			const char* argv[1] = { "nacl.nexe" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			bgfx::naclSetIntefraces(g_instance, g_instInterface, g_graphicsInterface, NULL);
			m_thread.init(MainThreadEntry::threadFunc, &m_mte);
		}

		~NaclContext()
		{
			m_thread.shutdown();
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;
	};

	static NaclContext* s_ctx;

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;

		PP_Resource resource = g_messageLoopInterface->Create(g_instance);
		g_messageLoopInterface->AttachToCurrentThread(resource);

		int32_t result = _main_(self->m_argc, self->m_argv);
		return result;
	}

	static PP_Bool naclInstanceDidCreate(PP_Instance _instance, uint32_t /*_argc*/, const char* /*_argn*/[], const char* /*_argv*/[])
	{
		g_instance = _instance; // one instance only!
		s_ctx = new NaclContext;
		return PP_TRUE;
	}

	static void naclInstanceDidDestroy(PP_Instance _instance)
	{
		delete s_ctx;
	}

	static void naclInstanceDidChangeView(PP_Instance /*_instance*/, PP_Resource /*_view*/)
	{
	}

	static void naclInstanceDidChangeFocus(PP_Instance /*_instance*/, PP_Bool /*_focus*/)
	{
	}

	static PP_Bool naclInstanceHandleDocumentLoad(PP_Instance /*_instance*/, PP_Resource /*_urlLoader*/)
	{
		return PP_FALSE;
	}

} // namespace entry

using namespace entry;

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

PP_EXPORT int32_t PPP_InitializeModule(PP_Module _module, PPB_GetInterface _interface)
{
	bool result = true;
	result &= initializeInterface(_interface, PPB_CORE_INTERFACE,            g_coreInterface);
	result &= initializeInterface(_interface, PPB_GRAPHICS_3D_INTERFACE,     g_graphicsInterface);
	result &= initializeInterface(_interface, PPB_INSTANCE_INTERFACE,        g_instInterface);
	result &= initializeInterface(_interface, PPB_MESSAGELOOP_INTERFACE,     g_messageLoopInterface);
	result &= initializeInterface(_interface, PPB_URLLOADER_INTERFACE,       g_urlLoaderInterface);
	result &= initializeInterface(_interface, PPB_URLREQUESTINFO_INTERFACE,  g_urlRequestInterface);
	result &= initializeInterface(_interface, PPB_URLRESPONSEINFO_INTERFACE, g_urlResponseInterface);
	result &= initializeInterface(_interface, PPB_VAR_INTERFACE,             g_varInterface);
	result &= glInitializePPAPI(_interface);

	return result ? PP_OK : PP_ERROR_NOINTERFACE;
}

PP_EXPORT void PPP_ShutdownModule()
{
}

#endif // BX_PLATFROM_NACL
