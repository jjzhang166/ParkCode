#ifndef MANIPULATEMESSAGE_H
#define MANIPULATEMESSAGE_H

#include <QObject>
#include "CommonData.h"

class CManipulateMessage : public QObject
{
    Q_OBJECT
public:
    explicit CManipulateMessage(QObject *parent = 0);

    NetTransport::ePacketType GetPacketType( NetTransport::sPacketType& sType );
    NetTransport::eTableType GetTableType( NetTransport::sTableType& sType );
    NetTransport::eImageType GetImageType( NetTransport::sImageType& sType );
    NetTransport::eHeartbeat GetHeartbeatType( NetTransport::sHeartbeat& sType );
    NetTransport::eSvrMsg GetSvrMsgType( NetTransport::sSvrMsg& sType );
    NetTransport::eCltMsg GetCltMsgType( NetTransport::sCltMsg& sType );
    NetTransport::eMgmtData GetMgmtType( NetTransport::eMgmtData& sType );

    NetTransport::CommonHeader& GetCommonHeader( const char* pData );
    NetTransport::TableHeader& GetTableHeader( const char* pData );
    NetTransport::ImageHeader& GetImageHeader( const char* pData );
    NetTransport::HeartbeatHeader& GetHeartbeatHeader( const char* pData );
    NetTransport::SvrMsgHeader& GetSvrMsgHeader( const char* pData );
    NetTransport::CltMsgHeader& GetCltMsgHeader( const char* pData );
    NetTransport::MgmtHeader& GetMgmtHeader( const char* pData );

    quint32 GetCommonHeaderSize( );
    quint32 GetTableHeaderSize( );
    quint32 GetImageHeaderSize( );
    quint32 GetHeartbeatHeaderSize( );
    quint32 GetSvrMsgHeaderSize( );
    quint32 GetCltMsgHeaderSize( );
    quint32 GetMgmtHeaderSize( );

    const char* GetTableBody( const char* pData );
    const char* GetImageBody( const char* pData );
    const char* GetHeartbeatBody( const char* pData );
    const char* GetSvrMsgBody( const char* pData );
    const char* GetMgmtBody( const char* pData );

private:
    inline int GetIndexValue( quint16 nType );

signals:

public slots:

};

#endif // MANIPULATEMESSAGE_H
