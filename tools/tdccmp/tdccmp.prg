
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

#include "bttable.ch"

// TAB_ALIAS  
// TAB_FILE   
// TAB_PATH   
// TAB_EXT    

// TAB_COLUMN 
// TAB_INDEX  


***************************************************************************************
function main(tdcspec,btspec)

local dd,n

    if( tdcspec==NIL .or. btspec==NIL )
        ? "Usage:  tdccmp.exe  <tdcspec>  <btspec>"
        ?
        quit
    end

    if( !direxist(tdcspec) )
        //egy tabla diff-je
        return diff(tdcspec,btspec)
    end

    //egesz directory diff-je

    if( !direxist(btspec) )
        //ha tdcspec egy directory
        //akkor btspec-nek is directorynak kell lennie
        ? "Not a directory: ", btspec
        ?
        quit
    end
    

    dd:=directory(tdcspec+dirsep()+"*.tdc")
    for n:=1 to len(dd)
        proc(dd[n][1],tdcspec,btspec)
    next


***************************************************************************************
function proc(tdc,tdcdir,btdir)

local tdcspec:=tdcdir+dirsep()+tdc
local fd:=fopen(tdcspec)
local rl:=readlineNew(fd),line
local table,path
local btspec

    while( NIL!=(line:=rl:readline) )
        line::=bin2str
        line::=strtran(chr(10))
        line::=strtran(chr(13))
        
        if( "!table"$line )
            table:=line::strtran("!table")::alltrim::lower
        elseif( "!path"$line  )
            path:=line::strtran("!path")::alltrim::lower
        end
    next
    fclose(fd)
    
    btspec:=btdir+dirsep()
    if( path!=NIL ) 
        btspec+=path+dirsep()
    end 
    btspec+=table
    btspec+=".bt"
    
    
    if( file(btspec) )
        return diff(tdcspec,btspec)
    end

    ? "Missing datafile for",tdc


***************************************************************************************
function diff(tdcspec,btspec)

local hash:=diff1(tdcspec,btspec)
local arr,n,item

    //mi van benne?    
    //azon elemek erteke
    //  amik benne vannak a tdc-ben de nincsenek a bt-ben: .t.
    //  amik benne vannak a bt-ben de nincsenek a tdc-ben: .f.
    //ha minden egyezik, akkor a hash ures

    if( hash:valuecount==0 )
        return NIL
    end
    
    arr:={}
    item:=hash:first
    while(item!=NIL)
        arr::aadd(item)
        item:=hash:next
    end
    
    asort(arr,,,{|x,y|x[1]<y[1]})
    ? ">>>",tdcspec
    for n:=1 to len(arr)
        if(arr[n][2])
            ? arr[n][1]
        end
    next

    ? ">>>",btspec
    for n:=1 to len(arr)
        if(!arr[n][2])
            ? arr[n][1]
        end
    next
    ?

***************************************************************************************
function diff1(tdcspec,btspec)

local fd,rl,line
local hash:=simplehashNew(),item
local table,idx,col,n

    if(0>(fd:=fopen(tdcspec)))
        ? "Can not open tdcspec: ", tdcspec
        ?
        quit
    end
    
    if( NIL==(table:=tabResource(btspec)) )
        ? "Can not read btspec: ", btspec
        ?
        quit
    end

    rl:=readlineNew(fd)
    while( NIL!=(line:=rl:readline)  )
        line::=bin2str
        
        if( left(line,1)=="!" )
            //csak !index + !field
            if( "!field"$line  )
                line::=form_tdcline_field
                hash[line]:=.t. //tdc
            elseif( "!index"$line  )
                line::=form_tdcline_index
                hash[line]:=.t. //tdc
            end
        end
    end
    fclose(fd)


    for n:=1 to len(table[TAB_COLUMN])
        col:=table[TAB_COLUMN][n]
        col::=form_field
        if( hash[col]==.t. )
            hash:remove(col)
        else
            hash[col]:=.f. //bt
        end
    next    

    for n:=1 to len(table[TAB_INDEX])
        idx:=table[TAB_INDEX][n]
        idx::=form_index(table)
        if( hash[idx]==.t. )
            hash:remove(idx)
        else
            hash[idx]:=.f. //bt
        end
    next    

    //mi van benne?    
    //azon elemek erteke
    //  amik benne vannak a tdc-ben de nincsenek a bt-ben: .t.
    //  amik benne vannak a bt-ben de nincsenek a tdc-ben: .f.
    //ha minden egyezik, akkor a hash ures

    return hash


***************************************************************************************
static function form_tdcline_field(line)
local x,n

    line::=strtran(chr(10))
    line::=strtran(chr(13))
    line::=alltrim
    while( "  "$line )
        line::=strtran("  "," ")
    end
    line::=upper
    line::=split(" ")
    
    x:=line[1]::lower             //!field
    for n:=2 to len(line)
        x+=" "+line[n]
    next
    return x


***************************************************************************************
static function form_tdcline_index(line)
local x,n

    line::=strtran(chr(10))
    line::=strtran(chr(13))
    line::=alltrim
    while( "  "$line )
        line::=strtran("  "," ")
    end
    line::=upper
    line::=split(" ")
    
    x:=line[1]::lower             //!index
    x+=" "+line[2]::lower         //index name
  //x+=" "+line[3]::lower         //index file name (kihagy)
    x+=" [...]"

    for n:=4 to len(line)
        x+=" "+line[n]
    next
    return x


***************************************************************************************
static function form_field(col)
local x:="!field"
    x+=" "+col[1]
    x+=" "+col[2]
    x+=" "+col[3]::str::alltrim
    x+=" "+col[4]::str::alltrim
    return x


***************************************************************************************
static function form_index(idx,table)
local seg
local x:="!index"

    x+=" "+idx[1]::lower          //index name
    //x+=" "+idx[2]::lower        //index file name (kihagy)
    x+=" [...]"

    for seg:=1 to len(idx[3])
        x+=" "+table[TAB_COLUMN][idx[3][seg]][1]::upper
    next
    return x


***************************************************************************************











