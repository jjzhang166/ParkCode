#include "quploaddatathread.h"
#include <QDebug>

// Modify ProcessData.cpp ProcessData.h
QUploadDataThread* QUploadDataThread::pThreadInstance = NULL;

QUploadDataThread::QUploadDataThread(QObject *parent) :
    QThread(parent)
{
    pSettings = NULL;
    connect( this, SIGNAL( terminated( ) ), this, SLOT( ThreadExit( ) ) );
}

QUploadDataThread::~QUploadDataThread( )
{
    if ( NULL != pSettings ) {
        delete pSettings;
    }
}

void QUploadDataThread::CloseDB( )
{
    QSqlDatabase db = QSqlDatabase::database( strConnectName, false );
    if ( db.isOpen( ) ) {
        db.close( );
    }
}

void QUploadDataThread::ThreadExit( )
{
    delete this;
}

void QUploadDataThread::PrintMsg( QSqlError sqlError )
{
    QString strText = sqlError.text( );
    qDebug( ) << strText << endl;
}

QUploadDataThread* QUploadDataThread::CreateInstance( QObject *pParent )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new QUploadDataThread( pParent );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void QUploadDataThread::PostUploadDataEvent( QStringList &lstRecordParams, QByteArray &byImage )
{
    QUploadDataEvent* pEvent = QUploadDataEvent::CreateEvent( QUploadDataEvent::InOutRecord );

    pEvent->SetRecordParams( lstRecordParams, byImage );
    PostEvent( pEvent );
}

void QUploadDataThread::PostEvent(QUploadDataEvent *pEvent)
{
    qApp->postEvent( this, pEvent );
}

void QUploadDataThread::InitializeThread( )
{
    strFileName = "%1_%2_%3_%4_%5.jpg";
    pSettings = new QSettings( "./Data/SystemCfg.ini", QSettings::IniFormat );
    strParkID = pSettings->value( "CommonCfg/ParkID", "" ).toString( );
    if ( strParkID.isEmpty( ) ) {
        qDebug( ) << "ParkID Invalid" << endl;
    }

    strConnectName = "SQLServer";
    QSqlDatabase dbODBC = QSqlDatabase::addDatabase( "QODBC", strConnectName );

    if ( !dbODBC.isValid( ) ) {
        PrintMsg( dbODBC.lastError( ) );
    }

    QString strHost = pSettings->value( "UploadData/Host", "115.29.149.133" ).toString( );
    QString strUser = pSettings->value( "UploadData/User", "parkdb" ).toString( );
    QString strPwd = pSettings->value( "UploadData/Pwd", "[Guid(EC1CC096-0327-424A-8300-57AA6A104EA5)]" ).toString( );
    QString strConnectString = QString( "DRIVER={SQL Server};SERVER=%1;UID=%2;PWD=%3;DATABASE=parkdb;" ).arg(
                strHost, strUser, strPwd );

    dbODBC.setDatabaseName( strConnectString );

    //pSqlQuery = new QSqlQuery( dbODBC );
    //pSqlQuery->prepare( "INSERT INTO dbo.jccxx ( ccbh, cphm, jccbj, rqsj, kh ) "
    //                    "VALUES ( :ccbh, :cphm, :jccbj, :rqsj, :kh )" );

    pFtpThread = QFtpThread::CreateInstance( );

    //QStringList lstFtpServer;
    //lstFtpServer << strHost << "21" << "Ftp" << "[Guid(\"269C795D-337F-485A-954A-186CBDEB0C66\")]";
    //pFtpThread->SetFtpServer( lstFtpServer );
}

void QUploadDataThread::run( )
{
    InitializeThread( );

    exec( );
}

void QUploadDataThread::customEvent( QEvent *e )
{
    QUploadDataEvent* pEvent = ( QUploadDataEvent* ) e;
    QUploadDataEvent::UploadDataEvent eEvent = ( QUploadDataEvent::UploadDataEvent ) e->type( );

    switch ( eEvent ) {
    case QUploadDataEvent::InOutRecord :
        ProcessUploadDataEvent( pEvent );
        break;
    }
}

void QUploadDataThread::GetFileName( QString& strName, QStringList& lstParams )
{
    const QString& strPlate = lstParams.at( 0 );
    const QString& strInOutFlag = lstParams.at( 1 );
    const QString& strDateTime = lstParams.at( 2 );
    const QString& strCardID = lstParams.at( 3 );

    bool bCard = ( strPlate.isEmpty( ) || "Î´Öª" == strPlate );
    QString strPlateFlag = bCard ? "0" : "1";
    QString strDT = QDateTime::fromString( strDateTime, "yyyy-MM-dd HH:mm:ss" ).toString( "yyyyMMddHHmmss" );

    //bCard = false;
    //QString strPlate1 = "´¨A12345";
    strName = strFileName.arg( strParkID, strPlateFlag,
                               bCard ? strCardID : strPlate,
                               strInOutFlag, strDT );
    //strName = "Test.jpg";
}

void QUploadDataThread::UploadImage( QUploadDataEvent *pEvent )
{
    QStringList& lstParams = pEvent->GetRecordParams( );
    if ( 4 > lstParams.count( ) ) {
        return;
    }

    QByteArray& byImage = pEvent->GetImageData( );
    if ( 0 >= byImage.count( ) ) {
        return;
    }

    QString strName;
    GetFileName( strName, lstParams );

/*
    static QByteArray byData;
    if ( byData.size( ) == 0 ) {
        QFile file( "d:/ipcDevice.jpg" );
        file.open( QFile::ReadOnly );
        byData = file.readAll( );
        file.close( );
    }*/

    pFtpThread->PostUploadFileEvent( strName, byImage );

}

void QUploadDataThread::ProcessUploadDataEvent( QUploadDataEvent *pEvent )
{
    QStringList& lstParams = pEvent->GetRecordParams( );
    if ( 4 > lstParams.count( ) ) {
        return;
    }

    //pSqlQuery->bindValue( ":ccbh", strParkID );
    //pSqlQuery->bindValue( ":cphm", lstParams.at( 0 ) );
    //pSqlQuery->bindValue( ":jccbj", lstParams.at( 1 ) );
    //pSqlQuery->bindValue( ":rqsj", lstParams.at( 2 ) );
    //pSqlQuery->bindValue( ":kh", lstParams.at( 3 ) );

    QSqlDatabase dbODBC = QSqlDatabase::database( strConnectName );
    if ( dbODBC.isOpenError( ) ) {
        PrintMsg( dbODBC.lastError( ) );
    }
    QSqlQuery sqlQuery( dbODBC );
    QString strSQL = QString( "Insert Into dbo.jccxx( ccbh, cphm, jccbj, rqsj, kh )"
                     " Values( '%1', '%2', '%3', '%4', '%5' )" ).arg(
                strParkID, lstParams.at( 0 ), lstParams.at( 1 ),
                lstParams.at( 2 ), lstParams.at( 3 ) );

    bool bRet = sqlQuery.exec( strSQL );
    if ( !bRet ) {
        PrintMsg( sqlQuery.lastError( ) );
    }

    UploadImage( pEvent );
}
