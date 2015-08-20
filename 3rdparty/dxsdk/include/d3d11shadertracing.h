

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* @@MIDL_FILE_HEADING(  ) */



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

#ifndef __d3d11ShaderTracing_h__
#define __d3d11ShaderTracing_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ID3D11ShaderTrace_FWD_DEFINED__
#define __ID3D11ShaderTrace_FWD_DEFINED__
typedef interface ID3D11ShaderTrace ID3D11ShaderTrace;

#endif 	/* __ID3D11ShaderTrace_FWD_DEFINED__ */


#ifndef __ID3D11ShaderTraceFactory_FWD_DEFINED__
#define __ID3D11ShaderTraceFactory_FWD_DEFINED__
typedef interface ID3D11ShaderTraceFactory ID3D11ShaderTraceFactory;

#endif 	/* __ID3D11ShaderTraceFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_d3d11ShaderTracing_0000_0000 */
/* [local] */ 

typedef 
enum D3D11_SHADER_TYPE
    {
        D3D11_VERTEX_SHADER	= 1,
        D3D11_HULL_SHADER	= 2,
        D3D11_DOMAIN_SHADER	= 3,
        D3D11_GEOMETRY_SHADER	= 4,
        D3D11_PIXEL_SHADER	= 5,
        D3D11_COMPUTE_SHADER	= 6
    } 	D3D11_SHADER_TYPE;

#define D3D11_TRACE_COMPONENT_X 0x1
#define D3D11_TRACE_COMPONENT_Y 0x2
#define D3D11_TRACE_COMPONENT_Z 0x4
#define D3D11_TRACE_COMPONENT_W 0x8
typedef UINT8 D3D11_TRACE_COMPONENT_MASK;

typedef struct D3D11_VERTEX_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    } 	D3D11_VERTEX_SHADER_TRACE_DESC;

typedef struct D3D11_HULL_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    } 	D3D11_HULL_SHADER_TRACE_DESC;

typedef struct D3D11_DOMAIN_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    } 	D3D11_DOMAIN_SHADER_TRACE_DESC;

typedef struct D3D11_GEOMETRY_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    } 	D3D11_GEOMETRY_SHADER_TRACE_DESC;

typedef struct D3D11_PIXEL_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    INT X;
    INT Y;
    UINT64 SampleMask;
    } 	D3D11_PIXEL_SHADER_TRACE_DESC;

typedef struct D3D11_COMPUTE_SHADER_TRACE_DESC
    {
    UINT64 Invocation;
    UINT ThreadIDInGroup[ 3 ];
    UINT ThreadGroupID[ 3 ];
    } 	D3D11_COMPUTE_SHADER_TRACE_DESC;

#define D3D11_SHADER_TRACE_FLAG_RECORD_REGISTER_WRITES  0x1
#define D3D11_SHADER_TRACE_FLAG_RECORD_REGISTER_READS   0x2
typedef struct D3D11_SHADER_TRACE_DESC
    {
    D3D11_SHADER_TYPE Type;
    UINT Flags;
    union 
        {
        D3D11_VERTEX_SHADER_TRACE_DESC VertexShaderTraceDesc;
        D3D11_HULL_SHADER_TRACE_DESC HullShaderTraceDesc;
        D3D11_DOMAIN_SHADER_TRACE_DESC DomainShaderTraceDesc;
        D3D11_GEOMETRY_SHADER_TRACE_DESC GeometryShaderTraceDesc;
        D3D11_PIXEL_SHADER_TRACE_DESC PixelShaderTraceDesc;
        D3D11_COMPUTE_SHADER_TRACE_DESC ComputeShaderTraceDesc;
        } 	;
    } 	D3D11_SHADER_TRACE_DESC;

typedef 
enum D3D11_TRACE_GS_INPUT_PRIMITIVE
    {
        D3D11_TRACE_GS_INPUT_PRIMITIVE_UNDEFINED	= 0,
        D3D11_TRACE_GS_INPUT_PRIMITIVE_POINT	= 1,
        D3D11_TRACE_GS_INPUT_PRIMITIVE_LINE	= 2,
        D3D11_TRACE_GS_INPUT_PRIMITIVE_TRIANGLE	= 3,
        D3D11_TRACE_GS_INPUT_PRIMITIVE_LINE_ADJ	= 6,
        D3D11_TRACE_GS_INPUT_PRIMITIVE_TRIANGLE_ADJ	= 7
    } 	D3D11_TRACE_GS_INPUT_PRIMITIVE;

typedef struct D3D11_TRACE_STATS
    {
    D3D11_SHADER_TRACE_DESC TraceDesc;
    UINT8 NumInvocationsInStamp;
    UINT8 TargetStampIndex;
    UINT NumTraceSteps;
    D3D11_TRACE_COMPONENT_MASK InputMask[ 32 ];
    D3D11_TRACE_COMPONENT_MASK OutputMask[ 32 ];
    UINT16 NumTemps;
    UINT16 MaxIndexableTempIndex;
    UINT16 IndexableTempSize[ 4096 ];
    UINT16 ImmediateConstantBufferSize;
    UINT PixelPosition[ 4 ][ 2 ];
    UINT64 PixelCoverageMask[ 4 ];
    UINT64 PixelDiscardedMask[ 4 ];
    UINT64 PixelCoverageMaskAfterShader[ 4 ];
    UINT64 PixelCoverageMaskAfterA2CSampleMask[ 4 ];
    UINT64 PixelCoverageMaskAfterA2CSampleMaskDepth[ 4 ];
    UINT64 PixelCoverageMaskAfterA2CSampleMaskDepthStencil[ 4 ];
    BOOL PSOutputsDepth;
    BOOL PSOutputsMask;
    D3D11_TRACE_GS_INPUT_PRIMITIVE GSInputPrimitive;
    BOOL GSInputsPrimitiveID;
    D3D11_TRACE_COMPONENT_MASK HSOutputPatchConstantMask[ 32 ];
    D3D11_TRACE_COMPONENT_MASK DSInputPatchConstantMask[ 32 ];
    } 	D3D11_TRACE_STATS;

typedef struct D3D11_TRACE_VALUE
    {
    UINT Bits[ 4 ];
    D3D11_TRACE_COMPONENT_MASK ValidMask;
    } 	D3D11_TRACE_VALUE;

typedef 
enum D3D11_TRACE_REGISTER_TYPE
    {
        D3D11_TRACE_OUTPUT_NULL_REGISTER	= 0,
        D3D11_TRACE_INPUT_REGISTER	= ( D3D11_TRACE_OUTPUT_NULL_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_PRIMITIVE_ID_REGISTER	= ( D3D11_TRACE_INPUT_REGISTER + 1 ) ,
        D3D11_TRACE_IMMEDIATE_CONSTANT_BUFFER	= ( D3D11_TRACE_INPUT_PRIMITIVE_ID_REGISTER + 1 ) ,
        D3D11_TRACE_TEMP_REGISTER	= ( D3D11_TRACE_IMMEDIATE_CONSTANT_BUFFER + 1 ) ,
        D3D11_TRACE_INDEXABLE_TEMP_REGISTER	= ( D3D11_TRACE_TEMP_REGISTER + 1 ) ,
        D3D11_TRACE_OUTPUT_REGISTER	= ( D3D11_TRACE_INDEXABLE_TEMP_REGISTER + 1 ) ,
        D3D11_TRACE_OUTPUT_DEPTH_REGISTER	= ( D3D11_TRACE_OUTPUT_REGISTER + 1 ) ,
        D3D11_TRACE_CONSTANT_BUFFER	= ( D3D11_TRACE_OUTPUT_DEPTH_REGISTER + 1 ) ,
        D3D11_TRACE_IMMEDIATE32	= ( D3D11_TRACE_CONSTANT_BUFFER + 1 ) ,
        D3D11_TRACE_SAMPLER	= ( D3D11_TRACE_IMMEDIATE32 + 1 ) ,
        D3D11_TRACE_RESOURCE	= ( D3D11_TRACE_SAMPLER + 1 ) ,
        D3D11_TRACE_RASTERIZER	= ( D3D11_TRACE_RESOURCE + 1 ) ,
        D3D11_TRACE_OUTPUT_COVERAGE_MASK	= ( D3D11_TRACE_RASTERIZER + 1 ) ,
        D3D11_TRACE_STREAM	= ( D3D11_TRACE_OUTPUT_COVERAGE_MASK + 1 ) ,
        D3D11_TRACE_THIS_POINTER	= ( D3D11_TRACE_STREAM + 1 ) ,
        D3D11_TRACE_OUTPUT_CONTROL_POINT_ID_REGISTER	= ( D3D11_TRACE_THIS_POINTER + 1 ) ,
        D3D11_TRACE_INPUT_FORK_INSTANCE_ID_REGISTER	= ( D3D11_TRACE_OUTPUT_CONTROL_POINT_ID_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_JOIN_INSTANCE_ID_REGISTER	= ( D3D11_TRACE_INPUT_FORK_INSTANCE_ID_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_CONTROL_POINT_REGISTER	= ( D3D11_TRACE_INPUT_JOIN_INSTANCE_ID_REGISTER + 1 ) ,
        D3D11_TRACE_OUTPUT_CONTROL_POINT_REGISTER	= ( D3D11_TRACE_INPUT_CONTROL_POINT_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_PATCH_CONSTANT_REGISTER	= ( D3D11_TRACE_OUTPUT_CONTROL_POINT_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_DOMAIN_POINT_REGISTER	= ( D3D11_TRACE_INPUT_PATCH_CONSTANT_REGISTER + 1 ) ,
        D3D11_TRACE_UNORDERED_ACCESS_VIEW	= ( D3D11_TRACE_INPUT_DOMAIN_POINT_REGISTER + 1 ) ,
        D3D11_TRACE_THREAD_GROUP_SHARED_MEMORY	= ( D3D11_TRACE_UNORDERED_ACCESS_VIEW + 1 ) ,
        D3D11_TRACE_INPUT_THREAD_ID_REGISTER	= ( D3D11_TRACE_THREAD_GROUP_SHARED_MEMORY + 1 ) ,
        D3D11_TRACE_INPUT_THREAD_GROUP_ID_REGISTER	= ( D3D11_TRACE_INPUT_THREAD_ID_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_THREAD_ID_IN_GROUP_REGISTER	= ( D3D11_TRACE_INPUT_THREAD_GROUP_ID_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_COVERAGE_MASK_REGISTER	= ( D3D11_TRACE_INPUT_THREAD_ID_IN_GROUP_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_THREAD_ID_IN_GROUP_FLATTENED_REGISTER	= ( D3D11_TRACE_INPUT_COVERAGE_MASK_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_GS_INSTANCE_ID_REGISTER	= ( D3D11_TRACE_INPUT_THREAD_ID_IN_GROUP_FLATTENED_REGISTER + 1 ) ,
        D3D11_TRACE_OUTPUT_DEPTH_GREATER_EQUAL_REGISTER	= ( D3D11_TRACE_INPUT_GS_INSTANCE_ID_REGISTER + 1 ) ,
        D3D11_TRACE_OUTPUT_DEPTH_LESS_EQUAL_REGISTER	= ( D3D11_TRACE_OUTPUT_DEPTH_GREATER_EQUAL_REGISTER + 1 ) ,
        D3D11_TRACE_IMMEDIATE64	= ( D3D11_TRACE_OUTPUT_DEPTH_LESS_EQUAL_REGISTER + 1 ) ,
        D3D11_TRACE_INPUT_CYCLE_COUNTER_REGISTER	= ( D3D11_TRACE_IMMEDIATE64 + 1 ) ,
        D3D11_TRACE_INTERFACE_POINTER	= ( D3D11_TRACE_INPUT_CYCLE_COUNTER_REGISTER + 1 ) 
    } 	D3D11_TRACE_REGISTER_TYPE;

#define D3D11_TRACE_REGISTER_FLAGS_RELATIVE_INDEXING 0x1
typedef struct D3D11_TRACE_REGISTER
    {
    D3D11_TRACE_REGISTER_TYPE RegType;
    union 
        {
        UINT16 Index1D;
        UINT16 Index2D[ 2 ];
        } 	;
    UINT8 OperandIndex;
    UINT8 Flags;
    } 	D3D11_TRACE_REGISTER;

#define D3D11_TRACE_MISC_GS_EMIT 0x1
#define D3D11_TRACE_MISC_GS_CUT  0x2 
#define D3D11_TRACE_MISC_PS_DISCARD 0x4 
#define D3D11_TRACE_MISC_GS_EMIT_STREAM 0x8 
#define D3D11_TRACE_MISC_GS_CUT_STREAM 0x10 
#define D3D11_TRACE_MISC_HALT 0x20 
#define D3D11_TRACE_MISC_MESSAGE 0x40 
typedef UINT16 D3D11_TRACE_MISC_OPERATIONS_MASK;

typedef struct D3D11_TRACE_STEP
    {
    UINT ID;
    BOOL InstructionActive;
    UINT8 NumRegistersWritten;
    UINT8 NumRegistersRead;
    D3D11_TRACE_MISC_OPERATIONS_MASK MiscOperations;
    UINT OpcodeType;
    UINT64 CurrentGlobalCycle;
    } 	D3D11_TRACE_STEP;



extern RPC_IF_HANDLE __MIDL_itf_d3d11ShaderTracing_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d11ShaderTracing_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D11ShaderTrace_INTERFACE_DEFINED__
#define __ID3D11ShaderTrace_INTERFACE_DEFINED__

/* interface ID3D11ShaderTrace */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D11ShaderTrace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36b013e6-2811-4845-baa7-d623fe0df104")
    ID3D11ShaderTrace : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TraceReady( 
            /* [annotation] */ 
            _Out_opt_  UINT64 *pTestCount) = 0;
        
        virtual void STDMETHODCALLTYPE ResetTrace( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTraceStats( 
            /* [annotation] */ 
            _Out_  D3D11_TRACE_STATS *pTraceStats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PSSelectStamp( 
            /* [annotation] */ 
            _In_  UINT stampIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInitialRegisterContents( 
            /* [annotation] */ 
            _In_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStep( 
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_STEP *pTraceStep) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWrittenRegister( 
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _In_  UINT writtenRegisterIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetReadRegister( 
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _In_  UINT readRegisterIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D11ShaderTraceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D11ShaderTrace * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D11ShaderTrace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D11ShaderTrace * This);
        
        HRESULT ( STDMETHODCALLTYPE *TraceReady )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _Out_opt_  UINT64 *pTestCount);
        
        void ( STDMETHODCALLTYPE *ResetTrace )( 
            ID3D11ShaderTrace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTraceStats )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_STATS *pTraceStats);
        
        HRESULT ( STDMETHODCALLTYPE *PSSelectStamp )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _In_  UINT stampIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetInitialRegisterContents )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _In_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetStep )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_STEP *pTraceStep);
        
        HRESULT ( STDMETHODCALLTYPE *GetWrittenRegister )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _In_  UINT writtenRegisterIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetReadRegister )( 
            ID3D11ShaderTrace * This,
            /* [annotation] */ 
            _In_  UINT stepIndex,
            /* [annotation] */ 
            _In_  UINT readRegisterIndex,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_REGISTER *pRegister,
            /* [annotation] */ 
            _Out_  D3D11_TRACE_VALUE *pValue);
        
        END_INTERFACE
    } ID3D11ShaderTraceVtbl;

    interface ID3D11ShaderTrace
    {
        CONST_VTBL struct ID3D11ShaderTraceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D11ShaderTrace_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D11ShaderTrace_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D11ShaderTrace_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D11ShaderTrace_TraceReady(This,pTestCount)	\
    ( (This)->lpVtbl -> TraceReady(This,pTestCount) ) 

#define ID3D11ShaderTrace_ResetTrace(This)	\
    ( (This)->lpVtbl -> ResetTrace(This) ) 

#define ID3D11ShaderTrace_GetTraceStats(This,pTraceStats)	\
    ( (This)->lpVtbl -> GetTraceStats(This,pTraceStats) ) 

#define ID3D11ShaderTrace_PSSelectStamp(This,stampIndex)	\
    ( (This)->lpVtbl -> PSSelectStamp(This,stampIndex) ) 

#define ID3D11ShaderTrace_GetInitialRegisterContents(This,pRegister,pValue)	\
    ( (This)->lpVtbl -> GetInitialRegisterContents(This,pRegister,pValue) ) 

#define ID3D11ShaderTrace_GetStep(This,stepIndex,pTraceStep)	\
    ( (This)->lpVtbl -> GetStep(This,stepIndex,pTraceStep) ) 

#define ID3D11ShaderTrace_GetWrittenRegister(This,stepIndex,writtenRegisterIndex,pRegister,pValue)	\
    ( (This)->lpVtbl -> GetWrittenRegister(This,stepIndex,writtenRegisterIndex,pRegister,pValue) ) 

#define ID3D11ShaderTrace_GetReadRegister(This,stepIndex,readRegisterIndex,pRegister,pValue)	\
    ( (This)->lpVtbl -> GetReadRegister(This,stepIndex,readRegisterIndex,pRegister,pValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D11ShaderTrace_INTERFACE_DEFINED__ */


#ifndef __ID3D11ShaderTraceFactory_INTERFACE_DEFINED__
#define __ID3D11ShaderTraceFactory_INTERFACE_DEFINED__

/* interface ID3D11ShaderTraceFactory */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D11ShaderTraceFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1fbad429-66ab-41cc-9617-667ac10e4459")
    ID3D11ShaderTraceFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateShaderTrace( 
            /* [annotation] */ 
            _In_  IUnknown *pShader,
            /* [annotation] */ 
            _In_  D3D11_SHADER_TRACE_DESC *pTraceDesc,
            /* [annotation] */ 
            _COM_Outptr_  ID3D11ShaderTrace **ppShaderTrace) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D11ShaderTraceFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D11ShaderTraceFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D11ShaderTraceFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D11ShaderTraceFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateShaderTrace )( 
            ID3D11ShaderTraceFactory * This,
            /* [annotation] */ 
            _In_  IUnknown *pShader,
            /* [annotation] */ 
            _In_  D3D11_SHADER_TRACE_DESC *pTraceDesc,
            /* [annotation] */ 
            _COM_Outptr_  ID3D11ShaderTrace **ppShaderTrace);
        
        END_INTERFACE
    } ID3D11ShaderTraceFactoryVtbl;

    interface ID3D11ShaderTraceFactory
    {
        CONST_VTBL struct ID3D11ShaderTraceFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D11ShaderTraceFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D11ShaderTraceFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D11ShaderTraceFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D11ShaderTraceFactory_CreateShaderTrace(This,pShader,pTraceDesc,ppShaderTrace)	\
    ( (This)->lpVtbl -> CreateShaderTrace(This,pShader,pTraceDesc,ppShaderTrace) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D11ShaderTraceFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d11ShaderTracing_0000_0002 */
/* [local] */ 

HRESULT WINAPI
D3DDisassemble11Trace(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                      _In_ SIZE_T SrcDataSize,
                      _In_ ID3D11ShaderTrace* pTrace,
                      _In_ UINT StartStep,
                      _In_ UINT NumSteps,
                      _In_ UINT Flags,
                      _COM_Outptr_ interface ID3D10Blob** ppDisassembly);


extern RPC_IF_HANDLE __MIDL_itf_d3d11ShaderTracing_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d11ShaderTracing_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


