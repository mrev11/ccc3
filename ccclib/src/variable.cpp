

#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <varsync.h>
#include <varlock.h>
#include <cccapi.h>

//---------------------------------------------------------------------------

#define USE_COLOR
#ifdef USE_COLOR
static const char *RESET="\e[0m";
static const char *BOLD="\e[1m";
static const char *BLACK="\e[30m";
static const char *RED="\e[31m";
static const char *GREEN="\e[32m";
static const char *YELLOW="\e[33m";
static const char *BLUE="\e[34m";
static const char *MAGENTA="\e[35m";
static const char *CYAN="\e[36m";
static const char *WHITE="\e[37m";
static const char *DEFAULT="\e[39m";
#else
static const char *RESET="";
static const char *BOLD="";
static const char *BLACK="";
static const char *RED="";
static const char *GREEN="";
static const char *YELLOW="";
static const char *BLUE="";
static const char *MAGENTA="";
static const char *CYAN="";
static const char *WHITE="";
static const char *DEFAULT="";
#endif


//---------------------------------------------------------------------------
// egyik vagy masik
 #define FINE_GRAINED_LOCK
// #define COARSE_GRAINED_LOCK

//---------------------------------------------------------------------------

static OREF *oref;          // oref tomb
static VREF *vref;          // vref tomb

static unsigned int onext;  // kovetkezo szabad index orefben
static unsigned int vnext;  // kovetkezo szabad index vrefben

static unsigned int olast;  // utolso szabad index orefben
static unsigned int vlast;  // utolso szabad index vrefben

static unsigned int ofree;  // szabad orefek szama
static unsigned int vfree;  // szabad vrefek szama

static unsigned int oresv;  // foglalt orefek a mark vegen
static unsigned int ormax;  // foglalt orefek maximuma

static char *env_gcdebug=getenv("CCC_GCDEBUG");
static char *env_marksync=getenv("CCC_MARKSYNC");
static char *env_orefsize=getenv("CCC_OREFSIZE");
static char *env_vrefsize=getenv("CCC_VREFSIZE");
static char *env_oreflevel=getenv("CCC_OREFLEVEL");
static char *env_vreflevel=getenv("CCC_VREFLEVEL");

static unsigned int  OREF_SIZE  = 200000;
static unsigned int  OREF_LEVEL = 0;

static unsigned int  VREF_SIZE  = 4000;
static unsigned int  VREF_LEVEL = 0;

static size_t tabsize = 0;

static unsigned int  ALLOC_COUNT = OREF_SIZE;
static unsigned long ALLOC_SIZE  = OREF_SIZE*256;

static unsigned int  alloc_count=0;  // foglalasok szama
static unsigned long alloc_size=0;   // foglalasok osszmerete

static unsigned int mark_phase=0;

static int *mark_stack=0;
static int *mark_stack_ptr=0;
static int mark_stack_depth=0;

static int  collector_tid=0;

static int gc_count=0;


//  COLOR_WHITE(x) <=> (x)<gc_count
//  COLOR_BLACK(x) <=> (x)=gc_count
//  COLOR_GRAY(x)  <=> (x)>gc_count


static void vartab_mark(void);
static void mark(void);
static void mark_lk(void);
static void vartab_sweep(void);
static void sweep();
static void vartab_shade(VALUE*);
static void vartab_shade_lk(VALUE*);
static void mark_push(OREF*o);
static OREF *mark_pop();

//debug
static char *decimal(long x);
static char *star(int);
static void sleep_milli(int ms);
static void sleep_micro(int micro);
static void valid_oref(OREF *o);
static void valid_value(VALUE *v);
static void inventory();

//---------------------------------------------------------------------------

static varsync sync_gc;                 // szemetgyujtes vezerlese
static varsync sync_gc_force;           // szemetgyujtes vezerlese
static varsync sync_oreftab;
static varsync sync_vreftab;
static varsync sync_stack;

static varsync sync_olast(&olast);
static varsync sync_vlast(&vlast);
static varsync sync_ofree(&ofree);
static varsync sync_vfree(&vfree);
static varsync sync_oresv(&oresv);

static varlock mutx_sweep(11);          // sweep vezerlese
static varlock mutx_mark(41);           // mark vezerlese
static varlock mutx_value(41);          // assign vezerlese

//---------------------------------------------------------------------------
static void mutex_state_init() // fork utan a childban elengedi a gc mutexeit
{
    sync_gc.init();
    sync_gc_force.init();
    sync_oreftab.init();
    sync_vreftab.init();
    sync_stack.init();

    sync_olast.init();
    sync_vlast.init();
    sync_ofree.init();
    sync_vfree.init();
    sync_oresv.init();

    mutx_mark.init();
    mutx_sweep.init();
    mutx_value.init();
}

//---------------------------------------------------------------------------
static void oreftab_lock()   {sync_oreftab.lock();} // mutator
static void vreftab_lock()   {sync_vreftab.lock();} // mutator
static void oreftab_unlock() {sync_oreftab.lock_free();} // mutator
static void vreftab_unlock() {sync_vreftab.lock_free();} // mutator


#ifdef FINE_GRAINED_LOCK
  int  assign_lock0(){ return mutx_value.lock(0); } // megfogja mutx[0]-t (specialis)
  void assign_unlock0(){ mutx_value.lock_free(0); } // elengedi mutx[0]-t (specialis)
  int  assign_lock(){ return mutx_value.lock(); } // minden VALUE mutexet megfog
  int  assign_lock(int x){ return mutx_value.lock(x); } // egy VALUE mutexet megfog
  int  assign_lock(VALUE*v){ return mutx_value.lock(v); } // egy VALUE mutexet megfog
  int  assign_lock(VALUE*v,int x){ return mutx_value.lock(v,x); } // egy plusz VALUE mutexet megfog
  int  assign_lock(VALUE*v1, VALUE*v2){ return mutx_value.lock(v1,v2); } // ket VALUE mutexet megfog
  void assign_unlock(){ mutx_value.lock_free();   } // minden VALUE mutexet elenged
  void assign_unlock(int x){ mutx_value.lock_free(x); } // egy vagy ket VALUE mutexet elenged
  void assign_deadlock(int id){ mutx_value.deadlock(id); }

  int  mark_lock(OREF *o){ return mutx_mark.lock(o); }
  int  mark_lock(VALUE *v){ return mutx_mark.lock(v->data.array.oref); }
  int  mark_lock(int x){ return mutx_mark.lock(x); }
  void mark_unlock(int x){ mutx_mark.lock_free(x); }
#endif

#ifdef COARSE_GRAINED_LOCK
  // simplified
  int  assign_lock0(){ return 0; }
  void assign_unlock0(){}
  int  assign_lock(){ return mutx_value.lock(0); }
  int  assign_lock(int x){ return mutx_value.lock(0); }
  int  assign_lock(VALUE*v){ return mutx_value.lock(0); }
  int  assign_lock(VALUE*v,int x){ return x; }
  int  assign_lock(VALUE*v1, VALUE*v2){ return mutx_value.lock(0); }
  void assign_unlock(){ mutx_value.lock_free(0);   }
  void assign_unlock(int x){ mutx_value.lock_free(0); }
  void assign_deadlock(int id){ mutx_value.deadlock(id); }

  int  mark_lock(OREF *o){ return mutx_mark.lock(0); }
  int  mark_lock(VALUE *v){ return mutx_mark.lock(0); }
  int  mark_lock(int x){ return mutx_mark.lock(0); }
  void mark_unlock(int x){ mutx_mark.lock_free(0); }
#endif


//---------------------------------------------------------------------------
void vartab_ini(void)
{
    if( env_orefsize )
    {
        long size=atol(env_orefsize);
        OREF_SIZE=size;
        VREF_SIZE=size/50;
        ALLOC_COUNT=size;
        ALLOC_SIZE=size*256;
    }
    if( env_vrefsize )
    {
        long size=atol(env_vrefsize);
        VREF_SIZE=size;
    }
    static struct VARTAB_SETSIZE vss={ &OREF_SIZE, &VREF_SIZE,
                                       &ALLOC_COUNT, &ALLOC_SIZE };
    vartab_setsize(&vss);
    VREF_SIZE=min(OREF_SIZE/2,VREF_SIZE);
    tabsize=sizeof(OREF)*OREF_SIZE+sizeof(VREF)*VREF_SIZE; // osszmeret

    if( env_oreflevel )
    {
        OREF_LEVEL=atol(env_oreflevel);
    }
    else if( env_orefsize && strchr(env_orefsize,'/') )
    {
        OREF_LEVEL=atol(strchr(env_orefsize,'/')+1);
    }
    else
    {
        OREF_LEVEL=OREF_SIZE/10;
    }
    OREF_LEVEL=min(OREF_LEVEL,OREF_SIZE);

    if( env_vreflevel )
    {
        VREF_LEVEL=atol(env_vreflevel);
    }
    else if( env_vrefsize && strchr(env_vrefsize,'/') )
    {
        VREF_LEVEL=atol(strchr(env_vrefsize,'/')+1);
    }
    else
    {
        VREF_LEVEL=VREF_SIZE/5;
    }
    VREF_LEVEL=min(VREF_LEVEL,VREF_SIZE);


    if( env_gcdebug )
    {
        printf("\n");
        printf("GC_OREFSIZE: %s/%s\n",decimal(OREF_SIZE),decimal(OREF_LEVEL));
        printf("GC_VREFSIZE: %s/%s\n",decimal(VREF_SIZE),decimal(VREF_LEVEL));

        if( tabsize>1024*1024*16 )
        {
            printf("GC_VARTAB: %sM\n",decimal((int)(tabsize/1024/1024)) );
            printf("GC_MALLOC: %sM\n", decimal((int)(ALLOC_SIZE/1024/1024)) );
        }
        else
        {
            printf("GC_VARTAB: %sK\n",decimal((int)(tabsize/1024)) );
            printf("GC_MALLOC: %sK\n", decimal((int)(ALLOC_SIZE/1024)) );
        }

        // printf("VALUE struct size: %d\n",(int)sizeof(VALUE));
        // printf("OREF struct size: %d\n",(int)sizeof(OREF));
        // printf("VREF struct size: %d\n",(int)sizeof(VREF));
        // printf("mutex struct size: %d\n",(int)sizeof(pthread_mutex_t));
        fflush(0);
    }

    oref=(OREF*)MEMALLOC(OREF_SIZE*sizeof(OREF));
    for(unsigned int n=0; n<OREF_SIZE; n++)
    {
        oref[n].ptr.valptr=NULL;
        oref[n].length=0;
        oref[n].link=n+1;
        oref[n].color=0; //=WHITE
    }
    onext=0;
    olast=OREF_SIZE-1;
    ofree=OREF_SIZE-1;

    vref=(VREF*)MEMALLOC(VREF_SIZE*sizeof(VREF));
    for(unsigned int n=0; n<VREF_SIZE; n++)
    {
        vref[n].value.type=TYPE_NIL;
        vref[n].link=n+1;
        vref[n].color=0; //=WHITE
    }
    vnext=0;
    vlast=VREF_SIZE-1;
    vfree=VREF_SIZE-1;

    ormax=0;
    oresv=0;

    mark_stack=(int*)MEMALLOC(OREF_SIZE*sizeof(int));
    mark_stack_ptr=mark_stack; // init

    pthread_t t=0;
    pthread_create(&t,0,vartab_collector,0);
    pthread_setname_np(t,"collector");
    pthread_detach(t);

#ifndef WINDOWS
    // windowson nincs fork
    pthread_atfork(0,0,mutex_state_init);
#endif
}


//---------------------------------------------------------------------------
void *vartab_collector(void *ptr)
{
    #ifdef _LINUX_ // mashol nincs gettid()
    collector_tid=gettid();
    if( env_gcdebug )
    {
        printf("GC_COLLECTOR: %d\n",collector_tid);
        fflush(0);
    }
    #endif

    sync_gc.lock();
    while(1)
    {
        if( sync_gc.wait(30000)==0 )
        {
            if( env_gcdebug )
            {
                printf(" sign");
            }
            vartab_mark();
            vartab_sweep();
        }
        else if( alloc_count>ALLOC_COUNT/10 || alloc_size>ALLOC_SIZE/10 )
        {
            if( env_gcdebug )
            {
                printf(" time");
            }
            vartab_mark();
            vartab_sweep();
        }

        sync_gc_force.lock();
        sync_gc_force.signal();
        sync_gc_force.lock_free();
    }
}

//---------------------------------------------------------------------------
static void vartab_mark(void)
{
    assign_lock(); // fontos a sorrend
    oreftab_lock();
    vreftab_lock();

    ++gc_count;

    if(env_gcdebug)
    {
        #ifdef FINE_GRAINED_LOCK
          printf(" fGC(%d)  %sMARK:%s ",gc_count,BOLD,RESET);
        #else
          printf(" cGC(%d)  %sMARK:%s ",gc_count,BOLD,RESET);
        #endif
        printf("%sofree=%s ", star(sync_ofree.read()<=OREF_LEVEL), decimal(sync_ofree.read()));
        printf("%svfree=%s ", star(sync_vfree.read()<=VREF_LEVEL), decimal(sync_vfree.read()));
        if( tabsize>1024*1024*8 )
        {
            printf("%smalloc=%sM ", star(alloc_size>ALLOC_SIZE), decimal(alloc_size/1024/1024));
        }
        else
        {
            printf("%smalloc=%sK ", star(alloc_size>ALLOC_SIZE), decimal(alloc_size/1024));
        }
        fflush(0);
    }

    mark_stack_ptr=mark_stack; // stack init
    mark_stack_depth=0;
    alloc_count=0;
    alloc_size=0;
    oresv=0;

    //-------------------------------------
    // stackrol kozvetlenul elerheto oref-ek -> GRAY
    //-------------------------------------

    for( VALUE *sp=ststackbuf; sp<ststack; sp++) // static stack
    {
        vartab_shade(sp); // static stack
    }

    int thrcnt=0;
    thread_data::lock();
    thread_data *td=thread_data::tdata_first;
    while( td!=0 )
    {
        ++thrcnt;
        for( VALUE *sp=td->_stackbuf; sp<td->_stack; sp++) // local stack
        {
            vartab_shade(sp); // local stack
        }
        td=td->next;
    }
    thread_data::unlock();


    //-------------------------------------
    // GRAY -> BLACK
    // BLACK-re allitott oref gyerekei -> GRAY
    // amig el nem tunik minden GRAY oref
    //-------------------------------------

    if( env_marksync && 0==strcmp(env_marksync,"enabled") )
    {
        // dolgozo szalak futasa engedelyezve
        // a szemetgyujtes mark fazisa kozben

        mark_phase=1;
        if( env_gcdebug ){ printf("%s%s#%s ",BOLD,YELLOW,RESET);fflush(0); }
        vreftab_unlock();
        oreftab_unlock();
        assign_unlock();

        mark_lk();

        assign_lock();
        oreftab_lock();
        vreftab_lock();
        mark_phase=0;
        if( env_gcdebug ){ printf(" %s%s#%s ",BOLD,YELLOW,RESET);fflush(0); }
    }

    mark();

    vreftab_unlock();
    oreftab_unlock();
    assign_unlock();

    if(env_gcdebug)
    {
        printf("thread=%d ",thrcnt);
        printf("depth=%s ",decimal(mark_stack_depth));
        printf("oresv=%s ",decimal(oresv));
        fflush(0);
    }
}

//---------------------------------------------------------------------------
static void mark()
{
    while( OREF *o=mark_pop() ) //pop
    {
        int lkx=mark_lock(o);
        o->color=gc_count; //=BLACK
        if( VALUE *v=o->ptr.valptr )
        {
            for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
            {
                vartab_shade(v); // mark
            }
        }
        mark_unlock(lkx);
        sync_oresv.inc();
        ormax=max(ormax,oresv);
    }
}


//---------------------------------------------------------------------------
static void mark_lk()
{
    while( OREF *o=mark_pop() ) //pop
    {
        int lkx=mark_lock(o);
        o->color=gc_count; //=BLACK
        if( VALUE *v=o->ptr.valptr )
        {
            #ifdef NOTDEFINED 
              int idx=0;
              v=o->ptr.valptr;
              for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
              {
                       if( v->type==TYPE_NIL     );
                  else if( v->type==TYPE_NUMBER  );
                  else if( v->type==TYPE_DATE    );
                  else if( v->type==TYPE_FLAG    );
                  else if( v->type==TYPE_POINTER );
                  else if( v->type==TYPE_BINARY  );
                  else if( v->type==TYPE_STRING  );
                  else if( v->type==TYPE_ARRAY   );
                  else if( v->type==TYPE_BLOCK   );
                  else if( v->type==TYPE_OBJECT  );
                  else if( v->type==TYPE_REF     );
                  else
                  {
                      printf("\n");
                      printf("INVALID TYPE=0x%02x idx=%d length=%d color=%d link=%d\n",
                                          v->type,idx,o->length,o->color,o->link);
                      fflush(0);
                      abort();
                  }
                  ++idx;
              }
            #endif

            v=o->ptr.valptr;
            for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
            {
                #ifdef FINE_GRAINED_LOCK
                  vartab_shade_lk(v);
                #else
                  vartab_shade(v);
                #endif
            }
        }
        mark_unlock(lkx);
        sync_oresv.inc();
        ormax=max(ormax,oresv);
    }
}

//---------------------------------------------------------------------------
static void vartab_shade(VALUE *v)
{
    if( v->type<TYPE_GARBAGE  )
    {
        // NIL
        // NUMBER
        // DATE
        // FLAG
        // POINTER
        // nincs oref
    }
    else if( v->type<=TYPE_SCALAR  )
    {
        // BINARY
        // STRING
        if( OREF *o=v->data.array.oref )
        {
            if( o->color!=gc_count ) //!=BLACK
            {
                o->color=gc_count; //=BLACK
                ++oresv;
                ormax=max(ormax,oresv);
            }
        }
    }
    else if( v->type<TYPE_REF )
    {
        // ARRAY  mindig van oref-je (len==0 eseten lehet ptr==NULL)
        // OBJECT megegyezik az array esetevel
        // BLOCK  lehet, hogy nincs oref-je, de ha van, akkor ptr!=NULL
        // a prototype objectekben nincs oref!

        OREF *o=v->data.array.oref;
        if( (o!=NULL) && (o->color<gc_count) ) //==WHITE
        {
            o->color=gc_count+1; //=GRAY
            mark_push(o);
        }
    }
    else if( v->type==TYPE_REF )
    {
        // REF
        VREF *r=v->data.vref;
        vartab_shade( &(r->value) ); // vartab_shade (rekurziv)
        r->color=gc_count; //=BLACK
    }
    else
    {
        printf("\nERROR: invalid VALUE type 0x%02x\n", v->type );
        fflush(0);
        abort();
    }
}

//---------------------------------------------------------------------------
static void vartab_shade_lk(VALUE *v)
{
    assign_lock0();
    int lkx=assign_lock(v);
    if( v->type!=TYPE_REF )
    {
        assign_unlock0();
    }

    if( v->type<TYPE_GARBAGE )
    {
        assign_unlock(lkx);
    }
    else if( v->type<=TYPE_SCALAR  )
    {
        if( OREF *o=v->data.array.oref )
        {
            if( o->color!=gc_count ) //!=BLACK
            {
                o->color=gc_count; //=BLACK
                ++oresv;
                ormax=max(ormax,oresv);
            }
        }
        assign_unlock(lkx);
    }
    else if( v->type<TYPE_REF  )
    {
        OREF *o=v->data.array.oref;
        if( (o!=NULL) && (o->color<gc_count) ) //==WHITE
        {
            o->color=gc_count+1; //=GRAY
            mark_push(o);
        }
        assign_unlock(lkx);
    }
    else if( v->type==TYPE_REF  )
    {
        VREF *r=v->data.vref;
        r->color=gc_count; //=BLACK
        lkx=assign_lock(&r->value,lkx);
        vartab_shade(&r->value); // vartab_shade_lk
        assign_unlock(lkx);
        assign_unlock0();
    }
    else
    {
        printf("\nERROR: invalid VALUE type 0x%02x\n", v->type );
        fflush(0);
        abort();
    }
}

//---------------------------------------------------------------------------
void oref_gray(OREF *o) // mutator
{
    if( mark_phase && o->color<=gc_count  ) //!=GRAY
    {
        o->color=gc_count+1; //=GRAY
        mark_push(o);
    }
}

//---------------------------------------------------------------------------
static void mark_push(OREF*o)
{
    sync_stack.lock();
    *mark_stack_ptr++=(o-oref); //indexet tarol
    int depth=mark_stack_ptr-mark_stack;
    if( depth>mark_stack_depth)
    {
        mark_stack_depth=depth;
    }
    sync_stack.lock_free();
}

//---------------------------------------------------------------------------
static OREF *mark_pop()
{
    OREF *ox=0;
    sync_stack.lock();
    if( mark_stack_ptr>mark_stack )
    {
        ox=oref+(*--mark_stack_ptr);
    }
    sync_stack.lock_free();
    return ox;
}

//---------------------------------------------------------------------------
static void vartab_sweep()
{
    if( env_gcdebug )
    {
        printf(" %sSWEEP:%s ",BOLD,RESET);
        fflush(0);
    }

    sweep();

    if( env_gcdebug )
    {
        printf("ofree=%s vfree=%s  %sMAX:%s %s",
            decimal(sync_ofree.read()),
            decimal(sync_vfree.read()),
            BOLD,RESET,
            decimal(ormax));

        printf("\n");
        fflush(0);
    }
}

//---------------------------------------------------------------------------
static void sweep()
{
    int oinc=0;
    int vinc=0;

    for( unsigned int n=0; n<OREF_SIZE; n++ )
    {
        // kozos ciklus oref-re es vref-re
        // hamar legyen szabad oref is ES vref is

        if( n<VREF_SIZE )
        {
            // n: 0 -> VREF_SIZE-1
            int lkx=mutx_sweep.lock(&vref[n]);
            if( vref[n].link!=-1 )
            {
                // benne van a szabad listaban
            }
            else if( n==vlast )
            {
                // kihagy
            }
            else
            {
                if( vref[n].color<gc_count ) //==WHITE
                {
                    vref[n].value.type=TYPE_NIL;
                    vref[vlast].link=n;
                    sync_vlast.write(n);
                    sync_vfree.inc();
                    sync_vreftab.signal();
                    vinc++;
                }
            }
            mutx_sweep.lock_free(lkx);
        }

        // n: 0 -> OREF_SIZE-1
        int lkx=mutx_sweep.lock(&oref[n]);
        if( oref[n].link!=-1 )
        {
            // benne van a szabad listaban
        }
        else if( n==olast )
        {
            // kihagy
        }
        else
        {
            if( oref[n].color<gc_count ) //==WHITE
            {
                if( oref[n].length )
                {
                    MEMFREE(oref[n].ptr.valptr);
                }
                oref[n].ptr.valptr=NULL;
                oref[n].length=0;
                oref[olast].link=n;
                sync_olast.write(n);
                sync_ofree.inc();
                sync_oreftab.signal();
                oinc++;
            }
        }
        mutx_sweep.lock_free(lkx);
    }

    sync_oreftab.signal();
    sync_vreftab.signal();


    if( sync_ofree.read()==0  && oinc==0 )
    {
        printf("\nOREF overflow!\n");
        fflush(0);
        abort();
        exit(1);
    }

    if( sync_vfree.read()==0 && vinc==0 )
    {
        printf("\nVREF overflow!\n");
        fflush(0);
        abort();
        exit(1);
    }
}


//---------------------------------------------------------------------------
// az alabbiakat csak a mutatorok hivjak
//---------------------------------------------------------------------------
OREF *oref_new(VALUE *v, void* ptr, int length)
{
    // kizarolag a mutator hivja
    // max egy mutator thread van itt

    oreftab_lock();

    int counter=0;
    while( onext==sync_olast.read() )
    {
        if( env_gcdebug && ++counter==1  )
        {
            counter=0;
            printf("%s%s$%s",YELLOW,BOLD,RESET);fflush(0);
        }
        if( 0==sync_gc.lock_try() )
        {
            if( env_gcdebug )
            {
                printf("%s%s!%s",RED,BOLD,RESET);fflush(0);
            }
            sync_gc.signal();
            sync_gc.lock_free();
        }
        sync_oreftab.wait(100);
    }

    OREF *o=oref+onext;
    int lkx=mutx_sweep.lock(o);
      o->color=gc_count; //=BLACK
      onext=o->link;
      o->link=-1;
      o->ptr.valptr=(VALUE*)ptr;
      o->length=length;
    mutx_sweep.lock_free(lkx);
    v->data.array.oref=o;
    stack->type=(v)->type; // push (megj: v a local stacken van)
    stack->data=(v)->data;
    stack++;

    sync_ofree.dec();
    oreftab_unlock();

    if( sync_ofree.read()<OREF_LEVEL && 0==sync_gc.lock_try() )
    {
        sync_gc.signal();
        sync_gc.lock_free();
    }

    return o;
}


//---------------------------------------------------------------------------
VREF *vref_new()  // TOP-ot refesiti
{
    // kizarolag a mutator hivja
    // max egy mutator thread van itt

    vreftab_lock();
    int counter=0;
    while( vnext==sync_vlast.read() )
    {
        if( env_gcdebug &&  ++counter==1  )
        {
            counter=0;
            printf("%s%s@%s",YELLOW,BOLD,RESET);fflush(0);
        }
        if( 0==sync_gc.lock_try() )
        {
            if( env_gcdebug )
            {
                printf("%s%s!%s",RED,BOLD,RESET);fflush(0);
            }
            sync_gc.signal();
            sync_gc.lock_free();
        }
        sync_vreftab.wait(100);
    }

    VREF *vr=vref+vnext;
    unsigned lkx=mutx_sweep.lock(vr);
      vr->color=gc_count; //=BLACK
      vnext=vr->link;
      vr->link=-1;
    mutx_sweep.lock_free(lkx);
    vreftab_unlock();

    vr->value=*TOP();
    TOP()->type=TYPE_REF;
    TOP()->data.vref=vr;
    sync_vfree.dec();

    if( sync_vfree.read()<VREF_LEVEL && 0==sync_gc.lock_try() )
    {
        sync_gc.signal();
        sync_gc.lock_free();
    }

    return vr;
}

//---------------------------------------------------------------------------
VALUE *newValue(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(VALUE)*len;
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==sync_gc.lock_try() )
    {
        sync_gc.signal();
        sync_gc.lock_free();
    }
    VALUE *p=(VALUE*)MEMALLOC( len*sizeof(VALUE) );
    memset((void*)p,0,len*sizeof(VALUE));
    return p;
}

//-------------------------------------------------------------------------
CHAR *newChar(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(CHAR)*len;
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==sync_gc.lock_try() )
    {
        sync_gc.signal();
        sync_gc.lock_free();
    }
    CHAR *p=(CHAR*)MEMALLOC(len*sizeof(CHAR));
    return p;
}

//-------------------------------------------------------------------------
BYTE *newBinary(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(BYTE)*len;
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==sync_gc.lock_try() )
    {
        sync_gc.signal();
        sync_gc.lock_free();
    }
    BYTE *p=(BYTE*)MEMALLOC(len*sizeof(BYTE));
    return p;
}

//---------------------------------------------------------------------------
void deleteValue(VALUE *v)
{
    MEMFREE(v);
}

//---------------------------------------------------------------------------
VALUE &VALUE::operator=(VALUE &v)
{
    int lkx=assign_lock(this,&v);
    type=v.type;
    data=v.data;
    if( mark_phase && this->type>TYPE_GARBAGE )
    {
        vartab_shade(this); // operator=
    }
    assign_unlock(lkx);
    return *this;
}

//---------------------------------------------------------------------------
void valuecopy(VALUE *to, VALUE *fr)
{
    memmove( (void*)to, (void*)fr, sizeof(VALUE) );
    if( mark_phase && to->type>TYPE_GARBAGE )
    {
        vartab_shade(to); // valuecopy
    }
}

void arraycopy(VALUE *to, VALUE *fr, int n)
{
    memmove( (void*)to, (void*)fr, n*sizeof(VALUE) );
}

//---------------------------------------------------------------------------
void __gc(int flag)
{
    if( flag )
    {
        // FORCED
        // megvarja, hogy az (esetleges) aktualis gc befejezodjon
        // elindit egy uj gc-t, es megvarja, hogy az is befejezodjon

        int count=gc_count;
        sync_gc.lock();
        sync_gc.signal();
        sync_gc.lock_free();
        sync_gc_force.lock();
        while( count==gc_count )
        {
            sync_gc_force.wait();
        }
        sync_gc_force.lock_free();
    }
    else
    {
        // UNFORCED
        // ha eppen nem fut, akkor elinditja a gc-t

        if( 0==sync_gc.lock_try() )
        {
            sync_gc.signal();
            sync_gc.lock_free();
        }
    }
}


//---------------------------------------------------------------------------
void _clp_gc(int argno)
{
    CCC_PROLOG("gc",1);
    int flag=ISNIL(1)?0:_parl(1);
    __gc(flag);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
// debug utils
//---------------------------------------------------------------------------
static char *decimal(long x) // nagy szamok olvashato kiirasahoz
{
    static char store[1024];
    static int storeidx=0;
    if( storeidx>1024-64 )
    {
        storeidx=0;
    }
    int storebeg=storeidx;

    int sign=0;
    if( x<0 )
    {
        sign=1;
        x=-x;
    }

    char buf[64];
    int i=0;
    if( x==0 )
    {
        buf[i++]='0';
    }
    while( x!=0 )
    {
        buf[i++]='0'+x%10;
        x/=10;

        // 987,654,321
        //    ^   ^   ^
        // 0  3   7  (11)

        if( x && (i-3)%4==0 )
        {
            buf[i++]=',';
        }
    }
    if( sign )
    {
        store[storeidx++]='-';
    }
    while( i>0 )
    {
        store[storeidx++]=buf[--i];
    }
    store[storeidx++]=0;
    return store+storebeg;
}

//---------------------------------------------------------------------------
static char *star(int flag)
{
    static char buf[32];
    sprintf(buf,"%s%s%s%s",RED,BOLD,(flag?"*":""),RESET);
    return buf;
}

//---------------------------------------------------------------------------
static void sleep_milli(int ms)
{
    struct timeval t;
    t.tv_sec=ms/1000;
    t.tv_usec=(ms%1000)*1000;
    select(0,NULL,NULL,NULL,&t);
}

static void sleep_micro(int micro)
{
    struct timeval t;
    t.tv_sec=micro/1000000;
    t.tv_usec=(micro%1000000);
    select(0,NULL,NULL,NULL,&t);
}

//---------------------------------------------------------------------------

