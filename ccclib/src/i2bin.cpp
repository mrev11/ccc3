
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

#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <cccapi.h>

//------------------------------------------------------------------------
void _clp_i2bin(int argno) //signed 16-bit
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_NUMBER) )
    {
        error_arg("i2bin",base,argno);
    }
    c_int16_t i=(c_int16_t)base->data.number;
    stack=base;
    binarys((BYTE*)&i,sizeof(c_int16_t)); 
}

//------------------------------------------------------------------------
void _clp_bin2i(int argno)  //signed 16-bit
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_BINARY) || (BINARYLEN(base)<sizeof(c_int16_t)) )
    {
        error_arg("bin2i",base,argno);
    }
    c_int16_t i=*(c_int16_t*)BINARYPTR(base);
    stack=base;
    number(i);
}

//------------------------------------------------------------------------
void _clp_bin2w(int argno)  //unsigned 16-bit
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_BINARY) || (BINARYLEN(base)<sizeof(c_uint16_t)) )
    {
        error_arg("bin2w",base,argno);
    }
    c_uint16_t w=*(c_uint16_t*)BINARYPTR(base);
    stack=base;
    number(w);
}

//------------------------------------------------------------------------
void _clp_l2bin(int argno) //signed 32-bit
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_NUMBER) )
    {
        error_arg("l2bin",base,argno);
    }
    c_int32_t l=D2INT(base->data.number);
    stack=base;
    binarys((BYTE*)&l,sizeof(c_int32_t)); 
}

//------------------------------------------------------------------------
void _clp_bin2l(int argno) //signed 32-bit
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_BINARY) || (BINARYLEN(base)<sizeof(c_int32_t)) )
    {
        error_arg("bin2l",base,argno);
    }
    c_int32_t l=*(c_int32_t*)BINARYPTR(base);
    stack=base;
    number(l);
}

//------------------------------------------------------------------------
void _clp_f2bin(int argno)
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_NUMBER) )
    {
        error_arg("f2bin",base,argno);
    }
    double f=base->data.number;
    stack=base;
    binarys((BYTE*)&f,sizeof(double));
}

//------------------------------------------------------------------------
void _clp_bin2f(int argno)
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_BINARY) || (BINARYLEN(base)<sizeof(double)) )
    {
        error_arg("bin2f",base,argno);
    }
    double f=*(double*)BINARYPTR(base);
    stack=base;
    number(f);
}

//------------------------------------------------------------------------
void _clp_l2hex(int argno)
{
    VALUE *base=stack-argno;
    unsigned long long x=0;
    if( argno<1 )
    {
        error_arg("l2hex",base,argno);
    }
    else if( base->type==TYPE_NUMBER )
    {
        x=D2ULONG(base->data.number);
    }
    else if( base->type==TYPE_POINTER )
    {
        x=(unsigned long long)base->data.pointer;
    }
    else
    {
        error_arg("l2hex",base,argno);
    }
    char buffer[32];
    sprintf(buffer,"%llx",x);
    stack=base;
    stringnb(buffer); 
}


//------------------------------------------------------------------------
void _clp_hex2l(int argno)
{
    VALUE *base=stack-argno;
    if( (argno<1) || (base->type!=TYPE_STRING) )
    {
        error_arg("hex2l",base,argno);
    }
    unsigned long l=wcstoul(STRINGPTR(base),0,16);
    stack=base;
    number(l);
}


//------------------------------------------------------------------------
void _clp_l2oct(int argno)
{
    CCC_PROLOG("l2oct",1);
    int mode=_parni(1);
    char buffer[32];
    sprintf(buffer,"%o",mode);
    _retcb( buffer );  
    CCC_EPILOG();
} 

//------------------------------------------------------------------------
void _clp_oct2l(int argno)
{
    CCC_PROLOG("oct2l",1);
    if( (argno<1) || (base->type!=TYPE_STRING) )
    {
        error_arg("oct2l",base,argno);
    }
    unsigned long mode=wcstoul(STRINGPTR(base),0,8);
    stack=base;
    number(mode);
    CCC_EPILOG();
} 

//------------------------------------------------------------------------

