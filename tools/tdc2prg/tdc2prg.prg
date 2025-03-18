
******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
local data,src,out

    for n:=1 to len(tdc)
        data:=tdc[n]::parsetdc
        src:=data::gensrc

        // kimenet nevkepzese a tdc-bol
        out:=tdc[n]::strtran(".tdc",".prg")

        if( !memoread(out)==src )
            memowrit(out,src)
        end
    next


******************************************************************************************
static function gensrc(data)

local table:=data[1]
local path:=data[2]
local index:=data[3]
local field:=data[4]
local keep:=data[5]

local lf:=chr(10)
local n,line,prg
    
    prg:="function _"+table::upper+"(col,exp)"+lf
    prg+="static dbf"+lf
    prg+="    if(empty(dbf))"+lf
    prg+='        dbf:=tabNew("'+table+'")'+lf

    for n:=1 to len(field)
        line:='        tabAddColumn(dbf,{[COLUMN],[TYPE],[WIDTH],[DEC]})'
        line::=strtran("[COLUMN]"   , ('"'+field[n]:column+'"')::padr(20))
        line::=strtran("[TYPE]"     , '"'+field[n]:type+'"')
        line::=strtran("[WIDTH]"    , field[n]:width::str::alltrim::padl(3))
        line::=strtran("[DEC]"      , field[n]:dec::str::alltrim::padl(2))
        prg+=line+lf
    next

    for n:=1 to len(index)
        line:='        tabAddIndex(dbf,{"[CONTROL]","[FILE]",[SEGMENTS]})'
        line::=strtran("[CONTROL]"  ,index[n]:control)
        line::=strtran("[FILE]"     ,index[n]:file)
        line::=strtran("[SEGMENTS]" ,index[n]:segments::any2str)
        prg+=line+lf
    next

    if( path!=NIL )
        prg+='        tabPath(dbf,"[PATH]/")'::strtran("[PATH]",path)+lf
    end
    if( keep!=NIL )
        prg+='        tabKeepDeleted(dbf,KEEP)'::strtran("KEEP",keep::str::alltrim)+lf
    end
   
    prg+="    end"+lf
    prg+="    if(col==NIL)"+lf
    prg+="        return dbf"+lf
    prg+="    end"+lf
    prg+="    return tabEvalColumn(dbf,col,exp)"+lf

    return prg

******************************************************************************************
