// ------------------------------------------------------------------------------------
// Copyright 2000 - Microsoft Corporation.
// All rights reserved. 
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
// EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// ------------------------------------------------------------------------------------
//
// Base64Helper.cpp: implementation of the CBase64Helper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Base64Helper.h"

static char cBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

struct ARRAYINFO {
	UINT nDim;
	UINT nElemSize;
	DWORD dwArrayLength;
};
struct ARRAYDIMS {
	long lLBound;
	long lUBound;
};
struct ARRAYDATA {
	ARRAYINFO Info;
	ARRAYDIMS * pDimData;
};


/*#define LOOKUP64CHAR(x) \
{ \
	int i; \
	for (i = 0; i < 64; i++) \
	{ \
		if (cBase64Alphabet[i] == x) \
		{ \
			x = i; \
			break; \
		} \
	} \
}*/

	/////////////////////////////////////////////////////////////////////////
	//	cslater 02/02/01 
	//	Replaced Microsoft's linear search with an Order(1) lookup to 
	//	enhance decoding performance
	/////////////////////////////////////////////////////////////////////////
#define LOOKUP64CHAR(nChar) \
	{\
	switch( nChar )\
		{\
		case 'A': nChar = 0; break;  case 'B': nChar = 1; break;  case 'C': nChar = 2; break;  case 'D': nChar = 3; break;\
		case 'E': nChar = 4; break;  case 'F': nChar = 5; break;  case 'G': nChar = 6; break;  case 'H': nChar = 7; break;\
		case 'I': nChar = 8; break;  case 'J': nChar = 9; break;  case 'K': nChar = 10; break; case 'L': nChar = 11; break;\
		case 'M': nChar = 12; break; case 'N': nChar = 13; break; case 'O': nChar = 14; break; case 'P': nChar = 15; break;\
		case 'Q': nChar = 16; break; case 'R': nChar = 17; break; case 'S': nChar = 18; break; case 'T': nChar = 19; break;\
		case 'U': nChar = 20; break; case 'V': nChar = 21; break; case 'W': nChar = 22; break; case 'X': nChar = 23; break;\
		case 'Y': nChar = 24; break; case 'Z': nChar = 25; break; case 'a': nChar = 26; break; case 'b': nChar = 27; break;\
		case 'c': nChar = 28; break; case 'd': nChar = 29; break; case 'e': nChar = 30; break; case 'f': nChar = 31; break;\
		case 'g': nChar = 32; break; case 'h': nChar = 33; break; case 'i': nChar = 34; break; case 'j': nChar = 35; break;\
		case 'k': nChar = 36; break; case 'l': nChar = 37; break; case 'm': nChar = 38; break; case 'n': nChar = 39; break;\
		case 'o': nChar = 40; break; case 'p': nChar = 41; break; case 'q': nChar = 42; break; case 'r': nChar = 43; break;\
		case 's': nChar = 44; break; case 't': nChar = 45; break; case 'u': nChar = 46; break; case 'v': nChar = 47; break;\
		case 'w': nChar = 48; break; case 'x': nChar = 49; break; case 'y': nChar = 50; break; case 'z': nChar = 51; break;\
		case '0': nChar = 52; break; case '1': nChar = 53; break; case '2': nChar = 54; break; case '3': nChar = 55; break;\
		case '4': nChar = 56; break; case '5': nChar = 57; break; case '6': nChar = 58; break; case '7': nChar = 59; break;\
		case '8': nChar = 60; break; case '9': nChar = 61; break; case '+': nChar = 62; break; case '/': nChar = 63; break;\
		case '=': nChar = 64; break;\
		}\
	}

#define BASE64_t2	0x30 //00110000
#define BASE64_m2	0x0c //00001100
#define BASE64_b2	0x03 //00000011
#define BASE64_t4	0x3c //00111100
#define BASE64_b4	0x0f //00001111
#define BASE64_h2	0xc0 //11000000
#define BASE64_b6	0x3f //00111111

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase64Helper::CBase64Helper()
{
}

CBase64Helper::~CBase64Helper()
{
}

/*
base64 encoding, in short
QP (base64-encoded) contains uppercase, lowercase, numbers, '+', '/' and '='. 
Take the encoded stuff in groups of 4 characters and turn each character into a code 0 to 63 thus: 

A means of labelling the content of mail messages. 
A-Z map to 0 to 25 
a-z map to 26 to 51 
0-9 map to 52 to 61 
+ maps to 62 
/ maps to 63 
Express the four numbers thus found (all 0 to 63) in binary: 

00aaaaaa 00bbbbbb 00cccccc 00dddddd 

This then maps to _three_ real bytes formed thus: 

aaaaaabb bbbbcccc ccdddddd 

Equals signs (one or two) are used at the end of the encoded block to indicate that the text
was not an integer multiple of three bytes long. 

*/

//new for 205>>>
CComBSTR CBase64Helper::Base64EncodeString(BSTR DataIn)
{
	HRESULT hRes;
	SAFEARRAY * psa;
	BSTR Result;

	if (DataIn)
	{
		hRes = VectorFromBstr(DataIn, &psa);
		hRes = Base64EncodeByteArray(&psa);
		hRes = BstrFromVector(psa, &Result);
		::SafeArrayDestroy(psa);
	}

	return Result;
}

CComBSTR CBase64Helper::Base64DecodeString(BSTR DataIn)
{
	HRESULT hRes;
	SAFEARRAY * psa;
	BSTR Result;

	if (DataIn)
	{
		hRes = VectorFromBstr(DataIn, &psa);
		hRes = Base64DecodeByteArray(&psa);
		hRes = BstrFromVector(psa, &Result);
		::SafeArrayDestroy(psa);
	}

	return Result;
}


HRESULT CBase64Helper::Base64EncodeByteArray(SAFEARRAY ** ppUserDataArray)
{
	PBYTE	pInputBytes;
	PBYTE	pOutputBytes;
	SAFEARRAY * psa;
	LONG lOutputBufferLength;
	HGLOBAL hBuffer;
	PBYTE pBufferPtr;
	LONG lBufferLength;

	//Simply get hold of the Bytes
	pInputBytes = (PBYTE)(*ppUserDataArray)->pvData;

	// get length
	lBufferLength = (*ppUserDataArray)->rgsabound[0].cElements;
	
	//Encode these Bytes and copy into buffer
	lOutputBufferLength = Base64Encoder((PBYTE)pInputBytes, lBufferLength, &hBuffer);
	pBufferPtr = (PBYTE)::GlobalLock(hBuffer);
	psa = ::SafeArrayCreateVector(VT_UI1, 0, lOutputBufferLength);
	pOutputBytes = (PBYTE)psa->pvData;
	::CopyMemory(pOutputBytes, pBufferPtr, lOutputBufferLength);
	::GlobalUnlock(hBuffer);
	::GlobalFree(hBuffer);

	// copy array back to user
//	::SafeArrayDestroy(*ppUserDataArray);
	::SafeArrayCopy(psa, ppUserDataArray);
	::SafeArrayDestroy(psa);

	return S_OK;
}

HRESULT CBase64Helper::Base64DecodeByteArray(SAFEARRAY ** ppUserDataArray)
{
	PBYTE	pInputBytes;
	PBYTE	pOutputBytes;
	SAFEARRAY * psa;
	LONG lOutputBufferLength;
	HGLOBAL hBuffer;
	PBYTE pBufferPtr;
	LONG lBufferLength;

	//Simply get hold of the Bytes
	pInputBytes = (PBYTE)(*ppUserDataArray)->pvData;
	
	// get length
	lBufferLength = (*ppUserDataArray)->rgsabound[0].cElements;
	
	//Encode these Bytes and copy into buffer
	lOutputBufferLength = Base64Decoder((PBYTE)pInputBytes, lBufferLength, &hBuffer);
	pBufferPtr = (PBYTE)::GlobalLock(hBuffer);
	psa = ::SafeArrayCreateVector(VT_UI1, 0, lOutputBufferLength);
	pOutputBytes = (PBYTE)psa->pvData;
	::CopyMemory(pOutputBytes, pBufferPtr, lOutputBufferLength);
	::GlobalUnlock(hBuffer);
	::GlobalFree(hBuffer);

	// copy array back to user
//	::SafeArrayDestroy(*ppUserDataArray);
	::SafeArrayCopy(psa, ppUserDataArray);
	::SafeArrayDestroy(psa);

	return S_OK;
}

LONG CBase64Helper::Base64Decoder(PBYTE DataIn, LONG DataLength, HGLOBAL * hDataOut)
{
	LONG lOutputBufferLength;
	long iGroupsOf4;
	long iLeftover;
	long n;
	HGLOBAL hBuffer;
	LPSTR pBuffer;
	LPSTR pBufferPtr;
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char r;

	// how many groups and leftovers
	iGroupsOf4 = DataLength / 4;
	iLeftover = 0;
	if (*(DataIn + DataLength - 1) == '=')
		iLeftover++;
	if (*(DataIn + DataLength - 2) == '=')
		iLeftover++;

	// every 4 characters become 3
	lOutputBufferLength = iGroupsOf4;
	if (iLeftover)
		lOutputBufferLength++;
	lOutputBufferLength *= 3;

	// create new buffer
	hBuffer = ::GlobalAlloc(GHND, lOutputBufferLength - iLeftover + 1);
	pBufferPtr = (LPSTR)::GlobalLock(hBuffer);
	pBuffer = pBufferPtr;
	for (n = 0; n < ((iGroupsOf4 * 4) - (iLeftover > 0 ? 4 : 0)); n += 4)
	{
		a = DataIn[n + 0];				// 00aaaaaa
		LOOKUP64CHAR(a);
		b = DataIn[n + 1];				// 00bbbbbb
		LOOKUP64CHAR(b);
		c = DataIn[n + 2];				// 00cccccc
		LOOKUP64CHAR(c);
		d = DataIn[n + 3];				// 00dddddd
		LOOKUP64CHAR(d);

		// first 64
		r = a;							// 00aaaaaa
		r = r << 2;						// aaaaaa00
		r = r + ((b & BASE64_t2) >> 4);	// aaaaaa00 + 000000bb = aaaaaabb
		*pBuffer++ = r;

		// second 64
		r = b;							// 00bbbbbb
		r = r & BASE64_b4;				// 0000bbbb
		r = r << 4;						// bbbb0000
		r = r + (c >> 2);				// bbbb0000 + 0000cccc = bbbbcccc
		*pBuffer++ = r;

		// third 64
		r = c;							// 00cccccc
		r = r << 6;						// cc000000
		r = r & BASE64_h2;				// cc000000
		r = r + d;						// cc000000 + 00dddddd = ccdddddd
		*pBuffer++ = r;
	}

	if (iLeftover)
	{
		n = (iGroupsOf4 * 4) - 4;
		a = DataIn[n + 0];				// 00aaaaaa
		LOOKUP64CHAR(a);
		b = DataIn[n + 1];				// 00bbbbbb
		LOOKUP64CHAR(b);
		c = DataIn[n + 2];				// 00cccccc
		LOOKUP64CHAR(c);

		// first 64
		r = a;							// 00aaaaaa
		r = r << 2;						// aaaaaa00
		r = r + ((b & BASE64_t2) >> 4);	// aaaaaa00 + 000000bb = aaaaaabb
		*pBuffer++ = r;

		if (iLeftover == 1)
		{
			// second 64
			r = b;							// 00bbbbbb
			r = r & BASE64_b4;				// 0000bbbb
			r = r << 4;						// bbbb0000
			r = r + (c >> 2);				// bbbb0000 + 0000cccc = bbbbcccc
			*pBuffer++ = r;
		}
	}

	// pass buffer back and cleanup
	::GlobalUnlock(hBuffer);
	*hDataOut = hBuffer;

	return lOutputBufferLength - iLeftover;
}

LONG CBase64Helper::Base64Encoder(PBYTE DataIn, LONG DataLength, HGLOBAL * hDataOut)
{
	LONG lOutputBufferLength;
	long n;
	long iGroupsOf3;
	long iLeftover;
	HGLOBAL hBuffer;
	PBYTE  pBuffer;
	PBYTE pBufferPtr;;
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char r;

	// how many groups and leftovers
	iGroupsOf3 = DataLength / 3;
	iLeftover = 3 - (DataLength % 3);

	// every 3 characters become 4
	lOutputBufferLength = iGroupsOf3;
	if (iLeftover)
		lOutputBufferLength++;
	lOutputBufferLength *= 4;

	// create new buffer (with terminator byte)
	hBuffer = ::GlobalAlloc(GHND, lOutputBufferLength + 1);
	pBufferPtr = (PBYTE)::GlobalLock(hBuffer);
	pBuffer = pBufferPtr;

	// encode
	for (n = 0; n < (iGroupsOf3 * 3); n += 3)
	{
		a = DataIn[n + 0];				// aaaaaabb
		b = DataIn[n + 1];				// bbbbcccc
		c = DataIn[n + 2];				// ccdddddd

		// first character
		r = a;							// aaaaaabb
		r = r >> 2;						// 00aaaaaa
		*pBuffer++ = cBase64Alphabet[r];

		// second character
		r = a;							// aaaaaabb
		r = r & BASE64_b2;				// 000000bb
		r = r << 4;						// 00bb0000
		r = r + (b >> 4);				// 00bb0000 + 0000bbbb = 00bbbbbb
		*pBuffer++ = cBase64Alphabet[r];

		// third character
		r = b;							// bbbbcccc
		r = b << 2;						// bbcccc00
		r = r & BASE64_t4;				// 00cccc00
		r = r + (c >> 6);				// 00cccc00 + 000000cc = 00cccccc
		*pBuffer++ = cBase64Alphabet[r];

		// fourth character
		r = c;							// ccdddddd
		r = r & BASE64_b6;				// 00dddddd
		*pBuffer++ = cBase64Alphabet[r];
	}

	// handle non multiple of 3 data and insert padding
	if (iLeftover)
	{
		n = (iGroupsOf3 * 3);
		switch (iLeftover)
		{
		case 2:
			a = DataIn[n + 0];				// aaaaaabb
			// first character
			r = a;							// aaaaaabb
			r = r >> 2;						// 00aaaaaa
			*pBuffer++ = cBase64Alphabet[r];
			// second character
			r = a;							// aaaaaabb
			r = r & BASE64_b2;				// 000000bb
			r = r << 4;						// 00bb0000
			r = r + (b >> 4);				// 00bbcccc
			*pBuffer++ = cBase64Alphabet[r];
			// insert padding x 2
			*pBuffer++ = cBase64Alphabet[64];
			*pBuffer++ = cBase64Alphabet[64];
			break;
		case 1:
			a = DataIn[n + 0];				// aaaaaabb
			b = DataIn[n + 1];				// bbbbcccc
			// first character
			r = a;							// aaaaaabb
			r = r >> 2;						// 00aaaaaa
			*pBuffer++ = cBase64Alphabet[r];
			// second character
			r = a;							// aaaaaabb
			r = r & BASE64_b2;				// 000000bb
			r = r << 4;						// 00bb0000
			r = r + (b >> 4);				// 00bbcccc
			*pBuffer++ = cBase64Alphabet[r];
			// third character
			r = b;							// bbbbcccc
			r = b << 2;						// bbcccc00
			r = r & BASE64_t4;				// 00cccc00
			*pBuffer++ = cBase64Alphabet[r];
			// insert padding
			*pBuffer++ = cBase64Alphabet[64];
			break;
		}
	}

	::GlobalUnlock(hBuffer);
	*hDataOut = hBuffer;

	return lOutputBufferLength;
}



//new for 205>>>
