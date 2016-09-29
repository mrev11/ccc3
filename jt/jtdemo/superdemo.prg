
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

#include "directry.ch"

******************************************************************************
function main()
local exelst:=exelst({},".")
    alertblock({|t,a|jtalert(t,a)})
    msgloop( makedlg(exelst) )

******************************************************************************
static function msgloop(dlg)
    dlg:show
    while( NIL!=dlg:getmessage )
    end

******************************************************************************
static function makedlg(exelst)
local dlg,pnl,but,n

    dlg:=jtdialogNew()
    dlg:layout:="vbox"
    dlg:caption:="Super Demo" 

    pnl:=jtpanelNew()
    pnl:layout:="vbox"
    pnl:vscroll:=.t.
    pnl:name:="buttonpanel"
    
    for n:=1 to len(exelst)
        but:=jtpushNew(0,1,0,100,exelst[n])
        but:border:="null"
        but:halign:="left"
        but:icon:="icons/22/exec.png"
        //but:tooltip:=
        but:actionblock:=mkblock(exelst[n])
        if( .f. )
            but:enabled:=.f.
        end
        pnl:additem(but)
    next
    dlg:add(pnl)

    return dlg

******************************************************************************
static function mkblock(exespec)
    return {||doblock(exespec)}

******************************************************************************
static function doblock(exespec)
local err,supdir,exedir,exenam

    supdir:=dirsep()+curdir()  //pl. /home/vermes/temp/jt/jtdemo
    exedir:=fpath0(exespec)    //pl. ./empty
    exenam:=fnameext(exespec)  //pl. empty.exe
    
    dirchange(exedir)
    begin
        jtrun(exenam)
    recover err
        ? err:operation, err:description 
    end
    dirchange(supdir)

******************************************************************************
static function exelst(lst,dspec) //összegyűjti az exe filéket
local d,n

    d:=directory(dspec+dirsep()+"*.exe","H")
    for n:=1 to len(d)
        aadd(lst,dspec+dirsep()+d[n][F_NAME])
    next

    d:=directory(dspec+dirsep()+"*","HD")
    for n:=1 to len(d)
        if( "D"$d[n][F_ATTR] .and.;
            !d[n][F_NAME]=="." .and.;
            !d[n][F_NAME]==".." )
            exelst(lst,dspec+dirsep()+d[n][F_NAME])
        end
    next

    return lst
    
******************************************************************************
static function fnameext(name)   // name.ext
local bslpos:=rat(dirsep(),name)
    name:=substr(name,bslpos+1)
    return alltrim(name)

******************************************************************************
static function fpath0(name) // path
local bslpos:=rat(dirsep(),name)
    if( 0<bslpos )
        return left(name,bslpos-1)
    end
    return ""

******************************************************************************
