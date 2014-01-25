
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
#include <wctype.h>
#include <ctype.h>
#include <cccapi.h>

//------------------------------------------------------------------------
void _clp_isalnum(int argno)
{
    CCC_PROLOG("isalnum",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswalnum(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=isalnum(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_isalpha(int argno)
{
    CCC_PROLOG("isalpha",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswalpha(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=isalpha(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}
 
//------------------------------------------------------------------------
void _clp_isdigit(int argno)
{
    CCC_PROLOG("isdigit",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswdigit(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=isdigit(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_isxdigit(int argno)
{
    CCC_PROLOG("isxdigit",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswxdigit(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=isxdigit(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}
 
//------------------------------------------------------------------------
void _clp_isupper(int argno)
{
    CCC_PROLOG("isupper",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswupper(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=isupper(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_islower(int argno)
{
    CCC_PROLOG("islower",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswlower(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=islower(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_iscntrl(int argno)
{
    CCC_PROLOG("iscntrl",1);
    int flag=0;
    if( ISSTRING(1) )
    {
        if( 0<STRINGLEN(base) )
        {
            flag=iswcntrl(*STRINGPTR(base));
        }
    }
    else if( ISBINARY(1) )
    {
        if( 0<BINARYLEN(base) )
        {
            flag=iscntrl(*BINARYPTR(base));
        }
    }
    else
    {
        ARGERROR();
    }
    _retl(flag);
    CCC_EPILOG();
}

//------------------------------------------------------------------------
