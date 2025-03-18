
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

#include "table.ch"     // OPEN_EXCLUSIVE-hoz

#define MSGOUT          // kiirasok masik xterm-ben
#include "msgout.ch"    // be kell allitani: export MSGOUT=/dev/pts/<n>


******************************************************************************************
function main()

local t,n:=0

    set dosconv fileshare

    t:=tabobj.cassaNew()
    t:create
    t:open(OPEN_EXCLUSIVE)
    t:zap
    t:close

    thread_create({||pasztazo()})

    t:open

    tranBegin()
    while( ++n<=5000 )
        t:append
        t:soregyeb:=n
        t:penztaros:=crypto_rand_bytes(4)::crypto_bin2hex
        t:szamlaszam:=crypto_rand_bytes(8)::crypto_bin2hex
        t:commit

        if((n%100)==0)
            ?? "."
            tranCommit()
            tranBegin()
            
        end
    end
    tranCommit()

    t:close

    sleep(100)
    ? "OK"
    ?


******************************************************************************************
static function pasztazo()

local t,top,bot

    t:=tabobj.cassaNew()  // masik objektum
    t:open
    t:control:="szamlaszam"

    while(.t.)
        t:gotop; top:=t:szamlaszam
        t:gobottom; bot:=t:szamlaszam
        ?@ top,bot,t:lastrec
        sleep(100)
    end


******************************************************************************************
