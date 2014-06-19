#include "recordevent.h"

CRecordEvent::CRecordEvent( RecordEvent event ) :
     QEvent( ( Type ) event )
{
}

CRecordEvent::~CRecordEvent( )
{

}
