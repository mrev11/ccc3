
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
local wlist:={}, n:=1, i, tail
    while( 0<(i:=at(sep,txt,n)) )
        aadd(wlist,txt[n..i-1])
        n:=i+1
    end
    tail:=txt[n..]
    if( !tail::empty  )
        aadd(wlist,tail)
    end
    return wlist


#ifdef NOTDEFINED

  Példák:

    ''      --> {}
    ':'     --> {''}
    'a'     --> {'a'}
    ':a'    --> {'','a'}  
    'a:'    --> {'a'}
    'a:b'   --> {'a','b'}
    'a:b:'  --> {'a','b'}
    'a::b'  --> {'a','','b'}

  Az utolsó határoló után csak akkor keletkezik tömbelem, ha az nem üres.
  Ugyanezért az üres stringből üres array keletkezik (nem pedig {''}).
  Ez kevesebb stringet gyárt, mint a korábbi változat, a kimenet ugyanaz.
#endif


************************************************************************
