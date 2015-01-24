
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

namespace sql2.db2

#include "db2.ch"

#ifdef EMLEKEZTETO //a rowsetekről

    Ezeket az objektumokat a tableEntityClass leszármazottai
    gyártják a find és select metódusaikkal. Az alkalmazások csak a 

        next
        close

    metódusokat használják, minden mást a tableentity elintéz.

    A next metódus mindaddig új rowentity objektumokat ad, 
    amíg a fetch sikeres, azután NIL-t. Ha a fetch-ek kimerítették
    a rowset-et, akkor az automatikusan lezáródik, ha nem, akkor
    explicite le kell zárni (máskülönben elfogynak a handlerek).

    A tableEntity objektum find metódusa rowentity objektumot ad.
    A tableEntity objektum select metódusai rowset objektumot adnak,
    ennek a next metódusa adogatja a rowentity objektumokat.

#endif


******************************************************************************
class rowset(object) 
    method  initialize
    method  __table__           {|this|eval(this:__tableblk__)}
    attrib  __tableblk__
    attrib  __stmthandle__
    attrib  __next__
    attrib  __transactionid__
    attrib  __closestmtidx__
    method  __select__
    method  next
    method  close

******************************************************************************
static function rowset.initialize(this,tab) 
    this:__tableblk__:={||tab} //rekurzivitás ellen blockba!
    this:__transactionid__:=tab:connection:__transactionid__
    this:__closestmtidx__:=tab:connection:__addstatementtoclose__({||this:__closestmtidx__:=NIL,this:close})
    return this


******************************************************************************
static function rowset.__select__(this,filterclause,orderbyclause,bindarray,wait)

local stmt,dst,err,rc
local fldcnt

    if( filterclause==NIL .or. filterclause!="distinct" )
        dst:=" "
    else
        filterclause:=substr(filterclause,9) //distinct levágva
        dst:=" distinct "
    end

    stmt:="select"+dst+this:__table__:__selectlist__
    stmt+=" from "+sql2.db2.sqlbind(this:__table__:__fromclause__,bindarray)

    if( filterclause!=NIL )
        stmt+=" "+sql2.db2.sqlbind(filterclause,bindarray)
    end

    if( NIL!=orderbyclause )
        stmt+=" order by "+orderbyclause
    end
    
    if( wait==NIL )
        //no lock

    elseif( wait==0 )
        //Az eredménytábla sorait lockolja,
        //a lock független a fetcheléstől (előre minden sort lockol),
        //a lockokat csak a commit/rollback szünteti meg, rowset:close nem,
        //ha a lock nem sikerül, kivételt dob.
        //stmt+=" for update nowait "
        stmt+=" for update " //nem lehet timeout-ot megadni
    elseif( wait==-1 )
        //Mint az előbbi eset, de korlátlan ideig vár .
        //stmt+=" for update wait "
        stmt+=" for update " //nem lehet timeout-ot megadni
    else
        //Mint az előbbi eset, de a megadott másodpercig vár.
        //stmt+=" for update wait "+alltrim(str(wait))
        stmt+=" for update " //nem lehet timeout-ot megadni
    end
    
    //stmt:=sql2.db2.sqlidcase(stmt,.f.)  //megszűnt: 2011.07.20
    
    sql2.db2.sqldebug(stmt)

    this:__stmthandle__:=sql2.db2._db2_execdirect(this:__table__:connection:__conhandle__,stmt)
    rc:=sql2.db2._db2_retcode(this:__stmthandle__)

    if( rc!=SQL_SUCCESS )
        err:=sql2.db2.sqlerror_create(this:__stmthandle__)
        err:operation:="rowset:select"
        err:args:={stmt}
        sql2.db2._db2_closestatement(this:__stmthandle__)
        this:__stmthandle__:=NIL
        //az itteni rollback nincs benne az sqldebug listában
        sql2.db2._db2_endtran(this:__conhandle__,SQL_ROLLBACK)
        this:__transactionid__++
        break(err)
    end

    //MySQL/Postgres-ben nem lehet timeout-ot megadni,
    //ezért ha nem sikerül, akkor végtelen ideig vár.
    //Ha lock volt előírva, és az nem sikerült,
    //akkor kivételt dobunk: sqllockerror, sqldeadlockerror.
     

******************************************************************************
static function rowset.next(this) //rowentity objektumgyártó

local rowentity,retcode

    if( this:__stmthandle__==NIL )
        //az eredmény NIL

    elseif( this:__table__:connection:__transactionid__!=this:__transactionid__ )
        //fetch across commit/rollback
        //az eredmény NIL
        this:close

    elseif( SQL_SUCCESS!=(retcode:=sql2.db2._db2_fetch(this:__stmthandle__)) )
        //az eredmény NIL
        this:close

    else
        rowentity:=mkrow(this)
    end
    
    return rowentity


******************************************************************************
static function mkrow(this)
local rowentity,columnlist,n,convtype,x
    rowentity:=objectNew(this:__table__:__rowclassid__)
    rowentity:initialize(this:__table__)
    columnlist:=this:__table__:columnlist
    for n:=1 to len(columnlist)
        if(columnlist[n]:type=="M")
            convtype:=SQL_BINARY
        else
            convtype:=SQL_CHAR
        end
        //más típusokat is számításba kéne venni
        x:= sql2.db2._db2_getdata(this:__stmthandle__,n,convtype) //binary string
        if( x!=NIL )
            eval(columnlist[n]:initblock,rowentity,x)
        end
    next
    return rowentity


******************************************************************************
static function rowset.close(this)
    if( this:__stmthandle__!=NIL )
        sql2.db2._db2_closestatement(this:__stmthandle__) 
        this:__stmthandle__:=NIL
    end
    if( this:__closestmtidx__!=NIL )
        //? "CLEAR-rs"
        this:__table__:connection:__clearstatement__(this:__closestmtidx__)
        this:__closestmtidx__:=NIL
    end


******************************************************************************
#ifdef EMLEKEZTETO  //a Postgres tranzakciók automatikus abortjáról

Az itt a probléma, hogyha az alkalmazás commit/rollback után óvatlanul 
fetchel, vagy lezár egy rowsetet, ami az előző tranzakcióhoz tartozott
(és ezért már nem létezik), akkor failed állapotba kerül az aktuális 
tranzakció.

    A probléma általánosabb, mint csak a kurzorok lezárása.
    Az interfész úgy van megírva, hogy a commit/rollback után
    automatikusan indul a következő tranzakció (küld egy begin-t).
    A Postgres azonban bármikor, amikor úgy gondolja, hogy hiba volt, 
    abortálja a tranzakciót. Az interfész (jelenleg) nem minden esetben 
    figyeli ezt (nincs break, pedig talán kellene). Ha az alkalmazás
    ilyen állapotban folytatja, akkor az SQL utasítások tranzakción
    kívülre kerülnek, azaz minden további utasítás hibás.
    Jelenleg a commit/rollback utáni fetch, illetve close cursor-nál
    látom ezt a problémát. 
    
    Ezzel szemben az Oracle hiba esetén nem abortál automatikusan,
    hanem a hibakód ismeretében az alkamazás eldöntheti, mi legyen.
    
1) Beépíthető az interfészbe, hogy explicite zárja le a kurzorokat
  a commit/rollback után. Akkor az alkalmazások mentesülnének
  a most kötelező rowset:close alól.

2) Kitalálhatjuk, hogy él-e még a kurzor.
  Minden tranzakció kap egy szám azonosítót (a connection attribútuma).
  A rowsetekbe szintén belekerül ez az azonosító, és ha az aktuális
  tranzakció azonosítója más, mint a rowsetben tárolt azonosító,
  akkor a rowset, és a hozzá tartozó kurzor érvénytelennek tekinthető,
  azaz a további fetch és a close tiltott.

Az Oracle-ben is a Postgres szűkösebb lehetőségeihez kell alkalmazkodni, 
azaz ott is tiltani kell a tranzakción átnyúló fetchelést.

Kellene a connection objektumba egy dup metódus, 
hogy külön connection-ök külön tranzakcióival lehessen 
pótolni a tranzakción átnyúló fetchelést.

#endif 


******************************************************************************
#ifdef EMLEKEZTETO //a tranzakcióhatárokon átnyúló fetchelésről

  Az adatbázis olvasása ugyanúgy tranzakcióban történik, 
  mint a módosítások.  Pl. egy select eredménytáblája már 
  az első fetch előtt véglegessé válik, és nem változik akkor sem, 
  ha a forrástáblákat a fetchek között más tranzakciók módosítják.
  Az a logikus tehát, ha a tranzakció befejeződésekor
  a kurzorok automatikusan megszűnnek, és nem lehet tovább
  fetchelni. Ez volt a helyzet a Postgresben. Persze ez
  nyilván kényelmetlen, ui. nehezebb megírni az olyan programot,
  ami végigmegy egy tábla sorain, és minden sorra végrehajt
  egy külön módosító tranzakciót (ui. a kurzor tranzakciója
  is lezáródik).
  
  Az Oracleben a fetchelés átnyúlhat a tranzakció határokon.
  (fetch across commit, kérdés rollback-en is átnyúlhat-e (igen)).

  A 8-as Postgresben szintén lehet commit-on átnyúlva fetchelni 
  (declare cursor with hold), rollback-en keresztül viszont nem.
#endif

******************************************************************************
#ifdef EMLEKEZTETO //az Oracle és Postgres select/fetchről

  Az Oracle-ben OCI szinten nincs kurzor.
  A select utasítást a szerver végrehajtja, és még az első fetch 
  előtt összeállítja (lerendezi, stb.) az eredménytáblát.
  Az eredménytábla a szerveren összeállítva vár a fetchelésre.
  Külön OCI fetch utasítás szolgál a fetchelésre, a kért sorokat
  a szerver átküldi a kliensre. A fetchek előtt nem mozog adat
  a szerver és kliens között. 

  A Postgresben kétféle select lehet.

     i) select
    ii) declare cursor for select

  Az i) esetben a szerver összeállítja az eredménytáblát,
  és az egészet egyben előre átküldi a kliensre. Amikor a kliens fetchel,
  akkor már csak a kliensen lokálisan, mátrix-szerűen tárolt eredménytáblából
  veszi elő az adatokat. A fetchek átnyúlhatnak a tranzakcióhatárokon,
  a sorokat lehet lockolni (for update).
  
  Az ii) esetben keletkezik egy kurzor (gondolom egy iterátor).
  Ez a kurzor sokkal gyorsabban elkészül, mint az Oracle selectje,
  vagy az i) eset eredménytáblája.  Alapesetben ez a kurzor csak a 
  tranzakción belül létezik, tehát commit/rollback után nem lehet
  többet fetchelni. A kurzor readonly (nem lehet megadni for update-et).
  
  A 8.x-as Postgresben megjelent: declare cursor WITH HOLD for select.
  Ez a forma lehetővé teszi, hogy egy commit után folytatni lehessen
  a fetcheket. Ezzel kapcsolatos megfigyelések: 
  
  Ha declare cursor-t rollback követi, akkor megszűnik a kurzor.
  
  Ha a declare cursor-t commit követi, akkor a szerver áttér az i)
  esetre, azaz nem iterátor módban működik tovább, hanem összeszedi 
  az eredménytábla maradékát, és átküldi azt a kliensre. Ezután
  már jöhetnek további commit/rollbackek azok nem befolyásolják
  a fetchelést. Ezek miatt elég gyenge dolognak tűnik a WITH HOLD opció.

#endif 

******************************************************************************

