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

#ifndef __d3d12video_h__
#define __d3d12video_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ID3D12VideoDecoderHeap_FWD_DEFINED__
#define __ID3D12VideoDecoderHeap_FWD_DEFINED__
typedef interface ID3D12VideoDecoderHeap ID3D12VideoDecoderHeap;

#endif 	/* __ID3D12VideoDecoderHeap_FWD_DEFINED__ */


#ifndef __ID3D12VideoDevice_FWD_DEFINED__
#define __ID3D12VideoDevice_FWD_DEFINED__
typedef interface ID3D12VideoDevice ID3D12VideoDevice;

#endif 	/* __ID3D12VideoDevice_FWD_DEFINED__ */


#ifndef __ID3D12VideoDecoder_FWD_DEFINED__
#define __ID3D12VideoDecoder_FWD_DEFINED__
typedef interface ID3D12VideoDecoder ID3D12VideoDecoder;

#endif 	/* __ID3D12VideoDecoder_FWD_DEFINED__ */


#ifndef __ID3D12VideoProcessor_FWD_DEFINED__
#define __ID3D12VideoProcessor_FWD_DEFINED__
typedef interface ID3D12VideoProcessor ID3D12VideoProcessor;

#endif 	/* __ID3D12VideoProcessor_FWD_DEFINED__ */


#ifndef __ID3D12VideoDecodeCommandList_FWD_DEFINED__
#define __ID3D12VideoDecodeCommandList_FWD_DEFINED__
typedef interface ID3D12VideoDecodeCommandList ID3D12VideoDecodeCommandList;

#endif 	/* __ID3D12VideoDecodeCommandList_FWD_DEFINED__ */


#ifndef __ID3D12VideoProcessCommandList_FWD_DEFINED__
#define __ID3D12VideoProcessCommandList_FWD_DEFINED__
typedef interface ID3D12VideoProcessCommandList ID3D12VideoProcessCommandList;

#endif 	/* __ID3D12VideoProcessCommandList_FWD_DEFINED__ */


#ifndef __ID3D12VideoDecodeCommandList1_FWD_DEFINED__
#define __ID3D12VideoDecodeCommandList1_FWD_DEFINED__
typedef interface ID3D12VideoDecodeCommandList1 ID3D12VideoDecodeCommandList1;

#endif 	/* __ID3D12VideoDecodeCommandList1_FWD_DEFINED__ */


#ifndef __ID3D12VideoProcessCommandList1_FWD_DEFINED__
#define __ID3D12VideoProcessCommandList1_FWD_DEFINED__
typedef interface ID3D12VideoProcessCommandList1 ID3D12VideoProcessCommandList1;

#endif 	/* __ID3D12VideoProcessCommandList1_FWD_DEFINED__ */


#ifndef __ID3D12VideoMotionEstimator_FWD_DEFINED__
#define __ID3D12VideoMotionEstimator_FWD_DEFINED__
typedef interface ID3D12VideoMotionEstimator ID3D12VideoMotionEstimator;

#endif 	/* __ID3D12VideoMotionEstimator_FWD_DEFINED__ */


#ifndef __ID3D12VideoMotionVectorHeap_FWD_DEFINED__
#define __ID3D12VideoMotionVectorHeap_FWD_DEFINED__
typedef interface ID3D12VideoMotionVectorHeap ID3D12VideoMotionVectorHeap;

#endif 	/* __ID3D12VideoMotionVectorHeap_FWD_DEFINED__ */


#ifndef __ID3D12VideoDevice1_FWD_DEFINED__
#define __ID3D12VideoDevice1_FWD_DEFINED__
typedef interface ID3D12VideoDevice1 ID3D12VideoDevice1;

#endif 	/* __ID3D12VideoDevice1_FWD_DEFINED__ */


#ifndef __ID3D12VideoEncodeCommandList_FWD_DEFINED__
#define __ID3D12VideoEncodeCommandList_FWD_DEFINED__
typedef interface ID3D12VideoEncodeCommandList ID3D12VideoEncodeCommandList;

#endif 	/* __ID3D12VideoEncodeCommandList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "dxgicommon.h"
#include "d3d12.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_d3d12video_0000_0000 */
/* [local] */ 

typedef 
enum D3D12_VIDEO_FIELD_TYPE
    {
        D3D12_VIDEO_FIELD_TYPE_NONE	= 0,
        D3D12_VIDEO_FIELD_TYPE_INTERLACED_TOP_FIELD_FIRST	= 1,
        D3D12_VIDEO_FIELD_TYPE_INTERLACED_BOTTOM_FIELD_FIRST	= 2
    } 	D3D12_VIDEO_FIELD_TYPE;

typedef 
enum D3D12_VIDEO_FRAME_STEREO_FORMAT
    {
        D3D12_VIDEO_FRAME_STEREO_FORMAT_NONE	= 0,
        D3D12_VIDEO_FRAME_STEREO_FORMAT_MONO	= 1,
        D3D12_VIDEO_FRAME_STEREO_FORMAT_HORIZONTAL	= 2,
        D3D12_VIDEO_FRAME_STEREO_FORMAT_VERTICAL	= 3,
        D3D12_VIDEO_FRAME_STEREO_FORMAT_SEPARATE	= 4
    } 	D3D12_VIDEO_FRAME_STEREO_FORMAT;

typedef struct D3D12_VIDEO_FORMAT
    {
    DXGI_FORMAT Format;
    DXGI_COLOR_SPACE_TYPE ColorSpace;
    } 	D3D12_VIDEO_FORMAT;

typedef struct D3D12_VIDEO_SAMPLE
    {
    UINT Width;
    UINT Height;
    D3D12_VIDEO_FORMAT Format;
    } 	D3D12_VIDEO_SAMPLE;

typedef 
enum D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE
    {
        D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_NONE	= 0,
        D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_FIELD_BASED	= 1
    } 	D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE;

typedef 
enum D3D12_FEATURE_VIDEO
    {
        D3D12_FEATURE_VIDEO_DECODE_SUPPORT	= 0,
        D3D12_FEATURE_VIDEO_DECODE_PROFILES	= 1,
        D3D12_FEATURE_VIDEO_DECODE_FORMATS	= 2,
        D3D12_FEATURE_VIDEO_DECODE_CONVERSION_SUPPORT	= 3,
        D3D12_FEATURE_VIDEO_PROCESS_SUPPORT	= 5,
        D3D12_FEATURE_VIDEO_PROCESS_MAX_INPUT_STREAMS	= 6,
        D3D12_FEATURE_VIDEO_PROCESS_REFERENCE_INFO	= 7,
        D3D12_FEATURE_VIDEO_DECODER_HEAP_SIZE	= 8,
        D3D12_FEATURE_VIDEO_PROCESSOR_SIZE	= 9,
        D3D12_FEATURE_VIDEO_DECODE_PROFILE_COUNT	= 10,
        D3D12_FEATURE_VIDEO_DECODE_FORMAT_COUNT	= 11,
        D3D12_FEATURE_VIDEO_ARCHITECTURE	= 17,
        D3D12_FEATURE_VIDEO_DECODE_HISTOGRAM	= 18,
        D3D12_FEATURE_VIDEO_FEATURE_AREA_SUPPORT	= 19,
        D3D12_FEATURE_VIDEO_MOTION_ESTIMATOR	= 20,
        D3D12_FEATURE_VIDEO_MOTION_ESTIMATOR_SIZE	= 21
    } 	D3D12_FEATURE_VIDEO;

typedef 
enum D3D12_BITSTREAM_ENCRYPTION_TYPE
    {
        D3D12_BITSTREAM_ENCRYPTION_TYPE_NONE	= 0
    } 	D3D12_BITSTREAM_ENCRYPTION_TYPE;

typedef struct D3D12_VIDEO_DECODE_CONFIGURATION
    {
    GUID DecodeProfile;
    D3D12_BITSTREAM_ENCRYPTION_TYPE BitstreamEncryption;
    D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE InterlaceType;
    } 	D3D12_VIDEO_DECODE_CONFIGURATION;

typedef struct D3D12_VIDEO_DECODER_DESC
    {
    UINT NodeMask;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    } 	D3D12_VIDEO_DECODER_DESC;

typedef struct D3D12_VIDEO_DECODER_HEAP_DESC
    {
    UINT NodeMask;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    UINT DecodeWidth;
    UINT DecodeHeight;
    DXGI_FORMAT Format;
    DXGI_RATIONAL FrameRate;
    UINT BitRate;
    UINT MaxDecodePictureBufferCount;
    } 	D3D12_VIDEO_DECODER_HEAP_DESC;

typedef struct D3D12_VIDEO_SIZE_RANGE
    {
    UINT MaxWidth;
    UINT MaxHeight;
    UINT MinWidth;
    UINT MinHeight;
    } 	D3D12_VIDEO_SIZE_RANGE;

typedef 
enum D3D12_VIDEO_PROCESS_FILTER
    {
        D3D12_VIDEO_PROCESS_FILTER_BRIGHTNESS	= 0,
        D3D12_VIDEO_PROCESS_FILTER_CONTRAST	= 1,
        D3D12_VIDEO_PROCESS_FILTER_HUE	= 2,
        D3D12_VIDEO_PROCESS_FILTER_SATURATION	= 3,
        D3D12_VIDEO_PROCESS_FILTER_NOISE_REDUCTION	= 4,
        D3D12_VIDEO_PROCESS_FILTER_EDGE_ENHANCEMENT	= 5,
        D3D12_VIDEO_PROCESS_FILTER_ANAMORPHIC_SCALING	= 6,
        D3D12_VIDEO_PROCESS_FILTER_STEREO_ADJUSTMENT	= 7
    } 	D3D12_VIDEO_PROCESS_FILTER;

typedef 
enum D3D12_VIDEO_PROCESS_FILTER_FLAGS
    {
        D3D12_VIDEO_PROCESS_FILTER_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_BRIGHTNESS	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_BRIGHTNESS ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_CONTRAST	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_CONTRAST ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_HUE	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_HUE ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_SATURATION	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_SATURATION ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_NOISE_REDUCTION	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_NOISE_REDUCTION ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_EDGE_ENHANCEMENT	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_EDGE_ENHANCEMENT ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_ANAMORPHIC_SCALING	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_ANAMORPHIC_SCALING ) ,
        D3D12_VIDEO_PROCESS_FILTER_FLAG_STEREO_ADJUSTMENT	= ( 1 << D3D12_VIDEO_PROCESS_FILTER_STEREO_ADJUSTMENT ) 
    } 	D3D12_VIDEO_PROCESS_FILTER_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_FILTER_FLAGS );
typedef 
enum D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS
    {
        D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_BOB	= 0x1,
        D3D12_VIDEO_PROCESS_DEINTERLACE_FLAG_CUSTOM	= 0x80000000
    } 	D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS );
typedef struct D3D12_VIDEO_PROCESS_ALPHA_BLENDING
    {
    BOOL Enable;
    FLOAT Alpha;
    } 	D3D12_VIDEO_PROCESS_ALPHA_BLENDING;

typedef struct D3D12_VIDEO_PROCESS_LUMA_KEY
    {
    BOOL Enable;
    FLOAT Lower;
    FLOAT Upper;
    } 	D3D12_VIDEO_PROCESS_LUMA_KEY;

typedef struct D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC
    {
    DXGI_FORMAT Format;
    DXGI_COLOR_SPACE_TYPE ColorSpace;
    DXGI_RATIONAL SourceAspectRatio;
    DXGI_RATIONAL DestinationAspectRatio;
    DXGI_RATIONAL FrameRate;
    D3D12_VIDEO_SIZE_RANGE SourceSizeRange;
    D3D12_VIDEO_SIZE_RANGE DestinationSizeRange;
    BOOL EnableOrientation;
    D3D12_VIDEO_PROCESS_FILTER_FLAGS FilterFlags;
    D3D12_VIDEO_FRAME_STEREO_FORMAT StereoFormat;
    D3D12_VIDEO_FIELD_TYPE FieldType;
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS DeinterlaceMode;
    BOOL EnableAlphaBlending;
    D3D12_VIDEO_PROCESS_LUMA_KEY LumaKey;
    UINT NumPastFrames;
    UINT NumFutureFrames;
    BOOL EnableAutoProcessing;
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC;

typedef 
enum D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE
    {
        D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_OPAQUE	= 0,
        D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_BACKGROUND	= 1,
        D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_DESTINATION	= 2,
        D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE_SOURCE_STREAM	= 3
    } 	D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE;

typedef struct D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC
    {
    DXGI_FORMAT Format;
    DXGI_COLOR_SPACE_TYPE ColorSpace;
    D3D12_VIDEO_PROCESS_ALPHA_FILL_MODE AlphaFillMode;
    UINT AlphaFillModeSourceStreamIndex;
    FLOAT BackgroundColor[ 4 ];
    DXGI_RATIONAL FrameRate;
    BOOL EnableStereo;
    } 	D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D12VideoDecoderHeap_INTERFACE_DEFINED__
#define __ID3D12VideoDecoderHeap_INTERFACE_DEFINED__

/* interface ID3D12VideoDecoderHeap */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDecoderHeap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0946B7C9-EBF6-4047-BB73-8683E27DBB1F")
    ID3D12VideoDecoderHeap : public ID3D12Pageable
    {
    public:
        virtual D3D12_VIDEO_DECODER_HEAP_DESC STDMETHODCALLTYPE GetDesc( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDecoderHeapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDecoderHeap * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDecoderHeap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDecoderHeap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoDecoderHeap * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoDecoderHeap * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoDecoderHeap * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoDecoderHeap * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoDecoderHeap * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_VIDEO_DECODER_HEAP_DESC ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D12VideoDecoderHeap * This);
        
        END_INTERFACE
    } ID3D12VideoDecoderHeapVtbl;

    interface ID3D12VideoDecoderHeap
    {
        CONST_VTBL struct ID3D12VideoDecoderHeapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDecoderHeap_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDecoderHeap_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDecoderHeap_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDecoderHeap_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoDecoderHeap_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoDecoderHeap_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoDecoderHeap_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoDecoderHeap_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12VideoDecoderHeap_GetDesc(This)	\
    ( (This)->lpVtbl -> GetDesc(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */








#endif 	/* __ID3D12VideoDecoderHeap_INTERFACE_DEFINED__ */


#ifndef __ID3D12VideoDevice_INTERFACE_DEFINED__
#define __ID3D12VideoDevice_INTERFACE_DEFINED__

/* interface ID3D12VideoDevice */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1F052807-0B46-4ACC-8A89-364F793718A4")
    ID3D12VideoDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport( 
            D3D12_FEATURE_VIDEO FeatureVideo,
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT FeatureSupportDataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateVideoDecoder( 
            _In_  const D3D12_VIDEO_DECODER_DESC *pDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateVideoDecoderHeap( 
            _In_  const D3D12_VIDEO_DECODER_HEAP_DESC *pVideoDecoderHeapDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoderHeap) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateVideoProcessor( 
            UINT NodeMask,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC *pOutputStreamDesc,
            UINT NumInputStreamDescs,
            _In_reads_(NumInputStreamDescs)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoProcessor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDevice * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckFeatureSupport )( 
            ID3D12VideoDevice * This,
            D3D12_FEATURE_VIDEO FeatureVideo,
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT FeatureSupportDataSize);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoDecoder )( 
            ID3D12VideoDevice * This,
            _In_  const D3D12_VIDEO_DECODER_DESC *pDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoder);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoDecoderHeap )( 
            ID3D12VideoDevice * This,
            _In_  const D3D12_VIDEO_DECODER_HEAP_DESC *pVideoDecoderHeapDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoderHeap);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoProcessor )( 
            ID3D12VideoDevice * This,
            UINT NodeMask,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC *pOutputStreamDesc,
            UINT NumInputStreamDescs,
            _In_reads_(NumInputStreamDescs)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoProcessor);
        
        END_INTERFACE
    } ID3D12VideoDeviceVtbl;

    interface ID3D12VideoDevice
    {
        CONST_VTBL struct ID3D12VideoDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDevice_CheckFeatureSupport(This,FeatureVideo,pFeatureSupportData,FeatureSupportDataSize)	\
    ( (This)->lpVtbl -> CheckFeatureSupport(This,FeatureVideo,pFeatureSupportData,FeatureSupportDataSize) ) 

#define ID3D12VideoDevice_CreateVideoDecoder(This,pDesc,riid,ppVideoDecoder)	\
    ( (This)->lpVtbl -> CreateVideoDecoder(This,pDesc,riid,ppVideoDecoder) ) 

#define ID3D12VideoDevice_CreateVideoDecoderHeap(This,pVideoDecoderHeapDesc,riid,ppVideoDecoderHeap)	\
    ( (This)->lpVtbl -> CreateVideoDecoderHeap(This,pVideoDecoderHeapDesc,riid,ppVideoDecoderHeap) ) 

#define ID3D12VideoDevice_CreateVideoProcessor(This,NodeMask,pOutputStreamDesc,NumInputStreamDescs,pInputStreamDescs,riid,ppVideoProcessor)	\
    ( (This)->lpVtbl -> CreateVideoProcessor(This,NodeMask,pOutputStreamDesc,NumInputStreamDescs,pInputStreamDescs,riid,ppVideoProcessor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoDevice_INTERFACE_DEFINED__ */


#ifndef __ID3D12VideoDecoder_INTERFACE_DEFINED__
#define __ID3D12VideoDecoder_INTERFACE_DEFINED__

/* interface ID3D12VideoDecoder */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C59B6BDC-7720-4074-A136-17A156037470")
    ID3D12VideoDecoder : public ID3D12Pageable
    {
    public:
        virtual D3D12_VIDEO_DECODER_DESC STDMETHODCALLTYPE GetDesc( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDecoder * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDecoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDecoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoDecoder * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoDecoder * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoDecoder * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoDecoder * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoDecoder * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_VIDEO_DECODER_DESC ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D12VideoDecoder * This);
        
        END_INTERFACE
    } ID3D12VideoDecoderVtbl;

    interface ID3D12VideoDecoder
    {
        CONST_VTBL struct ID3D12VideoDecoderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDecoder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDecoder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDecoder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDecoder_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoDecoder_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoDecoder_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoDecoder_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoDecoder_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12VideoDecoder_GetDesc(This)	\
    ( (This)->lpVtbl -> GetDesc(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */








#endif 	/* __ID3D12VideoDecoder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0003 */
/* [local] */ 

typedef 
enum D3D12_VIDEO_DECODE_TIER
    {
        D3D12_VIDEO_DECODE_TIER_NOT_SUPPORTED	= 0,
        D3D12_VIDEO_DECODE_TIER_1	= 1,
        D3D12_VIDEO_DECODE_TIER_2	= 2,
        D3D12_VIDEO_DECODE_TIER_3	= 3
    } 	D3D12_VIDEO_DECODE_TIER;

typedef 
enum D3D12_VIDEO_DECODE_SUPPORT_FLAGS
    {
        D3D12_VIDEO_DECODE_SUPPORT_FLAG_NONE	= 0,
        D3D12_VIDEO_DECODE_SUPPORT_FLAG_SUPPORTED	= 0x1
    } 	D3D12_VIDEO_DECODE_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_DECODE_SUPPORT_FLAGS );
typedef 
enum D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS
    {
        D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_NONE	= 0,
        D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_HEIGHT_ALIGNMENT_MULTIPLE_32_REQUIRED	= 0x1,
        D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_POST_PROCESSING_SUPPORTED	= 0x2,
        D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_REFERENCE_ONLY_ALLOCATIONS_REQUIRED	= 0x4,
        D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_ALLOW_RESOLUTION_CHANGE_ON_NON_KEY_FRAME	= 0x8
    } 	D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS );
typedef 
enum D3D12_VIDEO_DECODE_STATUS
    {
        D3D12_VIDEO_DECODE_STATUS_OK	= 0,
        D3D12_VIDEO_DECODE_STATUS_CONTINUE	= 1,
        D3D12_VIDEO_DECODE_STATUS_CONTINUE_SKIP_DISPLAY	= 2,
        D3D12_VIDEO_DECODE_STATUS_RESTART	= 3
    } 	D3D12_VIDEO_DECODE_STATUS;

typedef 
enum D3D12_VIDEO_DECODE_ARGUMENT_TYPE
    {
        D3D12_VIDEO_DECODE_ARGUMENT_TYPE_PICTURE_PARAMETERS	= 0,
        D3D12_VIDEO_DECODE_ARGUMENT_TYPE_INVERSE_QUANTIZATION_MATRIX	= 1,
        D3D12_VIDEO_DECODE_ARGUMENT_TYPE_SLICE_CONTROL	= 2,
        D3D12_VIDEO_DECODE_ARGUMENT_TYPE_MAX_VALID	= 3
    } 	D3D12_VIDEO_DECODE_ARGUMENT_TYPE;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT
    {
    UINT NodeIndex;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    UINT Width;
    UINT Height;
    DXGI_FORMAT DecodeFormat;
    DXGI_RATIONAL FrameRate;
    UINT BitRate;
    D3D12_VIDEO_DECODE_SUPPORT_FLAGS SupportFlags;
    D3D12_VIDEO_DECODE_CONFIGURATION_FLAGS ConfigurationFlags;
    D3D12_VIDEO_DECODE_TIER DecodeTier;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILE_COUNT
    {
    UINT NodeIndex;
    UINT ProfileCount;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILE_COUNT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILES
    {
    UINT NodeIndex;
    UINT ProfileCount;
    _Field_size_full_(ProfileCount)  GUID *pProfiles;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILES;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_FORMAT_COUNT
    {
    UINT NodeIndex;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    UINT FormatCount;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_FORMAT_COUNT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_FORMATS
    {
    UINT NodeIndex;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    UINT FormatCount;
    _Field_size_full_(FormatCount)  DXGI_FORMAT *pOutputFormats;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_FORMATS;

typedef struct D3D12_FEATURE_DATA_VIDEO_ARCHITECTURE
    {
    BOOL IOCoherent;
    } 	D3D12_FEATURE_DATA_VIDEO_ARCHITECTURE;

typedef 
enum D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT
    {
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_Y	= 0,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_U	= 1,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_V	= 2,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_R	= 0,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_G	= 1,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_B	= 2,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_A	= 3
    } 	D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT;

typedef 
enum D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS
    {
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_NONE	= 0,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_Y	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_Y ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_U	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_U ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_V	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_V ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_R	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_R ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_G	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_G ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_B	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_B ) ,
        D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAG_A	= ( 1 << D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_A ) 
    } 	D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS );
typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_HISTOGRAM
    {
    UINT NodeIndex;
    GUID DecodeProfile;
    UINT Width;
    UINT Height;
    DXGI_FORMAT DecodeFormat;
    D3D12_VIDEO_DECODE_HISTOGRAM_COMPONENT_FLAGS Components;
    UINT BinCount;
    UINT CounterBitDepth;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_HISTOGRAM;

typedef 
enum D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS
    {
        D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAG_NONE	= 0,
        D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAG_SUPPORTED	= 0x1
    } 	D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS );
typedef 
enum D3D12_VIDEO_SCALE_SUPPORT_FLAGS
    {
        D3D12_VIDEO_SCALE_SUPPORT_FLAG_NONE	= 0,
        D3D12_VIDEO_SCALE_SUPPORT_FLAG_POW2_ONLY	= 0x1,
        D3D12_VIDEO_SCALE_SUPPORT_FLAG_EVEN_DIMENSIONS_ONLY	= 0x2
    } 	D3D12_VIDEO_SCALE_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_SCALE_SUPPORT_FLAGS );
typedef struct D3D12_VIDEO_SCALE_SUPPORT
    {
    D3D12_VIDEO_SIZE_RANGE OutputSizeRange;
    D3D12_VIDEO_SCALE_SUPPORT_FLAGS Flags;
    } 	D3D12_VIDEO_SCALE_SUPPORT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODE_CONVERSION_SUPPORT
    {
    UINT NodeIndex;
    D3D12_VIDEO_DECODE_CONFIGURATION Configuration;
    D3D12_VIDEO_SAMPLE DecodeSample;
    D3D12_VIDEO_FORMAT OutputFormat;
    DXGI_RATIONAL FrameRate;
    UINT BitRate;
    D3D12_VIDEO_DECODE_CONVERSION_SUPPORT_FLAGS SupportFlags;
    D3D12_VIDEO_SCALE_SUPPORT ScaleSupport;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODE_CONVERSION_SUPPORT;

typedef struct D3D12_FEATURE_DATA_VIDEO_DECODER_HEAP_SIZE
    {
    D3D12_VIDEO_DECODER_HEAP_DESC VideoDecoderHeapDesc;
    UINT64 MemoryPoolL0Size;
    UINT64 MemoryPoolL1Size;
    } 	D3D12_FEATURE_DATA_VIDEO_DECODER_HEAP_SIZE;

typedef struct D3D12_FEATURE_DATA_VIDEO_PROCESSOR_SIZE
    {
    UINT NodeMask;
    const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC *pOutputStreamDesc;
    UINT NumInputStreamDescs;
    const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs;
    UINT64 MemoryPoolL0Size;
    UINT64 MemoryPoolL1Size;
    } 	D3D12_FEATURE_DATA_VIDEO_PROCESSOR_SIZE;

typedef struct D3D12_QUERY_DATA_VIDEO_DECODE_STATISTICS
    {
    UINT64 Status;
    UINT64 NumMacroblocksAffected;
    DXGI_RATIONAL FrameRate;
    UINT BitRate;
    } 	D3D12_QUERY_DATA_VIDEO_DECODE_STATISTICS;

typedef struct D3D12_VIDEO_DECODE_SUB_SAMPLE_MAPPING_BLOCK
    {
    UINT ClearSize;
    UINT EncryptedSize;
    } 	D3D12_VIDEO_DECODE_SUB_SAMPLE_MAPPING_BLOCK;

typedef struct D3D12_VIDEO_DECODE_FRAME_ARGUMENT
    {
    D3D12_VIDEO_DECODE_ARGUMENT_TYPE Type;
    UINT Size;
    _Field_size_bytes_full_(Size)  void *pData;
    } 	D3D12_VIDEO_DECODE_FRAME_ARGUMENT;

typedef struct D3D12_VIDEO_DECODE_REFERENCE_FRAMES
    {
    UINT NumTexture2Ds;
    _Field_size_full_(NumTexture2Ds)  ID3D12Resource **ppTexture2Ds;
    _Field_size_full_(NumTexture2Ds)  UINT *pSubresources;
    _Field_size_full_opt_(NumTexture2Ds)  ID3D12VideoDecoderHeap **ppHeaps;
    } 	D3D12_VIDEO_DECODE_REFERENCE_FRAMES;

typedef struct D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM
    {
    ID3D12Resource *pBuffer;
    UINT64 Offset;
    UINT64 Size;
    } 	D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM;

typedef struct D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS
    {
    BOOL Enable;
    ID3D12Resource *pReferenceTexture2D;
    UINT ReferenceSubresource;
    DXGI_COLOR_SPACE_TYPE OutputColorSpace;
    DXGI_COLOR_SPACE_TYPE DecodeColorSpace;
    } 	D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS;

typedef struct D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS
    {
    UINT NumFrameArguments;
    D3D12_VIDEO_DECODE_FRAME_ARGUMENT FrameArguments[ 10 ];
    D3D12_VIDEO_DECODE_REFERENCE_FRAMES ReferenceFrames;
    D3D12_VIDEO_DECODE_COMPRESSED_BITSTREAM CompressedBitstream;
    ID3D12VideoDecoderHeap *pHeap;
    } 	D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS;

typedef struct D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS
    {
    ID3D12Resource *pOutputTexture2D;
    UINT OutputSubresource;
    D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS ConversionArguments;
    } 	D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0003_v0_0_s_ifspec;

#ifndef __ID3D12VideoProcessor_INTERFACE_DEFINED__
#define __ID3D12VideoProcessor_INTERFACE_DEFINED__

/* interface ID3D12VideoProcessor */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoProcessor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("304FDB32-BEDE-410A-8545-943AC6A46138")
    ID3D12VideoProcessor : public ID3D12Pageable
    {
    public:
        virtual UINT STDMETHODCALLTYPE GetNodeMask( void) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetNumInputStreamDescs( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInputStreamDescs( 
            UINT NumInputStreamDescs,
            _Out_writes_(NumInputStreamDescs)  D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs) = 0;
        
        virtual D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC STDMETHODCALLTYPE GetOutputStreamDesc( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoProcessorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoProcessor * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoProcessor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoProcessor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoProcessor * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoProcessor * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoProcessor * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoProcessor * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoProcessor * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        UINT ( STDMETHODCALLTYPE *GetNodeMask )( 
            ID3D12VideoProcessor * This);
        
        UINT ( STDMETHODCALLTYPE *GetNumInputStreamDescs )( 
            ID3D12VideoProcessor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInputStreamDescs )( 
            ID3D12VideoProcessor * This,
            UINT NumInputStreamDescs,
            _Out_writes_(NumInputStreamDescs)  D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs);
        
        D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC ( STDMETHODCALLTYPE *GetOutputStreamDesc )( 
            ID3D12VideoProcessor * This);
        
        END_INTERFACE
    } ID3D12VideoProcessorVtbl;

    interface ID3D12VideoProcessor
    {
        CONST_VTBL struct ID3D12VideoProcessorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoProcessor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoProcessor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoProcessor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoProcessor_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoProcessor_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoProcessor_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoProcessor_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoProcessor_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12VideoProcessor_GetNodeMask(This)	\
    ( (This)->lpVtbl -> GetNodeMask(This) ) 

#define ID3D12VideoProcessor_GetNumInputStreamDescs(This)	\
    ( (This)->lpVtbl -> GetNumInputStreamDescs(This) ) 

#define ID3D12VideoProcessor_GetInputStreamDescs(This,NumInputStreamDescs,pInputStreamDescs)	\
    ( (This)->lpVtbl -> GetInputStreamDescs(This,NumInputStreamDescs,pInputStreamDescs) ) 

#define ID3D12VideoProcessor_GetOutputStreamDesc(This)	\
    ( (This)->lpVtbl -> GetOutputStreamDesc(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */








#endif 	/* __ID3D12VideoProcessor_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0004 */
/* [local] */ 

typedef 
enum D3D12_VIDEO_PROCESS_FEATURE_FLAGS
    {
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_FILL	= 0x1,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_LUMA_KEY	= 0x2,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_STEREO	= 0x4,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_ROTATION	= 0x8,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_FLIP	= 0x10,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_ALPHA_BLENDING	= 0x20,
        D3D12_VIDEO_PROCESS_FEATURE_FLAG_PIXEL_ASPECT_RATIO	= 0x40
    } 	D3D12_VIDEO_PROCESS_FEATURE_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_FEATURE_FLAGS );
typedef 
enum D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS
    {
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_DENOISE	= 0x1,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_DERINGING	= 0x2,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_EDGE_ENHANCEMENT	= 0x4,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_COLOR_CORRECTION	= 0x8,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_FLESH_TONE_MAPPING	= 0x10,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_IMAGE_STABILIZATION	= 0x20,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_SUPER_RESOLUTION	= 0x40,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_ANAMORPHIC_SCALING	= 0x80,
        D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAG_CUSTOM	= 0x80000000
    } 	D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS );
typedef 
enum D3D12_VIDEO_PROCESS_ORIENTATION
    {
        D3D12_VIDEO_PROCESS_ORIENTATION_DEFAULT	= 0,
        D3D12_VIDEO_PROCESS_ORIENTATION_FLIP_HORIZONTAL	= 1,
        D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_90	= 2,
        D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_90_FLIP_HORIZONTAL	= 3,
        D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_180	= 4,
        D3D12_VIDEO_PROCESS_ORIENTATION_FLIP_VERTICAL	= 5,
        D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_270	= 6,
        D3D12_VIDEO_PROCESS_ORIENTATION_CLOCKWISE_270_FLIP_HORIZONTAL	= 7
    } 	D3D12_VIDEO_PROCESS_ORIENTATION;

typedef 
enum D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS
    {
        D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_FRAME_DISCONTINUITY	= 0x1,
        D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAG_FRAME_REPEAT	= 0x2
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS );
typedef struct D3D12_VIDEO_PROCESS_FILTER_RANGE
    {
    INT Minimum;
    INT Maximum;
    INT Default;
    FLOAT Multiplier;
    } 	D3D12_VIDEO_PROCESS_FILTER_RANGE;

typedef 
enum D3D12_VIDEO_PROCESS_SUPPORT_FLAGS
    {
        D3D12_VIDEO_PROCESS_SUPPORT_FLAG_NONE	= 0,
        D3D12_VIDEO_PROCESS_SUPPORT_FLAG_SUPPORTED	= 0x1
    } 	D3D12_VIDEO_PROCESS_SUPPORT_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS(D3D12_VIDEO_PROCESS_SUPPORT_FLAGS );
typedef struct D3D12_FEATURE_DATA_VIDEO_PROCESS_SUPPORT
    {
    UINT NodeIndex;
    D3D12_VIDEO_SAMPLE InputSample;
    D3D12_VIDEO_FIELD_TYPE InputFieldType;
    D3D12_VIDEO_FRAME_STEREO_FORMAT InputStereoFormat;
    DXGI_RATIONAL InputFrameRate;
    D3D12_VIDEO_FORMAT OutputFormat;
    D3D12_VIDEO_FRAME_STEREO_FORMAT OutputStereoFormat;
    DXGI_RATIONAL OutputFrameRate;
    D3D12_VIDEO_PROCESS_SUPPORT_FLAGS SupportFlags;
    D3D12_VIDEO_SCALE_SUPPORT ScaleSupport;
    D3D12_VIDEO_PROCESS_FEATURE_FLAGS FeatureSupport;
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS DeinterlaceSupport;
    D3D12_VIDEO_PROCESS_AUTO_PROCESSING_FLAGS AutoProcessingSupport;
    D3D12_VIDEO_PROCESS_FILTER_FLAGS FilterSupport;
    D3D12_VIDEO_PROCESS_FILTER_RANGE FilterRangeSupport[ 32 ];
    } 	D3D12_FEATURE_DATA_VIDEO_PROCESS_SUPPORT;

typedef struct D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS
    {
    UINT NodeIndex;
    UINT MaxInputStreams;
    } 	D3D12_FEATURE_DATA_VIDEO_PROCESS_MAX_INPUT_STREAMS;

typedef struct D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO
    {
    UINT NodeIndex;
    D3D12_VIDEO_PROCESS_DEINTERLACE_FLAGS DeinterlaceMode;
    D3D12_VIDEO_PROCESS_FILTER_FLAGS Filters;
    D3D12_VIDEO_PROCESS_FEATURE_FLAGS FeatureSupport;
    DXGI_RATIONAL InputFrameRate;
    DXGI_RATIONAL OutputFrameRate;
    BOOL EnableAutoProcessing;
    UINT PastFrames;
    UINT FutureFrames;
    } 	D3D12_FEATURE_DATA_VIDEO_PROCESS_REFERENCE_INFO;

typedef struct D3D12_VIDEO_PROCESS_REFERENCE_SET
    {
    UINT NumPastFrames;
    ID3D12Resource **ppPastFrames;
    UINT *pPastSubresources;
    UINT NumFutureFrames;
    ID3D12Resource **ppFutureFrames;
    UINT *pFutureSubresources;
    } 	D3D12_VIDEO_PROCESS_REFERENCE_SET;

typedef struct D3D12_VIDEO_PROCESS_TRANSFORM
    {
    D3D12_RECT SourceRectangle;
    D3D12_RECT DestinationRectangle;
    D3D12_VIDEO_PROCESS_ORIENTATION Orientation;
    } 	D3D12_VIDEO_PROCESS_TRANSFORM;

typedef struct D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE
    {
    UINT OutputIndex;
    UINT InputFrameOrField;
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE;

typedef struct D3D12_VIDEO_PROCESS_INPUT_STREAM
    {
    ID3D12Resource *pTexture2D;
    UINT Subresource;
    D3D12_VIDEO_PROCESS_REFERENCE_SET ReferenceSet;
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM;

typedef struct D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS
    {
    D3D12_VIDEO_PROCESS_INPUT_STREAM InputStream[ 2 ];
    D3D12_VIDEO_PROCESS_TRANSFORM Transform;
    D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS Flags;
    D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE RateInfo;
    INT FilterLevels[ 32 ];
    D3D12_VIDEO_PROCESS_ALPHA_BLENDING AlphaBlending;
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS;

typedef struct D3D12_VIDEO_PROCESS_OUTPUT_STREAM
    {
    ID3D12Resource *pTexture2D;
    UINT Subresource;
    } 	D3D12_VIDEO_PROCESS_OUTPUT_STREAM;

typedef struct D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS
    {
    D3D12_VIDEO_PROCESS_OUTPUT_STREAM OutputStream[ 2 ];
    D3D12_RECT TargetRectangle;
    } 	D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0004_v0_0_s_ifspec;

#ifndef __ID3D12VideoDecodeCommandList_INTERFACE_DEFINED__
#define __ID3D12VideoDecodeCommandList_INTERFACE_DEFINED__

/* interface ID3D12VideoDecodeCommandList */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDecodeCommandList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B60536E-AD29-4E64-A269-F853837E5E53")
    ID3D12VideoDecodeCommandList : public ID3D12CommandList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            _In_  ID3D12CommandAllocator *pAllocator) = 0;
        
        virtual void STDMETHODCALLTYPE ClearState( void) = 0;
        
        virtual void STDMETHODCALLTYPE ResourceBarrier( 
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers) = 0;
        
        virtual void STDMETHODCALLTYPE DiscardResource( 
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion) = 0;
        
        virtual void STDMETHODCALLTYPE BeginQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE EndQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE ResolveQueryData( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset) = 0;
        
        virtual void STDMETHODCALLTYPE SetPredication( 
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation) = 0;
        
        virtual void STDMETHODCALLTYPE SetMarker( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE BeginEvent( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE EndEvent( void) = 0;
        
        virtual void STDMETHODCALLTYPE DecodeFrame( 
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments) = 0;
        
        virtual void STDMETHODCALLTYPE WriteBufferImmediate( 
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDecodeCommandListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDecodeCommandList * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDecodeCommandList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDecodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoDecodeCommandList * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoDecodeCommandList * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoDecodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoDecodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoDecodeCommandList * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoDecodeCommandList * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoDecodeCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoDecodeCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoDecodeCommandList * This);
        
        void ( STDMETHODCALLTYPE *DecodeFrame )( 
            ID3D12VideoDecodeCommandList * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoDecodeCommandList * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        END_INTERFACE
    } ID3D12VideoDecodeCommandListVtbl;

    interface ID3D12VideoDecodeCommandList
    {
        CONST_VTBL struct ID3D12VideoDecodeCommandListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDecodeCommandList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDecodeCommandList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDecodeCommandList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDecodeCommandList_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoDecodeCommandList_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoDecodeCommandList_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoDecodeCommandList_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoDecodeCommandList_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoDecodeCommandList_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoDecodeCommandList_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoDecodeCommandList_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoDecodeCommandList_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoDecodeCommandList_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoDecodeCommandList_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoDecodeCommandList_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoDecodeCommandList_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoDecodeCommandList_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoDecodeCommandList_DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoDecodeCommandList_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoDecodeCommandList_INTERFACE_DEFINED__ */


#ifndef __ID3D12VideoProcessCommandList_INTERFACE_DEFINED__
#define __ID3D12VideoProcessCommandList_INTERFACE_DEFINED__

/* interface ID3D12VideoProcessCommandList */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoProcessCommandList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEB2543A-167F-4682-ACC8-D159ED4A6209")
    ID3D12VideoProcessCommandList : public ID3D12CommandList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            _In_  ID3D12CommandAllocator *pAllocator) = 0;
        
        virtual void STDMETHODCALLTYPE ClearState( void) = 0;
        
        virtual void STDMETHODCALLTYPE ResourceBarrier( 
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers) = 0;
        
        virtual void STDMETHODCALLTYPE DiscardResource( 
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion) = 0;
        
        virtual void STDMETHODCALLTYPE BeginQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE EndQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE ResolveQueryData( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset) = 0;
        
        virtual void STDMETHODCALLTYPE SetPredication( 
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation) = 0;
        
        virtual void STDMETHODCALLTYPE SetMarker( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE BeginEvent( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE EndEvent( void) = 0;
        
        virtual void STDMETHODCALLTYPE ProcessFrames( 
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS *pInputArguments) = 0;
        
        virtual void STDMETHODCALLTYPE WriteBufferImmediate( 
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoProcessCommandListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoProcessCommandList * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoProcessCommandList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoProcessCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoProcessCommandList * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoProcessCommandList * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoProcessCommandList * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoProcessCommandList * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoProcessCommandList * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoProcessCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoProcessCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoProcessCommandList * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoProcessCommandList * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoProcessCommandList * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoProcessCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoProcessCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoProcessCommandList * This);
        
        void ( STDMETHODCALLTYPE *ProcessFrames )( 
            ID3D12VideoProcessCommandList * This,
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoProcessCommandList * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        END_INTERFACE
    } ID3D12VideoProcessCommandListVtbl;

    interface ID3D12VideoProcessCommandList
    {
        CONST_VTBL struct ID3D12VideoProcessCommandListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoProcessCommandList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoProcessCommandList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoProcessCommandList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoProcessCommandList_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoProcessCommandList_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoProcessCommandList_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoProcessCommandList_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoProcessCommandList_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoProcessCommandList_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoProcessCommandList_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoProcessCommandList_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoProcessCommandList_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoProcessCommandList_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoProcessCommandList_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoProcessCommandList_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoProcessCommandList_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoProcessCommandList_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoProcessCommandList_ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments)	\
    ( (This)->lpVtbl -> ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments) ) 

#define ID3D12VideoProcessCommandList_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoProcessCommandList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0006 */
/* [local] */ 

typedef struct D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM
    {
    UINT64 Offset;
    ID3D12Resource *pBuffer;
    } 	D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM;

typedef struct D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1
    {
    BOOL Enable;
    ID3D12Resource *pReferenceTexture2D;
    UINT ReferenceSubresource;
    DXGI_COLOR_SPACE_TYPE OutputColorSpace;
    DXGI_COLOR_SPACE_TYPE DecodeColorSpace;
    UINT OutputWidth;
    UINT OutputHeight;
    } 	D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1;

typedef struct D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1
    {
    ID3D12Resource *pOutputTexture2D;
    UINT OutputSubresource;
    D3D12_VIDEO_DECODE_CONVERSION_ARGUMENTS1 ConversionArguments;
    D3D12_VIDEO_DECODE_OUTPUT_HISTOGRAM Histograms[ 4 ];
    } 	D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0006_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0006_v0_0_s_ifspec;

#ifndef __ID3D12VideoDecodeCommandList1_INTERFACE_DEFINED__
#define __ID3D12VideoDecodeCommandList1_INTERFACE_DEFINED__

/* interface ID3D12VideoDecodeCommandList1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDecodeCommandList1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D52F011B-B56E-453C-A05A-A7F311C8F472")
    ID3D12VideoDecodeCommandList1 : public ID3D12VideoDecodeCommandList
    {
    public:
        virtual void STDMETHODCALLTYPE DecodeFrame1( 
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDecodeCommandList1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDecodeCommandList1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoDecodeCommandList1 * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoDecodeCommandList1 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoDecodeCommandList1 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoDecodeCommandList1 * This);
        
        void ( STDMETHODCALLTYPE *DecodeFrame )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoDecodeCommandList1 * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        void ( STDMETHODCALLTYPE *DecodeFrame1 )( 
            ID3D12VideoDecodeCommandList1 * This,
            _In_  ID3D12VideoDecoder *pDecoder,
            _In_  const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 *pOutputArguments,
            _In_  const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        END_INTERFACE
    } ID3D12VideoDecodeCommandList1Vtbl;

    interface ID3D12VideoDecodeCommandList1
    {
        CONST_VTBL struct ID3D12VideoDecodeCommandList1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDecodeCommandList1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDecodeCommandList1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDecodeCommandList1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDecodeCommandList1_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoDecodeCommandList1_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoDecodeCommandList1_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoDecodeCommandList1_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoDecodeCommandList1_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoDecodeCommandList1_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoDecodeCommandList1_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoDecodeCommandList1_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoDecodeCommandList1_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoDecodeCommandList1_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoDecodeCommandList1_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoDecodeCommandList1_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList1_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoDecodeCommandList1_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoDecodeCommandList1_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoDecodeCommandList1_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList1_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoDecodeCommandList1_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoDecodeCommandList1_DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame(This,pDecoder,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoDecodeCommandList1_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 


#define ID3D12VideoDecodeCommandList1_DecodeFrame1(This,pDecoder,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> DecodeFrame1(This,pDecoder,pOutputArguments,pInputArguments) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoDecodeCommandList1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0007 */
/* [local] */ 

typedef struct D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1
    {
    D3D12_VIDEO_PROCESS_INPUT_STREAM InputStream[ 2 ];
    D3D12_VIDEO_PROCESS_TRANSFORM Transform;
    D3D12_VIDEO_PROCESS_INPUT_STREAM_FLAGS Flags;
    D3D12_VIDEO_PROCESS_INPUT_STREAM_RATE RateInfo;
    INT FilterLevels[ 32 ];
    D3D12_VIDEO_PROCESS_ALPHA_BLENDING AlphaBlending;
    D3D12_VIDEO_FIELD_TYPE FieldType;
    } 	D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0007_v0_0_s_ifspec;

#ifndef __ID3D12VideoProcessCommandList1_INTERFACE_DEFINED__
#define __ID3D12VideoProcessCommandList1_INTERFACE_DEFINED__

/* interface ID3D12VideoProcessCommandList1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoProcessCommandList1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("542C5C4D-7596-434F-8C93-4EFA6766F267")
    ID3D12VideoProcessCommandList1 : public ID3D12VideoProcessCommandList
    {
    public:
        virtual void STDMETHODCALLTYPE ProcessFrames1( 
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1 *pInputArguments) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoProcessCommandList1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoProcessCommandList1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoProcessCommandList1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoProcessCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoProcessCommandList1 * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoProcessCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoProcessCommandList1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoProcessCommandList1 * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoProcessCommandList1 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoProcessCommandList1 * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoProcessCommandList1 * This);
        
        void ( STDMETHODCALLTYPE *ProcessFrames )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoProcessCommandList1 * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        void ( STDMETHODCALLTYPE *ProcessFrames1 )( 
            ID3D12VideoProcessCommandList1 * This,
            _In_  ID3D12VideoProcessor *pVideoProcessor,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS *pOutputArguments,
            UINT NumInputStreams,
            _In_reads_(NumInputStreams)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1 *pInputArguments);
        
        END_INTERFACE
    } ID3D12VideoProcessCommandList1Vtbl;

    interface ID3D12VideoProcessCommandList1
    {
        CONST_VTBL struct ID3D12VideoProcessCommandList1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoProcessCommandList1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoProcessCommandList1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoProcessCommandList1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoProcessCommandList1_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoProcessCommandList1_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoProcessCommandList1_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoProcessCommandList1_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoProcessCommandList1_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoProcessCommandList1_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoProcessCommandList1_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoProcessCommandList1_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoProcessCommandList1_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoProcessCommandList1_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoProcessCommandList1_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoProcessCommandList1_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList1_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoProcessCommandList1_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoProcessCommandList1_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoProcessCommandList1_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList1_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoProcessCommandList1_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoProcessCommandList1_ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments)	\
    ( (This)->lpVtbl -> ProcessFrames(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments) ) 

#define ID3D12VideoProcessCommandList1_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 


#define ID3D12VideoProcessCommandList1_ProcessFrames1(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments)	\
    ( (This)->lpVtbl -> ProcessFrames1(This,pVideoProcessor,pOutputArguments,NumInputStreams,pInputArguments) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoProcessCommandList1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0008 */
/* [local] */ 

typedef 
enum D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE
    {
        D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_8X8	= 0,
        D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_16X16	= 1
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE;

typedef 
enum D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS
    {
        D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_NONE	= 0,
        D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_8X8	= ( 1 << D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_8X8 ) ,
        D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAG_16X16	= ( 1 << D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_16X16 ) 
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS );
typedef 
enum D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION
    {
        D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_QUARTER_PEL	= 0
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION;

typedef 
enum D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS
    {
        D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAG_NONE	= 0,
        D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAG_QUARTER_PEL	= ( 1 << D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_QUARTER_PEL ) 
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS;

DEFINE_ENUM_FLAG_OPERATORS( D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS );
typedef struct D3D12_FEATURE_DATA_VIDEO_FEATURE_AREA_SUPPORT
    {
    UINT NodeIndex;
    BOOL VideoDecodeSupport;
    BOOL VideoProcessSupport;
    BOOL VideoEncodeSupport;
    } 	D3D12_FEATURE_DATA_VIDEO_FEATURE_AREA_SUPPORT;

typedef struct D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR
    {
    UINT NodeIndex;
    DXGI_FORMAT InputFormat;
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE_FLAGS BlockSizeFlags;
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION_FLAGS PrecisionFlags;
    D3D12_VIDEO_SIZE_RANGE SizeRange;
    } 	D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR;

typedef struct D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR_SIZE
    {
    UINT NodeIndex;
    DXGI_FORMAT InputFormat;
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE BlockSize;
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION Precision;
    D3D12_VIDEO_SIZE_RANGE SizeRange;
    BOOL Protected;
    UINT64 MotionVectorHeapMemoryPoolL0Size;
    UINT64 MotionVectorHeapMemoryPoolL1Size;
    UINT64 MotionEstimatorMemoryPoolL0Size;
    UINT64 MotionEstimatorMemoryPoolL1Size;
    } 	D3D12_FEATURE_DATA_VIDEO_MOTION_ESTIMATOR_SIZE;

typedef struct D3D12_VIDEO_MOTION_ESTIMATOR_DESC
    {
    UINT NodeMask;
    DXGI_FORMAT InputFormat;
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE BlockSize;
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION Precision;
    D3D12_VIDEO_SIZE_RANGE SizeRange;
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_DESC;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0008_v0_0_s_ifspec;

#ifndef __ID3D12VideoMotionEstimator_INTERFACE_DEFINED__
#define __ID3D12VideoMotionEstimator_INTERFACE_DEFINED__

/* interface ID3D12VideoMotionEstimator */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoMotionEstimator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("33FDAE0E-098B-428F-87BB-34B695DE08F8")
    ID3D12VideoMotionEstimator : public ID3D12Pageable
    {
    public:
        virtual D3D12_VIDEO_MOTION_ESTIMATOR_DESC STDMETHODCALLTYPE GetDesc( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProtectedResourceSession( 
            REFIID riid,
            _COM_Outptr_opt_  void **ppProtectedSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoMotionEstimatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoMotionEstimator * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoMotionEstimator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoMotionEstimator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoMotionEstimator * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoMotionEstimator * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoMotionEstimator * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoMotionEstimator * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoMotionEstimator * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_VIDEO_MOTION_ESTIMATOR_DESC ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D12VideoMotionEstimator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetProtectedResourceSession )( 
            ID3D12VideoMotionEstimator * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppProtectedSession);
        
        END_INTERFACE
    } ID3D12VideoMotionEstimatorVtbl;

    interface ID3D12VideoMotionEstimator
    {
        CONST_VTBL struct ID3D12VideoMotionEstimatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoMotionEstimator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoMotionEstimator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoMotionEstimator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoMotionEstimator_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoMotionEstimator_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoMotionEstimator_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoMotionEstimator_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoMotionEstimator_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12VideoMotionEstimator_GetDesc(This)	\
    ( (This)->lpVtbl -> GetDesc(This) ) 

#define ID3D12VideoMotionEstimator_GetProtectedResourceSession(This,riid,ppProtectedSession)	\
    ( (This)->lpVtbl -> GetProtectedResourceSession(This,riid,ppProtectedSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */








#endif 	/* __ID3D12VideoMotionEstimator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0009 */
/* [local] */ 

typedef struct D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC
    {
    UINT NodeMask;
    DXGI_FORMAT InputFormat;
    D3D12_VIDEO_MOTION_ESTIMATOR_SEARCH_BLOCK_SIZE BlockSize;
    D3D12_VIDEO_MOTION_ESTIMATOR_VECTOR_PRECISION Precision;
    D3D12_VIDEO_SIZE_RANGE SizeRange;
    } 	D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0009_v0_0_s_ifspec;

#ifndef __ID3D12VideoMotionVectorHeap_INTERFACE_DEFINED__
#define __ID3D12VideoMotionVectorHeap_INTERFACE_DEFINED__

/* interface ID3D12VideoMotionVectorHeap */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoMotionVectorHeap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5BE17987-743A-4061-834B-23D22DAEA505")
    ID3D12VideoMotionVectorHeap : public ID3D12Pageable
    {
    public:
        virtual D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC STDMETHODCALLTYPE GetDesc( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProtectedResourceSession( 
            REFIID riid,
            _COM_Outptr_opt_  void **ppProtectedSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoMotionVectorHeapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoMotionVectorHeap * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoMotionVectorHeap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoMotionVectorHeap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoMotionVectorHeap * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoMotionVectorHeap * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoMotionVectorHeap * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoMotionVectorHeap * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoMotionVectorHeap * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D12VideoMotionVectorHeap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetProtectedResourceSession )( 
            ID3D12VideoMotionVectorHeap * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppProtectedSession);
        
        END_INTERFACE
    } ID3D12VideoMotionVectorHeapVtbl;

    interface ID3D12VideoMotionVectorHeap
    {
        CONST_VTBL struct ID3D12VideoMotionVectorHeapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoMotionVectorHeap_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoMotionVectorHeap_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoMotionVectorHeap_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoMotionVectorHeap_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoMotionVectorHeap_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoMotionVectorHeap_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoMotionVectorHeap_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoMotionVectorHeap_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 



#define ID3D12VideoMotionVectorHeap_GetDesc(This)	\
    ( (This)->lpVtbl -> GetDesc(This) ) 

#define ID3D12VideoMotionVectorHeap_GetProtectedResourceSession(This,riid,ppProtectedSession)	\
    ( (This)->lpVtbl -> GetProtectedResourceSession(This,riid,ppProtectedSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */








#endif 	/* __ID3D12VideoMotionVectorHeap_INTERFACE_DEFINED__ */


#ifndef __ID3D12VideoDevice1_INTERFACE_DEFINED__
#define __ID3D12VideoDevice1_INTERFACE_DEFINED__

/* interface ID3D12VideoDevice1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoDevice1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("981611AD-A144-4C83-9890-F30E26D658AB")
    ID3D12VideoDevice1 : public ID3D12VideoDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateVideoMotionEstimator( 
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_DESC *pDesc,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoMotionEstimator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateVideoMotionVectorHeap( 
            _In_  const D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC *pDesc,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoMotionVectorHeap) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoDevice1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoDevice1 * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoDevice1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoDevice1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CheckFeatureSupport )( 
            ID3D12VideoDevice1 * This,
            D3D12_FEATURE_VIDEO FeatureVideo,
            _Inout_updates_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
            UINT FeatureSupportDataSize);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoDecoder )( 
            ID3D12VideoDevice1 * This,
            _In_  const D3D12_VIDEO_DECODER_DESC *pDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoder);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoDecoderHeap )( 
            ID3D12VideoDevice1 * This,
            _In_  const D3D12_VIDEO_DECODER_HEAP_DESC *pVideoDecoderHeapDesc,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoDecoderHeap);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoProcessor )( 
            ID3D12VideoDevice1 * This,
            UINT NodeMask,
            _In_  const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC *pOutputStreamDesc,
            UINT NumInputStreamDescs,
            _In_reads_(NumInputStreamDescs)  const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC *pInputStreamDescs,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoProcessor);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoMotionEstimator )( 
            ID3D12VideoDevice1 * This,
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_DESC *pDesc,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoMotionEstimator);
        
        HRESULT ( STDMETHODCALLTYPE *CreateVideoMotionVectorHeap )( 
            ID3D12VideoDevice1 * This,
            _In_  const D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC *pDesc,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession,
            _In_  REFIID riid,
            _COM_Outptr_  void **ppVideoMotionVectorHeap);
        
        END_INTERFACE
    } ID3D12VideoDevice1Vtbl;

    interface ID3D12VideoDevice1
    {
        CONST_VTBL struct ID3D12VideoDevice1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoDevice1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoDevice1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoDevice1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoDevice1_CheckFeatureSupport(This,FeatureVideo,pFeatureSupportData,FeatureSupportDataSize)	\
    ( (This)->lpVtbl -> CheckFeatureSupport(This,FeatureVideo,pFeatureSupportData,FeatureSupportDataSize) ) 

#define ID3D12VideoDevice1_CreateVideoDecoder(This,pDesc,riid,ppVideoDecoder)	\
    ( (This)->lpVtbl -> CreateVideoDecoder(This,pDesc,riid,ppVideoDecoder) ) 

#define ID3D12VideoDevice1_CreateVideoDecoderHeap(This,pVideoDecoderHeapDesc,riid,ppVideoDecoderHeap)	\
    ( (This)->lpVtbl -> CreateVideoDecoderHeap(This,pVideoDecoderHeapDesc,riid,ppVideoDecoderHeap) ) 

#define ID3D12VideoDevice1_CreateVideoProcessor(This,NodeMask,pOutputStreamDesc,NumInputStreamDescs,pInputStreamDescs,riid,ppVideoProcessor)	\
    ( (This)->lpVtbl -> CreateVideoProcessor(This,NodeMask,pOutputStreamDesc,NumInputStreamDescs,pInputStreamDescs,riid,ppVideoProcessor) ) 


#define ID3D12VideoDevice1_CreateVideoMotionEstimator(This,pDesc,pProtectedResourceSession,riid,ppVideoMotionEstimator)	\
    ( (This)->lpVtbl -> CreateVideoMotionEstimator(This,pDesc,pProtectedResourceSession,riid,ppVideoMotionEstimator) ) 

#define ID3D12VideoDevice1_CreateVideoMotionVectorHeap(This,pDesc,pProtectedResourceSession,riid,ppVideoMotionVectorHeap)	\
    ( (This)->lpVtbl -> CreateVideoMotionVectorHeap(This,pDesc,pProtectedResourceSession,riid,ppVideoMotionVectorHeap) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoDevice1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0011 */
/* [local] */ 

typedef struct D3D12_RESOURCE_COORDINATE
    {
    UINT64 X;
    UINT Y;
    UINT Z;
    UINT SubresourceIndex;
    } 	D3D12_RESOURCE_COORDINATE;

typedef struct D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT
    {
    ID3D12VideoMotionVectorHeap *pMotionVectorHeap;
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT;

typedef struct D3D12_VIDEO_MOTION_ESTIMATOR_INPUT
    {
    ID3D12Resource *pInputTexture2D;
    UINT InputSubresourceIndex;
    ID3D12Resource *pReferenceTexture2D;
    UINT ReferenceSubresourceIndex;
    ID3D12VideoMotionVectorHeap *pHintMotionVectorHeap;
    } 	D3D12_VIDEO_MOTION_ESTIMATOR_INPUT;

typedef struct D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT
    {
    ID3D12Resource *pMotionVectorTexture2D;
    D3D12_RESOURCE_COORDINATE MotionVectorCoordinate;
    } 	D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT;

typedef struct D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT
    {
    ID3D12VideoMotionVectorHeap *pMotionVectorHeap;
    UINT PixelWidth;
    UINT PixelHeight;
    } 	D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT;



extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0011_v0_0_s_ifspec;

#ifndef __ID3D12VideoEncodeCommandList_INTERFACE_DEFINED__
#define __ID3D12VideoEncodeCommandList_INTERFACE_DEFINED__

/* interface ID3D12VideoEncodeCommandList */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D12VideoEncodeCommandList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8455293A-0CBD-4831-9B39-FBDBAB724723")
    ID3D12VideoEncodeCommandList : public ID3D12CommandList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            _In_  ID3D12CommandAllocator *pAllocator) = 0;
        
        virtual void STDMETHODCALLTYPE ClearState( void) = 0;
        
        virtual void STDMETHODCALLTYPE ResourceBarrier( 
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers) = 0;
        
        virtual void STDMETHODCALLTYPE DiscardResource( 
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion) = 0;
        
        virtual void STDMETHODCALLTYPE BeginQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE EndQuery( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index) = 0;
        
        virtual void STDMETHODCALLTYPE ResolveQueryData( 
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset) = 0;
        
        virtual void STDMETHODCALLTYPE SetPredication( 
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation) = 0;
        
        virtual void STDMETHODCALLTYPE SetMarker( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE BeginEvent( 
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size) = 0;
        
        virtual void STDMETHODCALLTYPE EndEvent( void) = 0;
        
        virtual void STDMETHODCALLTYPE EstimateMotion( 
            _In_  ID3D12VideoMotionEstimator *pMotionEstimator,
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT *pOutputArguments,
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_INPUT *pInputArguments) = 0;
        
        virtual void STDMETHODCALLTYPE ResolveMotionVectorHeap( 
            const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT *pOutputArguments,
            const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT *pInputArguments) = 0;
        
        virtual void STDMETHODCALLTYPE WriteBufferImmediate( 
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes) = 0;
        
        virtual void STDMETHODCALLTYPE SetProtectedResourceSession( 
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D12VideoEncodeCommandListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D12VideoEncodeCommandList * This,
            REFIID riid,
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D12VideoEncodeCommandList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D12VideoEncodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  REFGUID guid,
            _Inout_  UINT *pDataSize,
            _Out_writes_bytes_opt_( *pDataSize )  void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  REFGUID guid,
            _In_  UINT DataSize,
            _In_reads_bytes_opt_( DataSize )  const void *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  REFGUID guid,
            _In_opt_  const IUnknown *pData);
        
        HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ID3D12VideoEncodeCommandList * This,
            _In_z_  LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D12VideoEncodeCommandList * This,
            REFIID riid,
            _COM_Outptr_opt_  void **ppvDevice);
        
        D3D12_COMMAND_LIST_TYPE ( STDMETHODCALLTYPE *GetType )( 
            ID3D12VideoEncodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            ID3D12VideoEncodeCommandList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12CommandAllocator *pAllocator);
        
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D12VideoEncodeCommandList * This);
        
        void ( STDMETHODCALLTYPE *ResourceBarrier )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  UINT NumBarriers,
            _In_reads_(NumBarriers)  const D3D12_RESOURCE_BARRIER *pBarriers);
        
        void ( STDMETHODCALLTYPE *DiscardResource )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12Resource *pResource,
            _In_opt_  const D3D12_DISCARD_REGION *pRegion);
        
        void ( STDMETHODCALLTYPE *BeginQuery )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *EndQuery )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT Index);
        
        void ( STDMETHODCALLTYPE *ResolveQueryData )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12QueryHeap *pQueryHeap,
            _In_  D3D12_QUERY_TYPE Type,
            _In_  UINT StartIndex,
            _In_  UINT NumQueries,
            _In_  ID3D12Resource *pDestinationBuffer,
            _In_  UINT64 AlignedDestinationBufferOffset);
        
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D12VideoEncodeCommandList * This,
            _In_opt_  ID3D12Resource *pBuffer,
            _In_  UINT64 AlignedBufferOffset,
            _In_  D3D12_PREDICATION_OP Operation);
        
        void ( STDMETHODCALLTYPE *SetMarker )( 
            ID3D12VideoEncodeCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *BeginEvent )( 
            ID3D12VideoEncodeCommandList * This,
            UINT Metadata,
            _In_reads_bytes_opt_(Size)  const void *pData,
            UINT Size);
        
        void ( STDMETHODCALLTYPE *EndEvent )( 
            ID3D12VideoEncodeCommandList * This);
        
        void ( STDMETHODCALLTYPE *EstimateMotion )( 
            ID3D12VideoEncodeCommandList * This,
            _In_  ID3D12VideoMotionEstimator *pMotionEstimator,
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT *pOutputArguments,
            _In_  const D3D12_VIDEO_MOTION_ESTIMATOR_INPUT *pInputArguments);
        
        void ( STDMETHODCALLTYPE *ResolveMotionVectorHeap )( 
            ID3D12VideoEncodeCommandList * This,
            const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT *pOutputArguments,
            const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT *pInputArguments);
        
        void ( STDMETHODCALLTYPE *WriteBufferImmediate )( 
            ID3D12VideoEncodeCommandList * This,
            UINT Count,
            _In_reads_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER *pParams,
            _In_reads_opt_(Count)  const D3D12_WRITEBUFFERIMMEDIATE_MODE *pModes);
        
        void ( STDMETHODCALLTYPE *SetProtectedResourceSession )( 
            ID3D12VideoEncodeCommandList * This,
            _In_opt_  ID3D12ProtectedResourceSession *pProtectedResourceSession);
        
        END_INTERFACE
    } ID3D12VideoEncodeCommandListVtbl;

    interface ID3D12VideoEncodeCommandList
    {
        CONST_VTBL struct ID3D12VideoEncodeCommandListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D12VideoEncodeCommandList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D12VideoEncodeCommandList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D12VideoEncodeCommandList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D12VideoEncodeCommandList_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D12VideoEncodeCommandList_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D12VideoEncodeCommandList_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D12VideoEncodeCommandList_SetName(This,Name)	\
    ( (This)->lpVtbl -> SetName(This,Name) ) 


#define ID3D12VideoEncodeCommandList_GetDevice(This,riid,ppvDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,riid,ppvDevice) ) 


#define ID3D12VideoEncodeCommandList_GetType(This)	\
    ( (This)->lpVtbl -> GetType(This) ) 


#define ID3D12VideoEncodeCommandList_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ID3D12VideoEncodeCommandList_Reset(This,pAllocator)	\
    ( (This)->lpVtbl -> Reset(This,pAllocator) ) 

#define ID3D12VideoEncodeCommandList_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D12VideoEncodeCommandList_ResourceBarrier(This,NumBarriers,pBarriers)	\
    ( (This)->lpVtbl -> ResourceBarrier(This,NumBarriers,pBarriers) ) 

#define ID3D12VideoEncodeCommandList_DiscardResource(This,pResource,pRegion)	\
    ( (This)->lpVtbl -> DiscardResource(This,pResource,pRegion) ) 

#define ID3D12VideoEncodeCommandList_BeginQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> BeginQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoEncodeCommandList_EndQuery(This,pQueryHeap,Type,Index)	\
    ( (This)->lpVtbl -> EndQuery(This,pQueryHeap,Type,Index) ) 

#define ID3D12VideoEncodeCommandList_ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset)	\
    ( (This)->lpVtbl -> ResolveQueryData(This,pQueryHeap,Type,StartIndex,NumQueries,pDestinationBuffer,AlignedDestinationBufferOffset) ) 

#define ID3D12VideoEncodeCommandList_SetPredication(This,pBuffer,AlignedBufferOffset,Operation)	\
    ( (This)->lpVtbl -> SetPredication(This,pBuffer,AlignedBufferOffset,Operation) ) 

#define ID3D12VideoEncodeCommandList_SetMarker(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> SetMarker(This,Metadata,pData,Size) ) 

#define ID3D12VideoEncodeCommandList_BeginEvent(This,Metadata,pData,Size)	\
    ( (This)->lpVtbl -> BeginEvent(This,Metadata,pData,Size) ) 

#define ID3D12VideoEncodeCommandList_EndEvent(This)	\
    ( (This)->lpVtbl -> EndEvent(This) ) 

#define ID3D12VideoEncodeCommandList_EstimateMotion(This,pMotionEstimator,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> EstimateMotion(This,pMotionEstimator,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoEncodeCommandList_ResolveMotionVectorHeap(This,pOutputArguments,pInputArguments)	\
    ( (This)->lpVtbl -> ResolveMotionVectorHeap(This,pOutputArguments,pInputArguments) ) 

#define ID3D12VideoEncodeCommandList_WriteBufferImmediate(This,Count,pParams,pModes)	\
    ( (This)->lpVtbl -> WriteBufferImmediate(This,Count,pParams,pModes) ) 

#define ID3D12VideoEncodeCommandList_SetProtectedResourceSession(This,pProtectedResourceSession)	\
    ( (This)->lpVtbl -> SetProtectedResourceSession(This,pProtectedResourceSession) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D12VideoEncodeCommandList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d12video_0000_0012 */
/* [local] */ 

DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG2, 0xee27417f, 0x5e28, 0x4e65, 0xbe, 0xea, 0x1d, 0x26, 0xb5, 0x08, 0xad, 0xc9); 
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG1_AND_MPEG2, 0x86695f12, 0x340e, 0x4f04, 0x9f, 0xd3, 0x92, 0x53, 0xdd, 0x32, 0x74, 0x60); 
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264, 0x1b81be68, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_STEREO_PROGRESSIVE, 0xd79be8da, 0x0cf1, 0x4c81, 0xb8, 0x2a, 0x69, 0xa4, 0xe2, 0x36, 0xf4, 0x3d);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_STEREO, 0xf9aaccbb, 0xc2b6, 0x4cfc, 0x87, 0x79, 0x57, 0x07, 0xb1, 0x76, 0x05, 0x52);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_H264_MULTIVIEW, 0x705b9d82, 0x76cf, 0x49d6, 0xb7, 0xe6, 0xac, 0x88, 0x72, 0xdb, 0x01, 0x3c);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VC1, 0x1b81beA3, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VC1_D2010, 0x1b81beA4, 0xa0c7, 0x11d3, 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG4PT2_SIMPLE, 0xefd64d74, 0xc9e8,0x41d7,0xa5,0xe9,0xe9,0xb0,0xe3,0x9f,0xa3,0x19);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_MPEG4PT2_ADVSIMPLE_NOGMC, 0xed418a9f, 0x010d, 0x4eda, 0x9a, 0xe3, 0x9a, 0x65, 0x35, 0x8d, 0x8d, 0x2e);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN, 0x5b11d51b, 0x2f4c, 0x4452, 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10, 0x107af0e0, 0xef1a, 0x4d19, 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP9, 0x463707f8, 0xa1d0, 0x4585, 0x87, 0x6d, 0x83, 0xaa, 0x6d, 0x60, 0xb8, 0x9e);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP9_10BIT_PROFILE2, 0xa4c749ef, 0x6ecf, 0x48aa, 0x84, 0x48, 0x50, 0xa7, 0xa1, 0x16, 0x5f, 0xf7);
DEFINE_GUID(D3D12_VIDEO_DECODE_PROFILE_VP8, 0x90b899ea, 0x3a62, 0x4705, 0x88, 0xb3, 0x8d, 0xf0, 0x4b, 0x27, 0x44, 0xe7);
DEFINE_GUID(IID_ID3D12VideoDecoderHeap,0x0946B7C9,0xEBF6,0x4047,0xBB,0x73,0x86,0x83,0xE2,0x7D,0xBB,0x1F);
DEFINE_GUID(IID_ID3D12VideoDevice,0x1F052807,0x0B46,0x4ACC,0x8A,0x89,0x36,0x4F,0x79,0x37,0x18,0xA4);
DEFINE_GUID(IID_ID3D12VideoDecoder,0xC59B6BDC,0x7720,0x4074,0xA1,0x36,0x17,0xA1,0x56,0x03,0x74,0x70);
DEFINE_GUID(IID_ID3D12VideoProcessor,0x304FDB32,0xBEDE,0x410A,0x85,0x45,0x94,0x3A,0xC6,0xA4,0x61,0x38);
DEFINE_GUID(IID_ID3D12VideoDecodeCommandList,0x3B60536E,0xAD29,0x4E64,0xA2,0x69,0xF8,0x53,0x83,0x7E,0x5E,0x53);
DEFINE_GUID(IID_ID3D12VideoProcessCommandList,0xAEB2543A,0x167F,0x4682,0xAC,0xC8,0xD1,0x59,0xED,0x4A,0x62,0x09);
DEFINE_GUID(IID_ID3D12VideoDecodeCommandList1,0xD52F011B,0xB56E,0x453C,0xA0,0x5A,0xA7,0xF3,0x11,0xC8,0xF4,0x72);
DEFINE_GUID(IID_ID3D12VideoProcessCommandList1,0x542C5C4D,0x7596,0x434F,0x8C,0x93,0x4E,0xFA,0x67,0x66,0xF2,0x67);
DEFINE_GUID(IID_ID3D12VideoMotionEstimator,0x33FDAE0E,0x098B,0x428F,0x87,0xBB,0x34,0xB6,0x95,0xDE,0x08,0xF8);
DEFINE_GUID(IID_ID3D12VideoMotionVectorHeap,0x5BE17987,0x743A,0x4061,0x83,0x4B,0x23,0xD2,0x2D,0xAE,0xA5,0x05);
DEFINE_GUID(IID_ID3D12VideoDevice1,0x981611AD,0xA144,0x4C83,0x98,0x90,0xF3,0x0E,0x26,0xD6,0x58,0xAB);
DEFINE_GUID(IID_ID3D12VideoEncodeCommandList,0x8455293A,0x0CBD,0x4831,0x9B,0x39,0xFB,0xDB,0xAB,0x72,0x47,0x23);


extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d12video_0000_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


