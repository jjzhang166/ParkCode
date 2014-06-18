#include "databasecontroller.h"

DatabaseController* DatabaseController::pController = NULL;

DatabaseController::DatabaseController( QObject* parent ) : QObject( parent )
{
    pComPortDataProcessor = NULL;
}

DatabaseController::~DatabaseController( )
{
    if ( NULL != pComPortDataProcessor ) {
        pComPortDataProcessor->deleteLater( );
    }
}

int DatabaseController::MySQLLibraryInit(int argc, char *argv[])
{
    return CMySqlDatabase::MySQLLibraryInit( argc, argv );
}

void DatabaseController::MySQLLibraryEnd( )
{
    CMySqlDatabase::MySQLLibraryEnd( );
}

void DatabaseController::CreateDbThreadPool( )
{
    QDataDispactherThread::CreateDbThread( GetController( ) );
}

void DatabaseController::PostConnectDbEvent( )
{
    QDataDispactherThread::PostConnectDbEvent( );
}

DatabaseController* DatabaseController::GetController( QObject *parent )
{
    if ( NULL == pController ) {
        pController = new DatabaseController( parent );
    }

    return pController;
}

void DatabaseController::ReleaseController( )
{
    if ( NULL == pController ) {
        delete pController;
        pController = NULL;
    }
}

void DatabaseController::HandleLog( QString strLog, bool bStatic )
{
    emit Log( strLog, bStatic );
}

QDataDispactherThread* DatabaseController::CreateDispactherThread( QObject* parent )
{
    QDataDispactherThread* pThread = QDataDispactherThread::CreateThread( parent );

    connect( pThread, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );


    return pThread;
}

void DatabaseController::PostComPortData( qint32 nPackageType, QByteArray &byData, QString& strParkID )
{
    if ( NULL == pComPortDataProcessor ) {
        pComPortDataProcessor = QDatabaseProcessor::CreateThread( false );
        connect( pComPortDataProcessor, SIGNAL( Log( QString, bool ) ),
                 this, SLOT( HandleLog( QString, bool ) ) );
    }

    pComPortDataProcessor->PostComPortDataProcessEvent( nPackageType, byData, strParkID );
}

void DatabaseController::PostDispactherData( QDataDispactherThread* pDispatcher, QTcpSocket* pSocket, qint32 nPackageType, QByteArray &byData )
{
    if ( NULL == pDispatcher ) {
        return;
    }

    pDispatcher->PostDispatchDataEvent( pSocket, nPackageType, byData );
}
