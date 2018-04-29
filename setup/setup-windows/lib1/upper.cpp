
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

#include <ctype.h>
#include <wctype.h>
#include <cccapi.h>
 
//------------------------------------------------------------------------
void _clp_lower(int argno)
{
    CCC_PROLOG("lower",1);
    if(ISSTRING(1))
    {
        CHAR *s=_parc(1);
        unsigned long len=_parclen(1);
        CHAR *p=stringl(len);
        unsigned long i;
        for( i=0; i<len; i++)
        {
            p[i]=towlower(s[i]);
        }
    }
    else if(ISBINARY(1))
    {
        char *s=_parb(1);
        unsigned long len=_parblen(1);
        char *p=binaryl(len);
        unsigned long i;
        for( i=0; i<len; i++)
        {
            p[i]=tolower(s[i]);
        }
    }
    else
    {
        ARGERROR();
    }
    _rettop();
    CCC_EPILOG();
}
 
//------------------------------------------------------------------------
void _clp_upper(int argno)
{
    CCC_PROLOG("upper",1);
    if(ISSTRING(1))
    {
        CHAR *s=_parc(1);
        unsigned long len=_parclen(1);
        CHAR *p=stringl(len);
        unsigned long i;
        for( i=0; i<len; i++)
        {
            p[i]=towupper(s[i]);
        }
    }
    else if(ISBINARY(1))
    {
        char *s=_parb(1);
        unsigned long len=_parblen(1);
        char *p=binaryl(len);
        unsigned long i;
        for( i=0; i<len; i++)
        {
            p[i]=toupper(s[i]);
        }
    }
    else
    {
        ARGERROR();
    }
    _rettop();
    CCC_EPILOG();
}
 
//------------------------------------------------------------------------
