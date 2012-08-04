
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

************************************************************************
function split(txt,sep:=if(valtype(txt)=="X",a",",","))
local wlist:={}, n:=1, i

    while( 0<(i:=at(sep,txt,n)) )
        aadd(wlist,txt[n..i-1])
        n:=i+1
    end

    //ha van maradék, azt még hozzáadjuk
    //a "" (üres) stringet nem adjuk hozzá

    if( len(txt)>=n )
        aadd(wlist,txt[n..])
    end
    return wlist


#ifdef NOTDEFINED

  Példák:

    ''      --> {}
    ' '     --> {' '}
    ':'     --> {''}
    ': '    --> {'',' '}
    'a'     --> {'a'}
    ':a'    --> {'','a'}  
    'a:'    --> {'a'}
    'a:b'   --> {'a','b'}
    'a:b:'  --> {'a','b'}
    'a::b'  --> {'a','','b'}

  Az utolsó határoló utáni részből csak akkor keletkezik tömbelem, ha az nem ''.
  Ugyanezért az '' (üres) stringből üres array keletkezik (nem pedig {''}).
  Ez kevesebb szemetet gyárt, mint a korábbi változat, a kimenet ugyanaz.


//a régebbi változat (elég körülményes)

function split(txt,sep)
local wlist:={}, n:=0, i
local emp:=if(valtype(txt)=="X",x"","")

    if(sep==NIL)
        sep:=","
    end
    
    while( n<len(txt) )

        txt:=substr(txt,n+1)    
    
        if( (i:=at(sep,txt))==0 )
            aadd(wlist, txt)
            n:=len(txt)
        elseif(i==1)
            aadd(wlist,emp)
            n:=1
        else
            aadd(wlist,substr(txt,1,i-1))
            n:=i
        end
    end

    return wlist

#endif


************************************************************************
