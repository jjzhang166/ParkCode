#ifndef LICENSE_H
#define LICENSE_H

#include <QObject>
#include <windows.h>
#include <QLibrary>
#include <QDate>
#include "../Dongle/ETDongle/etdongle.h"
#include <QSettings>

#define		BINARY_FORMAT_MAJOR_VERSION		((WORD)0x0001)
#define		BINARY_FORMAT_MINOR_VERSION		((WORD)0x0000)
#define		FILE_BINARY_FORMAT_VERSION		MAKELONG(BINARY_FORMAT_MINOR_VERSION,\
                                                                                                         BINARY_FORMAT_MAJOR_VERSION)

class CLicense : public QObject
{
    Q_OBJECT
public:
    typedef enum __CryptoType {
            FileEncrypt,
            //EncryptString,
            FileDecrypt,
            //DecryptString,
    } CryptoType;
    //explicit
    bool CheckExpiration( QString& strMsg );
    CDongle* GetDongle( );

    static CLicense& CreateSingleton( bool bVerify );
    static void ReleaseSingleton(  );
    bool DoCrypt( CryptoType type, QString& strSrcFile, QString& strDstFile );
    bool OpenCrypt( bool bEncrypt, QByteArray &byData );
    bool GetPlainText( QString& strMsg, QByteArray &byData );
    void GetPSN( QString& strPSN ); // Get Processor Serial Number to use CPUID Instruction
    void GetPSN( QStringList& lstPSNs );
    bool GenerateIniFile( QByteArray& byBase64 );

    BOOL OperateSignature( QByteArray& byData, DWORD &dwSignature, BOOL bWrite );
    DWORD SignatureValue( );
    void GetEndDate( QDate& dtEnd );

private:
    typedef BOOL WINAPI ( *DoCrypto ) ( CryptoType type, LPCWSTR lpszSrcFile, LPCWSTR lpszDesFile );
    typedef BOOL WINAPI  ( *MyOpenSourceCrypt ) ( LPBYTE pData, const int nDataLen, BOOL bEncrypt, char* pErrorMsg );

    CLicense( bool bVerify, QObject *parent = 0);
    ~CLicense( );

    void RegisterCOM( );
    bool SoftwareExpiration( QString& strMsg );
    bool GetSection( QString& strPSN, QString& strSection, QSettings& settings );

private:
    static CLicense* pInstance;
    DoCrypto MyDoCrypto;
    MyOpenSourceCrypt MyOpenCrypt;
    QLibrary libLoader;
    QDate dateStart;
    QDate dateEnd;
    CDongle* pDongle;

signals:

public slots:

};

#endif // LICENSE_H
