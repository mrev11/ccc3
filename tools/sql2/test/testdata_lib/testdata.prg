
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

static function testdata.init()
local libdata:=simplehashNew()
    libdata['testdata.c']:={|c|.testdata.c.tableEntityNew(c)}
    libdata['testdata.a']:={|c|.testdata.a.tableEntityNew(c)}
    libdata['testdata.b']:={|c|.testdata.b.tableEntityNew(c)}
    return libdata

function testdata(name,conn)
static libdata:=testdata.init(),blk
    if( name==NIL )
        return libdata //hashtable
    elseif( conn==NIL )
        return libdata[name] //codeblk
    else
        blk:=libdata[name]
        if( blk!=NIL )
            return eval(blk,conn) //tableentity
        end
    end
