
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



******************************************************************************************
function s_main(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_libnam(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_shared(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_srcdir(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_incdir(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_libdir(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_libfil(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_quiet(x)
static xx:=.f.
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_version(x)
static xx:=.f.
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result
 
******************************************************************************************
function s_debug(x)
static xx:=.f.
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_dry(x)
static xx:=.f.
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_runcnt(x)
static xx:=0
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_primary(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_resource(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_libspec(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result
 
******************************************************************************************
function s_rules(x)
static xx:={;
{".msk",".dlg"},;
{".msk",".pnl"},;
{".mnt",".gpi"},;
{".cls",".och"},;
{".msk",".say"},;
{".htm",".ctm"},;
{".msk",".wro"},;
{".pge",".out"},;
{".pge",".wro"},;
{".tdc",".ch" },;
{".asm",".obj"},;
{".c"  ,".obj"},;
{".cpp",".obj"},;
{".tds",".obj"},;
{".prg",".obj"},;
{".y"  ,".obj"},;
{".lem",".obj"},;
{".lex",".obj"},;
{".tdc",".obj"},;
{".obj",".lib"},;
{".obj",".exe"};
}
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function s_batext(x)
static xx
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function resource_hash(x)
static xx:=simplehashNew()
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
function omitted_hash(x)
static xx:=simplehashNew()
static mutex:=thread_mutex_init()
local result
    mutex::thread_mutex_lock
    result:=if(x==NIL,xx,xx:=x )
    mutex::thread_mutex_unlock
    return result

******************************************************************************************
