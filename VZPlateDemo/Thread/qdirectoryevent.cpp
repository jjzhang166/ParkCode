#include "qdirectoryevent.h"

QDirectoryEvent::QDirectoryEvent( Type evtType ) : QEvent( evtType )
{
}

void QDirectoryEvent::SetDirectory( QString &strDir )
{
    strDirectory = strDir;
}

QString& QDirectoryEvent::GetDirectory( )
{
    return strDirectory;
}
