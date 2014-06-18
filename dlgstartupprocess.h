#ifndef DLGSTARTUPPROCESS_H
#define DLGSTARTUPPROCESS_H

#include <QDialog>

namespace Ui {
    class CDlgStartupprocess;
}

class CDlgStartupprocess : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgStartupprocess(QWidget *parent = 0);
    ~CDlgStartupprocess();

    void UpdateInfo( QString strInfo );

public:
    static CDlgStartupprocess* GetFrame( QWidget* parent = NULL );
    static void FreeFrame( );

private:
    Ui::CDlgStartupprocess *ui;
    static CDlgStartupprocess* pFrame;
};

#endif // DLGSTARTUPPROCESS_H
