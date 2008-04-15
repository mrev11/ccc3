
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
        CHAR *s=_parc(1);           //ebben helyettesitunk
        unsigned slen=_parclen(1);  //ilyen hosszuban helyettesitunk
        unsigned nsta=_parni(2);    //innen kezdve
        unsigned ndel=_parni(3);    //ennyit vagunk ki
        CHAR *x=_parc(4);           //ezt rakjuk be
        unsigned xlen=_parclen(4);  //ennyit rakunk be

        if( nsta==0 || nsta>slen )
        {
            ARGERROR();
        }
    
        ndel=min(ndel,slen-nsta+1);
        unsigned nlen=slen-ndel+xlen;
    
        if( nlen > MAXSTRLEN )
        {
            error_cln("stuff",base,4);
        }
    
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
        char *s=_parb(1);           //ebben helyettesitunk
        unsigned slen=_parblen(1);  //ilyen hosszuban helyettesitunk
        unsigned nsta=_parni(2);    //innen kezdve
        unsigned ndel=_parni(3);    //ennyit vagunk ki
        char *x=_parb(4);           //ezt rakjuk be
        unsigned xlen=_parblen(4);  //ennyit rakunk be

        if( nsta==0 || nsta>slen )
        {
            ARGERROR();
            nsta=1;
        }
    
        ndel=min(ndel,slen-nsta+1);
        unsigned nlen=slen-ndel+xlen;
    
        if( nlen > MAXBINLEN )
        {
            error_cln("stuff",base,4);
        }
    
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

