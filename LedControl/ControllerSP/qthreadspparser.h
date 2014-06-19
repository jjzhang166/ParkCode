#ifndef QTHREADSPPARSER_H
#define QTHREADSPPARSER_H

#include <QThread>
#include "ControllerSP_global.h"
#include "../ControllerCmd/qcontrollercmd.h"

class CONTROLLERSPSHARED_EXPORT QThreadSPParser : public QThread
{
    Q_OBJECT
public:
    void SendData( QByteArray& data );
    static QThreadSPParser& GetSingleton(  );

protected:
    explicit QThreadSPParser(QObject *parent = 0);
    void run( );
    void customEvent( QEvent *e );

private:
    bool ParseData( );
    void ProcessError( const char cErrorCode, const bool bWrite  );
    void ProcessSuccess( );
    void ProcessData( const bool bSubsequence, QByteArray& data );

private:
    static QThreadSPParser* pSingleton;
    QByteArray byData;
    QControllerCmd* cmdController;
    
signals:
    void Cmd( QByteArray data, bool bSend );
    void Query( QString strInfo, qint8 nIndex, QByteArray byData );
    
public slots:
    
};

#endif // QTHREADSPPARSER_H
