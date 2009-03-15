
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
function main()
    jtencoding("utf-8")
    alertblock({|t,a|jtalert(t,a)})
    msgloop( makedlg() )

******************************************************************************
static function msgloop(dlg)
    while( NIL!=dlg:getmessage )
    end

******************************************************************************
static function makedlg()
local dlg:=jtdialogNew(),brw

    dlg:caption:="Celledit Application" 
    dlg:layout:="vbox"

    brw:=dlg:add(jtbrowsearrayNew())
    brw:name:="brw"
    brw:array:={{1,"aaaa",date()+1,.f.},;
                {2,"bbbb",date()+2,.f.},;
                {3,"cccc",date()+3,.f.},;
                {4,"dddd",date()+4,.f.},;
                {5,"eeee",date()+5,.f.},;
                {6,"ffff",date()+6,.f.},;
                {7,"gggg",date()+7,.f.},;
                {8,"hhhh",date()+8,.f.};
                }

    brw:addcolumn("Szám  ",1,"@N 999,999.99"):editable:=.t.
    brw:addcolumn("Betű  ",2,"@C XX-XX"):editable:=.t.
    brw:addcolumn("Dátum ",3,"@D"):editable:=.t.
    brw:addcolumn("Bool  ",4,"@L"):editable:=.t.
    
    dlg:add( jtpushNew("Hopp") )
    dlg:add( jtpushNew("Close") ):actionblock:={||dlg:close}

    dlg:show
    brw:pagefirst
    return dlg

******************************************************************************
 