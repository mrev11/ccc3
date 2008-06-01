
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

#include "inkey.ch"

static clid_zedit:=zeditRegister()

****************************************************************************
function zeditClass() 
    return clid_zedit

****************************************************************************
static function zeditRegister() 
local clid:=classRegister("zedit",objectClass()) //osztalynev,parentID
    
    classMethod(clid,"initialize",{|this,txt,t,l,b,r|zeditIni(this,txt,t,l,b,r)})

    classMethod(clid,"actrow",{|t|1+t:sftrow+t:winrow})  //kurzor sor    : 1, ..
    classMethod(clid,"actcol",{|t|1+t:sftcol+t:wincol})  //kurzor oszlop : 1, ...

    classMethod(clid,"height",{|t|t:bottom-t:top+1})     //ablak magassag
    classMethod(clid,"width",{|t|t:right-t:left+1})      //ablak szelesseg

    classMethod(clid,"scroll",{|t,n|scroll(t:top,t:left,t:bottom,t:right,n)})  

    classMethod(clid,"loop",{|t|_zedit_loop(t)}) 
    classMethod(clid,"display",{|t|_zedit_display(t)}) 
    classMethod(clid,"displine",{|t,x|_zedit_displine(t,x)}) 

    classMethod(clid,"down",{|t|_zedit_down(t)})  
    classMethod(clid,"up",{|t|_zedit_up(t)})  
    classMethod(clid,"pagedown",{|t|_zedit_pagedown(t)})  
    classMethod(clid,"pageup",{|t|_zedit_pageup(t)})  
    classMethod(clid,"ctrlpgdn",{|t|_zedit_ctrlpgdn(t)})  
    classMethod(clid,"ctrlpgup",{|t|_zedit_ctrlpgup(t)})  
    classMethod(clid,"moveright",{|t|_zedit_right(t)})  
    classMethod(clid,"moveleft",{|t|_zedit_left(t)})  
    classMethod(clid,"home",{|t|_zedit_home(t)})  
    classMethod(clid,"end",{|t|_zedit_end(t)})  

    classMethod(clid,"delete",{|t|_zedit_delete(t)})  
    classMethod(clid,"backspace",{|t|_zedit_backspace(t)})  
    classMethod(clid,"delline",{|t|_zedit_delline(t)})  
    classMethod(clid,"enter",{|t|_zedit_enter(t)})  
    classMethod(clid,"tab",{|t|_zedit_tab(t)})  
    classMethod(clid,"inschar",{|t,k|_zedit_inschar(t,k)})  

    classMethod(clid,"markright",{|t|_zedit_mright(t)})  
    classMethod(clid,"markleft",{|t|_zedit_mleft(t)})  
    classMethod(clid,"markend",{|t|_zedit_mend(t)})  
    classMethod(clid,"markhome",{|t|_zedit_mhome(t)})  
    classMethod(clid,"markdown",{|t|_zedit_mdown(t)})  
    classMethod(clid,"markup",{|t|_zedit_mup(t)})  
    classMethod(clid,"markpgdn",{|t|_zedit_mpagedn(t)})  
    classMethod(clid,"markpgup",{|t|_zedit_mpageup(t)})  

    classMethod(clid,"cut",{|t,dsp|_zedit_cut(t,dsp)})  
    classMethod(clid,"copy",{|t|_zedit_copy(t)})  
    classMethod(clid,"paste",{|t|_zedit_paste(t)})  
    classMethod(clid,"markedstring",{|t|_zedit_markedstring(t)})  
 
    classMethod(clid,"gettext",{|t|_zedit_gettext(t)}) 

    classMethod(clid,"toupper",{|t|_zedit_chcase(t,.t.)}) 
    classMethod(clid,"tolower",{|t|_zedit_chcase(t,.f.)}) 
 
    classMethod(clid,"search",{|t,m|_zedit_search(t,m)}) 
    classMethod(clid,"replace",{|t,m|_zedit_replace(t,m)}) 
    classMethod(clid,"searchagain",{|t,m|_zedit_sagain(t,m)}) 
    classMethod(clid,"replaceagain",{|t,m|_zedit_ragain(t,m)}) 
    classMethod(clid,"clipboard",{|t,c|_zedit_clipboard(t,c)})  
 
    classMethod(clid,"setpos",{|t,r,c|_zedit_setpos(t,r,c)}) 

    classAttrib(clid,"atxt")     //sorokra bontott szoveg

    classAttrib(clid,"top")      //0,...
    classAttrib(clid,"left")     //0,...
    classAttrib(clid,"bottom")   //,,,.maxrow()
    classAttrib(clid,"right")    //,,,.maxcol()
    classAttrib(clid,"modflg")   //.t. lehet modositani
    classAttrib(clid,"changed")  //modositas tortent
    classAttrib(clid,"usrfnc")
    classAttrib(clid,"tabsiz")   //4
    classAttrib(clid,"winrow")   //window sor        : 0, ...
    classAttrib(clid,"wincol")   //window oszlop     : 0, ...
    classAttrib(clid,"sftrow")   //ablaktolas sor    : 0, ...
    classAttrib(clid,"sftcol")   //ablaktolas oszlop : 0, ...

    classAttrib(clid,"markflg")  //.f. kijeloles nem aktiv
    classAttrib(clid,"markmode") //CONT/RECT
    classAttrib(clid,"markrow")  //kijeloles kezdete : 1, ...
    classAttrib(clid,"markcol")  //kijeloles kezdete : 1, ...
                                     
    classAttrib(clid,"clipfile") //clipboard file
                
    classAttrib(clid,"searchstring")
    classAttrib(clid,"replacestring")
    classAttrib(clid,"casesensitive")
 
    classAttrib(clid,"headerblk")
    classAttrib(clid,"keymapblk")

    classAttrib(clid,"savedtext")
    classAttrib(clid,"saveblk")
    classMethod(clid,"save",{|t|if(t:saveblk!=NIL,eval(t:saveblk,t),.t.)})

    classAttrib(clid,"diffblk")
    classMethod(clid,"diff",{|t|if(t:diffblk!=NIL,eval(t:diffblk,t),.t.)})

    return clid


****************************************************************************
function zeditNew(txt,t,l,b,r) 
local clid:=zeditClass()
    return objectNew(clid):initialize(txt,t,l,b,r)


****************************************************************************
function zeditIni(this,txt,t,l,b,r) 
local n

    objectIni(this)

    //minden adattagot inicializalni kell!
    
    if( txt==NIL )  //2000.06.21
        txt:=""
    end

    this:savedtext:=txt

    this:top     := if(t==NIL,0,t)
    this:left    := if(l==NIL,0,l)
    this:bottom  := if(b==NIL,maxrow(),b)
    this:right   := if(r==NIL,maxcol(),r)

    this:winrow  := 0
    this:wincol  := 0
    this:sftrow  := 0
    this:sftcol  := 0

    this:markflg := .f.
    this:markmode:= "CONT"
    this:markrow := 0
    this:markcol := 0
    this:tabsiz  := 4

    this:modflg  := .t.
    this:changed := .f.
 
    this:replacestring:=""
    this:searchstring:=""
    this:casesensitive:=.t.
 
    this:clipfile:="clipfile" //felhasznalo beallitja

    this:usrfnc:=NIL //?
    this:headerblk:={|this|NIL}
    this:keymapblk:={|key|key}


    if( empty(this:atxt:=lines(txt)) )
        this:atxt:={""}
    end

    for n:=1 to len(this:atxt)
        this:atxt[n]:=strtran(this:atxt[n],chr(13),"")
        //this:atxt[n]:=strtran(this:atxt[n],chr(9),space(this:tabsiz))
        this:atxt[n]:=detab(this:atxt[n],2*this:tabsiz)
    next
    
    return this

**************************************************************************** 
static function detab(x,ts)
local n,tp
    while( 0<(n:=at(chr(9),x)) )
        tp:=n%ts
        if( tp==0 )
            tp:=ts
        end
        tp:=ts-tp+1
        x:=stuff(x,n,1,space(tp))
    end
    return x

**************************************************************************** 
static function lines(txt)

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            exit
        end
    end

    return asize(a,i)

**************************************************************************** 

