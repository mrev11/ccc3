
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
        unsigned long len=_parclen(1);
        unsigned long beg;
        double dbeg=_parnd(2);
        if( dbeg>0 )
        {
            beg=D2ULONG(dbeg);
        }
        else
        {
            beg=D2ULONG(-dbeg);
            if( beg>=len )
            {
                beg=1;
            }
            else
            {
                beg=len-beg+1;
            }
        }
        unsigned long cnt;
        if( beg<1 || len<beg )
        {
            cnt=0;
        }
        else if( ISNIL(3) )
        {
            cnt=len-beg+1;
        }
        else
        {
            double dcnt=_parnd(3);
            cnt=dcnt<0?0:min(D2ULONG(dcnt),len-beg+1);
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
    else  //binary
    {
        BYTE *s=_parb(1);
        unsigned long len=_parblen(1);
        unsigned long beg;
        double dbeg=_parnd(2);
        if( dbeg>0 )
        {
            beg=D2ULONG(dbeg);
        }
        else
        {
            beg=D2ULONG(-dbeg);
            if( beg>=len )
            {
                beg=1;
            }
            else
            {
                beg=len-beg+1;
            }
        }

        unsigned long cnt;
        if( beg<1 || len<beg )
        {
            cnt=0;
        }
        else if( ISNIL(3) )
        {
            cnt=len-beg+1;
        }
        else
        {
            double dcnt=_parnd(3);
            cnt=dcnt<0?0:min(D2ULONG(dcnt),len-beg+1);
        }

        if( cnt==0 )
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
        unsigned long len=_parclen(1);
        int cnt=minUS(len,_parni(2));
        
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
        unsigned long len=_parblen(1);
        int cnt=minUS(len,_parni(2)); //min(unsigned,signed)
        
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
        unsigned long len=_parclen(1);
        int cnt=minUS(len,_parni(2));
    
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
        unsigned long len=_parblen(1);
        int cnt=minUS(len,_parni(2));  //min(unsigned,signed)
    
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
