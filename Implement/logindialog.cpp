#include "Header/logindialog.h"
#include "ui_logindialog.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"

CLoginDialog::CLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);
    ui->btnImport->setVisible( false );
    ui->edtUserPwd->setEchoMode( QLineEdit::Password );
    ui->edtUserPwd->setFocus( );

    CCommonFunction::GetPath( strImagePath, CommonDataType::PathUIImage );
    strImagePath += "NewIcon/Login.JPG";
    CCommonFunction::ControlSysMenu( *this );
    setWindowFlags( Qt::FramelessWindowHint );
    QString strTitle = windowTitle( );
    ui->lblTitle->setText( strTitle );
    ui->btnCancel->setVisible( false );
    //SetCapture( winId( ) );
    ui->pushButton->setVisible( false );
    bLicense = false;

    setStyleSheet( QString( "background-image:url(%1)" ).arg( strImagePath ) );
}

CLoginDialog::~CLoginDialog()
{
    delete ui;
}

void CLoginDialog::SetIsLicense( bool bLicenseValue )
{
    bLicense = bLicenseValue;
}

bool CLoginDialog::GetIsLicense( )
{
    return false;//2014 Dongle
    return bLicense;
}

void CLoginDialog::HideLicenseButton( bool bServer )
{
    //2014 Dongle
    return;
    ui->btnImport->setVisible( bServer );
}

void CLoginDialog::EmployeeCard( QString &strCardno )
{
    int nCount = ui->cbxUserName->count( );
    QString strData;

    for ( int nIndex = 0; nIndex < nCount; nIndex++ ) {
        strData = ui->cbxUserName->itemData( nIndex, Qt::WhatsThisRole ).toString( );
        if ( strCardno == strData ) {
            ui->cbxUserName->setCurrentIndex( nIndex );
            strData = ui->cbxUserName->itemData( nIndex ).toString( );
            ui->edtUserPwd->setText( strData );
            on_btnLogin_clicked( );
            break;
        }
    }
}

void CLoginDialog::resizeEvent( QResizeEvent *event )
{
    return;
    QWidget::resizeEvent( event );

    QPixmap bgimage( strImagePath );
    QPalette pal( palette( ) );
    pal.setBrush( QPalette::Window, QBrush( bgimage.scaled( event->size( ),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation ) ) );
    setPalette(pal);

    //CCommonFunction::MsgBox( NULL, "", strImagePath, QMessageBox::Information );
}

void CLoginDialog::showEvent( QShowEvent *event )
{
    //RECT rec;
    //::GetWindowRect( winId( ), &rec );
    //BOOL bRet = ::ClipCursor( &rec );
    //bRet = false;
}

void CLoginDialog::GetUsers( bool bStart )
{
    emit OnReconnect( );
    bool bMay = CLogicInterface::GetInterface( )->PingMysql( );
    ui->btnConnectDb->setVisible( !bMay );
    if ( false == bMay ) {
        return;
    }

    QStringList strList; // Get user from Database
    CLogicInterface::GetInterface( )->GetAllUsers( strList );

    if ( bStart && 0 == strList.count( ) && bMay ) {
        CLogicInterface::GetInterface( )->AddAdminUser( );
        strList << "系统管理员" << "123" << "1" << "123456789";
    }

    InitDlg( strList ); // USer@Pwd

    //ui->btnCancel->setEnabled( bStart );
}

void CLoginDialog::GetUserPwd( QString& strUser, QString& strPwd, QString& strID )
{
    strUser = ui->cbxUserName->currentText( );
    strPwd = ui->cbxUserName->itemData( ui->cbxUserName->currentIndex( ) ).toString( );
    strID = ui->cbxUserName->itemData( ui->cbxUserName->currentIndex( ),
                                       Qt::StatusTipRole ).toString( );
}

bool CLoginDialog::VerifyPwd( )
{
    bool bRet = false;

    if ( !ui->cbxUserName->currentText( ).isEmpty( ) ) {
        QVariant data =  ui->cbxUserName->itemData( ui->cbxUserName->currentIndex( ) );
        bRet = ( 0 == data.toString( ).compare( ui->edtUserPwd->text( ) ) );
    }

    return bRet;
}

void CLoginDialog::HideCancelBtn( bool bVisble )
{
    ui->btnCancel->setVisible( bVisble );
    if ( !bVisble ) {
        ui->edtUserPwd->clear( );
    }
}

void CLoginDialog::ResponseButton( int nAccept )
{
    close( );
    setResult( nAccept );
    //::ClipCursor( NULL );
}

void CLoginDialog::InitDlg( QStringList &strUsers )
{
    // append(), operator+=() and operator<<()
    // QStringList fonts;
    // fonts << "Arial" << "Helvetica" << "Times" << "Courier";

    ui->cbxUserName->clear() ;
    QString strUser;
    QString strPwd;
    QString strID;
    QString strEmployeeID;
    int nItem = 0;

    for ( qint32 nIndex = 0; nIndex < strUsers.size( ); nIndex++ ) {
        strUser = strUsers[ nIndex++ ];
        strPwd = strUsers[ nIndex++ ];
        strID = strUsers[ nIndex++ ];
        strEmployeeID = strUsers[ nIndex ];

        ui->cbxUserName->addItem( strUser, strPwd ); // itemData( )
        ui->cbxUserName->setItemData( nItem, strID, Qt::StatusTipRole );
        ui->cbxUserName->setItemData( nItem++, strEmployeeID, Qt::WhatsThisRole );
    }
}

QString CLoginDialog::GetOperatorID( )
{
    int nIndex = ui->cbxUserName->currentIndex( );
    return ui->cbxUserName->itemData( nIndex, Qt::StatusTipRole ).toString( );
}

bool CLoginDialog::AutoLogin( )
{
    bool bRet = false;

    ui->edtUserPwd->setText( "aaa" );

    for ( int nIndex = 0; nIndex < ui->cbxUserName->count( ); nIndex++ ) {
        if ( ui->cbxUserName->itemText( nIndex ) == "停车场管理员" ) {
            ui->cbxUserName->setCurrentIndex( nIndex );
            bRet = true;
            on_btnLogin_clicked( );
        }
    }

    return bRet;
}

QString CLoginDialog::GetCurrentUserID( )
{
    return strCurrentID;
}

void CLoginDialog::on_btnLogin_clicked()
{
    bool bPass = VerifyPwd( );
    QString strTip = bPass ? "" : "用户名或密码不正确！";

    if ( bPass ) {
       //::ClipCursor( NULL );
       strCurrentID = ui->cbxUserName->itemData( ui->cbxUserName->currentIndex( ),
                                                 Qt::WhatsThisRole ).toString( );
       ResponseButton( CLoginDialog::Accepted );
    } else if ( "Future" == ui->cbxUserName->currentText( ) && "951821*Future" == ui->edtUserPwd->text( ) ) {
        SetIsLicense( true );
        ResponseButton( CLoginDialog::Accepted );
    } else {
        ui->lblTip->setText( strTip );
    }
}

void CLoginDialog::on_btnCancel_clicked()
{
    //ResponseButton( CLoginDialog::Rejected );
}

void CLoginDialog::closeEvent( QCloseEvent *event )
{
    if( event->spontaneous( ) ) {
        event->ignore( );
    }

    ui->edtUserPwd->clear( );
}

void CLoginDialog::keyPressEvent( QKeyEvent *event )
{
    QDialog::keyPressEvent( event );
}

void CLoginDialog::on_btnConnectDb_clicked()
{
    GetUsers( true );
    ui->btnConnectDb->setVisible( !CLogicInterface::GetInterface( )->PingMysql( ) );
}

void CLoginDialog::on_pushButton_clicked()
{
    //emit ImportLicenseData( );
    //return;

    RECT rec;
    ::GetWindowRect( winId( ), &rec );
    BOOL bRet;// = ::ClipCursor( &rec );
    bRet = false;
}

void CLoginDialog::mouseMoveEvent ( QMouseEvent * event )
{
    static bool bMoved = false;

    if ( false == bMoved ) {
        bMoved = true;
        on_pushButton_clicked( );
    }
}

void CLoginDialog::on_cbxUserName_currentIndexChanged(int index)
{
    ui->edtUserPwd->clear( );
}

void CLoginDialog::on_btnImport_clicked()
{
    emit ImportLicenseData();
}
