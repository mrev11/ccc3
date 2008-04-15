
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

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <cccapi.h>
#include <inttypes.h>

//Ezek 32 bites egeszekre mukodnek.
//Nem jo 64-bites longokat hasznalni, 
//mert azok abrazolasa double-kent nem pontos.

//----------------------------------------------------------------------------
void _clp_isbit(int argno) //CA-Tools
{
    CCC_PROLOG("isbit",2);

    c_uint32_t n=0;
    c_uint32_t m=1;

    switch(base->type)
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }
    if( !ISNIL(2) )
    {
        int b=_parni(2);
        m=((1<=b)&&(b<=32))?(1<<(b-1)):0;
    }
    _retl( n&m );
    CCC_EPILOG();
}    

//----------------------------------------------------------------------------
void _clp_setbit(int argno)  //CA-Tools 
{
    VALUE *base=stack-argno;
    push_call("setbit",base);

    c_uint32_t n=0;

    if( argno<1 )
    {
        ARGERROR();
    }
    switch(base->type)
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }

    int i;
    for( i=2; i<=argno; i++ )
    {
        int b=_parni(i);
        int m=((1<=b)&&(b<=32))?(1<<(b-1)):0;
        n|=m;
    }
    pop_call();
    stack=base;
    number(n);
}

//----------------------------------------------------------------------------
void _clp_clearbit(int argno)  //CA-Tools 
{
    VALUE *base=stack-argno;
    push_call("setbit",base);

    c_uint32_t n=0;

    if( argno<1 )
    {
        ARGERROR();
    }
    switch(base->type)
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }
    
    int i;
    for( i=2; i<=argno; i++ )
    {
        int b=_parni(i);
        int m=((1<=b)&&(b<=32))?(1<<(b-1)):0;
        n&=~m;
    }
    pop_call();
    stack=base;
    number(n);
}
 
//----------------------------------------------------------------------------
void _clp_numand(int argno)  //CA-Tools 
{
    VALUE *base=stack-argno;
    push_call("numand",base);

    c_uint32_t n=0;

    if( argno<2 )
    {
        ARGERROR();
    }
    switch( PARTYPE(1) )
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }

    int i;
    for( i=2; i<=argno; i++ )
    {
        c_uint32_t m=0;
        switch( PARTYPE(i) )
        {
            case TYPE_NUMBER: m=PARNU(i); break;
            case TYPE_STRING: m=wcstoul(CHRPTR(i),0,16); break;
            case TYPE_BINARY: m=strtoul(BINPTR(i),0,16); break;
            default: ARGERROR();
        }
        n&=m;
    }
    pop_call();
    stack=base;
    number(n);
}

//----------------------------------------------------------------------------
void _clp_numor(int argno)  //CA-Tools 
{
    VALUE *base=stack-argno;
    push_call("numor",base);

    c_uint32_t n=0;

    if( argno<2 )
    {
        ARGERROR();
    }
    switch( PARTYPE(1) )
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }

    int i;
    for( i=2; i<=argno; i++ )
    {
        c_uint32_t m=0;
        switch( PARTYPE(i) )
        {
            case TYPE_NUMBER: m=PARNU(i); break;
            case TYPE_STRING: m=wcstoul(CHRPTR(i),0,16); break;
            case TYPE_BINARY: m=strtoul(BINPTR(i),0,16); break;
            default: ARGERROR();
        }
        n|=m;
    }
    pop_call();
    stack=base;
    number(n);
}

//----------------------------------------------------------------------------
void _clp_numxor(int argno)  //CA-Tools 
{
    CCC_PROLOG("numxor",2);
    c_uint32_t n=0;
    c_uint32_t m=0;
    switch( PARTYPE(1) )
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }
    switch( PARTYPE(2) )
    {
        case TYPE_NUMBER: m=PARNU(2); break;
        case TYPE_STRING: m=wcstoul(CHRPTR(2),0,16); break;
        case TYPE_BINARY: m=strtoul(BINPTR(2),0,16); break;
        default: ARGERROR();
    }
    _retnd( n^m );
    CCC_EPILOG();
}
 
//----------------------------------------------------------------------------
void _clp_numnot(int argno)  //CA-Tools 
{
    CCC_PROLOG("numnot",1);
    c_uint32_t n=0;
    switch( PARTYPE(1) )
    {
        case TYPE_NUMBER: n=PARNU(1); break;
        case TYPE_STRING: n=wcstoul(CHRPTR(1),0,16); break;
        case TYPE_BINARY: n=strtoul(BINPTR(1),0,16); break;
        default: ARGERROR();
    }
    _retnd( ~n );
    CCC_EPILOG();
}
 
//----------------------------------------------------------------------------
