#ifndef COMMONMYTIMER_H
#define COMMONMYTIMER_H

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#define rdtsc(low,high) __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

//static void Handler ( int sig, siginfo_t * extra, void *cruft );

class CMyTimer
{
public:
    CMyTimer();

private:

    void CreateTimer( );
};

#endif // COMMONMYTIMER_H
