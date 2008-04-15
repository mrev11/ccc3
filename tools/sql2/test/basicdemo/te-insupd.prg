
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

//insert/update a konto.proba táblába

function main()

local con,tableentity
local rowset,e1,e2

    set date format "yyyy-mm-dd"
    set printer to log-te-insupd
    set printer on

    con:=sqlconnect()  
    tableentity:=proba.tableEntityNew(con)

    e1:=tableentity:instance                //új entity objektum (csak a programban)
    e1:szamlaszam:="AAAABBBB-"+dtoc(date())
    e1:devnem:="USD"
    e1:nev:="Van, aki 'forrón' szereti"
    e1:egyenleg:=1000000.00
    e1:tulmenflag:=.f.
    e1:konyvkelt:=stod("19541011")
    e1:megjegyzes:=a"öt szép szűzlány őrült írót nyúz"

    e2:=tableentity:instance
    e2:szamlaszam:="CCCCDDDD-"+dtoc(date())
    e2:devnem:="HUF"
    e2:nev:="hopp"
    e2:egyenleg:=1234567.89
    e2:tulmenflag:=.t.
    e2:konyvkelt:=date()

    e1:show                                 //kilistázza magát
    e2:show                                 //kilistázza magát

    tableentity:insert(e1)                  //új sor az Oracle táblában
    e2:insert                               //új sor az Oracle táblában, másik hívási mód
    con:sqlcommit()                         //kiírások véglegesítve
    

    //Megjegyzés:
    //Ha a primary key nem egyedi, akkor az update rosszul működik,
    //a helyes működést unique indexszel lehet kikényszeríteni.

    rowset:=tableentity:select              //az összes soron végigmegy
    while( NIL!=(e1:=rowset:next) )

        //módosítások

        e1:nev:=alltrim(e1:nev)+"X" 
        e1:egyenleg+=1000
        e1:konyvkelt+=1
        e1:megjegyzes+=a"#"

        e1:show                             //kilistázza magát
        e1:update                           //kiírja magát az adatbázisba 
        ?
    end
    //rowset automatikusan lezáródik

    //select tranzakció lezárva
    //kiírás véglegesítve 

    con:sqlcommit()                         

    con:sqldisconnect


#ifdef EMLEKEZTETO 
    Oracle-ben a commit állhat a cikluson belül, az update után.
    Postgresben ez elrontaná (félbeszakítja) a tranzakciót, amit
    a DECLARE crs CURSOR FOR SELECT plusz FETCH  megkíván.
#endif

    return NIL
 
    