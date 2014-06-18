#include "qftpevent.h"

QFtpEvent::QFtpEvent( FtpEvent eEvent ) : QEvent( ( Type ) eEvent )
{
}

QFtpEvent* QFtpEvent::CreateFtpEvent( FtpEvent eEvent )
{
    return new QFtpEvent( eEvent );
}

void QFtpEvent::SetFileName( QString& strName )
{
    strFileName = strName;
}

QString& QFtpEvent::GetFileName( )
{
    return strFileName;
}

void QFtpEvent::SetFileData( QByteArray& byData )
{
    byFileData = byData;
}

QByteArray& QFtpEvent::GetFileData( )
{
    return byFileData;
}
