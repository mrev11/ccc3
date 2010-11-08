
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
#include <wchar.h>
#include <cccapi.h>

//----------------------------------------------------------------------------
void _clp_padr(int argno)
{
    CCC_PROLOG("padr",3);

    if( ISDATE(1) )
    {
        push_symbol(base);
        _clp_dtoc(1);
        *base=*TOP();
        POP();
    }
    else if( ISNUMBER(1) )
    {
        push_symbol(base);
        _clp_str(1);
        _clp_alltrim(1);
        *base=*TOP();
        POP();
    }
    
    if( ISSTRING(1) )
    {
        CHAR *str=_parc(1);
        unsigned long len=_parclen(1);
        unsigned plen=max(0,_parni(2));
        CHAR cfill=ISNIL(3)?' ':*_parc(3);
        CHAR *p=stringl(plen);

        if( len==0 )
        {
            wmemset(p,cfill,plen);
        }
        else if( len<plen )
        {
            wmemcpy(p,str,len);
            wmemset(p+len,cfill,plen-len);
        }
        else
        {
            wmemcpy(p,str,plen);
        }
    }
    else if( ISBINARY(1) )
    {
        char *str=_parb(1);
        unsigned long len=_parblen(1);
        unsigned plen=max(0,_parni(2));
        char cfill=ISNIL(3)?' ':*_parb(3);
        char *p=binaryl(plen);

        if( len==0 )
        {
            memset(p,cfill,plen);
        }
        else if( len<plen )
        {
            memcpy(p,str,len);
            memset(p+len,cfill,plen-len);
        }
        else
        {
            memcpy(p,str,plen);
        }
    }
    else
    {
        ARGERROR();
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_pad(int argno)
{
    _clp_padr(argno);
}

//----------------------------------------------------------------------------
void _clp_padl(int argno)
{
    CCC_PROLOG("padl",3);

    if( ISDATE(1) )
    {
        push_symbol(base);
        _clp_dtoc(1);
        *base=*TOP();
        POP();
    }
    else if( ISNUMBER(1) )
    {
        push_symbol(base);
        _clp_str(1);
        _clp_alltrim(1);
        *base=*TOP();
        POP();
    }
    
    if( ISSTRING(1) )
    {
        CHAR *str=_parc(1);
        unsigned long len=_parclen(1);
        unsigned plen=max(0,_parni(2));
        CHAR cfill=ISNIL(3)?' ':*_parc(3);
        CHAR *p=stringl(plen);

        if( len==0 )
        {
            wmemset(p,cfill,plen);
        }
        else if( len<plen )
        {
            wmemset(p,cfill,plen-len);
            wmemcpy(p+plen-len,str,len);
        }
        else
        {
            wmemcpy(p,str,plen);
        }
    }
    else if( ISBINARY(1) )
    {
        char *str=_parb(1);
        unsigned long len=_parblen(1);
        unsigned plen=max(0,_parni(2));
        char cfill=ISNIL(3)?' ':*_parb(3);
        char *p=binaryl(plen);

        if( len==0 )
        {
            memset(p,cfill,plen);
        }
        else if( len<plen )
        {
            memset(p,cfill,plen-len);
            memcpy(p+plen-len,str,len);
        }
        else
        {
            memcpy(p,str,plen);
        }
    }
    else
    {
        ARGERROR();
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_padc(int argno)
{
    CCC_PROLOG("padc",3);

    if( ISDATE(1) )
    {
        push_symbol(base);
        _clp_dtoc(1);
        *base=*TOP();
        POP();
    }
    else if( ISNUMBER(1) )
    {
        push_symbol(base);
        _clp_str(1);
        _clp_alltrim(1);
        *base=*TOP();
        POP();
    }
    
    if( ISSTRING(1) )
    {
        CHAR *str=_parc(1);
        unsigned long len=_parclen(1);
        unsigned plen=max(0,_parni(2));
        CHAR cfill=ISNIL(3)?' ':*_parc(3);
        CHAR *p=stringl(plen);

        if( len==0 )
        {
            wmemset(p,cfill,plen);
        }
        else if( len<plen )
        {
            int l1=(plen-len)/2;
            int l2=plen-len-l1;
            wmemset(p,cfill,l1);
            wmemcpy(p+l1,str,len);
            wmemset(p+l1+len,cfill,l2);
        }
        else
        {
            wmemcpy(p,str,plen);
        }
    }
    else if( ISBINARY(1) )
    {
        char *str=_parb(1);
        unsigned long len=_parblen(1);
        unsigned plen=max(0,_parni(2));
        char cfill=ISNIL(3)?' ':*_parb(3);
        char *p=binaryl(plen);

        if( len==0 )
        {
            memset(p,cfill,plen);
        }
        else if( len<plen )
        {
            int l1=(plen-len)/2;
            int l2=plen-len-l1;
            memset(p,cfill,l1);
            memcpy(p+l1,str,len);
            memset(p+l1+len,cfill,l2);
        }
        else
        {
            memcpy(p,str,plen);
        }
    }
    else
    {
        ARGERROR();
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
