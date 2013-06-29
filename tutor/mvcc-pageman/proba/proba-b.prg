
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


function main()

local con:=pageman.dbconnectionNew("dbproba")
local page,err

    while(.t.);begin

        page:=con:read(a"0000000000000003")  //C-s page
        page:content+=a"BB"
        ? page:content  //ezt akarja kiírni

        if( inkey(0)==K_ESC )
            exit
        end
        con:commit

    recover err <pageman.dbserialerror>
        ? err:classname, err:description
        con:rollback
    end;end
