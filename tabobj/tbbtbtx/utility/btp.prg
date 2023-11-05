
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


static tab
static pgsize

#include "table.ch"

#include "inkey.ch"
#include "search.say"


******************************************************************************************
static function usage()
    ? "Usage: btp <btfile>"
    ?
    quit

******************************************************************************************
function main(btfile)

local map
local page0
local maxpgn
local brw
local err

    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        if( empty(map:=btopen(btfile)) )
            break()
        end
        tab:=tabResource(btfile)
        tabOpen(tab,OPEN_READONLY)
    recover err
        usage()
    end

    page0:=pgread(0)
    pgsize:=page0[9..12]::num
    maxpgn:=len(map)/pgsize-1

    brw:=brwCreate()
    brwArray(brw,array(1+maxpgn))
    brwColumn(brw,"PgNo    ",blkpgno(brw),"AAAAAAAAAA")
    brwColumn(brw,"PgType  ",blktype(brw),"AAAAAAAA")
    brwColumn(brw,"Items   ",blkitem(brw),"99999")
    brwColumn(brw,"Space   ",blkroom(brw),"99999")
    brwColumn(brw,"Offset  ",blkoffs(brw),"AAAAAAAAAA")
    brwColumn(brw,"Link    ",blklink(brw),"AAAAAAAAAA")

    brwMenuName(brw,btfile)

    brwApplyKey(brw,{|b,k|appkey(b,k)})

    setcursor(0)
    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)


******************************************************************************************
static function appkey(brw,key)
    if( key==K_ENTER )
        show(brw)
    elseif( key==K_INS )
        show_header()
    elseif( key==asc("/") )
        search({||},{|*|readmodal(*)},{|*|store(brw,*)})
    end


******************************************************************************************
static function store(brw,getlist)
local pgno:=g_search:varget
    if( !pgno::empty )
        pgno::=hex2l
        brwArrayPos(brw,pgno+1)
        brw:refreshall
    end
    return .t.


******************************************************************************************
static function pgnumber(brw)
    return brwArrayPos(brw)-1


******************************************************************************************
static function pgread(p)
static pgno
static page
    if( p!=pgno )
        pgno:=p
        page:=_db_pgread(tab[2],pgno)
    end
    return page


******************************************************************************************
static function blkpgno(brw)
    return {||pgno(brw)}

static function pgno(brw)
local pgno:=pgnumber(brw)
    return pgno::l2hex::padl(8)


******************************************************************************************
static function blkoffs(brw)
    return {||offs(brw)}

static function offs(brw)
local pgno:=pgnumber(brw)
    return "0x"+(pgno*pgsize)::l2hex::padl(8,"0")


******************************************************************************************
static function blktype(brw)
    return {||type(brw)}

static function type(brw)
local pgno:=pgnumber(brw)
local page:=pgread(pgno)
    return pagetype(page)


******************************************************************************************
static function blklink(brw)
    return {||link(brw)}

static function link(brw)
local pgno:=pgnumber(brw)
local page:=pgread(pgno)
local link:=page[5..8]::num::numand(0x7fffffff)
    if( pgno==0 )
        link:=""
    elseif( link==0 )
        link:=""
    else
        link::=l2hex::padl(8)
    end
    return link


******************************************************************************************
static function blkitem(brw)
    return {||item(brw)}

static function item(brw)
local pgno:=pgnumber(brw)
local page:=pgread(pgno)
local type:=pagetype(page)
local lower,upper,item
    if( pgno==0 )
        //header
        item:=page[29..32]::num // ennyi index van benne
    elseif(type=="MEMO")
        lower:=page[ 9..12]::num
        upper:=page[13..16]::num
        item:=(lower-16)/16 // ennyi rekord van benne
    else
        lower:=page[21..22]::num
        upper:=page[23..24]::num
        item:=(lower-24)/2 // ennyi rekord van benne
    end
    return item::str(4)


******************************************************************************************
static function blkroom(brw)
    return {||room(brw)}

static function room(brw)
local pgno:=pgnumber(brw)
local page:=pgread(pgno)
local type:=pagetype(page)
local ords,lower,upper,room
    if( pgno==0 )
        ords:=page[29..32]::num
        room:=len(page)-48-ords*32
    elseif(type=="MEMO")
        lower:=page[ 9..12]::num
        upper:=page[13..16]::num
        room:=upper-lower // ennyi hely  van benne
    else
        lower:=page[21..22]::num
        upper:=page[23..24]::num
        room:=upper-lower // ennyi hely  van benne
    end
    return room::str(4)


******************************************************************************************
static function show(brw)

local pgno:=pgnumber(brw)
local page:=pgread(pgno)
local type:=pagetype(page)
local log,tv,scr

    set channel(log) to "log-btp"
    set channel(log) on

    ? "pgno  ", "0x"+pgno::l2hex

    if( pgno==0 )
        page_header(page)
    elseif( type=="TREE" )
        page_tree(page)
    elseif( type=="LEAF" )
        page_leaf(page)
    elseif( type=="DATA" )
        page_data(page)
    elseif( type=="MEMO" )
        page_memo(page)
    end
    set channel(log) off

    log:=memoread("log-btp")

    tv:=textviewNew(log)
    scr:=savescreen()
    setcursor(1)
    tv:loop
    setcursor(0)
    restscreen(,,,,scr)


******************************************************************************************
static function show_header()
local log,tv,scr
    set channel(log) to "log-header"
    set channel(log) on
    ? "HEADER"
    ?
    page_header(pgread(0))
    set channel(log) off
    log:=memoread("log-header")
    tv:=textviewNew(log)
    scr:=savescreen()
    setcursor(1)
    tv:loop
    setcursor(0)
    restscreen(,,,,scr)


******************************************************************************************
