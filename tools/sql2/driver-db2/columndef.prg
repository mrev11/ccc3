
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

namespace sql2.db2

******************************************************************************
class columndef(sql2.db2.columnref) 
    method  initialize

    attrib  type            // típus: Cw, Nw[,d], D, L, M 
    attrib  notnull         // .t., ha a mező nem lehet null
    attrib  default         // default érték null helyett
 
    attrib  offset          // a mező kezdete a bufferben (0-tól indul)
    attrib  size            // indvar(2)+hotflg(2)+width(size-4)
    attrib  block           // mezőkiolvasó/értékadó block
    attrib  initblock       // mezőinicializáló block
    attrib  keyseg          // .t. ha az oszlop eleme a primkey-nek

    method  sqltype
    method  indvar          {|t,o|xvgetint(o:__buffer__,t:offset)}
    method  isnull          {|t,o|-1==xvgetint(o:__buffer__,t:offset)}
    method  setnull         {|t,o,nf|xvputint(o:__buffer__,t:offset,if(nf,-1,0))}
    method  isdirty         {|t,o|!xvgetflag(o:__buffer__,t:offset+2)}
    method  setdirty        {|t,o,df|xvputflag(o:__buffer__,t:offset+2,!df)}
    method  eval            {|t,o,x|eval(t:block,o,x)}

    attrib  label
    attrib  tooltip
    attrib  picture

#ifdef EMLEKEZTETO //initblock
    Postgresben plusz attribútum az initblock.
    Oracle-ben a define-ban mondtuk meg az interfésznek, hogy
    a mezőértékeket hova rakja (közvetlenül a rowentity bufferbe).
    Postgresben viszont a _pq_getvalue0 hívásokkal kapott értékeket
    egyenként, Clipper szinten rakjuk be a rowentity bufferbe a fetch-ben.
    A buffer inicializálásakor a dirty flaget nem szabad beállítani.
#endif

******************************************************************************
static function columndef.initialize(this,name,expr,type)
    this:(sql2.db2.columnref)initialize(name,expr)  
    this:type:=type
    this:notnull:=.f. //default: lehet null
    this:keyseg:=.f.  //a primkey-be rakáskor kell átállítani
    return this


******************************************************************************
static function columndef.sqltype(this)

// Cn     --> char(n)         ha n<=8
// Cn     --> varchar(n)      ha n>8
// M      --> clob
// Nn     --> number(n)
// Nn,d   --> numeric(n,d)    //Oracle-ben number(n,d)
// Nn.d   --> numeric(n,d)    //Oracle-ben number(n,d)
// L      --> smallint        //Oracle-ben number(1)
// D      --> date

local type,prec

    type:=upper(left(this:type,1))
    
    if( type=="C" )
        prec:=substr(this:type,2) 
        type:=if(val(prec)<=8,"char","varchar")
        type+="("+prec+")"
 
    elseif( type=="N" )
        prec:=substr(this:type,2) 
        prec:=strtran(prec,".",",") //pont helyére vessző
        //type:="number("+prec+")"
        type:="numeric("+prec+")"
 
    elseif( type=="D" )
        type:="date"
 
    elseif( type=="L" )
        type:="smallint"       //MySQL-ben boolean egy alias tinyint-re

    elseif( type=="M" )
        type:="blob"
    end

    return type 

******************************************************************************
