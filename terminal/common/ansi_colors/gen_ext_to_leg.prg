
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

function main()
local x,l,rgbx,rgbl,i
local tipx,tipl
local sum,optsum,optidx,intense
local convtab:={}

    set alternate to "log-ext_to_leg"
    set alternate on
    set console off

    for x:=1 to 256
        ? x-1 , rgbx:=ansi_colors(x)
        
        tipx:=tip(rgbx[1],rgbx[2],rgbx[3])
        

        optsum:=999999999
        optidx:=0

        for l:=1 to 16
            rgbl:=ansi_colors(l)
            tipl:=tip(rgbl[1],rgbl[2],rgbl[3])
    
            sum:=if(tipx==tipl,0,100)
            sum+=abs(rgbx[1]-rgbl[1])
            sum+=abs(rgbx[2]-rgbl[2])
            sum+=abs(rgbx[3]-rgbl[3])
            
            if(sum<optsum)
                optsum:=sum
                optidx:=l
            end
        next 

        intense:=.f.
        for i:=1 to 3
            intense:=intense.or.(rgbx[i]>=250)
        next
        if( intense )
            ?? " *"
            optidx:=numor(optidx-1,8)+1
        else
            ?? "  "
        end

        ?? "  -->", optidx-1, ansi_colors(optidx) 
        
        aadd(convtab,optidx-1)
    next
    
    ?
    for x:=1 to len(convtab)
        convtab[x]::=str::alltrim
    next    
    


    
    ? convtab
    ?





******************************************************************************************
static function tip(r,g,b)

    if( r==g .and. g==b )
        return 'w'

    elseif( g==b )
        return if(r>g,"r","gb" )

    elseif( r==b )
        return if(g>r,"g","rb" )

    elseif( r==g )
        return if(b>r,"b","rg" )

    else
        return 'x'
    end 

    
******************************************************************************************











    