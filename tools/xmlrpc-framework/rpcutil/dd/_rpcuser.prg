
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

function _RPCUSER(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("RPCUSER")
        tabPath(dbf,"RPCBASE\")
        tabAddColumn(dbf,{"UID"       ,"C", 16, 0})
        tabAddColumn(dbf,{"TID"       ,"C", 16, 0})
        tabAddColumn(dbf,{"GID"       ,"C", 64, 0})
        tabAddColumn(dbf,{"NAME"      ,"C", 64, 0})
        tabAddColumn(dbf,{"PASSWORD"  ,"C", 16, 0})
        tabAddColumn(dbf,{"STARTDATE" ,"D",  8, 0})
        tabAddColumn(dbf,{"ENDDATE"   ,"D",  8, 0})
        tabAddIndex(dbf,{"USER","RPCUSER1",{"UID"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)

