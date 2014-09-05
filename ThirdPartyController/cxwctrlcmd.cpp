#include "cxwctrlcmd.h"

CXwCtrlCmd::CXwCtrlCmd(QObject *parent) :
    CControllerCmd(parent)
{
}

void CXwCtrlCmd::Initialize( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::ModifyTime( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::ReadTime( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::SelectWorkMode( QByteArray& byCmdData, quint16 nControllerAddr, bool bOffline )
{

}

void CXwCtrlCmd::GetOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //开闸	AA	03 00	4F 00	xx	无	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x03, 0x00, 0x4F, 0x00, cAddr, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::GetCloseGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //关闸	AA	03 00	43 00	xx	无	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x03, 0x00, 0x43, 0x00, cAddr, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::GetStopGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::GetRejectOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::ReadRecordState( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::ReadCardID( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CXwCtrlCmd::BallotSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //票箱地感车辆进入	AA	04 00	54 42	xx	01	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, cAddr, 0x01, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::BallotSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //票箱地感车辆离开	AA	04 00	54 42	xx	00	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, cAddr, 0x00, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::GateSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //道闸地感车辆进入	AA	04 00	54 46	xx	01	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x46, cAddr, 0x01, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::GateSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //道闸地感车辆离开	AA	04 00	54 46	xx	00	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x46, cAddr, 0x00, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CXwCtrlCmd::CarCreditCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID )
{
    //有车刷卡信息	AA	06 00	4B 01	xx	3字节，16进制卡号	xx	55
    byCmdData.clear( );
    if ( 3 > byCardID.size( ) ) {
        return;
    }

    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x06, 0x00, 0x4B, 0x01, cAddr, byCardID.at( 0 ), byCardID.at( 1 ), byCardID.at( 2 ), 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );

}

void CXwCtrlCmd::CarFreeCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID )
{
    //无车刷卡信息	AA	06 00	4B 00	xx	3字节，16进制卡号	xx	55
    byCmdData.clear( );
    if ( 3 > byCardID.size( ) ) {
        return;
    }

    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x06, 0x00, 0x4B, 0x00, cAddr, byCardID.at( 0 ), byCardID.at( 1 ), byCardID.at( 2 ), 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

CmdType CXwCtrlCmd::GetEnumType( QByteArray& byCmdData )
{
    CmdType cmd = CmdNone;
    if ( byCmdData.count( ) < 8 ) { // Less than 8 bytes
        return cmd;
    }

    quint8 byte0  = byCmdData[ 0 ]; // Frame Header
    quint8 byte3  = byCmdData[ 3 ]; // Cmd
    quint8 byte4  = byCmdData[ 4 ]; // Cmd
    quint8 byte5  = byCmdData[ 5 ]; // CAN Address
    quint8 byLast = byCmdData[ byCmdData.count( ) - 1 ]; // Frame Tail

    quint8 cHeader = 0xAA;
    quint8 cTail = 0x55;
    if ( cHeader != byte0 || cTail != byLast ) {
        return cmd;
    }

    bool bEnter = ( 0 != ( byte5 % 2 ) );

    if ( 0x4F == byte3 ) {
        cmd = bEnter ? CmdInOpenGate : CmdOutOpenGate;
    } else if ( 0x43 == byte3 ) {
        cmd = bEnter ? CmdInCloseGate : CmdOutCloseGate;
    } else if ( 0x4B == byte3 && ( 0x00 == byte4 || 0x01 == byte4 ) ) {
        cmd = CmdReadCardID;
    } else if ( 0x54 == byte3 ) {
        quint8 byte6 = byCmdData[ 6 ];
        if ( 0x42 == byte4 ) {
            if ( bEnter ) {
                cmd = byte6 ? CmdInBallotSenseEnter : CmdInBallotSenseLeave;
            } else {
                cmd = byte6 ? CmdOutBallotSenseEnter : CmdOutBallotSenseLeave;
            }
        } else if ( 0x46 == byte4 ) {
            if ( bEnter ) {
                cmd = byte6 ? CmdInGateSenseEnter : CmdInGateSenseLeave;
            } else {
                cmd = byte6 ? CmdOutGateSenseEnter : CmdOutGateSenseLeave;
            }
        }
    }

    return cmd;
}

void CXwCtrlCmd::ConvertCmd2Vz( CmdType eSrcCmdType, QByteArray &byXwData, QByteArray &byVzData )
{
    if ( CmdReadCardID == eSrcCmdType ) {

    } else if ( CmdInBallotSenseEnter == eSrcCmdType ) {

    } else if ( CmdInBallotSenseLeave == eSrcCmdType ) {

    } else if ( CmdOutBallotSenseEnter == eSrcCmdType ) {

    } else if ( CmdOutBallotSenseLeave == eSrcCmdType ) {

    } else if ( CmdInGateSenseEnter == eSrcCmdType ) {

    } else if ( CmdInGateSenseLeave == eSrcCmdType ) {

    } else if ( CmdOutGateSenseEnter == eSrcCmdType ) {

    } else if ( CmdOutGateSenseLeave == eSrcCmdType ) {

    } else if ( CmdInOpenGate == eSrcCmdType ) {

    } else if ( CmdOutOpenGate == eSrcCmdType ) {

    } else if ( CmdInCloseGate == eSrcCmdType ) {

    } else if ( CmdOutCloseGate == eSrcCmdType ) {

    }
}

void CXwCtrlCmd::ConvertCmd( CtrlType eDstType, CmdType eSrcCmdType,
                             QByteArray& bySrcData, QByteArray& byDstData )
{
    if ( CtrlVz == eDstType ) {
        ConvertCmd2Vz( eSrcCmdType, bySrcData, byDstData );
    }
}

char CXwCtrlCmd::GetAddress( QByteArray& byCmdData )
{
    char cAddr = 0;

    if ( 5 > byCmdData.size( ) ) {
        return cAddr;
    }

    return byCmdData.at( 5 );
}

void CXwCtrlCmd::GetCardID( QByteArray& byCmdData, QByteArray& byCardID )
{
    if ( 9 > byCmdData.size( ) ) {
        return;
    }

    byCardID.append( byCmdData.mid( 6, 3  ) );
}
