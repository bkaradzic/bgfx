/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"
#include "nvapi.h"

namespace bgfx
{
	/*
	 * NVAPI
	 *
	 * Reference(s):
	 * - https://web.archive.org/web/20181126035649/https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/index.html
	 * - https://web.archive.org/web/20181126035710/https://github.com/jNizM/AHK_NVIDIA_NvAPI/blob/master/info/NvAPI_IDs.txt
	 */

	struct NvPhysicalGpuHandle;

#define NVAPI_MAX_PHYSICAL_GPUS 64

#if BX_PLATFORM_WINDOWS
#	define NVAPICALL __cdecl
#else
#	define NVAPICALL
#endif // BX_PLATFORM_WINDOWS

	enum NvApiStatus
	{
		NVAPI_OK    =  0,
		NVAPI_ERROR = -1,
	};

	struct NvMemoryInfoV2
	{
		NvMemoryInfoV2()
			: version(sizeof(NvMemoryInfoV2) | (2 << 16) )
		{
		}

		uint32_t version;
		uint32_t dedicatedVideoMemory;
		uint32_t availableDedicatedVideoMemory;
		uint32_t systemVideoMemory;
		uint32_t sharedSystemMemory;
		uint32_t curAvailableDedicatedVideoMemory;
	};

	/*
	 * NVIDIA Reflex
	 *
	 * Reference(s):
	 * - https://github.com/NVIDIA/nvapi/blob/main/nvapi.h
	 * - https://developer.nvidia.com/performance-rendering-tools/reflex
	 */

	enum NvLatencyMarkerType
	{
		NV_SIMULATION_START   = 0,
		NV_SIMULATION_END     = 1,
		NV_RENDERSUBMIT_START = 2,
		NV_RENDERSUBMIT_END   = 3,
		NV_PRESENT_START      = 4,
		NV_PRESENT_END        = 5,
	};

	static const NvLatencyMarkerType s_nvLatencyMarker[] =
	{
		NV_SIMULATION_START,
		NV_SIMULATION_END,
		NV_RENDERSUBMIT_START,
		NV_RENDERSUBMIT_END,
		NV_PRESENT_START,
		NV_PRESENT_END,
	};

	struct NvSetSleepModeParamsV1
	{
		NvSetSleepModeParamsV1()
		{
			bx::memSet(this, 0, sizeof(NvSetSleepModeParamsV1) );
			version = sizeof(NvSetSleepModeParamsV1) | (1 << 16);
		}

		uint32_t version;
		uint8_t  lowLatencyMode;
		uint8_t  lowLatencyBoost;
		uint32_t minimumIntervalUs;
		uint8_t  useMarkersToOptimize;
		uint8_t  useMinQueueTime;
		uint8_t  reserved[30];
	};

	struct NvLatencyMarkerParamsV1
	{
		NvLatencyMarkerParamsV1()
		{
			bx::memSet(this, 0, sizeof(NvLatencyMarkerParamsV1) );
			version = sizeof(NvLatencyMarkerParamsV1) | (1 << 16);
		}

		uint32_t version;
		uint64_t frameId;
		NvLatencyMarkerType markerType;
		uint64_t reserved0;
		uint8_t  reserved[56];
	};

	struct NvLatencyFrameReport
	{
		uint64_t frameId;
		uint64_t inputSampleTime;
		uint64_t simStartTime;
		uint64_t simEndTime;
		uint64_t renderSubmitStartTime;
		uint64_t renderSubmitEndTime;
		uint64_t presentStartTime;
		uint64_t presentEndTime;
		uint64_t driverStartTime;
		uint64_t driverEndTime;
		uint64_t osRenderQueueStartTime;
		uint64_t osRenderQueueEndTime;
		uint64_t gpuRenderStartTime;
		uint64_t gpuRenderEndTime;
		uint8_t  reserved[128];
	};

	struct NvLatencyResultParamsV1
	{
		NvLatencyResultParamsV1()
		{
			bx::memSet(this, 0, sizeof(NvLatencyResultParamsV1) );
			version = sizeof(NvLatencyResultParamsV1) | (1 << 16);
		}

		uint32_t version;
		NvLatencyFrameReport frameReport[64];
		uint8_t  reserved[32];
	};

	typedef void*       (NVAPICALL* PFN_NVAPI_QUERYINTERFACE)(uint32_t _functionOffset);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_INITIALIZE)();
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_UNLOAD)();
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_ENUMPHYSICALGPUS)(NvPhysicalGpuHandle* _handle[NVAPI_MAX_PHYSICAL_GPUS], uint32_t* _gpuCount);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_GPUGETMEMORYINFO)(NvPhysicalGpuHandle* _handle, NvMemoryInfoV2* _memoryInfo);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_GPUGETFULLNAME)(NvPhysicalGpuHandle* _physicalGpu, char _name[64]);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_D3DSETSLEEPMODE)(IUnknown* _device, NvSetSleepModeParamsV1* _params);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_D3DSLEEP)(IUnknown* _device);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_D3DSETLATENCYMARKER)(IUnknown* _device, NvLatencyMarkerParamsV1* _params);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_D3DGETLATENCY)(IUnknown* _device, NvLatencyResultParamsV1* _params);

#define NVAPI_INITIALIZE                        UINT32_C(0x0150e828)
#define NVAPI_UNLOAD                            UINT32_C(0xd22bdd7e)
#define NVAPI_ENUMPHYSICALGPUS                  UINT32_C(0xe5ac921f)
#define NVAPI_GPUGETMEMORYINFO                  UINT32_C(0x07f9b368)
#define NVAPI_GPUGETFULLNAME                    UINT32_C(0xceee8e9f)
#define NVAPI_MULTIDRAWINSTANCEDINDIRECT        UINT32_C(0xd4e26bbf)
#define NVAPI_MULTIDRAWINDEXEDINSTANCEDINDIRECT UINT32_C(0x59e890f9)
#define NVAPI_D3DSETSLEEPMODE                   UINT32_C(0xac1ca9e0)
#define NVAPI_D3DSLEEP                          UINT32_C(0x852cd1d2)
#define NVAPI_D3DSETLATENCYMARKER               UINT32_C(0xd9984c05)
#define NVAPI_D3DGETLATENCY                     UINT32_C(0x1a587f9c)

	static PFN_NVAPI_QUERYINTERFACE      nvApiQueryInterface;
	static PFN_NVAPI_INITIALIZE          nvApiInitialize;
	static PFN_NVAPI_UNLOAD              nvApiUnload;
	static PFN_NVAPI_ENUMPHYSICALGPUS    nvApiEnumPhysicalGPUs;
	static PFN_NVAPI_GPUGETMEMORYINFO    nvApiGpuGetMemoryInfo;
	static PFN_NVAPI_GPUGETFULLNAME      nvApiGpuGetFullName;
	static PFN_NVAPI_D3DSETSLEEPMODE     nvApiD3DSetSleepMode;
	static PFN_NVAPI_D3DSLEEP            nvApiD3DSleep;
	static PFN_NVAPI_D3DSETLATENCYMARKER nvApiD3DSetLatencyMarker;
	static PFN_NVAPI_D3DGETLATENCY       nvApiD3DGetLatency;

	/*
	 * NVIDIA Aftermath
	 *
	 * Reference(s):
	 * - https://web.archive.org/web/20181126035743/https://developer.nvidia.com/nvidia-aftermath
	 */

	typedef int32_t (*PFN_NVAFTERMATH_DX11_INITIALIZE)(int32_t _version, int32_t _flags, const ID3D11Device* _device);
	typedef int32_t (*PFN_NVAFTERMATH_DX11_CREATECONTEXTHANDLE)(const ID3D11DeviceContext* _deviceCtx, NvAftermathContextHandle** _outContextHandle);
	typedef int32_t (*PFN_NVAFTERMATH_DX12_INITIALIZE)(int32_t _version, int32_t _flags, const ID3D12Device* _device);
	typedef int32_t (*PFN_NVAFTERMATH_DX12_CREATECONTEXTHANDLE)(const ID3D12CommandList* _commandList, NvAftermathContextHandle** _outContextHandle);
	typedef int32_t (*PFN_NVAFTERMATH_RELEASECONTEXTHANDLE)(const NvAftermathContextHandle* _contextHandle);
	typedef int32_t (*PFN_NVAFTERMATH_SETEVENTMARKER)(const NvAftermathContextHandle* _contextHandle, const void* _markerData, uint32_t _markerSize);
	typedef int32_t (*PFN_NVAFTERMATH_GETDATA)(uint32_t _numContexts, const NvAftermathContextHandle** _contextHandles, void* _outContextData);
	typedef int32_t (*PFN_NVAFTERMATH_GETDEVICESTATUS)(void* _outStatus);
	typedef int32_t (*PFN_NVAFTERMATH_GETPAGEFAULTINFORMATION)(void* _outPageFaultInformation);

	static PFN_NVAFTERMATH_DX11_INITIALIZE          nvAftermathDx11Initialize;
	static PFN_NVAFTERMATH_DX11_CREATECONTEXTHANDLE nvAftermathDx11CreateContextHandle;
	static PFN_NVAFTERMATH_DX12_INITIALIZE          nvAftermathDx12Initialize;
	static PFN_NVAFTERMATH_DX12_CREATECONTEXTHANDLE nvAftermathDx12CreateContextHandle;
	static PFN_NVAFTERMATH_RELEASECONTEXTHANDLE     nvAftermathReleaseContextHandle;
	static PFN_NVAFTERMATH_SETEVENTMARKER           nvAftermathSetEventMarker;
	static PFN_NVAFTERMATH_GETDATA                  nvAftermathGetData;
	static PFN_NVAFTERMATH_GETDEVICESTATUS          nvAftermathGetDeviceStatus;
	static PFN_NVAFTERMATH_GETPAGEFAULTINFORMATION  nvAftermathGetPageFaultInformation;

	NvApi::NvApi()
		: m_nvApiDll(NULL)
		, m_nvGpu(NULL)
		, m_nvAftermathDll(NULL)
		, m_aftermathHandle(NULL)
		, m_reflexDevice(NULL)
		, m_latencyResult(NULL)
	{
	}

	void NvApi::init()
	{
		m_nvGpu = NULL;
		m_nvApiDll = bx::dlopen(
			"nvapi"
#if BX_ARCH_64BIT
			"64"
#endif // BX_ARCH_32BIT
			".dll"
			);

		if (NULL != m_nvApiDll)
		{
			nvApiQueryInterface = (PFN_NVAPI_QUERYINTERFACE)bx::dlsym(m_nvApiDll, "nvapi_QueryInterface");

			bool initialized = NULL != nvApiQueryInterface;

			if (initialized)
			{
				nvApiInitialize       = (PFN_NVAPI_INITIALIZE      )nvApiQueryInterface(NVAPI_INITIALIZE);
				nvApiUnload           = (PFN_NVAPI_UNLOAD          )nvApiQueryInterface(NVAPI_UNLOAD);
				nvApiEnumPhysicalGPUs = (PFN_NVAPI_ENUMPHYSICALGPUS)nvApiQueryInterface(NVAPI_ENUMPHYSICALGPUS);
				nvApiGpuGetMemoryInfo = (PFN_NVAPI_GPUGETMEMORYINFO)nvApiQueryInterface(NVAPI_GPUGETMEMORYINFO);
				nvApiGpuGetFullName   = (PFN_NVAPI_GPUGETFULLNAME  )nvApiQueryInterface(NVAPI_GPUGETFULLNAME);

				nvApiD3D11MultiDrawInstancedIndirect        = (PFN_NVAPI_MULTIDRAWINDIRECT)nvApiQueryInterface(NVAPI_MULTIDRAWINSTANCEDINDIRECT);
				nvApiD3D11MultiDrawIndexedInstancedIndirect = (PFN_NVAPI_MULTIDRAWINDIRECT)nvApiQueryInterface(NVAPI_MULTIDRAWINDEXEDINSTANCEDINDIRECT);

				nvApiD3DSetSleepMode     = (PFN_NVAPI_D3DSETSLEEPMODE    )nvApiQueryInterface(NVAPI_D3DSETSLEEPMODE);
				nvApiD3DSleep            = (PFN_NVAPI_D3DSLEEP           )nvApiQueryInterface(NVAPI_D3DSLEEP);
				nvApiD3DSetLatencyMarker = (PFN_NVAPI_D3DSETLATENCYMARKER)nvApiQueryInterface(NVAPI_D3DSETLATENCYMARKER);
				nvApiD3DGetLatency       = (PFN_NVAPI_D3DGETLATENCY      )nvApiQueryInterface(NVAPI_D3DGETLATENCY);

				initialized = true
					&& NULL != nvApiInitialize
					&& NULL != nvApiUnload
					&& NULL != nvApiEnumPhysicalGPUs
					&& NULL != nvApiGpuGetMemoryInfo
					&& NULL != nvApiGpuGetFullName
					&& NVAPI_OK == nvApiInitialize()
					;

				if (initialized)
				{
					NvPhysicalGpuHandle* physicalGpus[NVAPI_MAX_PHYSICAL_GPUS];
					uint32_t numGpus = 0;
					nvApiEnumPhysicalGPUs(physicalGpus, &numGpus);

					initialized = 0 < numGpus;
					if (initialized)
					{
						m_nvGpu = physicalGpus[0];

						initialized = NULL != m_nvGpu;
						if (initialized)
						{
							char name[64];
							nvApiGpuGetFullName(m_nvGpu, name);
							BX_TRACE("%s", name);
						}
						else
						{
							nvApiUnload();
						}
					}
				}
			}

			if (!initialized)
			{
				bx::dlclose(m_nvApiDll);
				m_nvApiDll = NULL;
			}

			BX_WARN(!initialized, "NVAPI supported.");
		}
	}

	void NvApi::shutdown()
	{
		m_reflexDevice = NULL;

		if (NULL != m_latencyResult)
		{
			bx::deleteObject(g_allocator, m_latencyResult);
			m_latencyResult = NULL;
		}

		if (NULL != m_nvGpu)
		{
			nvApiUnload();
			m_nvGpu = NULL;
		}

		if (NULL != m_nvApiDll)
		{
			bx::dlclose(m_nvApiDll);
			m_nvApiDll = NULL;
		}

		shutdownAftermath();
	}

	void NvApi::getMemoryInfo(int64_t& _gpuMemoryUsed, int64_t& _gpuMemoryMax)
	{
		if (NULL != m_nvGpu)
		{
			NvMemoryInfoV2 memInfo;
			NvApiStatus status = nvApiGpuGetMemoryInfo(m_nvGpu, &memInfo);
			if (NVAPI_OK == status)
			{
				_gpuMemoryMax  = 1024 * int64_t(memInfo.availableDedicatedVideoMemory);
				_gpuMemoryUsed = 1024 * int64_t(memInfo.availableDedicatedVideoMemory - memInfo.curAvailableDedicatedVideoMemory);
//				BX_TRACE("            dedicatedVideoMemory: %d KiB", memInfo.dedicatedVideoMemory);
//				BX_TRACE("   availableDedicatedVideoMemory: %d KiB", memInfo.availableDedicatedVideoMemory);
//				BX_TRACE("               systemVideoMemory: %d KiB", memInfo.systemVideoMemory);
//				BX_TRACE("              sharedSystemMemory: %d KiB", memInfo.sharedSystemMemory);
//				BX_TRACE("curAvailableDedicatedVideoMemory: %d KiB", memInfo.curAvailableDedicatedVideoMemory);
			}
		}
		else
		{
			_gpuMemoryMax  = -INT64_MAX;
			_gpuMemoryUsed = -INT64_MAX;
		}
	}

	bool NvApi::loadAftermath()
	{
		m_nvAftermathDll = bx::dlopen(
			"GFSDK_Aftermath_Lib."
#if BX_ARCH_32BIT
			"x86"
#else
			"x64"
#endif // BX_ARCH_32BIT
			".dll"
			);

		if (NULL != m_nvAftermathDll)
		{
			nvAftermathDx11Initialize          = (PFN_NVAFTERMATH_DX11_INITIALIZE         )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_DX11_Initialize");
			nvAftermathDx11CreateContextHandle = (PFN_NVAFTERMATH_DX11_CREATECONTEXTHANDLE)bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_DX11_CreateContextHandle");
			nvAftermathDx12Initialize          = (PFN_NVAFTERMATH_DX12_INITIALIZE         )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_DX12_Initialize");
			nvAftermathDx12CreateContextHandle = (PFN_NVAFTERMATH_DX12_CREATECONTEXTHANDLE)bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_DX12_CreateContextHandle");
			nvAftermathReleaseContextHandle	   = (PFN_NVAFTERMATH_RELEASECONTEXTHANDLE    )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_ReleaseContextHandle");
			nvAftermathSetEventMarker          = (PFN_NVAFTERMATH_SETEVENTMARKER          )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_SetEventMarker");
			nvAftermathGetData                 = (PFN_NVAFTERMATH_GETDATA                 )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_GetData");
			nvAftermathGetDeviceStatus         = (PFN_NVAFTERMATH_GETDEVICESTATUS         )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_GetDeviceStatus");
			nvAftermathGetPageFaultInformation = (PFN_NVAFTERMATH_GETPAGEFAULTINFORMATION )bx::dlsym(m_nvAftermathDll, "GFSDK_Aftermath_GetPageFaultInformation");

			bool initialized = true
				&& NULL != nvAftermathDx11Initialize
				&& NULL != nvAftermathDx11CreateContextHandle
				&& NULL != nvAftermathDx12Initialize
				&& NULL != nvAftermathDx12CreateContextHandle
				&& NULL != nvAftermathReleaseContextHandle
				&& NULL != nvAftermathSetEventMarker
				&& NULL != nvAftermathGetData
				&& NULL != nvAftermathGetDeviceStatus
				&& NULL != nvAftermathGetPageFaultInformation
				;

			if (initialized)
			{
				return true;
			}

			shutdownAftermath();
		}

		return false;
	}

	bool NvApi::initAftermath(const ID3D11Device* _device, const ID3D11DeviceContext* _deviceCtx)
	{
		if (loadAftermath() )
		{
			int32_t result;
			result = nvAftermathDx11Initialize(0x13, 1, _device);
			if (1 == result)
			{
				result = nvAftermathDx11CreateContextHandle(_deviceCtx, &m_aftermathHandle);
				BX_WARN(1 == result, "NV Aftermath: nvAftermathDx12CreateContextHandle failed %x", result);

				if (1 == result)
				{
					return true;
				}
			}
			else
			{
				switch (result)
				{
				case int32_t(0xbad0000a): BX_TRACE("NV Aftermath: Debug layer not compatible with Aftermath."); break;
				default:                  BX_TRACE("NV Aftermath: Failed to initialize."); break;
				}
			}

			shutdownAftermath();
		}

		return false;
	}

	bool NvApi::initAftermath(const ID3D12Device* _device, const ID3D12CommandList* _commandList)
	{
		if (loadAftermath() )
		{
			int32_t result;
			result = nvAftermathDx12Initialize(0x13, 1, _device);
			if (1 == result)
			{
				result = nvAftermathDx12CreateContextHandle(_commandList, &m_aftermathHandle);
				BX_WARN(1 == result, "NV Aftermath: nvAftermathDx12CreateContextHandle failed %x", result);

				if (1 == result)
				{
					return true;
				}
			}
			else
			{
				switch (result)
				{
				case int32_t(0xbad0000a): BX_TRACE("NV Aftermath: Debug layer not compatible with Aftermath."); break;
				default:                  BX_TRACE("NV Aftermath: Failed to initialize."); break;
				}
			}

			shutdownAftermath();
		}

		return false;
	}

	NvAftermathDeviceStatus::Enum NvApi::getDeviceStatus() const
	{
		if (NULL != m_aftermathHandle)
		{
			int32_t status;
			nvAftermathGetDeviceStatus(&status);

			return NvAftermathDeviceStatus::Enum(status);
		}

		return NvAftermathDeviceStatus::NotInitialized;
	}

	void NvApi::shutdownAftermath()
	{
		if (NULL != m_nvAftermathDll)
		{
			if (NULL != m_aftermathHandle)
			{
				nvAftermathReleaseContextHandle(m_aftermathHandle);
				m_aftermathHandle = NULL;
			}

			bx::dlclose(m_nvAftermathDll);
			m_nvAftermathDll = NULL;
		}
	}

#define NVA_CHECK(_call)                                                          \
			BX_MACRO_BLOCK_BEGIN                                                  \
				int32_t __result__ = _call;                                       \
				BX_ASSERT(1 == __result__, #_call " FAILED 0x%08x\n", __result__); \
				BX_UNUSED(__result__);                                            \
			BX_MACRO_BLOCK_END

	void NvApi::setMarker(const bx::StringView& _marker)
	{
		if (NULL != m_aftermathHandle)
		{
			NVA_CHECK(nvAftermathSetEventMarker(m_aftermathHandle, _marker.getPtr(), _marker.getLength() ) );
		}
	}

	bool NvApi::initReflex(IUnknown* _device)
	{
		m_reflexDevice = NULL;

		// Reflex is available on Windows only.
		if (!BX_ENABLED(BX_PLATFORM_WINDOWS)
		||  !isInitialized()
		||  NULL == nvApiD3DSetSleepMode
		||  NULL == nvApiD3DSleep
		||  NULL == nvApiD3DSetLatencyMarker
		||  NULL == nvApiD3DGetLatency)
		{
			return false;
		}

		NvSetSleepModeParamsV1 params;
		const NvApiStatus status = nvApiD3DSetSleepMode(_device, &params);

		if (NVAPI_OK != status)
		{
			BX_TRACE("NVAPI: Reflex is not supported, NvAPI_D3D_SetSleepMode failed %d.", status);
			return false;
		}

		BX_TRACE("NVAPI: Reflex supported.");

		m_reflexDevice = _device;

		if (NULL == m_latencyResult)
		{
			// Latency result holds 64 frame reports, it's too big for the stack.
			m_latencyResult = BX_NEW(g_allocator, NvLatencyResultParamsV1);
		}

		return true;
	}

	void NvApi::shutdownReflex()
	{
		if (NULL != m_reflexDevice)
		{
			setSleepMode(LatencyMode::Off);
			m_reflexDevice = NULL;
		}

		if (NULL != m_latencyResult)
		{
			bx::deleteObject(g_allocator, m_latencyResult);
			m_latencyResult = NULL;
		}
	}

	void NvApi::setSleepMode(LatencyMode::Enum _mode)
	{
		if (NULL != m_reflexDevice)
		{
			NvSetSleepModeParamsV1 params;
			params.lowLatencyMode  = LatencyMode::Off   != _mode;
			params.lowLatencyBoost = LatencyMode::Boost == _mode;

			const NvApiStatus status = nvApiD3DSetSleepMode(m_reflexDevice, &params);
			BX_WARN(NVAPI_OK == status, "NVAPI: NvAPI_D3D_SetSleepMode failed %d.", status); BX_UNUSED(status);
		}
	}

	void NvApi::sleep()
	{
		if (NULL != m_reflexDevice)
		{
			nvApiD3DSleep(m_reflexDevice);
		}
	}

	void NvApi::setLatencyMarker(LatencyMarker::Enum _marker, uint64_t _frameId)
	{
		if (NULL != m_reflexDevice)
		{
			NvLatencyMarkerParamsV1 params;
			params.frameId    = _frameId;
			params.markerType = s_nvLatencyMarker[_marker];

			nvApiD3DSetLatencyMarker(m_reflexDevice, &params);
		}
	}

	bool NvApi::getLatencyReport(LatencyReport& _report)
	{
		if (NULL == m_reflexDevice
		||  NULL == m_latencyResult)
		{
			return false;
		}

		NvLatencyResultParamsV1& params = *m_latencyResult;
		if (NVAPI_OK != nvApiD3DGetLatency(m_reflexDevice, &params) )
		{
			return false;
		}

		for (uint32_t ii = BX_COUNTOF(params.frameReport); 0 < ii; --ii)
		{
			const NvLatencyFrameReport& frame = params.frameReport[ii-1];

			if (0 != frame.simStartTime
			&&  frame.gpuRenderEndTime > frame.simStartTime)
			{
				_report.simulationStart   = frame.simStartTime;
				_report.simulationEnd     = frame.simEndTime;
				_report.renderSubmitStart = frame.renderSubmitStartTime;
				_report.renderSubmitEnd   = frame.renderSubmitEndTime;
				_report.presentStart      = frame.presentStartTime;
				_report.presentEnd        = frame.presentEndTime;
				_report.gpuRenderStart    = frame.gpuRenderStartTime;
				_report.gpuRenderEnd      = frame.gpuRenderEndTime;
				return true;
			}
		}

		return false;
	}

} // namespace bgfx
