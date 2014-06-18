#include "creceiverthread.h"

CReceiverThread::CReceiverThread( Win_QextSerialPort* pPort, QObject *parent) :
    QThread(parent), pWinPort( pPort )
{
    pConfig = CComConfigurator::GetConfigurator( );
    setObjectName( QString( "[Data Receiver Thread ID = %1]" ).arg( qrand( ) ) );
}

CReceiverThread* CReceiverThread::CreateThread( Win_QextSerialPort* pPort, QObject* parent )
{
    qDebug( ) << Q_FUNC_INFO << endl;

    CReceiverThread* pThread = new CReceiverThread( pPort, parent );

    pThread->start( );
    pThread->moveToThread( pThread );
    pPort->moveToThread( pThread );
    return pThread;
}

void CReceiverThread::HandleLog( QString strLog, bool bStatic )
{
    emit Log( strLog, bStatic );
}

void CReceiverThread::Initialize( )
{
    QString strParkID = pWinPort->objectName( );
    strParkID = pConfig->GetComParkID( strParkID );
    pParserThread = CParserThread::CreateThread( strParkID );
    connect( pWinPort, SIGNAL( readyRead( ) ),
             this, SLOT( ReceiveData( ) ) );
    connect( pParserThread, SIGNAL( Log( QString, bool ) ),
             this, SLOT( HandleLog( QString, bool ) ) );
}

void CReceiverThread::run( )
{
    QString strLog = objectName( ) + " Started.";
    SendLog( strLog, true );
    Initialize( );
    exec( );
}

void CReceiverThread::PostEvent( CComThreadEvent *pEvent )
{
    qApp->postEvent( this, pEvent );
}

void CReceiverThread::PostOpenPort( const QString &strCOMx )
{
    CComThreadEvent* pEvent = CComThreadEvent::CreateThreadEvent( CComThreadEvent::ThreadReceiver, CComThreadEvent::EventOpenPort );
    pEvent->SetPortName( strCOMx );

    PostEvent( pEvent );
}

void CReceiverThread::PostClosePort( const QString &strCOMx )
{
    CComThreadEvent* pEvent = CComThreadEvent::CreateThreadEvent( CComThreadEvent::ThreadReceiver, CComThreadEvent::EventClosePort );
    pEvent->SetPortName( strCOMx );

    PostEvent( pEvent );
}

void CReceiverThread::customEvent( QEvent * pEvent )
{
    CComThreadEvent* pThreadEvent = ( CComThreadEvent* ) pEvent;
    CComThreadEvent::EventType evtType = ( CComThreadEvent::EventType ) pEvent->type( );

    QString strCOMx = pThreadEvent->GetPortName( );

    if ( CComThreadEvent::EventOpenPort == evtType ) {
        ProcessOpenPortEvent( strCOMx, pWinPort );
    } else if ( CComThreadEvent::EventClosePort == evtType ) {
        ProcessClosePortEvent( strCOMx, pWinPort );
    }
}

bool CReceiverThread::IsOpen( Win_QextSerialPort *pPort )
{
    return pPort->isOpen( );
}

void CReceiverThread::SendLog( QString& strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog );
    emit Log( strTmp, bStatic );
}

void CReceiverThread::ProcessOpenPortEvent( QString &strCOMx, Win_QextSerialPort *pPort )
{
    if ( pPort->portName( ) == strCOMx && IsOpen( pPort ) ) {
        return;
    }

    if ( IsOpen( pPort ) ) {
        pPort->close( );
    }

    pPort->setQueryMode( Win_QextSerialPort::EventDriven );
    pPort->setTimeout( 500 );
    pPort->setPortName( strCOMx );

    bool bRet = pPort->open( QIODevice::ReadWrite );

    pPort->setBaudRate( BAUD9600 );
    pPort->setDataBits( DATA_8 );
    pPort->setParity( PAR_NONE );
    pPort->setStopBits( STOP_1 );
    pPort->setFlowControl( FLOW_OFF );

    QString strLog = QString( "%1 is opened %2" ).arg( strCOMx,
                                                  bRet ? "Successfully." :
                                                         QString( "Unsuccessfully. %1" ).arg( pPort->errorString( ) ) );

    SendLog( strLog, true );
}

void CReceiverThread::ProcessClosePortEvent( QString &strCOMx, Win_QextSerialPort *pPort )
{
    if ( !IsOpen( pPort ) ) {
        return;
    }

    pPort->close();

    QString strLog = QString( "%1 is closed." ).arg( strCOMx );

    SendLog( strLog, true );
}

void CReceiverThread::ReceiveData( )
{
    Win_QextSerialPort* pPort = ( Win_QextSerialPort* ) sender( );

    QByteArray byData = pPort->readAll( );
    //QString strParkID = pPort->objectName( );
    //qint32 nLen = byData.length( );
    //qDebug( ) << Q_FUNC_INFO << "Length=" << QString::number( nLen ) << endl
    //          << "ASCII: " << QString( byData ) << endl
    //          << "Hex: " << QString( byData.toHex( ) ) << endl;

    pParserThread->PostData( byData );
}

