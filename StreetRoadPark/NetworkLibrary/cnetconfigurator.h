#ifndef CNETCONFIGURATOR_H
#define CNETCONFIGURATOR_H

#include <QObject>
#include <QTextCodec>
#include <QSettings>

class CNetConfigurator : public QObject
{
    Q_OBJECT
public:

    static CNetConfigurator* GetConfigurator( );

    ~CNetConfigurator( );

    qint32 GetThreadSocketCount( );
    qint32 GetPaserPeerCount( );
    qint32 GetPeerThreadSleep( );
    qint32 GetDataDispatcherParserCount( );
    QString GetMulticastIP( );
    quint16 GetMulticastPort( );
    bool GetDisplayDynamicLog( );
    qint32 GetTimeSyncInterval( );

    QTextCodec* GetTextCodec( );
    QString GetDateTime( );

private:
    CNetConfigurator(QObject *parent = 0);

private:
    QSettings* pSettings;
    
signals:
    
public slots:
    
};

#endif // CNETCONFIGURATOR_H
