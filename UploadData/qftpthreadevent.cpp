#include "qftpthreadevent.h"
QFtpThreadEvent::QFtpThreadEvent( FtpEvent eEvent ) : QEvent( ( Type ) eEvent )
{
}

QFtpThreadEvent* QFtpThreadEvent::CreateEvent( FtpEvent eEvent )
{
    return new QFtpThreadEvent( eEvent );
}

void QFtpThreadEvent::SetFileName( QString& strName )
{
    strFileName = strName;
}

QString& QFtpThreadEvent::GetFileName( )
{
    return strFileName;
}

void QFtpThreadEvent::SetImageData( QByteArray& byData )
{
    byImageData = byData;
}

QByteArray& QFtpThreadEvent::GetImageData( )
{
    return byImageData;
}
