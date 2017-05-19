
static config:=initconfig() 

***************************************************************************************
static function initconfig()
local hash,cnf,n,pos,key,value
    hash:=simplehashNew()
    if( !empty(getenv("CCC_CONFIG")) .and. !empty(cnf:=getenv("CCC_CONFIG")::memoread)  )
        cnf::=strtran(chr(13),"")
        cnf::=split(chr(10))
        for n:=1 to len(cnf)
            if( (pos:=at('=',cnf[n]))>0 )
                key:=cnf[n][1..pos-1]::alltrim
                value:=cnf[n][pos+1..]
                hash[key]:=value
            end
        next
    end
    //hash:list
    return hash


***************************************************************************************
function ccc_config(key,value)
local prev
    if( key==NIL )
        return config 
    elseif( value==NIL ) 
        return config[key]
    else
        prev:=config[key]
        config[key]:=value
        return prev
    end

***************************************************************************************
    

