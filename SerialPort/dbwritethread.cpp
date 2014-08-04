#include "dbwritethread.h"
#include <QApplication>

CDbWriteThread* CDbWriteThread::pWriteImage = NULL;
//由分发线程根据消息类型实现操作分流，从而实现异步串行化处理
//A-->B-->C-->D-->E 操作步骤首先到分发线程，由他决定操作
//是在分发线程完成还是在自身类的子线程内完成
// DispatcherThread( A C E ) Post( B D ) to SubThread
//可以实现B(D)操作依赖A(C)操作的结果，这样的串行化

CDbWriteThread::CDbWriteThread(bool bImage, QObject *parent) :
    QThread(parent)
{
    pHistoryThread = NULL;
    bWriteImage = bImage;

}

bool CDbWriteThread::ConnectDb( )
{
    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams, false );
    bool bRet = interfaceNormal.GetMysqlDb( ).DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ],
                                                     lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

    return bRet;
}

CDbWriteThread* CDbWriteThread::GetWriteImageThread( )
{
    if( NULL == pWriteImage ) {
        pWriteImage = new CDbWriteThread( true );
        pWriteImage->start( );
        pWriteImage->moveToThread( pWriteImage );
    }

    return pWriteImage;
}

void CDbWriteThread::run( )
{
    ConnectDb( );
    exec( );
}

void CDbWriteThread::ExcuteSQL( CLogicInterface& intf, bool bSQL, CDbEvent::WriteParameter &paramter )
{
    if ( bSQL ) {
        if ( paramter.bSelect ) {
            QStringList lstRow;
            intf.ExecuteSql( paramter.strSql, lstRow );
        } else {
            intf.ExecuteSql( paramter.strSql );
        }
    } else {
        if ( paramter.bGarage ) {
            intf.OperateBlob( paramter.byData, true, paramter.blob, paramter.strSql );
        } else {
            QStringList lstRow;
            paramter.strSql = QString( "Select InsertInOutImage( %1, %2, '%3', '%4' )" ).arg(
                        QString::number( paramter.bEnter ), QString::number( paramter.nType ),
                        paramter.strCardNo, paramter.byData.toBase64( ) );
            intf.ExecuteSql( paramter.strSql, lstRow );
        }
    }
}

void CDbWriteThread::WriteData( CDbEvent::WriteParameter &paramter, bool bSQL )
{
    //qDebug( ) << Q_FUNC_INFO << paramter.strSql << endl;
    if ( !paramter.bDbHistory || paramter.bTimeCard ) {
        ExcuteSQL( interfaceNormal, bSQL, paramter );
    }

    if ( paramter.bDbHistory ) {
        if ( NULL == pHistoryThread ) {
            pHistoryThread = new CDbHistoryThread( );
        }

        paramter.bDbHistory = bSQL;
        if ( pHistoryThread->AddParameters( paramter ) ) {
            pHistoryThread->start( );
            pHistoryThread= NULL;
        }
    }
}

void CDbWriteThread::PostWriteImage( QEvent* e )
{
    CDbEvent* pEvent = ( CDbEvent* ) e;
    CDbEvent::WriteParameter& parameter = pEvent->GetParameter( );

    CDbEvent* pDbEvent = new CDbEvent( e->type( ) );

    pDbEvent->SetParameter( parameter.strSql, parameter.bDbHistory, parameter.bTimeCard,
                            parameter.bEnter, parameter.strCardNo, parameter.bGarage, parameter.nType,
                            parameter.bSelect, parameter.blob, parameter.byData );
    qApp->postEvent( GetWriteImageThread( ), pDbEvent );
}

void CDbWriteThread::customEvent( QEvent *e )
{
    CDbEvent* pEvent = ( CDbEvent* ) e;
    CDbEvent::WriteParameter& parameter = pEvent->GetParameter( );
    CDbEvent::UserEvent evtType = ( CDbEvent::UserEvent ) e->type( );

    switch ( evtType ) {
    case CDbEvent::SQLExternal :
        WriteData( parameter, true );
        break;

    case CDbEvent::SQLInternal :
        WriteData( parameter, true );
        break;

    case CDbEvent::ImgExternal :
        if ( bWriteImage ) {
            WriteData( parameter, false );
        } else {
            PostWriteImage( e );
        }
        break;

    case CDbEvent::ImgInternal :
        if ( bWriteImage ) {
            WriteData( parameter, false );
        } else {
            PostWriteImage( e );
        }
        break;
    }

    if ( pEvent->GetRefreshUI( ) ) {
        emit RefreshUI( pEvent->GetStoprdid( ) );
    }
}
