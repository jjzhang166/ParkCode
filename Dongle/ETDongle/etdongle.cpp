#include "etdongle.h"

// Apple Carbon Cocoa API

CETDongle::CETDongle( bool bVerify, QObject* parent  ) :  CDongle( parent )
{
    bVerifyDate = bVerify;
    pETContext = new ET_CONTEXT;
    memset( pETContext, 0, sizeof ( ET_CONTEXT ) );

    FillAdminHash( );

    InitApiPointer( );
    GetApiPointer( );

    OpenETDongle( );
    DongleDetection( bVerifyDate);

    MyStartTimer( );
}

CETDongle::~CETDongle( )
{
    if ( NULL != DongleClose ) {
        ;//DongleClose( pETContext );
    }

    if ( NULL != pETContext ) {
        delete pETContext;
        pETContext = NULL;
    }
}

bool CETDongle::JudgeTime( )
{
    return ( ETDiamond == eDongleType );
}

void CETDongle::GetAllHids( QStringList& lstHids )
{
    DWORD dwRet = ET_S_SUCCESS;
    DWORD dwEtCounter = 0;
    quint8 bSN[ MAX_ID_LEN ] = { 0 };
    DWORD dwOut = 0;
    QString strHID = "";

    dwRet = DongleEnum( NULL, &dwEtCounter );
    bool bRet = ( ET_S_SUCCESS == dwRet || ET_E_INSUFFICIENT_BUFFER == dwRet );
    if ( !bRet ) {
        return;
    }

    ET_CONTEXT* pContext = new ET_CONTEXT[ dwEtCounter ];
    if ( NULL == pContext ) {
        return;
    }

    memset( pContext, 0, sizeof ( ET_CONTEXT ) * dwEtCounter );

    dwRet = DongleEnum( pContext, &dwEtCounter );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet ) {
        goto FREE_MEMORY;
    }

    for ( DWORD dwItem = 0; dwItem < dwEtCounter; dwItem++ ) {
        dwRet = DongleOpen( &pContext[ dwItem ] );
        bRet = ( ET_S_SUCCESS == dwRet );
        if ( !bRet ) {
            continue;
        }

        if ( !GetDongleType( eDongleType, &pContext[ dwItem ] ) ) {
            continue;
        }

        if ( dwCustomerID[ eDongleType ] == pContext[ dwItem ].dwCustomer &&
             QByteArray( ( LPCSTR ) pContext[ dwItem ].bAtr, pContext[ dwItem ].dwAtrLen )  ==
             QByteArray( ( LPCSTR ) bATR[ eDongleType ], sizeof ( bATR[ eDongleType ] ) ) ) {
             dwRet = DongleControl( &pContext[ dwItem ], ET_GET_SERIAL_NUMBER, NULL, 0, bSN, sizeof ( bSN ), &dwOut);
             bRet = ( ET_S_SUCCESS == dwRet );
             if ( !bRet ) {
                 goto CLOSE_DONGLE;
             }

            strHID = QString( QByteArray( ( LPCSTR ) bSN, sizeof ( bSN ) ).toHex( ).toUpper( ) );
            if ( IsAdminHID( strHID ) ) {
                continue;
            }

            if ( !strHID.isEmpty( ) ) {
                lstHids << strHID;
            }
        }

        CLOSE_DONGLE:
        ;
        //DongleClose( &pContext[ dwItem ] );
    }

    FREE_MEMORY:
    if ( NULL != pContext) {
        delete [ ] pContext;
        pContext = NULL;
    }
}

void CETDongle::Reopen( )
{
    if ( NULL != DongleClose ) {
        DongleClose( pETContext );
    }

    OpenETDongle( );
}

void CETDongle::FillAdminHash( )
{
    hashAdminHID.insert( "89004D4109000001", "89004D4109000001" );
    hashAdminHID.insert( "81005A4933000001", "81005A4933000001" );
    hashAdminHID.insert( "A6004B410F000001", "A6004B410F000001" );
}

bool CETDongle::ContainAdminHID( )
{
    bool bRet = false;
    QString strHID = "";

    if ( !GetHID( strHID ) ) {
        return bRet;
    }

    bRet = hashAdminHID.contains( strHID );

    return bRet;
}

bool CETDongle::IsAdminHID( QString &strHID )
{
    strHID = strHID.toUpper( );

    return hashAdminHID.contains( strHID );
}

bool CETDongle::Administrator( )
{
    bool bRet = false;

    bRet = ContainAdminHID( );
    if ( !bRet ) {
        QString strMsg =  "请插入管理员加密狗！";
        EmitDongleException( strMsg, true, true);
    }

    return bRet;
}

void CETDongle::DongleDetection( bool bVerifyDate  )
{
    VerifyDongle( pETContext );

    if ( bVerifyDate ) {
        VerifyDate( pETContext );
    }
}

bool CETDongle::ExclusiveOpen( ET_CONTEXT* pContext )
{
    bool bRet = false;
    ET_OPENINFO openIfno = { sizeof ( ET_OPENINFO ), 0 };

    DWORD dwRet = DongleOpenEx( pContext, &openIfno );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( bRet ) {
        DongleClose( pContext );
    }

    return bRet;
}

void CETDongle::DongleTimerOpen( )
{
    //OpenETDongle( );
}

bool CETDongle::OpenETDongle( )
{
    bool bRet = false;
    DWORD dwRet = ET_S_SUCCESS;
    DWORD dwEtCounter = 0;
    quint8 bSN[ MAX_ID_LEN ] = { 0 };
    DWORD dwOut = 0;
    QString strHID = "";

    if ( NULL == DongleEnum ) {
        return bRet;
    }

    dwRet = DongleEnum( NULL, &dwEtCounter );
    bRet = ( ET_S_SUCCESS == dwRet || ET_E_INSUFFICIENT_BUFFER == dwRet );
    if ( !bRet ) {
            FunctionException( dwRet );
            return bRet;
    }

    if ( 0 == dwEtCounter ) {
        QString strMsg =  "请插入正确的加密狗！";
        EmitDongleException( strMsg, true, true );
        return bRet;
    }

    ET_CONTEXT* pContext = new ET_CONTEXT[ dwEtCounter ];
    bRet = ( NULL != pContext );
    if (  !bRet ) {
        EmitDongleException( "创建加密狗上下文资源失败。", true, true );
        return bRet;
    }

    memset( pContext, 0, sizeof ( ET_CONTEXT ) * dwEtCounter );

    dwRet = DongleEnum( pContext, &dwEtCounter );
    FunctionException( dwRet );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet || 0 == dwEtCounter || NULL == DongleOpen) {
        delete [ ] pContext;
        pContext = NULL;
        return bRet;
    }

    QStringList lstIndexs;
    bool bHaveAdmin = false;

    for ( DWORD dwItem = 0; dwItem < dwEtCounter; dwItem++ ) {
        dwRet = DongleOpen( &pContext[ dwItem ] );
        bRet = ( ET_S_SUCCESS == dwRet );
        if ( !bRet ) {
            continue;
        }

        if ( !GetDongleType( eDongleType, &pContext[ dwItem ] ) ) {
            continue;
        }

        if ( dwCustomerID[ eDongleType ] == pContext[ dwItem ].dwCustomer &&
             QByteArray( ( LPCSTR ) pContext[ dwItem ].bAtr, pContext[ dwItem ].dwAtrLen )  ==
             QByteArray( ( LPCSTR ) bATR[ eDongleType ], sizeof ( bATR[ eDongleType ] ) ) ) {

            if ( 1 < dwEtCounter ) { // 管理员优先
                dwRet = DongleControl( &pContext[ dwItem ], ET_GET_SERIAL_NUMBER, NULL, 0, bSN, sizeof ( bSN ), &dwOut);
                bRet = ( ET_S_SUCCESS == dwRet );
                if ( bRet ) {
                    strHID = QString( QByteArray( ( LPCSTR ) bSN, sizeof ( bSN ) ).toHex( ).toUpper( ) );
                    if ( IsAdminHID( strHID ) ) {

                        if ( bHaveAdmin ) {
                            lstIndexs << QString::number( dwItem );
                            continue;
                        }

                        bHaveAdmin = true;
                        memcpy( pETContext, ( CONST LPVOID) &pContext[ dwItem ], sizeof ( ET_CONTEXT ) );
                        continue;
                    } else {
                        lstIndexs << QString::number( dwItem );
                        continue;
                    }
                }
            } else { // One
                memcpy( pETContext, ( CONST LPVOID) &pContext[ dwItem ], sizeof ( ET_CONTEXT ) );
                break;
            }
        }

        DongleClose( &pContext[ dwItem ] );
        bRet = false;
    }

    if ( !bHaveAdmin && lstIndexs.count( ) > 0 ) {
        strHID = lstIndexs[ 0 ];
        DWORD dwIndex = strHID.toULong( );
        memcpy( pETContext, ( CONST LPVOID) &pContext[ dwIndex ], sizeof ( ET_CONTEXT ) );
        lstIndexs.removeAt( 0 );
    }

    foreach ( const QString strIndex, lstIndexs ) {
        DWORD dwIndex = strIndex.toULong( );
        DongleClose( &pContext[ dwIndex ] );
    }

    delete [ ] pContext;
    pContext = NULL;

    if ( !bRet ) { // first
        EmitDongleException( "无有效的加密狗。", true, true );
        return bRet;
    }

    return bRet;
}

void CETDongle::GetCurrentDate( QDate &dtDate )
{
    tm curDate = { 0 };
    QString strMsg = "无有效的加密狗。";

    DWORD dwOutLen = 0;
    DWORD dwRet = DongleControl( pETContext, ET_GET_CURRENT_TIME, NULL, 0, &curDate, sizeof ( tm ), &dwOutLen );
    FunctionException( dwRet );
    bool bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet ) {
        EmitDongleException( strMsg, true, true );
        return;
    }

    dtDate.setYMD( curDate.tm_year + 1900, curDate.tm_mon + 1, curDate.tm_mday );
}

bool CETDongle::VerifyDate( ET_CONTEXT *pContext )
{
  bool bRet = false;

  if ( NULL == pContext ) {
      return bRet;
  }

  QDate date;
  GetCurrentDate( date );
  bRet = ( dateStart <= date && date <= dateEnd );

  bool bFuture = ( dateEnd.addDays( - 7 ) <= date && date <= dateEnd );

  if ( !bRet || bFuture ) {
      QString strFormat = "yyyy-MM-dd";
      QString strStart = dateStart.toString( strFormat );
      QString strEnd = dateEnd.toString( strFormat );
      QString strCur = date.toString( strFormat );

      QString strMsg = QString( "当前日期是【%1】。%2\n" ).arg( strCur, bFuture ? "" : "不在授权日期范围内" );
      strMsg += QString ( "软件授权%1过期!\n开始时间：%2\n截止时间：%3%4" ).arg(
                                     bFuture ? "即将" : "已经", strStart, strEnd, !bRet ? "\r软件即将退出！" : "" );

      EmitDongleException( strMsg, !bRet || !bFuture,  !bFuture );
  }

  return bRet;
}

BOOL CETDongle::GetDongleType( DongleType& eType, ET_CONTEXT *pContext )
{
    eType = ETDiamond;

    DWORD dwDongleType = 0;
    DWORD dwOutLen = 0;
    DWORD dwRet = DongleControl( pContext, ET_GET_CUSTOMER_NAME, NULL, 0, &dwDongleType, sizeof ( dwDongleType ), &dwOutLen );
    FunctionException( dwRet );
    BOOL bRet = ( ET_S_SUCCESS == dwRet );
    QString strMsg = "获取加密狗类型失败。";

    if ( !bRet ) {
        EmitDongleException( strMsg, true, true );
        return bRet;
    }

    if ( dwCustomerID[ 0 ] == dwDongleType ) {
        eType = ETDiamond;
    } else if ( dwCustomerID[ 1 ] == dwDongleType ) {
        eType = ET199;
    } else {
        EmitDongleException( strMsg, true, true );
        return false;
    }

    return bRet;
}

bool CETDongle::VerifyDongle( ET_CONTEXT *pContext )
{
    bool bRet = false;

    if ( NULL == pContext ) {
        return bRet;
    }

    if ( !GetDongleType( eDongleType, pContext ) ) {
        return bRet;
    }

    DWORD dwOutLen = 0;
    quint8 bAtrValue[ MAX_ATR_LEN ] = { 0 };
    quint8  bCustomer[ sizeof ( DWORD ) ] = { 0 };
    QString strMsg = "无有效的加密狗。";

    DWORD dwRet = DongleControl( pETContext, ET_GET_DEVICE_ATR, NULL, 0, bAtrValue, sizeof ( bAtrValue ), &dwOutLen );
    FunctionException( dwRet );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet ) {
        EmitDongleException( strMsg, true, true );
        return bRet;
    }

    dwRet = DongleControl( pETContext, ET_GET_CUSTOMER_NAME, NULL, 0, bCustomer, sizeof ( bCustomer ), &dwOutLen );
    FunctionException( dwRet );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet ) {
        EmitDongleException( strMsg, true, true );
        return bRet;
    }

    LPDWORD lpID = ( LPDWORD ) bCustomer;
    if ( dwCustomerID[ eDongleType ] != *lpID ||
         QByteArray( ( LPCSTR ) bAtrValue, sizeof ( bAtrValue ) ) != QByteArray( ( LPCSTR ) bATR[ eDongleType ], sizeof ( bATR[ eDongleType ] ) ) ) {
        EmitDongleException( strMsg, true, true );
        return false;
    }

    return bRet;
}

bool  CETDongle::GetHID( QString &strHID )
{
    bool bRet = false;
    if ( NULL == pETContext ) {
        return bRet;
    }

    quint8 bSN[ MAX_ID_LEN ] = { 0 };
    DWORD dwOut = 0;
    DWORD dwRet = 0;

    dwRet = DongleControl( pETContext, ET_GET_SERIAL_NUMBER, NULL, 0, bSN, sizeof ( bSN ), &dwOut);
    FunctionException( dwRet );
    bRet = ( ET_S_SUCCESS == dwRet );
    if ( !bRet ) {
        return bRet;
    }

    strHID = QString( QByteArray( ( LPCSTR ) bSN, sizeof ( bSN ) ).toHex( ).toUpper( ) );

    return bRet;
}

void CETDongle::InitApiPointer( )
{
    DongleEnum = NULL;
    DongleOpen = NULL;
    DongleClose = NULL;
    DongleControl = NULL;
    DongleErrorMsg = NULL;
    DongleOpenEx = NULL;
}

void CETDongle::FunctionException( DWORD dwRet )
{
    if ( NULL == DongleErrorMsg || ET_S_SUCCESS == dwRet ) {
        return;
    }

    CHAR cErrorMsg[ 1024 ] = { 0 };
    if ( ET_S_SUCCESS != DongleErrorMsg( dwRet, cErrorMsg, sizeof ( cErrorMsg ) / sizeof( CHAR ) - 1 ) ) {
        return;
    }

    QString strMsg( cErrorMsg );
    EmitDongleException( strMsg, true, true );
}

void CETDongle::EmitDongleException( QString strMsg, bool bExit, bool bRetry )
{
    emit DongleException( strMsg, bExit, bRetry );
}

void CETDongle::ResoveException( PVOID pFunc, QString strFuncName )
{
    if ( NULL != pFunc ) {
        return;
    }

    EmitDongleException( QString( "%1 Funtion isn't found." ).arg( strFuncName ), true, false );
}

void CETDongle::GetApiPointer( )
{
    QString strFile = "ET199_32.dll";

    apiLoader.setFileName( strFile );
    if ( !apiLoader.load( ) ) {
        EmitDongleException( apiLoader.errorString( ), true, false );
        return;
    }

    DongleEnum = ( MyETEnum ) apiLoader.resolve( "ETEnum" );
    ResoveException( ( PVOID ) DongleEnum, "ETEnum" );

    DongleOpen = ( MyETOpen ) apiLoader.resolve( "ETOpen" );
    ResoveException( ( PVOID ) DongleOpen, "ETOpen" );

    DongleOpenEx = ( MyETOpenEx ) apiLoader.resolve( "ETOpenEx" );
    ResoveException( ( PVOID ) DongleOpenEx, "ETOpenEx" );

    DongleClose = ( MyETClose ) apiLoader.resolve( "ETClose" );
    ResoveException( ( PVOID ) DongleClose, "ETClose" );

    DongleControl = ( MyETControl ) apiLoader.resolve( "ETControl" );
    ResoveException( ( PVOID ) DongleControl, "ETControl" );

    DongleErrorMsg = ( MyETFormatErrorMessage ) apiLoader.resolve( "ETFormatErrorMessage" );
    ResoveException( ( PVOID ) DongleErrorMsg, "ETFormatErrorMessage" );
}
