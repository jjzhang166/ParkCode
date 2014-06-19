#ifndef FEEFRAME_H
#define FEEFRAME_H

#include <QFrame>

namespace Ui {
    class CFeeFrame;
}

class CFeeFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CFeeFrame(QWidget *parent = 0);
    ~CFeeFrame();

private:
    Ui::CFeeFrame *ui;
};

#endif // FEEFRAME_H
