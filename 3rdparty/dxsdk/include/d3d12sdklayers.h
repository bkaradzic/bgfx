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

#ifndef __d3d12sdklayers_h__
#define __d3d12sdklayers_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ID3D12Debug_FWD_DEFINED__
#define __ID3D12Debug_FWD_DEFINED__
typedef interface ID3D12Debug ID3D12Debug;

#endif 	/* __ID3D12Debug_FWD_DEFINED__ */


#ifndef __ID3D12Debug1_FWD_DEFINED__
#define __ID3D12Debug1_FWD_DEFINED__
typedef interface ID3D12Debug1 ID3D12Debug1;

#endif 	/* __ID3D12Debug1_FWD_DEFINED__ */


#ifndef __ID3D12Debug2_FWD_DEFINED__
#define __ID3D12Debug2_FWD_DEFINED__
typedef interface ID3D12Debug2 ID3D12Debug2;

#endif 	/* __ID3D12Debug2_FWD_DEFINED__ */


#ifndef __ID3D12Debug3_FWD_DEFINED__
#define __ID3D12Debug3_FWD_DEFINED__
typedef interface ID3D12Debug3 ID3D12Debug3;

#endif 	/* __ID3D12Debug3_FWD_DEFINED__ */


#ifndef __ID3D12DebugDevice1_FWD_DEFINED__
#define __ID3D12DebugDevice1_FWD_DEFINED__
typedef interface ID3D12DebugDevice1 ID3D12DebugDevice1;

#endif 	/* __ID3D12DebugDevice1_FWD_DEFINED__ */


#ifndef __ID3D12DebugDevice_FWD_DEFINED__
#define __ID3D12DebugDevice_FWD_DEFINED__
typedef interface ID3D12DebugDevice ID3D12DebugDevice;

#endif 	/* __ID3D12DebugDevice_FWD_DEFINED__ */


#ifndef __ID3D12DebugDevice2_FWD_DEFINED__
#define __ID3D12DebugDevice2_FWD_DEFINED__
typedef interface ID3D12DebugDevice2 ID3D12DebugDevice2;

#endif 	/* __ID3D12DebugDevice2_FWD_DEFINED__ */


#ifndef __ID3D12DebugCommandQueue_FWD_DEFINED__
#define __ID3D12DebugCommandQueue_FWD_DEFINED__
typedef interface ID3D12DebugCommandQueue ID3D12DebugCommandQueue;

#endif 	/* __ID3D12DebugCommandQueue_FWD_DEFINED__ */


#ifndef __ID3D12DebugCommandList1_FWD_DEFINED__
#define __ID3D12DebugCommandList1_FWD_DEFINED__
typedef interface ID3D12DebugCommandList1 ID3D12DebugCommandList1;

#endif 	/* __ID3D12DebugCommandList1_FWD_DEFINED__ */


#ifndef __ID3D12DebugCommandList_FWD_DEFINED__
#define __ID3D12DebugCommandList_FWD_DEFINED__
typedef interface ID3D12DebugCommandList ID3D12DebugCommandList;

#endif 	/* __ID3D12DebugCommandList_FWD_DEFINED__ */


#ifndef __ID3D12DebugCommandList2_FWD_DEFINED__
#define __ID3D12DebugCommandList2_FWD_DEFINED__
typedef interface ID3D12DebugCommandList2 ID3D12DebugCommandList2;

#endif 	/* __ID3D12DebugCommandList2_FWD_DEFINED__ */


#ifndef __ID3D12SharingContract_FWD_DEFINED__
#define __ID3D12SharingContract_FWD_DEFINED__
typedef interface ID3D12SharingContract ID3D12SharingContract;

#endif 	/* __ID3D12SharingContract_FWD_DEFINED__ */


#ifndef __ID3D12InfoQueue_FWD_DEFINED__
#define __ID3D12InfoQueue_FWD_DEFINED__
typedef interface ID3D12InfoQueue ID3D12InfoQueue;

#endif 	/* __ID3D12InfoQueue_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "d3d12.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_d3d12sdklayers_0000_0000 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D12Debug_INTERFACE_DEFINED__
#define __ID3D12Debug_INTERFACE_DEFINED__

/* interface ID3D12Debug */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12Debug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("344488b7-6846-474b-b989-f027448245e0")
    ID3D12Debug : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE EnableDebugLayer( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12Debug * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12Debug * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12Debug * This);
        
        void ( STDMETHODCALLTYPE *EnableDebugLayer )( 
            ID3D12Debug * This);
        
        END_INTERFACE
    } ID3D12DebugVtbl;

    interface ID3D12Debug
    {
        CONST_VTBL struct ID3D12DebugVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12Debug_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12Debug_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12Debug_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12Debug_EnableDebugLayer(This)	\
    ( (This)->lpVtbl -> EnableDebugLayer(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12Debug_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0001 */
/* [local] */ 

typedef 
enum D3D12_GPU_BASED_VALIDATION_FLAGS
    {
        D3D12_GPU_BASED_VALIDATION_FLAGS_NONE	= 0,
        D3D12_GPU_BASED_VALIDATION_FLAGS_DISABLE_STATE_TRACKING	= 0x1
    } 	D3D12_GPU_BASED_VALIDATION_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_GPU_BASED_VALIDATION_FLAGS)


extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0001_v0_0_s_ifspec;

#ifndef __ID3D12Debug1_INTERFACE_DEFINED__
#define __ID3D12Debug1_INTERFACE_DEFINED__

/* interface ID3D12Debug1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12Debug1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("affaa4ca-63fe-4d8e-b8ad-159000af4304")
    ID3D12Debug1 : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE EnableDebugLayer( void) = 0;
        
        virtual void STDMETHODCALLTYPE SetEnableGPUBasedValidation( 
            BOOL Enable) = 0;
        
        virtual void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation( 
            BOOL Enable) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12Debug1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12Debug1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12Debug1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12Debug1 * This);
        
        void ( STDMETHODCALLTYPE *EnableDebugLayer )( 
            ID3D12Debug1 * This);
        
        void ( STDMETHODCALLTYPE *SetEnableGPUBasedValidation )( 
            ID3D12Debug1 * This,
            BOOL Enable);
        
        void ( STDMETHODCALLTYPE *SetEnableSynchronizedCommandQueueValidation )( 
            ID3D12Debug1 * This,
            BOOL Enable);
        
        END_INTERFACE
    } ID3D12Debug1Vtbl;

    interface ID3D12Debug1
    {
        CONST_VTBL struct ID3D12Debug1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12Debug1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12Debug1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12Debug1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12Debug1_EnableDebugLayer(This)	\
    ( (This)->lpVtbl -> EnableDebugLayer(This) ) 

#define ID3D12Debug1_SetEnableGPUBasedValidation(This,Enable)	\
    ( (This)->lpVtbl -> SetEnableGPUBasedValidation(This,Enable) ) 

#define ID3D12Debug1_SetEnableSynchronizedCommandQueueValidation(This,Enable)	\
    ( (This)->lpVtbl -> SetEnableSynchronizedCommandQueueValidation(This,Enable) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12Debug1_INTERFACE_DEFINED__ */


#ifndef __ID3D12Debug2_INTERFACE_DEFINED__
#define __ID3D12Debug2_INTERFACE_DEFINED__

/* interface ID3D12Debug2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12Debug2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93a665c4-a3b2-4e5d-b692-a26ae14e3374")
    ID3D12Debug2 : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE SetGPUBasedValidationFlags( 
            D3D12_GPU_BASED_VALIDATION_FLAGS Flags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12Debug2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12Debug2 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12Debug2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12Debug2 * This);
        
        void ( STDMETHODCALLTYPE *SetGPUBasedValidationFlags )( 
            ID3D12Debug2 * This,
            D3D12_GPU_BASED_VALIDATION_FLAGS Flags);
        
        END_INTERFACE
    } ID3D12Debug2Vtbl;

    interface ID3D12Debug2
    {
        CONST_VTBL struct ID3D12Debug2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12Debug2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12Debug2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12Debug2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12Debug2_SetGPUBasedValidationFlags(This,Flags)	\
    ( (This)->lpVtbl -> SetGPUBasedValidationFlags(This,Flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12Debug2_INTERFACE_DEFINED__ */


#ifndef __ID3D12Debug3_INTERFACE_DEFINED__
#define __ID3D12Debug3_INTERFACE_DEFINED__

/* interface ID3D12Debug3 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12Debug3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5cf4e58f-f671-4ff1-a542-3686e3d153d1")
    ID3D12Debug3 : public ID3D12Debug
    {
    public:
        virtual void STDMETHODCALLTYPE SetEnableGPUBasedValidation( 
            BOOL Enable) = 0;
        
        virtual void STDMETHODCALLTYPE SetEnableSynchronizedCommandQueueValidation( 
            BOOL Enable) = 0;
        
        virtual void STDMETHODCALLTYPE SetGPUBasedValidationFlags( 
            D3D12_GPU_BASED_VALIDATION_FLAGS Flags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12Debug3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12Debug3 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12Debug3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12Debug3 * This);
        
        void ( STDMETHODCALLTYPE *EnableDebugLayer )( 
            ID3D12Debug3 * This);
        
        void ( STDMETHODCALLTYPE *SetEnableGPUBasedValidation )( 
            ID3D12Debug3 * This,
            BOOL Enable);
        
        void ( STDMETHODCALLTYPE *SetEnableSynchronizedCommandQueueValidation )( 
            ID3D12Debug3 * This,
            BOOL Enable);
        
        void ( STDMETHODCALLTYPE *SetGPUBasedValidationFlags )( 
            ID3D12Debug3 * This,
            D3D12_GPU_BASED_VALIDATION_FLAGS Flags);
        
        END_INTERFACE
    } ID3D12Debug3Vtbl;

    interface ID3D12Debug3
    {
        CONST_VTBL struct ID3D12Debug3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12Debug3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12Debug3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12Debug3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12Debug3_EnableDebugLayer(This)	\
    ( (This)->lpVtbl -> EnableDebugLayer(This) ) 


#define ID3D12Debug3_SetEnableGPUBasedValidation(This,Enable)	\
    ( (This)->lpVtbl -> SetEnableGPUBasedValidation(This,Enable) ) 

#define ID3D12Debug3_SetEnableSynchronizedCommandQueueValidation(This,Enable)	\
    ( (This)->lpVtbl -> SetEnableSynchronizedCommandQueueValidation(This,Enable) ) 

#define ID3D12Debug3_SetGPUBasedValidationFlags(This,Flags)	\
    ( (This)->lpVtbl -> SetGPUBasedValidationFlags(This,Flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12Debug3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0004 */
/* [local] */ 

typedef 
enum D3D12_RLDO_FLAGS
    {
        D3D12_RLDO_NONE	= 0,
        D3D12_RLDO_SUMMARY	= 0x1,
        D3D12_RLDO_DETAIL	= 0x2,
        D3D12_RLDO_IGNORE_INTERNAL	= 0x4
    } 	D3D12_RLDO_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_RLDO_FLAGS)
typedef 
enum D3D12_DEBUG_DEVICE_PARAMETER_TYPE
    {
        D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS	= 0,
        D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS	= ( D3D12_DEBUG_DEVICE_PARAMETER_FEATURE_FLAGS + 1 ) ,
        D3D12_DEBUG_DEVICE_PARAMETER_GPU_SLOWDOWN_PERFORMANCE_FACTOR	= ( D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS + 1 ) 
    } 	D3D12_DEBUG_DEVICE_PARAMETER_TYPE;

typedef 
enum D3D12_DEBUG_FEATURE
    {
        D3D12_DEBUG_FEATURE_NONE	= 0,
        D3D12_DEBUG_FEATURE_ALLOW_BEHAVIOR_CHANGING_DEBUG_AIDS	= 0x1,
        D3D12_DEBUG_FEATURE_CONSERVATIVE_RESOURCE_STATE_TRACKING	= 0x2,
        D3D12_DEBUG_FEATURE_DISABLE_VIRTUALIZED_BUNDLES_VALIDATION	= 0x4,
        D3D12_DEBUG_FEATURE_EMULATE_WINDOWS7	= 0x8
    } 	D3D12_DEBUG_FEATURE;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_DEBUG_FEATURE)
typedef 
enum D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE
    {
        D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_NONE	= 0,
        D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_STATE_TRACKING_ONLY	= ( D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_NONE + 1 ) ,
        D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_UNGUARDED_VALIDATION	= ( D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_STATE_TRACKING_ONLY + 1 ) ,
        D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_GUARDED_VALIDATION	= ( D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_UNGUARDED_VALIDATION + 1 ) ,
        NUM_D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODES	= ( D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE_GUARDED_VALIDATION + 1 ) 
    } 	D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE;

typedef 
enum D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAGS
    {
        D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAG_NONE	= 0,
        D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAG_FRONT_LOAD_CREATE_TRACKING_ONLY_SHADERS	= 0x1,
        D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAG_FRONT_LOAD_CREATE_UNGUARDED_VALIDATION_SHADERS	= 0x2,
        D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAG_FRONT_LOAD_CREATE_GUARDED_VALIDATION_SHADERS	= 0x4,
        D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAGS_VALID_MASK	= 0x7
    } 	D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAGS)
typedef struct D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS
    {
    UINT MaxMessagesPerCommandList;
    D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE DefaultShaderPatchMode;
    D3D12_GPU_BASED_VALIDATION_PIPELINE_STATE_CREATE_FLAGS PipelineStateCreateFlags;
    } 	D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS;

typedef struct D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR
    {
    FLOAT SlowdownFactor;
    } 	D3D12_DEBUG_DEVICE_GPU_SLOWDOWN_PERFORMANCE_FACTOR;



extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0004_v0_0_s_ifspec;

#ifndef __ID3D12DebugDevice1_INTERFACE_DEFINED__
#define __ID3D12DebugDevice1_INTERFACE_DEFINED__

/* interface ID3D12DebugDevice1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugDevice1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a9b71770-d099-4a65-a698-3dee10020f88")
    ID3D12DebugDevice1 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDebugParameter( 
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDebugParameter( 
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects( 
            D3D12_RLDO_FLAGS Flags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugDevice1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugDevice1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugDevice1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugDevice1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDebugParameter )( 
            ID3D12DebugDevice1 * This,
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetDebugParameter )( 
            ID3D12DebugDevice1 * This,
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLiveDeviceObjects )( 
            ID3D12DebugDevice1 * This,
            D3D12_RLDO_FLAGS Flags);
        
        END_INTERFACE
    } ID3D12DebugDevice1Vtbl;

    interface ID3D12DebugDevice1
    {
        CONST_VTBL struct ID3D12DebugDevice1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugDevice1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugDevice1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugDevice1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugDevice1_SetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> SetDebugParameter(This,Type,pData,DataSize) ) 

#define ID3D12DebugDevice1_GetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> GetDebugParameter(This,Type,pData,DataSize) ) 

#define ID3D12DebugDevice1_ReportLiveDeviceObjects(This,Flags)	\
    ( (This)->lpVtbl -> ReportLiveDeviceObjects(This,Flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugDevice1_INTERFACE_DEFINED__ */


#ifndef __ID3D12DebugDevice_INTERFACE_DEFINED__
#define __ID3D12DebugDevice_INTERFACE_DEFINED__

/* interface ID3D12DebugDevice */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3febd6dd-4973-4787-8194-e45f9e28923e")
    ID3D12DebugDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFeatureMask( 
            D3D12_DEBUG_FEATURE Mask) = 0;
        
        virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportLiveDeviceObjects( 
            D3D12_RLDO_FLAGS Flags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugDevice * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFeatureMask )( 
            ID3D12DebugDevice * This,
            D3D12_DEBUG_FEATURE Mask);
        
        D3D12_DEBUG_FEATURE ( STDMETHODCALLTYPE *GetFeatureMask )( 
            ID3D12DebugDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLiveDeviceObjects )( 
            ID3D12DebugDevice * This,
            D3D12_RLDO_FLAGS Flags);
        
        END_INTERFACE
    } ID3D12DebugDeviceVtbl;

    interface ID3D12DebugDevice
    {
        CONST_VTBL struct ID3D12DebugDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugDevice_SetFeatureMask(This,Mask)	\
    ( (This)->lpVtbl -> SetFeatureMask(This,Mask) ) 

#define ID3D12DebugDevice_GetFeatureMask(This)	\
    ( (This)->lpVtbl -> GetFeatureMask(This) ) 

#define ID3D12DebugDevice_ReportLiveDeviceObjects(This,Flags)	\
    ( (This)->lpVtbl -> ReportLiveDeviceObjects(This,Flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugDevice_INTERFACE_DEFINED__ */


#ifndef __ID3D12DebugDevice2_INTERFACE_DEFINED__
#define __ID3D12DebugDevice2_INTERFACE_DEFINED__

/* interface ID3D12DebugDevice2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugDevice2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("60eccbc1-378d-4df1-894c-f8ac5ce4d7dd")
    ID3D12DebugDevice2 : public ID3D12DebugDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDebugParameter( 
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDebugParameter( 
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugDevice2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugDevice2 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugDevice2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugDevice2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFeatureMask )( 
            ID3D12DebugDevice2 * This,
            D3D12_DEBUG_FEATURE Mask);
        
        D3D12_DEBUG_FEATURE ( STDMETHODCALLTYPE *GetFeatureMask )( 
            ID3D12DebugDevice2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLiveDeviceObjects )( 
            ID3D12DebugDevice2 * This,
            D3D12_RLDO_FLAGS Flags);
        
        HRESULT ( STDMETHODCALLTYPE *SetDebugParameter )( 
            ID3D12DebugDevice2 * This,
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetDebugParameter )( 
            ID3D12DebugDevice2 * This,
            D3D12_DEBUG_DEVICE_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize);
        
        END_INTERFACE
    } ID3D12DebugDevice2Vtbl;

    interface ID3D12DebugDevice2
    {
        CONST_VTBL struct ID3D12DebugDevice2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugDevice2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugDevice2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugDevice2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugDevice2_SetFeatureMask(This,Mask)	\
    ( (This)->lpVtbl -> SetFeatureMask(This,Mask) ) 

#define ID3D12DebugDevice2_GetFeatureMask(This)	\
    ( (This)->lpVtbl -> GetFeatureMask(This) ) 

#define ID3D12DebugDevice2_ReportLiveDeviceObjects(This,Flags)	\
    ( (This)->lpVtbl -> ReportLiveDeviceObjects(This,Flags) ) 


#define ID3D12DebugDevice2_SetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> SetDebugParameter(This,Type,pData,DataSize) ) 

#define ID3D12DebugDevice2_GetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> GetDebugParameter(This,Type,pData,DataSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugDevice2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0007 */
/* [local] */ 

DEFINE_GUID(DXGI_DEBUG_D3D12, 0xcf59a98c, 0xa950, 0x4326, 0x91, 0xef, 0x9b, 0xba, 0xa1, 0x7b, 0xfd, 0x95);


extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0007_v0_0_s_ifspec;

#ifndef __ID3D12DebugCommandQueue_INTERFACE_DEFINED__
#define __ID3D12DebugCommandQueue_INTERFACE_DEFINED__

/* interface ID3D12DebugCommandQueue */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugCommandQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09e0bf36-54ac-484f-8847-4baeeab6053a")
    ID3D12DebugCommandQueue : public IUnknown
    {
    public:
        virtual BOOL STDMETHODCALLTYPE AssertResourceState( 
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugCommandQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugCommandQueue * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugCommandQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugCommandQueue * This);
        
        BOOL ( STDMETHODCALLTYPE *AssertResourceState )( 
            ID3D12DebugCommandQueue * This,
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State);
        
        END_INTERFACE
    } ID3D12DebugCommandQueueVtbl;

    interface ID3D12DebugCommandQueue
    {
        CONST_VTBL struct ID3D12DebugCommandQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugCommandQueue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugCommandQueue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugCommandQueue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugCommandQueue_AssertResourceState(This,pResource,Subresource,State)	\
    ( (This)->lpVtbl -> AssertResourceState(This,pResource,Subresource,State) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugCommandQueue_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0008 */
/* [local] */ 

typedef 
enum D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE
    {
        D3D12_DEBUG_COMMAND_LIST_PARAMETER_GPU_BASED_VALIDATION_SETTINGS	= 0
    } 	D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE;

typedef struct D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS
    {
    D3D12_GPU_BASED_VALIDATION_SHADER_PATCH_MODE ShaderPatchMode;
    } 	D3D12_DEBUG_COMMAND_LIST_GPU_BASED_VALIDATION_SETTINGS;



extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0008_v0_0_s_ifspec;

#ifndef __ID3D12DebugCommandList1_INTERFACE_DEFINED__
#define __ID3D12DebugCommandList1_INTERFACE_DEFINED__

/* interface ID3D12DebugCommandList1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugCommandList1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("102ca951-311b-4b01-b11f-ecb83e061b37")
    ID3D12DebugCommandList1 : public IUnknown
    {
    public:
        virtual BOOL STDMETHODCALLTYPE AssertResourceState( 
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDebugParameter( 
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDebugParameter( 
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugCommandList1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugCommandList1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugCommandList1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugCommandList1 * This);
        
        BOOL ( STDMETHODCALLTYPE *AssertResourceState )( 
            ID3D12DebugCommandList1 * This,
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State);
        
        HRESULT ( STDMETHODCALLTYPE *SetDebugParameter )( 
            ID3D12DebugCommandList1 * This,
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetDebugParameter )( 
            ID3D12DebugCommandList1 * This,
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize);
        
        END_INTERFACE
    } ID3D12DebugCommandList1Vtbl;

    interface ID3D12DebugCommandList1
    {
        CONST_VTBL struct ID3D12DebugCommandList1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugCommandList1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugCommandList1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugCommandList1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugCommandList1_AssertResourceState(This,pResource,Subresource,State)	\
    ( (This)->lpVtbl -> AssertResourceState(This,pResource,Subresource,State) ) 

#define ID3D12DebugCommandList1_SetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> SetDebugParameter(This,Type,pData,DataSize) ) 

#define ID3D12DebugCommandList1_GetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> GetDebugParameter(This,Type,pData,DataSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugCommandList1_INTERFACE_DEFINED__ */


#ifndef __ID3D12DebugCommandList_INTERFACE_DEFINED__
#define __ID3D12DebugCommandList_INTERFACE_DEFINED__

/* interface ID3D12DebugCommandList */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugCommandList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09e0bf36-54ac-484f-8847-4baeeab6053f")
    ID3D12DebugCommandList : public IUnknown
    {
    public:
        virtual BOOL STDMETHODCALLTYPE AssertResourceState( 
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFeatureMask( 
            D3D12_DEBUG_FEATURE Mask) = 0;
        
        virtual D3D12_DEBUG_FEATURE STDMETHODCALLTYPE GetFeatureMask( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugCommandListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugCommandList * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugCommandList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugCommandList * This);
        
        BOOL ( STDMETHODCALLTYPE *AssertResourceState )( 
            ID3D12DebugCommandList * This,
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State);
        
        HRESULT ( STDMETHODCALLTYPE *SetFeatureMask )( 
            ID3D12DebugCommandList * This,
            D3D12_DEBUG_FEATURE Mask);
        
        D3D12_DEBUG_FEATURE ( STDMETHODCALLTYPE *GetFeatureMask )( 
            ID3D12DebugCommandList * This);
        
        END_INTERFACE
    } ID3D12DebugCommandListVtbl;

    interface ID3D12DebugCommandList
    {
        CONST_VTBL struct ID3D12DebugCommandListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugCommandList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugCommandList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugCommandList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugCommandList_AssertResourceState(This,pResource,Subresource,State)	\
    ( (This)->lpVtbl -> AssertResourceState(This,pResource,Subresource,State) ) 

#define ID3D12DebugCommandList_SetFeatureMask(This,Mask)	\
    ( (This)->lpVtbl -> SetFeatureMask(This,Mask) ) 

#define ID3D12DebugCommandList_GetFeatureMask(This)	\
    ( (This)->lpVtbl -> GetFeatureMask(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugCommandList_INTERFACE_DEFINED__ */


#ifndef __ID3D12DebugCommandList2_INTERFACE_DEFINED__
#define __ID3D12DebugCommandList2_INTERFACE_DEFINED__

/* interface ID3D12DebugCommandList2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12DebugCommandList2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aeb575cf-4e06-48be-ba3b-c450fc96652e")
    ID3D12DebugCommandList2 : public ID3D12DebugCommandList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDebugParameter( 
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDebugParameter( 
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12DebugCommandList2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12DebugCommandList2 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12DebugCommandList2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12DebugCommandList2 * This);
        
        BOOL ( STDMETHODCALLTYPE *AssertResourceState )( 
            ID3D12DebugCommandList2 * This,
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            UINT State);
        
        HRESULT ( STDMETHODCALLTYPE *SetFeatureMask )( 
            ID3D12DebugCommandList2 * This,
            D3D12_DEBUG_FEATURE Mask);
        
        D3D12_DEBUG_FEATURE ( STDMETHODCALLTYPE *GetFeatureMask )( 
            ID3D12DebugCommandList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetDebugParameter )( 
            ID3D12DebugCommandList2 * This,
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _In_reads_bytes_(DataSize)  const void *pData,
            UINT DataSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetDebugParameter )( 
            ID3D12DebugCommandList2 * This,
            D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE Type,
            _Out_writes_bytes_(DataSize)  void *pData,
            UINT DataSize);
        
        END_INTERFACE
    } ID3D12DebugCommandList2Vtbl;

    interface ID3D12DebugCommandList2
    {
        CONST_VTBL struct ID3D12DebugCommandList2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12DebugCommandList2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12DebugCommandList2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12DebugCommandList2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12DebugCommandList2_AssertResourceState(This,pResource,Subresource,State)	\
    ( (This)->lpVtbl -> AssertResourceState(This,pResource,Subresource,State) ) 

#define ID3D12DebugCommandList2_SetFeatureMask(This,Mask)	\
    ( (This)->lpVtbl -> SetFeatureMask(This,Mask) ) 

#define ID3D12DebugCommandList2_GetFeatureMask(This)	\
    ( (This)->lpVtbl -> GetFeatureMask(This) ) 


#define ID3D12DebugCommandList2_SetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> SetDebugParameter(This,Type,pData,DataSize) ) 

#define ID3D12DebugCommandList2_GetDebugParameter(This,Type,pData,DataSize)	\
    ( (This)->lpVtbl -> GetDebugParameter(This,Type,pData,DataSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12DebugCommandList2_INTERFACE_DEFINED__ */


#ifndef __ID3D12SharingContract_INTERFACE_DEFINED__
#define __ID3D12SharingContract_INTERFACE_DEFINED__

/* interface ID3D12SharingContract */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12SharingContract;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0adf7d52-929c-4e61-addb-ffed30de66ef")
    ID3D12SharingContract : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE Present( 
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            _In_  HWND window) = 0;
        
        virtual void STDMETHODCALLTYPE SharedFenceSignal( 
            _In_  ID3D12Fence *pFence,
            UINT64 FenceValue) = 0;
        
        virtual void STDMETHODCALLTYPE BeginCapturableWork( 
            _In_  REFGUID guid) = 0;
        
        virtual void STDMETHODCALLTYPE EndCapturableWork( 
            _In_  REFGUID guid) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12SharingContractVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12SharingContract * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12SharingContract * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12SharingContract * This);
        
        void ( STDMETHODCALLTYPE *Present )( 
            ID3D12SharingContract * This,
            _In_  ID3D12Resource *pResource,
            UINT Subresource,
            _In_  HWND window);
        
        void ( STDMETHODCALLTYPE *SharedFenceSignal )( 
            ID3D12SharingContract * This,
            _In_  ID3D12Fence *pFence,
            UINT64 FenceValue);
        
        void ( STDMETHODCALLTYPE *BeginCapturableWork )( 
            ID3D12SharingContract * This,
            _In_  REFGUID guid);
        
        void ( STDMETHODCALLTYPE *EndCapturableWork )( 
            ID3D12SharingContract * This,
            _In_  REFGUID guid);
        
        END_INTERFACE
    } ID3D12SharingContractVtbl;

    interface ID3D12SharingContract
    {
        CONST_VTBL struct ID3D12SharingContractVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12SharingContract_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12SharingContract_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12SharingContract_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12SharingContract_Present(This,pResource,Subresource,window)	\
    ( (This)->lpVtbl -> Present(This,pResource,Subresource,window) ) 

#define ID3D12SharingContract_SharedFenceSignal(This,pFence,FenceValue)	\
    ( (This)->lpVtbl -> SharedFenceSignal(This,pFence,FenceValue) ) 

#define ID3D12SharingContract_BeginCapturableWork(This,guid)	\
    ( (This)->lpVtbl -> BeginCapturableWork(This,guid) ) 

#define ID3D12SharingContract_EndCapturableWork(This,guid)	\
    ( (This)->lpVtbl -> EndCapturableWork(This,guid) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12SharingContract_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0012 */
/* [local] */ 

typedef 
enum D3D12_MESSAGE_CATEGORY
    {
        D3D12_MESSAGE_CATEGORY_APPLICATION_DEFINED	= 0,
        D3D12_MESSAGE_CATEGORY_MISCELLANEOUS	= ( D3D12_MESSAGE_CATEGORY_APPLICATION_DEFINED + 1 ) ,
        D3D12_MESSAGE_CATEGORY_INITIALIZATION	= ( D3D12_MESSAGE_CATEGORY_MISCELLANEOUS + 1 ) ,
        D3D12_MESSAGE_CATEGORY_CLEANUP	= ( D3D12_MESSAGE_CATEGORY_INITIALIZATION + 1 ) ,
        D3D12_MESSAGE_CATEGORY_COMPILATION	= ( D3D12_MESSAGE_CATEGORY_CLEANUP + 1 ) ,
        D3D12_MESSAGE_CATEGORY_STATE_CREATION	= ( D3D12_MESSAGE_CATEGORY_COMPILATION + 1 ) ,
        D3D12_MESSAGE_CATEGORY_STATE_SETTING	= ( D3D12_MESSAGE_CATEGORY_STATE_CREATION + 1 ) ,
        D3D12_MESSAGE_CATEGORY_STATE_GETTING	= ( D3D12_MESSAGE_CATEGORY_STATE_SETTING + 1 ) ,
        D3D12_MESSAGE_CATEGORY_RESOURCE_MANIPULATION	= ( D3D12_MESSAGE_CATEGORY_STATE_GETTING + 1 ) ,
        D3D12_MESSAGE_CATEGORY_EXECUTION	= ( D3D12_MESSAGE_CATEGORY_RESOURCE_MANIPULATION + 1 ) ,
        D3D12_MESSAGE_CATEGORY_SHADER	= ( D3D12_MESSAGE_CATEGORY_EXECUTION + 1 ) 
    } 	D3D12_MESSAGE_CATEGORY;

typedef 
enum D3D12_MESSAGE_SEVERITY
    {
        D3D12_MESSAGE_SEVERITY_CORRUPTION	= 0,
        D3D12_MESSAGE_SEVERITY_ERROR	= ( D3D12_MESSAGE_SEVERITY_CORRUPTION + 1 ) ,
        D3D12_MESSAGE_SEVERITY_WARNING	= ( D3D12_MESSAGE_SEVERITY_ERROR + 1 ) ,
        D3D12_MESSAGE_SEVERITY_INFO	= ( D3D12_MESSAGE_SEVERITY_WARNING + 1 ) ,
        D3D12_MESSAGE_SEVERITY_MESSAGE	= ( D3D12_MESSAGE_SEVERITY_INFO + 1 ) 
    } 	D3D12_MESSAGE_SEVERITY;

typedef 
enum D3D12_MESSAGE_ID
    {
        D3D12_MESSAGE_ID_UNKNOWN	= 0,
        D3D12_MESSAGE_ID_STRING_FROM_APPLICATION	= ( D3D12_MESSAGE_ID_UNKNOWN + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_THIS	= ( D3D12_MESSAGE_ID_STRING_FROM_APPLICATION + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER1	= ( D3D12_MESSAGE_ID_CORRUPTED_THIS + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER2	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER1 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER3	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER2 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER4	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER3 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER5	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER4 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER6	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER5 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER7	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER6 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER8	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER7 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER9	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER8 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER10	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER9 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER11	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER10 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER12	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER11 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER13	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER12 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER14	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER13 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_PARAMETER15	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER14 + 1 ) ,
        D3D12_MESSAGE_ID_CORRUPTED_MULTITHREADING	= ( D3D12_MESSAGE_ID_CORRUPTED_PARAMETER15 + 1 ) ,
        D3D12_MESSAGE_ID_MESSAGE_REPORTING_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CORRUPTED_MULTITHREADING + 1 ) ,
        D3D12_MESSAGE_ID_GETPRIVATEDATA_MOREDATA	= ( D3D12_MESSAGE_ID_MESSAGE_REPORTING_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDFREEDATA	= ( D3D12_MESSAGE_ID_GETPRIVATEDATA_MOREDATA + 1 ) ,
        D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDIUNKNOWN	= ( D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDFREEDATA + 1 ) ,
        D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDIUNKNOWN + 1 ) ,
        D3D12_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS	= ( D3D12_MESSAGE_ID_SETPRIVATEDATA_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_SETPRIVATEDATA_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_UNRECOGNIZEDFORMAT	= ( D3D12_MESSAGE_ID_SETPRIVATEDATA_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDDESC	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_UNRECOGNIZEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDVIDEOPLANESLICE	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDPLANESLICE	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDVIDEOPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_UNRECOGNIZEDFORMAT	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_UNSUPPORTEDFORMAT	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_UNRECOGNIZEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDDESC	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_UNSUPPORTEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDVIDEOPLANESLICE	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDPLANESLICE	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDVIDEOPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_UNRECOGNIZEDFORMAT	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDDESC	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_UNRECOGNIZEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TOOMANYELEMENTS	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TOOMANYELEMENTS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INCOMPATIBLEFORMAT	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSLOT	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INCOMPATIBLEFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDINPUTSLOTCLASS	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSLOT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_STEPRATESLOTCLASSMISMATCH	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDINPUTSLOTCLASS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSLOTCLASSCHANGE	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_STEPRATESLOTCLASSMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSTEPRATECHANGE	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSLOTCLASSCHANGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDALIGNMENT	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDSTEPRATECHANGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_DUPLICATESEMANTIC	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_INVALIDALIGNMENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_UNPARSEABLEINPUTSIGNATURE	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_DUPLICATESEMANTIC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_NULLSEMANTIC	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_UNPARSEABLEINPUTSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_MISSINGELEMENT	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_NULLSEMANTIC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVERTEXSHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_MISSINGELEMENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEVERTEXSHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMENTRIES	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTPUTSTREAMSTRIDEUNUSED	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMENTRIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDDECL	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTPUTSTREAMSTRIDEUNUSED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_EXPECTEDDECL	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDDECL + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTPUTSLOT0EXPECTED	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_EXPECTEDDECL + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDOUTPUTSLOT	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_OUTPUTSLOT0EXPECTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_ONLYONEELEMENTPERSLOT	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDOUTPUTSLOT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDCOMPONENTCOUNT	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_ONLYONEELEMENTPERSLOT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTARTCOMPONENTANDCOMPONENTCOUNT	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDCOMPONENTCOUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDGAPDEFINITION	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTARTCOMPONENTANDCOMPONENTCOUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_REPEATEDOUTPUT	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDGAPDEFINITION + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDOUTPUTSTREAMSTRIDE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_REPEATEDOUTPUT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MISSINGSEMANTIC	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDOUTPUTSTREAMSTRIDE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MASKMISMATCH	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MISSINGSEMANTIC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_CANTHAVEONLYGAPS	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MASKMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DECLTOOCOMPLEX	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_CANTHAVEONLYGAPS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MISSINGOUTPUTSIGNATURE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DECLTOOCOMPLEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIXELSHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_MISSINGOUTPUTSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEPIXELSHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDFILLMODE	= ( D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDCULLMODE	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDFILLMODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDDEPTHBIASCLAMP	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDCULLMODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDSLOPESCALEDDEPTHBIAS	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDDEPTHBIASCLAMP + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_NULLDESC	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDSLOPESCALEDDEPTHBIAS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDDEPTHWRITEMASK	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_NULLDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDDEPTHFUNC	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDDEPTHWRITEMASK + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILFAILOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDDEPTHFUNC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILZFAILOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILFAILOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILPASSOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILZFAILOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILFUNC	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILPASSOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILFAILOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDFRONTFACESTENCILFUNC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILZFAILOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILFAILOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILPASSOP	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILZFAILOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILFUNC	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILPASSOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_NULLDESC	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_INVALIDBACKFACESTENCILFUNC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDSRCBLEND	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_NULLDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDDESTBLEND	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDSRCBLEND + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDBLENDOP	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDDESTBLEND + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDSRCBLENDALPHA	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDBLENDOP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDDESTBLENDALPHA	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDSRCBLENDALPHA + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDBLENDOPALPHA	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDDESTBLENDALPHA + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDRENDERTARGETWRITEMASK	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDBLENDOPALPHA + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_NULLDESC	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDRENDERTARGETWRITEMASK + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDFILTER	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_NULLDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSU	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDFILTER + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSV	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSU + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSW	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSV + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMIPLODBIAS	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDADDRESSW + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMAXANISOTROPY	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMIPLODBIAS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDCOMPARISONFUNC	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMAXANISOTROPY + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMINLOD	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDCOMPARISONFUNC + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMAXLOD	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMINLOD + 1 ) ,
        D3D12_MESSAGE_ID_CREATESAMPLERSTATE_NULLDESC	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_INVALIDMAXLOD + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNRECOGNIZED	= ( D3D12_MESSAGE_ID_CREATESAMPLERSTATE_NULLDESC + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNDEFINED	= ( D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNRECOGNIZED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RSSETVIEWPORTS_INVALIDVIEWPORT	= ( D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNDEFINED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RSSETSCISSORRECTS_INVALIDSCISSOR	= ( D3D12_MESSAGE_ID_DEVICE_RSSETVIEWPORTS_INVALIDVIEWPORT + 1 ) ,
        D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_DENORMFLUSH	= ( D3D12_MESSAGE_ID_DEVICE_RSSETSCISSORRECTS_INVALIDSCISSOR + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_DENORMFLUSH	= ( D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_DENORMFLUSH + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_INVALID	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_DENORMFLUSH + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSOURCE	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDDESTINATIONSTATE	= ( D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSOURCESTATE	= ( D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDDESTINATIONSTATE + 1 ) ,
        D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONSUBRESOURCE	= ( D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSOURCESTATE + 1 ) ,
        D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONBOX	= ( D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONSTATE	= ( D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONBOX + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_DESTINATION_INVALID	= ( D3D12_MESSAGE_ID_UPDATESUBRESOURCE_INVALIDDESTINATIONSTATE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_DESTINATION_SUBRESOURCE_INVALID	= ( D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_DESTINATION_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_SOURCE_INVALID	= ( D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_DESTINATION_SUBRESOURCE_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_SOURCE_SUBRESOURCE_INVALID	= ( D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_SOURCE_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_FORMAT_INVALID	= ( D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_SOURCE_SUBRESOURCE_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_BUFFER_MAP_INVALIDMAPTYPE	= ( D3D12_MESSAGE_ID_DEVICE_RESOLVESUBRESOURCE_FORMAT_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_BUFFER_MAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_BUFFER_MAP_INVALIDMAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_BUFFER_MAP_ALREADYMAPPED	= ( D3D12_MESSAGE_ID_BUFFER_MAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_BUFFER_MAP_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_BUFFER_MAP_ALREADYMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_BUFFER_UNMAP_NOTMAPPED	= ( D3D12_MESSAGE_ID_BUFFER_MAP_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDMAPTYPE	= ( D3D12_MESSAGE_ID_BUFFER_UNMAP_NOTMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDMAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_MAP_ALREADYMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE1D_MAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_MAP_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_TEXTURE1D_MAP_ALREADYMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_UNMAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE1D_MAP_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE1D_UNMAP_NOTMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE1D_UNMAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDMAPTYPE	= ( D3D12_MESSAGE_ID_TEXTURE1D_UNMAP_NOTMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDMAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_MAP_ALREADYMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE2D_MAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_MAP_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_TEXTURE2D_MAP_ALREADYMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_UNMAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE2D_MAP_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE2D_UNMAP_NOTMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE2D_UNMAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDMAPTYPE	= ( D3D12_MESSAGE_ID_TEXTURE2D_UNMAP_NOTMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDMAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_MAP_ALREADYMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE3D_MAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_MAP_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_TEXTURE3D_MAP_ALREADYMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_UNMAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_TEXTURE3D_MAP_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_TEXTURE3D_UNMAP_NOTMAPPED	= ( D3D12_MESSAGE_ID_TEXTURE3D_UNMAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CHECKFORMATSUPPORT_FORMAT_DEPRECATED	= ( D3D12_MESSAGE_ID_TEXTURE3D_UNMAP_NOTMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_CHECKMULTISAMPLEQUALITYLEVELS_FORMAT_DEPRECATED	= ( D3D12_MESSAGE_ID_CHECKFORMATSUPPORT_FORMAT_DEPRECATED + 1 ) ,
        D3D12_MESSAGE_ID_SETEXCEPTIONMODE_UNRECOGNIZEDFLAGS	= ( D3D12_MESSAGE_ID_CHECKMULTISAMPLEQUALITYLEVELS_FORMAT_DEPRECATED + 1 ) ,
        D3D12_MESSAGE_ID_SETEXCEPTIONMODE_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_SETEXCEPTIONMODE_UNRECOGNIZEDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_SETEXCEPTIONMODE_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_SETEXCEPTIONMODE_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_REF_SIMULATING_INFINITELY_FAST_HARDWARE	= ( D3D12_MESSAGE_ID_SETEXCEPTIONMODE_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_REF_THREADING_MODE	= ( D3D12_MESSAGE_ID_REF_SIMULATING_INFINITELY_FAST_HARDWARE + 1 ) ,
        D3D12_MESSAGE_ID_REF_UMDRIVER_EXCEPTION	= ( D3D12_MESSAGE_ID_REF_THREADING_MODE + 1 ) ,
        D3D12_MESSAGE_ID_REF_KMDRIVER_EXCEPTION	= ( D3D12_MESSAGE_ID_REF_UMDRIVER_EXCEPTION + 1 ) ,
        D3D12_MESSAGE_ID_REF_HARDWARE_EXCEPTION	= ( D3D12_MESSAGE_ID_REF_KMDRIVER_EXCEPTION + 1 ) ,
        D3D12_MESSAGE_ID_REF_ACCESSING_INDEXABLE_TEMP_OUT_OF_RANGE	= ( D3D12_MESSAGE_ID_REF_HARDWARE_EXCEPTION + 1 ) ,
        D3D12_MESSAGE_ID_REF_PROBLEM_PARSING_SHADER	= ( D3D12_MESSAGE_ID_REF_ACCESSING_INDEXABLE_TEMP_OUT_OF_RANGE + 1 ) ,
        D3D12_MESSAGE_ID_REF_OUT_OF_MEMORY	= ( D3D12_MESSAGE_ID_REF_PROBLEM_PARSING_SHADER + 1 ) ,
        D3D12_MESSAGE_ID_REF_INFO	= ( D3D12_MESSAGE_ID_REF_OUT_OF_MEMORY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_VERTEXPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_REF_INFO + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDEXED_INDEXPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_VERTEXPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINSTANCED_VERTEXPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDEXED_INDEXPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINSTANCED_INSTANCEPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINSTANCED_VERTEXPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDEXEDINSTANCED_INSTANCEPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINSTANCED_INSTANCEPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDEXEDINSTANCED_INDEXPOS_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDEXEDINSTANCED_INSTANCEPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_VERTEX_SHADER_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDEXEDINSTANCED_INDEXPOS_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_SEMANTICNAME_NOT_FOUND	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_VERTEX_SHADER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_REGISTERINDEX	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_SEMANTICNAME_NOT_FOUND + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_COMPONENTTYPE	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_REGISTERINDEX + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_REGISTERMASK	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_COMPONENTTYPE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_SYSTEMVALUE	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_REGISTERMASK + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_NEVERWRITTEN_ALWAYSREADS	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_SYSTEMVALUE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_ROOT_SIGNATURE_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_NEVERWRITTEN_ALWAYSREADS + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_ROOT_SIGNATURE_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INPUTLAYOUT_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_CONSTANT_BUFFER_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INPUTLAYOUT_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_CONSTANT_BUFFER_TOO_SMALL	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_CONSTANT_BUFFER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SAMPLER_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_CONSTANT_BUFFER_TOO_SMALL + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SHADERRESOURCEVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SAMPLER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VIEW_DIMENSION_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SHADERRESOURCEVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_STRIDE_TOO_SMALL	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VIEW_DIMENSION_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_TOO_SMALL	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_STRIDE_TOO_SMALL + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_BUFFER_TOO_SMALL + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_FORMAT_INVALID	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_TOO_SMALL	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_FORMAT_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_GS_INPUT_PRIMITIVE_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_BUFFER_TOO_SMALL + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_RETURN_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_GS_INPUT_PRIMITIVE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_POSITION_NOT_PRESENT	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_RETURN_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OUTPUT_STREAM_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_POSITION_NOT_PRESENT + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_BOUND_RESOURCE_MAPPED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OUTPUT_STREAM_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INVALID_PRIMITIVETOPOLOGY	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_BOUND_RESOURCE_MAPPED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_OFFSET_UNALIGNED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INVALID_PRIMITIVETOPOLOGY + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_STRIDE_UNALIGNED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_OFFSET_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_OFFSET_UNALIGNED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_VERTEX_STRIDE_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OUTPUT_STREAM_OFFSET_UNALIGNED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_INDEX_OFFSET_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_LD_UNSUPPORTED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OUTPUT_STREAM_OFFSET_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_SAMPLE_UNSUPPORTED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_LD_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_SAMPLE_C_UNSUPPORTED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_SAMPLE_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_MULTISAMPLE_UNSUPPORTED	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_FORMAT_SAMPLE_C_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SO_TARGETS_BOUND_WITHOUT_SOURCE	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RESOURCE_MULTISAMPLE_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SO_STRIDE_LARGER_THAN_BUFFER	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SO_TARGETS_BOUND_WITHOUT_SOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OM_RENDER_TARGET_DOES_NOT_SUPPORT_BLENDING	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_SO_STRIDE_LARGER_THAN_BUFFER + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OM_DUAL_SOURCE_BLENDING_CAN_ONLY_HAVE_RENDER_TARGET_0	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OM_RENDER_TARGET_DOES_NOT_SUPPORT_BLENDING + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_AT_FAULT	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_OM_DUAL_SOURCE_BLENDING_CAN_ONLY_HAVE_RENDER_TARGET_0 + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_POSSIBLY_AT_FAULT	= ( D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_AT_FAULT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_NOT_AT_FAULT	= ( D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_POSSIBLY_AT_FAULT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_DEVICE_REMOVAL_PROCESS_NOT_AT_FAULT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_BADINTERFACE_RETURN	= ( D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_VIEWPORT_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_BADINTERFACE_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TRAILING_DIGIT_IN_SEMANTIC	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_VIEWPORT_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_TRAILING_DIGIT_IN_SEMANTIC	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TRAILING_DIGIT_IN_SEMANTIC + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_RSSETVIEWPORTS_DENORMFLUSH	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_TRAILING_DIGIT_IN_SEMANTIC + 1 ) ,
        D3D12_MESSAGE_ID_OMSETRENDERTARGETS_INVALIDVIEW	= ( D3D12_MESSAGE_ID_DEVICE_RSSETVIEWPORTS_DENORMFLUSH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SETTEXTFILTERSIZE_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_OMSETRENDERTARGETS_INVALIDVIEW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_SAMPLER_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_SETTEXTFILTERSIZE_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_SAMPLER_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_BLENDSTATE_GETDESC_LEGACY	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_SHADERRESOURCEVIEW_GETDESC_LEGACY	= ( D3D12_MESSAGE_ID_BLENDSTATE_GETDESC_LEGACY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_PS_OUTPUT_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_SHADERRESOURCEVIEW_GETDESC_LEGACY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_RESOURCE_FORMAT_GATHER_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_PS_OUTPUT_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_USE_OF_CENTER_MULTISAMPLE_PATTERN	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_RESOURCE_FORMAT_GATHER_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_IASETVERTEXBUFFERS_STRIDE_TOO_LARGE	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_USE_OF_CENTER_MULTISAMPLE_PATTERN + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_IASETVERTEXBUFFERS_INVALIDRANGE	= ( D3D12_MESSAGE_ID_DEVICE_IASETVERTEXBUFFERS_STRIDE_TOO_LARGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_EMPTY_LAYOUT	= ( D3D12_MESSAGE_ID_DEVICE_IASETVERTEXBUFFERS_INVALIDRANGE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_RESOURCE_SAMPLE_COUNT_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_EMPTY_LAYOUT + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_OBJECT_SUMMARY	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_RESOURCE_SAMPLE_COUNT_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_BUFFER	= ( D3D12_MESSAGE_ID_LIVE_OBJECT_SUMMARY + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_TEXTURE1D	= ( D3D12_MESSAGE_ID_LIVE_BUFFER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_TEXTURE2D	= ( D3D12_MESSAGE_ID_LIVE_TEXTURE1D + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_TEXTURE3D	= ( D3D12_MESSAGE_ID_LIVE_TEXTURE2D + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_SHADERRESOURCEVIEW	= ( D3D12_MESSAGE_ID_LIVE_TEXTURE3D + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_RENDERTARGETVIEW	= ( D3D12_MESSAGE_ID_LIVE_SHADERRESOURCEVIEW + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_DEPTHSTENCILVIEW	= ( D3D12_MESSAGE_ID_LIVE_RENDERTARGETVIEW + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VERTEXSHADER	= ( D3D12_MESSAGE_ID_LIVE_DEPTHSTENCILVIEW + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_GEOMETRYSHADER	= ( D3D12_MESSAGE_ID_LIVE_VERTEXSHADER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_PIXELSHADER	= ( D3D12_MESSAGE_ID_LIVE_GEOMETRYSHADER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_INPUTLAYOUT	= ( D3D12_MESSAGE_ID_LIVE_PIXELSHADER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_SAMPLER	= ( D3D12_MESSAGE_ID_LIVE_INPUTLAYOUT + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_BLENDSTATE	= ( D3D12_MESSAGE_ID_LIVE_SAMPLER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_DEPTHSTENCILSTATE	= ( D3D12_MESSAGE_ID_LIVE_BLENDSTATE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_RASTERIZERSTATE	= ( D3D12_MESSAGE_ID_LIVE_DEPTHSTENCILSTATE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_QUERY	= ( D3D12_MESSAGE_ID_LIVE_RASTERIZERSTATE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_PREDICATE	= ( D3D12_MESSAGE_ID_LIVE_QUERY + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_COUNTER	= ( D3D12_MESSAGE_ID_LIVE_PREDICATE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_DEVICE	= ( D3D12_MESSAGE_ID_LIVE_COUNTER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_SWAPCHAIN	= ( D3D12_MESSAGE_ID_LIVE_DEVICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_LIVE_SWAPCHAIN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILVIEW_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEVERTEXSHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMSTREAMS	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTREAMTORASTERIZER	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMSTREAMS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDSTREAMS	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTREAMTORASTERIZER + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDSTREAMS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTREAM	= ( D3D12_MESSAGE_ID_CREATEPIXELSHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDENTRIES	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDSTRIDES	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDENTRIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMSTRIDES	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UNEXPECTEDSTRIDES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDCALL	= ( D3D12_MESSAGE_ID_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_INVALIDNUMSTRIDES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHULLSHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDCALL + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEHULLSHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDCALL	= ( D3D12_MESSAGE_ID_CREATEHULLSHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDOMAINSHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDCALL + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATEDOMAINSHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDSHADERTYPE	= ( D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDSHADERTYPE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_HS_XOR_DS_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEDOMAINSHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_INVALID_ARG_BUFFER	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_HS_XOR_DS_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_OFFSET_UNALIGNED	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_INVALID_ARG_BUFFER + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_OFFSET_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_OFFSET_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDMAPTYPE	= ( D3D12_MESSAGE_ID_DEVICE_DRAWINDIRECT_OFFSET_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDMAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_ALREADYMAPPED	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_DEVICEREMOVED_RETURN	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_ALREADYMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_DEVICEREMOVED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_MAP_WITHOUT_INITIAL_DISCARD	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_UNMAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_RESOURCE_MAP_WITHOUT_INITIAL_DISCARD + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_UNMAP_NOTMAPPED	= ( D3D12_MESSAGE_ID_RESOURCE_UNMAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_RASTERIZING_CONTROL_POINTS	= ( D3D12_MESSAGE_ID_RESOURCE_UNMAP_NOTMAPPED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_RASTERIZING_CONTROL_POINTS + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_IASETPRIMITIVETOPOLOGY_TOPOLOGY_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_HULL_SHADER_INPUT_TOPOLOGY_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_CONTROL_POINT_COUNT_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_HULL_SHADER_INPUT_TOPOLOGY_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_TESSELLATOR_DOMAIN_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_CONTROL_POINT_COUNT_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_UNRECOGNIZED_FEATURE	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_HS_DS_TESSELLATOR_DOMAIN_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_MISMATCHED_DATA_SIZE	= ( D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_UNRECOGNIZED_FEATURE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_MISMATCHED_DATA_SIZE + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDCALL	= ( D3D12_MESSAGE_ID_DEVICE_CHECKFEATURESUPPORT_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTESHADER_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDCALL + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDSHADERBYTECODE	= ( D3D12_MESSAGE_ID_CREATECOMPUTESHADER_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDCLASSLINKAGE	= ( D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDSHADERBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSSETSHADERRESOURCES_VIEWS_EMPTY	= ( D3D12_MESSAGE_ID_CREATECOMPUTESHADER_INVALIDCLASSLINKAGE + 1 ) ,
        D3D12_MESSAGE_ID_CSSETCONSTANTBUFFERS_INVALIDBUFFER	= ( D3D12_MESSAGE_ID_DEVICE_CSSETSHADERRESOURCES_VIEWS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSSETCONSTANTBUFFERS_BUFFERS_EMPTY	= ( D3D12_MESSAGE_ID_CSSETCONSTANTBUFFERS_INVALIDBUFFER + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSSETSAMPLERS_SAMPLERS_EMPTY	= ( D3D12_MESSAGE_ID_DEVICE_CSSETCONSTANTBUFFERS_BUFFERS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSGETSHADERRESOURCES_VIEWS_EMPTY	= ( D3D12_MESSAGE_ID_DEVICE_CSSETSAMPLERS_SAMPLERS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSGETCONSTANTBUFFERS_BUFFERS_EMPTY	= ( D3D12_MESSAGE_ID_DEVICE_CSGETSHADERRESOURCES_VIEWS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSGETSAMPLERS_SAMPLERS_EMPTY	= ( D3D12_MESSAGE_ID_DEVICE_CSGETCONSTANTBUFFERS_BUFFERS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CSGETSAMPLERS_SAMPLERS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_DOUBLEFLOATOPSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBUFFER_INVALIDSTRUCTURESTRIDE	= ( D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_DOUBLEFLOATOPSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_CREATEBUFFER_INVALIDSTRUCTURESTRIDE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDDESC	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDVIDEOPLANESLICE	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDPLANESLICE	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDVIDEOPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDPLANESLICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_UNRECOGNIZEDFORMAT	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_OVERLAPPING_OLD_SLOTS	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_UNRECOGNIZEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_NO_OP	= ( D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_OVERLAPPING_OLD_SLOTS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_NO_OP + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEW_DENORMFLUSH	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSSETUNORDEREDACCESSS_VIEWS_EMPTY	= ( D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEW_DENORMFLUSH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CSGETUNORDEREDACCESSS_VIEWS_EMPTY	= ( D3D12_MESSAGE_ID_DEVICE_CSSETUNORDEREDACCESSS_VIEWS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_DEVICE_CSGETUNORDEREDACCESSS_VIEWS_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_INVALID_ARG_BUFFER	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_OFFSET_UNALIGNED	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_INVALID_ARG_BUFFER + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_OFFSET_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_OFFSET_UNALIGNED + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_DEPTH_READONLY	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_OFFSET_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_STENCIL_READONLY	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_DEPTH_READONLY + 1 ) ,
        D3D12_MESSAGE_ID_CHECKFEATURESUPPORT_FORMAT_DEPRECATED	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_STENCIL_READONLY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_RETURN_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_CHECKFEATURESUPPORT_FORMAT_DEPRECATED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_RETURN_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_UNORDEREDACCESSVIEW_RENDERTARGETVIEW_OVERLAP	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_DIMENSION_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_UNORDEREDACCESSVIEW_RENDERTARGETVIEW_OVERLAP + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_APPEND_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_DIMENSION_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMICS_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_APPEND_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_STRUCTURE_STRIDE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMICS_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_BUFFER_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_STRUCTURE_STRIDE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_RAW_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_BUFFER_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_FORMAT_LD_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_RAW_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_FORMAT_STORE_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_FORMAT_LD_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_ADD_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_FORMAT_STORE_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_BITWISE_OPS_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_ADD_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_CMPSTORE_CMPEXCHANGE_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_BITWISE_OPS_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_EXCHANGE_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_CMPSTORE_CMPEXCHANGE_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_SIGNED_MINMAX_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_EXCHANGE_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_UNSIGNED_MINMAX_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_SIGNED_MINMAX_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCH_BOUND_RESOURCE_MAPPED	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_ATOMIC_UNSIGNED_MINMAX_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCH_THREADGROUPCOUNT_OVERFLOW	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCH_BOUND_RESOURCE_MAPPED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCH_THREADGROUPCOUNT_ZERO	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCH_THREADGROUPCOUNT_OVERFLOW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_STRUCTURE_STRIDE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCH_THREADGROUPCOUNT_ZERO + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_BUFFER_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_STRUCTURE_STRIDE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_RAW_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_BUFFER_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCH_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_SHADERRESOURCEVIEW_RAW_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_UNSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCH_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDOFFSET	= ( D3D12_MESSAGE_ID_DEVICE_DISPATCHINDIRECT_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_LARGEOFFSET	= ( D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDDESTINATIONSTATE	= ( D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_LARGEOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDSOURCESTATE	= ( D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDDESTINATIONSTATE + 1 ) ,
        D3D12_MESSAGE_ID_CHECKFORMATSUPPORT_FORMAT_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_COPYSTRUCTURECOUNT_INVALIDSOURCESTATE + 1 ) ,
        D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEWFLOAT_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CHECKFORMATSUPPORT_FORMAT_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_COUNTER_UNSUPPORTED	= ( D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEWFLOAT_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_PIXEL_SHADER_WITHOUT_RTV_OR_DSV	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_COUNTER_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_SHADER_ABORT	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_PIXEL_SHADER_WITHOUT_RTV_OR_DSV + 1 ) ,
        D3D12_MESSAGE_ID_SHADER_MESSAGE	= ( D3D12_MESSAGE_ID_SHADER_ABORT + 1 ) ,
        D3D12_MESSAGE_ID_SHADER_ERROR	= ( D3D12_MESSAGE_ID_SHADER_MESSAGE + 1 ) ,
        D3D12_MESSAGE_ID_OFFERRESOURCES_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_SHADER_ERROR + 1 ) ,
        D3D12_MESSAGE_ID_ENQUEUESETEVENT_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_OFFERRESOURCES_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_ENQUEUESETEVENT_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_ENQUEUESETEVENT_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_ENQUEUESETEVENT_ACCESSDENIED_RETURN	= ( D3D12_MESSAGE_ID_ENQUEUESETEVENT_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDFORCEDSAMPLECOUNT	= ( D3D12_MESSAGE_ID_ENQUEUESETEVENT_ACCESSDENIED_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_USE_OF_FORCED_SAMPLE_COUNT	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALIDFORCEDSAMPLECOUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDLOGICOPS	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_USE_OF_FORCED_SAMPLE_COUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDARRAYWITHDECODER	= ( D3D12_MESSAGE_ID_CREATEBLENDSTATE_INVALIDLOGICOPS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDARRAYWITHDECODER	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDARRAYWITHDECODER + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDARRAYWITHDECODER	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDARRAYWITHDECODER + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_LOCKEDOUT_INTERFACE	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDARRAYWITHDECODER + 1 ) ,
        D3D12_MESSAGE_ID_OFFERRESOURCES_INVALIDPRIORITY	= ( D3D12_MESSAGE_ID_DEVICE_LOCKEDOUT_INTERFACE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDVIEW	= ( D3D12_MESSAGE_ID_OFFERRESOURCES_INVALIDPRIORITY + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDVIEW + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_DOUBLEEXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_SHADEREXTENSIONSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_DOUBLEEXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_MINPRECISION	= ( D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_SHADEREXTENSIONSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_SHADER_LINKAGE_MINPRECISION + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEVERTEXSHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEHULLSHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEDOMAINSHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_UAVSNOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CREATEPIXELSHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_INVALIDOFFSET	= ( D3D12_MESSAGE_ID_DEVICE_CREATECOMPUTESHADER_UAVSNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_TOOMANYVIEWS	= ( D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_INVALIDOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_NOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS_TOOMANYVIEWS + 1 ) ,
        D3D12_MESSAGE_ID_SWAPDEVICECONTEXTSTATE_NOTSUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_NOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_UPDATESUBRESOURCE_PREFERUPDATESUBRESOURCE1	= ( D3D12_MESSAGE_ID_SWAPDEVICECONTEXTSTATE_NOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_GETDC_INACCESSIBLE	= ( D3D12_MESSAGE_ID_UPDATESUBRESOURCE_PREFERUPDATESUBRESOURCE1 + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDRECT	= ( D3D12_MESSAGE_ID_GETDC_INACCESSIBLE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_SAMPLE_MASK_IGNORED_ON_FL9	= ( D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDRECT + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE1_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_SAMPLE_MASK_IGNORED_ON_FL9 + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_BY_NAME_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE1_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_ENQUEUESETEVENT_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_DEVICE_OPEN_SHARED_RESOURCE_BY_NAME_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_OFFERRELEASE_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_ENQUEUESETEVENT_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_OFFERRESOURCES_INACCESSIBLE	= ( D3D12_MESSAGE_ID_OFFERRELEASE_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVIDEOPROCESSORINPUTVIEW_INVALIDMSAA	= ( D3D12_MESSAGE_ID_OFFERRESOURCES_INACCESSIBLE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEVIDEOPROCESSOROUTPUTVIEW_INVALIDMSAA	= ( D3D12_MESSAGE_ID_CREATEVIDEOPROCESSORINPUTVIEW_INVALIDMSAA + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDSOURCERECT	= ( D3D12_MESSAGE_ID_CREATEVIDEOPROCESSOROUTPUTVIEW_INVALIDMSAA + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_EMPTYRECT	= ( D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_INVALIDSOURCERECT + 1 ) ,
        D3D12_MESSAGE_ID_UPDATESUBRESOURCE_EMPTYDESTBOX	= ( D3D12_MESSAGE_ID_DEVICE_CLEARVIEW_EMPTYRECT + 1 ) ,
        D3D12_MESSAGE_ID_COPYSUBRESOURCEREGION_EMPTYSOURCEBOX	= ( D3D12_MESSAGE_ID_UPDATESUBRESOURCE_EMPTYDESTBOX + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_OM_RENDER_TARGET_DOES_NOT_SUPPORT_LOGIC_OPS	= ( D3D12_MESSAGE_ID_COPYSUBRESOURCEREGION_EMPTYSOURCEBOX + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_DEPTHSTENCILVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_OM_RENDER_TARGET_DOES_NOT_SUPPORT_LOGIC_OPS + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_DEPTHSTENCILVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET_DUE_TO_FLIP_PRESENT	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_NOT_SET_DUE_TO_FLIP_PRESENT	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET_DUE_TO_FLIP_PRESENT + 1 ) ,
        D3D12_MESSAGE_ID_GETDATAFORNEWHARDWAREKEY_NULLPARAM	= ( D3D12_MESSAGE_ID_DEVICE_UNORDEREDACCESSVIEW_NOT_SET_DUE_TO_FLIP_PRESENT + 1 ) ,
        D3D12_MESSAGE_ID_CHECKCRYPTOSESSIONSTATUS_NULLPARAM	= ( D3D12_MESSAGE_ID_GETDATAFORNEWHARDWAREKEY_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_SETEVENTONHARDWARECONTENTPROTECTIONTILT_NULLPARAM	= ( D3D12_MESSAGE_ID_CHECKCRYPTOSESSIONSTATUS_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_GETVIDEODECODERCAPS_NULLPARAM	= ( D3D12_MESSAGE_ID_SETEVENTONHARDWARECONTENTPROTECTIONTILT_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_GETVIDEODECODERCAPS_ZEROWIDTHHEIGHT	= ( D3D12_MESSAGE_ID_GETVIDEODECODERCAPS_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_NULLPARAM	= ( D3D12_MESSAGE_ID_GETVIDEODECODERCAPS_ZEROWIDTHHEIGHT + 1 ) ,
        D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_INVALIDCOLORSPACE	= ( D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_ZEROWIDTHHEIGHT	= ( D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_INVALIDCOLORSPACE + 1 ) ,
        D3D12_MESSAGE_ID_VIDEODECODERENABLEDOWNSAMPLING_NULLPARAM	= ( D3D12_MESSAGE_ID_CHECKVIDEODECODERDOWNSAMPLING_ZEROWIDTHHEIGHT + 1 ) ,
        D3D12_MESSAGE_ID_VIDEODECODERENABLEDOWNSAMPLING_UNSUPPORTED	= ( D3D12_MESSAGE_ID_VIDEODECODERENABLEDOWNSAMPLING_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEODECODERUPDATEDOWNSAMPLING_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEODECODERENABLEDOWNSAMPLING_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_VIDEODECODERUPDATEDOWNSAMPLING_UNSUPPORTED	= ( D3D12_MESSAGE_ID_VIDEODECODERUPDATEDOWNSAMPLING_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_CHECKVIDEOPROCESSORFORMATCONVERSION_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEODECODERUPDATEDOWNSAMPLING_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETOUTPUTCOLORSPACE1_NULLPARAM	= ( D3D12_MESSAGE_ID_CHECKVIDEOPROCESSORFORMATCONVERSION_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETOUTPUTCOLORSPACE1_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETOUTPUTCOLORSPACE1_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMCOLORSPACE1_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETOUTPUTCOLORSPACE1_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMCOLORSPACE1_INVALIDSTREAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMCOLORSPACE1_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMCOLORSPACE1_INVALIDSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_INVALIDSTREAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_UNSUPPORTED	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_INVALIDSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETSTREAMCOLORSPACE1_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETSTREAMMIRROR_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETSTREAMMIRROR_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETSTREAMCOLORSPACE1_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETSTREAMMIRROR_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_INVALIDCOLORSPACE	= ( D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_ZEROWIDTHHEIGHT	= ( D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_INVALIDCOLORSPACE + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORSETOUTPUTSHADERUSAGE_NULLPARAM	= ( D3D12_MESSAGE_ID_RECOMMENDVIDEODECODERDOWNSAMPLING_ZEROWIDTHHEIGHT + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETOUTPUTSHADERUSAGE_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORSETOUTPUTSHADERUSAGE_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_NULLPARAM	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETOUTPUTSHADERUSAGE_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDSTREAMCOUNT	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_NULLPARAM + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_TARGETRECT	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDSTREAMCOUNT + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDSOURCERECT	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_TARGETRECT + 1 ) ,
        D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDDESTRECT	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDSOURCERECT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEBUFFER_INVALIDUSAGE	= ( D3D12_MESSAGE_ID_VIDEOPROCESSORGETBEHAVIORHINTS_INVALIDDESTRECT + 1 ) ,
        D3D12_MESSAGE_ID_CREATETEXTURE1D_INVALIDUSAGE	= ( D3D12_MESSAGE_ID_CREATEBUFFER_INVALIDUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATETEXTURE2D_INVALIDUSAGE	= ( D3D12_MESSAGE_ID_CREATETEXTURE1D_INVALIDUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_LEVEL9_STEPRATE_NOT_1	= ( D3D12_MESSAGE_ID_CREATETEXTURE2D_INVALIDUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_LEVEL9_INSTANCING_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_LEVEL9_STEPRATE_NOT_1 + 1 ) ,
        D3D12_MESSAGE_ID_UPDATETILEMAPPINGS_INVALID_PARAMETER	= ( D3D12_MESSAGE_ID_CREATEINPUTLAYOUT_LEVEL9_INSTANCING_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_COPYTILEMAPPINGS_INVALID_PARAMETER	= ( D3D12_MESSAGE_ID_UPDATETILEMAPPINGS_INVALID_PARAMETER + 1 ) ,
        D3D12_MESSAGE_ID_COPYTILES_INVALID_PARAMETER	= ( D3D12_MESSAGE_ID_COPYTILEMAPPINGS_INVALID_PARAMETER + 1 ) ,
        D3D12_MESSAGE_ID_NULL_TILE_MAPPING_ACCESS_WARNING	= ( D3D12_MESSAGE_ID_COPYTILES_INVALID_PARAMETER + 1 ) ,
        D3D12_MESSAGE_ID_NULL_TILE_MAPPING_ACCESS_ERROR	= ( D3D12_MESSAGE_ID_NULL_TILE_MAPPING_ACCESS_WARNING + 1 ) ,
        D3D12_MESSAGE_ID_DIRTY_TILE_MAPPING_ACCESS	= ( D3D12_MESSAGE_ID_NULL_TILE_MAPPING_ACCESS_ERROR + 1 ) ,
        D3D12_MESSAGE_ID_DUPLICATE_TILE_MAPPINGS_IN_COVERED_AREA	= ( D3D12_MESSAGE_ID_DIRTY_TILE_MAPPING_ACCESS + 1 ) ,
        D3D12_MESSAGE_ID_TILE_MAPPINGS_IN_COVERED_AREA_DUPLICATED_OUTSIDE	= ( D3D12_MESSAGE_ID_DUPLICATE_TILE_MAPPINGS_IN_COVERED_AREA + 1 ) ,
        D3D12_MESSAGE_ID_TILE_MAPPINGS_SHARED_BETWEEN_INCOMPATIBLE_RESOURCES	= ( D3D12_MESSAGE_ID_TILE_MAPPINGS_IN_COVERED_AREA_DUPLICATED_OUTSIDE + 1 ) ,
        D3D12_MESSAGE_ID_TILE_MAPPINGS_SHARED_BETWEEN_INPUT_AND_OUTPUT	= ( D3D12_MESSAGE_ID_TILE_MAPPINGS_SHARED_BETWEEN_INCOMPATIBLE_RESOURCES + 1 ) ,
        D3D12_MESSAGE_ID_CHECKMULTISAMPLEQUALITYLEVELS_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_TILE_MAPPINGS_SHARED_BETWEEN_INPUT_AND_OUTPUT + 1 ) ,
        D3D12_MESSAGE_ID_GETRESOURCETILING_NONTILED_RESOURCE	= ( D3D12_MESSAGE_ID_CHECKMULTISAMPLEQUALITYLEVELS_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_NEED_TO_CALL_TILEDRESOURCEBARRIER	= ( D3D12_MESSAGE_ID_GETRESOURCETILING_NONTILED_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEVICE_INVALIDARGS	= ( D3D12_MESSAGE_ID_NEED_TO_CALL_TILEDRESOURCEBARRIER + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEVICE_WARNING	= ( D3D12_MESSAGE_ID_CREATEDEVICE_INVALIDARGS + 1 ) ,
        D3D12_MESSAGE_ID_TILED_RESOURCE_TIER_1_BUFFER_TEXTURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEDEVICE_WARNING + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_CRYPTOSESSION	= ( D3D12_MESSAGE_ID_TILED_RESOURCE_TIER_1_BUFFER_TEXTURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_AUTHENTICATEDCHANNEL	= ( D3D12_MESSAGE_ID_CREATE_CRYPTOSESSION + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_CRYPTOSESSION	= ( D3D12_MESSAGE_ID_CREATE_AUTHENTICATEDCHANNEL + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_AUTHENTICATEDCHANNEL	= ( D3D12_MESSAGE_ID_LIVE_CRYPTOSESSION + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_CRYPTOSESSION	= ( D3D12_MESSAGE_ID_LIVE_AUTHENTICATEDCHANNEL + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_AUTHENTICATEDCHANNEL	= ( D3D12_MESSAGE_ID_DESTROY_CRYPTOSESSION + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALID_SUBRESOURCE	= ( D3D12_MESSAGE_ID_DESTROY_AUTHENTICATEDCHANNEL + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALID_TYPE	= ( D3D12_MESSAGE_ID_MAP_INVALID_SUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_UNSUPPORTED_TYPE	= ( D3D12_MESSAGE_ID_MAP_INVALID_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALID_SUBRESOURCE	= ( D3D12_MESSAGE_ID_MAP_UNSUPPORTED_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_TYPE	= ( D3D12_MESSAGE_ID_UNMAP_INVALID_SUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_NULL_POINTER	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_SUBRESOURCE	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_NULL_POINTER + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_RESERVED_BITS	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_SUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISSING_BIND_FLAGS	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_RESERVED_BITS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_MISC_FLAGS	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISSING_BIND_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MATCHING_STATES	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_MISC_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMBINATION	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_MATCHING_STATES + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_BEFORE_AFTER_MISMATCH	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMBINATION + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_RESOURCE	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_BEFORE_AFTER_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_SAMPLE_COUNT	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAGS	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_SAMPLE_COUNT + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMBINED_FLAGS	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAGS_FOR_FORMAT	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMBINED_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_SPLIT_BARRIER	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAGS_FOR_FORMAT + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_UNMATCHED_END	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_SPLIT_BARRIER + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_UNMATCHED_BEGIN	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_UNMATCHED_END + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAG	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_UNMATCHED_BEGIN + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMMAND_LIST_TYPE	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_FLAG + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_SUBRESOURCE_STATE	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_COMMAND_LIST_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_INEFFICIENT_PRESENT	= ( D3D12_MESSAGE_ID_INVALID_SUBRESOURCE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_CONTENTION	= ( D3D12_MESSAGE_ID_INEFFICIENT_PRESENT + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_RESET	= ( D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_CONTENTION + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_RESET_BUNDLE	= ( D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_RESET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_CANNOT_RESET	= ( D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_RESET_BUNDLE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_OPEN	= ( D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_CANNOT_RESET + 1 ) ,
        D3D12_MESSAGE_ID_QUERY_STATE_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_OPEN + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_BUNDLE_API	= ( D3D12_MESSAGE_ID_QUERY_STATE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_CLOSED	= ( D3D12_MESSAGE_ID_INVALID_BUNDLE_API + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_CLOSED_WITH_INVALID_RESOURCE	= ( D3D12_MESSAGE_ID_COMMAND_LIST_CLOSED + 1 ) ,
        D3D12_MESSAGE_ID_WRONG_COMMAND_ALLOCATOR_TYPE	= ( D3D12_MESSAGE_ID_COMMAND_LIST_CLOSED_WITH_INVALID_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_INDIRECT_ARGUMENT_BUFFER	= ( D3D12_MESSAGE_ID_WRONG_COMMAND_ALLOCATOR_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_COMPUTE_AND_GRAPHICS_PIPELINE	= ( D3D12_MESSAGE_ID_INVALID_INDIRECT_ARGUMENT_BUFFER + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_SYNC	= ( D3D12_MESSAGE_ID_COMPUTE_AND_GRAPHICS_PIPELINE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_SYNC	= ( D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_SYNC + 1 ) ,
        D3D12_MESSAGE_ID_SET_DESCRIPTOR_HEAP_INVALID	= ( D3D12_MESSAGE_ID_COMMAND_LIST_SYNC + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUEUE_IMAGE_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_SET_DESCRIPTOR_HEAP_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMAND_ALLOCATOR_IMAGE_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_CREATE_QUEUE_IMAGE_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMANDQUEUE	= ( D3D12_MESSAGE_ID_CREATE_COMMAND_ALLOCATOR_IMAGE_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMANDALLOCATOR	= ( D3D12_MESSAGE_ID_CREATE_COMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_PIPELINESTATE	= ( D3D12_MESSAGE_ID_CREATE_COMMANDALLOCATOR + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMANDLIST12	= ( D3D12_MESSAGE_ID_CREATE_PIPELINESTATE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_IMAGECOMMANDLIST	= ( D3D12_MESSAGE_ID_CREATE_COMMANDLIST12 + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_RESOURCE	= ( D3D12_MESSAGE_ID_CREATE_IMAGECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_DESCRIPTORHEAP	= ( D3D12_MESSAGE_ID_CREATE_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_ROOTSIGNATURE	= ( D3D12_MESSAGE_ID_CREATE_DESCRIPTORHEAP + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_LIBRARY	= ( D3D12_MESSAGE_ID_CREATE_ROOTSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_HEAP	= ( D3D12_MESSAGE_ID_CREATE_LIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_MONITOREDFENCE	= ( D3D12_MESSAGE_ID_CREATE_HEAP + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUERYHEAP	= ( D3D12_MESSAGE_ID_CREATE_MONITOREDFENCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMANDSIGNATURE	= ( D3D12_MESSAGE_ID_CREATE_QUERYHEAP + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_COMMANDQUEUE	= ( D3D12_MESSAGE_ID_CREATE_COMMANDSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_COMMANDALLOCATOR	= ( D3D12_MESSAGE_ID_LIVE_COMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_PIPELINESTATE	= ( D3D12_MESSAGE_ID_LIVE_COMMANDALLOCATOR + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_COMMANDLIST12	= ( D3D12_MESSAGE_ID_LIVE_PIPELINESTATE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_IMAGECOMMANDLIST	= ( D3D12_MESSAGE_ID_LIVE_COMMANDLIST12 + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_RESOURCE	= ( D3D12_MESSAGE_ID_LIVE_IMAGECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_DESCRIPTORHEAP	= ( D3D12_MESSAGE_ID_LIVE_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_ROOTSIGNATURE	= ( D3D12_MESSAGE_ID_LIVE_DESCRIPTORHEAP + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_LIBRARY	= ( D3D12_MESSAGE_ID_LIVE_ROOTSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_HEAP	= ( D3D12_MESSAGE_ID_LIVE_LIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_MONITOREDFENCE	= ( D3D12_MESSAGE_ID_LIVE_HEAP + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_QUERYHEAP	= ( D3D12_MESSAGE_ID_LIVE_MONITOREDFENCE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_COMMANDSIGNATURE	= ( D3D12_MESSAGE_ID_LIVE_QUERYHEAP + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_COMMANDQUEUE	= ( D3D12_MESSAGE_ID_LIVE_COMMANDSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_COMMANDALLOCATOR	= ( D3D12_MESSAGE_ID_DESTROY_COMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_PIPELINESTATE	= ( D3D12_MESSAGE_ID_DESTROY_COMMANDALLOCATOR + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_COMMANDLIST12	= ( D3D12_MESSAGE_ID_DESTROY_PIPELINESTATE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_IMAGECOMMANDLIST	= ( D3D12_MESSAGE_ID_DESTROY_COMMANDLIST12 + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_RESOURCE	= ( D3D12_MESSAGE_ID_DESTROY_IMAGECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_DESCRIPTORHEAP	= ( D3D12_MESSAGE_ID_DESTROY_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_ROOTSIGNATURE	= ( D3D12_MESSAGE_ID_DESTROY_DESCRIPTORHEAP + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_LIBRARY	= ( D3D12_MESSAGE_ID_DESTROY_ROOTSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_HEAP	= ( D3D12_MESSAGE_ID_DESTROY_LIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_MONITOREDFENCE	= ( D3D12_MESSAGE_ID_DESTROY_HEAP + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_QUERYHEAP	= ( D3D12_MESSAGE_ID_DESTROY_MONITOREDFENCE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_COMMANDSIGNATURE	= ( D3D12_MESSAGE_ID_DESTROY_QUERYHEAP + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDHEAPTYPE	= ( D3D12_MESSAGE_ID_DESTROY_COMMANDSIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDIMENSIONS	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDHEAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_LARGEALLOCATION	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_SMALLALLOCATION	= ( D3D12_MESSAGE_ID_CREATERESOURCE_LARGEALLOCATION + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATERESOURCE_SMALLALLOCATION + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDESC	= ( D3D12_MESSAGE_ID_CREATERESOURCE_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDINITIALSTATE	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_HAS_PENDING_INITIAL_DATA	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDINITIALSTATE + 1 ) ,
        D3D12_MESSAGE_ID_POSSIBLY_INVALID_SUBRESOURCE_STATE	= ( D3D12_MESSAGE_ID_RESOURCE_HAS_PENDING_INITIAL_DATA + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_USE_OF_NON_RESIDENT_RESOURCE	= ( D3D12_MESSAGE_ID_POSSIBLY_INVALID_SUBRESOURCE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_POSSIBLE_INVALID_USE_OF_NON_RESIDENT_RESOURCE	= ( D3D12_MESSAGE_ID_INVALID_USE_OF_NON_RESIDENT_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_BUNDLE_PIPELINE_STATE_MISMATCH	= ( D3D12_MESSAGE_ID_POSSIBLE_INVALID_USE_OF_NON_RESIDENT_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_PRIMITIVE_TOPOLOGY_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_BUNDLE_PIPELINE_STATE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_NUMBER_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_PRIMITIVE_TOPOLOGY_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_FORMAT_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_NUMBER_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_SAMPLE_DESC_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_FORMAT_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_DEPTH_STENCIL_FORMAT_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_SAMPLE_DESC_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_DEPTH_STENCIL_SAMPLE_DESC_MISMATCH_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_DEPTH_STENCIL_FORMAT_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_NUMBER_MISMATCH_BUNDLE_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_DEPTH_STENCIL_SAMPLE_DESC_MISMATCH_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_FORMAT_MISMATCH_BUNDLE_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_NUMBER_MISMATCH_BUNDLE_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_RENDER_TARGET_SAMPLE_DESC_MISMATCH_BUNDLE_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_FORMAT_MISMATCH_BUNDLE_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_DEPTH_STENCIL_FORMAT_MISMATCH_BUNDLE_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_RENDER_TARGET_SAMPLE_DESC_MISMATCH_BUNDLE_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_DEPTH_STENCIL_SAMPLE_DESC_MISMATCH_BUNDLE_PIPELINE_STATE	= ( D3D12_MESSAGE_ID_DEPTH_STENCIL_FORMAT_MISMATCH_BUNDLE_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADER_INVALIDBYTECODE	= ( D3D12_MESSAGE_ID_DEPTH_STENCIL_SAMPLE_DESC_MISMATCH_BUNDLE_PIPELINE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_NULLDESC	= ( D3D12_MESSAGE_ID_CREATESHADER_INVALIDBYTECODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_INVALIDSIZE	= ( D3D12_MESSAGE_ID_CREATEHEAP_NULLDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDHEAPTYPE	= ( D3D12_MESSAGE_ID_CREATEHEAP_INVALIDSIZE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDCPUPAGEPROPERTIES	= ( D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDHEAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDMEMORYPOOL	= ( D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDCPUPAGEPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_INVALIDPROPERTIES	= ( D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDMEMORYPOOL + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_INVALIDALIGNMENT	= ( D3D12_MESSAGE_ID_CREATEHEAP_INVALIDPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATEHEAP_INVALIDALIGNMENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_INVALIDMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATEHEAP_UNRECOGNIZEDMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATEHEAP_INVALIDMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEHEAP_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATEHEAP_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLHEAPPROPERTIES	= ( D3D12_MESSAGE_ID_CREATEHEAP_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDHEAPTYPE	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLHEAPPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDCPUPAGEPROPERTIES	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDHEAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDMEMORYPOOL	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDCPUPAGEPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDHEAPPROPERTIES	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDMEMORYPOOL + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDHEAPMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDHEAPPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDHEAPMISCFLAGS	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_UNRECOGNIZEDHEAPMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDHEAPMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_GETCUSTOMHEAPPROPERTIES_UNRECOGNIZEDHEAPTYPE	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_GETCUSTOMHEAPPROPERTIES_INVALIDHEAPTYPE	= ( D3D12_MESSAGE_ID_GETCUSTOMHEAPPROPERTIES_UNRECOGNIZEDHEAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_DESCRIPTOR_HEAP_INVALID_DESC	= ( D3D12_MESSAGE_ID_GETCUSTOMHEAPPROPERTIES_INVALIDHEAPTYPE + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE	= ( D3D12_MESSAGE_ID_CREATE_DESCRIPTOR_HEAP_INVALID_DESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALID_CONSERVATIVERASTERMODE	= ( D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_SYSTEMVALUE	= ( D3D12_MESSAGE_ID_CREATERASTERIZERSTATE_INVALID_CONSERVATIVERASTERMODE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_INVALID_RESOURCE	= ( D3D12_MESSAGE_ID_DEVICE_DRAW_INVALID_SYSTEMVALUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_INVALID_DESC	= ( D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_INVALID_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_LARGE_OFFSET	= ( D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_INVALID_DESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_UNORDEREDACCESS_VIEW_INVALID_COUNTER_USAGE	= ( D3D12_MESSAGE_ID_CREATE_CONSTANT_BUFFER_VIEW_LARGE_OFFSET + 1 ) ,
        D3D12_MESSAGE_ID_COPY_DESCRIPTORS_INVALID_RANGES	= ( D3D12_MESSAGE_ID_CREATE_UNORDEREDACCESS_VIEW_INVALID_COUNTER_USAGE + 1 ) ,
        D3D12_MESSAGE_ID_COPY_DESCRIPTORS_WRITE_ONLY_DESCRIPTOR	= ( D3D12_MESSAGE_ID_COPY_DESCRIPTORS_INVALID_RANGES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_RTV_FORMAT_NOT_UNKNOWN	= ( D3D12_MESSAGE_ID_COPY_DESCRIPTORS_WRITE_ONLY_DESCRIPTOR + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_RENDER_TARGET_COUNT	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_RTV_FORMAT_NOT_UNKNOWN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_VERTEX_SHADER_NOT_SET	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_RENDER_TARGET_COUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INPUTLAYOUT_NOT_SET	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_VERTEX_SHADER_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_HS_DS_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INPUTLAYOUT_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_REGISTERINDEX	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_HS_DS_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_COMPONENTTYPE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_REGISTERINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_REGISTERMASK	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_COMPONENTTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_SYSTEMVALUE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_REGISTERMASK + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_NEVERWRITTEN_ALWAYSREADS	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_SYSTEMVALUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_MINPRECISION	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_NEVERWRITTEN_ALWAYSREADS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_SEMANTICNAME_NOT_FOUND	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_MINPRECISION + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_XOR_DS_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_LINKAGE_SEMANTICNAME_NOT_FOUND + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HULL_SHADER_INPUT_TOPOLOGY_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_XOR_DS_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_DS_CONTROL_POINT_COUNT_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HULL_SHADER_INPUT_TOPOLOGY_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_DS_TESSELLATOR_DOMAIN_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_DS_CONTROL_POINT_COUNT_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_USE_OF_CENTER_MULTISAMPLE_PATTERN	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_DS_TESSELLATOR_DOMAIN_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_USE_OF_FORCED_SAMPLE_COUNT	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_USE_OF_CENTER_MULTISAMPLE_PATTERN + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_PRIMITIVETOPOLOGY	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_USE_OF_FORCED_SAMPLE_COUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_SYSTEMVALUE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_PRIMITIVETOPOLOGY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_DUAL_SOURCE_BLENDING_CAN_ONLY_HAVE_RENDER_TARGET_0	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_SYSTEMVALUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_RENDER_TARGET_DOES_NOT_SUPPORT_BLENDING	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_DUAL_SOURCE_BLENDING_CAN_ONLY_HAVE_RENDER_TARGET_0 + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_RENDER_TARGET_DOES_NOT_SUPPORT_BLENDING + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_RENDER_TARGET_DOES_NOT_SUPPORT_LOGIC_OPS	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_RENDERTARGETVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_OM_RENDER_TARGET_DOES_NOT_SUPPORT_LOGIC_OPS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_DEPTHSTENCILVIEW_NOT_SET	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_RENDERTARGETVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_GS_INPUT_PRIMITIVE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_DEPTHSTENCILVIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_POSITION_NOT_PRESENT	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_GS_INPUT_PRIMITIVE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_MISSING_ROOT_SIGNATURE_FLAGS	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_POSITION_NOT_PRESENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_INDEX_BUFFER_PROPERTIES	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_MISSING_ROOT_SIGNATURE_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_SAMPLE_DESC	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_INDEX_BUFFER_PROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_INVALID_SAMPLE_DESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_DS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_HS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_VS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_DS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_GS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_VS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_GS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_MISSING_ROOT_SIGNATURE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTE_BUNDLE_OPEN_BUNDLE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_MISSING_ROOT_SIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTE_BUNDLE_DESCRIPTOR_HEAP_MISMATCH	= ( D3D12_MESSAGE_ID_EXECUTE_BUNDLE_OPEN_BUNDLE + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTE_BUNDLE_TYPE	= ( D3D12_MESSAGE_ID_EXECUTE_BUNDLE_DESCRIPTOR_HEAP_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_DRAW_EMPTY_SCISSOR_RECTANGLE	= ( D3D12_MESSAGE_ID_EXECUTE_BUNDLE_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_BLOB_NOT_FOUND	= ( D3D12_MESSAGE_ID_DRAW_EMPTY_SCISSOR_RECTANGLE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_DESERIALIZE_FAILED	= ( D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_BLOB_NOT_FOUND + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_INVALID_CONFIGURATION	= ( D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_DESERIALIZE_FAILED + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_NOT_SUPPORTED_ON_DEVICE	= ( D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_INVALID_CONFIGURATION + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLRESOURCEPROPERTIES	= ( D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_NOT_SUPPORTED_ON_DEVICE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLHEAP	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLRESOURCEPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_GETRESOURCEALLOCATIONINFO_INVALIDRDESCS	= ( D3D12_MESSAGE_ID_CREATERESOURCEANDHEAP_NULLHEAP + 1 ) ,
        D3D12_MESSAGE_ID_MAKERESIDENT_NULLOBJECTARRAY	= ( D3D12_MESSAGE_ID_GETRESOURCEALLOCATIONINFO_INVALIDRDESCS + 1 ) ,
        D3D12_MESSAGE_ID_MAKERESIDENT_INVALIDOBJECT	= ( D3D12_MESSAGE_ID_MAKERESIDENT_NULLOBJECTARRAY + 1 ) ,
        D3D12_MESSAGE_ID_EVICT_NULLOBJECTARRAY	= ( D3D12_MESSAGE_ID_MAKERESIDENT_INVALIDOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_EVICT_INVALIDOBJECT	= ( D3D12_MESSAGE_ID_EVICT_NULLOBJECTARRAY + 1 ) ,
        D3D12_MESSAGE_ID_HEAPS_UNSUPPORTED	= ( D3D12_MESSAGE_ID_EVICT_INVALIDOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_SET_DESCRIPTOR_TABLE_INVALID	= ( D3D12_MESSAGE_ID_HEAPS_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_SET_ROOT_CONSTANT_INVALID	= ( D3D12_MESSAGE_ID_SET_DESCRIPTOR_TABLE_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_ROOT_CONSTANT_BUFFER_VIEW_INVALID	= ( D3D12_MESSAGE_ID_SET_ROOT_CONSTANT_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_ROOT_SHADER_RESOURCE_VIEW_INVALID	= ( D3D12_MESSAGE_ID_SET_ROOT_CONSTANT_BUFFER_VIEW_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_ROOT_UNORDERED_ACCESS_VIEW_INVALID	= ( D3D12_MESSAGE_ID_SET_ROOT_SHADER_RESOURCE_VIEW_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_INVALID_DESC	= ( D3D12_MESSAGE_ID_SET_ROOT_UNORDERED_ACCESS_VIEW_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_LARGE_OFFSET	= ( D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_INVALID_DESC + 1 ) ,
        D3D12_MESSAGE_ID_SET_INDEX_BUFFER_INVALID_DESC	= ( D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_LARGE_OFFSET + 1 ) ,
        D3D12_MESSAGE_ID_SET_INDEX_BUFFER_LARGE_OFFSET	= ( D3D12_MESSAGE_ID_SET_INDEX_BUFFER_INVALID_DESC + 1 ) ,
        D3D12_MESSAGE_ID_SET_STREAM_OUTPUT_BUFFERS_INVALID_DESC	= ( D3D12_MESSAGE_ID_SET_INDEX_BUFFER_LARGE_OFFSET + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDDIMENSIONALITY	= ( D3D12_MESSAGE_ID_SET_STREAM_OUTPUT_BUFFERS_INVALID_DESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDLAYOUT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDDIMENSIONALITY + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDIMENSIONALITY	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDLAYOUT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDALIGNMENT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDDIMENSIONALITY + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDMIPLEVELS	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDALIGNMENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDSAMPLEDESC	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDMIPLEVELS + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDLAYOUT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDSAMPLEDESC + 1 ) ,
        D3D12_MESSAGE_ID_SET_INDEX_BUFFER_INVALID	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDLAYOUT + 1 ) ,
        D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_INVALID	= ( D3D12_MESSAGE_ID_SET_INDEX_BUFFER_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_STREAM_OUTPUT_BUFFERS_INVALID	= ( D3D12_MESSAGE_ID_SET_VERTEX_BUFFERS_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_SET_RENDER_TARGETS_INVALID	= ( D3D12_MESSAGE_ID_SET_STREAM_OUTPUT_BUFFERS_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_CREATEQUERY_HEAP_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_SET_RENDER_TARGETS_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_CREATEQUERY_HEAP_JPEG_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_CREATEQUERY_HEAP_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_BEGIN_END_QUERY_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_CREATEQUERY_HEAP_JPEG_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CLOSE_COMMAND_LIST_OPEN_QUERY	= ( D3D12_MESSAGE_ID_BEGIN_END_QUERY_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVE_QUERY_DATA_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_CLOSE_COMMAND_LIST_OPEN_QUERY + 1 ) ,
        D3D12_MESSAGE_ID_SET_PREDICATION_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_RESOLVE_QUERY_DATA_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_TIMESTAMPS_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_SET_PREDICATION_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_UNSTABLE_POWER_STATE	= ( D3D12_MESSAGE_ID_TIMESTAMPS_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDFORMAT	= ( D3D12_MESSAGE_ID_UNSTABLE_POWER_STATE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_GETCOPYABLELAYOUT_INVALIDSUBRESOURCERANGE	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_GETCOPYABLELAYOUT_INVALIDBASEOFFSET	= ( D3D12_MESSAGE_ID_GETCOPYABLELAYOUT_INVALIDSUBRESOURCERANGE + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_HEAP	= ( D3D12_MESSAGE_ID_GETCOPYABLELAYOUT_INVALIDBASEOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_SAMPLER_INVALID	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_INVALID_HEAP + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMMANDSIGNATURE_INVALID	= ( D3D12_MESSAGE_ID_CREATE_SAMPLER_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTE_INDIRECT_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_CREATECOMMANDSIGNATURE_INVALID + 1 ) ,
        D3D12_MESSAGE_ID_GETGPUVIRTUALADDRESS_INVALID_RESOURCE_DIMENSION	= ( D3D12_MESSAGE_ID_EXECUTE_INDIRECT_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDPLANEINDEX	= ( D3D12_MESSAGE_ID_GETGPUVIRTUALADDRESS_INVALID_RESOURCE_DIMENSION + 4 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_AMBIGUOUSVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_INVALIDVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATESHADERRESOURCEVIEW_AMBIGUOUSVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_AMBIGUOUSVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_INVALIDVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATERENDERTARGETVIEW_AMBIGUOUSVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_AMBIGUOUSVIDEOPLANEINDEX	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_INVALIDVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSCANDATAOFFSET	= ( D3D12_MESSAGE_ID_CREATEUNORDEREDACCESSVIEW_AMBIGUOUSVIDEOPLANEINDEX + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_NOTSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSCANDATAOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_DIMENSIONSTOOLARGE	= ( D3D12_MESSAGE_ID_JPEGDECODE_NOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDCOMPONENTS	= ( D3D12_MESSAGE_ID_JPEGDECODE_DIMENSIONSTOOLARGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDCOMPONENTS	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDCOMPONENTS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_DESTINATIONNOT2D	= ( D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDCOMPONENTS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_TILEDRESOURCESUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_DESTINATIONNOT2D + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_GUARDRECTSUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_TILEDRESOURCESUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_FORMATUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_GUARDRECTSUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_JPEGDECODE_FORMATUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDMIPLEVEL	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_EMPTYDESTBOX	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDMIPLEVEL + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXNOT2D	= ( D3D12_MESSAGE_ID_JPEGDECODE_EMPTYDESTBOX + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXNOTSUB	= ( D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXNOT2D + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXESINTERSECT	= ( D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXNOTSUB + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_XSUBSAMPLEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGDECODE_DESTBOXESINTERSECT + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_YSUBSAMPLEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGDECODE_XSUBSAMPLEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_XSUBSAMPLEODD	= ( D3D12_MESSAGE_ID_JPEGDECODE_YSUBSAMPLEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_YSUBSAMPLEODD	= ( D3D12_MESSAGE_ID_JPEGDECODE_XSUBSAMPLEODD + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UPSCALEUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_YSUBSAMPLEODD + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_TIER4DOWNSCALETOLARGE	= ( D3D12_MESSAGE_ID_JPEGDECODE_UPSCALEUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_TIER3DOWNSCALEUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_TIER4DOWNSCALETOLARGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_CHROMASIZEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGDECODE_TIER3DOWNSCALEUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_LUMACHROMASIZEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGDECODE_CHROMASIZEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDNUMDESTINATIONS	= ( D3D12_MESSAGE_ID_JPEGDECODE_LUMACHROMASIZEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_SUBBOXUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDNUMDESTINATIONS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_1DESTUNSUPPORTEDFORMAT	= ( D3D12_MESSAGE_ID_JPEGDECODE_SUBBOXUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_3DESTUNSUPPORTEDFORMAT	= ( D3D12_MESSAGE_ID_JPEGDECODE_1DESTUNSUPPORTEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_SCALEUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_3DESTUNSUPPORTEDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSOURCESIZE	= ( D3D12_MESSAGE_ID_JPEGDECODE_SCALEUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_INVALIDCOPYFLAGS	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDSOURCESIZE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_HAZARD	= ( D3D12_MESSAGE_ID_JPEGDECODE_INVALIDCOPYFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDSRCBUFFERUSAGE	= ( D3D12_MESSAGE_ID_JPEGDECODE_HAZARD + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDSRCBUFFERMISCFLAGS	= ( D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDSRCBUFFERUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDDSTTEXTUREUSAGE	= ( D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDSRCBUFFERMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_BACKBUFFERNOTSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDDSTTEXTUREUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDCOPYFLAGS	= ( D3D12_MESSAGE_ID_JPEGDECODE_BACKBUFFERNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_NOTSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGDECODE_UNSUPPORTEDCOPYFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_INVALIDSCANDATAOFFSET	= ( D3D12_MESSAGE_ID_JPEGENCODE_NOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_INVALIDCOMPONENTS	= ( D3D12_MESSAGE_ID_JPEGENCODE_INVALIDSCANDATAOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_SOURCENOT2D	= ( D3D12_MESSAGE_ID_JPEGENCODE_INVALIDCOMPONENTS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_TILEDRESOURCESUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGENCODE_SOURCENOT2D + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_GUARDRECTSUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGENCODE_TILEDRESOURCESUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_XSUBSAMPLEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGENCODE_GUARDRECTSUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_YSUBSAMPLEMISMATCH	= ( D3D12_MESSAGE_ID_JPEGENCODE_XSUBSAMPLEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDCOMPONENTS	= ( D3D12_MESSAGE_ID_JPEGENCODE_YSUBSAMPLEMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_FORMATUNSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDCOMPONENTS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_JPEGENCODE_FORMATUNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_INVALIDMIPLEVEL	= ( D3D12_MESSAGE_ID_JPEGENCODE_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_DIMENSIONSTOOLARGE	= ( D3D12_MESSAGE_ID_JPEGENCODE_INVALIDMIPLEVEL + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_HAZARD	= ( D3D12_MESSAGE_ID_JPEGENCODE_DIMENSIONSTOOLARGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDDSTBUFFERUSAGE	= ( D3D12_MESSAGE_ID_JPEGENCODE_HAZARD + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDDSTBUFFERMISCFLAGS	= ( D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDDSTBUFFERUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDSRCTEXTUREUSAGE	= ( D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDDSTBUFFERMISCFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_JPEGENCODE_BACKBUFFERNOTSUPPORTED	= ( D3D12_MESSAGE_ID_JPEGENCODE_UNSUPPORTEDSRCTEXTUREUSAGE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEQUERYORPREDICATE_UNSUPPORTEDCONTEXTTYPEFORQUERY	= ( D3D12_MESSAGE_ID_JPEGENCODE_BACKBUFFERNOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_FLUSH1_INVALIDCONTEXTTYPE	= ( D3D12_MESSAGE_ID_CREATEQUERYORPREDICATE_UNSUPPORTEDCONTEXTTYPEFORQUERY + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDCLEARVALUE	= ( D3D12_MESSAGE_ID_FLUSH1_INVALIDCONTEXTTYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDCLEARVALUEFORMAT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDCLEARVALUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDCLEARVALUEFORMAT	= ( D3D12_MESSAGE_ID_CREATERESOURCE_UNRECOGNIZEDCLEARVALUEFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CREATERESOURCE_CLEARVALUEDENORMFLUSH	= ( D3D12_MESSAGE_ID_CREATERESOURCE_INVALIDCLEARVALUEFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_INVALIDDEPTH	= ( D3D12_MESSAGE_ID_CREATERESOURCE_CLEARVALUEDENORMFLUSH + 1 ) ,
        D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_INVALIDDEPTH + 1 ) ,
        D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE	= ( D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDHEAP	= ( D3D12_MESSAGE_ID_CLEARDEPTHSTENCILVIEW_MISMATCHINGCLEARVALUE + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALIDHEAP	= ( D3D12_MESSAGE_ID_MAP_INVALIDHEAP + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_UNMAP_INVALIDHEAP + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_MAP_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_UNMAP_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_MAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDRANGE	= ( D3D12_MESSAGE_ID_UNMAP_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALIDRANGE	= ( D3D12_MESSAGE_ID_MAP_INVALIDRANGE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_NULLRANGE	= ( D3D12_MESSAGE_ID_UNMAP_INVALIDRANGE + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_NULLRANGE	= ( D3D12_MESSAGE_ID_MAP_NULLRANGE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDDATAPOINTER	= ( D3D12_MESSAGE_ID_UNMAP_NULLRANGE + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALIDARG_RETURN	= ( D3D12_MESSAGE_ID_MAP_INVALIDDATAPOINTER + 1 ) ,
        D3D12_MESSAGE_ID_MAP_OUTOFMEMORY_RETURN	= ( D3D12_MESSAGE_ID_MAP_INVALIDARG_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_BUNDLENOTSUPPORTED	= ( D3D12_MESSAGE_ID_MAP_OUTOFMEMORY_RETURN + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_COMMANDLISTMISMATCH	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_BUNDLENOTSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_OPENCOMMANDLIST	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_COMMANDLISTMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_FAILEDCOMMANDLIST	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_OPENCOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_NULLDST	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_FAILEDCOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDDSTRESOURCEDIMENSION	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_NULLDST + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_DSTRANGEOUTOFBOUNDS	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDDSTRESOURCEDIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_NULLSRC	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_DSTRANGEOUTOFBOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDSRCRESOURCEDIMENSION	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_NULLSRC + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_SRCRANGEOUTOFBOUNDS	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDSRCRESOURCEDIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDCOPYFLAGS	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_SRCRANGEOUTOFBOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_NULLDST	= ( D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALIDCOPYFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDDSTTYPE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_NULLDST + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTRESOURCEDIMENSION	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDDSTTYPE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTRESOURCE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTRESOURCEDIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTSUBRESOURCE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTOFFSET	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDDSTFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDDSTFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTDIMENSIONS	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTROWPITCH	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTPLACEMENT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTROWPITCH + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTDSPLACEDFOOTPRINTFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTPLACEMENT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_DSTREGIONOUTOFBOUNDS	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTDSPLACEDFOOTPRINTFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_NULLSRC	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_DSTREGIONOUTOFBOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDSRCTYPE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_NULLSRC + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCRESOURCEDIMENSION	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDSRCTYPE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCRESOURCE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCRESOURCEDIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCSUBRESOURCE	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCOFFSET	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDSRCFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCOFFSET + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_UNRECOGNIZEDSRCFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCDIMENSIONS	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCROWPITCH	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCDIMENSIONS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCPLACEMENT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCROWPITCH + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCDSPLACEDFOOTPRINTFORMAT	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCPLACEMENT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_SRCREGIONOUTOFBOUNDS	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCDSPLACEDFOOTPRINTFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTCOORDINATES	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_SRCREGIONOUTOFBOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCBOX	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDDSTCOORDINATES + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_FORMATMISMATCH	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDSRCBOX + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_EMPTYBOX	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_FORMATMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDCOPYFLAGS	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_EMPTYBOX + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_SUBRESOURCE_INDEX	= ( D3D12_MESSAGE_ID_COPYTEXTUREREGION_INVALIDCOPYFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_FORMAT	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_SUBRESOURCE_INDEX + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_RESOURCE_MISMATCH	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_FORMAT + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_SAMPLE_COUNT	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_RESOURCE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_INVALID_SHADER	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALID_SAMPLE_COUNT + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_CS_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_INVALID_SHADER + 1 ) ,
        D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_MISSING_ROOT_SIGNATURE	= ( D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_CS_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALIDCACHEDBLOB	= ( D3D12_MESSAGE_ID_CREATECOMPUTEPIPELINESTATE_MISSING_ROOT_SIGNATURE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBADAPTERMISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALIDCACHEDBLOB + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBDRIVERVERSIONMISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBADAPTERMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBDESCMISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBDRIVERVERSIONMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBIGNORED	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBDESCMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDHEAP	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CACHEDBLOBIGNORED + 1 ) ,
        D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDHEAP + 1 ) ,
        D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDBOX	= ( D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDBOX + 1 ) ,
        D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_EMPTYBOX	= ( D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDHEAP	= ( D3D12_MESSAGE_ID_WRITETOSUBRESOURCE_EMPTYBOX + 1 ) ,
        D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDHEAP + 1 ) ,
        D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDBOX	= ( D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDSUBRESOURCE	= ( D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDBOX + 1 ) ,
        D3D12_MESSAGE_ID_READFROMSUBRESOURCE_EMPTYBOX	= ( D3D12_MESSAGE_ID_READFROMSUBRESOURCE_INVALIDSUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_TOO_MANY_NODES_SPECIFIED	= ( D3D12_MESSAGE_ID_READFROMSUBRESOURCE_EMPTYBOX + 1 ) ,
        D3D12_MESSAGE_ID_INVALID_NODE_INDEX	= ( D3D12_MESSAGE_ID_TOO_MANY_NODES_SPECIFIED + 1 ) ,
        D3D12_MESSAGE_ID_GETHEAPPROPERTIES_INVALIDRESOURCE	= ( D3D12_MESSAGE_ID_INVALID_NODE_INDEX + 1 ) ,
        D3D12_MESSAGE_ID_NODE_MASK_MISMATCH	= ( D3D12_MESSAGE_ID_GETHEAPPROPERTIES_INVALIDRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_OUTOFMEMORY	= ( D3D12_MESSAGE_ID_NODE_MASK_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_MULTIPLE_SWAPCHAIN_BUFFER_REFERENCES	= ( D3D12_MESSAGE_ID_COMMAND_LIST_OUTOFMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_TOO_MANY_SWAPCHAIN_REFERENCES	= ( D3D12_MESSAGE_ID_COMMAND_LIST_MULTIPLE_SWAPCHAIN_BUFFER_REFERENCES + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_QUEUE_TOO_MANY_SWAPCHAIN_REFERENCES	= ( D3D12_MESSAGE_ID_COMMAND_LIST_TOO_MANY_SWAPCHAIN_REFERENCES + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_WRONGSWAPCHAINBUFFERREFERENCE	= ( D3D12_MESSAGE_ID_COMMAND_QUEUE_TOO_MANY_SWAPCHAIN_REFERENCES + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_SETRENDERTARGETS_INVALIDNUMRENDERTARGETS	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_WRONGSWAPCHAINBUFFERREFERENCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_TYPE	= ( D3D12_MESSAGE_ID_COMMAND_LIST_SETRENDERTARGETS_INVALIDNUMRENDERTARGETS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_FLAGS	= ( D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHAREDRESOURCE_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHAREDRESOURCE_INVALIDFORMAT	= ( D3D12_MESSAGE_ID_CREATESHAREDRESOURCE_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATESHAREDHEAP_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_CREATESHAREDRESOURCE_INVALIDFORMAT + 1 ) ,
        D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_UNRECOGNIZEDPROPERTIES	= ( D3D12_MESSAGE_ID_CREATESHAREDHEAP_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_INVALIDSIZE	= ( D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_UNRECOGNIZEDPROPERTIES + 1 ) ,
        D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_INVALIDOBJECT	= ( D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_INVALIDSIZE + 1 ) ,
        D3D12_MESSAGE_ID_KEYEDMUTEX_INVALIDOBJECT	= ( D3D12_MESSAGE_ID_REFLECTSHAREDPROPERTIES_INVALIDOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_KEYEDMUTEX_INVALIDKEY	= ( D3D12_MESSAGE_ID_KEYEDMUTEX_INVALIDOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_KEYEDMUTEX_WRONGSTATE	= ( D3D12_MESSAGE_ID_KEYEDMUTEX_INVALIDKEY + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_PRIORITY	= ( D3D12_MESSAGE_ID_KEYEDMUTEX_WRONGSTATE + 1 ) ,
        D3D12_MESSAGE_ID_OBJECT_DELETED_WHILE_STILL_IN_USE	= ( D3D12_MESSAGE_ID_CREATE_QUEUE_INVALID_PRIORITY + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALID_FLAGS	= ( D3D12_MESSAGE_ID_OBJECT_DELETED_WHILE_STILL_IN_USE + 1 ) ,
        D3D12_MESSAGE_ID_HEAP_ADDRESS_RANGE_HAS_NO_RESOURCE	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALID_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RENDER_TARGET_DELETED	= ( D3D12_MESSAGE_ID_HEAP_ADDRESS_RANGE_HAS_NO_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_ALL_RENDER_TARGETS_HAVE_UNKNOWN_FORMAT	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DRAW_RENDER_TARGET_DELETED + 1 ) ,
        D3D12_MESSAGE_ID_HEAP_ADDRESS_RANGE_INTERSECTS_MULTIPLE_BUFFERS	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_ALL_RENDER_TARGETS_HAVE_UNKNOWN_FORMAT + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_GPU_WRITTEN_READBACK_RESOURCE_MAPPED	= ( D3D12_MESSAGE_ID_HEAP_ADDRESS_RANGE_INTERSECTS_MULTIPLE_BUFFERS + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_RANGE_NOT_NEEDED	= ( D3D12_MESSAGE_ID_EXECUTECOMMANDLISTS_GPU_WRITTEN_READBACK_RESOURCE_MAPPED + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_RANGE_NOT_EMPTY	= ( D3D12_MESSAGE_ID_UNMAP_RANGE_NOT_NEEDED + 1 ) ,
        D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE	= ( D3D12_MESSAGE_ID_UNMAP_RANGE_NOT_EMPTY + 1 ) ,
        D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE	= ( D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE + 1 ) ,
        D3D12_MESSAGE_ID_NO_GRAPHICS_API_SUPPORT	= ( D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE + 1 ) ,
        D3D12_MESSAGE_ID_NO_COMPUTE_API_SUPPORT	= ( D3D12_MESSAGE_ID_NO_GRAPHICS_API_SUPPORT + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_RESOURCE_FLAGS_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_NO_COMPUTE_API_SUPPORT + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_ROOT_ARGUMENT_UNINITIALIZED	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_RESOURCE_FLAGS_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_HEAP_INDEX_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_ROOT_ARGUMENT_UNINITIALIZED + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_TABLE_REGISTER_INDEX_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_HEAP_INDEX_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_UNINITIALIZED	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_TABLE_REGISTER_INDEX_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_UNINITIALIZED + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_SRV_RESOURCE_DIMENSION_MISMATCH	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_DESCRIPTOR_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_UAV_RESOURCE_DIMENSION_MISMATCH	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_SRV_RESOURCE_DIMENSION_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_INCOMPATIBLE_RESOURCE_STATE	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_UAV_RESOURCE_DIMENSION_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_NULLDST	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_INCOMPATIBLE_RESOURCE_STATE + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDDSTRESOURCE	= ( D3D12_MESSAGE_ID_COPYRESOURCE_NULLDST + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_NULLSRC	= ( D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDDSTRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSRCRESOURCE	= ( D3D12_MESSAGE_ID_COPYRESOURCE_NULLSRC + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_NULLDST	= ( D3D12_MESSAGE_ID_COPYRESOURCE_INVALIDSRCRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALIDDSTRESOURCE	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_NULLDST + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_NULLSRC	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALIDDSTRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALIDSRCRESOURCE	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_NULLSRC + 1 ) ,
        D3D12_MESSAGE_ID_PIPELINE_STATE_TYPE_MISMATCH	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCE_INVALIDSRCRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DISPATCH_ROOT_SIGNATURE_NOT_SET	= ( D3D12_MESSAGE_ID_PIPELINE_STATE_TYPE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DISPATCH_ROOT_SIGNATURE_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DISPATCH_ROOT_SIGNATURE_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_ZERO_BARRIERS	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DISPATCH_ROOT_SIGNATURE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_BEGIN_END_EVENT_MISMATCH	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_ZERO_BARRIERS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_POSSIBLE_BEFORE_AFTER_MISMATCH	= ( D3D12_MESSAGE_ID_BEGIN_END_EVENT_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_BEGIN_END	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_POSSIBLE_BEFORE_AFTER_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_INVALID_RESOURCE	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_BEGIN_END + 1 ) ,
        D3D12_MESSAGE_ID_USE_OF_ZERO_REFCOUNT_OBJECT	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_INVALID_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_OBJECT_EVICTED_WHILE_STILL_IN_USE	= ( D3D12_MESSAGE_ID_USE_OF_ZERO_REFCOUNT_OBJECT + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_ROOT_DESCRIPTOR_ACCESS_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_OBJECT_EVICTED_WHILE_STILL_IN_USE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_INVALIDLIBRARYBLOB	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_ROOT_DESCRIPTOR_ACCESS_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_DRIVERVERSIONMISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_INVALIDLIBRARYBLOB + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_ADAPTERVERSIONMISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_DRIVERVERSIONMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_UNSUPPORTED	= ( D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_ADAPTERVERSIONMISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_PIPELINELIBRARY	= ( D3D12_MESSAGE_ID_CREATEPIPELINELIBRARY_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_PIPELINELIBRARY	= ( D3D12_MESSAGE_ID_CREATE_PIPELINELIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_PIPELINELIBRARY	= ( D3D12_MESSAGE_ID_LIVE_PIPELINELIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_STOREPIPELINE_NONAME	= ( D3D12_MESSAGE_ID_DESTROY_PIPELINELIBRARY + 1 ) ,
        D3D12_MESSAGE_ID_STOREPIPELINE_DUPLICATENAME	= ( D3D12_MESSAGE_ID_STOREPIPELINE_NONAME + 1 ) ,
        D3D12_MESSAGE_ID_LOADPIPELINE_NAMENOTFOUND	= ( D3D12_MESSAGE_ID_STOREPIPELINE_DUPLICATENAME + 1 ) ,
        D3D12_MESSAGE_ID_LOADPIPELINE_INVALIDDESC	= ( D3D12_MESSAGE_ID_LOADPIPELINE_NAMENOTFOUND + 1 ) ,
        D3D12_MESSAGE_ID_PIPELINELIBRARY_SERIALIZE_NOTENOUGHMEMORY	= ( D3D12_MESSAGE_ID_LOADPIPELINE_INVALIDDESC + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_RT_OUTPUT_MISMATCH	= ( D3D12_MESSAGE_ID_PIPELINELIBRARY_SERIALIZE_NOTENOUGHMEMORY + 1 ) ,
        D3D12_MESSAGE_ID_SETEVENTONMULTIPLEFENCECOMPLETION_INVALIDFLAGS	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_PS_OUTPUT_RT_OUTPUT_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_QUEUE_VIDEO_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_SETEVENTONMULTIPLEFENCECOMPLETION_INVALIDFLAGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMAND_ALLOCATOR_VIDEO_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_CREATE_QUEUE_VIDEO_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEQUERY_HEAP_VIDEO_DECODE_STATISTICS_NOT_SUPPORTED	= ( D3D12_MESSAGE_ID_CREATE_COMMAND_ALLOCATOR_VIDEO_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEODECODECOMMANDLIST	= ( D3D12_MESSAGE_ID_CREATEQUERY_HEAP_VIDEO_DECODE_STATISTICS_NOT_SUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEODECODER	= ( D3D12_MESSAGE_ID_CREATE_VIDEODECODECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEODECODESTREAM	= ( D3D12_MESSAGE_ID_CREATE_VIDEODECODER + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEODECODECOMMANDLIST	= ( D3D12_MESSAGE_ID_CREATE_VIDEODECODESTREAM + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEODECODER	= ( D3D12_MESSAGE_ID_LIVE_VIDEODECODECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEODECODESTREAM	= ( D3D12_MESSAGE_ID_LIVE_VIDEODECODER + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEODECODECOMMANDLIST	= ( D3D12_MESSAGE_ID_LIVE_VIDEODECODESTREAM + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEODECODER	= ( D3D12_MESSAGE_ID_DESTROY_VIDEODECODECOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEODECODESTREAM	= ( D3D12_MESSAGE_ID_DESTROY_VIDEODECODER + 1 ) ,
        D3D12_MESSAGE_ID_DECODE_FRAME_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_DESTROY_VIDEODECODESTREAM + 1 ) ,
        D3D12_MESSAGE_ID_DEPRECATED_API	= ( D3D12_MESSAGE_ID_DECODE_FRAME_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE	= ( D3D12_MESSAGE_ID_DEPRECATED_API + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_DESCRIPTOR_TABLE_NOT_SET	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_CONSTANT_BUFFER_VIEW_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_DESCRIPTOR_TABLE_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_SHADER_RESOURCE_VIEW_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_CONSTANT_BUFFER_VIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_UNORDERED_ACCESS_VIEW_NOT_SET	= ( D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_SHADER_RESOURCE_VIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DISCARD_INVALID_SUBRESOURCE_RANGE	= ( D3D12_MESSAGE_ID_COMMAND_LIST_ROOT_UNORDERED_ACCESS_VIEW_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_DISCARD_ONE_SUBRESOURCE_FOR_MIPS_WITH_RECTS	= ( D3D12_MESSAGE_ID_DISCARD_INVALID_SUBRESOURCE_RANGE + 1 ) ,
        D3D12_MESSAGE_ID_DISCARD_NO_RECTS_FOR_NON_TEXTURE2D	= ( D3D12_MESSAGE_ID_DISCARD_ONE_SUBRESOURCE_FOR_MIPS_WITH_RECTS + 1 ) ,
        D3D12_MESSAGE_ID_COPY_ON_SAME_SUBRESOURCE	= ( D3D12_MESSAGE_ID_DISCARD_NO_RECTS_FOR_NON_TEXTURE2D + 1 ) ,
        D3D12_MESSAGE_ID_SETRESIDENCYPRIORITY_INVALID_PAGEABLE	= ( D3D12_MESSAGE_ID_COPY_ON_SAME_SUBRESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_UNSUPPORTED	= ( D3D12_MESSAGE_ID_SETRESIDENCYPRIORITY_INVALID_PAGEABLE + 1 ) ,
        D3D12_MESSAGE_ID_STATIC_DESCRIPTOR_INVALID_DESCRIPTOR_CHANGE	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_DATA_STATIC_DESCRIPTOR_INVALID_DATA_CHANGE	= ( D3D12_MESSAGE_ID_STATIC_DESCRIPTOR_INVALID_DESCRIPTOR_CHANGE + 1 ) ,
        D3D12_MESSAGE_ID_DATA_STATIC_WHILE_SET_AT_EXECUTE_DESCRIPTOR_INVALID_DATA_CHANGE	= ( D3D12_MESSAGE_ID_DATA_STATIC_DESCRIPTOR_INVALID_DATA_CHANGE + 1 ) ,
        D3D12_MESSAGE_ID_EXECUTE_BUNDLE_STATIC_DESCRIPTOR_DATA_STATIC_NOT_SET	= ( D3D12_MESSAGE_ID_DATA_STATIC_WHILE_SET_AT_EXECUTE_DESCRIPTOR_INVALID_DATA_CHANGE + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_RESOURCE_ACCESS_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_EXECUTE_BUNDLE_STATIC_DESCRIPTOR_DATA_STATIC_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_SAMPLER_MODE_MISMATCH	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_RESOURCE_ACCESS_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_FENCE_INVALID_FLAGS	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_SAMPLER_MODE_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_RESOURCE_BARRIER_DUPLICATE_SUBRESOURCE_TRANSITIONS	= ( D3D12_MESSAGE_ID_CREATE_FENCE_INVALID_FLAGS + 1 ) ,
        D3D12_MESSAGE_ID_SETRESIDENCYPRIORITY_INVALID_PRIORITY	= ( D3D12_MESSAGE_ID_RESOURCE_BARRIER_DUPLICATE_SUBRESOURCE_TRANSITIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_PASS	= ( D3D12_MESSAGE_ID_SETRESIDENCYPRIORITY_INVALID_PRIORITY + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_PASS	= ( D3D12_MESSAGE_ID_CREATE_PASS + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_PASS	= ( D3D12_MESSAGE_ID_DESTROY_PASS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_DESCRIPTOR_HEAP_LARGE_NUM_DESCRIPTORS	= ( D3D12_MESSAGE_ID_LIVE_PASS + 1 ) ,
        D3D12_MESSAGE_ID_BEGIN_EVENT	= ( D3D12_MESSAGE_ID_CREATE_DESCRIPTOR_HEAP_LARGE_NUM_DESCRIPTORS + 1 ) ,
        D3D12_MESSAGE_ID_END_EVENT	= ( D3D12_MESSAGE_ID_BEGIN_EVENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEVICE_DEBUG_LAYER_STARTUP_OPTIONS	= ( D3D12_MESSAGE_ID_END_EVENT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_DEPTHBOUNDSTEST_UNSUPPORTED	= ( D3D12_MESSAGE_ID_CREATEDEVICE_DEBUG_LAYER_STARTUP_OPTIONS + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_DUPLICATE_SUBOBJECT	= ( D3D12_MESSAGE_ID_CREATEDEPTHSTENCILSTATE_DEPTHBOUNDSTEST_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_UNKNOWN_SUBOBJECT	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_DUPLICATE_SUBOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_ZERO_SIZE_STREAM	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_UNKNOWN_SUBOBJECT + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALID_STREAM	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_ZERO_SIZE_STREAM + 1 ) ,
        D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CANNOT_DEDUCE_TYPE	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_INVALID_STREAM + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_STATIC_DESCRIPTOR_RESOURCE_DIMENSION_MISMATCH	= ( D3D12_MESSAGE_ID_CREATEPIPELINESTATE_CANNOT_DEDUCE_TYPE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMAND_QUEUE_INSUFFICIENT_PRIVILEGE_FOR_GLOBAL_REALTIME	= ( D3D12_MESSAGE_ID_COMMAND_LIST_STATIC_DESCRIPTOR_RESOURCE_DIMENSION_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_COMMAND_QUEUE_INSUFFICIENT_HARDWARE_SUPPORT_FOR_GLOBAL_REALTIME	= ( D3D12_MESSAGE_ID_CREATE_COMMAND_QUEUE_INSUFFICIENT_PRIVILEGE_FOR_GLOBAL_REALTIME + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_ARCHITECTURE	= ( D3D12_MESSAGE_ID_CREATE_COMMAND_QUEUE_INSUFFICIENT_HARDWARE_SUPPORT_FOR_GLOBAL_REALTIME + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DST	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_ARCHITECTURE + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DST_RESOURCE_DIMENSION	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DST + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DST_RANGE_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DST_RESOURCE_DIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_SRC	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DST_RANGE_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_SRC_RESOURCE_DIMENSION	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_SRC + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_SRC_RANGE_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_SRC_RESOURCE_DIMENSION + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_OFFSET_ALIGNMENT	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_SRC_RANGE_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DEPENDENT_RESOURCES	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_OFFSET_ALIGNMENT + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DEPENDENT_SUBRESOURCE_RANGES	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DEPENDENT_RESOURCES + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DEPENDENT_RESOURCE	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_NULL_DEPENDENT_SUBRESOURCE_RANGES + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DEPENDENT_SUBRESOURCE_RANGE	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DEPENDENT_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DEPENDENT_SUBRESOURCE_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DEPENDENT_SUBRESOURCE_RANGE + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DEPENDENT_RANGE_OUT_OF_BOUNDS	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DEPENDENT_SUBRESOURCE_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_ZERO_DEPENDENCIES	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_DEPENDENT_RANGE_OUT_OF_BOUNDS + 1 ) ,
        D3D12_MESSAGE_ID_DEVICE_CREATE_SHARED_HANDLE_INVALIDARG	= ( D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_ZERO_DEPENDENCIES + 1 ) ,
        D3D12_MESSAGE_ID_DESCRIPTOR_HANDLE_WITH_INVALID_RESOURCE	= ( D3D12_MESSAGE_ID_DEVICE_CREATE_SHARED_HANDLE_INVALIDARG + 1 ) ,
        D3D12_MESSAGE_ID_SETDEPTHBOUNDS_INVALIDARGS	= ( D3D12_MESSAGE_ID_DESCRIPTOR_HANDLE_WITH_INVALID_RESOURCE + 1 ) ,
        D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_RESOURCE_STATE_IMPRECISE	= ( D3D12_MESSAGE_ID_SETDEPTHBOUNDS_INVALIDARGS + 1 ) ,
        D3D12_MESSAGE_ID_COMMAND_LIST_PIPELINE_STATE_NOT_SET	= ( D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_RESOURCE_STATE_IMPRECISE + 1 ) ,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_MODEL_MISMATCH	= ( D3D12_MESSAGE_ID_COMMAND_LIST_PIPELINE_STATE_NOT_SET + 1 ) ,
        D3D12_MESSAGE_ID_OBJECT_ACCESSED_WHILE_STILL_IN_USE	= ( D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_SHADER_MODEL_MISMATCH + 1 ) ,
        D3D12_MESSAGE_ID_PROGRAMMABLE_MSAA_UNSUPPORTED	= ( D3D12_MESSAGE_ID_OBJECT_ACCESSED_WHILE_STILL_IN_USE + 1 ) ,
        D3D12_MESSAGE_ID_SETSAMPLEPOSITIONS_INVALIDARGS	= ( D3D12_MESSAGE_ID_PROGRAMMABLE_MSAA_UNSUPPORTED + 1 ) ,
        D3D12_MESSAGE_ID_RESOLVESUBRESOURCEREGION_INVALID_RECT	= ( D3D12_MESSAGE_ID_SETSAMPLEPOSITIONS_INVALIDARGS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEODECODECOMMANDQUEUE	= ( D3D12_MESSAGE_ID_RESOLVESUBRESOURCEREGION_INVALID_RECT + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSCOMMANDLIST	= ( D3D12_MESSAGE_ID_CREATE_VIDEODECODECOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSCOMMANDQUEUE	= ( D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSCOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEODECODECOMMANDQUEUE	= ( D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSCOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSCOMMANDLIST	= ( D3D12_MESSAGE_ID_LIVE_VIDEODECODECOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSCOMMANDQUEUE	= ( D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSCOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEODECODECOMMANDQUEUE	= ( D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSCOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSCOMMANDLIST	= ( D3D12_MESSAGE_ID_DESTROY_VIDEODECODECOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSCOMMANDQUEUE	= ( D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSCOMMANDLIST + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSOR	= ( D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSCOMMANDQUEUE + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSSTREAM	= ( D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSOR + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSOR	= ( D3D12_MESSAGE_ID_CREATE_VIDEOPROCESSSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSSTREAM	= ( D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSOR + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSOR	= ( D3D12_MESSAGE_ID_LIVE_VIDEOPROCESSSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSSTREAM	= ( D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSOR + 1 ) ,
        D3D12_MESSAGE_ID_PROCESS_FRAME_INVALID_PARAMETERS	= ( D3D12_MESSAGE_ID_DESTROY_VIDEOPROCESSSTREAM + 1 ) ,
        D3D12_MESSAGE_ID_COPY_INVALIDLAYOUT	= ( D3D12_MESSAGE_ID_PROCESS_FRAME_INVALID_PARAMETERS + 1 ) ,
        D3D12_MESSAGE_ID_CREATE_CRYPTO_SESSION	= 1068,
        D3D12_MESSAGE_ID_CREATE_CRYPTO_SESSION_POLICY	= 1069,
        D3D12_MESSAGE_ID_CREATE_PROTECTED_RESOURCE_SESSION	= 1070,
        D3D12_MESSAGE_ID_LIVE_CRYPTO_SESSION	= 1071,
        D3D12_MESSAGE_ID_LIVE_CRYPTO_SESSION_POLICY	= 1072,
        D3D12_MESSAGE_ID_LIVE_PROTECTED_RESOURCE_SESSION	= 1073,
        D3D12_MESSAGE_ID_DESTROY_CRYPTO_SESSION	= 1074,
        D3D12_MESSAGE_ID_DESTROY_CRYPTO_SESSION_POLICY	= 1075,
        D3D12_MESSAGE_ID_DESTROY_PROTECTED_RESOURCE_SESSION	= 1076,
        D3D12_MESSAGE_ID_PROTECTED_RESOURCE_SESSION_UNSUPPORTED	= 1077,
        D3D12_MESSAGE_ID_FENCE_INVALIDOPERATION	= 1078,
        D3D12_MESSAGE_ID_CREATEQUERY_HEAP_COPY_QUEUE_TIMESTAMPS_NOT_SUPPORTED	= 1079,
        D3D12_MESSAGE_ID_SAMPLEPOSITIONS_MISMATCH_DEFERRED	= 1080,
        D3D12_MESSAGE_ID_SAMPLEPOSITIONS_MISMATCH_RECORDTIME_ASSUMEDFROMFIRSTUSE	= 1081,
        D3D12_MESSAGE_ID_SAMPLEPOSITIONS_MISMATCH_RECORDTIME_ASSUMEDFROMCLEAR	= 1082,
        D3D12_MESSAGE_ID_CREATE_VIDEODECODERHEAP	= 1083,
        D3D12_MESSAGE_ID_LIVE_VIDEODECODERHEAP	= 1084,
        D3D12_MESSAGE_ID_DESTROY_VIDEODECODERHEAP	= 1085,
        D3D12_MESSAGE_ID_OPENEXISTINGHEAP_INVALIDARG_RETURN	= 1086,
        D3D12_MESSAGE_ID_OPENEXISTINGHEAP_OUTOFMEMORY_RETURN	= 1087,
        D3D12_MESSAGE_ID_OPENEXISTINGHEAP_INVALIDADDRESS	= 1088,
        D3D12_MESSAGE_ID_OPENEXISTINGHEAP_INVALIDHANDLE	= 1089,
        D3D12_MESSAGE_ID_WRITEBUFFERIMMEDIATE_INVALID_DEST	= 1090,
        D3D12_MESSAGE_ID_WRITEBUFFERIMMEDIATE_INVALID_MODE	= 1091,
        D3D12_MESSAGE_ID_WRITEBUFFERIMMEDIATE_INVALID_ALIGNMENT	= 1092,
        D3D12_MESSAGE_ID_WRITEBUFFERIMMEDIATE_NOT_SUPPORTED	= 1093,
        D3D12_MESSAGE_ID_SETVIEWINSTANCEMASK_INVALIDARGS	= 1094,
        D3D12_MESSAGE_ID_VIEW_INSTANCING_UNSUPPORTED	= 1095,
        D3D12_MESSAGE_ID_VIEW_INSTANCING_INVALIDARGS	= 1096,
        D3D12_MESSAGE_ID_COPYTEXTUREREGION_MISMATCH_DECODE_REFERENCE_ONLY_FLAG	= 1097,
        D3D12_MESSAGE_ID_COPYRESOURCE_MISMATCH_DECODE_REFERENCE_ONLY_FLAG	= 1098,
        D3D12_MESSAGE_ID_CREATE_VIDEO_DECODE_HEAP_CAPS_FAILURE	= 1099,
        D3D12_MESSAGE_ID_CREATE_VIDEO_DECODE_HEAP_CAPS_UNSUPPORTED	= 1100,
        D3D12_MESSAGE_ID_VIDEO_DECODE_SUPPORT_INVALID_INPUT	= 1101,
        D3D12_MESSAGE_ID_CREATE_VIDEO_DECODER_UNSUPPORTED	= 1102,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_METADATA_ERROR	= 1103,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_VIEW_INSTANCING_VERTEX_SIZE_EXCEEDED	= 1104,
        D3D12_MESSAGE_ID_CREATEGRAPHICSPIPELINESTATE_RUNTIME_INTERNAL_ERROR	= 1105,
        D3D12_MESSAGE_ID_NO_VIDEO_API_SUPPORT	= 1106,
        D3D12_MESSAGE_ID_VIDEO_PROCESS_SUPPORT_INVALID_INPUT	= 1107,
        D3D12_MESSAGE_ID_CREATE_VIDEO_PROCESSOR_CAPS_FAILURE	= 1108,
        D3D12_MESSAGE_ID_VIDEO_PROCESS_SUPPORT_UNSUPPORTED_FORMAT	= 1109,
        D3D12_MESSAGE_ID_VIDEO_DECODE_FRAME_INVALID_ARGUMENT	= 1110,
        D3D12_MESSAGE_ID_ENQUEUE_MAKE_RESIDENT_INVALID_FLAGS	= 1111,
        D3D12_MESSAGE_ID_OPENEXISTINGHEAP_UNSUPPORTED	= 1112,
        D3D12_MESSAGE_ID_VIDEO_PROCESS_FRAMES_INVALID_ARGUMENT	= 1113,
        D3D12_MESSAGE_ID_VIDEO_DECODE_SUPPORT_UNSUPPORTED	= 1114,
        D3D12_MESSAGE_ID_CREATE_COMMANDRECORDER	= 1115,
        D3D12_MESSAGE_ID_LIVE_COMMANDRECORDER	= 1116,
        D3D12_MESSAGE_ID_DESTROY_COMMANDRECORDER	= 1117,
        D3D12_MESSAGE_ID_CREATE_COMMAND_RECORDER_VIDEO_NOT_SUPPORTED	= 1118,
        D3D12_MESSAGE_ID_CREATE_COMMAND_RECORDER_INVALID_SUPPORT_FLAGS	= 1119,
        D3D12_MESSAGE_ID_CREATE_COMMAND_RECORDER_INVALID_FLAGS	= 1120,
        D3D12_MESSAGE_ID_CREATE_COMMAND_RECORDER_MORE_RECORDERS_THAN_LOGICAL_PROCESSORS	= 1121,
        D3D12_MESSAGE_ID_CREATE_COMMANDPOOL	= 1122,
        D3D12_MESSAGE_ID_LIVE_COMMANDPOOL	= 1123,
        D3D12_MESSAGE_ID_DESTROY_COMMANDPOOL	= 1124,
        D3D12_MESSAGE_ID_CREATE_COMMAND_POOL_INVALID_FLAGS	= 1125,
        D3D12_MESSAGE_ID_CREATE_COMMAND_LIST_VIDEO_NOT_SUPPORTED	= 1126,
        D3D12_MESSAGE_ID_COMMAND_RECORDER_SUPPORT_FLAGS_MISMATCH	= 1127,
        D3D12_MESSAGE_ID_COMMAND_RECORDER_CONTENTION	= 1128,
        D3D12_MESSAGE_ID_COMMAND_RECORDER_USAGE_WITH_CREATECOMMANDLIST_COMMAND_LIST	= 1129,
        D3D12_MESSAGE_ID_COMMAND_ALLOCATOR_USAGE_WITH_CREATECOMMANDLIST1_COMMAND_LIST	= 1130,
        D3D12_MESSAGE_ID_CANNOT_EXECUTE_EMPTY_COMMAND_LIST	= 1131,
        D3D12_MESSAGE_ID_CANNOT_RESET_COMMAND_POOL_WITH_OPEN_COMMAND_LISTS	= 1132,
        D3D12_MESSAGE_ID_CANNOT_USE_COMMAND_RECORDER_WITHOUT_CURRENT_TARGET	= 1133,
        D3D12_MESSAGE_ID_CANNOT_CHANGE_COMMAND_RECORDER_TARGET_WHILE_RECORDING	= 1134,
        D3D12_MESSAGE_ID_COMMAND_POOL_SYNC	= 1135,
        D3D12_MESSAGE_ID_EVICT_UNDERFLOW	= 1136,
        D3D12_MESSAGE_ID_CREATE_META_COMMAND	= 1137,
        D3D12_MESSAGE_ID_LIVE_META_COMMAND	= 1138,
        D3D12_MESSAGE_ID_DESTROY_META_COMMAND	= 1139,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALID_DST_RESOURCE	= 1140,
        D3D12_MESSAGE_ID_COPYBUFFERREGION_INVALID_SRC_RESOURCE	= 1141,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_DST_RESOURCE	= 1142,
        D3D12_MESSAGE_ID_ATOMICCOPYBUFFER_INVALID_SRC_RESOURCE	= 1143,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_NULL_BUFFER	= 1144,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_NULL_RESOURCE_DESC	= 1145,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_UNSUPPORTED	= 1146,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_INVALID_BUFFER_DIMENSION	= 1147,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_INVALID_BUFFER_FLAGS	= 1148,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_INVALID_BUFFER_OFFSET	= 1149,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_INVALID_RESOURCE_DIMENSION	= 1150,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_INVALID_RESOURCE_FLAGS	= 1151,
        D3D12_MESSAGE_ID_CREATEPLACEDRESOURCEONBUFFER_OUTOFMEMORY_RETURN	= 1152,
        D3D12_MESSAGE_ID_CANNOT_CREATE_GRAPHICS_AND_VIDEO_COMMAND_RECORDER	= 1153,
        D3D12_MESSAGE_ID_UPDATETILEMAPPINGS_POSSIBLY_MISMATCHING_PROPERTIES	= 1154,
        D3D12_MESSAGE_ID_CREATE_COMMAND_LIST_INVALID_COMMAND_LIST_TYPE	= 1155,
        D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEW_INCOMPATIBLE_WITH_STRUCTURED_BUFFERS	= 1156,
        D3D12_MESSAGE_ID_COMPUTE_ONLY_DEVICE_OPERATION_UNSUPPORTED	= 1157,
        D3D12_MESSAGE_ID_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INVALID	= 1158,
        D3D12_MESSAGE_ID_EMIT_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_INVALID	= 1159,
        D3D12_MESSAGE_ID_COPY_RAYTRACING_ACCELERATION_STRUCTURE_INVALID	= 1160,
        D3D12_MESSAGE_ID_DISPATCH_RAYS_INVALID	= 1161,
        D3D12_MESSAGE_ID_GET_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO_INVALID	= 1162,
        D3D12_MESSAGE_ID_CREATE_LIFETIMETRACKER	= 1163,
        D3D12_MESSAGE_ID_LIVE_LIFETIMETRACKER	= 1164,
        D3D12_MESSAGE_ID_DESTROY_LIFETIMETRACKER	= 1165,
        D3D12_MESSAGE_ID_DESTROYOWNEDOBJECT_OBJECTNOTOWNED	= 1166,
        D3D12_MESSAGE_ID_CREATE_TRACKEDWORKLOAD	= 1167,
        D3D12_MESSAGE_ID_LIVE_TRACKEDWORKLOAD	= 1168,
        D3D12_MESSAGE_ID_DESTROY_TRACKEDWORKLOAD	= 1169,
        D3D12_MESSAGE_ID_RENDER_PASS_ERROR	= 1170,
        D3D12_MESSAGE_ID_META_COMMAND_ID_INVALID	= 1171,
        D3D12_MESSAGE_ID_META_COMMAND_UNSUPPORTED_PARAMS	= 1172,
        D3D12_MESSAGE_ID_META_COMMAND_FAILED_ENUMERATION	= 1173,
        D3D12_MESSAGE_ID_META_COMMAND_PARAMETER_SIZE_MISMATCH	= 1174,
        D3D12_MESSAGE_ID_UNINITIALIZED_META_COMMAND	= 1175,
        D3D12_MESSAGE_ID_META_COMMAND_INVALID_GPU_VIRTUAL_ADDRESS	= 1176,
        D3D12_MESSAGE_ID_CREATE_VIDEOENCODECOMMANDLIST	= 1177,
        D3D12_MESSAGE_ID_LIVE_VIDEOENCODECOMMANDLIST	= 1178,
        D3D12_MESSAGE_ID_DESTROY_VIDEOENCODECOMMANDLIST	= 1179,
        D3D12_MESSAGE_ID_CREATE_VIDEOENCODECOMMANDQUEUE	= 1180,
        D3D12_MESSAGE_ID_LIVE_VIDEOENCODECOMMANDQUEUE	= 1181,
        D3D12_MESSAGE_ID_DESTROY_VIDEOENCODECOMMANDQUEUE	= 1182,
        D3D12_MESSAGE_ID_CREATE_VIDEOMOTIONESTIMATOR	= 1183,
        D3D12_MESSAGE_ID_LIVE_VIDEOMOTIONESTIMATOR	= 1184,
        D3D12_MESSAGE_ID_DESTROY_VIDEOMOTIONESTIMATOR	= 1185,
        D3D12_MESSAGE_ID_CREATE_VIDEOMOTIONVECTORHEAP	= 1186,
        D3D12_MESSAGE_ID_LIVE_VIDEOMOTIONVECTORHEAP	= 1187,
        D3D12_MESSAGE_ID_DESTROY_VIDEOMOTIONVECTORHEAP	= 1188,
        D3D12_MESSAGE_ID_MULTIPLE_TRACKED_WORKLOADS	= 1189,
        D3D12_MESSAGE_ID_MULTIPLE_TRACKED_WORKLOAD_PAIRS	= 1190,
        D3D12_MESSAGE_ID_OUT_OF_ORDER_TRACKED_WORKLOAD_PAIR	= 1191,
        D3D12_MESSAGE_ID_CANNOT_ADD_TRACKED_WORKLOAD	= 1192,
        D3D12_MESSAGE_ID_INCOMPLETE_TRACKED_WORKLOAD_PAIR	= 1193,
        D3D12_MESSAGE_ID_CREATE_STATE_OBJECT_ERROR	= 1194,
        D3D12_MESSAGE_ID_GET_SHADER_IDENTIFIER_ERROR	= 1195,
        D3D12_MESSAGE_ID_GET_SHADER_STACK_SIZE_ERROR	= 1196,
        D3D12_MESSAGE_ID_GET_PIPELINE_STACK_SIZE_ERROR	= 1197,
        D3D12_MESSAGE_ID_SET_PIPELINE_STACK_SIZE_ERROR	= 1198,
        D3D12_MESSAGE_ID_GET_SHADER_IDENTIFIER_SIZE_INVALID	= 1199,
        D3D12_MESSAGE_ID_CHECK_DRIVER_MATCHING_IDENTIFIER_INVALID	= 1200,
        D3D12_MESSAGE_ID_CHECK_DRIVER_MATCHING_IDENTIFIER_DRIVER_REPORTED_ISSUE	= 1201,
        D3D12_MESSAGE_ID_RENDER_PASS_INVALID_RESOURCE_BARRIER	= 1202,
        D3D12_MESSAGE_ID_RENDER_PASS_DISALLOWED_API_CALLED	= 1203,
        D3D12_MESSAGE_ID_RENDER_PASS_CANNOT_NEST_RENDER_PASSES	= 1204,
        D3D12_MESSAGE_ID_RENDER_PASS_CANNOT_END_WITHOUT_BEGIN	= 1205,
        D3D12_MESSAGE_ID_RENDER_PASS_CANNOT_CLOSE_COMMAND_LIST	= 1206,
        D3D12_MESSAGE_ID_RENDER_PASS_GPU_WORK_WHILE_SUSPENDED	= 1207,
        D3D12_MESSAGE_ID_RENDER_PASS_MISMATCHING_SUSPEND_RESUME	= 1208,
        D3D12_MESSAGE_ID_RENDER_PASS_NO_PRIOR_SUSPEND_WITHIN_EXECUTECOMMANDLISTS	= 1209,
        D3D12_MESSAGE_ID_RENDER_PASS_NO_SUBSEQUENT_RESUME_WITHIN_EXECUTECOMMANDLISTS	= 1210,
        D3D12_MESSAGE_ID_TRACKED_WORKLOAD_COMMAND_QUEUE_MISMATCH	= 1211,
        D3D12_MESSAGE_ID_TRACKED_WORKLOAD_NOT_SUPPORTED	= 1212,
        D3D12_MESSAGE_ID_RENDER_PASS_MISMATCHING_NO_ACCESS	= 1213,
        D3D12_MESSAGE_ID_RENDER_PASS_UNSUPPORTED_RESOLVE	= 1214,
        D3D12_MESSAGE_ID_CLEARUNORDEREDACCESSVIEW_INVALID_RESOURCE_PTR	= 1215,
        D3D12_MESSAGE_ID_WINDOWS7_FENCE_OUTOFORDER_SIGNAL	= 1216,
        D3D12_MESSAGE_ID_WINDOWS7_FENCE_OUTOFORDER_WAIT	= 1217,
        D3D12_MESSAGE_ID_VIDEO_CREATE_MOTION_ESTIMATOR_INVALID_ARGUMENT	= 1218,
        D3D12_MESSAGE_ID_VIDEO_CREATE_MOTION_VECTOR_HEAP_INVALID_ARGUMENT	= 1219,
        D3D12_MESSAGE_ID_ESTIMATE_MOTION_INVALID_ARGUMENT	= 1220,
        D3D12_MESSAGE_ID_RESOLVE_MOTION_VECTOR_HEAP_INVALID_ARGUMENT	= 1221,
        D3D12_MESSAGE_ID_GETGPUVIRTUALADDRESS_INVALID_HEAP_TYPE	= 1222,
        D3D12_MESSAGE_ID_SET_BACKGROUND_PROCESSING_MODE_INVALID_ARGUMENT	= 1223,
        D3D12_MESSAGE_ID_CREATE_COMMAND_LIST_INVALID_COMMAND_LIST_TYPE_FOR_FEATURE_LEVEL	= 1224,
        D3D12_MESSAGE_ID_CREATE_VIDEOEXTENSIONCOMMAND	= 1225,
        D3D12_MESSAGE_ID_LIVE_VIDEOEXTENSIONCOMMAND	= 1226,
        D3D12_MESSAGE_ID_DESTROY_VIDEOEXTENSIONCOMMAND	= 1227,
        D3D12_MESSAGE_ID_INVALID_VIDEO_EXTENSION_COMMAND_ID	= 1228,
        D3D12_MESSAGE_ID_VIDEO_EXTENSION_COMMAND_INVALID_ARGUMENT	= 1229,
        D3D12_MESSAGE_ID_CREATE_ROOT_SIGNATURE_NOT_UNIQUE_IN_DXIL_LIBRARY	= 1230,
        D3D12_MESSAGE_ID_VARIABLE_SHADING_RATE_NOT_ALLOWED_WITH_TIR	= 1231,
        D3D12_MESSAGE_ID_GEOMETRY_SHADER_OUTPUTTING_BOTH_VIEWPORT_ARRAY_INDEX_AND_SHADING_RATE_NOT_SUPPORTED_ON_DEVICE	= 1232,
        D3D12_MESSAGE_ID_RSSETSHADING_RATE_INVALID_SHADING_RATE	= 1233,
        D3D12_MESSAGE_ID_RSSETSHADING_RATE_SHADING_RATE_NOT_PERMITTED_BY_CAP	= 1234,
        D3D12_MESSAGE_ID_RSSETSHADING_RATE_INVALID_COMBINER	= 1235,
        D3D12_MESSAGE_ID_RSSETSHADINGRATEIMAGE_REQUIRES_TIER_2	= 1236,
        D3D12_MESSAGE_ID_RSSETSHADINGRATE_REQUIRES_TIER_1	= 1237,
        D3D12_MESSAGE_ID_SHADING_RATE_IMAGE_INCORRECT_FORMAT	= 1238,
        D3D12_MESSAGE_ID_SHADING_RATE_IMAGE_INCORRECT_ARRAY_SIZE	= 1239,
        D3D12_MESSAGE_ID_SHADING_RATE_IMAGE_INCORRECT_MIP_LEVEL	= 1240,
        D3D12_MESSAGE_ID_SHADING_RATE_IMAGE_INCORRECT_SAMPLE_COUNT	= 1241,
        D3D12_MESSAGE_ID_SHADING_RATE_IMAGE_INCORRECT_SAMPLE_QUALITY	= 1242,
        D3D12_MESSAGE_ID_NON_RETAIL_SHADER_MODEL_WONT_VALIDATE	= 1243,
        D3D12_MESSAGE_ID_D3D12_MESSAGES_END	= ( D3D12_MESSAGE_ID_NON_RETAIL_SHADER_MODEL_WONT_VALIDATE + 1 ) 
    } 	D3D12_MESSAGE_ID;

static_assert(D3D12_MESSAGE_ID_GPU_BASED_VALIDATION_UNSUPPORTED == 1000, "Publicly released SDK D3D12_MESSAGE_ID enum values must not be changed. New enum values must be added to the end of the list.");
static_assert(D3D12_MESSAGE_ID_COPY_INVALIDLAYOUT == 1067, "Publicly released SDK D3D12_MESSAGE_ID enum values must not be changed. New enum values must be added to the end of the list.");
typedef struct D3D12_MESSAGE
    {
    D3D12_MESSAGE_CATEGORY Category;
    D3D12_MESSAGE_SEVERITY Severity;
    D3D12_MESSAGE_ID ID;
    _Field_size_(DescriptionByteLength)  const char *pDescription;
    SIZE_T DescriptionByteLength;
    } 	D3D12_MESSAGE;

typedef struct D3D12_INFO_QUEUE_FILTER_DESC
    {
    UINT NumCategories;
    _Field_size_(NumCategories)  D3D12_MESSAGE_CATEGORY *pCategoryList;
    UINT NumSeverities;
    _Field_size_(NumSeverities)  D3D12_MESSAGE_SEVERITY *pSeverityList;
    UINT NumIDs;
    _Field_size_(NumIDs)  D3D12_MESSAGE_ID *pIDList;
    } 	D3D12_INFO_QUEUE_FILTER_DESC;

typedef struct D3D12_INFO_QUEUE_FILTER
    {
    D3D12_INFO_QUEUE_FILTER_DESC AllowList;
    D3D12_INFO_QUEUE_FILTER_DESC DenyList;
    } 	D3D12_INFO_QUEUE_FILTER;

#define D3D12_INFO_QUEUE_DEFAULT_MESSAGE_COUNT_LIMIT 1024


extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0012_v0_0_s_ifspec;

#ifndef __ID3D12InfoQueue_INTERFACE_DEFINED__
#define __ID3D12InfoQueue_INTERFACE_DEFINED__

/* interface ID3D12InfoQueue */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12InfoQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0742a90b-c387-483f-b946-30a7e4e61458")
    ID3D12InfoQueue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMessageCountLimit( 
            _In_  UINT64 MessageCountLimit) = 0;
        
        virtual void STDMETHODCALLTYPE ClearStoredMessages( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMessage( 
            _In_  UINT64 MessageIndex,
            _Out_writes_bytes_opt_(*pMessageByteLength)  D3D12_MESSAGE *pMessage,
            _Inout_  SIZE_T *pMessageByteLength) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesAllowedByStorageFilter( void) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDeniedByStorageFilter( void) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessages( void) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessagesAllowedByRetrievalFilter( void) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDiscardedByMessageCountLimit( void) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetMessageCountLimit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddStorageFilterEntries( 
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStorageFilter( 
            _Out_writes_bytes_opt_(*pFilterByteLength)  D3D12_INFO_QUEUE_FILTER *pFilter,
            _Inout_  SIZE_T *pFilterByteLength) = 0;
        
        virtual void STDMETHODCALLTYPE ClearStorageFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushEmptyStorageFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushCopyOfStorageFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushStorageFilter( 
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual void STDMETHODCALLTYPE PopStorageFilter( void) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetStorageFilterStackSize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddRetrievalFilterEntries( 
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRetrievalFilter( 
            _Out_writes_bytes_opt_(*pFilterByteLength)  D3D12_INFO_QUEUE_FILTER *pFilter,
            _Inout_  SIZE_T *pFilterByteLength) = 0;
        
        virtual void STDMETHODCALLTYPE ClearRetrievalFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushEmptyRetrievalFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushCopyOfRetrievalFilter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushRetrievalFilter( 
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual void STDMETHODCALLTYPE PopRetrievalFilter( void) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetRetrievalFilterStackSize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMessage( 
            _In_  D3D12_MESSAGE_CATEGORY Category,
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  D3D12_MESSAGE_ID ID,
            _In_  LPCSTR pDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddApplicationMessage( 
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  LPCSTR pDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnCategory( 
            _In_  D3D12_MESSAGE_CATEGORY Category,
            _In_  BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnSeverity( 
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnID( 
            _In_  D3D12_MESSAGE_ID ID,
            _In_  BOOL bEnable) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnCategory( 
            _In_  D3D12_MESSAGE_CATEGORY Category) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnSeverity( 
            _In_  D3D12_MESSAGE_SEVERITY Severity) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnID( 
            _In_  D3D12_MESSAGE_ID ID) = 0;
        
        virtual void STDMETHODCALLTYPE SetMuteDebugOutput( 
            _In_  BOOL bMute) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetMuteDebugOutput( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12InfoQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12InfoQueue * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12InfoQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMessageCountLimit )( 
            ID3D12InfoQueue * This,
            _In_  UINT64 MessageCountLimit);
        
        void ( STDMETHODCALLTYPE *ClearStoredMessages )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMessage )( 
            ID3D12InfoQueue * This,
            _In_  UINT64 MessageIndex,
            _Out_writes_bytes_opt_(*pMessageByteLength)  D3D12_MESSAGE *pMessage,
            _Inout_  SIZE_T *pMessageByteLength);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesAllowedByStorageFilter )( 
            ID3D12InfoQueue * This);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesDeniedByStorageFilter )( 
            ID3D12InfoQueue * This);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumStoredMessages )( 
            ID3D12InfoQueue * This);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumStoredMessagesAllowedByRetrievalFilter )( 
            ID3D12InfoQueue * This);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesDiscardedByMessageCountLimit )( 
            ID3D12InfoQueue * This);
        
        UINT64 ( STDMETHODCALLTYPE *GetMessageCountLimit )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddStorageFilterEntries )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetStorageFilter )( 
            ID3D12InfoQueue * This,
            _Out_writes_bytes_opt_(*pFilterByteLength)  D3D12_INFO_QUEUE_FILTER *pFilter,
            _Inout_  SIZE_T *pFilterByteLength);
        
        void ( STDMETHODCALLTYPE *ClearStorageFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushEmptyStorageFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushCopyOfStorageFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushStorageFilter )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter);
        
        void ( STDMETHODCALLTYPE *PopStorageFilter )( 
            ID3D12InfoQueue * This);
        
        UINT ( STDMETHODCALLTYPE *GetStorageFilterStackSize )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddRetrievalFilterEntries )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetRetrievalFilter )( 
            ID3D12InfoQueue * This,
            _Out_writes_bytes_opt_(*pFilterByteLength)  D3D12_INFO_QUEUE_FILTER *pFilter,
            _Inout_  SIZE_T *pFilterByteLength);
        
        void ( STDMETHODCALLTYPE *ClearRetrievalFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushEmptyRetrievalFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushCopyOfRetrievalFilter )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *PushRetrievalFilter )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_INFO_QUEUE_FILTER *pFilter);
        
        void ( STDMETHODCALLTYPE *PopRetrievalFilter )( 
            ID3D12InfoQueue * This);
        
        UINT ( STDMETHODCALLTYPE *GetRetrievalFilterStackSize )( 
            ID3D12InfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddMessage )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_CATEGORY Category,
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  D3D12_MESSAGE_ID ID,
            _In_  LPCSTR pDescription);
        
        HRESULT ( STDMETHODCALLTYPE *AddApplicationMessage )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  LPCSTR pDescription);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnCategory )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_CATEGORY Category,
            _In_  BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnSeverity )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_SEVERITY Severity,
            _In_  BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnID )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_ID ID,
            _In_  BOOL bEnable);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnCategory )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_CATEGORY Category);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnSeverity )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_SEVERITY Severity);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnID )( 
            ID3D12InfoQueue * This,
            _In_  D3D12_MESSAGE_ID ID);
        
        void ( STDMETHODCALLTYPE *SetMuteDebugOutput )( 
            ID3D12InfoQueue * This,
            _In_  BOOL bMute);
        
        BOOL ( STDMETHODCALLTYPE *GetMuteDebugOutput )( 
            ID3D12InfoQueue * This);
        
        END_INTERFACE
    } ID3D12InfoQueueVtbl;

    interface ID3D12InfoQueue
    {
        CONST_VTBL struct ID3D12InfoQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12InfoQueue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12InfoQueue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12InfoQueue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12InfoQueue_SetMessageCountLimit(This,MessageCountLimit)	\
    ( (This)->lpVtbl -> SetMessageCountLimit(This,MessageCountLimit) ) 

#define ID3D12InfoQueue_ClearStoredMessages(This)	\
    ( (This)->lpVtbl -> ClearStoredMessages(This) ) 

#define ID3D12InfoQueue_GetMessage(This,MessageIndex,pMessage,pMessageByteLength)	\
    ( (This)->lpVtbl -> GetMessage(This,MessageIndex,pMessage,pMessageByteLength) ) 

#define ID3D12InfoQueue_GetNumMessagesAllowedByStorageFilter(This)	\
    ( (This)->lpVtbl -> GetNumMessagesAllowedByStorageFilter(This) ) 

#define ID3D12InfoQueue_GetNumMessagesDeniedByStorageFilter(This)	\
    ( (This)->lpVtbl -> GetNumMessagesDeniedByStorageFilter(This) ) 

#define ID3D12InfoQueue_GetNumStoredMessages(This)	\
    ( (This)->lpVtbl -> GetNumStoredMessages(This) ) 

#define ID3D12InfoQueue_GetNumStoredMessagesAllowedByRetrievalFilter(This)	\
    ( (This)->lpVtbl -> GetNumStoredMessagesAllowedByRetrievalFilter(This) ) 

#define ID3D12InfoQueue_GetNumMessagesDiscardedByMessageCountLimit(This)	\
    ( (This)->lpVtbl -> GetNumMessagesDiscardedByMessageCountLimit(This) ) 

#define ID3D12InfoQueue_GetMessageCountLimit(This)	\
    ( (This)->lpVtbl -> GetMessageCountLimit(This) ) 

#define ID3D12InfoQueue_AddStorageFilterEntries(This,pFilter)	\
    ( (This)->lpVtbl -> AddStorageFilterEntries(This,pFilter) ) 

#define ID3D12InfoQueue_GetStorageFilter(This,pFilter,pFilterByteLength)	\
    ( (This)->lpVtbl -> GetStorageFilter(This,pFilter,pFilterByteLength) ) 

#define ID3D12InfoQueue_ClearStorageFilter(This)	\
    ( (This)->lpVtbl -> ClearStorageFilter(This) ) 

#define ID3D12InfoQueue_PushEmptyStorageFilter(This)	\
    ( (This)->lpVtbl -> PushEmptyStorageFilter(This) ) 

#define ID3D12InfoQueue_PushCopyOfStorageFilter(This)	\
    ( (This)->lpVtbl -> PushCopyOfStorageFilter(This) ) 

#define ID3D12InfoQueue_PushStorageFilter(This,pFilter)	\
    ( (This)->lpVtbl -> PushStorageFilter(This,pFilter) ) 

#define ID3D12InfoQueue_PopStorageFilter(This)	\
    ( (This)->lpVtbl -> PopStorageFilter(This) ) 

#define ID3D12InfoQueue_GetStorageFilterStackSize(This)	\
    ( (This)->lpVtbl -> GetStorageFilterStackSize(This) ) 

#define ID3D12InfoQueue_AddRetrievalFilterEntries(This,pFilter)	\
    ( (This)->lpVtbl -> AddRetrievalFilterEntries(This,pFilter) ) 

#define ID3D12InfoQueue_GetRetrievalFilter(This,pFilter,pFilterByteLength)	\
    ( (This)->lpVtbl -> GetRetrievalFilter(This,pFilter,pFilterByteLength) ) 

#define ID3D12InfoQueue_ClearRetrievalFilter(This)	\
    ( (This)->lpVtbl -> ClearRetrievalFilter(This) ) 

#define ID3D12InfoQueue_PushEmptyRetrievalFilter(This)	\
    ( (This)->lpVtbl -> PushEmptyRetrievalFilter(This) ) 

#define ID3D12InfoQueue_PushCopyOfRetrievalFilter(This)	\
    ( (This)->lpVtbl -> PushCopyOfRetrievalFilter(This) ) 

#define ID3D12InfoQueue_PushRetrievalFilter(This,pFilter)	\
    ( (This)->lpVtbl -> PushRetrievalFilter(This,pFilter) ) 

#define ID3D12InfoQueue_PopRetrievalFilter(This)	\
    ( (This)->lpVtbl -> PopRetrievalFilter(This) ) 

#define ID3D12InfoQueue_GetRetrievalFilterStackSize(This)	\
    ( (This)->lpVtbl -> GetRetrievalFilterStackSize(This) ) 

#define ID3D12InfoQueue_AddMessage(This,Category,Severity,ID,pDescription)	\
    ( (This)->lpVtbl -> AddMessage(This,Category,Severity,ID,pDescription) ) 

#define ID3D12InfoQueue_AddApplicationMessage(This,Severity,pDescription)	\
    ( (This)->lpVtbl -> AddApplicationMessage(This,Severity,pDescription) ) 

#define ID3D12InfoQueue_SetBreakOnCategory(This,Category,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnCategory(This,Category,bEnable) ) 

#define ID3D12InfoQueue_SetBreakOnSeverity(This,Severity,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnSeverity(This,Severity,bEnable) ) 

#define ID3D12InfoQueue_SetBreakOnID(This,ID,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnID(This,ID,bEnable) ) 

#define ID3D12InfoQueue_GetBreakOnCategory(This,Category)	\
    ( (This)->lpVtbl -> GetBreakOnCategory(This,Category) ) 

#define ID3D12InfoQueue_GetBreakOnSeverity(This,Severity)	\
    ( (This)->lpVtbl -> GetBreakOnSeverity(This,Severity) ) 

#define ID3D12InfoQueue_GetBreakOnID(This,ID)	\
    ( (This)->lpVtbl -> GetBreakOnID(This,ID) ) 

#define ID3D12InfoQueue_SetMuteDebugOutput(This,bMute)	\
    ( (This)->lpVtbl -> SetMuteDebugOutput(This,bMute) ) 

#define ID3D12InfoQueue_GetMuteDebugOutput(This)	\
    ( (This)->lpVtbl -> GetMuteDebugOutput(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12InfoQueue_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12sdklayers_0000_0013 */
/* [local] */ 

DEFINE_GUID(IID_ID3D12Debug,0x344488b7,0x6846,0x474b,0xb9,0x89,0xf0,0x27,0x44,0x82,0x45,0xe0);
DEFINE_GUID(IID_ID3D12Debug1,0xaffaa4ca,0x63fe,0x4d8e,0xb8,0xad,0x15,0x90,0x00,0xaf,0x43,0x04);
DEFINE_GUID(IID_ID3D12Debug2,0x93a665c4,0xa3b2,0x4e5d,0xb6,0x92,0xa2,0x6a,0xe1,0x4e,0x33,0x74);
DEFINE_GUID(IID_ID3D12Debug3,0x5cf4e58f,0xf671,0x4ff1,0xa5,0x42,0x36,0x86,0xe3,0xd1,0x53,0xd1);
DEFINE_GUID(IID_ID3D12DebugDevice1,0xa9b71770,0xd099,0x4a65,0xa6,0x98,0x3d,0xee,0x10,0x02,0x0f,0x88);
DEFINE_GUID(IID_ID3D12DebugDevice,0x3febd6dd,0x4973,0x4787,0x81,0x94,0xe4,0x5f,0x9e,0x28,0x92,0x3e);
DEFINE_GUID(IID_ID3D12DebugDevice2,0x60eccbc1,0x378d,0x4df1,0x89,0x4c,0xf8,0xac,0x5c,0xe4,0xd7,0xdd);
DEFINE_GUID(IID_ID3D12DebugCommandQueue,0x09e0bf36,0x54ac,0x484f,0x88,0x47,0x4b,0xae,0xea,0xb6,0x05,0x3a);
DEFINE_GUID(IID_ID3D12DebugCommandList1,0x102ca951,0x311b,0x4b01,0xb1,0x1f,0xec,0xb8,0x3e,0x06,0x1b,0x37);
DEFINE_GUID(IID_ID3D12DebugCommandList,0x09e0bf36,0x54ac,0x484f,0x88,0x47,0x4b,0xae,0xea,0xb6,0x05,0x3f);
DEFINE_GUID(IID_ID3D12DebugCommandList2,0xaeb575cf,0x4e06,0x48be,0xba,0x3b,0xc4,0x50,0xfc,0x96,0x65,0x2e);
DEFINE_GUID(IID_ID3D12SharingContract,0x0adf7d52,0x929c,0x4e61,0xad,0xdb,0xff,0xed,0x30,0xde,0x66,0xef);
DEFINE_GUID(IID_ID3D12InfoQueue,0x0742a90b,0xc387,0x483f,0xb9,0x46,0x30,0xa7,0xe4,0xe6,0x14,0x58);


extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12sdklayers_0000_0013_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


