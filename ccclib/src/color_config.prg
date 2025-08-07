
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


static config:=initconfig()

#clang
#include <cccapi.h>
#cend



***************************************************************************************
static function initconfig()
local hash,cnf,n,pos,key,value
    hash:=simplehashNew()
    if( !empty(getenv("CCC_COLORCONF")) .and. !empty(cnf:=getenv("CCC_COLORCONF")::memoread)  )
        cnf::=strtran(chr(13),"")
        cnf::=split(chr(10))
        for n:=1 to len(cnf)
            if( (pos:=at('=',cnf[n]))>0 )
                key:=cnf[n][1..pos-1]::alltrim
                value:=cnf[n][pos+1..]::alltrim
                if( !empty(key) .and. !key[1]=="#"  )
                    hash[key]:=env(value)
                end
            end
        next
    end

    make_custom_color_table(hash)

#ifdef DEBUG
    ? "CCC_COLORCONF"
    cnf:=hash:toarr
    cnf::asortkey({|x|x[1]})
    for pos:=1 to len(cnf)
        ? cnf[pos]
    next
    //callstack()
#endif

    return hash


***************************************************************************************
static function make_custom_color_table(config)
local item,color1,color2

    item:=config:first
    while( NIL!=item )
        if( "COLOR:"==left(item[1],6) )
            color1:=item[1]::substr(7)::alltrim::colorstring_to_colorindex
            color2:=item[2]::alltrim::colorstring_to_colorindex
            if( color1<16 )
                #clang
                  extern void set_custom_color(int,int);
                  int c1=D2INT(LOCAL_color1->data.number);
                  int c2=D2INT(LOCAL_color2->data.number);
                  set_custom_color(c1,c2);
                  //printf("COLOR: #%d -> %d\n",c1,c2);
                #cend
            end
        end
        item:=config:next
    end


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
static function env(value)
local pos1,pos2:=1,var
    while( 0<(pos1:=at("${",value),pos2) .and. pos1<(pos2:=at("}",value,pos1)) )
        var:=value[pos1+2..pos2-1]
        value::=stuff(pos1,pos2-pos1+1,getenv(var))
    end
    return value

***************************************************************************************
