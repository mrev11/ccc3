
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

namespace _nsp_tdsutil{

//-----------------------------------------------------------------------------
void _clp_splitpar(int argno)
{
    //space-ek szerint darabol
    //a kiegyensúlyozott zárójelpárokon átmegy

    CCC_PROLOG("splitpar",1);

    CHAR *txt=_parc(1);
    int txtlen=_parclen(1);

                    //     xx(xx x(x) )xxx xx
    int state=0;    // 0000111111111111111011
    int par=0;      // 0000001111122110000000
                    //     ^             ^

    int count=0;
    int pleft=0,pright=0;
    int i1=0;

    for( int i=0; i<=txtlen; i++ )
    {
        CHAR c=(i<txtlen)?txt[i]:' ';

        if( c==' ' )
        {
            if( state==1 && par==0 )
            {
                state=0; //vége
                if( pleft==txt[i1] )
                {
                    strings(txt+i1+1,i-i1-2); //leszedi a szélét
                }
                else
                {
                    strings(txt+i1,i-i1);
                }
                count++;
                pleft=0;
                pright=0;
            }
        }
        else
        {
            if( state==0 )
            {
                state=1; //kezdődik
                i1=i;
            }
            
            if( par==0 )
            {
                if(c=='('){pleft='(';pright=')';par++;}
                if(c=='{'){pleft='{';pright='}';par++;}
                if(c=='['){pleft='[';pright=']';par++;}
            }
            else if( c==pleft )  par++;
            else if( c==pright ) par--;
        }
    }
    
    array(count);
    _rettop();
    CCC_EPILOG();
}
} //namepsace

//-----------------------------------------------------------------------------
