
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

//betesz néhány rekordot 
//a konto.proba 
//és konto.szerencse táblákba

function main()

local con, tbl1, tbl2, e1, e2

    set date format "yyyy-mm-dd"
    set printer to log-te-insert
    set printer on
 
    con:=sqlconnect()  
    tbl1:=proba.tableEntityNew(con)
    tbl2:=szerencse.tableEntityNew(con)

    //egy tranzakció

    e1:=tbl1:instance
    e1:szamlaszam:="AAAABBBB3333333355555555"
    e1:devnem:="USD"
    e1:nev:="Van, aki 'forrón' szereti"
    e1:egyenleg:=100000.00
    e1:konyvkelt:=stod("20010131")
    e1:insert

    e2:=tbl2:instance
    e2:szamlaszam:=e1:szamlaszam //foreign key
    e2:kiegdata:="kieg: "+e1:nev
    e2:insert

    con:sqlcommit


    //még egy tranzakció

    e1:=tbl1:instance
    e1:szamlaszam:="888888887777777711111111"
    e1:devnem:="EUR"
    e1:nev:="próba szerencse"
    e1:egyenleg:=1.00
    e1:konyvkelt:=stod("20020131")
    e1:insert

    e2:=tbl2:instance
    e2:szamlaszam:=e1:szamlaszam //foreign key
    e2:kiegdata:="kieg: "+e1:szamlaszam
    e2:insert

    con:sqlcommit

    //session vége

    con:sqldisconnect

    return NIL
 
    