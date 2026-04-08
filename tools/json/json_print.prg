

******************************************************************************************
function json_tostr(json)

local jsonstring
local tmp:=tempfile()
local channel:=channelNew(tmp)

    channel:open
    channel:on
    json_print(json)
    channel:off
    jsonstring:=memoread(tmp)
    channel:close
    ferase(tmp)
    return jsonstring


******************************************************************************************
function json_print(json)
    if( valtype(json)=="A" )
        jsprint_array(json)
    elseif( valtype(json)=="O" )
        jsprint_object(json)
    end


******************************************************************************************
static function jsprint_array(array)
local n,type
    ?? "["
    for n:=1 to len(array)
        if(n>1)
            ?? ","
        end
        type:=array[n]::valtype
        if( type=="A" )
            jsprint_array(array[n])
        elseif( type=="O" )
            jsprint_object(array[n])
        else
            jsprint_value(array[n])
        end
    next
    ?? "]"


******************************************************************************************
static function jsprint_object(object)
local n,member,type
    ?? "{"
    for n:=1 to len(object:array)
        if(n>1)
            ?? ","
        end
        member:=object:array[n]
        ?? member:name::escape+":"
        type:=member:value::valtype
        if( type=="A" )
            jsprint_array(member:value)
        elseif( type=="O" )
            jsprint_object(member:value)
        else
            jsprint_value(member:value)
        end
    next
    ?? "}"


******************************************************************************************
static function jsprint_value(value)
local type:=valtype(value)
    if( type=="C" )
        ?? value::escape
    elseif( type=="N" )
        ??  value::str::ltrim
    elseif( type=="L" )
        ?? if(value,"true","false")
    elseif( type=="U" )
        ?? "null"
    end


******************************************************************************************
static function escape(x)
    if( '\'$x )
        x::=strtran('\','\\')
    end
    if( '"'$x )
        x::=strtran('"','\"')
    end
    return '"'+x+'"'

******************************************************************************************









