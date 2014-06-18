#include "logindialog.h"
#include "ui_clogindialog.h"
#include "changecreaterpassworddialog.h"
#include "Comm/commfunction.h"

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

CLoginDialog::CLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbConnect( "localhost", "root", "root", "streetroadpark", 3306 );
    filePath = QApplication::applicationDirPath() + "/Data";

    //QString fileName = filePath + "/autoUser.ini";
    //pSettings = new QSettings( fileName, QSettings::IniFormat );

    InitLogin();
}

CLoginDialog::~CLoginDialog()
{
    delete ui;
}

void CLoginDialog::InitLogin()
{
    ui->edtPassword->setFocus();
    InitCombo();
}

void CLoginDialog::Clear()
{
    //ui->cbxUser
}

void CLoginDialog::InitCombo()
{
    ReadUserFile();
    if( -1 != ui->cbxUser->currentIndex() )
    {
        if( ui->cbxUser->itemData( ui->cbxUser->currentIndex(), Qt::StatusTipRole ).toBool() )
        {
            ui->edtPassword->setText( ui->cbxUser->itemData( ui->cbxUser->currentIndex() ).toString() );
        }
        else
        {
            ui->edtPassword->clear();
        }
       // ui->edtPassword->setText( ui->cbxUser->itemData( ui->cbxUser->currentIndex() ).toString() );
        ui->cbxRememberPass->setChecked( ui->cbxUser->itemData( ui->cbxUser->currentIndex(), Qt::StatusTipRole ).toBool() );
        //ui->cbxAutoLogin->setChecked( ui->cbxUser->itemData( ui->cbxUser->currentIndex(), Qt::WhatsThisRole ).toBool() );
    }
}

void CLoginDialog::ReadUserFile()
{
    ui->cbxUser->clear();
    QString setFileName = filePath + "/LastUser.ini";
    QSettings *pSettings = new QSettings( setFileName, QSettings::IniFormat );
    QStringList strGroups = pSettings->childGroups();

    QString groupName;
    int nItem = 0;

    foreach( groupName, strGroups )
    {
        QString strPassword = pSettings->value( groupName + "/password" ).toString();
        bool IsRemember = pSettings->value( groupName + "/isremember" ).toBool();
        bool IsAuto = pSettings->value( groupName + "/isauto" ).toBool();
        //QString strGroup = pSettings->group(); // username
        ui->cbxUser->addItem( groupName, strPassword );
        ui->cbxUser->setItemData( nItem, IsRemember, Qt::StatusTipRole );
        ui->cbxUser->setItemData( nItem++, IsAuto, Qt::WhatsThisRole );
    }

    return;
    ////////////////////////////////////////////////////////////////////////
    QString fileName = filePath + "/user.txt";
    QFile userFile( fileName );
    if( !userFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return;
    }

    QTextStream in( &userFile );
    //int nItem = 0;
    while( !in.atEnd() || nItem != 10 )// only read 10 lines
    {
        QString eachLine = in.readLine(); // read to \n
        QStringList user = eachLine.split( "," );

        ui->cbxUser->addItem( user[0], user[1] );
        ui->cbxUser->setItemData( nItem, user[2], Qt::StatusTipRole );
        ui->cbxUser->setItemData( nItem++, user[3], Qt::WhatsThisRole );
    }

    userFile.close(); // 局部变量没有关系，析构函数会自己看着办的。
}

void CLoginDialog::WriteUserFile()
{
    QString setFileName = filePath + "/LastUser.ini";
    QSettings *pSettings = new QSettings( setFileName, QSettings::IniFormat );

    pSettings->beginGroup( ui->cbxUser->currentText() );
    pSettings->setValue( QString("password"), ui->edtPassword->text() );
    pSettings->setValue( QString("isremember"), ui->cbxRememberPass->checkState() );
    pSettings->setValue( QString("isauto"), ui->cbxAutoLogin->checkState() );

    return;
    ////////////////////////////////////////////////////////
    QDir dir;
    if( !dir.exists( filePath ) )
    {
        dir.mkpath( filePath );
    }

    QString fileName = filePath+"/user.txt";

    QFile userFile( fileName );

    if( !userFile.open( QIODevice::Append | QIODevice::Text ) )
    {
        return;
    }

    QTextStream out( &userFile );
    out << ui->cbxUser->currentText() << ","
        << ui->edtPassword->text() << ","
        << ui->cbxRememberPass->checkState() << "," // 0 unChecked
        << ui->cbxAutoLogin->checkState()  << "\n" ;

    userFile.close();
}

void CLoginDialog::WriteAutoUser()
{
    QString fileName = filePath + "/autoUser.ini";
    QSettings *pSettings = new QSettings( fileName, QSettings::IniFormat );

    bool IsAutoLogin = ui->cbxAutoLogin->checkState();
    if( IsAutoLogin )
    {
        pSettings->beginGroup( QString( "User" ) );
        pSettings->setValue( "name", ui->cbxUser->currentText() );
        pSettings->setValue( "password", ui->edtPassword->text() );
    }
    else
    {
        pSettings->clear();
    }
}

QString CLoginDialog::GetUser()
{
    return ui->cbxUser->currentText();
}

qint64 CLoginDialog::GetGroupID()
{
    return groupId;
}

bool CLoginDialog::VerifyPass( QString &username, QString & password, QStringList & lstRows )
{
    bool bMay = IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql();
    if( false == bMay )
    {
        ui->lblStatus->setText( "数据库连接失败！" );
        return 0;
    }

    QString strSql = "select UserName, UserPwd, GroupID from tabmanageruserinfo where UserName = '%1'";
    strSql = strSql.arg( username );
    QString strError;
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    //QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    if( lstRows.count() == 0 )
    {
        QMessageBox::information( this, QString("提示"), QString("没有此用户，请重新输入！"), "确定" );
        //ui->cbxUser->clear();
        ui->edtPassword->clear();
        ui->edtPassword->setFocus();
        ui->btnLogin->setVisible( true );
        return 0;
    }

    QString strPasswdDb = lstRows[1]; // 0 name, 1 password, 2 groupid
    if( 0 != password.compare( strPasswdDb ) )
    {
        QMessageBox::information( this, QString("提示"), QString("密码错误，请重新输入！"), "确定" );
        ui->edtPassword->clear();
        ui->edtPassword->setFocus();
        ui->btnLogin->setVisible( true );
        return 0;
    }
    groupId = lstRows[2].toLongLong();

    return true;
}

bool CLoginDialog::AutoLogin( QString &strUserName )
{
    QString fileName = filePath + "/autoUser.ini";
    QSettings *pSettings = new QSettings( fileName, QSettings::IniFormat );

    QString strName = pSettings->value( "User/name" ).toString();
    QString strPassword = pSettings->value( "User/password" ).toString();
    QStringList lstRows;
    if( !strName.isEmpty() )
    {
        if( !VerifyPass( strName, strPassword, lstRows ) )
        {
            return false;
        }
        close();
        this->setResult( CLoginDialog::Accepted );

        QString setFileName = filePath + "/LastUser.ini";
        pSettings = new QSettings( setFileName, QSettings::IniFormat );

        pSettings->beginGroup( strName );
        pSettings->setValue( QString("password"), strPassword );
        pSettings->setValue( QString("isremember"), 1 );
        pSettings->setValue( QString("isauto"), 1 );

        strUserName = strName;

        return true;
    }
    else
    {
        return false;
    }
}

void CLoginDialog::on_btnLogin_clicked()
{
    //ui->btnLogin->setVisible( false );

    QString strName; 
    strName = ui->cbxUser->currentText();

    QString strPassword = ui->edtPassword->text();
    QStringList lstRows;
    if( !VerifyPass( strName, strPassword, lstRows ) )
    {
        ui->btnLogin->setVisible( true );
        return;
    }

    // 用户 密码都正确。
    WriteUserFile();
    WriteAutoUser();

    close(); // 没有它的话跳转不回 exec()的返回值。
    this->setResult( CLoginDialog::Accepted );
}

void CLoginDialog::on_cbxUser_currentIndexChanged(int index)
{
    bool IsRememberPass = ui->cbxUser->itemData( index, Qt::StatusTipRole ).toBool();
    ui->cbxRememberPass->setChecked( ui->cbxUser->itemData( ui->cbxUser->currentIndex(), Qt::StatusTipRole ).toBool() );
    //ui->cbxAutoLogin->setChecked( ui->cbxUser->itemData( ui->cbxUser->currentIndex(), Qt::WhatsThisRole ).toBool() );

    if( IsRememberPass )
    {
        ui->edtPassword->setText( ui->cbxUser->itemData( index ).toString( ) );
    }
    else
    {
        ui->edtPassword->clear();
    }
}

void CLoginDialog::on_ptnChangePassword_clicked()
{
    if( ui->cbxUser->currentText().isEmpty() )
    {
        QMessageBox::information( NULL, "提示", "请选择用户", "确定" );
        return;
    }

    QString strSql = "select * from tabmanageruserinfo where UserName = '%1'";
    strSql = strSql.arg( ui->cbxUser->currentText() );
    QString strError;
    QStringList lstRows;
    CommFunction::OperateSql( strSql, strError, lstRows );

    if( lstRows.isEmpty() )
    {
        QMessageBox::information( NULL, "提示", "没有此用户，请联系管理员新建用户！", "确定" );
        return;
    }

    QString userId = lstRows[0];
    QString password = lstRows[4];

    ChangeCreaterPasswordDialog dialog( userId, password );

    if( dialog.exec() == ChangeCreaterPasswordDialog::Rejected )
    {
        return;
    }

    QString newPass = dialog.GetPassword();
    strSql = "update tabmanageruserinfo set UserPwd = '%1' where UserID = '%2'";
    strSql = strSql.arg( newPass ).arg( userId );
    CommFunction::OperateSql( strSql, strError, lstRows );
}
