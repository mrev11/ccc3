
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
#endif

namespace sql2.postgres

#include "pq.ch"

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
    this:(object)initialize()
    this:connection:=con
    this:name:=name
    return this

****************************************************************************
static function sqlsequence.create(this)
local stmt:="create sequence "+this:name
    if( this:increment!=NIL )
        stmt+=" increment "+alltrim(str(this:increment))
    end
    if( this:minvalue!=NIL )
        stmt+=" minvalue "+alltrim(str(this:minvalue))
    end
    if( this:maxvalue!=NIL )
        stmt+=" maxvalue "+alltrim(str(this:maxvalue))
    end
    if( this:start!=NIL )
        stmt+=" start "+alltrim(str(this:start))
    end
    if( this:cache!=NIL )
        stmt+=" cache "+alltrim(str(this:cache))
    end
    if( this:cycle!=NIL )
        stmt+=" cycle "
    end
    
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit

    return NIL

#ifdef EMLEKEZTETO //implicit commit a DDL utasítások körül
    Az Oracle csinál egy implicit commit-ot minden DDL utasítás előtt 
    és után (tehát minden create, drop, alter, grant, revoke, stb. körül).
    A Postgres ezt nem csinálja,  a különbséget ki kell egyenlíteni.
#endif

****************************************************************************
static function sqlsequence.drop(this)
local stmt:="drop sequence "+this:name
    this:connection:sqlcommit
    this:connection:sqlexec(stmt)
    this:connection:sqlcommit
    return NIL

#ifdef EMLEKEZTETO //implicit commit a DDL utasítások körül
    Az Oracle csinál egy implicit commit-ot minden DDL utasítás előtt 
    és után (tehát minden create, drop, alter, grant, revoke, stb. körül).
    A Postgres ezt nem csinálja,  a különbséget ki kell egyenlíteni.
#endif

****************************************************************************
static function sqlsequence.nextval(this)
local stmt:="select nextval('"+this:name+"')"
local query:=this:connection:sqlquerynew(stmt)
local sequence_value:=if(query:next,query:getnumber(1),NIL)
    query:close
    return sequence_value

****************************************************************************
