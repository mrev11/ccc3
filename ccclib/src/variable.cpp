

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

static OREF *oref;          // oref tomb
static VREF *vref;          // vref tomb

static unsigned int onext;  // a kovetkezo szabad index orefben
static unsigned int vnext;  // a kovetkezo szabad index vrefben

static unsigned int ofree;  // szabad orefek szama
static unsigned int vfree;  // szabad vrefek szama

static char *env_gcdebug=getenv("CCC_GCDEBUG");

static char *env_orefsize=getenv("CCC_OREFSIZE");
static char *env_vrefsize=getenv("CCC_VREFSIZE");
static char *env_oreflevel=getenv("CCC_OREFLEVEL");
static char *env_vreflevel=getenv("CCC_VREFLEVEL");

static int  OREF_SIZE   = 200000;
static int  VREF_SIZE   = 5000;

static int  OREF_LEVEL  = 0;
static int  VREF_LEVEL  = 0;

static int  ALLOC_COUNT = OREF_SIZE;
static unsigned long ALLOC_SIZE = OREF_SIZE*128;

static int alloc_count=0;   // foglalasok szama
static unsigned long alloc_size=0;   // foglalasok osszmerete

static int *mark_stack=0;
static int *mark_stack_ptr=0;


void vartab_ini(void);
static void *collector(void*);
static void vartab_mark(void);
static void vartab_sweep(void);
static void oref_sweep();
static void vref_sweep();
static void vartab_shade(VALUE*);
static void mark_push(OREF*o);
static OREF *mark_pop();

//debug
static char *decimal(long x);
static void sleep(int ms);
static void sleepmicro(int micro);
static void valid_oref(OREF *o);
static void valid_value(VALUE *v);

//#define DEBUG_VALID // ellenorzi a VALUE-kat

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
    timeout.tv_sec=now.tv_sec+millis/1000;
    timeout.tv_nsec=now.tv_usec*1000;
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
    timeout.tv_sec=now.tv_sec+millis/1000;
    timeout.tv_nsec=now.tv_usec*1000;
    return pthread_cond_timedwait(&cond_vartab,&mutex_vartab,&timeout);
}

//---------------------------------------------------------------------------

static pthread_mutex_t          mutex_assign=PTHREAD_MUTEX_INITIALIZER;

static void assign_lock()       {pthread_mutex_lock(&mutex_assign);}
static void assign_unlock()     {pthread_mutex_unlock(&mutex_assign);}


//---------------------------------------------------------------------------
void vartab_ini(void)
{
    if( env_orefsize )
    {
        long size=atol(env_orefsize);
        OREF_SIZE=size;
        ALLOC_COUNT=size;
        ALLOC_SIZE=size*200;
    }
    if( env_vrefsize )
    {
        long size=atol(env_vrefsize);
        VREF_SIZE=size;
    }
    if( env_oreflevel )
    {
        long level=atol(env_oreflevel);
        OREF_LEVEL=level;
    }
    if( env_vreflevel )
    {
        long level=atol(env_vreflevel);
        VREF_LEVEL=level;
    }

    static struct VARTAB_SETSIZE vss={ &OREF_SIZE, &VREF_SIZE,
                                       &ALLOC_COUNT, &ALLOC_SIZE };
    vartab_setsize(&vss);

    if( env_gcdebug )
    {
        printf("\n");
        printf("OREF_SIZE: %s/%s\n",decimal(OREF_SIZE),decimal(OREF_LEVEL));
        printf("VREF_SIZE: %s/%s\n",decimal(VREF_SIZE),decimal(VREF_LEVEL));
        printf("VARTAB: %sM\n",decimal((int)(sizeof(OREF)*OREF_SIZE+sizeof(VREF)*VREF_SIZE)/(1024*1024))  );
        printf("ALLOC: %sM\n",decimal( (int)(ALLOC_SIZE/1024/1024) ) );
        printf("VALUE struct size: %d\n",(int)sizeof(VALUE));
        printf("OREF struct size: %d\n",(int)sizeof(OREF));
        printf("VREF struct size: %d\n",(int)sizeof(VREF));
        printf("mutex struct size: %d\n",(int)sizeof(pthread_mutex_t));
        fflush(0);
    }

    oref=(OREF*)MEMALLOC(OREF_SIZE*sizeof(OREF));
    for(int n=0; n<OREF_SIZE; n++)
    {
        oref[n].ptr.valptr=NULL;
        oref[n].length=0;
        oref[n].link=n+1;
        oref[n].color=COLOR_WHITE;
    }
    onext=0;
    ofree=OREF_SIZE;

    vref=(VREF*)MEMALLOC(VREF_SIZE*sizeof(VREF));
    for(int n=0; n<VREF_SIZE; n++)
    {
        vref[n].value.type=TYPE_NIL;
        vref[n].link=n+1;
        vref[n].color=COLOR_WHITE;
    }
    vnext=0;
    vfree=VREF_SIZE;


    mark_stack=(int*)MEMALLOC(OREF_SIZE*sizeof(int));
    mark_stack_ptr=mark_stack; // init

    pthread_t t=0;
    pthread_create(&t,0,collector,0);
    pthread_setname_np(t,"collector");
    pthread_detach(t);
}


//---------------------------------------------------------------------------
static void *collector(void *ptr)
{
    gc_lock();
    while(1)
    {
        if( gc_timedwait(20000)==0 )
        {
            //printf(" signal");fflush(0);
            vartab_lock();
            vartab_mark();
            vartab_sweep();
            vartab_unlock();
        }
        else if( alloc_count>ALLOC_COUNT/10 || alloc_size>ALLOC_SIZE/10 )
        {
            //printf(" timeout");fflush(0);
            vartab_lock();
            vartab_mark();
            vartab_sweep();
            vartab_unlock();
        }
        else
        {
            //printf(".");fflush(0);
        }
    }
}

//---------------------------------------------------------------------------
static void vartab_mark(void)
{
    if(env_gcdebug)
    {
        static int count=0;
        printf(" GC(%d)  MARK: ",++count);
        printf("%sofree=%s ", (ofree<=OREF_LEVEL?"*":"")     , decimal(ofree));
        printf("%svfree=%s ", (vfree<=VREF_LEVEL?"*":"")     , decimal(vfree));
        printf("%salloc=%s ", (alloc_size>ALLOC_SIZE?"*":"") , decimal(alloc_size/1024/1024));
        fflush(0);
    }

    assign_lock();

    alloc_count=0;
    alloc_size=0;
    mark_stack_ptr=mark_stack; // init

    //-------------------------------------
    // minden BLACK oref -> WHITE
    //-------------------------------------

    for( int n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].color==COLOR_BLACK )
        {
            oref[n].color=COLOR_WHITE;
        }
    }

    for( int n=0; n<VREF_SIZE; n++ )
    {
        if( vref[n].color==COLOR_BLACK )
        {
            vref[n].color=COLOR_WHITE;
        }
    }

    //-------------------------------------
    // minden stackrol elerheto oref -> GRAY
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

    if(env_gcdebug)
    {
        printf("thread=%d ",thrcnt);
        fflush(0);
    }

    //-------------------------------------
    // GRAY -> BLACK
    // BLACK-re allitott oref gyerekei -> GRAY
    // amig el nem tunik minden GRAY oref
    //-------------------------------------

    OREF *o;
    while( 0!=(o=mark_pop()) ) //pop
    {
        //printf(".");fflush(0);
        if( VALUE *v=o->ptr.valptr )
        {
            for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
            {
                vartab_shade(v); //push
            }
        }
        o->color=COLOR_BLACK;
    }

    assign_unlock();
}


//---------------------------------------------------------------------------
static void vartab_shade(VALUE *v)
{
    #ifdef DEBUG_VALID
        valid_value(v);
    #endif

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
            o->color=COLOR_BLACK;
        }
    }
    else
    {
        // ARRAY  mindig van oref-je (len==0 eseten lehet ptr==NULL)
        // OBJECT megegyezik az array esetevel
        // BLOCK  lehet, hogy nincs oref-je, de ha van, akkor ptr!=NULL
        // a prototype objectekben nincs oref!

        OREF *o=v->data.array.oref;
        if( o==NULL )
        {
            // nincs oref
        }
        else if( o->color!=COLOR_WHITE )
        {
            // nem WHITE
        }
        //else if( o->length<=0 )
        //{
        //    o->color=COLOR_BLACK;
        //}
        else
        {
            mark_push(v->data.array.oref); // -> GRAY
        }
    }
}

//---------------------------------------------------------------------------
static void mark_push(OREF*o)
{
    o->color=COLOR_GRAY;
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
        printf("  SWEEP: "); fflush(0);
        printf("ofree=%s vfree=%s --> ",
            decimal(ofree),
            decimal(vfree));
        fflush(0);
    }

    vref_sweep();
    oref_sweep();

    if( env_gcdebug )
    {
        printf("ofree=%s vfree=%s\n",
            decimal(ofree),
            decimal(vfree));
        fflush(0);
    }
}

//---------------------------------------------------------------------------
static void oref_sweep()
{
    unsigned int free_inc=0;
    unsigned int free_beg=ofree;
    for( int n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].color==COLOR_WHITE ) // nincs ra hivatkozas
        {
            if( oref[n].link==-1 ) // VOLT ra hivatkozas
            {
                if( oref[n].length )
                {
                    MEMFREE(oref[n].ptr.valptr);
                }
                oref[n].ptr.valptr=NULL;
                oref[n].length=0;
                oref[n].link=onext;
                onext=n;
                ofree++;
                free_inc++;
                //if( (free_inc%10)==0 )
                {
                    vartab_unlock();
                    vartab_signal();
                    vartab_lock();
                }
            }
        }
    }
    if( env_gcdebug )
    {
        // mutatja
        // hogy a felszabadulo oref-ek kozul
        // hanyat hasznalt el a program a sweep kozben
        printf("[%d] ",(int)(free_beg+free_inc-ofree) );fflush(0);
    }
    vartab_signal();

    if( ofree<=32 && free_inc==0 )
    {
        fprintf(stderr,"\nOREF overflow!\n");
        fflush(0);
        exit(1);
    }
}

//---------------------------------------------------------------------------
static void vref_sweep()
{
    unsigned int free_inc=0;
    for( int n=0; n<VREF_SIZE; n++ )
    {
        if( vref[n].color==COLOR_WHITE ) // nincs ra hivarkozas
        {
            if( vref[n].link==-1 ) // VOLT ra hivatkozas
            {
                vref[n].value.type=TYPE_NIL;
                vref[n].link=vnext;
                vnext=n;
                vfree++;
                free_inc++;
                //if( (free_inc%10)==0 )
                {
                    vartab_unlock();
                    vartab_signal();
                    vartab_lock();
                }
            }
        }
    }
    vartab_signal();

    if( vfree<=32 && free_inc==0 )
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

    while( onext>=OREF_SIZE )
    {
        if( 0==gc_trylock() )
        {
            gc_signal();
            gc_unlock();
        }
        vartab_timedwait(100);
    }
    OREF *o=oref+onext;
    onext=o->link;
    o->link=-1;
    o->color=COLOR_LOCKED;

    --ofree;
    if( ofree<OREF_LEVEL && 0==gc_trylock() )
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

    while( vnext>=VREF_SIZE )
    {
        if( 0==gc_trylock() )
        {
            gc_signal();
            gc_unlock();
        }
        vartab_timedwait(100);
    }
    VREF *v=vref+vnext;
    vnext=v->link;
    v->link=-1;
    v->color=COLOR_LOCKED;

    --vfree;
    if( vfree<VREF_LEVEL && 0==gc_trylock() )
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
    if( v.type<TYPE_GARBAGE )
    {
        type=v.type;
        data=v.data;
    }
    else
    {
        assign_lock();
        // vartab shade?
        type=TYPE_NIL;
        data=v.data;
        type=v.type;
        assign_unlock();
    }
    #ifdef DEBUG_VALID
        valid_value(this);
    #endif
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
static void sleep(int ms)
{
    struct timeval t;
    t.tv_sec=ms/1000;
    t.tv_usec=(ms%1000)*1000;
    select(0,NULL,NULL,NULL,&t);
}

static void sleepmicro(int micro)
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


