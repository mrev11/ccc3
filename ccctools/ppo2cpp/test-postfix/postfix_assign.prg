
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

function main()
local x:="Próba szerencse"
local num:=100


    ? x::strtran("szer","SZER")  //x nem változik
    ? x
    ?

    ? x::=strtran("encse","ENCSE")   //x is változik
    ? x 
    ?

    ? x::=upper
    ? x
    ?
    
    //x::padr(20,"X")::=lower //illegal lvalue

    ? x::=padr(20,"X")::lower+"!" //-> próba szerencsexxxxx!
    ? x                           //-> próba szerencsexxxxx!
    ?
    
    ? hohoNew("HoHo"):padr(10,"x"):upper:cdata //metódushívások!
    ? hohoNew("HoHo"):padup(10,"x"):cdata
    ?

    x:=10
    ? x+=num+13
    ? x
    ?

***************************************************************************
class hoho(object)
    attrib  cdata
    method  initialize  {|this,x| this:cdata:=x,this}
    method  padr        {|this,w,p| this:cdata::=padr(w,p),this}
    method  upper       {|this| this:cdata::=upper,this}
    method  padup       {|this,w,p| this:cdata::=padr(w,p)::upper,this}

***************************************************************************
