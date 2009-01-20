
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

//----------------------------------------------------------------------
#define  HOPP hoppsza
#ifeq HOPP hopp
    HOPP==hopp
#else
    HOPP<>hopp
#endif

//----------------------------------------------------------------------
#ifdef PROBA1
PROBA1 defined
#else
PROBA1 not defined
#endif

#ifndef PROBA1
PROBA1 not defined
#else
PROBA1 defined
#endif
 
//----------------------------------------------------------------------
    ? a"asciistring"
    ? x"1100aabb"
    ? @"nlstext"
    ? 0B1010001
    ? 0x0123abc

//----------------------------------------------------------------------
#include "table.ch"
#include "_napforg.ch"
 
    NAPFORG:open:=OPEN_EXCLUSIVE
    NAPFORG_UGYSZAM:="hopp"
    
//----------------------------------------------------------------------
#define LISTA  a, b, c, d
#xtranslate STRING( <list,...> )   => <"list">
#xtranslate STRINGX( <list,...> )  => #<list>
#xtranslate SETNIL(<first>[,<list,...>]) => <first>:=NIL[;SETNIL(<list>)]  
    ? STRING(LISTA)
    ? STRINGX(LISTA)
    SETNIL(LISTA)

//----------------------------------------------------------------------
#define ADD(a,b)   a+b     //tobbszoros define
#define XX(a,b)    a,b
    ADD(XX(a,b))

//----------------------------------------------------------------------
#define TRACE(x)  ? #x, x  //a regi Clipper is tudja!
    TRACE(a+b+c)
 
//----------------------------------------------------------------------
#translate EXCL ! <x> => (<x>)
    EXCL ! x y z

#define CONCAT1(x,y) ! x/**/y               //egymas melle iras 
    CONCAT1(x,6)                            //! x6
    EXCL CONCAT1(x,6)                       //(x)6
 
#translate CONCAT2(<x>,<y>) => ! <x><y>     //egymas melle iras  
    CONCAT2(x,6)                            //! x6 
    EXCL CONCAT2(x,6)                       //(x)6
 
#define GLUE1(x,y) ! x ## y                 //valodi ragasztas
    GLUE1(x,6)                              //! x6  
    EXCL GLUE1(x,6)                         //(x6) 

#translate GLUE2(<x>,<y>) => ! <x> ## <y>   //valodi ragasztas
    GLUE2(x,6)                              //! x6  
    EXCL GLUE2(x,6)                         //(x6) 
    EXCL GLUE2("x",'y')                     //("x"+'y')
 

//----------------------------------------------------------------------
#xtranslate RESTRICTED <x:egy,ketto>  =>  restricted(<"x">)
    restricted egy
    restricted ketto
    restricted harom
 
//----------------------------------------------------------------------
#xtranslate LOOK [<a>]:<b> => AHEAD([<a>,]<b>)
#xtranslate LOOK1 [<a>] [<x>] : <b> => AHEAD([<a>,]<b>)
    LOOK a:b
    LOOK :b
    LOOK1 1+2+3 :b   //ezt sajnos nem tudja
    LOOK1 :b
 
//----------------------------------------------------------------------
#undef HOPP
#define HOPP()  EMPTYPAR()
    HOPP
    HOPP()
    HOPP(a)

//----------------------------------------------------------------------
 