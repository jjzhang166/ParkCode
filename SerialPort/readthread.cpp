#include "readthread.h"
#include "processdata.h"

CReadThread* CReadThread::pThreadInstance = NULL;

CReadThread::CReadThread(CWinSerialPort* pSerial, QObject *parent) :
    QThread(parent)
{
    pWinSerial = pSerial;
}

CReadThread* CReadThread::CreateInstance( CWinSerialPort* pSerial )
{
    if ( NULL == pThreadInstance ) {
        pThreadInstance = new CReadThread( pSerial );
        pThreadInstance->start( );
        pThreadInstance->moveToThread( pThreadInstance );
    }

    return pThreadInstance;
}

void CReadThread::InitializeThread( )
{
    connect( &pWinSerial->GetRawSerialPort( ), SIGNAL( readyRead( ) ),
             this, SLOT( DataMayRead( ) ) );

    hInOutEvent [ 0 ] = CreateEvent( NULL, TRUE, TRUE, NULL );
    hInOutEvent [ 1 ] = CreateEvent( NULL, TRUE, TRUE, NULL );
}

void CReadThread::DataMayRead( )
{
    //Sleep( 10 );
    Sleep( 4 );

    int nMinLen = 8;
    Win_QextSerialPort& winSerial = pWinSerial->GetRawSerialPort( );
    int nValided = winSerial.bytesAvailable( );
    if ( nMinLen > nValided ) {
#ifndef QT_NO_DEBUG
        qDebug( ) << QString( " Data Length less than 8 ( %1 )") .arg( nValided )  << endl;
#endif
         return;
    }

#ifndef QT_NO_DEBUG
        qDebug( ) << "Time " << QDateTime::currentDateTime( ).toMSecsSinceEpoch( ) << endl;
#endif
        QByteArray byData = winSerial.readAll( );

#ifndef QT_NO_DEBUG
        QString strData( byData.toHex( ) );
        qDebug( ) << "Read Serial Port Cmd : " << strData << endl;
#endif

        if ( byData.count( ) < nMinLen ) {
            return;
        }

        char cEnd = 0x55;
        char cStart = 0xAA;
        int nIndex = -1;
        QByteArray bySingle;
        int nDataLen = 0;

        do {
            nIndex = byData.indexOf( cStart );
            if ( -1 == nIndex ) { // No 0xAA
                break;
            } else if ( 0 < nIndex ) { // First 0xAA
                byData.remove( 0, nIndex );
                if ( nMinLen > byData.count( ) ) {
                    break;
                }
            }

            nDataLen = ( BYTE ) byData[ 1 ] + ( ( ( BYTE ) byData[ 2 ]  ) << 8 );
            nDataLen += 4;

            if ( nDataLen >= byData.count( ) ) {
                break;
            }

            if ( cEnd != byData[ nDataLen ] ) {
                nDataLen += 1;
                byData.remove( 0, nDataLen );
                continue;
            }

            nDataLen += 1;
            bySingle = byData.left( nDataLen  );
            byData.remove( 0, nDataLen );

            ParseData( bySingle );
        } while ( nMinLen <= byData.count( ) );
}

void CReadThread::run( )
{
    InitializeThread( );
    exec( );
}

void CReadThread::ParseData( QByteArray& byData )
{
    int nRet = 0;
    QByteArray vData;
    quint16 nDataLen = 0;
    quint8 nCanAddr = 0;
    quint8 nCheckSum = 0;
    CPortCmd::PortUpCmd cmdType =  portCmd.ParseUpCmd( byData, nDataLen, nCanAddr, nCheckSum, vData );
    ProcessCmd( byData, cmdType );

    emit SerialData( byData );
}

void CReadThread::GateSense( bool bEnterGate, bool bLeavePark )
{
    //GateIfHaveVehicle[ !bLeavePark ] = bEnterGate;

    HANDLE hEvent = hInOutEvent [ !bLeavePark ];
    if ( bEnterGate ) {
        ResetEvent( hEvent ); //无信号
    } else {
        SetEvent( hEvent ); //有信号
    }

    qDebug( ) << "Event Object" << endl;
}

HANDLE CReadThread::GetEventObject( bool bEnter )
{
    return hInOutEvent[ bEnter ];
}

void CReadThread::ProcessCmd( QByteArray &byData, CPortCmd::PortUpCmd cmdType )
{
    bool bEnter = ( 0x01 == byData[ 6 ]  ); // Enter Gate / Sense
    //bool bLeave = ( 0x00 == byData[ 6 ] ); // Leave Gate / Sense
    QByteArray vData;

    switch ( cmdType ) {
    case CPortCmd::UpNone :
        ;
        break;
    case CPortCmd::UpSuccess :
        ;
        break;
    case CPortCmd::UpFailed :
        ;
        break;
    case CPortCmd::UpCCExist :
        break;
    case CPortCmd::UpInGateExist :
    case CPortCmd::UpOutGateExist :
        ;
        break;
    case CPortCmd::UpCardInfo : // Shua Card
        ;
        break;
    case CPortCmd::UpDispenserReply : // 发卡机状态
        ;
        break;
    case CPortCmd::UpAudioEnd :
        ;
        break;
    case CPortCmd::UpInBallotSenseVehcleEnter : // Vehcle Enter
        ;
        break;
    case CPortCmd::UpInBallotSenseVehcleLeave :
        ;
        break;
    case CPortCmd::UpOutBallotSenseVehcleEnter : // Vehcle Enter
        ;
        break;
    case CPortCmd::UpOutBallotSenseVehcleLeave :
        ;
        break;
    case CPortCmd::UpButtonDownCar : //
    case CPortCmd::UpButtonDownNoCar :
        ;
        break;
    case CPortCmd::UpButtonUpCar :
        ;//BallotButton( byData, vData, false );
        break;
    //case CPortCmd::UpButtonDownNoCar :
    //    ;
    //    break;
    case CPortCmd::UpButtonUpNoCar :
        ;//BallotButton( byData, vData, false );
        break;
    case CPortCmd::UpInGateSenseVehcleEnter :// 道闸地感车辆进入
        GateSense( bEnter, false );
        break;
    case CPortCmd::UpInGateSenseVehcleLeave :
        GateSense( bEnter, false );
        break;
    case CPortCmd::UpOutGateSenseVehcleEnter :// 道闸地感车辆进入
        GateSense( bEnter, true );
        break;
    case CPortCmd::UpOutGateSenseVehcleLeave :
        GateSense( bEnter, true );
        break;
    case CPortCmd::UpQuerySenseCar : // 票箱地感状态
        ;
        break;
    case CPortCmd::UpQuerySenseNoCar :
        ;
        break;
    case CPortCmd::UpQueryButtonOpen : // 取卡按钮状态
        ;
        break;
    case CPortCmd::UpQueryButtonClose :
        break;
    case CPortCmd::UpQueryGateCar : // 道闸地感状态
        break;
    case CPortCmd::UpQueryGateNoCar :
        break;
    case CPortCmd::UpQueryControler : // 道闸控制器状态
        break;
    }
}

void CReadThread::customEvent( QEvent* e )
{

}
