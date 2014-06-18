#include "startupthread.h"
#include "StartupProcess.h"
#include "Common/commonfunction.h"
#include <windows.h>

CStartupThread::CStartupThread(QObject *parent) :
    QThread(parent)
{
}

void CStartupThread::run( )
{
    exec( ); // Event loop
}

void CStartupThread::StartDlg( )
{
    CStartupProcess::GetFrame( )->show( );
}

void CStartupThread::DestroyDlg( )
{
    CStartupProcess::FreeFrame( );
}

void CStartupThread::UpdateInfo(QString strInfo)
{
    CStartupProcess::GetFrame( )->UpdateInfo( strInfo );
}

void CStartupThread::customEvent( QEvent * )
{
}
