#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Implement/addadmindialog.h"
#include "Implement/addunitdialog.h"
#include "Implement/addparkdialog.h"
#include "Implement/addreceiverdialog.h"
#include "Implement/adddetectordialog.h"
#include "Implement/addgroupdialog.h"
#include "Implement/adduserdialog.h"

#include "Implement/modadmindialog.h"
#include "Implement/modunitdialog.h"
#include "Implement/modparkdialog.h"
#include "Implement/modreceiverdialog.h"
#include "Implement/moddetectordialog.h"
#include "Implement/modgroupdialog.h"
#include "Implement/moduserdialog.h"

#include "Batch/batchadmindialog.h"
#include "Batch/batchdetectordialog.h"
#include "Batch/batchgroupdialog.h"
#include "Batch/batchparkdialog.h"
#include "Batch/batchreceiverdialog.h"
#include "Batch/batchunitdialog.h"
#include "Batch/batchuserdialog.h"

#include "Comm/commfunction.h"

#include <QDateTime>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QMenu>
#include <QPushButton>
#include <QMessageBox>

extern QTextCodec *pCodec;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pDlgLogin = new CLoginDialog( NULL );

    QString strAutoUserName;
    if( pDlgLogin->AutoLogin( strAutoUserName ) )
    {
        Welcome( strAutoUserName );
    }
    else
    {
        Login();
    }

    pTimer = new QTimer();
    QObject::connect( pTimer, SIGNAL( timeout( ) ), this, SLOT( ShowTime( ) ) );
    pTimer->start( 1000 );

    ui->ptnAdd->hide();
    ui->ptnAddNext->hide();
    ui->ptnDel->hide();
    ui->ptnMod->hide();
    ui->ptnBatchAdd->hide();
    ui->ptnBatchAddNext->hide();

    // set top item 放在构造函数只执行一次，InitTree函数在刷新时会被调用，所以不适合放在InitTree里面。
    ui->treeWidget->topLevelItem( 0 )->setData( 0, Qt::WhatsThisRole, AdminItem );
    QVariant tmpValue;
    ItemInfoAdmin tmpItemInfo;
    tmpItemInfo.setId( "0" );
    tmpItemInfo.setType( "Province" );
    tmpItemInfo.setName( "中国" );
    tmpValue.setValue( tmpItemInfo );
    ui->treeWidget->topLevelItem( 0 )->setData( 0, Qt::UserRole, tmpValue );


    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;

    this->setWindowFlags( flags );

    ui->selfTabWidget->hide();
    ui->lblSelf->hide();
    ui->childrenTabWidget->hide();
    ui->lblChild1->hide();
    ui->childrenTabWidget_2->hide();
    ui->lblChild2->hide();
    InitTree();
}

MainWindow::~MainWindow()
{
    delete ui;
    if( pDlgLogin )
    {
        delete pDlgLogin;
        pDlgLogin = NULL;
    }
    if( pTimer )
    {
        delete pTimer;
        pTimer = NULL;
    }

    if( curItem )
    {
        delete curItem;
        curItem = NULL;
    }
}

void MainWindow::Login()
{
    pDlgLogin->InitLogin();
    if( QDialog::Rejected == pDlgLogin->exec() )
    {
        exit( 0 );
    }
   // else
    {
        QString strUser = pDlgLogin->GetUser();
        Welcome( strUser );
        this->show();
    }
 }

void MainWindow::Welcome(QString userName)
{
    QString strText = QString( "欢迎管理员 %1 登录系统" ).arg( userName );
    ui->lblWelcome->setText( strText );
}

void MainWindow::InitTree()
{
    GetItemInfo();
    // Admin
    for( int i = 0; i < AdminList.size(); ++i )
    {
        if( AdminList[i].getPid().toInt() == 0 )
        {
            const ItemInfoAdmin curValue = AdminList[i];
            QVariant var;
            var.setValue( curValue );

            //QTreeWidgetItem,构造时需要QStringList类型的参数，转换一下
            QTreeWidgetItem *pItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
            pItem->setData( 0, Qt::UserRole, var );
            pItem->setData( 0, Qt::WhatsThisRole, AdminItem );

            ui->treeWidget->topLevelItem( 0 )->addChild( pItem );

            ListItem( pItem, curValue.getId() );// loop递归
        }
    }

    // Unit
    for( int i = 0; i < AdminList.size(); ++i )
    {
        for( int j = 0; j < UnitList.size(); ++j )
        {
            if( AdminList[i].getId().toInt() == UnitList[j].getPid().toInt() )
            {
                // find parentItem 父节点：树中有节点名为 AdminList[i].getName()
                QTreeWidgetItem *pParentItem = NULL;
                QString strName = AdminList[i].getName();
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( strName, Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    break;// return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoAdmin tmpAdmin = tmpValue.value< ItemInfoAdmin >();
                    if( tmpAdmin.getId().toInt() == AdminList[i].getId().toInt() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }
                const ItemInfoUnit curValue = UnitList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, UnitItem );

                pParentItem->addChild( childItem );

                //ListItem( childItem, curValue.getId() );// loop递归
            }
        }
    }

    // Park
    for( int i = 0; i < UnitList.size(); ++i )
    {
        for( int j = 0; j < ParkList.size(); ++j )
        {
            if( UnitList[i].getId().toInt() == ParkList[j].getPid().toInt() )
            {
                // find parentItem
                bool isTopPark = ParkList[j].getParkParentID().toLongLong() == 0; // may > 2^32
                if( !isTopPark )
                {
                    continue; // not care child park
                }
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( UnitList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoUnit tmpUnit = tmpValue.value< ItemInfoUnit >();
                    if( tmpUnit.getId().toInt() == UnitList[i].getId().toInt() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }

                const ItemInfoPark curValue = ParkList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, ParkItem );

                pParentItem->addChild( childItem );
                ListItem( childItem, curValue.getId() );// loop递归 add child park
            }
        }
    }
#if false
    // child park
    for( int i = 0; i < ParkList.size(); ++i )
    {
        for( int j = 0; j < ParkList.size(); ++j )
        {
            // parkID 13位 need longlong int type
            if( ParkList[i].getId().toLongLong() == ParkList[j].getParkParentID().toLongLong() ) // have child park
            {
                // find pid parentItem
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( ParkList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    break;// return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoPark tmpPark = tmpValue.value< ItemInfoPark >();
                    if( tmpPark.getId().toLongLong() == ParkList[i].getId().toLongLong() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }
                const ItemInfoPark curValue = ParkList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, ParkItem );

                pParentItem->addChild( childItem );

                ListItem( childItem, curValue.getId() );// loop递归
            } // else{ continue; }
        }
    }
#endif
    // Receiver
    for( int i = 0; i < ParkList.size(); ++i )
    {
        for( int j = 0; j < ReceiverList.size(); ++j )
        {
            if( ParkList[i].getId().toLongLong() == ReceiverList[j].getPid().toLongLong() )
            {
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( ParkList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoPark tmpPark = tmpValue.value< ItemInfoPark >();
                    if( tmpPark.getId().toLongLong() == ParkList[i].getId().toLongLong() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }

                const ItemInfoReceiver curValue = ReceiverList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, ReceiverItem );

                pParentItem->addChild( childItem );

                //ListItem( childItem, curValue.getParkReceiverID() );// loop递归
            }
        }
    }

    // Detector
    for( int i = 0; i < ReceiverList.size(); ++i )
    {
        for( int j = 0; j < DetectorList.size(); ++j )
        {
            if( ReceiverList[i].getParkReceiverID().toLongLong() == DetectorList[j].getPid().toLongLong() )
            {
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( ReceiverList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoReceiver tmpReceiver = tmpValue.value< ItemInfoReceiver >();
                    if( tmpReceiver.getParkReceiverID().toLongLong() == ReceiverList[i].getParkReceiverID().toLongLong() ) // 主键ParkReceiverID
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }
                const ItemInfoDetector curValue = DetectorList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getId() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, DetectorItem );

                pParentItem->addChild( childItem );

                //ListItem( childItem, curValue.getReceiverDetectorID() );// loop递归
            }
        }
    }

    // Group
    for( int i = 0; i < UnitList.size(); ++i )
    {
        for( int j = 0; j < GroupList.size(); ++j ) // i = 1 j = 3
        {
            if( 0 == UnitList[i].getId().compare( GroupList[j].getPid() ) )
            {
                bool isTopGroup = GroupList[j].getParentID() == 0; // may > 2^32
                if( !isTopGroup )
                {
                    continue;
                }
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( UnitList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoUnit tmpUnit = tmpValue.value< ItemInfoUnit >();
                    if( tmpUnit.getId().toInt() == UnitList[i].getId().toInt() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }

                const ItemInfoGroup curValue = GroupList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, GroupItem );

                pParentItem->addChild( childItem );
                ListItem( childItem, QString::number( curValue.getId() ) );// loop递归 add child group
            }
        }
    }

    // User
    for( int i = 0; i < GroupList.size(); ++i )
    {
        for( int j = 0; j < UserList.size(); ++j )
        {
            if( GroupList[i].getId() ==  UserList[j].getPid()  )
            {
                QTreeWidgetItem *pParentItem = NULL;
                QList< QTreeWidgetItem *> lstParent = ui->treeWidget->findItems( GroupList[i].getName(), Qt::MatchRecursive );
                if( lstParent.isEmpty() )
                {
                    return;
                }

                for( int k = 0; k < lstParent.size(); ++k )
                {
                    QVariant tmpValue = lstParent[k]->data( 0, Qt::UserRole );
                    ItemInfoGroup tmpGroup = tmpValue.value< ItemInfoGroup >();
                    if( tmpGroup.getId() == GroupList[i].getId() )
                    {
                        pParentItem = lstParent[k];
                        break;
                    }
                }

                if( pParentItem == NULL )
                {
                    break;
                }

                const ItemInfoUser curValue = UserList[j];
                QVariant var;
                var.setValue( curValue );

                QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( curValue.getName() ) );
                childItem->setData( 0, Qt::UserRole, var );
                childItem->setData( 0, Qt::WhatsThisRole, UserItem );

                pParentItem->addChild( childItem );
                //ListItem( childItem, QString::number( curValue.getId() ) );// loop递归 必须不能要，因为userid 和groupid类型一样。
            }
        }
    }

    ui->treeWidget->show();
}

void MainWindow::ListItem( QTreeWidgetItem *pParentItem, QString pid )
{
    ItemType itemType = ( ItemType )pParentItem->data( 0, Qt::WhatsThisRole ).toInt();

    switch( itemType )
    {
    case AdminItem:
        for( int i = 0; i < AdminList.size(); ++i )
        {
            const ItemInfoAdmin curValue = AdminList[i];
            int nEqual = curValue.getPid().compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, AdminItem );

                pParentItem->addChild( child );

                ListItem( child, curValue.getId() );
            }
        }
        break;

    case UnitItem: // no use
        for( int i = 0; i < UnitList.size(); ++i )
        {
            const ItemInfoUnit curValue = UnitList[i];
            int nEqual = curValue.getPid().compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, UnitItem );

                pParentItem->addChild( child );

                ListItem( child, curValue.getId() );
            }
        }
        break;

    case ParkItem:
        for( int i = 0; i < ParkList.size(); ++i )
        {
            const ItemInfoPark curValue = ParkList[i];
            int nEqual = curValue.getParkParentID().compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, ParkItem );

                pParentItem->addChild( child );

                ListItem( child, curValue.getId() );
            }
        }
        break;

    case ReceiverItem: //no use
        for( int i = 0; i < ReceiverList.size(); ++i )
        {
            const ItemInfoReceiver curValue = ReceiverList[i];
            int nEqual = curValue.getPid().compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, ReceiverItem );

                pParentItem->addChild( child );

                ListItem( child, curValue.getParkReceiverID() );
            }
        }
        break;

    case DetectorItem: // no use
        for( int i = 0; i < DetectorList.size(); ++i )
        {
            const ItemInfoDetector curValue = DetectorList[i];
            int nEqual = curValue.getPid().compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getId() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, DetectorItem );

                pParentItem->addChild( child );

                ListItem( child, curValue.getReceiverDetectorID() );
            }
        }
        break;

    case GroupItem: // 死循环 groupid 不能为0.parentID为0表示没有父组。
        for( int i = 0; i < GroupList.size(); ++i )
        {
            const ItemInfoGroup curValue = GroupList[i];
            int nEqual = QString::number( curValue.getParentID() ).compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, GroupItem );

                pParentItem->addChild( child );

                ListItem( child, QString::number( curValue.getId() ) );
            }
        }
        break;

    case UserItem: // no use 死循环
        for( int i = 0; i < UserList.size(); ++i )
        {
            const ItemInfoUser curValue = UserList[i];
            int nEqual = QString::number( curValue.getPid() ).compare( pid );

            if( 0 == nEqual )
            {
                QTreeWidgetItem *child =new QTreeWidgetItem( QStringList( curValue.getName() ) );

                QVariant var;
                var.setValue( curValue );
                child->setData( 0, Qt::UserRole, var );
                child->setData( 0, Qt::WhatsThisRole, UserItem );

                pParentItem->addChild( child );

                ListItem( child, QString::number( curValue.getId() ) );
            }
        }
        break;

    }
}

void MainWindow::GetItemInfo()
{
    QString strStatus;
    bool bMay = IterfaceToMySql::GetInterface()->GetMySqlDb().PingMysql();
    if( false == bMay )
    {
       strStatus.append( "数据库连接失败！" );
       return;
    }

    // adminnistrative
    QString strSql = "select * from tabadministrativeinfo";
    QString strError;
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    int nRows = 0;
    int nCols = 5;
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoAdmin tmpItem;
        tmpItem.setId( lstRows[i] );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setPid( lstRows[++i] );
        tmpItem.setType( lstRows[++i] );
        //tmpItem.setItemType( AdminItem );
        AdminList.push_back( tmpItem );
    }

    // unit
    strSql = "select * from tabunitinfo";
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    lstRows.clear();
    nCols = 5;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoUnit tmpItem;
        tmpItem.setId( lstRows[i] );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setPid( lstRows[++i] );
        tmpItem.setAddress( lstRows[++i] );
       // tmpItem.setItemType( UnitItem );
        UnitList.push_back( tmpItem );
    }

    //park
    strSql = "select * from tabparkinfo";
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    lstRows.clear();
    nCols = 8;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoPark tmpItem;
        tmpItem.setId( lstRows[i] );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setSpace( lstRows[++i].toShort() );
        tmpItem.setUsedSpace( lstRows[++i].toShort() );
        tmpItem.setSelfNumber( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setParkParentID( lstRows[++i] );
        tmpItem.setPid( lstRows[++i] );
      //  tmpItem.setItemType( ParkItem );
        ParkList.push_back( tmpItem );
    }

    //receiver
    strSql = "select * from tabreceiverinfo";
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    lstRows.clear();
    nCols = 6;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoReceiver tmpItem;
        tmpItem.setPid( lstRows[i] );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setId( lstRows[++i] );
        tmpItem.setChannelID( lstRows[++i].toInt() );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setParkReceiverID( lstRows[++i] );
      //  tmpItem.setItemType( ReceiverItem );
        ReceiverList.push_back( tmpItem );
    }

    //detector
    strSql = "select * from tabdetectorinfo";
    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );

    lstRows.clear();
    nCols = 8;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoDetector tmpItem;
        tmpItem.setPid( lstRows[i] );
        tmpItem.setId( lstRows[++i] );
        tmpItem.setChannelID( lstRows[++i].toInt() );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setThreshold( lstRows[++i].toShort() );
        tmpItem.setDelayTime( lstRows[++i].toShort() );
        tmpItem.setDetectorReset( *lstRows[++i].toUtf8().data() ); // QByteArray.data
        tmpItem.setReceiverDetectorID( lstRows[++i] );
       // tmpItem.setItemType( DetectorItem );
        DetectorList.push_back( tmpItem );
    }

    // group unit 下级
    strSql = "select * from tabgroupinfo";
    lstRows.clear();
    nCols = 6;
    CommFunction::OperateSql( strSql, strError, lstRows );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoGroup tmpItem;
        tmpItem.setId( lstRows[i].toULongLong() );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setParentID( lstRows[++i].toULongLong() );
        tmpItem.setGroupRight( lstRows[++i].toULongLong() );
        tmpItem.setPid( lstRows[++i] ); // unitid
        GroupList.push_back( tmpItem );
    }

    // user group 下级
    strSql = "select * from tabuserinfo";
    lstRows.clear();
    nCols = 5;
    CommFunction::OperateSql( strSql, strError, lstRows );
    nRows = lstRows.count() / nCols;

    for( int i = 0; i < lstRows.count(); ++i )
    {
        ItemInfoUser tmpItem;
        tmpItem.setId( lstRows[i].toULongLong() );
        tmpItem.setName( lstRows[++i] );
        tmpItem.setComments( lstRows[++i] );
        tmpItem.setPid( lstRows[++i].toULongLong() ); // groupid
        tmpItem.setPassword( lstRows[++i] );
        UserList.push_back( tmpItem );
    }
}

/*
 *int groupID = pDlgLogin->GetGroupID();

        switch( groupID )
        {
        case 0: // highest level
            ui->ptnAdd->setEnabled( true );
            ui->ptnAddNext->setEnabled( true );
            ui->ptnDel->setEnabled( true );
            ui->ptnMod->setEnabled( true );
            break;

        case 1: // highest level to admin
            ui->ptnAdd->setEnabled( true );
            ui->ptnAddNext->setEnabled( true );
            ui->ptnDel->setEnabled( true );
            ui->ptnMod->setEnabled( true );
            break;

        case 11: // only add
            ui->ptnAdd->setEnabled( true );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 12: // modify and del
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( true );
            ui->ptnMod->setEnabled( true );
            break;

        case 2:
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 21: // only add
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 22: // modify and del
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 3:
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 31: // only add
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;

        case 32: // modify and del
            ui->ptnAdd->setEnabled( false );
            ui->ptnAddNext->setEnabled( false );
            ui->ptnDel->setEnabled( false );
            ui->ptnMod->setEnabled( false );
            break;
        }

*/
void MainWindow::InitFrame( ItemType type )
{
    curItem = ui->treeWidget->currentItem();

    switch( type )
    {
    case AdminItem:
    {       
        QTreeWidgetItem *pTopItem = ui->treeWidget->topLevelItem( 0 );
        if( curItem == pTopItem )
        {
           ui->ptnAdd->setText( "添加下级行政区" );
           ui->ptnBatchAdd->setText( "批量添加行政区" );
           ui->ptnAdd->show();
           ui->ptnBatchAdd->show();
           ui->ptnAddNext->hide();
           ui->ptnBatchAddNext->hide();
           ui->ptnDel->hide();
           ui->ptnMod->hide();

           addItemType = AddAdmin;
        }
        else
        {
            // Province City 不给增加企业的权限，具体到区和县。
            QVariant varValue = curItem->data( 0, Qt::UserRole );
            ItemInfoAdmin curInfo = varValue.value<ItemInfoAdmin>();
            QString cityType = curInfo.getType();

            if( 0 == cityType.compare( "District" ) )
            {
                addItemType = AddUnit;
                ui->ptnAdd->setText( "添加企业" );
                ui->ptnBatchAdd->setText( "批量添加企业" );
            }
            else
            {
                addItemType = AddAdmin;
                ui->ptnAdd->setText( "添加下级行政区" );
                ui->ptnBatchAdd->setText( "批量添加行政区" );
            }

            ui->ptnDel->setText( "删除该行政区" );
            ui->ptnMod->setText( "修改行政区信息" );

            ui->ptnAdd->show();
            ui->ptnBatchAdd->show();
            ui->ptnDel->show();
            ui->ptnMod->show();
            ui->ptnAddNext->hide();
            ui->ptnBatchAddNext->hide();

            //addNextItemType = AddUnit;
            modItemType = ModAdmin;
        }
        break;
    }
    case UnitItem:
    {
        ui->ptnAddNext->setText( "添加用户组" );
        ui->ptnBatchAddNext->setText( "批量添加用户组" );
        ui->ptnAdd->setText( "添加停车场" );
        ui->ptnBatchAdd->setText( "批量添加停车场" );
        ui->ptnDel->setText( "删除该企业" );
        ui->ptnMod->setText( "修改企业信息" );

        ui->ptnAdd->show();
        ui->ptnAddNext->show();
        ui->ptnDel->show();
        ui->ptnMod->show();
        ui->ptnBatchAdd->show();
        ui->ptnBatchAddNext->show();

        addItemType = AddPark;
        addNextItemType = AddGroup;
        modItemType = ModUnit;
        break;
    }
    case ParkItem:
    {
        ui->ptnAdd->setText( "添加子停车场" );
        ui->ptnBatchAdd->setText( "批量添加子停车场" );
        ui->ptnAddNext->setText( "添加接收器" );
        ui->ptnBatchAddNext->setText( "批量添加接收器" );
        ui->ptnDel->setText( "删除该停车场" );
        ui->ptnMod->setText( "修改停车场信息" );

        ui->ptnAdd->show();
        ui->ptnAddNext->show();
        ui->ptnBatchAdd->show();
        ui->ptnBatchAddNext->show();
        ui->ptnDel->show();
        ui->ptnMod->show();

        addItemType = AddPark;
        addNextItemType = AddReceiver;
        modItemType = ModPark;

        break;
    }
    case ReceiverItem:
    {
        ui->ptnAddNext->hide();
        ui->ptnBatchAddNext->hide();
        ui->ptnAdd->setText( "添加探测器" );
        ui->ptnBatchAdd->setText( "批量添加探测器" );
        ui->ptnDel->setText( "删除该接收器" );
        ui->ptnMod->setText( "修改接收器信息" );

        ui->ptnAdd->show();
        ui->ptnBatchAdd->show();
        ui->ptnDel->show();
        ui->ptnMod->show();

        addItemType = AddDetector;
        modItemType = ModReceiver;
        break;
    }
    case DetectorItem:
    {    
        ui->ptnAdd->hide();
        ui->ptnAddNext->hide();
        ui->ptnBatchAdd->hide();
        ui->ptnBatchAddNext->hide();
        ui->ptnDel->setText( "删除该探测器" );
        ui->ptnMod->setText( "修改探测器信息" );
        ui->ptnDel->show();
        ui->ptnMod->show();

        modItemType = ModDetector;
        break;
    }

    case GroupItem:
    {
        ui->ptnAddNext->hide();
        ui->ptnBatchAddNext->hide();
        ui->ptnAdd->setText( "添加用户" );
        ui->ptnBatchAdd->setText( "批量添加用户" );
        ui->ptnDel->setText( "删除该组" );
        ui->ptnMod->setText( "修改组信息" );

        ui->ptnAdd->show();
        ui->ptnBatchAdd->show();
        ui->ptnDel->show();
        ui->ptnMod->show();

        addItemType = AddUser;
        modItemType = ModGroup;
        break;
    }
    case UserItem:
    {
        ui->ptnAdd->hide();
        ui->ptnAddNext->hide();
        ui->ptnBatchAdd->hide();
        ui->ptnBatchAddNext->hide();
        ui->ptnDel->setText( "删除该用户" );
        ui->ptnMod->setText( "修改用户信息" );
        ui->ptnDel->show();
        ui->ptnMod->show();

        modItemType = ModUser;
        break;
    }

    }

    ui->frame->show();
}

void MainWindow::InitTableWidget(ItemType type, QTableWidget * parent, int nRows )
{
    curItem = ui->treeWidget->currentItem();

    int nCols = 0;
   // int nRows = curItem->childCount() + 1; // add self

    QStringList lstColName;
    QStringList lstCellName;

    switch( type )
    {
    case AdminItem:
    {
        // 自身信息
        //static AdminFrame *frame = new AdminFrame( ui->selfWidget );
        //frame->SetCurrentItem( curItem );
        //frame->show();
        // title
        nCols = 4;
        lstColName << "行政区编号" << "行政区名称" << "行政区类型" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoAdmin info = var.value<ItemInfoAdmin>();
        QList<ItemInfoAdmin> lstComments;
        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            info = var.value<ItemInfoAdmin>();
            lstComments.append( info );
        }

        QString type;
        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << lstComments[i].getId() << lstComments[i].getName();
            type = lstComments[i].getType();
            if( 0 == type.compare( "Province" ) )
            {
                type = "省";
            }
            else if( 0 == type.compare( "City" ) )
            {
                type = "市";
            }
            else //District
            {
                type = "区（县）";
            }
            lstCellName << type << lstComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        if( nRows == 0 )
        {
            nRows = 1;
        }
        for( int row = 0; row < nRows; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }
        break;
    }

    case UnitItem:
    {
        nCols = 4;
        lstColName << "企业编号" << "企业名称" << "企业地址" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoUnit info = var.value<ItemInfoUnit>();
        QList<ItemInfoUnit> lstComments;
        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            info = var.value<ItemInfoUnit>();
            lstComments.append( info );
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << lstComments[i].getId() << lstComments[i].getName()
                        << lstComments[i].getAddress() << lstComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        if( nRows == 0 )
        {
            nRows = 1;
        }
        for( int row = 0; row < nRows; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }
        break;
    }

    case ParkItem: // park or group
    {
        nCols = 6;
        lstColName << "停车场编号" << "停车场名称" << "总车位" << "已停车位数" << "自编码" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoPark info = var.value<ItemInfoPark>();
        QList<ItemInfoPark> lstComments;
        QList<ItemInfoGroup> lstGroupComments;
        ItemType varType;

        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        int nParkRow = 0;
        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            varType = (ItemType)curItem->child( i )->data( 0, Qt::WhatsThisRole ).toInt();

            if( varType == GroupItem )
            {
                ItemInfoGroup groupInfo = var.value<ItemInfoGroup>();
                lstGroupComments.append( groupInfo );
            }
            else
            {
                info = var.value<ItemInfoPark>();
                lstComments.append( info );
                nParkRow++;
            }
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << lstComments[i].getId() << lstComments[i].getName()
                        << QString::number( lstComments[i].getSpace() ) << QString::number( lstComments[i].getUsedSpace() )
                        << lstComments[i].getSelfNumber() << lstComments[i].getComments();
        }

        QStringList lstGroupName;
        for( int i = 0; i < lstGroupComments.size(); ++i )
        {
            lstGroupName << QString::number( lstGroupComments[i].getId() ) << lstGroupComments[i].getName()
                           << QString::number( lstGroupComments[i].getGroupRight() ) << lstGroupComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        int nRowMax = 0;
        if( nRows == 0 )
        {
            nRowMax = 1;
        }
        else   // 有孩子的情况才能分有几种孩子显示。
        {
#if false
            if( lstCellName.isEmpty() )
            {
                 ui->childrenTabWidget->hide();
                 ui->lblChild1->hide();
            }
            else
            {
                ui->childrenTabWidget->show();
                ui->lblChild1->show();
            }

            if( lstGroupName.isEmpty() )
            {
                 ui->childrenTabWidget_2->hide();
                 ui->lblChild2->hide();
            }
            else
            {
                ui->childrenTabWidget_2->show();
                ui->lblChild2->show();
            }
            parent->setRowCount( nParkRow );
#endif
            nRowMax = nParkRow;           
        }

        for( int row = 0; row < nRowMax; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }

        if( nRows == nParkRow ) // 只有park一种孩子
        {
            break;
        }

        // fill to group
        nCols = 4;
        ui->childrenTabWidget_2->setColumnCount( nCols );
        //ui->childrenTabWidget_2->setRowCount( nRows - nParkRow );

        lstColName.clear();
        lstColName << "组编号" << "组名称" << "组权限" << "备注";
        QTableWidgetItem *pItem2 = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem2 = new QTableWidgetItem( lstColName[i] );
            ui->childrenTabWidget_2->setHorizontalHeaderItem( i, pItem2 );
        }

        for( int row = 0; row < nRows - nParkRow ; ++row ) //
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstGroupName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                ui->childrenTabWidget_2->setItem( row, col, cellItem );
            }
        }

        break;
    }

    case ReceiverItem:  // receiver or childpark
    {
        nCols = 5;
        lstColName << "接收器编号" << "接收器名称" << "接收器信道编号" << "停车场编号+接收器编号" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemType varType;

        ItemInfoReceiver info = var.value<ItemInfoReceiver>();
        QList<ItemInfoReceiver> lstComments;
        QList<ItemInfoPark> lstParkComments;

        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        int nReceiverRow = 0;
        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            varType = (ItemType)curItem->child( i )->data( 0, Qt::WhatsThisRole ).toInt();

            if( varType == ParkItem )
            {
                ItemInfoPark ParkInfo = var.value<ItemInfoPark>();
                lstParkComments.append( ParkInfo );
            }
            else
            {
                info = var.value<ItemInfoReceiver>();
                lstComments.append( info );
                nReceiverRow++;
            }
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << lstComments[i].getId() << lstComments[i].getName()
                        << QString::number( lstComments[i].getChannelID() ) << lstComments[i].getParkReceiverID()
                        << lstComments[i].getComments();
        }

        QStringList lstNextParkName;
        for( int i = 0; i < lstParkComments.size(); ++i )
        {
            lstNextParkName << lstParkComments[i].getId() << lstParkComments[i].getName()
                            << QString::number( lstParkComments[i].getSpace() )
                            << QString::number( lstParkComments[i].getUsedSpace() )
                            << lstParkComments[i].getSelfNumber() << lstParkComments[i].getComments();
        }

        // fill cell

        QTableWidgetItem *cellItem = NULL;
        int nRowMax = 0;
        if( nRows == 0 )
        {
            nRowMax = 1;
        }
        else
        {
#if false
            if( lstCellName.isEmpty() )
            {
                ui->childrenTabWidget->hide();
                ui->lblChild1->hide();
            }
            else
            {
                ui->childrenTabWidget->show();
                ui->lblChild1->show();
            }

            if( lstNextParkName.isEmpty() )
            {
                ui->childrenTabWidget_2->hide();
                ui->lblChild2->hide();
            }
            else
            {
                ui->childrenTabWidget_2->show();
                ui->lblChild2->show();
            }

            parent->setRowCount( nReceiverRow );
#endif
            nRowMax = nReceiverRow;          
        }

        for( int row = 0; row < nRowMax; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }

        if( nRows == nReceiverRow )
        {
            break;
        }
        // fill to park
        nCols = 6;
        ui->childrenTabWidget_2->setColumnCount( nCols );
        //ui->childrenTabWidget_2->setRowCount( nRows - nReceiverRow );

        lstColName.clear();
        lstColName << "停车场编号" << "停车场名称" << "总车位" << "已停车位数" << "自编码" << "备注";

        QTableWidgetItem *pItem2 = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem2 = new QTableWidgetItem( lstColName[i] );
            ui->childrenTabWidget_2->setHorizontalHeaderItem( i, pItem2 );
        }

        for( int row = 0; row < nRows - nReceiverRow; ++row ) //
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstNextParkName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                ui->childrenTabWidget_2->setItem( row, col, cellItem );
            }
        }

        break;
    }

    case DetectorItem:
    {
        nCols = 7;
        lstColName << "探测器编号" << "探测器信道编号" << "阀值" << "拖延时间" << "探测器是否重启" << "停车场编号+接收器编号+探测器编号" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoDetector info = var.value<ItemInfoDetector>();
        QList<ItemInfoDetector> lstComments;
        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            info = var.value<ItemInfoDetector>();
            lstComments.append( info );
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << lstComments[i].getId() << QString::number( lstComments[i].getChannelID() )
                        << QString::number( lstComments[i].getThreshold() ) << QString::number( lstComments[i].getDelayTime() );
            int reset = (int)lstComments[i].getDetectorReset();
            QString strReset;
            if( reset == 0 )
            {
                strReset = "否";
            }
            else
            {
                strReset = "是";
            }

            lstCellName << strReset << lstComments[i].getReceiverDetectorID() << lstComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        if( nRows == 0 )
        {
            nRows = 1;
        }
        for( int row = 0; row < nRows; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }
        break;
    }

    case GroupItem: //
    {
        nCols = 4;
        lstColName << "组编号" << "组名称" << "组权限" << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoGroup info = var.value<ItemInfoGroup>();
        QList<ItemInfoGroup> lstComments;
        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            info = var.value<ItemInfoGroup>();
            lstComments.append( info );
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << QString::number( lstComments[i].getId() ) <<  lstComments[i].getName()
                        << QString::number( lstComments[i].getGroupRight() ) << lstComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        if( nRows == 0 )
        {
            nRows = 1;
        }
        for( int row = 0; row < nRows; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }
        break;
    }

    case UserItem:
    {
        nCols = 4;
        lstColName << "用户编号" << "用户名称" << "所属组编号"  << "备注";
        parent->setColumnCount( nCols );

        QTableWidgetItem *pItem = NULL;
        for( int i = 0; i < nCols; ++i )
        {
            pItem = new QTableWidgetItem( lstColName[i] );
            parent->setHorizontalHeaderItem( i, pItem );
        }

        // comments
        QVariant var = curItem->data( 0, Qt::UserRole );
        ItemInfoUser info = var.value<ItemInfoUser>();
        QList<ItemInfoUser> lstComments;
        if( 0 == nRows ) // self
        {
            lstComments.append( info );
        }

        for( int i = 0; i < nRows; ++i ) // have children enter
        {
            var = curItem->child( i )->data( 0, Qt::UserRole );
            info = var.value<ItemInfoUser>();
            lstComments.append( info );
        }

        for( int i = 0; i < lstComments.size(); ++i )
        {
            lstCellName << QString::number( lstComments[i].getId() ) <<  lstComments[i].getName()
                        << QString::number( lstComments[i].getPid() ) << lstComments[i].getComments();
        }

        // fill cell
        QTableWidgetItem *cellItem = NULL;
        if( nRows == 0 )
        {
            nRows = 1;
        }
        for( int row = 0; row < nRows; ++row ) // childcount + 1 => rows
        {
            for( int col = 0; col < nCols; ++col )
            {
                cellItem = new QTableWidgetItem( lstCellName[ row*nCols + col ] );
                cellItem->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
                parent->setItem( row, col, cellItem );
            }
        }

        break;
    }

    }
}

QTreeWidgetItem * MainWindow::FindCurrentItemParent( ItemType itemType )
{
    curItem = ui->treeWidget->currentItem();
    ItemType parkParentType = ( ItemType )curItem->data( 0, Qt::WhatsThisRole ).toInt();

    if( parkParentType == itemType )
    {
        return curItem;
    }

    QTreeWidgetItem * pParentItem = NULL;
    curItem = curItem->parent();

    while( parkParentType != itemType )
    {
        pParentItem = curItem;
        parkParentType = ( ItemType )pParentItem->data( 0, Qt::WhatsThisRole ).toInt();
        curItem = curItem->parent();
    }

    return pParentItem;
}

void MainWindow::GetDeleteSql( QTreeWidgetItem *pItem )
{
    ItemType itemType = (ItemType)pItem->data( 0, Qt::WhatsThisRole ).toInt();

    switch( itemType )
    {
    case AdminItem:
    {
        QStringList tmp = sqlHash.value( AdminItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( AdminItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoAdmin itemInfo = varValue.value< ItemInfoAdmin >();
        tmp << itemInfo.getId();
        sqlHash[AdminItem] = tmp;
        break;
    }

    case UnitItem:
    {
        QStringList tmp = sqlHash.value( UnitItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( UnitItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoUnit itemInfo = varValue.value< ItemInfoUnit >();
        tmp << itemInfo.getId();
        sqlHash[UnitItem] = tmp;
        break;
    }

    case ParkItem:
    {
        QStringList tmp = sqlHash.value( ParkItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( ParkItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoPark itemInfo = varValue.value< ItemInfoPark >();
        tmp << itemInfo.getId();
        sqlHash[ParkItem] = tmp;
        break;
    }

    case ReceiverItem:
    {
        QStringList tmp = sqlHash.value( ReceiverItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( ReceiverItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoReceiver itemInfo = varValue.value< ItemInfoReceiver >();
        tmp << itemInfo.getParkReceiverID();
        sqlHash[ReceiverItem] = tmp;
        break;
    }

    case DetectorItem:
    {
        QStringList tmp = sqlHash.value( DetectorItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( DetectorItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoDetector itemInfo = varValue.value< ItemInfoDetector >();
        tmp << itemInfo.getReceiverDetectorID();
        sqlHash[DetectorItem] = tmp;
        break;
    }

    case GroupItem:
    {
        QStringList tmp = sqlHash.value( GroupItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( GroupItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoGroup itemInfo = varValue.value< ItemInfoGroup >();
        tmp << QString::number( itemInfo.getId() );
        sqlHash[GroupItem] = tmp;
        break;
    }

    case UserItem:
    {
        QStringList tmp = sqlHash.value( UserItem );
        if( tmp.isEmpty() )
        {
            sqlHash.insert( UserItem, tmp );
        }
        QVariant varValue = pItem->data( 0, Qt::UserRole );
        ItemInfoUser itemInfo = varValue.value< ItemInfoUser >();
        tmp << QString::number( itemInfo.getId() );
        sqlHash[UserItem] = tmp;
        break;
    }

    }
}

void MainWindow::GetAllChild(QTreeWidgetItem *pItem)
{
    for( int i = 0; i < pItem->childCount() && pItem->childCount() != 0; ++i )
    {
        lstChildren.append( pItem->child( i ) );
        GetAllChild( pItem->child( i ) );
    }
}

//void MainWindow::OperateTabadministrativeinfoDb(QString strSql, DatabaseOperation dbOperation, QStringList &lstRows)
//{}

void MainWindow::ShowTime()
{
    QString strTime = QDateTime::currentDateTime().toString( "yyyy-mm-dd HH:mm:ss" );
    ui->lblTime->setText( QString( "当前时间： %1" ).arg( strTime ) );
    ui->lblTime->show();
}

void MainWindow::refreshSlot()
{
    QTreeWidgetItem *pTopItem = ui->treeWidget->topLevelItem( 0 );
    pTopItem->takeChildren();
    AdminList.clear();
    UnitList.clear();
    ParkList.clear();
    ReceiverList.clear();
    DetectorList.clear();
    GroupList.clear();
    UserList.clear();

    InitTree();
}

void MainWindow::AddAdminFunc()
{
    curItem = ui->treeWidget->currentItem();
    AddAdminDialog dialog( curItem );
    if( AddAdminDialog::Rejected == dialog.exec() )
    {
        return;
    }

    return;
    //////////////////////////////////////////////////////////////////////////////////////////////
    QStringList lstInfos = dialog.GetAdminItemInfo(); // no name comments type

    curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoAdmin tmpInfo = tmpValue.value<ItemInfoAdmin>();
    QString parentId = tmpInfo.getId();

    QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( lstInfos[1] ) );
    ItemInfoAdmin newItemInfo;
    newItemInfo.setId( lstInfos[0] );
    newItemInfo.setName( lstInfos[1] );
    newItemInfo.setComments( lstInfos[2] );
    newItemInfo.setType( lstInfos[3] );
    newItemInfo.setPid( parentId );

    QVariant newValue;
    newValue.setValue( newItemInfo );
    childItem->setData( 0, Qt::WhatsThisRole, AdminItem );
    childItem->setData( 0, Qt::UserRole, newValue );
    curItem->addChild( childItem );

    // insert table tabadministrativeinfo
    QString strSql = "insert into tabadministrativeinfo values( '%1', '%2', '%3', '%4', '%5' )";
    strSql = strSql.arg( lstInfos[0] ).arg( lstInfos[1] ).arg( lstInfos[2] ).arg( parentId ).arg( lstInfos[3] );
    QString strError;

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void MainWindow::AddUnitFunc()
{
    AddUnitDialog dialog;
    if( AddUnitDialog::Rejected == dialog.exec() )
    {
        return;
    }

    QStringList lstInfos = dialog.GetUnitItemInfo(); // no name comments address

    curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoAdmin tmpInfo = tmpValue.value<ItemInfoAdmin>();
    QString parentId = tmpInfo.getId();

    QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( lstInfos[1] ) );
    ItemInfoUnit newItemInfo;
    newItemInfo.setId( lstInfos[0] );
    newItemInfo.setName( lstInfos[1] );
    newItemInfo.setComments( lstInfos[2] );
    newItemInfo.setAddress( lstInfos[3] );
    newItemInfo.setPid( parentId ); // AdminstrativeID

    QVariant newValue;
    newValue.setValue( newItemInfo );
    childItem->setData( 0, Qt::WhatsThisRole, UnitItem );
    childItem->setData( 0, Qt::UserRole, newValue );
    curItem->addChild( childItem );

    // insert table tabunitinfo
    QString strSql = "insert into tabunitinfo values( '%1', '%2', '%3', '%4', '%5' )";
    strSql = strSql.arg( lstInfos[0] ).arg( lstInfos[1] ).arg( lstInfos[2] ).arg( parentId ).arg( lstInfos[3] );
    QString strError;

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void MainWindow::AddParkFunc()
{
    // find current greatest parent item is Admin
    QTreeWidgetItem *curParentItem = FindCurrentItemParent( AdminItem );
    QVariant curParentValue = curParentItem->data( 0, Qt::UserRole );
    ItemInfoAdmin curParentInfo = curParentValue.value<ItemInfoAdmin>();
    QString adminId = curParentInfo.getId(); // pid

    AddParkDialog dialog( adminId );
    if( AddParkDialog::Rejected == dialog.exec() )
    {
        return;
    }

    // pid is UnitID
    curItem = ui->treeWidget->currentItem(); // current is new item's parent

    ItemType parkType = ( ItemType )curItem->data( 0, Qt::WhatsThisRole ).toInt();  
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString parkParentId;
    QString parentId; // UnitID
    if( parkType == UnitItem )
    {
        parkParentId = "0";
        ItemInfoUnit tmpParentInfo = tmpValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }
    else // 找到最终父节点是Unit类型的。
    {
        ItemInfoPark tmpInfo = tmpValue.value<ItemInfoPark>();
        parkParentId = tmpInfo.getId();

        QTreeWidgetItem * pParentItem = FindCurrentItemParent( UnitItem );
        QVariant tmpParentValue = pParentItem->data( 0, Qt::UserRole );
        ItemInfoUnit tmpParentInfo = tmpParentValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }

    //No Name ParkSpace UsedSpace ParkSelfNum ParkComments
    QStringList lstInfos = dialog.GetParkItemInfo(); // no name comments address
    QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( lstInfos[1] ) );
    ItemInfoPark newItemInfo;
    newItemInfo.setId( lstInfos[0] );
    newItemInfo.setName( lstInfos[1] );
    newItemInfo.setSpace( lstInfos[2].toUInt() );
    newItemInfo.setUsedSpace( lstInfos[3].toUInt() );
    newItemInfo.setSelfNumber( lstInfos[4] );
    newItemInfo.setComments( lstInfos[5] );
    newItemInfo.setPid( parentId ); // UnitID
    newItemInfo.setParkParentID( parkParentId );

    QVariant newValue;
    newValue.setValue( newItemInfo );
    childItem->setData( 0, Qt::WhatsThisRole, ParkItem );
    childItem->setData( 0, Qt::UserRole, newValue );
    ui->treeWidget->currentItem()->addChild( childItem ); // curItem had changed

    // insert table tabparkinfo
    QString strSql = "insert into tabparkinfo values( '%1', '%2', %3, %4, '%5', '%6', '%7', '%8')";
    strSql = strSql.arg( lstInfos[0] ).arg( lstInfos[1] ).arg( lstInfos[2].toUInt() ).arg( lstInfos[3].toUInt() )
            .arg( lstInfos[4] ).arg( lstInfos[5] ).arg( parkParentId ).arg( parentId );
    QString strError;

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void MainWindow::AddReceiverFunc()
{
    curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoPark tmpInfo = tmpValue.value<ItemInfoPark>();
    QString parkId = tmpInfo.getId(); // pid

    AddReceiverDialog dialog( parkId );
    if( AddReceiverDialog::Rejected == dialog.exec() )
    {
        return;
    }

    // ReceiverNo ReceiverName ChannelID ReceiverComments parkReceiverId
    QStringList lstInfos = dialog.GetReceiverItemInfo(); // no name comments address

    QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( lstInfos[1] ) );
    ItemInfoReceiver newItemInfo;
    newItemInfo.setId( lstInfos[0] );
    newItemInfo.setName( lstInfos[1] );
    newItemInfo.setChannelID( lstInfos[2].toUShort());
    newItemInfo.setComments( lstInfos[3] );
    newItemInfo.setParkReceiverID( lstInfos[4] );
    newItemInfo.setPid( parkId ); // ParkID

    QVariant newValue;
    newValue.setValue( newItemInfo );
    childItem->setData( 0, Qt::WhatsThisRole, ReceiverItem );
    childItem->setData( 0, Qt::UserRole, newValue );
    curItem->addChild( childItem );

    // insert table tabreceiverinfo
    QString strSql = "insert into tabreceiverinfo values( '%1', '%2', '%3', %4, '%5', '%6' )";
    strSql = strSql.arg( parkId ).arg( lstInfos[1] ).arg( lstInfos[0] ).arg( lstInfos[2].toUShort() ).arg( lstInfos[3] ).arg( lstInfos[4] );
    QString strError;

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void MainWindow::AddDetectorFunc()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoReceiver tmpInfo = tmpValue.value<ItemInfoReceiver>();
    QString parkReceiverId = tmpInfo.getParkReceiverID(); // pid

    AddDetectorDialog dialog( parkReceiverId );
    if( AddDetectorDialog::Rejected == dialog.exec() )
    {
        return;
    }

    // DetectorNo DetectorChannelID sbxThreshold sbxDelayTime cmbReset DetectorComments ReceiverDetectorId
    QStringList lstInfos = dialog.GetDetectorItemInfo(); // no name comments address

    QTreeWidgetItem *childItem = new QTreeWidgetItem( QStringList( lstInfos[0] ) );
    ItemInfoDetector newItemInfo;
    newItemInfo.setId( lstInfos[0] );
    newItemInfo.setChannelID( lstInfos[1].toUInt() );
    newItemInfo.setThreshold( lstInfos[2].toUShort() );
    newItemInfo.setDelayTime( lstInfos[3].toUShort() );
    newItemInfo.setDetectorReset( lstInfos[4].toInt() );
    newItemInfo.setComments( lstInfos[5] );
    newItemInfo.setReceiverDetectorID( lstInfos[6] );
    newItemInfo.setPid( parkReceiverId ); // parkReceiverId is pid

    QVariant newValue;
    newValue.setValue( newItemInfo );
    childItem->setData( 0, Qt::WhatsThisRole, DetectorItem );
    childItem->setData( 0, Qt::UserRole, newValue );
    curItem->addChild( childItem );

    // insert table tabdetectorinfo reset: (BIT) use number
    QString strSql = "insert into tabdetectorinfo values( '%1', '%2', %3, '%4', %5, %6, %7, '%8' )";
    strSql = strSql.arg( parkReceiverId ).arg( lstInfos[0] ).arg( lstInfos[1].toUInt() ).arg( lstInfos[5] )
            .arg( lstInfos[2].toUShort() ).arg( lstInfos[3].toUShort() ).arg( lstInfos[4].toInt() ).arg( lstInfos[6] );
    QString strError;

    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows;
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );
}

void MainWindow::AddGroupFunc()
{
    // Unit下增加group parentid = 0， pid = unitid
    // group下增加子group parentid = 当前ItemID， pid = unitid

    curItem = ui->treeWidget->currentItem(); // current is new item's parent

    ItemType itemType = ( ItemType )curItem->data( 0, Qt::WhatsThisRole ).toInt();
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString groupParentId;
    QString parentId; // UnitID

    if( itemType == UnitItem )
    {
        groupParentId = "0";

        ItemInfoUnit tmpParentInfo = tmpValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }
    else // 找到最终父节点是Unit类型的。
    {
        ItemInfoGroup tmpInfo = tmpValue.value<ItemInfoGroup>();
        groupParentId = tmpInfo.getId();

        QTreeWidgetItem * pParentItem = FindCurrentItemParent( UnitItem );
        QVariant tmpParentValue = pParentItem->data( 0, Qt::UserRole );
        ItemInfoUnit tmpParentInfo = tmpParentValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }

     curItem = ui->treeWidget->currentItem();
     AddGroupDialog dialog( groupParentId, parentId, curItem ); // parentid = unitid = pid
     if( AddGroupDialog::Rejected == dialog.exec() )
     {
         return;
     }
}

void MainWindow::AddUserFunc()
{
    curItem = ui->treeWidget->currentItem(); // current is new item's parent

    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString pid; // GroupID
    ItemInfoGroup tmpInfo = tmpValue.value<ItemInfoGroup>();
    pid = QString::number( tmpInfo.getId() );

    AddUserDialog dialog( pid, curItem ); // groupid = pid
    if( AddUserDialog::Rejected == dialog.exec() )
    {
         return;
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit( 0 );
}

void MainWindow::on_actionChange_triggered()
{
    this->close();

    Login();
}

void MainWindow::on_treeWidget_customContextMenuRequested( const QPoint &pos )
{
    QTreeWidgetItem *curItem = ui->treeWidget->itemAt( pos );
    if( curItem == NULL )
    {
        QPoint point = QCursor::pos();
        QMenu *menu = new QMenu( ui->treeWidget );
        menu->addAction( QString( "刷新" ), this, SLOT( refreshSlot() ) );
        menu->move( point );
        menu->show();
    }
}

void MainWindow::ResizeControl( QTreeWidgetItem *pItem )
{
    // init
    {
        ui->childrenTabWidget->hide();
        ui->lblChild1->hide();
        ui->childrenTabWidget_2->hide();
        ui->lblChild2->hide();

        ui->selfTabWidget->setRowCount( 1 );
    }

    ItemType tmpType = ( ItemType )pItem->data( 0, Qt::WhatsThisRole ).toInt();
    curItem = ui->treeWidget->currentItem();
    int nChildCount = curItem->childCount();

    switch( tmpType )
    {
    case AdminItem:
    case ReceiverItem:
    case GroupItem:
    case UserItem:
    {
        ui->ptnMod->move( 225, 1 );
        ui->ptnDel->move( 330, 1 );

        if( nChildCount )
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 411 );
            ui->childrenTabWidget->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->childrenTabWidget_2->hide();
            ui->lblChild2->hide();
            ui->childrenTabWidget->setRowCount( nChildCount );
        }

        break;
    }

    case DetectorItem:
    {
        ui->ptnMod->move( 13, 1 );
        ui->ptnDel->move( 119, 1 );

        if( nChildCount )
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 411 );
            ui->childrenTabWidget->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->childrenTabWidget_2->hide();
            ui->lblChild2->hide();
            ui->childrenTabWidget->setRowCount( nChildCount );
        }

        break;
    }

    case UnitItem: // park and group
    {
        ui->ptnMod->move( 225, 1 );
        ui->ptnDel->move( 330, 1 );

        QTreeWidgetItem *childItem = NULL;
        ItemType childType;
        int nParkCount = 0;

        if( nChildCount )
        {
            for( int i = 0; i < nChildCount; ++i )
            {
                childItem = curItem->child( i );
                childType = ( ItemType )childItem->data( 0, Qt::WhatsThisRole ).toInt();
                if( childType == ParkItem )
                {
                    nParkCount++;
                }
            }
        }
        else
        {
            break;
        }

        if( 0 == nParkCount )
        {
            ui->childrenTabWidget_2->move( 340, 260 );
            ui->childrenTabWidget_2->resize( 620, 411 );
            ui->childrenTabWidget_2->show();
            ui->lblChild2->move( 340, 240 );
            ui->lblChild2->show();
            ui->childrenTabWidget->hide();
            ui->lblChild1->hide();

            ui->childrenTabWidget_2->setRowCount( nChildCount );
        }
        else if( nChildCount == nParkCount )
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 411 );
            ui->childrenTabWidget->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->childrenTabWidget_2->hide();
            ui->lblChild2->hide();

            ui->childrenTabWidget->setRowCount( nChildCount );
        }
        else
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 190 );
            ui->childrenTabWidget_2->move( 340, 480 );
            ui->childrenTabWidget_2->resize( 620, 190 );
            ui->childrenTabWidget->show();
            ui->childrenTabWidget_2->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->lblChild2->move( 340, 460 );
            ui->lblChild2->show();

            ui->childrenTabWidget->setRowCount( nParkCount );
            ui->childrenTabWidget_2->setRowCount( nChildCount - nParkCount );
        }
        break;
    }

    case ParkItem: // park and receiver
    {
        ui->ptnMod->move( 225, 1 );
        ui->ptnDel->move( 330, 1 );

        QTreeWidgetItem *childItem = NULL;
        ItemType childType;
        int nReceiverCount = 0;

        if( nChildCount )
        {
            for( int i = 0; i < nChildCount; ++i )
            {
                childItem = curItem->child( i );
                childType = ( ItemType )childItem->data( 0, Qt::WhatsThisRole ).toInt();
                if( childType == ReceiverItem )
                {
                    nReceiverCount++;
                }
            }
        }
        else
        {
            break;
        }

        if( 0 == nReceiverCount )
        {
            ui->childrenTabWidget_2->move( 340, 260 );
            ui->childrenTabWidget_2->resize( 620, 411 );
            ui->childrenTabWidget_2->show();
            ui->lblChild2->move( 340, 240 );
            ui->lblChild2->show();
            ui->childrenTabWidget->hide();
            ui->lblChild1->hide();

            ui->childrenTabWidget_2->setRowCount( nChildCount );
        }
        else if( nChildCount == nReceiverCount )
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 411 );
            ui->childrenTabWidget->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->childrenTabWidget_2->hide();
            ui->lblChild2->hide();

            ui->childrenTabWidget->setRowCount( nChildCount );
        }
        else
        {
            ui->childrenTabWidget->move( 340, 260 );
            ui->childrenTabWidget->resize( 620, 190 );
            ui->childrenTabWidget_2->move( 340, 480 );
            ui->childrenTabWidget_2->resize( 620, 190 );
            ui->childrenTabWidget->show();
            ui->childrenTabWidget_2->show();
            ui->lblChild1->move( 340, 240 );
            ui->lblChild1->show();
            ui->lblChild2->move( 340, 460 );
            ui->lblChild2->show();

            ui->childrenTabWidget->setRowCount( nReceiverCount );
            ui->childrenTabWidget_2->setRowCount( nChildCount - nReceiverCount );
        }
        break;
    }
    }
}

void MainWindow::on_treeWidget_itemClicked( QTreeWidgetItem *item, int column )
{
    ResizeControl( item );

    ItemType tmpType = ( ItemType )item->data( 0, Qt::WhatsThisRole ).toInt();
    curItem = ui->treeWidget->currentItem();
    int childCount = curItem->childCount();
    //ui->selfTabWidget->setRowCount( 1 );
    //ui->childrenTabWidget->setRowCount( childCount );
    //ui->selfTabWidget->setWindowTitle( "相关信息" );
    //ui->childrenTabWidget->setWindowTitle( "直接下级" );

    switch( tmpType )
    {
    case AdminItem:
        InitFrame( AdminItem );      
        InitTableWidget( AdminItem, ui->selfTabWidget, 0 ); // no children

        if( childCount )
        {
            QVariant var = curItem->data( 0, Qt::UserRole );
            ItemInfoAdmin info = var.value<ItemInfoAdmin>();
            QString type = info.getType();
            if( 0 == type.compare( "District") )
            {
                InitTableWidget( UnitItem, ui->childrenTabWidget, childCount );
            }
            else
            {
                InitTableWidget( AdminItem, ui->childrenTabWidget, childCount );
            }
            //ui->childrenTabWidget->show();
           //ui->lblChild1->show();
        }
        break;

    case UnitItem: // children : park or group
        InitFrame( UnitItem );
        InitTableWidget( UnitItem, ui->selfTabWidget, 0 );

        if( childCount )
        {
            InitTableWidget( ParkItem, ui->childrenTabWidget, childCount );
            //ui->childrenTabWidget->show();
        }
        break;

    case ParkItem: // children : receiver or childpark
        InitFrame( ParkItem );
        InitTableWidget( ParkItem, ui->selfTabWidget, 0 );

        if( childCount )
        {
            InitTableWidget( ReceiverItem, ui->childrenTabWidget, childCount );
            //ui->childrenTabWidget->show();
        }
        break;

    case ReceiverItem:
        InitFrame( ReceiverItem );
        InitTableWidget( ReceiverItem, ui->selfTabWidget, 0 );

        if( childCount )
        {
            InitTableWidget( DetectorItem, ui->childrenTabWidget, childCount );
            //ui->childrenTabWidget->show();
            //ui->lblChild1->show();
        }
        break;

    case DetectorItem:
        InitFrame( DetectorItem );
        InitTableWidget( DetectorItem, ui->selfTabWidget, 0 );
        break;

    case GroupItem:
        InitFrame( GroupItem );
        InitTableWidget( GroupItem, ui->selfTabWidget, 0 );

        if( childCount )
        {
            InitTableWidget( UserItem, ui->childrenTabWidget, childCount );
            //ui->childrenTabWidget->show();
            //ui->lblChild1->show();
        }
        break;

    case UserItem:
        InitFrame( UserItem );
        InitTableWidget( UserItem, ui->selfTabWidget, 0 );
        break;

    }
    ui->selfTabWidget->show();
    ui->lblSelf->show();
}

void MainWindow::on_ptnAdd_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要增加的选项！", "确定" );
        return;
    }

    switch( addItemType )
    {
    case AddAdmin:
        AddAdminFunc();
        break;

    case AddUnit:
        AddUnitFunc();
        break;

    case AddPark:
        AddParkFunc();
        break;

    case AddReceiver:
        AddReceiverFunc();
        break;

    case AddDetector:
        AddDetectorFunc();
        break;

    case AddGroup:
        AddGroupFunc();
        break;

    case AddUser:
        AddUserFunc();
        break;

    }
}

void MainWindow::on_ptnAddNext_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要增加的选项！", "确定" );
        return;
    }

    switch( addNextItemType )
    {
    case AddUnit:
        AddUnitFunc();
        break;

    case AddReceiver:
        AddReceiverFunc();
        break;

    case AddGroup:
        AddGroupFunc();
        break;
    }
}

void MainWindow::on_ptnMod_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要修改的选项！", "确定" );
        return;
    }

    switch( modItemType )
    {
    case ModAdmin:
        ModAdminFunc();
        break;

    case ModUnit:
        ModUnitFunc();
        break;

    case ModPark:
        ModParkFunc();
        break;

    case ModReceiver:
        ModReceiverFunc();
        break;

    case ModDetector:
        ModDetectorFunc();
        break;

    case ModGroup:
        ModGroupFunc();
        break;

    case ModUser:
        ModUserFunc();
        break;

    }
}

void MainWindow::on_ptnDel_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要删除的选项！","确定" );
        return;
    }

    sqlHash.clear();
    lstChildren.clear();

    QString strSql = "";
    QString strError;
    QString strWhere;
    curItem = ui->treeWidget->currentItem();

    //lstChildren = curItem->takeChildren(); // only get one grade children
    int tmp = QMessageBox::information(
                NULL, "提示",
                QString("确定删除【%1】，及其所有下级").arg( curItem->text( 0 ) ),
                "确定", "取消" ); // return int 0 1
    if( tmp == 1 )
    {
        return;
    }

    GetAllChild( curItem );
    GetDeleteSql( curItem );

    if( !lstChildren.isEmpty() )
    {
        QTreeWidgetItem * tmpItem = NULL;

        foreach( tmpItem, lstChildren )
        {
            GetDeleteSql( tmpItem );
        }
    }

    // detector
    QStringList tmpLstNo = sqlHash.value( DetectorItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString( "'%%1" ).arg( i + 1 ) + "', ";
        }
        strWhere += QString( "'%%1" ).arg( tmpLstNo.size() ) + "' );";

        strSql += "delete from tabdetectorinfo where ReceiverDetectorID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i] );
        }

        strWhere.clear();
    }

    // receiver
    tmpLstNo = sqlHash.value( ReceiverItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString("'%%1").arg( i + 1 ) + "', ";
        }
        strWhere += QString("'%%1").arg( tmpLstNo.size() ) + "' );";

        strSql += "delete from tabreceiverinfo where ParkReceiverID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i] );
        }

        strWhere.clear();
    }

    // park
    tmpLstNo = sqlHash.value( ParkItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString( "'%%1" ).arg( i + 1 ) +"', ";
        }
        strWhere += QString( "'%%1" ).arg( tmpLstNo.size() ) + "' );";

        strSql += "delete from tabparkinfo where ParkID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i] );
        }

        strWhere.clear();
    }

    // User
    tmpLstNo = sqlHash.value( UserItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString("%%1").arg( i + 1 ) + ", ";
        }
        strWhere += QString("%%1").arg( tmpLstNo.size() ) + " );";

        strSql += "delete from tabuserinfo where UserID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i].toULongLong() );
        }

        strWhere.clear();
    }

    // Group
    tmpLstNo = sqlHash.value( GroupItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString( "%%1" ).arg( i + 1 ) +", ";
        }
        strWhere += QString( "%%1" ).arg( tmpLstNo.size() ) + " );";

        strSql += "delete from tabgroupinfo where GroupID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i].toULongLong() );
        }

        strWhere.clear();
    }

    // unit
    tmpLstNo = sqlHash.value( UnitItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString( "'%%1" ).arg( i + 1 ) + "', ";
        }
        strWhere += QString( "'%%1" ).arg( tmpLstNo.size() ) + "' );";

        strSql += "delete from tabunitinfo where UnitID in ( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i] );
        }

        strWhere.clear();
    }

    //admin
    tmpLstNo = sqlHash.value( AdminItem );

    if( !tmpLstNo.isEmpty() )
    {
        for( int i = 0; i < tmpLstNo.size() - 1; ++i )
        {
            strWhere += QString( "'%%1" ).arg( i + 1 ) + "', ";
        }
        strWhere += QString( "'%%1" ).arg( tmpLstNo.size() ) + "' );";

        strSql += "delete from tabadministrativeinfo where AdministrativeID in( ";
        strSql += strWhere;

        for( int i = 0; i < tmpLstNo.size(); ++i )
        {
            strSql = strSql.arg( tmpLstNo[i] );
        }
    }


    IterfaceToMySql::GetInterface()->GetMySqlDb().DbCrud( strSql, strError );
    QStringList lstRows; // 没有执行它的话，执行多条删除语句后就无法与数据库连接上了。ping
    IterfaceToMySql::GetInterface()->GetMySqlDb().GetRowData( lstRows, strError );

    curItem = ui->treeWidget->currentItem();
    curItem->parent()->removeChild( curItem );
}


void MainWindow::ModAdminFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModAdminDialog dialog( curItem );

    if( dialog.exec() == ModAdminDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModUnitFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModUnitDialog dialog( curItem );

    if( dialog.exec() == ModUnitDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModParkFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModParkDialog dialog( curItem );

    if( dialog.exec() == ModParkDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModReceiverFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModReceiverDialog dialog( curItem );

    if( dialog.exec() == ModReceiverDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModDetectorFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModDetectorDialog dialog( curItem );

    if( dialog.exec() == ModDetectorDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModGroupFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModGroupDialog dialog( curItem );

    if( dialog.exec() == ModGroupDialog::Rejected )
    {
        return;
    }
}

void MainWindow::ModUserFunc()
{
    curItem = ui->treeWidget->currentItem();
    ModUserDialog dialog( curItem );

    if( dialog.exec() == ModUserDialog::Rejected )
    {
        return;
    }
}

// batch add
void MainWindow::BatchAdminFunc()
{
    curItem = ui->treeWidget->currentItem();
    BatchAdminDialog dialog( curItem );

    if( dialog.exec() == BatchAdminDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchUnitFunc()
{
    curItem = ui->treeWidget->currentItem();
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoAdmin tmpInfo = tmpValue.value<ItemInfoAdmin>();
    QString pid = tmpInfo.getId();
    BatchUnitDialog dialog( pid, curItem );

    if( dialog.exec() == BatchUnitDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchParkFunc()
{
    QTreeWidgetItem *curParentItem = FindCurrentItemParent( AdminItem );
    QVariant curParentValue = curParentItem->data( 0, Qt::UserRole );
    ItemInfoAdmin curParentInfo = curParentValue.value<ItemInfoAdmin>();
    QString adminId = curParentInfo.getId(); // pid

    curItem = ui->treeWidget->currentItem();

    ItemType parkType = ( ItemType )curItem->data( 0, Qt::WhatsThisRole ).toInt();
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString parkParentId;
    QString parentId; // UnitID
    if( parkType == UnitItem )
    {
        parkParentId = "0";
        ItemInfoUnit tmpParentInfo = tmpValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }
    else // 找到最终父节点是Unit类型的。
    {
        ItemInfoPark tmpInfo = tmpValue.value<ItemInfoPark>();
        parkParentId = tmpInfo.getId();

        QTreeWidgetItem * pParentItem = FindCurrentItemParent( UnitItem );
        QVariant tmpParentValue = pParentItem->data( 0, Qt::UserRole );
        ItemInfoUnit tmpParentInfo = tmpParentValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }

    curItem = ui->treeWidget->currentItem();
    BatchParkDialog dialog( adminId, parkParentId, parentId,  curItem );

    if( dialog.exec() == BatchParkDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchReceiverFunc()
{
    curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoPark tmpInfo = tmpValue.value<ItemInfoPark>();
    QString parkId = tmpInfo.getId();

    BatchReceiverDialog dialog( parkId, curItem );

    if( dialog.exec() == BatchReceiverDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchDetectorFunc()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem(); // current is new item's parent
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    ItemInfoReceiver tmpInfo = tmpValue.value<ItemInfoReceiver>();
    QString parkReceiverId = tmpInfo.getParkReceiverID(); // pid

    curItem = ui->treeWidget->currentItem();
    BatchDetectorDialog dialog( curItem, parkReceiverId );

    if( dialog.exec() == BatchDetectorDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchGroupFunc()
{
    curItem = ui->treeWidget->currentItem(); // current is new item's parent

    ItemType itemType = ( ItemType )curItem->data( 0, Qt::WhatsThisRole ).toInt();
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString groupParentId;
    QString parentId; // UnitID

    if( itemType == UnitItem )
    {
        groupParentId = "0";

        ItemInfoUnit tmpParentInfo = tmpValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }
    else // 找到最终父节点是Unit类型的。
    {
        ItemInfoGroup tmpInfo = tmpValue.value<ItemInfoGroup>();
        groupParentId = tmpInfo.getId();

        QTreeWidgetItem * pParentItem = FindCurrentItemParent( UnitItem );
        QVariant tmpParentValue = pParentItem->data( 0, Qt::UserRole );
        ItemInfoUnit tmpParentInfo = tmpParentValue.value<ItemInfoUnit>();
        parentId = tmpParentInfo.getId();
    }

    curItem = ui->treeWidget->currentItem();
    BatchGroupDialog dialog( groupParentId, parentId, curItem );

    if( dialog.exec() == BatchGroupDialog::Rejected )
    {
        return;
    }
}

void MainWindow::BatchUserFunc()
{
    curItem = ui->treeWidget->currentItem();
    QVariant tmpValue = curItem->data( 0, Qt::UserRole );
    QString pid; // GroupID
    ItemInfoGroup tmpInfo = tmpValue.value<ItemInfoGroup>();
    pid = QString::number( tmpInfo.getId() );

    BatchUserDialog dialog( pid, curItem );

    if( dialog.exec() == BatchUserDialog::Rejected )
    {
        return;
    }
}


void MainWindow::on_ptnBatchAdd_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要批量添加的选项！", "确定" );
        return;
    }

    switch( addItemType )
    {
    case AddAdmin:
        BatchAdminFunc();
        break;

    case AddUnit:
        BatchUnitFunc();
        break;

    case AddPark:
        BatchParkFunc();
        break;

    case AddReceiver:
        BatchReceiverFunc();
        break;

    case AddDetector:
        BatchDetectorFunc();
        break;

    case AddGroup:
        BatchGroupFunc();
        break;

    case AddUser:
        BatchUserFunc();
        break;

    }
}

void MainWindow::on_ptnBatchAddNext_clicked()
{
    if( ui->treeWidget->currentItem() == NULL )
    {
        QMessageBox::information( NULL, "提示", "请选择要批量添加的选项！", "确定" );
        return;
    }

    switch( addNextItemType )
    {
    case AddUnit:
        BatchUnitFunc();
        break;

    case AddReceiver:
        BatchReceiverFunc();
        break;

    case AddGroup:
        BatchGroupFunc();
        break;
    }
}
