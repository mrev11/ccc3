
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

*****************************************************************************
function lastdayom(month) //CA-tools

static honapok:={31,28,31,30,31,30,31,31,30,31,30,31}
local m, utnap:=0, ev

    if( month==NIL )
        month:=date()
    end
   
    if( valtype(month)=="N" )
        m:=month
        if( 1<=m .and. m<=12 )
            utnap:=honapok[m]
        end

    elseif( valtype(month)=="D" )
        m:=month(month)

        if( m==2 ) //február 
            ev:=left(dtos(month),4)
            utnap:=val(right(dtos(stod(ev+"0301")-1),2))
        else
            utnap:=honapok[m]
        end
    end
    
    return utnap


*****************************************************************************
function addmonth(date,addm)
 
// A date-hez hozzáad addm hónapot,
// ha az így kapott dátum nem létezik, 
// akkor az adott hónap utolsó napját veszi

local y,m,d,mm

    if( date==NIL )
        date:=date()
    end
    
    if( empty(date) )
        return date
    end
    
    if( addm==NIL )
        addm:=0
    end

    mm:=year(date)*12+month(date)-1+addm
    m:=mm%12+1
    y:=round((mm-m+1)/12,0)
    d:=day(date)

    while( d>28 .and. empty(ymdtod(y,m,d)) )
        d--
    end

    return ymdtod(y,m,d)


****************************************************************************
static function ymdtod(y,m,d)
local w
    w:=padl(y,4,'0')+padl(m,2,'0')+padl(d,2,'0')
    return stod(w)


****************************************************************************
function isleap(d:=date()) //CA-tools
    return lastdayom(stod(substr(dtos(d),1,4)+"0201")) == 29


****************************************************************************
   