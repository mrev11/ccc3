
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

#include "dirsync.ch"
#include "statvar.ch"


******************************************************************************    
function sortName(brw)
local arr:=brwArray(brw)
    #ifdef WINDOWS
        //megj: pontosan az a rendezes kell, mint ami rdir-ben van
        asortkey(arr,{|x,key|key:=x[IDX_FILE]+chr(0), key:=upper(key)+key },.t.)
    #else
        asortkey(arr,{|x,key|key:=x[IDX_FILE]+chr(0), key                 },.t.)
    #endif
    brw:refreshAll()


******************************************************************************    
function sortBaseName(brw)
local arr:=brwArray(brw)
    #ifdef WINDOWS
        asortkey(arr,{|x|upper(fnameext(x[IDX_FILE]))+chr(0)+x[IDX_FILE]},.t.)
    #else
        asortkey(arr,{|x|      fnameext(x[IDX_FILE]) +chr(0)+x[IDX_FILE]},.t.)
    #endif
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortReverseBaseName(brw)
local arr:=brwArray(brw)
    #ifdef WINDOWS
        asortkey(arr,{|x|upper(fnameext(x[IDX_FILE]))+chr(0)+x[IDX_FILE]},.f.)
    #else
        asortkey(arr,{|x|      fnameext(x[IDX_FILE]) +chr(0)+x[IDX_FILE]},.f.)
    #endif
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortExtension(brw)
local arr:=brwArray(brw)
    #ifdef WINDOWS
        asortkey(arr,{|x|upper(fext(x[IDX_FILE]))+chr(0)+x[IDX_FILE]},.t.)
    #else
        asortkey(arr,{|x|      fext(x[IDX_FILE]) +chr(0)+x[IDX_FILE]},.t.)
    #endif
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortTime(brw)
local arr:=brwArray(brw)
    if( "S"$s_compmode )
        asort(arr,,,{|x,y|x[IDX_SAVE]>y[IDX_SAVE]})
    else
        asort(arr,,,{|x,y|x[IDX_WORK]>y[IDX_WORK]})
    end
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortSize(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|x[IDX_SIZE]>y[IDX_SIZE]})
    brw:refreshAll()
    return NIL


******************************************************************************    
