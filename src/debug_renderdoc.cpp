/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX
#	if BX_PLATFORM_WINDOWS
#		ifndef WIN32_LEAN_AND_MEAN
#			define WIN32_LEAN_AND_MEAN
#		endif // WIN32_LEAN_AND_MEAN
#		include <windows.h>
#		include <psapi.h>
#	endif // BX_PLATFORM_WINDOWS
#	include <renderdoc/renderdoc_app.h>

namespace bgfx
{
	void* findModule(const char* _name)
	{
#if BX_PLATFORM_WINDOWS
		// NOTE: there was some reason to do it this way instead of simply calling GetModuleHandleA,
		// but not sure what it was.
		HANDLE process = GetCurrentProcess();
		DWORD size;
		BOOL result = EnumProcessModules(process
						, NULL
						, 0
						, &size
						);
		if (0 != result)
		{
			HMODULE* modules = (HMODULE*)alloca(size);
			result = EnumProcessModules(process
				, modules
				, size
				, &size
				);

			if (0 != result)
			{
				char moduleName[MAX_PATH];
				for (uint32_t ii = 0, num = uint32_t(size/sizeof(HMODULE) ); ii < num; ++ii)
				{
					result = GetModuleBaseNameA(process
								, modules[ii]
								, moduleName
								, BX_COUNTOF(moduleName)
								);
					if (0 != result
					&&  0 == bx::strCmpI(_name, moduleName) )
					{
						return (void*)modules[ii];
					}
				}
			}
		}
#else
		BX_UNUSED(_name);
#endif // BX_PLATFORM_WINDOWS

		return NULL;
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

		// If RenderDoc is already injected in the process then use the already present DLL
		void* renderDocDll = findModule("renderdoc.dll");
		if (NULL == renderDocDll)
		{
			// TODO: try common installation paths before looking in current directory
			renderDocDll = bx::dlopen(
#if BX_PLATFORM_WINDOWS
					"renderdoc.dll"
#else
					"./librenderdoc.so"
#endif // BX_PLATFORM_WINDOWS
					);
		}

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
