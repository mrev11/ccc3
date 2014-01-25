
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

//Windowson egyszálú esetben is kell a GC_THREADS.
//GC_THREADS nélkül, egyszálú CCC-vel fordított programok Windowson 
//nem indulnak el: nem érkezik meg a vezérlés a C szintű main-be. 

#define GC_THREADS
#include <gc/gc.h> 

// Boehm-féle szemétgyűjtés

//---------------------------------------------------------------------------
void valuesort(VALUE *v, int n)  //egyszálú
{
    qsort(v,n,sizeof(VALUE),valuecompare);
}

//---------------------------------------------------------------------------
void valuemove(VALUE *to, VALUE *fr, int n)  //egyszálú 
{
    memmove(to,fr,n*sizeof(VALUE));
}

//---------------------------------------------------------------------------
VREF *vref_new(void)
{
    return (VREF*)GC_MALLOC(sizeof(VREF));
}

//---------------------------------------------------------------------------
OREF *oref_new(void)
{
    return (OREF*)GC_MALLOC(sizeof(OREF));
}

//---------------------------------------------------------------------------
void deleteValue(VALUE *v)
{
    //empty
}

//---------------------------------------------------------------------------
VALUE *newValue(unsigned int len)
{
    return (VALUE*)GC_MALLOC_IGNORE_OFF_PAGE( len*sizeof(VALUE) );
}

//-------------------------------------------------------------------------
CHAR *newChar(unsigned int len)
{
    return (CHAR*)GC_MALLOC_ATOMIC_IGNORE_OFF_PAGE(len*sizeof(CHAR));
}

//-------------------------------------------------------------------------
BYTE *newBinary(unsigned int len)
{
    return (BYTE*)GC_MALLOC_ATOMIC_IGNORE_OFF_PAGE(len*sizeof(BYTE));
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


    GC_INIT();

#if ! defined  MULTITHREAD
    //üres
#elif defined UNIX
    pthread_key_create(&thread_key,0);
    pthread_setspecific(thread_key,NEWTHRDATA());
#else
    thread_key=TlsAlloc();
    TlsSetValue(thread_key,NEWTHRDATA());
#endif
    siglocklev=0; //unlock (kezdetben lockolva van)
}

//---------------------------------------------------------------------------
void vartab_lock(void)
{
    //empty
}

//---------------------------------------------------------------------------
void vartab_unlock(void)
{
    //empty
}

//---------------------------------------------------------------------------
void vartab_lock0(void)
{
    //empty
}

//---------------------------------------------------------------------------
void vartab_unlock0(void)
{
    //empty
}

//---------------------------------------------------------------------------
void vartab_rebuild(void)
{
    GC_gcollect();
}

//---------------------------------------------------------------------------
void _clp_gc(int argno)
{
    stack-=argno;
    GC_gcollect();
    push(&NIL);
}
 
//---------------------------------------------------------------------------
