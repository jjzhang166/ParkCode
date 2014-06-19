#ifndef FTP_H
#define FTP_H

#include <QObject>
#include <QtNetwork>
 #include <QMutex>
#include <QHash>
#include "ftpevent.h"

class CFtp : public QThread
{
    Q_OBJECT
public:
    explicit CFtp( QObject *parent = 0);

    static void GetCommonParams( );

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    bool SendFile( QStringList& lstParams );
    void GetImgData( QByteArray& byData, QStringList& lstParams );

    void Encoding( QString& strRaw, QString& strResult );
    void Decoding( QString& strRaw, QString& strResult );

private:
    QFtp ftpClient;
    QHash< int, QByteArray* > dataHash;
    static QStringList lstFtpServer;

signals:

private slots:
    void ThreadExit( );
    void FtpCmdFinished( int nId, bool bError );
    void StateChanged( int nState );
};

#endif // FTP_H
