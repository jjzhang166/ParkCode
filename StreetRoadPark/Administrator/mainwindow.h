#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTableWidget>

#include "Implement/logindialog.h"
#include "ItemInfos/iteminfoadmin.h"
#include "ItemInfos/iteminfounit.h"
#include "ItemInfos/iteminfopark.h"
#include "ItemInfos/iteminforeceiver.h"
#include "ItemInfos/iteminfodetector.h"
#include "ItemInfos/iteminfogroup.h"
#include "ItemInfos/iteminfouser.h"
#include "ItemInfos/ItemType.h"

typedef enum __AddItemType
{
    AddAdmin,
    AddUnit,
    AddPark,
    AddReceiver,
    AddDetector,
    AddGroup,
    AddUser
}AddItemType;

typedef enum __ModItemType
{
    ModAdmin,
    ModUnit,
    ModPark,
    ModReceiver,
    ModDetector,
    ModGroup,
    ModUser
}ModItemType;


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void Login();
    void Welcome(QString userName );
    void InitTree();
    void ListItem( QTreeWidgetItem *pParentItem, QString pid );
    void GetItemInfo();
    void InitFrame( ItemType type );
    void InitTableWidget(ItemType type , QTableWidget *parent, int nRows );

    QTreeWidgetItem * FindCurrentItemParent( ItemType itemType );
    void GetDeleteSql( QTreeWidgetItem *pItem );
    void GetAllChild( QTreeWidgetItem *pItem );

    void AddAdminFunc();
    void AddUnitFunc();
    void AddParkFunc();
    void AddReceiverFunc();
    void AddDetectorFunc();
    void AddGroupFunc();
    void AddUserFunc();

    void ModAdminFunc();
    void ModUnitFunc();
    void ModParkFunc();
    void ModReceiverFunc();
    void ModDetectorFunc();
    void ModGroupFunc();
    void ModUserFunc();

    void BatchAdminFunc();
    void BatchUnitFunc();
    void BatchParkFunc();
    void BatchReceiverFunc();
    void BatchDetectorFunc();
    void BatchGroupFunc();
    void BatchUserFunc();

    void ResizeControl( QTreeWidgetItem* pItem );

private slots:
    void ShowTime();
    void refreshSlot();
    
    void on_actionExit_triggered();
    void on_actionChange_triggered();
    void on_treeWidget_customContextMenuRequested( const QPoint &pos );
    void on_treeWidget_itemClicked( QTreeWidgetItem *item, int column );

    void on_ptnAdd_clicked();
    void on_ptnAddNext_clicked();
    void on_ptnMod_clicked();
    void on_ptnDel_clicked();

    void on_ptnBatchAdd_clicked();
    void on_ptnBatchAddNext_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *pTimer;
    CLoginDialog* pDlgLogin;
    QList< ItemInfoAdmin > AdminList;
    QList< ItemInfoUnit > UnitList;
    QList< ItemInfoPark > ParkList;
    QList< ItemInfoReceiver > ReceiverList;
    QList< ItemInfoDetector > DetectorList;
    QList< ItemInfoGroup > GroupList;
    QList< ItemInfoUser > UserList;

    AddItemType addItemType;
    AddItemType addNextItemType;
    ModItemType modItemType;

    QTreeWidgetItem * curItem;
    QList< QTreeWidgetItem * > lstChildren;
    QHash< int, QStringList > sqlHash;
};

#endif // MAINWINDOW_H
