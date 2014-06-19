#include "Header/syssetting.h"
#include "ui_syssetting.h"
#include "Common/commonfunction.h"

CSysSetting::CSysSetting(QWidget* mainWnd, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CSysSetting)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );

    pSettings = CCommonFunction::GetSettings( CommonDataType::CfgSysSet );
}

CSysSetting::~CSysSetting( )
{
    delete ui;
}

void CSysSetting::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CSysSetting::CalculatePos( )
{
    QRect rectWnd = this->geometry( );

    QString strName = "wgCommon";
    QWidget* pWgCommon = findChild< QWidget* >( strName );
    QRect rectCommon = pWgCommon->geometry( );
    pWgCommon->setGeometry( ( rectWnd.width( ) - 2 - rectCommon.width( ) ) / 2,
                          ( rectWnd.height( )  - 26 - rectCommon.height( ) ) / 2,
                          rectCommon.width( ), rectCommon.height( ) );

    strName.clear( );
    strName.append( "gbTimeLimit" );
    QGroupBox* pGB = findChild< QGroupBox* >( strName );
    QRect rectGB = pGB->geometry( );
    pGB->setGeometry( ( rectWnd.width( ) - 2 - rectGB.width( ) ) / 2,
                          ( rectWnd.height( )  - 26 - rectGB.height( ) ) / 2,
                          rectGB.width( ), rectGB.height( ) );

    strName.clear( );
    strName.append( "wgVideo" );
    QWidget* pVideo = findChild< QWidget* >( strName );
    QRect rectVideo = pVideo->geometry( );
    pVideo->setGeometry( ( rectWnd.width( ) - 2 - rectVideo.width( ) ) / 2,
                          ( rectWnd.height( )  - 26 - rectVideo.height( ) ) / 2,
                          rectVideo.width( ), rectVideo.height( ) );

    strName.clear( );
    strName.append( "wgVichle" );
    QWidget* pVichle = findChild< QWidget* >( strName );
    QRect rectVichle = pVichle->geometry( );
    pVichle->setGeometry( ( rectWnd.width( ) - 2 - rectVichle.width( ) ) / 2,
                          ( rectWnd.height( )  - 26 - rectVichle.height( ) ) / 2,
                          rectVichle.width( ), rectVichle.height( ) );

    strName.clear( );
    strName.append( "wgSpecial" );
    QWidget* pSpecial = findChild< QWidget* >( strName );
    QRect rectSpecial = pSpecial->geometry( );
    pSpecial->setGeometry( ( rectWnd.width( ) - 2 - rectSpecial.width( ) ) / 2,
                          ( rectWnd.height( )  - 26 - rectSpecial.height( ) ) / 2,
                          rectSpecial.width( ), rectSpecial.height( ) );
}

void CSysSetting::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CSysSetting::ReadFile( )
{
    if ( !QFile::exists( pSettings->fileName( ) ) ) {
        return;
    }
}

void CSysSetting::WriteFile( )
{
    QString strGropu = "CommonSet";
    pSettings->beginGroup( strGropu );
    pSettings->endGroup( );

    strGropu = "TimeLimit";
    pSettings->beginGroup( strGropu );
    pSettings->endGroup( );

    strGropu = "VideoMode";
    pSettings->beginGroup( strGropu );
    pSettings->endGroup( );

    strGropu = "CarLicence";
    pSettings->beginGroup( strGropu );
    pSettings->endGroup( );

    strGropu = "SpecialSet";
    pSettings->beginGroup( strGropu );
    pSettings->endGroup( );
}
