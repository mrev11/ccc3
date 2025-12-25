
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

#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <tid2ptr.h>
#include <cccapi.h>
 

static pthread_mutex_t mutcre=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  cond=PTHREAD_COND_INITIALIZER; 

struct thread_block
{
    VALUE *blk; 
    int argno;
};


#ifdef MUTEX_DBG //deadlockok keresesehez
#include <mutex_dbg.h>
#endif

//---------------------------------------------------------------------------
static void *thread(void *ptr)
{
    //sajat lokalis stack letrehozasa,
    //thread_data konstruktoraban es destruktoraban
    //listakezeles van, aminek egyedul kell futnia,
    //a listat a szemetgyujtes is hasznalja:


    pthread_setspecific(thread_key, NEWTHRDATA());

    //block plusz parameterek atmasolasa a sajat stackre,
    //a hivo szalnak varnia kell, erre szolgal mutex es cond:

    thread_block *b=(thread_block*)ptr;
    int n;
    for(n=0; n<b->argno; n++)
    {
        PUSH((b->blk)+n);
    }

    pthread_mutex_lock(&mutex);
    b->argno=-1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    //a hivo szal tovabbengedve,
    //az uj szal kodblokkja elinditva:

    _clp_eval(n);
    POP();

    DELTHRDATA(pthread_getspecific(thread_key));

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

    pthread_mutex_lock(&mutcre);
    pthread_mutex_lock(&mutex);
    pthread_t t=0;

    if( 0==pthread_create(&t,0,thread,&b) )
    {
        //varunk, amig az uj szal atveszi a parametereket
        while( b.argno>=0 )
        {
            pthread_cond_wait(&cond,&mutex);
        }
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutcre);
        stack-=argno;
        pointer( tid2ptr(t) );
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutcre);
        stack-=argno;
        PUSHNIL();
    }
}

//---------------------------------------------------------------------------
void _clp_thread_self(int argno)
{
    stack-=argno;
    pointer( tid2ptr(pthread_self()) );
}

//---------------------------------------------------------------------------
void _clp_thread_detach(int argno)
{
    CCC_PROLOG("thread_detach",1);
    pthread_t t=ptr2tid(_parp(1));
    _retni( pthread_detach(t));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_exit(int argno)
{
    CCC_PROLOG("thread_exit",0);
    DELTHRDATA(pthread_getspecific(thread_key));
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
    pthread_t t=ptr2tid(_parp(1));
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
void _clp_thread_cond_broadcast(int argno)
{
    CCC_PROLOG("thread_cond_broadcast",1);
    _retni( pthread_cond_broadcast((pthread_cond_t*)_parb(1)) );
    CCC_EPILOG();
}
 
//---------------------------------------------------------------------------
void _clp_thread_cond_wait(int argno)
{
    CCC_PROLOG("thread_cond_wait",3);
    pthread_cond_t *c=(pthread_cond_t*)_parb(1);
    pthread_mutex_t *m=(pthread_mutex_t*)_parb(2);
    if( ISNUMBER(3) )
    {
        unsigned millis=_parnu(3);
        struct timeval now;
        struct timespec timeout;
        gettimeofday(&now,0);
        timeout.tv_sec=now.tv_sec;
        timeout.tv_nsec=now.tv_usec*1000;
        timeout.tv_sec+=millis/1000;
        timeout.tv_nsec+=(millis%1000)*1000000;
        if( timeout.tv_nsec>999999999 )
        {
            timeout.tv_sec++;
            timeout.tv_nsec-=1000000000;
        }
        // FIGYELEM:  timeout abszolut ido
        _retni( pthread_cond_timedwait(c,m,&timeout) );
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
void _clp_thread_setname(int argno)
{
    // nonportable
    // max length of name: 15 bytes
    // only ascii names are supported 

    CCC_PROLOG("thread_setname",2);
#ifdef _LINUX_
    str2bin(base+1);
    number(15);
    _clp_left(2);
    pthread_t t=ptr2tid(_parp(1));
    const char *name=_parb(2);
    _retni( pthread_setname_np(t,name) ); // 0=ok, !0=failed
#else
    _retni(0);
#endif
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_getname(int argno)
{
    CCC_PROLOG("thread_getname",1);
    char name[32];
#ifdef _LINUX_
    pthread_t t=ptr2tid(_parp(1));
    if( 0!=pthread_getname_np(t,name,sizeof(name)) )
    {
        name[0]=0;
    }
#else
    name[0]=0;
#endif
    _retcb(name);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_init(int argno)
{
    CCC_PROLOG("thread_rwlock_init",0);
    pthread_rwlock_t rwlk;
    pthread_rwlock_init(&rwlk,0);
    _retblen((char*)&rwlk,sizeof(rwlk));
    CCC_EPILOG();
}

// static initializer
// pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

//---------------------------------------------------------------------------
void _clp_thread_rwlock_destroy(int argno)
{
    CCC_PROLOG("thread_rwlock_destroy",0);
    _retni( pthread_rwlock_destroy((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_rdlock(int argno)
{
    CCC_PROLOG("thread_rwlock_rdlock",1);
    _retni( pthread_rwlock_rdlock((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_tyrrdlock(int argno)
{
    CCC_PROLOG("thread_rwlock_tryrdlock",1);
    _retni( pthread_rwlock_tryrdlock((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_wrlock(int argno)
{
    CCC_PROLOG("thread_rwlock_wrlock",1);
    _retni( pthread_rwlock_wrlock((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_trywrlock(int argno)
{
    CCC_PROLOG("thread_rwlock_trywrlock",1);
    _retni( pthread_rwlock_trywrlock((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_thread_rwlock_unlock(int argno)
{
    CCC_PROLOG("thread_rwlock_unlock",1);
    _retni( pthread_rwlock_unlock((pthread_rwlock_t*)_parb(1)) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------


 

