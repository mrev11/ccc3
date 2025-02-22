
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



#ifdef NOTDEFINED

static s_main    //main modulok
static s_libnam  //készítendő lib
static s_shared  //shared library flag
static s_srcdir  //itt keresünk forrásokat
static s_incdir  //átadjuk a fordítónak : srcdir,incdir,BUILD_INC
static s_libdir  //átadjuk a linkernek  : libdir,BUILD_LPT 
static s_libfil  //átadjuk a linkernek  : libfil,BUILD_LIB

static s_quiet   := .f.
static s_version := .f.
 
static s_debug:=.f.
static s_dry:=.f.
static s_primary   //kiszamitja s_rules-bol //:=".y.lem.lex.prg.cpp.c.asm.tds.tdc."
static s_resource  //kiszamitja s_rules-bol //:=".msk.mnt.cls.htm.pge.tdc"

static s_libspec   //lib specifikációk
 
static s_rules:={;
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

static s_batext

static resource_hash:=simplehashNew()
static omitted_hash:=simplehashNew()

#endif


******************************************************************************************
function s_main(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_libnam(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_shared(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_srcdir(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_incdir(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_libdir(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_libfil(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_quiet(x)
static xx:=.f.
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_version(x)
static xx:=.f.
    return if(x==NIL,xx,xx:=x )
 
******************************************************************************************
function s_debug(x)
static xx:=.f.
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_dry(x)
static xx:=.f.
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_runcnt(x)
static xx:=0
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_primary(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_resource(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_libspec(x)
static xx
    return if(x==NIL,xx,xx:=x )
 
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
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function s_batext(x)
static xx
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function resource_hash(x)
static xx:=simplehashNew()
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
function omitted_hash(x)
static xx:=simplehashNew()
    return if(x==NIL,xx,xx:=x )

******************************************************************************************
