
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


function szerencse.tableEntityNew(connection,tablist)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".szerencse"
local clid:=classidbyname(classname)
    if( clid==0 )
        clid:=szerencse.tableEntityRegister(connection)
    end
    return objectNew(clid):initialize(connection,tablist)



static function szerencse.tableEntityIni(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=if(tablist==NIL,{"konto.szerencse=q"},tablist)
    return this



static function szerencse.tableEntityRegister(connection)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".szerencse"
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

    classMethod(clid,"initialize",{|this,c,t|szerencse.tableEntityIni(this,c,t)})
    classMethod(clid,"version",{||"2,2006-07-18"})
    classMethod(clid,"__rowclassname__",{||connection:driver+".rowentity.szerencse"})
    classMethod(clid,"__rowclassid__",{|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)})
    classMethod(clid,"__buffersize__",{|t,x|if(buffersize==NIL,buffersize:=x,buffersize)})
    classMethod(clid,"__memocount__",{|t,x|if(memocount==NIL,memocount:=x,memocount)})
    classMethod(clid,"__selectlist__",{|t|if(selectlist==NIL,selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),selectlist)})
    classMethod(clid,"__tabjoin__",{||tabjoin})
    classMethod(clid,"__indexlist__",{|this|indexlist})
    classMethod(clid,"__primarykey__",{||primarykey})
    classMethod(clid,"__filterlist__",{||filterlist})
    classMethod(clid,"columnlist",{||columnlist})

    aadd(columnlist,c:=dummy:__columndefnew__("szamlaszam",'"szamla"',"C24"))
    aadd(columnlist,c:=dummy:__columndefnew__("kiegdata",'"kiegdata"',"C32"))

    aadd(indexlist,dummy:__indexdefnew__("primarykey",primarykey,.t.))
    aadd(primarykey,c:=dummy:getcolumn("szamlaszam"));c:notnull:=.t.

    classMethod(clid,"find",{|this,key,lck|this:__find__('where "szamla"=:1',key,lck)})
    aadd(filterlist,{"select","","szamlaszam"})
    classMethod(clid,"select",{|this,bnd,lck|this:__select__(,'"szamla"',bnd,lck)})

    dummy:__registerrowentityclass__
    return clid
