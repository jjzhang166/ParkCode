#ifndef QSERIALFRAME_H
#define QSERIALFRAME_H

#include <QFrame>
#include <QCloseEvent>
#include <QTimerEvent>
#include "qanalogthread.h"

namespace Ui {
class QSerialFrame;
}

class QSerialFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit QSerialFrame(QWidget *parent = 0);
    ~QSerialFrame();

private:
    typedef enum __ECmd {
        CmdCarOutEnter = 0,
        CmdCarInEnter,
        CmdCarOutLeave,
        CmdCarInLeave,
        CmdCarCard
    } ECmd;

    void GetCmd( ECmd eType, QByteArray& byCmd, char cCan, int nCardId = 0 );
    void GetCardId( QByteArray& byCardId, int nCardId );
    void SendCmd( QObject* pObj );

protected:
    void closeEvent( QCloseEvent* e );
    void timerEvent( QTimerEvent* e );
    
private slots:
    void HandleCommand( QByteArray byCmd );
    void on_btnTimer_clicked();

    void on_btn1_clicked();

    void on_btn0_clicked();

    void on_btn2_clicked();

    void on_btn4_clicked();

    void on_btn3_clicked();

    void on_btn5_clicked();

private:
    Ui::QSerialFrame *ui;
    bool bTimerStart;
    int nTimerId;
    QAnalogThread* pAnalogThread;
};

#endif // QSERIALFRAME_H
