
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

//A driverekben definiált osztály egyszerűsített változata,
//ami csak adattárolásra képes, viszont adatbázisfüggetlen.


namespace tdsutil

******************************************************************************
class columndef(tdsutil.columnref)
    method  initialize
    attrib  type        // típus: Cw, Nw[,d], D, L, M 
    attrib  notnull     // .t., ha a mező nem lehet null
    attrib  default     // default érték null helyett
    attrib  label
    attrib  tooltip
    attrib  picture

******************************************************************************
static function columndef.initialize(this,nam,exp,typ)
    this:(tdsutil.columnref)initialize(nam,exp)  
    this:type:=typ
    this:notnull:=.f.  //default: lehet null
    return this

******************************************************************************
