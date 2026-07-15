
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

#include "tdcutil.ch"

******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
local data,src,out
local tcre,tacc,tmod

    for n:=1 to len(tdc)
        data:=tdc[n]::parsetdc // {table,path,index,field,keep}
        src:=data::gensrc

        // a kimenet neve nem a tdc-bol
        // hanem az osztalynevbol kepzodik
        out:="tabobj."+data[1]::lower+".prg"
        memowrit(out,src)
        {tcre,tacc,tmod}:=getfiletime(tdc[n])
        setfiletime(out,tcre,tacc,tmod)
    next


******************************************************************************************
static function gensrc(data)

local table:=data[1]
local path:=data[2]
local index:=data[3]
local field:=data[4]
local keep:=data[5]

local lf:=chr(10)
local n,line
local prg:="//"+TDCUTIL_BUILD+lf+lf

    prg+="class tabobj."+table::lower+"(tabobj)"+lf
    for n:=1 to len(field)
        line:="    method  FIELD {||}"
        line::=strtran("FIELD",field[n]:column::padr(24))
        prg+=line+lf
    end
    prg+="    method  initialize"+lf
    prg+="    method  __stamp__"+lf
    prg+="    method  __mutex__"+lf
    prg+=lf
    
    prg+="static function tabobj."+table::lower+".initialize(this,file:='"+table+"')"+lf
    prg+="    this:(tabobj)initialize(file)"+lf
    for n:=1 to len(field)
        line:='    tabAddColumn(this,{"[COLUMN]","[TYPE]",[WIDTH],[DEC]})'
        line::=strtran("[COLUMN]"   ,field[n]:column::padr(24))
        line::=strtran("[TYPE]"     ,field[n]:type)
        line::=strtran("[WIDTH]"    ,field[n]:width::str::alltrim::padl(4))
        line::=strtran("[DEC]"      ,field[n]:dec::str::alltrim::padl(2))
        prg+=line+lf
    next

    for n:=1 to len(index)
        line:='    tabAddIndex(this,{"[CONTROL]","[FILE]",[SEGMENTS]})'
        line::=strtran("[CONTROL]"  ,index[n]:control)
        line::=strtran("[FILE]"     ,index[n]:file)
        line::=strtran("[SEGMENTS]" ,index[n]:segments::any2str)
        prg+=line+lf
    next

    if( path!=NIL )
        prg+='    tabPath(this,"[PATH]/")'::strtran("[PATH]",path)+lf
    end
    if( keep!=NIL )
        prg+='    tabKeepDeleted(this,KEEP)'::strtran("KEEP",keep::str::alltrim)+lf
    end
   
    prg+="    return this"+lf

    prg+=<<PRG>>
static function tabobj.TABLE.__stamp__(this,x) 
static stamp
    if( x!=NIL )
        stamp:=x
    end
    return stamp

static function tabobj.TABLE.__mutex__()
static mutex:=thread_mutex_init()
    return mutex
<<PRG>>::strtran("TABLE",table::lower)
    
    return prg

******************************************************************************************

