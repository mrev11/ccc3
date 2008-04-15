
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

#include <string.h>
#include <cccapi.h>

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
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=strlen((char*)ptr);
    v->type=TYPE_BINARY;
 
    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
void binaryn(BYTE const *ptr) //új példány másolással (new)
{
//stack:   --- s

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    int len=strlen((char*)ptr);
    BYTE *p=newBinary(len+1);
    memcpy(p,ptr,(len+1)*sizeof(BYTE));
    o->ptr.binptr=p;
    o->length=-1;              //szemétgyűjtés törli
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=len;
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
void binarys(BYTE const *ptr, unsigned int len) //substring kimásolása new-val
{
//stack:   --- s

    VARTAB_LOCK();

    OREF *o=oref_new(); 
    BYTE *p=newBinary(len+1);
    memcpy(p,ptr,len*sizeof(BYTE));
    *(p+len)=(BYTE)0x00;
    o->ptr.binptr=p;
    o->length=-1;              //szemétgyűjtés törli 
    o->next=NEXT_RESERVED;
  
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=len;
    v->type=TYPE_BINARY;

    VARTAB_UNLOCK();
}

//------------------------------------------------------------------------
BYTE *binaryl(unsigned int len) //inicializálatlan binary new-val
{
//stack:   --- s
//return: binary pointer

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->ptr.binptr=newBinary(len+1);
    *(o->ptr.binptr+len)=(BYTE)0x00; 
    o->length=-1;              //szemétgyűjtés törli  
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.binary.oref=o;
    v->data.binary.len=len;
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
