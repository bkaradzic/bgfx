/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX
#	if BX_PLATFORM_WINDOWS
#		include <psapi.h>
#	endif // BX_PLATFORM_WINDOWS
#	include <renderdoc/renderdoc_app.h>

namespace bgfx
{
	void* findModule(const char* _name)
	{
#if BX_PLATFORM_WINDOWS
		return (void*)GetModuleHandleA(_name);
#else
		BX_UNUSED(_name);
		return NULL;
#endif
	}

	pRENDERDOC_GetAPI RENDERDOC_GetAPI;
	static RENDERDOC_API_1_1_2* s_renderDoc = NULL;
	static void* s_renderDocDll = NULL;

	void* loadRenderDoc()
	{
		if (NULL != s_renderDoc)
		{
			return s_renderDocDll;
		}

		// Skip loading RenderDoc when IntelGPA is present to avoid RenderDoc crash.
		if (findModule(BX_ARCH_32BIT ? "shimloader32.dll" : "shimloader64.dll") )
		{
			return NULL;
		}

#if BX_PLATFORM_WINDOWS
		// If RenderDoc is already injected in the process then use the already present DLL
		void* renderDocDll = findModule("renderdoc.dll");
		if (NULL == renderDocDll)
		{
			// Load the RenderDoc DLL from its default installation location
			renderDocDll = bx::dlopen("C:\\Program Files\\RenderDoc\\renderdoc.dll");
		}
#else
		void* renderDocDll = bx::dlopen("./librenderdoc.so");
#endif

		if (NULL != renderDocDll)
		{
			RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)bx::dlsym(renderDocDll, "RENDERDOC_GetAPI");

			if (NULL != RENDERDOC_GetAPI
			&&  1 == RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_1_2, (void**)&s_renderDoc) )
			{
				s_renderDoc->SetCaptureFilePathTemplate(BGFX_CONFIG_RENDERDOC_LOG_FILEPATH);

				s_renderDoc->SetFocusToggleKeys(NULL, 0);

				RENDERDOC_InputButton captureKeys[] = BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS;
				s_renderDoc->SetCaptureKeys(captureKeys, BX_COUNTOF(captureKeys) );

				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_AllowVSync,      1);
				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_SaveAllInitials, 1);

				s_renderDoc->MaskOverlayBits(eRENDERDOC_Overlay_None, eRENDERDOC_Overlay_None);

				s_renderDocDll = renderDocDll;
			}
			else
			{
				bx::dlclose(renderDocDll);
				renderDocDll = NULL;
			}
		}

		return renderDocDll;
	}

	void unloadRenderDoc(void* _renderdocdll)
	{
		if (NULL != _renderdocdll)
		{
			// BK - Once RenderDoc is loaded there shouldn't be calls
			// to Shutdown or unload RenderDoc DLL.
			// https://github.com/bkaradzic/bgfx/issues/1192
			//
			// s_renderDoc->Shutdown();
			// bx::dlclose(_renderdocdll);
		}
	}

	void renderDocTriggerCapture()
	{
		if (NULL != s_renderDoc)
		{
			s_renderDoc->TriggerCapture();
		}
	}

} // namespace bgfx

#else

namespace bgfx
{

	void* loadRenderDoc()
	{
		return NULL;
	}

	void unloadRenderDoc(void*)
	{
	}

	void renderDocTriggerCapture()
	{
	}

} // namespace bgfx

#endif // BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX
