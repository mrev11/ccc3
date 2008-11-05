
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

#ifdef NOT_DEFINED

  Volt már szó róla kb. egy éve, hogy talán érdemes volna
  megcsinálni a postfix függvényhívást. Hát itt van.
  
    expr ::= expr : : func ( parlist )
    expr ::= expr : : func         
  
  A fenti két új szabályt felvettem a nyelvtanba.
  
    x::func(a,b,c)  ->  func(x,a,b,c)
    x::func         ->  func(x)
  
  A postfix függvényhívás operátora a '::'.
  Egy-karakteres operátor nem lehetséges, mert már minden
  szóbajöhető karakter foglalt. De nem olyan rossz a '::',
  hasonlít ui. a metódushíváshoz, de mégis megkülönböztethető.
  
  A ::-tól balra levő akármilyen kifejezés (precedencia!)
  lesz a ::-tól jobbra álló akármilyen (pl. névtérből vett) 
  függvény első paramétere, miközben az esetleges többi
  paraméter eggyel hátrébb csúszik. (Mintha minden függvény
  az első argumentumának a metódusa volna.)

  Egyelőre csak a nálam levő kísérleti CCC-ben van benne.
  Várom az észrevételeket. Ha nincs kifogásotok ellene,
  akkor berakom az éles repóba (a CCC2-be és CCC3-ba is).
  
  Ellene szól:
    szokatlan új szintaktika
    hosszabb kód
    összetéveszhető a metódushívással
    precedencia
    
  Mellette szól:
    balról jobbra olvasható kód
    kevesebb távoli zárójelpár
  
  Az itt következő programmal teszteltem, 
  nálatok egyelőre nem fordul le,
  az eredmény a log-ban nézhető meg.
#endif


#define FNAME1(x) strtran(atail(split(x,dirsep())),".ogg","")
#define FNAME2(x) (x)::split(dirsep())::atail::strtran(".ogg","")

#define FORMAT1(x) padl(alltrim(str(x)),10,"0")
#define FORMAT2(x) (x)::str::alltrim::padl(10,"0")

***************************************************************************
function main(*)

local oggfile:="/home/vermes/zene/wagner/walkur_1.ogg"

local blk1:={|x|FORMAT1(x)}
local blk2:={|x|FORMAT2(x)}

    ? FNAME1(oggfile)
    ? FNAME2(oggfile)
    ? eval(blk1,123)
    ? eval(blk2,123)
    ? 

    ? hohoNew("HoHo"):padr(10,"x"):upper:cdata //metódushívások!
    ?

    NIL::params(1,2,3)
    params(*)
    params(*,1,*)
    NIL::params(*)
    ?

    //preprocesszor!
    //precedencia!
    ? "1"+2::str()::alltrim()
    ? (1+2)::str()::alltrim()
    ?

***************************************************************************
static function params(*)
    ? "params",{*}

***************************************************************************
class hoho(object)
    attrib  cdata
    method  initialize  {|this,x| this:cdata:=x,this}
    method  padr        {|this,w,p| w::params(*), this:cdata:=this:cdata::.padr(w,p),this}
    method  upper       {|this| params(*,"!",*), this:cdata:=this:cdata::.upper,this}

***************************************************************************
    