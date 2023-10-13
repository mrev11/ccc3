
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


// ezeket a fuggvenyeket hasznaljak:
//  pgview
//  pgstat
//  pgmemo


#clang
#include <cccapi.h>
#cend


******************************************************************************************
function btopen(btfile)

local fd:=-1,map,magic

    if( btfile!=NIL )
        fd:=fopen(btfile)
        if( fd<0 )
            fd:=fopen(btfile+=".bt")
        end
    end
    if( fd<0 )
        return NIL
    end

    map:=filemap.open(fd)
    fclose(fd)
    if( empty(map) )
        return NIL
    end

    magic:=map[1..4]
    if( magic==x"62310500" )
        dskord("litend")
        swap(endian()==.t.)
    elseif( magic==x"00053162" )
        dskord("bigend")
        swap(endian()==.f.)
    else
        ? "WRONG MAGIC NUMBER", magic::hex
        ?
        quit
    end

    return map


******************************************************************************************
function swap(x)
static value
    return if(x==NIL,value,value:=x)


******************************************************************************************
function dskord(x)
static value
    return if(x==NIL,value,value:=x)


******************************************************************************************
function num(x)  // N tipus
    if( len(x)==2 )
        x::=bin2w
    elseif( len(x)==4 )
        x::=bin2u
    else
        break("invalid binary length")
    end
    return x

******************************************************************************************
function numswap(x)  // N tipus
    x:=if(swap(),reverse(x),x)
    if( len(x)==2 )
        x::=bin2w
    elseif( len(x)==4 )
        x::=bin2u
    else
        break("invalid binary length")
    end
    return x

******************************************************************************************
function dec(x)  // C tipus decimalisan
    return x::num::str::alltrim

******************************************************************************************
function hex(x)  // C tipus hexa
    return x::num::l2hex

******************************************************************************************
function reverse(x)
local r:=a"",n
    for n:=len(x) to 1 step -1
        r+=x[n]
    next
    return r

******************************************************************************************
static function endian()
local endian
#clang
    int endian=1;
    binarys( (char*)&endian, sizeof(int) );
    assign(LOCAL_endian);
    pop();
#cend
    //? endian::bin2hex
    return if( endian[1]::asc==0, .t., .f. ) // litend=.f., bigend=.t.


******************************************************************************************
function parse_poslen(poslen)
local pos,len
#clang
    unsigned int poslen=_parni(1);
    number( poslen&0xffff );        // also 16 bit offset
    assign(LOCAL_pos);
    pop();
    number( (poslen>>16)&0xffff );  // felso 16 bit size
    assign(LOCAL_len);
    pop();
#cend
    return {pos,len}


******************************************************************************************
function parse_recmix(recmix)
local recno,memix
#clang
    unsigned int recmix=_parni(1);
    number( recmix&0xfffffff );     // also 28 bit recno
    assign(LOCAL_recno);
    pop();
    number( (recmix>>28)&0xf );     // felso 4 bit memix
    assign(LOCAL_memix);
    pop();
#cend
    return {recno,memix}


******************************************************************************************
function form_recmix(rec,mix,w)
local x
    if( rec>0 )
        x:="mid["+rec::str::alltrim+","+mix::str::alltrim+"]"
    else
        x:="mid[]"
    end
    if( w!=NIL )
        x::=padr(w)
    end
    return x


******************************************************************************************
function form_mempos(pgno,indx,w)
local x:="(0x"+pgno::l2hex+","+indx::str::alltrim+")"
    if( w!=NIL )
        x::=padr(w)
    end
    return x


******************************************************************************************
function form_memseg(memseg,w)
local lt,rt
    if( len(memseg)>w-2 )
        lt:=int(w/2)-4
        rt:=w-lt-5
        memseg:=memseg::left(lt)+a'...'+memseg::right(rt)
    end
    memseg:=a"["+memseg+a"]"
    if( w!=NIL )
        memseg::=padr(w)
    end
    return memseg


******************************************************************************************
