
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

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <signal.ch>
#include <cccapi.h>

__stdcall static BOOL ctrlc_handler(DWORD event);

extern void setup_signal_handlers();
static void signal_handler(int);
extern int  signal_send(int pid, int sig);
extern int  signal_raise(int signum);
extern int  signal_lock();
extern int  signal_unlock();
extern int  cccsig2signum(int cccsig);
extern int  signum2cccsig(int signum);

//--------------------------------------------------------------------------

static int siglocklev=0;

static unsigned sigmask=0;  // bits for CCC signal numbers
static unsigned sigsave=0;  // bits for CCC signal numbers
static unsigned sigpend=0;  // bits for CCC signal numbers


//-------------------------------------------------------------------------
void setup_signal_handlers()
{
    signal(SIGFPE,signal_handler);
    signal(SIGSEGV,signal_handler);
    signal(SIGINT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGABRT,signal_handler);
    signal(SIGILL,signal_handler);
    
    SetConsoleCtrlHandler(0,0); 

    //If the HandlerRoutine parameter is NULL, 
    //a TRUE value causes the calling process to ignore CTRL+C input, 
    //and a FALSE value restores normal processing of CTRL+C input. 
    //This attribute of ignoring or processing CTRL+C is inherited 
    //by child processes. (Visszaállítjuk a _normál_ állapotot.)

    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlc_handler,1); 
}

//--------------------------------------------------------------------------
static void signal_handler(int signum)
{
    signal(signum,signal_handler);
    int cccsig=signum2cccsig(signum);

    if( (cccsig&sigmask)!=0 )
    {
        //ignored
        sigpend|=cccsig;
        return;
    }

    // return;
    // vagy inkabb lepjunk ki?

    fprintf(stderr,"Signal (%d) received: %s now quits\n",signum,*ARGV);
    exit(1);
}

//-------------------------------------------------------------------------
__stdcall static BOOL ctrlc_handler(DWORD event) 
{
    if( (SIG_INT&sigmask)==0 )
    {
        // SIG_INT nincs maszkolva
        // fprintf(stderr,"CTRL_C received\n");fflush(0);

        pthread_setspecific(thread_key,NEWTHRDATA());
        _clp_signalblock(0);
        number(SIG_INT);
        _clp_eval(2);
        pop();
        DELTHRDATA(pthread_getspecific(thread_key));
    }
    return 1; 
}
 
//--------------------------------------------------------------------------
int signal_send(int pid, int cccsig)
{
    return 0;
}

//--------------------------------------------------------------------------
int signal_raise(int signum)
{
    return raise(signum);
}

//--------------------------------------------------------------------------
int signal_lock()
{
    if( siglocklev==0 )
    {
        sigsave=sigmask;
        sigmask=-1;
        sigpend=0;

    }
    return ++siglocklev;
}

//--------------------------------------------------------------------------
int signal_unlock()
{
    if( siglocklev<=0 )
    {
        return 0;
    }
    else if( siglocklev==1 )
    {
        sigmask=sigsave;
        sigsave=0;
    }
    return --siglocklev;
}


//--------------------------------------------------------------------------
int cccsig2signum(int cccsig)
{
    switch( cccsig )
    {
      //case SIG_HUP : return SIGHUP;    // Hangup (POSIX)
        case SIG_INT : return SIGINT;    // Interrupt (ANSI)
      //case SIG_QUIT: return SIGQUIT;   // Quit (POSIX)
        case SIG_ILL : return SIGILL;    // Illegal instruction (ANSI)
        case SIG_ABRT: return SIGABRT;   // Abort (ANSI)
        case SIG_FPE : return SIGFPE;    // Floating-point exception (ANSI)
        case SIG_SEGV: return SIGSEGV;   // Segmentation violation (ANSI)
      //case SIG_PIPE: return SIGPIPE;   // Broken pipe (POSIX)
        case SIG_TERM: return SIGTERM;   // Termination (ANSI)

      //case SIG_CONT: return SIGCONT;   // Continue (POSIX)
      //case SIG_STOP: return SIGSTOP;   // Stop, unblockable (POSIX)
      //case SIG_KILL: return SIGKILL;   // Kill, unblockable (POSIX)
    }
    return 0;
}

//--------------------------------------------------------------------------
int signum2cccsig(int signum)
{
    switch( signum )
    {
      //case SIGHUP : return SIG_HUP;    // Hangup (POSIX)
        case SIGINT : return SIG_INT;    // Interrupt (ANSI)
      //case SIGQUIT: return SIG_QUIT;   // Quit (POSIX)
        case SIGILL : return SIG_ILL;    // Illegal instruction (ANSI)
        case SIGABRT: return SIG_ABRT;   // Abort (ANSI)
        case SIGFPE : return SIG_FPE;    // Floating-point exception (ANSI)
        case SIGSEGV: return SIG_SEGV;   // Segmentation violation (ANSI)
      //case SIGPIPE: return SIG_PIPE;   // Broken pipe (POSIX)
        case SIGTERM: return SIG_TERM;   // Termination (ANSI)

      //case SIGCONT: return SIG_CONT;   // Continue (POSIX)
      //case SIGSTOP: return SIG_STOP;   // Stop, unblockable (POSIX)
      //case SIGKILL: return SIG_KILL;   // Kill, unblockable (POSIX)
    }
    return 0;
}

//--------------------------------------------------------------------------
// CCC interface
//--------------------------------------------------------------------------
void _clp_signal_description(int argno) //szignál leírása
{
    CCC_PROLOG("signal_description",1);
    int cccsig=_parni(1);
    char desc[128];
    switch(cccsig)
    {
      //case SIG_HUP : strcpy(desc,"SIGHUP (Hangup signal)");break;
        case SIG_INT : strcpy(desc,"SIGINT (Interrupt from keyboard, Crlt-C)");break;
      //case SIG_QUIT: strcpy(desc,"SIGQUIT (Quit from keyboard, Ctrl-C)");break;
        case SIG_ILL : strcpy(desc,"SIGILL (Illegal instruction)");break;
        case SIG_ABRT: strcpy(desc,"SIGABRT (Abort signal)");break;
        case SIG_FPE : strcpy(desc,"SIGFPE (Floating point error)");break;
        case SIG_SEGV: strcpy(desc,"SIGSEGV (Invalid memory reference)");break;
      //case SIG_PIPE: strcpy(desc,"SIGPIPE (Broken pipe)");break;
        case SIG_TERM: strcpy(desc,"SIGTERM (Termination signal)");break;

      //case SIG_CONT: strcpy(desc,"SIGCONT (Continue signal)");break;
      //case SIG_STOP: strcpy(desc,"SIGSTOP (Stop, unblockable)");break;
      //case SIG_KILL: strcpy(desc,"SIGKILL (Kill, unblockable)");break;

        default: sprintf(desc,"SIG<%d> (Unknown signal)",cccsig);
    }
    _retcb(desc);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_raise(int argno)
{
    CCC_PROLOG("signal_raise",1);
    int cccsig=_parni(1);
    
  //if( cccsig&SIG_HUP ) {signal_raise(SIGHUP);}
    if( cccsig&SIG_INT ) {signal_raise(SIGINT);}
  //if( cccsig&SIG_QUIT) {signal_raise(SIGQUIT);}
    if( cccsig&SIG_ILL ) {signal_raise(SIGILL);}
    if( cccsig&SIG_ABRT) {signal_raise(SIGABRT);}
    if( cccsig&SIG_FPE ) {signal_raise(SIGFPE);}
    if( cccsig&SIG_SEGV) {signal_raise(SIGSEGV);}
  //if( cccsig&SIG_PIPE) {signal_raise(SIGPIPE);}
    if( cccsig&SIG_TERM) {signal_raise(SIGTERM);}
  //if( cccsig&SIG_ALRM) {signal_raise(SIGALRM);}
  //if( cccsig&SIG_TSTP) {signal_raise(SIGTSTP);}

    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_send(int argno)
{
    CCC_PROLOG("signal_send",2);
    int pid=_parni(1);
    int signum=cccsig2signum(_parni(2));
    _retni(signal_send(pid,signum));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_lock(int argno)
{
    CCC_PROLOG("signal_lock",0);
    _retni(signal_lock());
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_signal_unlock(int argno)
{
    CCC_PROLOG("signal_unlock",0);
    _retni(signal_unlock());
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_signal_getpend(int argno)
{
    CCC_PROLOG("signal_getpend",0);
    _retni(sigpend);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_getmask(int argno)
{
    CCC_PROLOG("signal_getmask",0);
    _retni(sigmask);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_setmask(int argno) //szignálok letiltása
{ 
    CCC_PROLOG("signal_setmask",1);
    sigmask=_parni(1);
    _ret();
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_signal_mask(int argno) //szignálok letiltása
{ 
    CCC_PROLOG("signal_mask",1);
    sigmask |= _parni(1);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_signal_unmask(int argno) 
{ 
    CCC_PROLOG("signal_unmask",1);
    sigmask &= ~_parni(1);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------


