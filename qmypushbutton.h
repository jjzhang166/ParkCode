#ifndef QMYPUSHBUTTON_H
#define QMYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class QMyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QMyPushButton(QWidget *parent = 0);

protected:
    void mousePressEvent (QMouseEvent  *e );
    
signals:
    void RightClick( );
    
public slots:
    
};

#endif // QMYPUSHBUTTON_H
