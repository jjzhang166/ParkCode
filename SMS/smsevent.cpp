#include "smsevent.h"

CSmsEvent::CSmsEvent( Type evtType ) : QEvent( evtType )
{
}

void CSmsEvent::SetParameters( QStringList &lstTel, QString &strCnt )
{
    lstTelNumber = lstTel;
    strContent = strCnt;
}

QStringList& CSmsEvent::GetTelList( )
{
    return lstTelNumber;
}

QString& CSmsEvent::GetSmsCnt( )
{
    return strContent;
}
