#include "SerialPort/portcmd.h"
#include <QApplication>
#include <QStringList>
#include "Common/commonfunction.h"

#if FALSE
[DownloadCmd]
Success=AA 04 00 45 43 80 00 B6 55
Failed=AA 04 00 45 43 80 01 B7 55
CCDisplay=AA 0B 00 64 00 80 data check 55
OpenGate=AA 03 00 4F 00 can check 55
CloseGate=AA 03 00 43 00 can check 55
DispenserReset=AA 03 00 4D 52 can check 55
DispenserSend=AA 03 00 4D 53 can check 55
DispenserReceive=AA 03 00 4D 47 can check 55
DispenserQuery=AA 03 00 4D 43 can check 55
PlayAudio=AA 05 00 50 cmd can data check 55
LED=AA len 44 00 can data check 55
QuerySense=AA 03 00 51 42 can check 55
QueryButton=AA 03 00 51 43 can check 55
QueryGate=AA 03 00 51 46 can check 55
QueryControler=AA 03 00 51 41 can check 55
[UploadCmd]
Success=AA 04 00 45 43 80 00 B6 55
Failed=AA 04 00 45 43 80 01 B7 55
CardInfo= AA 06 00 4B 00 can data check 55
DispenserReply=AA 0B 00 4D 43 can data check 55
AudioEnd=AA 03 00 50 4F can check 55
BallotSenseVihcleEnter=AA 04 00 54 42 can 01 check 55
BallotSenseVihcleLeave=AA 04 00 54 42 can 00 check 55
ButtonDown=AA 04 00 54 43 can 01 check 55
ButtonUp=AA 04 00 54 43 can 00 check 55
GateSenseVihcleEnter=AA 04 00 54 46 can 01 check 55
GateSenseVihcleLeave=AA 04 00 54 46 can 00 check 55
QuerySense=AA 04 00 51 42 can data check 55
QueryButton=AA 04 00 51 43 can data check 55
QueryGate=AA 04 00 51 46 can data check 55
QueryControler=AA 04 00 51 41 can data check 55
#endif

CPortCmd::CPortCmd(QObject *parent) :
    QObject(parent)
{
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    pCodec = CCommonFunction::GetTextCodec( );

    nLedMsgCounter = pSettings->value( "CommonCfg/LedMsgCounter", 1 ).toInt( );
}

quint8 CPortCmd::CheckSum( QByteArray &byData )
{
    return byData[ byData.count( ) - 2 ];
}

void CPortCmd::GetLedInfo2( LedInfo infoType, QByteArray& vData, QString* pStrParam, ... )
{
    va_list argPtr;
    QString* pTmp = pStrParam;
    va_start( argPtr, pStrParam );
    QString strKey;

    if ( LedCCDisplay == infoType ) {
        strKey = "LedInfo/CCDisplay";
    } else if ( LedSaveCardExit == infoType ) {
        strKey = "LedInfo/SaveCardExit";
    } else if ( LedTimeCardExit == infoType ) {
        strKey = "LedInfo/TimeCardExit";
    }

    QString strInfo = pSettings->value( strKey ).toString( ).trimmed( );

    while ( NULL != pTmp ) {
        // Use pTmp
        strInfo = strInfo.arg( *pTmp );
        pTmp = va_arg( argPtr, QString* );
    }

    va_end( argPtr );

    vData.clear( );
    vData.append( ( char ) 0x1A );
    vData.append( ( char ) 0x1B );
    vData.append( pCodec->fromUnicode( strInfo ) );
    //vData.append( ( char ) 0x01);
    vData.append( ( char ) nLedMsgCounter );
    vData.append( ( char ) 0x1C);
    vData.append( ( char ) 0x1D );
}


void CPortCmd::GetAudioAddr2( AudioAddress audioType, QByteArray* pData, ... )
{
    va_list argPtr;
    QByteArray* pTmp = pData;
    va_start( argPtr, pData );
    QString strKey;
    QString strHex;

    if ( AudioCCDisplay == audioType ) {
        strKey = "AudioAddress/CCDisplay";
    } else if ( AudioSaveCardExit == audioType ) {
        strKey = "AudioAddress/SaveCardExit";
    } else if ( AudioTimeCardExit == audioType ) {
        strKey = "AudioAddress/TimeCardExit";
    }

    //TimeCardExit=84 00 DE 00 %1 0C 01 %2 10 01 DC 00 %3 14 01
    //SaveCardExit=27 00 DE 00 %1 0C 01 %2 10 01 DC 00 %3 14 01 4C 00 %4 14 01
    QString strCmd = pSettings->value( strKey ).toString( ).trimmed( );

    while ( NULL != pTmp ) {
        // Use pTmp
        strHex.clear( );
        ConvertHex2MyString( *pTmp, strHex );
        strCmd = strCmd.arg( strHex );
        pTmp = va_arg( argPtr, QByteArray* );
    }

    va_end( argPtr );

    pData->clear( );
    SplitString( strCmd, *pData );
}

void CPortCmd::GetLedInfo( LedInfo infoType, QByteArray &vData )
{
    bool bVData = false;
    QString strKey = "";

    switch ( infoType ) {
    case LedShuaCard :
        strKey = "LedInfo/ShuaCard";
        break;

    case LedGoodLuck :
        strKey = "LedInfo/GoodLuck";
        break;

    case LedWelcome :
        strKey = "LedInfo/Welcome";
        break;

    case LedFee :
        strKey = "LedInfo/Fee";
        break;

    case LedPass :
        strKey = "LedInfo/PleasePass";
        bVData = true;
        break;

    case LedCardMonth :
        strKey = "LedInfo/CardMonth";
        break;

    case LedCardSave :
        strKey = "LedInfo/CardSave";
        break;

    case LedCardTime :
        strKey = "LedInfo/CardTime";
        break;

    case LedCardInvalid :
        strKey = "LedInfo/CardInvalid";
        break;

    case LedContactAdmin :
        strKey = "LedInfo/ContactAdmin";
        break;

    case LedMonthlyExceed :
        strKey = "LedInfo/MonthlyExceed";
        break;

    case LedMonthlyRemainder :
        strKey = "LedInfo/MonthlyRemainder";
        bVData = true;
        break;

    case LedSaveRemainder :
        strKey = "LedInfo/SaveRemainder";
        bVData = true;
        break;

    case LedSaveRemainderInsufficient :
        strKey = "LedInfo/SaveRemainderInsufficient";
        break;

    case LedTimeRemainder :
        strKey = "LedInfo/TimeRemainder";
        bVData = true;
        break;

    case LedCardLoss :
        strKey = "LedInfo/CardLoss";
        break;

    case LedRenewal :
        strKey = "LedInfo/Renewal";
        break;

    case LedRecharge :
        strKey = "LedInfo/Recharge";
        break;

    case LedCCDisplay :
        break;

    case LedCarInside :
        strKey = "LedInfo/CarInside";
         break;

    case LedCarOutside :
         strKey = "LedInfo/CarOutside";
          break;

    case LedStartup :
         strKey = "LedInfo/Startup";
          break;

    case LedTimeCardEnter :
          strKey = "LedInfo/TimeCardEnter";
          break;

    case LedTimeCardPass :
          strKey = "LedInfo/TimeCardPass";
          bVData = true;
          break;

    case LedExitConfirm :
          strKey = "LedInfo/ExitConfirm";
          break;

    case LedCardNoRight :
          strKey = "LedInfo/CardNoRight";
          break;

    case LedParksFull :
          strKey = "LedInfo/ParksFull";
          break;
    }

    QString strInfo = pSettings->value( strKey, "" ).toString( ).trimmed( );
    if ( strInfo.isEmpty( ) ) {
        return;
    }

    if ( bVData ) {
        QString strVData( vData );
        strInfo = strInfo.arg( strVData );
    }

    vData.clear( );
    vData.append( ( char ) 0x1A );
    vData.append( ( char ) 0x1B );
    vData.append( pCodec->fromUnicode( strInfo ) );
    //vData.append( ( char ) 0x01 );
    vData.append( ( char ) nLedMsgCounter );
    vData.append( ( char ) 0x1C );
    vData.append( ( char ) 0x1D );

}

void CPortCmd::ConvertHex2MyString( QByteArray &vData, QString &strHex )
{
    if ( vData.count( ) < 0 ) {
        return;
    }

    QString strVData = vData.toHex( );
    int nCount = strVData.count( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strHex.append( strVData[ nIndex ] );

        if ( ( nIndex % 2 == 1 ) && ( nIndex < nCount - 2 ) ) {
            strHex.append( ' ' );
        }
    }
}

void CPortCmd::GetAudioAddr( AudioAddress audioType, QByteArray &vData )
{
    bool bVData = false;
    QString strKey = "";

    switch ( audioType ) {
    case AudioShuaCard :
        strKey = "AudioAddress/ShuaCard";
        break;

    case AudioGoodLuck :
        strKey = "AudioAddress/GoodLuck";
        break;

    case AudioWelcome :
        strKey = "AudioAddress/Welcome";
        break;

    case AudioFee :
        strKey = "AudioAddress/Fee";
        break;

    case AudioPass :
        strKey = "AudioAddress/PleasePass";
        bVData = true;
        break;

    case AudioCardInvalid :
        strKey = "AudioAddress/CardInvalid";
        break;

    case AudioContactAdmin :
        strKey = "AudioAddress/ContactAdmin";
        break;

    case AudioMonthlyExceed :
        strKey = "AudioAddress/MonthlyExceed";
        break;

    case AudioMonthlyRemainder :
        strKey = "AudioAddress/MonthlyRemainder";
        bVData = true;
        break;

    case AudioCardMonth :
        strKey = "AudioAddress/CardMonth";
        break;

    case AudioCardSave :
        strKey = "AudioAddress/CardSave";
        break;

    case AudioCardTime :
        strKey = "AudioAddress/CardTime";
        break;

    case AudioSaveRemainder :
        strKey = "AudioAddress/SaveRemainder";
        bVData = true;
        break;

    case AudioSaveRemainderInsufficient :
        strKey = "AudioAddress/SaveRemainderInsufficient";
        break;

    case AudioTimeRemainder :
        strKey = "AudioAddress/TimeRemainder";
        bVData = true;
        break;

    case AudioCardLoss :
        strKey = "AudioAddress/CardLoss";
        break;

    case AudioRenewal :
        strKey = "AudioAddress/Renewal";
        break;

    case AudioRecharge :
        strKey = "AudioAddress/Recharge";
        break;

    case AudioCCDisplay :
        break;

    case AudioCarInside :
        strKey = "AudioAddress/CarInside";
         break;

    case AudioCarOutside :
         strKey = "AudioAddress/CarOutside";
          break;

    case AudioStartup :
         strKey = "AudioAddress/Welcome";
          break;

    case AudioTimeCardEnter :
          strKey = "AudioAddress/TimeCardEnter";
          break;

    case AudioTimeCardPass :
          strKey = "AudioAddress/TimeCardPass";
          bVData = true;
          break;

    case AudioExitConfirm :
          strKey = "AudioAddress/ExitConfirm";
          break;

    case AudioCardNoRight :
          strKey = "AudioAddress/CardNoRight";
          break;

    case AudioParksFull :
          strKey = "AudioAddress/ParksFull";
          break;
    }

    QString strCmd = pSettings->value( strKey, "" ).toString( ).trimmed( );
    if ( strCmd.isEmpty( ) ) {
        return;
    }

    if ( bVData ) {
        QString strVData = "";
        ConvertHex2MyString( vData, strVData );
        strCmd = strCmd.arg( strVData );
    }

    vData.clear( );
    SplitString( strCmd, vData );
}

void CPortCmd::ParseDownCmd( QByteArray& byData, PortDownCmd cmdType, QByteArray& vData )
{
    quint8 nCanAddr = byData[ 5 ];
    byData.clear( );

    QString strCmd;
    QString strKey;
    int nLen = 0;
    int nAudio = 0;
    bool bAudio = false;
    bool bLedInfo = false;
    bool bCC = false;

    switch ( cmdType ) {
    case DownSuccess :
        strKey = "DownloadCmd/Success";
        break;

    case DownFailed :
        strKey = "DownloadCmd/Failed";
        break;

    case DownCCDisplay :
        strKey = "DownloadCmd/CCDisplay";
        bCC = true;
        break;

    case DownOpenGate :
        strKey = "DownloadCmd/OpenGate";
        break;

    case DownCloseGate :
        strKey = "DownloadCmd/CloseGate";
        break;

    case DownDispenserReset :
        strKey = "DownloadCmd/DispenserReset";
        break;

    case DownDispenserSend :
        strKey = "DownloadCmd/DispenserSend";
        break;

    case DownDispenserReceive :
        strKey = "DownloadCmd/DispenserReceive";
        break;

    case DownDispenserQuery :
        strKey = "DownloadCmd/DispenserQuery";
        break;

    case DownPlayAudio :
        strKey = "DownloadCmd/PlayAudio";
        nLen = vData.count( );
        nAudio = nLen / 2;
        bAudio = true;
        break;

    case DownLED :
        strKey = "DownloadCmd/LED";
        nLen = vData.count( );
        bLedInfo = true;
        break;

    case DownQuerySense :
        strKey = "DownloadCmd/QuerySense";
        break;

    case DownQueryButton :
        strKey = "DownloadCmd/QueryButton";
        break;

    case DownQueryGate :
        strKey = "DownloadCmd/QueryGate";
        break;

    case DownQueryControler :
        strKey = "DownloadCmd/QueryControler";
        break;
    }

    strCmd = pSettings->value( strKey ).toString( ).trimmed( );

    QString strCan = QString::number( nCanAddr, 16 );
    if ( bLedInfo || bAudio ) {
        nLen += 3; // Can CheckSum Tail
        QString strLen = QString::number( nLen, 16 );
        QString strAudioLen = QString::number( nAudio, 16 );
        strCmd = bLedInfo ? strCmd.arg( strLen ).arg( strCan ) :
                 strCmd.arg( strLen ).arg( strAudioLen ).arg( strCan ); //  %2 Can %3 Data

    } else if ( !bCC ){
        strCmd = strCmd.arg( strCan ); //  %1 Can %2 Data
    }

    strCmd = strCmd.trimmed( );
    SplitString( strCmd, byData );

    if ( 0 < vData.count( ) ) { // Squeeze No Data
        byData.append( vData );
    }
    //CheckSum( )
    byData.append( 0x01 ); // Checksum
    byData.append( 0x55); // Frame tail
}

void CPortCmd::SplitString( QString &strCmd, QByteArray &byData )
{
    byData.clear( );
    QChar splitter = ' ';
    QStringList lstCmd = strCmd.split( splitter );
    int nCount = lstCmd.count( );

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strCmd = lstCmd[ nIndex ];
        quint8 nCmd = strCmd.toUShort( 0, 16 );
        byData.append( nCmd );
    }
}

CPortCmd::PortUpCmd CPortCmd::ParseUpCmd( QByteArray& byData, quint16 &nDataLen, quint8 &nCanAddr, quint8& nCheckSum, QByteArray& vData ) // QVariant data
{
    PortUpCmd cmd = UpNone;

    if ( byData.count( ) < 8 ) { // Less than 8 bytes
        return cmd;
    }

    quint8 byte0  = byData[ 0 ]; // Frame Header
    quint8 byte1  = byData[ 1 ]; // Data Len
    quint8 byte2  = byData[ 2 ]; // Data Len
    quint8 byte3  = byData[ 3 ]; // Cmd
    quint8 byte4  = byData[ 4 ]; // Cmd
    quint8 byte5  = byData[ 5 ]; // CAN Address
    nCheckSum   = byData[ byData.count( ) - 2 ]; // CheckSum
    quint8 byLast = byData[ byData.count( ) - 1 ]; // Frame Tail

    quint8 cHeader = 0xAA;
    quint8 cTail = 0x55;
    if ( cHeader != byte0 || cTail != byLast ) {
        return cmd;
    }

    nDataLen = byte1 + ( byte2 << 8 );
    nCanAddr = byte5;

    if ( 0x45 == byte3 ) {
        if ( 0x43 == byte4 ) {
            quint8 byte6 = byData[ 6 ];
            if ( 0x00 == byte6 ) {
                cmd = UpSuccess;
            } else if ( 0x01 == byte6 ) {
                cmd = UpFailed;
            }
        } else if ( 0x44 == byte4 ) {
            if ( 0x80 == byte5 ) {
                cmd = UpCCExist;
            } else if ( CCommonFunction::ContainAddress( char ( byte5 ), true ) ) {
                cmd = UpInGateExist;
            } else if ( CCommonFunction::ContainAddress( char ( byte5 ), false ) ) {
                cmd = UpOutGateExist;
            }
        }
    } else if ( 0x4B == byte3 && ( 0x00 == byte4 || 0x01 == byte4 ) ) {
        cmd = UpCardInfo;
        char byte6 = byData[ 6 ];
        char byte7 = byData[ 7 ];
        char byte8 = byData[ 8];
        vData.push_back( byte6 );
        vData.push_back( byte7 );
        vData.push_back( byte8 );
    } else if ( 0x4D == byte3 && 0x43 == byte4 ) {
        cmd = UpDispenserReply;
        char* pData = byData.data( ) + 6;
        vData.append( pData, 8 );
    } else if ( 0x50 == byte3 && 0x4F == byte4 ) {
        cmd = UpAudioEnd;
    } else if ( 0x54 == byte3 ) {
        quint8 byte6 = byData[ 6 ];
        if ( 0x42 == byte4 ) {
            if ( CCommonFunction::ContainAddress( char ( byte5 ), true ) ) {
                if ( 0x00 == byte6 ) { //Èë¿Ú
                    cmd = UpInBallotSenseVehcleLeave;
                } else if ( 0x01 == byte6 ) {
                    cmd = UpInBallotSenseVehcleEnter;
                }
            } else if ( CCommonFunction::ContainAddress( char ( byte5 ), false ) ) {
                if ( 0x00 == byte6 ) { //³ö¿Ú
                    cmd = UpOutBallotSenseVehcleLeave;
                } else if ( 0x01 == byte6 ) {
                    cmd = UpOutBallotSenseVehcleEnter;
                }
            }
        } else if ( 0x43 == byte4 ) {
            if ( 0x00 == byte6 ) {
                cmd = UpButtonUpNoCar;
            } else if ( 0x01 == byte6 ) {
                cmd = UpButtonDownNoCar;
            } else if ( 0x80 == byte6 ) {
                cmd = UpButtonUpCar;
            } else if ( 0x81 == byte6 ) {
                cmd = UpButtonDownCar;
            }
        } else if ( 0x44 == byte4 ) {
            if ( 0x00 == byte6 ) {
                cmd = UpButtonUpCar;
            } else if ( 0x01 == byte6 ) {
                cmd = UpButtonDownCar;
            }
        } else if ( 0x46 == byte4 ) {
            if ( CCommonFunction::ContainAddress( char ( byte5 ), true ) ) {
                if ( 0x00 == byte6 ) { //Èë¿Ú
                    cmd = UpInGateSenseVehcleLeave;
                } else if ( 0x01 == byte6 ) {
                    cmd = UpInGateSenseVehcleEnter;
                }
            } else if ( CCommonFunction::ContainAddress( char ( byte5 ), false ) ) {
                if ( 0x00 == byte6 ) { //³ö¿Ú
                    cmd = UpOutGateSenseVehcleLeave;
                } else if ( 0x01 == byte6 ) {
                    cmd = UpOutGateSenseVehcleEnter;
                }
            }
        }
    } else if ( 0x51 == byte3 ) {
        quint8 byte6 = byData[ 6 ];
        if ( 0x42 == byte4 ) {
            if ( 0x00 == byte6 ) {
                cmd = UpQuerySenseCar;
            } else if ( 0x01 == byte6 ) {
                cmd = UpQuerySenseNoCar;
            }
        } else if ( 0x43 == byte4 ) {
            if ( 0x00 == byte6 ) {
                cmd = UpQueryButtonOpen;
            } else if ( 0x01 == byte6 ) {
                cmd = UpQueryButtonClose;
            }
        } else if ( 0x46 == byte4 ) {
            if ( 0x00 == byte6 ) {
                cmd = UpQueryGateCar;
            } else if ( 0x01 == byte6 ) {
                cmd = UpQueryGateNoCar;
            }
        } else if ( 0x41 == byte4 ) { // Gate Controller State
            cmd = UpQueryControler;
        }
    }

    return cmd;
}

void CPortCmd::GetAudioDigital( QByteArray& vData, quint8 nDigital )
{
    vData.clear( );

    if ( nDigital < 0 || nDigital > 9 ) { // [ 0 .. 9 ]
        return;
    }
    bool bGE5 = ( 0x05 <= nDigital );
    quint8 nBase = ( bGE5 ? 0x28 : 0x1F );
    if ( bGE5 ) {
        nDigital -= 5;
    }
    nDigital *= 2;
    nDigital += nBase;
    vData.append( nDigital );
    vData.append( ( char ) 0x01 );
}

void CPortCmd::GetAudioChineseChar( QByteArray& vData, quint8 nIndex )
{
    vData.clear( );
    // Ê®°ÙÇ§ÍòÒÚ [ 0..4 ]
    if ( 0 > nIndex || nIndex > 4 ) {
        return;
    }

    vData.append( 0x32 + nIndex * 2 );
    vData.append( ( char ) 0x01 );
}

void CPortCmd::GetAudioLatinChar( QByteArray& vData, QString& strChar )
{
    vData.clear( );

    if ( strChar.count( ) != 1 || !strChar[ 0 ].isLetter( ) ) { // [ A .. Z / a .. z]
        return;
    }
    strChar.toUpper( );
    char cValue = strChar[ 0 ].toAscii( );

    if ( 'A' <= cValue && cValue <= 'H' ) { //[ A.. H ]
        cValue = ( 'A' + ( cValue - 'A' ) * 2 );
    } else if ( 'I' <= cValue && cValue <= 'W' ) { // [ I.. W ]
        cValue = ( 'I' + ( cValue - 'I' ) * 2 );
    } else if ( 'X' <= cValue && cValue <= 'Z' ) { // [ X.. Z ]
        cValue = ( 'X' + ( cValue - 'X' ) * 2 );
    }

    vData.append( cValue );
    vData.append( ( char ) 0x01 );
}

void CPortCmd::GetAudioAbbreviation( QByteArray& vData, QString& strAbbrev )
{
    vData.clear( );
    static QString strAbbreviation = "´¨¶õ¸Ê¸Ó¹ó¹ðºÚ»¦¼ª¼½½ò½ú¾©ÁÉÂ³ÃÉÃöÄþÇàÇíÉÂËÕÍîÏæÐÂÓåÔ¥ÔÁÔÆ²ØÕã¼×ÒÒ±û¼º¸ýÐÁÈÉÒú³½ÊùÎçÎ´ÉêÏû±ßÍ¨É­½ð¾¯µç";
    qint32 nIndex = strAbbreviation.indexOf( strAbbrev );
    if ( -1 == nIndex ) {
        return;
    }

    quint8 cValue = 0x00;

    if ( 0 <= nIndex && nIndex <= 6 ) {
        cValue = 0x73 + nIndex * 2;
    } else if ( 7 == nIndex ) {
        cValue = 0x80;
    } else if ( 8 <= nIndex && nIndex <= 50 ) {
        cValue = 0x83 + nIndex * 2;
    }

    vData.append( cValue );
    vData.append( ( char ) 0x01 );
}
