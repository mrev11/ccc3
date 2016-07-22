
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

#include "savex.ver"
#include "savex.ch"
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

    if( "."==s_save )
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

    brwColumn(brw,"Size",brwABlock(brw,IDX_SIZE),"9999,999,999")
    
    brw:freeze:=1
    if( !"."==s_save )
        colSave:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]>dbrw[x][IDX_WORK],{6,6},{1,2})}
    end
    colWork:colorBlock:={|x|x:=brwArrayPos(brw),if(dbrw[x][IDX_SAVE]<dbrw[x][IDX_WORK],{6,6},{1,2})}
    
    brwMenuName(brw,"["+alltrim(str(len(dbrw)))+"]")

    if( !"."==s_save )

        aadd(olvas,{"-m0: exist here and there, differ   ",{||S_COMPMODE("0"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-m1: exist here and there           ",{||S_COMPMODE("1"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-m2: exist here and there, match    ",{||S_COMPMODE("2"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mW: newer in WORK or missed in SAVE",{||S_COMPMODE("W"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mS: newer in SAVE or missed in WORK",{||S_COMPMODE("S"),repeat:=.t.,break("X")}})
        aadd(olvas,{"-mD: unio of -mW and -mS            ",{||S_COMPMODE("D"),repeat:=.t.,break("X")}})
        brwMenu(brw,"Reread","Read disks and compare files",olvas,"R")

        brwMenu(brw,"Save",formDir(s_save,35)+" <-- "+formDir(s_work,35),{||repeat:=.t.,copyMent(brw)},"S")
        brwMenu(brw,"Freshen",formDir(s_save,35)+" --> "+formDir(s_work,35),{||repeat:=.t.,copyFrissit(brw)},"F")
 
        aadd(timecorr,{"Reset datetime in SAVE if file contents are the same",{||repeat:=.t.,copyIdo(brw,.f.),break("X")}})
        aadd(timecorr,{"Reset datetime in WORK if file contents are the same",{||repeat:=.t.,copyIdo(brw,.t.),break("X")}})
        brwMenu(brw,"Time","Reset datetime if file contents are the same",timecorr)

        brwMenu(brw,"DelSav","Delete newer files in SAVE",{||repeat:=.t.,delSave(brw)})
        brwMenu(brw,"DelWrk","Delete newer files in WORK",{||repeat:=.t.,delWork(brw)})

        brwMenu(brw,"Skip","Skip selected row from comparing and saving",{||kihagy(brw)},"S")
        brwMenu(brw,"TxtCmp","Diff text files (by rows)",{||compFile(brw),.t.},"T")
        brwMenu(brw,"BinCmp","Compare binary files",{||compFile(brw,.t.),.t.},"B")
    else
        brwApplyKey(brw,{|b,k|applykey(b,k)})
    end

    aadd(rendez,{"By date-time",{||sortIdo(brw)}})
    aadd(rendez,{"By name (default)",{||sortNev(brw)}})
    aadd(rendez,{"By basename",{||sortBaseName(brw)}})
    aadd(rendez,{"By size",{||sortMeret(brw)}})
    brwMenu(brw,"Sort","Set order by name, time, size",rendez,"S")

    brwMenu(brw,"List","List rows to standard output",{||listbrw(brw)},"L")
 
    brwCaption(brw,"SAVEX "+VERZIO)
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
static function applykey(brw,key)

local f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]

    if( key==K_F3 )
        dolist(f,s_list,DEFAULT_LIST)
        return .t.

    elseif( key==K_F4 )
        dolist(f,s_edit,DEFAULT_EDIT)
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
