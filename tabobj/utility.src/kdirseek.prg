
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

#include "table.ch"
#include "kdirseek.say"


************************************************************************
function keres(brw,tab)
//local color:=setcolor("w/n,n/w,,,w/n")
local color:=setcolor("w/b,b/w,,,w/b")
    brwKillFocus(brw)
    if( tabControl(tab)==0 )
        kdirseek({|g|kdgload(g,tab)},{|g|readfilt(g)},{|g|kdgstore(g,brw,tab)})
    else
        kdirseek({|g|kdload(g,tab)},{|g|readfilt(g)},{|g|kdstore(g,brw,tab)})
    end
    setcolor(color)
    brwSetFocus(brw)
    return .t.


************************************************************************
static function kdgload(getlist,tab)
local never:={||.f.}

    g_col1:varPut("RECNO")
    g_col1:display()
    g_seg1:varPut(0)
    g_seg1:picture:="@Z 99999999"
    g_seg1:display()

    g_col1:preBlock:=never
    g_seg2:preBlock:=never
    g_col2:preBlock:=never
    g_seg3:preBlock:=never
    g_col3:preBlock:=never
    g_seg4:preBlock:=never
    g_col4:preBlock:=never
    return NIL

static function kdgstore(getlist,brw,tab)
local n:=g_seg1:varGet()
    brw:gotop()
    tabGoto(tab,n)
    brw:refreshAll()
    return .t.   
    

************************************************************************
static function kdload(getlist,tab)
local gcol:={g_col1,g_col2,g_col3,g_col4}
local gseg:={g_seg1,g_seg2,g_seg3,g_seg4}
local index:=tabIndex(tab)[tabControl(tab)][IND_COL] //index oszlopok sorszama
local column:=tabColumn(tab), n
local name,type,width,dec
local pict,value

    for n:=1 to len(index)
        name:=column[index[n]][COL_NAME]
        type:=column[index[n]][COL_TYPE]
        width:=column[index[n]][COL_WIDTH]
        dec:=column[index[n]][COL_DEC]
        pict:=column[index[n]][COL_PICT]
        value:=tabEvalColumn(tab,index[n])
 
        gcol[n]:varput(name)
        gcol[n]:display
 
        if( replicate("X",21)$pict )
            gseg[n]:picture:=strtran(pict,"@R","@S20")
        else
            gseg[n]:picture:=pict
        end

        gseg[n]:varput(value)
        gseg[n]:display
        gseg[n]:preblock:={||.t.}
    next



    for n:=len(index)+1 to 4
        gseg[n]:preBlock:={||.f.}
    end
    for n:=1 to 4
        gcol[n]:preBlock:={||.f.}
    end
    return NIL


static function kdstore(getlist,brw,tab)
local n, seg:={g_seg1,g_seg2,g_seg3,g_seg4}, key:={}
    for n:=1 to 4
        if( eval(seg[n]:preBlock) )
            aadd(key,seg[n]:varGet())
        end
    next
    brw:gotop()
    tabSeek(tab,key)
    brw:refreshAll()
    return .t.   
   

************************************************************************


