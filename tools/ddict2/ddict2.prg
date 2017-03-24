
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

#include "ddict2.ver"


#include "inkey.ch"
 
#include "table.ch"
#include "_ddict.ch"


****************************************************************************
function main(*) //argumentumok: dbfdir, datadict, namespace

local sset:=standardset()
local p:={*},pp,i,dbfdir,ddict,nspace
local karbtart:={}, struct:={}, program:={}
local ddpath, ddname, n
local browse

    i:=1
    while( i<=len(p) .and. p[i]!=NIL )
    
        p[i]:=strtran(p[i],"/",dirsep())
        p[i]:=strtran(p[i],"\",dirsep())
        
        pp:=","+p[i]+","
 
        if( pp $ ",-u+,-u," )
            underscore("_") //default
            adel(p,i)

        elseif( pp $ ",-u-," )
            underscore("") 
            adel(p,i)

        elseif( pp $ ",-s+,-s," )
            superlist(.t.) //default
            adel(p,i)

        elseif( pp $ ",-s-," )
            superlist(.f.) 
            adel(p,i)

        else
            i++
        end
    end
    
    if( p[1]==NIL )
        ? "Data Dictionary Utility Version "+VERZIO
        ? "Copyright (C) ComFirm BT. 1998. All rights reserved"

        ?
        ? "Usage: ddict2 [dbfDir [ddPathName [namespace]]]  [-u+|-u-] [-s+|-s-]"
        ?
        ? "dbfDir     : directory containing database tables (default='.')"
        ? "ddPathName : datadict file (default='datadict')"
        ? "namespace  : namespace of tabSuperList"
        ? "-u+,-u-    : underline before object names (default: -u+)"
        ? "-s+,-s-    : genarate _super??.prg modules (default: -s+)"
        ?
        ? "Status"
        ?
        ? "' ': OK"
        ? "'F': no index name"
        ? "'O': index has no columns"
        ? "<n>: <n>-th key segment (column) does not exist"
        ? "'?': database table not found"
        ? "'*': structures in datadict and database differ"
        ? "'!': modified record"
        ? "'M': imported from external datadict"
        ?
        ? "Hit any key!"
        inkey(0)
    end
    
    p::asize(3)

    dbfdir := if(NIL==p[1],".",p[1])
    ddict  := if(NIL==p[2],"datadict",p[2])
    nspace := if(NIL==p[3],"",p[3]+".")
    
    dbfRoot(dbfdir)  //beállítja a dbf directory-t
    
    n:=max( rat(dirsep(),ddict), rat(":",ddict) )   
    DDICT:path:=left(ddict,n)
    DDICT:file:=substr(ddict,n+1)
    tabDelIndex(DDICT:table)

    DDICT:upgrade    
    DDICT:open
    DDICT:control:="table"
    DDICT:gotop

    browse:=DDICT:browse(0,0,maxrow(),maxcol())

    brwColumn(browse,"",{||DDICT_STATE},1)
    brwColumn(browse,"Table",{||tabver()},18)
    brwColumn(browse,"Order",{||lower(DDICT_INDNAME)},10)
    brwColumn(browse,"Index columns",{||DDICT_INDFIELD},36)
    brwColumn(browse,"Directory",{||DDICT_DIRECTORY},28)
    brwColumn(browse,"Owner",{||DDICT_OWNER})
    brwColumn(browse,"Date",{||DDICT_STRDATE})
    brwColumn(browse,"Index file",{||lower(DDICT_INDFILE)},16)

    brwMenuName(browse,"[Dictionary:"+ddictName()+"]")

    aadd(struct,{"Verify all tables           (ALT-V)",{||structVerif(browse)}})
    aadd(struct,{"Diff of ddict and table     (ALT-X)",{||browseDiff(browse)}})
    aadd(struct,{"View ddict structure        (ALT-T)",{||structBrowse(browse)}})
    aadd(struct,{"Save table structure to ddict      ",{||structReplace(browse)}})
    aadd(struct,{"Create table with ddict structure  ",{||structCreate(browse)}})
    aadd(struct,{"Import external dictionary         ",{||mergeDdict(browse)}})
    aadd(struct,{"Browse selected table       (ALT_B)",{||browseData(browse)}})
    brwMenu(browse,"Structure","Compare structures in tables and ddict",struct)

    aadd(karbtart,{"Enter table/index definition  (ALT-A)",{||sorBev(browse)}})
    aadd(karbtart,{"Modify selected definition    (ALT-M)",{||sorMod(browse)}})
    aadd(karbtart,{"Delete selected definition           ",{||sorTor(browse)}})
    aadd(karbtart,{MENUSEP})
    aadd(karbtart,{"Create new version                   ",{||verzioMake(),browse:refreshAll(),.t.}})
    aadd(karbtart,{"Delete older version                 ",{||verzioDelete(),browse:refreshAll(),.t.}})
    brwMenu(browse,"Maintain","Maintaining table/index definitions",karbtart)

    aadd(program,{"Generate #ifdef ARROW type include files",{||progOutPut(browse,"##",nspace)}})
    aadd(program,{"Generate (FIELD:alias:count) type include files",{||progOutPut(browse,"::",nspace)}})
    aadd(program,{"Generate alias->field type include files",{||progOutPut(browse,"->",nspace)}})
    brwMenu(browse,"Program","Generate program output (PRG,CH)",program)

    brwMenu(browse,"Pack!","Remove deleted records from datadict file",{||ddictPack(browse),.t.})

    browse:freeze:=2

    brwApplyKey(browse,{|b,k|applykey(b,k)})
    brwCaption(browse,"Data Dictionary Utility "+VERZIO)
    brwSetFocus(browse)

    if( underscore()=="_" )
        browse:colorspec("w/b,bg/w,,,w/b")
    else
        browse:colorspec("w/n,bg/w,,,w/n")
    end
    
    brwShow(browse)
    brwLoop(browse)
    brwHide(browse)

    setcolor("w/n,n/w")
    cls
    return NIL


****************************************************************************
static function tabver()
    return DDICT_TABLE+str(int(1000.0001-DDICT_VERSION),3,0) 


****************************************************************************
static function brwSeekKey(browse,ncol,key)
local column:=browse:getColumn(ncol)
local pos

#define HEADING   column:cargo[1]
#define SEEKKEY   column:cargo[2]

    if( column:cargo==NIL )
        column:cargo:={column:heading,""}
    end
    
    if( 32<key.and.key<255 )
        SEEKKEY+=upper(chr(key))

        DDICT:seek(SEEKKEY)

        if( DDICT_TABLE!=SEEKKEY )
            SEEKKEY:=left(SEEKKEY,len(SEEKKEY)-1)
        else
            pos:=DDICT:position
            browse:goTop()
            DDICT:goto:=pos
            column:heading:=SEEKKEY
            browse:configure()
            browse:refreshAll()
        end
        return .t.

    elseif( !empty(SEEKKEY) )
        SEEKKEY:=""
        column:heading:=HEADING //vissza az eredetit
        browse:configure()
        browse:refreshAll()
    end

    return NIL


****************************************************************************
static function applykey(b,k)
    if(k==K_ALT_M)
        sorMod(b)
        return .t.

    elseif(k==K_INS)
        sorNez(b)
        return .t.

    elseif(k==K_ALT_A)
        sorBev(b)
        return .t.

    elseif(k==K_ALT_V)
        structVerif(b)
        return .t.

    elseif(k==K_ALT_X)
        browseDiff(b)
        return .t.

    elseif(k==K_ALT_T)
        structBrowse(b)
        return .t.

    elseif(k==K_ALT_B)
        browseData(b)
        return .t.

    elseif(k==K_ESC)
        return 2!=alert("Are you sure to quit?", {"Cancel","Quit"}) 

    end

    return brwSeekKey(b,2,k)


****************************************************************************
function dbfRoot(path)  //a dbf-ekhez vezető path
static rootpath:=""
    if( !empty(path) )
        path:=upper(alltrim(path))
        if( !right(path,1)$":"+dirsep() )
            path+=dirsep()
        end
        rootpath:=path
    end
    return rootpath


****************************************************************************
function ddictName()
    return DDICT:file


****************************************************************************
function ddictPath()
    return DDICT:path


****************************************************************************
function ddictPack()
local state:=DDICT:save
    if( DDICT:open(OPEN_EXCLUSIVE,{||.f.}) )
        DDICT:pack
        DDICT:open
    end
    DDICT:restore:=state
    return NIL


****************************************************************************
function standardset()

    setcursor(0)
    setcolor("w/bg,b/w")
    underscore("_") //default

    return NIL


****************************************************************************
