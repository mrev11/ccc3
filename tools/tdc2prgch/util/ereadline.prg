
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

//ereadline osztály
//soronként olvas egy file descriptorból hibakezeléssel.
//osztálydefiníció class utasítással

//Ez a változat kevesebb stringet gyárt,
//helyette a read-bufferen belül rendezgeti az adatokat,
//és így kevésbé terheli a szemétgyűjtést -> gyorsabb.

//Kiegészítve az endofline atribútummal (sorvég karakter).

#define INCSIZE 4096

****************************************************************************
class ereadline(object)
    method initialize
    attrib fd
    attrib buffer
    attrib nbyte
    attrib endofline
    attrib errno

    method readline

****************************************************************************
static function ereadline.initialize(this,fd) 
    this:(object)initialize
    this:fd:=fd
    this:buffer:=a""
    this:nbyte:=0
    this:endofline:=bin(10)
    this:errno:=0
    return this
    
****************************************************************************
static function ereadline.readline(this)

local line,eolpos,nbyte

    eolpos:=at(this:endofline,this:buffer)
    while( eolpos<=0 .or. this:nbyte<eolpos )
        if( this:nbyte>=len(this:buffer) )
            this:buffer+=replicate(x"00",INCSIZE)
        end
        nbyte:=xvread(this:fd,this:buffer,this:nbyte,len(this:buffer)-this:nbyte)
        if (nbyte==-1)
           this:errno:=ferror()
           break(readerrorNew()) //enelkul vegtelen ciklus
        elseif( nbyte>0 )
            this:nbyte+=nbyte
        else
            eolpos:=NIL
            exit
        end
        eolpos:=at(this:endofline,this:buffer)
    end
    
    if( eolpos!=NIL )
        line:=xvgetchar(this:buffer,0,eolpos)
        xvmove(this:buffer,0,this:buffer,eolpos,this:nbyte-=eolpos)
    elseif(this:nbyte>0)
        line:=xvgetchar(this:buffer,0,this:nbyte)
        this:buffer:=a""
        this:nbyte:=0
    else
        line:=NIL
    end
    return line  //a következő sor, vagy NIL, ha vége a filének

****************************************************************************

