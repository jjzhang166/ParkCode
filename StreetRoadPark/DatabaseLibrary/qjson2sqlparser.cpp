#include "qjson2sqlparser.h"
#include <QDebug>
#include <QHostAddress>
#include "Constant.h"

// Android DateFormat.parse( string ) ==> Date
QJson2SqlParser::QJson2SqlParser(QObject *parent) :
    QObject(parent)
{
    pPeerSocket = NULL;
    strSeperator = "@";
    strUnknown = "未知";
    strZero = "0";
    pConfig = CDbConfigurator::GetConfigurator( );
}

void QJson2SqlParser::GetJsonHead( QJsonObject &objJson, JsonStruct::JsonHead &sHead )
{
    GetStringValue( objJson, sHead.sKeys.strClientID, sHead.sValues.strClientID );
    GetStringValue( objJson, sHead.sKeys.strTypeCode, sHead.sValues.strTypeCode );
    GetStringValue( objJson, sHead.sKeys.strUserID, sHead.sValues.strUserID );

    sHead.sValues.jsonData = objJson.value( sHead.sKeys.strData ).toObject( );
}

void QJson2SqlParser::PrintJson( QByteArray &byJson, QJsonParseError &jsonError )
{
    qDebug( ) << jsonError.errorString( ) << endl
              << QString( byJson ) << endl;
}

void QJson2SqlParser::GetJsonObject( QByteArray& byJson, JsonStruct::JsonHead& sHead )
{
    QJsonParseError jsonError;
    QJsonDocument docJson = QJsonDocument::fromJson( byJson, &jsonError );

    PrintJson( byJson, jsonError );

    if ( !docJson.isObject( ) ) {
        return;
    }

    QJsonObject objJson = docJson.object( );

    byJson.clear( );
    GetJsonHead( objJson, sHead );

    // IP@ClientID@TypeCode LogFormat
    sHead.strLog = Constant::SpXmlPattern.strXmlHeadRecord.arg(
                   pPeerSocket->peerAddress( ).toString( ),
                   sHead.sValues.strClientID,
                   sHead.sValues.strTypeCode,
                   sHead.sValues.strUserID );
}

void QJson2SqlParser::GetDataRecordData( JsonStruct::JsonDataRecord& sRecord )
{
    if ( Constant::TypeCode.strCodeDataInfo == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strDataType,
                        sRecord.sData.sValues.strDataType );
    }
}

void QJson2SqlParser::GetFeeRecordData( JsonStruct::JsonFeeRecord& sRecord )
{
    if ( Constant::TypeCode.strCodeGetFeeRate == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strParkID,
                        sRecord.sData.sValues.strParkID );
    } else if ( Constant::TypeCode.strCodeGetFreeType == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strParkID,
                        sRecord.sData.sValues.strParkID );
    }
}

void QJson2SqlParser::GetDeviceRecordData( JsonStruct::JsonDeviceRecord& sRecord )
{
    if ( Constant::TypeCode.strCodeConfigInfo == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strDeviceID,
                        sRecord.sData.sValues.strDeviceID );
    } else {
        QJsonValue aryValue = sRecord.sHead.sValues.jsonData.value( sRecord.sData.sKeys.strList );
        if ( !aryValue.isArray( ) ) {
            return;
        }

        if ( Constant::TypeCode.strCodeDeviceRegister == sRecord.sHead.sValues.strTypeCode ) {
            sRecord.sHead.nFlag = Constant::TTypeCode::EDeviceRegister;
            sRecord.sData.bRegister = true;
        } else if ( Constant::TypeCode.strCodeDeviceUnregister == sRecord.sHead.sValues.strTypeCode ) {
            sRecord.sHead.nFlag = Constant::TTypeCode::EDeviceUnregister;
            sRecord.sData.bRegister = false;
        }

        QJsonArray lstValue = aryValue.toArray( );
        qint32 nItems = lstValue.count( );

        QJsonObject objValue;
        QString strValue;
        QString strItems;

        for ( qint32 nItem = 0; nItem < nItems; nItem++ ) {
            aryValue = lstValue.at( nItem );

            if ( !aryValue.isObject( ) ) {
                continue;
            }

            objValue = aryValue.toObject( );

            strItems = sRecord.sData.sFormat.strLeftBracket;

            GetStringValue( objValue, sRecord.sData.sKeys.strDeviceID, strValue );
            strItems += sRecord.sData.sFormat.strFormat.arg( strValue );

            if ( sRecord.sData.bRegister ) {
                GetStringValue( objValue, sRecord.sData.sKeys.strStartTime, strValue );
                strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );

                GetStringValue( objValue, sRecord.sData.sKeys.strEndTime, strValue );
                strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );

                GetStringValue( objValue, sRecord.sData.sKeys.strSN, strValue );
                strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );

                GetStringValue( objValue, sRecord.sData.sKeys.strComments, strValue );
                strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );

                GetStringValue( objValue, sRecord.sData.sKeys.strUnitID, strValue );
                strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );
            }

            GetStringValue( objValue, sRecord.sData.sKeys.strOperator, strValue );
            strItems += sRecord.sData.sFormat.strCommasFormat.arg( strValue );

            strItems += sRecord.sData.sFormat.strRightBracket;

            sRecord.sData.lstValues << strItems;
        }
    }
}

void QJson2SqlParser::GetInOutRecordData( JsonStruct::JsonInOutRecord &sRecord )
{
    if ( Constant::TypeCode.strCodeTabletNormalData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLocationID,
                        sRecord.sData.sValues.strLocationID );

        if ( sRecord.sData.sValues.strLocationID.isEmpty( ) ) {
            sRecord.sData.sValues.strLocationID = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPlate,
                        sRecord.sData.sValues.strPlate );

        if ( sRecord.sData.sValues.strPlate.isEmpty( ) ) {
            sRecord.sData.sValues.strPlate = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPayment,
                        sRecord.sData.sValues.strPayment );

        if ( sRecord.sData.sValues.strPayment.isEmpty( ) ) {
            sRecord.sData.sValues.strPayment = strZero;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strOperator,
                        sRecord.sData.sValues.strOperator );

        if ( sRecord.sData.sValues.strOperator.isEmpty( ) ) {
            sRecord.sData.sValues.strOperator = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentTime,
                        sRecord.sData.sValues.strPaymentTime );

        if ( sRecord.sData.sValues.strPaymentTime.isEmpty( ) ) {
            sRecord.sData.sValues.strPaymentTime = pConfig->GetDateTime( );
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strImage,
                        sRecord.sData.sValues.strImage );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strState,
                        sRecord.sData.sValues.strState );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strRecordType,
                        sRecord.sData.sValues.strRecordType );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strFeeReceivable,
                        sRecord.sData.sValues.strFeeReceivable );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strFreeType,
                        sRecord.sData.sValues.strFreeType );
    } else if ( Constant::TypeCode.strCodeTabletManualData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLocationID,
                        sRecord.sData.sValues.strLocationID );

        if ( sRecord.sData.sValues.strLocationID.isEmpty( ) ) {
            sRecord.sData.sValues.strLocationID = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPlate,
                        sRecord.sData.sValues.strPlate );

        if ( sRecord.sData.sValues.strPlate.isEmpty( ) ) {
            sRecord.sData.sValues.strPlate = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPayment,
                        sRecord.sData.sValues.strPayment );

        if ( sRecord.sData.sValues.strPayment.isEmpty( ) ) {
            sRecord.sData.sValues.strPayment = strZero;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strOperator,
                        sRecord.sData.sValues.strOperator );

        if ( sRecord.sData.sValues.strOperator.isEmpty( ) ) {
            sRecord.sData.sValues.strOperator = strUnknown;
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentTime,
                        sRecord.sData.sValues.strPaymentTime );

        if ( sRecord.sData.sValues.strPaymentTime.isEmpty( ) ) {
            sRecord.sData.sValues.strPaymentTime = pConfig->GetDateTime( );
        }

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strImage,
                        sRecord.sData.sValues.strImage );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strState,
                        sRecord.sData.sValues.strState );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strRecordType,
                        sRecord.sData.sValues.strRecordType );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strFeeReceivable,
                        sRecord.sData.sValues.strFeeReceivable );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strFreeType,
                        sRecord.sData.sValues.strFreeType );
    } else if ( Constant::TypeCode.strCodeUnhandledSensorData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLocationID,
                        sRecord.sData.sValues.strLocationID );
    } else if ( Constant::TypeCode.strCodeTabletQueryLocationData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLocationID,
                        sRecord.sData.sValues.strLocationID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strEnterStartTime,
                        sRecord.sData.sValues.strEnterStartTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strEnterEndTime,
                        sRecord.sData.sValues.strEnterEndTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLeaveStartTime,
                        sRecord.sData.sValues.strLeaveStartTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLeaveEndTime,
                        sRecord.sData.sValues.strLeaveEndTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPlate,
                        sRecord.sData.sValues.strPlate );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strOperator,
                        sRecord.sData.sValues.strOperator );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLimit,
                        sRecord.sData.sValues.strLimit );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strIncludedImage,
                        sRecord.sData.sValues.strIncludedImage );
    } else if ( Constant::TypeCode.strCodeTabletQueryImageData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strRecordID,
                        sRecord.sData.sValues.strRecordID );
    } else if ( Constant::TypeCode.strCodeTabletQueryReprotData == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strUnitID,
                        sRecord.sData.sValues.strUnitID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strParkID,
                        sRecord.sData.sValues.strParkID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentStartTime,
                        sRecord.sData.sValues.strPaymentStartTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentEndTime,
                        sRecord.sData.sValues.strPaymentEndTime );
    } else if ( Constant::TypeCode.strCodeTabletVehicleShiftRequest == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strSrcLocationID,
                        sRecord.sData.sValues.strSrcLocationID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strDstLocationID,
                        sRecord.sData.sValues.strDstLocationID );
    } else if ( Constant::TypeCode.strCodeTabletUploadInOutRecord == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLocationID,
                        sRecord.sData.sValues.strLocationID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strState,
                        sRecord.sData.sValues.strState );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strRecordID,
                        sRecord.sData.sValues.strRecordID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strEnterTime,
                        sRecord.sData.sValues.strEnterTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLeaveTime,
                        sRecord.sData.sValues.strLeaveTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPrepayment,
                        sRecord.sData.sValues.strPrepayment );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPayment,
                        sRecord.sData.sValues.strPayment );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strEnterPlate,
                        sRecord.sData.sValues.strEnterPlate );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLeavePlate,
                        sRecord.sData.sValues.strLeavePlate );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPrepaymentOperator,
                        sRecord.sData.sValues.strPrepaymentOperator );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentOperator,
                        sRecord.sData.sValues.strPaymentOperator );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strEnterImage,
                        sRecord.sData.sValues.strEnterImage );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strLeaveImage,
                        sRecord.sData.sValues.strLeaveImage );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPrepaymentTime,
                        sRecord.sData.sValues.strPrepaymentTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentTime,
                        sRecord.sData.sValues.strPaymentTime );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPrepaymentUserID,
                        sRecord.sData.sValues.strPrepaymentUserID );

        GetStringValue( sRecord.sHead.sValues.jsonData,
                        sRecord.sData.sKeys.strPaymentUserID,
                        sRecord.sData.sValues.strPaymentUserID );
    }
}

void QJson2SqlParser::GetSpName( QString &strTypeCode, QString& strSpName )
{
    if ( Constant::TypeCode.strCodeTabletNormalData == strTypeCode ) {
        strSpName = Constant::SpName.strSpTabletNormalRecord;
    } else if ( Constant::TypeCode.strCodeTabletManualData == strTypeCode ) {
        strSpName = Constant::SpName.strSpTabletManualRecord;
    } else if ( Constant::TypeCode.strCodeTabletQueryLocationData == strTypeCode ) {
        strSpName = Constant::SpName.strSpQueryInOutRecord;
    } else if ( Constant::TypeCode.strCodeTabletQueryImageData == strTypeCode ) {
        strSpName = Constant::SpName.strSpQueryImageRecord;
    } else if ( Constant::TypeCode.strCodeTabletQueryReprotData == strTypeCode ) {
        strSpName = Constant::SpName.strSpQueryReportRecord;
    } else if ( Constant::TypeCode.strCodeUnhandledSensorData == strTypeCode ) {
        strSpName = Constant::SpName.strSpUnhandledSensorRecord;
    } else if( Constant::TypeCode.strCodeDeviceRegister == strTypeCode ) {
        strSpName = Constant::SpName.strDeviceRecord;
    } else if( Constant::TypeCode.strCodeDeviceUnregister == strTypeCode ) {
        strSpName = Constant::SpName.strDeviceRecord;
    } else if ( Constant::TypeCode.strCodeGroupSelect == strTypeCode ) {
        strSpName = Constant::SpName.strSpGroupRecord;
    } else if ( Constant::TypeCode.strCodeUserSelect == strTypeCode ) {
        strSpName = Constant::SpName.strSpUserRecord;
    } else if ( Constant::TypeCode.strCodeUserUpdate == strTypeCode ) {
        strSpName = Constant::SpName.strSpUserRecord;
    } else if ( Constant::TypeCode.strCodeUserLogin == strTypeCode ) {
        strSpName = Constant::SpName.strSpUserRecord;
    } else if ( Constant::TypeCode.strCodeUserLogout == strTypeCode ) {
        strSpName = Constant::SpName.strSpUserRecord;
    } else if ( Constant::TypeCode.strCodeUserFee == strTypeCode ) {
        strSpName = Constant::SpName.strSpUserRecord;
    } else if ( Constant::TypeCode.strCodeConfigInfo == strTypeCode ) {
        strSpName = Constant::SpName.strSpQueryConfigRecord;
    } else if ( Constant::TypeCode.strCodeTabletVehicleShiftRequest == strTypeCode ) {
        strSpName = Constant::SpName.strSpVehicleShiftRecord;
    } else if ( Constant::TypeCode.strCodeDataInfo == strTypeCode ) {
        strSpName = Constant::SpName.strSpQueryCommonRecord;
    } else if ( Constant::TypeCode.strCodeTabletUploadInOutRecord == strTypeCode ) {
        strSpName = Constant::SpName.strSpUploadInOutRecord;
    } else if ( Constant::TypeCode.strCodeGetFeeRate == strTypeCode ) {
        strSpName = Constant::SpName.strSpGetFeeRateRecord;
    } else if ( Constant::TypeCode.strCodeGetFreeType == strTypeCode ) {
        strSpName = Constant::SpName.strSpGetFreeTypeRecord;
    }
}

void QJson2SqlParser::ParseDataJson( QByteArray &byJson, JsonStruct::JsonHead &sHead )
{
    JsonStruct::JsonDataRecord sRecordRequest;

    GetJsonObject( byJson, sRecordRequest.sHead );
    GetSpName( sRecordRequest.sHead.sValues.strTypeCode, sRecordRequest.sHead.strSpName );
    GetDataRecordData( sRecordRequest );

    QString strXml;
    GetDataXmlData( sRecordRequest, strXml );
    byJson.append( strXml );

    sHead = sRecordRequest.sHead;
}

void QJson2SqlParser::ParseFeeJson( QByteArray &byJson, JsonStruct::JsonHead &sHead )
{
    JsonStruct::JsonFeeRecord sRecordRequest;

    GetJsonObject( byJson, sRecordRequest.sHead );
    GetSpName( sRecordRequest.sHead.sValues.strTypeCode, sRecordRequest.sHead.strSpName );
    GetFeeRecordData( sRecordRequest );

    QString strXml;
    GetFeeXmlData( sRecordRequest, strXml );
    byJson.append( strXml );

    sHead = sRecordRequest.sHead;
}

void QJson2SqlParser::ParseSystemJson( QByteArray &byJson, JsonStruct::JsonHead &sHead )
{
    JsonStruct::JsonDeviceRecord sRecordRequest;

    GetJsonObject( byJson, sRecordRequest.sHead );
    GetSpName( sRecordRequest.sHead.sValues.strTypeCode, sRecordRequest.sHead.strSpName );
    GetDeviceRecordData( sRecordRequest );

    QString strXml;
    GetDeviceXmlData( sRecordRequest, strXml );
    byJson.append( strXml );

    sHead = sRecordRequest.sHead;
}

void QJson2SqlParser::GetDataXmlData( JsonStruct::JsonDataRecord &sRecord, QString &strXml )
{
    if ( Constant::TypeCode.strCodeDataInfo == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlDataInfo.arg(
                             sRecord.sData.sValues.strDataType,
                             sRecord.sHead.strLog );
    }
}

void QJson2SqlParser::GetFeeXmlData( JsonStruct::JsonFeeRecord &sRecord, QString &strXml )
{
    if ( Constant::TypeCode.strCodeGetFeeRate == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlGetFeeRate.arg(
                             sRecord.sData.sValues.strParkID,
                             sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeGetFreeType == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlGetFreeType.arg(
                             sRecord.sData.sValues.strParkID,
                             sRecord.sHead.strLog );
    }
}

void QJson2SqlParser::GetDeviceXmlData( JsonStruct::JsonDeviceRecord &sRecord, QString &strXml )
{
    if ( Constant::TypeCode.strCodeConfigInfo == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlConfigRecord.arg(
                             sRecord.sData.sValues.strDeviceID,
                             sRecord.sHead.strLog );
    } else {
        QString strValue = sRecord.sData.lstValues.join( sRecord.sData.sFormat.strCommas );
        strXml = Constant::SpXmlPattern.strXmlDeviceRecord.arg( strValue, sRecord.sHead.strLog );
    }
}

void QJson2SqlParser::ParseInOutRecordJson( QByteArray& byJson, JsonStruct::JsonHead& sHead )
{
    char nFlag = 0;
    QString strXml;
    JsonStruct::JsonInOutRecord sRecordRequest;

    GetJsonObject( byJson, sRecordRequest.sHead );
    GetSpName( sRecordRequest.sHead.sValues.strTypeCode, sRecordRequest.sHead.strSpName );

    if ( Constant::TypeCode.strCodeTabletUploadInOutRecord == sRecordRequest.sHead.sValues.strTypeCode ) {
        GetUploadInOutXmlData( sRecordRequest, strXml );
    } else {
        GetInOutRecordData( sRecordRequest );
        GetInOutXmlData( sRecordRequest, strXml );
    }

    byJson.append( strXml );
    nFlag = sRecordRequest.sData.sValues.strState.toShort( );

    sHead = sRecordRequest.sHead;
    sHead.nFlag = nFlag;
}

void QJson2SqlParser::GetInOutXmlData( JsonStruct::JsonInOutRecord &sRecord, QString &strXml )
{
    if ( Constant::TypeCode.strCodeTabletNormalData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletNormalRecord.arg(
                             sRecord.sData.sValues.strLocationID,
                             sRecord.sData.sValues.strPlate,
                             sRecord.sData.sValues.strPayment,
                             sRecord.sData.sValues.strOperator,
                             sRecord.sData.sValues.strPaymentTime,
                             sRecord.sData.sValues.strImage,
                             sRecord.sHead.strLog,
                             sRecord.sHead.sValues.strUserID );
        strXml = strXml.arg( sRecord.sData.sValues.strFeeReceivable,
                             sRecord.sData.sValues.strRecordType,
                             sRecord.sData.sValues.strFreeType);
    } else if ( Constant::TypeCode.strCodeTabletManualData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletManualRecord.arg(
                             sRecord.sData.sValues.strLocationID,
                             sRecord.sData.sValues.strPlate,
                             sRecord.sData.sValues.strPayment,
                             sRecord.sData.sValues.strOperator,
                             sRecord.sData.sValues.strPaymentTime,
                             sRecord.sData.sValues.strImage,
                             sRecord.sHead.strLog,
                             sRecord.sHead.sValues.strUserID,
                             pConfig->GetDateTime( ) );
        strXml = strXml.arg( sRecord.sData.sValues.strFeeReceivable,
                             sRecord.sData.sValues.strRecordType,
                             sRecord.sData.sValues.strFreeType);
    } else if ( Constant::TypeCode.strCodeUnhandledSensorData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUnhandledSensorRecord.arg(
                             sRecord.sData.sValues.strLocationID,
                             sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeTabletQueryLocationData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletQueryLocationRecord.arg(
                             sRecord.sData.sValues.strLocationID,
                             sRecord.sData.sValues.strEnterStartTime,
                             sRecord.sData.sValues.strEnterEndTime,
                             sRecord.sData.sValues.strLeaveStartTime,
                             sRecord.sData.sValues.strLeaveEndTime,
                             sRecord.sData.sValues.strPlate,
                             sRecord.sData.sValues.strOperator,
                             sRecord.sData.sValues.strLimit,
                             sRecord.sData.sValues.strIncludedImage );
        strXml = strXml.arg( sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeTabletQueryImageData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletQueryImageRecord.arg(
                             sRecord.sData.sValues.strRecordID,
                             sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeTabletQueryReprotData == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletQueryLocationRecord.arg(
                             sRecord.sData.sValues.strUnitID,
                             sRecord.sData.sValues.strParkID,
                             sRecord.sData.sValues.strPaymentStartTime,
                             sRecord.sData.sValues.strPaymentEndTime,
                             sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeTabletVehicleShiftRequest == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletVehicleShiftRecord.arg(
                             sRecord.sData.sValues.strSrcLocationID,
                             sRecord.sData.sValues.strDstLocationID,
                             sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeTabletUploadInOutRecord == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlTabletUploadInOutRecord.arg(
                             sRecord.sData.sValues.strLocationID,
                             sRecord.sData.sValues.strState,
                             sRecord.sData.sValues.strRecordID,
                             sRecord.sData.sValues.strEnterTime,
                             sRecord.sData.sValues.strLeaveTime,
                             sRecord.sData.sValues.strPrepayment,
                             sRecord.sData.sValues.strPayment,
                             sRecord.sData.sValues.strEnterPlate,
                             sRecord.sData.sValues.strLeavePlate );

        strXml = strXml.arg( sRecord.sData.sValues.strPrepaymentOperator,
                             sRecord.sData.sValues.strPaymentOperator,
                             sRecord.sData.sValues.strEnterImage,
                             sRecord.sData.sValues.strLeaveImage,
                             sRecord.sData.sValues.strPrepaymentTime,
                             sRecord.sData.sValues.strPaymentTime,
                             sRecord.sData.sValues.strPrepaymentUserID,
                             sRecord.sData.sValues.strPaymentUserID );
    }
}

void QJson2SqlParser::GetUploadInOutXmlData( JsonStruct::JsonInOutRecord &sRecord, QString &strXml )
{
    QJsonValue aryValue = sRecord.sHead.sValues.jsonData.value( sRecord.sData.sKeys.strList );
    if ( !aryValue.isArray( ) ) {
        return;
    }

    QJsonArray lstValue = aryValue.toArray( );
    qint32 nItems = lstValue.count( );
    JsonStruct::JsonInOutRecord sTmpRecord;
    QString strTmpXml;

    for ( qint32 nItem = 0; nItem < nItems; nItem++ ) {
        aryValue = lstValue.at( nItem );

        if ( !aryValue.isObject( ) ) {
            continue;
        }

        sTmpRecord.sHead.sValues.strTypeCode = sRecord.sHead.sValues.strTypeCode;
        sTmpRecord.sHead.sValues.jsonData = aryValue.toObject( );

        GetInOutRecordData( sTmpRecord );
        GetInOutXmlData( sTmpRecord, strTmpXml );
        strXml.append( strTmpXml );
    }

    strXml.insert( 0, "<Data>" );
    strXml.append( "<Accessor>" );
    strXml.append( sRecord.sHead.strLog );
    strXml.append( "</Accessor>" );
    strXml.append( "</Data>" );
}

void QJson2SqlParser::ParseGroupJson( QByteArray &byJson, JsonStruct::JsonHead &sHead )
{
    char nFlag = 0;
    JsonStruct::JsonGroup sGroupRequest;

    GetJsonObject( byJson, sGroupRequest.sHead );
    GetSpName( sGroupRequest.sHead.sValues.strTypeCode, sGroupRequest.sHead.strSpName );
    GetGroupRecordData( sGroupRequest );

    QString strXml;
    GetGroupXmlData( sGroupRequest, strXml );
    byJson.append( strXml );

    sHead = sGroupRequest.sHead;
    sHead.nFlag = nFlag;
}

void QJson2SqlParser::GetGroupXmlData( JsonStruct::JsonGroup &sRecord, QString &strXml )
{
    strXml = Constant::SpXmlPattern.strXmlGroupRecord.arg(
                             sRecord.sData.sValues.strUnitID,
                             sRecord.sHead.strLog );
}

void QJson2SqlParser::GetGroupRecordData( JsonStruct::JsonGroup &sRecord )
{
    GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUnitID, sRecord.sData.sValues.strUnitID );
}

void QJson2SqlParser::GetUserRecordData( JsonStruct::JsonUser &sRecord )
{
    if ( Constant::TypeCode.strCodeUserSelect == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strGroupID, sRecord.sData.sValues.strGroupID );

        sRecord.sHead.nFlag = Constant::TTypeCode::EUserSelect;
    } else if ( Constant::TypeCode.strCodeUserUpdate == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserID, sRecord.sData.sValues.strUserID );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserName, sRecord.sData.sValues.strUserName );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserPwd, sRecord.sData.sValues.strUserPwd );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strPwdMD5, sRecord.sData.sValues.strPwdMD5 );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserNewPwd, sRecord.sData.sValues.strUserNewPwd );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strPwdNewMD5, sRecord.sData.sValues.strPwdNewMD5 );

        sRecord.sHead.nFlag = Constant::TTypeCode::EUserUpdate;
    } else if ( Constant::TypeCode.strCodeUserLogin == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserID, sRecord.sData.sValues.strUserID );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserName, sRecord.sData.sValues.strUserName );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserPwd, sRecord.sData.sValues.strUserPwd );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strPwdMD5, sRecord.sData.sValues.strPwdMD5 );

        sRecord.sHead.nFlag = Constant::TTypeCode::EUserLogin;
    } else if ( Constant::TypeCode.strCodeUserLogout == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserID, sRecord.sData.sValues.strUserID );

        sRecord.sHead.nFlag = Constant::TTypeCode::EUserLogout;
    } else if ( Constant::TypeCode.strCodeUserFee == sRecord.sHead.sValues.strTypeCode ) {
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strUserID, sRecord.sData.sValues.strUserID );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strStartTime, sRecord.sData.sValues.strStartTime );
        GetStringValue( sRecord.sHead.sValues.jsonData, sRecord.sData.sKeys.strEndTime, sRecord.sData.sValues.strEndTime );

        sRecord.sHead.nFlag = Constant::TTypeCode::EUserFee;
    }
}

void QJson2SqlParser::GetUserXmlData( JsonStruct::JsonUser &sRecord, QString &strXml )
{
    if ( Constant::TypeCode.strCodeUserSelect == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUserSelectRecord.arg( sRecord.sData.sValues.strGroupID,
                                                                    sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeUserUpdate == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUserUdapteRecord.arg( sRecord.sData.sValues.strUserID,
                                                                    sRecord.sData.sValues.strUserName,
                                                                    sRecord.sData.sValues.strUserPwd,
                                                                    sRecord.sData.sValues.strPwdMD5,
                                                                    sRecord.sData.sValues.strUserNewPwd,
                                                                    sRecord.sData.sValues.strPwdNewMD5,
                                                                    sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeUserLogin == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUserLoginRecord.arg( sRecord.sData.sValues.strUserID,
                                                                    sRecord.sData.sValues.strUserName,
                                                                    sRecord.sData.sValues.strUserPwd,
                                                                    sRecord.sData.sValues.strPwdMD5,
                                                                    sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeUserLogout == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUserLogoutRecord.arg( sRecord.sData.sValues.strUserID,
                                                                    sRecord.sHead.strLog );
    } else if ( Constant::TypeCode.strCodeUserFee == sRecord.sHead.sValues.strTypeCode ) {
        strXml = Constant::SpXmlPattern.strXmlUserFeeRecord.arg( sRecord.sData.sValues.strUserID,
                                                                 sRecord.sData.sValues.strStartTime,
                                                                 sRecord.sData.sValues.strEndTime,
                                                                 sRecord.sHead.strLog );
    }
}

void QJson2SqlParser::ParseUserJson( QByteArray &byJson, JsonStruct::JsonHead &sHead )
{
    JsonStruct::JsonUser sUserRequest;

    GetJsonObject( byJson, sUserRequest.sHead );
    GetSpName( sUserRequest.sHead.sValues.strTypeCode, sUserRequest.sHead.strSpName );
    GetUserRecordData( sUserRequest );

    QString strXml;
    GetUserXmlData( sUserRequest, strXml );
    byJson.append( strXml );

    sHead = sUserRequest.sHead;
}

void QJson2SqlParser::SetSocket( QTcpSocket *pSocket )
{
    pPeerSocket = pSocket;
}

void QJson2SqlParser::GetStringValue( QJsonObject &objJson, const QString& strKey, QString &strValue )
{
    QJsonValue valJson = objJson.value( strKey );

    if ( valJson.isUndefined( ) ||
         valJson.isNull( ) ||
         !valJson.isString( ) ) {
        strValue = "";
        return;
    }

    strValue = valJson.toString( );
}
