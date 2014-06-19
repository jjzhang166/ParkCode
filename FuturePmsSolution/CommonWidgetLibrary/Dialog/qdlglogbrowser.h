#ifndef QDLGLOGBROWSER_H
#define QDLGLOGBROWSER_H

#include <QDialog>
#include "../MyWidget/qmysplitter.h"
#include <QTreeWidgetItem>
#include "../../ManipulateIniFile/qmanipulateinifile.h"

namespace Ui {
class QDlgLogBrowser;
}

class QDlgLogBrowser : public QDialog
{
    Q_OBJECT
    
public:
    explicit QDlgLogBrowser(QWidget *parent = 0);
    ~QDlgLogBrowser();

    void BrowseLog( const QManipulateIniFile::LogFileNames file );

private:
    void Initialize( );
    void BuildTree( );
    void ReadLog( const QManipulateIniFile::LogFileNames file, const QManipulateIniFile::LogTypes type, const QString& strDate );

    void FreeItemWidget( );
    
private:
    Ui::QDlgLogBrowser *ui;
    QMySplitter splitter;
    QManipulateIniFile manipulateFile;
    QCommonFunction commonFunction;
    QManipulateIniFile::LogFileNames logName;

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
};

#endif // QDLGLOGBROWSER_H
