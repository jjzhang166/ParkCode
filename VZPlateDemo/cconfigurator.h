#ifndef CCONFIGURATOR_H
#define CCONFIGURATOR_H

#include <QObject>
#include <QSettings>
#include "qcommon.h"
#include <QApplication>
#include <QStringList>

class CConfigurator : public QObject
{
    Q_OBJECT
public:
    static CConfigurator* CreateInstance( );

    void ReadAppMainWindow( QString& strType );
    void WriteAppMainWindow( QString& strType );

    void ReadVideoType( QString& strType );
    void WriteVideoType( QString& strType );

    void ReadIpcIP( QString& strIP );
    void WriteIpcIP( QString& strIP );

    int ReadPlateWay( );
    void WritePlateWay( int nWay );

    bool ReadMainStream( );
    void WriteMainStream( bool bStream );

    bool ReadRealStream( );
    void WriteRealStream( bool bReal );

    bool ReadPlateMultiThread( );
    void WritePlateMultiThread( bool bMulti );

    bool ReadVideoCapture( );
    void WriteVideoCapture( bool bCapture );

    void ReadBlacklistPlate( QStringList& lstPlates );
    void WriteBlacklistPlate( QStringList& lstPlates );

    void ReadPlateProvider( QString& strProvider );
    bool ReadPlateDongleWay( );

private:
    explicit CConfigurator(QObject *parent = 0);

    QSettings* pSettings;
    QTextCodec* pCodec;
    static CConfigurator* pConfigurator;
    
signals:
    
public slots:
    
};

#endif // CCONFIGURATOR_H
