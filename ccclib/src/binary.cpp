
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
#include <string.h>
#include <cccapi.h>

#ifdef _TERMUX_                                                                                                         
#define  aligned_alloc  memalign                                                                                        
// termuxon nincs  aligned_alloc()                                                                                      
// netbsd-n nincs  memalign()                                                                                           
// ugyanazt csinaljak                                                                                                   
#endif      

//------------------------------------------------------------------------
static char *oneletter(int c)
{
    static char *buffer=0;
    if( buffer==0 )
    {
        int ps=4096; //getpagesize();

        #ifdef _UNIX_
            buffer=(char*)aligned_alloc(ps,ps);
         #else
            buffer=(char*)VirtualAlloc(0,ps,MEM_COMMIT,PAGE_READWRITE);
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
    //printf("\noneletter %6d %3d [%s]", ++count, c, buffer+((c&255)<<1)); fflush(0);
    return buffer+((c&255)<<1);
}

//------------------------------------------------------------------------
void _clp___maxbinlen(int argno)
{
    stack-=argno;
    number(MAXBINLEN);
}

//------------------------------------------------------------------------
void binary(BYTE const *ptr) //új példány rámutatással (new nélkül)
{
//stack:   --- s

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->ptr.binptr=(BYTE*)ptr;
    o->length=0;              //szemétgyűjtés NEM törli
    o->color=COLOR_RESERVED;

    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    BINARYLEN(v)=strlen((char*)ptr);
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
void binaryn(BYTE const *ptr) //új példány másolással (new)
{
//stack:   --- s

    unsigned long len=strlen((char*)ptr);
    if( len>MAXBINLEN )
    {
        number(len);
        error_bln("binaryn",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new();
    if( len<=1 )
    {
        o->ptr.binptr=oneletter(*ptr);
        o->length=0; //szemétgyűjtés NEM törli
        //printf("<n>");fflush(0);
    }
    else
    {
        BYTE *p=newBinary(len+1);
        memcpy(p,ptr,(len+1)*sizeof(BYTE));
        o->ptr.binptr=p;
        o->length=-1; //szemétgyűjtés törli
    }
    o->color=COLOR_RESERVED;

    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    BINARYLEN(v)=len;
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
void binarys(BYTE const *ptr, unsigned long len) //substring kimásolása new-val
{
//stack:   --- s

    if( len==0 )
    {
        ptr="";
    }

    if( len>MAXBINLEN )
    {
        number(len);
        error_bln("binarys",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new();
    if( len<=1 )
    {
        o->ptr.binptr=oneletter(*ptr);
        o->length=0; //szemétgyűjtés NEM törli
        //printf("<s>");fflush(0);
    }
    else
    {
        BYTE *p=newBinary(len+1);
        memcpy(p,ptr,len*sizeof(BYTE));
        *(p+len)=(BYTE)0x00;
        o->ptr.binptr=p;
        o->length=-1; //szemétgyűjtés törli
    }
    o->color=COLOR_RESERVED;

    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    BINARYLEN(v)=len;
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
BYTE *binaryl(unsigned long len) //inicializálatlan binary new-val
{
//stack:   --- s
//return: binary pointer

    if( len>MAXBINLEN )
    {
        number(len);
        error_bln("binaryl",stack-1,1);
    }

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->ptr.binptr=newBinary(len+1);
    *(o->ptr.binptr+len)=(BYTE)0x00;
    o->length=-1;              //szemétgyűjtés törli
    o->color=COLOR_RESERVED;

    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    BINARYLEN(v)=len;
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
    return o->ptr.binptr;
}

//------------------------------------------------------------------------
void binaryx(const char *s) // e.g. CR/LF: x"0d0a"
{
    int len=strlen(s)/2;
    BYTE *p=binaryl(len);
    int i,j;
    for(i=0,j=0; i<len; i++,j+=2)
    {
        char buf[3];
        buf[0]=s[j];
        buf[1]=s[j+1];
        buf[2]=(char)0;
        *(p+i)=(BYTE)strtoul(buf,0,16);
    }
}

//------------------------------------------------------------------------
//compatibility
void binarys(BYTE const *ptr, unsigned int len){binarys(ptr,(unsigned long)len);}
BYTE *binaryl(unsigned int len){return binaryl((unsigned long)len);}
//------------------------------------------------------------------------
