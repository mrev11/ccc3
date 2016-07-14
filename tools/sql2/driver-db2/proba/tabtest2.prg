
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

//#define ISNULL(t,x,r)   t:getcolumn(#x):isnull(r)
#define ISNULL(t,x,r)   ""

function main()
local con
local tab
local rowset
local n:=0,row

    set date format 'yyyy-mm-dd'

    con:=sql2.db2.sqlconnectionNew("@sample")

    tab:=proba.tableEntityNew(con)
    //tab:list
    rowset:=tab:select
    while( NIL!=(row:=rowset:next) )
    
        if(++n%10==0)
            //con:sqlrollback
        end
        
        
        ? row:szamlaszam,              ISNULL(tab,szamlaszam,row), ;           
          row:devnem,                  ISNULL(tab,devnem,row), ;               
          row:nev,                     ISNULL(tab,nev,row), ;                  
          row:egyenleg::str(10,2),     ISNULL(tab,egyenleg,row), ;  
          row:sorszam,                 ISNULL(tab,sorszam,row), ;              
          row:tulmenflag,              ISNULL(tab,tulmenflag,row), ;           
          row:konyvkelt,               ISNULL(tab,konyvkelt,row), ;            
          row:megjegyzes,              ISNULL(tab,megjegyzes,row)
                                          
    end                                   
                                          
    ?                                     
                                          
                                          
                                          