
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

#include "directry.ch"

#include "icons.ch"
 
static s_ziplist  := "ziplist.txt"
static s_zipdir   := "zipdir"
static s_notexist := "Nem elérhető"

#define PKG_CAT     1
#define PKG_ZIP     2
#define PKG_NAM     3
#define PKG_SRV     4
#define PKG_CLN     5
#define PKG_SEL     6
#define PKG_SIZ     7
#define PKG_SIZEOF  7

******************************************************************************
function main(zipdir,ziplist)

local a:={},line,n,i
local dir,memo,zipname,dx
local dlg,brw,bar,pan,box,msg 

    s_zipdir:=zipdir
    s_ziplist:=ziplist

    set date format "yyyy.mm.dd"
    set dosconv off

    alertblock({|t,a|jtalert(t,a)})
    
    jtencoding("UTF-8")
    
    dir:=directory(s_zipdir+dirsep()+fullmask(),"H")
    
  #ifdef _WINDOWS_
    for n:=1 to len(dir)
        dir[n][1]:=lower(dir[n][1])
    next
  #endif    
 
    memo:=memoread(s_ziplist)    
    memo:=strtran(memo,chr(13),"")
    memo:=split(memo,chr(10))

    for n:=1 to len(memo)
        if( !empty(memo[n]) .and. !left(alltrim(memo[n]),1)=="#"  )
            line:=split(memo[n],"|") 
            for i:=1 to len(line)
                line[i]:=alltrim(line[i])
            next
            
            asize(line,PKG_SIZEOF)
            
            zipname:=line[PKG_ZIP]
           
            dx:=ascan(dir,{|d|d[F_NAME]==zipname})
            if( dx>0 )
                line[PKG_SRV]:=datetime(dir[dx])  
                line[PKG_SIZ]:=dir[dx][F_SIZE]
            else
                line[PKG_SRV]:=s_notexist
                line[PKG_SIZ]:=0
            end

            line[PKG_CLN]:=s_notexist 
            line[PKG_SEL]:=.f.

            aadd(a,line)
        next
    next
    
    dlg:=jtdialogNew(12,12,30,100)
    dlg:name:="cccdown"
    dlg:layout:="vbox"
    dlg:caption:="CCC Letöltő" 

    brw:=jtbrowsearrayNew()
    brw:name:="browse"
    brw:array:=a
    brw:maxrow:=len(a)
                                            
    brw:addcolumn("Platform"    ,{||platform_name(brw)} ,"XXXXXXX")
    brw:addcolumn("Csomag"      ,PKG_ZIP                ,replicate("X",20))
    brw:addcolumn("Megnevezés"  ,PKG_NAM                ,replicate("X",32))
    brw:addcolumn("Letölt"      ,PKG_SEL                ,"@L"):editable:=.t.
    brw:addcolumn("Méret"       ,PKG_SIZ                ,"@RN 99,999,999")
    brw:addcolumn("Szerver idő" ,PKG_SRV                ,replicate("X",20))
    brw:addcolumn("Lokális idő" ,PKG_CLN                ,replicate("X",20))
 
    bar:=jttoolbarNew()
    bar:additem(  box:=jtcheckNew() )
                  box:name:="checkwin"
                  box:text:="Windows" 
                  box:varput(.t.)
                  box:tooltip:="Frissíti a Windows csomagokat."

    bar:additem(  box:=jtcheckNew() )
                  box:name:="checklin"
                  box:text:="Linux" 
                  box:varput(.t.)
                  box:tooltip:="Frissíti a Linux csomagokat."

    bar:additem(  box:=jtcheckNew() )
                  box:name:="checksol"
                  box:text:="Solaris" 
                  box:varput(.t.)
                  box:tooltip:="Frissíti a Solaris csomagokat."

    bar:additem(  box:=jtpushNew() )
                  box:name:="locdir"
                  box:text:="Hová töltse?" 
                  box:icon:=ICON_OPEN
                  box:tooltip:="Lokális könyvtár választás a letöltéshez"
                  box:actionblock:={||seldir(dlg)}

    bar:additem(  box:=jtpushNew() )
                  box:name:="download"
                  box:text:="Letöltés"
                  box:icon:=ICON_EXEC
                  box:tooltip:="Indítja a kijelölt csomagok letöltését"
                  box:actionblock:={||download(dlg)}

    bar:additem(  box:=jthglueNew() )

    bar:additem(  box:=jtpushNew() )
                  box:name:="exit"
                  box:text:="Kilép"
                  box:icon:=ICON_EXIT
                  box:tooltip:="Kilép"
                  box:actionblock:={||quit()}

    pan:=jtpanelNew()

    pan:additem(  box:=jtlabelNew() )
                  box:text:="Lokális directory: " 

    pan:additem(  box:=jtlabelNew() )
                  box:name:="labeldir"
                  box:text:="" 

    pan:additem(  box:=jthglueNew() )

    pan:additem(  box:=jtprogbarNew() )
                  box:name:="progbar"
                  box:text:="" 

    pan:additem(  box:=jthglueNew() )
 

    dlg:add(bar)
    dlg:add(brw)
    dlg:add(pan)
    dlg:varinst("cccdown") //azt hittem ez automatikus
    dlg:show

    brw:pagefirst
    while( NIL!=(msg:=dlg:getmessage) ) 
    end

    return NIL


******************************************************************************
static function seldir(dlg)
local fc,ch

    fc:=jtfilechooserNew()  
    fc:caption:="Hova menjen a letöltés?"
    fc:text:="Kiválaszt"
    fc:selectmode:="D"
    fc:multiselect:=.f.
    ch:=fc:getchoice 

    if( empty(ch) )
        return NIL
    else
        ch:=ch[1]
    end

    dlg:var:labeldir:changetext(ch)
    reload(dlg)
    return NIL
 

******************************************************************************
static function reload(dlg)

local termdir,dir,dx 
local kat,win,lin,sol
local brw,arr,n
 
    termdir:=dlg:var:labeldir:text
    dir:=jtdirectory(termdir+dirsep()+fullmask())
    
    brw:=dlg:var:browse 
    arr:=brw:array
    win:=dlg:var:checkwin:state
    lin:=dlg:var:checklin:state
    sol:=dlg:var:checksol:state
 
    for n:=1 to len(arr)
        kat:=arr[n][PKG_CAT] 
        dx:=ascan(dir,{|d|d[F_NAME]==arr[n][PKG_ZIP]})
        if( dx>0 )
            arr[n][PKG_CLN]:=datetime(dir[dx])
            arr[n][PKG_SEL]:=platform_select(kat,win,lin,sol) .and.; 
                                      (arr[n][PKG_CLN]<arr[n][PKG_SRV]) 
        else
            arr[n][PKG_CLN]:=s_notexist 
            arr[n][PKG_SEL]:=platform_select(kat,win,lin,sol)
        end
    next
    
    dlg:var:browse:pagereload
    
    return NIL


******************************************************************************
static function platform_select(kat,win,lin,sol)
    if( kat=="W" )
        return win
    elseif( kat=="L" )
        return lin
    elseif( kat=="S" )
        return sol
    elseif( kat=="U" )
        return lin.or.sol
    elseif( kat=="C" )
        return win.or.lin.or.sol
    end
    return .f.


******************************************************************************
static function platform_name(brw)

local arr:=brw:array
local pos:=brw:arraypos
local kat:=arr[pos][1]

    if( kat=="U" )
        return "UNIX"
    elseif( kat=="L" )
        return "Linux"
    elseif( kat=="S" )
        return "Solaris"
    elseif( kat=="W" )
        return "Windows"
    elseif( kat=="C" )
        return "Közös"
    end
    return kat


******************************************************************************
static function datetime(diritem)
    return dtoc(diritem[F_DATE])+" "+diritem[F_TIME] 

static function getdate(dt)
    return ctod( left(dt,10) ) 

static function gettime(dt)
    return right(dt,8) 

******************************************************************************
static function download(dlg)

local arr:=dlg:var:browse:array, n
local termdir:=dlg:var:labeldir:text
local servdir:=s_zipdir
local total:=0, ready:=0
local zipname, zipdate, ziptime

    if( empty(termdir) )
        alert("Nincs kijelölve a letöltés helye!")
        return NIL
    end

    for n:=1 to len(arr)
        if( arr[n][PKG_SEL]  )
            total+=arr[n][PKG_SIZ] 
        end
    next

    for n:=1 to len(arr)
        if( arr[n][PKG_SEL] .and. arr[n][PKG_SIZ]>0   )
            ready+=arr[n][PKG_SIZ] 

            zipname:=arr[n][PKG_ZIP] 
            zipdate:=getdate(arr[n][PKG_SRV])
            ziptime:=gettime(arr[n][PKG_SRV])
     
            dlg:var:progbar:setbar(ready/total*99,zipname) 

            jtdownload( servdir+dirsep()+zipname,;
                        termdir+dirsep()+zipname, zipdate, ziptime )

            arr[n][PKG_SEL]:=.f.
        end
    next

    dlg:var:progbar:setbar(100,"") 
    reload(dlg)
 
    return NIL

******************************************************************************
