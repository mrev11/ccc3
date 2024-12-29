
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

******************************************************************************
function direxist(dirspec)   //nincs NG-ben 

local mode
    mode:=stat_st_mode(dirspec)
    return mode!=NIL .and. s_isdir(mode)

 
******************************************************************************
function fileexist(fspec)  //nincs NG-ben
//The difference between file() and fileexist():
//fileexist() returns .f., if fspec is a directory.

local mode:=stat_st_mode(fspec)
    return mode!=NIL .and. !s_isdir(mode)


******************************************************************************
#ifdef WINDOWS

function fileisexecutable(fspec)  //nincs NG-ben 
    return fileexist(fspec) .and.;
           bin2str("."+upper(right(fspec,3))+".") $ ".EXE.BAT.COM."

#else

function fileisexecutable(fspec)  //nincs NG-ben 
local mode:=stat_st_mode(fspec)
    return mode!=NIL .and. !s_isdir(mode) .and. 0!=numand(mode,oct2l("111"))

#endif 


******************************************************************************
 