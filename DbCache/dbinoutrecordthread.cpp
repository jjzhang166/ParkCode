#include "DbCache/dbinoutrecordthread.h"
#include "DbCache/recordevent.h"

CDbInOutRecordThread::CDbInOutRecordThread(QObject *parent) :
    QThread(parent)
{
}

void CDbInOutRecordThread::run( )
{
    exec( ); // Event loop
}

void CDbInOutRecordThread::customEvent( QEvent *event )
{
    CRecordEvent::RecordEvent evtType = ( CRecordEvent::RecordEvent ) event->type( );
    CRecordEvent* pEvent = ( CRecordEvent* ) ( event );

    switch ( evtType ) {
        case CRecordEvent::WriteInRecord :
        break;

    case CRecordEvent::WriteOutRecord :
        break;
    }
}
