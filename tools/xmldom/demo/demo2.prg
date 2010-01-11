
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

//kilistázza az ügyfél objektumokat

****************************************************************************
function main(fname)
local p:=xmlparserNew(fname) 

    p:processblock:={|node|feldolgozo(node)}
    p:parse  

    ? //"maximális stack méret:", yaccmaxidx() 
    return NIL

****************************************************************************
static function feldolgozo(node)

    if( node:type=="ugyfel" )
        node:xmlout
    end
    
    return .t. //nem kell az objektumfa

****************************************************************************
 