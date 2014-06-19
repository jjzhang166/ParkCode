#ifndef DLGALERT_H
#define DLGALERT_H

#include <QDialog>
#include <QResizeEvent>
#include "Common/logicinterface.h"

namespace Ui {
    class CDlgAlert;
}

class CDlgAlert : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgAlert(QWidget *parent = 0);
    ~CDlgAlert();

    void DisplayAlert( QStringList& lstData );

protected:
    void resizeEvent ( QResizeEvent * event );

private:
    void GetImage( QString& strAlert );
    void DisplayImage( QLabel* pLbl, CommonDataType::BlobType blob, QString& strWhere );
    inline void PlayAudio( QString& strName );
    inline void SendSms( QString& strInfo );

private:
    Ui::CDlgAlert *ui;
    QString strTrue;
    QString strSeprator;
    QString strSnapPath;

private slots:
    void on_tabAlert_cellDoubleClicked(int row, int column );
    void on_lblClose_linkActivated( QString );
};

#endif // DLGALERT_H
