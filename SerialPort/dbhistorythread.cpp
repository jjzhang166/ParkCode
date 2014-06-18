#include "dbhistorythread.h"
#include <QDebug>

CDbHistoryThread::CDbHistoryThread(QObject *parent) :
    QThread(parent)
{
    connect( this, SIGNAL( finished( ) ), this, SLOT( ExitThread( ) ) );
    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
}

bool CDbHistoryThread::ConnectDb( )
{
    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams, true );
    bool bRet = interfaceHistory.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ],
                                                         lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

    return bRet;
}

void CDbHistoryThread::ExitThread( )
{
    delete this;
}

void CDbHistoryThread::DisconnectDb( )
{
    interfaceHistory.GetMysqlDb( ).DbDisconnect( );
}

bool CDbHistoryThread::AddParameters( CDbEvent::WriteParameter& parameter )
{
    CDbEvent::WriteParameter param = parameter;
    lstParameters.append( param );

    int nRecord = pSettings->value( "CommonCfg/HistoryRecord", 10 ).toInt( ) *
                             pSettings->value( "CommonCfg/HistoryEachRecordStmt", 4 ).toInt( );

    return ( nRecord <= lstParameters.count( ) ); // 20 / 4
}

void CDbHistoryThread::run( )
{
    if ( !ConnectDb( ) ) {
        return;
    }

    for ( int nIndex = 0; nIndex < lstParameters.count( ); nIndex++ ) {
        CDbEvent::WriteParameter& param = lstParameters[ nIndex];
        if ( param.bDbHistory ) {
            interfaceHistory.ExecuteSql( param.strSql );
        } else {
            interfaceHistory.OperateBlob( param.byData, true, param.blob, param.strSql );
        }
    }

    DisconnectDb( );
}
