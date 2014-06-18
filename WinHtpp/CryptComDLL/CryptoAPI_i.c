/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Nov 17 12:05:11 2011
 */
/* Compiler settings for C:\Documents and Settings\Administrator\×ÀÃæ\c89ac7bfcf46\CryptoAPI.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ICrypto = {0x6F7D3059,0xE96A,0x48DF,{0xB2,0x32,0x1A,0xE4,0x44,0x38,0x40,0x97}};


const IID LIBID_CRYPTOAPILib = {0x15EA8944,0x438E,0x471E,{0x86,0x0D,0x67,0x43,0xD4,0x38,0x3A,0x37}};


const CLSID CLSID_Crypto = {0x391B0AA4,0x1E17,0x485F,{0xB6,0x35,0x0F,0xE2,0x62,0x19,0xE8,0x7E}};


#ifdef __cplusplus
}
#endif

