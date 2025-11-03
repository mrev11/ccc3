
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

#ifdef _TERMUX_
#define  aligned_alloc  memalign
// termuxon nincs  aligned_alloc()
// netbsd-n nincs  memalign()
// ugyanazt csinaljak
#endif

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
void string(CHAR const *ptr) //uj peldany ramutatassal (new nelkul)
{
//stack:   --- s

    VALUE v;
    v.type=TYPE_STRING;
    v.data.string.len=wcslen(ptr);
    oref_new(&v,(void*)ptr,0); // PUSH (szemetgyujtes nem torli)
}

//------------------------------------------------------------------------
void stringn(CHAR const *ptr) //uj peldany masolassal (new)
{
//stack:   --- s

    unsigned long len=wcslen(ptr);
    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("stringn",stack-1,1);
    }

    CHAR *chrptr=0;
    int length=0;
    if( (len<=1) && (*ptr<256) )
    {
        chrptr=oneletter(*ptr);
        length=0; //szemetgyujtes NEM torli
        //printf("<n>");fflush(0);
    }
    else
    {
        chrptr=newChar(len+1);
        wmemcpy(chrptr,ptr,len+1);
        length=-1; //szemetgyujtes torli
    }

    VALUE v;
    v.type=TYPE_STRING;
    v.data.string.len=len;
    oref_new(&v,chrptr,length); // PUSH
}

void stringnb(char const *ptr) //uj string bytearraybol
{
    unsigned reslen=0;
    CHAR *p=utf8_to_wchar(ptr,strlen(ptr),&reslen);
    strings(p,reslen);
    free(p);
}

//------------------------------------------------------------------------
void strings(CHAR const *ptr, unsigned long len) //substring kimasolasa new-val
{
//stack:   --- s

    if( len==0 )
    {
        ptr=L"";
    }

    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("strings",stack-1,1);
    }

    CHAR *chrptr=0;
    int length=0;
    if( (len<=1) && (*ptr<256) )
    {
        chrptr=oneletter(*ptr);
        length=0; //szemetgyujtes NEM torli
        //printf("<S>");fflush(0);
    }
    else
    {
        chrptr=newChar(len+1);
        wmemcpy(chrptr,ptr,len);
        *(chrptr+len)=(CHAR)0x00;
        length=-1; //szemetgyujtes torli
    }

    VALUE v;
    v.type=TYPE_STRING;
    v.data.string.len=len;

    oref_new(&v,chrptr,length); // PUSH
}

void stringsb(char const *ptr, unsigned long len) //uj string bytearraybol
{
    unsigned reslen=0;
    CHAR *p=utf8_to_wchar(ptr,len,&reslen);
    strings(p,reslen);
    free(p);
}

//------------------------------------------------------------------------
CHAR *stringl(unsigned long len) //inicializalatlan string new-val
{
//stack:   --- s
//return: string pointer

    if(len>MAXSTRLEN)
    {
        number(len);
        error_cln("stringl",stack-1,1);
    }

    CHAR *chrptr=newChar(len+1);
    *(chrptr+len)=(CHAR)0x00;

    VALUE v;
    v.type=TYPE_STRING;
    v.data.string.len=len;

    oref_new(&v,chrptr,-1); // PUSH (szemetgyujtes torli)
    return chrptr;
}

//------------------------------------------------------------------------
//compatibility
void strings(CHAR const *ptr, unsigned int len){ strings(ptr,(unsigned long)len); }
void stringsb(char const *ptr, unsigned len){ stringsb(ptr,(unsigned long)len); }
CHAR *stringl(unsigned int len){ return stringl((unsigned long)len); }
//------------------------------------------------------------------------
