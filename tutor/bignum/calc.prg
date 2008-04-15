
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

//tesztprogram az alapműveletekhez

function main(op,arg1,arg2,arg3)

local a,b,m,x,r

    a:=bignum.bignum(arg1)
    b:=bignum.bignum(arg2)


    if(arg3!=NIL)
        m:=bignum.bignum(arg3)
    end
    
    if( op=="add" )
        x:=bignum.add(a,b)
        op:=" + "

    elseif( op=="sub" )
        x:=bignum.sub(a,b)
        op:=" - "

    elseif( op=="mul" )
        x:=bignum.mul(a,b)
        op:=" * "

    elseif( op=="div" )
        x:=bignum.div(a,b,@r)
        op:=" / "

    elseif( op=="mod" )
        x:=bignum.mod(a,b)
        op:=" % "

    elseif( op=="pow" )
        x:=bignum.pow(a,b,m)
        op:=" ^ "
    end

    ? bignum.tostr(a)
    ? bignum.tostr(b)
    ? bignum.tostr(x)

    if( r!=NIL )
        ? bignum.tostr(r)
    end
    ?

    bc(op,a,b)
    


static function bc(op,a,b)
local x

    x:=bignum.tostr(a)+op+bignum.tostr(b)+endofline()
    x+="quit"+endofline()
    memowrit("bc",x)
    run( "bc -q bc" )
        

