#ifndef QCOMMONFUNCTION_H
#define QCOMMONFUNCTION_H

#include <windows.h>
#include "QCommonFunction_global.h"
#include <QTextCodec>
#include <QDateTime>

class QCOMMONFUNCTIONSHARED_EXPORT QCommonFunction : public QObject
{
    Q_OBJECT
public:
    explicit QCommonFunction(QObject *parent = 0);
    virtual ~QCommonFunction( );

    enum PathType {
        PathImages,
        PathConfigs,
        PathLogs
    };

    Q_DECLARE_FLAGS( PathTypes, PathType )
    Q_FLAGS( PathType )

public:
    void GetPath( QString& strPath, const PathTypes type );
    void GetPathTypeName( PathTypes type, QString& strName );
    QTextCodec* GetTextCodec( ) const;
    void InstallTextCodec( ) const;
    void SetDateTimeFormat( );

    QString GetDateString( const QDate& date );
    QString GetTimeString( const QTime& time );
    QString GetDateTimeString( const QDateTime& dateTime );

    QDate GetStringDate( const QString& strDate );
    QTime GetStringTime( const QString& strTime );
    QDateTime GetStringDateTime( const QString& strDateTime );

private:
    void MakePath( const QString& strPath ) const;

private:
    QString strTimeFormat;
    QString strDateFormat;
    
signals:
    
public slots:
    
};

#endif // QCOMMONFUNCTION_H
