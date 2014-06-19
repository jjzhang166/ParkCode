#ifndef PEERSOCKET_H
#define PEERSOCKET_H

#include <QTcpSocket>

class CPeerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CPeerSocket(QObject *parent = 0);
    ~CPeerSocket( );

    QByteArray* GetData( );
    void SetMaxDataSize( quint64 nSize  );
    quint64 GetMaxDataSize( );
    void Clear( );

    void SetCurrentDataSize( quint64 nSize  );
    quint64 GetCurrentDataSize( );

private:
    QByteArray* pData;
    quint64 nDataLen;
    quint64 nCurrentLen;

signals:

public slots:

};

#endif // PEERSOCKET_H
