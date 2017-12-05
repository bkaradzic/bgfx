

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
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

#ifndef __dxgidebug_h__
#define __dxgidebug_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDXGIInfoQueue_FWD_DEFINED__
#define __IDXGIInfoQueue_FWD_DEFINED__
typedef interface IDXGIInfoQueue IDXGIInfoQueue;

#endif 	/* __IDXGIInfoQueue_FWD_DEFINED__ */


#ifndef __IDXGIDebug_FWD_DEFINED__
#define __IDXGIDebug_FWD_DEFINED__
typedef interface IDXGIDebug IDXGIDebug;

#endif 	/* __IDXGIDebug_FWD_DEFINED__ */


#ifndef __IDXGIDebug1_FWD_DEFINED__
#define __IDXGIDebug1_FWD_DEFINED__
typedef interface IDXGIDebug1 IDXGIDebug1;

#endif 	/* __IDXGIDebug1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_dxgidebug_0000_0000 */
/* [local] */ 

#define	DXGI_DEBUG_BINARY_VERSION	( 1 )

typedef 
enum DXGI_DEBUG_RLO_FLAGS
    {
        DXGI_DEBUG_RLO_SUMMARY	= 0x1,
        DXGI_DEBUG_RLO_DETAIL	= 0x2,
        DXGI_DEBUG_RLO_IGNORE_INTERNAL	= 0x4,
        DXGI_DEBUG_RLO_ALL	= 0x7
    } 	DXGI_DEBUG_RLO_FLAGS;

typedef GUID DXGI_DEBUG_ID;

DEFINE_GUID(DXGI_DEBUG_ALL, 0xe48ae283, 0xda80, 0x490b, 0x87, 0xe6, 0x43, 0xe9, 0xa9, 0xcf, 0xda, 0x8);
DEFINE_GUID(DXGI_DEBUG_DX, 0x35cdd7fc, 0x13b2, 0x421d, 0xa5, 0xd7, 0x7e, 0x44, 0x51, 0x28, 0x7d, 0x64);
DEFINE_GUID(DXGI_DEBUG_DXGI, 0x25cddaa4, 0xb1c6, 0x47e1, 0xac, 0x3e, 0x98, 0x87, 0x5b, 0x5a, 0x2e, 0x2a);
DEFINE_GUID(DXGI_DEBUG_APP, 0x6cd6e01, 0x4219, 0x4ebd, 0x87, 0x9, 0x27, 0xed, 0x23, 0x36, 0xc, 0x62);
typedef 
enum DXGI_INFO_QUEUE_MESSAGE_CATEGORY
    {
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN	= 0,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_CATEGORY_SHADER	= ( DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION + 1 ) 
    } 	DXGI_INFO_QUEUE_MESSAGE_CATEGORY;

typedef 
enum DXGI_INFO_QUEUE_MESSAGE_SEVERITY
    {
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION	= 0,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR	= ( DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING	= ( DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO	= ( DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING + 1 ) ,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE	= ( DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO + 1 ) 
    } 	DXGI_INFO_QUEUE_MESSAGE_SEVERITY;

typedef int DXGI_INFO_QUEUE_MESSAGE_ID;

#define DXGI_INFO_QUEUE_MESSAGE_ID_STRING_FROM_APPLICATION 0
typedef struct DXGI_INFO_QUEUE_MESSAGE
    {
    DXGI_DEBUG_ID Producer;
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category;
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity;
    DXGI_INFO_QUEUE_MESSAGE_ID ID;
    /* [annotation] */ 
    _Field_size_(DescriptionByteLength)  const char *pDescription;
    SIZE_T DescriptionByteLength;
    } 	DXGI_INFO_QUEUE_MESSAGE;

typedef struct DXGI_INFO_QUEUE_FILTER_DESC
    {
    UINT NumCategories;
    /* [annotation] */ 
    _Field_size_(NumCategories)  DXGI_INFO_QUEUE_MESSAGE_CATEGORY *pCategoryList;
    UINT NumSeverities;
    /* [annotation] */ 
    _Field_size_(NumSeverities)  DXGI_INFO_QUEUE_MESSAGE_SEVERITY *pSeverityList;
    UINT NumIDs;
    /* [annotation] */ 
    _Field_size_(NumIDs)  DXGI_INFO_QUEUE_MESSAGE_ID *pIDList;
    } 	DXGI_INFO_QUEUE_FILTER_DESC;

typedef struct DXGI_INFO_QUEUE_FILTER
    {
    DXGI_INFO_QUEUE_FILTER_DESC AllowList;
    DXGI_INFO_QUEUE_FILTER_DESC DenyList;
    } 	DXGI_INFO_QUEUE_FILTER;

#define DXGI_INFO_QUEUE_DEFAULT_MESSAGE_COUNT_LIMIT 1024
HRESULT WINAPI DXGIGetDebugInterface(REFIID riid, void **ppDebug);


extern RPC_IF_HANDLE __MIDL_itf_dxgidebug_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgidebug_0000_0000_v0_0_s_ifspec;

#ifndef __IDXGIInfoQueue_INTERFACE_DEFINED__
#define __IDXGIInfoQueue_INTERFACE_DEFINED__

/* interface IDXGIInfoQueue */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IDXGIInfoQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D67441C7-672A-476f-9E82-CD55B44949CE")
    IDXGIInfoQueue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMessageCountLimit( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  UINT64 MessageCountLimit) = 0;
        
        virtual void STDMETHODCALLTYPE ClearStoredMessages( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMessage( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  UINT64 MessageIndex,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pMessageByteLength)  DXGI_INFO_QUEUE_MESSAGE *pMessage,
            /* [annotation] */ 
            _Inout_  SIZE_T *pMessageByteLength) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessagesAllowedByRetrievalFilters( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumStoredMessages( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDiscardedByMessageCountLimit( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetMessageCountLimit( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesAllowedByStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT64 STDMETHODCALLTYPE GetNumMessagesDeniedByStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddStorageFilterEntries( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pFilterByteLength)  DXGI_INFO_QUEUE_FILTER *pFilter,
            /* [annotation] */ 
            _Inout_  SIZE_T *pFilterByteLength) = 0;
        
        virtual void STDMETHODCALLTYPE ClearStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushEmptyStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushDenyAllStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushCopyOfStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual void STDMETHODCALLTYPE PopStorageFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetStorageFilterStackSize( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddRetrievalFilterEntries( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pFilterByteLength)  DXGI_INFO_QUEUE_FILTER *pFilter,
            /* [annotation] */ 
            _Inout_  SIZE_T *pFilterByteLength) = 0;
        
        virtual void STDMETHODCALLTYPE ClearRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushEmptyRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushDenyAllRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushCopyOfRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PushRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter) = 0;
        
        virtual void STDMETHODCALLTYPE PopRetrievalFilter( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual UINT STDMETHODCALLTYPE GetRetrievalFilterStackSize( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMessage( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID,
            /* [annotation] */ 
            _In_  LPCSTR pDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddApplicationMessage( 
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  LPCSTR pDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnCategory( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category,
            /* [annotation] */ 
            _In_  BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnSeverity( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBreakOnID( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID,
            /* [annotation] */ 
            _In_  BOOL bEnable) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnCategory( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnSeverity( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetBreakOnID( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID) = 0;
        
        virtual void STDMETHODCALLTYPE SetMuteDebugOutput( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  BOOL bMute) = 0;
        
        virtual BOOL STDMETHODCALLTYPE GetMuteDebugOutput( 
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIInfoQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIInfoQueue * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIInfoQueue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIInfoQueue * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMessageCountLimit )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  UINT64 MessageCountLimit);
        
        void ( STDMETHODCALLTYPE *ClearStoredMessages )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *GetMessage )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  UINT64 MessageIndex,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pMessageByteLength)  DXGI_INFO_QUEUE_MESSAGE *pMessage,
            /* [annotation] */ 
            _Inout_  SIZE_T *pMessageByteLength);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumStoredMessagesAllowedByRetrievalFilters )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumStoredMessages )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesDiscardedByMessageCountLimit )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT64 ( STDMETHODCALLTYPE *GetMessageCountLimit )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesAllowedByStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT64 ( STDMETHODCALLTYPE *GetNumMessagesDeniedByStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *AddStorageFilterEntries )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pFilterByteLength)  DXGI_INFO_QUEUE_FILTER *pFilter,
            /* [annotation] */ 
            _Inout_  SIZE_T *pFilterByteLength);
        
        void ( STDMETHODCALLTYPE *ClearStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushEmptyStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushDenyAllStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushCopyOfStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter);
        
        void ( STDMETHODCALLTYPE *PopStorageFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT ( STDMETHODCALLTYPE *GetStorageFilterStackSize )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *AddRetrievalFilterEntries )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pFilterByteLength)  DXGI_INFO_QUEUE_FILTER *pFilter,
            /* [annotation] */ 
            _Inout_  SIZE_T *pFilterByteLength);
        
        void ( STDMETHODCALLTYPE *ClearRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushEmptyRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushDenyAllRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushCopyOfRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *PushRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_FILTER *pFilter);
        
        void ( STDMETHODCALLTYPE *PopRetrievalFilter )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        UINT ( STDMETHODCALLTYPE *GetRetrievalFilterStackSize )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        HRESULT ( STDMETHODCALLTYPE *AddMessage )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID,
            /* [annotation] */ 
            _In_  LPCSTR pDescription);
        
        HRESULT ( STDMETHODCALLTYPE *AddApplicationMessage )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  LPCSTR pDescription);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnCategory )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category,
            /* [annotation] */ 
            _In_  BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnSeverity )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity,
            /* [annotation] */ 
            _In_  BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE *SetBreakOnID )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID,
            /* [annotation] */ 
            _In_  BOOL bEnable);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnCategory )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_CATEGORY Category);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnSeverity )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_SEVERITY Severity);
        
        BOOL ( STDMETHODCALLTYPE *GetBreakOnID )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  DXGI_INFO_QUEUE_MESSAGE_ID ID);
        
        void ( STDMETHODCALLTYPE *SetMuteDebugOutput )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer,
            /* [annotation] */ 
            _In_  BOOL bMute);
        
        BOOL ( STDMETHODCALLTYPE *GetMuteDebugOutput )( 
            IDXGIInfoQueue * This,
            /* [annotation] */ 
            _In_  DXGI_DEBUG_ID Producer);
        
        END_INTERFACE
    } IDXGIInfoQueueVtbl;

    interface IDXGIInfoQueue
    {
        CONST_VTBL struct IDXGIInfoQueueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIInfoQueue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIInfoQueue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIInfoQueue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIInfoQueue_SetMessageCountLimit(This,Producer,MessageCountLimit)	\
    ( (This)->lpVtbl -> SetMessageCountLimit(This,Producer,MessageCountLimit) ) 

#define IDXGIInfoQueue_ClearStoredMessages(This,Producer)	\
    ( (This)->lpVtbl -> ClearStoredMessages(This,Producer) ) 

#define IDXGIInfoQueue_GetMessage(This,Producer,MessageIndex,pMessage,pMessageByteLength)	\
    ( (This)->lpVtbl -> GetMessage(This,Producer,MessageIndex,pMessage,pMessageByteLength) ) 

#define IDXGIInfoQueue_GetNumStoredMessagesAllowedByRetrievalFilters(This,Producer)	\
    ( (This)->lpVtbl -> GetNumStoredMessagesAllowedByRetrievalFilters(This,Producer) ) 

#define IDXGIInfoQueue_GetNumStoredMessages(This,Producer)	\
    ( (This)->lpVtbl -> GetNumStoredMessages(This,Producer) ) 

#define IDXGIInfoQueue_GetNumMessagesDiscardedByMessageCountLimit(This,Producer)	\
    ( (This)->lpVtbl -> GetNumMessagesDiscardedByMessageCountLimit(This,Producer) ) 

#define IDXGIInfoQueue_GetMessageCountLimit(This,Producer)	\
    ( (This)->lpVtbl -> GetMessageCountLimit(This,Producer) ) 

#define IDXGIInfoQueue_GetNumMessagesAllowedByStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> GetNumMessagesAllowedByStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_GetNumMessagesDeniedByStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> GetNumMessagesDeniedByStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_AddStorageFilterEntries(This,Producer,pFilter)	\
    ( (This)->lpVtbl -> AddStorageFilterEntries(This,Producer,pFilter) ) 

#define IDXGIInfoQueue_GetStorageFilter(This,Producer,pFilter,pFilterByteLength)	\
    ( (This)->lpVtbl -> GetStorageFilter(This,Producer,pFilter,pFilterByteLength) ) 

#define IDXGIInfoQueue_ClearStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> ClearStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushEmptyStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushEmptyStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushDenyAllStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushDenyAllStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushCopyOfStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushCopyOfStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushStorageFilter(This,Producer,pFilter)	\
    ( (This)->lpVtbl -> PushStorageFilter(This,Producer,pFilter) ) 

#define IDXGIInfoQueue_PopStorageFilter(This,Producer)	\
    ( (This)->lpVtbl -> PopStorageFilter(This,Producer) ) 

#define IDXGIInfoQueue_GetStorageFilterStackSize(This,Producer)	\
    ( (This)->lpVtbl -> GetStorageFilterStackSize(This,Producer) ) 

#define IDXGIInfoQueue_AddRetrievalFilterEntries(This,Producer,pFilter)	\
    ( (This)->lpVtbl -> AddRetrievalFilterEntries(This,Producer,pFilter) ) 

#define IDXGIInfoQueue_GetRetrievalFilter(This,Producer,pFilter,pFilterByteLength)	\
    ( (This)->lpVtbl -> GetRetrievalFilter(This,Producer,pFilter,pFilterByteLength) ) 

#define IDXGIInfoQueue_ClearRetrievalFilter(This,Producer)	\
    ( (This)->lpVtbl -> ClearRetrievalFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushEmptyRetrievalFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushEmptyRetrievalFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushDenyAllRetrievalFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushDenyAllRetrievalFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushCopyOfRetrievalFilter(This,Producer)	\
    ( (This)->lpVtbl -> PushCopyOfRetrievalFilter(This,Producer) ) 

#define IDXGIInfoQueue_PushRetrievalFilter(This,Producer,pFilter)	\
    ( (This)->lpVtbl -> PushRetrievalFilter(This,Producer,pFilter) ) 

#define IDXGIInfoQueue_PopRetrievalFilter(This,Producer)	\
    ( (This)->lpVtbl -> PopRetrievalFilter(This,Producer) ) 

#define IDXGIInfoQueue_GetRetrievalFilterStackSize(This,Producer)	\
    ( (This)->lpVtbl -> GetRetrievalFilterStackSize(This,Producer) ) 

#define IDXGIInfoQueue_AddMessage(This,Producer,Category,Severity,ID,pDescription)	\
    ( (This)->lpVtbl -> AddMessage(This,Producer,Category,Severity,ID,pDescription) ) 

#define IDXGIInfoQueue_AddApplicationMessage(This,Severity,pDescription)	\
    ( (This)->lpVtbl -> AddApplicationMessage(This,Severity,pDescription) ) 

#define IDXGIInfoQueue_SetBreakOnCategory(This,Producer,Category,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnCategory(This,Producer,Category,bEnable) ) 

#define IDXGIInfoQueue_SetBreakOnSeverity(This,Producer,Severity,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnSeverity(This,Producer,Severity,bEnable) ) 

#define IDXGIInfoQueue_SetBreakOnID(This,Producer,ID,bEnable)	\
    ( (This)->lpVtbl -> SetBreakOnID(This,Producer,ID,bEnable) ) 

#define IDXGIInfoQueue_GetBreakOnCategory(This,Producer,Category)	\
    ( (This)->lpVtbl -> GetBreakOnCategory(This,Producer,Category) ) 

#define IDXGIInfoQueue_GetBreakOnSeverity(This,Producer,Severity)	\
    ( (This)->lpVtbl -> GetBreakOnSeverity(This,Producer,Severity) ) 

#define IDXGIInfoQueue_GetBreakOnID(This,Producer,ID)	\
    ( (This)->lpVtbl -> GetBreakOnID(This,Producer,ID) ) 

#define IDXGIInfoQueue_SetMuteDebugOutput(This,Producer,bMute)	\
    ( (This)->lpVtbl -> SetMuteDebugOutput(This,Producer,bMute) ) 

#define IDXGIInfoQueue_GetMuteDebugOutput(This,Producer)	\
    ( (This)->lpVtbl -> GetMuteDebugOutput(This,Producer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIInfoQueue_INTERFACE_DEFINED__ */


#ifndef __IDXGIDebug_INTERFACE_DEFINED__
#define __IDXGIDebug_INTERFACE_DEFINED__

/* interface IDXGIDebug */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IDXGIDebug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("119E7452-DE9E-40fe-8806-88F90C12B441")
    IDXGIDebug : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReportLiveObjects( 
            GUID apiid,
            DXGI_DEBUG_RLO_FLAGS flags) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDebugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDebug * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDebug * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDebug * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLiveObjects )( 
            IDXGIDebug * This,
            GUID apiid,
            DXGI_DEBUG_RLO_FLAGS flags);
        
        END_INTERFACE
    } IDXGIDebugVtbl;

    interface IDXGIDebug
    {
        CONST_VTBL struct IDXGIDebugVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDebug_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDebug_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDebug_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDebug_ReportLiveObjects(This,apiid,flags)	\
    ( (This)->lpVtbl -> ReportLiveObjects(This,apiid,flags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDebug_INTERFACE_DEFINED__ */


#ifndef __IDXGIDebug1_INTERFACE_DEFINED__
#define __IDXGIDebug1_INTERFACE_DEFINED__

/* interface IDXGIDebug1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IDXGIDebug1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c5a05f0c-16f2-4adf-9f4d-a8c4d58ac550")
    IDXGIDebug1 : public IDXGIDebug
    {
    public:
        virtual void STDMETHODCALLTYPE EnableLeakTrackingForThread( void) = 0;
        
        virtual void STDMETHODCALLTYPE DisableLeakTrackingForThread( void) = 0;
        
        virtual BOOL STDMETHODCALLTYPE IsLeakTrackingEnabledForThread( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDXGIDebug1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDXGIDebug1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDXGIDebug1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDXGIDebug1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLiveObjects )( 
            IDXGIDebug1 * This,
            GUID apiid,
            DXGI_DEBUG_RLO_FLAGS flags);
        
        void ( STDMETHODCALLTYPE *EnableLeakTrackingForThread )( 
            IDXGIDebug1 * This);
        
        void ( STDMETHODCALLTYPE *DisableLeakTrackingForThread )( 
            IDXGIDebug1 * This);
        
        BOOL ( STDMETHODCALLTYPE *IsLeakTrackingEnabledForThread )( 
            IDXGIDebug1 * This);
        
        END_INTERFACE
    } IDXGIDebug1Vtbl;

    interface IDXGIDebug1
    {
        CONST_VTBL struct IDXGIDebug1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDXGIDebug1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDXGIDebug1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDXGIDebug1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDXGIDebug1_ReportLiveObjects(This,apiid,flags)	\
    ( (This)->lpVtbl -> ReportLiveObjects(This,apiid,flags) ) 


#define IDXGIDebug1_EnableLeakTrackingForThread(This)	\
    ( (This)->lpVtbl -> EnableLeakTrackingForThread(This) ) 

#define IDXGIDebug1_DisableLeakTrackingForThread(This)	\
    ( (This)->lpVtbl -> DisableLeakTrackingForThread(This) ) 

#define IDXGIDebug1_IsLeakTrackingEnabledForThread(This)	\
    ( (This)->lpVtbl -> IsLeakTrackingEnabledForThread(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDXGIDebug1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dxgidebug_0000_0003 */
/* [local] */ 

DEFINE_GUID(IID_IDXGIInfoQueue,0xD67441C7,0x672A,0x476f,0x9E,0x82,0xCD,0x55,0xB4,0x49,0x49,0xCE);
DEFINE_GUID(IID_IDXGIDebug,0x119E7452,0xDE9E,0x40fe,0x88,0x06,0x88,0xF9,0x0C,0x12,0xB4,0x41);
DEFINE_GUID(IID_IDXGIDebug1,0xc5a05f0c,0x16f2,0x4adf,0x9f,0x4d,0xa8,0xc4,0xd5,0x8a,0xc5,0x50);


extern RPC_IF_HANDLE __MIDL_itf_dxgidebug_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgidebug_0000_0003_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


