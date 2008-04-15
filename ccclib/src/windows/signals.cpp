
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
#include <signal.ch>

#include <cccapi.h>

//--------------------------------------------------------------------------
static int cccsig2signum(int cccsig)
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
static int signum2cccsig(int signum)
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
static void signal_handler(int signum)
{
    signal(signum,signal_handler);

    int cccsig=signum2cccsig(signum);
    //printf("\nSignal received: cccsig=%d pid=%d\n",cccsig,getpid());fflush(0);

    if( cccsig==0 )
    {
        return;
    }

#ifdef MULTITHREAD
    if( 0==thread_data_ptr )
    {
        return;  //új szál, nincs még thread_data-ja
    }
#endif    

    if( (cccsig&~sigcccmask)==0 ) 
    {
        return;
    }

    if( siglocklev>0 ) //egy szálra vonatkozó szemafor kapcsoló
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

//-------------------------------------------------------------------------
static BOOL ctrlc_handler(DWORD event) 
{
    //fprintf(stderr,"CTRL_C received\n");fflush(0);

    //A CTRL_C kezelés más, mint a többi, mert új szál keletkezik. 
    //Hogy a stack makrónak és társainak értelme legyen, csinálni kell 
    //egy külön thread_data objektumot. A "new thread_data()"-t minimum 
    //vartab_lock0() védi, és a szál befejeződésekor törölni kell.
    
    //Mivel a CTRL_C külön szálat indít, nem lehet ellene siglocklev-vel 
    //védekezni (mint UNIX-on), hiszen a szálnak még nincs thread_data-ja.
    //Ugyanezért viszont nincs is szükség a védelemre.
    
    //Egyszálúra fordított CCC-ben ez nem működhet, ui. a szálaknak
    //nincs külön vermük, azaz a stack, siglocklev, stb. globálisak.
    //Egyszálú CCC-ben ezért a CTRL_C-t elnyomjuk.
    
#ifdef MULTITHREAD
    //extern void vartab_lock0();
    //extern void vartab_unlock0();

    vartab_lock0();
    TlsSetValue(thread_key,NEWTHRDATA());
    vartab_unlock();

    siglocklev=1;           //jobb, ha nem rekurzív
    signumpend=0;           //tiszta lap

    VALUE save=*stack;
    _clp_signalblock(0);
    number(SIG_INT);
    _clp_eval(2);
    pop();
    *stack=save;

    vartab_lock();
    DELTHRDATA(TlsGetValue(thread_key));
    vartab_unlock0();
#endif
    return 1; 
}
 
//-------------------------------------------------------------------------
void setup_signal_handlers()
{
    // WATCOM-C-ben az stdin/stdout/stderr streamekben lévő
    // filédescriptor tag értéke mindig 0/1/1, akkor is, ha ezekhez 
    // nem tartozik valódi nyitott filé. Ha ezután egy később
    // megnyíló filé megkapja a 0 vagy 1 számokat descriptornak,
    // akkor az stdout-ba szánt írás tévesen belemegy a filébe
    // (pl. a ? operátor beleír a SZAMLA.DBF-be). 
    //
    // Hogy ez ne lehessen így, az alábbi while elhasználja
    // a szabad alacsony filé descriptorokat, tehát azokat NEM
    // kaphatja meg egy később megnyíló dbf vagy bt filé.
    // Ez egyúttal az érvénytelen descriptorú standard streamek
    // NUL-ba irányítását jelenti.

#if defined MSVC
    while( _open("NUL",_O_RDWR)<3 ); //stdout NUL-ba irányítása
#elif defined MINGW
    while( _open("NUL",_O_RDWR)<3 ); //stdout NUL-ba irányítása
#elif defined WATCOM
    while( open("NUL",O_RDWR)<3 );   //stdout NUL-ba irányítása
#elif defined BORLAND
    while( open("NUL",O_RDWR)<3 );   //stdout NUL-ba irányítása
#endif

    signal(SIGFPE,signal_handler);
    signal(SIGSEGV,signal_handler);
    signal(SIGINT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGABRT,signal_handler);
    signal(SIGILL,signal_handler);
    
    //A CTRL_C kezelés más, mint a többi, mert külön szál
    //keletkezik. Ahhoz, hogy a stack makrónak értelme legyen
    //csinálni kell egy külön thread_data objektumot.
    
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlc_handler,1); 
}
 
//--------------------------------------------------------------------------
int signal_raise(int cccsig)
{
    int cnt=0;
  //if( cccsig&SIG_HUP ) {++cnt; signal_handler(SIGHUP);}
    if( cccsig&SIG_INT ) {++cnt; signal_handler(SIGINT);}
  //if( cccsig&SIG_QUIT) {++cnt; signal_handler(SIGQUIT);}
    if( cccsig&SIG_ILL ) {++cnt; signal_handler(SIGILL);}
    if( cccsig&SIG_ABRT) {++cnt; signal_handler(SIGABRT);}
    if( cccsig&SIG_FPE ) {++cnt; signal_handler(SIGFPE);}
    if( cccsig&SIG_SEGV) {++cnt; signal_handler(SIGSEGV);}
  //if( cccsig&SIG_PIPE) {++cnt; signal_handler(SIGPIPE);}
    if( cccsig&SIG_TERM) {++cnt; signal_handler(SIGTERM);}
    return cnt;
}

//--------------------------------------------------------------------------
int signal_send(int pid, int cccsig)
{
    int cnt=0;
    #ifdef WINDOWSON_NINCS_KILL
  //if( cccsig&SIG_HUP ) {++cnt; kill(pid,SIGHUP);}
    if( cccsig&SIG_INT ) {++cnt; kill(pid,SIGINT);}
  //if( cccsig&SIG_QUIT) {++cnt; kill(pid,SIGQUIT);}
    if( cccsig&SIG_ILL ) {++cnt; kill(pid,SIGILL);}
    if( cccsig&SIG_ABRT) {++cnt; kill(pid,SIGABRT);}
    if( cccsig&SIG_FPE ) {++cnt; kill(pid,SIGFPE);}
    if( cccsig&SIG_SEGV) {++cnt; kill(pid,SIGSEGV);}
  //if( cccsig&SIG_PIPE) {++cnt; kill(pid,SIGPIPE);}
    if( cccsig&SIG_TERM) {++cnt; kill(pid,SIGTERM);}

  //if( cccsig&SIG_CONT) {++cnt; kill(pid,SIGCONT);}
  //if( cccsig&SIG_STOP) {++cnt; kill(pid,SIGSTOP);}
  //if( cccsig&SIG_KILL) {++cnt; kill(pid,SIGKILL);}
    #endif
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

