#ifndef DLGQUERYOWNER_H
#define DLGQUERYOWNER_H

#include <QDialog>
#include <QResizeEvent>

namespace Ui {
    class CDlgQueryOwner;
}

class CDlgQueryOwner : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgQueryOwner(QWidget *parent = 0);
    ~CDlgQueryOwner();

protected:
    void resizeEvent( QResizeEvent * event );

private:
    Ui::CDlgQueryOwner *ui;

private slots:
    void on_lblClose_linkActivated(QString);
    void on_btnClose_clicked();
    void on_btnQuery_clicked();
};

#endif // DLGQUERYOWNER_H
