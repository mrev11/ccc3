
namespace webapp

***************************************************************************************
function loadconfig(fspec)

local config,n
local line,pos,opt,val
local hash:=simplehashNew()

    config:=memoread(fspec)::split(chr(10))

    for n:=1 to len(config)
        line:=config[n]::alltrim

        if( empty(line) )
            loop
        end

        if( left(line,1)=="#" )
            loop
        end
        
        pos:=at("=",line)
        if( pos==0 )
            loop
        end

        opt:=line[1..pos-1]
        val:=line[pos+1..]
        
        hash[opt]:=substenv(val)
    next
    
    return hash


***************************************************************************************
static function substenv(val)
local pos1,pos2
    while( 0<(pos1:=at("$(",val)) )
        pos2:=at(")",val,pos1+3)
        val::=stuff(pos1, pos2-pos1+1, getenv( val[pos1+2..pos2-1] ))
    end
    return val


***************************************************************************************
