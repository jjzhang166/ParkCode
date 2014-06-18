#ifndef CDBCONFIGURATOR_H
#define CDBCONFIGURATOR_H

#include <QObject>
#include <QTextCodec>
#include <QDebug>
#include <QSettings>
#include <QStringList>

class CDbConfigurator : public QObject
{
    Q_OBJECT
public:
    static CDbConfigurator* GetConfigurator( );
    ~CDbConfigurator( );

    void ReadDbInfo( QStringList& lstDbInfo );
    void WriteDbInfo( QString& strIP, quint16 nPort );
    qint32 GetDbThreadOperationCount( );
    qint32 GetDbThreadCount( );
    qint32 GetDbThreadInvalidWaitTime( );
    QString GetParkID( );
    bool GetDisplayDynamicLog( );
    QString GetDateTime( );
    QString GetHttpHost( );
    int GetHttpPort( );
    void DetectorID2LocationID( QString& strDetectorID );

    QTextCodec* GetTextCodec( );

private:
    CDbConfigurator( QObject* parent = NULL );

private:
    QSettings* pSettings;
    
signals:
    
public slots:
    
};

#endif // CDBCONFIGURATOR_H
