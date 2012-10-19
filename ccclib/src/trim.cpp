
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

//------------------------------------------------------------------------
void _clp_ltrim(int argno)
{
    CCC_PROLOG("ltrim",1);
    if( ISSTRING(1) )
    {
        unsigned long len=_parclen(1);
        if( len<=0 )
        {
            _retc(L"");
        }
        else
        {
            CHAR *p=_parc(1);
            while( len>0 && *p==' ' )
            {
                ++p;
                --len;
            }
            _retclen(p,len);
        }
    }
    else if( ISBINARY(1) )
    {
        binarysize_t len=_parblen(1);
        if( len<=0 )
        {
            _retb("");
        }
        else
        {
            BYTE *p=_parb(1);
            while( len>0 && *p==' ' )
            {
                ++p;
                --len;
            }
            _retblen(p,len);
        }
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_rtrim(int argno)
{
    CCC_PROLOG("rtrim",1);
    if( ISSTRING(1) )
    {
        unsigned long len=_parclen(1);
        if( len<=0 )
        {
            _retc(L"");
        }
        else
        {
            CHAR *p=_parc(1);
            while( len>0 && *(p+len-1)==' ' )
            {
                --len;
            }
            _retclen(p,len);
        }
    }
    else if( ISBINARY(1) )
    {
        binarysize_t len=_parblen(1);
        if( len<=0 )
        {
            _retb("");
        }
        else
        {
            BYTE *p=_parb(1);
            while( len>0 && *(p+len-1)==' ' )
            {
                --len;
            }
            _retblen(p,len);
        }
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_alltrim(int argno)
{
    CCC_PROLOG("alltrim",1);
    if( ISSTRING(1) )
    {
        unsigned long len=_parclen(1);
        if( len<=0 )
        {
            _retc(L"");
        }
        else
        {
            CHAR *p=_parc(1);
            while( len>0 && *p==' ' )
            {
                ++p;
                --len;
            }
            while( len>0 && *(p+len-1)==' ' )
            {
                --len;
            }
            _retclen(p,len);
        }
    }
    else if( ISBINARY(1) )
    {
        binarysize_t len=_parblen(1);
        if( len<=0 )
        {
            _retb("");
        }
        else
        {
            BYTE *p=_parb(1);
            while( len>0 && *p==' ' )
            {
                ++p;
                --len;
            }
            while( len>0 && *(p+len-1)==' ' )
            {
                --len;
            }
            _retblen(p,len);
        }
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_trim(int argno)
{
    _clp_rtrim(argno);
}

//------------------------------------------------------------------------
