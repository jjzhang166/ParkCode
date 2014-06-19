#include "qdatabasethread.h"
QDatabaseThread* QDatabaseThread::pThreadInstance = NULL;
MyDataStructs::QPointerQueue QDatabaseThread::dbObjectQueue;
QMutex QDatabaseThread::queueMutex;

QDatabaseThread::QDatabaseThread(QObject *parent) :
    QMyBaseThread(parent)
{
    setObjectName( "QDatabaseThread" );
    OutputMsg( QString( " Created" ) );
    //bTcpTask = true;
    nDatabaseObjLifeTime = 60;
    pDatabaseGenerator = QDatabaseGenerator::GetSingleton( );
}

QDatabaseThread::~QDatabaseThread( )
{
    OutputMsg( "" );
}

QDatabaseThread* QDatabaseThread::GetSingleton( /*const bool bTcpThread*/ )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QDatabaseThread( );
        pThreadInstance->InitializeThread( );
        //pThreadInstance->SetTaskType( bTcpThread );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

#if false
void QDatabaseThread::SetTaskType( bool bTcpTaskItem )
{
    bTcpTask = bTcpTaskItem;
}
#endif

void QDatabaseThread::run( )
{
    InitializeSubThread( );
    exec( ); // Event Loop
}

void QDatabaseThread::GetDatabaseParam( const QManipulateIniFile::IniFileSectionItems item, QVariant &var )
{
    QManipulateIniFile::IniFileNames file = manipulateFile.GetIniFileNameType( );
    manipulateFile.IniFileValue( file, QManipulateIniFile::IniDatabase, item, false, var );
}

void QDatabaseThread::GetDatabaseTypeParam( )
{
    QVariant var;

    GetDatabaseParam( QManipulateIniFile::DatabaseType, var );
    dbType = ( MyEnums::DatabaseType ) var.toInt( );
}

void QDatabaseThread::GetDatabaseThreadpoolParam( )
{
    QVariant var;

    GetDatabaseParam( QManipulateIniFile::DatabaseThreadpoolMaxThreads, var );
    dbThreadPool.setMaxThreadCount( var.toInt( ) );

    GetDatabaseParam( QManipulateIniFile::DatabaseThreadpoolThreadExpire, var );
    dbThreadPool.setExpiryTimeout( var.toInt( ) * 1000 );
}

void QDatabaseThread::GetConnectParamItem( const QManipulateIniFile::IniFileSectionItems item )
{
    QVariant var;

    GetDatabaseParam( item, var );
    hashDatabaseParams.insertMulti( item, var );
}

void QDatabaseThread::GetDatabaseObjLifeTime( )
{
    QVariant var;

    GetDatabaseParam( QManipulateIniFile::DatabaseObjectLifeTime, var );
    nDatabaseObjLifeTime = var.toUInt( );
}

void QDatabaseThread::GetDatabaseConnectParam( )
{
    GetConnectParamItem( QManipulateIniFile::DatabaseHost );
    GetConnectParamItem( QManipulateIniFile::DatabasePort );
    GetConnectParamItem( QManipulateIniFile::DatabaseUser );
    GetConnectParamItem( QManipulateIniFile::DatabasePwd );
    GetConnectParamItem( QManipulateIniFile::DatabaseSchema );
}

void QDatabaseThread::InitializeSubThread( )
{
    GetDatabaseTypeParam( );
    GetDatabaseThreadpoolParam( );
    GetDatabaseConnectParam( );
}

bool QDatabaseThread::SignalConnected( )
{
    int nSignal = receivers( SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ) );

    return ( 0 < nSignal );
}

void QDatabaseThread::ProcessCrudEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    QMyDatabase* pDatabase = NULL;
    QueueDatabaseObject( pDatabase, false );

    if ( NULL == pDatabase ) {
        pDatabase = pDatabaseGenerator->GeneratorDatabaseInstance( dbType );
        if ( NULL == pDatabase ) {
            QString* strMsg = new QString( QString( "Database type error (%1)" ).arg( dbType ) );
            HandleMessage( strMsg, QManipulateIniFile::LogCfgParam );
            return;
        }
    }

    connect( pDatabase, SIGNAL( NotifyMessage( void*, QManipulateIniFile::LogTypes ) ), this, SLOT( HandleMessage( void*, QManipulateIniFile::LogTypes ) ) );

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );

    QVariant varData = hash.value( MyEnums::NetworkParamData );
    quint32 nBytePointer = varData.toUInt( );
    QByteArray* pByteData = ( QByteArray* ) nBytePointer;

    varData = hash.value( MyEnums::NetworkParamSenderThread );
    quint32 nThreadPointer = ( quint32 ) varData.toUInt( );
    QThread* pSenderSocketThread = ( QThread* ) nThreadPointer;

    varData = hash.value( MyEnums::NetworkParamSocket );
    quint32 nSocketPointer = ( quint32 ) varData.toUInt( );
    QAbstractSocket* pPeerSocket = ( QAbstractSocket* ) nSocketPointer;

    bool bTcpTask = ( pPeerSocket->socketType( ) == QAbstractSocket::TcpSocket );

    varData = hash.value( MyEnums::NetworkParamUdpSenderIP );
    QString strSenderIP = varData.toString( );

    varData = hash.value( MyEnums::NetworkParamUdpSenderPort );
    quint16 nSenderPort = ( quint16 ) varData.toUInt( );

    pDatabase->SetLifeTime( nDatabaseObjLifeTime );
    pDatabase->SetDatabaseParams( hashDatabaseParams );

    QThreadPoolTask* pTask = QThreadPoolTask::GetInstance( pByteData, pSenderSocketThread,
                                                           this, pPeerSocket,
                                                           pDatabase, bTcpTask, strSenderIP, nSenderPort );

    if ( !bTcpTask ) {
        varData = hash.value( MyEnums::NetworkParamUdpDatagramType );
        pTask->SetUdpDatagramType( ( MyEnums::UdpDatagramType ) varData.toInt( ) );
    }

    dbThreadPool.start( pTask );
}

void QDatabaseThread::ProcessEnqueueEvent( MyDataStructs::PQQueueEventParams pEventParams )
{
    if ( NULL == pEventParams || pEventParams->isEmpty( ) ) {
        return;
    }

    MyDataStructs::QEventMultiHash& hash = pEventParams->head( );

    QVariant varData = hash.value( MyEnums::NetworkParamDatabaseObject );
    quint32 nDatabasePointer = varData.toUInt( );
    QMyDatabase* pDatabase = ( QMyDatabase* ) nDatabasePointer;

    QueueDatabaseObject( pDatabase, true );
}

void QDatabaseThread::ReleaseDatabaseObject( )
{
    QMyDatabase* pDatabase = NULL;

    queueMutex.lock( );

    bool bEmpty = dbObjectQueue.isEmpty( );

    if ( !bEmpty ) {
        MyDataStructs::QPointerList lstDatabases = dbObjectQueue.toSet( ).toList( );
        foreach ( void* pObject, lstDatabases ) {
            pDatabase = ( QMyDatabase* ) pObject;

            if ( pDatabase->MayRelease( ) ) {
                dbObjectQueue.removeOne( pObject );
            }

            delete pDatabase;
        }
    }

    queueMutex.unlock( );
}

void QDatabaseThread::QueueDatabaseObject( QMyDatabase *&pDababase, const bool bEnqueue )
{
    queueMutex.lock( );

    if ( bEnqueue ) {
        if ( NULL != pDababase ) {
            dbObjectQueue.enqueue( pDababase );
            pDababase->SetEnqueueStartMinute(  );
        }
    } else if ( !dbObjectQueue.empty( ) ) {
        pDababase = ( QMyDatabase * ) dbObjectQueue.dequeue( );
    }

    queueMutex.unlock( );
}

void QDatabaseThread::customEvent( QEvent *event )
{
    QDatabaseThreadEvent* pEvent = ( QDatabaseThreadEvent* ) event;
    MyEnums::EventType type = ( MyEnums::EventType ) pEvent->type( );
    MyDataStructs::PQQueueEventParams pEventParams = pEvent->GetEventParams( );

    if ( MyEnums::DatabaseCrud == type ) {
        ProcessCrudEvent( pEventParams );
    } else if ( MyEnums::DatabaseObjectEnqueue == type ) {
        ProcessCrudEvent( pEventParams );
    } else if ( MyEnums::ThreadExit == type ) {
        pThreadInstance = NULL;
        LaunchThreadExit( );
    }
}
