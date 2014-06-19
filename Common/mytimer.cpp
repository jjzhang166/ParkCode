#include "Common/mytimer.h"
#include <QDebug>
#include <QString>

//timer_t tt;

CMyTimer::CMyTimer()
{
    CreateTimer( );
}

void CMyTimer::CreateTimer( )
{
#if false
    int i = 0;
    sigset_t sigset;

    sigfillset (&sigset);
    sigdelset (&sigset, SIGRTMIN);
    sigprocmask (SIG_SETMASK, &sigset, NULL);

    struct sigaction sa;
    sigfillset (&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = Handler;

    if (sigaction (SIGRTMIN, &sa, NULL) < 0)
    {
     qDebug( ) << "sigaction failed \r\n";
     //exit (-1);
    }

    struct sigevent timer_event;
    struct itimerspec timer;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 100 * 1000 * 1000;
    timer.it_value = timer.it_interval;

    timer_event.sigev_notify = SIGEV_SIGNAL;
    timer_event.sigev_signo = SIGRTMIN;
    timer_event.sigev_value.sival_ptr = (void *) &tt;

    if (timer_create (CLOCK_REALTIME, &timer_event, &tt) < 0)
    {
     qDebug( ) <<  "timer_create failed\t\n";
     //exit (-1);
    }

    if (timer_settime (tt, 0, &timer, NULL) < 0)
    {
     qDebug( ) <<  "timer_settime failed\r\n";
     //exit (-1);
    }

    while (i++ < 10)
    {
     ;//pause ();
    }
#endif
}
#if false
void Handler ( int sig, siginfo_t * extra, void *cruft )
{
    static int last_i=0;
       unsigned int i, j;
       rdtsc(i,j);
       QString strInfo( "time:%1, %2, [%3] %4HZ ");
       strInfo.arg( "%1", j ).arg( "%2", i ).arg( "%3", i - last_i ).arg( "%4", ( i - last_i ) * 10 / 1000000 );
       qDebug( ) <<  strInfo;
       last_i = i;
}
#endif
