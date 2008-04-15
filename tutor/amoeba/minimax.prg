
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

#include "amoeba.ch"

#define TDEPTH   1
#define ADEPTH   2

static width1:=powinit(POW1) 
static width2:=powinit(POW2) 
static width3:=powinit(POW3) 
static width4:=powinit(POW4) 
static width5:=powinit(POW5) 
static width6:=powinit(POW6)
static width7:=powinit(POW7)
static width8:=powinit(POW8)
static width:=width1
static power
 
static depth:=0
static tree:={}
static teach:=TDEPTH

*****************************************************************************
function go()

local x,v,m:=move()

    if( power!=NIL )
        width:=power
    elseif( m<=4 )
        width:=width1
    elseif( m<=8 )
        width:=width2
    elseif( m<=16 )
        width:=width3
    elseif( m<=24 )
        width:=width4
    elseif( m<=40 )
        width:=width5
    elseif( m<=56 )
        width:=width6
    elseif( m<=72 )
        width:=width7
    else
        width:=width8
    end

    v:=minimax(tree:={})

    x:=atail(tree)
    if( NIL!=x )
        forw(x)
        draw(x)
    end
    
    if( teach() )
        ? "minimax",m,int(v)
    end
    
*****************************************************************************
static function powinit(x)
local n
    x:=split(x)
    for n:=1 to len(x)
        x[n]:=val(x[n])
    next
    return x

*****************************************************************************
function power(p)
    if( p=="auto" )
        power:=NIL
    else
        power:=powinit(p)
    end

*****************************************************************************
function teach(t)
local prev:=!empty(teach)
    if( t!=NIL )
        teach:=if(t,TDEPTH,0)
    end
    return prev

*****************************************************************************
function tree()
    set printer to amoeba
    set printer on
    set console off
    aview(tree)
    set printer to 
    set printer off
    set console on
    run("less amoeba &")
    return NIL

*****************************************************************************
static function aview(a)
static d:=0
local n
    for n:=1 to len(a)
        if( valtype(a[n])=="A" )
            d++
            aview(a[n])
            d--
        else
            ? space(d*16),"[",a[n],"]"
        end
    next
    return NIL

*****************************************************************************
static function minimax(t,cut)

local fm,x,v,xm,vm
local n,t1

    if( depth>=len(width) )
        movegen(4)
        return posvalue(depth)+rand()/10
    end
    
    depth++

    fm:=movegen(width[depth]) 
    
    aadd(t,turn())
    
    for n:=1 to len(fm)

        if( forw(x:=fm[n]) )

            if( teach>=depth )
                draw(x,1)
                sleep(300)
            end

            v:=minimax( t1:={}, vm )

            //elemzőfa építés
            if( depth<=ADEPTH ) 
                aadd(t,str(x,3)+","+str(v,6))
                if( depth<ADEPTH )
                    aadd(t,t1)
                end
            end
 
            if( turn_o() )
                if( vm==NIL .or. v>vm ) //maximum 
                    vm:=v
                    xm:=x
                end

                if( cut!=NIL .and. cut<vm )
                    n:=1000 //a-vagas
                end

            else //if( turn_x() )
                if( vm==NIL .or. v<vm ) //minimum 
                    vm:=v
                    xm:=x
                end

                if( cut!=NIL .and. vm<cut )
                    n:=1000 //b-vagas
                end
            end

            back()

            if( teach>=depth )
                draw(x)
            end
        end
    next

    depth--
 
    if( vm==NIL ) //nem lehet lépni
        vm:=if(turn_o(),PVALUE_INFIN-depth,-PVALUE_INFIN+depth)
    end
    
    aadd(t,"best")
    aadd(t,vm)
    aadd(t,xm)

    return vm

*****************************************************************************
 
   