
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


#ifdef EMLEKEZTETO
  Olyan malloc/realloc/free wrapper, ami Linuxon lehetővé 
  teszi a program memóriahasználatának figyelését.

  A projektből keletkezik egy libmalloc_dbg.so könyvtár, amit 
  az LD_LIBRARY_PATH-ba kell tenni. Készítünk egy scriptet, pl.:
  
  #!/bin/bash
  (LD_PRELOAD="/usr/lib/libdl.so libmalloc_dbg.so" "$@")
  
  ami úgy indítja az exe-t, hogy a spéci malloc/free/realloc 
  wrapper jut érvényre, amik meghívják az eredeti implementációt.

  A wrapper függvények számontartják a memóriablokkokat.
  Lehet figyelni, hogy nem nő-e lassacskán a számuk,
  vannak-e nem lefoglalt, de felszabadított blokkok (ini hiba),
  vannak-e többször felszabadított blokkok (fre hiba),
  vannak-e többszörös memóriacímek (all hiba).

  Ezek a hibák kétféleképpen keletkeznek:
  1) Rossz a program, ezt keressük (remélhetőleg a CCC nem rossz).
  2) Valamely malloc/realloc/free mégsem megy át a wrapperen.
  
  Tapasztalat szerint olyan programokban, amik sok ideiglenes 
  szálat hoznak létre a malloc néha kikerüli a wrappert,
  miáltal ini típusú hiba keletkezik. Ha a program többszálú,
  de ugyanazok a szálak dolgoznak, akkor nincs ilyen hiba.
  Gyanúm szerint magában a pthread_create-ban hívott malloc
  vész el néha.
  
  A "man malloc_hook"-ban leírt technika sokkal rosszabb,
  egyáltalán nem szálbiztos, az esetek 1%-ban kikerüli
  a wrappert (hookot), és ini/fre/all hibákat vegyesen csinál.
  Nem is lehet kijavítani, el kell felejteni.
  
  A wrapper MAXBLK/2 memóriablokkot tud nyilvántartani,
  tehát óriás programok (mint savex) teszteléséhez nem túl jó.
  Akkor hasznos, ha nem nagy, de sokáig futó, sok objektumot
  létrehozó és felszabadító programban keresünk memóriaszivárgást,
#endif


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include <pthread.h>

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

static pthread_mutex_t mutex_hook=PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

#define MAXBLK 0x20001
#define ST_INIT   0
#define ST_ALLOC  1
#define ST_FREE   2

//----------------------------------------------------------------------------
struct BLKHASH
{
    int blkcnt;

    struct
    {
      void *ptr;
      int stat; //0 init, 1 lefoglal, 2 elenged
      int age;
      int size;
    } blklst[MAXBLK];

    int blkidx(void *p)
    {
        int hidx=((unsigned long)p)%MAXBLK;
        while(1)
        {
            if( blklst[hidx].ptr==0 )
            {
                if( blkcnt>MAXBLK/2 )
                {
                    hidx=-1;
                    break;
                }
                blklst[hidx].ptr=p;
                blklst[hidx].stat=ST_INIT;
                blkcnt++;
                break;
            }
            else if( blklst[hidx].ptr==p )
            {
                break;
            }
            else if( ++hidx>=MAXBLK )
            {
                hidx=0;
            }
        }
        return hidx;
    }

    BLKHASH()
    {
        blkcnt=0;
        for(int i=0; i<MAXBLK; i++)
        {
            blklst[i].ptr=0;
            blklst[i].stat=ST_INIT;
            blklst[i].age=0;
            blklst[i].size=0;
        }
    }

    BLKHASH(BLKHASH *h)
    {
        blkcnt=0;
        for(int i=0; i<MAXBLK; i++)
        {
            blklst[i].ptr=0;
            blklst[i].stat=ST_INIT;
            blklst[i].age=0;
            blklst[i].size=0;
        }

        for(int i=0; i<MAXBLK; i++)
        {
            if( h->blklst[i].ptr!=0 && h->blklst[i].stat==ST_ALLOC )
            {
                int x=this->blkidx(h->blklst[i].ptr);
                this->blklst[x].stat=ST_ALLOC;
                this->blklst[x].age=h->blklst[i].age+1;
                this->blklst[x].size=h->blklst[i].size;
            }
        }
    }
};

static BLKHASH *blkhash=0;
static int blkreb=0;
static long err0=0,err1=0,err2=0,err3=0;

//----------------------------------------------------------------------------
static int blkidx(void *p)
{
    int x=blkhash->blkidx(p);
    if( x<0 )
    {
        BLKHASH *h=new BLKHASH(blkhash);
        printf("\n%d BLKHASH rebuild %d -> %5d (ok=%ld ini=%ld fre=%ld all=%ld) %lxd", 
               ++blkreb,blkhash->blkcnt,h->blkcnt,
               err0,err1,err2,err3, 
               (unsigned long)pthread_self() );
        delete blkhash;
        blkhash=h;
    }
    x=blkhash->blkidx(p);
    if( x<0 )
    {
        /*
        BLKHASH *h=blkhash;

        for(int i=0; i<MAXBLK; i++)
        {
            if( h->blklst[i].ptr!=0 && h->blklst[i].stat==ST_ALLOC )
            {
                char *p=(char *)h->blklst[i].ptr;
                printf("%04d %d %s\n", h->blklst[i].age, h->blklst[i].size, p);
            }
        }
        */


        printf("\ntoo many memblk\n");
        exit(1);
    }
    return x;
}

//----------------------------------------------------------------------------
static void COUNT(void *p1, void *p2, int size)
{
    static int COUNT_DEPTH=0;
    if( COUNT_DEPTH>0 ) 
        return;
    COUNT_DEPTH++;

    if( blkhash==0 )
    {
        blkhash=new BLKHASH();
    }
    
    if( p1 ) //elenged
    {
        //printf("f:%lx\n",(unsigned long)p1);fflush(0);

        int x=blkidx(p1);
        if( blkhash->blklst[x].stat==ST_INIT )
        {
            err1++;
        }
        if( blkhash->blklst[x].stat==ST_FREE )
        {
            err2++;
        }
        else
        {
            err0++;
        }
        blkhash->blklst[x].stat=ST_FREE;
        blkhash->blklst[x].size=size;
    }

    if( p2 ) //lefoglal
    {
        //printf("a:%lx\n",(unsigned long)p2);fflush(0);

        int x=blkidx(p2);
        if( blkhash->blklst[x].stat==ST_ALLOC )
        {
            err3++;
        }
        else
        {
            err0++;
        }
        blkhash->blklst[x].stat=ST_ALLOC;
        blkhash->blklst[x].size=size;
    }

    COUNT_DEPTH--;
}

//----------------------------------------------------------------------------
typedef void *malloc_t(size_t size);
typedef void *realloc_t(void *ptr,size_t size);
typedef void free_t(void *ptr);

static void* ptr_malloc=0;
static void* ptr_realloc=0;
static void* ptr_free=0;

static void load_implementation()
{
    ptr_malloc=dlsym(RTLD_NEXT,"malloc");
    if( ptr_malloc==0 )
    {
        printf("malloc implementation not found\n");fflush(0);
        exit(1);
    }
    printf("dlsym: malloc\n");fflush(0);

    ptr_realloc=dlsym(RTLD_NEXT,"realloc");
    if( ptr_realloc==0 )
    {
        printf("realloc implementation not found\n");fflush(0);
        exit(1);
    }
    printf("dlsym: realloc\n");fflush(0);

    ptr_free=dlsym(RTLD_NEXT,"free");
    if( ptr_free==0 )
    {
        printf("free implementation not found\n");fflush(0);
        exit(1);
    }
    printf("dlsym: free\n");fflush(0);
}


static void *orig_malloc(size_t size)
{
    if( ptr_malloc==0 )
    {   
        load_implementation();
    }
    return ((malloc_t*)ptr_malloc)(size);
}

static void *orig_realloc(void *ptr,size_t size)
{
    if( ptr_realloc==0 )
    {
        load_implementation();
    }
    return ((realloc_t*)ptr_realloc)(ptr,size);
}

static void orig_free(void *ptr)
{
    if( ptr_free==0 )
    {
        load_implementation();
    }
    ((free_t*)ptr_free)(ptr);
}

//----------------------------------------------------------------------------
void *malloc(size_t size)
{
    sigset_t oldmask;
    pthread_sigmask(SIG_BLOCK,&sigmask,&oldmask);
    pthread_mutex_lock(&mutex_hook);
    
    void *result=orig_malloc(size); 
    COUNT(0,result,size);

    pthread_mutex_unlock(&mutex_hook);
    pthread_sigmask(SIG_SETMASK,&oldmask,0);
    //printf("malloc(%d) -> %lx\n",(int)size,(unsigned long)result);
    return result;
}
     
void free(void *ptr)
{
    sigset_t oldmask;
    pthread_sigmask(SIG_BLOCK,&sigmask,&oldmask);
    pthread_mutex_lock(&mutex_hook);

    COUNT(ptr,0,0);
    orig_free(ptr);  

    pthread_mutex_unlock(&mutex_hook);
    pthread_sigmask(SIG_SETMASK,&oldmask,0);
    //printf("free(%lx)\n",(unsigned long)ptr);
}

void *realloc(void *ptr, size_t size)
{
    sigset_t oldmask;
    pthread_sigmask(SIG_BLOCK,&sigmask,&oldmask);
    pthread_mutex_lock(&mutex_hook);

    void *result=orig_realloc(ptr,size); 
    COUNT(ptr,result,size);

    pthread_mutex_unlock(&mutex_hook);
    pthread_sigmask(SIG_SETMASK,&oldmask,0);
    //printf("malloc(%lx,%d) -> %lx\n",(unsigned long)ptr,(int)size,(unsigned long)result);
    return result;
}
 
//----------------------------------------------------------------------------

