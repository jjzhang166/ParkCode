#include "qmanipulatemessage.h"

QManipulateMessage::QManipulateMessage(QObject *parent) :
    QObject(parent)
{
}

int QManipulateMessage::GetIndexValue( quint16 nType )
{
    int nRet = 0;

    for ( quint8 nIndex = 0; nIndex < ( sizeof ( nType ) * 8 ); nIndex++ ) {
        if ( nType & ( 1 << nIndex ) ) {
            nRet = nIndex;
            break;
        }
    }

    return nRet;
}

MyEnums::ePacketType QManipulateMessage::GetPacketType( MyDataStructs::sPacketType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::ePacketType ) nRet;
}

MyEnums::eTableType QManipulateMessage::GetTableType( MyDataStructs::sTableType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eTableType ) nRet;
}

MyEnums::eImageType QManipulateMessage::GetImageType( MyDataStructs::sImageType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eImageType ) nRet;
}

MyEnums::eHeartbeat QManipulateMessage::GetHeartbeatType( MyDataStructs::sHeartbeat& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eHeartbeat ) nRet;
}

MyEnums::eSvrMsg QManipulateMessage::GetSvrMsgType( MyDataStructs::sSvrMsg& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eSvrMsg ) nRet;
}

MyEnums::eCltMsg QManipulateMessage::GetCltMsgType( MyDataStructs::sCltMsg& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eCltMsg ) nRet;
}

MyEnums::eMgmtData QManipulateMessage::GetMgmtType( MyDataStructs::sMgmtDataType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( MyEnums::eMgmtData ) nRet;
}

MyDataStructs::CommonHeader& QManipulateMessage::GetCommonHeader( const char* pData )
{
    return *( MyDataStructs::PCommonHeader ) pData;
}

MyDataStructs::TableHeader& QManipulateMessage::GetTableHeader( const char* pData )
{
    return *( MyDataStructs::PTableHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

MyDataStructs::ImageHeader& QManipulateMessage::GetImageHeader( const char* pData )
{
    return *( MyDataStructs::PImageHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

MyDataStructs::HeartbeatHeader& QManipulateMessage::GetHeartbeatHeader( const char* pData )
{
    return *( MyDataStructs::PHeartbeatHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

MyDataStructs::SvrMsgHeader& QManipulateMessage::GetSvrMsgHeader( const char* pData )
{
    return *( MyDataStructs::PSvrMsgHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

MyDataStructs::CltMsgHeader& QManipulateMessage::GetCltMsgHeader( const char* pData )
{
    return *( MyDataStructs::PCltMsgHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

MyDataStructs::MgmtHeader& QManipulateMessage::GetMgmtHeader( const char* pData )
{
    return *( MyDataStructs::PMgmtHeader ) ( pData + sizeof ( MyDataStructs::CommonHeader ) );
}

const char* QManipulateMessage::GetTableBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( MyDataStructs::CommonHeader ) +
                             sizeof ( MyDataStructs::TableHeader ) );
}

const char* QManipulateMessage::GetImageBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( MyDataStructs::CommonHeader ) +
                             sizeof ( MyDataStructs::ImageHeader ) );
}

const char* QManipulateMessage::GetHeartbeatBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( MyDataStructs::CommonHeader ) +
                             sizeof ( MyDataStructs::HeartbeatHeader ) );
}

const char* QManipulateMessage::GetSvrMsgBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( MyDataStructs::CommonHeader ) +
                             sizeof ( MyDataStructs::SvrMsgHeader ) );
}

const char* QManipulateMessage::GetMgmtBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( MyDataStructs::CommonHeader ) +
                             sizeof ( MyDataStructs::MgmtHeader ) );
}

quint32 QManipulateMessage::GetCommonHeaderSize( )
{
    return sizeof ( MyDataStructs::CommonHeader );
}

quint32 QManipulateMessage::GetTableHeaderSize( )
{
    return sizeof ( MyDataStructs::TableHeader );
}

quint32 QManipulateMessage::GetImageHeaderSize( )
{
    return sizeof ( MyDataStructs::ImageHeader );
}

quint32 QManipulateMessage::GetHeartbeatHeaderSize( )
{
    return sizeof ( MyDataStructs::HeartbeatHeader );
}

quint32 QManipulateMessage::GetSvrMsgHeaderSize( )
{
    return sizeof ( MyDataStructs::SvrMsgHeader );
}

quint32 QManipulateMessage::GetCltMsgHeaderSize( )
{
    return sizeof ( MyDataStructs::CltMsgHeader );
}

quint32 QManipulateMessage::GetMgmtHeaderSize( )
{
    return sizeof ( MyDataStructs::MgmtHeader );
}
