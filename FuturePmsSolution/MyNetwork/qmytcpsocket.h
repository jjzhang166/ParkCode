#ifndef QMYTCPSOCKET_H
#define QMYTCPSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>
#include "../ManipulateIniFile/qmanipulateinifile.h"
#include "../CommonLibrary/CommonMacro.h"
#include "../CommonLibrary/qmanipulatemessage.h"
#include "../CommonLibrary/qcommonfunction.h"

class QMyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit QMyTcpSocket(QObject *parent = 0);

    quint64 SendData( const char * data, qint64 maxSize );
    quint64 SendData( const QByteArray & byteArray );
    quint64 ReceiveData( char* data, qint64 maxSize );
    QByteArray ReceiveData( qint64 maxSize );
    QByteArray ReceiveData(  );

protected:
    bool GetTcpStreamData( );
    void GetKeyMsg( QString &strKey, QString &strMsg, bool bConnected );
    void GenerateLogText( bool bConnected );

private:
    void SetMaxDataSize( quint64 nSize );
    quint64 GetMaxDataSize( );
    void Clear( );
    void SetCurrentDataSize( quint64 nSize );
    quint64 GetCurrentDataSize( );

protected:
    QTextCodec* pTextCodec;
    QManipulateMessage processMsg;
    QCommonFunction commonFunction;
    QByteArray* pByteArray;

private:
    quint64 nDataLen;
    quint64 nCurrentLen;
    
signals:
    void NotifyMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );
    
public slots:
    
};

#endif // QMYTCPSOCKET_H
