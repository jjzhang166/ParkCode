#include "qipcthread.h"

QIPCThread::QIPCThread(QObject *parent) :
    QThread(parent)
{
}

void QIPCThread::PostIPCGateEvent(QIPCEvent::EventParam &uParam)
{

}
