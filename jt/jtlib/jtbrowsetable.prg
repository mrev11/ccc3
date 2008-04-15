
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

****************************************************************************
//jtbrowsetable (segédlet táblaobjektumok browseolásához) 
****************************************************************************

#ifdef PROBLEMA
  Ennek a modulnak nehéz jó helyet találni, ui. ha belefordítjuk 
  libjtlib.so-ba, akkor az maga után húzza a táblaobjektum könyvtárat. 
  
  Lehetséges megoldások:
  
  1) Ahol nem akarjuk belinkelni a táblaobjektum könyvtárat, 
     ott linkelhetjük jtlib-et statikusan.

  2) Ahol nem akarjuk belinkelni a táblaobjektum könyvtárat, 
     ott definiálunk dummy tabSkip, tabGotop, stb. függvényeket.
     
  3) A jtbrowsetable osztályt kivesszük a könyvtárból,
     és forrásban terjesztjük.
  
  Sajnos egyik lehetőség sem igazán jó. Ha a táblaobjektum igazi
  objektum volna, akkor tabSkip helyén egy metódushívás állna, 
  és nem lépne fel ez a probléma.
#endif

****************************************************************************
class jtbrowsetable(jttable) 
    method  initialize
    method  xmlname         {|this|"jttable"}
    attrib  _table_
    method  table           {|this,t|if(t==NIL,this:_table_,this:_table_:=t)}

****************************************************************************
static function jtbrowsetable.initialize(this,t,l,b,r)  
    this:(jttable)initialize(t,l,b,r)
    this:skipblock:={|s|if(tabSkip(this:_table_,s),s,0)}
    this:gotopblock:={||tabGotop(this:_table_)}
    this:gobottomblock:={||tabGobottom(this:_table_)}
    this:saveposblock:={||tabPosition(this:_table_)}
    this:restposblock:={|p|tabGoto(this:_table_,p)}
    return this


****************************************************************************
 