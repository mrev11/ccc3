
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

#include "savex.ch"
#include "statvar.ch"

******************************************************************************    
function compFile(brw,opt)

local f:=brwArray(brw)[brwArrayPos(brw)][IDX_FILE]
local timesave:=brwArray(brw)[brwArrayPos(brw)][IDX_SAVE]
local timework:=brwArray(brw)[brwArrayPos(brw)][IDX_WORK]

local w:=s_work+f
local s:=s_save+f
local fc//:=if(opt==.t.,getenv("CMP"),getenv("DIFF"))
local temp:=tempdir()
//local screen:=savescreen(0,0,maxrow(),maxcol())

    if( opt!=.t. .and. isbinfile(w,1) )
        if( 2!=alert(w+" looks like a binary file",{"Compare as binary", "Compare as text"}) )
            opt:=.t.
        end
    end

    fc:=if(opt==.t.,getenv("CMP"),getenv("DIFF"))
    if( empty(fc) )
        fc:=if(opt==.t.,DEFAULT_CMPBIN,DEFAULT_CMPTXT)
    end

    if( opt==.t. )    
        run (fc+" "+escape(s)+" "+escape(w)+" >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
    else
        //osszehasonlitas elott a filekbol ki kell
        //venni a CR-eket, es egyseges kodrendszerre 
        //kell transzformalni

        removecr_file(w,temp+"work")
        removecr_file(s,temp+"save")
        
        if( timesave<timework )
            run (fc+" "+temp+"save "+temp+"work >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
        else
            run (fc+" "+temp+"work "+temp+"save >"+temp+"fc_diff"+" 2>"+temp+"fc_err")
        end
    end
    
    if( !empty(memoread(temp+"fc_err")) )
        dolist(temp+"fc_err",s_list,DEFAULT_LIST)
    elseif( !empty(memoread(temp+"fc_diff")) )
        dolist(temp+"fc_diff",s_list,DEFAULT_LIST)
    else
        alert("Files match.") //no output from diff
    end
    
    //clear screen //2003.01.01
    //restscreen(0,0,maxrow(),maxcol(),screen)
    //setcursor(0) //hatastalan ???!
    //return NIL


******************************************************************************    
static function removecr_file(f,f1)
local x:=memoread(f,.t.)
    x:=removecr(x)
    memowrit(f1,x)
    return NIL


******************************************************************************    
function removecr(x)
    x:=strtran(x,bin(13))
    return x


******************************************************************************    
