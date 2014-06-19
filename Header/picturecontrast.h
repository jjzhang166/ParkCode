#ifndef PICTURECONTRAST_H
#define PICTURECONTRAST_H

#include <QFrame>
#include <QCloseEvent>
#include <QShowEvent>
#include "mainwindow.h"

namespace Ui {
    class CPictureContrast;
}

class CPictureContrast : public QFrame
{
    Q_OBJECT

public:
    explicit CPictureContrast(QWidget* mainWnd, QWidget *parent = 0);
    ~CPictureContrast();

    void SetParams( QByteArray &byData, QByteArray &vData, int nMin, int nHour, int nAmount, bool bEnter );

protected:
    void  closeEvent ( QCloseEvent * event );
    void showEvent(QShowEvent *  );

signals:
    void SendTimeCardInfo( QByteArray &byData, QByteArray &vData, int nMin, int nHour, int nAmount, bool bEnter );

private:
    Ui::CPictureContrast *ui;
    MainWindow* pParent;

    QByteArray byData;
    QByteArray vData;
    int nMin;
    int nHour;
    int nAmount;
    bool bEnter;

private slots:
    void on_btnPass_clicked();
    void on_btnImg4_clicked();
    void on_btnImg3_clicked();
    void on_btnImg2_clicked();
    void on_btnImg1_clicked();
};

#endif // PICTURECONTRAST_H
