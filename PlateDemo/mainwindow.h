#ifndef MAINWINDOW_PLATEDEMO_H
#define MAINWINDOW_PLATEDEMO_H

#include <QMainWindow>
#include <QFileInfoList>
#include "multimedia.h"
#include "vehiclelicense.h"

#define INVALID_HANDLE ( HANDLE ) ( 0XFFFFFFFF )

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CVehicleLicense* GetPlateRecognization( );
    void InsertPlate( UINT nChannel, bool bRet, QString& strFile );
    void ClearTable( );

    void Recognize( quint8* pData, ULONG& lSize );

    bool bStartVideo;

private:
    void RecognizeFile( QString& strName );
    bool Init( int nFormat );
    static void ImageStreamCallback( UINT nChannel, PVOID pContent );

private:
    Ui::MainWindow *ui;
    QString strFile;
    QFileInfoList lstFileInfo;
    CMultimedia* pMultimedia;
    CVehicleLicense* pVehicle;
    HANDLE hChannel[ 2];


private slots:
    void on_btnCapture_clicked();
    void on_btnClear_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_btnCloseVideo_clicked();
    void on_btnOpenVideo_clicked();
    void on_btnImagePath_clicked();
    void on_btnParam_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_PLATEDEMO_H
