
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

#ifdef _UNIX_
#include <sys/mman.h>
#endif

#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <string.h>
#include <cccapi.h>

//------------------------------------------------------------------------
static CHAR *oneletter(int c)
{
    static CHAR *buffer=0;
    if( buffer==0 )
    {
        int ps=4096; //getpagesize();

        #ifdef _UNIX_
            buffer=(CHAR*)aligned_alloc(ps,ps);
        #else
            buffer=(CHAR*)VirtualAlloc(0,ps,MEM_COMMIT,PAGE_READWRITE);
        #endif

        for( int i=0; i<256; i++ )
        {
            buffer[(i<<1)]=i;
            buffer[(i<<1)+1]=0;
        }

        #ifdef _UNIX_
            mprotect(buffer,ps,PROT_READ);
        #else
            DWORD oldprot=0; VirtualProtect(buffer,ps,PAGE_READONLY,&oldprot);
        #endif
    }

    //static int count=0;
    //printf("\nONELETTER %6d %3d [%s]", ++count, c, (char*)&buffer[c<<1]); fflush(0);
    return  &buffer[c<<1];
}


//------------------------------------------------------------------------
void _clp___maxstrlen(int argno)
{
    stack-=argno;
    number(MAXSTRLEN);
}

//------------------------------------------------------------------------
void string(CHAR const *ptr) //új példány rámutatással (new nélkül)
{
//stack:   --- s

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    o->ptr.chrptr=(CHAR*)ptr;
    o->length=0;              //szemétgyűjtés NEM törli 
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.string.oref=o;
    STRINGLEN(v)=wcslen(ptr);
    v->type=TYPE_STRING;
 
    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
void stringn(CHAR const *ptr) //új példány másolással (new)
{
//stack:   --- s

    unsigned long len=wcslen(ptr);
    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("stringn",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    if( (len<=1) && (*ptr<256) )
    {
        o->ptr.chrptr=oneletter(*ptr);
        o->length=0; //szemétgyűjtés NEM törli
        //printf("<N>");fflush(0);
    }
    else
    {
        CHAR *p=newChar(len+1);
        wmemcpy(p,ptr,len+1);
        o->ptr.chrptr=p;
        o->length=-1; //szemétgyűjtés törli
    }
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.string.oref=o;
    STRINGLEN(v)=len;
    v->type=TYPE_STRING;

    VARTAB_UNLOCK();
}

void stringnb(char const *ptr) //új string bytearrayből
{
    unsigned reslen=0;
    CHAR *p=utf8_to_wchar(ptr,strlen(ptr),&reslen);
    strings(p,reslen);
    free(p);
}

//------------------------------------------------------------------------
void strings(CHAR const *ptr, unsigned long len) //substring kimásolása new-val
{
//stack:   --- s

    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("strings",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    if( (len<=1) && (*ptr<256) )
    {
        o->ptr.chrptr=oneletter(*ptr);
        o->length=0; //szemétgyűjtés NEM törli
        //printf("<S>");fflush(0);
    }
    else
    {
        CHAR *p=newChar(len+1);
        wmemcpy(p,ptr,len);
        *(p+len)=(CHAR)0x00;
        o->ptr.chrptr=p;
        o->length=-1; //szemétgyűjtés törli 
    }
    o->next=NEXT_RESERVED;
  
    VALUE *v=PUSHNIL();
    v->data.string.oref=o;
    STRINGLEN(v)=len;
    v->type=TYPE_STRING;

    VARTAB_UNLOCK();
}

void stringsb(char const *ptr, unsigned long len) //új string bytearrayből
{
    unsigned reslen=0;
    CHAR *p=utf8_to_wchar(ptr,len,&reslen);
    strings(p,reslen);
    free(p);
}

//------------------------------------------------------------------------
CHAR *stringl(unsigned long len) //inicializálatlan string new-val
{
//stack:   --- s
//return: string pointer

    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("stringl",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->ptr.chrptr=newChar(len+1);
    *(o->ptr.chrptr+len)=(CHAR)0x00; 
    o->length=-1;              //szemétgyűjtés törli  
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.string.oref=o;
    STRINGLEN(v)=len;
    v->type=TYPE_STRING;
 
    VARTAB_UNLOCK();
    return o->ptr.chrptr;
}

//------------------------------------------------------------------------
//compatibility
void strings(CHAR const *ptr, unsigned int len){ strings(ptr,(unsigned long)len); }
void stringsb(char const *ptr, unsigned len){ stringsb(ptr,(unsigned long)len); }
CHAR *stringl(unsigned int len){ return stringl((unsigned long)len); }
//------------------------------------------------------------------------
