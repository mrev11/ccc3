
// bejár egy jsonobject-et
// és a leveleknél kiértékel egy kódblokkot
//
//   eval(codeblk,path,value)
//
// ahol 
// path a levélhez vezető út
// value a levél értéke


******************************************************************************************
function json_walk(jsonobject,root:="",codeblk)
    walk_object(jsonobject,root,codeblk)


******************************************************************************************
static function walk_object(jsobj,path,codeblk)

local m
local member,value,type
local pathx

    for m:=1 to len(jsobj:array)
        member:=jsobj:array[m]
        value:=member:value
        type:=value::valtype
        pathx:=path+"."+member:name
        
        if( type$"UCNL" )
            eval(codeblk,pathx,value)
        elseif( type=="A" )
            walk_array(value,pathx,codeblk)
        elseif( type=="O" )
            walk_object(value,pathx,codeblk)
        end
    next


******************************************************************************************
static function walk_array(arr,path,codeblk)

local v
local value,type

    for v:=1 to len(arr)
        value:=arr[v]
        type:=value::valtype

        if( type$"UCNL" )
            eval(codeblk,path,value)
        elseif( type=="A" )
            walk_array(value,path,codeblk)
        elseif( type=="O" )
            walk_object(value,path,codeblk)
        end
    next


******************************************************************************************
/*
start ::= json.
json ::= object.
json ::= array.
object ::= LBRACE memberlist RBRACE.
memberlist ::=.
memberlist ::= member.
memberlist ::= memberlist COMMA member.
member ::= STRING COLON value.
array ::= LBRACKET valuelist RBRACKET.
valuelist ::=.
valuelist ::= value.
valuelist ::= valuelist COMMA value.

value ::= NuLL.
value ::= STRING.
value ::= NUMBER.
value ::= TRUE.
value ::= FALSE.

value ::= array.
value ::= object.
*/

    