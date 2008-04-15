
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

******************************************************************************
class base(object)
    attrib attrib
    method method
    method step  //máshol kulcsszó

static function base.method(this,x,y)
    if( x!=NIL )
        this:attrib:=x
    end
    ? "base.method      ",this:classname,this:attrib,y

static function base.step(this)
    ? "base.step        ",this:classname,this:attrib

******************************************************************************
class derived(base)
    method method
    method method2      {||qout("derived.method2")}

static function derived.method(this,x)
    if( x!=NIL )
        this:attrib:=x
    end
    ? "derived.method   ",this:classname,this:attrib
    

******************************************************************************
function main()

local b:=baseNew()
local d:=derivedNew()

    //Megjegyzés:
    //Az osztály és metódusnevek binaryban tárolódnak,
    //azért az összes hibaágat újra kell tesztelni.

    //d:methodx                 //no exported method
    //d:(derived)methodx        //no exported method
    //d:(derivedx)method        //not a valid classname
    //d:(base)method2           //no exported method

    //d:(base@derived)methodx   //no exported method
    //d:(base@derivedx)method   //not a valid classname
    //d:(basex@derived)method   //not a valid classname

    //d:(object@derived)method  //is not parent of
    //d:(super@derivedx)method  //not a valid classname
    //d:(super@derived)methodx  //no exported method

    ? "-------------------"
    ? "b:method"
    ? "-------------------"

    b:method //kulcsszó!
    b:method(0)
    b:method:=1
    b:method(2)
    b:method():=3
    b:method(4,5)
    b:method(5):=6
    b:step //kulcsszó

    ? "-------------------"
    ? "d:(base)method"
    ? "-------------------"

    d:(base)method
    d:(base)method(0)
    d:(base)method:=1
    d:(base)method(2)
    d:(base)method():=3
    d:(base)method(4,5)
    d:(base)method(5):=6
    d:(base)step

    ? "-------------------"
    ? "d:(base@derived)method"
    ? "-------------------"

    d:(base@derived)method
    d:(base@derived)method(0)
    d:(base@derived)method:=1
    d:(base@derived)method(2)
    d:(base@derived)method():=3
    d:(base@derived)method(4,5)
    d:(base@derived)method(5):=6
    d:(base@derived)step

    ? "-------------------"
    ? "d:(super@derived)method"
    ? "-------------------"

    d:(super@derived)method
    d:(super@derived)method(0)
    d:(super@derived)method:=1
    d:(super@derived)method(2)
    d:(super@derived)method():=3
    d:(super@derived)method(4,5)
    d:(super@derived)method(5):=6
    d:(super@derived)step
    
    ?

    ? d:attrib          ;  ?? d:attrib
    ? d:attrib+=10      ;  ?? d:attrib
    ? d:attrib-=1       ;  ?? d:attrib
    ? d:attrib*=10      ;  ?? d:attrib
    ? d:attrib/=2       ;  ?? d:attrib

    ? d:attrib--        ;  ?? d:attrib
    ? d:attrib++        ;  ?? d:attrib
    ? --d:attrib        ;  ?? d:attrib
    ? ++d:attrib        ;  ?? d:attrib
    
    ?


    //az alábbiakat a régi fordító nem tudja
    //nehéz nekik valódi értelmet tulajdonítani
    //az új fordító is kizárja azokat az eseteket,
    //amikor a metódushívásnak paraméterlistája van

    //? d:attrib()+=1                           //syntax
    //? d:attrib(1,2,3)+=1                      //syntax

    ? d:(base)attrib+=1
    ? d:(base@derived)attrib+=1
    ? d:(super@derived)attrib+=1

    ? d:attrib(25)
    //? d:attrib(11,22,33)+=1                   //syntax
    //? d:(base)attrib(11,22,33)+=1             //syntax
    //? d:(base@derived)attrib(11,22,33)+=1     //syntax
    //? d:(super@derived)attrib(11,22,33)+=1    //syntax
    
    ?

    return NIL
