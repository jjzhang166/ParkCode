#ifndef STARTUPPROCESS_H
#define STARTUPPROCESS_H

#include <QFrame>

namespace Ui {
    class CStartupProcess;
}

class CStartupProcess : public QFrame
{
    Q_OBJECT

public:
    explicit CStartupProcess(QWidget *parent = 0);
    ~CStartupProcess();

    void UpdateInfo( QString strInfo );

public:
    static CStartupProcess* GetFrame( QWidget* parent = NULL );
    static void FreeFrame( );

private:
    Ui::CStartupProcess *ui;
    static CStartupProcess* pFrame;
};

#endif // STARTUPPROCESS_H
