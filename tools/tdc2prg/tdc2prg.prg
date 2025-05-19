
#include "tdcutil.ch"

******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
local data,src,out
local tcre,tacc,tmod

    for n:=1 to len(tdc)
        data:=tdc[n]::parsetdc
        src:=data::gensrc

        // kimenet nevkepzese a tdc-bol
        out:=tdc[n]::strtran(".tdc",".prg")
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
local n,line,prg:="//"+TDCUTIL_BUILD+lf+lf
    
    prg+="function table."+table::lower+"(col,exp)"+lf
    prg+="static tbl"+lf
    prg+="    if(empty(tbl))"+lf
    prg+="        tbl:=table.init."+table::lower+"()"+lf
    prg+="    end"+lf
    prg+="    if(col==NIL)"+lf
    prg+="        return tbl"+lf
    prg+="    end"+lf
    prg+="    return tabEvalColumn(tbl,col,exp)"+lf
    prg+=lf

    prg+="static function table.init."+table::lower+"()"+lf
    prg+='local tbl:=tabNew("'+table+'")'+lf

    for n:=1 to len(field)
        line:='    tabAddColumn(tbl,{[COLUMN],[TYPE],[WIDTH],[DEC]})'
        line::=strtran("[COLUMN]"   , ('"'+field[n]:column+'"')::padr(20))
        line::=strtran("[TYPE]"     , '"'+field[n]:type+'"')
        line::=strtran("[WIDTH]"    , field[n]:width::str::alltrim::padl(3))
        line::=strtran("[DEC]"      , field[n]:dec::str::alltrim::padl(2))
        prg+=line+lf
    next

    for n:=1 to len(index)
        line:='    tabAddIndex(tbl,{"[CONTROL]","[FILE]",[SEGMENTS]})'
        line::=strtran("[CONTROL]"  ,index[n]:control)
        line::=strtran("[FILE]"     ,index[n]:file)
        line::=strtran("[SEGMENTS]" ,index[n]:segments::any2str)
        prg+=line+lf
    next

    if( path!=NIL )
        prg+='    tabPath(tbl,"[PATH]/")'::strtran("[PATH]",path)+lf
    end
    if( keep!=NIL )
        prg+='    tabKeepDeleted(tbl,KEEP)'::strtran("KEEP",keep::str::alltrim)+lf
    end
   
    prg+="    return tbl"+lf

    return prg

******************************************************************************************
