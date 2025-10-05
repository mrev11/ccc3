
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
#include "box.ch"

#include "dirsync.ver"
#include "dirsync.ch"
#include "statvar.ch"


****************************************************************************
function savebrowse()

local dbrw,colFile,colWork,colSave
local brw:=brwCreate(0,0,maxrow(),maxcol())
local olvas:={},rendez:={},timecorr:={}
local x,repeat:=.f.
    
    dbrw:=makearr()
    if( len(dbrw)<1 )
        aadd(dbrw,{"",space(16),space(16),0})
    end

    brwArray(brw,dbrw)

    if( ""==s_save )
        colFile:=brwColumn(brw,"File",f0Block(brw,IDX_FILE),FISIZE)
        colWork:=brwColumn(brw,"Date/Time",d0Block(brw,IDX_WORK))
    else
        colFile:=brwColumn(brw,"File",fiBlock(brw,IDX_FILE),FISIZE)
        colSave:=brwColumn(brw,formDir(s_save),dtBlock(brw,IDX_SAVE))
        colWork:=brwColumn(brw,formDir(s_work),dtBlock(brw,IDX_WORK))

        colFile:footing:="Compare = -m"+s_compmode
        colSave:footing:="SAVE"
        colWork:footing:="WORK"
        brw:footSep:=B_HS+B_SS2+B_HS
    end

    brwColumn(brw,"Size",brwABlock(brw,IDX_SIZE),"99999,999,999")
    
    brw:freeze:=1
    if( !""==s_save )
        colSave:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]>dbrw[x][IDX_WORK],{6,6},{1,2})}
    end
    colWork:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]<dbrw[x][IDX_WORK],{6,6},{1,2})}
    
    brwMenuName(brw,"["+alltrim(transform(len(dbrw),"999,999,999"))+"]")

    if( !""==s_save )

        aadd(olvas,{"-m0: exist here and there, differ   ",{||S_COMPMODE("0"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-m1: exist here and there           ",{||S_COMPMODE("1"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-m2: exist here and there, match    ",{||S_COMPMODE("2"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mW: newer in WORK or missed in SAVE",{||S_COMPMODE("W"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mS: newer in SAVE or missed in WORK",{||S_COMPMODE("S"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mD: unio of -mW and -mS            ",{||S_COMPMODE("D"),repeat:=.t.,break("X")}})
        brwMenu(brw,"Reread","Read disks and compare files",olvas)  //R shortcut megszunt

        brwMenu(brw,"Save",formDir(s_save,35)+" <-- "+formDir(s_work,35),{||repeat:=.t.,copySave(brw)}) //S shortcut megszunt
        brwMenu(brw,"Freshen",formDir(s_save,35)+" --> "+formDir(s_work,35),{||repeat:=.t.,copyFreshen(brw)}) //F shortcut megszunt
 
        aadd(timecorr,{"Reset datetime in SAVE if file contents are the same",{||repeat:=.t.,copyTime(brw,.f.),break("X")}})
        aadd(timecorr,{"Reset datetime in WORK if file contents are the same",{||repeat:=.t.,copyTime(brw,.t.),break("X")}})
        brwMenu(brw,"Time","Reset datetime if file contents are the same",timecorr)

        brwMenu(brw,"DelSav","Delete newer files in SAVE",{||repeat:=.t.,delSave(brw)})
        brwMenu(brw,"DelWrk","Delete newer files in WORK",{||repeat:=.t.,delWork(brw)})

        //brwMenu(brw,"Skip","Skip selected row from comparing and saving",{||skiprow(brw)},"S") //megszunt, helyette shortcut
        brwMenu(brw,"TxtCmp","Diff text files (by rows)",{||compFile(brw),.t.},"T")
        brwMenu(brw,"BinCmp","Compare binary files",{||compFile(brw,.t.),.t.},"B")

        brwApplyKey(brw,{|b,k|applykey2(b,k)})
    else
        brwApplyKey(brw,{|b,k|applykey1(b,k)})
    end

    aadd(rendez,{"By date-time",{||sortTime(brw)}})
    aadd(rendez,{"By name (default)",{||sortName(brw)}})
    aadd(rendez,{"By basename",{||sortBaseName(brw)}})
    aadd(rendez,{"By reverse basename",{||sortReverseBaseName(brw)}})
    aadd(rendez,{"By extension",{||sortExtension(brw)}})
    aadd(rendez,{"By size",{||sortSize(brw)}})
    brwMenu(brw,"Sort","Set order by name, time, size",rendez,"S")

    brwMenu(brw,"List","List rows to standard output",{||listbrw(brw)},"L")
 
    brwCaption(brw,"DirSYNC "+VERZIO)
    brwSetFocus(brw)    
    brwShow(brw)

    begin
        brwLoop(brw)
    recover x <C>
        //alert("ujraolvas")
    //recover x
    //  minden mas kivetel hiba,
    //  amit a default hibakezelo kap el
    end

    brwHide(brw)

    return repeat

******************************************************************************    
static function applykey1(brw,key) //onedir mode

local f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]

    if( key==K_ALT_S )
        skiprow(brw)
        return .t.

    elseif( key==K_F3 )
        dolist(s_work+f,s_list,DEFAULT_LIST)
        return .t.

    elseif( key==K_F4 )
        dolist(s_work+f,s_edit,DEFAULT_EDIT)
        return .t.

    elseif( key==K_ALT_P )
        play(brw)
        return .t.

    elseif( key==asc("/") ) 
        find_file(brw)
        return .t.

    elseif( key==K_ALT_G ) 
        gc()
        return .t.
    end


******************************************************************************    
static function applykey2(brw,key) //twodir mode

local f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]

    if( key==K_ALT_S )
        skiprow(brw)
        return .t.

    elseif( key==K_ALT_R .and. 2==alert("Reset old version?",{"Escape","Continue"}) )
        resetold(brw)
        skiprow(brw)
        return .t.

    elseif( key==K_ALT_N .and. 2==alert("Copy new version?",{"Escape","Continue"}) )
        copynew(brw)
        skiprow(brw)
        return .t.

    elseif( key==K_ALT_P )
        play(brw)
        return .t.

    elseif( key==asc("/") ) 
        find_file(brw)
        return .t.

    elseif( key==K_ALT_G ) 
        gc()
        return .t.
    end


******************************************************************************    
static function fiBlock(brw,idx)
local arr:=brwArray(brw)
    return {||arrow(brw)+formFile(arr[brwArrayPos(brw)][idx],FISIZE-1)}


******************************************************************************    
static function f0Block(brw,idx)
local arr:=brwArray(brw)
    return {||formFile(arr[brwArrayPos(brw)][idx],FISIZE)}


******************************************************************************    
static function dtBlock(brw,idx)
local arr:=brwArray(brw)
    return {||substr(arr[brwArrayPos(brw)][idx],3,DTSIZE)}


******************************************************************************    
static function d0Block(brw,idx)
local arr:=brwArray(brw)
    return {|d|d:=arr[brwArrayPos(brw)][idx],;
               dtoc(stod(left(d,8)))+" "+substr(d,9) }


****************************************************************************
