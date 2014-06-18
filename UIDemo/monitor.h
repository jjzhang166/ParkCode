#ifndef MONITOR_H
#define MONITOR_H

#include <QFrame>

namespace Ui {
    class CMonitor;
}

class CMonitor : public QFrame
{
    Q_OBJECT

public:
    explicit CMonitor(QWidget *parent = 0);
    ~CMonitor();

private:
    Ui::CMonitor *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // MONITOR_H
