
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

#include "table.ch"
#include "table.gtkapi.tdh"


******************************************************************************
function main(fspec)

local x,o,pos:=1

    if( !empty(getenv("GTKAPI_BT")) )
        GTKAPI:open(OPEN_EXCLUSIVE)
        GTKAPI:control:="capi"
    end

    readinput(fspec)

    set alternate to kihagy_met.bak
    set alternate to kihagy_met1.bak
    set alternate to extra_types.bak
    set alternate to
    
    debuginfo_add(".funcname.")


    //függvények
    pos:=1
    while( !empty(x:=getdef({},@pos)) )
        if( x[1]=="define-function" )
            o:=gtkdefNew(x)
            if( "API"$o:ccc .or. empty(o:state) .and. empty(o:ccc) )
                codegen_api(o)
                gtkapi_append(o)
            elseif( "D"$o:state  )
                //nem listáz
            else
                gtkapi_append(o,"X") //kihagyva
            end

        //ellenőrzés
        elseif( x[1]=="define-method" )
            //ezek később
        elseif( x[1]=="include" )
            //ezek kihagyva
        else
            alert( any2str(x)  )
        end
    end

    //metódusok
    pos:=1
    while( !empty(x:=getdef({},@pos)) )
        if( x[1]=="define-method" )
            o:=gtkdefNew(x)
            if( "API"$o:ccc .or. empty(o:state) .and. empty(o:ccc) )
                codegen_api(o)
                gtkapi_append(o)
            elseif( "D"$o:state  )
                //nem listáz
            else
                gtkapi_append(o,"X") //kihagyva
            end


        //ellenőrzés
        elseif( x[1]=="define-function" )
            //ezek már voltak
        elseif( x[1]=="include" )
            //ezek kihagyva
        else
            alert( any2str(x)  )
        end
    end
    ?
    
    nsclose()
    
    
    set printer to count.bak
    set printer on
    
    ?


******************************************************************************
static function list(o)

    set alternate on

    set alternate to kihagy_met.bak additive  //részletes lista
    o:list
    ?

    set alternate to kihagy_met1.bak additive //egy soros lista
    ?? padr(o:c_api,48),o:state,o:ccc
    ?

    set alternate off


******************************************************************************
