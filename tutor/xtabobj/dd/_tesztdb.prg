
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

function _TESZTDB(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("TESZTDB")
        tabAddColumn(dbf,{"NAME"      ,"C", 13, 0})
        tabAddColumn(dbf,{"SIZE"      ,"N",  8, 0})
        tabAddColumn(dbf,{"DATE"      ,"D",  8, 0})
        tabAddColumn(dbf,{"TIME"      ,"C", 10, 0})
        tabAddColumn(dbf,{"ATTR"      ,"C",  1, 0})
        tabAddColumn(dbf,{"EXTRA"     ,"X", 32, 0})
        tabAddColumn(dbf,{"DBMEXTRA"  ,"C", 10, 0})
        tabAddIndex(dbf,{"NAME","TESZTDB1",{"NAME"}})
        tabAddIndex(dbf,{"SIZE","TESZTDB2",{"SIZE"}})
        tabAddIndex(dbf,{"TIME","TESZTDB3",{"DATE","TIME"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)

