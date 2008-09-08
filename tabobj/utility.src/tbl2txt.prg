
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

#define VERSION "1.0.00"

#include "table.ch"
#include "fileio.ch"
 
******************************************************************************
function table2txt(*)

local table
local dext:=lower(tabDataExt())
local appname:=substr(dext,2)+"2txt"
local args:={*},n,ctrl,fname

    for n:=1 to len(args)
        if( args[n]=="-c"  )
            ctrl:=args[++n]
        elseif( args[n]=="-f" )
            fname:=args[++n]
        elseif( n==len(args) )
            fname:=args[n]
        end
    next

    if( fname==NIL )
        ? appname+" "+VERSION+" (C) ComFirm 2002"
        ? @"Usage: "+appname+@" filename"
        ?
        errorlevel(1)
        quit
    end

    if( !dext $ fname )
        fname+=dext
    end
    
    if( !file(fname) )
        ? fname, @"not found"
        ?
        errorlevel(1)
        quit
    end
    
    table:=open(fname,ctrl)
    
    if( table==NIL )
        ? fname, @"not available"
        ?
        errorlevel(1)
        quit
    end

    tabCopyTo(table, strtran(fname,dext,".txt")) 

    return NIL


******************************************************************************
static function open(fname,ctrl:=0)
local tab:=tabResource(fname)

    if( valtype(tab)!="A" .or.  empty(tab) )
        tab:=NIL 
    else
        tabOpen(tab,OPEN_EXCLUSIVE)
        //tabOpen(tab)
    end
    tabControl(tab,ctrl)
    return tab
 

******************************************************************************
