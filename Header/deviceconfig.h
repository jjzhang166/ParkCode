#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QFrame>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QTreeWidget>
#include "mainwindow.h"
#include <QMenu>
#include <QSettings>
#include "Common/commonfunction.h"

namespace Ui {
    class CDeviceConfig;
}

class CDeviceConfig : public QFrame
{
    Q_OBJECT

public:
    explicit CDeviceConfig( QWidget* mainWnd, QWidget *parent = 0);
    ~CDeviceConfig();

protected:
    void  closeEvent ( QCloseEvent * event );
    void resizeEvent( QResizeEvent * );
    void CalculatePos( );

private:
    void CreateContextMenu( QTreeWidget* parent, QPoint pos );
    void AddTreeItem( bool bSubPark );
    inline void SetTreeItemFlag( QTreeWidgetItem* pItem );
    inline void FreeTreeItem( QTreeWidgetItem* pItem, bool bDeleteFromDb = false );

    void BuildTree( int ntID, QTreeWidgetItem& tvNode );
    void TraverseTree( QTreeWidgetItem& tvNode, QList< QTreeWidgetItem* >& lstDescendants );
    void SaveTree( CommonDataType::DatabaseOperation operate, QTreeWidgetItem& tvCurNode );
    QString GetMaxID( );

private:
    Ui::CDeviceConfig *ui;
    MainWindow* pParent;
    QMenu* pMenu;
    QTreeWidgetItem* pCurItem;
    QList< QAction* > actMenu;
    QSettings* pSetting;
    bool bNocardMode;

public:
    typedef enum __ItemType {
        None,
        Park,
        Controller,
    } ItemType;

    typedef struct __NodeData {
        QString strDevName;
        QString strDevID;
        QString strParentID;
        QString strDevType;
        QString strParkNum;
        QString strHostIP;
        QString strIPCIP;
        QString strParkNocardNum;
        bool bNocardMode;

        __NodeData( bool bPark = true )
        {
            strDevName = "ÐÂÉè±¸";
            strDevID = "0";
            strParentID = "0";
            strDevType = "tcc";
            strParkNum = bPark ? "88" : "0";
            strParkNocardNum = "0";
            strHostIP = CCommonFunction::GetHostIP( );
            strIPCIP = CCommonFunction::GetHostIP( );
            bNocardMode = false;
        }
    } NodeData, *PNodeData;

private:
    ItemType GetItemType( QTreeWidgetItem* pItem );
    inline NodeData& GetUserData( QTreeWidgetItem& node );
    inline PNodeData CreateUserData( QTreeWidgetItem& node, bool bPark = true );

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnMinimalize_clicked();
    void on_treeWidget_customContextMenuRequested(QPoint pos);
    void AddPark( );
    void AddSubPark( );
    void AddControler( );
    void ModifyAttribute( );
    void DeleteItem( );
    void DisplayTree( );
};

#endif // DEVICECONFIG_H
