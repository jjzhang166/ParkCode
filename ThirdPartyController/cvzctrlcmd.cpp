#include "cvzctrlcmd.h"

CVzCtrlCmd::CVzCtrlCmd(QObject *parent) :
    CControllerCmd(parent)
{
}

void CVzCtrlCmd::Initialize( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::ModifyTime( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::ReadTime( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::SelectWorkMode( QByteArray& byCmdData, quint16 nControllerAddr, bool bOffline )
{

}

void CVzCtrlCmd::GetOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //开闸	AA	03 00	4F 00	xx	无	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x03, 0x00, 0x4F, 0x00, cAddr, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::GetCloseGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //关闸	AA	03 00	43 00	xx	无	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x03, 0x00, 0x43, 0x00, cAddr, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::GetStopGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::GetRejectOpenGateCmd( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::ReadRecordState( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::ReadCardID( QByteArray& byCmdData, quint16 nControllerAddr )
{

}

void CVzCtrlCmd::BallotSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //票箱地感车辆进入	AA	04 00	54 42	xx	01	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, cAddr, 0x01, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::BallotSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //票箱地感车辆离开	AA	04 00	54 42	xx	00	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x42, cAddr, 0x00, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::GateSenseEnter( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //道闸地感车辆进入	AA	04 00	54 46	xx	01	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x46, cAddr, 0x01, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::GateSenseLeave( QByteArray& byCmdData, quint16 nControllerAddr )
{
    //道闸地感车辆离开	AA	04 00	54 46	xx	00	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x04, 0x00, 0x54, 0x46, cAddr, 0x00, 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

void CVzCtrlCmd::CarCreditCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID )
{
    //有车刷卡信息	AA	06 00	4B 01	xx	3字节，16进制卡号	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x06, 0x00, 0x4B, 0x01, cAddr, byCardID.at( 0 ), byCardID.at( 1 ), byCardID.at( 2 ), 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );

}

void CVzCtrlCmd::CarFreeCard( QByteArray& byCmdData, quint16 nControllerAddr, QByteArray& byCardID )
{
    //无车刷卡信息	AA	06 00	4B 00	xx	3字节，16进制卡号	xx	55
    byCmdData.clear( );
    char cAddr = ( char ) nControllerAddr;
    char cCmd[ ] = { 0xAA, 0x06, 0x00, 0x4B, 0x00, cAddr, byCardID.at( 0 ), byCardID.at( 1 ), byCardID.at( 2 ), 0x00, 0x55 };
    byCmdData.append( cCmd, sizeof (  cCmd ) / sizeof ( cCmd[ 0 ] ) );
}

CmdType CVzCtrlCmd::GetEnumType( QByteArray& byCmdData )
{
    CmdType cmd = CmdNone;
    return cmd;
}

void CVzCtrlCmd::ConvertCmd2Xw( CmdType eSrcCmdType, QByteArray &bXwData, QByteArray &byVzData )
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

void CVzCtrlCmd::ConvertCmd( CtrlType eDstType, CmdType eSrcCmdType,
                             QByteArray& bySrcData, QByteArray& byDstData )
{
    if ( CtrlXw == eDstType ) {
        ConvertCmd2Xw( eSrcCmdType, bySrcData, byDstData );
    }
}

char CVzCtrlCmd::GetAddress( QByteArray& byCmdData )
{
    char cAddr = 0;

    if ( 5 > byCmdData.size( ) ) {
        return cAddr;
    }

    return byCmdData.at( 5 );
}

void CVzCtrlCmd::GetCardID( QByteArray& byCmdData, QByteArray& byCardID )
{
    if ( 9 > byCmdData.size( ) ) {
        return;
    }

    byCardID.append( byCmdData.mid( 6, 3 ) );
}
