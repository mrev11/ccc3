
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

#include "inkey.ch"


function main(ini)

local con,seq


    con:=sql2.db2.sqlconnectionNew("@sample")
    ? con:version


    seq:=con:sqlsequenceNew("seqproba")
   
    
    if(ini!=NIL)    
        begin
            seq:drop
        end

        seq:minvalue:=1000
        seq:increment:=2
        seq:create
    end


    while( inkey(0)!=K_ESC  )
        ? seq:nextval
    end
    
    
    con:sqlrollback
    con:sqldisconnect
    ?
     
