/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_NACL

#include <bgfx/platform.h>

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

#include <bx/thread.h>

#include "entry.h"

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

	const Event* poll(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
		return NULL;
	}

	void release(const Event* _event)
	{
		BX_UNUSED(_event);
	}

	WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags, const char* _title)
	{
		BX_UNUSED(_x, _y, _width, _height, _flags, _title);
		WindowHandle handle = { UINT16_MAX };
		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		BX_UNUSED(_handle, _x, _y);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_handle, _width, _height);
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		BX_UNUSED(_handle, _title);
	}

	void toggleWindowFrame(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}

	template<typename Type>
	bool initializeInterface(PPB_GetInterface _interface, const char* _name, const Type*& _result)
	{
		_result = reinterpret_cast<const Type*>(_interface(_name) );
//		DBG("%p %s", _result, _name);
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
			static const char* argv[1] = { "nacl.nexe" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

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

		int32_t result = main(self->m_argc, self->m_argv);
		return result;
	}

	static PP_Bool naclInstanceDidCreate(PP_Instance _instance, uint32_t /*_argc*/, const char* /*_argn*/[], const char* /*_argv*/[])
	{
		g_instance = _instance; // one instance only!

		if (bgfx::naclSetInterfaces(g_instance, g_instInterface, g_graphicsInterface, NULL) )
		{
			s_ctx = new NaclContext;
			return PP_TRUE;
		}

		return PP_FALSE;
	}

	static void naclInstanceDidDestroy(PP_Instance _instance)
	{
		BX_UNUSED(_instance);
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
	if (0 == bx::strncmp(_name, PPP_INSTANCE_INTERFACE) )
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
	DBG("PPAPI version: %d", PPAPI_RELEASE);

	BX_UNUSED(_module);
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

#endif // ENTRY_CONFIG_USE_NATIVE && BX_PLATFROM_NACL
