#include "qcontrollersp.h"
#include <QDebug>
#include "qthreadspwriter.h"
#include "../ControllerCommon/qcontrollercommon.h"

//http://java-source.net/open-source/charting-and-reporting
// PDFBox/iText/PDFClown/PDFRenderer/jPod/PDFJet(.net) PDF
// JFreeChart/Chart JasperReport(iReport UI)/Report
// JNI/JNA JACOB/Call Windows COM
// C++ NetworkFramework IOCP/EPoll/KQueue ACE/ICE/POCO/libevent
// Java NIO NetworkFramework Netty/Vert.x/NodeJS/MINA/Servlet
// NettyÊÇMINAµÄÇ°±²
// Java SerialPort RXTX/javax.comm
//

//
// Controll serial port
// Communicate with serial port / write, read data
//

QControllerSP::QControllerSP( QObject* parent ) : QObject( parent )
{
    winPort = new Win_QextSerialPort( );
    connect( winPort, SIGNAL( readyRead( ) ), this, SLOT( ReceiveData( ) ) );
}

QControllerSP::~QControllerSP( )
{
    if ( NULL != winPort ) {
        delete winPort;
        winPort = NULL;
    }
}

void QControllerSP::ReceiveData( )
{
    // 4 115200 DalaLen
    // 8 2400
    // 6 9600
    //Sleep( 8 ); // Baud DataLen Relation

    qint64 nRet = winPort->bytesAvailable( );
    if ( 0 == nRet ) {
        //qDebug( ) << "winPort->bytesAvailable( ) return zero" << endl;
        return;
    }

    QByteArray byData = winPort->readAll( );
    //qDebug( ) << byData.toHex( ).toUpper( ) << endl;
    emit Data( byData );
}

BaudRateType QControllerSP::GetBaud( quint8 nIndex )
{
    BaudRateType nRet = BAUD115200;
    switch ( nIndex ) {
    case 0 :
        nRet = BAUD50;
        break;

    case 1 :
        nRet = BAUD75;
        break;

    case 2 :
        nRet = BAUD110;
        break;

    case 3 :
        nRet = BAUD134;
        break;

    case 4:
        nRet = BAUD150;
        break;

    case 5 :
        nRet = BAUD200;
        break;

    case 6 :
        nRet = BAUD300;
        break;

    case 7 :
        nRet = BAUD600;
        break;

    case 8 :
        nRet = BAUD1200;
        break;

    case 9 :
        nRet = BAUD1800;
        break;

    case 10 :
        nRet = BAUD2400;
        break;

    case 11 :
        nRet = BAUD4800;
        break;

    case 12 :
        nRet = BAUD9600;
        break;

    case 13 :
        nRet = BAUD14400;
        break;

    case 14 :
        nRet = BAUD19200;
        break;

    case 15 :
        nRet = BAUD38400;
        break;

    case 16 :
        nRet = BAUD56000;
        break;

    case 17 :
        nRet = BAUD57600;
        break;

    case 18 :
        nRet = BAUD76800;
        break;

    case 19 :
        nRet = BAUD115200;
        break;

    case 20 :
        nRet = BAUD128000;
        break;

    case 21 :
        nRet = BAUD256000;
        break;
    }

    return nRet;
}

DataBitsType QControllerSP::GetDataBit( quint8 nIndex )
{
    DataBitsType nRet = DATA_8;

    switch ( nIndex ) {
    case 0 :
        nRet = DATA_5;
        break;

    case 1 :
        nRet = DATA_6;
        break;

    case 2 :
        nRet = DATA_7;
        break;

    case 3 :
        nRet = DATA_8;
        break;
    }

    return nRet;
}

StopBitsType QControllerSP::GetStopBit( quint8 nIndex )
{
    StopBitsType  nRet = STOP_1;

    switch ( nIndex ) {
    case 0 :
        nRet = STOP_1;
        break;

    case 1 :
        nRet = STOP_1_5;
        break;

    case 2 :
        nRet = STOP_2;
        break;
    }

    return nRet;
}

ParityType QControllerSP::GetParity( quint8 nIndex )
{
    ParityType nRet = PAR_NONE;

    switch ( nIndex ) {
    case 0 :
        nRet = PAR_NONE;
        break;

    case 1 :
        nRet = PAR_ODD;
        break;

    case 2 :
        nRet = PAR_EVEN;
        break;

    case 3 :
        nRet = PAR_MARK;
        break;

    case 4 :
        nRet = PAR_SPACE;
        break;
    }

    return nRet;
}

FlowType QControllerSP::GetFlow( quint8 nIndex )
{
    FlowType  nRet = FLOW_OFF;

    switch ( nIndex ) {
    case 0 :
        nRet = FLOW_OFF;
        break;

    case 1 :
        nRet = FLOW_HARDWARE;
        break;

    case 2 :
        nRet = FLOW_XONXOFF;
        break;
    }

    return nRet;
}



void QControllerSP::ConfigPortBeforeOpen( const LedControll::SComConfig& sConfig )
{
    winPort->setQueryMode( Win_QextSerialPort::EventDriven );
    winPort->setTimeout( 500 );

    QString strName= QString( "COM%1" ).arg( sConfig.nComName + 1 );
    winPort->setPortName( strName );
}

void QControllerSP::ConfigPortAfterOpen( const LedControll::SComConfig &sConfig )
{
    winPort->setBaudRate( GetBaud( sConfig.nBaudRate ) );
    winPort->setDataBits( GetDataBit( sConfig.nDataBit ) );
    winPort->setParity( GetParity( sConfig.nParity ) );
    winPort->setStopBits( GetStopBit( sConfig.nStopBit ) );
    winPort->setFlowControl( GetFlow( sConfig.nFlowCtrl ) );
}

bool QControllerSP::IsOpened(  )
{
    return winPort->isOpen( );
}

bool QControllerSP::OpenPort( )
{
    bool bRet = true;

    if ( IsOpened( ) ) {
        return bRet;
    }

    LedControll::SComConfig sConfig;
    QControllerCommon::GetSPConfig( sConfig );
    ConfigPortBeforeOpen( sConfig );
    bRet = winPort->open( QIODevice::ReadWrite );
    ConfigPortAfterOpen( sConfig );

    return bRet;
}

void QControllerSP::ClosePort( )
{
    if ( winPort->isOpen( ) ) {
        winPort->close( );
    }
}

qint64 QControllerSP::WriteData( QByteArray& data, int nWaitTime, const bool bThread )
{
    qint64 nRet = 0;

    if ( bThread ) {
        QThreadSPWriter::GetSingleton( ).SendData( data, nWaitTime );
        return nRet;
    }

    if ( 0 == data.length( ) ) {
        return nRet;
    }

    if ( !IsOpened( ) && !OpenPort( ) ) {
      return nRet;
    }

    int nCount = data.count( );
    static quint8 nFrequence = 10;
    nRet = nCount;

    do {
        if ( winPort->isWritable( ) ) {
            nRet = winPort->write( data );
            winPort->flush( );

    #ifndef QT_NO_DEBUG
            //QString strData( data.toHex( ).toUpper( ) );
            //qDebug( ) << "Write Serial Port Cmd : " << strData << endl;
    #else
            //emit Cmd( data );
    #endif

            emit Cmd( data, true );

            break;
        } else {
            Sleep( 10 );
            nFrequence--;
        }
    } while( 0 < nFrequence );

    nFrequence = 10;

    return nRet;
}
