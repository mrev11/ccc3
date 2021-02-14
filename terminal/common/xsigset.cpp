
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <xsigset.h>


#ifdef WINDOWS
//--------------------------------------------------------------------------
void xsigset(int signum, sighandler_t sighnd)
{
    //empty
}

//--------------------------------------------------------------------------
void xsigset_handlers()
{
    //empty
}

//--------------------------------------------------------------------------
#endif



#ifdef _UNIX_
//--------------------------------------------------------------------------
void xsigset(int signum, sighandler_t sighnd)
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler=sighnd;
    sigaction(signum,&act,0);
}

//--------------------------------------------------------------------------
void xsigset_handlers()
{
    xsigset(SIGCHLD,SIG_IGN); //zombik ellen 2021.02.13
}

//--------------------------------------------------------------------------
#endif


