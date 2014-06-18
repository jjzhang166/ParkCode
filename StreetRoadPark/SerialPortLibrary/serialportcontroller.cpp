#include "serialportcontroller.h"

SerialPortController* SerialPortController::pController = NULL;

SerialPortController* SerialPortController::GetController( QObject* parent )
{
    if ( NULL == pController ) {
        pController = new SerialPortController( parent );
    }

    return pController;
}

void SerialPortController::ReleaseController( )
{
    if ( NULL != pController ) {
        delete pController;
        pController = NULL;
    }
}

SerialPortController::SerialPortController( QObject* parent ) : QObject( parent )
{
}

SerialPortController::~SerialPortController( )
{
    FreeThread( hashReceiver );
    FreeThread( hashSender );
    FreeComObject( hashCom );
}

void SerialPortController::FreeThread( QComThreadHash &hashThread )
{
    foreach ( QThread* pThread, hashThread.values( ) ) {
        pThread->deleteLater( );
    }

    hashThread.clear( );
}

void SerialPortController::FreeComObject( QComHash &hashCom )
{
    foreach ( const Win_QextSerialPort* pCom, hashCom.values( ) ) {
        delete pCom;
    }

    hashCom.clear( );
}

void SerialPortController::HandleLog( QString strLog, bool bStatic )
{
    emit Log( strLog, bStatic );
}

void SerialPortController::OpenSerialPort( const QString &strCOMx )
{
    if ( strCOMx.isEmpty( ) ) {
        return;
    }

    ReceiverThread( strCOMx )->PostOpenPort( strCOMx );
}

void SerialPortController::CloseSerialPort( const QString &strCOMx )
{
    if ( strCOMx.isEmpty( ) ) {
        return;
    }

    ReceiverThread( strCOMx )->PostClosePort( strCOMx );
}



Win_QextSerialPort* SerialPortController::ComObject( const QString &strCOMx )
{
    Win_QextSerialPort* pPort = hashCom.value( strCOMx, NULL );

    if ( NULL == pPort ) {
        pPort = new Win_QextSerialPort( );
        pPort->setObjectName( strCOMx );
        hashCom.insert( strCOMx, pPort );
    }

    return pPort;
}

void SerialPortController::SendCmd( const QString &strCOMx, CmdPort eCmd, quint32 nP0, quint32 nP1,quint32 nP2 )
{
    Win_QextSerialPort* pPort = ComObject( strCOMx );

    if ( !pPort->isOpen( ) ) {
        OpenSerialPort( strCOMx );
    }

    QString strCmd;
    char* pFormat = NULL;
    char nParamCount = 0;

    switch ( eCmd ) {
    case CmdDetectorThresholdModify :
        pFormat = ( char* ) "#%03d,*Lim%02d=%03d";
        nParamCount = 3;
        break;

    case CmdDetectorDelayTimeModify :
        pFormat = ( char* ) "#%03d,*Day%02d=%03d";
        nParamCount = 3;
        break;

    case CmdDetectorReadData$ :
        pFormat = ( char* ) "#%03d,*$%02d";
        nParamCount = 2;
        break;

    case CmdDetectorReadDataR :
        pFormat = ( char* ) "#%03d,*R%02d";
        nParamCount = 2;
        break;

    case CmdDetectorReadDataA :
        pFormat = ( char* ) "#%03d,*A%02d";
        nParamCount = 2;
        break;

    case CmdDetectorForceReset :
        pFormat = ( char* ) "#%03d,#r%02d";
        nParamCount = 2;
        break;

    case CmdDetectorModifyID :
        pFormat = ( char* ) "#%03d,*Sid%02d=%03d";
        nParamCount = 3;
        break;

    case CmdDetectorModifyChannel :
        pFormat = ( char* ) "#%03d,*Sch%02d=%03d";
        nParamCount = 3;
        break;

    case CmdDetectorCommunicationTestOpen :
        pFormat = ( char* ) "#%03d,#T%02d";
        nParamCount = 2;
        break;

    case CmdDetectorCommunicationTestClose :
        pFormat = ( char* ) "#%03d,*T%02d";
        nParamCount = 2;
        break;

    case CmdReceiverModifyHostChannel :
        pFormat = ( char* ) "#%03d,*CHL=%03d";
        nParamCount = 2;
        break;

    case CmdReciverSetID :
        pFormat = ( char* ) "#%03d,*ID=%03d";
        nParamCount = 2;
        break;

    case CmdReceiverHostSleep :
        pFormat = ( char* ) "#%03d,*WAT";
        nParamCount = 1;
        break;

    case CmdCount :
        break;
    }

    switch ( nParamCount ) {
    case 1 :
        strCmd.sprintf( pFormat, nP0 );
        break;

    case 2 :
        strCmd.sprintf( pFormat, nP0, nP1 );
        break;

    case 3 :
        strCmd.sprintf( pFormat, nP0, nP1, nP2 );
        break;
    }

    if ( !strCmd.isEmpty( ) ) {
        QByteArray byCmd = strCmd.toLatin1( );
        SenderThread( strCOMx )->PostCmd( byCmd );
    }
}

CReceiverThread* SerialPortController::ReceiverThread( const QString &strCOMx )
{
    CReceiverThread* pThread = ( CReceiverThread* ) hashReceiver.value( strCOMx, NULL );

    if ( NULL == pThread ) {
        Win_QextSerialPort* pPort = ComObject( strCOMx );
        pThread = CReceiverThread::CreateThread( pPort );
        connect( pThread, SIGNAL( Log( QString, bool ) ),
                 this, SLOT( HandleLog( QString, bool ) ) );
        hashReceiver.insert( strCOMx, pThread );
    }

    return pThread;
}

CSenderThread* SerialPortController::SenderThread( const QString &strCOMx )
{
    CSenderThread* pThread = ( CSenderThread* ) hashSender.value( strCOMx, NULL );

    if ( NULL == pThread ) {
        pThread = CSenderThread::CreateThread( ComObject( strCOMx ) );
        connect( pThread, SIGNAL( Log( QString, bool ) ),
                 this, SLOT( HandleLog( QString, bool ) ) );
        hashSender.insert( strCOMx, pThread );
    }

    return pThread;
}
