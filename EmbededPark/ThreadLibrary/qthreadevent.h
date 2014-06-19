#ifndef QTHREADEVENT_H
#define QTHREADEVENT_H

#include <QEvent>
#include "../CommonLibrary/qcommonlibrary.h"

class QThreadEvent : public QEvent
{
public:
    ~QThreadEvent( );
    static QThreadEvent* GetInstance( Type type );

    void SetEventParam( QCommonLibrary::EventParam& uParam,
                        QCommonLibrary::ThreadType eThread,
                        QCommonLibrary::ThreadEventType eEvent );
    QCommonLibrary::EventParam& GetEventParam( );
private:
    QThreadEvent( Type type );

    QCommonLibrary::EventParam evtParam;
    QCommonLibrary::ThreadType threadType;
    QCommonLibrary::ThreadEventType threadEvent;
};

#endif // QTHREADEVENT_H
