
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

//RSA titkosítás szemléltetése


#include "bignum.imp"  //gyakorlat: using utasítás


function main()

local x:=str2bin("Öt szép szűzlány őrült írót nyúz.")   //üzenet (<m)
//local x:=str2bin("Öt szép szűzlány.")   //üzenet (<m)

//local p1:=bignum("5333")      //prím
//local p2:=bignum("3571")      //prím
//local e:=bignum("877")        //nyilvános kulcs (encoding)

local p1:=bignum("xc0e99898d785473a911aef243a88801d95d561c595c09aa9c145a1b169ff0393")
local p2:=bignum("xe06788d7204b7176a8cb4d8d5689e43c818de740c16e19db6a77a329db81f5cf")
//local  e:=bignum("xd4a7c0750abaee104eb69be00bdf989b")
local  e:=bignum("xF49589CECEF3628104E8C927DFEB2C68C04A00C3CCEABB56276A7FA221A69695")


//local p1:=bignum("xfc5fa17cbe427de78ffe895e679843a9c064339245d5f753fcc7d2858314682a73660168cf24316e3eb1c0c4a5f79d1e90a9778a595bc06c388a76d03684598750473a258520ad4f27f81563a7b5094126d1afc53ccba398f0f9015a5b7f6c877a43bd7e1c468ff4e865f426fca8ea757e79a714e42539d5cf00455c3198a2cb")
//local p2:=bignum("xd20ccaf6a5a5aeff29b44625b1cd0fed241039cad18478a4c1b6ef50de3c8fb1e3af607534c8c9ef2b0c000c044b710ba7f64e7abfc57fa591349b05af9271f98651b0f4bea0fa3f3b4cb5a1811f8b9f52beef7cbcb8fc2ba0e8e135c9588cc7e2598223a578d2b92a4d60dfb4ea52c2601c515bdd88ae23cd40e43800c34e15")
//local  e:=bignum("xebe90a415d72d13f6b0b627f5dfd3f2bb6b3aed0d34ac89aa777e4beeb8fe7b5b017aa96707171dc965784201f05cec977ee02ecb86137ae03b53151787ee27cd8261d298ce93e684341a99c75440cce1172e218aaeaa6403f5fd1cb17321fe2d844ce096009ac80cc61abf4da78f4a4f001444e38ab583b819b35847f06172d")

//local p1:=bignum("xe82a622a773d43f38eda7146285cf337")
//local p2:=bignum("xd9ff60adcf288fe78edc6c1c2545ecdd")
//local  e:=bignum("xdfb4fd321a2e6ede9e52ba3884eb6797")

local d                         //titkos kulcs (decoding)

local p11:=sub(p1,x"01")        //p1-1
local p21:=sub(p2,x"01")        //p2-1

local m:=mul(p1,p2)             //nyilvános modulus
local Fm:=mul(p11,p21)          //(p1-1)*(p2-1) Euler féle Fi függvény

    if( cmp(x,m)>=0 )
        ? "túl nagy az üzenet"
        quit
    end
   
    d:=inv(e,Fm)                //moduló inverz: titkos kulcs
   
    //? "p1",tostr(p1,16)
    //? "p2",tostr(p2,16)

    ? "m",tostr(m,16)
    //? "Fm",tostr(Fm,16)

    ? "e",tostr(e,16)           //nyilvános kulcs, (Fm,e)=1
    ? "d",tostr(d,16)           //titkos kulcs, d*e=1 (mod Fm)
    
    ? "msg",x                   //nyilvános üzenet 
    ?

    x:=pow(x,e,m)               //kódolt üzenet
    ? "enc",tostr(x,16)
    ?
                                //az üzenet az e nyilvános kulccsal kódolva,
                                //csak a d titkos kulcs birtokosa tudja dekódolni

    x:=pow(x,d,m)               //dekódolt üzenet, egyezik az eredetivel
    ? "dec",x
    ?

