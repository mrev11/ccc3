
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

#include <cccapi.h>

//----------------------------------------------------------------------------
void str2bin(VALUE *v)
{
    if( v->type==TYPE_STRING )
    {
        CHAR *p=STRINGPTR(v);
        unsigned long len=STRINGLEN(v);
        if( len>MAXSTRLEN )
        {
            error_cln("str2bin",v,1);
        }
        unsigned res=0;
        BYTE *u=wchar_to_utf8(p,len,&res);
        binarys(u,res);
        free(u);
        *v=*TOP();
        pop();
    }
}

//----------------------------------------------------------------------------
void bin2str(VALUE *v)
{
    if( v->type==TYPE_BINARY )
    {
        BYTE *u=BINARYPTR(v);
        unsigned long len=BINARYLEN(v);
        if( len>MAXBINLEN )
        {
            error_bln("bin2str",v,1);
        }
        unsigned res=0;
        CHAR *p=utf8_to_wchar(u,len,&res);
        strings(p,res);
        free(p);
        *v=*TOP();
        pop();
    }
}

//----------------------------------------------------------------------------
void _clp_str2bin(int argno)
{
    CCC_PROLOG("str2bin",1);
    if( ISSTRING(1) )
    {
        str2bin(base);
    }
    else if( ISBINARY(1) )
    {
        //OK
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_bin2str(int argno)
{
    CCC_PROLOG("bin2str",1);
    if( ISBINARY(1) )
    {
        bin2str(base);
    }
    else if( ISSTRING(1) )
    {
        //OK
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
