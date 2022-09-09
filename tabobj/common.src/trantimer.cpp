

#include <string.h>
#include <cccapi.h>

#ifdef WINDOWS

void _clp_trantimer_start(int argno)  { stack-=argno; PUSHNIL(); }
void _clp_trantimer_delete(int argno) { stack-=argno; PUSHNIL(); }

#else


#define TIMEOUT_SIGNAL SIGALRM
// #define TIMEOUT_SIGNAL SIGUSR1
// #define TIMEOUT_SIGNAL SIGUSR2


//----------------------------------------------------------------------------------------
static struct sigevent init_sigevent()
{
    struct sigevent sev;
    memset(&sev,0,sizeof(sev));
    sev.sigev_notify=SIGEV_SIGNAL;
    sev.sigev_signo=TIMEOUT_SIGNAL;
    return sev;
}

static struct sigevent sev=init_sigevent();                // sev
static timer_t timerid[8];                                 // timerid
static struct itimerspec timeout[8];                       // timeout
static int timer_flag[8]={0,0,0,0,0,0,0,0};

//----------------------------------------------------------------------------------------
void _clp_trantimer_start(int argno)
{
    CCC_PROLOG("trantimer_start",2);
    
    int level=_parni(1);        // 1..8
    int timeout_ms=_parni(2);   // millis
    
    if( (level<1) || (8<level) )
    {
        ARGERROR();
    }
    level--;
    
    if( timer_flag[level]  )
    {
        timer_delete(timerid[level]);
    }
    else
    {
        timer_flag[level]=1;
    }

    memset(&timeout[level],0,sizeof(struct itimerspec));
    timeout[level].it_value.tv_sec  = (timeout_ms/1000);
    timeout[level].it_value.tv_nsec = (timeout_ms%1000)*1000000;

    timer_create(CLOCK_REALTIME,&sev,&timerid[level]);
    timer_settime(timerid[level],0,&timeout[level],0);

    _ret();

    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_trantimer_delete(int argno)
{
    CCC_PROLOG("trantimer_delete",1);
    int level=_parni(1);        // 1..8
    if( (level<1) || (8<level) )
    {
        ARGERROR();
    }
    level--;
    if( timer_flag[level] )
    {
        timer_flag[level]=0;
        timer_delete(timerid[level]);
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
#endif

