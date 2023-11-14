
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


// fabejarassal bejarja az indexeket (minden index lapot megjelol)
// az azonos indexhez tartozo lapok listajat ujraepiti
// a nem-index, nem-data, nem-memo lapokbol ujraepiti a free listet 
// kiirja a tree, leaf, data, memo, free lapok szamat

#include "table.ch"

static indx_page
static mark_page

#clang
#include <cccapi.h>
#cend


******************************************************************************************
static function usage()
    ? "Usage: btlink <btfile>"
    ?
    quit

******************************************************************************************
function main(btfile)

local table
local btree
local fd
local fsize
local page0
local maxpgno

local MAGIC
local VERSION
local ENCRYPT
local PGSIZE
local NRECS
local FREE
local LASTDATA
local MEMO
local NORDS

local ord,offset,order,iname,rootpgno,n
local create_time,access_time,modif_time

    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        {create_time,access_time,modif_time}:=getfiletime(btfile)
        table:=tabResource(btfile)
        tabOpen(table,OPEN_EXCLUSIVE)
        fd:=table[1]
        btree:=table[2]
    recover
        usage()
    end

    fsize:=fstat_st_size(fd)
    page0:=_db_pgread(btree,0)

    MAGIC    := page0[ 1.. 4]
    VERSION  := page0[ 5.. 8]::num::numand(0xf)
    ENCRYPT  := page0[ 5.. 8]::num::numand(0x100)!=0
    PGSIZE   := page0[ 9..12]::num
    NRECS    := page0[13..16]::num
    FREE     := page0[17..20]::num
    LASTDATA := page0[21..24]::num
    MEMO     := page0[25..28]::num
    NORDS    := page0[29..32]::num
    maxpgno  := fsize/PGSIZE-1

    mark_page:=array(maxpgno)

    _db_header_read(btree,.t.) //for writing
    offset:=0x31
    for ord:=1 to NORDS
        order:=page0::substr(offset,32)
        rootpgno:=order[1..4]::num
        iname:=order::right(16)::strtran(bin(0),bin(32))::trim

        indx_page:={}
        walk(btree,rootpgno)
        relink(btree,ord)

        offset+=32
    next

    freelist(btree)

    _db_header_write(btree)
    setfiletime(btfile,create_time,access_time,modif_time)

    ?? btfile; ?


******************************************************************************************
static function code_link(page,pgno)
    //? page[1..4]::hex, "<-", pgno::l2hex
    if( xvgetlong(page,4)!=pgno )
        xvputlong(page,4,pgno)
        // visszairja
        return page
    end
    // nem kell visszairni


******************************************************************************************
static function freelist(btree) // a szabad lapokat listaba fuzi

local cnt_tree:=0
local cnt_leaf:=0
local cnt_data:=0
local cnt_memo:=0
local cnt_free:=0

local free:={},n
local pgno,page,type
local blk:={|p|code_link(p,pgno)}

    for pgno:=1 to len(mark_page)
        if( mark_page[pgno]!=NIL  )
            //index lap: TREE/LEAF
            if( mark_page[pgno]==1 )
                cnt_tree++
            elseif( mark_page[pgno]==2 )
                cnt_leaf++
            else
                break({"unknown page type",pgno,mark_page[pgno]})
            end
        else
            //nem index: DATA,MEMO,free
            page:=_db_pgread(btree,pgno)
            type:=pagetype_num(page)
            if( type==3 )
                mark_page[pgno]:=type
                cnt_data++
            elseif( type==4 )
                mark_page[pgno]:=type
                cnt_memo++
            else
                cnt_free++
                aadd(free,pgno)
            end
        end
    next

    ?? if(cnt_tree==0,"tree","TREE"),cnt_tree,;
       if(cnt_leaf==0,"leaf","LEAF"),cnt_leaf,;
       if(cnt_data==0,"data","DATA"),cnt_data,; 
       if(cnt_memo==0,"memo","MEMO"),cnt_memo,;  
       if(cnt_free==0,"free","FREE"),cnt_free,;
       "    "

    if( empty(free) )
        setfree(btree,0)
    else
        // ujraepiti freelistet
        free::arev
        for n:=2 to len(free) 
            pgno:=free[n]
            _db_pgeval(btree,free[n-1],blk)
            // beolvassa a page:=free[n-1] lapot
            // vegrehajtja: code_link(page,pgno)
            // a lap visszairodik a lemezre
        next
        pgno:=0
        _db_pgeval(btree,free::atail,blk) // az utolsoba NULL-t
    end


function setfree(btree,free)
#clang
    unsigned *header=(unsigned*)_parp(1);
    header[4]=_parni(2);  // bt_free felulirva
#cend


******************************************************************************************
static function relink(btree,ord) // az ord index lapjait listaba fuzi
local n,pgno
local blk:={|p|code_link(p,pgno)}
    for n:=len(indx_page) to 2 step -1
        pgno:=indx_page[n-1]
        _db_pgeval(btree,indx_page[n],blk)
        // beolvassa a page:=indx_page[n] lapot
        // vegrehajtja: code_link(page,pgno)
        // visszairja a lapot a lemezre
    next
    setlast(btree,ord,indx_page[1],indx_page::atail)


function setlast(btree,ord,root,last)
#clang
    unsigned *header=(unsigned*)_parp(1);
    unsigned order=_parni(2);
    unsigned root=_parni(3);
    unsigned last=_parni(4);

    unsigned offs=12+(order-1)*8;
    unsigned hroot=header[offs+0];
    unsigned hlast=header[offs+1];
    char *name=(char*)(&header[offs+4]);
    //printf("\n>>>> root=%x last=%x->%x name=%s\n",hroot,hlast,last,name); // stimmelnek

    if( root!=hroot )
    {
        // ellenorzes
        printf("ERROR: hroot=%x != root=%x\n",hroot,root);
    }
    else
    {
        header[offs+1]=last;  // hlast felulirva
    }
#cend


******************************************************************************************
static function walk(btree,pgno)

// fabejarassal bejarja a pgno-bol gyokerezo reszfat
// az aktualis index lapjait indx_page-ben gyujti
// az osszes index lapjait mark_page-ben jeloli

local page:=_db_pgread(btree,pgno)
local type:=pagetype_num(page)

    indx_page::aadd(pgno)   // az aktualis index lapjai
    mark_page[pgno]:=type   // az osszes index lapjai

    if( type==1 )
        // TREE
        walk1(btree,page)
    elseif( type==2 )
        // LEAF
        // rekurzio vege
    else
        break({"unexpected page type",pgno,type})
    end


static function walk1(btree,page)

local lower:=page::substr(21,2)::num
local upper:=page::substr(23,2)::num
local offset:=24
local pos,len,pgn

    while( offset<lower )
        pos:=page::substr(offset+1,2)::num  // record offset on page
        len:=page::substr(pos+1,4)::num     // key length
        pgn:=page::substr(pos+5,4)::num     // page number

        // rekurzio
        walk(btree,pgn)

        offset+=2
    end


******************************************************************************************
