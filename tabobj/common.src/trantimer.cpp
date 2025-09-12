
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <string.h>
#include <cccapi.h>

#ifdef WINDOWS

void _clp_trantimer_start(int argno)    { stack-=argno; PUSHNIL(); }
void _clp_trantimer_delete(int argno)   { stack-=argno; PUSHNIL(); }
void _clp_trantimer_remained(int argno) { stack-=argno; number(0); }
void _clp_trantimer_timeout(int argno)  { stack-=argno; logical(0);}

#else

#include <signal.h>

#define TIMEOUT_SIGNAL SIGALRM
// #define TIMEOUT_SIGNAL SIGUSR1
// #define TIMEOUT_SIGNAL SIGUSR2


static int timeout=0;

//----------------------------------------------------------------------
static void signal_handler(int signum)
{
    timeout=1;
}

// Az aszinkron szignal kezeles veszelyes ugy.
// A program barhol jarhat: felig vegrehajtott
// malloc-ban, vagy felig vegrehajtott gc-ben,
// es ekozben kiugrik a TIMEOUT_SIGNAL kezelesere.
// Ilyenkor csak ket dolog lehet biztonsagos:
// 1) teljesen elnyomjuk a szignalt (nem csinalnunk semmit),
// 2) vagy kilepunk a programbol.

// Aszinkron signal kezelesben nem jo breakelni,
// mert elromolhat a CCC futtato kornyezet.
// Ezert itt csak megjegyezzuk, hogy timeout tortent,
// amit a tranCommit kesobb lekerdezhet, es ha .t.-t kap,
// akkor commit helyett megis rollback-et csinal.
// Hatrany, hogy teljesen beragadhatnak a tranzakciok.

int init_sighandler()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler=signal_handler;
    sigaction(TIMEOUT_SIGNAL,&act,0);
    return 1;
}


//----------------------------------------------------------------------------------------
static timer_t timerid[8]={0,0,0,0,0,0,0,0};

int init_timerid()
{
    static struct sigevent sev;
    memset(&sev,0,sizeof(sev));
    sev.sigev_notify=SIGEV_SIGNAL;
    sev.sigev_signo=TIMEOUT_SIGNAL;

    for(int level=0; level<8; level++)
    {
        timer_create(CLOCK_REALTIME,&sev,&timerid[level]);
    }
    return 1;
}


//----------------------------------------------------------------------------------------
void _clp_trantimer_start(int argno)  // inditja a timeout idozitest
{
    int init1=init_sighandler();
    int init2=init_timerid();

    // ha init1 kulso static volna,
    // akkor a kesobb inicializalodo CCC sighandler
    // felulirna az itt beallitott signal kezelest


    CCC_PROLOG("trantimer_start",2);
    int level=_parni(1);        // 1..8
    int timeout_ms=_parni(2);   // millis

    if( (level<1) || (8<level) )
    {
        ARGERROR();
    }
    level--;

    struct itimerspec itimer;
    memset(&itimer,0,sizeof(itimer));
    itimer.it_value.tv_sec  = (timeout_ms/1000);
    itimer.it_value.tv_nsec = (timeout_ms%1000)*1000000;
    timer_settime(timerid[level],0,&itimer,0);

    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_trantimer_delete(int argno)  // torli a timeout idozitest
{
    CCC_PROLOG("trantimer_delete",1);
    int level=_parni(1);
    if( (level<1) || (8<level) )
    {
        ARGERROR();
    }
    level--;

    struct itimerspec itimer;
    memset(&itimer,0,sizeof(itimer));
    timer_settime(timerid[level],0,&itimer,0);

    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_trantimer_remained(int argno) // mennyi ido maradt a timeoutig
{
    CCC_PROLOG("trantimer_remained",1);
    int level=_parni(1);
    if( (level<1) || (8<level) )
    {
        ARGERROR();
    }
    level--;

    struct itimerspec itimer;
    memset(&itimer,0,sizeof(itimer));
    timer_gettime(timerid[level],&itimer);
    char buf[64];
    sprintf(buf,"%ld.%ld",itimer.it_value.tv_sec,itimer.it_value.tv_nsec);
    double remained;
    sscanf(buf,"%lf",&remained);

    _retnd(remained);
    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp_trantimer_timeout(int argno) // volt-e timeout
{
    CCC_PROLOG("trantimer_timeout",1);
    int clear=!ISNIL(1);
    _retl( timeout );
    if( clear )
    {
        timeout=0;
    }
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
#endif


