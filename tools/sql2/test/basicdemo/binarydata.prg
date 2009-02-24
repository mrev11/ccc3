
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

//ellenőrzés: bináris adatok tárolása memó mezőben

#ifdef EMLEKEZTETO //a bináris adatok tárolásáról
  Oracle-ben a CHAR, VARCHAR és memó (CLOB) mezők is képesek
  tárolni bináris adatokat.  Oracle-ben a szervert Latin1 kódkészlettel 
  kell installálni, és a kliensen Latin1 kódkészletet kell beállítani:

  export NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1
  export NLS_DATE_FORMAT="YYYY-MM-DD"

  Postgresben csak a memók tudnak bináris adatot tárolni,
  a CHAR és VARCHAR mezők nem. Postgresben az adatbázist --no-locale 
  opcióval kell létrehozni:

  initdb --no-locale  -D `pwd`
#endif

#ifdef EMLEKEZTETO //a bináris adatok tárolásáról
  Ez volt helyzet a CCC2-SQL2-1.0-ban.
  A CCC3-SQL2-1.1-ben kissé módosult a helyzet:

  Oracleben sem lehet a CHAR mezőkben bináris adatot tárolni.
  Az Oracle talán tudná, de nehéz a CCC3 str2bin konverzóját kikerülni, 
  amivel a karakter stringet UTF-8 kódolású bytesorozattá alakítja.
  Ugyanezért Oracleben a memók tárolása CLOB-ról BLOB-ra változott.
#endif


function main()

local con,tbl,row1,row2
local xx,n

    set date format "yyyy-mm-dd"
    set printer to log-binarydata
    set printer on

    xx:=str2bin(dtoc(date1()))
    for n:=0 to 255
        xx+=bin(n)
    next
    xx+=a"'"+a"\"+bin(0)+bin(0)
 
    con:=sqlConnect()  
 
    tbl:=testdata.b.tableEntityNew(con)

    row1:=tbl:find(10)

    if( .f. .and. row1!=NIL )    
        row1:delete
        row1:=NIL
    end

    if( row1==NIL )
        row1:=tbl:instance
        row1:id:=10
        row1:remark:=xx
        row1:insert
    else
        row1:id:=10
        row1:remark:=xx
        row1:update
    end
    con:sqlcommit
    
    row2:=row1:find
    
    if( !xx==row2:remark )
        memowrit("xx-1",row1:remark)
        memowrit("xx-2",row2:remark)
        alert("Error!")
    end
    
    con:sqldisconnect

    return NIL
