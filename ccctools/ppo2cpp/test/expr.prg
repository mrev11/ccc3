
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

#include "hopp.h"

function hopp()
    return NIL

static function _clp_zsupsz(b1)
local a:="1",b,c

    a:="proba szerencse"
    a:=.t.
    a:=.f.
    b:=!a
    a:=a.and.(b.or.a).or.a$"proba szerencse"
    a:=b==c.or.b!=c
    a:=b<c.or.b>c
    a:=b<=c.or.b>=c
    a:=b-1*10-2-3-4+5
    a:=-(2*10-2+3-4*5)
    a:=+(2*10-2+3-4*5)
    c:=a++
    c:=a--
    c:=++a
    c:=--a

    a:=b
    a+=b
    a-=b
    a*=b
    a/=b
    a%=b

    a[1+2+3]
    a[c+1+2+3]
    a[c]

    a[1+2+3]:=1
    a[c+1+2+3]:=1
    a[c]:=1
    
    a:=alias->field
    alias->field:=1+2+3
    alias->field+=1
    alias->field*=10
    alias->field++
    alias->field--
    
    (a):=b
    a:={1,,,2,b+c}

    a:=probafunc()
    a:=probafunc(c)
    a:=probafunc(1,,,2,b+c)
    a:=probafunc(,,,2,)
    
    a:loop
    a:method
    a:method()
    a:method:=b
    a:method(b)
    a:method():=b
    a:method(b,c)
    a:method(b):=c

    a:(class)method
    a:(class)method()
    a:(class)method:=b
    a:(class)method(b)
    a:(class)method():=b
    a:(class)method(b,c)
    a:(class)method(b):=c

    a:(parent@class)method
    a:(parent@class)method()
    a:(parent@class)method:=b
    a:(parent@class)method(b)
    a:(parent@class)method():=b
    a:(parent@class)method(b,c)
    a:(parent@class)method(b):=c

    a:(super@class)method
    a:(super@class)method()
    a:(super@class)method:=b
    a:(super@class)method(b)
    a:(super@class)method():=b
    a:(super@class)method(b,c)
    a:(super@class)method(b):=c
    
    a:=if(b,c-1,c+1)
    a:=()
    a:=(b)
    a:=(a+a,b+b,c+c)
    
    return NIL

