
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

namespace bignum

#ifdef EMLEKEZTETO
    Euklideszi algoritmussal számolunk moduló inverzet.
    Az a és b szám lnko-ja azon pozitív számok minimuma,
    amik előállnak xa+yb  alakban, ahol x és y tetszőleges 
    egészek. Legyen b=m és (a,m)=1, akkor 1=xa+ym,
    azaz xa=1 (mod m), tehát x a moduló inverz.
    
    A moduló inverz így is számolható: a^(m-2), ui.
    a^(m-2)a=a^(m-1)=1 (mod m) a kis Fermat tétel miatt.
    x:=bignum.pow(a,bignum.sub(m,x"02"),m)
#endif    

******************************************************************************
function inv(a,m) //(euklideszi algoritmus)

local r1:=m
local r2:=a
local q,r
local x:={x"00",x"01",NIL}

    while( len(r2)>0 )
        q:=bignum.div(r1,r2,@r)
        r1:=r2
        r2:=r
        x[3]:=subx(x[1],bignum.mul(q,x[2]),m) //x3=x1-q*x2
        adel(x,1)  //{x1,x2,x3}->{x2,x3,NIL}
    end
    
    return x[1] 

******************************************************************************
static function subx(a,b,m) //a-b, b>a esetén moduló
local x,m1
    if( bignum.cmp(a,b)>=0 ) //a>=b
        x:=bignum.sub(a,b)
    else
        m1:=bignum.sub(m,x"01") //m-1 = -1 (mod m)
        b:=bignum.mul(b,m1) //==-b (mod m)
        x:=bignum.add(a,b)
        x:=bignum.mod(x,m)
    end
    return x

******************************************************************************
