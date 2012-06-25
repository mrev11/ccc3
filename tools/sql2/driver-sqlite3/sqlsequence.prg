
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

namespace sql2.sqlite3

#include "sqlite3.ch"

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
    this:(object)initialize()
    this:connection:=con
    this:name:=name
    return this


****************************************************************************
static function sqlsequence.create(this)
local stmt:="create table :1(value integer primary key autoincrement);"
    this:connection:sqlcommit
    this:connection:sqlexec(stmt,{this:name})
    if( this:start!=NIL )
        stmt:="insert into :1 values(:2);delete from :1;"
        this:connection:sqlexec(stmt,{this:name,this:start})
    end
    this:connection:sqlcommit


****************************************************************************
static function sqlsequence.drop(this)
local stmt:="drop table "+this:name
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit


****************************************************************************
static function sqlsequence.nextval(this)
local stmt:="insert into :1 values(null);delete from :1;"
    this:connection:sqlexec(stmt,{this:name})
    return _sqlite3_last_insert_rowid(this:connection:__conhandle__)


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
