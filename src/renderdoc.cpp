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

#define RENDERDOC_IMPORT \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_Shutdown); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetLogFile); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_GetCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetCaptureOptions); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetActiveWindow); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_TriggerCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_StartFrameCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_EndFrameCapture); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_GetOverlayBits); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_MaskOverlayBits); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetFocusToggleKeys); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_SetCaptureKeys); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_InitRemoteAccess); \
			RENDERDOC_IMPORT_FUNC(RENDERDOC_UnloadCrashHandler);

#define RENDERDOC_IMPORT_FUNC(_func) p##_func _func
	RENDERDOC_IMPORT
#undef RENDERDOC_IMPORT_FUNC

	pRENDERDOC_GetAPIVersion RENDERDOC_GetAPIVersion;

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
			RENDERDOC_GetAPIVersion = (pRENDERDOC_GetAPIVersion)bx::dlsym(renderdocdll, "RENDERDOC_GetAPIVersion");
			if (NULL != RENDERDOC_GetAPIVersion
			&&  RENDERDOC_API_VERSION == RENDERDOC_GetAPIVersion() )
			{
#define RENDERDOC_IMPORT_FUNC(_func) \
			_func = (p##_func)bx::dlsym(renderdocdll, #_func); \
			BX_TRACE("%p " #_func, _func);
RENDERDOC_IMPORT
#undef RENDERDOC_IMPORT_FUNC

				RENDERDOC_SetLogFile("temp/bgfx");

				RENDERDOC_SetFocusToggleKeys(NULL, 0);

				KeyButton captureKey = eKey_F11;
				RENDERDOC_SetCaptureKeys(&captureKey, 1);

				CaptureOptions opt;
				memset(&opt, 0, sizeof(opt) );
				opt.AllowVSync      = 1;
				opt.SaveAllInitials = 1;
				RENDERDOC_SetCaptureOptions(&opt);

				uint32_t ident = 0;
				RENDERDOC_InitRemoteAccess(&ident);

				RENDERDOC_MaskOverlayBits(eOverlay_None, eOverlay_None);
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
			RENDERDOC_Shutdown();
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
