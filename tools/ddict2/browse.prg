
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

//BROWSE-olások

#include "inkey.ch"
#include "box.ch"
 
#include "table.ch"
#include "_ddict.ch"
#include "_dummy.ch"

****************************************************************************
function browseDiff(prevBrw) // browse struktúrák összehasonlításához

local browse:=brwCreate(5,30,maxrow()-1,maxcol()-2)
local dbfname, str1, str2, m, n, col

    if( empty(dbstruct()) )
        return NIL
    end
    
    str1:=ctoa(dbstruct())
    str2:=structColumn()

    if( empty(str2) )
        alert(DUMMY:pathname+" not found!")
        return NIL
    end

    if( len(dbfname:=DUMMY:pathname)>30 )
        dbfname:="..."+right(dbfname,27)
    end
    
    if( alltrim(atoc(str2))==alltrim(dbstruct()) )
        alert("Structures in datadict and database are the same.")
        return NIL
    end

    for n:=1 to len(str1)
         aadd(str1[n],"dic")
    next
    for n:=1 to len(str2)
         aadd(str2[n],"dbf")
    next

    for n:=1 to len(str2)
         col:=str2[n]
         //alert( col[1]+col[2]+str(col[3])+str(col[4])+col[5] )
         
         if( 0<(m:=ascan(str1,{|c| c[1]==col[1].and.;
                                   c[2]==col[2].and.;
                                   c[3]==col[3].and.;
                                   c[4]==col[4]       }))  )
             adel(str1,m)
             asize(str1,len(str1)-1)
         else
             aadd(str1,col)
         end
    next
    if( len(str1)<=0 )
        alert("Structures in datadict and database are the same.")
        return NIL
    end
    brwKillFocus(prevBrw)
    
    asort(str1,,,{|x,y|x[1]<y[1]})
    brwArray(browse,str1)
    brwColumn(browse,"",brwABlock(browse,5),3)
    brwColumn(browse,"Field",brwABlock(browse,1),24)
    brwColumn(browse,"Typ",brwABlock(browse,2),3)
    brwColumn(browse,"Len",brwABlock(browse,3),"999")
    brwColumn(browse,"Dec",brwABlock(browse,4),"999")
    brwMenuName(browse,dbfname)
    brwMenu(browse,"","Differences between datadict and database",{||.f.})

    browse:headSep:=B_HD
    browse:colSep:="  "

    brwSetFocus(browse)
    browse:colorspec:="bg/w,w/bg,,,bg/w"
    brwShow(browse)
    brwLoop(browse)
    brwHide(browse)

    brwSetFocus(prevBrw)
    return NIL


****************************************************************************
function browseData(prevbrw) // kiválasztott tábla browse-olása

local err, browse, index, n

    if( !structLatest("Only the latest version modifiable!") )
        return NIL
    end

    if( !structLoadDummy() )
        alert(DUMMY:pathname+if(file(lower(DUMMY:pathname))," busy"," not found"))
    else
        brwKillFocus(prevbrw)

        begin sequence
            DUMMY:open

        recover using err
        
            //alert("RECOVER")
            //itt vizsgálni kéne, 
            //hogy tényleg az indexek okozták-e az elszállást,
            //vagy át kéne térni az új struktúrált recover-re
            
            DUMMY:close
            if( tabDelIndex(DUMMY:table) )
                alert("Incompatible indexes deleted!")
            else
                alert("Deleting incompatible indexes failed!")
                asize(DUMMY:index,0)
            end
            DUMMY:open
        end sequence
        

        if( empty(DDICT_INDNAME) )
            index:="{recno}"

        elseif( 0==ascan(DUMMY:index,{|a|a[1]==alltrim(DDICT_INDNAME)}) )
            index:="{recno}"
            
        else
            DUMMY:control:=alltrim(DDICT_INDNAME)

            index:=alltrim(DDICT_INDFIELD)
            if( len(index)>52 )
                index:=left(index,49)
                index:=left(index,rat(",",index))+"..."
            end
            index:="{"+index+"}"
        end

        browse:=DUMMY:browse(0,0,maxrow(),maxcol(),.t.)
        brwMenuName(browse,"Table: "+DUMMY:pathname)
        brwMenu(browse,"","Order: "+lower(alltrim(DDICT_INDNAME))+" "+index,{||.f.})

        brwSetFocus(browse)
        browse:colorspec:="w/b,b/w,,,w/b"
        brwShow(browse)
        brwLoop(browse)
        brwHide(browse)
        brwSetFocus(prevbrw)
        
        DUMMY:close
    end
    return NIL


****************************************************************************
function browseStruct(str,name,rect) // dbStruct browse-olása
local crs:=setcursor(0), browse

    if( empty(rect) )
        rect:={3,38,23,78}
    end

    browse:=brwCreate(rect[1],rect[2],rect[3],rect[4])

    browse:headSep:=B_HD
    browse:colSep:="  "

    brwArray(browse,str)
    brwColumn(browse,"Field",brwABlock(browse,1),24)
    brwColumn(browse,"T",brwABlock(browse,2),1)
    brwColumn(browse,"  H",brwABlock(browse,3),"999")
    brwColumn(browse,"D",brwABlock(browse,4),"9")
    brwMenuName(browse,name)
    brwMenu(browse,"","database structure",{||.f.})

    brwSetFocus(browse)
    browse:colorspec:="bg/w,w/bg,,,gb/w"
    brwShow(browse)
    brwLoop(browse)
    brwHide(browse)
    setcursor(crs)
    return if(lastkey()==K_ENTER,brwArraypos(browse),0)


****************************************************************************
