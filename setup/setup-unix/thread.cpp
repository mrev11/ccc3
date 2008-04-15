
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

//POSIX thread API

#include <signal.h>
#include <pthread.h>
#include <errno.h>
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

static pthread_mutex_t mutcre=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond=PTHREAD_COND_INITIALIZER; 

struct thread_block
{
    VALUE *blk; 
    int argno;
    int sigllev;
    int sigmask;
};

//---------------------------------------------------------------------------
static sigset_t signal_mask()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGHUP);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGILL);
    sigaddset(&set,SIGABRT);
    sigaddset(&set,SIGFPE);
    sigaddset(&set,SIGSEGV);
    sigaddset(&set,SIGPIPE);
    sigaddset(&set,SIGTERM);
    return set;
}

static sigset_t sigmask=signal_mask();

#ifdef MUTEX_DBG //deadlockok kereséséhez
#include <mutex_dbg.h>
#endif

//---------------------------------------------------------------------------
static void *thread(void *ptr)
{
    //saját lokális stack létrehozása,
    //thread_data konstruktorában és destruktorában
    //listakezelés van, aminek egyedül kell futnia,
    //a listát a szemétgyűjtés is használja:

    sigprocmask(SIG_BLOCK,&sigmask,0);

    vartab_lock0(); //nincs még siglocklev
    pthread_setspecific(thread_key, NEWTHRDATA());
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

    pthread_mutex_lock(&mutex);
    b->argno=-1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    sigprocmask(SIG_UNBLOCK,&sigmask,0);

    //a hívó szál továbbengedve,
    //az új szál kódblokkja elindítva:

    _clp_eval(n);
    POP();

    //a szál futása befejeződött,
    //az eredményt eldobjuk (nem tudjuk visszaadni),
    //a saját lokális stacket megszüntetjük:

    sigprocmask(SIG_BLOCK,&sigmask,0);
    vartab_lock0();
    DELTHRDATA(pthread_getspecific(thread_key));
    vartab_unlock0(); //nincs már siglocklev
    //sigprocmask(SIG_UNBLOCK,&sigmask,0);

    //vartab_unlock0() nélkül lockolva marad a mutex,
    //azaz egy megszűnt szál lockja megmarad (rendszer hiba);
    //a vartab_unlock0()-ban levő pthread_mutex_unlock gyakran
    //SIGSEGV-zik, ha szignált kap (rendszer hiba);
    //ha itt "sigprocmask(SIG_UNBLOCK,&sigmask,0);" hivással
    //töröljük a maszkolást, akkor gyakran SIGSEGV-zik a program;
    //a man nem ír arról, hogy a maszkolás
    //a szálakra nézve privát, vagy globális,
    //de a tapasztalat azt mutatja, hogy privát;

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

    SIGNAL_LOCK();  //az aktuális szálra vonatkozik

    pthread_mutex_lock(&mutcre);
    pthread_mutex_lock(&mutex);
    pthread_t t=0;

    if( 0==pthread_create(&t,0,thread,&b) )
    {
        //várunk, amíg az új szál átveszi a paramétereket
        while( b.argno>=0 )
        {
            pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutcre);
        SIGNAL_UNLOCK(); //az aktuális szálra vonatkozik
        stack-=argno;
        pointer( (void*)t );
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutcre);
        SIGNAL_UNLOCK(); //az aktuális szálra vonatkozik
        stack-=argno;
        PUSHNIL();
    }
}

//---------------------------------------------------------------------------
void _clp_thread_self(int argno)
{
    stack-=argno;
    pointer( (void*)pthread_self() );
}

//---------------------------------------------------------------------------
void _clp_thread_detach(int argno)
{
    CCC_PROLOG("thread_detach",1);
    pthread_t t=(pthread_t)_parp(1);
    _retni( pthread_detach(t));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_exit(int argno)
{
    CCC_PROLOG("thread_exit",0);
    sigprocmask(SIG_BLOCK,&sigmask,0);
    vartab_lock();
    delete (thread_data*)pthread_getspecific(thread_key);
    vartab_unlock0();
    pthread_exit(0);
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
    pthread_t t=(pthread_t)_parp(1);
    _retni( pthread_join(t,0));
    CCC_EPILOG();
}
 
//---------------------------------------------------------------------------
void _clp_thread_mutex_init(int argno)
{
    CCC_PROLOG("thread_mutex_init",0);
    pthread_mutex_t mut;
    pthread_mutex_init(&mut,0);
    _retblen((char*)&mut,sizeof(mut));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_mutex_lock(int argno)
{
    CCC_PROLOG("thread_mutex_lock",1);
    _retni( pthread_mutex_lock((pthread_mutex_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_mutex_trylock(int argno)
{
    CCC_PROLOG("thread_mutex_trylock",1);
    _retni( pthread_mutex_trylock((pthread_mutex_t*)_parb(1)) );
    CCC_EPILOG();
}
 
//---------------------------------------------------------------------------
void _clp_thread_mutex_unlock(int argno)
{
    CCC_PROLOG("thread_mutex_unlock",1);
    _retni( pthread_mutex_unlock((pthread_mutex_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_mutex_destroy(int argno)
{
    CCC_PROLOG("thread_mutex_destroy",1);
    _retni( pthread_mutex_destroy((pthread_mutex_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_cond_init(int argno)
{
    CCC_PROLOG("thread_cond_init",0);
    pthread_cond_t cond;
    pthread_cond_init(&cond,0);
    _retblen((char*)&cond,sizeof(cond));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_cond_signal(int argno)
{
    CCC_PROLOG("thread_cond_signal",1);
    _retni( pthread_cond_broadcast((pthread_cond_t*)_parb(1)) );
    //_retni( pthread_cond_signal((pthread_cond_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
//void _clp_thread_cond_broadcast(int argno)
//{
//    CCC_PROLOG("thread_cond_broadcast",1);
//    _retni( pthread_cond_broadcast((pthread_cond_t*)_parb(1)) );
//    CCC_EPILOG();
//}
 
//---------------------------------------------------------------------------
void _clp_thread_cond_wait(int argno)
{
    CCC_PROLOG("thread_cond_wait",3);
    pthread_cond_t *c=(pthread_cond_t*)_parb(1);
    pthread_mutex_t *m=(pthread_mutex_t*)_parb(2);
    if( ISNUMBER(3) )
    {
        unsigned millis=_parnu(3);
        struct timespec ts;
        ts.tv_sec=millis/1000;
        ts.tv_nsec=(millis%1000)*1000*1000; //nanosecundum
        _retni( pthread_cond_timedwait(c,m,&ts) );
    }
    else
    {
        _retni( pthread_cond_wait(c,m) );
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_cond_destroy(int argno)
{
    CCC_PROLOG("thread_cond_destroy",1);
    _retni( pthread_cond_destroy((pthread_cond_t*)_parb(1)) );
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
 

