#include "startupprocess.h"
#include "ui_startupprocess.h"
#include "Common/commonfunction.h"

#include <windows.h>

CStartupProcess* CStartupProcess::pFrame = NULL;

CStartupProcess::CStartupProcess(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CStartupProcess)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint );
    //QString strPath;
    //CCommonFunction::GetPath( strPath, CommonDataType::PathUIImage );
    //strPath += "StartupProcess.jpg";
    //QString strStyle = QString( "backfround-image:url(%1);" ).arg( strPath );

    //setStyleSheet( strStyle );
}

CStartupProcess::~CStartupProcess()
{
    delete ui;
}

CStartupProcess* CStartupProcess::GetFrame( QWidget* parent )
{
    if ( NULL == pFrame ) {
        pFrame = new CStartupProcess( parent );
        CCommonFunction::MySetWindowPos( pFrame );
        pFrame->show();
    }

    return pFrame;
}

void CStartupProcess::FreeFrame( )
{
    if ( NULL != pFrame ) {
        delete pFrame;
        pFrame = NULL;
    }
}

void CStartupProcess::UpdateInfo( QString strInfo )
{
    ui->lblInfo->setText( strInfo );
    pFrame->show();
}
