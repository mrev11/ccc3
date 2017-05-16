
static config:=initconfig() 

***************************************************************************************
static function initconfig()

local hash,cnf,n

    if( !empty(getenv("CCC_CONFIG")) .and. !empty(cnf:=getenv("CCC_CONFIG")::memoread)  )
        //? "read ccc_config from", getenv("CCC_CONFIG")
        
        cnf::=strtran(chr(13),"")
        cnf::=split(chr(10))
        
        hash:=simplehashNew()
        for n:=1 to len(cnf)
            cnf[n]::=split("=")
            if( cnf[n]::len==2 )
                hash[cnf[n][1]]:=cnf[n][2]
            end
        next
    end

    return hash


***************************************************************************************
function ccc_config(key,value)

    if( value==NIL ) 
        value:=if(config==NIL,NIL,config[key])

    elseif(config==NIL)
        config:=simplehashNew()
        config[key]:=value

    else
        config[key]:=value
    end

    //? key, value
    return value


***************************************************************************************
    

