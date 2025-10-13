

#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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

static int *mark_stack=0;
static int *mark_stack_ptr=0;


void vartab_ini(void);
void *vartab_collector(void*);
static void vartab_mark(void);
static void mark(void);
static void vartab_sweep(void);
static void sweep();
static void vartab_shade(VALUE*);
static void mark_push(OREF*o);
static OREF *mark_pop();

//debug
static char *decimal(long x);
static void sleep_milli(int ms);
static void sleep_micro(int micro);
static void valid_oref(OREF *o);
static void valid_value(VALUE *v);
static void inventory();

//---------------------------------------------------------------------------

static pthread_mutex_t          mutex_gc=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t           cond_gc=PTHREAD_COND_INITIALIZER;

static void gc_lock()           {pthread_mutex_lock(&mutex_gc);}
static void gc_unlock()         {pthread_mutex_unlock(&mutex_gc);}
static void gc_wait()           {pthread_cond_wait(&cond_gc,&mutex_gc);}
static void gc_signal()         {pthread_cond_signal(&cond_gc);}
static int  gc_trylock()        {return pthread_mutex_trylock(&mutex_gc);}

static int  gc_timedwait(int millis)
{
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
    return pthread_cond_timedwait(&cond_gc,&mutex_gc,&timeout);
}

//---------------------------------------------------------------------------

static pthread_mutex_t          mutex_vartab=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t           cond_vartab=PTHREAD_COND_INITIALIZER;

void vartab_lock()              {pthread_mutex_lock(&mutex_vartab);} // mutator
void vartab_unlock()            {pthread_mutex_unlock(&mutex_vartab);} // mutator
static void vartab_wait()       {pthread_cond_wait(&cond_vartab,&mutex_vartab);}
static void vartab_signal()     {pthread_cond_signal(&cond_vartab);}

static int  vartab_timedwait(int millis)
{
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
    return pthread_cond_timedwait(&cond_vartab,&mutex_vartab,&timeout);
}

//---------------------------------------------------------------------------

static pthread_mutex_t          mutex_assign=PTHREAD_MUTEX_INITIALIZER;
static void assign_lock()       {pthread_mutex_lock(&mutex_assign);}
static void assign_unlock()     {pthread_mutex_unlock(&mutex_assign);}

static pthread_mutex_t          mutex_sweep=PTHREAD_MUTEX_INITIALIZER;
static void sweep_lock()        {pthread_mutex_lock(&mutex_sweep);}
static void sweep_unlock()      {pthread_mutex_unlock(&mutex_sweep);}

//---------------------------------------------------------------------------

static pthread_mutex_t  mutex_olast=PTHREAD_MUTEX_INITIALIZER;
static unsigned olast_read(){pthread_mutex_lock(&mutex_olast); unsigned x=olast; pthread_mutex_unlock(&mutex_olast); return x;}
static void olast_write(unsigned x){pthread_mutex_lock(&mutex_olast); olast=x; pthread_mutex_unlock(&mutex_olast);}

static pthread_mutex_t  mutex_vlast=PTHREAD_MUTEX_INITIALIZER;
static unsigned vlast_read(){pthread_mutex_lock(&mutex_vlast); unsigned x=vlast; pthread_mutex_unlock(&mutex_vlast); return x;}
static void vlast_write(unsigned x){pthread_mutex_lock(&mutex_vlast); vlast=x; pthread_mutex_unlock(&mutex_vlast);}


static pthread_mutex_t  mutex_ofree=PTHREAD_MUTEX_INITIALIZER;
static void ofree_inc(){pthread_mutex_lock(&mutex_ofree); ++ofree; pthread_mutex_unlock(&mutex_ofree);}
static void ofree_dec(){pthread_mutex_lock(&mutex_ofree); --ofree; pthread_mutex_unlock(&mutex_ofree);}
static unsigned ofree_read(){pthread_mutex_lock(&mutex_ofree); unsigned x=ofree; pthread_mutex_unlock(&mutex_ofree); return x;}

static pthread_mutex_t  mutex_vfree=PTHREAD_MUTEX_INITIALIZER;
static void vfree_inc(){pthread_mutex_lock(&mutex_vfree); ++vfree; pthread_mutex_unlock(&mutex_vfree);}
static void vfree_dec(){pthread_mutex_lock(&mutex_vfree); --vfree; pthread_mutex_unlock(&mutex_vfree);}
static unsigned vfree_read(){pthread_mutex_lock(&mutex_vfree); unsigned x=vfree; pthread_mutex_unlock(&mutex_vfree); return x;}


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
    OREF_LEVEL=min(OREF_LEVEL,OREF_SIZE/2);
    
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
    VREF_LEVEL=min(VREF_LEVEL,VREF_SIZE/2);


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
        oref[n].color=COLOR_WHITE;
    }
    onext=0;
    olast=OREF_SIZE-1;
    ofree=OREF_SIZE-1;

    vref=(VREF*)MEMALLOC(VREF_SIZE*sizeof(VREF));
    for(unsigned int n=0; n<VREF_SIZE; n++)
    {
        vref[n].value.type=TYPE_NIL;
        vref[n].link=n+1;
        vref[n].color=COLOR_WHITE;
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
}


//---------------------------------------------------------------------------
void *vartab_collector(void *ptr)
{
    gc_lock();
    while(1)
    {
        if( gc_timedwait(20000)==0 )
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
    }
}

//---------------------------------------------------------------------------
static void vartab_mark(void)
{
    if(env_gcdebug)
    {
        static int count=0;
        printf(" ^GC(%d)  %sMARK:%s ",++count,BOLD,RESET);
        printf("%sofree=%s ", (ofree_read()<=OREF_LEVEL?"*":"")     , decimal(ofree_read()));
        printf("%svfree=%s ", (vfree_read()<=VREF_LEVEL?"*":"")     , decimal(vfree_read()));
        if( tabsize>1024*1024*8 )
        {
            printf("%smalloc=%sM ", (alloc_size>ALLOC_SIZE?"*":"") , decimal(alloc_size/1024/1024));
        }
        else
        {
            printf("%smalloc=%sK ", (alloc_size>ALLOC_SIZE?"*":"") , decimal(alloc_size/1024));
        }
        fflush(0);
    }

    vartab_lock();
    assign_lock();

    alloc_count=0;
    alloc_size=0;
    oresv=0;
    mark_stack_ptr=mark_stack; // stack init

    //-------------------------------------
    // minden BLACK oref -> WHITE
    //-------------------------------------

    for( unsigned int n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].color==COLOR_BLACK )
        {
            oref[n].color=COLOR_WHITE;
        }
        else
        {
            assert( oref[n].color==COLOR_WHITE );
        }
    }

    for( unsigned int n=0; n<VREF_SIZE; n++ )
    {
        if( vref[n].color==COLOR_BLACK )
        {
            vref[n].color=COLOR_WHITE;
        }
        else
        {
            assert( vref[n].color==COLOR_WHITE );
        }
    }

    //-------------------------------------
    // stackrol kozvetlenul elerheto oref-ek -> GRAY
    //-------------------------------------

    for( VALUE *sp=ststackbuf; sp<ststack; sp++)
    {
        vartab_shade(sp);
    }

    int thrcnt=0;
    thread_data::lock();
    thread_data *td=thread_data::tdata_first;
    while( td!=0 )
    {
        ++thrcnt;
        for( VALUE *sp=td->_stackbuf; sp<td->_stack; sp++)
        {
            vartab_shade(sp);
        }
        td=td->next;
    }
    thread_data::unlock();


    //-------------------------------------
    // GRAY -> BLACK
    // BLACK-re allitott oref gyerekei -> GRAY
    // amig el nem tunik minden GRAY oref
    //-------------------------------------

    mark();

    assign_unlock();
    vartab_unlock();

    if(env_gcdebug)
    {
        printf("thread=%d ",thrcnt);
        printf("oresv=%s ",decimal(oresv));
        fflush(0);
    }
}


//---------------------------------------------------------------------------
static void mark()
{
    OREF *o;
    while( 0!=(o=mark_pop()) ) //pop
    {
        if( VALUE *v=o->ptr.valptr )
        {
            for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
            {
                vartab_shade(v); //push
            }
        }

        // ez biztosan GRAY
        o->color=COLOR_BLACK;
        ++oresv;
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
    else if( v->type>=TYPE_REF )
    {
        // REF
        VREF *r=v->data.vref;
        r->color=COLOR_BLACK;
        vartab_shade( &(r->value) );
    }
    else if( v->type<=TYPE_SCALAR  )
    {
        // BINARY
        // STRING
        if( OREF *o=v->data.array.oref )
        {
            if( o->color!=COLOR_BLACK )
            {
                o->color=COLOR_BLACK;
                ++oresv;
                ormax=max(ormax,oresv);
            }
        }
    }
    else
    {
        // ARRAY  mindig van oref-je (len==0 eseten lehet ptr==NULL)
        // OBJECT megegyezik az array esetevel
        // BLOCK  lehet, hogy nincs oref-je, de ha van, akkor ptr!=NULL
        // a prototype objectekben nincs oref!

        OREF *o=v->data.array.oref;
        if( o!=NULL && o->color==COLOR_WHITE )
        {
            o->color=COLOR_GRAY;
            mark_push(v->data.array.oref);
        }
    }
}

//---------------------------------------------------------------------------
static void mark_push(OREF*o)
{
    *mark_stack_ptr++=(o-oref); //indexet tarol
}

//---------------------------------------------------------------------------
static OREF *mark_pop()
{
    if( mark_stack_ptr>mark_stack )
    {
        int idx=(*--mark_stack_ptr);
        return oref+idx;
    }
    return 0;
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
            decimal(ofree_read()),
            decimal(vfree_read()),
            BOLD,RESET, 
            decimal(ormax));

        printf("\n");
        fflush(0);
    }
}

//---------------------------------------------------------------------------
static void sweep()
{
    for( unsigned int n=0; n<OREF_SIZE; n++ )
    {
        if( n<VREF_SIZE )
        {
            // n: 0 -> VREF_SIZE-1
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
                sweep_lock();
                if( vref[n].color==COLOR_WHITE )
                {
                    vref[n].value.type=TYPE_NIL;
                    vref[vlast].link=n;
                    vlast_write(n);
                    vfree_inc();
                }
                sweep_unlock();
                vartab_signal();
            }
        }

        // n: 0 -> OREF_SIZE-1
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
            sweep_lock();
            if( oref[n].color==COLOR_WHITE )
            {
                if( oref[n].length )
                {
                    MEMFREE(oref[n].ptr.valptr);
                }
                oref[n].ptr.valptr=NULL;
                oref[n].length=0;
                oref[olast].link=n;
                olast_write(n);
                ofree_inc();
            }
            sweep_unlock();
            vartab_signal();
        }
    }

    vartab_signal();


    if( ofree_read()<=32 )
    {
        fprintf(stderr,"\nOREF overflow!\n");
        fflush(0);
        exit(1);
    }

    if( vfree_read()<=32 )
    {
        fprintf(stderr,"\nVREF overflow!\n");
        fflush(0);
        exit(1);
    }
}


//---------------------------------------------------------------------------
// az alabbiakat csak a mutatorok hivjak
//---------------------------------------------------------------------------
OREF *oref_new(void)
{
    // kizarolag a mutator hivja
    // VARTAB_LOCK vedelem alatt
    // max egy mutator thread van itt

    while( onext==olast_read() )
    {
        if( env_gcdebug )
        {
            printf("%s%s$%s",YELLOW,BOLD,RESET);fflush(0);
        }
        if( 0==gc_trylock() )
        {
            if( env_gcdebug )
            {
                printf("%s%s!%s",RED,BOLD,RESET);fflush(0);
            }
            gc_signal();
            gc_unlock();
        }
        vartab_timedwait(100);
    }
    sweep_lock();
    OREF *o=oref+onext;
    o->color=COLOR_LOCKED;
    onext=o->link;
    o->link=-1;
    ofree_dec();
    sweep_unlock();

    if( ofree_read()<OREF_LEVEL && 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
    }

    return o;
}

//---------------------------------------------------------------------------
VREF *vref_new(void)
{
    // kizarolag a mutator hivja
    // VARTAB_LOCK vedelem alatt
    // max egy mutator thread van itt

    while( vnext==vlast_read() )
    {
        if( env_gcdebug )
        {
            printf("%s%s@%s",YELLOW,BOLD,RESET);fflush(0);
        }
        if( 0==gc_trylock() )
        {
            if( env_gcdebug )
            {
                printf("%s%s!%s",RED,BOLD,RESET);fflush(0);
            }
            gc_signal();
            gc_unlock();
        }
        vartab_timedwait(100);
    }
    sweep_lock();
    VREF *v=vref+vnext;
    v->color=COLOR_LOCKED;
    vnext=v->link;
    v->link=-1;
    vfree_dec();
    sweep_unlock();

    if( vfree_read()<VREF_LEVEL && 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
    }

    return v;
}

//---------------------------------------------------------------------------
VALUE *newValue(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(VALUE)*len;
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
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
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
    }
    CHAR *p=(CHAR*)MEMALLOC(len*sizeof(CHAR));
    return p;
}

//-------------------------------------------------------------------------
BYTE *newBinary(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(BYTE)*len;
    if( (alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE) && 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
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
VALUE VALUE::operator=(VALUE v)
{
    assign_lock();
    type=v.type;
    data=v.data;
    assign_unlock();
    return *this;
}

//---------------------------------------------------------------------------
void valuemove(VALUE *to, VALUE *fr, int n)
{
    if( to<fr )
    {
        for( int i=0; i<n; i++ )
        {
            to[i]=fr[i];
        }
    }
    else
    {
        while( --n>=0 )
        {
            to[n]=fr[n];
        }
    }
}


//---------------------------------------------------------------------------
void _clp_gc(int argno)
{
    vartab_lock();
    if( 0==gc_trylock() )
    {
        gc_signal();
        gc_unlock();
    }
    vartab_unlock();
    stack-=argno;
    PUSHNIL();
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
static void valid_oref(OREF *o) // hibas adatok felderitesehez
{
    unsigned x=((unsigned)(o-oref))/sizeof(OREF);
    if( x>=OREF_SIZE )
    {
        printf("\ninvalid oref 0x%2x\n",x);
        fflush(0);
        raise(SIGABRT);
    }
}

static void valid_value(VALUE *v) // hibas adatok felderitesehez
{
         if( v->type==TYPE_END     );
    else if( v->type==TYPE_NIL     );
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
        printf("\ninvalid type 0x%2x\n",v->type);
        fflush(0);
        raise(SIGABRT);
    }

    if( v->type<TYPE_GARBAGE )
    {
        // nincs memoria objektuma
    }
    else if( v->type==TYPE_REF )
    {
        // itt nem vizsgaljuk
    }
    else if( OREF *o=v->data.binary.oref )
    {
        //BINARY
        //STRING
        //ARRAY
        //BLOCK
        //OBJECT

        valid_oref(o);
    }
    else
    {
        // a prototype objectekben nincs oref
        // ezert nem vizsgalhato az oref letezese
        // egyebkent normalisan csak a BLOCK-okban
        // lehetne oref==NULL
    }
}

//---------------------------------------------------------------------------
static void inventory()
{
    int white = 0;
    int gray  = 0;
    int black = 0;
    int locked= 0;

    for ( unsigned int n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].color==COLOR_WHITE )
        {
            white++;
        }
        else if( oref[n].color==COLOR_GRAY )
        {
            gray++;
        }
        else if( oref[n].color==COLOR_BLACK )
        {
            black++;
        }
        else if( oref[n].color==COLOR_LOCKED )
        {
            locked++;
        }
    }
    printf("inventory: white=%s black=%s locked=%d (%d) ",
                       decimal(white),decimal(black),locked, white+gray+black+locked);
    fflush(0);

}

//---------------------------------------------------------------------------



