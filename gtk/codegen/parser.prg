
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

static code_lp:=asc("(")
static code_rp:=asc(")")
static code_bl:=asc(" ")
static code_ap:=asc("'")
static code_qu:=asc('"')
static code_lf:=10
static code_cr:=13
static code_tb:=9

static defs

******************************************************************************
function readinput(fspec)
    defs:=memoread(fspec)
    if( empty(defs) )
        ? "Not found", fspec
        errorlevel(1)
        quit
    end

******************************************************************************
function getdef(arr,pos)
local p1,quote:=.f.,c

    while( pos<=len(defs) .and. ascpos(defs,pos)!=code_lp  )  
        pos++
    end
    pos++

    while( pos<=len(defs) )
        c:=ascpos(defs,pos)
    
        if( quote )
            if( c==code_qu )
                quote:=.f.
                aadd(arr,substr(defs,p1,pos-p1))
                p1:=NIL
            end

        elseif(  c==code_qu )
            quote:=.t.
            if( p1!=NIL )
                aadd(arr,substr(defs,p1,pos-p1))
            end
            p1:=pos+1
 
        elseif(c==code_lp)
            aadd(arr, getdef({},@pos) )

        elseif(c==code_rp)
            if( p1!=NIL )
                aadd(arr,substr(defs,p1,pos-p1))
                p1:=NIL
            end
            exit

        elseif( c==code_bl .or. c==code_ap .or. c==code_lf .or. c==code_cr .or. c==code_tb )
            if( p1!=NIL )
                aadd(arr,substr(defs,p1,pos-p1))
                p1:=NIL
            end
        
        else
            if( p1==NIL )
                p1:=pos
            end
        end

        pos++
    end
    return arr

******************************************************************************
    