
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

//Created by dom2prg 1.3.00


function proba.tableEntityNew(connection,tablist)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".proba"
local clid:=classidbyname(classname)
    if( clid==0 )
        clid:=proba.tableEntityRegister(connection)
    end
    return objectNew(clid):initialize(connection,tablist)



static function proba.tableEntityIni(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=if(tablist==NIL,{"konto.proba=p"},tablist)
    return this



static function proba.tableEntityRegister(connection)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".proba"
local clid:=classRegister(classname,{parentclid})
local dummy:=objectNew(clid),c,x

local rowclassid
local buffersize
local memocount
local selectlist
local tabjoin
local columnlist:={}
local indexlist:={}
local primarykey:={}
local filterlist:={}

    classMethod(clid,"initialize",{|this,c,t|proba.tableEntityIni(this,c,t)})
    classMethod(clid,"version",{||"2,2006-07-18"})
    classMethod(clid,"__rowclassname__",{||connection:driver+".rowentity.proba"})
    classMethod(clid,"__rowclassid__",{|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)})
    classMethod(clid,"__buffersize__",{|t,x|if(buffersize==NIL,buffersize:=x,buffersize)})
    classMethod(clid,"__memocount__",{|t,x|if(memocount==NIL,memocount:=x,memocount)})
    classMethod(clid,"__selectlist__",{|t|if(selectlist==NIL,selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),selectlist)})
    classMethod(clid,"__tabjoin__",{||tabjoin})
    classMethod(clid,"__indexlist__",{|this|indexlist})
    classMethod(clid,"__primarykey__",{||primarykey})
    classMethod(clid,"__filterlist__",{||filterlist})
    classMethod(clid,"columnlist",{||columnlist})

    aadd(columnlist,c:=dummy:__columndefnew__("szamlaszam",'"szamla"',"C24"));c:notnull:=.t.
    aadd(columnlist,c:=dummy:__columndefnew__("devnem",'"devnem"',"C3"))
    aadd(columnlist,c:=dummy:__columndefnew__("nev",'"megnevezes"',"C30"))
    aadd(columnlist,c:=dummy:__columndefnew__("egyenleg",'"osszeg"',"N17.2"))
    aadd(columnlist,c:=dummy:__columndefnew__("tulmenflag",'"tulmenflag"',"L"))
    aadd(columnlist,c:=dummy:__columndefnew__("konyvkelt",'"konyvkelt"',"D"))
    aadd(columnlist,c:=dummy:__columndefnew__("megjegyzes",'"megjegyzes"',"M"))

    aadd(indexlist,dummy:__indexdefnew__("primarykey",primarykey,.t.))
    aadd(primarykey,c:=dummy:getcolumn("szamlaszam"));c:notnull:=.t.
    aadd(primarykey,c:=dummy:getcolumn("devnem"));c:notnull:=.t.

    aadd(indexlist,dummy:__indexdefnew__("nev",x:={}))
    aadd(x,dummy:getcolumn("nev"))
    aadd(x,dummy:getcolumn("szamlaszam"))

    classMethod(clid,"find",{|this,key,lck|this:__find__('where "szamla"=:1 and "devnem"=:2',key,lck)})
    aadd(filterlist,{"select","","szamlaszam,devnem"})
    classMethod(clid,"select",{|this,bnd,lck|this:__select__(,'"szamla","devnem"',bnd,lck)})
    aadd(filterlist,{"select_kk","where konyvkelt<:1 or konyvkelt is null","szamlaszam"})
    classMethod(clid,"select_kk",{|this,bnd,lck|this:__select__('where "konyvkelt"<:1 or "konyvkelt" is null','"szamla"',bnd,lck)})
    aadd(filterlist,{"select_ge","where szamlaszam>=:1","nev desc,szamlaszam"})
    classMethod(clid,"select_ge",{|this,bnd,lck|this:__select__('where "szamla">=:1','"megnevezes" desc,"szamla"',bnd,lck)})
    aadd(filterlist,{"select_tf","where tulmenflag=:1","szamlaszam"})
    classMethod(clid,"select_tf",{|this,bnd,lck|this:__select__('where "tulmenflag"=:1','"szamla"',bnd,lck)})
    aadd(filterlist,{"select_bl","where egyenleg<:1","szamlaszam"})
    classMethod(clid,"select_bl",{|this,bnd,lck|this:__select__('where "osszeg"<:1','"szamla"',bnd,lck)})

    dummy:__registerrowentityclass__
    return clid
