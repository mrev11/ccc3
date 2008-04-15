
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

//dbf megjelenítő,
//Vermes M. 2003.03.10.
//példa a dbaseiii osztály
//(dbfclass, dbfedrec) használatára.
//
//mutatja a memók tartalmát (.dbm file),
//stringeket tud keresni (f/F billentyűk),
//bármely típus string ábrázolása kereshető,
//mezőhatárokon átlógó találatokat jelezhet,
//lehet csak egy mezőben keresni (memókban is),
//lehet hátrafelé keresni.

#include "inkey.ch"
 
static searchstring    := ""
static casesensitive   := .f.
static includedeleted  := .f.
static searchfield     := 0
static reversedirect   := .f.

#include "search.say"
 
******************************************************************************
function main(dbfspec)

local db:=dbaseiiiNew()
local b,rw,n,c,h,t,w,d,p
local memonm,memofd,e

    set date format "yyyy-mm-dd"

    //set printer to log
    //set printer on
 
    if( dbfspec==NIL )
        ? "Usage: dbfview  <dbfspec>"
        ?
        quit
    elseif( !file(dbfspec) )
        ? dbfspec, "not found"
        ?
        quit
    end

    db:open(dbfspec)
    db:gotop
    
    b:=dbBrowse(db)

    rw:=max(4,len(alltrim(str(db:reccnt)))) //width of Rec#
    brwColumn(b,padl("Rec#",rw),{||str(db:recno,rw,0)+if(db:deleted,"*"," ")},rw+1)
    b:freeze:=1
 
    for n:=1 to len(db:dbstruct)

        c:=db:dbstruct[n]

        h:=c[1] //heading
        t:=c[2] //type
        w:=c[3] //width
        d:=c[4] //dec
        
        if( t=="C" )
            p:=replicate("X",w)

            if( w>64 )
                p:="@S64 "+p
            
            elseif( left(h,3)=="DBM" .and. w==10  ) //memó
            
                if( memofd==NIL )
                    memonm:=strtran(dbfspec,".dbf",".dbm")
                    memofd:=memoOpen(memonm)
                    if( memofd<0 )
                        e:=fnferrorNew()
                        e:description:="Could not open memo file"
                        e:operation:="memoOpen"
                        e:filename:=memonm
                        break(e)
                    end
                end
                
                db:fldblk[n]:=memoblk(memofd,db:fldblk[n])  //blokk lecserélve
                c[3]:=512                                   //width lecserélve
                p:="@S64 "+replicate("X",1024)              //picture lecserélve
            end

        elseif( t=="N" )
            p:=replicate("9",w)
            if( d>0 )
               p+="."+replicate("9",w)
               p:=right(p,w)
            end

        elseif( t=="D" )
            p:="@D"

        elseif( t=="L" )
            p:="@L"
        end
        
        brwColumn(b,h,db:fldblk[n],p)
    next
    
    brwMenuName(b,"dbview: "+dbfspec)
    
    brwApplyKey(b,{|b,k|applykey(b,k,db)})
    
    brwShow(b)
    brwLoop(b)
    brwHide(b)
 
    return NIL

******************************************************************************
static function memoblk(fd,blk)
    return {|of|of:=eval(blk),if(empty(of),"",memoGetValue(fd,val(of)))}

******************************************************************************
static function applykey(b,k,db)

    if( k==K_INS )
        dbEditRecord(db,"TM")
        return .t.

    elseif( k==K_F3 .or. k==asc("f") .or. k==asc("/") )
        search({|g|getlistini(g,db)},{|g|readmodal(g)},{|g|dosearch(g,db)})
        b:refreshall
        return .t.

    elseif( k==K_SH_F3 .or. k==asc("F") )
        dosearch(,db,.t.)
        b:refreshall
        return .t.

    elseif( k==asc("n") )
        reversedirect:=.f.
        dosearch(,db,.t.)
        b:refreshall
        return .t.

    elseif( k==asc("p") )
        reversedirect:=.t.
        dosearch(,db,.t.)
        b:refreshall
        return .t.
    end
    return NIL


******************************************************************************
// Keresés
******************************************************************************
static function getlistini(getlist,db)
local n
    g_search:picture:="@KS20 "+replicate("X",32)
    g_search:varput(searchstring)
    g_c:varput(casesensitive)
    g_d:varput(includedeleted)
    g_r:varput(reversedirect)
    
    g_field:item("any")
    for n:=1 to len(db:dbstruct)
        g_field:item( db:dbstruct[n][1] )
    next
    g_field:select(1+searchfield)

    aeval(getlist,{|g|g:display})
    return NIL

******************************************************************************
static function dosearch(getlist,db,nxt)

local pos

    if( getlist!=NIL )
        searchstring   := rtrim(g_search:varget)
        casesensitive  := g_c:varget
        includedeleted := g_d:varget
        reversedirect  := g_r:varget
        searchfield    := g_field:selected-1
    end

    if( !empty(searchstring) )
        pos:=db:recno

        if( nxt==.t. )
            db:skip( if(reversedirect,-1,1)  )  
        end

        if( !dosearch1(db,searchstring,casesensitive,;
                          includedeleted,reversedirect,searchfield) )
            db:goto(pos)
            alert('"'+searchstring+'";;not found')
        end
    end

    return .t.

******************************************************************************
static function dosearch1(db,ss,cs,id,rv,sf)

local buffer,typ,wid,dec

    if( sf!=0 )
        typ:=db:dbstruct[sf][2] 
        wid:=db:dbstruct[sf][3]
        dec:=db:dbstruct[sf][4]
    end
 
    if( !cs )
        ss:=lower(ss)
    end

    while( !db:eof )

        if( id .or. !db:deleted )

            if( sf==0 )
                buffer:=bin2str(db:buffer)

            else
                buffer:=db:evalcolumn(sf)

                if( typ=="N" )
                    buffer:=str(buffer,wid,dec)

                elseif(typ=="D")
                    buffer:=dtos(buffer)

                elseif(typ=="L")
                    buffer:=if(buffer,"T","F")

                end
            end

            if( !cs )
                buffer:=lower(buffer)
            end

            if( ss $ buffer ) 
                return .t.
            end
        end

        db:skip( if(rv,-1,1)  )  
    end
    return .f.

******************************************************************************
 