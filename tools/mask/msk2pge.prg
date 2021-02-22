
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

#include "box.ch"

static size80x25:={80,25}
static size100x50:={100,50}
static size120x60:={120,60}
static size160x60:={160,60}
static size200x60:={200,60}
static termsize:=size80x25
#define CALCSIZE(t)  (t[1]*t[2]*4)

#define MSK_MAXCOL    termsize[1]
#define MSK_MAXROW    termsize[2]

#define PGE_MAXCOL    160
#define PGE_MAXROW    64


static hor_simple:=(B_HS+;
    B_SS1+B_SS2+B_SS3+B_SS4+B_SS5+B_SS6+B_SS7+B_SS8+B_SS9+;
    B_SD1+B_SD2+B_SD3+B_SD4+B_SD5+B_SD6+B_SD7+B_SD8+B_SD9)

static hor_double:=(B_HD+;
    B_DD1+B_DD2+B_DD3+B_DD4+B_DD5+B_DD6+B_DD7+B_DD8+B_DD9+; 
    B_DS1+B_DS2+B_DS3+B_DS4+B_DS5+B_DS6+B_DS7+B_DS8+B_DS9)

static vert:=(B_VS+B_VD)

static box:=vert+hor_simple+hor_double


***********************************************************************************
function main(*)

local arg:={*},n

local mskfile
local pgefile
local mskstr
local pgestr
local mskrow:={}
local mskrowlen
local pgerowlen
local pagerow
local opt,opt_r:=.f.,opt_u:=.f.

    for n:=1 to len(arg)
        if( "-"==arg[n][1] )
            opt:=arg[n][2..]
            if( "u"$opt )
                opt_u:=.t.
                opt::=strtran("u","")
            end
            if( "r"$opt )
                opt_r:=.t.
                opt::=strtran("r","")
            end
            if( !empty(opt) )
                ? "Unknown option:", "-"+opt
                usage()
            end

        elseif( mskfile==NIL )
            mskfile:=arg[n]  

        elseif( pgefile==NIL )
            pgefile:=arg[n]  

        else
            ? "Unknown argument:", arg[n]
            usage()
        end
    next

    if(mskfile==NIL)
        usage()
    end
    
    if( !right(mskfile,4)==".msk" )
        mskfile+=".msk"
    end
    
    if( pgefile==NIL )
        pgefile:=mskfile[1..len(mskfile)-4]+".pge"
    end
    
    if( !file(mskfile) )
        ? mskfile, "not found"
        ?
        quit
    end


    mskstr:=memoread(mskfile,.t.)

    if( len(mskstr)%4!=0  )
        mskstr:=left(mskstr,len(mskstr)-(len(mskstr)%4))
    end

    if( len(mskstr)==CALCSIZE(size80x25) )
        termsize:=size80x25
    elseif( len(mskstr)==CALCSIZE(size100x50) )
        termsize:=size100x50
    elseif( len(mskstr)==CALCSIZE(size120x60) )
        termsize:=size120x60
    elseif( len(mskstr)==CALCSIZE(size160x60) )
        termsize:=size160x60
    elseif( len(mskstr)==CALCSIZE(size200x60) )
        termsize:=size200x60
    else
        ? "Incompatible msk file length",len(mskstr)
        ?
        quit
    end

    //? MSK_MAXCOL, MSK_MAXROW

    mskrowlen:=MSK_MAXCOL*4 //length in bytes
    pgerowlen:=PGE_MAXCOL*4 //length in bytes

    for n:=1 to MSK_MAXROW
        mskrow::aadd( mskstr::substr((n-1)*mskrowlen+1,mskrowlen) )
    next

    pgestr:=a""
    for n:=1 to PGE_MAXROW
        pagerow:=if(n>MSK_MAXROW,emprow(),mskrow[n]+emprow())::left(pgerowlen)
        if( opt_u .and. row_is_empty(pagerow) )
            pagerow:=a""
        else
            opt_u:=.f.
        end
        if( opt_r )
            pagerow::=replace_box_char
        end
        pgestr+=pagerow
    next
    
    memowrit(pgefile,pgestr)


***********************************************************************************
static function usage()
    ? "Usage: msk2pge.exe [-r] [-u] mskfile"
    ?
    quit


***********************************************************************************
static function row_is_empty(row)
    return row==emprow()


***********************************************************************************
static function replace_box_char(row)
local chr,atr,n

    if( !empty(row) )
        chr:=screenchar(row)
        atr:=screenattr(row)

        for n:=1 to len(chr)
            if( chr[n] $ hor_simple )
                chr:=chr[1..n-1]+"-"+chr[n+1..]
            elseif( chr[n] $ hor_double )
                chr:=chr[1..n-1]+"="+chr[n+1..]
            elseif( chr[n] $ box )
                chr:=chr[1..n-1]+" "+chr[n+1..]
            end
        next
        row:=screencompose(chr,atr)
    end

    return row

***********************************************************************************
static function emprow() // egy üres sor (színkóddal)
static empty_row
    if( empty_row==NIL )
        empty_row:=replicate(empchr(),PGE_MAXCOL)
    end
    return empty_row


***********************************************************************************
static function empchr() // egy üres karakter (színkóddal)
static empty_chr
    if( empty_chr==NIL )
        empty_chr:=x"20000700"
    end
    return empty_chr


***********************************************************************************
