#include "SerialPort/winserialport.h"
#include <QDebug>
#include <QApplication>
#include <QStringList>
#include <QTextCodec>
#include "Common/commonfunction.h"

CWinSerialPort::CWinSerialPort( const char* pCOMSection,QObject *parent) :
    QObject(parent)
{
    pParent = parent;
    strCOMSection = pCOMSection;
    pWinSerialPort = new  Win_QextSerialPort(  );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
}

CWinSerialPort::~CWinSerialPort( )
{
    if ( NULL != pWinSerialPort ) {
        delete pWinSerialPort;
    }

    if ( NULL != pSettings ){
        delete pSettings;
    }
}

void CWinSerialPort::SetPortName( )
{
    int nPort = pSettings->value( strCOMSection + "/name" ).toInt( ) + 1;

    QString strName= QString( "COM%1" ).arg( nPort );
    pWinSerialPort->setPortName( strName );
}

void CWinSerialPort::SetQueryMode( QextSerialBase::QueryMode mode )
{
    pWinSerialPort->setQueryMode( mode );
}

Win_QextSerialPort& CWinSerialPort::GetRawSerialPort( )
{
    return *pWinSerialPort;
}

BaudRateType CWinSerialPort::GetBaud( int nIndex )
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

DataBitsType CWinSerialPort::GetDataBit( int nIndex )
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

StopBitsType CWinSerialPort::GetStopBit( int nIndex )
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

ParityType CWinSerialPort::GetParity( int nIndex )
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

FlowType CWinSerialPort::GetFlow( int nIndex )
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

void CWinSerialPort::GetCfg( QStringList &cfgStream, bool bRead )
{
    if ( bRead ) {
        cfgStream << pSettings->value( strCOMSection + "/name", QVariant( 0 ) ).toString( );;
        cfgStream << pSettings->value( strCOMSection + "/baud", QVariant( 19 ) ).toString( );
        cfgStream << pSettings->value( strCOMSection + "/data", QVariant( 3 ) ).toString( );
        cfgStream << pSettings->value( strCOMSection + "/parity", QVariant( 0 ) ).toString( );
        cfgStream << pSettings->value( strCOMSection + "/stop", QVariant( 0 ) ).toString( );
        cfgStream << pSettings->value( strCOMSection + "/flow", QVariant( 0 ) ).toString( );
    } else {
        pSettings->beginGroup( strCOMSection );
        pSettings->setValue( "name", cfgStream[ 0 ] );
        pSettings->setValue( "baud", cfgStream[ 1 ] );
        pSettings->setValue( "data", cfgStream[ 2 ] );
        pSettings->setValue( "parity", cfgStream[ 3 ] );
        pSettings->setValue( "stop", cfgStream[ 4 ] );
        pSettings->setValue( "flow", cfgStream[ 5 ] );
        pSettings->endGroup( );

        pSettings->sync( );
    }
}

void CWinSerialPort::ConfigPort( )
{
    QStringList cfgStream;
    GetCfg( cfgStream, true );

    pWinSerialPort->setBaudRate( GetBaud( cfgStream[ 1 ].toInt( ) ) );
    pWinSerialPort->setDataBits( GetDataBit( cfgStream[ 2 ].toInt( ) ) );
    pWinSerialPort->setParity( GetParity( cfgStream[ 3 ].toInt( ) ) );
    pWinSerialPort->setStopBits( GetStopBit( cfgStream[ 4 ].toInt( ) ) );
    pWinSerialPort->setFlowControl( GetFlow( cfgStream[ 5 ].toInt( )) );

    pWinSerialPort->setTimeout( 500 );
}

bool CWinSerialPort::IsOpened(  )
{
    return pWinSerialPort->isOpen( );
}

bool CWinSerialPort::OpenPort( )
{
    bool bRet = pWinSerialPort->open( QIODevice::ReadWrite );
    bRet = connect( pWinSerialPort, SIGNAL( readyRead( ) ), pParent, SLOT( DataMayRead( ) ) );

    return bRet;
}

void CWinSerialPort::ClosePort( )
{
    if ( pWinSerialPort->isOpen( ) ) {
        pWinSerialPort->close( );
    }
}

qint64 CWinSerialPort::WriteData( QByteArray& data )
{
    return pWinSerialPort->write( data );
}

