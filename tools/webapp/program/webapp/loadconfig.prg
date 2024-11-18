
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

static config_default:="webapp_config"

static option_hash:=load_config()
static option_known:=load_known()


***************************************************************************************
static function load_known()
local hash:=simplehashNew()
    hash["iface"]:=.t.
    hash["port"]:=.t.
    hash["ssl"]:=.t.
    hash["keyfile"]:=.t.
    hash["cafile"]:=.t.
    hash["capath"]:=.t.
    hash["gzip"]:=.t.
    hash["permessage-deflate"]:=.t.
    hash["exec"]:=.t.
    return hash


***************************************************************************************
***************************************************************************************
function option_hash()
    return option_hash


***************************************************************************************
static function load_config()

local config_file:=option("-c")
local hash:=simplehashNew()
local n,arr:={},item

    if( config_file!=NIL  )
        if( !file(config_file) )
            ? "config file does not exist:", config_file
            ?
            quit
        end
    elseif( file(config_default)  ) 
        config_file:=config_default
    end
    
    if( !empty(config_file) )
        load_options_from(hash,config_file)
    end

    for n:=1 to len(argv())
        if( argv(n)=="-c"  )
            n++
        elseif( argv(n)=="-i" )
            hash["iface"]:=argv(++n)
        elseif( argv(n)=="-p" )
            hash["port"]:=argv(++n)
        elseif( argv(n)=="-s" )
            hash["ssl"]:=argv(++n)
        elseif( argv(n)=="-z" )
            hash["gzip"]:=argv(++n)
        elseif( argv(n)=="-x" )
            hash["exec"]:=argv(++n)
        else
            ? "unknown option:",argv(n)
            ?
            quit
        end
    next
    
    item:=hash:first
    while( item!=NIL )
        if( option_known[item[1]]==NIL  )
            ? "unknown option:",item[1]
            ?
            quit
        end
        arr::aadd(item)
        item:=hash:next
    end
    arr::asort({|x,y|x[1]<y[1]})

    for item:=1 to len(arr)
        ? arr[item]
    next
    ?
    
    return hash


***************************************************************************************
static function load_options_from(hash,file)

local config:=memoread(file)::split(chr(10))
local n,line,pos,opt,val

    for n:=1 to len(config)
        line:=config[n]
        line::=strtran(chr(13),"")
        if( (pos:=at("#",line))>0 )
            line::=left(pos-1)
        end
        if( empty(line) )
            loop
        end

        pos:=at("=",line)
        opt:=line[1..pos-1]::alltrim
        val:=line[pos+1..]::alltrim
        
        if( !empty(opt)  )
            hash[opt]:=substenv(val)
        else
            hash[val]:="true"
        end
    next

    ? "config loaded from:", file
    return hash


***************************************************************************************
static function option(opt)
local n
    for n:=1 to len(argv())
        if( argv(n)==opt  )
            return argv(n+1)
        end 
    next


***************************************************************************************
static function substenv(val)
local pos1,pos2
    while( 0<(pos1:=at("$(",val)) )
        pos2:=at(")",val,pos1+3)
        val::=stuff(pos1, pos2-pos1+1, getenv( val[pos1+2..pos2-1] ))
    end
    while( 0<(pos1:=at("${",val)) )
        pos2:=at("}",val,pos1+3)
        val::=stuff(pos1, pos2-pos1+1, getenv( val[pos1+2..pos2-1] ))
    end
    return val


***************************************************************************************
