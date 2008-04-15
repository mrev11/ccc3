
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


function localtds.abc.tableEntityNew(connection,tablist)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".localtds.abc"
local clid:=classidbyname(classname)
    if( clid==0 )
        clid:=localtds.abc.tableEntityRegister(connection)
    end
    return objectNew(clid):initialize(connection,tablist)



static function localtds.abc.tableEntityIni(this,connection,tablist)
local parentclid:=connection:__tableentityclass__
local initmethod:=getmethod(parentclid,"initialize")
    eval(initmethod,this,connection)
    this:tablist:=if(tablist==NIL,{"konto.a=a","konto.b=b","konto.c=c"},tablist)
    return this



static function localtds.abc.tableEntityRegister(connection)
local parentclid:=connection:__tableentityclass__
local parentname:=classname(parentclid)
local classname:=parentname+".localtds.abc"
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

    classMethod(clid,"initialize",{|this,c,t|localtds.abc.tableEntityIni(this,c,t)})
    classMethod(clid,"version",{||"2"})
    classMethod(clid,"__rowclassname__",{||connection:driver+".rowentity.localtds.abc"})
    classMethod(clid,"__rowclassid__",{|t,x|if(rowclassid==NIL,rowclassid:=x,rowclassid)})
    classMethod(clid,"__buffersize__",{|t,x|if(buffersize==NIL,buffersize:=x,buffersize)})
    classMethod(clid,"__memocount__",{|t,x|if(memocount==NIL,memocount:=x,memocount)})
    classMethod(clid,"__selectlist__",{|t|if(selectlist==NIL,selectlist:=eval(getmethod(parentclid,"__selectlist__"),t),selectlist)})
    classMethod(clid,"__tabjoin__",{||tabjoin})
    classMethod(clid,"__indexlist__",{|this|indexlist})
    classMethod(clid,"__primarykey__",{||primarykey})
    classMethod(clid,"__filterlist__",{||filterlist})
    classMethod(clid,"columnlist",{||columnlist})

    aadd(columnlist,c:=dummy:__columndefnew__("id_a",'"a"."id"',"N4"))
    aadd(columnlist,c:=dummy:__columndefnew__("name_a",'"a"."name"',"C10"))
    aadd(columnlist,c:=dummy:__columndefnew__("val_a",'"a"."value"',"N19,2"))
    aadd(columnlist,c:=dummy:__columndefnew__("id_b",'"b"."id"',"N4"))
    aadd(columnlist,c:=dummy:__columndefnew__("val_b",'"b"."value"',"N6"))
    aadd(columnlist,c:=dummy:__columndefnew__("attrib",'"c"."attrib"',"C24"))

    tabjoin:='a full join b on "a"."id"="b"."id" left join c on "a"."name"="c"."name"'


    aadd(filterlist,{"select","",""})
    classMethod(clid,"select",{|this,bnd,lck|this:__select__(,,bnd,lck)})
    aadd(filterlist,{"selord","","id_a"})
    classMethod(clid,"selord",{|this,bnd,lck|this:__select__(,'"a"."id"',bnd,lck)})

    dummy:__registerrowentityclass__
    return clid
