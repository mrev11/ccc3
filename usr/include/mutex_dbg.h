
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

//MUTEX_DBG: deadlockok felderítésére szolgál.
//Ha definiálva van, saját nyilvántartást vezet a lockolt mutexekről, 
//és deadlock esetén megpróbál úgy megállni, hogy a gdb backtrace 
//segítségével meg lehessen állapítani a deadlock helyét és okát.
//Ezt a forrást a unixos thread.cpp inkludálja.
//
//Ahhoz hogy a backtrace informatív legyen:
//  -O6 helyett -ggdb opcióval kell fordítani,
//  telepíteni kell a libc debug változatát,
//  és annak helyét meg kell adni az LD_LIBRARY_PATH-ban.

#ifdef MUTEX_DBG
//---------------------------------------------------------------------------
#define MAXMUT 2047

struct MUTEX_HASH{

    int mutcnt;

    struct
    {
        pthread_mutex_t *mut;
        pthread_t thr;
    }   mutlst[MAXMUT];
    
    MUTEX_HASH() //konstruktor
    {
        mutcnt=0;
        for(int i=0; i<MAXMUT; i++)
        {
            mutlst[i].mut=0;
            mutlst[i].thr=0;
        }
    }

    MUTEX_HASH(MUTEX_HASH *other) //konstruktor
    {
        mutcnt=0;
        for(int i=0; i<MAXMUT; i++)
        {
            mutlst[i].mut=0;
            mutlst[i].thr=0;
        }

        for(int i=0; i<MAXMUT; i++)
        {
            if( other->mutlst[i].thr!=0 )
            {
                int x=this->mutidx(other->mutlst[i].mut);
                mutlst[x].thr=other->mutlst[i].thr;
            }
        }
    }

    int mutidx(pthread_mutex_t *m)
    {
        int hidx=((unsigned long)m)%MAXMUT;
        while(1)
        {
            if( mutlst[hidx].mut==0 )
            {
                if( mutcnt>MAXMUT/2 )
                {
                    hidx=-1;
                    break;
                }
                //else
                //{
                //    printf("\nmutex: %d %d %lx",mutcnt,hidx,(unsigned long)m);fflush(0);
                //}

                mutlst[hidx].mut=m;
                mutcnt++;
                break;
            }
            else if( mutlst[hidx].mut==m )
            {
                break;
            }
            else if( ++hidx>=MAXMUT )
            {
                hidx=0;
            }
        }
        return hidx;
    }    
};

static MUTEX_HASH *mutex_list=new MUTEX_HASH();

//---------------------------------------------------------------------------
static int mutidx(pthread_mutex_t *m)
{
    int x=mutex_list->mutidx(m);
    if( x<0 )
    {
        MUTEX_HASH *list=new MUTEX_HASH(mutex_list);
        printf("\nMUTEX_HASH rebuild %d -> %d", mutex_list->mutcnt, list->mutcnt);
        delete mutex_list;
        mutex_list=list;
    }
    x=mutex_list->mutidx(m);
    if( x<0 )
    {
        printf("\ntoo many mutex\n");
        exit(1);
    }
    return x;
}

static pthread_mutex_t mutex_hash_mutex=PTHREAD_MUTEX_INITIALIZER;

static void lck(pthread_mutex_t *m)
{
    //return;
    pthread_mutex_lock(&mutex_hash_mutex);
    int x=mutidx(m);
    mutex_list->mutlst[x].thr=pthread_self();
    pthread_mutex_unlock(&mutex_hash_mutex);
}

static void unlck(pthread_mutex_t *m)
{
    //return;
    pthread_mutex_lock(&mutex_hash_mutex);
    int x=mutidx(m);
    mutex_list->mutlst[x].thr=0;
    pthread_mutex_unlock(&mutex_hash_mutex);
}

static void sleep_forever(pthread_t thr)
{
    sleep(36000); //leáll (10 órára)
}

static void sleep_short(int n)
{
    usleep(1);
}

static void halt(pthread_mutex_t *m)
{
    pthread_mutex_lock(&mutex_hash_mutex);
    int x=mutidx(m);
    pthread_t thr=mutex_list->mutlst[x].thr;
    printf("\nhalt(%ld) %lx %ld",(long)pthread_self(),(unsigned long)m,(long)thr); fflush(0);
    pthread_mutex_unlock(&mutex_hash_mutex);

    sleep_forever(thr);
}

//---------------------------------------------------------------------------
int pthread_mutex_lock_wrapper(pthread_mutex_t *m)
{
    int n=0;
    int result=pthread_mutex_trylock(m);
    while( result )
    {
        if( result!=EBUSY )
        {
            printf("pthread_mutex_lock %d\n",result);fflush(0);
        }
        if( ++n>2000 )
        {
            halt(m); //nem sikerült
        }
        sleep_short(n);
        result=pthread_mutex_trylock(m);
    }
    lck(m);
    return result;
}

//---------------------------------------------------------------------------
int pthread_mutex_unlock_wrapper(pthread_mutex_t *m)
{
    unlck(m);
    int result=pthread_mutex_unlock(m);
    if( result )
    {
        printf("pthread_mutex_unlock %d\n",result);fflush(0);
    }
    return result;
}

//---------------------------------------------------------------------------
#define pthread_mutex_lock(x)    pthread_mutex_lock_wrapper(x)
#define pthread_mutex_unlock(x)  pthread_mutex_unlock_wrapper(x)
//---------------------------------------------------------------------------

#endif //MUTEX_DBG
