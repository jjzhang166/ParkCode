#ifndef QNETCOMMFUNCTION_H
#define QNETCOMMFUNCTION_H

#include <QObject>
#include <QtNetwork>

class QNetCommFunction : public QObject
{
    Q_OBJECT
public:
    static void GetErrorMsg( QString& strMsg, QNetworkReply::NetworkError code, QIODevice* pDevice = NULL );
    static void GetErrorMsg( QString& strMsg, QAbstractSocket::SocketError code, QIODevice* pDevice = NULL );

private:
    QNetCommFunction(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // QNETCOMMFUNCTION_H
