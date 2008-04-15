
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

static x1
static x2:=NIL
static x3:=123
static x4:=.t.
static x5:="pr?ba szerencse"
static x6:={1,2,3,4}
static x7:={|a,b,c|(-b+sqrt(b**2-4*a*c))/(2*a)}
static x8:={|a,b,c|(-b-sqrt(b**2-4*a*c))/(2*a)}
static x9:=hipp()+hopp()


function proba()

static y1
static y2:=NIL
static y3:=123
static y4:=.t.
static y5:="pr?ba szerencse"
static y6:={1,2,3,4}
static y7:={|a,b,c|(-b+sqrt(b**2-4*a*c))/(2*a)}
static y8:={|a,b,c|(-b-sqrt(b**2-4*a*c))/(2*a)}
static y9:=hipp()+hopp()

    x1:=y1
    y1:=x1

    return NIL

