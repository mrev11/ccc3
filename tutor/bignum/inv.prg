
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

//tesztprogram a moduló inverzhez


function main()

local a,b,m,x,n

    a:=bignum.bignum("xd9ff60adcf288fe78edc6c1c2545ecdd")
    b:=bignum.bignum("178958329213930680822105728551584389230")
    m:=bignum.bignum("xdfb4fd321a2e6ede9e52ba3884eb6797")


    b:=bignum.pow(a,bignum.sub(m,x"02"),m)
    ? "b",bignum.tostr(b)

    //a:=bignum.bignum("x36d")
    //b:=bignum.bignum("xcea9d")
    //m:=bignum.bignum("x1227468")

    //a:=bignum.bignum("23")
    //b:=bignum.bignum("27")
    //m:=bignum.bignum("31")

    //a:=bignum.bignum("7")
    //b:=bignum.bignum("2")
    //m:=bignum.bignum("13")



    ? "a",bignum.tostr(a)
    ? "b",bignum.tostr(b)
    ? "m",bignum.tostr(m)
    
    b:=bignum.inv(a,m)  ; ? "inv",bignum.tostr(b)
    a:=bignum.inv(b,m)  ; ? "inv",bignum.tostr(a)

    x:=bignum.mul(a,b); ? "mul",bignum.tostr(x)
    x:=bignum.mod(x,m); ? "mod",bignum.tostr(x)

    ? "a",bignum.tostr(a)
    ? "b",bignum.tostr(b)
    ? "m",bignum.tostr(m)

    ?
    