
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

function main( nspace )

local d:=directory("*.tdc"),n
local eol:=endofline()

local tabnames
local tabsuper

local tabbynam:=<<XX>>
function !NSPACE!tabByName(t)
local n:=ascan(!NSPACE!tabNameList(),{|s|s==upper(alltrim(t))})
    return if(n>0,eval(!NSPACE!tabSuperList()[n]),NIL)
<<XX>>

local sup:="tabsuperlist.prg"
local tab
local out

    asort(d,,,{|x,y|x[1]<y[1]}) 


    tabnames:="function "
    tabsuper:="function "
    if( nspace!=NIL )
        tabnames+=nspace+"."
        tabsuper+=nspace+"."
        tabbynam::=strtran("!NSPACE!",nspace+".")
    else
        tabbynam::=strtran("!NSPACE!","")
    end

    tabnames+="tabNameList()"+eol
    tabnames+="local nameList:={}"+eol

    tabsuper+="tabSuperList()"+eol
    tabsuper+="local supList:={}"+eol

    for n:=1 to len(d)
        tab:=tabname(d[n][1])
        tabnames+='    aadd(nameList,"'+tab::upper+'")'+eol
        tabsuper+='    aadd(supList,{||table.'+tab::lower+'()})'+eol
    next

    tabnames+="    return nameList"+eol
    tabsuper+="    return supList"+eol

    out:=eol+tabsuper+eol+eol+tabnames+eol+eol+tabbynam+eol
    if( !out==memoread(sup) )
        memowrit(sup,out )
    end


************************************************************************************
static function tabname(fspec)

static rx:=pcre2.compile(a"!table[ \t]+[_0-9a-zA-Z]+")

local fd:=fopen(fspec)
local map:=filemap.open(fd)
local match,tabname

    fclose(fd)

    if( (match:=pcre2.match(rx,map))==NIL )
        ? "invalid tdc file (does not have !table line):", fspec
        ?
        quit
    end

    tabname:=map[match[1]..match[2]-1]
    tabname::=bin2str
    tabname::=strtran("!table","")
    tabname::=strtran(chr(9),"")
    tabname::=alltrim

    filemap.close(map)
    return tabname


************************************************************************************

