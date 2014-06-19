#include "Header/deviceconfig.h"
#include "ui_deviceconfig.h"
#include <QDebug>
#include "Common/commonfunction.h"
#include "Common/CommonType.h"
#include <QList>
#include <QFile>
#include <Dialog/spacedialog.h>
#include "Common/logicinterface.h"
#include "Dialog/channelattribute.h"

#define TCC     "tcc"
#define KZQ     "kzq"
#define ROOT    "root"

CDeviceConfig::CDeviceConfig(QWidget* mainWnd, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CDeviceConfig)
{
    ui->setupUi(this);
    pParent = dynamic_cast< MainWindow* > ( mainWnd );
    CCommonFunction::ConnectCloseButton( ui->lblClose );
    pCurItem = NULL;
    pMenu = NULL;

    pSetting = CCommonFunction::GetSettings( CommonDataType::CfgSystem );
    bNocardMode = pSetting->value( "CommonCfg/SenseOpenGate", false ).toBool( ) &&
            pSetting->value( "CommonCfg/NoCardWork", false ).toBool( );

    pSetting = CCommonFunction::GetSettings( CommonDataType::CfgDevice );
    //ReadFile( );

    DisplayTree( );
    ui->lblTitle->setText( windowTitle( ) );
}

void CDeviceConfig::DisplayTree( )
{
    QTreeWidgetItem& tvTopNode = *ui->treeWidget->topLevelItem( 0 );
    tvTopNode.setData( 0, Qt::UserRole, 0 );
    FreeTreeItem( &tvTopNode );
    PNodeData pData = CreateUserData( tvTopNode );
    pData->strDevType = ROOT;
    BuildTree( 1, tvTopNode );
}

CDeviceConfig::PNodeData CDeviceConfig::CreateUserData( QTreeWidgetItem &node, bool bPark )
{
    PNodeData pData = new NodeData( bPark );
    quint32 userData = ( quint32 ) pData;
    node.setData( 0, Qt::UserRole, userData );

    return pData;
}

CDeviceConfig::~CDeviceConfig()
{
    delete ui;
}

QString CDeviceConfig::GetMaxID( )
{
    QString strSql = "Select Max( shebeiid ) From treeview";
    QStringList lstRows;

    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstRows );

    return( 0 < lstRows.count( ) ) ? lstRows[ 0 ] : "1";
}

void CDeviceConfig::SaveTree( CommonDataType::DatabaseOperation operate, QTreeWidgetItem &tvCurNode )
{
    QString strSql = "";
    NodeData& data = GetUserData( tvCurNode );
    NodeData& parentData = GetUserData( *tvCurNode.parent( ) );
    QString strParentID = ( ROOT == parentData.strDevType ) ? "1" : parentData.strDevID;

    if ( CommonDataType::InsertData == operate ) {
        strSql = "Insert into treeview( shebeiname, parentid, shebeikind ) VALUES( '%1', %2, '%3')";
        strSql = strSql.arg( data.strDevName, strParentID, data.strDevType );
    } else if ( CommonDataType::UpdateData == operate ) {
        // tcc update parkinfo
        // kzp update roadconerinfo
        if ( TCC == data.strDevType ) {
            if ( data.bNocardMode ) {
                strSql = QString( "Update parkinfo Set parkname = '%1', parknum = %2, usedSpace = %3 Where shebeiid = %4" ).arg(
                                   data.strDevName, data.strParkNum, data.strParkNocardNum, data.strDevID );
            } else {
                strSql = QString( "Update parkinfo Set parkname = '%1', parknum = %2 Where shebeiid = %3" ).arg(
                                   data.strDevName, data.strParkNum, data.strDevID );
            }
        } else if ( KZQ == data.strDevType ) {
            strSql = QString( "Update roadconerinfo Set shebeiname = '%1', shebeiadr = %2, \
                              video1ip = '%3', video2ip = '%4' Where shebeiid = %5" ).arg(
                               data.strDevName, data.strParkNum, data.strHostIP, data.strIPCIP, data.strDevID );
        }

        tvCurNode.setText( 0, data.strDevName );
    }

    CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    data.strDevID = GetMaxID( );
    qDebug( ) << strSql << endl;
}

CDeviceConfig::NodeData& CDeviceConfig::GetUserData( QTreeWidgetItem &node )
{
    quint32 nData = node.data( 0, Qt::UserRole ).toUInt( );

    NodeData& data = *( ( PNodeData ) nData );

    return data;
}

void CDeviceConfig::BuildTree( int nID, QTreeWidgetItem& tvNode )
{
    // select distinct level from treeview
    // Select parkname,parkindex, parknum,shebeiid From parkinfo
    static const char* pszFormat = "Select shebeiname, shebeiid, parentid, \
                                   shebeikind, parknum, parkname, tmp, usedSpace \
            From ( select a.shebeiname, a.shebeiid, a.parentid, A.shebeikind, b.parknum, b.parkname, 'tmp', usedSpace \
                                          from treeview as a, parkinfo as b \
                                          where a.shebeiid = b.shebeiid And a.shebeikind = 'tcc' \
                                          union \
                                          select a.shebeiname, a.shebeiid, a.parentid, a.shebeikind, \
                   b.shebeiadr as parknum, b.video1ip as parkname, b.video2ip as tmp, '0' as usedSpace \
                                          from treeview a, roadconerinfo b \
                                          where a.shebeiid = b.shebeiid And a.shebeikind = 'kzq' ) as tmpTbale \
                                   Where tmpTbale.parentid = %d"; //1 Begin

    static const int nCols = 8;

    QStringList lstNodes;
    QString strSqlNodes;
    int nField = 0;

    strSqlNodes = strSqlNodes.sprintf( pszFormat, nID );

    //qDebug( ) << strSqlNodes << endl;
    CLogicInterface::GetInterface( )->ExecuteSql( strSqlNodes, lstNodes );
    int nNodeCount = lstNodes.count( ) / nCols;

    if ( 0 >= nNodeCount ) { // Exit Recursive
        return;
    }

    for ( int nNode = 0; nNode < nNodeCount; nNode++ ) {
        nField = nNode * nCols;
        QTreeWidgetItem* pChild = new QTreeWidgetItem( );
        PNodeData pData = CreateUserData( *pChild );

        QString& strText = lstNodes[ nField++ ];
        pData->strDevName = strText;

        pData->strDevID = lstNodes[ nField++ ];
        nID = pData->strDevID.toInt( );

        pData->strParentID = lstNodes[ nField++ ];
        pData->strDevType = lstNodes[ nField++ ];
        pData->strParkNum = lstNodes[ nField++ ];
        pData->strHostIP = lstNodes[ nField++ ];
        pData->strIPCIP = lstNodes[ nField++ ];
        pData->strParkNocardNum = lstNodes[ nField++ ];

        pChild->setData( 0, Qt::ToolTipRole, pData->strParkNum );
        pChild->setText( 0, strText );
        tvNode.addChild( pChild );

        BuildTree( nID, *pChild ); // Select Children
    }
}

void CDeviceConfig::closeEvent( QCloseEvent *event )
{
    pParent->ControlChild( event, this );
}

void CDeviceConfig::resizeEvent( QResizeEvent* )
{
    CalculatePos( );
}

void CDeviceConfig::CalculatePos( )
{
    //move( 123, 177 );
    return;
    QRect rectWnd = this->geometry( );

    QString strName = "widget";
    QWidget* pTW = findChild< QWidget* >( strName );
    QRect rectWg = pTW->geometry( );
    pTW->setGeometry( ( rectWnd.width( ) - rectWg.width( ) - 2 ) / 2,
                      ( rectWnd.height( )  - rectWg.height( ) - 2 ) / 2,
                      rectWg.width( ), rectWg.height( ) );
}

CDeviceConfig::ItemType CDeviceConfig::GetItemType( QTreeWidgetItem* pItem )
{
    ItemType itmData = None;
    if ( NULL == pItem ) {
        return itmData;
    }

    NodeData& data = GetUserData( *pItem );

    if ( TCC == data.strDevType ) {
        itmData = Park;
    } else if ( KZQ == data.strDevType ) {
        itmData = Controller;
    }

    return itmData;
}

void CDeviceConfig::AddTreeItem( bool bSubPark )
{
    if ( NULL == pCurItem ) { // Level == 2
        return;
    }

    ItemType itemData = GetItemType( pCurItem );
    if ( ( ( Controller == itemData ) && !bSubPark ) ||
         ( Controller == itemData && bSubPark ) ||
          ( None == itemData && !bSubPark ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                 "请选择停车场！", QMessageBox::Information );
        return;
    }


    QTreeWidgetItem* pChild = new QTreeWidgetItem( );
    PNodeData pData = CreateUserData( *pChild, bSubPark );
    pData->strDevType = bSubPark ? TCC : KZQ;
    pChild->setText( 0, bSubPark ? "新建停车场" : "新建通道控制器" );
    pData->strDevName = bSubPark ? "新建停车场" : "新建通道控制器";
    pChild->setData( 0, Qt::ToolTipRole, pData->strParkNum );
    pCurItem->addChild( pChild );
    SetTreeItemFlag( pChild );

    SaveTree( CommonDataType::InsertData, *pChild );
}

void CDeviceConfig::AddSubPark( )
{
    AddTreeItem( true );
}

void CDeviceConfig::AddControler( )
{
    AddTreeItem( false );
}

void CDeviceConfig::ModifyAttribute( )
{
    if ( NULL == pCurItem ) {
        return;
    }

    ItemType type = GetItemType( pCurItem );
    NodeData& data = GetUserData( *pCurItem );

    bool bGet = false;
    bool bSave = false;

    if ( Park == type ) {
        CSpaceDialog dlg( NULL );
        int nSpace = data.strParkNum.toInt( );

        bGet = false;
        dlg.SpaceNumber( nSpace, bGet );
        dlg.ParkName( data.strDevName, bGet );

        if ( bNocardMode ) {
            nSpace = data.strParkNocardNum.toInt( );
            dlg.SpaceNocardNumber( nSpace, bGet );
        }

        if ( CSpaceDialog::Accepted == dlg.exec( ) ) {
            bGet = true;
            dlg.SpaceNumber( nSpace, bGet );
            data.strParkNum = QString::number( nSpace );
            dlg.ParkName( data.strDevName, bGet );

            if ( bNocardMode ) {
                data.bNocardMode = bNocardMode;
                dlg.SpaceNocardNumber( nSpace, bGet );
                data.strParkNocardNum = QString::number( nSpace );
            }

            bSave = true;
        }
    } else if ( Controller == type ) {
        CChannelAttribute dlg( NULL );
        bGet = false;
        int nCan = data.strParkNum.toInt( );
        dlg.CANAddr( nCan, bGet );
        dlg.ChannelName( data.strDevName, bGet );
        dlg.HostIP( data.strHostIP, bGet );
        dlg.IPCIP( data.strIPCIP, bGet );

        if ( CChannelAttribute::Accepted == dlg.exec( ) ) {
            bGet = true;
            dlg.CANAddr( nCan, bGet );
            data.strParkNum = QString::number( nCan );
            dlg.ChannelName( data.strDevName, bGet );
            dlg.HostIP( data.strHostIP, bGet );
            dlg.IPCIP( data.strIPCIP, bGet );
            bSave = true;
        }
    }

    if ( bSave ) {
        pCurItem->setData( 0, Qt::ToolTipRole, data.strParkNum );
        SaveTree( CommonDataType::UpdateData, *pCurItem );
    }
}

void CDeviceConfig::DeleteItem( )
{
    if ( NULL == pCurItem ) {
        return;
    }

    QTreeWidgetItem* pParentIem = pCurItem->parent( );
    if ( NULL == pParentIem &&
         0 == pParentIem->childCount( ) ) { // Only root node
        return;
    }

    QVariant itemData = GetItemType( pCurItem );
    QString strText = "确定要删除所有停车场吗？";

    if ( NULL != pParentIem ) {
        switch ( itemData.toInt( ) ) {
        case Park :
            strText = "确定要删除 " + pCurItem->text( 0 ) + "及下属停车场与通道控制器吗？";
            break;

        case Controller :
            strText = "确定要删除 " + pCurItem->text( 0 );
            break;
        }
    }

    if ( QMessageBox::Ok == CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ),
                                                     strText, QMessageBox::Question ) ) {
        FreeTreeItem( pCurItem, true );
    }
}

void CDeviceConfig::TraverseTree( QTreeWidgetItem &tvNode, QList< QTreeWidgetItem* >& lstDescendants )
{
    QList< QTreeWidgetItem* > lstItem = tvNode.takeChildren( );
    PNodeData pData = ( PNodeData ) tvNode.data( 0, Qt::UserRole ).toInt( );

    if ( NULL != pData && pData->strDevType != ROOT ) {
        lstDescendants.append( &tvNode );
    }

    for ( int nItem = 0; nItem < lstItem.count( ); nItem++ ) {
        QTreeWidgetItem* pNode = lstItem[ nItem ];
        TraverseTree( *pNode, lstDescendants );
    }
}

void CDeviceConfig::FreeTreeItem( QTreeWidgetItem *pItem, bool bDeleteFromDb)
{
    QList< QTreeWidgetItem* > lstItem;
    TraverseTree( *pItem, lstItem ); // Get Descendants

    QList< QTreeWidgetItem* >::Iterator iteBegin = lstItem.begin( );
    QList< QTreeWidgetItem* >::Iterator iteEnd = lstItem.end( );
    QString strDevID = "";

    for ( ; iteBegin < iteEnd; iteBegin++ ) {
        pItem = *iteBegin;
        NodeData& data = GetUserData( *pItem );
        strDevID += strDevID.isEmpty( ) ? data.strDevID : ( "," + data.strDevID );

        delete &data;
        delete pItem;
    }

    if ( bDeleteFromDb ) {
        QString strSql = QString( "Delete From treeview Where shebeiid in ( %1 )" ).arg( strDevID );
        CLogicInterface::GetInterface( )->ExecuteSql( strSql );
    }
}

void CDeviceConfig::AddPark( )
{
    if ( NULL == pCurItem ) {
        return;
    }

    AddTreeItem( true );
}

void CDeviceConfig::SetTreeItemFlag( QTreeWidgetItem *pItem )
{
    pItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
}

void CDeviceConfig::CreateContextMenu( QTreeWidget *parent, QPoint pos )
{
    QTreeWidgetItem* pItem = parent->itemAt( pos );
    pCurItem = pItem;

    if ( NULL == pCurItem ) {
        return;
    }

    if ( NULL == pMenu ) {
        pMenu = new QMenu( parent );
        QAction* pAct = pMenu->addAction( "增加停车场", this, SLOT( AddPark( ) ) );
        actMenu.append( pAct );
        pAct = pMenu->addAction( "增加通道控制器", this, SLOT( AddControler( ) ) );
        actMenu.append( pAct );

        pMenu->addSeparator( );

        pAct = pMenu->addAction( "修改属性", this, SLOT( ModifyAttribute( ) ) );
        actMenu.append( pAct );
        pAct = pMenu->addAction( "刷新配置", this, SLOT(DisplayTree( ) ) );
        actMenu.append( pAct );
        pAct = pMenu->addAction( "删除当前项", this, SLOT( DeleteItem( ) ) );
        actMenu.append( pAct );
    }

    pMenu->exec( parent->cursor( ).pos( ) );
}

void CDeviceConfig::on_treeWidget_customContextMenuRequested(QPoint pos)
{
    CreateContextMenu( ui->treeWidget, pos );
}

void CDeviceConfig::on_btnMinimalize_clicked()
{
    setVisible( false );
    pParent->ControlMonitor( true );
}

void CDeviceConfig::on_lblClose_linkActivated(QString)
{
    close( );
}
