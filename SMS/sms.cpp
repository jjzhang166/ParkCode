#include "SMS\sms.h"
#include "Common/commonfunction.h"
#include <QDebug>
#include <QUuid>
#include <windows.h>

CSms* CSms::pSingleton = NULL;

CSms::CSms(QObject *parent) : QThread(parent)
{
    pAxCtrl = new QAxWidget( );
    bool bRet = pAxCtrl->setControl( QString::fromUtf8( "{6C701A8E-0EFD-4539-83D6-3BDEBCDD9C1F}" ) );
    pAxCtrl->setVisible( false );

    bRet = connect( pAxCtrl, SIGNAL( exception( int, const QString&, const QString&, const QString& ) ),
                    this, SLOT( HandleException( int, const QString&, const QString&, const QString& ) ) );
    bRet = connect( pAxCtrl, SIGNAL( OnConnectResult( int ) ), this, SLOT( OnConnectResult( int ) ) );
    bRet = connect( pAxCtrl, SIGNAL( OnRecvMsg( int ) ), this, SLOT( OnRecvMsg( int ) ) );
    bRet = connect( pAxCtrl, SIGNAL( OnSendMsg( int, int ) ), this, SLOT( OnSendMsg( int, int ) ) );
    QVariant var = pAxCtrl->dynamicCall( "init( )" );
    qDebug( ) << ( QVariant( 0 ) == var ? "Init GSM Success" : "Init GSM Failure" ) << endl;

    //mutex.lock( );
}

CSms::~CSms( )
{
    if ( NULL != pAxCtrl ) {
        pAxCtrl->clear( );
        delete pAxCtrl;
        pAxCtrl = NULL;
    }
}

void CSms::customEvent( QEvent *event )
{
    if ( QEvent::User != event->type( ) ) {
        return;
    }

    CSmsEvent* pEvent = ( CSmsEvent* ) event;
    QVariant var;
    var = pAxCtrl->dynamicCall( "ModemConnected( )" );

    if ( !var.toBool( ) ) {
        QSettings* pSet = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
        QVariant varAC = pSet->value( "SMS/AccessCode", "176032225005207" );
        QVariant varCOM = pSet->value( "SMS/COM", "COM3" );
        QVariant varBR = 115200;

        var = pAxCtrl->dynamicCall( "ConnectModem( const QString&, int, const QString& )", varCOM, varBR, varAC );
       // mutex.lock( );

        int nCounter = 12;

        while ( 0 < nCounter-- ) {
            var = pAxCtrl->dynamicCall( "ModemConnected( )" );
            if ( var.toBool( ) ) {
                break;
            }

            Sleep( 10000 );
            qDebug( ) << "Wait for 10 seconds." << endl;
        }
    }

    SendMsg( pEvent );

    //var = pAxCtrl->dynamicCall( "DisconnectModem( )" );
}

CSms& CSms::GetSingleton( )
{
    if ( NULL == pSingleton )   {
        pSingleton = new CSms( );
        pSingleton->start( );
        pSingleton->moveToThread( pSingleton ) ;
    }

    return *pSingleton;
}

void CSms::HandleException( int code, const QString &source, const QString &desc, const QString &help )
{
    QString strMsg = QString( "nCode:%1 Source:%2 Desc:%3 Help:%4" ).arg( QString::number( code ), source, desc, help );
    qDebug( ) << strMsg << endl;
}

void CSms::OnConnectResult( int nStatus )
{
    qDebug( ) << "Connect SGM Modem "  << QString( ( 0 == nStatus ) ? "Success" : "Failure" ) << endl;
   // mutex.unlock( );
}

void CSms::OnRecvMsg( int nMsgCount )
{
    QVariant var;
    QVariant nYear = 0, nMonth = 0, nDay = 0, nHour = 0, nMinute = 0, nSecond = 0;
    QString strTel, strCnt;
    strTel.reserve( 32 );
    strCnt.reserve( 200 );

    while ( 0 < nMsgCount ) {
        var = pAxCtrl->dynamicCall( "RecvMsg( QString&, QString&, int&, int&, int&, int&, int&, int& )",
                                    strTel, strCnt, nYear, nMonth, nDay, nHour, nMinute, nSecond );
        qDebug( ) << QString( "Received message :%1 %2" ).arg( strTel, strCnt ) << endl;
        nMsgCount--;
    }
}

void CSms::OnSendMsg( int nResult, int nMsgIndex )
{
    qDebug( ) << "Send Message " << QString( ( 0 == nResult ) ? "Success" : "Failure" ) <<  QString( " DestNumber:%1" ).arg( nMsgIndex )<< endl;
}

void CSms::SendMsg( QStringList &lstTelNumber, QString &strContent )
{
    CSmsEvent* pEvent = new CSmsEvent( QEvent::User );
    pEvent->SetParameters( lstTelNumber, strContent );
    QApplication::postEvent( this, pEvent );
}

void CSms::SendMsg( CSmsEvent* pEvent )
{
    QStringList& lstTelNumber = pEvent->GetTelList( );
    QVariant varContent = pEvent->GetSmsCnt( );

    QVariant var;

    foreach ( const QString& str, lstTelNumber ) {
        if ( 11 != str.count( ) || "1" != str.left( 1 ) ) {
            continue;
        }

        QVariant varTelNum = str;
        QVariant varIndex = str.toInt( );
        var = pAxCtrl->dynamicCall( "SendMsg(  const QString&, const QString&, int )", varTelNum, varContent, varIndex  );
    }
}

void CSms::run( )
{
    exec( );
}
