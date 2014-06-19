#include "qcmdparser.h"
#include <QDebug>

//
// Parse serial port command
//

QCmdParser::QCmdParser(QObject *parent) :
    QObject(parent)
{
}

QCmdParser::~QCmdParser( )
{

}

void QCmdParser::GetThreshold( QByteArray &data, QString &strInfo )
{
    QByteArray byHex = data.toHex(  );
    if ( 2 > byHex.count( ) ) {
        return;
    }

    qint8 cHigh = byHex.at( 0 );
    qint8 nLow = byHex.at( 1 );

    data.clear( );
    data.append( ( qint8 ) byHex.toShort( ) );

    strInfo.sprintf( "%c.%c", cHigh, nLow );
}

void QCmdParser::GetFloatValue( QByteArray &data, QString& strInfo )
{
    float fValue = 0.0F;

    char cValue = data.at( 0 );
    fValue = cValue * 0.01F;
    // fValue = ( cValue & 0x0F ) / 4.0F;
    // fValue += ( cValue >> 4 ) / 2.0F;

    qint32 nLen = data.length( );
    qint32 nValue = 0;

    for ( qint32 nIndex = 1; nIndex < nLen; nIndex++ ) {
        nValue |= ( data.at( nIndex ) << ( ( nIndex - 1 ) * 8 ) );
    }

    fValue += ( nValue * 1.0F );
    strInfo.sprintf( "%5.2f", fValue );
}

void QCmdParser::GetIntegerValue( QByteArray &data, QString &strInfo )
{
    qint32 nValue = data.at( 0 );

    strInfo.sprintf( "%d", nValue );
}

void QCmdParser::GeLedtIlluminance( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    strInfo = data.at( 0 ) ? "控制" : "不控制";
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetFrameFreqControl( QByteArray &data, QString &strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    switch ( data.at( 0 ) ) {
    case 1 :
       strInfo = "整倍频";
       break;

    case 2 :
       strInfo = "半倍频";
       break;

    case 3 :
       strInfo = "14.5帧";
       break;
    }
}

void QCmdParser::GetLedTemperature( QByteArray& data, QString& strInfo )
{
    if ( 3 > data.length( ) ) {
        return;
    }

    GetFloatValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedWorkState( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    strInfo = data.at( 0 ) ? "闪光" : "频闪";
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetTriggerMode( QByteArray &data, QString &strInfo )
{
    switch ( data.at( 0 ) ) {
    case 0 :
        strInfo = "下降沿触发";
        break;

    case 1:
        strInfo = "上升沿触发";
        break;

    case 2 :
        strInfo = "下降沿跟随模式";
        break;

    case 3 :
        strInfo = "上升沿跟随模式";
        break;
    }
}

void QCmdParser::GetLedFreqTriggerMode( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetTriggerMode( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFreqTime( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFlashTime( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFreqBrightness( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFlashBrightness( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFrequency( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedWorkVoltage( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetFloatValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedExternalTriggerSignalState( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    strInfo = data.at( 0 ) ? "异常" : "正常";
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFlashRadiance( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFrenquencyRadiance( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetIntegerValue( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::GetLedFlashTriggerMode( QByteArray& data, QString& strInfo )
{
    if ( 1 > data.length( ) ) {
        return;
    }

    GetTriggerMode( data, strInfo );
    qDebug( ) << Q_FUNC_INFO << endl;
}

void QCmdParser::ParseDataDomain( QByteArray &data, QString& strInfo, qint8& nIndex )
{
    // data.length( ) >= 4

    qint32 nDomainLen = 4;

    if ( nDomainLen > data.length( ) ) {
        return;
    }

    qint32 nDI = data[ 0 ];
    nDI |= ( data[ 1 ] << 8 );
    nDI |= ( data[ 2 ] << 16 );
    nDI |= ( data[ 3 ] << 24 );

    data.remove( 0, nDomainLen );
    nDomainLen = data.length( );

    strInfo = "";

    switch ( nDI ) {
    case 0x04000300 :
        nIndex = 0;
        break;

    case 0x0400030C : // 频闪光敏控制
        GeLedtIlluminance( data, strInfo );
        nIndex = 1;
        break;

    case 0x04000301 : // 温度
        GetLedTemperature( data, strInfo );
        nIndex = 3;
        break;

    case 0x04000302 : // 灯工作状态（00 =频闪；01=闪光）模式
        GetLedWorkState( data, strInfo );
        nIndex = 4;
        break;

    case 0x04000303 : // 频闪触发方式（00=上升沿触发；01=下降沿触发；02=跟随模式）同步
        GetLedFreqTriggerMode( data, strInfo );
        nIndex = 5;
        break;

    case 0x04000304 : // 输出脉宽0（百分比显示）频闪时间
        GetLedFreqTime( data, strInfo );
        nIndex = 7;
        break;

    case 0x04000305 : // 输出脉宽1（百分比显示）闪光时间
        GetLedFlashTime( data, strInfo );
        nIndex = 8;
        break;

    case 0x04000306 : // 输出脉宽2（百分比显示）频闪亮度
        GetLedFreqBrightness( data, strInfo );
        nIndex = 9;
        break;

    case 0x04000307 : // 输出脉宽3（百分比显示）闪光亮度
        GetLedFlashBrightness( data, strInfo );
        nIndex = 10;
        break;

    case 0x04000308 : // 频闪频率
        GetLedFrequency( data, strInfo );
        nIndex = 13;
        break;

    case 0x04000309 : // LED灯工作电压
        GetLedWorkVoltage( data, strInfo );
        nIndex = 14;
        break;

    case 0x0400030A : // 外部触发信号状态（00= 正常；01 = 异常）
        GetLedExternalTriggerSignalState( data, strInfo );
        nIndex = 15;
        break;

    case 0x0400030B : // 闪光触发方式（00=上升沿触发；01=下降沿触发；02=跟随模式）同步
        GetLedFlashTriggerMode( data, strInfo );
        nIndex = 6;
        break;

    case 0x0400030E : // 频闪光敏阀值
        GetThreshold( data, strInfo );
        nIndex = 11;
        break;

    case 0x0400030F : // 闪光光敏阀值
        GetThreshold( data, strInfo );
        nIndex = 12;
        break;

    case 0x0400030D : // 闪光光敏控制
        GeLedtIlluminance( data, strInfo );
        nIndex = 2;
        break;

    case 0x04000310 : // 帧频控制
        GetFrameFreqControl( data, strInfo );
        nIndex = 16;
        break;
    }
}
