
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

function _DDICT(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("DDICT")
        tabAddColumn(dbf,{"TABLE"     ,"C", 15, 0})
        tabAddColumn(dbf,{"VERSION"   ,"N",  4, 0})
        tabAddColumn(dbf,{"INDNAME"   ,"C", 10, 0})
        tabAddColumn(dbf,{"INDFILE"   ,"C", 16, 0})
        tabAddColumn(dbf,{"STATE"     ,"C",  1, 0})
        tabAddColumn(dbf,{"STRDATE"   ,"C", 16, 0})
        tabAddColumn(dbf,{"INDFIELD"  ,"C",128, 0})
        tabAddColumn(dbf,{"DIRECTORY" ,"C", 32, 0})
        tabAddColumn(dbf,{"OWNER"     ,"C",  8, 0})
        tabAddColumn(dbf,{"DBMSTRUCT" ,"C", 10, 0})
        tabAddIndex(dbf,{"TABLE","DDICT",{"TABLE","VERSION","INDFILE"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)

