
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// bejár egy jsonobject-et
// és a leveleknél kiértékel egy kódblokkot
//
//   eval(codeblk,path,value)
//
// ahol 
// path a levélhez vezető út
// value a levél értéke


******************************************************************************************
function json_walk(json,root:="",blkleaf,blkelem,blkmemb)
    if( valtype(json)=="O" )
        walk_object(json,root,blkleaf,blkelem,blkmemb)
    elseif( valtype(json)=="A" )
        walk_array(json,root,blkleaf,blkelem,blkmemb)
    else
        break( "invalid json type")
    end

******************************************************************************************
static function walk_object(jsobj,path,blkleaf,blkelem,blkmemb)

local m
local member,value,type
local pathx

    for m:=1 to len(jsobj:array)
        member:=jsobj:array[m]
        value:=member:value
        type:=value::valtype
        pathx:=path+"."+member:name

        if( blkmemb!=NIL )
            eval(blkmemb,path,member)
        end

        if( type$"UCNL" )
            if(blkleaf==NIL,NIL,eval(blkleaf,pathx,value))
        elseif( type=="A" )
            walk_array(value,pathx,blkleaf,blkelem,blkmemb)
        elseif( type=="O" )
            walk_object(value,pathx,blkleaf,blkelem,blkmemb)
        end
    next


******************************************************************************************
static function walk_array(arr,path,blkleaf,blkelem,blkmemb)

local v
local value,type

    for v:=1 to len(arr)
        value:=arr[v]
        type:=value::valtype

        if( blkelem!=NIL )
            eval(blkelem,path,value)
        end

        if( type$"UCNL" )
            if(blkleaf==NIL,NIL,eval(blkleaf,path,value))
        elseif( type=="A" )
            walk_array(value,path,blkleaf,blkelem,blkmemb)
        elseif( type=="O" )
            walk_object(value,path,blkleaf,blkelem,blkmemb)
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

    