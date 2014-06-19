#include "parserevent.h"

CParserEvent::CParserEvent( QByteArray& data, quint32 nSocket, ParserEvent event  ) : QEvent( ( Type ) event )
{
    nSocketPointer = nSocket;
    byData.append( data );
    strUdpIP = "";
}

CParserEvent::CParserEvent( QByteArray& data, ParserEvent event  ) : QEvent( ( Type ) event )
{
    nSocketPointer = 0;
    byData.append( data );
    strUdpIP = "";
}

CParserEvent::CParserEvent( QByteArray& data, QString& strIP, ParserEvent event  ) : QEvent( ( Type ) event )
{
    nSocketPointer = 0;
    strUdpIP = strIP;
    byData.append( data );
}

CParserEvent::CParserEvent( quint32 nSocket, ParserEvent event  ) : QEvent( ( Type ) event )
{
    nSocketPointer = nSocket;
    strUdpIP = "";
}

QString& CParserEvent::GetUdpIP( )
{
    return strUdpIP;
}

QByteArray& CParserEvent::GetData( )
{
    return byData;
}

quint32 CParserEvent::GetSocket( )
{
    return nSocketPointer;
}
