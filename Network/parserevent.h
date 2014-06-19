#ifndef PARSEREVENT_H
#define PARSEREVENT_H

#include <QEvent>
#include <QString>

class CParserEvent : public QEvent
{
public:
    typedef enum __ParserEvent {
        ParserData = User,
        ParserRelease
    } ParserEvent;

public:
    CParserEvent( QByteArray& data, quint32 nSocket, ParserEvent event );
    CParserEvent( QByteArray& data, ParserEvent event );
    CParserEvent( QByteArray& data, QString&strIP, ParserEvent event );
    CParserEvent( quint32 nSocket, ParserEvent event );
    QByteArray& GetData( );
    quint32 GetSocket( );
    QString& GetUdpIP( );

private:
    QByteArray byData;
    quint32 nSocketPointer;
    QString strUdpIP;
};

#endif // PARSEREVENT_H
