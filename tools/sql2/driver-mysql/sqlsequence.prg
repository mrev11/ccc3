
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

#ifdef EMLEKEZTETO //a sequence objektum nevekről
    A sequence-ek neve nem ütközhet más objektumok
    pl. táblák nevével. Az sqlsequence objektum alkalmazhatna
    a névképzésben valamilyen automatikus prefixet az ütközés
    elkerülésére, ekkor azonban nem tudnánk hozzáférni a kézzel 
    létrehozott sequence-ekhez, amiknek nincs ilyen prefixe. 
    Ezért az esetleges prefixelés az alkalmazás feladata.
    
    sqlite3-ban a sequence-ek közönséges táblák,
    már csak ezért sem lehet névütközés.
#endif

namespace sql2.mysql


****************************************************************************
class sqlsequence(object)
    method  initialize

    attrib  connection
    attrib  name

    attrib  increment     //ezek nem működnek
    attrib  minvalue      //ezek nem működnek
    attrib  maxvalue      //ezek nem működnek
    attrib  start
    attrib  cache         //ezek nem működnek
    attrib  cycle         //ezek nem működnek

    method  create
    method  drop
    method  nextval


****************************************************************************
static function sqlsequence.initialize(this,con,name)
    this:connection:=con
    this:name:=name
    return this


****************************************************************************
static function sqlsequence.create(this)
    this:connection:sqlcommit
    this:connection:sqlexec("create table "+this:name+" (value integer primary key auto_increment) ENGINE=MYISAM")
    if( this:start!=NIL .and. this:start>=1 )
        this:connection:sqlexec("insert into "+this:name+" values(:1)",{this:start-1})
        this:connection:sqlexec("delete from "+this:name) 
    end
    this:connection:sqlcommit

// ENGINE=MYISAM
// A (default) INNODB motorral gyakori deadlock keletkezik.
// A MYISAM motor nem tranzakciós, ami itt éppen kapóra jön.

// Az sqlexec bind literált (!) helyettesít a :n szimbólum helyére. 
// MySQL-ben a táblaneveket nem lehet 'tabname' formában használni, 
// ezért a táblanév helyettesítését nem szabad az sqlexec-re bízni.


****************************************************************************
static function sqlsequence.drop(this)
local stmt:="drop table "+this:name
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit


****************************************************************************
static function sqlsequence.nextval(this)
local query,sequence_value

    this:connection:sqlexec("insert into "+this:name+" values(null)") 
    this:connection:sqlexec("delete from "+this:name) 

    query:=this:connection:sqlqueryNew("select last_insert_id()")
    sequence_value:=if(query:next,query:getnumber(1),NIL)
    query:close
    return sequence_value


****************************************************************************

#ifdef EMLEKEZTETO //implicit commit a DDL utasítások körül
    Az Oracle csinál egy implicit commit-ot minden DDL utasítás előtt 
    és után (tehát minden create, drop, alter, grant, revoke, stb. körül).
    A Postgres ezt nem csinálja,  a különbséget ki kell egyenlíteni.
#endif

#ifdef EMLEKEZTETO //a sequence-ek commitjáról
    Oracle-ben és Postgresben a sequence-ek értéke a tranzakcióktól
    függetlenül megmarad, sqlite-ban csak akkor, ha commit is volt.
#endif
