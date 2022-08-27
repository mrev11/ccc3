
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

#ifdef NOT_DEFINED
error -> apperror

error -> apperror -> invalidoptionerror

error -> apperror -> invalidformaterror
error -> apperror -> invalidformaterror -> invalidstructerror
error -> apperror -> invalidformaterror -> xmlsyntaxerror
error -> apperror -> invalidformaterror -> xmlsyntaxerror -> xmltagerror

error -> apperror -> tabobjerror
error -> apperror -> tabobjerror -> tabindexerror
error -> apperror -> tabobjerror -> tabstructerror
error -> apperror -> tabobjerror -> memoerror
error -> apperror -> tabobjerror -> tranlogerror

error -> apperror -> ioerror
error -> apperror -> ioerror -> eoferror
error -> apperror -> ioerror -> fnferror
error -> apperror -> ioerror -> readerror
error -> apperror -> ioerror -> writeerror
error -> apperror -> ioerror -> socketerror
#endif


******************************************************************************
class apperror(error)
    method initialize

static function apperror.initialize(this,op)
    this:(error)initialize
    this:description:=@"application error"
    this:operation:=if(op==NIL,"",op)
    return this

******************************************************************************
class invalidoptionerror(apperror)
    method initialize

static function invalidoptionerror.initialize(this,op)
    this:(apperror)initialize(op)
    this:description:=@"invalid option"
    return this

******************************************************************************
class invalidformaterror(apperror)
    method initialize

static function invalidformaterror.initialize(this,op)
    this:(apperror)initialize(op)
    this:description:=@"invalid format"
    this:oscode:=ferror()
    return this

******************************************************************************
class invalidstructerror(invalidformaterror)
    method initialize

static function invalidstructerror.initialize(this,op)
    this:(invalidformaterror)initialize(op)
    this:description:=@"invalid struct"
    return this

******************************************************************************
class xmlsyntaxerror(invalidformaterror)
    method initialize

static function xmlsyntaxerror.initialize(this,op)
    this:(invalidformaterror)initialize(op)
    this:description:=@"XML syntax"
    return this

******************************************************************************
class xmltagerror(xmlsyntaxerror)
    method initialize

static function xmltagerror.initialize(this,op)
    this:(xmlsyntaxerror)initialize(op)
    this:description:=@"XML tag mismatch"
    return this

******************************************************************************
class tabobjerror(apperror)
    method initialize

static function tabobjerror.initialize(this,op)
    this:(apperror)initialize(op)
    this:description:=@"table object error"
    this:oscode:=ferror()
    this:subsystem:="BTBTX database"
    return this

******************************************************************************
class tabindexerror(tabobjerror)
    method initialize

static function tabindexerror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"table index error"
    return this

******************************************************************************
class tabstructerror(tabobjerror)
    method initialize

static function tabstructerror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"table struct error"
    return this

******************************************************************************
class memoerror(tabobjerror)
    method initialize

static function memoerror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"invalid memo file"
    this:oscode:=ferror()
    return this

******************************************************************************
class tranlogerror(tabobjerror)
    method initialize

static function tranlogerror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"transaction log error"
    this:oscode:=ferror()
    return this

******************************************************************************
class tranlockerror(tabobjerror)
    method initialize

static function tranlockerror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"record lock without active transaction"
    return this


******************************************************************************
class trantimeouterror(tabobjerror)
    method initialize

static function trantimeouterror.initialize(this,op)
    this:(tabobjerror)initialize(op)
    this:description:=@"transaction timed out"
    return this

******************************************************************************
class ioerror(apperror)
    method initialize

static function ioerror.initialize(this,op)
    this:(apperror)initialize(op)
    this:description:=@"i/o error"
    this:oscode:=ferror()
    return this

******************************************************************************
class eoferror(ioerror)
    method initialize

static function eoferror.initialize(this,op)
    this:(ioerror)initialize(op)
    this:description:=@"end of file"
    return this

******************************************************************************
class fnferror(ioerror)
    method initialize

static function fnferror.initialize(this,op)
    this:(ioerror)initialize(op)
    this:description:=@"file not found"
    return this

******************************************************************************
class readerror(ioerror)
    method initialize

static function readerror.initialize(this,op)
    this:(ioerror)initialize(op)
    this:description:=@"read failed"
    return this

******************************************************************************
class writeerror(ioerror)
    method initialize

static function writeerror.initialize(this,op)
    this:(ioerror)initialize(op)
    this:description:=@"write failed"
    return this

******************************************************************************
class socketerror(ioerror)
    method initialize

static function socketerror.initialize(this,op)
    this:(ioerror)initialize(op)
    this:description:=@"socket failed"
    return this

******************************************************************************

