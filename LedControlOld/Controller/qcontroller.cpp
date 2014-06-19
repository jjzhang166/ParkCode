#include "qcontroller.h"
#include "../ControllerSP/qthreadsp.h"
#include "../ControllerSP/qthreadspwriter.h"
#include "../ControllerSP/qthreadspparser.h"


QController::QController( QObject* parent ) : QObject( parent )
{
    pController = new QControllerSP( );
    connect( pController, SIGNAL( Cmd( QByteArray, bool ) ), this, SLOT( HandleCmd( QByteArray, bool ) ) );
    connect( &QThreadSPParser::GetSingleton( ), SIGNAL( Cmd( QByteArray, bool ) ),
             this, SLOT( HandleCmd( QByteArray,bool ) ) );
    connect( &QThreadSPParser::GetSingleton( ), SIGNAL( Query( QString, qint8, QByteArray ) ),
             this, SLOT( HandleQuery( QString, qint8, QByteArray ) ) );
    connect( pController, SIGNAL( Data( QByteArray ) ), this, SLOT( HandleData( QByteArray ) ) );
}

QController::~QController( )
{
    if ( NULL != pController ) {
        delete pController;
        pController = NULL;
    }
}

void QController::HandleCmd( QByteArray data, bool bSend )
{
    emit Cmd( data, bSend );
}

void QController::HandleData( QByteArray data )
{
    emit Data( data );
}

void QController::HandleQuery( QString strInfo, qint8 nIndex, QByteArray byData )
{
    emit Query( strInfo, nIndex, byData );
}

qint64 QController::WriteData( QByteArray &data, int nWaitTime, const bool bThread )
{
    return pController->WriteData( data, nWaitTime, bThread );
}

bool QController::ConrollSP( const bool bOpen )
{
    bool bRet = true;

    if ( bOpen ) {
        bRet = pController->OpenPort( );

        QThreadSP::GetSingleton( ).SetController( pController );
        QThreadSP::GetSingleton( ).SetDataReceiver( &QThreadSPParser::GetSingleton( ) );
        QThreadSPWriter::GetSingleton( ).SetController( pController );
    } else {
        pController->ClosePort( );
    }

    return bRet;
}
