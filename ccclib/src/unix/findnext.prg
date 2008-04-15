
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

//Clipper findfirst/findnext implemented by directory()

static find:=NIL //{pos,dirlist}

**************************************************************************
function findfirst(mask,type)  //nincs NG-ben
    find:={1,directory(mask,type)}
    return findnext()

**************************************************************************
function findnext() //nincs NG-ben 
    if( find==NIL .or. find[1]>len(find[2]) )
        return NIL
    end
    return find[2][find[1]++]

**************************************************************************
function findclose()
    find:=NIL
    return NIL

**************************************************************************
function findsave()
    return if(find==NIL,NIL,aclone(find))

**************************************************************************
function findrest(fsave)
    if( fsave==NIL )
        find:=NIL
    else
        find:=aclone(fsave)
    end
    return NIL

**************************************************************************

