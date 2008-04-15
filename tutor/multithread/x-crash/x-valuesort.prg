
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

//Kimutatja asort() azon hibáját,
//hogy a valuesort() zsilipelését elrontja
//a valuesort() közben meghívódó VALUE:operator=() zsilipelése.
//Az operator=()-t nem a qsort hívja meg (mint elsőre gondolnánk),
//hanem az asort() összehasonlító kódblokkja.



*****************************************************************************
function main()

local  th, cnt:=0 

    ? "valuesort"

    printpid()
    printexe()
    
    th:=thread_create({||gcloop()}); thread_detach(th)
    th:=thread_create({||nyuzo()}); thread_detach(th)
    
    while( inkey()!=asc("q") )
        ?? str(++cnt,4)
        sleep(1000)
    end
    ?

*****************************************************************************
static function gcloop()
    while(.t.)    
        gc()
        sleep(2*rand())
    end

*****************************************************************************
static function nyuzo()
    while(.t.)
        vsort()
    end


*****************************************************************************
static function vsort()
local a:={},n,x1,x2

    for n:=1 to 100
        x1:=int(1000*rand())%26
        x2:=int(1000*rand())%26
        x1:=chr(asc("A")+x1)
        x2:=chr(asc("A")+x2)
        aadd(a,{x1,x2})
    next

    for n:=1 to 32
        asort(a,,,{|x,y|x[1]<y[1]})
        asort(a,,,{|x,y|x[1]>y[1]})
    next


*****************************************************************************
static function printpid()
    set printer to pid
    set printer on
    ?? getpid()
    set printer to
    set printer off

static function printexe()
    set printer to exe
    set printer on
    ?? exename()
    set printer to
    set printer off

*****************************************************************************
