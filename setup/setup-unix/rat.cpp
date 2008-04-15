
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
#include <wchar.h>
#include <string.h>
#include <cccapi.h>

//----------------------------------------------------------------------------
void _clp_rat(int argno)
{
    CCC_PROLOG("rat",2);

    if( ISSTRING(2) )
    {
        bin2str(base);

        unsigned slen=_parclen(1); //ezt keressuk
        unsigned tlen=_parclen(2); //ebben keresunk

        if( slen==0 || tlen==0 || slen>tlen )
        {
            _retni(0);
        }
        else
        {
            CHAR *sp=_parc(1); //ezt keressuk
            CHAR *tp=_parc(2); //ebben keresunk
            long i;
            for( i=tlen-slen; i>=0; i-- )
            {
                 if( 0==wmemcmp(tp+i,sp,slen) )
                 {
                     break;
                 }
            }
            _retni(i>=0?i+1:0);
        }
    }
    else if( ISBINARY(2) )
    {
        str2bin(base);

        unsigned slen=_parblen(1); //ezt keressuk
        unsigned tlen=_parblen(2); //ebben keresunk

        if( slen==0 || tlen==0 || slen>tlen )
        {
            _retni(0);
        }
        else
        {
            char *sp=_parb(1); //ezt keressuk
            char *tp=_parb(2); //ebben keresunk
            long i;
            for( i=tlen-slen; i>=0; i-- )
            {
                 if( 0==memcmp(tp+i,sp,slen) )
                 {
                     break;
                 }
            }
            _retni(i>=0?i+1:0);
        }
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
