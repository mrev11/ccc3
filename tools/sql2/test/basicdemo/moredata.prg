
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

function main()

local moredata:=<<ins>>
insert into konto.a 
(id, name, datum, flag, value)
values  (:1, :2, :3, :4, :5)
<<ins>>

local con:=sqlconnect()

    set date format "yyyy-mm-dd"
    set printer to log-moredata
    set printer on
    

    con:sqlexec(moredata,{11,"a11",date()+1,.t.,1001})
    con:sqlexec(moredata,{12,"a12",date()+2,.t.,1002})
    con:sqlexec(moredata,{13,"a13",date()+3,.t.,1003})
   
    con:sqlcommit
    con:sqldisconnect
    
    return NIL
     