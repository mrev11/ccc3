
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

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <signal.ch>
#include <cccapi.h>


//--------------------------------------------------------------------------
static int cccsig2signum(int cccsig)
{
    switch( cccsig )
    {
        case SIG_HUP : return SIGHUP;    // Hangup (POSIX)
        case SIG_INT : return SIGINT;    // Interrupt (ANSI)
        case SIG_QUIT: return SIGQUIT;   // Quit (POSIX)
        case SIG_ILL : return SIGILL;    // Illegal instruction (ANSI)
        case SIG_ABRT: return SIGABRT;   // Abort (ANSI)
        case SIG_FPE : return SIGFPE;    // Floating-point exception (ANSI)
        case SIG_SEGV: return SIGSEGV;   // Segmentation violation (ANSI)
        case SIG_PIPE: return SIGPIPE;   // Broken pipe (POSIX)
        case SIG_TERM: return SIGTERM;   // Termination (ANSI)

        case SIG_CONT: return SIGCONT;   // Continue (POSIX)
        case SIG_STOP: return SIGSTOP;   // Stop, unblockable (POSIX)
        case SIG_KILL: return SIGKILL;   // Kill, unblockable (POSIX)
    }
    return 0;
}

//--------------------------------------------------------------------------
static int signum2cccsig(int signum)
{
    switch( signum )
    {
        case SIGHUP : return SIG_HUP;    // Hangup (POSIX)
        case SIGINT : return SIG_INT;    // Interrupt (ANSI)
        case SIGQUIT: return SIG_QUIT;   // Quit (POSIX)
        case SIGILL : return SIG_ILL;    // Illegal instruction (ANSI)
        case SIGABRT: return SIG_ABRT;   // Abort (ANSI)
        case SIGFPE : return SIG_FPE;    // Floating-point exception (ANSI)
        case SIGSEGV: return SIG_SEGV;   // Segmentation violation (ANSI)
        case SIGPIPE: return SIG_PIPE;   // Broken pipe (POSIX)
        case SIGTERM: return SIG_TERM;   // Termination (ANSI)

        case SIGCONT: return SIG_CONT;   // Continue (POSIX)
        case SIGSTOP: return SIG_STOP;   // Stop, unblockable (POSIX)
        case SIGKILL: return SIG_KILL;   // Kill, unblockable (POSIX)
    }
    return 0;
}


//--------------------------------------------------------------------------
static void signal_handler(int signum)
{   
    #ifdef EMLEKEZTETO
    //signal(signum,signal_handler);
    Nincs szükség a signal handler újbóli beállítására, ui.
    a BSD és a linuxos glibc2 nem csinálja a default visszaállítását,
    Solarison pedig signal() helyett sigset()-et használunk ugyanezért.
    A signal_handler futása alatt ugyanolyan signal nem jön,
    mert a rendszer azt automatikusan blokkolja.
    #endif

    int cccsig=signum2cccsig(signum);

    //printf("\nSignal received: cccsig=%d pid=%d\n",cccsig,getpid());fflush(0);
    //printf("\nSignal received: signal=%d pid=%d\n",signum,getpid());fflush(0);
    //abort();

    #ifdef EMLEKEZTETO //2008.11.27

        Korábban SIGSTOP-pal megállítottam az elszálló programot,
        és a "gdb exename pid" paranccsal debugoltam. 
        Ehelyett egyszerűbb abortálni, amiből keletkezik egy core filé,
        és a "gdb exename corefile" adja ugyanazt az infót. 
        
        Linuxon az "ulimit -c 100000" paranccsal előzőleg 0-ról
        fel kell emelni a minimális core filé méretet, másképp
        nem keletkezik core filé.
        
        FreeBSD-n és Solarison defaultból készül core.
        
        A SIGABRT szignált nem célszerű elkapni. Ha itt abort-ot
        hívok, és a SIGABRT-ot elkapom, az végtelen rekurzió.
    #endif

    if( cccsig==0 )
    {
        return;
    }
#ifdef MULTITHREAD
    else if( 0==thread_data_ptr )
    {
        return; //új szál, nincs még thread_data-ja
    }
#endif    
    else if( (cccsig&~sigcccmask)==0 ) 
    {
        return;
    }
    else if( siglocklev>0 ) //egy szálra vonatkozó szemafor kapcsoló
    {
        signumpend|=cccsig;
        return;
    }

    siglocklev=1;           //jobb, ha nem rekurzív
    signumpend=0;           //tiszta lap

    VALUE save=*stack;      //félkész VALUE a stack fölött
    _clp_signalblock(0);
    number(cccsig);
    _clp_eval(2);
    pop();
    *stack=save;            //félkész VALUE a stack fölött

    siglocklev=0;           //újra engedélyezve
    signumpend=0;           //tiszta lap
}

//--------------------------------------------------------------------------
void setup_signal_handlers()
{
    #ifdef _SOLARIS_
        sigset(SIGHUP  ,signal_handler);
        sigset(SIGINT  ,signal_handler);
        sigset(SIGQUIT ,signal_handler);
        sigset(SIGILL  ,signal_handler);
        //sigset(SIGABRT ,signal_handler); //kivéve 2008.11.27
        sigset(SIGFPE  ,signal_handler);
        sigset(SIGSEGV ,signal_handler);
        sigset(SIGPIPE ,signal_handler);
        sigset(SIGTERM ,signal_handler);
    #else
        signal(SIGHUP  ,signal_handler);
        signal(SIGINT  ,signal_handler);
        signal(SIGQUIT ,signal_handler);
        signal(SIGILL  ,signal_handler);
        //signal(SIGABRT ,signal_handler); //kivéve 2008.11.27
        signal(SIGFPE  ,signal_handler);
        signal(SIGSEGV ,signal_handler);
        signal(SIGPIPE ,signal_handler);
        signal(SIGTERM ,signal_handler);
    #endif
}

//--------------------------------------------------------------------------
int signal_raise(int cccsig)
{
    int cnt=0;
    if( cccsig&SIG_HUP ) {++cnt; signal_handler(SIGHUP);}
    if( cccsig&SIG_INT ) {++cnt; signal_handler(SIGINT);}
    if( cccsig&SIG_QUIT) {++cnt; signal_handler(SIGQUIT);}
    if( cccsig&SIG_ILL ) {++cnt; signal_handler(SIGILL);}
    if( cccsig&SIG_ABRT) {++cnt; signal_handler(SIGABRT);}
    if( cccsig&SIG_FPE ) {++cnt; signal_handler(SIGFPE);}
    if( cccsig&SIG_SEGV) {++cnt; signal_handler(SIGSEGV);}
    if( cccsig&SIG_PIPE) {++cnt; signal_handler(SIGPIPE);}
    if( cccsig&SIG_TERM) {++cnt; signal_handler(SIGTERM);}
    return cnt;
}

//--------------------------------------------------------------------------
int signal_send(int pid, int cccsig)
{
    int cnt=0;
    if( cccsig&SIG_HUP ) {++cnt; kill(pid,SIGHUP);}
    if( cccsig&SIG_INT ) {++cnt; kill(pid,SIGINT);}
    if( cccsig&SIG_QUIT) {++cnt; kill(pid,SIGQUIT);}
    if( cccsig&SIG_ILL ) {++cnt; kill(pid,SIGILL);}
    if( cccsig&SIG_ABRT) {++cnt; kill(pid,SIGABRT);}
    if( cccsig&SIG_FPE ) {++cnt; kill(pid,SIGFPE);}
    if( cccsig&SIG_SEGV) {++cnt; kill(pid,SIGSEGV);}
    if( cccsig&SIG_PIPE) {++cnt; kill(pid,SIGPIPE);}
    if( cccsig&SIG_TERM) {++cnt; kill(pid,SIGTERM);}

    if( cccsig&SIG_CONT) {++cnt; kill(pid,SIGCONT);}
    if( cccsig&SIG_STOP) {++cnt; kill(pid,SIGSTOP);}
    if( cccsig&SIG_KILL) {++cnt; kill(pid,SIGKILL);}
    return cnt;
}

//--------------------------------------------------------------------------
void _clp_signal_pending(int argno) //feldolgozásra váró szignálok
{
    CCC_PROLOG("signal_pending",1);
    _retni(signumpend);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_clear(int argno) //töröl a feldolgozásra váró szignálok közül
{
    CCC_PROLOG("signal_clear",1);
    int mask=ISNIL(1)?-1:_parni(1);
    signumpend &= ~mask;
    _retni(signumpend);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_raise(int argno) //feldolgozza a szignálokat
{
    CCC_PROLOG("signal_raise",1);
    int cccsig=_parni(1);
    _retni(signal_raise(cccsig));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_send(int argno) //szignálokat küld egy processznek
{
    CCC_PROLOG("signal_send",2);
    int pid=_parni(1);
    int cccsig=_parni(2);
    _retni(signal_send(pid,cccsig));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_description(int argno) //szignál leírása
{
    CCC_PROLOG("signal_description",1);
    int cccsig=_parni(1);
    char desc[128];
    switch(cccsig)
    {
        case SIG_HUP : strcpy(desc,"SIGHUP (Hangup signal)");break;
        case SIG_INT : strcpy(desc,"SIGINT (Interrupt from keyboard, Crlt-C)");break;
        case SIG_QUIT: strcpy(desc,"SIGQUIT (Quit from keyboard, Ctrl-C)");break;
        case SIG_ILL : strcpy(desc,"SIGILL (Illegal instruction)");break;
        case SIG_ABRT: strcpy(desc,"SIGABRT (Abort signal)");break;
        case SIG_FPE : strcpy(desc,"SIGFPE (Floating point error)");break;
        case SIG_SEGV: strcpy(desc,"SIGSEGV (Invalid memory reference)");break;
        case SIG_PIPE: strcpy(desc,"SIGPIPE (Broken pipe)");break;
        case SIG_TERM: strcpy(desc,"SIGTERM (Termination signal)");break;

        case SIG_CONT: strcpy(desc,"SIGCONT (Continue signal)");break;
        case SIG_STOP: strcpy(desc,"SIGSTOP (Stop, unblockable)");break;
        case SIG_KILL: strcpy(desc,"SIGKILL (Kill, unblockable)");break;

        default: sprintf(desc,"SIG<%d> (Unknown signal)",cccsig);
    }
    _retcb(desc);
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_signal_setmask(int argno) //szignálok letiltása
{ 
    CCC_PROLOG("signal_setmask",1);
    int mask=sigcccmask;
    if( !ISNIL(1) )
    {
        sigcccmask = _parni(1);
    }
    _retni(mask);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_mask(int argno) //szignálok letiltása
{ 
    CCC_PROLOG("signal_mask",1);
    int mask=sigcccmask;
    if( !ISNIL(1) )
    {
        sigcccmask |= _parni(1);
    }
    _retni(mask);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_unmask(int argno) //szignálok letiltása
{ 
    CCC_PROLOG("signal_unmask",1);
    int mask=sigcccmask;
    if( !ISNIL(1) )
    {
        sigcccmask &= ~_parni(1);
    }
    _retni(mask);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_lock(int argno) //blokkolja a szignálokat (kurrens szál)
{ 
    SIGNAL_LOCK();//(++siglocklev)
    stack-=argno;
    PUSH(&NIL);
}

//---------------------------------------------------------------------------
void _clp_signal_unlock(int argno) //engedélyezi és feldolgozza a függő szignálokat
{ 
    SIGNAL_UNLOCK();//((--siglocklev==0)&&(signumpend!=0)?signal_raise(signumpend):0)
    stack-=argno;
    PUSH(&NIL);
}

//---------------------------------------------------------------------------
