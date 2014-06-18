#ifndef SMS_H
#define SMS_H

#include <QThread>
#include <QStringList>
#include <QAxWidget>
#include <QEvent>
#include <QApplication>
#include "smsevent.h"
#include <QMutex>

class CSms : public QThread
{
    Q_OBJECT
public:
    void SendMsg( QStringList& lstTelNumber, QString& strContent );

    static CSms& GetSingleton( );

protected:
    void customEvent(  QEvent* event );

private:
    explicit CSms(QObject *parent = 0);
    ~CSms( );

protected:
    virtual void run( );

private:
    void SendMsg( CSmsEvent* pEvent );

private:
    QAxWidget* pAxCtrl;
    static CSms* pSingleton;
    QMutex mutex;
    
signals:
    void ReceiveMessage( QStringList& lstTelNumber, QString& strContent );
    void SendFailed( QStringList& lstTelNumber );

private slots:
    void OnConnectResult( int nStatus );
    void OnRecvMsg( int nMsgCount );
    void OnSendMsg( int nResult,int nMsgIndex );
    void HandleException ( int code, const QString & source, const QString & desc, const QString & help );
};

#endif // SMS_H
