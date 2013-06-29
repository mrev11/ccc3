
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

*************************************************************************************************
class dbconnection(object)

    attrib  database
    attrib  pagehash
    attrib  readmark
    
    method  initialize

    method  append
    method  read
    method  commit
    method  rollback

*************************************************************************************************
static function dbconnection.initialize(this,dbspec)
    this:database:=databaseNew(dbspec)
    this:pagehash:=simplehashNew()
    this:readmark:=NIL  //a tranzakciók első olvasásakor kap értéket
    return this


*************************************************************************************************
static function dbconnection.append(this)  //új page
local page:=this:database:append()
    this:pagehash[page:pgid]:=page
    return page


*************************************************************************************************
static function dbconnection.read(this,pgid)  //beolvas egy page-et
local page,rm
    if( (page:=this:pagehash[pgid])==NIL )
        rm:=this:readmark //először NIL
        page:=this:database:read(pgid,@rm)
        this:readmark:=rm
        this:pagehash[page:pgid]:=page
    next
    return page


*************************************************************************************************
static function dbconnection.rollback(this)
    this:readmark:=NIL
    this:pagehash:clear


*************************************************************************************************
static function dbconnection.commit(this)
    this:database:commit(this:pagehash,this:readmark)
    this:readmark:=NIL
    this:pagehash:clear

*************************************************************************************************
    