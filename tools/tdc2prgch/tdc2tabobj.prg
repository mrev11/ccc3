
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

#define VERSION "tdc2tabobj 1.2"


******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
    for n:=1 to len(tdc)
        tdc2prg( tdc[n] )
    next


******************************************************************************************
static function tdc2prg( tdcspec )

local tdc:=memoread(tdcspec)
local n,line,pos,key,val
local table
local index:={}
local field:={}
local path
local keep
local prg
local outspec

    tdc::=strtran(chr(13),"")
    tdc::=strtran(chr(9)," ")
    while( "  "$tdc )
        tdc::=strtran("  "," ")
    end
    tdc::=split(chr(10))

    for n:=1 to len(tdc)
        line:=tdc[n]
        if( line::left(1)=="!" )
            pos:=at(" ",line)
            key:=line[1..pos-1]::alltrim
            val:=line[pos+1..]::alltrim
        
            if( key=="!field" )
                field::aadd(val::split(" "))
            elseif( key=="!index" )
                index::aadd(val::split(" "))
            elseif( key=="!path" )
                path:=val
            elseif( key=="!table" )
                table:=val
            elseif( key=="!keepdeleted" )
                keep:=val
            end
        end
    next
    
    prg:=genprg( table,path,index,field,keep )

    outspec:="tabobj."+lower(table)+".prg"
    if( !memoread( outspec)==prg )
        memowrit(outspec,prg)
    end


******************************************************************************************
static function genprg(table,path,index,field,keep)

local lf:=chr(10)
local n,line
local prg:="//"+VERSION+lf+lf

    prg+="class tabobj."+table+"(tabobj)"+lf
    for n:=1 to len(field)
        line:="    method  FIELD {||}"
        line::=strtran("FIELD",field[n][1]::padr(24))
        prg+=line+lf
    end
    prg+="    method  initialize"+lf
    prg+="    method  __stamp__"+lf
    prg+="    method  __mutex__"+lf
    prg+=lf
    
    prg+="static function tabobj."+table+".initialize(this,alias:='"+table+"')"+lf
    prg+="    this:(tabobj)initialize(alias)"+lf
    for n:=1 to len(field)
        line:='    tabAddColumn(this,{"[COLUMN]","[TYPE]",[WIDTH],[DEC]})'
        line::=strtran("[COLUMN]"   ,field[n][1]::padr(24))
        line::=strtran("[TYPE]"     ,field[n][2])
        line::=strtran("[WIDTH]"    ,field[n][3]::alltrim::padl(4))
        line::=strtran("[DEC]"      ,field[n][4]::alltrim::padl(2))
        prg+=line+lf
    next

    for n:=1 to len(index)
        line:='    tabAddIndex(this,{"[CONTROL]","[FILE]",[SEGMENTS]})'
        line::=strtran("[CONTROL]"  ,index[n][1])
        line::=strtran("[FILE]"     ,index[n][2])
        line::=strtran("[SEGMENTS]" ,index[n][3..]::any2str)
        prg+=line+lf
    next

    if( path!=NIL )
        prg+='    tabPath(this,"[PATH]/")'::strtran("[PATH]",path)+lf
    end
    if( keep!=NIL )
        prg+='    tabKeepDeleted(this,KEEP)'::strtran("KEEP",keep)+lf
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
<<PRG>>::strtran("TABLE",table)
    
    return prg

******************************************************************************************
