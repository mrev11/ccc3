
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

************************************************************************************
class csvreader(object)

    method  initialize
    method  nextrecord
    method  nextfield
    method  free        {||NIL}

    attrib  text        // CSV formatumu binary text
    attrib  delimeter   // hatarolo karakter

    attrib  delim       // a kurrens mezo hataroloja: delimeter|EOL|EOF
    attrib  fieldcount  // mezok szama egy sorban (eloszor NIL)
    attrib  linecount   // hanyadik sorban tart az olvasas     
    attrib  pos         // az olvasas aktualis pozicioja

    attrib  qq          // dupla idezo
    attrib  nl          // bin(10) vagy chr(10)
    attrib  cr          // bin(13) vagy chr(13)


************************************************************************************
static function csvreader.initialize(this,text,delimeter:=",")

    this:text:=text
    this:delimeter:=delimeter

    this:delim:=NIL
    this:fieldcount:=NIL    
    this:linecount:=0
    this:pos:=1

    this:qq:='"'
    this:nl:=chr(10)
    this:cr:=chr(13)

    return this


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
        err:description:="field count error in line "+this:linecount::str::alltrim
        err:args:={ this:linecount, this:fieldcount, len(line)  }
        break(err)
    end

    return line


************************************************************************************
static function csvreader.nextfield(this)  // kovetkezo mezo / NIL

local p1,p2
local pd,pn
local value,err

    p1:=this:pos

    if( p1>len(this:text) )
        // nincs tobb adat
        return NIL

    elseif( p1==1 )
        // alkalmazkodik text tipusahoz
        if( this:text::valtype=="X" )
            this:delimeter::=str2bin
            this:qq::=str2bin
            this:nl::=str2bin
            this:cr::=str2bin
        end
    end

    if( this:text[p1]==this:qq )
        p2:=qq(this:text,p1)

        if( p2<=0 )
            err:=invalidformaterrorNew()
            err:operation:="csvreader.nextfield"
            err:description:="incomplete quotation at offset "+p1::str::alltrim
            break(err)
        
        elseif( p2>=this:text::len )
            p2:=0
        
        elseif( this:text[p2+1]==this:delimeter )
            p2++

        elseif( this:text[p2+1]==this:nl )
            p2++

        elseif( this:text[p2+1..p2+2]==this:cr+this:nl )
            p2+=2

        else
            err:=invalidformaterrorNew()
            err:operation:="csvreader.nextfield"
            err:description:="unexpected char after quotation at offset "+(p2+1)::str::alltrim
            break(err)
        end

    else
        pd:=at(this:delimeter,this:text,p1)
        pn:=at(this:nl,this:text,p1)
        
        if( pd==0 .and. pn==0 )
            p2:=0
        elseif( pd==0 )
            p2:=pn
        elseif( pn==0 )
            p2:=pd
        else
            p2:=min(pd,pn)
        end
    end
    
    if( p2==0 )
        this:delim:=0  //eof
    else
        this:delim:=this:text[p2]::asc // delimeter|eol
    end
    
    if( p1>p2 )
        value:=this:text[p1..]
        this:pos:=len(this:text)+1

    else//if( p1<=p2 )
        value:=this:text[p1..p2-1]
        this:pos:=p2+1    
    end
    
    if( value::right(1)==this:cr )
        value::=left(len(value)-1) //esetleges cr levagva
    end

    if( left(value,1)==a'"' )
        value::=substr(2,len(value)-2)    // remove " .... "
        value::=strtran(a'""',a'"')       // unescape  ""
    end

    return value


************************************************************************************
static function qq(text,pos)

local qq:=text[pos]
local pq1:=pos               // bal
local pq2:=at(qq,text,pq1+1) // jobb

    while( .t. )
        if( pq2==0 )
            exit // error

        elseif( len(text)>pq2 .and. text[pq2+1]==qq )
            pq1:=pq2+1
            pq2:=at(qq,text,pq1+1) 

        else
            exit // ok
        end
    end
    return pq2


************************************************************************************
