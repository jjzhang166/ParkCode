#ifndef QMYUDPSOCKET_H
#define QMYUDPSOCKET_H

#include <QUdpSocket>
#include <QHostAddress>
#include "../ManipulateIniFile/qmanipulateinifile.h"
#include "../CommonLibrary/CommonMacro.h"
#include "../CommonLibrary/qmanipulatemessage.h"
#include "../CommonLibrary/qcommonfunction.h"

class QMyUdpSocket : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QMyUdpSocket(QObject *parent = 0);

    quint64 BroadcastDatagram( const QByteArray& byteData, const quint16 targetPort );
    bool StartupUdpListening( const quint16 nPort );
    bool OperateMulticast( const QHostAddress& groupAddress, const bool bJoined );
    quint64 SendDatagram( const QByteArray& byteData, const QHostAddress& targetAddress, const quint16 targetPort );

protected:
    void GetUdpDatagram( QHostAddress& senderAddr, quint16& senderPort );

private:
    void GetBroadOrMultiCastConfig( );

protected:
    QTextCodec* pTextCodec;
    QManipulateMessage processMsg;
    QCommonFunction commonFunction;
    QByteArray* pByteArray;

    quint16 nBroadcastPort;

private:

signals:
    void NotifyMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );

public slots:
    
};

#endif // QMYUDPSOCKET_H
