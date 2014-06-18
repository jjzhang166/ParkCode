#include "qmypushbutton.h"

QMyPushButton::QMyPushButton(QWidget *parent) :
    QPushButton(parent)
{

}

void QMyPushButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent( e );

    if ( Qt::RightButton == e->button( ) ) {
        emit RightClick( );
    }
}
