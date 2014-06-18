#include "cdataparser.h"
#include "../SerialPort/processdata.h"
#include "../SerialPort/writethread.h"
#include <QApplication>

extern CWriteThread g_serialThread;

CDataParser::CDataParser(QObject *parent) :
    QObject(parent)
{
    pWineSerialPort = new  CWinSerialPort( "WineSerialPort", this  );
    pSerialPort = new  CWinSerialPort( "SerialPort", this  );

    ControlSerialPort( pSerialPort, true );
    ControlSerialPort( pWineSerialPort, true );

    g_serialThread.SetSerialPort( pSerialPort );
    g_serialThread.SetSerialPort( pWineSerialPort, 1 );
}

void CDataParser::DataMayRead()
{
    Sleep( 4 );

    int nMinLen = 8;
    Win_QextSerialPort& winSerial = *( Win_QextSerialPort* ) sender( );
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

            ParseSerialData( bySingle );
        } while ( nMinLen <= byData.count( ) );
}

void CDataParser::ParseSerialData( QByteArray &byData )
{
    quint8 nCanAddr = 0;
    int nCmd = ParseUpCmd( byData, nCanAddr );
    qDebug( ) << "ParseSerialData( ) " << nCmd << endl;

    switch ( nCmd ) {
    case 1 : // UpInBallotSenseVehcleLeave
        CreateReponse( Protocol::ResponseBallotSenseState, 2, nCanAddr );
        break;

    case 2 : // UpInBallotSenseVehcleEnter
        CreateReponse( Protocol::ResponseBallotSenseState, 1, nCanAddr );
        break;

    case 3 : // UpOutBallotSenseVehcleLeave
        CreateReponse( Protocol::ResponseBallotSenseState, 2, nCanAddr );
        break;

    case 4 : // UpOutBallotSenseVehcleEnter
        CreateReponse( Protocol::ResponseBallotSenseState, 1, nCanAddr );
        break;

    case 5 : // UpButtonUpNoCar
        CreateReponse( Protocol::ResponseInfraredState, 2, nCanAddr );
        break;

    case 6 : // UpButtonDownNoCar
        CreateReponse( Protocol::ResponseInfraredState, 1, nCanAddr );
        break;

    case 7 : // UpButtonUpCar
        //CreateReponse( Protocol::ResponseBallotSenseState, 1, nCanAddr );
        break;

    case 8 : // UpButtonDownCar
        break;

    case 9 : // UpButtonUpCar
        break;

    case 10 : // UpButtonDownCar
        break;

    case 11 : // UpInGateSenseVehcleLeave
        CreateReponse( Protocol::ResponseGateSenseState, 2, nCanAddr );
        break;

    case 12 : // UpInGateSenseVehcleEnter
        CreateReponse( Protocol::ResponseGateSenseState, 1, nCanAddr );
        break;

    case 13 : // UpOutGateSenseVehcleLeave
        CreateReponse( Protocol::ResponseGateSenseState, 2, nCanAddr );
        break;

    case 14 : // UpOutGateSenseVehcleEnter
        CreateReponse( Protocol::ResponseGateSenseState, 1, nCanAddr );
        break;

    case 15 : // UpQuerySenseCar
        CreateReponse( Protocol::ResponseGateSenseState, 3, nCanAddr );
        break;

    case 16 : // UpQuerySenseNoCar
        CreateReponse( Protocol::ResponseBallotSenseState, 0, nCanAddr );
        break;

    case 17 : // UpQueryButtonOpen
        CreateReponse( Protocol::ResponseInfraredState, 3, nCanAddr );
        break;

    case 18 : // UpQueryButtonClose
        CreateReponse( Protocol::ResponseInfraredState, 1, nCanAddr );
        break;

    case 19 : // UpQueryGateCar
        CreateReponse( Protocol::ResponseGateSenseState, 0, nCanAddr );
        break;

    case 20 : // UpQueryGateNoCar
        CreateReponse( Protocol::ResponseGateSenseState, 0, nCanAddr );
        break;

    case 21 : // UpQueryControler
        CreateReponse( Protocol::ResponseActiveSend, byData[ 6 ], nCanAddr );
        break;
    }
}

int CDataParser::ParseUpCmd( QByteArray& byData,quint8 &nCanAddr ) // QVariant data
{
    int nCmd = 0;

    if ( byData.count( ) < 8 ) { // Less than 8 bytes
        return nCmd;
    }

    quint8 byte0  = byData[ 0 ]; // Frame Header
    //quint8 byte1  = byData[ 1 ]; // Data Len
    //quint8 byte2  = byData[ 2 ]; // Data Len
    quint8 byte3  = byData[ 3 ]; // Cmd
    quint8 byte4  = byData[ 4 ]; // Cmd
    quint8 byte5  = byData[ 5 ]; // CAN Address
    //nCheckSum   = byData[ byData.count( ) - 2 ]; // CheckSum
    quint8 byLast = byData[ byData.count( ) - 1 ]; // Frame Tail

    quint8 cHeader = 0xAA;
    quint8 cTail = 0x55;
    if ( cHeader != byte0 || cTail != byLast ) {
        return nCmd;
    }

    //nDataLen = byte1 + ( byte2 << 8 );
    nCanAddr = byte5;
    bool bEnter = ( 0 != nCanAddr % 2 );

    if ( 0x54 == byte3 ) {
            quint8 byte6 = byData[ 6 ];
            if ( 0x42 == byte4 ) {
                if ( bEnter ) {
                    if ( 0x00 == byte6 ) { //入口
                        nCmd = 1;//UpInBallotSenseVehcleLeave;
                    } else if ( 0x01 == byte6 ) {
                        nCmd = 2;//UpInBallotSenseVehcleEnter;
                    }
                } else  {
                    if ( 0x00 == byte6 ) { //出口
                        nCmd = 3;//UpOutBallotSenseVehcleLeave;
                    } else if ( 0x01 == byte6 ) {
                        nCmd = 4;//UpOutBallotSenseVehcleEnter;
                    }
                }
            } else if ( 0x43 == byte4 ) {
                if ( 0x00 == byte6 ) {
                    nCmd = 5;//UpButtonUpNoCar;
                } else if ( 0x01 == byte6 ) {
                    nCmd = 6;//UpButtonDownNoCar;
                } else if ( 0x80 == byte6 ) {
                    nCmd = 7;//UpButtonUpCar;
                } else if ( 0x81 == byte6 ) {
                    nCmd = 8;//UpButtonDownCar;
                }
            } else if ( 0x44 == byte4 ) {
                if ( 0x00 == byte6 ) {
                    nCmd = 9;//UpButtonUpCar;
                } else if ( 0x01 == byte6 ) {
                    nCmd = 10;//UpButtonDownCar;
                }
            } else if ( 0x46 == byte4 ) {
                if ( bEnter ) {
                    if ( 0x00 == byte6 ) { //入口
                        nCmd = 11;//UpInGateSenseVehcleLeave;
                    } else if ( 0x01 == byte6 ) {
                        nCmd = 12;//UpInGateSenseVehcleEnter;
                    }
                } else {
                    if ( 0x00 == byte6 ) { //出口
                        nCmd = 13;//UpOutGateSenseVehcleLeave;
                    } else if ( 0x01 == byte6 ) {
                        nCmd = 14;//UpOutGateSenseVehcleEnter;
                    }
                }
            }
        } else if ( 0x51 == byte3 ) {
        quint8 byte6 = byData[ 6 ];
        if ( 0x42 == byte4 ) {
            if ( 0x00 == byte6 ) {
                nCmd = 15;//UpQuerySenseCar;
            } else if ( 0x01 == byte6 ) {
                nCmd = 16;//UpQuerySenseNoCar;
            }
        } else if ( 0x43 == byte4 ) {
            if ( 0x00 == byte6 ) {
                nCmd = 17;//UpQueryButtonOpen;
            } else if ( 0x01 == byte6 ) {
                nCmd = 18;//UpQueryButtonClose;
            }
        } else if ( 0x46 == byte4 ) {
            if ( 0x00 == byte6 ) {
                nCmd = 19;//UpQueryGateCar;
            } else if ( 0x01 == byte6 ) {
                nCmd = 20;//UpQueryGateNoCar;
            }
        } else if ( 0x41 == byte4 ) { // Gate Controller State
            nCmd = 21;//UpQueryControler;
        }
    }

    return nCmd;
}

void CDataParser::ControlSerialPort( CWinSerialPort* pSerial, bool bOpen )
{
    if ( bOpen ) {
        if ( pSerial->IsOpened( ) ) {
            return;
        }

        pSerial->SetPortName( );
        pSerial->SetQueryMode( QextSerialBase::EventDriven );
        pSerial->OpenPort( );
        pSerial->ConfigPort( );
    } else if ( pSerial->IsOpened( ) ) {
        pSerial->ClosePort( );
    }
}

void CDataParser::ProcessBallotSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "A地感地址：%1\nA地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );
}

void CDataParser::ProcessGateSenseResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "B地感地址：%1\nB地感状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );
}

void CDataParser::ProcessInfraredResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "红外地址：%1\n红外状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );
}

void CDataParser::ProcessActiveSendResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    if ( 2 != byBody.length( ) ) {
        return;
    }

    QString strMsg;
    quint8 nAddress = byBody.at( 0 );
    quint8 nState = byBody.at( 1 );

    strMsg = QString( "地址：%1\n状态：%2" ).arg(
                        QString::number( nAddress ),
                        QString::number( nState ) );
}

void CDataParser::ProcessPlateResponse( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );

    qint32 nIndex = 0;
    quint8 nAddress = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    QByteArray byDateTime = byBody.mid( nIndex, Protocol::nDateTimeLength );
    QString strDateTime ( byDateTime );

    nIndex += Protocol::nDateTimeLength;
    quint8 nConfidence = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint8 nPlateByteCount = byBody.at( nIndex );

    nIndex += sizeof ( quint8 );
    quint32 nPictureByteCount = *( quint32*  ) ( byBody.data( ) + nIndex );
    nPictureByteCount = ntohl( nPictureByteCount );

    nIndex += sizeof ( quint32 );
    QByteArray byPlate = byBody.mid( nIndex, nPlateByteCount );
    QString strPlate( byPlate );

    QString strMsg;
    strMsg = QString( "车牌地址：%1\n获取时间：%2\n可信度：%3\n车牌：%4" ).arg(
                        QString::number( nAddress ),
                        strDateTime,
                        QString::number( nConfidence ),
                        strPlate );

    nIndex += nPlateByteCount;
    QByteArray byPicture = byBody.mid( nIndex, nPictureByteCount );
    QFile file;
    file.setFileName( "tmp.jpg" );
    bool bRet = file.open( QIODevice::ReadWrite | QIODevice::Truncate );
    if ( !bRet ) {
        return;
    }

    file.write( byPicture );
    file.close( );
}

void CDataParser::ProcessBallotSenseRequest( QByteArray& byStream )
{
    //查询票箱地感状态	AA	03 00	51 42	xx	无 	xx	55

    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = byBody.at( 0 );

    char cCmd [ ] = { 0xAA, 0x03, 0x00, 0x51, 0x42, nAddress + 1, 0x00, 0x55 };

    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

void CDataParser::TimerActiveSend( quint16 nAddress )
{
    char cCmd [ ] = { 0xAA, 0x03, 0x00, 0x51, 0x41, nAddress, 0x00, 0x55 };
    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

void CDataParser::ProcessActiveSendRequest( QByteArray& byStream )
{
    //查询道闸控制器状态	AA	03 00	51 41	xx	无	xx	55

    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = byBody.at( 0 );

    char cCmd [ ] = { 0xAA, 0x03, 0x00, 0x51, 0x41, nAddress + 1, 0x00, 0x55 };

    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

void CDataParser::ProcessGateSenseRequest( QByteArray& byStream )
{
    //查询道闸地感状态	AA	03 00	51 46	xx	无	xx	55

    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = byBody.at( 0 );

    char cCmd [ ] = { 0xAA, 0x03, 0x00, 0x51, 0x46, nAddress + 1, 0x00, 0x55 };

    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

void CDataParser::ProcessInfraredRequest( QByteArray& byStream )
{
    //查询取卡按钮状态	AA	03 00	51 43	xx	无	xx	55

    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = byBody.at( 0 );

    char cCmd [ ] = { 0xAA, 0x03, 0x00, 0x51, 0x43, nAddress + 1, 0x00, 0x55 };

    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

QByteArray CDataParser::GetToken( QByteArray& byStream )
{
    return byStream.mid( 0, Protocol::nTokenLength );
}

quint8 CDataParser::GetMessageType( QByteArray& byStream )
{
    return ( quint8 ) byStream.at( Protocol::nTokenLength );
}

QByteArray CDataParser::GetBody( QByteArray &byStream )
{
    return byStream.right( byStream.length( ) - Protocol::nHeadLength );
}

quint32 CDataParser::GetStreamLength( QByteArray& byStream )
{
    QByteArray byLen = byStream.mid( Protocol::nTokenLength + sizeof ( quint8 ), sizeof( quint32 ) );
    quint32* pLen = ( quint32* ) byLen.data( );

    return ntohl( *pLen );
}

void CDataParser::ProcessLedRequest( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = ( quint8 ) byBody.at( 0 );
    QByteArray byData = byBody.right( byBody.length( ) - 1 );
    QString strContent( byData );

    //F5 C2 FF 01 0B 08 FF FF 26 4E 30 34 26 48 30 34 24 31
    QByteArray byTmp;
    char cCmd [ ] = { 0xF5, 0xC2, 0xFF, 0x01, 0x0B, 0x08, 0xFF, 0xFF, 0x26,
                                 0x4E, 0x30, 0x34, 0x26, 0x48, 0x30, 0x34, 0x24, 0x31 };
    byTmp.append( cCmd, sizeof ( cCmd ) );
    byTmp.append( CCommonFunction::GetTextCodec( )->fromUnicode( strContent ) );
    byTmp.append( char ( 0x1A ) );

    WriteSerial( pWineSerialPort, byTmp.data( ), byTmp.length( ) );
}

void CDataParser::ProcessTrafficLightsRequest( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 2 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = ( quint8 ) byBody.at( 0 );
    quint8 nOperation = ( quint8 ) byBody.at( 1 );
    quint8 nTail;

    //地址码01
    //灯关闭：FA 2C 01 00 27
    //红灯亮：FA 2C 01 01 28
    //绿灯亮：FA 2C 01 02 29
    //==================================
    //地址码02
    //灯关闭：FA 2C 02 00 28
    //红灯亮：FA 2C 02 01 29
    //绿灯亮：FA 2C 02 02 2A

    switch ( nOperation  ) {
    case 0 :
        nOperation = 0x01;
        nTail = 0x28;
        break;
    case 1 :
        nOperation = 0x02;
        nTail = 0x29;
        break;

    case 2 :
        nOperation = 0x00;
        nTail = 0x27;
        break;
    }

    char cCmd [ ] = { 0xFA, 0x2C, nAddress + 1, nOperation, nAddress ?  nTail + 1 : nTail };

    WriteSerial( pWineSerialPort, cCmd, sizeof ( cCmd ) ); // pWineSerialPort
}

void CDataParser::WriteSerial( CWinSerialPort *pSerial, char cCmd[ ], int nCmdLen )
{
    ControlSerialPort( pSerial, true );

    QByteArray byCmd;
    byCmd.append( cCmd, nCmdLen );

    CSerialEvent* pEvent = new CSerialEvent( QEvent::User );
    bool bWineSerial = ( pSerial == pWineSerialPort );
    pEvent->SetSerialData( byCmd,  bWineSerial ? 1 : 0 );
    QApplication::postEvent( &g_serialThread, pEvent );

    return;

    int nCount = byCmd.count( );
    Win_QextSerialPort& rawSerial = pSerial->GetRawSerialPort( );

    if ( rawSerial.isWritable( ) ) {
        bool bRet = ( nCount == rawSerial.write( byCmd ) );
        rawSerial.flush( );
#ifndef QT_NO_DEBUG
        QString strData( byCmd.toHex( ) );
        qDebug( ) << "Write Serial Port Cmd : " << strData << endl;
#endif

       Sleep( 300 );
    }
}

void CDataParser::ProcessGateRequest( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 2 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = ( quint8 ) byBody.at( 0 );
    quint8 nOperation = ( quint8 ) byBody.at( 1 );

    bool bOpen = ( 0 == nOperation );
    char cCan = nAddress + 1;
    char cCmd [ ] = { 0xAA, 0x03, 0x00, bOpen ? 0x4F : 0x43, 0x00, cCan, 0x00, 0x55 };
    //OpenGate=AA 03 00 4F 00 %1
    //CloseGate=AA 03 00 43 00 %1

    WriteSerial( pSerialPort, cCmd, sizeof ( cCmd ) );
}

void CDataParser::ProcessPlateRequest( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 1 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = byBody.at( 0 );
}

void CDataParser::ProcessVehicleUpDwonWeigh( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 2 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = ( quint8 ) byBody.at( 0 );
    quint8 nSate = ( quint8 ) byBody.at( 1 ); // Up Down
}

void CDataParser::ProcessSavePlateRequest( QByteArray& byStream )
{
    QByteArray byBody = GetBody( byStream );
    if ( 2 > byBody.length( ) ) {
        return;
    }
    quint8 nAddress = ( quint8 ) byBody.at( 0 );
    quint8 nOperation = ( quint8 ) byBody.at( 1 );
}

void CDataParser::CreateBallotSenseReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;

    nTcpStreamLength = htonl( nTcpStreamLength );
    byResponse.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    byResponse.append( nAddress );
    byResponse.append( nState );
}

void CDataParser::CreateGateSenseReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;

    nTcpStreamLength = htonl( nTcpStreamLength );
    byResponse.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    byResponse.append( nAddress );
    byResponse.append( nState );
}

void CDataParser::CreateInfraredReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;

    nTcpStreamLength = htonl( nTcpStreamLength );
    byResponse.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    byResponse.append( nAddress ); // 1 / 2
    byResponse.append( nState );

    if ( nState ) {
        CaptureImage( nAddress - 1 );
    }
}

void CDataParser::CaptureImage( quint8 nChannel )
{
    emit Capture( nChannel );
}

void CDataParser::CreatePlateReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;

    nTcpStreamLength = htonl( nTcpStreamLength );
    byResponse.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    byResponse.append( nAddress );
    byResponse.append( nState );
}

void CDataParser::CreateActiveSendReponse( QByteArray& byResponse, quint8 nState, quint8 nAddress )
{
    quint32 nTcpStreamLength = Protocol::nHeadLength + sizeof ( quint8 ) * 2;

    nTcpStreamLength = htonl( nTcpStreamLength );
    byResponse.append( ( const char* ) &nTcpStreamLength, sizeof ( quint32 ) );
    byResponse.append( nAddress );
    byResponse.append( nState );
}

void CDataParser::CreateReponse( Protocol::ResponseType respType, quint8 nState, quint8 nAddress )
{
    QByteArray byResponse;
    byResponse.append( Protocol::byToken );
    byResponse.append( ( char ) respType );

    switch ( respType ) {
    case Protocol::ResponseBallotSenseState :
        CreateBallotSenseReponse( byResponse, nState, nAddress );
        break;

    case Protocol::ResponseGateSenseState :
        CreateGateSenseReponse( byResponse, nState, nAddress );
        break;

    case Protocol::ResponseInfraredState :
        CreateInfraredReponse( byResponse, nState, nAddress );
        break;

    case Protocol::ResponsePlateData :
        CreatePlateReponse( byResponse, nState, nAddress );
        break;

    case Protocol::ResponseActiveSend :
        CreateActiveSendReponse( byResponse, nState, nAddress );
        break;
    }

    emit Response( byResponse );
}

void CDataParser::ProcessResponse( QByteArray &byStream )
{
    QByteArray byToken = GetToken( byStream );
    if ( byToken != Protocol::byToken ) {
        return;
    }

    Protocol::RequestType nMessageType = ( Protocol::RequestType ) GetMessageType( byStream );

    switch ( nMessageType ) {
    case Protocol::ResponseBallotSenseState :
        ProcessBallotSenseResponse( byStream );
        break;

    case Protocol::ResponseGateSenseState :
        ProcessGateSenseResponse( byStream );
        break;

    case Protocol::ResponseInfraredState :
        ProcessInfraredResponse( byStream );
        break;

    case Protocol::ResponsePlateData :
        ProcessPlateResponse( byStream );
        break;

    case Protocol::ResponseActiveSend :
        ProcessActiveSendResponse( byStream );
        break;
    }
}

void CDataParser::Parse( QByteArray &byStream )
{
    Protocol::RequestType nMessageType = ( Protocol::RequestType ) GetMessageType( byStream );

    switch ( nMessageType ) {
    case Protocol::RequestQueryBallotSenseState :
        ProcessBallotSenseRequest( byStream );
        break;

    case Protocol::RequestQueryGateSenseState :
        ProcessGateSenseRequest( byStream );
        break;

    case Protocol::RequestQueryInfraredState :
        ProcessInfraredRequest( byStream );
        break;

    case Protocol::RequestControlLED :
        ProcessLedRequest( byStream );
        break;

    case Protocol::RequestControlTrafficLights :
        ProcessTrafficLightsRequest( byStream );
        break;

    case Protocol::RequestControlGate :
        ProcessGateRequest( byStream );
        break;

    case Protocol::RequestQueryPlateData :
        ProcessPlateRequest( byStream );
        break;

    case Protocol::RequestVehicleUpDwonWeigh :
        ProcessVehicleUpDwonWeigh( byStream );
        break;

    case Protocol::RequestSavePlate :
        ProcessSavePlateRequest( byStream );
        break;

    case Protocol::RequestActiveSend :
        ProcessActiveSendRequest( byStream );
        break;
    }
}
