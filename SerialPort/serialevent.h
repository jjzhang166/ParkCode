#ifndef SERIALEVENT_H
#define SERIALEVENT_H

#include <QEvent>
#include <QByteArray>

class CSerialEvent : public QEvent
{
public:
    CSerialEvent( Type event );

    void SetSerialData( const QByteArray& byData, const int nIndex = 0 );
    QByteArray& GetSerialData( );
    int GetSerialIndex( );

private:
    QByteArray bySerialData;
    int nSerialPortIndex;
};

#endif // SERIALEVENT_H
