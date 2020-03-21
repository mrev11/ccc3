
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

#include "regex.ch"

using regex  regcomp regexec regfree


************************************************************************************
class csvreader(object)

    method  initialize
    method  free        // felszabaditja a regex handlert
    method  nextfield
    method  nextrecord

    attrib  text        // CSV formatumu binary text
    attrib  fieldcount  // mezok szama egy sorban (eloszor NIL)
    attrib  linecount   // hanyadik sorban tart az olvasas     

    attrib  regex       // regularis kifejezes handler (vegul free)
    attrib  delimeter   // hatarolo karakter
    attrib  delim       // a kurrens mezo hataroloja: delimeter|EOL|EOF
    attrib  pos         // az olvasas aktualis pozicioja


************************************************************************************
static function csvreader.initialize(this,text,delimeter)

    this:text:=text
    this:fieldcount:=NIL    
    this:linecount:=0

    if( this:regex==NIL .or. (delimeter!=NIL .and. delimeter!=this:delimeter) )
        this:free
        if( delimeter!=NIL )
            this:delimeter:=delimeter
        elseif( this:delimeter==NIL )
            this:delimeter:=","
        end
        this:regex:=csv_regex(this:delimeter)
    end
    
    this:delim:=NIL
    this:pos:={1,0}

    return this


************************************************************************************
static function csvreader.free(this)
    if( this:regex!=NIL )
        this:regex::regfree
        this:regex==NIL
    end    


************************************************************************************
static function csvreader.nextrecord(this) // kovetkezo sor / {}

local err, value, line:={}

    while( (value:=this:nextfield())!=NIL )
        line::aadd( value )
        if( this:delim==10 .or. this:delim==0 )
            exit
        end
    end
    this:linecount++
    
    if( this:fieldcount==NIL )
        this:fieldcount:=len(line)

    elseif( !empty(line) .and. this:fieldcount!=len(line) )
        err:=invalidformaterrorNew()
        err:operation:="csvreader.nextrecord"
        err:description:="field count error"
        err:args:={ this:linecount, this:fieldcount, len(line)  }
        break(err)
    end

    return line


************************************************************************************
static function csvreader.nextfield(this)  // kovetkezo mezo / NIL

local p:=regexec(this:regex,this:text,this:pos[1]+this:pos[2])
local value
local err

    if( p==NIL .or. p[2]==0 )
        return NIL
    end
    
    if( this:pos[1]+this:pos[2]!=p[1] )
        // a szintaktikus hibat az mutatja,
        // hogy az olvasas nem folytonos
    
        err:=invalidformaterrorNew()
        err:description("CSV syntax error at offset "+(this:pos[1]+this:pos[2])::str::alltrim)
        err:operation:="csvreader.nextfield"
        err:args:={this:text::substr(this:pos[1]+this:pos[2],32)}
        break(err)
    end

    this:pos[1]:=p[1]  //latest match offset
    this:pos[2]:=p[2]  //latest match length

    this:delim:=this:text[p[1]+p[2]-1]::asc

    if( len(this:text)==p[1]+p[2]-1 .and. this:delim!=10 )
        value:=this:text::substr(p[1],p[2])
        this:delim:=0 //EOF
    else 
        value:=this:text::substr(p[1],p[2]-1) //NL levagva
    end
    
    if( value::right(1)==bin(13) )
        //ha a sorvegeken eredetileg CRLF volt
        //akkor a CR hozza van ragadva a value-hoz
        value::=left(len(value)-1) //CR levagva
    end

    if( left(value,1)==a'"' )
        value::=substr(2,len(value)-2)    // remove " .... "
        value::=strtran(a'""',a'"')       // unescape  ""
    end

    return value


************************************************************************************
static function csv_regex(delimeter:=",")

local qq:='"([^"]|"")*"'        // elejen "
                                // belsejeben " -> ""
                                // vegen "


local xx:='[^"\n,][^\n,]*'      // eleje nem "
                                // utana barmi, kiveve '\n' es ','


local value:='(('+qq+')|('+xx+')|())' //qq vagy xx vagy ures
local delim:='([\n,]|$)'
local field:=value+delim

    if( delimeter!=',' )
        field::=strtran(',',delimeter)
    end
    
    //? "pattern",field

    return regcomp(field::str2bin)


************************************************************************************
