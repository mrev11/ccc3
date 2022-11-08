
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

*****************************************************************************
#ifdef NOT_DEFINED
  Tarolja a felhasznalo read/modify/delete/append jogosultsagait (ugo).

    u: csak sajat adathoz
    g: csak sajat csoport adatahoz
    o: minden adathoz

  Az access metodus
  a jogosultsagot osszeveti a kivant hozzaferesi moddal,
  es kivetelt dob, ha a jogosultsag nem megfelelo.
  Az o (other) tipusu jogosultsag vizsgalata egyszeru: van/nincs.
  A g/u jogosultsagokhoz tudni kell, hogy mi a sajat/csoport adat,
  ehhez felul kell definialni az accessuser/accessgroup metodusokat.
#endif

*****************************************************************************
class accesssession(basesession) new: //absztrakt
    method  initialize
    attrib  permread
    attrib  permmodify
    attrib  permdelete
    attrib  permappend
    method  access
    method  accessgroup     {||.f.}  //felul kell definialni
    method  accessuser      {||.f.}  //felul kell definialni 

****************************************************************************
static function accesssession.initialize(this,sid,srv) 
local perm,i
    this:(basesession)initialize(sid,srv)
    perm:=wrapper():call("session.permission",{sid,srv}) 
    i:=ascan(perm,{|p|p[1]==srv+".read"});   this:permread:=if(i>0,perm[i][2],"X") 
    i:=ascan(perm,{|p|p[1]==srv+".modify"}); this:permmodify:=if(i>0,perm[i][2],"X") 
    i:=ascan(perm,{|p|p[1]==srv+".delete"}); this:permdelete:=if(i>0,perm[i][2],"X") 
    i:=ascan(perm,{|p|p[1]==srv+".append"}); this:permappend:=if(i>0,perm[i][2],"X") 
    return this

*****************************************************************************
static function accesssession.access(this,mode)

local perm,e

    if( mode=="r" )
        perm:=this:permread
    elseif( mode$"m" )
        perm:=this:permmodify
    elseif( mode$"d" )
        perm:=this:permdelete
    elseif( mode=="a" )
        perm:=this:permappend
    else
        e:=xmlrpcaccessdeniederrorNew("accesssession.access")
        e:args:={mode}
        break(e)
    end

    if( perm=="o" )
    elseif( perm=="g" .and. this:accessgroup(mode) )
    elseif( perm=="u" .and. this:accessuser(mode) )
    else
        e:=xmlrpcaccessdeniederrorNew("accesssession.access")
        if( mode=="r" )
            e:description:="read access denied"
        elseif( mode$"m" )
            e:description:="modify access denied"
        elseif( mode$"d" )
            e:description:="delete access denied"
        elseif( mode=="a" )
            e:description:="append access denied"
        end
        e:args:={mode}
        break(e)
    end

****************************************************************************
