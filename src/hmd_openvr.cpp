/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "hmd_openvr.h"

BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-variable")
#include <openvr/openvr_capi.h>

namespace bgfx
{
#if BX_PLATFORM_WINDOWS
#	define VR_CALLTYPE __cdecl
#else
#	define VR_CALLTYPE
#endif

	typedef uint32_t    (VR_CALLTYPE *PFN_VR_INITINTERNAL)(EVRInitError* peError, EVRApplicationType eType);
	typedef void        (VR_CALLTYPE *PFN_VR_SHUTDOWNINTERNAL)();
	typedef bool        (VR_CALLTYPE *PFN_VR_ISHMDPRESENT)();
	typedef void*       (VR_CALLTYPE *PFN_VR_GETGENERICINTERFACE)(const char* pchInterfaceVersion, EVRInitError* peError);
	typedef bool        (VR_CALLTYPE *PFN_VR_ISRUNTIMEINSTALLED)();
	typedef bool        (VR_CALLTYPE *PFN_VR_ISINTERFACEVERSIONVALID)(const char *pchInterfaceVersion);
	typedef uint32_t    (VR_CALLTYPE *PFN_VR_GETINITTOKEN)();
	typedef const char* (VR_CALLTYPE *PFN_VR_GETVRINITERRORASSYMBOL)(EVRInitError error);
	typedef const char* (VR_CALLTYPE *PFN_VR_GETVRINITERRORASENGLISHDESCRIPTION)(EVRInitError error);

	PFN_VR_INITINTERNAL                       VR_InitInternal;
	PFN_VR_SHUTDOWNINTERNAL                   VR_ShutdownInternal;
	PFN_VR_ISHMDPRESENT                       VR_IsHmdPresent;
	PFN_VR_GETGENERICINTERFACE                VR_GetGenericInterface;
	PFN_VR_ISRUNTIMEINSTALLED                 VR_IsRuntimeInstalled;
	PFN_VR_ISINTERFACEVERSIONVALID            VR_IsInterfaceVersionValid;
	PFN_VR_GETINITTOKEN                       VR_GetInitToken;
	PFN_VR_GETVRINITERRORASSYMBOL             VR_GetVRInitErrorAsSymbol;
	PFN_VR_GETVRINITERRORASENGLISHDESCRIPTION VR_GetVRInitErrorAsEnglishDescription;

	void* loadOpenVR()
	{
		void* openvrdll = bx::dlopen(
#if BX_PLATFORM_LINUX
			"libopenvr_api.so"
#elif BX_PLATFORM_OSX
			"libopenvr_api.dylib"
#else
			"openvr_api.dll"
#endif // BX_PLATFORM_*
			);
		if (NULL != openvrdll)
		{
			VR_InitInternal            = (PFN_VR_INITINTERNAL           )bx::dlsym(openvrdll, "VR_InitInternal");
			VR_ShutdownInternal        = (PFN_VR_SHUTDOWNINTERNAL       )bx::dlsym(openvrdll, "VR_ShutdownInternal");
			VR_IsHmdPresent            = (PFN_VR_ISHMDPRESENT           )bx::dlsym(openvrdll, "VR_IsHmdPresent");
			VR_GetGenericInterface     = (PFN_VR_GETGENERICINTERFACE    )bx::dlsym(openvrdll, "VR_GetGenericInterface");
			VR_IsRuntimeInstalled      = (PFN_VR_ISRUNTIMEINSTALLED     )bx::dlsym(openvrdll, "VR_IsRuntimeInstalled");
			VR_IsInterfaceVersionValid = (PFN_VR_ISINTERFACEVERSIONVALID)bx::dlsym(openvrdll, "VR_IsInterfaceVersionValid");
			VR_GetInitToken            = (PFN_VR_GETINITTOKEN           )bx::dlsym(openvrdll, "VR_GetInitToken");
			VR_GetVRInitErrorAsSymbol             = (PFN_VR_GETVRINITERRORASSYMBOL            )bx::dlsym(openvrdll, "VR_GetVRInitErrorAsSymbol");
			VR_GetVRInitErrorAsEnglishDescription = (PFN_VR_GETVRINITERRORASENGLISHDESCRIPTION)bx::dlsym(openvrdll, "VR_GetVRInitErrorAsEnglishDescription");

			if (NULL == VR_InitInternal
			||  NULL == VR_ShutdownInternal
			||  NULL == VR_IsHmdPresent
			||  NULL == VR_GetGenericInterface
			||  NULL == VR_IsRuntimeInstalled
			||  NULL == VR_IsInterfaceVersionValid
			||  NULL == VR_GetInitToken
			||  NULL == VR_GetVRInitErrorAsSymbol
			||  NULL == VR_GetVRInitErrorAsEnglishDescription)
			{
				bx::dlclose(openvrdll);
				return NULL;
			}

			EVRInitError err;
			uint32_t token = VR_InitInternal(&err, EVRApplicationType_VRApplication_Scene);
			BX_UNUSED(token);

			BX_TRACE("OpenVR: HMD is %spresent, Runtime is %sinstalled."
				, VR_IsHmdPresent() ? "" : "not "
				, VR_IsRuntimeInstalled() ? "" : "not "
				);
		}

		return openvrdll;
	}

	void unloadOpenVR(void* _openvrdll)
	{
		VR_ShutdownInternal();
		bx::dlclose(_openvrdll);
	}

} // namespace bgfx
