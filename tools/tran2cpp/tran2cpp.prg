
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

******************************************************************************
function main(input,output)

local txt,key,value,sep
local addstmt:="t->add(KEY,VALUE);",x,n

    if( !file(input) .or. empty(txt:=memoread(input)) )
        usage()
    end
    
    if( NIL!=output )
        set printer to (output)
        set printer on
        set console off
    end
    
    
    ? "#include <hashtable.h>"
    ?
    ? "void hashtable_fill(hashtable *t){"
    
    txt:=split(txt,chr(10))

    for n:=1 to len(txt)
        sep:=at('"<<"',txt[n])
        if( sep>0 )
            key:=left(txt[n],sep)
            value:=substr(txt[n],sep+3)
            value:=left(value,rat('"',value))

            //x:=addstmt
            //x:=strtran(x,"KEY",unicode_escape(key))
            //x:=strtran(x,"VALUE",unicode_escape(value))
            
            x:="t->add("+unicode_escape(key)+","+unicode_escape(value)+");" //2012.04.22
 
            if( len(value)>2 )
                ? x
            end
        end
    next
    ? "}"
    ?    

******************************************************************************
static function unicode_escape(x)
local y:="L",i,a
    for i:=1 to len(x)
        a:=ascpos(x,i)
        if( a<128 )
            y+=chr(a)
        else
            y+="\u"+padl(l2hex(a),4,"0")
        end
    next
    return y

******************************************************************************
static function usage()
    ? "Usage: input [output]"
    ?
    quit

******************************************************************************
