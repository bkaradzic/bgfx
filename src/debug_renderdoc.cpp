/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX
#	include <renderdoc/renderdoc_app.h>

namespace bgfx
{
	pRENDERDOC_GetAPI RENDERDOC_GetAPI;
	static RENDERDOC_API_1_6_0* s_renderDoc = NULL;
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
			BX_TRACE("IntelGPA is present, not loading RenderDoc.");
			return NULL;
		}

		if (bgfx::NativeWindowHandleType::Wayland == g_platformData.type)
		{
			BX_TRACE("RenderDoc is not available on Wayland. https://github.com/baldurk/renderdoc/issues/853");
			return NULL;
		}

		const char* renderDocDllName =
#if BX_PLATFORM_WINDOWS
			"renderdoc.dll"
#else
			"librenderdoc.so"
#endif // BX_PLATFORM_WINDOWS
			;

		// If RenderDoc is already injected in the process then use the already present DLL
		void* renderDocDll = findModule(renderDocDllName);

		if (NULL == renderDocDll)
		{
			BX_TRACE("Loading RenderDoc...");
			renderDocDll = bx::dlopen(renderDocDllName);
		}
		else
		{
			BX_TRACE("RenderDoc is already loaded.");
		}

		if (NULL != renderDocDll)
		{
			RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)bx::dlsym(renderDocDll, "RENDERDOC_GetAPI");

			if (NULL != RENDERDOC_GetAPI
			&&  1 == RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_6_0, (void**)&s_renderDoc) )
			{
				s_renderDoc->SetCaptureFilePathTemplate(BGFX_CONFIG_RENDERDOC_LOG_FILEPATH);

				s_renderDoc->SetFocusToggleKeys(NULL, 0);

				RENDERDOC_InputButton captureKeys[] = BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS;
				s_renderDoc->SetCaptureKeys(captureKeys, BX_COUNTOF(captureKeys) );

				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_AllowVSync,    1);
				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_APIValidation, 1);

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
