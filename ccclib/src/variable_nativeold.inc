
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

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cccapi.h> 
 
//  Javítások
//
//  2007.05.05 generációs szemétgyűjtés, hisztogramm
//  2007.04.11 MUTEX_LOCK/MUTEX_UNLOCK makrók
//  2006.03.17 unicode támogatás (TYPE_BINARY <--> TYPE_STRING)
//  2005.07.20 szálkezelés átírva, szignálkezelés
//  2003.07.30 multithreading támogatás
//  2002.06.28 oref_size mérete linkeléskor szabályozható    
//  1999.01.16 oref többé egyáltalán nem látszik ki    
//  1998.05.03 oref,vref static, szabályozható méretű
//  1996.06.26 0-ás oref nincs

//---------------------------------------------------------------------------
static int vnext;  // a következő szabad index vref-ben
static int onext;  // a következő szabad index oref-ben

static int vfree;  // szabad elemek száma vref-ben szemétgyűjtés után
static int ofree;  // szabad elemek száma oref-ben szemétgyűjtés után

static int alloc_count=0;  // szemétgyűjtés paramétere
static long alloc_size=0;  // szemétgyűjtés paramétere

static int gc_total=0;     // teljes gyűjtés be (generációs algoritmus ki)
static int gc_agelimit=0;  // fiatal egy objektum, ha age<=gc_agelimit
static int gc_gener=0;     // ennyi generációs gyűjtést csinál gc_total nélkül
static int gc_counter=0;   // a szemétgyűjtéseket számolja
static int gc_walkcnt=0;

#define AGE_HISTO_SIZE 8
static int age_histo_befor[AGE_HISTO_SIZE+1];
static int age_histo_after[AGE_HISTO_SIZE+1];

#define YOUNG(x) ( (gc_total!=0) || (oref[x].age<=gc_agelimit))

static char *env_garbage=NULL;  // szemétgyűjtés debugolása

static int  OREF_SIZE   =   40000;
static int  VREF_SIZE   =    5000;

static int  ALLOC_COUNT =   40000;
static long ALLOC_SIZE  = 4000000;  //4MB
 
static OREF *oref;
static VREF *vref;

static volatile int garbage_collection_is_running=0;

static void vartab_walk(VALUE *v);
static void vartab_garbage();


#define DEBUG_GC
#if defined DEBUG_GC
    static volatile int debug_gc=0;
    static int examined_thread=0;

    #define EXAMINED_INIT()     examined_thread=0
    #define EXAMINED_THREAD()   examined_thread++
    #define VALIDATE_OREF(o,v)  validate_oref(o,v)
    #define VALIDATE_VREF(r,v)  validate_vref(r,v)
    static void validate_oref(OREF*,VALUE*);
    static void validate_vref(VREF*,VALUE*);
#else
    #define EXAMINED_INIT()
    #define EXAMINED_THREAD()
    #define VALIDATE_OREF(o,v)
    #define VALIDATE_VREF(o,v)
#endif

static void trap()
{
    #ifdef _UNIX_
        printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        printf("\nGC-TRAP pid=%d",(int)getpid());
        printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        printf("\n");fflush(0);
        kill(0,SIGSTOP);
    #endif
} 


#if ! defined MULTITHREAD
//---------------------------------------------------------------------------
void valuesort(VALUE *v, int n)  //egyszálú
{
    SIGNAL_LOCK();
    qsort(v,n,sizeof(VALUE),valuecompare);
    SIGNAL_UNLOCK();
}

//---------------------------------------------------------------------------
void valuemove(VALUE *to, VALUE *fr, int n)  //egyszálú 
{
    SIGNAL_LOCK();
    memmove(to,fr,n*sizeof(VALUE));
    SIGNAL_UNLOCK();
}
 
#define VARTAB_STOP()
#define VARTAB_CONT()
 
void vartab_lock(){ SIGNAL_LOCK(); }
void vartab_unlock(){ SIGNAL_UNLOCK(); }

#else // UNIX és Windows

MUTEX_CREATE(mutex);

void vartab_lock0(){ MUTEX_LOCK(mutex); }
void vartab_unlock0(){ MUTEX_UNLOCK(mutex); }
void vartab_lock(){ SIGNAL_LOCK(); MUTEX_LOCK(mutex); }
void vartab_unlock(){ MUTEX_UNLOCK(mutex); SIGNAL_UNLOCK(); }
 
#endif


#ifdef MULTITHREAD
//---------------------------------------------------------------------------
void valuesort(VALUE *v, int n)
{
    if( n<2 )
    {
    }
    else if( thread_data::tdata_count==1 )
    {
        SIGNAL_LOCK();
        qsort(v,n,sizeof(VALUE),valuecompare);
        SIGNAL_UNLOCK();
    }
    else
    {
        SIGNAL_LOCK();
        thread_data_ptr->lock();
        qsort(v,n,sizeof(VALUE),valuecompare);
        thread_data_ptr->unlock();
        SIGNAL_UNLOCK();
    }
}

//---------------------------------------------------------------------------
void valuemove(VALUE *to, VALUE *fr, int n)
{
    if( n==0 )
    {
    }
    else if( thread_data::tdata_count==1 )
    {
        SIGNAL_LOCK();
        memmove(to,fr,n*sizeof(VALUE));
        SIGNAL_UNLOCK();
    }
    else
    {
        SIGNAL_LOCK();
        thread_data_ptr->lock();
        memmove(to,fr,n*sizeof(VALUE));
        thread_data_ptr->unlock();
        SIGNAL_UNLOCK();
    }
}

//---------------------------------------------------------------------------
VALUE VALUE::operator=(VALUE v)
{
#if defined DEBUG_GC    
    while( debug_gc )
    {
        #ifdef _UNIX_
            struct timeval t;
            t.tv_sec=1;
            t.tv_usec=0;
            select(0,0,0,0,0);
        #else
            Sleep(1000);
        #endif
    }
#endif

    if( this==&v )
    {
        //OK
    }
    else if( (thread_data::tdata_count==1) || (v.type<TYPE_SCALAR) )
    {
        //fontos optimalizálás;
        //másik szálon futó szemétgyűjtés alatt is megengedett
        //a skalár<--skalár és array<--skalár típusú értékadás;
        //lényeges, hogy amíg type és data nem összetartozó
        //értékeket tartalmaz, addig type-ban ne legyen array típus,
        //mert akkor a szemétgyűjtés elromolhat;
        //ugyanez a védelem kell egyszálú esetben is,
        //ui. a szignálkezelőből is indulhat szemétgyűjtés;

        ((volatile VALUE*)this)->type=TYPE_NIL; //atomi
        data=v.data;
        type=v.type; //atomi
    }
    else
    {
        SIGNAL_LOCK();
        thread_data_ptr->lock();
        type=v.type;
        data=v.data;
        thread_data_ptr->unlock();
        SIGNAL_UNLOCK();
    }
    return *this;
}

//---------------------------------------------------------------------------
static void vartab_stop()  //a többi szálat elzárja az értékadástól
{
    thread_data *td=thread_data::tdata_first;
    while( td!=0 )
    {
        td->lock();
        td=td->next;
    }
}

//---------------------------------------------------------------------------
static void vartab_cont() // minden várakozó szálat kienged
{
    thread_data *td=thread_data::tdata_first;
    while( td!=0 )
    {
        td->unlock();
        td=td->next;
    }
}

#define VARTAB_STOP()    vartab_stop() 
#define VARTAB_CONT()    vartab_cont() 
 
#endif
 

//---------------------------------------------------------------------------
void vartab_ini(void)
{
    static int initialized=0;
    if( initialized )
    {
        return;
    }
    initialized=1;

    //csak egyszer lehet inicializálni
    //printf("\nvartab initialized");fflush(0);

#if ! defined  MULTITHREAD
    //üres
#elif defined UNIX
    pthread_key_create(&thread_key,0);
    pthread_setspecific(thread_key,new thread_data());
#else
    thread_key=TlsAlloc();
    TlsSetValue(thread_key,new thread_data());
#endif
    siglocklev=0; //unlock (kezdetben lockolva van)
 
    char *orsp=getenv("OREF_SIZE");
    if( orsp )
    {
        long size=atol(orsp);
        OREF_SIZE=size;
        ALLOC_COUNT=size;
        ALLOC_SIZE=size*100;
    }

    char *vrsp=getenv("VREF_SIZE");  //2000.07.25
    if( vrsp )
    {
        long size=atol(vrsp);
        VREF_SIZE=size;
    }
    
    static struct VARTAB_SETSIZE vss={ &OREF_SIZE, &VREF_SIZE, 
                                       &ALLOC_COUNT, &ALLOC_SIZE };
    vartab_setsize(&vss);

    oref=(OREF*)MEMALLOC(OREF_SIZE*sizeof(OREF));  //dinamikus helyfoglalás
    if(oref==NULL)
    {
        fprintf(stderr,"\nNo memory for oref!");
        exit(1);
    }

    vref=(VREF*)MEMALLOC(VREF_SIZE*sizeof(VREF));  //dinamikus helyfoglalás
    if(vref==NULL)
    {
        fprintf(stderr,"\nNo memory for vref!");
        exit(1);
    }


    env_garbage=getenv("GARBAGE");


    int n;

    for(n=0; n<VREF_SIZE; n++)
    {
        vref[n].value.type=TYPE_NIL;
        vref[n].next=n+1;
    }
    vnext=0;

    for(n=0; n<OREF_SIZE; n++)
    {
        oref[n].ptr.valptr=NULL;
        oref[n].length=0;
        oref[n].next=n+1;
        oref[n].age=0;
    }
    onext=1; // 0-ás oref nincs!
}

//---------------------------------------------------------------------------
VREF *vref_new(void)
{
    if( ++alloc_count>ALLOC_COUNT )
    {
        vartab_rebuild();
    }

    if( vnext>=VREF_SIZE )
    {
        //gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();
    }
    VREF *v=vref+vnext;
    vnext=v->next;
    v->next=NEXT_LOCKED;
    return v;
}

//---------------------------------------------------------------------------
OREF *oref_new(void)
{
    if( ++alloc_count>ALLOC_COUNT )
    {
        vartab_rebuild();
    }

    if( onext>=OREF_SIZE )
    {
        //gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();
    }
    OREF *o=oref+onext;
    onext=o->next;
    o->next=NEXT_LOCKED;
    o->age=0;
    return o;
}

//---------------------------------------------------------------------------
void vartab_rebuild(void)
{
    if( garbage_collection_is_running )
    {
        return;
    }
    else
    {
        garbage_collection_is_running=1;
    }

    VARTAB_STOP();
 
    gc_walkcnt=0;
    if( gc_counter>0 )
    {
        gc_total=0; //generációs gyűjtés
        gc_counter--;
    }
    else
    {
        gc_total=1; //teljes gyűjtés
        gc_counter=gc_gener;
    }

    if( env_garbage )
    {
        //fprintf(stderr,"\npid: %u",(unsigned)getpid());

        fprintf
        (
            stderr,
            "\nalloc_count: %d/%d, alloc_size: %ldK/%ldK",
            alloc_count,ALLOC_COUNT,alloc_size>>10,ALLOC_SIZE>>10 
        );
        fflush(0);

        for( int x=0; x<=AGE_HISTO_SIZE; x++ )
        {
            age_histo_befor[x]=0;
            age_histo_after[x]=0;
        }

        for( int n=1; n<OREF_SIZE; n++ ) //statisztika
        {
            if( oref[n].next==NEXT_RESERVED )
            {
                int x=(oref[n].age<AGE_HISTO_SIZE)?oref[n].age:AGE_HISTO_SIZE-1;
                age_histo_befor[x]++;
                age_histo_befor[AGE_HISTO_SIZE]++; //összes
            }
        }
    }

    alloc_count=0;
    alloc_size=0;

    int n;

    for( n=0; n<VREF_SIZE; n++ )
    {
        if( vref[n].next!=NEXT_LOCKED )
        {
            vref[n].next=NEXT_UNKNOWN;
        }
    }

    for( n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].next!=NEXT_LOCKED )
        {
            oref[n].next=YOUNG(n)?NEXT_UNKNOWN:NEXT_AGELIMIT;
        }
    }

    //static változók stack-je
    VALUE *sp;

    EXAMINED_INIT();
    for( sp=ststackbuf; sp<ststack; sp++)
    {
        if( sp->type>TYPE_GARBAGE )
        {
            vartab_walk(sp);
        }
    }

#ifdef MULTITHREAD
    //local változók stack-je
    //az összes szál local stackjét be kell járni

    thread_data *td=thread_data::tdata_first;

    while( td!=0 )
    {
        EXAMINED_THREAD();
        for( sp=td->_stackbuf; sp<td->_stack; sp++)
        {
            if( sp->type>TYPE_GARBAGE )
            {
                vartab_walk(sp);
            }
        }
        td=td->next;
    }
#else
    //local változók stack-je
    for( sp=stackbuf; sp<stack; sp++)
    {
        if( sp->type>=TYPE_GARBAGE )
        {
            vartab_walk(sp);
        }
    }
#endif

    if( gc_total==0 )
    {
        for(int n=1; n<OREF_SIZE; n++ )
        {
            if( oref[n].next==NEXT_AGELIMIT )
            {
                oref[n].next=NEXT_RESERVED;
                oref[n].age++;
                if( oref[n].length>0 )
                {
                    VALUE *p=oref[n].ptr.valptr;
                    for(int t=p->type; p->type>=TYPE_NIL; t=((++p)->type) )
                    {
                        if( t>=TYPE_GARBAGE ) 
                        {
                            vartab_walk(p);
                        }
                    }
                }
            }
        }
    }

    vartab_garbage();

    if( env_garbage )
    {
        for( n=1; n<OREF_SIZE; n++ ) //statisztika
        {
            if( oref[n].next==NEXT_RESERVED )
            {
                int x=(oref[n].age<AGE_HISTO_SIZE)?oref[n].age:AGE_HISTO_SIZE-1;
                age_histo_after[x]++;
                age_histo_after[AGE_HISTO_SIZE]++; //összes
            }
        }

        fprintf(stderr,"\nvfree=%d ofree=%d walk=%d\n",vfree,ofree,gc_walkcnt);

        fprintf(stderr, "bef [%2d]", gc_counter);
        for( int i=0; i<=AGE_HISTO_SIZE; i++ )
        {
            fprintf(stderr, "%8d",age_histo_befor[i]);       
        }
        fprintf(stderr,"\n");       

        fprintf(stderr, "aft [%2d]", gc_total);
        for( int i=0; i<=AGE_HISTO_SIZE; i++ )
        {
            fprintf(stderr, "%8d",age_histo_after[i]);       
        }
        fprintf(stderr,"\n");       
        fflush(0);
    }

    garbage_collection_is_running=0;
    VARTAB_CONT();
    return;
}

//---------------------------------------------------------------------------
static void vartab_walk(VALUE *v)
{
    gc_walkcnt++;

    //printf("\n%ld",++vw_count);fflush(0);
    
    switch( v->type )
    {
        case TYPE_BINARY:
        case TYPE_STRING:
        {
            OREF *o=v->data.string.oref;
            VALIDATE_OREF(o,v);
            if( o!=NULL && o->next==NEXT_UNKNOWN )
            {
                o->next=NEXT_RESERVED;
                o->age++;
            }
            break;
        }
       
        case TYPE_ARRAY:
        case TYPE_BLOCK:
        case TYPE_OBJECT:
        {
            OREF *o=v->data.array.oref;
            VALIDATE_OREF(o,v);
            if( (o!=NULL) && (o->next==NEXT_UNKNOWN) )
            {
                o->next=NEXT_RESERVED;
                o->age++;
                VALUE *p=o->ptr.valptr;

                if( p )
                {
                    // az array elemek, block változók, object slotok
                    // lezárását a TYPE_END (==-1) típusú elem jelzi

                    for( int t=p->type; t>=TYPE_NIL; t=((++p)->type) )
                    {
                        if( t>=TYPE_GARBAGE ) 
                        {
                            vartab_walk(p);
                        }
                    }
                }
            }
            break;
        }

        case TYPE_REF:
        {
            VREF *r=v->data.vref;
            VALIDATE_VREF(r,v);
            if( r->next==NEXT_UNKNOWN )
            {
                r->next=NEXT_RESERVED;
                if( r->value.type>=TYPE_GARBAGE )
                {
                    vartab_walk( &r->value );
                }
            }
            break;
        }
    }

    //printf("!");fflush(0);
    return;
}

//---------------------------------------------------------------------------
static void vartab_garbage()
{
    // vref-ek takarítása

    vfree=0;
    int vprev=vnext=-1;
    int n;

    for( n=0; n<VREF_SIZE; n++ )
    {
        if( vref[n].next==NEXT_UNKNOWN )
        {
            vref[n].value.type=TYPE_NIL;

            if( vfree++==0 )
            {
                vprev=vnext=n;
            }
            else
            {
                vref[vprev].next=n;
                vprev=n;
            }
        }
    }

    if( vfree>0 )
    {
        vref[vprev].next=VREF_SIZE;
    }
    else
    {
        fprintf(stderr,"\nVREF overflow");
        fflush(0);
        exit(1);
    }


    // oref-ek takarítása

    ofree=0;
    int oprev=onext=-1;

    for( n=1; n<OREF_SIZE; n++ )  // 0-ás oref nincs!
    {
        if( oref[n].next==NEXT_UNKNOWN )
        {
            if( oref[n].length )
            {
                // szándékos rongálás, abból a célból,
                // hogy könnyebben kiderüljön, ha törölt
                // bufferekre hivatkozik a program
                *oref[n].ptr.chrptr='?'; 

                //delete (void*)(oref[n].ptr.valptr);
                MEMFREE(oref[n].ptr.valptr); //99.07.06
            }
            oref[n].ptr.valptr=NULL;
            oref[n].length=0;
            oref[n].age=0;

            if( ofree++==0 )
            {
                oprev=onext=n;
            }
            else
            {
                oref[oprev].next=n;
                oprev=n;
            }
        }
    }

    if( ofree>0 )
    {
        oref[oprev].next=OREF_SIZE;
    }
    else
    {
        fprintf(stderr,"\nOREF overflow");
        fflush(0);
        exit(1);
    }

    return;
}


//---------------------------------------------------------------------------
void deleteValue(VALUE *v)
{
    MEMFREE(v);
}

//---------------------------------------------------------------------------
VALUE *newValue(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(VALUE)*len;
    if( alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE )
    {
        vartab_rebuild();
    }

    //VALUE *p=new VALUE[len];
    VALUE *p=(VALUE*)MEMALLOC( len*sizeof(VALUE) ); //99.07.06

    if( p==NULL )
    {
        gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();

        //p=new VALUE[len];
        p=(VALUE*)MEMALLOC(len*sizeof(VALUE)); //99.07.06
 
        if( p==NULL )
        {
            fprintf(stderr,"\nmemory overbooked: %d",len);
            fflush(0);
            trap();
            exit(1);
        }
    }
    return p;
}

//-------------------------------------------------------------------------
CHAR *newChar(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(CHAR)*len;
    if( alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE )
    {
        vartab_rebuild();
    }

    CHAR *p=(CHAR*)MEMALLOC(len*sizeof(CHAR));

    if( p==NULL )
    {
        gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();

        p=(CHAR*)MEMALLOC(len*sizeof(CHAR));

        if( p==NULL )
        {
            fprintf(stderr,"\nmemory overbooked: %d",len);
            fflush(0);
            trap();
            exit(1);
        }
    }
    return p;
}

//-------------------------------------------------------------------------
BYTE *newBinary(unsigned int len)
{
    alloc_count++;
    alloc_size+=sizeof(BYTE)*len;
    if( alloc_count>ALLOC_COUNT || alloc_size>ALLOC_SIZE )
    {
        vartab_rebuild();
    }

    BYTE *p=(BYTE*)MEMALLOC(len*sizeof(BYTE));

    if( p==NULL )
    {
        gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();

        p=(BYTE*)MEMALLOC(len*sizeof(BYTE));

        if( p==NULL )
        {
            fprintf(stderr,"\nmemory overbooked: %d",len);
            fflush(0);
            trap();
            exit(1);
        }
    }
    return p;
}
 

//---------------------------------------------------------------------------
void _clp_gc(int argno)
{
    stack-=argno;
    VARTAB_LOCK();
    vartab_rebuild();
    VARTAB_UNLOCK();
    push(&NIL);
}
 
//---------------------------------------------------------------------------
#if defined DEBUG_GC

static VALUE *examined_stack=0;
static VALUE *examined_stackbuf=0;
static TRACE *examined_trace=0;
static TRACE *examined_tracebuf=0;

//---------------------------------------------------------------------------
static void print(VALUE *v, int len, int tab)
{
    for( int i=0; i<len; i++,v++ )
    {
        if( tab==0 )
        {
            for( TRACE *t=examined_tracebuf+1; t<=examined_trace; t++ )
            {
                if(v==t->base)
                {
                    printf("--------%s(%d)\n",t->func,t->line);fflush(0);
                }
            }
        }

        printf("%*s",tab,"");fflush(0);

        if( v->type==TYPE_NIL )
        {
            printf("U\n");fflush(0);
        }

        else if( v->type==TYPE_NUMBER )
        {
            printf("N %f\n",v->data.number);fflush(0);
        }

        else if( v->type==TYPE_DATE )
        {
            printf("D %ld\n", v->data.date);fflush(0);
        }
  
        else if( v->type==TYPE_FLAG )
        {
            printf("L %d\n",v->data.flag);fflush(0);
        }

        else if( v->type==TYPE_POINTER )
        {
            printf("P %lx\n",(unsigned long)v->data.pointer);fflush(0);
        }

        else if( v->type==TYPE_BINARY )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "X %lx [%d]",(unsigned long)o,idx);fflush(0);

            if( o==0 )
            {
                printf(" null\n");fflush(0);
            }
            else if( (idx<=0) || (OREF_SIZE<=idx) )
            {
                printf(" crashed\n");fflush(0);
            }
            else
            {
                printf(" \'%s\'\n",BINARYPTR(v));fflush(0);
            }
        }

        else if( v->type==TYPE_STRING )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "C %lx [%d]",(unsigned long)o,idx);fflush(0);

            if( o==0 )
            {
                printf(" null\n");fflush(0);
            }
            else if( (idx<=0) || (OREF_SIZE<=idx) )
            {
                printf(" crashed\n");fflush(0);
            }
            else
            {
                char *p=wchar_to_utf8(STRINGPTR(v),STRINGLEN(v),0);
                printf(" \'%s\'\n",p);fflush(0);
                free(p);
            }
        }

        else if( v->type==TYPE_ARRAY )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "A %lx [%d]",(unsigned long)o,idx);fflush(0);

            if( o==0 )
            {
                printf(" null\n");fflush(0);
            }
            else if( (idx<=0) || (OREF_SIZE<=idx) )
            {
                printf(" crashed\n");fflush(0);
            }
            else
            {
                int l=o->length;
                VALUE *v1=o->ptr.valptr;
                printf(" length=%d\n", l);fflush(0);
                print(v1,l,tab+4);fflush(0);
            }
        }

        else if( v->type==TYPE_BLOCK )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "B %lx [%d]",(unsigned long)o,idx);fflush(0);
            printf("\n");fflush(0);
        }

        else if( v->type==TYPE_OBJECT )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "O %lx [%d]",(unsigned long)o,idx);fflush(0);

            if( o==0 )
            {
                printf(" null\n");fflush(0);
            }
            else if( (idx<=0) || (OREF_SIZE<=idx) )
            {
                printf(" crashed\n");fflush(0);
            }
            else
            {
                int l=o->length;
                VALUE *v1=o->ptr.valptr;
                printf(" length=%d\n",l);fflush(0);
                print(v1,l,tab+4);fflush(0);
            }
        }

        else if( v->type==TYPE_REF )
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "R %lx [%d]",(unsigned long)o,idx);fflush(0);
            printf("\n");fflush(0);
        }

        else
        {
            OREF *o=v->data.array.oref;
            int idx=o-oref;
            printf( "<%d> %lx [%d]",v->type,(unsigned long)o,idx);fflush(0);
            printf("\n");fflush(0);
        }
    }
}

//---------------------------------------------------------------------------
static void walk()
{
#ifdef MULTITHREAD
    int tcnt=0;
    thread_data *td=thread_data::tdata_first;
    while( td!=0 )
    {
        printf("thread %d\n",++tcnt); fflush(0);
        TRACE *tbuf=td->_tracebuf;
        TRACE *tptr=td->_trace;
        while( tptr>tbuf )
        {
            printf("    %s(%d)\n",tptr->func,tptr->line);fflush(0);
            --tptr;
        }
        
        if( tcnt==examined_thread )
        {
            examined_stack=td->_stack;
            examined_stackbuf=td->_stackbuf;
            examined_trace=td->_trace;
            examined_tracebuf=td->_tracebuf;
        }
        td=td->next;
    }
#else
    examined_stack=stack;
    examined_stackbuf=stackbuf;
    examined_trace=trace;
    examined_tracebuf=tracebuf;
#endif    

    if( examined_stack )
    {
        int depth=(int)(examined_stack-examined_stackbuf);
        printf("depth=%d\n",depth);fflush(0);
        print(examined_stackbuf,depth,0);fflush(0);
    }

#ifdef _UNIX_    
    kill(getpid(),SIGSTOP);
#else    
    exit(1);
#endif    
}

//---------------------------------------------------------------------------
static void validate_oref(OREF*o, VALUE*v)
{
    if( o==0 )
    {
        return; //jó
    }

    int i=o-oref;
    if( (0<i) && (i<OREF_SIZE) )
    {
        return; //jó
    }

    debug_gc=1;
    printf("\noref_error %lx [%d]\n",(unsigned long)o,i);fflush(0);
#ifdef MULTITHREAD
    printf("error on stack %d of %d\n",examined_thread,thread_data::tdata_count);fflush(0);
#endif
    printf("type %d\n",v->type);fflush(0);

    walk();
}

//---------------------------------------------------------------------------
static void validate_vref(VREF*r,VALUE*v)
{
    int i=r-vref;
    if( (0<=i) && (i<VREF_SIZE) )
    {
        return; //jó
    }

    debug_gc=1;
    printf("\nvref_error %lx [%d]\n",(unsigned long)r,i);fflush(0);
#ifdef MULTITHREAD
    printf("error on stack %d of %d\n",examined_thread,thread_data::tdata_count);fflush(0);
#endif
    printf("type %d\n",v->type);fflush(0);

    walk();
}


//---------------------------------------------------------------------------
#endif // DEBUG_GC
//---------------------------------------------------------------------------


