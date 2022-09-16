/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:   d3d9.h
 *  Content:    Direct3D include file
 *
 ****************************************************************************/

#ifndef _D3D9_H_
#define _D3D9_H_

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0900
#endif  //DIRECT3D_VERSION

// include this file content only if compiling for DX9 interfaces
#if(DIRECT3D_VERSION >= 0x0900)



/* This identifier is passed to Direct3DCreate9 in order to ensure that an
 * application was built against the correct header files. This number is
 * incremented whenever a header (or other) change would require applications
 * to be rebuilt. If the version doesn't match, Direct3DCreate9 will fail.
 * (The number itself has no meaning.)*/

#ifdef D3D_DEBUG_INFO
#define D3D_SDK_VERSION   (32 | 0x80000000)
#define D3D9b_SDK_VERSION (31 | 0x80000000)

#else
#define D3D_SDK_VERSION   32
#define D3D9b_SDK_VERSION 31
#endif


#include <stdlib.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#include <windows.h>

#if !defined(HMONITOR_DECLARED) && (WINVER < 0x0500)
    #define HMONITOR_DECLARED
    DECLARE_HANDLE(HMONITOR);
#endif

#define D3DAPI WINAPI
/*
 * Interface IID's
 */
#if defined( _WIN32 ) && !defined( _NO_COM)

/* IID_IDirect3D9 */
/* {81BDCBCA-64D4-426d-AE8D-AD0147F4275C} */
DEFINE_GUID(IID_IDirect3D9, 0x81bdcbca, 0x64d4, 0x426d, 0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c);

/* IID_IDirect3DDevice9 */
// {D0223B96-BF7A-43fd-92BD-A43B0D82B9EB} */
DEFINE_GUID(IID_IDirect3DDevice9, 0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb);

/* IID_IDirect3DResource9 */
// {05EEC05D-8F7D-4362-B999-D1BAF357C704}
DEFINE_GUID(IID_IDirect3DResource9, 0x5eec05d, 0x8f7d, 0x4362, 0xb9, 0x99, 0xd1, 0xba, 0xf3, 0x57, 0xc7, 0x4);

/* IID_IDirect3DBaseTexture9 */
/* {580CA87E-1D3C-4d54-991D-B7D3E3C298CE} */
DEFINE_GUID(IID_IDirect3DBaseTexture9, 0x580ca87e, 0x1d3c, 0x4d54, 0x99, 0x1d, 0xb7, 0xd3, 0xe3, 0xc2, 0x98, 0xce);

/* IID_IDirect3DTexture9 */
/* {85C31227-3DE5-4f00-9B3A-F11AC38C18B5} */
DEFINE_GUID(IID_IDirect3DTexture9, 0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5);

/* IID_IDirect3DCubeTexture9 */
/* {FFF32F81-D953-473a-9223-93D652ABA93F} */
DEFINE_GUID(IID_IDirect3DCubeTexture9, 0xfff32f81, 0xd953, 0x473a, 0x92, 0x23, 0x93, 0xd6, 0x52, 0xab, 0xa9, 0x3f);

/* IID_IDirect3DVolumeTexture9 */
/* {2518526C-E789-4111-A7B9-47EF328D13E6} */
DEFINE_GUID(IID_IDirect3DVolumeTexture9, 0x2518526c, 0xe789, 0x4111, 0xa7, 0xb9, 0x47, 0xef, 0x32, 0x8d, 0x13, 0xe6);

/* IID_IDirect3DVertexBuffer9 */
/* {B64BB1B5-FD70-4df6-BF91-19D0A12455E3} */
DEFINE_GUID(IID_IDirect3DVertexBuffer9, 0xb64bb1b5, 0xfd70, 0x4df6, 0xbf, 0x91, 0x19, 0xd0, 0xa1, 0x24, 0x55, 0xe3);

/* IID_IDirect3DIndexBuffer9 */
/* {7C9DD65E-D3F7-4529-ACEE-785830ACDE35} */
DEFINE_GUID(IID_IDirect3DIndexBuffer9, 0x7c9dd65e, 0xd3f7, 0x4529, 0xac, 0xee, 0x78, 0x58, 0x30, 0xac, 0xde, 0x35);

/* IID_IDirect3DSurface9 */
/* {0CFBAF3A-9FF6-429a-99B3-A2796AF8B89B} */
DEFINE_GUID(IID_IDirect3DSurface9, 0xcfbaf3a, 0x9ff6, 0x429a, 0x99, 0xb3, 0xa2, 0x79, 0x6a, 0xf8, 0xb8, 0x9b);

/* IID_IDirect3DVolume9 */
/* {24F416E6-1F67-4aa7-B88E-D33F6F3128A1} */
DEFINE_GUID(IID_IDirect3DVolume9, 0x24f416e6, 0x1f67, 0x4aa7, 0xb8, 0x8e, 0xd3, 0x3f, 0x6f, 0x31, 0x28, 0xa1);

/* IID_IDirect3DSwapChain9 */
/* {794950F2-ADFC-458a-905E-10A10B0B503B} */
DEFINE_GUID(IID_IDirect3DSwapChain9, 0x794950f2, 0xadfc, 0x458a, 0x90, 0x5e, 0x10, 0xa1, 0xb, 0xb, 0x50, 0x3b);

/* IID_IDirect3DVertexDeclaration9 */
/* {DD13C59C-36FA-4098-A8FB-C7ED39DC8546} */
DEFINE_GUID(IID_IDirect3DVertexDeclaration9, 0xdd13c59c, 0x36fa, 0x4098, 0xa8, 0xfb, 0xc7, 0xed, 0x39, 0xdc, 0x85, 0x46);

/* IID_IDirect3DVertexShader9 */
/* {EFC5557E-6265-4613-8A94-43857889EB36} */
DEFINE_GUID(IID_IDirect3DVertexShader9, 0xefc5557e, 0x6265, 0x4613, 0x8a, 0x94, 0x43, 0x85, 0x78, 0x89, 0xeb, 0x36);

/* IID_IDirect3DPixelShader9 */
/* {6D3BDBDC-5B02-4415-B852-CE5E8BCCB289} */
DEFINE_GUID(IID_IDirect3DPixelShader9, 0x6d3bdbdc, 0x5b02, 0x4415, 0xb8, 0x52, 0xce, 0x5e, 0x8b, 0xcc, 0xb2, 0x89);

/* IID_IDirect3DStateBlock9 */
/* {B07C4FE5-310D-4ba8-A23C-4F0F206F218B} */
DEFINE_GUID(IID_IDirect3DStateBlock9, 0xb07c4fe5, 0x310d, 0x4ba8, 0xa2, 0x3c, 0x4f, 0xf, 0x20, 0x6f, 0x21, 0x8b);

/* IID_IDirect3DQuery9 */
/* {d9771460-a695-4f26-bbd3-27b840b541cc} */
DEFINE_GUID(IID_IDirect3DQuery9, 0xd9771460, 0xa695, 0x4f26, 0xbb, 0xd3, 0x27, 0xb8, 0x40, 0xb5, 0x41, 0xcc);


/* IID_HelperName */
/* {E4A36723-FDFE-4b22-B146-3C04C07F4CC8} */
DEFINE_GUID(IID_HelperName, 0xe4a36723, 0xfdfe, 0x4b22, 0xb1, 0x46, 0x3c, 0x4, 0xc0, 0x7f, 0x4c, 0xc8);

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

/* IID_IDirect3D9Ex */
/* {02177241-69FC-400C-8FF1-93A44DF6861D} */
DEFINE_GUID(IID_IDirect3D9Ex, 0x02177241, 0x69FC, 0x400C, 0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D);

/* IID_IDirect3DDevice9Ex */
// {B18B10CE-2649-405a-870F-95F777D4313A}
DEFINE_GUID(IID_IDirect3DDevice9Ex, 0xb18b10ce, 0x2649, 0x405a, 0x87, 0xf, 0x95, 0xf7, 0x77, 0xd4, 0x31, 0x3a);

/* IID_IDirect3DSwapChain9Ex */
/* {91886CAF-1C3D-4d2e-A0AB-3E4C7D8D3303} */
DEFINE_GUID(IID_IDirect3DSwapChain9Ex, 0x91886caf, 0x1c3d, 0x4d2e, 0xa0, 0xab, 0x3e, 0x4c, 0x7d, 0x8d, 0x33, 0x3);

/* IID_IDirect3D9ExOverlayExtension */
/* {187aeb13-aaf5-4c59-876d-e059088c0df8} */
DEFINE_GUID(IID_IDirect3D9ExOverlayExtension, 0x187aeb13, 0xaaf5, 0x4c59, 0x87, 0x6d, 0xe0, 0x59, 0x8, 0x8c, 0xd, 0xf8);

/* IID_IDirect3DDevice9Video */
// {26DC4561-A1EE-4ae7-96DA-118A36C0EC95}
DEFINE_GUID(IID_IDirect3DDevice9Video, 0x26dc4561, 0xa1ee, 0x4ae7, 0x96, 0xda, 0x11, 0x8a, 0x36, 0xc0, 0xec, 0x95);

/* IID_IDirect3D9AuthenticatedChannel */
// {FF24BEEE-DA21-4beb-98B5-D2F899F98AF9}
DEFINE_GUID(IID_IDirect3DAuthenticatedChannel9, 0xff24beee, 0xda21, 0x4beb, 0x98, 0xb5, 0xd2, 0xf8, 0x99, 0xf9, 0x8a, 0xf9);

/* IID_IDirect3DCryptoSession9 */
// {FA0AB799-7A9C-48ca-8C5B-237E71A54434}
DEFINE_GUID(IID_IDirect3DCryptoSession9, 0xfa0ab799, 0x7a9c, 0x48ca, 0x8c, 0x5b, 0x23, 0x7e, 0x71, 0xa5, 0x44, 0x34);


#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */

#endif

#ifdef __cplusplus

#ifndef DECLSPEC_UUID
#if _MSC_VER >= 1100
#define DECLSPEC_UUID(x)    __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif
#endif

interface DECLSPEC_UUID("81BDCBCA-64D4-426d-AE8D-AD0147F4275C") IDirect3D9;
interface DECLSPEC_UUID("D0223B96-BF7A-43fd-92BD-A43B0D82B9EB") IDirect3DDevice9;

interface DECLSPEC_UUID("B07C4FE5-310D-4ba8-A23C-4F0F206F218B") IDirect3DStateBlock9;
interface DECLSPEC_UUID("05EEC05D-8F7D-4362-B999-D1BAF357C704") IDirect3DResource9;
interface DECLSPEC_UUID("DD13C59C-36FA-4098-A8FB-C7ED39DC8546") IDirect3DVertexDeclaration9;
interface DECLSPEC_UUID("EFC5557E-6265-4613-8A94-43857889EB36") IDirect3DVertexShader9;
interface DECLSPEC_UUID("6D3BDBDC-5B02-4415-B852-CE5E8BCCB289") IDirect3DPixelShader9;
interface DECLSPEC_UUID("580CA87E-1D3C-4d54-991D-B7D3E3C298CE") IDirect3DBaseTexture9;
interface DECLSPEC_UUID("85C31227-3DE5-4f00-9B3A-F11AC38C18B5") IDirect3DTexture9;
interface DECLSPEC_UUID("2518526C-E789-4111-A7B9-47EF328D13E6") IDirect3DVolumeTexture9;
interface DECLSPEC_UUID("FFF32F81-D953-473a-9223-93D652ABA93F") IDirect3DCubeTexture9;

interface DECLSPEC_UUID("B64BB1B5-FD70-4df6-BF91-19D0A12455E3") IDirect3DVertexBuffer9;
interface DECLSPEC_UUID("7C9DD65E-D3F7-4529-ACEE-785830ACDE35") IDirect3DIndexBuffer9;

interface DECLSPEC_UUID("0CFBAF3A-9FF6-429a-99B3-A2796AF8B89B") IDirect3DSurface9;
interface DECLSPEC_UUID("24F416E6-1F67-4aa7-B88E-D33F6F3128A1") IDirect3DVolume9;

interface DECLSPEC_UUID("794950F2-ADFC-458a-905E-10A10B0B503B") IDirect3DSwapChain9;
interface DECLSPEC_UUID("d9771460-a695-4f26-bbd3-27b840b541cc") IDirect3DQuery9;


/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

interface DECLSPEC_UUID("02177241-69FC-400C-8FF1-93A44DF6861D") IDirect3D9Ex;
interface DECLSPEC_UUID("B18B10CE-2649-405a-870F-95F777D4313A") IDirect3DDevice9Ex;
interface DECLSPEC_UUID("91886CAF-1C3D-4d2e-A0AB-3E4C7D8D3303") IDirect3DSwapChain9Ex;
interface DECLSPEC_UUID("187AEB13-AAF5-4C59-876D-E059088C0DF8") IDirect3D9ExOverlayExtension;
interface DECLSPEC_UUID("26DC4561-A1EE-4ae7-96DA-118A36C0EC95") IDirect3DDevice9Video;
interface DECLSPEC_UUID("FF24BEEE-DA21-4beb-98B5-D2F899F98AF9") IDirect3DAuthenticatedChannel9;
interface DECLSPEC_UUID("FA0AB799-7A9C-48CA-8C5B-237E71A54434") IDirect3DCryptoSession9;

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */

#if defined(_COM_SMARTPTR_TYPEDEF)
_COM_SMARTPTR_TYPEDEF(IDirect3D9, __uuidof(IDirect3D9));
_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9, __uuidof(IDirect3DDevice9));

_COM_SMARTPTR_TYPEDEF(IDirect3DStateBlock9, __uuidof(IDirect3DStateBlock9));
_COM_SMARTPTR_TYPEDEF(IDirect3DResource9, __uuidof(IDirect3DResource9));
_COM_SMARTPTR_TYPEDEF(IDirect3DVertexDeclaration9, __uuidof(IDirect3DVertexDeclaration9));
_COM_SMARTPTR_TYPEDEF(IDirect3DVertexShader9, __uuidof(IDirect3DVertexShader9));
_COM_SMARTPTR_TYPEDEF(IDirect3DPixelShader9, __uuidof(IDirect3DPixelShader9));
_COM_SMARTPTR_TYPEDEF(IDirect3DBaseTexture9, __uuidof(IDirect3DBaseTexture9));
_COM_SMARTPTR_TYPEDEF(IDirect3DTexture9, __uuidof(IDirect3DTexture9));
_COM_SMARTPTR_TYPEDEF(IDirect3DVolumeTexture9, __uuidof(IDirect3DVolumeTexture9));
_COM_SMARTPTR_TYPEDEF(IDirect3DCubeTexture9, __uuidof(IDirect3DCubeTexture9));

_COM_SMARTPTR_TYPEDEF(IDirect3DVertexBuffer9, __uuidof(IDirect3DVertexBuffer9));
_COM_SMARTPTR_TYPEDEF(IDirect3DIndexBuffer9, __uuidof(IDirect3DIndexBuffer9));

_COM_SMARTPTR_TYPEDEF(IDirect3DSurface9, __uuidof(IDirect3DSurface9));
_COM_SMARTPTR_TYPEDEF(IDirect3DVolume9, __uuidof(IDirect3DVolume9));

_COM_SMARTPTR_TYPEDEF(IDirect3DSwapChain9, __uuidof(IDirect3DSwapChain9));
_COM_SMARTPTR_TYPEDEF(IDirect3DQuery9, __uuidof(IDirect3DQuery9));


/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

_COM_SMARTPTR_TYPEDEF(IDirect3D9Ex, __uuidof(IDirect3D9Ex));
_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9Ex, __uuidof(IDirect3DDevice9Ex));
_COM_SMARTPTR_TYPEDEF(IDirect3DSwapChain9Ex, __uuidof(IDirect3DSwapChain9Ex));
_COM_SMARTPTR_TYPEDEF(IDirect3D9ExOverlayExtension, __uuidof(IDirect3D9ExOverlayExtension));
_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9Video, __uuidof(IDirect3DDevice9Video));
_COM_SMARTPTR_TYPEDEF(IDirect3DAuthenticatedChannel9, __uuidof(IDirect3DAuthenticatedChannel9));
_COM_SMARTPTR_TYPEDEF(IDirect3DCryptoSession9, __uuidof(IDirect3DCryptoSession9));

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */

#endif

#endif


typedef interface IDirect3D9                    IDirect3D9;
typedef interface IDirect3DDevice9              IDirect3DDevice9;
typedef interface IDirect3DStateBlock9          IDirect3DStateBlock9;
typedef interface IDirect3DVertexDeclaration9   IDirect3DVertexDeclaration9;
typedef interface IDirect3DVertexShader9        IDirect3DVertexShader9;
typedef interface IDirect3DPixelShader9         IDirect3DPixelShader9;
typedef interface IDirect3DResource9            IDirect3DResource9;
typedef interface IDirect3DBaseTexture9         IDirect3DBaseTexture9;
typedef interface IDirect3DTexture9             IDirect3DTexture9;
typedef interface IDirect3DVolumeTexture9       IDirect3DVolumeTexture9;
typedef interface IDirect3DCubeTexture9         IDirect3DCubeTexture9;
typedef interface IDirect3DVertexBuffer9        IDirect3DVertexBuffer9;
typedef interface IDirect3DIndexBuffer9         IDirect3DIndexBuffer9;
typedef interface IDirect3DSurface9             IDirect3DSurface9;
typedef interface IDirect3DVolume9              IDirect3DVolume9;
typedef interface IDirect3DSwapChain9           IDirect3DSwapChain9;
typedef interface IDirect3DQuery9               IDirect3DQuery9;


/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)


typedef interface IDirect3D9Ex                   IDirect3D9Ex;
typedef interface IDirect3DDevice9Ex             IDirect3DDevice9Ex;
typedef interface IDirect3DSwapChain9Ex          IDirect3DSwapChain9Ex;
typedef interface IDirect3D9ExOverlayExtension   IDirect3D9ExOverlayExtension;
typedef interface IDirect3DDevice9Video          IDirect3DDevice9Video;
typedef interface IDirect3DAuthenticatedChannel9 IDirect3DAuthenticatedChannel9;
typedef interface IDirect3DCryptoSession9        IDirect3DCryptoSession9;

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */

#include "d3d9types.h"
#include "d3d9caps.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
 * DLL Function for creating a Direct3D9 object. This object supports
 * enumeration and allows the creation of Direct3DDevice9 objects.
 * Pass the value of the constant D3D_SDK_VERSION to this function, so
 * that the run-time can validate that your application was compiled
 * against the right headers.
 */

IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion);

/*
 * Stubs for graphics profiling.
 */
 
int WINAPI D3DPERF_BeginEvent( D3DCOLOR col, LPCWSTR wszName );
int WINAPI D3DPERF_EndEvent( void );
void WINAPI D3DPERF_SetMarker( D3DCOLOR col, LPCWSTR wszName );
void WINAPI D3DPERF_SetRegion( D3DCOLOR col, LPCWSTR wszName );
BOOL WINAPI D3DPERF_QueryRepeatFrame( void );

void WINAPI D3DPERF_SetOptions( DWORD dwOptions );
DWORD WINAPI D3DPERF_GetStatus( void );

/*
 * Direct3D interfaces
 */






#undef INTERFACE
#define INTERFACE IDirect3D9

DECLARE_INTERFACE_(IDirect3D9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3D9 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) PURE;
    STDMETHOD_(UINT, GetAdapterCount)(THIS) PURE;
    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) PURE;
    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter,D3DFORMAT Format) PURE;
    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) PURE;
    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) PURE;
    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) PURE;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) PURE;
    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Version;
    #endif
};
    
typedef struct IDirect3D9 *LPDIRECT3D9, *PDIRECT3D9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3D9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3D9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3D9_RegisterSoftwareDevice(p,a) (p)->lpVtbl->RegisterSoftwareDevice(p,a)
#define IDirect3D9_GetAdapterCount(p) (p)->lpVtbl->GetAdapterCount(p)
#define IDirect3D9_GetAdapterIdentifier(p,a,b,c) (p)->lpVtbl->GetAdapterIdentifier(p,a,b,c)
#define IDirect3D9_GetAdapterModeCount(p,a,b) (p)->lpVtbl->GetAdapterModeCount(p,a,b)
#define IDirect3D9_EnumAdapterModes(p,a,b,c,d) (p)->lpVtbl->EnumAdapterModes(p,a,b,c,d)
#define IDirect3D9_GetAdapterDisplayMode(p,a,b) (p)->lpVtbl->GetAdapterDisplayMode(p,a,b)
#define IDirect3D9_CheckDeviceType(p,a,b,c,d,e) (p)->lpVtbl->CheckDeviceType(p,a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->lpVtbl->CheckDeviceFormat(p,a,b,c,d,e,f)
#define IDirect3D9_CheckDeviceMultiSampleType(p,a,b,c,d,e,f) (p)->lpVtbl->CheckDeviceMultiSampleType(p,a,b,c,d,e,f)
#define IDirect3D9_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->lpVtbl->CheckDepthStencilMatch(p,a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormatConversion(p,a,b,c,d) (p)->lpVtbl->CheckDeviceFormatConversion(p,a,b,c,d)
#define IDirect3D9_GetDeviceCaps(p,a,b,c) (p)->lpVtbl->GetDeviceCaps(p,a,b,c)
#define IDirect3D9_GetAdapterMonitor(p,a) (p)->lpVtbl->GetAdapterMonitor(p,a)
#define IDirect3D9_CreateDevice(p,a,b,c,d,e,f) (p)->lpVtbl->CreateDevice(p,a,b,c,d,e,f)
#else
#define IDirect3D9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D9_AddRef(p) (p)->AddRef()
#define IDirect3D9_Release(p) (p)->Release()
#define IDirect3D9_RegisterSoftwareDevice(p,a) (p)->RegisterSoftwareDevice(a)
#define IDirect3D9_GetAdapterCount(p) (p)->GetAdapterCount()
#define IDirect3D9_GetAdapterIdentifier(p,a,b,c) (p)->GetAdapterIdentifier(a,b,c)
#define IDirect3D9_GetAdapterModeCount(p,a,b) (p)->GetAdapterModeCount(a,b)
#define IDirect3D9_EnumAdapterModes(p,a,b,c,d) (p)->EnumAdapterModes(a,b,c,d)
#define IDirect3D9_GetAdapterDisplayMode(p,a,b) (p)->GetAdapterDisplayMode(a,b)
#define IDirect3D9_CheckDeviceType(p,a,b,c,d,e) (p)->CheckDeviceType(a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->CheckDeviceFormat(a,b,c,d,e,f)
#define IDirect3D9_CheckDeviceMultiSampleType(p,a,b,c,d,e,f) (p)->CheckDeviceMultiSampleType(a,b,c,d,e,f)
#define IDirect3D9_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->CheckDepthStencilMatch(a,b,c,d,e)
#define IDirect3D9_CheckDeviceFormatConversion(p,a,b,c,d) (p)->CheckDeviceFormatConversion(a,b,c,d)
#define IDirect3D9_GetDeviceCaps(p,a,b,c) (p)->GetDeviceCaps(a,b,c)
#define IDirect3D9_GetAdapterMonitor(p,a) (p)->GetAdapterMonitor(a)
#define IDirect3D9_CreateDevice(p,a,b,c,d,e,f) (p)->CreateDevice(a,b,c,d,e,f)
#endif







/* SwapChain */















#undef INTERFACE
#define INTERFACE IDirect3DDevice9

DECLARE_INTERFACE_(IDirect3DDevice9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DDevice9 methods ***/
    STDMETHOD(TestCooperativeLevel)(THIS) PURE;
    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) PURE;
    STDMETHOD(EvictManagedResources)(THIS) PURE;
    STDMETHOD(GetDirect3D)(THIS_ IDirect3D9** ppD3D9) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS9* pCaps) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) PURE;
    STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags) PURE;
    STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow) PURE;
    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain) PURE;
    STDMETHOD(GetSwapChain)(THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain) PURE;
    STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) PURE;
    STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD(SetDialogBoxMode)(THIS_ BOOL bEnableDialogs) PURE;
    STDMETHOD_(void, SetGammaRamp)(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD_(void, GetGammaRamp)(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(UpdateSurface)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) PURE;
    STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) PURE;
    STDMETHOD(GetRenderTargetData)(THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(GetFrontBufferData)(THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(StretchRect)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) PURE;
    STDMETHOD(ColorFill)(THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) PURE;
    STDMETHOD(CreateOffscreenPlainSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(SetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) PURE;
    STDMETHOD(SetDepthStencilSurface)(THIS_ IDirect3DSurface9* pNewZStencil) PURE;
    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface9** ppZStencilSurface) PURE;
    STDMETHOD(BeginScene)(THIS) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
    STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
    STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT9*) PURE;
    STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT9*) PURE;
    STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable) PURE;
    STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) PURE;
    STDMETHOD(BeginStateBlock)(THIS) PURE;
    STDMETHOD(EndStateBlock)(THIS_ IDirect3DStateBlock9** ppSB) PURE;
    STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture) PURE;
    STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(GetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses) PURE;
    STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber) PURE;
    STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber) PURE;
    STDMETHOD(SetScissorRect)(THIS_ CONST RECT* pRect) PURE;
    STDMETHOD(GetScissorRect)(THIS_ RECT* pRect) PURE;
    STDMETHOD(SetSoftwareVertexProcessing)(THIS_ BOOL bSoftware) PURE;
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) PURE;
    STDMETHOD(SetNPatchMode)(THIS_ float nSegments) PURE;
    STDMETHOD_(float, GetNPatchMode)(THIS) PURE;
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) PURE;
    STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) PURE;
    STDMETHOD(SetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9* pDecl) PURE;
    STDMETHOD(GetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9** ppDecl) PURE;
    STDMETHOD(SetFVF)(THIS_ DWORD FVF) PURE;
    STDMETHOD(GetFVF)(THIS_ DWORD* pFVF) PURE;
    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ IDirect3DVertexShader9* pShader) PURE;
    STDMETHOD(GetVertexShader)(THIS_ IDirect3DVertexShader9** ppShader) PURE;
    STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(GetVertexShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(GetVertexShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) PURE;
    STDMETHOD(GetVertexShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) PURE;
    STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) PURE;
    STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride) PURE;
    STDMETHOD(SetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT Setting) PURE;
    STDMETHOD(GetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT* pSetting) PURE;
    STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer9* pIndexData) PURE;
    STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer9** ppIndexData) PURE;
    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) PURE;
    STDMETHOD(SetPixelShader)(THIS_ IDirect3DPixelShader9* pShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ IDirect3DPixelShader9** ppShader) PURE;
    STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(GetPixelShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(GetPixelShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) PURE;
    STDMETHOD(GetPixelShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) PURE;
    STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD(DeletePatch)(THIS_ UINT Handle) PURE;
    STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) PURE;
    
    #ifdef D3D_DEBUG_INFO
    D3DDEVICE_CREATION_PARAMETERS CreationParameters;
    D3DPRESENT_PARAMETERS PresentParameters;
    D3DDISPLAYMODE DisplayMode;
    D3DCAPS9 Caps;
    
    UINT AvailableTextureMem;
    UINT SwapChains;
    UINT Textures;
    UINT VertexBuffers;
    UINT IndexBuffers;
    UINT VertexShaders;
    UINT PixelShaders;
    
    D3DVIEWPORT9 Viewport;
    D3DMATRIX ProjectionMatrix;
    D3DMATRIX ViewMatrix;
    D3DMATRIX WorldMatrix;
    D3DMATRIX TextureMatrices[8];
    
    DWORD FVF;
    UINT VertexSize;
    DWORD VertexShaderVersion;
    DWORD PixelShaderVersion;
    BOOL SoftwareVertexProcessing;
    
    D3DMATERIAL9 Material;
    D3DLIGHT9 Lights[16];
    BOOL LightsEnabled[16];
    
    D3DGAMMARAMP GammaRamp;
    RECT ScissorRect;
    BOOL DialogBoxMode;
    #endif
};
    
typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9, *PDIRECT3DDEVICE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DDevice9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DDevice9_TestCooperativeLevel(p) (p)->lpVtbl->TestCooperativeLevel(p)
#define IDirect3DDevice9_GetAvailableTextureMem(p) (p)->lpVtbl->GetAvailableTextureMem(p)
#define IDirect3DDevice9_EvictManagedResources(p) (p)->lpVtbl->EvictManagedResources(p)
#define IDirect3DDevice9_GetDirect3D(p,a) (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice9_GetDeviceCaps(p,a) (p)->lpVtbl->GetDeviceCaps(p,a)
#define IDirect3DDevice9_GetDisplayMode(p,a,b) (p)->lpVtbl->GetDisplayMode(p,a,b)
#define IDirect3DDevice9_GetCreationParameters(p,a) (p)->lpVtbl->GetCreationParameters(p,a)
#define IDirect3DDevice9_SetCursorProperties(p,a,b,c) (p)->lpVtbl->SetCursorProperties(p,a,b,c)
#define IDirect3DDevice9_SetCursorPosition(p,a,b,c) (p)->lpVtbl->SetCursorPosition(p,a,b,c)
#define IDirect3DDevice9_ShowCursor(p,a) (p)->lpVtbl->ShowCursor(p,a)
#define IDirect3DDevice9_CreateAdditionalSwapChain(p,a,b) (p)->lpVtbl->CreateAdditionalSwapChain(p,a,b)
#define IDirect3DDevice9_GetSwapChain(p,a,b) (p)->lpVtbl->GetSwapChain(p,a,b)
#define IDirect3DDevice9_GetNumberOfSwapChains(p) (p)->lpVtbl->GetNumberOfSwapChains(p)
#define IDirect3DDevice9_Reset(p,a) (p)->lpVtbl->Reset(p,a)
#define IDirect3DDevice9_Present(p,a,b,c,d) (p)->lpVtbl->Present(p,a,b,c,d)
#define IDirect3DDevice9_GetBackBuffer(p,a,b,c,d) (p)->lpVtbl->GetBackBuffer(p,a,b,c,d)
#define IDirect3DDevice9_GetRasterStatus(p,a,b) (p)->lpVtbl->GetRasterStatus(p,a,b)
#define IDirect3DDevice9_SetDialogBoxMode(p,a) (p)->lpVtbl->SetDialogBoxMode(p,a)
#define IDirect3DDevice9_SetGammaRamp(p,a,b,c) (p)->lpVtbl->SetGammaRamp(p,a,b,c)
#define IDirect3DDevice9_GetGammaRamp(p,a,b) (p)->lpVtbl->GetGammaRamp(p,a,b)
#define IDirect3DDevice9_CreateTexture(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateTexture(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i) (p)->lpVtbl->CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9_CreateCubeTexture(p,a,b,c,d,e,f,g) (p)->lpVtbl->CreateCubeTexture(p,a,b,c,d,e,f,g)
#define IDirect3DDevice9_CreateVertexBuffer(p,a,b,c,d,e,f) (p)->lpVtbl->CreateVertexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateIndexBuffer(p,a,b,c,d,e,f) (p)->lpVtbl->CreateIndexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateRenderTarget(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateRenderTarget(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_UpdateSurface(p,a,b,c,d) (p)->lpVtbl->UpdateSurface(p,a,b,c,d)
#define IDirect3DDevice9_UpdateTexture(p,a,b) (p)->lpVtbl->UpdateTexture(p,a,b)
#define IDirect3DDevice9_GetRenderTargetData(p,a,b) (p)->lpVtbl->GetRenderTargetData(p,a,b)
#define IDirect3DDevice9_GetFrontBufferData(p,a,b) (p)->lpVtbl->GetFrontBufferData(p,a,b)
#define IDirect3DDevice9_StretchRect(p,a,b,c,d,e) (p)->lpVtbl->StretchRect(p,a,b,c,d,e)
#define IDirect3DDevice9_ColorFill(p,a,b,c) (p)->lpVtbl->ColorFill(p,a,b,c)
#define IDirect3DDevice9_CreateOffscreenPlainSurface(p,a,b,c,d,e,f) (p)->lpVtbl->CreateOffscreenPlainSurface(p,a,b,c,d,e,f)
#define IDirect3DDevice9_SetRenderTarget(p,a,b) (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice9_GetRenderTarget(p,a,b) (p)->lpVtbl->GetRenderTarget(p,a,b)
#define IDirect3DDevice9_SetDepthStencilSurface(p,a) (p)->lpVtbl->SetDepthStencilSurface(p,a)
#define IDirect3DDevice9_GetDepthStencilSurface(p,a) (p)->lpVtbl->GetDepthStencilSurface(p,a)
#define IDirect3DDevice9_BeginScene(p) (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice9_EndScene(p) (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice9_Clear(p,a,b,c,d,e,f) (p)->lpVtbl->Clear(p,a,b,c,d,e,f)
#define IDirect3DDevice9_SetTransform(p,a,b) (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice9_GetTransform(p,a,b) (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice9_MultiplyTransform(p,a,b) (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice9_SetViewport(p,a) (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DDevice9_GetViewport(p,a) (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DDevice9_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DDevice9_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DDevice9_SetLight(p,a,b) (p)->lpVtbl->SetLight(p,a,b)
#define IDirect3DDevice9_GetLight(p,a,b) (p)->lpVtbl->GetLight(p,a,b)
#define IDirect3DDevice9_LightEnable(p,a,b) (p)->lpVtbl->LightEnable(p,a,b)
#define IDirect3DDevice9_GetLightEnable(p,a,b) (p)->lpVtbl->GetLightEnable(p,a,b)
#define IDirect3DDevice9_SetClipPlane(p,a,b) (p)->lpVtbl->SetClipPlane(p,a,b)
#define IDirect3DDevice9_GetClipPlane(p,a,b) (p)->lpVtbl->GetClipPlane(p,a,b)
#define IDirect3DDevice9_SetRenderState(p,a,b) (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice9_GetRenderState(p,a,b) (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice9_CreateStateBlock(p,a,b) (p)->lpVtbl->CreateStateBlock(p,a,b)
#define IDirect3DDevice9_BeginStateBlock(p) (p)->lpVtbl->BeginStateBlock(p)
#define IDirect3DDevice9_EndStateBlock(p,a) (p)->lpVtbl->EndStateBlock(p,a)
#define IDirect3DDevice9_SetClipStatus(p,a) (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice9_GetClipStatus(p,a) (p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice9_GetTexture(p,a,b) (p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice9_SetTexture(p,a,b) (p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice9_GetTextureStageState(p,a,b,c) (p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice9_SetTextureStageState(p,a,b,c) (p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice9_GetSamplerState(p,a,b,c) (p)->lpVtbl->GetSamplerState(p,a,b,c)
#define IDirect3DDevice9_SetSamplerState(p,a,b,c) (p)->lpVtbl->SetSamplerState(p,a,b,c)
#define IDirect3DDevice9_ValidateDevice(p,a) (p)->lpVtbl->ValidateDevice(p,a)
#define IDirect3DDevice9_SetPaletteEntries(p,a,b) (p)->lpVtbl->SetPaletteEntries(p,a,b)
#define IDirect3DDevice9_GetPaletteEntries(p,a,b) (p)->lpVtbl->GetPaletteEntries(p,a,b)
#define IDirect3DDevice9_SetCurrentTexturePalette(p,a) (p)->lpVtbl->SetCurrentTexturePalette(p,a)
#define IDirect3DDevice9_GetCurrentTexturePalette(p,a) (p)->lpVtbl->GetCurrentTexturePalette(p,a)
#define IDirect3DDevice9_SetScissorRect(p,a) (p)->lpVtbl->SetScissorRect(p,a)
#define IDirect3DDevice9_GetScissorRect(p,a) (p)->lpVtbl->GetScissorRect(p,a)
#define IDirect3DDevice9_SetSoftwareVertexProcessing(p,a) (p)->lpVtbl->SetSoftwareVertexProcessing(p,a)
#define IDirect3DDevice9_GetSoftwareVertexProcessing(p) (p)->lpVtbl->GetSoftwareVertexProcessing(p)
#define IDirect3DDevice9_SetNPatchMode(p,a) (p)->lpVtbl->SetNPatchMode(p,a)
#define IDirect3DDevice9_GetNPatchMode(p) (p)->lpVtbl->GetNPatchMode(p)
#define IDirect3DDevice9_DrawPrimitive(p,a,b,c) (p)->lpVtbl->DrawPrimitive(p,a,b,c)
#define IDirect3DDevice9_DrawIndexedPrimitive(p,a,b,c,d,e,f) (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f)
#define IDirect3DDevice9_DrawPrimitiveUP(p,a,b,c,d) (p)->lpVtbl->DrawPrimitiveUP(p,a,b,c,d)
#define IDirect3DDevice9_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_ProcessVertices(p,a,b,c,d,e,f) (p)->lpVtbl->ProcessVertices(p,a,b,c,d,e,f)
#define IDirect3DDevice9_CreateVertexDeclaration(p,a,b) (p)->lpVtbl->CreateVertexDeclaration(p,a,b)
#define IDirect3DDevice9_SetVertexDeclaration(p,a) (p)->lpVtbl->SetVertexDeclaration(p,a)
#define IDirect3DDevice9_GetVertexDeclaration(p,a) (p)->lpVtbl->GetVertexDeclaration(p,a)
#define IDirect3DDevice9_SetFVF(p,a) (p)->lpVtbl->SetFVF(p,a)
#define IDirect3DDevice9_GetFVF(p,a) (p)->lpVtbl->GetFVF(p,a)
#define IDirect3DDevice9_CreateVertexShader(p,a,b) (p)->lpVtbl->CreateVertexShader(p,a,b)
#define IDirect3DDevice9_SetVertexShader(p,a) (p)->lpVtbl->SetVertexShader(p,a)
#define IDirect3DDevice9_GetVertexShader(p,a) (p)->lpVtbl->GetVertexShader(p,a)
#define IDirect3DDevice9_SetVertexShaderConstantF(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantF(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantI(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantI(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantB(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantB(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_SetStreamSource(p,a,b,c,d) (p)->lpVtbl->SetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9_GetStreamSource(p,a,b,c,d) (p)->lpVtbl->GetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9_SetStreamSourceFreq(p,a,b) (p)->lpVtbl->SetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9_GetStreamSourceFreq(p,a,b) (p)->lpVtbl->GetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9_SetIndices(p,a) (p)->lpVtbl->SetIndices(p,a)
#define IDirect3DDevice9_GetIndices(p,a) (p)->lpVtbl->GetIndices(p,a)
#define IDirect3DDevice9_CreatePixelShader(p,a,b) (p)->lpVtbl->CreatePixelShader(p,a,b)
#define IDirect3DDevice9_SetPixelShader(p,a) (p)->lpVtbl->SetPixelShader(p,a)
#define IDirect3DDevice9_GetPixelShader(p,a) (p)->lpVtbl->GetPixelShader(p,a)
#define IDirect3DDevice9_SetPixelShaderConstantF(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantF(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantI(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantI(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantB(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantB(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9_DrawRectPatch(p,a,b,c) (p)->lpVtbl->DrawRectPatch(p,a,b,c)
#define IDirect3DDevice9_DrawTriPatch(p,a,b,c) (p)->lpVtbl->DrawTriPatch(p,a,b,c)
#define IDirect3DDevice9_DeletePatch(p,a) (p)->lpVtbl->DeletePatch(p,a)
#define IDirect3DDevice9_CreateQuery(p,a,b) (p)->lpVtbl->CreateQuery(p,a,b)
#else
#define IDirect3DDevice9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice9_AddRef(p) (p)->AddRef()
#define IDirect3DDevice9_Release(p) (p)->Release()
#define IDirect3DDevice9_TestCooperativeLevel(p) (p)->TestCooperativeLevel()
#define IDirect3DDevice9_GetAvailableTextureMem(p) (p)->GetAvailableTextureMem()
#define IDirect3DDevice9_EvictManagedResources(p) (p)->EvictManagedResources()
#define IDirect3DDevice9_GetDirect3D(p,a) (p)->GetDirect3D(a)
#define IDirect3DDevice9_GetDeviceCaps(p,a) (p)->GetDeviceCaps(a)
#define IDirect3DDevice9_GetDisplayMode(p,a,b) (p)->GetDisplayMode(a,b)
#define IDirect3DDevice9_GetCreationParameters(p,a) (p)->GetCreationParameters(a)
#define IDirect3DDevice9_SetCursorProperties(p,a,b,c) (p)->SetCursorProperties(a,b,c)
#define IDirect3DDevice9_SetCursorPosition(p,a,b,c) (p)->SetCursorPosition(a,b,c)
#define IDirect3DDevice9_ShowCursor(p,a) (p)->ShowCursor(a)
#define IDirect3DDevice9_CreateAdditionalSwapChain(p,a,b) (p)->CreateAdditionalSwapChain(a,b)
#define IDirect3DDevice9_GetSwapChain(p,a,b) (p)->GetSwapChain(a,b)
#define IDirect3DDevice9_GetNumberOfSwapChains(p) (p)->GetNumberOfSwapChains()
#define IDirect3DDevice9_Reset(p,a) (p)->Reset(a)
#define IDirect3DDevice9_Present(p,a,b,c,d) (p)->Present(a,b,c,d)
#define IDirect3DDevice9_GetBackBuffer(p,a,b,c,d) (p)->GetBackBuffer(a,b,c,d)
#define IDirect3DDevice9_GetRasterStatus(p,a,b) (p)->GetRasterStatus(a,b)
#define IDirect3DDevice9_SetDialogBoxMode(p,a) (p)->SetDialogBoxMode(a)
#define IDirect3DDevice9_SetGammaRamp(p,a,b,c) (p)->SetGammaRamp(a,b,c)
#define IDirect3DDevice9_GetGammaRamp(p,a,b) (p)->GetGammaRamp(a,b)
#define IDirect3DDevice9_CreateTexture(p,a,b,c,d,e,f,g,h) (p)->CreateTexture(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i) (p)->CreateVolumeTexture(a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9_CreateCubeTexture(p,a,b,c,d,e,f,g) (p)->CreateCubeTexture(a,b,c,d,e,f,g)
#define IDirect3DDevice9_CreateVertexBuffer(p,a,b,c,d,e,f) (p)->CreateVertexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateIndexBuffer(p,a,b,c,d,e,f) (p)->CreateIndexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateRenderTarget(p,a,b,c,d,e,f,g,h) (p)->CreateRenderTarget(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h) (p)->CreateDepthStencilSurface(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_UpdateSurface(p,a,b,c,d) (p)->UpdateSurface(a,b,c,d)
#define IDirect3DDevice9_UpdateTexture(p,a,b) (p)->UpdateTexture(a,b)
#define IDirect3DDevice9_GetRenderTargetData(p,a,b) (p)->GetRenderTargetData(a,b)
#define IDirect3DDevice9_GetFrontBufferData(p,a,b) (p)->GetFrontBufferData(a,b)
#define IDirect3DDevice9_StretchRect(p,a,b,c,d,e) (p)->StretchRect(a,b,c,d,e)
#define IDirect3DDevice9_ColorFill(p,a,b,c) (p)->ColorFill(a,b,c)
#define IDirect3DDevice9_CreateOffscreenPlainSurface(p,a,b,c,d,e,f) (p)->CreateOffscreenPlainSurface(a,b,c,d,e,f)
#define IDirect3DDevice9_SetRenderTarget(p,a,b) (p)->SetRenderTarget(a,b)
#define IDirect3DDevice9_GetRenderTarget(p,a,b) (p)->GetRenderTarget(a,b)
#define IDirect3DDevice9_SetDepthStencilSurface(p,a) (p)->SetDepthStencilSurface(a)
#define IDirect3DDevice9_GetDepthStencilSurface(p,a) (p)->GetDepthStencilSurface(a)
#define IDirect3DDevice9_BeginScene(p) (p)->BeginScene()
#define IDirect3DDevice9_EndScene(p) (p)->EndScene()
#define IDirect3DDevice9_Clear(p,a,b,c,d,e,f) (p)->Clear(a,b,c,d,e,f)
#define IDirect3DDevice9_SetTransform(p,a,b) (p)->SetTransform(a,b)
#define IDirect3DDevice9_GetTransform(p,a,b) (p)->GetTransform(a,b)
#define IDirect3DDevice9_MultiplyTransform(p,a,b) (p)->MultiplyTransform(a,b)
#define IDirect3DDevice9_SetViewport(p,a) (p)->SetViewport(a)
#define IDirect3DDevice9_GetViewport(p,a) (p)->GetViewport(a)
#define IDirect3DDevice9_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DDevice9_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DDevice9_SetLight(p,a,b) (p)->SetLight(a,b)
#define IDirect3DDevice9_GetLight(p,a,b) (p)->GetLight(a,b)
#define IDirect3DDevice9_LightEnable(p,a,b) (p)->LightEnable(a,b)
#define IDirect3DDevice9_GetLightEnable(p,a,b) (p)->GetLightEnable(a,b)
#define IDirect3DDevice9_SetClipPlane(p,a,b) (p)->SetClipPlane(a,b)
#define IDirect3DDevice9_GetClipPlane(p,a,b) (p)->GetClipPlane(a,b)
#define IDirect3DDevice9_SetRenderState(p,a,b) (p)->SetRenderState(a,b)
#define IDirect3DDevice9_GetRenderState(p,a,b) (p)->GetRenderState(a,b)
#define IDirect3DDevice9_CreateStateBlock(p,a,b) (p)->CreateStateBlock(a,b)
#define IDirect3DDevice9_BeginStateBlock(p) (p)->BeginStateBlock()
#define IDirect3DDevice9_EndStateBlock(p,a) (p)->EndStateBlock(a)
#define IDirect3DDevice9_SetClipStatus(p,a) (p)->SetClipStatus(a)
#define IDirect3DDevice9_GetClipStatus(p,a) (p)->GetClipStatus(a)
#define IDirect3DDevice9_GetTexture(p,a,b) (p)->GetTexture(a,b)
#define IDirect3DDevice9_SetTexture(p,a,b) (p)->SetTexture(a,b)
#define IDirect3DDevice9_GetTextureStageState(p,a,b,c) (p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice9_SetTextureStageState(p,a,b,c) (p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice9_GetSamplerState(p,a,b,c) (p)->GetSamplerState(a,b,c)
#define IDirect3DDevice9_SetSamplerState(p,a,b,c) (p)->SetSamplerState(a,b,c)
#define IDirect3DDevice9_ValidateDevice(p,a) (p)->ValidateDevice(a)
#define IDirect3DDevice9_SetPaletteEntries(p,a,b) (p)->SetPaletteEntries(a,b)
#define IDirect3DDevice9_GetPaletteEntries(p,a,b) (p)->GetPaletteEntries(a,b)
#define IDirect3DDevice9_SetCurrentTexturePalette(p,a) (p)->SetCurrentTexturePalette(a)
#define IDirect3DDevice9_GetCurrentTexturePalette(p,a) (p)->GetCurrentTexturePalette(a)
#define IDirect3DDevice9_SetScissorRect(p,a) (p)->SetScissorRect(a)
#define IDirect3DDevice9_GetScissorRect(p,a) (p)->GetScissorRect(a)
#define IDirect3DDevice9_SetSoftwareVertexProcessing(p,a) (p)->SetSoftwareVertexProcessing(a)
#define IDirect3DDevice9_GetSoftwareVertexProcessing(p) (p)->GetSoftwareVertexProcessing()
#define IDirect3DDevice9_SetNPatchMode(p,a) (p)->SetNPatchMode(a)
#define IDirect3DDevice9_GetNPatchMode(p) (p)->GetNPatchMode()
#define IDirect3DDevice9_DrawPrimitive(p,a,b,c) (p)->DrawPrimitive(a,b,c)
#define IDirect3DDevice9_DrawIndexedPrimitive(p,a,b,c,d,e,f) (p)->DrawIndexedPrimitive(a,b,c,d,e,f)
#define IDirect3DDevice9_DrawPrimitiveUP(p,a,b,c,d) (p)->DrawPrimitiveUP(a,b,c,d)
#define IDirect3DDevice9_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->DrawIndexedPrimitiveUP(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9_ProcessVertices(p,a,b,c,d,e,f) (p)->ProcessVertices(a,b,c,d,e,f)
#define IDirect3DDevice9_CreateVertexDeclaration(p,a,b) (p)->CreateVertexDeclaration(a,b)
#define IDirect3DDevice9_SetVertexDeclaration(p,a) (p)->SetVertexDeclaration(a)
#define IDirect3DDevice9_GetVertexDeclaration(p,a) (p)->GetVertexDeclaration(a)
#define IDirect3DDevice9_SetFVF(p,a) (p)->SetFVF(a)
#define IDirect3DDevice9_GetFVF(p,a) (p)->GetFVF(a)
#define IDirect3DDevice9_CreateVertexShader(p,a,b) (p)->CreateVertexShader(a,b)
#define IDirect3DDevice9_SetVertexShader(p,a) (p)->SetVertexShader(a)
#define IDirect3DDevice9_GetVertexShader(p,a) (p)->GetVertexShader(a)
#define IDirect3DDevice9_SetVertexShaderConstantF(p,a,b,c) (p)->SetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantF(p,a,b,c) (p)->GetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantI(p,a,b,c) (p)->SetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantI(p,a,b,c) (p)->GetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9_SetVertexShaderConstantB(p,a,b,c) (p)->SetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9_GetVertexShaderConstantB(p,a,b,c) (p)->GetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9_SetStreamSource(p,a,b,c,d) (p)->SetStreamSource(a,b,c,d)
#define IDirect3DDevice9_GetStreamSource(p,a,b,c,d) (p)->GetStreamSource(a,b,c,d)
#define IDirect3DDevice9_SetStreamSourceFreq(p,a,b) (p)->SetStreamSourceFreq(a,b)
#define IDirect3DDevice9_GetStreamSourceFreq(p,a,b) (p)->GetStreamSourceFreq(a,b)
#define IDirect3DDevice9_SetIndices(p,a) (p)->SetIndices(a)
#define IDirect3DDevice9_GetIndices(p,a) (p)->GetIndices(a)
#define IDirect3DDevice9_CreatePixelShader(p,a,b) (p)->CreatePixelShader(a,b)
#define IDirect3DDevice9_SetPixelShader(p,a) (p)->SetPixelShader(a)
#define IDirect3DDevice9_GetPixelShader(p,a) (p)->GetPixelShader(a)
#define IDirect3DDevice9_SetPixelShaderConstantF(p,a,b,c) (p)->SetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantF(p,a,b,c) (p)->GetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantI(p,a,b,c) (p)->SetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantI(p,a,b,c) (p)->GetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9_SetPixelShaderConstantB(p,a,b,c) (p)->SetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9_GetPixelShaderConstantB(p,a,b,c) (p)->GetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9_DrawRectPatch(p,a,b,c) (p)->DrawRectPatch(a,b,c)
#define IDirect3DDevice9_DrawTriPatch(p,a,b,c) (p)->DrawTriPatch(a,b,c)
#define IDirect3DDevice9_DeletePatch(p,a) (p)->DeletePatch(a)
#define IDirect3DDevice9_CreateQuery(p,a,b) (p)->CreateQuery(a,b)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DStateBlock9

DECLARE_INTERFACE_(IDirect3DStateBlock9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DStateBlock9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(Capture)(THIS) PURE;
    STDMETHOD(Apply)(THIS) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DStateBlock9 *LPDIRECT3DSTATEBLOCK9, *PDIRECT3DSTATEBLOCK9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DStateBlock9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DStateBlock9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DStateBlock9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DStateBlock9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DStateBlock9_Capture(p) (p)->lpVtbl->Capture(p)
#define IDirect3DStateBlock9_Apply(p) (p)->lpVtbl->Apply(p)
#else
#define IDirect3DStateBlock9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DStateBlock9_AddRef(p) (p)->AddRef()
#define IDirect3DStateBlock9_Release(p) (p)->Release()
#define IDirect3DStateBlock9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DStateBlock9_Capture(p) (p)->Capture()
#define IDirect3DStateBlock9_Apply(p) (p)->Apply()
#endif




#undef INTERFACE
#define INTERFACE IDirect3DSwapChain9

DECLARE_INTERFACE_(IDirect3DSwapChain9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DSwapChain9 methods ***/
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) PURE;
    STDMETHOD(GetFrontBufferData)(THIS_ IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(GetPresentParameters)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    
    #ifdef D3D_DEBUG_INFO
    D3DPRESENT_PARAMETERS PresentParameters;
    D3DDISPLAYMODE DisplayMode;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DSwapChain9 *LPDIRECT3DSWAPCHAIN9, *PDIRECT3DSWAPCHAIN9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSwapChain9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSwapChain9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DSwapChain9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DSwapChain9_Present(p,a,b,c,d,e) (p)->lpVtbl->Present(p,a,b,c,d,e)
#define IDirect3DSwapChain9_GetFrontBufferData(p,a) (p)->lpVtbl->GetFrontBufferData(p,a)
#define IDirect3DSwapChain9_GetBackBuffer(p,a,b,c) (p)->lpVtbl->GetBackBuffer(p,a,b,c)
#define IDirect3DSwapChain9_GetRasterStatus(p,a) (p)->lpVtbl->GetRasterStatus(p,a)
#define IDirect3DSwapChain9_GetDisplayMode(p,a) (p)->lpVtbl->GetDisplayMode(p,a)
#define IDirect3DSwapChain9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSwapChain9_GetPresentParameters(p,a) (p)->lpVtbl->GetPresentParameters(p,a)
#else
#define IDirect3DSwapChain9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DSwapChain9_AddRef(p) (p)->AddRef()
#define IDirect3DSwapChain9_Release(p) (p)->Release()
#define IDirect3DSwapChain9_Present(p,a,b,c,d,e) (p)->Present(a,b,c,d,e)
#define IDirect3DSwapChain9_GetFrontBufferData(p,a) (p)->GetFrontBufferData(a)
#define IDirect3DSwapChain9_GetBackBuffer(p,a,b,c) (p)->GetBackBuffer(a,b,c)
#define IDirect3DSwapChain9_GetRasterStatus(p,a) (p)->GetRasterStatus(a)
#define IDirect3DSwapChain9_GetDisplayMode(p,a) (p)->GetDisplayMode(a)
#define IDirect3DSwapChain9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DSwapChain9_GetPresentParameters(p,a) (p)->GetPresentParameters(a)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DResource9

DECLARE_INTERFACE_(IDirect3DResource9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
};
    
typedef struct IDirect3DResource9 *LPDIRECT3DRESOURCE9, *PDIRECT3DRESOURCE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DResource9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DResource9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DResource9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DResource9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DResource9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DResource9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DResource9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DResource9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DResource9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DResource9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DResource9_GetType(p) (p)->lpVtbl->GetType(p)
#else
#define IDirect3DResource9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DResource9_AddRef(p) (p)->AddRef()
#define IDirect3DResource9_Release(p) (p)->Release()
#define IDirect3DResource9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DResource9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DResource9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DResource9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DResource9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DResource9_GetPriority(p) (p)->GetPriority()
#define IDirect3DResource9_PreLoad(p) (p)->PreLoad()
#define IDirect3DResource9_GetType(p) (p)->GetType()
#endif




#undef INTERFACE
#define INTERFACE IDirect3DVertexDeclaration9

DECLARE_INTERFACE_(IDirect3DVertexDeclaration9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVertexDeclaration9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(GetDeclaration)(THIS_ D3DVERTEXELEMENT9* pElement,UINT* pNumElements) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DVertexDeclaration9 *LPDIRECT3DVERTEXDECLARATION9, *PDIRECT3DVERTEXDECLARATION9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexDeclaration9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexDeclaration9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexDeclaration9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVertexDeclaration9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexDeclaration9_GetDeclaration(p,a,b) (p)->lpVtbl->GetDeclaration(p,a,b)
#else
#define IDirect3DVertexDeclaration9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVertexDeclaration9_AddRef(p) (p)->AddRef()
#define IDirect3DVertexDeclaration9_Release(p) (p)->Release()
#define IDirect3DVertexDeclaration9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVertexDeclaration9_GetDeclaration(p,a,b) (p)->GetDeclaration(a,b)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DVertexShader9

DECLARE_INTERFACE_(IDirect3DVertexShader9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVertexShader9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(GetFunction)(THIS_ void*,UINT* pSizeOfData) PURE;
    
    #ifdef D3D_DEBUG_INFO
    DWORD Version;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DVertexShader9 *LPDIRECT3DVERTEXSHADER9, *PDIRECT3DVERTEXSHADER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexShader9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexShader9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexShader9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVertexShader9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexShader9_GetFunction(p,a,b) (p)->lpVtbl->GetFunction(p,a,b)
#else
#define IDirect3DVertexShader9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVertexShader9_AddRef(p) (p)->AddRef()
#define IDirect3DVertexShader9_Release(p) (p)->Release()
#define IDirect3DVertexShader9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVertexShader9_GetFunction(p,a,b) (p)->GetFunction(a,b)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DPixelShader9

DECLARE_INTERFACE_(IDirect3DPixelShader9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DPixelShader9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(GetFunction)(THIS_ void*,UINT* pSizeOfData) PURE;
    
    #ifdef D3D_DEBUG_INFO
    DWORD Version;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DPixelShader9 *LPDIRECT3DPIXELSHADER9, *PDIRECT3DPIXELSHADER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DPixelShader9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DPixelShader9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DPixelShader9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DPixelShader9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DPixelShader9_GetFunction(p,a,b) (p)->lpVtbl->GetFunction(p,a,b)
#else
#define IDirect3DPixelShader9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DPixelShader9_AddRef(p) (p)->AddRef()
#define IDirect3DPixelShader9_Release(p) (p)->Release()
#define IDirect3DPixelShader9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DPixelShader9_GetFunction(p,a,b) (p)->GetFunction(a,b)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DBaseTexture9

DECLARE_INTERFACE_(IDirect3DBaseTexture9, IDirect3DResource9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType) PURE;
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS) PURE;
    STDMETHOD_(void, GenerateMipSubLevels)(THIS) PURE;
};
    
typedef struct IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9, *PDIRECT3DBASETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DBaseTexture9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DBaseTexture9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DBaseTexture9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DBaseTexture9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DBaseTexture9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DBaseTexture9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DBaseTexture9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DBaseTexture9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DBaseTexture9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DBaseTexture9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DBaseTexture9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DBaseTexture9_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DBaseTexture9_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DBaseTexture9_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DBaseTexture9_SetAutoGenFilterType(p,a) (p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DBaseTexture9_GetAutoGenFilterType(p) (p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DBaseTexture9_GenerateMipSubLevels(p) (p)->lpVtbl->GenerateMipSubLevels(p)
#else
#define IDirect3DBaseTexture9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DBaseTexture9_AddRef(p) (p)->AddRef()
#define IDirect3DBaseTexture9_Release(p) (p)->Release()
#define IDirect3DBaseTexture9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DBaseTexture9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DBaseTexture9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DBaseTexture9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DBaseTexture9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DBaseTexture9_GetPriority(p) (p)->GetPriority()
#define IDirect3DBaseTexture9_PreLoad(p) (p)->PreLoad()
#define IDirect3DBaseTexture9_GetType(p) (p)->GetType()
#define IDirect3DBaseTexture9_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DBaseTexture9_GetLOD(p) (p)->GetLOD()
#define IDirect3DBaseTexture9_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DBaseTexture9_SetAutoGenFilterType(p,a) (p)->SetAutoGenFilterType(a)
#define IDirect3DBaseTexture9_GetAutoGenFilterType(p) (p)->GetAutoGenFilterType()
#define IDirect3DBaseTexture9_GenerateMipSubLevels(p) (p)->GenerateMipSubLevels()
#endif





#undef INTERFACE
#define INTERFACE IDirect3DTexture9

DECLARE_INTERFACE_(IDirect3DTexture9, IDirect3DBaseTexture9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType) PURE;
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS) PURE;
    STDMETHOD_(void, GenerateMipSubLevels)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetSurfaceLevel)(THIS_ UINT Level,IDirect3DSurface9** ppSurfaceLevel) PURE;
    STDMETHOD(LockRect)(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ CONST RECT* pDirtyRect) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Width;
    UINT Height;
    UINT Levels;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    DWORD Priority;
    DWORD LOD;
    D3DTEXTUREFILTERTYPE FilterType;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DTexture9 *LPDIRECT3DTEXTURE9, *PDIRECT3DTEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DTexture9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DTexture9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DTexture9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DTexture9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DTexture9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DTexture9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DTexture9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DTexture9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DTexture9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DTexture9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DTexture9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DTexture9_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DTexture9_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DTexture9_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DTexture9_SetAutoGenFilterType(p,a) (p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DTexture9_GetAutoGenFilterType(p) (p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DTexture9_GenerateMipSubLevels(p) (p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DTexture9_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DTexture9_GetSurfaceLevel(p,a,b) (p)->lpVtbl->GetSurfaceLevel(p,a,b)
#define IDirect3DTexture9_LockRect(p,a,b,c,d) (p)->lpVtbl->LockRect(p,a,b,c,d)
#define IDirect3DTexture9_UnlockRect(p,a) (p)->lpVtbl->UnlockRect(p,a)
#define IDirect3DTexture9_AddDirtyRect(p,a) (p)->lpVtbl->AddDirtyRect(p,a)
#else
#define IDirect3DTexture9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DTexture9_AddRef(p) (p)->AddRef()
#define IDirect3DTexture9_Release(p) (p)->Release()
#define IDirect3DTexture9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DTexture9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DTexture9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DTexture9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DTexture9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DTexture9_GetPriority(p) (p)->GetPriority()
#define IDirect3DTexture9_PreLoad(p) (p)->PreLoad()
#define IDirect3DTexture9_GetType(p) (p)->GetType()
#define IDirect3DTexture9_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DTexture9_GetLOD(p) (p)->GetLOD()
#define IDirect3DTexture9_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DTexture9_SetAutoGenFilterType(p,a) (p)->SetAutoGenFilterType(a)
#define IDirect3DTexture9_GetAutoGenFilterType(p) (p)->GetAutoGenFilterType()
#define IDirect3DTexture9_GenerateMipSubLevels(p) (p)->GenerateMipSubLevels()
#define IDirect3DTexture9_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DTexture9_GetSurfaceLevel(p,a,b) (p)->GetSurfaceLevel(a,b)
#define IDirect3DTexture9_LockRect(p,a,b,c,d) (p)->LockRect(a,b,c,d)
#define IDirect3DTexture9_UnlockRect(p,a) (p)->UnlockRect(a)
#define IDirect3DTexture9_AddDirtyRect(p,a) (p)->AddDirtyRect(a)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DVolumeTexture9

DECLARE_INTERFACE_(IDirect3DVolumeTexture9, IDirect3DBaseTexture9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType) PURE;
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS) PURE;
    STDMETHOD_(void, GenerateMipSubLevels)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DVOLUME_DESC *pDesc) PURE;
    STDMETHOD(GetVolumeLevel)(THIS_ UINT Level,IDirect3DVolume9** ppVolumeLevel) PURE;
    STDMETHOD(LockBox)(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT Levels;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    DWORD Priority;
    DWORD LOD;
    D3DTEXTUREFILTERTYPE FilterType;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DVolumeTexture9 *LPDIRECT3DVOLUMETEXTURE9, *PDIRECT3DVOLUMETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolumeTexture9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolumeTexture9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVolumeTexture9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVolumeTexture9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolumeTexture9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolumeTexture9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolumeTexture9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolumeTexture9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVolumeTexture9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DVolumeTexture9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DVolumeTexture9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DVolumeTexture9_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DVolumeTexture9_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DVolumeTexture9_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DVolumeTexture9_SetAutoGenFilterType(p,a) (p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DVolumeTexture9_GetAutoGenFilterType(p) (p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DVolumeTexture9_GenerateMipSubLevels(p) (p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DVolumeTexture9_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DVolumeTexture9_GetVolumeLevel(p,a,b) (p)->lpVtbl->GetVolumeLevel(p,a,b)
#define IDirect3DVolumeTexture9_LockBox(p,a,b,c,d) (p)->lpVtbl->LockBox(p,a,b,c,d)
#define IDirect3DVolumeTexture9_UnlockBox(p,a) (p)->lpVtbl->UnlockBox(p,a)
#define IDirect3DVolumeTexture9_AddDirtyBox(p,a) (p)->lpVtbl->AddDirtyBox(p,a)
#else
#define IDirect3DVolumeTexture9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVolumeTexture9_AddRef(p) (p)->AddRef()
#define IDirect3DVolumeTexture9_Release(p) (p)->Release()
#define IDirect3DVolumeTexture9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVolumeTexture9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolumeTexture9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVolumeTexture9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVolumeTexture9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DVolumeTexture9_GetPriority(p) (p)->GetPriority()
#define IDirect3DVolumeTexture9_PreLoad(p) (p)->PreLoad()
#define IDirect3DVolumeTexture9_GetType(p) (p)->GetType()
#define IDirect3DVolumeTexture9_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DVolumeTexture9_GetLOD(p) (p)->GetLOD()
#define IDirect3DVolumeTexture9_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DVolumeTexture9_SetAutoGenFilterType(p,a) (p)->SetAutoGenFilterType(a)
#define IDirect3DVolumeTexture9_GetAutoGenFilterType(p) (p)->GetAutoGenFilterType()
#define IDirect3DVolumeTexture9_GenerateMipSubLevels(p) (p)->GenerateMipSubLevels()
#define IDirect3DVolumeTexture9_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DVolumeTexture9_GetVolumeLevel(p,a,b) (p)->GetVolumeLevel(a,b)
#define IDirect3DVolumeTexture9_LockBox(p,a,b,c,d) (p)->LockBox(a,b,c,d)
#define IDirect3DVolumeTexture9_UnlockBox(p,a) (p)->UnlockBox(a)
#define IDirect3DVolumeTexture9_AddDirtyBox(p,a) (p)->AddDirtyBox(a)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DCubeTexture9

DECLARE_INTERFACE_(IDirect3DCubeTexture9, IDirect3DBaseTexture9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType) PURE;
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS) PURE;
    STDMETHOD_(void, GenerateMipSubLevels)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface) PURE;
    STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Width;
    UINT Height;
    UINT Levels;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    DWORD Priority;
    DWORD LOD;
    D3DTEXTUREFILTERTYPE FilterType;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DCubeTexture9 *LPDIRECT3DCUBETEXTURE9, *PDIRECT3DCUBETEXTURE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DCubeTexture9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DCubeTexture9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DCubeTexture9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DCubeTexture9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DCubeTexture9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DCubeTexture9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DCubeTexture9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DCubeTexture9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DCubeTexture9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DCubeTexture9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DCubeTexture9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DCubeTexture9_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirect3DCubeTexture9_GetLOD(p) (p)->lpVtbl->GetLOD(p)
#define IDirect3DCubeTexture9_GetLevelCount(p) (p)->lpVtbl->GetLevelCount(p)
#define IDirect3DCubeTexture9_SetAutoGenFilterType(p,a) (p)->lpVtbl->SetAutoGenFilterType(p,a)
#define IDirect3DCubeTexture9_GetAutoGenFilterType(p) (p)->lpVtbl->GetAutoGenFilterType(p)
#define IDirect3DCubeTexture9_GenerateMipSubLevels(p) (p)->lpVtbl->GenerateMipSubLevels(p)
#define IDirect3DCubeTexture9_GetLevelDesc(p,a,b) (p)->lpVtbl->GetLevelDesc(p,a,b)
#define IDirect3DCubeTexture9_GetCubeMapSurface(p,a,b,c) (p)->lpVtbl->GetCubeMapSurface(p,a,b,c)
#define IDirect3DCubeTexture9_LockRect(p,a,b,c,d,e) (p)->lpVtbl->LockRect(p,a,b,c,d,e)
#define IDirect3DCubeTexture9_UnlockRect(p,a,b) (p)->lpVtbl->UnlockRect(p,a,b)
#define IDirect3DCubeTexture9_AddDirtyRect(p,a,b) (p)->lpVtbl->AddDirtyRect(p,a,b)
#else
#define IDirect3DCubeTexture9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DCubeTexture9_AddRef(p) (p)->AddRef()
#define IDirect3DCubeTexture9_Release(p) (p)->Release()
#define IDirect3DCubeTexture9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DCubeTexture9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DCubeTexture9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DCubeTexture9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DCubeTexture9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DCubeTexture9_GetPriority(p) (p)->GetPriority()
#define IDirect3DCubeTexture9_PreLoad(p) (p)->PreLoad()
#define IDirect3DCubeTexture9_GetType(p) (p)->GetType()
#define IDirect3DCubeTexture9_SetLOD(p,a) (p)->SetLOD(a)
#define IDirect3DCubeTexture9_GetLOD(p) (p)->GetLOD()
#define IDirect3DCubeTexture9_GetLevelCount(p) (p)->GetLevelCount()
#define IDirect3DCubeTexture9_SetAutoGenFilterType(p,a) (p)->SetAutoGenFilterType(a)
#define IDirect3DCubeTexture9_GetAutoGenFilterType(p) (p)->GetAutoGenFilterType()
#define IDirect3DCubeTexture9_GenerateMipSubLevels(p) (p)->GenerateMipSubLevels()
#define IDirect3DCubeTexture9_GetLevelDesc(p,a,b) (p)->GetLevelDesc(a,b)
#define IDirect3DCubeTexture9_GetCubeMapSurface(p,a,b,c) (p)->GetCubeMapSurface(a,b,c)
#define IDirect3DCubeTexture9_LockRect(p,a,b,c,d,e) (p)->LockRect(a,b,c,d,e)
#define IDirect3DCubeTexture9_UnlockRect(p,a,b) (p)->UnlockRect(a,b)
#define IDirect3DCubeTexture9_AddDirtyRect(p,a,b) (p)->AddDirtyRect(a,b)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DVertexBuffer9

DECLARE_INTERFACE_(IDirect3DVertexBuffer9, IDirect3DResource9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Length;
    DWORD Usage;
    DWORD FVF;
    D3DPOOL Pool;
    DWORD Priority;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DVertexBuffer9 *LPDIRECT3DVERTEXBUFFER9, *PDIRECT3DVERTEXBUFFER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVertexBuffer9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexBuffer9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexBuffer9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVertexBuffer9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVertexBuffer9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVertexBuffer9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVertexBuffer9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVertexBuffer9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DVertexBuffer9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DVertexBuffer9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DVertexBuffer9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DVertexBuffer9_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DVertexBuffer9_Unlock(p) (p)->lpVtbl->Unlock(p)
#define IDirect3DVertexBuffer9_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DVertexBuffer9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVertexBuffer9_AddRef(p) (p)->AddRef()
#define IDirect3DVertexBuffer9_Release(p) (p)->Release()
#define IDirect3DVertexBuffer9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVertexBuffer9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVertexBuffer9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVertexBuffer9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVertexBuffer9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DVertexBuffer9_GetPriority(p) (p)->GetPriority()
#define IDirect3DVertexBuffer9_PreLoad(p) (p)->PreLoad()
#define IDirect3DVertexBuffer9_GetType(p) (p)->GetType()
#define IDirect3DVertexBuffer9_Lock(p,a,b,c,d) (p)->Lock(a,b,c,d)
#define IDirect3DVertexBuffer9_Unlock(p) (p)->Unlock()
#define IDirect3DVertexBuffer9_GetDesc(p,a) (p)->GetDesc(a)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DIndexBuffer9

DECLARE_INTERFACE_(IDirect3DIndexBuffer9, IDirect3DResource9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Length;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    DWORD Priority;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DIndexBuffer9 *LPDIRECT3DINDEXBUFFER9, *PDIRECT3DINDEXBUFFER9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DIndexBuffer9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DIndexBuffer9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DIndexBuffer9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DIndexBuffer9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DIndexBuffer9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DIndexBuffer9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DIndexBuffer9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DIndexBuffer9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DIndexBuffer9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DIndexBuffer9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DIndexBuffer9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DIndexBuffer9_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirect3DIndexBuffer9_Unlock(p) (p)->lpVtbl->Unlock(p)
#define IDirect3DIndexBuffer9_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#else
#define IDirect3DIndexBuffer9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DIndexBuffer9_AddRef(p) (p)->AddRef()
#define IDirect3DIndexBuffer9_Release(p) (p)->Release()
#define IDirect3DIndexBuffer9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DIndexBuffer9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DIndexBuffer9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DIndexBuffer9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DIndexBuffer9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DIndexBuffer9_GetPriority(p) (p)->GetPriority()
#define IDirect3DIndexBuffer9_PreLoad(p) (p)->PreLoad()
#define IDirect3DIndexBuffer9_GetType(p) (p)->GetType()
#define IDirect3DIndexBuffer9_Lock(p,a,b,c,d) (p)->Lock(a,b,c,d)
#define IDirect3DIndexBuffer9_Unlock(p) (p)->Unlock()
#define IDirect3DIndexBuffer9_GetDesc(p,a) (p)->GetDesc(a)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DSurface9

DECLARE_INTERFACE_(IDirect3DSurface9, IDirect3DResource9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS) PURE;
    STDMETHOD(GetDC)(THIS_ HDC *phdc) PURE;
    STDMETHOD(ReleaseDC)(THIS_ HDC hdc) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Width;
    UINT Height;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    DWORD MultiSampleQuality;
    DWORD Priority;
    UINT LockCount;
    UINT DCCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DSurface9 *LPDIRECT3DSURFACE9, *PDIRECT3DSURFACE9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSurface9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSurface9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DSurface9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DSurface9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSurface9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DSurface9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DSurface9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DSurface9_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirect3DSurface9_GetPriority(p) (p)->lpVtbl->GetPriority(p)
#define IDirect3DSurface9_PreLoad(p) (p)->lpVtbl->PreLoad(p)
#define IDirect3DSurface9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DSurface9_GetContainer(p,a,b) (p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DSurface9_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#define IDirect3DSurface9_LockRect(p,a,b,c) (p)->lpVtbl->LockRect(p,a,b,c)
#define IDirect3DSurface9_UnlockRect(p) (p)->lpVtbl->UnlockRect(p)
#define IDirect3DSurface9_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirect3DSurface9_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#else
#define IDirect3DSurface9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DSurface9_AddRef(p) (p)->AddRef()
#define IDirect3DSurface9_Release(p) (p)->Release()
#define IDirect3DSurface9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DSurface9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DSurface9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DSurface9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DSurface9_SetPriority(p,a) (p)->SetPriority(a)
#define IDirect3DSurface9_GetPriority(p) (p)->GetPriority()
#define IDirect3DSurface9_PreLoad(p) (p)->PreLoad()
#define IDirect3DSurface9_GetType(p) (p)->GetType()
#define IDirect3DSurface9_GetContainer(p,a,b) (p)->GetContainer(a,b)
#define IDirect3DSurface9_GetDesc(p,a) (p)->GetDesc(a)
#define IDirect3DSurface9_LockRect(p,a,b,c) (p)->LockRect(a,b,c)
#define IDirect3DSurface9_UnlockRect(p) (p)->UnlockRect()
#define IDirect3DSurface9_GetDC(p,a) (p)->GetDC(a)
#define IDirect3DSurface9_ReleaseDC(p,a) (p)->ReleaseDC(a)
#endif





#undef INTERFACE
#define INTERFACE IDirect3DVolume9

DECLARE_INTERFACE_(IDirect3DVolume9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVolume9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DVOLUME_DESC *pDesc) PURE;
    STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS) PURE;
    
    #ifdef D3D_DEBUG_INFO
    LPCWSTR Name;
    UINT Width;
    UINT Height;
    UINT Depth;
    DWORD Usage;
    D3DFORMAT Format;
    D3DPOOL Pool;
    UINT LockCount;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DVolume9 *LPDIRECT3DVOLUME9, *PDIRECT3DVOLUME9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DVolume9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVolume9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DVolume9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DVolume9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DVolume9_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirect3DVolume9_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirect3DVolume9_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirect3DVolume9_GetContainer(p,a,b) (p)->lpVtbl->GetContainer(p,a,b)
#define IDirect3DVolume9_GetDesc(p,a) (p)->lpVtbl->GetDesc(p,a)
#define IDirect3DVolume9_LockBox(p,a,b,c) (p)->lpVtbl->LockBox(p,a,b,c)
#define IDirect3DVolume9_UnlockBox(p) (p)->lpVtbl->UnlockBox(p)
#else
#define IDirect3DVolume9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVolume9_AddRef(p) (p)->AddRef()
#define IDirect3DVolume9_Release(p) (p)->Release()
#define IDirect3DVolume9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DVolume9_SetPrivateData(p,a,b,c,d) (p)->SetPrivateData(a,b,c,d)
#define IDirect3DVolume9_GetPrivateData(p,a,b,c) (p)->GetPrivateData(a,b,c)
#define IDirect3DVolume9_FreePrivateData(p,a) (p)->FreePrivateData(a)
#define IDirect3DVolume9_GetContainer(p,a,b) (p)->GetContainer(a,b)
#define IDirect3DVolume9_GetDesc(p,a) (p)->GetDesc(a)
#define IDirect3DVolume9_LockBox(p,a,b,c) (p)->LockBox(a,b,c)
#define IDirect3DVolume9_UnlockBox(p) (p)->UnlockBox()
#endif




#undef INTERFACE
#define INTERFACE IDirect3DQuery9

DECLARE_INTERFACE_(IDirect3DQuery9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DQuery9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD_(D3DQUERYTYPE, GetType)(THIS) PURE;
    STDMETHOD_(DWORD, GetDataSize)(THIS) PURE;
    STDMETHOD(Issue)(THIS_ DWORD dwIssueFlags) PURE;
    STDMETHOD(GetData)(THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags) PURE;
    
    #ifdef D3D_DEBUG_INFO
    D3DQUERYTYPE Type;
    DWORD DataSize;
    LPCWSTR CreationCallStack;
    #endif
};
    
typedef struct IDirect3DQuery9 *LPDIRECT3DQUERY9, *PDIRECT3DQUERY9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DQuery9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DQuery9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DQuery9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DQuery9_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DQuery9_GetType(p) (p)->lpVtbl->GetType(p)
#define IDirect3DQuery9_GetDataSize(p) (p)->lpVtbl->GetDataSize(p)
#define IDirect3DQuery9_Issue(p,a) (p)->lpVtbl->Issue(p,a)
#define IDirect3DQuery9_GetData(p,a,b,c) (p)->lpVtbl->GetData(p,a,b,c)
#else
#define IDirect3DQuery9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DQuery9_AddRef(p) (p)->AddRef()
#define IDirect3DQuery9_Release(p) (p)->Release()
#define IDirect3DQuery9_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DQuery9_GetType(p) (p)->GetType()
#define IDirect3DQuery9_GetDataSize(p) (p)->GetDataSize()
#define IDirect3DQuery9_Issue(p,a) (p)->Issue(a)
#define IDirect3DQuery9_GetData(p,a,b,c) (p)->GetData(a,b,c)
#endif

/****************************************************************************
 * Flags for SetPrivateData method on all D3D9 interfaces
 *
 * The passed pointer is an IUnknown ptr. The SizeOfData argument to SetPrivateData
 * must be set to sizeof(IUnknown*). Direct3D will call AddRef through this
 * pointer and Release when the private data is destroyed. The data will be
 * destroyed when another SetPrivateData with the same GUID is set, when
 * FreePrivateData is called, or when the D3D9 object is freed.
 ****************************************************************************/
#define D3DSPD_IUNKNOWN                         0x00000001L

/****************************************************************************
 *
 * Flags for IDirect3D9::CreateDevice's BehaviorFlags
 *
 ****************************************************************************/

#define D3DCREATE_FPU_PRESERVE                  0x00000002L
#define D3DCREATE_MULTITHREADED                 0x00000004L

#define D3DCREATE_PUREDEVICE                    0x00000010L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING     0x00000020L
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000040L
#define D3DCREATE_MIXED_VERTEXPROCESSING        0x00000080L

#define D3DCREATE_DISABLE_DRIVER_MANAGEMENT     0x00000100L
#define D3DCREATE_ADAPTERGROUP_DEVICE           0x00000200L
#define D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX  0x00000400L

// This flag causes the D3D runtime not to alter the focus 
// window in any way. Use with caution- the burden of supporting
// focus management events (alt-tab, etc.) falls on the 
// application, and appropriate responses (switching display
// mode, etc.) should be coded.
#define D3DCREATE_NOWINDOWCHANGES				0x00000800L

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

// Disable multithreading for software vertex processing
#define D3DCREATE_DISABLE_PSGP_THREADING        0x00002000L
// This flag enables present statistics on device.
#define D3DCREATE_ENABLE_PRESENTSTATS           0x00004000L
// This flag disables printscreen support in the runtime for this device
#define D3DCREATE_DISABLE_PRINTSCREEN           0x00008000L

#define D3DCREATE_SCREENSAVER                   0x10000000L


#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */



/****************************************************************************
 *
 * Parameter for IDirect3D9::CreateDevice's Adapter argument
 *
 ****************************************************************************/

#define D3DADAPTER_DEFAULT                     0

/****************************************************************************
 *
 * Flags for IDirect3D9::EnumAdapters
 *
 ****************************************************************************/

/*
 * The D3DENUM_WHQL_LEVEL value has been retired for 9Ex and future versions,
 * but it needs to be defined here for compatibility with DX9 and earlier versions.
 * See the DirectX SDK for sample code on discovering driver signatures.
 */
#define D3DENUM_WHQL_LEVEL                      0x00000002L

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

/* NO_DRIVERVERSION will not fill out the DriverVersion field, nor will the
   DriverVersion be incorporated into the DeviceIdentifier GUID. WINNT only */
#define D3DENUM_NO_DRIVERVERSION                0x00000004L

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */


/****************************************************************************
 *
 * Maximum number of back-buffers supported in DX9
 *
 ****************************************************************************/

#define D3DPRESENT_BACK_BUFFERS_MAX             3L

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

/****************************************************************************
 *
 * Maximum number of back-buffers supported when apps use CreateDeviceEx
 *
 ****************************************************************************/

#define D3DPRESENT_BACK_BUFFERS_MAX_EX          30L

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */

/****************************************************************************
 *
 * Flags for IDirect3DDevice9::SetGammaRamp
 *
 ****************************************************************************/

#define D3DSGR_NO_CALIBRATION                  0x00000000L
#define D3DSGR_CALIBRATE                       0x00000001L

/****************************************************************************
 *
 * Flags for IDirect3DDevice9::SetCursorPosition
 *
 ****************************************************************************/

#define D3DCURSOR_IMMEDIATE_UPDATE             0x00000001L

/****************************************************************************
 *
 * Flags for IDirect3DSwapChain9::Present
 *
 ****************************************************************************/

#define D3DPRESENT_DONOTWAIT                   0x00000001L
#define D3DPRESENT_LINEAR_CONTENT              0x00000002L

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)

#define D3DPRESENT_DONOTFLIP                   0x00000004L
#define D3DPRESENT_FLIPRESTART                 0x00000008L
#define D3DPRESENT_VIDEO_RESTRICT_TO_MONITOR   0x00000010L
#define D3DPRESENT_UPDATEOVERLAYONLY           0x00000020L
#define D3DPRESENT_HIDEOVERLAY                 0x00000040L
#define D3DPRESENT_UPDATECOLORKEY              0x00000080L
#define D3DPRESENT_FORCEIMMEDIATE              0x00000100L

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */


/****************************************************************************
 *
 * Flags for DrawPrimitive/DrawIndexedPrimitive
 *   Also valid for Begin/BeginIndexed
 *   Also valid for VertexBuffer::CreateVertexBuffer
 ****************************************************************************/


/*
 *  DirectDraw error codes
 */
#define _FACD3D  0x876
#define MAKE_D3DHRESULT( code )  MAKE_HRESULT( 1, _FACD3D, code )
#define MAKE_D3DSTATUS( code )  MAKE_HRESULT( 0, _FACD3D, code )

/*
 * Direct3D Errors
 */
#define D3D_OK                              S_OK

#define D3DERR_WRONGTEXTUREFORMAT               MAKE_D3DHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION        MAKE_D3DHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG              MAKE_D3DHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION        MAKE_D3DHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG              MAKE_D3DHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS                MAKE_D3DHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER         MAKE_D3DHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE           MAKE_D3DHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE           MAKE_D3DHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER         MAKE_D3DHRESULT(2082)
#define D3DERR_CONFLICTINGTEXTUREPALETTE        MAKE_D3DHRESULT(2086)
#define D3DERR_DRIVERINTERNALERROR              MAKE_D3DHRESULT(2087)

#define D3DERR_NOTFOUND                         MAKE_D3DHRESULT(2150)
#define D3DERR_MOREDATA                         MAKE_D3DHRESULT(2151)
#define D3DERR_DEVICELOST                       MAKE_D3DHRESULT(2152)
#define D3DERR_DEVICENOTRESET                   MAKE_D3DHRESULT(2153)
#define D3DERR_NOTAVAILABLE                     MAKE_D3DHRESULT(2154)
#define D3DERR_OUTOFVIDEOMEMORY                 MAKE_D3DHRESULT(380)
#define D3DERR_INVALIDDEVICE                    MAKE_D3DHRESULT(2155)
#define D3DERR_INVALIDCALL                      MAKE_D3DHRESULT(2156)
#define D3DERR_DRIVERINVALIDCALL                MAKE_D3DHRESULT(2157)
#define D3DERR_WASSTILLDRAWING                  MAKE_D3DHRESULT(540)
#define D3DOK_NOAUTOGEN                         MAKE_D3DSTATUS(2159)

/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)


#define D3DERR_DEVICEREMOVED                    MAKE_D3DHRESULT(2160)
#define S_NOT_RESIDENT                          MAKE_D3DSTATUS(2165)
#define S_RESIDENT_IN_SHARED_MEMORY             MAKE_D3DSTATUS(2166)
#define S_PRESENT_MODE_CHANGED                  MAKE_D3DSTATUS(2167)
#define S_PRESENT_OCCLUDED                      MAKE_D3DSTATUS(2168)
#define D3DERR_DEVICEHUNG                       MAKE_D3DHRESULT(2164)
#define D3DERR_UNSUPPORTEDOVERLAY               MAKE_D3DHRESULT(2171)
#define D3DERR_UNSUPPORTEDOVERLAYFORMAT         MAKE_D3DHRESULT(2172)
#define D3DERR_CANNOTPROTECTCONTENT             MAKE_D3DHRESULT(2173)
#define D3DERR_UNSUPPORTEDCRYPTO                MAKE_D3DHRESULT(2174)
#define D3DERR_PRESENT_STATISTICS_DISJOINT      MAKE_D3DHRESULT(2180)


/*********************
 * D3D9Ex interfaces
 *********************/

HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex**);




#undef INTERFACE
#define INTERFACE IDirect3D9Ex

DECLARE_INTERFACE_(IDirect3D9Ex, IDirect3D9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3D9 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) PURE;
    STDMETHOD_(UINT, GetAdapterCount)(THIS) PURE;
    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) PURE;
    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter,D3DFORMAT Format) PURE;
    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) PURE;
    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) PURE;
    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) PURE;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) PURE;
    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) PURE;
    STDMETHOD_(UINT, GetAdapterModeCountEx)(THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter ) PURE;
    STDMETHOD(EnumAdapterModesEx)(THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode) PURE;
    STDMETHOD(GetAdapterDisplayModeEx)(THIS_ UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation) PURE;
    STDMETHOD(CreateDeviceEx)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface) PURE;
    STDMETHOD(GetAdapterLUID)(THIS_ UINT Adapter,LUID * pLUID) PURE;
};
    
typedef struct IDirect3D9Ex *LPDIRECT3D9EX, *PDIRECT3D9EX;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3D9Ex_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D9Ex_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3D9Ex_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3D9Ex_RegisterSoftwareDevice(p,a) (p)->lpVtbl->RegisterSoftwareDevice(p,a)
#define IDirect3D9Ex_GetAdapterCount(p) (p)->lpVtbl->GetAdapterCount(p)
#define IDirect3D9Ex_GetAdapterIdentifier(p,a,b,c) (p)->lpVtbl->GetAdapterIdentifier(p,a,b,c)
#define IDirect3D9Ex_GetAdapterModeCount(p,a,b) (p)->lpVtbl->GetAdapterModeCount(p,a,b)
#define IDirect3D9Ex_EnumAdapterModes(p,a,b,c,d) (p)->lpVtbl->EnumAdapterModes(p,a,b,c,d)
#define IDirect3D9Ex_GetAdapterDisplayMode(p,a,b) (p)->lpVtbl->GetAdapterDisplayMode(p,a,b)
#define IDirect3D9Ex_CheckDeviceType(p,a,b,c,d,e) (p)->lpVtbl->CheckDeviceType(p,a,b,c,d,e)
#define IDirect3D9Ex_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->lpVtbl->CheckDeviceFormat(p,a,b,c,d,e,f)
#define IDirect3D9Ex_CheckDeviceMultiSampleType(p,a,b,c,d,e,f) (p)->lpVtbl->CheckDeviceMultiSampleType(p,a,b,c,d,e,f)
#define IDirect3D9Ex_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->lpVtbl->CheckDepthStencilMatch(p,a,b,c,d,e)
#define IDirect3D9Ex_CheckDeviceFormatConversion(p,a,b,c,d) (p)->lpVtbl->CheckDeviceFormatConversion(p,a,b,c,d)
#define IDirect3D9Ex_GetDeviceCaps(p,a,b,c) (p)->lpVtbl->GetDeviceCaps(p,a,b,c)
#define IDirect3D9Ex_GetAdapterMonitor(p,a) (p)->lpVtbl->GetAdapterMonitor(p,a)
#define IDirect3D9Ex_CreateDevice(p,a,b,c,d,e,f) (p)->lpVtbl->CreateDevice(p,a,b,c,d,e,f)
#define IDirect3D9Ex_GetAdapterModeCountEx(p,a,b) (p)->lpVtbl->GetAdapterModeCountEx(p,a,b)
#define IDirect3D9Ex_EnumAdapterModesEx(p,a,b,c,d) (p)->lpVtbl->EnumAdapterModesEx(p,a,b,c,d)
#define IDirect3D9Ex_GetAdapterDisplayModeEx(p,a,b,c) (p)->lpVtbl->GetAdapterDisplayModeEx(p,a,b,c)
#define IDirect3D9Ex_CreateDeviceEx(p,a,b,c,d,e,f,g) (p)->lpVtbl->CreateDeviceEx(p,a,b,c,d,e,f,g)
#define IDirect3D9Ex_GetAdapterLUID(p,a,b) (p)->lpVtbl->GetAdapterLUID(p,a,b)
#else
#define IDirect3D9Ex_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D9Ex_AddRef(p) (p)->AddRef()
#define IDirect3D9Ex_Release(p) (p)->Release()
#define IDirect3D9Ex_RegisterSoftwareDevice(p,a) (p)->RegisterSoftwareDevice(a)
#define IDirect3D9Ex_GetAdapterCount(p) (p)->GetAdapterCount()
#define IDirect3D9Ex_GetAdapterIdentifier(p,a,b,c) (p)->GetAdapterIdentifier(a,b,c)
#define IDirect3D9Ex_GetAdapterModeCount(p,a,b) (p)->GetAdapterModeCount(a,b)
#define IDirect3D9Ex_EnumAdapterModes(p,a,b,c,d) (p)->EnumAdapterModes(a,b,c,d)
#define IDirect3D9Ex_GetAdapterDisplayMode(p,a,b) (p)->GetAdapterDisplayMode(a,b)
#define IDirect3D9Ex_CheckDeviceType(p,a,b,c,d,e) (p)->CheckDeviceType(a,b,c,d,e)
#define IDirect3D9Ex_CheckDeviceFormat(p,a,b,c,d,e,f) (p)->CheckDeviceFormat(a,b,c,d,e,f)
#define IDirect3D9Ex_CheckDeviceMultiSampleType(p,a,b,c,d,e,f) (p)->CheckDeviceMultiSampleType(a,b,c,d,e,f)
#define IDirect3D9Ex_CheckDepthStencilMatch(p,a,b,c,d,e) (p)->CheckDepthStencilMatch(a,b,c,d,e)
#define IDirect3D9Ex_CheckDeviceFormatConversion(p,a,b,c,d) (p)->CheckDeviceFormatConversion(a,b,c,d)
#define IDirect3D9Ex_GetDeviceCaps(p,a,b,c) (p)->GetDeviceCaps(a,b,c)
#define IDirect3D9Ex_GetAdapterMonitor(p,a) (p)->GetAdapterMonitor(a)
#define IDirect3D9Ex_CreateDevice(p,a,b,c,d,e,f) (p)->CreateDevice(a,b,c,d,e,f)
#define IDirect3D9Ex_GetAdapterModeCountEx(p,a,b) (p)->GetAdapterModeCountEx(a,b)
#define IDirect3D9Ex_EnumAdapterModesEx(p,a,b,c,d) (p)->EnumAdapterModesEx(a,b,c,d)
#define IDirect3D9Ex_GetAdapterDisplayModeEx(p,a,b,c) (p)->GetAdapterDisplayModeEx(a,b,c)
#define IDirect3D9Ex_CreateDeviceEx(p,a,b,c,d,e,f,g) (p)->CreateDeviceEx(a,b,c,d,e,f,g)
#define IDirect3D9Ex_GetAdapterLUID(p,a,b) (p)->GetAdapterLUID(a,b)
#endif
























#undef INTERFACE
#define INTERFACE IDirect3DDevice9Ex

DECLARE_INTERFACE_(IDirect3DDevice9Ex, IDirect3DDevice9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DDevice9 methods ***/
    STDMETHOD(TestCooperativeLevel)(THIS) PURE;
    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) PURE;
    STDMETHOD(EvictManagedResources)(THIS) PURE;
    STDMETHOD(GetDirect3D)(THIS_ IDirect3D9** ppD3D9) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS9* pCaps) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) PURE;
    STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags) PURE;
    STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow) PURE;
    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain) PURE;
    STDMETHOD(GetSwapChain)(THIS_ UINT iSwapChain,IDirect3DSwapChain9** pSwapChain) PURE;
    STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS) PURE;
    STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD(SetDialogBoxMode)(THIS_ BOOL bEnableDialogs) PURE;
    STDMETHOD_(void, SetGammaRamp)(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD_(void, GetGammaRamp)(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(UpdateSurface)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) PURE;
    STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) PURE;
    STDMETHOD(GetRenderTargetData)(THIS_ IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(GetFrontBufferData)(THIS_ UINT iSwapChain,IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(StretchRect)(THIS_ IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) PURE;
    STDMETHOD(ColorFill)(THIS_ IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) PURE;
    STDMETHOD(CreateOffscreenPlainSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) PURE;
    STDMETHOD(SetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) PURE;
    STDMETHOD(SetDepthStencilSurface)(THIS_ IDirect3DSurface9* pNewZStencil) PURE;
    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface9** ppZStencilSurface) PURE;
    STDMETHOD(BeginScene)(THIS) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
    STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
    STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT9*) PURE;
    STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT9*) PURE;
    STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable) PURE;
    STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) PURE;
    STDMETHOD(BeginStateBlock)(THIS) PURE;
    STDMETHOD(EndStateBlock)(THIS_ IDirect3DStateBlock9** ppSB) PURE;
    STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9** ppTexture) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture9* pTexture) PURE;
    STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(GetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses) PURE;
    STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber) PURE;
    STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber) PURE;
    STDMETHOD(SetScissorRect)(THIS_ CONST RECT* pRect) PURE;
    STDMETHOD(GetScissorRect)(THIS_ RECT* pRect) PURE;
    STDMETHOD(SetSoftwareVertexProcessing)(THIS_ BOOL bSoftware) PURE;
    STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS) PURE;
    STDMETHOD(SetNPatchMode)(THIS_ float nSegments) PURE;
    STDMETHOD_(float, GetNPatchMode)(THIS) PURE;
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) PURE;
    STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) PURE;
    STDMETHOD(SetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9* pDecl) PURE;
    STDMETHOD(GetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9** ppDecl) PURE;
    STDMETHOD(SetFVF)(THIS_ DWORD FVF) PURE;
    STDMETHOD(GetFVF)(THIS_ DWORD* pFVF) PURE;
    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ IDirect3DVertexShader9* pShader) PURE;
    STDMETHOD(GetVertexShader)(THIS_ IDirect3DVertexShader9** ppShader) PURE;
    STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(GetVertexShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(GetVertexShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) PURE;
    STDMETHOD(GetVertexShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) PURE;
    STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) PURE;
    STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride) PURE;
    STDMETHOD(SetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT Setting) PURE;
    STDMETHOD(GetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT* pSetting) PURE;
    STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer9* pIndexData) PURE;
    STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer9** ppIndexData) PURE;
    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) PURE;
    STDMETHOD(SetPixelShader)(THIS_ IDirect3DPixelShader9* pShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ IDirect3DPixelShader9** ppShader) PURE;
    STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(GetPixelShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount) PURE;
    STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(GetPixelShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount) PURE;
    STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) PURE;
    STDMETHOD(GetPixelShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount) PURE;
    STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD(DeletePatch)(THIS_ UINT Handle) PURE;
    STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) PURE;
    STDMETHOD(SetConvolutionMonoKernel)(THIS_ UINT width,UINT height,float* rows,float* columns) PURE;
    STDMETHOD(ComposeRects)(THIS_ IDirect3DSurface9* pSrc,IDirect3DSurface9* pDst,IDirect3DVertexBuffer9* pSrcRectDescs,UINT NumRects,IDirect3DVertexBuffer9* pDstRectDescs,D3DCOMPOSERECTSOP Operation,int Xoffset,int Yoffset) PURE;
    STDMETHOD(PresentEx)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) PURE;
    STDMETHOD(GetGPUThreadPriority)(THIS_ INT* pPriority) PURE;
    STDMETHOD(SetGPUThreadPriority)(THIS_ INT Priority) PURE;
    STDMETHOD(WaitForVBlank)(THIS_ UINT iSwapChain) PURE;
    STDMETHOD(CheckResourceResidency)(THIS_ IDirect3DResource9** pResourceArray,UINT32 NumResources) PURE;
    STDMETHOD(SetMaximumFrameLatency)(THIS_ UINT MaxLatency) PURE;
    STDMETHOD(GetMaximumFrameLatency)(THIS_ UINT* pMaxLatency) PURE;
    STDMETHOD(CheckDeviceState)(THIS_ HWND hDestinationWindow) PURE;
    STDMETHOD(CreateRenderTargetEx)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage) PURE;
    STDMETHOD(CreateOffscreenPlainSurfaceEx)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage) PURE;
    STDMETHOD(CreateDepthStencilSurfaceEx)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage) PURE;
    STDMETHOD(ResetEx)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX *pFullscreenDisplayMode) PURE;
    STDMETHOD(GetDisplayModeEx)(THIS_ UINT iSwapChain,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation) PURE;
};
    
typedef struct IDirect3DDevice9Ex *LPDIRECT3DDEVICE9EX, *PDIRECT3DDEVICE9EX;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DDevice9Ex_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice9Ex_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice9Ex_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DDevice9Ex_TestCooperativeLevel(p) (p)->lpVtbl->TestCooperativeLevel(p)
#define IDirect3DDevice9Ex_GetAvailableTextureMem(p) (p)->lpVtbl->GetAvailableTextureMem(p)
#define IDirect3DDevice9Ex_EvictManagedResources(p) (p)->lpVtbl->EvictManagedResources(p)
#define IDirect3DDevice9Ex_GetDirect3D(p,a) (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice9Ex_GetDeviceCaps(p,a) (p)->lpVtbl->GetDeviceCaps(p,a)
#define IDirect3DDevice9Ex_GetDisplayMode(p,a,b) (p)->lpVtbl->GetDisplayMode(p,a,b)
#define IDirect3DDevice9Ex_GetCreationParameters(p,a) (p)->lpVtbl->GetCreationParameters(p,a)
#define IDirect3DDevice9Ex_SetCursorProperties(p,a,b,c) (p)->lpVtbl->SetCursorProperties(p,a,b,c)
#define IDirect3DDevice9Ex_SetCursorPosition(p,a,b,c) (p)->lpVtbl->SetCursorPosition(p,a,b,c)
#define IDirect3DDevice9Ex_ShowCursor(p,a) (p)->lpVtbl->ShowCursor(p,a)
#define IDirect3DDevice9Ex_CreateAdditionalSwapChain(p,a,b) (p)->lpVtbl->CreateAdditionalSwapChain(p,a,b)
#define IDirect3DDevice9Ex_GetSwapChain(p,a,b) (p)->lpVtbl->GetSwapChain(p,a,b)
#define IDirect3DDevice9Ex_GetNumberOfSwapChains(p) (p)->lpVtbl->GetNumberOfSwapChains(p)
#define IDirect3DDevice9Ex_Reset(p,a) (p)->lpVtbl->Reset(p,a)
#define IDirect3DDevice9Ex_Present(p,a,b,c,d) (p)->lpVtbl->Present(p,a,b,c,d)
#define IDirect3DDevice9Ex_GetBackBuffer(p,a,b,c,d) (p)->lpVtbl->GetBackBuffer(p,a,b,c,d)
#define IDirect3DDevice9Ex_GetRasterStatus(p,a,b) (p)->lpVtbl->GetRasterStatus(p,a,b)
#define IDirect3DDevice9Ex_SetDialogBoxMode(p,a) (p)->lpVtbl->SetDialogBoxMode(p,a)
#define IDirect3DDevice9Ex_SetGammaRamp(p,a,b,c) (p)->lpVtbl->SetGammaRamp(p,a,b,c)
#define IDirect3DDevice9Ex_GetGammaRamp(p,a,b) (p)->lpVtbl->GetGammaRamp(p,a,b)
#define IDirect3DDevice9Ex_CreateTexture(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateTexture(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i) (p)->lpVtbl->CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_CreateCubeTexture(p,a,b,c,d,e,f,g) (p)->lpVtbl->CreateCubeTexture(p,a,b,c,d,e,f,g)
#define IDirect3DDevice9Ex_CreateVertexBuffer(p,a,b,c,d,e,f) (p)->lpVtbl->CreateVertexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateIndexBuffer(p,a,b,c,d,e,f) (p)->lpVtbl->CreateIndexBuffer(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateRenderTarget(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateRenderTarget(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_UpdateSurface(p,a,b,c,d) (p)->lpVtbl->UpdateSurface(p,a,b,c,d)
#define IDirect3DDevice9Ex_UpdateTexture(p,a,b) (p)->lpVtbl->UpdateTexture(p,a,b)
#define IDirect3DDevice9Ex_GetRenderTargetData(p,a,b) (p)->lpVtbl->GetRenderTargetData(p,a,b)
#define IDirect3DDevice9Ex_GetFrontBufferData(p,a,b) (p)->lpVtbl->GetFrontBufferData(p,a,b)
#define IDirect3DDevice9Ex_StretchRect(p,a,b,c,d,e) (p)->lpVtbl->StretchRect(p,a,b,c,d,e)
#define IDirect3DDevice9Ex_ColorFill(p,a,b,c) (p)->lpVtbl->ColorFill(p,a,b,c)
#define IDirect3DDevice9Ex_CreateOffscreenPlainSurface(p,a,b,c,d,e,f) (p)->lpVtbl->CreateOffscreenPlainSurface(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_SetRenderTarget(p,a,b) (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice9Ex_GetRenderTarget(p,a,b) (p)->lpVtbl->GetRenderTarget(p,a,b)
#define IDirect3DDevice9Ex_SetDepthStencilSurface(p,a) (p)->lpVtbl->SetDepthStencilSurface(p,a)
#define IDirect3DDevice9Ex_GetDepthStencilSurface(p,a) (p)->lpVtbl->GetDepthStencilSurface(p,a)
#define IDirect3DDevice9Ex_BeginScene(p) (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice9Ex_EndScene(p) (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice9Ex_Clear(p,a,b,c,d,e,f) (p)->lpVtbl->Clear(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_SetTransform(p,a,b) (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice9Ex_GetTransform(p,a,b) (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice9Ex_MultiplyTransform(p,a,b) (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice9Ex_SetViewport(p,a) (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DDevice9Ex_GetViewport(p,a) (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DDevice9Ex_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DDevice9Ex_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DDevice9Ex_SetLight(p,a,b) (p)->lpVtbl->SetLight(p,a,b)
#define IDirect3DDevice9Ex_GetLight(p,a,b) (p)->lpVtbl->GetLight(p,a,b)
#define IDirect3DDevice9Ex_LightEnable(p,a,b) (p)->lpVtbl->LightEnable(p,a,b)
#define IDirect3DDevice9Ex_GetLightEnable(p,a,b) (p)->lpVtbl->GetLightEnable(p,a,b)
#define IDirect3DDevice9Ex_SetClipPlane(p,a,b) (p)->lpVtbl->SetClipPlane(p,a,b)
#define IDirect3DDevice9Ex_GetClipPlane(p,a,b) (p)->lpVtbl->GetClipPlane(p,a,b)
#define IDirect3DDevice9Ex_SetRenderState(p,a,b) (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice9Ex_GetRenderState(p,a,b) (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice9Ex_CreateStateBlock(p,a,b) (p)->lpVtbl->CreateStateBlock(p,a,b)
#define IDirect3DDevice9Ex_BeginStateBlock(p) (p)->lpVtbl->BeginStateBlock(p)
#define IDirect3DDevice9Ex_EndStateBlock(p,a) (p)->lpVtbl->EndStateBlock(p,a)
#define IDirect3DDevice9Ex_SetClipStatus(p,a) (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice9Ex_GetClipStatus(p,a) (p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice9Ex_GetTexture(p,a,b) (p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice9Ex_SetTexture(p,a,b) (p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice9Ex_GetTextureStageState(p,a,b,c) (p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice9Ex_SetTextureStageState(p,a,b,c) (p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice9Ex_GetSamplerState(p,a,b,c) (p)->lpVtbl->GetSamplerState(p,a,b,c)
#define IDirect3DDevice9Ex_SetSamplerState(p,a,b,c) (p)->lpVtbl->SetSamplerState(p,a,b,c)
#define IDirect3DDevice9Ex_ValidateDevice(p,a) (p)->lpVtbl->ValidateDevice(p,a)
#define IDirect3DDevice9Ex_SetPaletteEntries(p,a,b) (p)->lpVtbl->SetPaletteEntries(p,a,b)
#define IDirect3DDevice9Ex_GetPaletteEntries(p,a,b) (p)->lpVtbl->GetPaletteEntries(p,a,b)
#define IDirect3DDevice9Ex_SetCurrentTexturePalette(p,a) (p)->lpVtbl->SetCurrentTexturePalette(p,a)
#define IDirect3DDevice9Ex_GetCurrentTexturePalette(p,a) (p)->lpVtbl->GetCurrentTexturePalette(p,a)
#define IDirect3DDevice9Ex_SetScissorRect(p,a) (p)->lpVtbl->SetScissorRect(p,a)
#define IDirect3DDevice9Ex_GetScissorRect(p,a) (p)->lpVtbl->GetScissorRect(p,a)
#define IDirect3DDevice9Ex_SetSoftwareVertexProcessing(p,a) (p)->lpVtbl->SetSoftwareVertexProcessing(p,a)
#define IDirect3DDevice9Ex_GetSoftwareVertexProcessing(p) (p)->lpVtbl->GetSoftwareVertexProcessing(p)
#define IDirect3DDevice9Ex_SetNPatchMode(p,a) (p)->lpVtbl->SetNPatchMode(p,a)
#define IDirect3DDevice9Ex_GetNPatchMode(p) (p)->lpVtbl->GetNPatchMode(p)
#define IDirect3DDevice9Ex_DrawPrimitive(p,a,b,c) (p)->lpVtbl->DrawPrimitive(p,a,b,c)
#define IDirect3DDevice9Ex_DrawIndexedPrimitive(p,a,b,c,d,e,f) (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_DrawPrimitiveUP(p,a,b,c,d) (p)->lpVtbl->DrawPrimitiveUP(p,a,b,c,d)
#define IDirect3DDevice9Ex_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_ProcessVertices(p,a,b,c,d,e,f) (p)->lpVtbl->ProcessVertices(p,a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateVertexDeclaration(p,a,b) (p)->lpVtbl->CreateVertexDeclaration(p,a,b)
#define IDirect3DDevice9Ex_SetVertexDeclaration(p,a) (p)->lpVtbl->SetVertexDeclaration(p,a)
#define IDirect3DDevice9Ex_GetVertexDeclaration(p,a) (p)->lpVtbl->GetVertexDeclaration(p,a)
#define IDirect3DDevice9Ex_SetFVF(p,a) (p)->lpVtbl->SetFVF(p,a)
#define IDirect3DDevice9Ex_GetFVF(p,a) (p)->lpVtbl->GetFVF(p,a)
#define IDirect3DDevice9Ex_CreateVertexShader(p,a,b) (p)->lpVtbl->CreateVertexShader(p,a,b)
#define IDirect3DDevice9Ex_SetVertexShader(p,a) (p)->lpVtbl->SetVertexShader(p,a)
#define IDirect3DDevice9Ex_GetVertexShader(p,a) (p)->lpVtbl->GetVertexShader(p,a)
#define IDirect3DDevice9Ex_SetVertexShaderConstantF(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantF(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantF(p,a,b,c)
#define IDirect3DDevice9Ex_SetVertexShaderConstantI(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantI(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantI(p,a,b,c)
#define IDirect3DDevice9Ex_SetVertexShaderConstantB(p,a,b,c) (p)->lpVtbl->SetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantB(p,a,b,c) (p)->lpVtbl->GetVertexShaderConstantB(p,a,b,c)
#define IDirect3DDevice9Ex_SetStreamSource(p,a,b,c,d) (p)->lpVtbl->SetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9Ex_GetStreamSource(p,a,b,c,d) (p)->lpVtbl->GetStreamSource(p,a,b,c,d)
#define IDirect3DDevice9Ex_SetStreamSourceFreq(p,a,b) (p)->lpVtbl->SetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9Ex_GetStreamSourceFreq(p,a,b) (p)->lpVtbl->GetStreamSourceFreq(p,a,b)
#define IDirect3DDevice9Ex_SetIndices(p,a) (p)->lpVtbl->SetIndices(p,a)
#define IDirect3DDevice9Ex_GetIndices(p,a) (p)->lpVtbl->GetIndices(p,a)
#define IDirect3DDevice9Ex_CreatePixelShader(p,a,b) (p)->lpVtbl->CreatePixelShader(p,a,b)
#define IDirect3DDevice9Ex_SetPixelShader(p,a) (p)->lpVtbl->SetPixelShader(p,a)
#define IDirect3DDevice9Ex_GetPixelShader(p,a) (p)->lpVtbl->GetPixelShader(p,a)
#define IDirect3DDevice9Ex_SetPixelShaderConstantF(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantF(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantF(p,a,b,c)
#define IDirect3DDevice9Ex_SetPixelShaderConstantI(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantI(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantI(p,a,b,c)
#define IDirect3DDevice9Ex_SetPixelShaderConstantB(p,a,b,c) (p)->lpVtbl->SetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantB(p,a,b,c) (p)->lpVtbl->GetPixelShaderConstantB(p,a,b,c)
#define IDirect3DDevice9Ex_DrawRectPatch(p,a,b,c) (p)->lpVtbl->DrawRectPatch(p,a,b,c)
#define IDirect3DDevice9Ex_DrawTriPatch(p,a,b,c) (p)->lpVtbl->DrawTriPatch(p,a,b,c)
#define IDirect3DDevice9Ex_DeletePatch(p,a) (p)->lpVtbl->DeletePatch(p,a)
#define IDirect3DDevice9Ex_CreateQuery(p,a,b) (p)->lpVtbl->CreateQuery(p,a,b)
#define IDirect3DDevice9Ex_SetConvolutionMonoKernel(p,a,b,c,d) (p)->lpVtbl->SetConvolutionMonoKernel(p,a,b,c,d)
#define IDirect3DDevice9Ex_ComposeRects(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->ComposeRects(p,a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_PresentEx(p,a,b,c,d,e) (p)->lpVtbl->PresentEx(p,a,b,c,d,e)
#define IDirect3DDevice9Ex_GetGPUThreadPriority(p,a) (p)->lpVtbl->GetGPUThreadPriority(p,a)
#define IDirect3DDevice9Ex_SetGPUThreadPriority(p,a) (p)->lpVtbl->SetGPUThreadPriority(p,a)
#define IDirect3DDevice9Ex_WaitForVBlank(p,a) (p)->lpVtbl->WaitForVBlank(p,a)
#define IDirect3DDevice9Ex_CheckResourceResidency(p,a,b) (p)->lpVtbl->CheckResourceResidency(p,a,b)
#define IDirect3DDevice9Ex_SetMaximumFrameLatency(p,a) (p)->lpVtbl->SetMaximumFrameLatency(p,a)
#define IDirect3DDevice9Ex_GetMaximumFrameLatency(p,a) (p)->lpVtbl->GetMaximumFrameLatency(p,a)
#define IDirect3DDevice9Ex_CheckDeviceState(p,a) (p)->lpVtbl->CheckDeviceState(p,a)
#define IDirect3DDevice9Ex_CreateRenderTargetEx(p,a,b,c,d,e,f,g,h,i) (p)->lpVtbl->CreateRenderTargetEx(p,a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_CreateOffscreenPlainSurfaceEx(p,a,b,c,d,e,f,g) (p)->lpVtbl->CreateOffscreenPlainSurfaceEx(p,a,b,c,d,e,f,g)
#define IDirect3DDevice9Ex_CreateDepthStencilSurfaceEx(p,a,b,c,d,e,f,g,h,i) (p)->lpVtbl->CreateDepthStencilSurfaceEx(p,a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_ResetEx(p,a,b) (p)->lpVtbl->ResetEx(p,a,b)
#define IDirect3DDevice9Ex_GetDisplayModeEx(p,a,b,c) (p)->lpVtbl->GetDisplayModeEx(p,a,b,c)
#else
#define IDirect3DDevice9Ex_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice9Ex_AddRef(p) (p)->AddRef()
#define IDirect3DDevice9Ex_Release(p) (p)->Release()
#define IDirect3DDevice9Ex_TestCooperativeLevel(p) (p)->TestCooperativeLevel()
#define IDirect3DDevice9Ex_GetAvailableTextureMem(p) (p)->GetAvailableTextureMem()
#define IDirect3DDevice9Ex_EvictManagedResources(p) (p)->EvictManagedResources()
#define IDirect3DDevice9Ex_GetDirect3D(p,a) (p)->GetDirect3D(a)
#define IDirect3DDevice9Ex_GetDeviceCaps(p,a) (p)->GetDeviceCaps(a)
#define IDirect3DDevice9Ex_GetDisplayMode(p,a,b) (p)->GetDisplayMode(a,b)
#define IDirect3DDevice9Ex_GetCreationParameters(p,a) (p)->GetCreationParameters(a)
#define IDirect3DDevice9Ex_SetCursorProperties(p,a,b,c) (p)->SetCursorProperties(a,b,c)
#define IDirect3DDevice9Ex_SetCursorPosition(p,a,b,c) (p)->SetCursorPosition(a,b,c)
#define IDirect3DDevice9Ex_ShowCursor(p,a) (p)->ShowCursor(a)
#define IDirect3DDevice9Ex_CreateAdditionalSwapChain(p,a,b) (p)->CreateAdditionalSwapChain(a,b)
#define IDirect3DDevice9Ex_GetSwapChain(p,a,b) (p)->GetSwapChain(a,b)
#define IDirect3DDevice9Ex_GetNumberOfSwapChains(p) (p)->GetNumberOfSwapChains()
#define IDirect3DDevice9Ex_Reset(p,a) (p)->Reset(a)
#define IDirect3DDevice9Ex_Present(p,a,b,c,d) (p)->Present(a,b,c,d)
#define IDirect3DDevice9Ex_GetBackBuffer(p,a,b,c,d) (p)->GetBackBuffer(a,b,c,d)
#define IDirect3DDevice9Ex_GetRasterStatus(p,a,b) (p)->GetRasterStatus(a,b)
#define IDirect3DDevice9Ex_SetDialogBoxMode(p,a) (p)->SetDialogBoxMode(a)
#define IDirect3DDevice9Ex_SetGammaRamp(p,a,b,c) (p)->SetGammaRamp(a,b,c)
#define IDirect3DDevice9Ex_GetGammaRamp(p,a,b) (p)->GetGammaRamp(a,b)
#define IDirect3DDevice9Ex_CreateTexture(p,a,b,c,d,e,f,g,h) (p)->CreateTexture(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_CreateVolumeTexture(p,a,b,c,d,e,f,g,h,i) (p)->CreateVolumeTexture(a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_CreateCubeTexture(p,a,b,c,d,e,f,g) (p)->CreateCubeTexture(a,b,c,d,e,f,g)
#define IDirect3DDevice9Ex_CreateVertexBuffer(p,a,b,c,d,e,f) (p)->CreateVertexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateIndexBuffer(p,a,b,c,d,e,f) (p)->CreateIndexBuffer(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateRenderTarget(p,a,b,c,d,e,f,g,h) (p)->CreateRenderTarget(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_CreateDepthStencilSurface(p,a,b,c,d,e,f,g,h) (p)->CreateDepthStencilSurface(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_UpdateSurface(p,a,b,c,d) (p)->UpdateSurface(a,b,c,d)
#define IDirect3DDevice9Ex_UpdateTexture(p,a,b) (p)->UpdateTexture(a,b)
#define IDirect3DDevice9Ex_GetRenderTargetData(p,a,b) (p)->GetRenderTargetData(a,b)
#define IDirect3DDevice9Ex_GetFrontBufferData(p,a,b) (p)->GetFrontBufferData(a,b)
#define IDirect3DDevice9Ex_StretchRect(p,a,b,c,d,e) (p)->StretchRect(a,b,c,d,e)
#define IDirect3DDevice9Ex_ColorFill(p,a,b,c) (p)->ColorFill(a,b,c)
#define IDirect3DDevice9Ex_CreateOffscreenPlainSurface(p,a,b,c,d,e,f) (p)->CreateOffscreenPlainSurface(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_SetRenderTarget(p,a,b) (p)->SetRenderTarget(a,b)
#define IDirect3DDevice9Ex_GetRenderTarget(p,a,b) (p)->GetRenderTarget(a,b)
#define IDirect3DDevice9Ex_SetDepthStencilSurface(p,a) (p)->SetDepthStencilSurface(a)
#define IDirect3DDevice9Ex_GetDepthStencilSurface(p,a) (p)->GetDepthStencilSurface(a)
#define IDirect3DDevice9Ex_BeginScene(p) (p)->BeginScene()
#define IDirect3DDevice9Ex_EndScene(p) (p)->EndScene()
#define IDirect3DDevice9Ex_Clear(p,a,b,c,d,e,f) (p)->Clear(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_SetTransform(p,a,b) (p)->SetTransform(a,b)
#define IDirect3DDevice9Ex_GetTransform(p,a,b) (p)->GetTransform(a,b)
#define IDirect3DDevice9Ex_MultiplyTransform(p,a,b) (p)->MultiplyTransform(a,b)
#define IDirect3DDevice9Ex_SetViewport(p,a) (p)->SetViewport(a)
#define IDirect3DDevice9Ex_GetViewport(p,a) (p)->GetViewport(a)
#define IDirect3DDevice9Ex_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DDevice9Ex_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DDevice9Ex_SetLight(p,a,b) (p)->SetLight(a,b)
#define IDirect3DDevice9Ex_GetLight(p,a,b) (p)->GetLight(a,b)
#define IDirect3DDevice9Ex_LightEnable(p,a,b) (p)->LightEnable(a,b)
#define IDirect3DDevice9Ex_GetLightEnable(p,a,b) (p)->GetLightEnable(a,b)
#define IDirect3DDevice9Ex_SetClipPlane(p,a,b) (p)->SetClipPlane(a,b)
#define IDirect3DDevice9Ex_GetClipPlane(p,a,b) (p)->GetClipPlane(a,b)
#define IDirect3DDevice9Ex_SetRenderState(p,a,b) (p)->SetRenderState(a,b)
#define IDirect3DDevice9Ex_GetRenderState(p,a,b) (p)->GetRenderState(a,b)
#define IDirect3DDevice9Ex_CreateStateBlock(p,a,b) (p)->CreateStateBlock(a,b)
#define IDirect3DDevice9Ex_BeginStateBlock(p) (p)->BeginStateBlock()
#define IDirect3DDevice9Ex_EndStateBlock(p,a) (p)->EndStateBlock(a)
#define IDirect3DDevice9Ex_SetClipStatus(p,a) (p)->SetClipStatus(a)
#define IDirect3DDevice9Ex_GetClipStatus(p,a) (p)->GetClipStatus(a)
#define IDirect3DDevice9Ex_GetTexture(p,a,b) (p)->GetTexture(a,b)
#define IDirect3DDevice9Ex_SetTexture(p,a,b) (p)->SetTexture(a,b)
#define IDirect3DDevice9Ex_GetTextureStageState(p,a,b,c) (p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice9Ex_SetTextureStageState(p,a,b,c) (p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice9Ex_GetSamplerState(p,a,b,c) (p)->GetSamplerState(a,b,c)
#define IDirect3DDevice9Ex_SetSamplerState(p,a,b,c) (p)->SetSamplerState(a,b,c)
#define IDirect3DDevice9Ex_ValidateDevice(p,a) (p)->ValidateDevice(a)
#define IDirect3DDevice9Ex_SetPaletteEntries(p,a,b) (p)->SetPaletteEntries(a,b)
#define IDirect3DDevice9Ex_GetPaletteEntries(p,a,b) (p)->GetPaletteEntries(a,b)
#define IDirect3DDevice9Ex_SetCurrentTexturePalette(p,a) (p)->SetCurrentTexturePalette(a)
#define IDirect3DDevice9Ex_GetCurrentTexturePalette(p,a) (p)->GetCurrentTexturePalette(a)
#define IDirect3DDevice9Ex_SetScissorRect(p,a) (p)->SetScissorRect(a)
#define IDirect3DDevice9Ex_GetScissorRect(p,a) (p)->GetScissorRect(a)
#define IDirect3DDevice9Ex_SetSoftwareVertexProcessing(p,a) (p)->SetSoftwareVertexProcessing(a)
#define IDirect3DDevice9Ex_GetSoftwareVertexProcessing(p) (p)->GetSoftwareVertexProcessing()
#define IDirect3DDevice9Ex_SetNPatchMode(p,a) (p)->SetNPatchMode(a)
#define IDirect3DDevice9Ex_GetNPatchMode(p) (p)->GetNPatchMode()
#define IDirect3DDevice9Ex_DrawPrimitive(p,a,b,c) (p)->DrawPrimitive(a,b,c)
#define IDirect3DDevice9Ex_DrawIndexedPrimitive(p,a,b,c,d,e,f) (p)->DrawIndexedPrimitive(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_DrawPrimitiveUP(p,a,b,c,d) (p)->DrawPrimitiveUP(a,b,c,d)
#define IDirect3DDevice9Ex_DrawIndexedPrimitiveUP(p,a,b,c,d,e,f,g,h) (p)->DrawIndexedPrimitiveUP(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_ProcessVertices(p,a,b,c,d,e,f) (p)->ProcessVertices(a,b,c,d,e,f)
#define IDirect3DDevice9Ex_CreateVertexDeclaration(p,a,b) (p)->CreateVertexDeclaration(a,b)
#define IDirect3DDevice9Ex_SetVertexDeclaration(p,a) (p)->SetVertexDeclaration(a)
#define IDirect3DDevice9Ex_GetVertexDeclaration(p,a) (p)->GetVertexDeclaration(a)
#define IDirect3DDevice9Ex_SetFVF(p,a) (p)->SetFVF(a)
#define IDirect3DDevice9Ex_GetFVF(p,a) (p)->GetFVF(a)
#define IDirect3DDevice9Ex_CreateVertexShader(p,a,b) (p)->CreateVertexShader(a,b)
#define IDirect3DDevice9Ex_SetVertexShader(p,a) (p)->SetVertexShader(a)
#define IDirect3DDevice9Ex_GetVertexShader(p,a) (p)->GetVertexShader(a)
#define IDirect3DDevice9Ex_SetVertexShaderConstantF(p,a,b,c) (p)->SetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantF(p,a,b,c) (p)->GetVertexShaderConstantF(a,b,c)
#define IDirect3DDevice9Ex_SetVertexShaderConstantI(p,a,b,c) (p)->SetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantI(p,a,b,c) (p)->GetVertexShaderConstantI(a,b,c)
#define IDirect3DDevice9Ex_SetVertexShaderConstantB(p,a,b,c) (p)->SetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9Ex_GetVertexShaderConstantB(p,a,b,c) (p)->GetVertexShaderConstantB(a,b,c)
#define IDirect3DDevice9Ex_SetStreamSource(p,a,b,c,d) (p)->SetStreamSource(a,b,c,d)
#define IDirect3DDevice9Ex_GetStreamSource(p,a,b,c,d) (p)->GetStreamSource(a,b,c,d)
#define IDirect3DDevice9Ex_SetStreamSourceFreq(p,a,b) (p)->SetStreamSourceFreq(a,b)
#define IDirect3DDevice9Ex_GetStreamSourceFreq(p,a,b) (p)->GetStreamSourceFreq(a,b)
#define IDirect3DDevice9Ex_SetIndices(p,a) (p)->SetIndices(a)
#define IDirect3DDevice9Ex_GetIndices(p,a) (p)->GetIndices(a)
#define IDirect3DDevice9Ex_CreatePixelShader(p,a,b) (p)->CreatePixelShader(a,b)
#define IDirect3DDevice9Ex_SetPixelShader(p,a) (p)->SetPixelShader(a)
#define IDirect3DDevice9Ex_GetPixelShader(p,a) (p)->GetPixelShader(a)
#define IDirect3DDevice9Ex_SetPixelShaderConstantF(p,a,b,c) (p)->SetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantF(p,a,b,c) (p)->GetPixelShaderConstantF(a,b,c)
#define IDirect3DDevice9Ex_SetPixelShaderConstantI(p,a,b,c) (p)->SetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantI(p,a,b,c) (p)->GetPixelShaderConstantI(a,b,c)
#define IDirect3DDevice9Ex_SetPixelShaderConstantB(p,a,b,c) (p)->SetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9Ex_GetPixelShaderConstantB(p,a,b,c) (p)->GetPixelShaderConstantB(a,b,c)
#define IDirect3DDevice9Ex_DrawRectPatch(p,a,b,c) (p)->DrawRectPatch(a,b,c)
#define IDirect3DDevice9Ex_DrawTriPatch(p,a,b,c) (p)->DrawTriPatch(a,b,c)
#define IDirect3DDevice9Ex_DeletePatch(p,a) (p)->DeletePatch(a)
#define IDirect3DDevice9Ex_CreateQuery(p,a,b) (p)->CreateQuery(a,b)
#define IDirect3DDevice9Ex_SetConvolutionMonoKernel(p,a,b,c,d) (p)->SetConvolutionMonoKernel(a,b,c,d)
#define IDirect3DDevice9Ex_ComposeRects(p,a,b,c,d,e,f,g,h) (p)->ComposeRects(a,b,c,d,e,f,g,h)
#define IDirect3DDevice9Ex_PresentEx(p,a,b,c,d,e) (p)->PresentEx(a,b,c,d,e)
#define IDirect3DDevice9Ex_GetGPUThreadPriority(p,a) (p)->GetGPUThreadPriority(a)
#define IDirect3DDevice9Ex_SetGPUThreadPriority(p,a) (p)->SetGPUThreadPriority(a)
#define IDirect3DDevice9Ex_WaitForVBlank(p,a) (p)->WaitForVBlank(a)
#define IDirect3DDevice9Ex_CheckResourceResidency(p,a,b) (p)->CheckResourceResidency(a,b)
#define IDirect3DDevice9Ex_SetMaximumFrameLatency(p,a) (p)->SetMaximumFrameLatency(a)
#define IDirect3DDevice9Ex_GetMaximumFrameLatency(p,a) (p)->GetMaximumFrameLatency(a)
#define IDirect3DDevice9Ex_CheckDeviceState(p,a) (p)->CheckDeviceState(a)
#define IDirect3DDevice9Ex_CreateRenderTargetEx(p,a,b,c,d,e,f,g,h,i) (p)->CreateRenderTargetEx(a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_CreateOffscreenPlainSurfaceEx(p,a,b,c,d,e,f,g) (p)->CreateOffscreenPlainSurfaceEx(a,b,c,d,e,f,g)
#define IDirect3DDevice9Ex_CreateDepthStencilSurfaceEx(p,a,b,c,d,e,f,g,h,i) (p)->CreateDepthStencilSurfaceEx(a,b,c,d,e,f,g,h,i)
#define IDirect3DDevice9Ex_ResetEx(p,a,b) (p)->ResetEx(a,b)
#define IDirect3DDevice9Ex_GetDisplayModeEx(p,a,b,c) (p)->GetDisplayModeEx(a,b,c)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DSwapChain9Ex

DECLARE_INTERFACE_(IDirect3DSwapChain9Ex, IDirect3DSwapChain9)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DSwapChain9 methods ***/
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) PURE;
    STDMETHOD(GetFrontBufferData)(THIS_ IDirect3DSurface9* pDestSurface) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    STDMETHOD(GetPresentParameters)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD(GetLastPresentCount)(THIS_ UINT* pLastPresentCount) PURE;
    STDMETHOD(GetPresentStats)(THIS_ D3DPRESENTSTATS* pPresentationStatistics) PURE;
    STDMETHOD(GetDisplayModeEx)(THIS_ D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation) PURE;
};
    
typedef struct IDirect3DSwapChain9Ex *LPDIRECT3DSWAPCHAIN9EX, *PDIRECT3DSWAPCHAIN9EX;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DSwapChain9Ex_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DSwapChain9Ex_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DSwapChain9Ex_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DSwapChain9Ex_Present(p,a,b,c,d,e) (p)->lpVtbl->Present(p,a,b,c,d,e)
#define IDirect3DSwapChain9Ex_GetFrontBufferData(p,a) (p)->lpVtbl->GetFrontBufferData(p,a)
#define IDirect3DSwapChain9Ex_GetBackBuffer(p,a,b,c) (p)->lpVtbl->GetBackBuffer(p,a,b,c)
#define IDirect3DSwapChain9Ex_GetRasterStatus(p,a) (p)->lpVtbl->GetRasterStatus(p,a)
#define IDirect3DSwapChain9Ex_GetDisplayMode(p,a) (p)->lpVtbl->GetDisplayMode(p,a)
#define IDirect3DSwapChain9Ex_GetDevice(p,a) (p)->lpVtbl->GetDevice(p,a)
#define IDirect3DSwapChain9Ex_GetPresentParameters(p,a) (p)->lpVtbl->GetPresentParameters(p,a)
#define IDirect3DSwapChain9Ex_GetLastPresentCount(p,a) (p)->lpVtbl->GetLastPresentCount(p,a)
#define IDirect3DSwapChain9Ex_GetPresentStats(p,a) (p)->lpVtbl->GetPresentStats(p,a)
#define IDirect3DSwapChain9Ex_GetDisplayModeEx(p,a,b) (p)->lpVtbl->GetDisplayModeEx(p,a,b)
#else
#define IDirect3DSwapChain9Ex_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DSwapChain9Ex_AddRef(p) (p)->AddRef()
#define IDirect3DSwapChain9Ex_Release(p) (p)->Release()
#define IDirect3DSwapChain9Ex_Present(p,a,b,c,d,e) (p)->Present(a,b,c,d,e)
#define IDirect3DSwapChain9Ex_GetFrontBufferData(p,a) (p)->GetFrontBufferData(a)
#define IDirect3DSwapChain9Ex_GetBackBuffer(p,a,b,c) (p)->GetBackBuffer(a,b,c)
#define IDirect3DSwapChain9Ex_GetRasterStatus(p,a) (p)->GetRasterStatus(a)
#define IDirect3DSwapChain9Ex_GetDisplayMode(p,a) (p)->GetDisplayMode(a)
#define IDirect3DSwapChain9Ex_GetDevice(p,a) (p)->GetDevice(a)
#define IDirect3DSwapChain9Ex_GetPresentParameters(p,a) (p)->GetPresentParameters(a)
#define IDirect3DSwapChain9Ex_GetLastPresentCount(p,a) (p)->GetLastPresentCount(a)
#define IDirect3DSwapChain9Ex_GetPresentStats(p,a) (p)->GetPresentStats(a)
#define IDirect3DSwapChain9Ex_GetDisplayModeEx(p,a,b) (p)->GetDisplayModeEx(a,b)
#endif

#endif // !D3D_DISABLE_9EX
/* -- D3D9Ex only */



/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)



#undef INTERFACE
#define INTERFACE IDirect3D9ExOverlayExtension

DECLARE_INTERFACE_(IDirect3D9ExOverlayExtension, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3D9ExOverlayExtension methods ***/
    STDMETHOD(CheckDeviceOverlayType)(THIS_ UINT Adapter,D3DDEVTYPE DevType,UINT OverlayWidth,UINT OverlayHeight,D3DFORMAT OverlayFormat,D3DDISPLAYMODEEX* pDisplayMode,D3DDISPLAYROTATION DisplayRotation,D3DOVERLAYCAPS* pOverlayCaps) PURE;
};
    
typedef struct IDirect3D9ExOverlayExtension *LPDIRECT3D9EXOVERLAYEXTENSION, *PDIRECT3D9EXOVERLAYEXTENSION;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3D9ExOverlayExtension_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D9ExOverlayExtension_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3D9ExOverlayExtension_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3D9ExOverlayExtension_CheckDeviceOverlayType(p,a,b,c,d,e,f,g,h) (p)->lpVtbl->CheckDeviceOverlayType(p,a,b,c,d,e,f,g,h)
#else
#define IDirect3D9ExOverlayExtension_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D9ExOverlayExtension_AddRef(p) (p)->AddRef()
#define IDirect3D9ExOverlayExtension_Release(p) (p)->Release()
#define IDirect3D9ExOverlayExtension_CheckDeviceOverlayType(p,a,b,c,d,e,f,g,h) (p)->CheckDeviceOverlayType(a,b,c,d,e,f,g,h)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DDevice9Video

DECLARE_INTERFACE_(IDirect3DDevice9Video, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DDevice9Video methods ***/
    STDMETHOD(GetContentProtectionCaps)(THIS_ CONST GUID* pCryptoType,CONST GUID* pDecodeProfile,D3DCONTENTPROTECTIONCAPS* pCaps) PURE;
    STDMETHOD(CreateAuthenticatedChannel)(THIS_ D3DAUTHENTICATEDCHANNELTYPE ChannelType,IDirect3DAuthenticatedChannel9** ppAuthenticatedChannel,HANDLE* pChannelHandle) PURE;
    STDMETHOD(CreateCryptoSession)(THIS_ CONST GUID* pCryptoType,CONST GUID* pDecodeProfile,IDirect3DCryptoSession9** ppCryptoSession,HANDLE* pCryptoHandle) PURE;
};
    
typedef struct IDirect3DDevice9Video *LPDIRECT3DDEVICE9VIDEO, *PDIRECT3DDEVICE9VIDEO;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DDevice9Video_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice9Video_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice9Video_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DDevice9Video_GetContentProtectionCaps(p,a,b,c) (p)->lpVtbl->GetContentProtectionCaps(p,a,b,c)
#define IDirect3DDevice9Video_CreateAuthenticatedChannel(p,a,b,c) (p)->lpVtbl->CreateAuthenticatedChannel(p,a,b,c)
#define IDirect3DDevice9Video_CreateCryptoSession(p,a,b,c,d) (p)->lpVtbl->CreateCryptoSession(p,a,b,c,d)
#else
#define IDirect3DDevice9Video_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice9Video_AddRef(p) (p)->AddRef()
#define IDirect3DDevice9Video_Release(p) (p)->Release()
#define IDirect3DDevice9Video_GetContentProtectionCaps(p,a,b,c) (p)->GetContentProtectionCaps(a,b,c)
#define IDirect3DDevice9Video_CreateAuthenticatedChannel(p,a,b,c) (p)->CreateAuthenticatedChannel(a,b,c)
#define IDirect3DDevice9Video_CreateCryptoSession(p,a,b,c,d) (p)->CreateCryptoSession(a,b,c,d)
#endif




#undef INTERFACE
#define INTERFACE IDirect3DAuthenticatedChannel9

DECLARE_INTERFACE_(IDirect3DAuthenticatedChannel9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DAuthenticatedChannel9 methods ***/
    STDMETHOD(GetCertificateSize)(THIS_ UINT* pCertificateSize) PURE;
    STDMETHOD(GetCertificate)(THIS_ UINT CertifacteSize,BYTE* ppCertificate) PURE;
    STDMETHOD(NegotiateKeyExchange)(THIS_ UINT DataSize,VOID* pData) PURE;
    STDMETHOD(Query)(THIS_ UINT InputSize,CONST VOID* pInput,UINT OutputSize,VOID* pOutput) PURE;
    STDMETHOD(Configure)(THIS_ UINT InputSize,CONST VOID* pInput,D3DAUTHENTICATEDCHANNEL_CONFIGURE_OUTPUT* pOutput) PURE;
};
    
typedef struct IDirect3DAuthenticatedChannel9 *LPDIRECT3DAUTHENTICATEDCHANNEL9, *PDIRECT3DAUTHENTICATEDCHANNEL9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DAuthenticatedChannel9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DAuthenticatedChannel9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DAuthenticatedChannel9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DAuthenticatedChannel9_GetCertificateSize(p,a) (p)->lpVtbl->GetCertificateSize(p,a)
#define IDirect3DAuthenticatedChannel9_GetCertificate(p,a,b) (p)->lpVtbl->GetCertificate(p,a,b)
#define IDirect3DAuthenticatedChannel9_NegotiateKeyExchange(p,a,b) (p)->lpVtbl->NegotiateKeyExchange(p,a,b)
#define IDirect3DAuthenticatedChannel9_Query(p,a,b,c,d) (p)->lpVtbl->Query(p,a,b,c,d)
#define IDirect3DAuthenticatedChannel9_Configure(p,a,b,c) (p)->lpVtbl->Configure(p,a,b,c)
#else
#define IDirect3DAuthenticatedChannel9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DAuthenticatedChannel9_AddRef(p) (p)->AddRef()
#define IDirect3DAuthenticatedChannel9_Release(p) (p)->Release()
#define IDirect3DAuthenticatedChannel9_GetCertificateSize(p,a) (p)->GetCertificateSize(a)
#define IDirect3DAuthenticatedChannel9_GetCertificate(p,a,b) (p)->GetCertificate(a,b)
#define IDirect3DAuthenticatedChannel9_NegotiateKeyExchange(p,a,b) (p)->NegotiateKeyExchange(a,b)
#define IDirect3DAuthenticatedChannel9_Query(p,a,b,c,d) (p)->Query(a,b,c,d)
#define IDirect3DAuthenticatedChannel9_Configure(p,a,b,c) (p)->Configure(a,b,c)
#endif



#undef INTERFACE
#define INTERFACE IDirect3DCryptoSession9

DECLARE_INTERFACE_(IDirect3DCryptoSession9, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DCryptoSession9 methods ***/
    STDMETHOD(GetCertificateSize)(THIS_ UINT* pCertificateSize) PURE;
    STDMETHOD(GetCertificate)(THIS_ UINT CertifacteSize,BYTE* ppCertificate) PURE;
    STDMETHOD(NegotiateKeyExchange)(THIS_ UINT DataSize,VOID* pData) PURE;
    STDMETHOD(EncryptionBlt)(THIS_ IDirect3DSurface9* pSrcSurface,IDirect3DSurface9* pDstSurface,UINT DstSurfaceSize,VOID* pIV) PURE;
    STDMETHOD(DecryptionBlt)(THIS_ IDirect3DSurface9* pSrcSurface,IDirect3DSurface9* pDstSurface,UINT SrcSurfaceSize,D3DENCRYPTED_BLOCK_INFO* pEncryptedBlockInfo,VOID* pContentKey,VOID* pIV) PURE;
    STDMETHOD(GetSurfacePitch)(THIS_ IDirect3DSurface9* pSrcSurface,UINT* pSurfacePitch) PURE;
    STDMETHOD(StartSessionKeyRefresh)(THIS_ VOID* pRandomNumber,UINT RandomNumberSize) PURE;
    STDMETHOD(FinishSessionKeyRefresh)(THIS) PURE;
    STDMETHOD(GetEncryptionBltKey)(THIS_ VOID* pReadbackKey,UINT KeySize) PURE;
};
    
typedef struct IDirect3DCryptoSession9 *LPDIRECT3DCRYPTOSESSION9, *PDIRECT3DCRYPTOSESSION9;

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IDirect3DCryptoSession9_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DCryptoSession9_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirect3DCryptoSession9_Release(p) (p)->lpVtbl->Release(p)
#define IDirect3DCryptoSession9_GetCertificateSize(p,a) (p)->lpVtbl->GetCertificateSize(p,a)
#define IDirect3DCryptoSession9_GetCertificate(p,a,b) (p)->lpVtbl->GetCertificate(p,a,b)
#define IDirect3DCryptoSession9_NegotiateKeyExchange(p,a,b) (p)->lpVtbl->NegotiateKeyExchange(p,a,b)
#define IDirect3DCryptoSession9_EncryptionBlt(p,a,b,c,d) (p)->lpVtbl->EncryptionBlt(p,a,b,c,d)
#define IDirect3DCryptoSession9_DecryptionBlt(p,a,b,c,d,e,f) (p)->lpVtbl->DecryptionBlt(p,a,b,c,d,e,f)
#define IDirect3DCryptoSession9_GetSurfacePitch(p,a,b) (p)->lpVtbl->GetSurfacePitch(p,a,b)
#define IDirect3DCryptoSession9_StartSessionKeyRefresh(p,a,b) (p)->lpVtbl->StartSessionKeyRefresh(p,a,b)
#define IDirect3DCryptoSession9_FinishSessionKeyRefresh(p) (p)->lpVtbl->FinishSessionKeyRefresh(p)
#define IDirect3DCryptoSession9_GetEncryptionBltKey(p,a,b) (p)->lpVtbl->GetEncryptionBltKey(p,a,b)
#else
#define IDirect3DCryptoSession9_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DCryptoSession9_AddRef(p) (p)->AddRef()
#define IDirect3DCryptoSession9_Release(p) (p)->Release()
#define IDirect3DCryptoSession9_GetCertificateSize(p,a) (p)->GetCertificateSize(a)
#define IDirect3DCryptoSession9_GetCertificate(p,a,b) (p)->GetCertificate(a,b)
#define IDirect3DCryptoSession9_NegotiateKeyExchange(p,a,b) (p)->NegotiateKeyExchange(a,b)
#define IDirect3DCryptoSession9_EncryptionBlt(p,a,b,c,d) (p)->EncryptionBlt(a,b,c,d)
#define IDirect3DCryptoSession9_DecryptionBlt(p,a,b,c,d,e,f) (p)->DecryptionBlt(a,b,c,d,e,f)
#define IDirect3DCryptoSession9_GetSurfacePitch(p,a,b) (p)->GetSurfacePitch(a,b)
#define IDirect3DCryptoSession9_StartSessionKeyRefresh(p,a,b) (p)->StartSessionKeyRefresh(a,b)
#define IDirect3DCryptoSession9_FinishSessionKeyRefresh(p) (p)->FinishSessionKeyRefresh()
#define IDirect3DCryptoSession9_GetEncryptionBltKey(p,a,b) (p)->GetEncryptionBltKey(a,b)
#endif

/* -- D3D9Ex only */
#endif // !D3D_DISABLE_9EX


#ifdef __cplusplus
};
#endif


#endif /* (DIRECT3D_VERSION >= 0x0900) */
#endif /* _D3D_H_ */

