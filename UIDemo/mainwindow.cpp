#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QMdiSubWindow>
#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <QSplitter>
#include <QWidgetAction>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDateTime>
#include "Common/logicinterface.h"
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QString strNumber = "k";
    int nNumber = strNumber.toInt( );
    strNumber = "";
    nNumber = strNumber.toInt( );
    QString strDateTime = "2011-01-06 01:02:03";
    QString strFormat = "yyyy-M-d H:m:s";
    QDateTime dt = QDateTime::fromString( strDateTime, strFormat );
    strDateTime = "";
    strDateTime = dt.toString( "yyyy-MM-dd HH:mm:ss" );
    ui->setupUi(this);
    //QPalette pal;
    //QPixmap map( "D:/WinParkUI/debug/Image/NewIcon/CommonBG-normal.jpg");
    //QBrush br( map );
    //pal.setBrush( backgroundRole( ), br );
    //setPalette( pal );
    //setAutoFillBackground( true );

    //mysql.DbConnect( "192.168.1.51", "test", "test", "parkadmin", 3306 );

    //QSplitter *splitter = new QSplitter(this);
    //splitter->setGeometry( this->geometry( ) );
    //splitter->addWidget( ui->pushButton );
    //splitter->addWidget( ui->tableWidget );
    //splitter->addWidget( ui->pushButton_3 );

    QWidgetAction* act = new QWidgetAction( ui->menuTest );
    QComboBox* cbx = new QComboBox( ui->menuTest );
    QStringList lst;
    lst << "1" << "2" << "3";
    cbx->addItems( lst );
    act->setDefaultWidget( cbx );
    //ui->toolBar->addAction( act );

    act->setText( "Hello" );
    ui->menuTest->addAction( act );

    act = new QWidgetAction( ui->menuTest );
    QDateTimeEdit* edit = new QDateTimeEdit( ui->menuTest );
    edit->setCalendarPopup( true );
    act->setDefaultWidget( edit );
    ui->menuTest->addAction( act );
}

MainWindow::~MainWindow()
{
    //mysql.DbDisconnect( );
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString strSql = ui->lineEdit->text( );
    if (  strSql.isEmpty( ) ) {
        strSql = "select stoprdid from stoprd";
    }

    QStringList lstStoprdID;
    CLogicInterface intef;

    QStringList lstParams;
    CCommonFunction::ConnectMySql( lstParams );
    bool bRet = intef.GetMysqlDb().DbConnect( lstParams[ 0 ], lstParams[ 1 ], lstParams[ 2 ], lstParams[ 3 ], lstParams[ 4 ].toUInt( ) );

    if ( !bRet ) {
        CCommonFunction::MsgBox( NULL, "提示", "连接数据库失败！" ,QMessageBox::Information );
        return;
    }

    intef.ExecuteSql( strSql, lstStoprdID );
    QString strPath = qApp->applicationDirPath( ) + "/Pic/";
    QDir dir;
    dir.mkpath( strPath );
    QString strFile = strPath + "%1%2.jpg";
    QString strTmp;
    QString strWhere = " where stoprdid = %1";
    QString strTmpWhere;

    foreach ( const QString& strID, lstStoprdID ) {
        strTmp = strFile.arg( strID, "In" );
        strTmpWhere = strWhere.arg( strID );
        intef.OperateBlob( strTmp, false, CommonDataType::BlobVehicleIn1, strTmpWhere );

        strTmp = strFile.arg( strID, "Out" );
        intef.OperateBlob( strTmp, false, CommonDataType::BlobVehicleOut1, strTmpWhere );
    }

    intef.GetMysqlDb( ).DbDisconnect( );

#if 0
    QFrame *frame = new QFrame;
   frame->resize(400,700);

   QPixmap pixmap("D:/WinParkUI/debug/Image/NewIcon/CommonBG-normal.jpg");
   QPixmap a = pixmap.scaled( frame->size( ) );
   QPalette   palette;
   palette.setBrush(frame->backgroundRole(),QBrush(a));
   frame->setPalette(palette);
   //frame->setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
   frame->setAutoFillBackground(true);
   frame->show();


   QPalette pal;
   QPixmap map( "D:/WinParkUI/debug/Image/NewIcon/CommonBG-normal.jpg");
   QBrush br( map );
   pal.setBrush( frame->backgroundRole( ), br );
   frame->setPalette( pal );
   frame->setAutoFillBackground( true );
   frame->show();

   QDialog dlg;

   QPalette pal;
   QPixmap map( "D:/WinParkUI/debug/Image/NewIcon/CommonBG-normal.jpg");
   QBrush br( map );
   pal.setBrush(dlg.backgroundRole( ), br );
   dlg.setPalette( pal );
   dlg.setAutoFillBackground( true );
   dlg.exec();
#endif
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strFile = "d:/MainBG.jpg";
    QString strSql = "Update stoprd Set invideo1 = ? where stoprdid = 1";
    QString strError;

    bool bRet = mysql.BlobWriteDb( strFile, strSql, strError );
    bRet = true;
}

void MainWindow::on_pushButton_3_clicked()
{
    //QWidget* pWG = ui->tableWidget->cellWidget( 0, 0 );
    //qDebug ( ) << pWG->metaObject( )->className( )<< endl;
}
