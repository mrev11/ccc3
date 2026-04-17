

******************************************************************************************
function json_tostr(json,indent:=.f.)

local jsonstring
local tmp:=tempfile()
local channel:=channelNew(tmp)

    channel:open
    channel:on
    json_print(json,indent)
    channel:off
    jsonstring:=memoread(tmp)
    channel:close
    ferase(tmp)
    return jsonstring


******************************************************************************************
function json_print(json,indent:=.f.)
    if( valtype(json)=="A" )
        if(indent, jsprint_array_indent(json), jsprint_array(json))
    elseif( valtype(json)=="O" )
        if(indent, jsprint_object_indent(json), jsprint_object(json))
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
static function jsprint_array_indent(array,indent:=0)
local n,type
    ? tab(indent)+"["
    for n:=1 to len(array)
        if(n>1)
            ?? ","
        end
        type:=array[n]::valtype
        if( type=="A" )
            jsprint_array_indent(array[n],indent+1)
        elseif( type=="O" )
            jsprint_object_indent(array[n],indent+1)
        else
            ?;jsprint_value_indent(array[n],indent+1)
        end
    next
    ? tab(indent)+"]"


******************************************************************************************
static function jsprint_object_indent(object,indent:=0)
local n,member,type
    ? tab(indent)+"{"
    for n:=1 to len(object:array)
        if(n>1)
            ?? ","
        end
        member:=object:array[n]
        ? tab(indent+1)+member:name::escape+": "
        type:=member:value::valtype
        if( type=="A" )
            jsprint_array_indent(member:value,indent+1)
        elseif( type=="O" )
            jsprint_object_indent(member:value,indent+1)
        else
            jsprint_value_indent(member:value,0)
        end
    next
    ? tab(indent)+"}"


******************************************************************************************
static function jsprint_value_indent(value,indent:=0)
local type:=valtype(value)
    ?? tab(indent)
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
static function tab(indent)
    return replicate("    ",indent)


******************************************************************************************









