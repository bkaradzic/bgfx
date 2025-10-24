

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 501
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dxgi1_6_h__
#define __dxgi1_6_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IDXGIAdapter4_FWD_DEFINED__
#define __IDXGIAdapter4_FWD_DEFINED__
typedef interface IDXGIAdapter4 IDXGIAdapter4;

#endif 	/* __IDXGIAdapter4_FWD_DEFINED__ */


#ifndef __IDXGIOutput6_FWD_DEFINED__
#define __IDXGIOutput6_FWD_DEFINED__
typedef interface IDXGIOutput6 IDXGIOutput6;

#endif 	/* __IDXGIOutput6_FWD_DEFINED__ */


#ifndef __IDXGIFactory6_FWD_DEFINED__
#define __IDXGIFactory6_FWD_DEFINED__
typedef interface IDXGIFactory6 IDXGIFactory6;

#endif 	/* __IDXGIFactory6_FWD_DEFINED__ */


#ifndef __IDXGIFactory7_FWD_DEFINED__
#define __IDXGIFactory7_FWD_DEFINED__
typedef interface IDXGIFactory7 IDXGIFactory7;

#endif 	/* __IDXGIFactory7_FWD_DEFINED__ */


/* header files for imported files */
#include "dxgi1_5.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_dxgi1_6_0000_0000 */
/* [local] */ 

// Copyright (c) Microsoft Corporation.  All Rights Reserved
#include <winapifamily.h>
#pragma region App Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP | WINAPI_PARTITION_GAMES)
HRESULT WINAPI DXGIDeclareAdapterRemovalSupport();
typedef 
enum DXGI_ADAPTER_FLAG3
    {
        DXGI_ADAPTER_FLAG3_NONE	= 0,
        DXGI_ADAPTER_FLAG3_REMOTE	= 1,
        DXGI_ADAPTER_FLAG3_SOFTWARE	= 2,
        DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE	= 4,
        DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES	= 8,
        DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES	= 0x10,
        DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE	= 0x20,
        DXGI_ADAPTER_FLAG3_FORCE_DWORD	= 0xffffffff
    } 	DXGI_ADAPTER_FLAG3;

DEFINE_ENUM_FLAG_OPERATORS( DXGI_ADAPTER_FLAG3 );
typedef struct DXGI_ADAPTER_DESC3
    {
    WCHAR Description[ 128 ];
    UINT VendorId;
    UINT DeviceId;
    UINT SubSysId;
    UINT Revision;
    SIZE_T DedicatedVideoMemory;
    SIZE_T DedicatedSystemMemory;
    SIZE_T SharedSystemMemory;
    LUID AdapterLuid;
    DXGI_ADAPTER_FLAG3 Flags;
    DXGI_GRAPHICS_PREEMPTION_GRANULARITY GraphicsPreemptionGranularity;
    DXGI_COMPUTE_PREEMPTION_GRANULARITY ComputePreemptionGranularity;
    } 	DXGI_ADAPTER_DESC3;



extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0000_v0_0_s_ifspec;

#ifndef __IDXGIAdapter4_INTERFACE_DEFINED__
#define __IDXGIAdapter4_INTERFACE_DEFINED__

/* interface IDXGIAdapter4 */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IDXGIAdapter4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3c8d99d1-4fbf-4181-a82c-af66bf7bd24e")
    IDXGIAdapter4 : public IDXGIAdapter3
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDesc3( 
            /* [annotation][out] */ 
            _Out_  DXGI_ADAPTER_DESC3 *pDesc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIAdapter4Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIAdapter4 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIAdapter4 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIAdapter4 * This);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetParent)
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter, EnumOutputs)
        HRESULT ( STDMETHODCALLTYPE *EnumOutputs )( 
            IDXGIAdapter4 * This,
            /* [in] */ UINT Output,
            /* [annotation][out][in] */ 
            _COM_Outptr_  IDXGIOutput **ppOutput);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter, GetDesc)
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGIAdapter4 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_ADAPTER_DESC *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter, CheckInterfaceSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckInterfaceSupport )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  REFGUID InterfaceName,
            /* [annotation][out] */ 
            _Out_  LARGE_INTEGER *pUMDVersion);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter1, GetDesc1)
        HRESULT ( STDMETHODCALLTYPE *GetDesc1 )( 
            IDXGIAdapter4 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_ADAPTER_DESC1 *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter2, GetDesc2)
        HRESULT ( STDMETHODCALLTYPE *GetDesc2 )( 
            IDXGIAdapter4 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_ADAPTER_DESC2 *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, RegisterHardwareContentProtectionTeardownStatusEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterHardwareContentProtectionTeardownStatusEvent )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, UnregisterHardwareContentProtectionTeardownStatus)
        void ( STDMETHODCALLTYPE *UnregisterHardwareContentProtectionTeardownStatus )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, QueryVideoMemoryInfo)
        HRESULT ( STDMETHODCALLTYPE *QueryVideoMemoryInfo )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  UINT NodeIndex,
            /* [annotation][in] */ 
            _In_  DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
            /* [annotation][out] */ 
            _Out_  DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, SetVideoMemoryReservation)
        HRESULT ( STDMETHODCALLTYPE *SetVideoMemoryReservation )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  UINT NodeIndex,
            /* [annotation][in] */ 
            _In_  DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup,
            /* [annotation][in] */ 
            _In_  UINT64 Reservation);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, RegisterVideoMemoryBudgetChangeNotificationEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterVideoMemoryBudgetChangeNotificationEvent )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter3, UnregisterVideoMemoryBudgetChangeNotification)
        void ( STDMETHODCALLTYPE *UnregisterVideoMemoryBudgetChangeNotification )( 
            IDXGIAdapter4 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIAdapter4, GetDesc3)
        HRESULT ( STDMETHODCALLTYPE *GetDesc3 )( 
            IDXGIAdapter4 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_ADAPTER_DESC3 *pDesc);
        
        END_INTERFACE
    } IDXGIAdapter4Vtbl;

    interface IDXGIAdapter4
    {
        CONST_VTBL struct IDXGIAdapter4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIAdapter4_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIAdapter4_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIAdapter4_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIAdapter4_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGIAdapter4_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGIAdapter4_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGIAdapter4_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGIAdapter4_EnumOutputs(This,Output,ppOutput)	\
    ( (This)->lpVtbl -> EnumOutputs(This,Output,ppOutput) ) 

#define IDXGIAdapter4_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 

#define IDXGIAdapter4_CheckInterfaceSupport(This,InterfaceName,pUMDVersion)	\
    ( (This)->lpVtbl -> CheckInterfaceSupport(This,InterfaceName,pUMDVersion) ) 


#define IDXGIAdapter4_GetDesc1(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc1(This,pDesc) ) 


#define IDXGIAdapter4_GetDesc2(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc2(This,pDesc) ) 


#define IDXGIAdapter4_RegisterHardwareContentProtectionTeardownStatusEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterHardwareContentProtectionTeardownStatusEvent(This,hEvent,pdwCookie) ) 

#define IDXGIAdapter4_UnregisterHardwareContentProtectionTeardownStatus(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterHardwareContentProtectionTeardownStatus(This,dwCookie) ) 

#define IDXGIAdapter4_QueryVideoMemoryInfo(This,NodeIndex,MemorySegmentGroup,pVideoMemoryInfo)	\
    ( (This)->lpVtbl -> QueryVideoMemoryInfo(This,NodeIndex,MemorySegmentGroup,pVideoMemoryInfo) ) 

#define IDXGIAdapter4_SetVideoMemoryReservation(This,NodeIndex,MemorySegmentGroup,Reservation)	\
    ( (This)->lpVtbl -> SetVideoMemoryReservation(This,NodeIndex,MemorySegmentGroup,Reservation) ) 

#define IDXGIAdapter4_RegisterVideoMemoryBudgetChangeNotificationEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterVideoMemoryBudgetChangeNotificationEvent(This,hEvent,pdwCookie) ) 

#define IDXGIAdapter4_UnregisterVideoMemoryBudgetChangeNotification(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterVideoMemoryBudgetChangeNotification(This,dwCookie) ) 


#define IDXGIAdapter4_GetDesc3(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc3(This,pDesc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIAdapter4_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dxgi1_6_0000_0001 */
/* [local] */ 

typedef struct DXGI_OUTPUT_DESC1
    {
    WCHAR DeviceName[ 32 ];
    RECT DesktopCoordinates;
    BOOL AttachedToDesktop;
    DXGI_MODE_ROTATION Rotation;
    HMONITOR Monitor;
    UINT BitsPerColor;
    DXGI_COLOR_SPACE_TYPE ColorSpace;
    FLOAT RedPrimary[ 2 ];
    FLOAT GreenPrimary[ 2 ];
    FLOAT BluePrimary[ 2 ];
    FLOAT WhitePoint[ 2 ];
    FLOAT MinLuminance;
    FLOAT MaxLuminance;
    FLOAT MaxFullFrameLuminance;
    } 	DXGI_OUTPUT_DESC1;

typedef 
enum DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS
    {
        DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_FULLSCREEN	= 1,
        DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_WINDOWED	= 2,
        DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_CURSOR_STRETCHED	= 4
    } 	DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS );


extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0001_v0_0_s_ifspec;

#ifndef __IDXGIOutput6_INTERFACE_DEFINED__
#define __IDXGIOutput6_INTERFACE_DEFINED__

/* interface IDXGIOutput6 */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IDXGIOutput6;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("068346e8-aaec-4b84-add7-137f513f77a1")
    IDXGIOutput6 : public IDXGIOutput5
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDesc1( 
            /* [annotation][out] */ 
            _Out_  DXGI_OUTPUT_DESC1 *pDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckHardwareCompositionSupport( 
            /* [annotation][out] */ 
            _Out_  UINT *pFlags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIOutput6Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIOutput6 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIOutput6 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIOutput6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetParent)
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetDesc)
        HRESULT ( STDMETHODCALLTYPE *GetDesc )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_OUTPUT_DESC *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetDisplayModeList)
        HRESULT ( STDMETHODCALLTYPE *GetDisplayModeList )( 
            IDXGIOutput6 * This,
            /* [in] */ DXGI_FORMAT EnumFormat,
            /* [in] */ UINT Flags,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pNumModes,
            /* [annotation][out] */ 
            _Out_writes_to_opt_(*pNumModes,*pNumModes)  DXGI_MODE_DESC *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, FindClosestMatchingMode)
        HRESULT ( STDMETHODCALLTYPE *FindClosestMatchingMode )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  const DXGI_MODE_DESC *pModeToMatch,
            /* [annotation][out] */ 
            _Out_  DXGI_MODE_DESC *pClosestMatch,
            /* [annotation][in] */ 
            _In_opt_  IUnknown *pConcernedDevice);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, WaitForVBlank)
        HRESULT ( STDMETHODCALLTYPE *WaitForVBlank )( 
            IDXGIOutput6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, TakeOwnership)
        HRESULT ( STDMETHODCALLTYPE *TakeOwnership )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            BOOL Exclusive);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, ReleaseOwnership)
        void ( STDMETHODCALLTYPE *ReleaseOwnership )( 
            IDXGIOutput6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetGammaControlCapabilities)
        HRESULT ( STDMETHODCALLTYPE *GetGammaControlCapabilities )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, SetGammaControl)
        HRESULT ( STDMETHODCALLTYPE *SetGammaControl )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  const DXGI_GAMMA_CONTROL *pArray);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetGammaControl)
        HRESULT ( STDMETHODCALLTYPE *GetGammaControl )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_GAMMA_CONTROL *pArray);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, SetDisplaySurface)
        HRESULT ( STDMETHODCALLTYPE *SetDisplaySurface )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IDXGISurface *pScanoutSurface);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetDisplaySurfaceData)
        HRESULT ( STDMETHODCALLTYPE *GetDisplaySurfaceData )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IDXGISurface *pDestination);
        
        DECLSPEC_XFGVIRT(IDXGIOutput, GetFrameStatistics)
        HRESULT ( STDMETHODCALLTYPE *GetFrameStatistics )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_FRAME_STATISTICS *pStats);
        
        DECLSPEC_XFGVIRT(IDXGIOutput1, GetDisplayModeList1)
        HRESULT ( STDMETHODCALLTYPE *GetDisplayModeList1 )( 
            IDXGIOutput6 * This,
            /* [in] */ DXGI_FORMAT EnumFormat,
            /* [in] */ UINT Flags,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pNumModes,
            /* [annotation][out] */ 
            _Out_writes_to_opt_(*pNumModes,*pNumModes)  DXGI_MODE_DESC1 *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIOutput1, FindClosestMatchingMode1)
        HRESULT ( STDMETHODCALLTYPE *FindClosestMatchingMode1 )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  const DXGI_MODE_DESC1 *pModeToMatch,
            /* [annotation][out] */ 
            _Out_  DXGI_MODE_DESC1 *pClosestMatch,
            /* [annotation][in] */ 
            _In_opt_  IUnknown *pConcernedDevice);
        
        DECLSPEC_XFGVIRT(IDXGIOutput1, GetDisplaySurfaceData1)
        HRESULT ( STDMETHODCALLTYPE *GetDisplaySurfaceData1 )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IDXGIResource *pDestination);
        
        DECLSPEC_XFGVIRT(IDXGIOutput1, DuplicateOutput)
        HRESULT ( STDMETHODCALLTYPE *DuplicateOutput )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIOutputDuplication **ppOutputDuplication);
        
        DECLSPEC_XFGVIRT(IDXGIOutput2, SupportsOverlays)
        BOOL ( STDMETHODCALLTYPE *SupportsOverlays )( 
            IDXGIOutput6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIOutput3, CheckOverlaySupport)
        HRESULT ( STDMETHODCALLTYPE *CheckOverlaySupport )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  DXGI_FORMAT EnumFormat,
            /* [annotation][out] */ 
            _In_  IUnknown *pConcernedDevice,
            /* [annotation][out] */ 
            _Out_  UINT *pFlags);
        
        DECLSPEC_XFGVIRT(IDXGIOutput4, CheckOverlayColorSpaceSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckOverlayColorSpaceSupport )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  DXGI_FORMAT Format,
            /* [annotation][in] */ 
            _In_  DXGI_COLOR_SPACE_TYPE ColorSpace,
            /* [annotation][in] */ 
            _In_  IUnknown *pConcernedDevice,
            /* [annotation][out] */ 
            _Out_  UINT *pFlags);
        
        DECLSPEC_XFGVIRT(IDXGIOutput5, DuplicateOutput1)
        HRESULT ( STDMETHODCALLTYPE *DuplicateOutput1 )( 
            IDXGIOutput6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [in] */ UINT Flags,
            /* [annotation][in] */ 
            _In_  UINT SupportedFormatsCount,
            /* [annotation][in] */ 
            _In_reads_(SupportedFormatsCount)  const DXGI_FORMAT *pSupportedFormats,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIOutputDuplication **ppOutputDuplication);
        
        DECLSPEC_XFGVIRT(IDXGIOutput6, GetDesc1)
        HRESULT ( STDMETHODCALLTYPE *GetDesc1 )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  DXGI_OUTPUT_DESC1 *pDesc);
        
        DECLSPEC_XFGVIRT(IDXGIOutput6, CheckHardwareCompositionSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckHardwareCompositionSupport )( 
            IDXGIOutput6 * This,
            /* [annotation][out] */ 
            _Out_  UINT *pFlags);
        
        END_INTERFACE
    } IDXGIOutput6Vtbl;

    interface IDXGIOutput6
    {
        CONST_VTBL struct IDXGIOutput6Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIOutput6_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIOutput6_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIOutput6_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIOutput6_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGIOutput6_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGIOutput6_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGIOutput6_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGIOutput6_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 

#define IDXGIOutput6_GetDisplayModeList(This,EnumFormat,Flags,pNumModes,pDesc)	\
    ( (This)->lpVtbl -> GetDisplayModeList(This,EnumFormat,Flags,pNumModes,pDesc) ) 

#define IDXGIOutput6_FindClosestMatchingMode(This,pModeToMatch,pClosestMatch,pConcernedDevice)	\
    ( (This)->lpVtbl -> FindClosestMatchingMode(This,pModeToMatch,pClosestMatch,pConcernedDevice) ) 

#define IDXGIOutput6_WaitForVBlank(This)	\
    ( (This)->lpVtbl -> WaitForVBlank(This) ) 

#define IDXGIOutput6_TakeOwnership(This,pDevice,Exclusive)	\
    ( (This)->lpVtbl -> TakeOwnership(This,pDevice,Exclusive) ) 

#define IDXGIOutput6_ReleaseOwnership(This)	\
    ( (This)->lpVtbl -> ReleaseOwnership(This) ) 

#define IDXGIOutput6_GetGammaControlCapabilities(This,pGammaCaps)	\
    ( (This)->lpVtbl -> GetGammaControlCapabilities(This,pGammaCaps) ) 

#define IDXGIOutput6_SetGammaControl(This,pArray)	\
    ( (This)->lpVtbl -> SetGammaControl(This,pArray) ) 

#define IDXGIOutput6_GetGammaControl(This,pArray)	\
    ( (This)->lpVtbl -> GetGammaControl(This,pArray) ) 

#define IDXGIOutput6_SetDisplaySurface(This,pScanoutSurface)	\
    ( (This)->lpVtbl -> SetDisplaySurface(This,pScanoutSurface) ) 

#define IDXGIOutput6_GetDisplaySurfaceData(This,pDestination)	\
    ( (This)->lpVtbl -> GetDisplaySurfaceData(This,pDestination) ) 

#define IDXGIOutput6_GetFrameStatistics(This,pStats)	\
    ( (This)->lpVtbl -> GetFrameStatistics(This,pStats) ) 


#define IDXGIOutput6_GetDisplayModeList1(This,EnumFormat,Flags,pNumModes,pDesc)	\
    ( (This)->lpVtbl -> GetDisplayModeList1(This,EnumFormat,Flags,pNumModes,pDesc) ) 

#define IDXGIOutput6_FindClosestMatchingMode1(This,pModeToMatch,pClosestMatch,pConcernedDevice)	\
    ( (This)->lpVtbl -> FindClosestMatchingMode1(This,pModeToMatch,pClosestMatch,pConcernedDevice) ) 

#define IDXGIOutput6_GetDisplaySurfaceData1(This,pDestination)	\
    ( (This)->lpVtbl -> GetDisplaySurfaceData1(This,pDestination) ) 

#define IDXGIOutput6_DuplicateOutput(This,pDevice,ppOutputDuplication)	\
    ( (This)->lpVtbl -> DuplicateOutput(This,pDevice,ppOutputDuplication) ) 


#define IDXGIOutput6_SupportsOverlays(This)	\
    ( (This)->lpVtbl -> SupportsOverlays(This) ) 


#define IDXGIOutput6_CheckOverlaySupport(This,EnumFormat,pConcernedDevice,pFlags)	\
    ( (This)->lpVtbl -> CheckOverlaySupport(This,EnumFormat,pConcernedDevice,pFlags) ) 


#define IDXGIOutput6_CheckOverlayColorSpaceSupport(This,Format,ColorSpace,pConcernedDevice,pFlags)	\
    ( (This)->lpVtbl -> CheckOverlayColorSpaceSupport(This,Format,ColorSpace,pConcernedDevice,pFlags) ) 


#define IDXGIOutput6_DuplicateOutput1(This,pDevice,Flags,SupportedFormatsCount,pSupportedFormats,ppOutputDuplication)	\
    ( (This)->lpVtbl -> DuplicateOutput1(This,pDevice,Flags,SupportedFormatsCount,pSupportedFormats,ppOutputDuplication) ) 


#define IDXGIOutput6_GetDesc1(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc1(This,pDesc) ) 

#define IDXGIOutput6_CheckHardwareCompositionSupport(This,pFlags)	\
    ( (This)->lpVtbl -> CheckHardwareCompositionSupport(This,pFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIOutput6_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dxgi1_6_0000_0002 */
/* [local] */ 

typedef 
enum DXGI_GPU_PREFERENCE
    {
        DXGI_GPU_PREFERENCE_UNSPECIFIED	= 0,
        DXGI_GPU_PREFERENCE_MINIMUM_POWER	= ( DXGI_GPU_PREFERENCE_UNSPECIFIED + 1 ) ,
        DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE	= ( DXGI_GPU_PREFERENCE_MINIMUM_POWER + 1 ) 
    } 	DXGI_GPU_PREFERENCE;



extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0002_v0_0_s_ifspec;

#ifndef __IDXGIFactory6_INTERFACE_DEFINED__
#define __IDXGIFactory6_INTERFACE_DEFINED__

/* interface IDXGIFactory6 */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IDXGIFactory6;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c1b6694f-ff09-44a9-b03c-77900a0a1d17")
    IDXGIFactory6 : public IDXGIFactory5
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumAdapterByGpuPreference( 
            /* [annotation] */ 
            _In_  UINT Adapter,
            /* [annotation] */ 
            _In_  DXGI_GPU_PREFERENCE GpuPreference,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIFactory6Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIFactory6 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIFactory6 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIFactory6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetParent)
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, EnumAdapters)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapters )( 
            IDXGIFactory6 * This,
            /* [in] */ UINT Adapter,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, MakeWindowAssociation)
        HRESULT ( STDMETHODCALLTYPE *MakeWindowAssociation )( 
            IDXGIFactory6 * This,
            HWND WindowHandle,
            UINT Flags);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, GetWindowAssociation)
        HRESULT ( STDMETHODCALLTYPE *GetWindowAssociation )( 
            IDXGIFactory6 * This,
            /* [annotation][out] */ 
            _Out_  HWND *pWindowHandle);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, CreateSwapChain)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChain )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  DXGI_SWAP_CHAIN_DESC *pDesc,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, CreateSoftwareAdapter)
        HRESULT ( STDMETHODCALLTYPE *CreateSoftwareAdapter )( 
            IDXGIFactory6 * This,
            /* [in] */ HMODULE Module,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory1, EnumAdapters1)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapters1 )( 
            IDXGIFactory6 * This,
            /* [in] */ UINT Adapter,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter1 **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory1, IsCurrent)
        BOOL ( STDMETHODCALLTYPE *IsCurrent )( 
            IDXGIFactory6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, IsWindowedStereoEnabled)
        BOOL ( STDMETHODCALLTYPE *IsWindowedStereoEnabled )( 
            IDXGIFactory6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForHwnd)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForHwnd )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  HWND hWnd,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForCoreWindow)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForCoreWindow )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  IUnknown *pWindow,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, GetSharedResourceAdapterLuid)
        HRESULT ( STDMETHODCALLTYPE *GetSharedResourceAdapterLuid )( 
            IDXGIFactory6 * This,
            /* [annotation] */ 
            _In_  HANDLE hResource,
            /* [annotation] */ 
            _Out_  LUID *pLuid);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterStereoStatusWindow)
        HRESULT ( STDMETHODCALLTYPE *RegisterStereoStatusWindow )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  HWND WindowHandle,
            /* [annotation][in] */ 
            _In_  UINT wMsg,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterStereoStatusEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterStereoStatusEvent )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, UnregisterStereoStatus)
        void ( STDMETHODCALLTYPE *UnregisterStereoStatus )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterOcclusionStatusWindow)
        HRESULT ( STDMETHODCALLTYPE *RegisterOcclusionStatusWindow )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  HWND WindowHandle,
            /* [annotation][in] */ 
            _In_  UINT wMsg,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterOcclusionStatusEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterOcclusionStatusEvent )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, UnregisterOcclusionStatus)
        void ( STDMETHODCALLTYPE *UnregisterOcclusionStatus )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForComposition)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForComposition )( 
            IDXGIFactory6 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory3, GetCreationFlags)
        UINT ( STDMETHODCALLTYPE *GetCreationFlags )( 
            IDXGIFactory6 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory4, EnumAdapterByLuid)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapterByLuid )( 
            IDXGIFactory6 * This,
            /* [annotation] */ 
            _In_  LUID AdapterLuid,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory4, EnumWarpAdapter)
        HRESULT ( STDMETHODCALLTYPE *EnumWarpAdapter )( 
            IDXGIFactory6 * This,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory5, CheckFeatureSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckFeatureSupport )( 
            IDXGIFactory6 * This,
            DXGI_FEATURE Feature,
            /* [annotation] */ 
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT FeatureSupportDataSize);
        
        DECLSPEC_XFGVIRT(IDXGIFactory6, EnumAdapterByGpuPreference)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapterByGpuPreference )( 
            IDXGIFactory6 * This,
            /* [annotation] */ 
            _In_  UINT Adapter,
            /* [annotation] */ 
            _In_  DXGI_GPU_PREFERENCE GpuPreference,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        END_INTERFACE
    } IDXGIFactory6Vtbl;

    interface IDXGIFactory6
    {
        CONST_VTBL struct IDXGIFactory6Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIFactory6_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIFactory6_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIFactory6_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIFactory6_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGIFactory6_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGIFactory6_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGIFactory6_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGIFactory6_EnumAdapters(This,Adapter,ppAdapter)	\
    ( (This)->lpVtbl -> EnumAdapters(This,Adapter,ppAdapter) ) 

#define IDXGIFactory6_MakeWindowAssociation(This,WindowHandle,Flags)	\
    ( (This)->lpVtbl -> MakeWindowAssociation(This,WindowHandle,Flags) ) 

#define IDXGIFactory6_GetWindowAssociation(This,pWindowHandle)	\
    ( (This)->lpVtbl -> GetWindowAssociation(This,pWindowHandle) ) 

#define IDXGIFactory6_CreateSwapChain(This,pDevice,pDesc,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChain(This,pDevice,pDesc,ppSwapChain) ) 

#define IDXGIFactory6_CreateSoftwareAdapter(This,Module,ppAdapter)	\
    ( (This)->lpVtbl -> CreateSoftwareAdapter(This,Module,ppAdapter) ) 


#define IDXGIFactory6_EnumAdapters1(This,Adapter,ppAdapter)	\
    ( (This)->lpVtbl -> EnumAdapters1(This,Adapter,ppAdapter) ) 

#define IDXGIFactory6_IsCurrent(This)	\
    ( (This)->lpVtbl -> IsCurrent(This) ) 


#define IDXGIFactory6_IsWindowedStereoEnabled(This)	\
    ( (This)->lpVtbl -> IsWindowedStereoEnabled(This) ) 

#define IDXGIFactory6_CreateSwapChainForHwnd(This,pDevice,hWnd,pDesc,pFullscreenDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForHwnd(This,pDevice,hWnd,pDesc,pFullscreenDesc,pRestrictToOutput,ppSwapChain) ) 

#define IDXGIFactory6_CreateSwapChainForCoreWindow(This,pDevice,pWindow,pDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForCoreWindow(This,pDevice,pWindow,pDesc,pRestrictToOutput,ppSwapChain) ) 

#define IDXGIFactory6_GetSharedResourceAdapterLuid(This,hResource,pLuid)	\
    ( (This)->lpVtbl -> GetSharedResourceAdapterLuid(This,hResource,pLuid) ) 

#define IDXGIFactory6_RegisterStereoStatusWindow(This,WindowHandle,wMsg,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterStereoStatusWindow(This,WindowHandle,wMsg,pdwCookie) ) 

#define IDXGIFactory6_RegisterStereoStatusEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterStereoStatusEvent(This,hEvent,pdwCookie) ) 

#define IDXGIFactory6_UnregisterStereoStatus(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterStereoStatus(This,dwCookie) ) 

#define IDXGIFactory6_RegisterOcclusionStatusWindow(This,WindowHandle,wMsg,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterOcclusionStatusWindow(This,WindowHandle,wMsg,pdwCookie) ) 

#define IDXGIFactory6_RegisterOcclusionStatusEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterOcclusionStatusEvent(This,hEvent,pdwCookie) ) 

#define IDXGIFactory6_UnregisterOcclusionStatus(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterOcclusionStatus(This,dwCookie) ) 

#define IDXGIFactory6_CreateSwapChainForComposition(This,pDevice,pDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForComposition(This,pDevice,pDesc,pRestrictToOutput,ppSwapChain) ) 


#define IDXGIFactory6_GetCreationFlags(This)	\
    ( (This)->lpVtbl -> GetCreationFlags(This) ) 


#define IDXGIFactory6_EnumAdapterByLuid(This,AdapterLuid,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumAdapterByLuid(This,AdapterLuid,riid,ppvAdapter) ) 

#define IDXGIFactory6_EnumWarpAdapter(This,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumWarpAdapter(This,riid,ppvAdapter) ) 


#define IDXGIFactory6_CheckFeatureSupport(This,Feature,pFeatureSupportData,FeatureSupportDataSize)	\
    ( (This)->lpVtbl -> CheckFeatureSupport(This,Feature,pFeatureSupportData,FeatureSupportDataSize) ) 


#define IDXGIFactory6_EnumAdapterByGpuPreference(This,Adapter,GpuPreference,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumAdapterByGpuPreference(This,Adapter,GpuPreference,riid,ppvAdapter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIFactory6_INTERFACE_DEFINED__ */


#ifndef __IDXGIFactory7_INTERFACE_DEFINED__
#define __IDXGIFactory7_INTERFACE_DEFINED__

/* interface IDXGIFactory7 */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IDXGIFactory7;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a4966eed-76db-44da-84c1-ee9a7afb20a8")
    IDXGIFactory7 : public IDXGIFactory6
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterAdaptersChangedEvent( 
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterAdaptersChangedEvent( 
            /* [annotation][in] */ 
            _In_  DWORD dwCookie) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIFactory7Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIFactory7 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIFactory7 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIFactory7 * This);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [in] */ UINT DataSize,
            /* [annotation][in] */ 
            _In_reads_bytes_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][in] */ 
            _In_opt_  const IUnknown *pUnknown);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  REFGUID Name,
            /* [annotation][out][in] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation][out] */ 
            _Out_writes_bytes_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(IDXGIObject, GetParent)
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][retval][out] */ 
            _COM_Outptr_  void **ppParent);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, EnumAdapters)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapters )( 
            IDXGIFactory7 * This,
            /* [in] */ UINT Adapter,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, MakeWindowAssociation)
        HRESULT ( STDMETHODCALLTYPE *MakeWindowAssociation )( 
            IDXGIFactory7 * This,
            HWND WindowHandle,
            UINT Flags);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, GetWindowAssociation)
        HRESULT ( STDMETHODCALLTYPE *GetWindowAssociation )( 
            IDXGIFactory7 * This,
            /* [annotation][out] */ 
            _Out_  HWND *pWindowHandle);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, CreateSwapChain)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChain )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  DXGI_SWAP_CHAIN_DESC *pDesc,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory, CreateSoftwareAdapter)
        HRESULT ( STDMETHODCALLTYPE *CreateSoftwareAdapter )( 
            IDXGIFactory7 * This,
            /* [in] */ HMODULE Module,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory1, EnumAdapters1)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapters1 )( 
            IDXGIFactory7 * This,
            /* [in] */ UINT Adapter,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGIAdapter1 **ppAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory1, IsCurrent)
        BOOL ( STDMETHODCALLTYPE *IsCurrent )( 
            IDXGIFactory7 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, IsWindowedStereoEnabled)
        BOOL ( STDMETHODCALLTYPE *IsWindowedStereoEnabled )( 
            IDXGIFactory7 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForHwnd)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForHwnd )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  HWND hWnd,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForCoreWindow)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForCoreWindow )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  IUnknown *pWindow,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, GetSharedResourceAdapterLuid)
        HRESULT ( STDMETHODCALLTYPE *GetSharedResourceAdapterLuid )( 
            IDXGIFactory7 * This,
            /* [annotation] */ 
            _In_  HANDLE hResource,
            /* [annotation] */ 
            _Out_  LUID *pLuid);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterStereoStatusWindow)
        HRESULT ( STDMETHODCALLTYPE *RegisterStereoStatusWindow )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  HWND WindowHandle,
            /* [annotation][in] */ 
            _In_  UINT wMsg,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterStereoStatusEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterStereoStatusEvent )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, UnregisterStereoStatus)
        void ( STDMETHODCALLTYPE *UnregisterStereoStatus )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterOcclusionStatusWindow)
        HRESULT ( STDMETHODCALLTYPE *RegisterOcclusionStatusWindow )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  HWND WindowHandle,
            /* [annotation][in] */ 
            _In_  UINT wMsg,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, RegisterOcclusionStatusEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterOcclusionStatusEvent )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, UnregisterOcclusionStatus)
        void ( STDMETHODCALLTYPE *UnregisterOcclusionStatus )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory2, CreateSwapChainForComposition)
        HRESULT ( STDMETHODCALLTYPE *CreateSwapChainForComposition )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  IUnknown *pDevice,
            /* [annotation][in] */ 
            _In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
            /* [annotation][in] */ 
            _In_opt_  IDXGIOutput *pRestrictToOutput,
            /* [annotation][out] */ 
            _COM_Outptr_  IDXGISwapChain1 **ppSwapChain);
        
        DECLSPEC_XFGVIRT(IDXGIFactory3, GetCreationFlags)
        UINT ( STDMETHODCALLTYPE *GetCreationFlags )( 
            IDXGIFactory7 * This);
        
        DECLSPEC_XFGVIRT(IDXGIFactory4, EnumAdapterByLuid)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapterByLuid )( 
            IDXGIFactory7 * This,
            /* [annotation] */ 
            _In_  LUID AdapterLuid,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory4, EnumWarpAdapter)
        HRESULT ( STDMETHODCALLTYPE *EnumWarpAdapter )( 
            IDXGIFactory7 * This,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory5, CheckFeatureSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckFeatureSupport )( 
            IDXGIFactory7 * This,
            DXGI_FEATURE Feature,
            /* [annotation] */ 
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT FeatureSupportDataSize);
        
        DECLSPEC_XFGVIRT(IDXGIFactory6, EnumAdapterByGpuPreference)
        HRESULT ( STDMETHODCALLTYPE *EnumAdapterByGpuPreference )( 
            IDXGIFactory7 * This,
            /* [annotation] */ 
            _In_  UINT Adapter,
            /* [annotation] */ 
            _In_  DXGI_GPU_PREFERENCE GpuPreference,
            /* [annotation] */ 
            _In_  REFIID riid,
            /* [annotation] */ 
            _COM_Outptr_  void **ppvAdapter);
        
        DECLSPEC_XFGVIRT(IDXGIFactory7, RegisterAdaptersChangedEvent)
        HRESULT ( STDMETHODCALLTYPE *RegisterAdaptersChangedEvent )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  HANDLE hEvent,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwCookie);
        
        DECLSPEC_XFGVIRT(IDXGIFactory7, UnregisterAdaptersChangedEvent)
        HRESULT ( STDMETHODCALLTYPE *UnregisterAdaptersChangedEvent )( 
            IDXGIFactory7 * This,
            /* [annotation][in] */ 
            _In_  DWORD dwCookie);
        
        END_INTERFACE
    } IDXGIFactory7Vtbl;

    interface IDXGIFactory7
    {
        CONST_VTBL struct IDXGIFactory7Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIFactory7_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIFactory7_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIFactory7_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIFactory7_SetPrivateData(This,Name,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,Name,DataSize,pData) ) 

#define IDXGIFactory7_SetPrivateDataInterface(This,Name,pUnknown)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,Name,pUnknown) ) 

#define IDXGIFactory7_GetPrivateData(This,Name,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,Name,pDataSize,pData) ) 

#define IDXGIFactory7_GetParent(This,riid,ppParent)	\
    ( (This)->lpVtbl -> GetParent(This,riid,ppParent) ) 


#define IDXGIFactory7_EnumAdapters(This,Adapter,ppAdapter)	\
    ( (This)->lpVtbl -> EnumAdapters(This,Adapter,ppAdapter) ) 

#define IDXGIFactory7_MakeWindowAssociation(This,WindowHandle,Flags)	\
    ( (This)->lpVtbl -> MakeWindowAssociation(This,WindowHandle,Flags) ) 

#define IDXGIFactory7_GetWindowAssociation(This,pWindowHandle)	\
    ( (This)->lpVtbl -> GetWindowAssociation(This,pWindowHandle) ) 

#define IDXGIFactory7_CreateSwapChain(This,pDevice,pDesc,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChain(This,pDevice,pDesc,ppSwapChain) ) 

#define IDXGIFactory7_CreateSoftwareAdapter(This,Module,ppAdapter)	\
    ( (This)->lpVtbl -> CreateSoftwareAdapter(This,Module,ppAdapter) ) 


#define IDXGIFactory7_EnumAdapters1(This,Adapter,ppAdapter)	\
    ( (This)->lpVtbl -> EnumAdapters1(This,Adapter,ppAdapter) ) 

#define IDXGIFactory7_IsCurrent(This)	\
    ( (This)->lpVtbl -> IsCurrent(This) ) 


#define IDXGIFactory7_IsWindowedStereoEnabled(This)	\
    ( (This)->lpVtbl -> IsWindowedStereoEnabled(This) ) 

#define IDXGIFactory7_CreateSwapChainForHwnd(This,pDevice,hWnd,pDesc,pFullscreenDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForHwnd(This,pDevice,hWnd,pDesc,pFullscreenDesc,pRestrictToOutput,ppSwapChain) ) 

#define IDXGIFactory7_CreateSwapChainForCoreWindow(This,pDevice,pWindow,pDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForCoreWindow(This,pDevice,pWindow,pDesc,pRestrictToOutput,ppSwapChain) ) 

#define IDXGIFactory7_GetSharedResourceAdapterLuid(This,hResource,pLuid)	\
    ( (This)->lpVtbl -> GetSharedResourceAdapterLuid(This,hResource,pLuid) ) 

#define IDXGIFactory7_RegisterStereoStatusWindow(This,WindowHandle,wMsg,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterStereoStatusWindow(This,WindowHandle,wMsg,pdwCookie) ) 

#define IDXGIFactory7_RegisterStereoStatusEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterStereoStatusEvent(This,hEvent,pdwCookie) ) 

#define IDXGIFactory7_UnregisterStereoStatus(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterStereoStatus(This,dwCookie) ) 

#define IDXGIFactory7_RegisterOcclusionStatusWindow(This,WindowHandle,wMsg,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterOcclusionStatusWindow(This,WindowHandle,wMsg,pdwCookie) ) 

#define IDXGIFactory7_RegisterOcclusionStatusEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterOcclusionStatusEvent(This,hEvent,pdwCookie) ) 

#define IDXGIFactory7_UnregisterOcclusionStatus(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterOcclusionStatus(This,dwCookie) ) 

#define IDXGIFactory7_CreateSwapChainForComposition(This,pDevice,pDesc,pRestrictToOutput,ppSwapChain)	\
    ( (This)->lpVtbl -> CreateSwapChainForComposition(This,pDevice,pDesc,pRestrictToOutput,ppSwapChain) ) 


#define IDXGIFactory7_GetCreationFlags(This)	\
    ( (This)->lpVtbl -> GetCreationFlags(This) ) 


#define IDXGIFactory7_EnumAdapterByLuid(This,AdapterLuid,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumAdapterByLuid(This,AdapterLuid,riid,ppvAdapter) ) 

#define IDXGIFactory7_EnumWarpAdapter(This,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumWarpAdapter(This,riid,ppvAdapter) ) 


#define IDXGIFactory7_CheckFeatureSupport(This,Feature,pFeatureSupportData,FeatureSupportDataSize)	\
    ( (This)->lpVtbl -> CheckFeatureSupport(This,Feature,pFeatureSupportData,FeatureSupportDataSize) ) 


#define IDXGIFactory7_EnumAdapterByGpuPreference(This,Adapter,GpuPreference,riid,ppvAdapter)	\
    ( (This)->lpVtbl -> EnumAdapterByGpuPreference(This,Adapter,GpuPreference,riid,ppvAdapter) ) 


#define IDXGIFactory7_RegisterAdaptersChangedEvent(This,hEvent,pdwCookie)	\
    ( (This)->lpVtbl -> RegisterAdaptersChangedEvent(This,hEvent,pdwCookie) ) 

#define IDXGIFactory7_UnregisterAdaptersChangedEvent(This,dwCookie)	\
    ( (This)->lpVtbl -> UnregisterAdaptersChangedEvent(This,dwCookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIFactory7_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dxgi1_6_0000_0004 */
/* [local] */ 

#if defined(NTDDI_VERSION) && (NTDDI_VERSION >= NTDDI_WIN10_NI)
HRESULT WINAPI DXGIDisableVBlankVirtualization();
#endif
#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP | WINAPI_PARTITION_GAMES) */
#pragma endregion
DEFINE_GUID(IID_IDXGIAdapter4,0x3c8d99d1,0x4fbf,0x4181,0xa8,0x2c,0xaf,0x66,0xbf,0x7b,0xd2,0x4e);
DEFINE_GUID(IID_IDXGIOutput6,0x068346e8,0xaaec,0x4b84,0xad,0xd7,0x13,0x7f,0x51,0x3f,0x77,0xa1);
DEFINE_GUID(IID_IDXGIFactory6,0xc1b6694f,0xff09,0x44a9,0xb0,0x3c,0x77,0x90,0x0a,0x0a,0x1d,0x17);
DEFINE_GUID(IID_IDXGIFactory7,0xa4966eed,0x76db,0x44da,0x84,0xc1,0xee,0x9a,0x7a,0xfb,0x20,0xa8);


extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgi1_6_0000_0004_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


