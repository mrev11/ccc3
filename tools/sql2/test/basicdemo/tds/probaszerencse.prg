
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


function probaszerencse.tableEntityNew(connection,tablist)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".probaszerencse"
local clid:=classidbyname(classname)
    if( clid==0 )
        clid:=probaszerencse.tableEntityRegister(connection)
    end
    return objectNew(clid):initialize(connection,tablist)



static function probaszerencse.tableEntityIni(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=if(tablist==NIL,{"konto.proba=p","konto.szerencse=q"},tablist)
    return this



static function probaszerencse.tableEntityRegister(connection)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".probaszerencse"
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

    classMethod(clid,"initialize",{|this,c,t|probaszerencse.tableEntityIni(this,c,t)})
    classMethod(clid,"version",{||"2,2006-07-18"})
    classMethod(clid,"__rowclassname__",{||connection:driver+".rowentity.probaszerencse"})
    classMethod(clid,"__rowclassid__",{|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)})
    classMethod(clid,"__buffersize__",{|t,x|if(buffersize==NIL,buffersize:=x,buffersize)})
    classMethod(clid,"__memocount__",{|t,x|if(memocount==NIL,memocount:=x,memocount)})
    classMethod(clid,"__selectlist__",{|t|if(selectlist==NIL,selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),selectlist)})
    classMethod(clid,"__tabjoin__",{||tabjoin})
    classMethod(clid,"__indexlist__",{|this|indexlist})
    classMethod(clid,"__primarykey__",{||primarykey})
    classMethod(clid,"__filterlist__",{||filterlist})
    classMethod(clid,"columnlist",{||columnlist})

    aadd(columnlist,c:=dummy:__columndefnew__("szamlaszam",'"p"."szamla"',"C24"))
    aadd(columnlist,c:=dummy:__columndefnew__("devnem",'"devnem"',"C3"))
    aadd(columnlist,c:=dummy:__columndefnew__("nev",'"megnevezes"',"C30"))
    aadd(columnlist,c:=dummy:__columndefnew__("egyenleg",'"osszeg"',"N17.2"))
    aadd(columnlist,c:=dummy:__columndefnew__("tulmenflag",'"tulmenflag"',"L"))
    aadd(columnlist,c:=dummy:__columndefnew__("konyvkelt",'"konyvkelt"',"D"))
    aadd(columnlist,c:=dummy:__columndefnew__("megjegyzes",'"megjegyzes"',"M"))
    aadd(columnlist,c:=dummy:__columndefnew__("kiegdata",'"kiegdata"',"C20"))

    tabjoin:='p left join q on "p"."szamla"="q"."szamla"'

    aadd(indexlist,dummy:__indexdefnew__("primarykey",primarykey,.t.))
    aadd(primarykey,c:=dummy:getcolumn("szamlaszam"));c:notnull:=.t.
    aadd(primarykey,c:=dummy:getcolumn("devnem"));c:notnull:=.t.

    classMethod(clid,"find",{|this,key,lck|this:__find__('where "p"."szamla"=:1 and "devnem"=:2',key,lck)})
    aadd(filterlist,{"select","","szamlaszam,devnem"})
    classMethod(clid,"select",{|this,bnd,lck|this:__select__(,'"p"."szamla","devnem"',bnd,lck)})

    dummy:__registerrowentityclass__
    return clid
