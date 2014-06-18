#include "cdlgconfig.h"
#include "ui_cdlgconfig.h"

CDlgConfig::CDlgConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgConfig)
{
    ui->setupUi(this);
    ReadConfig( );
}

CDlgConfig::~CDlgConfig()
{
    delete ui;
}

int CDlgConfig::FillComboBox( QComboBox *pCbx, QString strInfo[ ][ 2 ], int nRow, const QString& strCurItem )
{
    int nCurrentIndex = 0;

    for ( int nIndex = 0; nIndex < nRow; nIndex++ ) {
        QString& strUSerData = strInfo[ nIndex ][ 1 ];
        pCbx->insertItem( nIndex, strInfo[ nIndex ][ 0 ], strUSerData );

        if ( strUSerData == strCurItem ) {
            nCurrentIndex = nIndex;
            pCbx->setCurrentIndex( nIndex );
        }
    }

    return nCurrentIndex;
}

void CDlgConfig::ReadConfig( )
{
    CConfigurator* pConfig = CConfigurator::CreateInstance( );
    QString strType;

    pConfig->ReadAppMainWindow( strType );
    QString strUIInfo[ 2 ][ 2 ] = { { "Demo界面", "Demo" }, { "黑名单报警界面", "Blacklist" } };
    FillComboBox( ui->cbxUIType, strUIInfo, 2, strType );

    pConfig->ReadVideoType( strType );
    QString strVideoInfo[ 9 ][ 2 ] = { { "静态图片文件", "PictureFile" },
                                       { "海康采集卡", "HkAnalog" },
                                       { "天敏采集卡", "TmAnalog" },
                                       { "天敏采集棒UV200", "TmUV200" },
                                       { "海康网络相机", "HkIPC" },
                                       { "捷威思网络相机", "JwsIPC" },
                                       { "深圳安普网络相机", "JBNV" },
                                       { "ONVIF网络相机", "OnvifIPC" },
                                       { "视频文件", "VideoFile" } };
    int nIndex = FillComboBox( ui->cbxVideoType, strVideoInfo, 9, strType );

    ui->spPlateWay->setValue( pConfig->ReadPlateWay( ) );

    pConfig->ReadIpcIP( strType );
    ui->edtIpcIP->setText( strType );

    ui->chxMainStream->setChecked( pConfig->ReadMainStream( ) );
    ui->chxVideoCapture->setChecked( pConfig->ReadVideoCapture( ) );
    ui->chxPlateThread->setChecked( pConfig->ReadPlateMultiThread( ) );

    connect( ui->cbxVideoType, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( OnVideoType_currentIndexChanged( int ) ) );
    ui->cbxVideoType->setCurrentIndex( -1 );
    ui->cbxVideoType->setCurrentIndex( nIndex );
}

void CDlgConfig::Saveconfig( )
{
    CConfigurator* pConfig = CConfigurator::CreateInstance( );
    int nIndex = ui->cbxUIType->currentIndex( );

    QString strType = ui->cbxUIType->itemData( nIndex ).toString( );
    pConfig->WriteAppMainWindow( strType );

    nIndex = ui->cbxVideoType->currentIndex( );
    strType = ui->cbxVideoType->itemData( nIndex ).toString( );
    pConfig->WriteVideoType( strType );

    int nWay = 1;
    if ( 0 != nIndex ) { // PictureFile
        nWay = ui->spPlateWay->value( );
    }

    pConfig->WritePlateWay( nWay );

    strType = ui->edtIpcIP->text( );
    pConfig->WriteIpcIP( strType );
    pConfig->WriteMainStream( ui->chxMainStream->isChecked( ) );
    pConfig->WriteVideoCapture( ui->chxVideoCapture->isChecked( ) );
    pConfig->WritePlateMultiThread( ui->chxPlateThread->isChecked( ) );

}

void CDlgConfig::on_btnOk_clicked()
{
    Saveconfig( );

    QMessageBox::information( this, "提示", "要使配置生效，请重启程序。" );
}

void CDlgConfig::on_btnClose_clicked()
{
    close( );
}

void CDlgConfig::EnableAllControls( bool bEnable )
{
    ui->spPlateWay->setEnabled( bEnable );
    ui->edtIpcIP->setEnabled( bEnable );
    ui->chxMainStream->setEnabled( bEnable );
    ui->chxVideoCapture->setEnabled( bEnable );
}

void CDlgConfig::EnableIPCControl( bool bEnable )
{
    ui->edtIpcIP->setEnabled( bEnable );
    ui->chxMainStream->setEnabled( bEnable );
}

void CDlgConfig::EnbaleCaptureControl( bool bEnable )
{
    ui->chxVideoCapture->setEnabled( bEnable );
}

void CDlgConfig::OnVideoType_currentIndexChanged( int index )
{

    EnableAllControls( true );

    switch ( index ) {
    case 0 : // Picture
    case 7 :
        EnableAllControls( false );
        break;

    case 1 : // Capture
    case 2 :
        EnableIPCControl( false );
        break;

    case 3 : // IPC
    case 4 :
    case 5 :
    case 6 :
        break;
    }
}

void CDlgConfig::on_cbxVideoType_currentIndexChanged(int index)
{

}
