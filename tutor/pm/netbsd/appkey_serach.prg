
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

#include "inkey.ch"
#include "search.say"

#define BR_SEARCH   1

*********************************************************************************************
function appkey_search(b,k)
    if( k==K_F3 )
        search({|gl|load(gl,b,k)},{|gl|readmodal(gl)},{|gl|find(gl,b,k)})

    elseif( k==K_SH_F3 )
        find_next(b)
        return .t.

    elseif( k==K_CTRL_F3 )
        find_prev(b)
        return .t.
    end

*********************************************************************************************
static function load(getlist,b,k)
    g_search:picture:="@K "+replicate("X",len(g_search:varget))
    g_search:varput(brwSlot(b,BR_SEARCH))
    g_search:display

*********************************************************************************************
static function find(getlist,b,k)
local arr:=brwArray(b)
local ss:=g_search:varget::alltrim,n
    brwSlot(b,BR_SEARCH,ss)
    if( !empty(ss) )
        for n:=1 to len(arr)
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end
    return .t.

*********************************************************************************************
static function find_next(b)
local arr:=brwArray(b)
local ss:=brwSlot(b,BR_SEARCH),n
    if( !empty(ss) )
        for n:=brwArrayPos(b)+1 to len(arr)
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end

*********************************************************************************************
static function find_prev(b)
local arr:=brwArray(b)
local ss:=brwSlot(b,BR_SEARCH),n
    if( !empty(ss) )
        for n:=brwArrayPos(b)-1 to 1 step -1
            if( ss$arr[n][1] )
                brwStabilize(b)
                brwArrayPos(b,n)
                b:refreshall
                exit
            end
        next
    end

*********************************************************************************************
