#ifndef QPROCESSRESPONSETHREAD_H
#define QPROCESSRESPONSETHREAD_H

#include <QThread>
#include <QByteArray>
#include "../PlateDilivery/ProtocolStructure.h"

class QProcessResponseThread : public QThread
{
    Q_OBJECT
public:
    explicit QProcessResponseThread(QObject *parent = 0);

    static QProcessResponseThread* GetSingleton( );

protected:
    void run( );
    void customEvent( QEvent * e );

private:
    void ParseResponseData( QByteArray& byData );
    bool ParseMultipleResponseData( QByteArray &byResponse );

    void ProcessResponse( QByteArray& byStream );
    void ProcessBallotSenseResponse( QByteArray& byStream );
    void ProcessGateSenseResponse( QByteArray& byStream );
    void ProcessInfraredResponse( QByteArray& byStream );
    void ProcessPlateResponse( QByteArray& byStream );
    void ProcessActiveSendResponse( QByteArray& byStream );
    void AppendResponse( QString& strMsg );

    QByteArray GetToken( QByteArray& byStream );
    quint8 GetMessageType( QByteArray& byStream );
    quint32 GetStreamLength( QByteArray& byStream );
    QByteArray GetBody( QByteArray& byStream );

private:
    QByteArray byResponseData;
    static QProcessResponseThread* pThreadInstance;
    
signals:
    void Response( QString strMsg );
    void PlateImg( QString strFile );
    
public slots:
    
};

#endif // QPROCESSRESPONSETHREAD_H
