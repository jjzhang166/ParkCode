// Base64Helper.h: interface for the CBase64Helper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__D2837630_A37D_4A92_9B18_F685697E795F__INCLUDED_)
#define AFX_BASE64_H__D2837630_A37D_4A92_9B18_F685697E795F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBase64Helper  
{
public:
//new for 205 >>>
	CBase64Helper();
	~CBase64Helper();
	CComBSTR Base64EncodeString(BSTR DataIn);
	CComBSTR Base64DecodeString(BSTR DataIn);
	HRESULT Base64EncodeByteArray(SAFEARRAY ** ppUserDataArray);
	HRESULT Base64DecodeByteArray(SAFEARRAY ** ppUserDataArray);
	LONG Base64Decoder(PBYTE DataIn, LONG DataLength, HGLOBAL * hDataOut);
	LONG Base64Encoder(PBYTE DataIn, LONG DataLength, HGLOBAL * hDataOut);
//new for 205 >>>

};

#endif // !defined(AFX_BASE64_H__D2837630_A37D_4A92_9B18_F685697E795F__INCLUDED_)
