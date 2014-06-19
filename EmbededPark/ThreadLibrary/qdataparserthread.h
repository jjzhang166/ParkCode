#ifndef QDATAPARSERTHREAD_H
#define QDATAPARSERTHREAD_H

#include "qmythread.h"
#include <QTcpSocket>
#include "../DataProtocol/qdataprotocol.h"

class QDataParserThread : public QMyThread
{
    Q_OBJECT
public:
    static QDataParserThread* GetSingletonInstance( QObject* pParent = 0 );
    static QDataParserThread* GetInstance( QObject* pParent = 0 );
    void SetServerSide( bool bServerSide );

    ~QDataParserThread( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QHash< QTcpSocket*, QByteArray* > QSocketArrayHash;
    void TcpParse( QCommonLibrary::EventParam& uParam );
    void UdpParse( QCommonLibrary::EventParam& uParam );
    bool ParseData( QTcpSocket* pSocket, QByteArray &data );

private:
    typedef QHash< QTcpSocket*, QByteArray* > QSocketByteArrayHash;

    QDataParserThread(QObject *parent = 0);
    static QDataParserThread* CreateThread( QObject *pParent );

    void FreeSocketByteArray( QSocketByteArrayHash& hash );

private:
    static QDataParserThread* pThreadInstance;
    bool bServerSideParser;
    QByteArray byDataToken;

    QSocketByteArrayHash tcpSocketByteArrayHash;
    QSocketByteArrayHash udpSocketByteArrayHash;

    QDataProtocol protocolData;
    QString strParserInfo;
    QByteArray byPackageData;
    
signals:
    void DataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray );
    
public slots:
    
};

#endif // QDATAPARSERTHREAD_H
