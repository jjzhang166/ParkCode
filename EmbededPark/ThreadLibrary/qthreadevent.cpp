#include "qthreadevent.h"

QThreadEvent::QThreadEvent( Type type ) : QEvent( type )
{
}

QThreadEvent::~QThreadEvent( )
{
    QString strLog = "";
    //qDebug( ) << Q_FUNC_INFO << " Unhandled." << endl;
    switch ( threadType ) {
    case QCommonLibrary::ThreadListener :
        break;

    case QCommonLibrary::ThreadSocketDispatcher :
        break;

    case QCommonLibrary::ThreadSocketClient :
        if ( QCommonLibrary::EventClientSendData == threadEvent ) {
            delete evtParam.ParamValue.ClientSocketThread.Data.pByteArray;
            strLog = "evtParam.ParamValue.ClientSocketThread.Data.pByteArray";
        }
        break;

    case QCommonLibrary::ThreadSocketServer :
        break;

    case QCommonLibrary::ThreadDataParser :
        break;

    case QCommonLibrary::ThreadDatabase :
        break;

    case QCommonLibrary::ThreadLog :
        if ( QCommonLibrary::TypeLogContent == evtParam.type) {
            //delete evtParam.ParamValue.LogThread.pLogSQLStmt;
        }
        break;
    }

    QCommonLibrary::PrintLog( strLog );
}

QThreadEvent* QThreadEvent::GetInstance( Type type )
{
    return new QThreadEvent( type );
}

void QThreadEvent::SetEventParam( QCommonLibrary::EventParam &uParam,
                                  QCommonLibrary::ThreadType eThread,
                                  QCommonLibrary::ThreadEventType eEvent )
{
    threadType = eThread;
    evtParam = uParam;
    threadEvent = eEvent;
}

QCommonLibrary::EventParam& QThreadEvent::GetEventParam( )
{
    return evtParam;
}
