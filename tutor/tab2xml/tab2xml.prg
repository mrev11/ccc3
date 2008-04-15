
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

//Egy táblát XML-ben exportál az stdout-ra,
//a típusok Clipper típusként (C,N,D,L) vannak jelölve.

#include "table.ch"
 
******************************************************************************
static function usage()
    ? "Usage: tab2xml <tabspec>"
    ?
    quit
 
******************************************************************************
function main(tabspec)

local table,n:=0 
local hdr:=.t.,recno,nam,typ,val

    if( tabspec==NIL )
        ? "Error: <tabspec> not set"
        usage()
    end

    if( !file(tabspec) )
        ? "Error: "+tabspec+" not found"
        usage()
    end
    
    table:=tabResource(tabspec)
    
    if( table==NIL )
        ? "Error: unknown format"
        usage()
    end
    
    tabOpen(table,OPEN_READONLY)
    tabGotop(table)

    while( !tabEof(table) )

        if( hdr )
            hdr:=.f.
            ?? "<header>"
            for n:=1 to tabFcount(table)
                nam:=tabColumn(table)[n][COL_NAME]
                typ:=tabColumn(table)[n][COL_TYPE]
                ? "<column>"
                ?? "<name>"+nam+"</name>" 
                ?? "<type>"+typ+"</type>" 
                ?? "</column>"
            next
            ? "</header>"
        end

        recno:=tabPosition(table)
    
        ? "<r><n>"+alltrim(str(recno))+"</n>"
        for n:=1 to tabFcount(table)
            val:=tabEvalColumn(table,n)
            typ:=valtype(val)
            if( typ=="C" )
                val:=cdataif(alltrim(val))
            elseif( typ=="N" )
                val:=alltrim(str(val))
            elseif( typ=="L" )
                val:=if(val,"T","F")
            elseif( typ=="D" )
                val:=if(empty(val),"",dtos(val))
            end
            ?? "<v>"+val+"</v>" 
        next
        ?? "</r>"
        tabSkip(table)
    end
    ?
    return NIL

******************************************************************************
static function cdata(x)
local cd:="", n
    while( .t. )
        n:=at("]]>",x)
        if( n==0 )
            cd+="<![CDATA["+x+"]]>"
            exit
        else
            cd+="<![CDATA["+left(x,n+1)+"]]>" 
            x:=substr(x,n+2)
        end
    end
    return  cd
 
******************************************************************************
static function cdataif(x)
    if( "<"$x .or. "&"$x )
        return  cdata(x) 
    end
    return x

******************************************************************************
 