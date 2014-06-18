#ifndef QCOMMON_H
#define QCOMMON_H

#include <QObject>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <phonon/phonon>

#define CHANNEL_WAY ( int ) 4
#define VIDEO_WIDTH   ( int ) ( 720 )
#define VIDEO_HEIGHT  ( int ) ( 576 )

class QCommon : public QObject
{
    Q_OBJECT
public:
    static QTextCodec* GetTextCodec( );
    static void GetPlatePicPath( QString& strPath );
    static void GetCurrentDateTime( QString& strDateTime );
    static void PlayMusic( QString& strName, bool bStop );

private:
    QCommon(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // QCOMMON_H
