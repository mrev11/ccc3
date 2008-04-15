
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
#include <malloc.h>
#include <cccapi.h> 
 
//  Javítások
//
//  2007.05.12 rekurzió nélkül, typeinfó nélkül, 0-ás oref
//  2007.05.05 generációs szemétgyűjtés, age hisztogramm
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

static int alloc_count=0;  // foglalások száma
static long alloc_size=0;  // foglalások összmérete 

static int gc_total=0;     // teljes gyűjtés be (generációs algoritmus ki)
static int gc_agelimit=0;  // öreg egy objektum, ha age>gc_agelimit
static int gc_gener=0;     // ennyi generációs gyűjtést csinál gc_total nélkül
static int gc_counter=0;   // a szemétgyűjtéseket számolja

#define OLD_OREF(x) ((gc_total==0) && (oref[x].age>gc_agelimit))

#define AGE_HISTO_SIZE 8
static int age_histo_befor[AGE_HISTO_SIZE+1]; //hisztogramm gc előtt
static int age_histo_after[AGE_HISTO_SIZE+1]; //hisztogramm gc után

static char *env_garbage=NULL;  // szemétgyűjtés debug infó

static int  OREF_SIZE   =   40000;
static int  VREF_SIZE   =    5000;

static int  ALLOC_COUNT =   40000;
static long ALLOC_SIZE  = 4000000;  //4MB
 
static OREF *oref;
static VREF *vref;

static volatile int garbage_collection_is_running=0;

static void vartab_mark(void*);
static void vartab_sweep();


#if ! defined MULTITHREAD
//---------------------------------------------------------------------------
#define VARTAB_STOP()
#define VARTAB_CONT()
 
void vartab_lock0(){}
void vartab_unlock0(){}
void vartab_lock(){ SIGNAL_LOCK(); }
void vartab_unlock(){ SIGNAL_UNLOCK(); }

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

#else //MULTITHREAD
//---------------------------------------------------------------------------
MUTEX_CREATE(mutex);

#define VARTAB_STOP()    vartab_stop() 
#define VARTAB_CONT()    vartab_cont() 

void vartab_lock0(){ MUTEX_LOCK(mutex); }
void vartab_unlock0(){ MUTEX_UNLOCK(mutex); }
void vartab_lock(){ SIGNAL_LOCK(); MUTEX_LOCK(mutex); }
void vartab_unlock(){ MUTEX_UNLOCK(mutex); SIGNAL_UNLOCK(); }

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
 
#endif //MULTITHREAD


//---------------------------------------------------------------------------
static int *mark_stack=0;
static int *mark_stack_ptr=0;

static void mark_stack_init()
{
    mark_stack_ptr=mark_stack;
}

static void mark_push(OREF*o)
{
    *mark_stack_ptr++=(o-oref); //indexet tárol
}

static OREF *mark_pop()
{
    if( mark_stack_ptr>mark_stack )
    {
        return oref+(*--mark_stack_ptr);
    }
    return 0;
}

//---------------------------------------------------------------------------
void vartab_ini(void)
{
    static int initialized=0;
    if( initialized )
    {
        return;
    }
    initialized=1;

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

    char *vrsp=getenv("VREF_SIZE");
    if( vrsp )
    {
        long size=atol(vrsp);
        VREF_SIZE=size;
    }
    
    static struct VARTAB_SETSIZE vss={ &OREF_SIZE, &VREF_SIZE, 
                                       &ALLOC_COUNT, &ALLOC_SIZE };
    vartab_setsize(&vss);

    oref=(OREF*)MEMALLOC(OREF_SIZE*sizeof(OREF));
    if(oref==NULL)
    {
        fprintf(stderr,"\nNo memory for oref!");
        exit(1);
    }

    vref=(VREF*)MEMALLOC(VREF_SIZE*sizeof(VREF));
    if(vref==NULL)
    {
        fprintf(stderr,"\nNo memory for vref!");
        exit(1);
    }

    mark_stack=(int*)MEMALLOC(OREF_SIZE*sizeof(int));
    if(mark_stack==NULL)
    {
        fprintf(stderr,"\nNo memory for mark_stack!");
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
    onext=0;
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

    if( env_garbage ) //debug infó
    { 
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
        for( int n=0; n<OREF_SIZE; n++ ) //age hisztogramm
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
    
    mark_stack_init();
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
            oref[n].next=NEXT_UNKNOWN;
            if( OLD_OREF(n) )
            {
                vartab_mark(oref+n);
            }
        }
    }

    //static változók stack-je
    VALUE *sp;

    for( sp=ststackbuf; sp<ststack; sp++)
    {
        vartab_mark(sp->data.pointer);
    }

#ifdef MULTITHREAD
    //local változók stack-je
    //az összes szál local stackjét be kell járni

    thread_data *td=thread_data::tdata_first;

    while( td!=0 )
    {
        for( sp=td->_stackbuf; sp<td->_stack; sp++)
        {
            vartab_mark(sp->data.pointer);
        }
        td=td->next;
    }
#else
    //local változók stack-je
    for( sp=stackbuf; sp<stack; sp++)
    {
        vartab_mark(sp->data.pointer);
    }
#endif

    OREF *marked_oref;
    while( 0!=(marked_oref=mark_pop()) ) //pop
    {
        VALUE *v=marked_oref->ptr.valptr;
        for( int t=v->type; t>=TYPE_NIL; t=(++v)->type )
        {
            vartab_mark(v->data.pointer); //push
        }
    }

    vartab_sweep();

    if( env_garbage ) //degub infó
    {
        for( n=0; n<OREF_SIZE; n++ ) //age hisztogramm
        {
            if( oref[n].next==NEXT_RESERVED )
            {
                int x=(oref[n].age<AGE_HISTO_SIZE)?oref[n].age:AGE_HISTO_SIZE-1;
                age_histo_after[x]++;
                age_histo_after[AGE_HISTO_SIZE]++; //összes
            }
        }

        fprintf(stderr, "\nbef [%2d]", gc_counter);
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
        fprintf(stderr,"\nofree=%d vfree=%d\n",ofree,vfree);
        fflush(0);
    }

    garbage_collection_is_running=0;
    VARTAB_CONT();
    return;
}

//---------------------------------------------------------------------------
static void vartab_mark(void *ptr)
{
    int oidx=(OREF*)ptr-oref;
    if( 0<=oidx && oidx<OREF_SIZE ) //valid oref
    {
        OREF *o=oref+oidx;
        if( o->next==NEXT_UNKNOWN )
        {
            o->next=NEXT_RESERVED;
            o->age++;
            if( o->length>0 )
            {
                mark_push(o);
            }
        }
    }
    else
    {
        int vidx=(VREF*)ptr-vref;
        if( 0<=vidx && vidx<VREF_SIZE ) //valid vref
        {
            VREF *r=vref+vidx;
            if( r->next==NEXT_UNKNOWN )
            {
                r->next=NEXT_RESERVED;
                vartab_mark(r->value.data.pointer);
            }
        }
    }
}

//---------------------------------------------------------------------------
static void vartab_sweep()
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

    for( n=0; n<OREF_SIZE; n++ )
    {
        if( oref[n].next==NEXT_UNKNOWN )
        {
            if( oref[n].length )
            {
                *oref[n].ptr.chrptr='@'; // szándékos rongálás
                MEMFREE(oref[n].ptr.valptr);
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
}

//---------------------------------------------------------------------------
VREF *vref_new(void)
{
    if( ++alloc_count>ALLOC_COUNT || vnext>=VREF_SIZE )
    {
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
    if( ++alloc_count>ALLOC_COUNT || onext>=OREF_SIZE )
    {
        vartab_rebuild();
    }
    OREF *o=oref+onext;
    onext=o->next;
    o->next=NEXT_LOCKED;
    o->age=0;
    return o;
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

    VALUE *p=(VALUE*)MEMALLOC( len*sizeof(VALUE) );

    if( p==NULL )
    {
        gc_counter=0; //teljes gyűjtés kikényszerítve
        vartab_rebuild();
        p=(VALUE*)MEMALLOC(len*sizeof(VALUE));
        if( p==NULL )
        {
            fprintf(stderr,"\nmemory overbooked: %d",len);
            fflush(0);
            exit(1);
        }
    }
    memset(p,0,len*sizeof(VALUE));
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
