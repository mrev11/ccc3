
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

// jtfilefilter
//
// Filefilter a jtdirlist és jtfilechooser osztályokhoz.
// Directorykhoz és normál filékhez külön filtert kell magadni.
//
// regexdir  : 1 db reguláris kifejezés directorykra
// regexlist : reguláris kifejezések listája normál filékre 
//
// regexlist az addregex és addpattern metódusokkal bővíthető,
// utóbbi a filémaszkot megpróbálja reguláris kifejezésre alakítani

#include "jtelem.ch"
 

****************************************************************************
class jtfilefilter(object) 
    method  initialize
    attrib  description
    attrib  regexdir        //regular exp for dirs
    attrib  regexlist       //regular exps for files
    method  addregex        {|this,rx|aadd(this:regexlist,rx),rx}
    method  addpattern      {|this,p,fp|aadd(this:regexlist,fp:=jtfilepattern(p)),fp}
    method  xmlout

****************************************************************************
static function jtfilefilter.initialize(this) 
    this:(object)initialize
    this:description:=""
    this:regexdir:=NIL
    this:regexlist:={}
    return this
    
****************************************************************************
static function jtfilefilter.xmlout(this)
local n, x
    x:="<filter>"
    if( !empty(this:description) )
        x+="<description>"+this:description+"</description>" 
    end
    if( !empty(this:regexdir) )
        x+="<dirmask>"+this:regexdir+"</dirmask>"
    end
    for n:=1 to len(this:regexlist)
        x+="<mask>"+this:regexlist[n]+"</mask>"
    next
    x+="</filter>"
    return x


****************************************************************************
function jtfilepattern(x)
    
//Megjegyzés: a Jáva Pattern osztály ennél sokkal többet 
//tud, ez itt csak emlékeztető a legegyszerűbb esetekre.

    if( x!=NIL )
        x:=strtran(x,".","\.")
        x:=strtran(x,"*",".*")
        x:=strtran(x,"?",".")
    end
    return x
 
****************************************************************************
 