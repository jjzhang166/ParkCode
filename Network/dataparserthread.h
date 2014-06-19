#ifndef DATAPARSERTHREAD_H
#define DATAPARSERTHREAD_H

#include <QThread>
#include <QEvent>
#include <QHash>
#include <QThreadPool>
#include "parserevent.h"
#include <QByteArray>

class CDataParserThread : public QThread
{
    Q_OBJECT
public:
    static CDataParserThread* GetInstance( qint32 nThreadPool, bool bTcp );
    static void ReleaseInstance( );

    void PostDataMessage( QByteArray& data, quint32 nSocket );
    void PostDataMessage( QByteArray& data );
    void PostDataMessage( QByteArray& data, QString& strIP );
    void PostReleaseMessage( quint32 nSocket );

private:
    explicit CDataParserThread( qint32 nThreadPool, bool bTcp, QObject *parent = 0);
    ~CDataParserThread( );

    inline void PostEvent( CParserEvent* pEvent );

protected:
    void run( );
    void customEvent( QEvent* e );

private:
    bool ParseData( QByteArray& data, QString& strIP );
    void TcpParse( quint32 nSocket, QByteArray& byData, QString& strIP, CParserEvent::ParserEvent event );
    void UdpParse( QByteArray& byData, QString& strIP, CParserEvent::ParserEvent event );

private:
    QHash< quint32, QByteArray* > peerData;
    QByteArray byUdpData;
    QThreadPool* svrThreadPool;
    bool bTcpParser;
    
signals:
    
public slots:
    
};

#endif // DATAPARSERTHREAD_H
