#include "license\license.h"
#include <QDebug>
#include <QProcess>
#include <QtGui/QApplication>
#include <QFile>
#include "Common/logicinterface.h"
#include <QBuffer>
#include <QTemporaryFile>

#include "windows.h"

#define CIPHERTEXT_SIGNATURE           "PMSZ"

CLicense* CLicense::pInstance = NULL;

CLicense::CLicense( bool bVerify, QObject *parent) :
    QObject(parent)
{
    //2014 Dongle 查找注释解密狗
    //RegisterCOM( );
    //QString strFile = "CryptComDLL.dll";
    QString strFile = "OpenSoucreCrypt.dll";
    libLoader.setFileName( strFile );
    MyDoCrypto = NULL;
    MyOpenCrypt = NULL;

    if ( libLoader.load( ) ) {
        MyOpenCrypt = ( MyOpenSourceCrypt ) libLoader.resolve( "OpenSourceCrypt" );
    } else {
        qDebug( ) << libLoader.errorString( ) << endl;
    }

    pDongle = new CETDongle( bVerify, this );

    dateEnd = QDate::fromString( "2088-08-08", "yyyy-MM-dd" );
}

void CLicense::RegisterCOM( )
{
    QProcess proc( this );

    QString strFile = "regsvr32.exe";
    QStringList lstParams;

    lstParams << ( QApplication::applicationDirPath() + "/CryptoAPI.dll" );
    proc.startDetached( strFile + " /u /s ", lstParams );
    proc.startDetached( strFile + " /s ", lstParams );
}

CLicense::~CLicense( )
{
    if ( NULL != pDongle ) {
        delete pDongle;
    }
}

CLicense& CLicense::CreateSingleton( bool bVerify )
{
    if ( NULL == pInstance ) {
        pInstance = new CLicense( bVerify );
    }

    return *pInstance;
}

void CLicense::ReleaseSingleton( )
{
    if ( NULL != pInstance ) {
        delete pInstance;
        pInstance = NULL;
    }
}

bool CLicense::GenerateIniFile( QByteArray& byBase64 )
{
    bool bRet = false;

    if ( NULL ==MyOpenCrypt || byBase64.isEmpty( ) ) {
        return bRet;
    }

    byBase64 = QByteArray::fromBase64( byBase64 );
    DWORD dwFormat = 0;

    OperateSignature( byBase64, dwFormat, FALSE );
    byBase64.remove( 0,  sizeof ( dwFormat ) );

    bool bDecrypt = ( SignatureValue( ) == dwFormat );
    bRet = OpenCrypt( !bDecrypt, byBase64 );

    return bRet;
}

DWORD CLicense::SignatureValue( )
{
    QString strSignature = CIPHERTEXT_SIGNATURE;
    DWORD dwSignature = *( LPDWORD ) strSignature.toAscii( ).data( );
    //char cData[ ] = { 'P', 'M', 'S', 'Z' }; // 50 4d 53 5a

    return dwSignature;
}

BOOL CLicense::OperateSignature( QByteArray& byData, DWORD &dwSignature, BOOL bWrite )
{
    BOOL bRet = FALSE;

    char* pSignature = ( char* ) &dwSignature;
    quint64 nMaxLen = sizeof( dwSignature );

    if ( bWrite ) {
        byData.insert( 0, pSignature, nMaxLen );
    } else {
        dwSignature = * ( LPDWORD ) byData.data( );
    }

    bRet = TRUE;

    return bRet;
}

bool CLicense::GetSection( QString &strPSN, QString &strSection, QSettings& settings )
{
    bool bRet = false;

    int nCount = settings.value( "Counter/Count", 0 ).toInt( );
    QString strItem = "%1/PSN";

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        if ( strPSN == settings.value( strItem.arg( nIndex ), "" ).toString( ) ) {
            strSection = QString::number( nIndex );
            bRet = true;
            break;
        }
    }

    return bRet;
}

bool CLicense::GetPlainText( QString &strMsg, QByteArray &byData )
{
    if ( !pDongle->JudgeTime( ) ) {
         return true;
    }

    bool bRet = false;
    strMsg = "无效的授权数据！\r软件即将退出！";

    if ( !GenerateIniFile( byData ) ) {
        return bRet;
    }

    QTemporaryFile file;
    if ( !file.open( ) ) {
        return bRet;
    }

    QTextStream stream( &file );
    stream << QString( byData );

    file.close( );

    QString strFile = file.fileName( );
    QSettings setings( strFile, QSettings::IniFormat );
    setings.setIniCodec( CCommonFunction::GetTextCodec( ) );

    QString strPSN;
    GetPSN( strPSN );

    QString strSection = "";
    if ( !GetSection( strPSN, strSection, setings ) ) {
        return bRet;
    }

    strSection += "/%1";

    QDate curDate = QDate::currentDate( );

    dateStart = QDateTime::fromMSecsSinceEpoch( setings.value( strSection.arg( "StartDate" ) ).toLongLong( ) ).date( );
    dateEnd = QDateTime::fromMSecsSinceEpoch( setings.value( strSection.arg( "EndDate" ) ).toLongLong( ) ).date( );

    bRet = !( dateStart == curDate && dateEnd == curDate );

    return bRet;
}

void CLicense::GetEndDate( QDate &dtEnd )
{
    dtEnd = dateEnd;
}

bool CLicense::CheckExpiration( QString& strMsg )
{
    bool bRet = SoftwareExpiration( strMsg );
    return bRet;
}

bool CLicense::SoftwareExpiration( QString& strMsg )
{
    if ( !pDongle->JudgeTime( ) ) {
        return true;
    }

    QDate curDate;
    pDongle->GetCurrentDate( curDate );
    bool bRet = ( dateStart <= curDate && curDate <= dateEnd );
    strMsg.clear( );

    if ( !bRet ) {
        QString strStart;
        QString strEnd;
        QString strCur;

        CCommonFunction::Date2String( curDate, strCur);
        CCommonFunction::Date2String( dateStart, strStart);
        CCommonFunction::Date2String( dateEnd, strEnd );
        strMsg = QString( "当前日期是【%1】不在授权日期范围内。\n" ).arg( strCur );
        strMsg += QString ( "软件授权过期了!\n开始时间：【%1】\n截止时间：【%2】\r软件即将退出！" ).arg( strStart, strEnd );
    }

    pDongle->SetDate( dateStart, dateEnd );

    return bRet;
}

CDongle* CLicense::GetDongle( )
{
    return pDongle;
}

bool CLicense::OpenCrypt( bool bEncrypt, QByteArray &byData )
{
    bool bRet = false;

    if ( NULL == MyOpenCrypt ) {
        return bRet;
    }

    char cErrorMsg[ 512 ] = { 0 };
    bRet = MyOpenCrypt( ( LPBYTE ) byData.data( ), byData.count( ), bEncrypt, cErrorMsg );
    qDebug( ) << "MyOpenCrypt" << cErrorMsg << endl;

    return bRet;
}

bool CLicense::DoCrypt( CryptoType type, QString &strSrcFile, QString &strDstFile )
{
    bool bRet = false;
    if ( NULL == MyDoCrypto ) {
        return bRet;
    }

    LPCWSTR pSrc = ( LPCWSTR ) strSrcFile.utf16( );
    LPCWSTR pDst = ( LPCWSTR ) ( strDstFile.isEmpty( ) ? NULL : strDstFile.utf16( ) );

    HRESULT hr = ::CoInitialize( NULL );
    if ( FAILED( hr ) ) {
        return bRet;
    }

    bRet = MyDoCrypto( type, pSrc, pDst );
    ::CoUninitialize( );

    return bRet;
}

void CLicense::GetPSN( QStringList &lstPSNs )
{
    pDongle->GetAllHids( lstPSNs );
}

void CLicense::GetPSN( QString &strPSN )
{
#if false
    unsigned long lMSB = 0;
    unsigned long lMiddle = 0;
    unsigned long lLSB = 0;

    // DataType Label = DefaultValue;
    // Define DataVariable
    // Label:
    //  .DataType DefaultValue
    //
    // ljmp $section, $offse // AT&T
    // jmp section:offset    // Intel
    //
    // movl $test, %eax
    // mov eax, dword ptr test
    // .intel_syntax // Intel syntax replace AT&T syntax
    //
    // .section .data .section .bss .section .text Section
    // .section .data
    // < initialized data here>
    // .section .bss
    // < uninitialized data here>
    // .section .text
    // .globl _start // External Call
    // _start: // EntryPoint
    // <instruction code goes here>
    // movl %ebx, 28(%edi)
    // movl %ebx, -28(%edi)
    // int $0x80
    // call printf // Call C Library
    //
    // movx source, destination
    // movl movw mob 4 2 1
    // movl $output, %edi
    // movl %ebx, (%edi)
    // values:
    // .int 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60
    // base_address(offset_address, index, size)
    // movl $2, %edi
    // movl values( 0, %edi, 4), %eax
    // CMOVO conditional move

    asm( "movl $1, %eax" ); // Function code
    asm( "cpuid" );
    asm( "movl %%edx, %%edx" : "=d"( lMSB ) );

    if ( lMSB &= ( 2 < 18 ) ) { // If PSN
        asm( "movl $1, %eax" );
        asm( "cpuid" );
        asm( "movl %%eax, %%eax" : "=a"( lMSB ) ); // 64-95

        asm( "movl $3, %eax" );
        asm( "cpuid" );
        asm( "movl %%edx, %%edx" : "=d"( lMiddle ) );   // 32-63
        asm( "movl %%ecx, %%ecx" : "=c"( lLSB ) );  // 0-31
    } else {
        ;
    }

    strPSN = QString( "%1-%2-%3" ).arg( QString::number( lMSB ), QString::number( lMiddle ), QString::number( lLSB ) );
#endif

    pDongle->GetHID( strPSN );
}
