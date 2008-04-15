
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

function _GTKAPI(col,exp)
static dbf
    if(empty(dbf))
        dbf:=tabNew("GTKAPI")
        tabAddColumn(dbf,{"CAPI"      ,"C", 48, 0})
        tabAddColumn(dbf,{"CCCAPI"    ,"C", 48, 0})
        tabAddColumn(dbf,{"KIHAGY"    ,"C",  2, 0})
        tabAddColumn(dbf,{"ISFUNCTION","L",  1, 0})
        tabAddColumn(dbf,{"ISMETHOD"  ,"L",  1, 0})
        tabAddColumn(dbf,{"ISCONSTRUC","L",  1, 0})
        tabAddColumn(dbf,{"CLNAME"    ,"C", 24, 0})
        tabAddColumn(dbf,{"MODNAME"   ,"C", 24, 0})
        tabAddColumn(dbf,{"STATE"     ,"C",  4, 0})
        tabAddColumn(dbf,{"RETTYPE"   ,"C", 24, 0})
        tabAddColumn(dbf,{"RETOPTION" ,"L",  1, 0})
        tabAddColumn(dbf,{"VARARGS"   ,"L",  1, 0})
        tabAddColumn(dbf,{"CCC"       ,"C",128, 0})
        tabAddColumn(dbf,{"CODEBLOCK" ,"C",256, 0})
        tabAddColumn(dbf,{"PARAMETERS","C",512, 0})
        tabAddIndex(dbf,{"CAPI","GTKAPI1",{"CAPI"}})
    end
    if(col==NIL)
        return dbf
    end
    return tabEvalColumn(dbf,col,exp)

