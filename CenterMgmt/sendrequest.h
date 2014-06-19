#ifndef SENDREQUEST_H
#define SENDREQUEST_H

#include <QRunnable>
#include "mgmtthread.h"

class CSendRequest : public QRunnable
{
public:
    static CSendRequest* GetTask( CMgmtThread* pSender );
    void run( );

private:
    CSendRequest( CMgmtThread* pSender );

private:
    CMgmtThread* pSenderThread;
};

#endif // SENDREQUEST_H
