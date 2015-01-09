
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

namespace sql2.mysql


******************************************************************************
class columnref(object)
    method  initialize
    attrib  name            // a mező programbeli neve
    attrib  expr            // oszlopkifejezés
    attrib  columnid        // oszlopazonosító

******************************************************************************
static function columnref.initialize(this,name,expr)  
    this:(object)initialize

    this:name:=name

    if( expr==NIL )
        this:expr:=sql2.mysql.quotedname(name)
    else
        this:expr:=sql2.mysql.quotedname(expr)
    end
    
    this:columnid:=atail(split(this:expr,".")) //update-hez

    return this


******************************************************************************
