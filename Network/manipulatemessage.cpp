#include "manipulatemessage.h"

CManipulateMessage::CManipulateMessage(QObject *parent) :
    QObject(parent)
{
}

int CManipulateMessage::GetIndexValue( quint16 nType )
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

NetTransport::ePacketType CManipulateMessage::GetPacketType( NetTransport::sPacketType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::ePacketType ) nRet;
}

NetTransport::eTableType CManipulateMessage::GetTableType( NetTransport::sTableType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eTableType ) nRet;
}

NetTransport::eImageType CManipulateMessage::GetImageType( NetTransport::sImageType& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eImageType ) nRet;
}

NetTransport::eHeartbeat CManipulateMessage::GetHeartbeatType( NetTransport::sHeartbeat& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eHeartbeat ) nRet;
}

NetTransport::eSvrMsg CManipulateMessage::GetSvrMsgType( NetTransport::sSvrMsg& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eSvrMsg ) nRet;
}

NetTransport::eCltMsg CManipulateMessage::GetCltMsgType( NetTransport::sCltMsg& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eCltMsg ) nRet;
}

NetTransport::eMgmtData CManipulateMessage::GetMgmtType( NetTransport::eMgmtData& sType )
{
    quint16* pType = ( quint16* ) &sType;
    int nRet = GetIndexValue ( *pType );
    return ( NetTransport::eMgmtData ) nRet;
}

NetTransport::CommonHeader& CManipulateMessage::GetCommonHeader( const char* pData )
{
    return *( NetTransport::PCommonHeader ) pData;
}

NetTransport::TableHeader& CManipulateMessage::GetTableHeader( const char* pData )
{
    return *( NetTransport::PTableHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

NetTransport::ImageHeader& CManipulateMessage::GetImageHeader( const char* pData )
{
    return *( NetTransport::PImageHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

NetTransport::HeartbeatHeader& CManipulateMessage::GetHeartbeatHeader( const char* pData )
{
    return *( NetTransport::PHeartbeatHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

NetTransport::SvrMsgHeader& CManipulateMessage::GetSvrMsgHeader( const char* pData )
{
    return *( NetTransport::PSvrMsgHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

NetTransport::CltMsgHeader& CManipulateMessage::GetCltMsgHeader( const char* pData )
{
    return *( NetTransport::PCltMsgHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

NetTransport::MgmtHeader& CManipulateMessage::GetMgmtHeader( const char* pData )
{
    return *( NetTransport::PMgmtHeader ) ( pData + sizeof ( NetTransport::CommonHeader ) );
}

const char* CManipulateMessage::GetTableBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( NetTransport::CommonHeader ) +
                             sizeof ( NetTransport::TableHeader ) );
}

const char* CManipulateMessage::GetImageBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( NetTransport::CommonHeader ) +
                             sizeof ( NetTransport::ImageHeader ) );
}

const char* CManipulateMessage::GetHeartbeatBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( NetTransport::CommonHeader ) +
                             sizeof ( NetTransport::HeartbeatHeader ) );
}

const char* CManipulateMessage::GetSvrMsgBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( NetTransport::CommonHeader ) +
                             sizeof ( NetTransport::SvrMsgHeader ) );
}

const char* CManipulateMessage::GetMgmtBody( const char* pData )
{
    return ( const char* ) ( pData + sizeof ( NetTransport::CommonHeader ) +
                             sizeof ( NetTransport::MgmtHeader ) );
}

quint32 CManipulateMessage::GetCommonHeaderSize( )
{
    return sizeof ( NetTransport::CommonHeader );
}

quint32 CManipulateMessage::GetTableHeaderSize( )
{
    return sizeof ( NetTransport::TableHeader );
}

quint32 CManipulateMessage::GetImageHeaderSize( )
{
    return sizeof ( NetTransport::ImageHeader );
}

quint32 CManipulateMessage::GetHeartbeatHeaderSize( )
{
    return sizeof ( NetTransport::HeartbeatHeader );
}

quint32 CManipulateMessage::GetSvrMsgHeaderSize( )
{
    return sizeof ( NetTransport::SvrMsgHeader );
}

quint32 CManipulateMessage::GetCltMsgHeaderSize( )
{
    return sizeof ( NetTransport::CltMsgHeader );
}

quint32 CManipulateMessage::GetMgmtHeaderSize( )
{
    return sizeof ( NetTransport::MgmtHeader );
}
