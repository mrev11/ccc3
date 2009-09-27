
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

****************************************************************************
class sqlerror(apperror)
    method initialize

static function sqlerror.initialize(this)
    this:(apperror)initialize
    this:description:="SQL2 interface error"
    return this

****************************************************************************
class sqllockerror(sqlerror)
    method initialize

static function sqllockerror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 lock error"
    this:canretry:=.t.
    return this

****************************************************************************
class sqlserialerror(sqlerror)
    method initialize

static function sqlserialerror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 transaction serialization error"
    this:canretry:=.t.
    return this

****************************************************************************
class sqldeadlockerror(sqllockerror,sqlserialerror) //!
    method initialize

static function sqldeadlockerror.initialize(this)
    this:(sqllockerror)initialize
    this:(sqlserialerror)initialize
    this:description:="SQL2 deadlock error"
    this:canretry:=.t.
    return this

****************************************************************************
class sqlconnecterror(sqlerror)
    method initialize

static function sqlconnecterror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 connection error"
    return this

****************************************************************************
class sqlrowcounterror(sqlerror)
    method initialize

static function sqlrowcounterror.initialize(this)
    this:(sqlerror)initialize
    this:description:="SQL2 rowcount error"
    return this

****************************************************************************
