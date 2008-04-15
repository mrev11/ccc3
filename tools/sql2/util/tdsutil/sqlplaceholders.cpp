
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
#include <cccapi.h>

// egy ilyen stringből "xx:1yy:2zzz" 
// csinál egy ilyen arrayt  {"xx",1,"yy",2,"zz"}

namespace _nsp_tdsutil {


void _clp_sqlplaceholders(int argno)
{
    CCC_PROLOG("sqlplaceholders",1);

    CHAR *text=_parc(1);
    int  tlen=_parclen(1);
    int count=0;
    
    
    int i=0,q=0,x0=0;
    while( i<tlen )
    {
        CHAR c=text[i];

        if( c=='\'' )
        {
            q=q?0:1;
            i++;
        }
        else if( (c==':') && (q==0) && isdigit(text[i+1]) )
        {
            strings(text+x0,i-x0);
            count++;

            i++;
            char buf[8]; int k=0;
            while( (i<tlen) && (k<7) && isdigit(text[i]) )
            {
                buf[k++]=text[i++];
            }
            buf[k]=0;
            int ph=atoi(buf);
            number(ph);
            count++;

            x0=i;
        }
        else
        {
            i++;
        }
    }

    strings(text+x0,i-x0);
    count++;
    array(count);
    _rettop();

    CCC_EPILOG();
}

}//namespace

