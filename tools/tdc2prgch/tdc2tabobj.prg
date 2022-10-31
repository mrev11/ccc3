

#define VERSION "tdc2tabobj 1.0"


******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
    for n:=1 to len(tdc)
        tdc2prg( tdc[n] )
    next


******************************************************************************************
static function tdc2prg( tdcspec )

local tdc:=memoread(tdcspec)
local n,line,key,val
local table
local index:={}
local field:={}
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
            key:=line[1..6]
            val:=line[8..]::alltrim
        
            if( key=="!field" )
                field::aadd(val::split(" "))
            elseif( key=="!index" )
                index::aadd(val::split(" "))
            elseif( key=="!table" )
                table:=val
            end
        end
    next
    
    prg:=genprg( table,index,field )

    outspec:="tabobj."+lower(table)+".prg"
    if( !memoread( outspec)==prg )
        memowrit(outspec,prg)
    end


******************************************************************************************
static function genprg(table,index,field)

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
    prg+="    method  __colblk__"+lf
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
    prg+="    return this"+lf

    prg+=<<PRG>>
static function tabobj.cassa.__colblk__() 
static colblk:=.t.
local result:=colblk
    colblk:=.f.
    return result // eloszor .t., utana mindig .f.

static function tabobj.cassa.__mutex__()
static mutex:=thread_mutex_init()
    return mutex
<<PRG>>
    
    return prg

******************************************************************************************
