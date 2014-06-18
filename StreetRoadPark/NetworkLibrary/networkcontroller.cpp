// Java HttpServer API / Client API com.sun.net.httpserver org.apache.http
// Windows HttpServer API / Client API
// NodeJS OPA
// c Client / curl libUrl libWWW
// pdfFactory setupFactory InstallShield
// PECL PHP-GTK bcompiler-->php...bytecode
// PHP-Qt, PHP bindings to the Qt toolkit
// PHP-GTK, PHP bindings to GTK+
// wxPHP, PHP bindings for wxWidgets
// WinBinder, native window bindings for PHP
// 脚本语言与跨平台GUI绑定都可实现GUI应用开发 eg. LUA Python etc.

//
// Windows IOCP / Select.... model
// Linux EPoll / Process Per Connection( PPC )
// Thread Per Connection( TPC ) Select Poll model
// libevent an event notification library
// POCO library
// Unix-->select poll
// Solaris-->/dev/pool
// BSD-->kqueue
//
//

#include "networkcontroller.h"

NetworkController* NetworkController::pController = NULL;

NetworkController::NetworkController( QObject *parent ) : QObject( parent )
{
    qRegisterMetaType< qintptr >( "qintptr" );
    pListenerThread = QListenerThread::CreateThread( );
    pMulticastThread = QLikeBroadcastThread::CreateThread( );
    byTokenData = DATA_TOKEN;

    connect( pListenerThread, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );
    connect( pMulticastThread, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );
}

NetworkController::~NetworkController( )
{
    pMulticastThread->deleteLater( );
    pListenerThread->deleteLater( );
}

NetworkController* NetworkController::GetController( QObject *parent )
{
    if ( NULL == pController ) {
        pController = new NetworkController( parent );
    }

    return pController;
}

void NetworkController::ReleaseController( )
{
    if ( NULL != pController ) {
        delete pController;
        pController = NULL;
    }
}

void NetworkController::StartListen( quint16 nPort, qint32 nMaxConn )
{
    pListenerThread->PostStartListenEvent( nPort, nMaxConn );
}

void NetworkController::StartMultiCastListen( )
{
    pMulticastThread->PostStartListenEvent( );
}

void NetworkController::StopListen( )
{
    pListenerThread->PostStopListenEvent( );
}

void NetworkController::StopMultiCastListen( )
{
    pMulticastThread->PostStopListenEvent( );
}

void NetworkController::MulticastData( QByteArray& byJson, qint32 nMulticastType )
{
    //pMulticastThread->PostUDPMultiDataEvent( byJson, nMulticastType );
    quint32 nBodyDataLen = byJson.length( );
    quint32 nDataSize = sizeof ( quint32 );

    qint32 nType = qToBigEndian< qint32 >( nMulticastType );
    byJson.insert( 0, ( const char* ) &nType, nDataSize );

    quint32 nReserved = qToBigEndian< quint32 >( 0 );
    byJson.insert( 0, ( const char* ) &nReserved, nDataSize );

    qint32 nDataLen = byTokenData.length( ) + nDataSize * 3 + nBodyDataLen;
    nDataLen = qToBigEndian< quint32 >( nDataLen );
    byJson.insert( 0, ( const char* ) &nDataLen, nDataSize );

    byJson.insert( 0, byTokenData );

    pMulticastThread->PostMulticastSocketEvent( byJson );
}

void NetworkController::HandleLog( QString strLog, bool bStatic )
{
    emit Log( strLog, bStatic );
}
