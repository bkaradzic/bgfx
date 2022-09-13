/*-------------------------------------------------------------------------------------
 *
 * Copyright (c) Microsoft Corporation
 * Licensed under the MIT license
 *
 *-------------------------------------------------------------------------------------*/

/* this ALWAYS GENERATED file contains the definitions for the interfaces */

/* File created by MIDL compiler version 8.01.0627 */

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

#ifndef __unknwnbase_h__
#define __unknwnbase_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */

#ifndef __IUnknown_FWD_DEFINED__
#define __IUnknown_FWD_DEFINED__
typedef interface IUnknown IUnknown;

#endif 	/* __IUnknown_FWD_DEFINED__ */

#ifndef __IUnknown_INTERFACE_DEFINED__
#define __IUnknown_INTERFACE_DEFINED__

/* interface IUnknown */
/* [unique][uuid][object][local] */

typedef /* [unique] */ IUnknown *LPUNKNOWN;

EXTERN_C const IID IID_IUnknown;

#if defined(__cplusplus) && !defined(CINTERFACE)
extern "C++"
{
    MIDL_INTERFACE("00000000-0000-0000-c000-000000000046")
    IUnknown
    {
        BEGIN_INTERFACE

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID riid,
            void **ppvObject) = 0;

        virtual ULONG STDMETHODCALLTYPE AddRef() = 0;

        virtual ULONG STDMETHODCALLTYPE Release() = 0;

        template <class Q>
        HRESULT
            STDMETHODCALLTYPE
            QueryInterface(_COM_Outptr_ Q * *pp)
        {
            return QueryInterface(__uuidof(Q), (void **)pp);
        }
        END_INTERFACE
    };
}
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IUnknown, 0x00000000, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)
#endif
#else
typedef struct IUnknownVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IUnknown *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IUnknown *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IUnknown *This);

    END_INTERFACE
} IUnknownVtbl;

interface IUnknown {
    CONST_VTBL IUnknownVtbl* lpVtbl;
};

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IUnknown_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IUnknown_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IUnknown_Release(This) (This)->lpVtbl->Release(This)
#endif

#endif

#endif /* __IUnknown_INTERFACE_DEFINED__ */

DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46);

#endif /* __unknwnbase_h__ */
