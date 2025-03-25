
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

//#include "box.ch"

#define VERSION "1.0.00"    //nem lesz ez már jobb
//#define VERSION "0.9.01"  jtslider
//#define VERSION "0.9.00"  2006.08.31 áttérés a class szintaktikára
//#define VERSION "0.3.00"  unicode port
//#define VERSION "0.2.00"  2006.01.07 kulcsszavak kikerülve (class,new,method,attrib)
//#define VERSION "0.1.05"  2003.10.02 sorok vége javítva
//#define VERSION "0.1.04"  Build-be integrálva
//#define VERSION "0.1.03"  méretezés
//#define VERSION "0.1.02"  jttable alosztályai
//#define VERSION "0.1.01"  password mezők


#define MAXROW    24
#define MAXCOL    79


#define CHAR(n)         (substr(linec,n,1))
#define ATTR(n)         (substr(linea,n,1)::asc)  // fg
#define NORMAL          7   // white
#define INVERS          0   // black


#define STR(n)   alltrim(str(n))

// getfield (inverse)
// labelfield (normal)
// <push> text
// (radio) text
// [check] text
// {combo}
// |panel| text
// *passwfield (inverse)

// #table
// ^tabpane
// !progbar
// ?tree (később)
// @label (named)
// &html area
// +text area
// %slider

static baseclass:="jtdialog"
static addmethod:="add"
static extension:=".dlg"

static verbose:=.f.

*****************************************************************************
function main()

local msk, n
local screen, input, output
local path, prgcode

    for n:=1 to argc()-1

        if( argv(n)=="--jtdialog"  )
            baseclass:="jtdialog"
            addmethod:="add"
            extension:=".dlg"

        elseif( argv(n)=="--jtpanel"  )
            baseclass:="jtpanel"
            addmethod:="additem"
            extension:=".pnl"

        elseif( argv(n)=="--verbose"  )
            verbose:=.t.

        else
            msk:=argv(n)
        end
    next

    set dosconv off

    ?? "MSK2DLG",VERSION,"(C) ComFirm 2006"

    if( msk==NIL )
        ? "Usage: msk2dlg <mskfile>"
        quit
    end

    if( empty(filespec.extension(msk)) )
        msk+=".msk"
    end
    path:=filespec.path(msk)

    if( !file(msk) )
        ? "File not found:", msk
        quit
    end

    if( verbose )
        ? "  Input file  :", input:=msk
        ? "  Output file :", output:=path+filespec.name(msk)+extension

        screen:=readmask(input)
        prgcode:=prgoutput(filespec.name(msk),screen)
        prgcode:="//MSK2DLG "+VERSION+chr(10)+chr(10)+prgcode

        if( prgcode==memoread(output) )
            ?? " not changed"
        else
            memowrit(output,prgcode)
            ?? " written"
        end

    else
        input:=msk
        output:=path+filespec.name(msk)+extension

        screen:=readmask(input)
        prgcode:=prgoutput(filespec.name(msk), screen)
        prgcode:="//MSK2DLG "+VERSION+chr(10)+chr(10)+prgcode
        memowrit(output,prgcode)
    end
    ?
    return NIL

*****************************************************************************
static function parsescreen(screen)

local list:={}
local i, line, linec, linea
local n,cbeg,c

    //inverz komponensek

    for i:=0 to MAXROW

        cbeg:=NIL

        line:=substr(screen,4*i*(MAXCOL+1)+1,4*(MAXCOL+1))
        linec:=screenchar(line)
        linea:=screen_fg(line)

        for n:=1 to MAXCOL+2

            if( ATTR(N)==NORMAL .or. n==MAXCOL+2 )

                if( cbeg!=NIL )

                    c:=component(substr(linec,cbeg,n-cbeg),i,cbeg)

                    if( !empty(c:type) )
                        aadd(list,c)
                    else
                        concat(list,c)
                    end

                    cbeg:=NIL
                end

            elseif( ATTR(n)==INVERS )

                if( cbeg==NIL )
                    cbeg:=n
                end
            end
        next
    next


    //síma labelek

    for i:=0 to MAXROW

        cbeg:=NIL

        line:=substr(screen,4*i*(MAXCOL+1)+1,4*(MAXCOL+1))
        linec:=box2spc(screenchar(line))
        linea:=screen_fg(line)

        for n:=1 to MAXCOL+2

            if( ATTR(n)==NORMAL )

                if( cbeg==NIL .and. !CHAR(n)==" " )
                    cbeg:=n
                end

            elseif( ATTR(n)==INVERS .or. n==MAXCOL+2 )

                if( cbeg!=NIL )
                    c:=label(substr(linec,cbeg,n-cbeg),i,cbeg)
                    aadd(list,c)
                    cbeg:=NIL
                end
            end
        next
    next

    for n:=1 to len(list)
        list[n]:setloc
    next

    //for n:=1 to len(list)
    //    ? list[n]
    //next

    return list //komponensek listája


*****************************************************************************
static function label(str,row,col)
local c:=componentNew()

    c:type:="label"
    c:name:=""
    c:text:=alltrim(str)
    c:top:=row
    c:left:=col
    c:bottom:=row
    c:right:=col+len(c:text)-1

    maxrect(c)

    return c


*****************************************************************************
static function component(str,row,col)

local c:=componentNew()
local p:=parse(str)

    c:type:=p[1]
    c:name:=p[2]
    c:text:=p[3]
    c:top:=row
    c:left:=col
    c:bottom:=row
    c:right:=col+len(str)-1

    maxrect(c)

    return c


*****************************************************************************
static function maxrect(c)

static rect:={MAXROW,MAXCOL,0,0} //{top,left,bottom,right}

local addtop    := -1
local addleft   := -3
local addbottom :=  2
local addright  :=  3

    if( c!=NIL )

        if( c:type=="B" )
            addbottom:=2.5
        elseif( c:type=="T" )
            addbottom:=2.3
        elseif( c:type=="{" )
            addbottom:=2.3
        elseif( c:type=="[" )
            addbottom:=2.2
        elseif( c:type=="(" )
            addbottom:=2.2
        end

        rect[1]:=max(0,min(rect[1],c:top+addtop))
        rect[2]:=max(0,min(rect[2],c:left+addleft))
        rect[3]:=max(rect[3],c:bottom+addbottom)
        rect[4]:=max(rect[4],c:right+addright)

        //? padr(c:name,10), c:bottom, rect
    end

    return rect


*****************************************************************************
static function parse(s)   // "t name text" --> {type,name,text}

local type,name,text:=""
local t,p

    s:=alltrim(s)
    t:=left(s,1)

    if( t=="{" )
        p:=at("}",s)
        type:="combo"
        name:=substr(s,2,p-2)

    elseif( t=="[" )
        p:=at("]",s)
        type:="check"
        name:=substr(s,2,p-2)
        text:=alltrim(substr(s,p+1))

    elseif( t=="(" )
        p:=at(")",s)
        type:="radio"
        name:=substr(s,2,p-2)
        text:=alltrim(substr(s,p+1))

    elseif( t=="<" )
        p:=at(">",s)
        type:="push"
        name:=substr(s,2,p-2)
        text:=alltrim(substr(s,p+1))

    elseif( t=="|" )
        p:=rat("|",s)
        type:="panel"
        name:=substr(s,2,p-2)
        text:=alltrim(substr(s,p+1))

    elseif( t=="^" )
        type:="tabpane"
        name:=substr(s,2)

    elseif( t=="*" )
        type:="passw"
        name:=substr(s,2)

    elseif( t=="#" )
        type:="table"
        name:=substr(s,2)

    elseif( t=="@" )
        type:="label"
        name:=substr(s,2)

    elseif( t=="!" )
        type:="progbar"
        name:=substr(s,2)

    elseif( t=="+" )
        type:="textarea"
        name:=substr(s,2)

    elseif( t=="%" )
        type:="slider"
        name:=substr(s,2)

    elseif( t=="&" )
        type:="htmlarea"
        name:=substr(s,2)

    elseif( !empty(s) )
        type:="get"
        name:=s
    end

    return {type,name,text}



*****************************************************************************
static function concat(list,c)  //az üres c-vel bővít egy komponenst
local n,d
    for n:=1 to len(list)
        d:=list[n]
        if( d:left==c:left .and. d:right==c:right .and. d:bottom+1==c:top )
            d:bottom++
            maxrect(d)
            exit
        end
    next
    return NIL


*****************************************************************************
function componentClass()
static clid
    if( clid==NIL )
        clid:=classRegister("component",{objectClass()})
        classMethod(clid,"initialize",{|this|componentIni(this)})
        classMethod(clid,"setloc",{|t|setloc(t)} )

        classAttrib(clid,"type")
        classAttrib(clid,"name")
        classAttrib(clid,"text")
        classAttrib(clid,"top")
        classAttrib(clid,"left")
        classAttrib(clid,"bottom")
        classAttrib(clid,"right")
    end
    return clid


****************************************************************************
function componentNew()
local clid:=componentClass()
    return objectNew(clid):initialize()

****************************************************************************
function componentIni(this)
    return this

*****************************************************************************
static function setloc(t)
local r:=maxrect()
    t:top    -= r[1]
    t:left   -= r[2]
    t:bottom -= r[1]
    t:right  -= r[2]
    return NIL


*****************************************************************************
//generating output

#define EOL   endofline()
#define RECT  STR(t)+","+STR(l)+","+STR(b)+","+STR(r)

*****************************************************************************
static function prgoutput(clsname,screen)

local list:=parsescreen(screen)
local clstxt:="", inicode:=""
local n,t,l,b,r,nm,tx,cl


    //----------------------------------------------
    clstxt:="class "+clsname+"("+baseclass+")"+EOL
    clstxt+="    method initialize"+EOL
    for n:=1 to len(list)
        if( !empty(list[n]:name) )
            clstxt+="    attrib  "+list[n]:name+EOL
        end
    next

    //----------------------------------------------

    t:=maxrect()[1]
    l:=maxrect()[2]
    b:=maxrect()[3]
    r:=maxrect()[4]


    inicode:="static function "+clsname+".initialize(this)"+EOL
    inicode+="    this:("+baseclass+")initialize("+RECT+")"+EOL
    inicode+="    this:name:='"+clsname+"'"+EOL
    inicode+="    this:layout:='fix'"+EOL

    for n:=1 to len(list)

        t:=list[n]:top
        l:=list[n]:left
        b:=list[n]:bottom
        r:=list[n]:right

        nm:=list[n]:name
        tx:=list[n]:text

        if( empty(nm) )
            inicode+="    this:"+addmethod+"(jtlabelNew("+RECT+",'"+tx+"'))"+EOL

        elseif( list[n]:type=="label" )
            inicode+="    this:"+nm+":=jtlabelNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="progbar" )
            inicode+="    this:"+nm+":=jtprogbarNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="get" )
            inicode+="    this:"+nm+":=jtgetNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="push" )
            inicode+="    this:"+nm+":=jtpushNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+nm+":text:='"+tx+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="radio" )
            inicode+="    this:"+nm+":=jtradioNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+nm+":text:='"+tx+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="check" )
            inicode+="    this:"+nm+":=jtcheckNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+nm+":text:='"+tx+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="combo" )
            inicode+="    this:"+nm+":=jtcomboNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="passw" )
            inicode+="    this:"+nm+":=jtpasswNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="textarea" )
            inicode+="    this:"+nm+":=jttextareaNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="slider" )
            inicode+="    this:"+nm+":=jtsliderNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="htmlarea" )
            inicode+="    this:"+nm+":=jthtmlareaNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="table" )

            //a jttable leszármazott osztályaiból
            //választunk a név kezdőbetűje szerint

            if( left(nm,1)=="a" )
                cl:="jtbrowsearray"
            elseif( left(nm,1)=="t" )
                cl:="jtbrowsetable"
            elseif( left(nm,1)=="_" )
                cl:="jttable"+nm+"_"
                nm:=substr(nm,2)
            else
                cl:="jttable"
            end

            inicode+="    this:"+nm+":="+cl+"New("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="panel" )
            inicode+="    this:"+nm+":=jtpanelNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            if( !empty(tx) )
                inicode+="; this:"+nm+":text:='"+tx+"'"
            end
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL

        elseif( list[n]:type=="tabpane" )
            inicode+="    this:"+nm+":=jttabpaneNew("+RECT+")"
            inicode+="; this:"+nm+":name:='"+nm+"'"
            if( !empty(tx) )
                inicode+="; this:"+nm+":text:='"+tx+"'"
            end
            inicode+="; this:"+addmethod+"(this:"+nm+")"
            inicode+=EOL
        end
    next
    inicode+="    return this"+EOL

    return clstxt+EOL+EOL+inicode+EOL


*****************************************************************************
