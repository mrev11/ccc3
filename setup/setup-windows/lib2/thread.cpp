
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

//WINDOWS thread API

#include <cccapi.h>
 
#ifndef MULTITHREAD

const int MULTITHREAD_SUPPORT=0;

void _clp_thread_create(int argno){stack-=argno;PUSHNIL();}
void _clp_thread_self(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_detach(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_exit(int argno){stack-=argno;PUSHNIL();} 
//void _clp_thread_cancel(int argno){stack-=argno;PUSHNIL();} 
//void _clp_thread_testcancel(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_join(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_mutex_init(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_mutex_lock(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_mutex_trylock(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_mutex_unlock(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_mutex_destroy(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_cond_init(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_cond_signal(int argno){stack-=argno;PUSHNIL();} 
//void _clp_thread_cond_broadcast(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_cond_wait(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_cond_destroy(int argno){stack-=argno;PUSHNIL();} 
void _clp_thread_create_detach(int argno){stack-=argno;PUSHNIL();}

#else

const int MULTITHREAD_SUPPORT=1;

//extern void vartab_lock0();
//extern void vartab_unlock0();
 
static HANDLE mutex=CreateMutex(0,0,0);
static HANDLE event=CreateEvent(0,0,0,0); 

struct thread_block
{
    VALUE *blk; 
    int argno;
    int sigllev;
    int sigmask;
};

int WCODE(int x)
{
         if( x==WAIT_FAILED )       return GetLastError();
    else if( x==WAIT_TIMEOUT )      return x;
  //else if( x==WAIT_ABANDONED )    return x;
    else                            return 0;
}

//---------------------------------------------------------------------------
static void *thread(void *ptr)
{
    //saját lokális stack létrehozása,
    //thread_data konstruktorában és destruktorában
    //listakezelés van, aminek egyedül kell futnia,
    //a listát a szemétgyűjtés is használja:

    vartab_lock0(); //nincs még siglocklev
    TlsSetValue(thread_key,NEWTHRDATA());
    vartab_unlock0(); //nem bántjuk siglocklev-et (1)

    //block plusz paraméterek átmásolása a saját stackre,
    //a hívó szálnak várnia kell, erre szolgál mutex és cond:

    thread_block *b=(thread_block*)ptr;
    int n;
    for(n=0; n<b->argno; n++)
    {
        PUSH((b->blk)+n);
    }
    sigcccmask=b->sigmask; //öröklődik
    siglocklev=b->sigllev; //öröklődik (eddig 1 volt)

    SetEvent(event);

    //a hívó szál továbbengedve,
    //az új szál kódblokkja elindítva:
    
    _clp_eval(n);
    POP();

    //a szál futása befejeződött,
    //az eredményt eldobjuk (nem tudjuk visszaadni),
    //a saját lokális stacket megszüntetjük:

    vartab_lock();
    DELTHRDATA(TlsGetValue(thread_key));
    vartab_unlock0(); //nincs már siglocklev

    return 0;
}

//---------------------------------------------------------------------------
void _clp_thread_create(int argno)  // thread_create(blk,arg1,arg2,...)
{
    VALUE *blk=stack-argno;
    if( blk->type!=TYPE_BLOCK )
    {
        error_blk("thread_create",blk,argno);    
    }

    thread_block b;
    b.blk=blk;
    b.argno=argno;
    b.sigllev=siglocklev; //öröklődik
    b.sigmask=sigcccmask; //öröklődik

    SIGNAL_LOCK();  //az aktuális szálra voatkozik

    WaitForSingleObject(mutex,INFINITE);
    ResetEvent(event);
    DWORD threadid=0;
    HANDLE thandle=CreateThread(0,0,(LPTHREAD_START_ROUTINE)thread,&b,0,&threadid);
    if( thandle )
    {
        WaitForSingleObject(event,INFINITE);
        ReleaseMutex(mutex);
        SIGNAL_UNLOCK(); //az aktuális szálra voatkozik
        stack-=argno;
        pointer( (void*)thandle );
    }
    else
    {
        //printf("GetLastError %d %x\n",GetLastError(),GetLastError());
        //fflush(0);
        ReleaseMutex(mutex);
        SIGNAL_UNLOCK(); //az aktuális szálra voatkozik
        stack-=argno;
        PUSHNIL();
    }
}


//---------------------------------------------------------------------------
void _clp_thread_self(int argno)
{
    stack-=argno;

    //DWORD threadid=GetCurrentThreadId();
    //pointer( (void*)threadid );
    //(warningot ad cast-ra, helyette union)


    union{ void *ptr; DWORD dwd;} threadid;
    threadid.ptr=0; 
    threadid.dwd=GetCurrentThreadId(); 
    pointer( threadid.ptr );

    
    //Ad egy szálra egyedi azonosítót.
    //Nem egyezik thread_create értékével!
}
 
//---------------------------------------------------------------------------
void _clp_thread_detach(int argno)
{
    CCC_PROLOG("thread_detach",1);
    _retni( CloseHandle((HANDLE)_parp(1))?0:GetLastError() );
    CCC_EPILOG();
}
 
//---------------------------------------------------------------------------
void _clp_thread_exit(int argno)
{
    CCC_PROLOG("thread_exit",0);
    vartab_lock();
    //delete (thread_data*)TlsGetValue(thread_key); //Boehm-gc
    DELTHRDATA(TlsGetValue(thread_key));
    vartab_unlock0();
    ExitThread(0);
    _ret();
    CCC_EPILOG();
}


 
//---------------------------------------------------------------------------
//void _clp_thread_cancel(int argno)
//{
//    CCC_PROLOG("thread_cancel",1);
//    pthread_t t=(pthread_t)_parp(1);
//    _retni( pthread_cancel(t));
//    CCC_EPILOG();
//}

//---------------------------------------------------------------------------
//void _clp_thread_testcancel(int argno)
//{
//    pthread_testcancel();
//    stack-=argno;
//    PUSH(&NIL);
//}

 
//---------------------------------------------------------------------------
void _clp_thread_join(int argno)
{
    CCC_PROLOG("thread_join",1);
    HANDLE t=(HANDLE)_parp(1);
    int result=WaitForSingleObject(t,INFINITE);
    _retni( WCODE(result) );
    CloseHandle(t);
    CCC_EPILOG();
}

 
//---------------------------------------------------------------------------
void _clp_thread_mutex_init(int argno)
{
    CCC_PROLOG("thread_mutex_init",0);
    HANDLE mutex=CreateMutex(0,0,0);
    _retp( (void*)mutex );
    CCC_EPILOG();
}

 
//---------------------------------------------------------------------------
void _clp_thread_mutex_lock(int argno)
{
    CCC_PROLOG("thread_mutex_lock",1);
    HANDLE mutex=(HANDLE)_parp(1);
    int result=WaitForSingleObject(mutex,INFINITE);
    _retni( WCODE(result) );
    CCC_EPILOG();
}

 
//---------------------------------------------------------------------------
void _clp_thread_mutex_trylock(int argno)
{
    CCC_PROLOG("thread_mutex_trylock",1);
    HANDLE mutex=(HANDLE)_parp(1);
    int result=WaitForSingleObject(mutex,0);
    _retni( WCODE(result) );
    CCC_EPILOG();
}

 
//---------------------------------------------------------------------------
void _clp_thread_mutex_unlock(int argno)
{
    CCC_PROLOG("thread_mutex_unlock",1);
    HANDLE mutex=(HANDLE)_parp(1);
    _retni( ReleaseMutex(mutex)?0:GetLastError() );
    CCC_EPILOG();
}
         
 
//---------------------------------------------------------------------------
void _clp_thread_mutex_destroy(int argno)
{
    CCC_PROLOG("thread_mutex_destroy",1);
    HANDLE mutex=(HANDLE)_parp(1);
    _retni( CloseHandle(mutex)?0:GetLastError() );
    CCC_EPILOG();
}

 
//---------------------------------------------------------------------------
void _clp_thread_cond_init(int argno)
{
    CCC_PROLOG("thread_cond_init",0);
    HANDLE cond=CreateEvent(0,1,0,0); 
    _retp( (void*)cond );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_cond_signal(int argno)
{
    CCC_PROLOG("thread_cond_signal",1);
    HANDLE cond=(HANDLE)_parp(1);
    _retni( SetEvent(cond)?0:GetLastError() );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
//void _clp_thread_cond_broadcast(int argno)
//{
//    CCC_PROLOG("thread_cond_broadcast",1);
//    HANDLE cond=(HANDLE)_parp(1);
//    _retni( PulseEvent(cond)?0:GetLastError() );
//    CCC_EPILOG();
//}
 
//---------------------------------------------------------------------------
void _clp_thread_cond_wait(int argno)
{
    CCC_PROLOG("thread_cond_wait",3);
    HANDLE cond=(HANDLE)_parp(1);
    HANDLE mutex=(HANDLE)_parp(2);
    DWORD wtime=ISNUMBER(3)?_parnu(3):INFINITE;
    ResetEvent(cond);
    ReleaseMutex(mutex);
    int result=WaitForSingleObject(cond,wtime);
    _retni( WCODE(result) );
    WaitForSingleObject(mutex,INFINITE);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_cond_destroy(int argno)
{
    CCC_PROLOG("thread_cond_destroy",1);
    HANDLE cond=(HANDLE)_parp(1);
    _retni( CloseHandle(cond)?0:GetLastError() );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_create_detach(int argno)
{
    _clp_thread_create(argno);
    _clp_thread_detach(1);
}

//---------------------------------------------------------------------------

#endif


