#ifndef BLACKLISTMAINWINDOW_H
#define BLACKLISTMAINWINDOW_H

#include <QMainWindow>
#include "Thread/qdirectorythread.h"
#include "Thread/qhkcapturecardthread.h"
#include "Thread/qtmcapturecardthread.h"
#include "Thread/qplatethread.h"
#include <QFileInfoList>
#include <QTableWidget>

namespace Ui {
class BlacklistMainWindow;
}

class BlacklistMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BlacklistMainWindow(QWidget *parent = 0);
    ~BlacklistMainWindow();

private:
    void Initialize( );
    void LoadLogoTitle( );
    inline QString GetSelectedFile( );
    inline void ButtonEnable( bool bPreEnable, bool bNextEnable );
    void SingleFileRecognize( bool bPreFile );
    inline void LoadPicture( const QString& strImage );
    inline void AddItem( QTableWidget* pTable, int nRow, int nCol, const QString& strText );
    void CheckBlacklistPlate( const QString& strPlate, const QString& strFile );
    
private slots:
    void HandlePlateResult( QStringList lstResult, int nChannel, bool bSuccess, bool bVideo );
    void on_btnSingleFile_clicked();

    void on_btnPreFile_clicked();

    void on_btnNextFile_clicked();

    void on_actBlacklist_triggered();

    void on_tableAlert_cellClicked(int row, int column);

    void on_actParameter_triggered();

private:
    Ui::BlacklistMainWindow *ui;
    int nFileIndex;
    QFileInfoList lstFiles;
    QStringList lstBlacklistPlates;
};

#endif // BLACKLISTMAINWINDOW_H
