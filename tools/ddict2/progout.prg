
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

#include "table.ch"
#include "_ddict.ch"

****************************************************************************
#define UNDERSCORE  underscore()

function underscore(x)
static us:=""
    if( x!=NIL )
        us:=x
    end
    return us

****************************************************************************
function superlist(x)
static sx:=.t.
    if( x!=NIL )
        sx:=x
    end
    return sx

****************************************************************************
//* PROGRAMKIMENET előállítása

****************************************************************************
function progOutPut(browse,mode,nspace)
local tab, msg
local pos:=DDICT:position
local lsuper:={}, xsup:=0, xtab:=0
local super:="", nsuper:="", byname:="", rmk:="", lib:="", wmk:=""
local crlf0:=chr(13)+chr(10)
local crlf4:=chr(13)+chr(10)+replicate(" ",4)

  //  super: _super.prg
  //  wmk  : datadict.wmk   // új prg-k fordításához (wmake)
  //  rmk  : datadict.rmk   // új prg-k fordításához (rmake)
  //  lib  : datadict.rsp   // datadict.lib feltöltéséhez


    super:=crlf0+"function "+nspace+"tabSuperList()"
    super+=crlf0+"local supList:={}"
    nsuper:=crlf0+"function "+nspace+"tabNameList()"
    nsuper+=crlf0+"local nameList:={}"
    rmk:=".prg.obj:"
    rmk+=crlf4+"clipper $* /w/n/m/es2 >>clpout"
    rmk+=crlf4+"lib "+ddictName()+" -+$*"+".obj;"
    rmk+=crlf0
    wmk+="!include $(%cccdir)\usr\wmkrules\rules.wmk"
    wmk+=crlf0+crlf0+"lib_"+ddictName()+" ="
    lib:=ddictName()+" &" //1995.09.09 az első obj-ot nem rakta be a lib-be

    DDICT:gotop
    while( !DDICT:eof )
    
        msg:=message(msg,"Program output: "+DDICT_TABLE)
        
        xtab++
        if( (xtab%100)==0 )
            xsup++
            super+=crlf4+"return "+nspace+"tabSuper"+alltrim(str(xsup))+"(supList)"
            super+=crlf0
            aadd(lsuper,super)
            super:=crlf0+"function "+nspace+"tabSuper"+alltrim(str(xsup))+"(supList)"
        end

        super+=crlf4+"aadd(supList,{||"+UNDERSCORE+alltrim(DDICT_TABLE)+"()})"
        nsuper+=crlf4+'aadd(nameList,"'+alltrim(DDICT_TABLE)+'")'
        rmk+=crlf0+"_"+alltrim(DDICT_TABLE)+".obj: "+"_"+alltrim(DDICT_TABLE)+".prg"
        wmk+=" &"+crlf0+"_"+alltrim(DDICT_TABLE)+".obj"
        lib+=crlf0+"+"+"_"+alltrim(DDICT_TABLE)+".obj &"
        
        tab:=DDICT_TABLE
        progTable(mode)

        while( !DDICT:eof .and. tab==DDICT_TABLE )
            DDICT:skip
        end
    end

    super+=crlf4+"return supList"
    aadd(lsuper,super+crlf0)

    nsuper+=crlf4+"return nameList"
    aadd(lsuper,nsuper+crlf0)

    byname+=crlf0+"function "+nspace+"tabByName(t)"
    byname+=crlf0+"local n:=ascan("+nspace+"tabNameList(),{|s|s==upper(alltrim(t))})"
    byname+=crlf4+"return if(n>0,eval("+nspace+"tabSuperList()[n]),NIL)"
    aadd(lsuper,byname+crlf0)

    if( superlist() )
        for xsup:=1 to len(lsuper)
            progWrite("_super"+padl(alltrim(str(xsup)),2,"0")+".prg",lsuper[xsup])
        next
    else
        for xsup:=1 to len(lsuper)
            ferase(ddictPath()+"_super"+padl(alltrim(str(xsup)),2,"0")+".prg")
        next
        lsuper:={}
    end

    ********************************

    for xsup:=1 to len(lsuper)
        rmk+=crlf0+"_super"+padl(alltrim(str(xsup)),2,"0")+".obj: "+;
                   "_super"+padl(alltrim(str(xsup)),2,"0")+".prg"
    next
    //progWrite( ddictName()+".rmk", rmk+crlf0) //99/07.27

    ********************************

    for xsup:=1 to len(lsuper)
        wmk+=" &"+crlf0+"_super"+padl(alltrim(str(xsup)),2,"0")+".obj"
    next
    wmk+=crlf0
    wmk+=crlf0+ddictName()+".lib : "+ddictName()+".log $(lib_"+ddictName()+")"+crlf0
    wmk+=crlf0+ddictName()+".log :"
    wmk+=crlf4+"echo $(EXETYPE) >"+ddictName()+".log"+crlf0
    //progWrite( ddictName()+".wmk", wmk+crlf0) //99/07.27

    ********************************

    for xsup:=1 to len(lsuper)
        lib+=crlf0+"+_super"+padl(alltrim(str(xsup)),2,"0")+".obj &"
    next
    lib+=crlf0+";"
    //progWrite( ddictName()+".rsp", lib+crlf0) //99.07.27

    ********************************

  //  set console on
  //  set printer to
  //  set printer off

    message(msg)
    DDICT:goto(pos)
    browse:refreshAll()
    keyboard("")
    return NIL


****************************************************************************
static function progTable(mode)

local tab:=alltrim(DDICT_TABLE)
local ver:=DDICT_VERSION
local struct:=ctoa(dbstruct())

local prg:="", ind:=""
local name, type, width, dec, fldnum, indcol, n
local ualias:=upper(tab)
local lalias:=lower(tab)
local crlf0:=chr(13)+chr(10)
local crlf4:=chr(13)+chr(10)+replicate(" ",4)
local crlf8:=chr(13)+chr(10)+replicate(" ",8)
local dir:=alltrim(DDICT_DIRECTORY)
local memofield:={}, dbmname

    prg:="function "+UNDERSCORE+tab+"(col,exp)"
    prg+=crlf0+"static dbf"
    prg+=crlf4+"if(empty(dbf))"
    prg+=crlf8+'dbf:=tabNew("'+tab+'")'

    if( !empty(dir) )
        if( right(dir,1)!="\" )    //kompatibilitás!
            dir+="\"               //kompatibilitás! 
        end
        prg+=crlf8+'tabPath(dbf,"'+dir+'")'
    end

    for n:=1 to len(struct)
        name:=struct[n][1]
        name :=padr('"'+name+'"',max(10,len(name))+2)
        type :='"'+struct[n][2]+'"'
        width:=str(struct[n][3],3)
        dec  :=str(struct[n][4],2)
        prg+=crlf8+"tabAddColumn(dbf,{"+name+","+type+","+width+","+dec+"})"
        

        name :=struct[n][1]
        type :=struct[n][2]
        width:=struct[n][3]
       
        if( type=="M" .or. type=="C".and.width==10.and.left(name,3)=="DBM" )
            aadd(memofield,name)
        end
    next
    

    while( !DDICT:eof .and. alltrim(DDICT_TABLE)==tab .and. ver==DDICT_VERSION )

        if( !DDICT:rlock({||.f.}) ) //státusz beírás
            DDICT:skip  //kihagyja
            loop
        end

        indcol:=split(DDICT_INDFIELD)
        
        if( empty(DDICT_INDNAME) )
            // nincs index, OK

        elseif( empty(DDICT_INDFILE) )
            DDICT_STATE:="F"  // van index, de nincs indexfájl -- hibás

        elseif( len(indcol)<1 )
            DDICT_STATE:="O"  // van index, de nincs egy oszlop sem -- hibás
         
        else
            // még ellenőrízni kell, hogy az indexben
            // szereplő oszlopok léteznek-e

            ind:='{'
            ind+='"'+alltrim(DDICT_INDNAME)+'","'+alltrim(DDICT_INDFILE)+'"'
            ind+=',{'
            
            for n:=1 to len(indcol)
                 if( colExist(struct,indcol[n]) )
                     if( n>1 )
                         ind+=","
                     end
                     ind+='"'+upper(alltrim(indcol[n]))+'"'
                 else
                     DDICT_STATE:=alltrim(str(n))
                 end
            next
     
            ind+='}}'
            prg+=crlf8+"tabAddIndex(dbf,"+ind+")"
        end
        
        DDICT:unlock
        DDICT:skip
    end

    prg+=crlf4+"end"
    prg+=crlf4+"if(col==NIL)"
    prg+=crlf8+"return dbf"
    prg+=crlf4+"end"
    prg+=crlf4+"return tabEvalColumn(dbf,col,exp)"
    prg+=crlf0

#ifdef NOT_DEFINED //elavult    
    if( !empty(memofield) )
        prg+=crlf0
        prg+="#ifdef _cl_"
       
        for n:=1 to len(memofield)
            name:=memofield[n]
            dbmname:=name
            if( left(name,3)=="DBM" )
                name:=substr(name,4)
            end
            prg+=crlf0+"function _"+tab+"_"+name+"(exp)"
            prg+=crlf0+"static col"
            prg+=crlf4+"if(col==NIL)"
            prg+=crlf8+'col:=tabColNumber('+UNDERSCORE+tab+'(),"'+dbmname+'")'
            prg+=crlf4+"end"
            prg+=crlf4+"return "+UNDERSCORE+tab+"(col,exp)"
            prg+=crlf0
        next
        prg+="#endif"
        prg+=crlf0
    end
#endif

    prg+=crlf0
    progWrite("_"+tab+".prg", prg)

    prg:=crlf0+"#define "+padr(ualias,len(ualias)+13)+"("+"TABLE:"+UNDERSCORE+lalias+")"

    if(mode=="->")
        //alias->field-re preprocesszál
        for n:=1 to len(struct)
            name:=struct[n][1]
            name:=padr(name,max(10,len(name))+2)
            prg+=crlf0+"#define "+ualias+"_"+name+lalias+"->"+lower(name)
        next

    elseif(mode=="::")
        //(FIELD:alias:count)-ra preprocesszál
        for n:=1 to len(struct)
            name:=struct[n][1]
            name:=padr(name,max(10,len(name))+2)
            fldnum:=alltrim(str(n,2))
            prg+=crlf0+"#define "+ualias+"_"+name+"(FIELD:"+UNDERSCORE+lalias+":"+fldnum+")"
        next

    elseif(mode=="##")

        prg+=crlf0+crlf0+"#ifdef ARROW"
        //alias->field-re preprocesszál
        for n:=1 to len(struct)
            name:=struct[n][1]
            name:=padr(name,max(10,len(name))+2)
            prg+=crlf0+"#define "+ualias+"_"+name+lalias+"->"+lower(name)
        next

        prg+=crlf0+"#else"
        //(FIELD:alias:count)-ra preprocesszál
        for n:=1 to len(struct)
            name:=struct[n][1]
            name:=padr(name,max(10,len(name))+2)
            fldnum:=alltrim(str(n,2))
            prg+=crlf0+"#define "+ualias+"_"+name+"(FIELD:"+UNDERSCORE+lalias+":"+fldnum+")"
        next

        prg+=crlf0+"#endif"
        prg+=crlf0
    end

#ifdef NOT_DEFINED //elavult    
    if( mode$";->;##;" .and. !empty(memofield) )
        prg+=crlf0
        prg+=crlf0+"#ifdef _cl_"
        for n:=1 to len(memofield)
            name:=memofield[n]
            dbmname:=padr(name,max(10,len(name))+2)
            if( left(name,3)=="DBM" )
                name:=substr(name,4)
            end
            prg+=crlf0+"#undef  "+ualias+"_"+dbmname
            prg+=crlf0+"#define "+ualias+"_"+dbmname+"(MEMO:_"+ualias+"_"+name+")"
        next
        prg+=crlf0+"#endif"
        prg+=crlf0
    end
#endif    
    
    prg+=crlf0
    progWrite("_"+tab+".ch", prg)

    return NIL


*******************************************************************************
static function progWrite(file,txt) // kiírja text-et, ha megváltozott
    file:=lower(file) //99.07.27

    txt+=chr(26) //EOF

    if( !(memoread(ddictPath()+file)==txt) )
        if(!memowrit(ddictPath()+file,txt))
            alert(file+" not writable!")
        end
    end
    return NIL


*******************************************************************************
static function colExist(struct,col) // ellenőrzi egy mező létezését
    return 0<ascan(struct,{|c|alltrim(c[1])==alltrim(col)})


*******************************************************************************
