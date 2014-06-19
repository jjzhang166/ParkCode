#ifndef NETCOMMFUNCTION_H
#define NETCOMMFUNCTION_H

#include <QObject>
#include <QtNetwork>

class CNetCommFunction : public QObject
{
    Q_OBJECT
public:
    static void GetErrorMsg( QString& strMsg, QNetworkReply::NetworkError code, QIODevice* pDevice = NULL );
    static void GetErrorMsg( QString& strMsg, QAbstractSocket::SocketError code, QIODevice* pDevice = NULL );

private:
    CNetCommFunction(QObject *parent = 0);

signals:

public slots:

};

#endif // NETCOMMFUNCTION_H
