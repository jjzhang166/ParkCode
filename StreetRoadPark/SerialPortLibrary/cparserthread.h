#ifndef CPARSERTHREAD_H
#define CPARSERTHREAD_H

#include <QThread>
#include "ccomthreadevent.h"
#include "../DatabaseLibrary/databasecontroller.h"

class CParserThread : public QThread
{
    Q_OBJECT
public:
    static CParserThread* CreateThread( QString& strParkID, QObject* parent = 0 );
    void PostData( QByteArray& byData );

protected:
    void run( );
    void customEvent( QEvent * pEvent );

private:
    explicit CParserThread( QString& strParkID, QObject *parent = 0);
    void Initialize( );

    bool ParseData( QByteArray& byData );
    bool GetVersionInfo( QByteArray& byData );

    inline void PostEvent( CComThreadEvent* pEvent );

    inline void SendLog( QByteArray& byCmd, bool bStatic );
    inline void SendLog( QString& strLog, bool bStatic );

private:
    QString strComParkID;
    QByteArray byPortData;
    char cStart;
    QByteArray byEnd;
    QByteArray byVerInfo;
    CComConfigurator* pConfig;
    DatabaseController* pDbController;
    
signals:
    void Log( QString strLog, bool bStatic );

public slots:
    
};

#endif // CPARSERTHREAD_H
