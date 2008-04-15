
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

//readline osztály
//soronként olvas egy file descriptorból
//osztálydefiníció class utasítással

//Ez a változat kevesebb stringet gyárt,
//helyette a read-bufferen belül rendezgeti az adatokat,
//és így kevésbé terheli a szemétgyűjtést -> gyorsabb.

#define INCSIZE 4096

****************************************************************************
class readline(object)
    method initialize
    attrib fd
    attrib buffer
    attrib nbyte
    method readline

****************************************************************************
static function readline.initialize(this,fd) 
    this:(object)initialize
    this:fd:=fd
    this:buffer:=a""
    this:nbyte:=0
    return this
    
****************************************************************************
static function readline.readline(this)

static nl:=bin(10)
local line,nlpos,nbyte

    nlpos:=at(nl,this:buffer)
    while( nlpos<=0 .or. this:nbyte<nlpos )
        if( this:nbyte>=len(this:buffer) )
            this:buffer+=replicate(x"00",INCSIZE)
        end
        nbyte:=xvread(this:fd,this:buffer,this:nbyte,len(this:buffer)-this:nbyte)
        if( nbyte>0 )
            this:nbyte+=nbyte
        else
            nlpos:=NIL
            exit
        end
        nlpos:=at(nl,this:buffer)
    end
    
    if( nlpos!=NIL )
        line:=xvgetchar(this:buffer,0,nlpos)
        xvmove(this:buffer,0,this:buffer,nlpos,this:nbyte-=nlpos)
    elseif(this:nbyte>0)
        line:=xvgetchar(this:buffer,0,this:nbyte)
        this:buffer:=a""
        this:nbyte:=0
    else
        line:=NIL
    end
    return line  //a következő sor, vagy NIL, ha vége a filének

****************************************************************************

