
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
void _clp_substr(int argno)
{
    CCC_PROLOG("substr",3);
    
    if( ISSTRING(1) )
    {
        CHAR *s=_parc(1);
        int len=_parclen(1);
        int beg=_parni(2);
        if( beg<1 )
        {
            // Inkompatibilitás,
            // a Clipper beg==0-ra is előlről indul,
            // holott a 0. pozíció nincs értelmezve,
            // mi beg==0-ra ""-t adunk.

            beg=(beg+len<0) ? 1 : len+beg+1;
        }
        int cnt=len-beg+1;
        if( !ISNIL(3) )
        {
            cnt=min(cnt,_parni(3));
        }
        if( cnt<=0 )
        {
            _retc(L"");
        }
        else
        {
            _retclen(s+beg-1,cnt);
        }
    }
    else
    {
        BYTE *s=_parb(1);
        int len=_parblen(1);
        int beg=_parni(2);
        if( beg<1 )
        {
            beg=(beg+len<0) ? 1 : len+beg+1;
        }
        int cnt=len-beg+1;
        if( !ISNIL(3) )
        {
            cnt=min(cnt,_parni(3));
        }
        if( cnt<=0 )
        {
            _retb("");
        }
        else
        {
            _retblen(s+beg-1,cnt);
        }
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_left(int argno)
{
    CCC_PROLOG("left",2);
    if( ISSTRING(1) )
    {
        CHAR *s=_parc(1);
        int len=_parclen(1);
        int cnt=min(len,_parni(2));
        
        if(cnt<=0)
        {
            _retc(L"");
        }
        else
        {
            _retclen(s,cnt);
        }
    }
    else
    {
        BYTE *s=_parb(1);
        int len=_parblen(1);
        int cnt=min(len,_parni(2));
        
        if(cnt<=0)
        {
            _retb("");
        }
        else
        {
            _retblen(s,cnt);
        }
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_right(int argno)
{
    CCC_PROLOG("right",2);
    if( ISSTRING(1) )
    {
        CHAR *s=_parc(1);
        int len=_parclen(1);
        int cnt=min(len,_parni(2));
    
        if(cnt<=0)
        {
            _retc(L"");
        }
        else
        {
            _retclen(s+len-cnt,cnt);
        }
    }
    else
    {
        BYTE *s=_parb(1);
        int len=_parblen(1);
        int cnt=min(len,_parni(2));
    
        if(cnt<=0)
        {
            _retb("");
        }
        else
        {
            _retblen(s+len-cnt,cnt);
        }
    }
    CCC_EPILOG();
}    

//------------------------------------------------------------------------
