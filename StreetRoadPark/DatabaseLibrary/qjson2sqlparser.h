#ifndef QJSON2SQLPARSER_H
#define QJSON2SQLPARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTcpSocket>
#include <QDomDocument>
#include "cdbconfigurator.h"
#include "qjsonstruct.h"

class QJson2SqlParser : public QObject
{
    Q_OBJECT
public:
    explicit QJson2SqlParser(QObject *parent = 0);
    void SetSocket( QTcpSocket* pSocket );

    void ParseGroupJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    void ParseUserJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    void ParseInOutRecordJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    void ParseSystemJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    void ParseDataJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    void ParseFeeJson( QByteArray& byJson, JsonStruct::JsonHead& sHead );

private:
    inline void GetJsonHead( QJsonObject& objJson, JsonStruct::JsonHead& sHead );
    inline void GetStringValue( QJsonObject& objJson, const QString& strKey, QString& strValue );

    void GetGroupRecordData( JsonStruct::JsonGroup& sRecord );
    void GetGroupXmlData( JsonStruct::JsonGroup& sRecord, QString& strXml );

    void GetUserRecordData( JsonStruct::JsonUser& sRecord );
    void GetUserXmlData( JsonStruct::JsonUser& sRecord, QString& strXml );

    void GetInOutRecordData( JsonStruct::JsonInOutRecord& sRecord );
    void GetInOutXmlData( JsonStruct::JsonInOutRecord& sRecord, QString& strXml );
    void GetUploadInOutXmlData( JsonStruct::JsonInOutRecord& sRecord, QString& strXml );

    void GetDeviceRecordData( JsonStruct::JsonDeviceRecord& sRecord );
    void GetDeviceXmlData( JsonStruct::JsonDeviceRecord& sRecord, QString& strXml );

    void GetDataRecordData( JsonStruct::JsonDataRecord& sRecord );
    void GetDataXmlData( JsonStruct::JsonDataRecord& sRecord, QString& strXml );

    void GetFeeRecordData( JsonStruct::JsonFeeRecord& sRecord );
    void GetFeeXmlData( JsonStruct::JsonFeeRecord& sRecord, QString& strXml );

    void GetSpName( QString& strTypeCode, QString& strSpName );
    inline void GetJsonObject( QByteArray& byJson, JsonStruct::JsonHead& sHead );
    inline void PrintJson( QByteArray& byJson, QJsonParseError& jsonError);

private:
    QString strSeperator;
    QTcpSocket* pPeerSocket;
    QString strUnknown;
    QString strZero;
    CDbConfigurator* pConfig;

signals:
    
public slots:
    
};

#endif // QJSON2SQLPARSER_H
