#include "qcmdgenerator.h"

//
// Generate serial port command
//

QCmdGenerator::QCmdGenerator(QObject *parent) :
    QObject(parent)
{
}

QCmdGenerator::~QCmdGenerator( )
{

}

void QCmdGenerator::GetFlashStateAlwaysRadianceChane( QByteArray &body )
{

}

void QCmdGenerator::GetFlashFrenquencyIntensityTune( const qint16 nTune, QByteArray &body )
{
    char* pValue = ( char* ) &nTune;
    char cCmd[ ] = { 0x02, 0x03, 0xd8,  pValue[ 1 ], pValue[ 0 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFlashFrenquencyGearClose( const qint32 nClose, QByteArray &body )
{
    char* pValue = ( char* ) &nClose;
    char cCmd[ ] = { 0x04, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFlashGearAlwaysRadianceClose( const qint32 nClose, QByteArray &body )
{
    char* pValue = ( char* ) &nClose;
    char cCmd[ ] = { 0x05, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFlashGearAlwaysRadianceOpen( const qint32 nOpen, QByteArray &body )
{
    char* pValue = ( char* ) &nOpen;
    char cCmd[ ] = { 0x06, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFlashFrenquencyGearWorkTimeSet( const qint32 nTime, QByteArray &body )
{
    char* pValue = ( char* ) &nTime;
    char cCmd[ ] = { 0x07, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFlashFrenquencyLightSensitiveIfWork( const qint32 nWork, QByteArray &body )
{
    char* pValue = ( char* ) &nWork;
    char cCmd[ ] = { 0x08, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetSyncModeCmd( const qint32 nMode, QByteArray &body )
{
    char* pValue = ( char* ) &nMode;
    char cCmd[ ] = { 0x09, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetTestFlashCmd( const qint8 nTest, QByteArray &body )
{
    // AA 55 0A 03 D8 01 FF FF FF Open
    // AA 55 0A 03 D8 03 FF FF FF Close

    char cCmd[ ] = { 0x0A, 0x03, 0xD8, nTest, 0xFF };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFrameFrequencyCmd( const qint8 nFrameFreq, QByteArray &body )
{

}

void QCmdGenerator::GetFlashGearSet( const qint32 nGear, QByteArray &body )
{
    char* pValue = ( char* ) &nGear;
    char cCmd[ ] = { 0x03, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetFrenquencyGearSet( const qint32 nGear, QByteArray &body )
{
    char* pValue = ( char* ) &nGear;
    char cCmd[ ] = { 0x03, pValue[ 0 ], pValue[ 1 ],  pValue[ 2 ], pValue[ 3 ] };
    body.append( cCmd, sizeof ( cCmd ) );
}

void QCmdGenerator::GetOldCmdBody( QByteArray &body, LedControll::ECommand eCmd, qint32 nParam )
{
    switch ( eCmd ) {
    case LedControll::CmdFlashStateAlwaysRadianceChange : // 0x01
        GetFlashStateAlwaysRadianceChane( body );
        break;

    case LedControll::CmdFlashFrenquencyIntensityTune : // 0x02
        GetFlashFrenquencyIntensityTune( nParam, body );
        break;

    case LedControll::CmdFlashGearSet : // 0x03
        GetFlashGearSet( nParam, body );
        break;

    case LedControll::CmdFrenquencyGearSet :
        GetFrenquencyGearSet( nParam, body );
        break;

    case LedControll::CmdFlashFrenquencyGearClose : // 0x04
        GetFlashFrenquencyGearClose( nParam, body );
        break;

    case LedControll::CmdFlashGearAlwaysRadianceClose : // 0x05
        GetFlashGearAlwaysRadianceClose( nParam, body );
        break;

    case LedControll::CmdFlashGearAlwaysRadianceOpen : // 0x06
        GetFlashGearAlwaysRadianceOpen( nParam, body );
        break;

    case LedControll::CmdFlashFrenquencyGearWorkTimeSet : // 0x07
        GetFlashFrenquencyGearWorkTimeSet( nParam, body );
        break;

    case LedControll::CmdFlashFrenquencyLightSensitiveIfWork : // 0x08
        GetFlashFrenquencyLightSensitiveIfWork( nParam, body );
        break;

    case LedControll::CmdSyncModeDownTrigger : // 0x09
    case LedControll::CmdSyncModeUpTrigger :
    case LedControll::CmdSyncModeFollowTrigger :
        GetSyncModeCmd( nParam, body );
        break;

    case LedControll::CmdTestFlashOpen :
    case LedControll::CmdTestFlashClose :
        GetTestFlashCmd( nParam, body );
        break;

    case LedControll::CmdLedTemperature : // New Device
    case LedControll::CmdLedFrequency :
    case LedControll::CmdLedWorkVoltage :
    case LedControll::CmdLedExternalTriggerSignalState :
    case LedControll::CmdSyncModeForFlash :
    case LedControll::CmdFlashRadianceChange :
    case LedControll::CmdFrenquencyRadianceChange :
        break;
    }
}

void QCmdGenerator::GetNewCmdAddr( QByteArray &body )
{
    const char cAddrValue = ( char ) 0xAA;
    char cAddress[ ] = { cAddrValue, cAddrValue, cAddrValue, cAddrValue, cAddrValue, cAddrValue };
    body.append( cAddress, sizeof ( cAddress ) );
}

void QCmdGenerator::GetControlCode4NewCmd( QByteArray &body, const bool bQuery )
{
    // D7......D0
    // 00010001B Query / Read from Led
    // 00010100B Not Query / Write to Led
    char cCtrlCode = 0;

    if ( bQuery ) {
        cCtrlCode = ( char ) 17; // 0x11
    } else {
        cCtrlCode = ( char  ) 20; // 0x14
    }

    body.append( cCtrlCode );
}

void QCmdGenerator::GetData4NewCmd( QByteArray &body, const LedControll::ECommand eCmd, qint32 nParam, const bool bQuery, const bool bFlash )
{
    // BCD
    // 十进制为96的码制，用压缩BCD码为1001 0110

    char cDataLen = 0;
    qint32 nDI = 0x04000300;
    QByteArray byData;
    QByteArray byDataDomain;

    switch ( eCmd ) {
    case LedControll::CmdTestConnect :
        byData.append( char ( 0 ) );
        cDataLen += 1;
        break;

    case LedControll::CmdFlashStateAlwaysRadianceChange : // Cmd 0x01
        break;

    case LedControll::CmdFlashFrenquencyIntensityTune : // 0x02
        nDI |= bFlash ? 0x00000007 : 0x00000006;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFlashGearSet : // 0x03
    case LedControll::CmdFrenquencyGearSet :
        nDI |= 0x00000002;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFlashFrenquencyGearClose : // 0x04
        break;

    case LedControll::CmdFlashGearAlwaysRadianceClose : // 0x05

        break;

    case LedControll::CmdFlashGearAlwaysRadianceOpen : // 0x06
        break;

    case LedControll::CmdFlashFrenquencyGearWorkTimeSet : // 0x07
        nDI |= bFlash ? 0x00000005 : 0x00000004;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFlashFrenquencyLightSensitiveIfWork : // 0x08
        nDI |= bFlash ? 0x0000000D : 0x0000000C;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdSyncModeDownTrigger : // 0x09
    case LedControll::CmdSyncModeUpTrigger :
    case LedControll::CmdSyncModeFollowTrigger :
    case LedControll::CmdSyncModeFollowDownTrigger :
        nDI |= 0x00000003;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdTestFlashOpen :
    case LedControll::CmdTestFlashClose :
        break;

    case LedControll::CmdLedTemperature : // New Device
        nDI |= 0x00000001;
        break;

    case LedControll::CmdLedFrequency :
        nDI |= 0x00000008;
        break;

    case LedControll::CmdLedWorkVoltage :
        nDI |= 0x00000009;
        break;

    case LedControll::CmdLedExternalTriggerSignalState :
        nDI |= 0x0000000A;
        break;

    case LedControll::CmdSyncModeForFlash :
        nDI |= 0x0000000B;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFlashRadianceChange :
        nDI |= 0x0000000F;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFrenquencyRadianceChange :
        nDI |= 0x0000000E;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;

    case LedControll::CmdFrameFrequency :
        nDI |= 0x00000010;
        cDataLen += 1;
        byData.append( ( char ) nParam );
        break;
    }

    if( !bQuery ) {
        cDataLen += 12;
    } else {
        cDataLen = 4;
    }

    body.append( cDataLen );
    byDataDomain.append( ( char * ) &nDI, 4 );
    if( !bQuery ) {
       char cPwd[ ] = { 0x02, 0x00, 0x00, 0x00, 0x0A, 0x0B, 0x0C, 0x0D };
       byDataDomain.append( cPwd, sizeof ( cPwd ) );
    }

    if( !bQuery ) {
        byDataDomain.append( byData );
    }

    for ( int nIndex = 0; nIndex < byDataDomain.length( ); nIndex++ ) {
        byDataDomain[ nIndex ] = byDataDomain.at( nIndex ) + 0x33;
    }

    body.append( byDataDomain );
}

void QCmdGenerator::GetCheckSum4NewCmd( QByteArray &body )
{
    char cCheckSum = ( char ) 0;

    foreach ( char c, body ) {
        cCheckSum += ( c % 256 );
    }

    body.append( cCheckSum );
}

void QCmdGenerator::GetNewCmdBody( QByteArray &body, const LedControll::ECommand eCmd, qint32 nParam, const bool bQuery, const bool bFlash )
{
    const char cFrameStart = ( char ) 0x68;

    GetNewCmdAddr( body ); // Address
    body.append( cFrameStart ); // Frame Start
    GetControlCode4NewCmd( body, bQuery ); // Control code
    GetData4NewCmd( body, eCmd, nParam, bQuery, bFlash ); // Data length / Data
    GetCheckSum4NewCmd( body ); // CheckSum
}
