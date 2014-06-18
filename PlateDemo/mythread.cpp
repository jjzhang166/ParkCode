#include "mythread.h"
#include "MainWindow.h"

CMyThread::CMyThread(QObject *parent) :
    QThread(parent)
{
}

void CMyThread::run( )
{
    MainWindow* pMulti = ( MainWindow* ) parent( );
    quint8 data[ 704 * 576 * 4 ];
    ULONG lSize = 704 * 576 * 4;

    while ( true ) {
        pMulti->Recognize( data, lSize );
    }
}
