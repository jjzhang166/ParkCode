/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 09 16:14:59 2011
 */
/* Compiler settings for D:\WinParkUI\WinHtpp\VC6Crypt\CryptoAPI.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CryptoAPI_h__
#define __CryptoAPI_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICrypto_FWD_DEFINED__
#define __ICrypto_FWD_DEFINED__
typedef interface ICrypto ICrypto;
#endif 	/* __ICrypto_FWD_DEFINED__ */


#ifndef __Crypto_FWD_DEFINED__
#define __Crypto_FWD_DEFINED__

#ifdef __cplusplus
typedef class Crypto Crypto;
#else
typedef struct Crypto Crypto;
#endif /* __cplusplus */

#endif 	/* __Crypto_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICrypto_INTERFACE_DEFINED__
#define __ICrypto_INTERFACE_DEFINED__

/* interface ICrypto */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICrypto;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6F7D3059-E96A-48DF-B232-1AE444384097")
    ICrypto : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EncryptDoc( 
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DecryptDoc( 
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64EncodeString( 
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64DecodeString( 
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EncryptString( 
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DecryptString( 
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DigitalSignature( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyDigitalSignature( 
            /* [in] */ BSTR bstrDigitalSig,
            /* [retval][out] */ BOOL __RPC_FAR *pbMatches) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64EncodeFile( 
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64DecodeFile( 
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64EncodeFileToString( 
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64DecodeStringToFile( 
            /* [in] */ BSTR bstrSrc,
            /* [in] */ BSTR bstrDestination) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContainerName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContainerName( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICryptoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICrypto __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICrypto __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICrypto __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EncryptDoc )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DecryptDoc )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64EncodeString )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64DecodeString )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EncryptString )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DecryptString )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DigitalSignature )( 
            ICrypto __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VerifyDigitalSignature )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrDigitalSig,
            /* [retval][out] */ BOOL __RPC_FAR *pbMatches);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64EncodeFile )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64DecodeFile )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [optional][in] */ VARIANT varDestination);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64EncodeFileToString )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Base64DecodeStringToFile )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR bstrSrc,
            /* [in] */ BSTR bstrDestination);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerName )( 
            ICrypto __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerName )( 
            ICrypto __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICryptoVtbl;

    interface ICrypto
    {
        CONST_VTBL struct ICryptoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICrypto_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICrypto_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICrypto_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICrypto_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICrypto_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICrypto_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICrypto_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICrypto_EncryptDoc(This,bstrSrc,varDestination)	\
    (This)->lpVtbl -> EncryptDoc(This,bstrSrc,varDestination)

#define ICrypto_DecryptDoc(This,bstrSrc,varDestination)	\
    (This)->lpVtbl -> DecryptDoc(This,bstrSrc,varDestination)

#define ICrypto_Base64EncodeString(This,bstrSrc,pbstrResult)	\
    (This)->lpVtbl -> Base64EncodeString(This,bstrSrc,pbstrResult)

#define ICrypto_Base64DecodeString(This,bstrSrc,pbstrResult)	\
    (This)->lpVtbl -> Base64DecodeString(This,bstrSrc,pbstrResult)

#define ICrypto_EncryptString(This,bstrSrc,pbstrResult)	\
    (This)->lpVtbl -> EncryptString(This,bstrSrc,pbstrResult)

#define ICrypto_DecryptString(This,bstrSrc,pbstrResult)	\
    (This)->lpVtbl -> DecryptString(This,bstrSrc,pbstrResult)

#define ICrypto_get_DigitalSignature(This,pVal)	\
    (This)->lpVtbl -> get_DigitalSignature(This,pVal)

#define ICrypto_VerifyDigitalSignature(This,bstrDigitalSig,pbMatches)	\
    (This)->lpVtbl -> VerifyDigitalSignature(This,bstrDigitalSig,pbMatches)

#define ICrypto_Base64EncodeFile(This,bstrSrc,varDestination)	\
    (This)->lpVtbl -> Base64EncodeFile(This,bstrSrc,varDestination)

#define ICrypto_Base64DecodeFile(This,bstrSrc,varDestination)	\
    (This)->lpVtbl -> Base64DecodeFile(This,bstrSrc,varDestination)

#define ICrypto_Base64EncodeFileToString(This,bstrSrc,pbstrResult)	\
    (This)->lpVtbl -> Base64EncodeFileToString(This,bstrSrc,pbstrResult)

#define ICrypto_Base64DecodeStringToFile(This,bstrSrc,bstrDestination)	\
    (This)->lpVtbl -> Base64DecodeStringToFile(This,bstrSrc,bstrDestination)

#define ICrypto_get_ContainerName(This,pVal)	\
    (This)->lpVtbl -> get_ContainerName(This,pVal)

#define ICrypto_put_ContainerName(This,newVal)	\
    (This)->lpVtbl -> put_ContainerName(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_EncryptDoc_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [optional][in] */ VARIANT varDestination);


void __RPC_STUB ICrypto_EncryptDoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_DecryptDoc_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [optional][in] */ VARIANT varDestination);


void __RPC_STUB ICrypto_DecryptDoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64EncodeString_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);


void __RPC_STUB ICrypto_Base64EncodeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64DecodeString_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);


void __RPC_STUB ICrypto_Base64DecodeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_EncryptString_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);


void __RPC_STUB ICrypto_EncryptString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_DecryptString_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);


void __RPC_STUB ICrypto_DecryptString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICrypto_get_DigitalSignature_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICrypto_get_DigitalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_VerifyDigitalSignature_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrDigitalSig,
    /* [retval][out] */ BOOL __RPC_FAR *pbMatches);


void __RPC_STUB ICrypto_VerifyDigitalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64EncodeFile_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [optional][in] */ VARIANT varDestination);


void __RPC_STUB ICrypto_Base64EncodeFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64DecodeFile_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [optional][in] */ VARIANT varDestination);


void __RPC_STUB ICrypto_Base64DecodeFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64EncodeFileToString_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrResult);


void __RPC_STUB ICrypto_Base64EncodeFileToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICrypto_Base64DecodeStringToFile_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR bstrSrc,
    /* [in] */ BSTR bstrDestination);


void __RPC_STUB ICrypto_Base64DecodeStringToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICrypto_get_ContainerName_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICrypto_get_ContainerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICrypto_put_ContainerName_Proxy( 
    ICrypto __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICrypto_put_ContainerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICrypto_INTERFACE_DEFINED__ */



#ifndef __CRYPTOAPILib_LIBRARY_DEFINED__
#define __CRYPTOAPILib_LIBRARY_DEFINED__

/* library CRYPTOAPILib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CRYPTOAPILib;

EXTERN_C const CLSID CLSID_Crypto;

#ifdef __cplusplus

class DECLSPEC_UUID("391B0AA4-1E17-485F-B635-0FE26219E87E")
Crypto;
#endif
#endif /* __CRYPTOAPILib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
