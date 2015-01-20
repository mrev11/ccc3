
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

namespace sql2.db2


****************************************************************************
class sqlsequence(object)
    method  initialize

    attrib  connection
    attrib  name

    attrib  increment
    attrib  minvalue
    attrib  maxvalue
    attrib  start
    attrib  cache
    attrib  cycle

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
local stmt:="create sequence "+this:name
    if( this:start!=NIL )
        stmt+=" start with "+alltrim(str(this:start))
    end
    if( this:increment!=NIL )
        stmt+=" increment by "+alltrim(str(this:increment))
    end
    if( this:minvalue!=NIL )
        stmt+=" minvalue "+alltrim(str(this:minvalue))
    end
    if( this:maxvalue!=NIL )
        stmt+=" maxvalue "+alltrim(str(this:maxvalue))
    end
    if( this:cycle!=NIL )
        stmt+=" cycle "
    end
    if( this:cache!=NIL )
        stmt+=" cache "+alltrim(str(this:cache))
    else
        stmt+=" no cache" //20 volna a default
    end
    
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit


****************************************************************************
static function sqlsequence.drop(this)
local stmt:="drop sequence "+this:name
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit


****************************************************************************
static function sqlsequence.nextval(this)
local query,seqval
    query:=this:connection:sqlqueryNew("values nextval for "+this:name)
    query:next
    seqval:=query:getnumber(1)
    query:close
    return seqval

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
