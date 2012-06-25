
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

/*
sqlerror
    ->  sqltranctlerror
            ->  sqlnodatafounderror
            ->  sqluniqueconstrainterror
            ->  sqlrowcounterror
            ->  sqlconcurrencyerror
                    ->  sqlserialerror
                    ->  sqllockerror
                            ->  sqldeadlockerror
    ->  sqlconnecterror

  A programozás szepontjából egyetlen fontos dolog van: Tudni kell, 
  mely hibák után érdemes ismételni a tranzakciót. A struktúra úgy
  készült, hogy az sqltranctlerror alatt vannak az ismételéssel 
  javítható hibák. Nemcsak a lockolással kapcsolatos hibák ilyenek.
  
  sqluniqueconstrainterror pl. keletkezhet azért, mert

  1) hibás program be akar tenni egy már létező kulcsot

  2) a program ellenőrzi a kulcs létezését, de ellenőrzéskor az még nem 
  létezett, viszont mire berakná, addigra egy másik program megelőzte.
  
  A gyakorlat szempontjából a 2) eset a fontos, tehát érdemes az ilyeneket
  a könnyű kezelés érdekében az sqltranctlerror alá sorolni.
*/

****************************************************************************
class sqlerror(apperror)
    method initialize

static function sqlerror.initialize(this)
    this:(apperror)initialize
    this:description:="SQL2 interface error"
    return this

****************************************************************************
class sqltranctlerror(sqlerror)
    method initialize

static function sqltranctlerror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 transaction control error"
    return this

****************************************************************************
class sqlnodatafounderror(sqltranctlerror)
    method initialize

static function sqlnodatafounderror.initialize(this)
    this:(sqltranctlerror)initialize
    this:description:="SQL2 no data found error"
    return this

****************************************************************************
class sqluniqueconstrainterror(sqltranctlerror)
    method initialize

static function sqluniqueconstrainterror.initialize(this)
    this:(sqltranctlerror)initialize
    this:description:="SQL2 unique constraint error"
    return this

****************************************************************************
class sqlrowcounterror(sqltranctlerror)
    method initialize

static function sqlrowcounterror.initialize(this)
    this:(sqltranctlerror)initialize
    this:description:="SQL2 rowcount error"
    return this

****************************************************************************
class sqlconcurrencyerror(sqltranctlerror)
    method initialize

static function sqlconcurrencyerror.initialize(this)
    this:(sqltranctlerror)initialize
    this:description:="SQL2 transaction concurrency control error"
    return this

****************************************************************************
class sqlserialerror(sqlconcurrencyerror)
    method initialize

static function sqlserialerror.initialize(this)
    this:(sqlconcurrencyerror)initialize
    this:description:="SQL2 transaction serialization error"
    return this

****************************************************************************
class sqllockerror(sqlconcurrencyerror)
    method initialize

static function sqllockerror.initialize(this)
    this:(sqlconcurrencyerror)initialize
    this:description:="SQL2 lock error"
    return this

****************************************************************************
class sqldeadlockerror(sqllockerror) 
    method initialize

static function sqldeadlockerror.initialize(this)
    this:(sqllockerror)initialize
    this:description:="SQL2 deadlock error"
    return this

****************************************************************************
class sqlconnecterror(sqlerror)
    method initialize

static function sqlconnecterror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 connection error"
    return this

****************************************************************************
