/*-------------------------------------------------------------------------------------
 *
 * Copyright (c) Microsoft Corporation
 *
 *-------------------------------------------------------------------------------------*/


/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
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

#ifndef __d3d12_1_h__
#define __d3d12_1_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ID3D12CryptoSession_FWD_DEFINED__
#define __ID3D12CryptoSession_FWD_DEFINED__
typedef interface ID3D12CryptoSession ID3D12CryptoSession;

#endif 	/* __ID3D12CryptoSession_FWD_DEFINED__ */


#ifndef __ID3D12CryptoSessionPolicy_FWD_DEFINED__
#define __ID3D12CryptoSessionPolicy_FWD_DEFINED__
typedef interface ID3D12CryptoSessionPolicy ID3D12CryptoSessionPolicy;

#endif 	/* __ID3D12CryptoSessionPolicy_FWD_DEFINED__ */


#ifndef __ID3D12ContentProtectionDevice_FWD_DEFINED__
#define __ID3D12ContentProtectionDevice_FWD_DEFINED__
typedef interface ID3D12ContentProtectionDevice ID3D12ContentProtectionDevice;

#endif 	/* __ID3D12ContentProtectionDevice_FWD_DEFINED__ */


#ifndef __ID3D12VideoDecodeCommandList2_FWD_DEFINED__
#define __ID3D12VideoDecodeCommandList2_FWD_DEFINED__
typedef interface ID3D12VideoDecodeCommandList2 ID3D12VideoDecodeCommandList2;

#endif 	/* __ID3D12VideoDecodeCommandList2_FWD_DEFINED__ */


#ifndef __ID3D12VideoProcessCommandList2_FWD_DEFINED__
#define __ID3D12VideoProcessCommandList2_FWD_DEFINED__
typedef interface ID3D12VideoProcessCommandList2 ID3D12VideoProcessCommandList2;

#endif 	/* __ID3D12VideoProcessCommandList2_FWD_DEFINED__ */


#ifndef __ID3D12StateObjectPrototype_FWD_DEFINED__
#define __ID3D12StateObjectPrototype_FWD_DEFINED__
typedef interface ID3D12StateObjectPrototype ID3D12StateObjectPrototype;

#endif 	/* __ID3D12StateObjectPrototype_FWD_DEFINED__ */


#ifndef __ID3D12StateObjectPropertiesPrototype_FWD_DEFINED__
#define __ID3D12StateObjectPropertiesPrototype_FWD_DEFINED__
typedef interface ID3D12StateObjectPropertiesPrototype ID3D12StateObjectPropertiesPrototype;

#endif 	/* __ID3D12StateObjectPropertiesPrototype_FWD_DEFINED__ */


#ifndef __ID3D12DeviceRaytracingPrototype_FWD_DEFINED__
#define __ID3D12DeviceRaytracingPrototype_FWD_DEFINED__
typedef interface ID3D12DeviceRaytracingPrototype ID3D12DeviceRaytracingPrototype;

#endif 	/* __ID3D12DeviceRaytracingPrototype_FWD_DEFINED__ */


#ifndef __ID3D12CommandListRaytracingPrototype_FWD_DEFINED__
#define __ID3D12CommandListRaytracingPrototype_FWD_DEFINED__
typedef interface ID3D12CommandListRaytracingPrototype ID3D12CommandListRaytracingPrototype;

#endif 	/* __ID3D12CommandListRaytracingPrototype_FWD_DEFINED__ */


#ifndef __ID3D12DeviceMetaCommand_FWD_DEFINED__
#define __ID3D12DeviceMetaCommand_FWD_DEFINED__
typedef interface ID3D12DeviceMetaCommand ID3D12DeviceMetaCommand;

#endif 	/* __ID3D12DeviceMetaCommand_FWD_DEFINED__ */


#ifndef __ID3D12MetaCommand_FWD_DEFINED__
#define __ID3D12MetaCommand_FWD_DEFINED__
typedef interface ID3D12MetaCommand ID3D12MetaCommand;

#endif 	/* __ID3D12MetaCommand_FWD_DEFINED__ */


#ifndef __ID3D12CommandListMetaCommand_FWD_DEFINED__
#define __ID3D12CommandListMetaCommand_FWD_DEFINED__
typedef interface ID3D12CommandListMetaCommand ID3D12CommandListMetaCommand;

#endif 	/* __ID3D12CommandListMetaCommand_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgicommon.h"
#include "d3dcommon.h"
#include "d3d12.h"
#include "d3d12video.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_d3d12_1_0000_0000 */
/* [local] */ 

#include <winapifamily.h>
// BK - pragma region App Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#define D3D12_FEATURE_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEMES       static_cast<D3D12_FEATURE_VIDEO>(4)
#define D3D12_FEATURE_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEME_COUNT  static_cast<D3D12_FEATURE_VIDEO>(12)
#define D3D12_FEATURE_VIDEO_CRYPTO_SESSION_SUPPORT                    static_cast<D3D12_FEATURE_VIDEO>(13)
#define D3D12_FEATURE_VIDEO_CONTENT_PROTECTION_SYSTEM_COUNT           static_cast<D3D12_FEATURE_VIDEO>(14)
#define D3D12_FEATURE_VIDEO_CONTENT_PROTECTION_SYSTEM_SUPPORT         static_cast<D3D12_FEATURE_VIDEO>(15)
#define D3D12_FEATURE_VIDEO_CRYPTO_SESSION_TRANSFORM_SUPPORT          static_cast<D3D12_FEATURE_VIDEO>(16)
#define D3D12_BITSTREAM_ENCRYPTION_TYPE_CENC_AES_CTR_128              static_cast<D3D12_BITSTREAM_ENCRYPTION_TYPE>(1)
typedef struct D3D12_FEATURE_DATA_VIDEO_CONTENT_PROTECTION_SYSTEM_COUNT
    {
    UINT NodeIndex;
    UINT ContentProtectionSystemCount;
    } 	D3D12_FEATURE_DATA_VIDEO_CONTENT_PROTECTION_SYSTEM_COUNT;

typedef struct D3D12_FEATURE_DATA_VIDEO_CONTENT_PROTECTION_SYSTEM_SUPPORT
    {
    UINT NodeIndex;
    UINT ContentProtectionSystemCount;
    GUID *pContentProtectionSystems;
    } 	D3D12_FEATURE_DATA_VIDEO_CONTENT_PROTECTION_SYSTEM_SUPPORT;

typedef 
enum D3D12_CRYPTO_SESSION_SUPPORT_FLAGS
    {
        D3D12_CRYPTO_SESSION_SUPPORT_FLAG_NONE	= 0,
        D3D12_CRYPTO_SESSION_SUPPORT_FLAG_SUPPORTED	= 0x1,
        D3D12_CRYPTO_SESSION_SUPPORT_FLAG_HEADER_DECRYPTION_REQUIRED	= 0x2,
        D3D12_CRYPTO_SESSION_SUPPORT_FLAG_INDEPENDENT_DECRYPTION_REQUIRED	= 0x4,
        D3D12_CRYPTO_SESSION_SUPPORT_FLAG_TRANSCRYPTION_REQUIRED	= 0x8
    } 	D3D12_CRYPTO_SESSION_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_CRYPTO_SESSION_SUPPORT_FLAGS );
typedef 
enum D3D12_CRYPTO_SESSION_FLAGS
    {
        D3D12_CRYPTO_SESSION_FLAG_NONE	= 0,
        D3D12_CRYPTO_SESSION_FLAG_HARDWARE	= 0x1
    } 	D3D12_CRYPTO_SESSION_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_CRYPTO_SESSION_FLAGS );
typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEME_COUNT
    {
    UINT NodeIndex;
    GUID DecodeProfile;
    UINT EncryptionSchemeCount;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEME_COUNT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEMES
    {
    UINT NodeIndex;
    GUID DecodeProfile;
    UINT EncryptionSchemeCount;
    _Field_size_full_(EncryptionSchemeCount)  D3D12_BITSTREAM_ENCRYPTION_TYPE *pEncryptionSchemes;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_BITSTREAM_ENCRYPTION_SCHEMES;

typedef struct D3D12_FEATURE_DATA_VIDEO_CRYPTO_SESSION_SUPPORT
    {
    UINT NodeIndex;
    GUID DecodeProfile;
    GUID ContentProtectionSystem;
    D3D12_CRYPTO_SESSION_FLAGS Flags;
    D3D12_BITSTREAM_ENCRYPTION_TYPE BitstreamEncryption;
    UINT KeyBaseDataSize;
    D3D12_CRYPTO_SESSION_SUPPORT_FLAGS Support;
    } 	D3D12_FEATURE_DATA_VIDEO_CRYPTO_SESSION_SUPPORT;

typedef struct D3D12_CRYPTO_SESSION_DESC
    {
    UINT NodeMask;
    GUID DecodeProfile;
    GUID ContentProtectionSystem;
    D3D12_BITSTREAM_ENCRYPTION_TYPE BitstreamEncryption;
    D3D12_CRYPTO_SESSION_FLAGS Flags;
    } 	D3D12_CRYPTO_SESSION_DESC;



extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D12CryptoSession_INTERFACE_DEFINED__
#define __ID3D12CryptoSession_INTERFACE_DEFINED__

/* interface ID3D12CryptoSession */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12CryptoSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC7C6C9D-C27D-4904-835D-A5F2096EC65F")
    ID3D12CryptoSession : public ID3D12ProtectedSession
    {
    public:
        virtual D3D12_CRYPTO_SESSION_DESC STDMETHODCALLTYPE GetDesc( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetKeyBaseData( 
            UINT KeyInputDataSize,
            _In_reads_bytes_( KeyInputDataSize )  const void *pKeyInputData,
            UINT KeyBaseDataSize,
            _Out_writes_bytes_( KeyBaseDataSize )  void *pKeyBaseData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12CryptoSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12CryptoSession * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12CryptoSession * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12CryptoSession * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12CryptoSession * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12CryptoSession * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12CryptoSession * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12CryptoSession * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12CryptoSession * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatusFence )( 
            ID3D12CryptoSession * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppFence);
        
        D3D12_PROTECTED_SESSION_STATUS ( STDMETHODCALLTYPE *GetSessionStatus )( 
            ID3D12CryptoSession * This);
        
        D3D12_CRYPTO_SESSION_DESC ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D12CryptoSession * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetKeyBaseData )( 
            ID3D12CryptoSession * This,
            UINT KeyInputDataSize,
            _In_reads_bytes_( KeyInputDataSize )  const void *pKeyInputData,
            UINT KeyBaseDataSize,
            _Out_writes_bytes_( KeyBaseDataSize )  void *pKeyBaseData);
        
        END_INTERFACE
    } ID3D12CryptoSessionVtbl;

    interface ID3D12CryptoSession
    {
        CONST_VTBL struct ID3D12CryptoSessionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12CryptoSession_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12CryptoSession_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12CryptoSession_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12CryptoSession_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12CryptoSession_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12CryptoSession_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12CryptoSession_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12CryptoSession_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12CryptoSession_GetStatusFence(This,riid,ppFence)	\
    ( (This)->lpVtbl -> GetStatusFence(This,riid,ppFence) ) 

#define ID3D12CryptoSession_GetSessionStatus(This)	\
    ( (This)->lpVtbl -> GetSessionStatus(This) ) 


#define ID3D12CryptoSession_GetDesc(This)	\
    ( (This)->lpVtbl -> GetDesc(This) ) 

#define ID3D12CryptoSession_GetKeyBaseData(This,KeyInputDataSize,pKeyInputData,KeyBaseDataSize,pKeyBaseData)	\
    ( (This)->lpVtbl -> GetKeyBaseData(This,KeyInputDataSize,pKeyInputData,KeyBaseDataSize,pKeyBaseData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12CryptoSession_INTERFACE_DEFINED__ */


#ifndef __ID3D12CryptoSessionPolicy_INTERFACE_DEFINED__
#define __ID3D12CryptoSessionPolicy_INTERFACE_DEFINED__

/* interface ID3D12CryptoSessionPolicy */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12CryptoSessionPolicy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69FE3108-01A4-4AC3-AB91-F51E377A62AC")
    ID3D12CryptoSessionPolicy : public ID3D12DeviceChild
    {
    public:
        virtual UINT STDMETHODCALLTYPE GetKeyInfoSize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetKeyInfo( 
            _Out_writes_bytes_( KeyInfoDataSize )  void *pKeyInfo,
            UINT KeyInfoDataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCryptoSession( 
            REFIID riid,
            _COM_Outptr_opt_  void **ppCryptoSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12CryptoSessionPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12CryptoSessionPolicy * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12CryptoSessionPolicy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12CryptoSessionPolicy * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12CryptoSessionPolicy * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12CryptoSessionPolicy * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12CryptoSessionPolicy * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12CryptoSessionPolicy * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12CryptoSessionPolicy * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        UINT ( STDMETHODCALLTYPE *GetKeyInfoSize )( 
            ID3D12CryptoSessionPolicy * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetKeyInfo )( 
            ID3D12CryptoSessionPolicy * This,
            _Out_writes_bytes_( KeyInfoDataSize )  void *pKeyInfo,
            UINT KeyInfoDataSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetCryptoSession )( 
            ID3D12CryptoSessionPolicy * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppCryptoSession);
        
        END_INTERFACE
    } ID3D12CryptoSessionPolicyVtbl;

    interface ID3D12CryptoSessionPolicy
    {
        CONST_VTBL struct ID3D12CryptoSessionPolicyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12CryptoSessionPolicy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12CryptoSessionPolicy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12CryptoSessionPolicy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12CryptoSessionPolicy_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12CryptoSessionPolicy_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12CryptoSessionPolicy_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12CryptoSessionPolicy_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12CryptoSessionPolicy_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12CryptoSessionPolicy_GetKeyInfoSize(This)	\
    ( (This)->lpVtbl -> GetKeyInfoSize(This) ) 

#define ID3D12CryptoSessionPolicy_GetKeyInfo(This,pKeyInfo,KeyInfoDataSize)	\
    ( (This)->lpVtbl -> GetKeyInfo(This,pKeyInfo,KeyInfoDataSize) ) 

#define ID3D12CryptoSessionPolicy_GetCryptoSession(This,riid,ppCryptoSession)	\
    ( (This)->lpVtbl -> GetCryptoSession(This,riid,ppCryptoSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12CryptoSessionPolicy_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12_1_0000_0002 */
/* [local] */ 

typedef 
enum D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION
    {
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_NONE	= 0,
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_DECRYPT	= 1,
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_DECRYPT_WITH_HEADER	= 2,
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_TRANSCRYPT	= 3,
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_TRANSCRYPT_WITH_HEADER	= 4,
        D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION_DECRYPT_HEADER	= 5
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION;

typedef 
enum D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAGS
    {
        D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAG_NONE	= 0,
        D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAG_SUPPORTED	= 0x1
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAGS );
typedef struct D3D12_FEATURE_DATA_VIDEO_CRYPTO_SESSION_TRANSFORM_SUPPORT
    {
    UINT NodeIndex;
    GUID DecodeProfile;
    GUID ContentProtectionSystem;
    D3D12_CRYPTO_SESSION_FLAGS Flags;
    D3D12_BITSTREAM_ENCRYPTION_TYPE BitstreamEncryption;
    D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION Operation;
    BOOL ProtectedOutputRequired;
    UINT64 InputAlignment;
    UINT64 InputPreambleSize;
    UINT64 OutputAlignment;
    UINT64 OutputPreambleSize;
    D3D12_CRYPTO_SESSION_TRANSFORM_SUPPORT_FLAGS Support;
    } 	D3D12_FEATURE_DATA_VIDEO_CRYPTO_SESSION_TRANSFORM_SUPPORT;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_INPUT_ARGUMENTS
    {
    BOOL Enable;
    _Field_size_bytes_full_(SliceHeadersSize)  const void *pSliceHeaders;
    UINT64 SliceHeadersSize;
    _Field_size_full_(SliceHeaderCount)  const DWORD *pSliceHeadersOffsets;
    UINT64 SliceHeaderCount;
    _Field_size_bytes_full_(ContextSize)  const void *pContext;
    UINT64 ContextSize;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_INPUT_ARGUMENTS;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_INPUT_ARGUMENTS
    {
    ID3D12CryptoSessionPolicy *pCryptoSessionPolicy;
    ID3D12Resource *pBuffer;
    UINT64 Size;
    UINT64 Offset;
    _Field_size_bytes_full_(IVSize)  const void *pIV;
    UINT IVSize;
    UINT SubSampleMappingCount;
    _Field_size_bytes_full_(SubSampleMappingCount)  const void *pSubSampleMappingBlock;
    UINT64 ContextSize;
    _Field_size_bytes_full_(ContextSize)  const void *pContext;
    D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_INPUT_ARGUMENTS EncryptedHeader;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_INPUT_ARGUMENTS;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_OUTPUT_ARGUMENTS
    {
    BOOL Enable;
    ID3D12ProtectedSession *pProtectedSession;
    ID3D12Resource *pBuffer;
    UINT64 Size;
    UINT64 Offset;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_OUTPUT_ARGUMENTS;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_TRANSCRYPT_OUTPUT_ARGUMENTS
    {
    BOOL Enable;
    _Field_size_bytes_full_(IVSize)  void *pIV;
    UINT IVSize;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_TRANSCRYPT_OUTPUT_ARGUMENTS;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_OUTPUT_ARGUMENTS
    {
    BOOL Enable;
    UINT64 SliceHeadersSize;
    _Field_size_bytes_full_(SliceHeadersSize)  const void *pSliceHeaders;
    UINT64 ContextSize;
    _Field_size_bytes_full_(ContextSize)  const void *pContext;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_OUTPUT_ARGUMENTS;

typedef struct D3D12_CRYPTO_SESSION_TRANSFORM_OUTPUT_ARGUMENTS
    {
    D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_OUTPUT_ARGUMENTS Decrypt;
    D3D12_CRYPTO_SESSION_TRANSFORM_TRANSCRYPT_OUTPUT_ARGUMENTS Transcrypt;
    D3D12_CRYPTO_SESSION_TRANSFORM_DECRYPT_HEADER_OUTPUT_ARGUMENTS ClearHeader;
    } 	D3D12_CRYPTO_SESSION_TRANSFORM_OUTPUT_ARGUMENTS;



extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0002_v0_0_s_ifspec;

#ifndef __ID3D12ContentProtectionDevice_INTERFACE_DEFINED__
#define __ID3D12ContentProtectionDevice_INTERFACE_DEFINED__

/* interface ID3D12ContentProtectionDevice */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12ContentProtectionDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59975f53-bf5f-42f2-b84f-5e347c1e3d43")
    ID3D12ContentProtectionDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateCryptoSession( 
            _In_  const D3D12_CRYPTO_SESSION_DESC *pDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateCryptoSessionPolicy( 
            _In_reads_bytes_( KeyInfoSize )  const void *pKeyInfo,
            UINT KeyInfoSize,
            _In_  ID3D12CryptoSession *pCryptoSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppCryptoSessionPolicy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TransformEncryptedData( 
            D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION Operation,
            _In_  const D3D12_CRYPTO_SESSION_TRANSFORM_OUTPUT_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_CRYPTO_SESSION_TRANSFORM_INPUT_ARGUMENTS *pInputArguments) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12ContentProtectionDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12ContentProtectionDevice * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12ContentProtectionDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12ContentProtectionDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateCryptoSession )( 
            ID3D12ContentProtectionDevice * This,
            _In_  const D3D12_CRYPTO_SESSION_DESC *pDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppSession);
        
        HRESULT ( STDMETHODCALLTYPE *CreateCryptoSessionPolicy )( 
            ID3D12ContentProtectionDevice * This,
            _In_reads_bytes_( KeyInfoSize )  const void *pKeyInfo,
            UINT KeyInfoSize,
            _In_  ID3D12CryptoSession *pCryptoSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppCryptoSessionPolicy);
        
        HRESULT ( STDMETHODCALLTYPE *TransformEncryptedData )( 
            ID3D12ContentProtectionDevice * This,
            D3D12_CRYPTO_SESSION_TRANSFORM_OPERATION Operation,
            _In_  const D3D12_CRYPTO_SESSION_TRANSFORM_OUTPUT_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_CRYPTO_SESSION_TRANSFORM_INPUT_ARGUMENTS *pInputArguments);
        
        END_INTERFACE
    } ID3D12ContentProtectionDeviceVtbl;

    interface ID3D12ContentProtectionDevice
    {
        CONST_VTBL struct ID3D12ContentProtectionDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12ContentProtectionDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12ContentProtectionDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12ContentProtectionDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12ContentProtectionDevice_CreateCryptoSession(This,pDesc,riid,ppSession)	\
    ( (This)->lpVtbl -> CreateCryptoSession(This,pDesc,riid,ppSession) ) 

#define ID3D12ContentProtectionDevice_CreateCryptoSessionPolicy(This,pKeyInfo,KeyInfoSize,pCryptoSession,riid,ppCryptoSessionPolicy)	\
    ( (This)->lpVtbl -> CreateCryptoSessionPolicy(This,pKeyInfo,KeyInfoSize,pCryptoSession,riid,ppCryptoSessionPolicy) ) 

#define ID3D12ContentProtectionDevice_TransformEncryptedData(This,Operation,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> TransformEncryptedData(This,Operation,pOutputArguments,pInputArguments) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12ContentProtectionDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12_1_0000_0003 */
/* [local] */ 

typedef struct D3D12_VIDEO_DECODE_DECRYPTION_ARGUMENTS
    {
    ID3D12CryptoSessionPolicy *pCryptoSessionPolicy;
    _Field_size_bytes_full_(IVSize)  const void *pIV;
    UINT IVSize;
    _Field_size_bytes_full_(SubSampleMappingCount)  const void *pSubSampleMappingBlock;
    UINT SubSampleMappingCount;
    UINT cBlocksStripeEncrypted;
    UINT cBlocksStripeClear;
    } 	D3D12_VIDEO_DECODE_DECRYPTION_ARGUMENTS;

typedef struct D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS1
    {
    UINT NumFrameArguments;
    D3D12_VIDEO_DECODE_FRAME_ARGUMENT FrameArguments[ 10 ];
    D3D12_VIDEO_DECODE_REFERENCE_FRAMES ReferenceFrames;
    D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM CompressedBitstream;
    D3D12_VIDEO_DECODE_DECRYPTION_ARGUMENTS DecryptionArguments;
    ID3D12VideoDecoderHeap *pHeap;
    } 	D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS1;



extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0003_v0_0_s_ifspec;

#ifndef __ID3D12VideoDecodeCommandList2_INTERFACE_DEFINED__
#define __ID3D12VideoDecodeCommandList2_INTERFACE_DEFINED__

/* interface ID3D12VideoDecodeCommandList2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDecodeCommandList2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EAD05737-EE1D-4442-9B18-7D992E9A8960")
    ID3D12VideoDecodeCommandList2 : public ID3D12VideoDecodeCommandList1
    {
    public:
        virtual void STDMETHODCALLTYPE DecodeFrame2( 
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS1 *pInputArguments) = 0;
        
        virtual void STDMETHODCALLTYPE SetProtectedResourceSession( 
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDecodeCommandList2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDecodeCommandList2 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoDecodeCommandList2 * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoDecodeCommandList2 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoDecodeCommandList2 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoDecodeCommandList2 * This);
        
        void ( STDMETHODCALLTYPE *DecodeFrame )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoDecodeCommandList2 * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        void ( STDMETHODCALLTYPE *DecodeFrame1 )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *DecodeFrame2 )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS1 *pInputArguments);
        
        void ( STDMETHODCALLTYPE *SetProtectedResourceSession )( 
            ID3D12VideoDecodeCommandList2 * This,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession);
        
        END_INTERFACE
    } ID3D12VideoDecodeCommandList2Vtbl;

    interface ID3D12VideoDecodeCommandList2
    {
        CONST_VTBL struct ID3D12VideoDecodeCommandList2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDecodeCommandList2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDecodeCommandList2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDecodeCommandList2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDecodeCommandList2_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoDecodeCommandList2_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoDecodeCommandList2_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoDecodeCommandList2_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoDecodeCommandList2_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoDecodeCommandList2_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoDecodeCommandList2_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoDecodeCommandList2_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoDecodeCommandList2_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoDecodeCommandList2_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoDecodeCommandList2_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoDecodeCommandList2_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList2_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList2_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoDecodeCommandList2_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoDecodeCommandList2_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList2_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList2_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoDecodeCommandList2_DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoDecodeCommandList2_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 


#define ID3D12VideoDecodeCommandList2_DecodeFrame1(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame1(This,pDecoder,pOutputArguments,pInputArguments) ) 


#define ID3D12VideoDecodeCommandList2_DecodeFrame2(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame2(This,pDecoder,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoDecodeCommandList2_SetProtectedResourceSession(This,pProtectedResourceSession)	\
    ( (This)->lpVtbl -> SetProtectedResourceSession(This,pProtectedResourceSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoDecodeCommandList2_INTERFACE_DEFINED__ */


#ifndef __ID3D12VideoProcessCommandList2_INTERFACE_DEFINED__
#define __ID3D12VideoProcessCommandList2_INTERFACE_DEFINED__

/* interface ID3D12VideoProcessCommandList2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoProcessCommandList2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("569AB919-94DE-4529-8292-35DE97848059")
    ID3D12VideoProcessCommandList2 : public ID3D12VideoProcessCommandList1
    {
    public:
        virtual void STDMETHODCALLTYPE SetProtectedResourceSession( 
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoProcessCommandList2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoProcessCommandList2 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoProcessCommandList2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoProcessCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoProcessCommandList2 * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoProcessCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoProcessCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoProcessCommandList2 * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoProcessCommandList2 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoProcessCommandList2 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoProcessCommandList2 * This);
        
        void ( STDMETHODCALLTYPE *ProcessFrames )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoProcessCommandList2 * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        void ( STDMETHODCALLTYPE *ProcessFrames1 )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1 *pInputArguments);
        
        void ( STDMETHODCALLTYPE *SetProtectedResourceSession )( 
            ID3D12VideoProcessCommandList2 * This,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession);
        
        END_INTERFACE
    } ID3D12VideoProcessCommandList2Vtbl;

    interface ID3D12VideoProcessCommandList2
    {
        CONST_VTBL struct ID3D12VideoProcessCommandList2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoProcessCommandList2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoProcessCommandList2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoProcessCommandList2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoProcessCommandList2_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoProcessCommandList2_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoProcessCommandList2_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoProcessCommandList2_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoProcessCommandList2_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoProcessCommandList2_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoProcessCommandList2_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoProcessCommandList2_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoProcessCommandList2_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoProcessCommandList2_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoProcessCommandList2_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoProcessCommandList2_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList2_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList2_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoProcessCommandList2_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoProcessCommandList2_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList2_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList2_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoProcessCommandList2_ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments)	\
    ( (This)->lpVtbl -> ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments) ) 

#define ID3D12VideoProcessCommandList2_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 


#define ID3D12VideoProcessCommandList2_ProcessFrames1(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments)	\
    ( (This)->lpVtbl -> ProcessFrames1(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments) ) 


#define ID3D12VideoProcessCommandList2_SetProtectedResourceSession(This,pProtectedResourceSession)	\
    ( (This)->lpVtbl -> SetProtectedResourceSession(This,pProtectedResourceSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoProcessCommandList2_INTERFACE_DEFINED__ */


#ifndef __ID3D12StateObjectPrototype_INTERFACE_DEFINED__
#define __ID3D12StateObjectPrototype_INTERFACE_DEFINED__

/* interface ID3D12StateObjectPrototype */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12StateObjectPrototype;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47016943-fca8-4594-93ea-af258b55346d")
    ID3D12StateObjectPrototype : public ID3D12Pageable
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCachedBlob( 
            _COM_Outptr_  ID3DBlob **ppBlob) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12StateObjectPrototypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12StateObjectPrototype * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12StateObjectPrototype * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12StateObjectPrototype * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12StateObjectPrototype * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12StateObjectPrototype * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12StateObjectPrototype * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12StateObjectPrototype * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12StateObjectPrototype * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetCachedBlob )( 
            ID3D12StateObjectPrototype * This,
            _COM_Outptr_  ID3DBlob **ppBlob);
        
        END_INTERFACE
    } ID3D12StateObjectPrototypeVtbl;

    interface ID3D12StateObjectPrototype
    {
        CONST_VTBL struct ID3D12StateObjectPrototypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12StateObjectPrototype_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12StateObjectPrototype_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12StateObjectPrototype_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12StateObjectPrototype_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12StateObjectPrototype_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12StateObjectPrototype_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12StateObjectPrototype_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12StateObjectPrototype_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12StateObjectPrototype_GetCachedBlob(This,ppBlob)	\
    ( (This)->lpVtbl -> GetCachedBlob(This,ppBlob) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12StateObjectPrototype_INTERFACE_DEFINED__ */


#ifndef __ID3D12StateObjectPropertiesPrototype_INTERFACE_DEFINED__
#define __ID3D12StateObjectPropertiesPrototype_INTERFACE_DEFINED__

/* interface ID3D12StateObjectPropertiesPrototype */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12StateObjectPropertiesPrototype;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("de5fa827-9bf9-4f26-89ff-d7f56fde3860")
    ID3D12StateObjectPropertiesPrototype : public IUnknown
    {
    public:
        virtual void *STDMETHODCALLTYPE GetShaderIdentifier( 
            _In_  LPCWSTR pExportName) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetShaderStackSize( 
            _In_  LPCWSTR pExportName) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetPipelineStackSize( void) = 0;
        
        virtual void STDMETHODCALLTYPE SetPipelineStackSize( 
            UINT64 PipelineStackSizeInBytes) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12StateObjectPropertiesPrototypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12StateObjectPropertiesPrototype * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12StateObjectPropertiesPrototype * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12StateObjectPropertiesPrototype * This);
        
        void *( STDMETHODCALLTYPE *GetShaderIdentifier )( 
            ID3D12StateObjectPropertiesPrototype * This,
            _In_  LPCWSTR pExportName);
        
        UINT64 ( STDMETHODCALLTYPE *GetShaderStackSize )( 
            ID3D12StateObjectPropertiesPrototype * This,
            _In_  LPCWSTR pExportName);
        
        UINT64 ( STDMETHODCALLTYPE *GetPipelineStackSize )( 
            ID3D12StateObjectPropertiesPrototype * This);
        
        void ( STDMETHODCALLTYPE *SetPipelineStackSize )( 
            ID3D12StateObjectPropertiesPrototype * This,
            UINT64 PipelineStackSizeInBytes);
        
        END_INTERFACE
    } ID3D12StateObjectPropertiesPrototypeVtbl;

    interface ID3D12StateObjectPropertiesPrototype
    {
        CONST_VTBL struct ID3D12StateObjectPropertiesPrototypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12StateObjectPropertiesPrototype_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12StateObjectPropertiesPrototype_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12StateObjectPropertiesPrototype_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12StateObjectPropertiesPrototype_GetShaderIdentifier(This,pExportName)	\
    ( (This)->lpVtbl -> GetShaderIdentifier(This,pExportName) ) 

#define ID3D12StateObjectPropertiesPrototype_GetShaderStackSize(This,pExportName)	\
    ( (This)->lpVtbl -> GetShaderStackSize(This,pExportName) ) 

#define ID3D12StateObjectPropertiesPrototype_GetPipelineStackSize(This)	\
    ( (This)->lpVtbl -> GetPipelineStackSize(This) ) 

#define ID3D12StateObjectPropertiesPrototype_SetPipelineStackSize(This,PipelineStackSizeInBytes)	\
    ( (This)->lpVtbl -> SetPipelineStackSize(This,PipelineStackSizeInBytes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12StateObjectPropertiesPrototype_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12_1_0000_0007 */
/* [local] */ 

typedef 
enum D3D12_STATE_SUBOBJECT_TYPE
    {
        D3D12_STATE_SUBOBJECT_TYPE_FLAGS	= 0,
        D3D12_STATE_SUBOBJECT_TYPE_ROOT_SIGNATURE	= 1,
        D3D12_STATE_SUBOBJECT_TYPE_LOCAL_ROOT_SIGNATURE	= 2,
        D3D12_STATE_SUBOBJECT_TYPE_NODE_MASK	= 3,
        D3D12_STATE_SUBOBJECT_TYPE_CACHED_STATE_OBJECT	= 4,
        D3D12_STATE_SUBOBJECT_TYPE_DXIL_LIBRARY	= 5,
        D3D12_STATE_SUBOBJECT_TYPE_EXISTING_COLLECTION	= 6,
        D3D12_STATE_SUBOBJECT_TYPE_SUBOBJECT_TO_EXPORTS_ASSOCIATION	= 7,
        D3D12_STATE_SUBOBJECT_TYPE_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION	= 8,
        D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_SHADER_CONFIG	= 9,
        D3D12_STATE_SUBOBJECT_TYPE_RAYTRACING_PIPELINE_CONFIG	= 10,
        D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP	= 11,
        D3D12_STATE_SUBOBJECT_TYPE_MAX_VALID	= ( D3D12_STATE_SUBOBJECT_TYPE_HIT_GROUP + 1 ) 
    } 	D3D12_STATE_SUBOBJECT_TYPE;

typedef struct D3D12_STATE_SUBOBJECT
    {
    D3D12_STATE_SUBOBJECT_TYPE Type;
    const void *pDesc;
    } 	D3D12_STATE_SUBOBJECT;

typedef 
enum D3D12_STATE_OBJECT_FLAGS
    {
        D3D12_STATE_OBJECT_FLAG_NONE	= 0
    } 	D3D12_STATE_OBJECT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_STATE_OBJECT_FLAGS );
typedef 
enum D3D12_EXPORT_FLAGS
    {
        D3D12_EXPORT_FLAG_NONE	= 0
    } 	D3D12_EXPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_EXPORT_FLAGS );
typedef struct D3D12_EXPORT_DESC
    {
    LPCWSTR Name;
    _In_opt_  LPCWSTR ExportToRename;
    D3D12_EXPORT_FLAGS Flags;
    } 	D3D12_EXPORT_DESC;

typedef struct D3D12_DXIL_LIBRARY_DESC
    {
    D3D12_SHADER_BYTECODE DXILLibrary;
    UINT NumExports;
    _In_reads_(NumExports)  D3D12_EXPORT_DESC *pExports;
    } 	D3D12_DXIL_LIBRARY_DESC;

typedef struct D3D12_EXISTING_COLLECTION_DESC
    {
    ID3D12StateObjectPrototype *pExistingCollection;
    UINT NumExports;
    _In_reads_(NumExports)  D3D12_EXPORT_DESC *pExports;
    } 	D3D12_EXISTING_COLLECTION_DESC;

typedef struct D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION
    {
    const D3D12_STATE_SUBOBJECT *pSubobjectToAssociate;
    UINT NumExports;
    _In_reads_(NumExports)  LPCWSTR *pExports;
    } 	D3D12_SUBOBJECT_TO_EXPORTS_ASSOCIATION;

typedef struct D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION
    {
    LPCWSTR SubobjectToAssociate;
    UINT NumExports;
    _In_reads_(NumExports)  LPCWSTR *pExports;
    } 	D3D12_DXIL_SUBOBJECT_TO_EXPORTS_ASSOCIATION;

typedef struct D3D12_HIT_GROUP_DESC
    {
    LPCWSTR HitGroupExport;
    _In_opt_  LPCWSTR AnyHitShaderImport;
    _In_opt_  LPCWSTR ClosestHitShaderImport;
    _In_opt_  LPCWSTR IntersectionShaderImport;
    } 	D3D12_HIT_GROUP_DESC;

typedef struct D3D12_RAYTRACING_SHADER_CONFIG
    {
    UINT MaxPayloadSizeInBytes;
    UINT MaxAttributeSizeInBytes;
    } 	D3D12_RAYTRACING_SHADER_CONFIG;

typedef struct D3D12_RAYTRACING_PIPELINE_CONFIG
    {
    UINT MaxTraceRecursionDepth;
    } 	D3D12_RAYTRACING_PIPELINE_CONFIG;

typedef 
enum D3D12_STATE_OBJECT_TYPE
    {
        D3D12_STATE_OBJECT_TYPE_COLLECTION	= 0,
        D3D12_STATE_OBJECT_TYPE_RAYTRACING_PIPELINE	= 3
    } 	D3D12_STATE_OBJECT_TYPE;

typedef struct D3D12_STATE_OBJECT_DESC
    {
    D3D12_STATE_OBJECT_TYPE Type;
    UINT NumSubobjects;
    _In_reads_(NumSubobjects)  const D3D12_STATE_SUBOBJECT *pSubobjects;
    } 	D3D12_STATE_OBJECT_DESC;

typedef 
enum D3D12_RAYTRACING_GEOMETRY_FLAGS
    {
        D3D12_RAYTRACING_GEOMETRY_FLAG_NONE	= 0,
        D3D12_RAYTRACING_GEOMETRY_FLAG_OPAQUE	= 0x1,
        D3D12_RAYTRACING_GEOMETRY_FLAG_NO_DUPLICATE_ANYHIT_INVOCATION	= 0x2
    } 	D3D12_RAYTRACING_GEOMETRY_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_RAYTRACING_GEOMETRY_FLAGS );
typedef 
enum D3D12_RAYTRACING_GEOMETRY_TYPE
    {
        D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES	= 0,
        D3D12_RAYTRACING_GEOMETRY_TYPE_PROCEDURAL_PRIMITIVE_AABBS	= ( D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES + 1 ) 
    } 	D3D12_RAYTRACING_GEOMETRY_TYPE;

typedef 
enum D3D12_RAYTRACING_INSTANCE_FLAGS
    {
        D3D12_RAYTRACING_INSTANCE_FLAG_NONE	= 0,
        D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE	= 0x1,
        D3D12_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE	= 0x2,
        D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE	= 0x4,
        D3D12_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE	= 0x8
    } 	D3D12_RAYTRACING_INSTANCE_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_RAYTRACING_INSTANCE_FLAGS );
typedef struct D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE
    {
    D3D12_GPU_VIRTUAL_ADDRESS StartAddress;
    UINT64 StrideInBytes;
    } 	D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE;

typedef struct D3D12_GPU_VIRTUAL_ADDRESS_RANGE
    {
    D3D12_GPU_VIRTUAL_ADDRESS StartAddress;
    UINT64 SizeInBytes;
    } 	D3D12_GPU_VIRTUAL_ADDRESS_RANGE;

typedef struct D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE
    {
    D3D12_GPU_VIRTUAL_ADDRESS StartAddress;
    UINT64 SizeInBytes;
    UINT64 StrideInBytes;
    } 	D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE;

typedef struct D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC
    {
    D3D12_GPU_VIRTUAL_ADDRESS Transform;
    DXGI_FORMAT IndexFormat;
    DXGI_FORMAT VertexFormat;
    UINT IndexCount;
    UINT VertexCount;
    D3D12_GPU_VIRTUAL_ADDRESS IndexBuffer;
    D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE VertexBuffer;
    } 	D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC;

typedef struct D3D12_RAYTRACING_AABB
    {
    FLOAT MinX;
    FLOAT MinY;
    FLOAT MinZ;
    FLOAT MaxX;
    FLOAT MaxY;
    FLOAT MaxZ;
    } 	D3D12_RAYTRACING_AABB;

typedef struct D3D12_RAYTRACING_GEOMETRY_AABBS_DESC
    {
    UINT64 AABBCount;
    D3D12_GPU_VIRTUAL_ADDRESS_AND_STRIDE AABBs;
    } 	D3D12_RAYTRACING_GEOMETRY_AABBS_DESC;

typedef struct D3D12_RAYTRACING_GEOMETRY_DESC
    {
    D3D12_RAYTRACING_GEOMETRY_TYPE Type;
    D3D12_RAYTRACING_GEOMETRY_FLAGS Flags;
    union 
        {
        D3D12_RAYTRACING_GEOMETRY_TRIANGLES_DESC Triangles;
        D3D12_RAYTRACING_GEOMETRY_AABBS_DESC AABBs;
        } 	;
    } 	D3D12_RAYTRACING_GEOMETRY_DESC;

typedef 
enum D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS
    {
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE	= 0,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE	= 0x1,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_COMPACTION	= 0x2,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE	= 0x4,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD	= 0x8,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_MINIMIZE_MEMORY	= 0x10,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE	= 0x20
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS );
typedef 
enum D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE
    {
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_CLONE	= 0,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_COMPACT	= 0x1,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_VISUALIZATION_DECODE_FOR_TOOLS	= 0x2,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_SERIALIZE	= 0x3,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE_DESERIALIZE	= 0x4
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE;

typedef 
enum D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE
    {
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL	= 0,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL	= 0x1
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE;

typedef struct D3D12_RAYTRACING_INSTANCE_DESC
    {
    FLOAT Transform[ 12 ];
    UINT InstanceID	: 24;
    UINT InstanceMask	: 8;
    UINT InstanceContributionToHitGroupIndex	: 24;
    UINT Flags	: 8;
    D3D12_GPU_VIRTUAL_ADDRESS AccelerationStructure;
    } 	D3D12_RAYTRACING_INSTANCE_DESC;

typedef struct D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO
    {
    UINT64 ResultDataMaxSizeInBytes;
    UINT64 ScratchDataSizeInBytes;
    UINT64 UpdateScratchDataSizeInBytes;
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO;

typedef 
enum D3D12_ELEMENTS_LAYOUT
    {
        D3D12_ELEMENTS_LAYOUT_ARRAY	= 0,
        D3D12_ELEMENTS_LAYOUT_ARRAY_OF_POINTERS	= 0x1
    } 	D3D12_ELEMENTS_LAYOUT;

typedef struct D3D12_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO_DESC
    {
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE Type;
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS Flags;
    UINT NumDescs;
    D3D12_ELEMENTS_LAYOUT DescsLayout;
    union 
        {
        const D3D12_RAYTRACING_GEOMETRY_DESC *pGeometryDescs;
        const D3D12_RAYTRACING_GEOMETRY_DESC *const *ppGeometryDescs;
        } 	;
    } 	D3D12_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO_DESC;

typedef 
enum D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE
    {
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE	= 0,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION	= ( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE + 1 ) ,
        D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION	= ( D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION + 1 ) 
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE;

typedef struct D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC
    {
    UINT64 CompactedSizeInBytes;
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_COMPACTED_SIZE_DESC;

typedef struct D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC
    {
    UINT64 DecodedSizeInBytes;
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TOOLS_VISUALIZATION_DESC;

typedef struct D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER
    {
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE Type;
    UINT NumDescs;
    } 	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER;

// Regarding D3D12_BUILD_RAY_TRACING_ACCELERATION_STRUCTURE_TOOLS_VISUALIZATION_HEADER above,
// depending on Type field, NumDescs above is followed by either:
//       D3D12_RAY_TRACING_INSTANCE_DESC InstanceDescs[NumDescs]
//    or D3D12_RAY_TRACING_GEOMETRY_DESC GeometryDescs[NumDescs].
// There is 4 bytes of padding between GeometryDesc structs in the array so alignment is natural when viewed by CPU.

typedef struct D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC
    {
    UINT64 SerializedSizeInBytes;
    UINT64 NumBottomLevelAccelerationStructurePointers;
    } 	D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_SERIALIZATION_DESC;

typedef struct D3D12_SERIALIZED_ACCELERATION_STRUCTURE_HEADER
    {
    UINT64 SerializedSizeInBytesIncludingHeader;
    UINT64 DeserializedSizeInBytes;
    UINT64 NumBottomLevelAccelerationStructurePointersAfterHeader;
    } 	D3D12_SERIALIZED_ACCELERATION_STRUCTURE_HEADER;

typedef struct D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC
    {
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE DestAccelerationStructureData;
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE Type;
    UINT NumDescs;
    D3D12_ELEMENTS_LAYOUT DescsLayout;
    union 
        {
        D3D12_GPU_VIRTUAL_ADDRESS InstanceDescs;
        const D3D12_RAYTRACING_GEOMETRY_DESC *pGeometryDescs;
        const D3D12_RAYTRACING_GEOMETRY_DESC *const *ppGeometryDescs;
        } 	;
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS Flags;
    _In_opt_  D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData;
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE ScratchAccelerationStructureData;
    } 	D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC;

typedef struct D3D12_DISPATCH_RAYS_DESC
    {
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE RayGenerationShaderRecord;
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE MissShaderTable;
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE HitGroupTable;
    D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE CallableShaderTable;
    UINT Width;
    UINT Height;
    } 	D3D12_DISPATCH_RAYS_DESC;

#define D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BYTE_ALIGNMENT 256
#define D3D12_RAYTRACING_INSTANCE_DESCS_BYTE_ALIGNMENT 16
#define D3D12_RAYTRACING_MAX_ATTRIBUTE_SIZE_IN_BYTES 32
#define D3D12_RAYTRACING_SHADER_RECORD_BYTE_ALIGNMENT 16
#define D3D12_RAYTRACING_MAX_DECLARABLE_TRACE_RECURSION_DEPTH 31
#define D3D12_RAYTRACING_AABB_BYTE_ALIGNMENT 4


extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0007_v0_0_s_ifspec;

#ifndef __ID3D12DeviceRaytracingPrototype_INTERFACE_DEFINED__
#define __ID3D12DeviceRaytracingPrototype_INTERFACE_DEFINED__

/* interface ID3D12DeviceRaytracingPrototype */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DeviceRaytracingPrototype;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f52ef3ca-f710-4ee4-b873-a7f504e43995")
    ID3D12DeviceRaytracingPrototype : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateStateObject( 
            const D3D12_STATE_OBJECT_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppStateObject) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetShaderIdentifierSize( void) = 0;
        
        virtual void STDMETHODCALLTYPE GetRaytracingAccelerationStructurePrebuildInfo( 
            _In_  D3D12_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO_DESC *pDesc,
            _Out_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DeviceRaytracingPrototypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DeviceRaytracingPrototype * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DeviceRaytracingPrototype * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DeviceRaytracingPrototype * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateStateObject )( 
            ID3D12DeviceRaytracingPrototype * This,
            const D3D12_STATE_OBJECT_DESC *pDesc,
            REFIID riid,
            _COM_Outptr_  void **ppStateObject);
        
        UINT ( STDMETHODCALLTYPE *GetShaderIdentifierSize )( 
            ID3D12DeviceRaytracingPrototype * This);
        
        void ( STDMETHODCALLTYPE *GetRaytracingAccelerationStructurePrebuildInfo )( 
            ID3D12DeviceRaytracingPrototype * This,
            _In_  D3D12_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO_DESC *pDesc,
            _Out_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *pInfo);
        
        END_INTERFACE
    } ID3D12DeviceRaytracingPrototypeVtbl;

    interface ID3D12DeviceRaytracingPrototype
    {
        CONST_VTBL struct ID3D12DeviceRaytracingPrototypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DeviceRaytracingPrototype_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DeviceRaytracingPrototype_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DeviceRaytracingPrototype_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DeviceRaytracingPrototype_CreateStateObject(This,pDesc,riid,ppStateObject)	\
    ( (This)->lpVtbl -> CreateStateObject(This,pDesc,riid,ppStateObject) ) 

#define ID3D12DeviceRaytracingPrototype_GetShaderIdentifierSize(This)	\
    ( (This)->lpVtbl -> GetShaderIdentifierSize(This) ) 

#define ID3D12DeviceRaytracingPrototype_GetRaytracingAccelerationStructurePrebuildInfo(This,pDesc,pInfo)	\
    ( (This)->lpVtbl -> GetRaytracingAccelerationStructurePrebuildInfo(This,pDesc,pInfo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DeviceRaytracingPrototype_INTERFACE_DEFINED__ */


#ifndef __ID3D12CommandListRaytracingPrototype_INTERFACE_DEFINED__
#define __ID3D12CommandListRaytracingPrototype_INTERFACE_DEFINED__

/* interface ID3D12CommandListRaytracingPrototype */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12CommandListRaytracingPrototype;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3c69787a-28fa-4701-970a-37a1ed1f9cab")
    ID3D12CommandListRaytracingPrototype : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE BuildRaytracingAccelerationStructure( 
            _In_  const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC *pDesc) = 0;
        
        virtual void STDMETHODCALLTYPE EmitRaytracingAccelerationStructurePostBuildInfo( 
            _In_  D3D12_GPU_VIRTUAL_ADDRESS_RANGE DestBuffer,
            _In_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE InfoType,
            _In_  UINT NumSourceAccelerationStructures,
            _In_reads_( NumSourceAccelerationStructures )  const D3D12_GPU_VIRTUAL_ADDRESS *pSourceAccelerationStructureData) = 0;
        
        virtual void STDMETHODCALLTYPE CopyRaytracingAccelerationStructure( 
            _In_  D3D12_GPU_VIRTUAL_ADDRESS_RANGE DestAccelerationStructureData,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
            _In_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode) = 0;
        
        virtual void STDMETHODCALLTYPE DispatchRays( 
            _In_  ID3D12StateObjectPrototype *pRaytracingPipelineState,
            _In_  const D3D12_DISPATCH_RAYS_DESC *pDesc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12CommandListRaytracingPrototypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12CommandListRaytracingPrototype * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12CommandListRaytracingPrototype * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12CommandListRaytracingPrototype * This);
        
        void ( STDMETHODCALLTYPE *BuildRaytracingAccelerationStructure )( 
            ID3D12CommandListRaytracingPrototype * This,
            _In_  const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC *pDesc);
        
        void ( STDMETHODCALLTYPE *EmitRaytracingAccelerationStructurePostBuildInfo )( 
            ID3D12CommandListRaytracingPrototype * This,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS_RANGE DestBuffer,
            _In_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_TYPE InfoType,
            _In_  UINT NumSourceAccelerationStructures,
            _In_reads_( NumSourceAccelerationStructures )  const D3D12_GPU_VIRTUAL_ADDRESS *pSourceAccelerationStructureData);
        
        void ( STDMETHODCALLTYPE *CopyRaytracingAccelerationStructure )( 
            ID3D12CommandListRaytracingPrototype * This,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS_RANGE DestAccelerationStructureData,
            _In_  D3D12_GPU_VIRTUAL_ADDRESS SourceAccelerationStructureData,
            _In_  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE Mode);
        
        void ( STDMETHODCALLTYPE *DispatchRays )( 
            ID3D12CommandListRaytracingPrototype * This,
            _In_  ID3D12StateObjectPrototype *pRaytracingPipelineState,
            _In_  const D3D12_DISPATCH_RAYS_DESC *pDesc);
        
        END_INTERFACE
    } ID3D12CommandListRaytracingPrototypeVtbl;

    interface ID3D12CommandListRaytracingPrototype
    {
        CONST_VTBL struct ID3D12CommandListRaytracingPrototypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12CommandListRaytracingPrototype_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12CommandListRaytracingPrototype_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12CommandListRaytracingPrototype_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12CommandListRaytracingPrototype_BuildRaytracingAccelerationStructure(This,pDesc)	\
    ( (This)->lpVtbl -> BuildRaytracingAccelerationStructure(This,pDesc) ) 

#define ID3D12CommandListRaytracingPrototype_EmitRaytracingAccelerationStructurePostBuildInfo(This,DestBuffer,InfoType,NumSourceAccelerationStructures,pSourceAccelerationStructureData)	\
    ( (This)->lpVtbl -> EmitRaytracingAccelerationStructurePostBuildInfo(This,DestBuffer,InfoType,NumSourceAccelerationStructures,pSourceAccelerationStructureData) ) 

#define ID3D12CommandListRaytracingPrototype_CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode)	\
    ( (This)->lpVtbl -> CopyRaytracingAccelerationStructure(This,DestAccelerationStructureData,SourceAccelerationStructureData,Mode) ) 

#define ID3D12CommandListRaytracingPrototype_DispatchRays(This,pRaytracingPipelineState,pDesc)	\
    ( (This)->lpVtbl -> DispatchRays(This,pRaytracingPipelineState,pDesc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12CommandListRaytracingPrototype_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12_1_0000_0009 */
/* [local] */ 

typedef 
enum D3D12_METACOMMAND_PARAMETER_TYPE
    {
        D3D12_METACOMMAND_PARAMETER_FLOAT	= 0,
        D3D12_METACOMMAND_PARAMETER_UINT64	= 1,
        D3D12_METACOMMAND_PARAMETER_BUFFER_UAV	= 2,
        D3D12_METACOMMAND_PARAMETER_BINDPOINT_IN_SHADER	= 3
    } 	D3D12_METACOMMAND_PARAMETER_TYPE;

typedef 
enum D3D12_METACOMMAND_PARAMETER_ATTRIBUTES
    {
        D3D12_METACOMMAND_PARAMETER_INPUT	= 0x1,
        D3D12_METACOMMAND_PARAMETER_OUTPUT	= 0x2
    } 	D3D12_METACOMMAND_PARAMETER_ATTRIBUTES;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_METACOMMAND_PARAMETER_ATTRIBUTES );
typedef 
enum D3D12_METACOMMAND_PARAMETER_MUTABILITY
    {
        D3D12_METACOMMAND_PARAMETER_MUTABILITY_PER_EXECUTE	= 0,
        D3D12_METACOMMAND_PARAMETER_MUTABILITY_CREATION_ONLY	= 1,
        D3D12_METACOMMAND_PARAMETER_MUTABILITY_INITIALIZATION_ONLY	= 2
    } 	D3D12_METACOMMAND_PARAMETER_MUTABILITY;

typedef struct D3D12_METACOMMAND_PARAMETER_DESC
    {
    char Name[ 128 ];
    D3D12_METACOMMAND_PARAMETER_TYPE Type;
    D3D12_METACOMMAND_PARAMETER_ATTRIBUTES Attributes;
    D3D12_METACOMMAND_PARAMETER_MUTABILITY Mutability;
    } 	D3D12_METACOMMAND_PARAMETER_DESC;

typedef 
enum D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE
    {
        D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE_CBV	= 0,
        D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE_SRV	= ( D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE_CBV + 1 ) ,
        D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE_UAV	= ( D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE_SRV + 1 ) 
    } 	D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE;

typedef struct D3D12_BINDPOINT_IN_SHADER
    {
    D3D12_METACOMMAND_BINDPOINT_PARAMETER_TYPE Type;
    UINT Register;
    UINT Space;
    } 	D3D12_BINDPOINT_IN_SHADER;

typedef struct D3D12_METACOMMAND_PARAMETER_DATA
    {
    UINT ParameterIndex;
    union 
        {
        FLOAT FloatValue;
        UINT64 UnsignedInt64Value;
        D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;
        D3D12_BINDPOINT_IN_SHADER BindingInfo;
        } 	;
    } 	D3D12_METACOMMAND_PARAMETER_DATA;

typedef struct D3D12_METACOMMAND_DESCRIPTION
    {
    GUID Id;
    char Name[ 128 ];
    UINT SignatureCount;
    } 	D3D12_METACOMMAND_DESCRIPTION;



extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0009_v0_0_s_ifspec;

#ifndef __ID3D12DeviceMetaCommand_INTERFACE_DEFINED__
#define __ID3D12DeviceMetaCommand_INTERFACE_DEFINED__

/* interface ID3D12DeviceMetaCommand */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DeviceMetaCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("547e33c7-ff86-4cd9-bea3-5d4a28375396")
    ID3D12DeviceMetaCommand : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumerateMetaCommands( 
            _Inout_  UINT *pNumMetaCommands,
            _Out_writes_opt_(*pNumMetaCommands)  D3D12_METACOMMAND_DESCRIPTION *pDescs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateMetaCommandSignature( 
            _In_  REFGUID CommandId,
            _In_  UINT SignatureId,
            _Inout_  UINT *pParameterCount,
            _Out_writes_opt_(*pParameterCount)  D3D12_METACOMMAND_PARAMETER_DESC *pParameterDescs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateMetaCommand( 
            _In_  REFGUID CommandId,
            _In_  UINT SignatureId,
            _In_opt_  ID3D12RootSignature *pRootSignature,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters,
            REFIID riid,
            _COM_Outptr_  void **ppMetaCommand) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DeviceMetaCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DeviceMetaCommand * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DeviceMetaCommand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DeviceMetaCommand * This);
        
        HRESULT ( STDMETHODCALLTYPE *EnumerateMetaCommands )( 
            ID3D12DeviceMetaCommand * This,
            _Inout_  UINT *pNumMetaCommands,
            _Out_writes_opt_(*pNumMetaCommands)  D3D12_METACOMMAND_DESCRIPTION *pDescs);
        
        HRESULT ( STDMETHODCALLTYPE *EnumerateMetaCommandSignature )( 
            ID3D12DeviceMetaCommand * This,
            _In_  REFGUID CommandId,
            _In_  UINT SignatureId,
            _Inout_  UINT *pParameterCount,
            _Out_writes_opt_(*pParameterCount)  D3D12_METACOMMAND_PARAMETER_DESC *pParameterDescs);
        
        HRESULT ( STDMETHODCALLTYPE *CreateMetaCommand )( 
            ID3D12DeviceMetaCommand * This,
            _In_  REFGUID CommandId,
            _In_  UINT SignatureId,
            _In_opt_  ID3D12RootSignature *pRootSignature,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters,
            REFIID riid,
            _COM_Outptr_  void **ppMetaCommand);
        
        END_INTERFACE
    } ID3D12DeviceMetaCommandVtbl;

    interface ID3D12DeviceMetaCommand
    {
        CONST_VTBL struct ID3D12DeviceMetaCommandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DeviceMetaCommand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DeviceMetaCommand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DeviceMetaCommand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DeviceMetaCommand_EnumerateMetaCommands(This,pNumMetaCommands,pDescs)	\
    ( (This)->lpVtbl -> EnumerateMetaCommands(This,pNumMetaCommands,pDescs) ) 

#define ID3D12DeviceMetaCommand_EnumerateMetaCommandSignature(This,CommandId,SignatureId,pParameterCount,pParameterDescs)	\
    ( (This)->lpVtbl -> EnumerateMetaCommandSignature(This,CommandId,SignatureId,pParameterCount,pParameterDescs) ) 

#define ID3D12DeviceMetaCommand_CreateMetaCommand(This,CommandId,SignatureId,pRootSignature,NumParameters,pParameters,riid,ppMetaCommand)	\
    ( (This)->lpVtbl -> CreateMetaCommand(This,CommandId,SignatureId,pRootSignature,NumParameters,pParameters,riid,ppMetaCommand) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DeviceMetaCommand_INTERFACE_DEFINED__ */


#ifndef __ID3D12MetaCommand_INTERFACE_DEFINED__
#define __ID3D12MetaCommand_INTERFACE_DEFINED__

/* interface ID3D12MetaCommand */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12MetaCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8AFDA767-8003-494F-9E9A-4AA8864F3524")
    ID3D12MetaCommand : public ID3D12Pageable
    {
    public:
        virtual void STDMETHODCALLTYPE GetRequiredParameterResourceSize( 
            UINT32 ParameterIndex,
            UINT64 *SizeInBytes) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12MetaCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12MetaCommand * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12MetaCommand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12MetaCommand * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12MetaCommand * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12MetaCommand * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12MetaCommand * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12MetaCommand * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12MetaCommand * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        void ( STDMETHODCALLTYPE *GetRequiredParameterResourceSize )( 
            ID3D12MetaCommand * This,
            UINT32 ParameterIndex,
            UINT64 *SizeInBytes);
        
        END_INTERFACE
    } ID3D12MetaCommandVtbl;

    interface ID3D12MetaCommand
    {
        CONST_VTBL struct ID3D12MetaCommandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12MetaCommand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12MetaCommand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12MetaCommand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12MetaCommand_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12MetaCommand_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12MetaCommand_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12MetaCommand_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12MetaCommand_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12MetaCommand_GetRequiredParameterResourceSize(This,ParameterIndex,SizeInBytes)	\
    ( (This)->lpVtbl -> GetRequiredParameterResourceSize(This,ParameterIndex,SizeInBytes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12MetaCommand_INTERFACE_DEFINED__ */


#ifndef __ID3D12CommandListMetaCommand_INTERFACE_DEFINED__
#define __ID3D12CommandListMetaCommand_INTERFACE_DEFINED__

/* interface ID3D12CommandListMetaCommand */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12CommandListMetaCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A5F59F3-7124-4766-8E9E-CB637764FB0B")
    ID3D12CommandListMetaCommand : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE InitializeMetaCommand( 
            _In_  ID3D12MetaCommand *pMetaCommand,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters) = 0;
        
        virtual void STDMETHODCALLTYPE ExecuteMetaCommand( 
            _In_  ID3D12MetaCommand *pMetaCommand,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12CommandListMetaCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12CommandListMetaCommand * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12CommandListMetaCommand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12CommandListMetaCommand * This);
        
        void ( STDMETHODCALLTYPE *InitializeMetaCommand )( 
            ID3D12CommandListMetaCommand * This,
            _In_  ID3D12MetaCommand *pMetaCommand,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters);
        
        void ( STDMETHODCALLTYPE *ExecuteMetaCommand )( 
            ID3D12CommandListMetaCommand * This,
            _In_  ID3D12MetaCommand *pMetaCommand,
            _In_  UINT NumParameters,
            _In_reads_(NumParameters)  const D3D12_METACOMMAND_PARAMETER_DATA *pParameters);
        
        END_INTERFACE
    } ID3D12CommandListMetaCommandVtbl;

    interface ID3D12CommandListMetaCommand
    {
        CONST_VTBL struct ID3D12CommandListMetaCommandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12CommandListMetaCommand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12CommandListMetaCommand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12CommandListMetaCommand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12CommandListMetaCommand_InitializeMetaCommand(This,pMetaCommand,NumParameters,pParameters)	\
    ( (This)->lpVtbl -> InitializeMetaCommand(This,pMetaCommand,NumParameters,pParameters) ) 

#define ID3D12CommandListMetaCommand_ExecuteMetaCommand(This,pMetaCommand,NumParameters,pParameters)	\
    ( (This)->lpVtbl -> ExecuteMetaCommand(This,pMetaCommand,NumParameters,pParameters) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12CommandListMetaCommand_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12_1_0000_0012 */
/* [local] */ 

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
// BK - pragma endregion
DEFINE_GUID(IID_ID3D12CryptoSession,0xFC7C6C9D,0xC27D,0x4904,0x83,0x5D,0xA5,0xF2,0x09,0x6E,0xC6,0x5F);
DEFINE_GUID(IID_ID3D12CryptoSessionPolicy,0x69FE3108,0x01A4,0x4AC3,0xAB,0x91,0xF5,0x1E,0x37,0x7A,0x62,0xAC);
DEFINE_GUID(IID_ID3D12ContentProtectionDevice,0x59975f53,0xbf5f,0x42f2,0xb8,0x4f,0x5e,0x34,0x7c,0x1e,0x3d,0x43);
DEFINE_GUID(IID_ID3D12VideoDecodeCommandList2,0xEAD05737,0xEE1D,0x4442,0x9B,0x18,0x7D,0x99,0x2E,0x9A,0x89,0x60);
DEFINE_GUID(IID_ID3D12VideoProcessCommandList2,0x569AB919,0x94DE,0x4529,0x82,0x92,0x35,0xDE,0x97,0x84,0x80,0x59);
DEFINE_GUID(IID_ID3D12StateObjectPrototype,0x47016943,0xfca8,0x4594,0x93,0xea,0xaf,0x25,0x8b,0x55,0x34,0x6d);
DEFINE_GUID(IID_ID3D12StateObjectPropertiesPrototype,0xde5fa827,0x9bf9,0x4f26,0x89,0xff,0xd7,0xf5,0x6f,0xde,0x38,0x60);
DEFINE_GUID(IID_ID3D12DeviceRaytracingPrototype,0xf52ef3ca,0xf710,0x4ee4,0xb8,0x73,0xa7,0xf5,0x04,0xe4,0x39,0x95);
DEFINE_GUID(IID_ID3D12CommandListRaytracingPrototype,0x3c69787a,0x28fa,0x4701,0x97,0x0a,0x37,0xa1,0xed,0x1f,0x9c,0xab);
DEFINE_GUID(IID_ID3D12DeviceMetaCommand,0x547e33c7,0xff86,0x4cd9,0xbe,0xa3,0x5d,0x4a,0x28,0x37,0x53,0x96);
DEFINE_GUID(IID_ID3D12MetaCommand,0x8AFDA767,0x8003,0x494F,0x9E,0x9A,0x4A,0xA8,0x86,0x4F,0x35,0x24);
DEFINE_GUID(IID_ID3D12CommandListMetaCommand,0x5A5F59F3,0x7124,0x4766,0x8E,0x9E,0xCB,0x63,0x77,0x64,0xFB,0x0B);


extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12_1_0000_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


