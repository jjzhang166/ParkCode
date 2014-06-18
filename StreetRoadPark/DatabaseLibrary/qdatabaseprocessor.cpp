#include "qdatabaseprocessor.h"
#include "../NetworkLibrary/networkcontroller.h"
#include "Constant.h"

QDatabaseProcessor::QDatabaseProcessor( bool bPoolThread, QObject *parent) :
    QThread(parent), bThreadPoolProcessor( bPoolThread )
{
    setObjectName( QString( "[Database Processor Thread ID = %1]" ).arg( qrand( ) ) );
    pResSemaphore = NULL;
    pDataDispatcher = NULL;
    pDatabase = NULL;
    pConfig = CDbConfigurator::GetConfigurator( );
    nDbOperationCount = pConfig->GetDbThreadOperationCount( );
}

QDatabaseProcessor::~QDatabaseProcessor( )
{
    if ( NULL != pResSemaphore ) {
        delete pResSemaphore;
        pResSemaphore = NULL;
    }

    if ( NULL != pDatabase ) {
        delete pDatabase;
        pDatabase = NULL;
    }
}

void QDatabaseProcessor::SetDataDispatcher(QThread *pDispatcher)
{
    pDataDispatcher = pDispatcher;
}

QDatabaseProcessor* QDatabaseProcessor::CreateThread( bool bPoolThread, QObject *parent )
{
    qDebug( ) << Q_FUNC_INFO << endl;
    QDatabaseProcessor* pThread = new QDatabaseProcessor( bPoolThread, parent );

    pThread->start( );
    pThread->moveToThread( pThread );

    return pThread;
}

qint32 QDatabaseProcessor::GetFreeOperationCount( )
{
    qint32 nCount = 0;
    if ( !bThreadPoolProcessor ) {
        return nCount;
    }

    nCount = pResSemaphore->available( );
    qDebug( ) << Q_FUNC_INFO << objectName( )
              << ":" << QString::number( nCount ) << endl;
    return nCount;
}

void QDatabaseProcessor::AcquireProcessor( qint32 nResCount )
{
    if ( !bThreadPoolProcessor ) {
        return;
    }

    pResSemaphore->acquire( nResCount );
}

bool QDatabaseProcessor::TryAcquireProcessor( )
{
    bool bRet = false;
    if ( !bThreadPoolProcessor ) {
        return bRet;
    }

    bRet = pResSemaphore->tryAcquire( 1 );
    qDebug( ) <<  Q_FUNC_INFO << ":"
               << objectName( )
               << ":" <<
               ( bRet ? "Success" : "Unsuccess" ) << endl;

    return bRet;
}

bool QDatabaseProcessor::TryAcquireProcessor( qint32 nTimeout )
{
    bool bRet = false;
    if ( !bThreadPoolProcessor ) {
        return bRet;
    }

    bRet = pResSemaphore->tryAcquire( 1, nTimeout * 1000 );

    qDebug( ) <<  Q_FUNC_INFO << ":"
               << objectName( )
               << ":" <<
               ( bRet ? "Success" : "Unsuccess" ) << endl;

    return  bRet;
}

void QDatabaseProcessor::HandleLog( QString strLog, bool bStatic )
{
    SendLog( strLog, bStatic );
}

void QDatabaseProcessor::SendLog( QString &strLog, bool bStatic )
{
    if ( !bStatic && !pConfig->GetDisplayDynamicLog( ) ) {
        return;
    }

    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QDatabaseProcessor::InitializeSubThread( )
{
    pConfig->ReadDbInfo( lstDbInfo );

    if ( bThreadPoolProcessor ) {
        pResSemaphore = new QSemaphore( nDbOperationCount );
    } else {
        //dataProcessor.SetNetController( NetworkController::GetController( ) );
    }

    connect( &dataProcessor, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );

    QString strObjName = objectName( );
    dataProcessor.SetNetController( NetworkController::GetController( ) );
    dataProcessor.setObjectName( strObjName );
    pDatabase = new CMySqlDatabase( );
    pDatabase->setObjectName( strObjName );

    connect( pDatabase, SIGNAL( NotifyError( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );

    dataProcessor.SetDatabase( pDatabase );

    //QDbThreadEvent* pEvent = QDbThreadEvent::CreateThreadEvent( QDbThreadEvent::ThreadDbProcessor,
    //                                                            QDbThreadEvent::EventConnectDb );
    //pEvent->SetReconnect( false );
    ProcessDatabaseConnectEvent( NULL );
    //delete pEvent;
}

void QDatabaseProcessor::run( )
{
    QString strLog = objectName() + " Started.";
    SendLog( strLog, true );
    InitializeSubThread( );
    exec() ;
}

void QDatabaseProcessor::customEvent( QEvent *event )
{
    QDbThreadEvent* pEvent = ( QDbThreadEvent* ) event;
    QDbThreadEvent::EventType evtType = ( QDbThreadEvent::EventType ) pEvent->type( );

    if ( QDbThreadEvent::EventProcessDbData == evtType ) {
        ProcessDatabaseDataEvent( pEvent );
    } else if ( QDbThreadEvent::EventConnectDb == evtType ) {
        ProcessDatabaseConnectEvent( pEvent );
    } else if ( QDbThreadEvent::EventProcessComPortData == evtType ) {
        ProcessComPortDataEvent( pEvent );
    }
}

void QDatabaseProcessor::ProcessComPortDataEvent( QDbThreadEvent *pEvent )
{
    //
    // SensorEnter-->TabletEneter-->SensorLeave-->TabletLeave finish
    // Consumer
    qint32 nPackageType = pEvent->GetDataPackageType( );
    QByteArray& byData = pEvent->GetByteArray( );
    QString& strParkID = pEvent->GetComParkID( );

    QString strLog = "Com Port Dispatcher:"
            + objectName( ) + ":" + QString( byData );
    SendLog( strLog, false );

    //ProcessDatabaseConnectEvent( NULL );
    dataProcessor.ProcessComPortData( nPackageType, byData, strParkID );
}

void QDatabaseProcessor::ProcessDatabaseDataEvent( QDbThreadEvent *pEvent )
{
    // Consumer
    QTcpSocket* pSocket = pEvent->GetPeerSocket( );
    qint32 nPackageType = pEvent->GetDataPackageType( );
    QByteArray& byData = pEvent->GetByteArray( );

    QString strData = QString::fromUtf8( byData );
    if ( Constant::TypeInOutRecordInfo == nPackageType ) {
        QString strImage = "\"Image\":\"";
        qint32 nStartIndex = strData.indexOf( strImage );
        if ( -1 != nStartIndex ) {
            nStartIndex += strImage.length( );
            qint32 nEndIndex = strData.indexOf( "\"", nStartIndex );
            if ( -1 != nEndIndex ) {
                strData.remove( nStartIndex, nEndIndex - nStartIndex );
            }
        }
    }

    QString strLog = pDataDispatcher->objectName( ) + ":"
            + objectName( ) + ":" + strData;

    //static int nCount = 0;
    //strLog = QString::number( ++nCount );
    SendLog( strLog, false );

    //ProcessDatabaseConnectEvent( NULL );
    dataProcessor.SetPeerSocket( pSocket );
    dataProcessor.ProcessSocketData( nPackageType, byData );
    pResSemaphore->release( 1 );
}

void QDatabaseProcessor::ProcessDatabaseConnectEvent( QDbThreadEvent *pEvent )
{
    QString strLog;
    Q_UNUSED( pEvent )
    QStringList lstInfo;
    pConfig->ReadDbInfo( lstInfo );

    if ( 5 != lstDbInfo.count( ) || 5 != lstInfo.length( ) ) {
        strLog = "Database argument error.";
        SendLog( strLog, true );
        return;
    }

    bool bRet = ( lstDbInfo.at( 0 ) != lstInfo.at( 0 ) );

    if ( !pDatabase->GetFirstConnect( ) && bRet ) {
        //pDatabase->SetFirstConnect( false );
        pDatabase->SetFirstConnect( bRet );
        lstDbInfo.replace( 0, lstInfo.at( 0 ) );
    }

    if ( pDatabase->GetFirstConnect( ) ) {
        bRet = pDatabase->DbConnect( lstDbInfo.at( 0 ),
                                     lstDbInfo.at( 1 ),
                                     lstDbInfo.at( 2 ),
                                     lstDbInfo.at( 3 ),
                                     lstDbInfo.at( 4 ).toUInt( ) );
        strLog = "Firstly Connect Database.";
        SendLog( strLog, true );
    } else {
        do {
            ulong lID0 = pDatabase->GetThreadID( );
            bRet = pDatabase->PingMysql( );
            qDebug( ) << QString::number( lID0 ) <<endl;

            if ( !bRet ) {
                sleep( 5 );
            }

            ulong lID1 = pDatabase->GetThreadID( );

            if ( lID1 != lID0 ) {
                strLog = "Ping Connect Database.";
                SendLog( strLog, true );
            }
        } while ( !bRet );
    }
}

void QDatabaseProcessor::PostDbConnectEvent( )
{
    QDbThreadEvent* pEvent = QDbThreadEvent::CreateThreadEvent( QDbThreadEvent::ThreadDbProcessor, QDbThreadEvent::EventConnectDb );

    PostEvent( pEvent );
}

void QDatabaseProcessor::PostComPortDataProcessEvent( qint32 nPackageType, QByteArray &byData, QString& strParkID )
{
    QDbThreadEvent* pEvent = QDbThreadEvent::CreateThreadEvent( QDbThreadEvent::ThreadDbProcessor, QDbThreadEvent::EventProcessComPortData );

    pEvent->SetDataPackageType( nPackageType );
    pEvent->SetByteArray( byData );
    pEvent->SetComParkID( strParkID );

    PostEvent( pEvent );
}

void QDatabaseProcessor::PostDbDataProcessEvent( QTcpSocket *pSocket, qint32 nPackageType, QByteArray &byData )
{
    QDbThreadEvent* pEvent = QDbThreadEvent::CreateThreadEvent( QDbThreadEvent::ThreadDbProcessor, QDbThreadEvent::EventProcessDbData );

    pEvent->SetDataPackageType( nPackageType );
    pEvent->SetByteArray( byData );
    pEvent->SetPeerSocket( pSocket );

    PostEvent( pEvent );
}

void QDatabaseProcessor::PostEvent( QDbThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}
