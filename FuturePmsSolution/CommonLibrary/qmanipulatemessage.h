#ifndef QMANIPULATEMESSAGE_H
#define QMANIPULATEMESSAGE_H

#include "QCommonFunction_global.h"
#include <QObject>
#include "CommonEnum.h"
#include "CommonDataStruct.h"

class QCOMMONFUNCTIONSHARED_EXPORT QManipulateMessage : public QObject
{
    Q_OBJECT
public:
    explicit QManipulateMessage(QObject *parent = 0);

    MyEnums::ePacketType GetPacketType( MyDataStructs::sPacketType& sType );
    MyEnums::eTableType GetTableType( MyDataStructs::sTableType& sType );
    MyEnums::eImageType GetImageType( MyDataStructs::sImageType& sType );
    MyEnums::eHeartbeat GetHeartbeatType( MyDataStructs::sHeartbeat& sType );
    MyEnums::eSvrMsg GetSvrMsgType( MyDataStructs::sSvrMsg& sType );
    MyEnums::eCltMsg GetCltMsgType( MyDataStructs::sCltMsg& sType );
    MyEnums::eMgmtData GetMgmtType( MyDataStructs::sMgmtDataType& sType );

    MyDataStructs::CommonHeader& GetCommonHeader( const char* pData );
    MyDataStructs::TableHeader& GetTableHeader( const char* pData );
    MyDataStructs::ImageHeader& GetImageHeader( const char* pData );
    MyDataStructs::HeartbeatHeader& GetHeartbeatHeader( const char* pData );
    MyDataStructs::SvrMsgHeader& GetSvrMsgHeader( const char* pData );
    MyDataStructs::CltMsgHeader& GetCltMsgHeader( const char* pData );
    MyDataStructs::MgmtHeader& GetMgmtHeader( const char* pData );

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

#endif // QMANIPULATEMESSAGE_H
