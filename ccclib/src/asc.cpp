
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
#include <string.h>
#include <ctype.h>
#include <cccapi.h>

//------------------------------------------------------------------------
void _clp_asc(int argno)
{
    unsigned c=0;
    VALUE *base=stack-argno;
    if( argno<1 )
    {
        error_arg("asc",base,argno);
    }
    else if( base->type==TYPE_BINARY )
    {
        c=(unsigned)*BINPTR(1);
    }
    else if( base->type==TYPE_STRING )
    {
        c=(unsigned)*CHRPTR(1);
    }
    else
    {
        error_arg("asc",base,argno);
    }
    stack=base;
    number(c);
}

//------------------------------------------------------------------------
void _clp_chr(int argno)
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_NUMBER) )
    {
        error_arg("chr",base,argno);
    }
    int c=D2UINT(base->data.number);
    stack=base;
    *stringl(1)=c;
}


//------------------------------------------------------------------------
void _clp_bin(int argno)
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_NUMBER) )
    {
        error_arg("bin",base,argno);
    }
    int c=D2INT(base->data.number);
    stack=base;
    *binaryl(1)=c;
}

//------------------------------------------------------------------------
