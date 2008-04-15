
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

function _SESSION(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("SESSION")
        tabPath(dbf,"RPCBASE\")
        tabAddColumn(dbf,{"SID"       ,"C", 24, 0})
        tabAddColumn(dbf,{"SRVNAME"   ,"C", 16, 0})
        tabAddColumn(dbf,{"SECONDS"   ,"N",  6, 0})
        tabAddColumn(dbf,{"UID"       ,"C", 16, 0})
        tabAddColumn(dbf,{"TID"       ,"C", 16, 0})
        tabAddColumn(dbf,{"DATETIME"  ,"C", 16, 0})
        tabAddColumn(dbf,{"DBMDATA"   ,"C", 10, 0})
        tabAddIndex(dbf,{"SID","SESSION1",{"SID","SRVNAME"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)

#ifdef _cl_
function _SESSION_DATA(exp)
static col
    if(col==NIL)
        col:=tabColNumber(_SESSION(),"DBMDATA")
    end
    return _SESSION(col,exp)
#endif

