

static clhash:=simplehashNew(0)::getclassid

******************************************************************************************
function marshal(x)

local type:=valtype(x)
local n,x1,av

    if( x==NIL )
        type:="U"
        x:=x""

    elseif( type=="C"  )
        // ok

    elseif( type=="X"  )
        x::=base64_encode

    elseif( type=="N" )
        x::=str::alltrim

    elseif( type=="D"  )
        x:=if(empty(x),"",x::dtos)

    elseif( type=="L"  )
        x:=if(x,"t","f")

    elseif( type=="A"  )
        x1:=x""
        for n:=1 to len(x)
            x1+=marshal(x[n])
        next
        x:=x1

    elseif( type=="O" )
        x1:=x""
        if( x:isderivedfrom(clhash) )
            av:=x:first
            while( av!=NIL )
                //ures datumot kihagyni
                if( valtype(av[2])!="D".or.!empty(av[2]) )
                    x1+=marshal(av)
                end
                av:=x:next
            end
        else
            av:=x:attrvals
            for n:=1 to len(av)
                if( av[n][2]!=NIL )
                    //ures datumot kihagyni
                    if( valtype(av[n][2])!="D" .or. !empty(av[n][2]) )
                        x1+=marshal(av[n])
                    end
                end
            next
        end
        x:=x1
    end

    x::=str2bin

    return str2bin(type+x::len::str::alltrim+":")+x


******************************************************************************************
function unmarshal(x)

local result
local type:=x[1]::bin2str
local colon:=at(a":",x)
local len:=val(x[2..colon])
local body:=substr(x,colon+1,len)
local pos
local hash,item
local clnm,clid,av,n

    if( type=="U" )
        return NIL

    elseif( type=="C" )
        return bin2str(body)

    elseif( type=="X" )
        return body::base64_decode

    elseif( type=="N" )
        return val(body)

    elseif( type=="L" )
        return body==a"t"

    elseif( type=="D" )
        return body::padr(8)::stod

    elseif( type=="A" )
        result:={}
        pos:=1
        while( 0<(colon:=at(a":",body,pos))  )
            len:=val(body[pos+1..colon])
            item:=body[pos..colon+len]
            pos+=len(item)
            aadd(result,unmarshal(item))
        end
        return result

    elseif( type=="O" )
        hash:=simplehashNew()
        pos:=1
        while( 0<(colon:=at(a":",body,pos))  )
            len:=val(body[pos+1..colon])
            item:=body[pos..colon+len]
            pos+=len(item)
            item:=unmarshal(item)
            hash[item[1]]:=item[2]
        end

        if( (clnm:=hash[a"_"])!=NIL .and. (clid:=classidbyname(clnm))>0  )
            result:=objectNew(clid)
            av:=result:attrnames
            for n:=1 to len(av)
                av[n]:=hash[av[n]]
            next
            iniobjectfromarray(result,av)
        else
            result:=hash
        end

        return result
    end

******************************************************************************************


