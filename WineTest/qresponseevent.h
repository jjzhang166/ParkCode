#ifndef QRESPONSEEVENT_H
#define QRESPONSEEVENT_H

#include <QEvent>
#include <QByteArray>

class QResponseEvent : public QEvent
{
public:
    QResponseEvent( Type event );

    void SetReponseData( const QByteArray& byData );
    QByteArray& GetReponseData( );

private:
    QByteArray byReponseData;
};

#endif // QRESPONSEEVENT_H
