/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_DEBUG_PIX && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)
#	if BX_PLATFORM_WINDOWS
#		include <psapi.h>
#	endif // BX_PLATFORM_WINDOWS
#	include <renderdoc/renderdoc_app.h>

namespace bgfx
{
	bool findModule(const char* _name)
	{
#if BX_PLATFORM_WINDOWS
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
					&&  0 == bx::stricmp(_name, moduleName) )
					{
						return true;
					}
				}
			}
		}
#endif // BX_PLATFORM_WINDOWS
		BX_UNUSED(_name);
		return false;
	}

	pRENDERDOC_GetAPI RENDERDOC_GetAPI;
	static RENDERDOC_API_1_0_0* s_renderDoc;

	void* loadRenderDoc()
	{
		// Skip loading RenderDoc when IntelGPA is present to avoid RenderDoc crash.
		if (findModule(BX_ARCH_32BIT ? "shimloader32.dll" : "shimloader64.dll") )
		{
			return NULL;
		}

		void* renderdocdll = bx::dlopen("renderdoc.dll");

		if (NULL != renderdocdll)
		{
			RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)bx::dlsym(renderdocdll, "RENDERDOC_GetAPI");
			if (NULL != RENDERDOC_GetAPI
			&&  1 == RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_0_0, (void**)&s_renderDoc) )
			{
				s_renderDoc->SetLogFilePathTemplate("temp/bgfx");

 				s_renderDoc->SetFocusToggleKeys(NULL, 0);

				RENDERDOC_InputButton captureKey = eRENDERDOC_Key_F11;
				s_renderDoc->SetCaptureKeys(&captureKey, 1);

				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_AllowVSync,      1);
				s_renderDoc->SetCaptureOptionU32(eRENDERDOC_Option_SaveAllInitials, 1);

				s_renderDoc->MaskOverlayBits(eRENDERDOC_Overlay_None, eRENDERDOC_Overlay_None);
			}
			else
			{
				bx::dlclose(renderdocdll);
				renderdocdll = NULL;
			}
		}

		return renderdocdll;
	}

	void unloadRenderDoc(void* _renderdocdll)
	{
		if (NULL != _renderdocdll)
		{
			s_renderDoc->Shutdown();
			bx::dlclose(_renderdocdll);
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

} // namespace bgfx

#endif // BGFX_CONFIG_DEBUG_PIX && (BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX)
