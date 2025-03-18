
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

#include "box.ch"

#include "table.ch"
#include "utility.ver"

#define APPVER    APPNAME+" "+VERSION
#define BLANKROW  {space(10),"C",0,0}
#define FIELDROW  {"FIELD","C",24,0} 

static APPNAME

*********************************************************************
function appstru(fname,app)

local tab,upg,sav,n,result
local fnamex
local aidx,aidxc,i,c
local err

    APPNAME:=app

    if( fname==NIL )
        ? APPVER, "Copyright (C) ComFirm BT. 1998."
        ? @"Usage: "+lower(APPNAME)+@" <filename>"
        ?
        quit
    end

    fname:=relpath(fname)
    
    fnamex:=fname

    if( !tabDataExt()$fnamex )
        fnamex+=tabDataExt()
    else
        fname:=left(fnamex,rat(".",fnamex)-1)
    end


    setcursor(0)
    setcolor("w/b,b/w")

    //set printer to (APPNAME+".REP")
    //set printer on


    if( !file(fnamex) )
        tab:=tabNew0(fname)
        tabAddColumn(tab,FIELDROW)
        tabCreate(tab)
    end

    tab:=tabResource(fnamex) 

    if( valtype(tab)!="A" .or. empty(tab) )
        ? @"tabResource failed:", tab
        ?
        quit
    end
    

    //az index oszlopok sorszamokkal vannak nyilvantartva
    //mivel az editalas soran a sorszamok elcsuszhatnak,
    //meg kell jegyezni az oszlopneveket
    
    aidx:=tabIndex(tab)
    for i:=1 to len(aidx)
        aidxc:=aidx[i][IND_COL]
        for c:=1 to len(aidxc)
            aidxc[c]:=tabColumn(tab)[aidxc[c]][COL_NAME] 
        next
    next
    
    sav:=aclone(tab)

    while( NIL!=(upg:=struktura(tab)) ) //struktura editalas
        
        tab:=tabNew0(tabFile(sav))
        tabPath(tab,tabPath(sav))

        for n:=1 to len(tabColumn(upg))
            if( !empty(tabColumn(upg)[n][1]) )
                tabAddColumn(tab,tabColumn(upg)[n])
            end
        next
        
        begin
            for n:=1 to len(tabIndex(upg))
                if( !empty(tabIndex(upg)[n][1]) )
                    tabAddIndex(tab,tabIndex(upg)[n])
                end
            next

        recover err <tabobjerror>
            result:=alert(@"tabAddIndex error",{@"Fix",@"Quit"})
            if( result!=1 )
                return NIL
            end
            tab:=aclone(sav)
            loop
        end
        
        result:=tabUpgrade(tab)
          
        if( result==NIL )
            alert(@"File busy: "+tabPathName(tab))

        elseif( result==.f. )

            if( 2<=alert(@"Cannot convert all fields!",{@"Cancel",@"Continue"}) )
                result:=tabUpgrade(tab,.t.)
                if( result==.f. )
                    alert(@"Conversion failed!")
                end
            end
        end
        
        exit
    end
    
    return NIL
   

************************************************************************
static function struktura(tab)

local brw:=brwCreate(1,2,maxrow()-1,maxcol()-28)
local upg:=aclone(tab)
local str:=tabColumn(upg),n,total:=0
local upgrade:=.f.
   
    for n:=1 to len(str)
         asize(str[n],4)  //name,type,len,dec
         total+=str[n][3]
    next

    if( empty(str) )
        aadd(str,BLANKROW)
    end

    brwFooting(brw,{@"Record length: "+alltrim(str(total,4))+" byte","",""})
    brw:headSep:=B_HS+B_HS+B_HS 
    brw:colSep:="   "
    brw:footSep:=B_HS+B_HS+B_HS
    brwArray(brw,str)

    brwColumn(brw,@"Name",brwABlock(brw,1),"@!S16 NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN")
    brwColumn(brw,@"Typ" ,brwABlock(brw,2),"@! A")
    brwColumn(brw,@"Len" ,brwABlock(brw,3),"@Z 999")
    brwColumn(brw,@"Dec" ,brwABlock(brw,4),"@Z 99")

    brwMenuName(brw,"["+tabPathName(tab)+"]")

    brwMenu(brw,@"App" ,@"New field to the end",{||fld_append(brw)})
    brwMenu(brw,@"Ins" ,@"New field at the cursor position",{||fld_insert(brw)})
    brwMenu(brw,@"Mod" ,@"Edit selected field",{||fld_modify(brw)})
    brwMenu(brw,@"Del" ,@"Delete selected field",{||fld_delete(brw)})

    if( !tabIndexExt()==".CTX" )
        brwMenu(brw,@"Xnd" ,@"Maintain indexes",{||brwKillFocus(brw),index(upg,brwArray(brw)),brwSetFocus(brw),.t.})
    end

    brwMenu(brw,@"Upg" ,@"Save modifications",{||upgrade:=.t.,.f.})

    brwCaption(brw,APPVER)
    brwSetFocus(brw)

    brw:getcolumn(1):cargo:={{|g|post_name(brw,g)}}
    brw:getcolumn(2):cargo:={{|g|post_type(brw,g)}}
    brw:getcolumn(3):cargo:={{|g|post_len(brw,g)},{|g|pre_len(brw,g)}}
    brw:getcolumn(4):cargo:={{|g|post_dec(brw,g)},{|g|pre_dec(brw,g)}}
 
    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)
    
    return if(upgrade,upg,NIL)


************************************************************************
static function post_name(brw,g)

local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local name:=g:varget(), n

    if( empty(name) )
        alert( @"Empty value not allowed!" )
        return .f.
    end

    for n:=1 to len(str)
        if( n!=pos .and. alltrim(name)==alltrim(str[n][1]) )
            alert( @"Column name must be unique!" )
            return .f.
        end
    next

    return .t.


************************************************************************
static function post_type(brw,g)

local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local type:=g:varget() 

    if( type=="D" )
        str[pos][3]:=8
        str[pos][4]:=0
    elseif( type=="L" )
        str[pos][3]:=1
        str[pos][4]:=0
    end

    return type$"CXNDL"
 

************************************************************************
static function post_len(brw,g)

local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local type:=str[pos][2]
local len:=g:varget() 

    if( str[pos][4] > len-2 )
        str[pos][4]:=max(len-2,0)
    end

    return 0<len .and. if(type=="C",.t.,len<=32)
 

************************************************************************
static function pre_len(brw,g)

local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local type:=str[pos][2]

    return  type$"CXN"
 

************************************************************************
static function post_dec(brw,g)

local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local len:=str[pos][3]

    return g:varget()<=max(len-2,0)
 

************************************************************************
static function pre_dec(brw,g)
 
local str:=brwArray(brw)
local pos:=brwArrayPos(brw)
local type:=str[pos][2]
local len:=str[pos][3]

    return  type$"N" .and. len>2


************************************************************************
static function fld_append(brw)

local arr:=brwArray(brw), pos
 
    aadd(arr,BLANKROW)
    brw:gobottom()
    pos:=brwArrayPos(brw) 
    brwEditRow(brw,{1,2,3,4})

    if( empty(arr[pos][1]) )
        adel(arr,pos)
        asize(arr,len(arr)-1)
        if( empty(arr) )
            aadd(arr,FIELDROW)
        end
        brw:gobottom()
    end
    return .t.


************************************************************************
static function fld_insert(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)

    aadd(arr,NIL) //ains kicsusztatja az utolso elemet!
    ains(arr,pos)
    arr[pos]:=BLANKROW
    brw:refreshall()
    brwEditRow(brw,{1,2,3,4})
    
    if( empty(arr[pos][1]) )
        adel(arr,pos)
        asize(arr,len(arr)-1)
        brw:refreshall()
    end

    return .t.


************************************************************************
static function fld_modify(brw)
    brwEditRow(brw,{1,2,3,4})
    return .t.


************************************************************************
static function fld_delete(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)

    adel(arr,pos)
    asize(arr,len(arr)-1)
    if( empty(arr) )
        fld_append(brw)        
    elseif( pos>len(arr) )
        brwArraypos(brw,pos-1)
    end
    brw:refreshall()
    return .t.


************************************************************************
function index(tab,str)

local brw:=brwCreate(9,20,maxrow()-3,maxcol()-2)
local idx:=aclone(tabIndex(tab)),i,x,cols,c
local upg:=NIL
   
    for i:=1 to len(idx)
         asize(idx[i],3)  //name,file,cols
         cols:=idx[i][3]
         x:=""
         for c:=1 to len(cols)
             x+=","+cols[c]
         next
         idx[i][3]:=substr(x,2)
    next

    if( empty(idx) )
        aadd(idx,{"","",""})
    end

    brwArray(brw,idx)

    brwColumn(brw,@"Name"   ,brwABlock(brw,1),"@! XXXXXXXXXX")
    brwColumn(brw,@"Column" ,brwABlock(brw,3),"@S40! "+replicate("X",128) )

    brwMenuName(brw,"["+tabIndexName(tab)+"]")

    brwMenu(brw,@"App" ,@"Create new index",{||idx_append(brw)})
    brwMenu(brw,@"Mod" ,@"Edit selected index",{||idx_modify(brw)})
    brwMenu(brw,@"Del" ,@"Delete selected index",{||idx_delete(brw)})
    
    brw:getcolumn(1):cargo:={{|g|valid_idxname(brw)}}
    brw:getcolumn(2):cargo:={{|g|valid_segnames(g,str)}}
 
    brwSetFocus(brw)
    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)
    
    asize(tabIndex(tab),0)
    for i:=1 to len(idx)
        if( !empty(idx[i][1]) )
            aadd(tabIndex(tab),{idx[i][1],tabFile(tab)+alltrim(str(i)),split(idx[i][3])})
        end
    next
    
    return NIL


************************************************************************
static function valid_idxname(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local name:=upper(alltrim(arr[pos][1])),n

    if( empty(name) )
        alert(@"Empty name not allowed!")
        return .f.
    end
    
    for n:=1 to len(arr)
        if( pos!=n .and. name==arr[n][1] )
            alert(@"Index name must be unique!")
            return .f.
        end
    end
    
    return .t.


************************************************************************
static function valid_segnames(g,str)

local colnames:=g:varget() 
local segname:=split(colnames)
local seg, n, i 

    if( empty(segname) .or. empty(colnames) )
        alert(@"Index must have columns!")
        return .f.
    end
    
    for n:=1 to len(segname)

        seg:=upper(alltrim(segname[n]))
        
        for i:=1 to len(str)
             if( seg==upper(alltrim(str[i][1])) )
                 exit
             end
        next
        
        if( i>len(str) )
            alert( @"Invaild column name: "+seg )
            return .f.
        end
    next
    
    return .t.



************************************************************************
static function idx_append(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
 
    if( !empty(arr[pos][1]) )
        aadd(brwArray(brw),{"","",""})
        brw:gobottom()
        pos:=brwArrayPos(brw) 
    end

    brwEditRow(brw,{1,2})
    
    if( empty(arr[pos][1]) )
        adel(arr,pos)
        asize(arr,len(arr)-1)
        if( empty(arr) )
            aadd(brwArray(brw),{"","",""})
        end
        brw:gobottom()
    end
    
    return .t.


************************************************************************
static function idx_modify(brw)
    brwEditRow(brw,{1,2})
    return .t.


************************************************************************
static function idx_delete(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)

    adel(arr,pos)
    asize(arr,len(arr)-1)

    if( empty(arr) )
        aadd(brwArray(brw),{"","",""})
    elseif( pos>len(arr) )
        brwArraypos(brw,pos-1)
    end
    brw:refreshall()

    return .t.


************************************************************************
static function tabPrint(tab)
local n
    for n:=1 to len(tab)
        ? tab[n]
    next
    return NIL


************************************************************************
static function relpath(fname)
local dn:=dirname()+dirsep()
    if( at(dn,fname)==1 )
        fname:=substr(fname,len(dn)+1)
    end
    return fname


************************************************************************
 