#include "quploaddataevent.h"

QUploadDataEvent::QUploadDataEvent( Type eEvent ) : QEvent( eEvent )
{
}

QUploadDataEvent* QUploadDataEvent::CreateEvent( UploadDataEvent eEvent )
{
    return new QUploadDataEvent( ( Type ) eEvent );
}

void QUploadDataEvent::SetRecordParams( QStringList& lstParam, QByteArray& byImage )
{
    lstRecordParams = lstParam;
    byImageData = byImage;
}

QStringList& QUploadDataEvent::GetRecordParams( )
{
    return lstRecordParams;
}

QByteArray& QUploadDataEvent::GetImageData( )
{
    return byImageData;
}
