#include "qmydatabase.h"
#include <QDateTime>

QMyDatabase::QMyDatabase( QObject *parent ) : QObject( parent )
{
    nEnqueueStartMinute = 0;
    nLifeTime = 60;
}

QMyDatabase::~QMyDatabase( )
{

}

void QMyDatabase::SetDatabaseParams( MyDataStructs::QParamMultiHash &hashParam )
{
    hashDatabaseParams = hashParam;
}

quint64 QMyDatabase::GetCurrentMinute( )
{
    return QDateTime::currentMSecsSinceEpoch( ) / 1000 / 60;
}

void QMyDatabase::SetEnqueueStartMinute( )
{
    nEnqueueStartMinute = GetCurrentMinute( );
}

void QMyDatabase::SetLifeTime( quint32 nTime )
{
    nLifeTime = nTime;
}

bool QMyDatabase::MayRelease( )
{
    bool bRelease = ( ( GetCurrentMinute( ) - nEnqueueStartMinute ) >= nLifeTime );

    return bRelease;
}

void QMyDatabase::HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type )
{
    OutputMsg( "Sender:" + sender( )->objectName( ) + QString( ":emit NotifyMessage( %1, LogTypes=%2 )" ).arg( *( QString* ) pstrMsg, QString::number( type ) ) );
    emit NotifyMessage( pstrMsg, type );
}
