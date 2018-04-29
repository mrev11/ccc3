
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
#include <wchar.h>
#include <cccapi.h>

//----------------------------------------------------------------------------
void _clp_stuff(int argno)
{
    CCC_PROLOG("stuff",4);
    if( ISSTRING(1) )
    {
        CHAR *s=_parc(1);                //ebben helyettesitunk
        unsigned long slen=_parclen(1);  //ilyen hosszuban helyettesitunk
        double dsta=_parnd(2);           //innen kezdve
        unsigned long nsta=dsta<0?0:D2ULONG(dsta);
        double ddel=_parnd(3);           //ennyit vagunk ki
        unsigned long ndel=ddel<0?0:D2ULONG(ddel);
        CHAR *x=_parc(4);                //ezt rakjuk be
        unsigned long xlen=_parclen(4);  //ennyit rakunk be

        if( slen > MAXSTRLEN )
        {
            error_cln("stuff",base,4);
        }

        if( nsta==0 || nsta>slen+1 )
        {
            ARGERROR();
        }
    
        ndel=min(ndel,slen-nsta+1);
        unsigned long nlen=slen-ndel+xlen;
    
        CHAR *p=stringl(nlen);  // uj string a stacken
    
        if( nsta>1 )
        {
            wmemcpy(p,s,nsta-1);
            p+=(nsta-1);
        }

        if( xlen>0 )
        {
            wmemcpy(p,x,xlen);
            p+=(xlen);
        }

        if( slen>nsta-1+ndel )
        {
            wmemcpy(p,s+nsta-1+ndel,slen-(nsta-1+ndel));
            p+=(slen-(nsta-1+ndel));
        }
    }
    else if( ISBINARY(1) )
    {
        char *s=_parb(1);                //ebben helyettesitunk
        unsigned long slen=_parblen(1);  //ilyen hosszuban helyettesitunk
        double dsta=_parnd(2);           //innen kezdve
        unsigned long nsta=dsta<0?0:D2ULONG(dsta);
        double ddel=_parnd(3);           //ennyit vagunk ki
        unsigned long ndel=ddel<0?0:D2ULONG(ddel);
        char *x=_parb(4);                //ezt rakjuk be
        unsigned long xlen=_parblen(4);  //ennyit rakunk be

        if( slen>MAXBINLEN )
        {
            error_bln("stuff",base,4);
        }

        if( nsta==0 || nsta>slen+1 )
        {
            ARGERROR();
        }
    
        ndel=min(ndel,slen-nsta+1);
        unsigned long nlen=slen-ndel+xlen;
    
        char *p=binaryl(nlen);  // uj string a stacken
    
        if( nsta>1 )
        {
            memcpy(p,s,nsta-1);
            p+=(nsta-1);
        }

        if( xlen>0 )
        {
            memcpy(p,x,xlen);
            p+=(xlen);
        }

        if( slen>nsta-1+ndel )
        {
            memcpy(p,s+nsta-1+ndel,slen-(nsta-1+ndel));
            p+=(slen-(nsta-1+ndel));
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

