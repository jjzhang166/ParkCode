#include "qdbdataprocess.h"
#include "Constant.h"
#include "../NetworkLibrary/qthreadevent.h"
#include "../NetworkLibrary/networkcontroller.h"

QDbDataProcess::QDbDataProcess( QObject *parent ) :
    QObject( parent )
{
    pDatabase = NULL;
    pPeerSocket = NULL;
    pNetController = NULL;
    pConfig = CDbConfigurator::GetConfigurator( );
}

void QDbDataProcess::SetNetController( QObject *pController )
{
    pNetController = pController;
}

void QDbDataProcess::SetPeerSocket( QTcpSocket *pSocket )
{
    pPeerSocket = pSocket;
    parserJson2Sql.SetSocket( pSocket );
}

void QDbDataProcess::SetDatabase( CMySqlDatabase *pDb )
{
    pDatabase = pDb;
}

void QDbDataProcess::SendLog( QString &strLog, bool bStatic )
{
    QString strTmp = QDateTime::currentDateTime().toString( "【yyyy-MM-dd hh:mm:ss】%1" ).arg( strLog ) ;
    emit Log( strTmp, bStatic );
}

void QDbDataProcess::PostData2PeerThread( QTcpSocket *pSocket, QByteArray &byData, int nPkType )
{
    QThreadEvent* pEvent = QThreadEvent::CreateThreadEvent( QThreadEvent::ThreadSocket,
                                                            QThreadEvent::EventServerSendData );

    QString strLog( byData );
    strLog = objectName( ) + ":" + strLog;
    SendLog( strLog, false );

    //byData.append( "\r\n" );
    byData.append( char ( '\r' ) );
    byData.append( char ( '\n' ) );

    pEvent->SetPeerSocket( pSocket );
    pEvent->SetByteArray( byData );
    pEvent->SetPackageType( nPkType );
    qApp->postEvent( pSocket->thread( ), pEvent );
}

QString QDbDataProcess::GetDateTime( )
{
    return QDateTime::currentDateTime( ).toString( "yyyy-MM-dd HH:mm:ss" );
}

void QDbDataProcess::DetectorID2LocationID( QString& strDetectorID )
{
    pConfig->DetectorID2LocationID( strDetectorID );
}

void QDbDataProcess::ProcessComPortData( qint32 nPackageType, QByteArray &byData, QString& strParkID )
{
    // 24 30 30 31 2C 30 30 2C 30 36 2C 30 0d 0a 00 Anlog Result
    // 510107+StreetID(ReceiverID) 四川省成都市武侯区
    //ParkID-->ReceiverID-->DetectorID
    //qDebug( ) << Q_FUNC_INFO << QString( byData ) << endl;

    // 001,02,01,0 // ReceiverID, ChannelID, DetectorID, State
    QString strData( byData );
    QStringList lstData = strData.split( ',' );
    nPackageType = Constant::TypeInOutRecordInfo;

    if ( lstData.length( ) < 4 || "2" == lstData.at( 3 ) ) {
        return;
    }

    char nFlag = lstData.at( 3 ).toShort( );

    if ( 0 > nFlag || 1 < nFlag ) {
        return;
    }

    QString strDateTime = GetDateTime( );
    QString strDetectorID = QString( "%1" ).arg( lstData.at( 2 ).toShort( ), 3, 10, QChar( '0' ) );
    DetectorID2LocationID( strDetectorID );
    QString strXml = Constant::SpXmlPattern.strXmlSensorRecord.arg(
                    strParkID, lstData.at( 0 ), strDetectorID, strDateTime );

    byData.clear( );
    byData.append( strXml );

    JsonStruct::JsonHead sHead;
    sHead.strSpName = Constant::SpName.strSpSensorRecord;
    sHead.nFlag = nFlag;
    sHead.sValues.strUserID = "-1";
    sHead.sValues.strClientID = "-1";
    sHead.sValues.strTypeCode = Constant::TypeCode.strCodeSensorData;

    nPackageType = Constant::TypeSensorInfo;
    CallSP( byData, sHead, nPackageType );
}

void QDbDataProcess::CallSP( QByteArray &byData, JsonStruct::JsonHead &sHead, int nPkType )
{
    bool bRet = pDatabase->ExcutePreparedStmt( byData, sHead.nFlag, sHead.strSpName );
    bool bMulticast = false;
    bool bUnicast = false;
    bool bFeedback = false;
    QString strMessage = "{\"Message\":\"%4\"}";
    JsonStruct::JsonHead sFeedbackHead = sHead;
    bool bSpSuccess = ( -1 != sHead.nFlag );
    bool bFromDbMsg = false;

    qDebug( ) << "Sp Data " << QString( byData ) << endl;

    if ( bSpSuccess ) {
        switch ( nPkType ) {
        case Constant::TypeGroupInfo :
            bMulticast = false;
            bFeedback = true;
            bUnicast = true;
            break;

        case Constant::TypeUserInfo :
            bMulticast = false;
            bFeedback = true;
            bUnicast = true;

            if ( Constant::TypeCode.strCodeUserSelect == sHead.sValues.strTypeCode ) {

            } else if ( Constant::TypeCode.strCodeUserUpdate == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
                bUnicast = false;
            } else if ( Constant::TypeCode.strCodeUserLogin == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
                bUnicast = false;
            } else if ( Constant::TypeCode.strCodeUserLogout == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
                bUnicast = false;
            } else if ( Constant::TypeCode.strCodeUserFee == sHead.sValues.strTypeCode ) {

            }
            break;

        case Constant::TypeInOutRecordInfo :
            bMulticast = true;
            bFeedback = true;
            bUnicast = false;
            if ( Constant::TypeCode.strCodeTabletNormalData == sHead.sValues.strTypeCode ) {
                sHead.sValues.strTypeCode = Constant::TypeCode.strCodeRemoveRecord;
            } else if ( Constant::TypeCode.strCodeTabletManualData == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
                //bMulticast = false;
                sHead.sValues.strTypeCode = Constant::TypeCode.strCodeRemoveRecord;
            } else if ( Constant::TypeCode.strCodeUnhandledSensorData == sHead.sValues.strTypeCode ) {
                bMulticast = false;
                bUnicast = true;
            } else if ( Constant::TypeCode.strCodeTabletQueryLocationData == sHead.sValues.strTypeCode ) {
                bMulticast = false;
                bUnicast = true;
            } else if ( Constant::TypeCode.strCodeTabletQueryImageData == sHead.sValues.strTypeCode ) {
                bMulticast = false;
                bUnicast = true;
            } else if ( Constant::TypeCode.strCodeTabletQueryReprotData == sHead.sValues.strTypeCode ) {
                bMulticast = false;
                bUnicast = true;
            } else if ( Constant::TypeCode.strCodeTabletVehicleShiftRequest == sHead.sValues.strTypeCode ) {
                bMulticast = true;
                bUnicast = false;
            } else if ( Constant::TypeCode.strCodeTabletUploadInOutRecord == sHead.sValues.strTypeCode ) {
                bMulticast = false;
                bUnicast = false;
                bFeedback = true;
            }
            break;

        case Constant::TypeSystemInfo :
            bMulticast = false;
            bFeedback = true;
            bUnicast = false;

            if ( Constant::TypeCode.strCodeDeviceRegister == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
            } else if ( Constant::TypeCode.strCodeDeviceUnregister == sHead.sValues.strTypeCode ) {
                bFromDbMsg = true;
            } else if ( Constant::TypeCode.strCodeConfigInfo == sHead.sValues.strTypeCode ) {
                bUnicast = true;
            }
            break;

        case Constant::TypeDataInfo :
            bMulticast = false;
            bFeedback = false;
            bUnicast = true;
            break;

        case Constant::TypeSensorInfo :
            bMulticast = ( 0 == sHead.nFlag || 1 == sHead.nFlag );
            bUnicast = false;
            bFeedback = false;
            break;
        case Constant::TypeFeeInfo :
            bMulticast = false;
            bFeedback = false;
            bUnicast = true;
            break;
        }
    } else {
        bFeedback = true;
    }

    if ( !bRet ) { // Failed
        if ( bFeedback ) { // Unicast
            strMessage = strMessage.arg( "数据库操作失败。" );
            FeedbackData( sHead, strMessage, nPkType, bRet );
        }

        return;
    }

    if ( bMulticast || bUnicast ) {
        QJsonObject objJson;

        objJson.insert( sHead.sKeys.strClientID, QJsonValue( sHead.sValues.strClientID ) );
        objJson.insert( sHead.sKeys.strTypeCode, QJsonValue( sHead.sValues.strTypeCode ) );
        objJson.insert( sHead.sKeys.strUserID, QJsonValue( sHead.sValues.strUserID ) );
        objJson.insert( sHead.sKeys.strStateCode, QJsonValue( QString::number( ( qint32 ) bSpSuccess ) ) );

        QJsonParseError jsonError;
        QJsonObject objContentJson = QJsonDocument::fromJson( byData, &jsonError ).object( );
        objJson.insert( sHead.sKeys.strData, QJsonValue( objContentJson ) );

        if ( QJsonParseError::NoError != jsonError.error ) {
            qDebug( ) << Q_FUNC_INFO << QString( byData ) << endl << jsonError.errorString( ) << endl;
        }

        QJsonDocument docJson( objJson );
        byData = docJson.toJson( ); // UTF-8

        if ( bUnicast ) {
            PostData2PeerThread( pPeerSocket, byData, nPkType );
        }

        if ( bMulticast && NULL != pNetController ) {
            // After a tablet does process a record,
            // server does notify tablets
            NetworkController* pController = ( NetworkController* ) pNetController;

            byData.append( char ( '\r' ) );
            byData.append( char ( '\n' ) );
            pController->MulticastData( byData, nPkType );
        }
    }

    if ( bFeedback ) {
        if ( bSpSuccess ) {
            strMessage = bFromDbMsg ? QString( byData ) : strMessage.arg( "此操作成功。" );
        } else {
            strMessage = QString( byData );
        }

        FeedbackData( sFeedbackHead, strMessage, nPkType, bSpSuccess );
    }
}

// Sucess Failed DataReturned
void QDbDataProcess::FeedbackData( JsonStruct::JsonHead &sHead,
                                     QString& strMessage,
                                     qint32 nPackageType,
                                     bool bSuccess )
{
    QString strFormat = "{\"ClientID\":\"%1\","
                        "\"StateCode\":\"%2\","
                        "\"TypeCode\":\"%3\","
                        "\"UserID\":\"%4\""
                        ",Data:%5}";

    QString strJson;
    strJson = strFormat.arg(
                sHead.sValues.strClientID,
                QString::number( bSuccess ),
                sHead.sValues.strTypeCode,
                sHead.sValues.strUserID,
                strMessage );

    QByteArray byJson = strJson.toUtf8( );
    PostData2PeerThread( pPeerSocket, byJson, nPackageType );
}

void QDbDataProcess::ProcessSocketData( qint32 nPackageType, QByteArray &byJson )
{
    // IP@ClientID@TypeCode LogFormat

    JsonStruct::JsonHead sHead;

    switch ( nPackageType ) {
    case Constant::TypeGroupInfo :
        parserJson2Sql.ParseGroupJson( byJson, sHead );
        break;

    case Constant::TypeUserInfo :
        parserJson2Sql.ParseUserJson( byJson, sHead );
        break;

    case Constant::TypeInOutRecordInfo :
        parserJson2Sql.ParseInOutRecordJson( byJson, sHead );
        break;

    case Constant::TypeSystemInfo :
        parserJson2Sql.ParseSystemJson( byJson, sHead );
        break;

    case Constant::TypeDataInfo :
        parserJson2Sql.ParseDataJson(byJson, sHead );
        break;

    case Constant::TypeFeeInfo :
        parserJson2Sql.ParseFeeJson(byJson, sHead );
        break;
    }

    PrintPackageType( nPackageType );
    CallSP( byJson, sHead, nPackageType );
    //Sleep( 2000 );
}

void QDbDataProcess::PrintPackageType( qint32 nPackageType )
{
    QString strMsg = "未知包类型。";

    switch ( nPackageType ) {
    case Constant::TypeGroupInfo :
        strMsg = "Constant::TypeGroupInfo";
        break;

    case Constant::TypeUserInfo :
        strMsg = "Constant::TypeUserInfo";
        break;

    case Constant::TypeInOutRecordInfo :
        strMsg = "Constant::TypeInOutRecordInfo";
        break;

    case Constant::TypeSystemInfo :
        strMsg = "Constant::TypeSystemInfo";
        break;

    case Constant::TypeDataInfo :
        strMsg = "Constant::TypeDataInfo";
        break;

    case Constant::TypeFeeInfo :
        strMsg = "Constant::TypeFeeInfo";
        break;

    default :
        strMsg = "Unknown";
        break;
    }

    qDebug( ) << Q_FUNC_INFO << strMsg << endl;
}
