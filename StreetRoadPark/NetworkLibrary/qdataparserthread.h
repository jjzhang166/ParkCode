#ifndef QDATAPARSERTHREAD_H
#define QDATAPARSERTHREAD_H

#include "qthreadevent.h"
#include "databasecontroller.h"

class QDataParserThread : public QThread
{
    Q_OBJECT
public:
    static QDataParserThread* CreateThread( QObject *pParent = NULL );

    void SetDataDispatcher( QDataDispactherThread* pThread );

    void PostTCPDataEvent( QTcpSocket* pSocket, QByteArray& byTcpData );
    void PostUDPDataEvent( QByteArray& byUdpData );

    ~QDataParserThread( );

protected:
    void run( );
    virtual void customEvent( QEvent* event );
    void InitializeSubThread( );

private:
    typedef QHash< QTcpSocket*, QByteArray* > QSocketArrayHash;
    void TcpParse( QThreadEvent* pEvent );
    void UdpParse( QThreadEvent* pEvent );
    bool ParseData( QTcpSocket* pSocket, QByteArray &data );
    inline void PostEvent( QThreadEvent* pEvent );

    inline quint32 GetUInt32Value( const char* pData );
    void DispatchData( QTcpSocket* pSocket, qint32 nPackageType, QByteArray& byDbData );

private:
    typedef QHash< QTcpSocket*, QByteArray* > QSocketByteArrayHash;

    QDataParserThread(QObject *parent = 0);

    inline void SendLog( QString& strLog, bool bStatic );
    void FreeSocketByteArray( QSocketByteArrayHash& hash );

private:
    QByteArray byDataToken;

    QSocketByteArrayHash tcpSocketByteArrayHash;
    QSocketByteArrayHash udpSocketByteArrayHash;
    QDataDispactherThread* pDataDispatcher;
    DatabaseController* pDbController;
    
signals:
    void Log( QString strLog, bool bStatic );
    void DataIncoming( QTcpSocket* pSocket, QByteArray* pByteArray );
    
public slots:

private slots:
    
};

#endif // QDATAPARSERTHREAD_H
