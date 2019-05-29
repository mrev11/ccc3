
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

#define VERSION "1.1.0"  //2019-05-29 #define-okat képez az id-kbol
//#define VERSION "1.0.3"  //2017-03-18 fieldsetek alja kicsit lejjebb
//#define VERSION "1.0.2"  //id-vel rendelkező labelek default szövege javítva
//#define VERSION "1.0.1"


#define MAXROW         f_maxrow()
#define MAXCOL         f_maxcol()
#define SCREENSIZE     f_screensize()


#define NORMAL     7
#define INVERS   112

#define attr(n)  asc(substr(linea,n,1))
#define char(n)  substr(linec,n,1)
#define char2(n) substr(linec,n-1,2)
#define STR(n)   alltrim(str(n))

// text             (normal  -> label)
// get              (inverse -> input:text)
// <push> text      (inverse -> input:button)
// (radio) text     (inverse -> input:radio)
// [check] text     (inverse -> input:checkbox)
// {select}         (inverse -> select)
// |panel|          (inverse -> div)
// *passw           (inverse -> input:password)

// --|fs|Legend--   (szimpla keret -> fieldset)

// #table           (inverse -> div)
// ^tabpane         (inverse -> div)
// !progbar         (inverse -> div)
// ?tree            (inverse -> div)
// @label           (inverse -> div)
// &htmlarea        (inverse -> div)
// +textarea        (inverse -> div)
// %slider          (inverse -> div)


static extension:=".html"


static size80x25:={80,25}
static size100x50:={100,50}
static size120x60:={120,60}
static size160x60:={160,60}
static size200x60:={200,60}
static termsize:=size80x25
#define CALCSIZE(t)  (t[1]*t[2]*4)


static tabindex:=simplehashNew()


*************************************************************************
static function termsetup()
    f_maxcol(termsize[1]-1)
    f_maxrow(termsize[2]-1)
    f_screensize(CALCSIZE(termsize))

*************************************************************************
static function f_maxrow(s)
static x:=24
    if( s!=NIL )
        x:=s
    end
    return x

static function f_maxcol(s)
static x:=79
    if( s!=NIL )
        x:=s
    end
    return x

static function f_screensize(s)
static x:=8000
    if( s!=NIL )
        x:=s
    end
    return x


*****************************************************************************
function main(msk)

local n
local screen, input, output
local path, prgcode

    ?? "msk2html",VERSION,"(C) ComFirm 2012"

    if( msk==NIL )
        ? "Usage: msk2html <mskfile>"
        quit
    end

    if( fext(msk)=="." )
        msk+=".msk"
    end

    if( empty(path:=fpath(msk)) )
        path:=""
    else
        path+=dirsep()
    end

    if( !file(msk) )
        ? "File not found:", msk
        quit
    end
    
    init_tabindex(msk)

    ?  "  in:", input:=msk
    ?? "  out:", output:=path+fname(msk)+extension


    screen:=memoread(input,.t.)
    if( len(screen)==CALCSIZE(size80x25) )
        termsize:=size80x25
    elseif( len(screen)==CALCSIZE(size100x50) )
        termsize:=size100x50
    elseif( len(screen)==CALCSIZE(size120x60) )
        termsize:=size120x60
    elseif( len(screen)==CALCSIZE(size160x60) )
        termsize:=size160x60
    elseif( len(screen)==CALCSIZE(size200x60) )
        termsize:=size200x60
    else
        ? "Incompatible screen size",len(screen)
        ?
        quit
    end
    termsetup()


    prgcode:=prgoutput(fname(msk), screen)
    prgcode:="//msk2html "+VERSION+chr(10)+chr(10)+prgcode

    if( prgcode==memoread(output) )
        memowrit(output,prgcode)
        ?? " not changed"
    else
        memowrit(output,prgcode)
        ?? " written"
    end

    ?


*****************************************************************************
static function parsescreen(screen)

local list:={}
local i, line, linec, linea
local n,cbeg,c


    //fieldset (doboz) komponensek

    for i:=0 to MAXROW

        cbeg:=NIL

        line:=substr(screen,4*i*(MAXCOL+1)+1,4*(MAXCOL+1))
        linec:=screenchar(line)
        linea:=screenattr(line)

        for n:=1 to MAXCOL+2
        
            if( cbeg==NIL )
                if( char(n)$(B_VS+B_SS1+B_SS7) )
                    cbeg:=n // komponens kezdődik
                end

            else
                if( char(n)$(B_VS+B_SS3+B_SS9) .or. n==MAXCOL+2 )
                    c:=fieldset(substr(linec,cbeg,n-cbeg),i,cbeg)

                    if( !empty(c:type) )
                        aadd(list,c)
                    else
                        concat(list,c)
                    end

                    cbeg:=NIL // komponenes vége
                end
            end
        next
    next


    //inverz komponensek

    for i:=0 to MAXROW

        cbeg:=NIL

        line:=substr(screen,4*i*(MAXCOL+1)+1,4*(MAXCOL+1))
        linec:=screenchar(line)
        linea:=screenattr(line)

        for n:=1 to MAXCOL+2
        
            if( cbeg==NIL )
                if( attr(n)==INVERS )
                    cbeg:=n // komponens kezdődik
                end

            else
                if( attr(n)==NORMAL .or. n==MAXCOL+2 )
                    c:=component(substr(linec,cbeg,n-cbeg),i,cbeg)
                    //c:list

                    if( !empty(c:type) )
                        aadd(list,c)
                    else
                        concat(list,c)
                    end

                    cbeg:=NIL // komponenes vége
                end
            end
        next
    next


    //síma labelek

    for i:=0 to MAXROW

        cbeg:=NIL

        line:=substr(screen,4*i*(MAXCOL+1)+1,4*(MAXCOL+1))
        linec:=box2chr(screenchar(line),B_VS)
        linea:=screenattr(line)

        for n:=1 to MAXCOL+2
        
            if( cbeg==NIL )
                if( attr(n)==NORMAL .and. !empty(char(n)) .and. char(n)!=B_VS )
                    cbeg:=n // label kezdődik
                end
            else
                if( attr(n)==INVERS .or. empty(char2(n)) .or. char(n)==B_VS .or. n==MAXCOL+2  )
                    c:=label(substr(linec,cbeg,n-cbeg),i,cbeg)
                    aadd(list,c)
                    cbeg:=NIL // label vége
                end
            end
        next
    next


    for n:=1 to len(list)
        list[n]:setloc
    next

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
static function fieldset(str,row,col)

local c:=componentNew()
local title

    c:top:=row
    c:left:=col
    c:bottom:=row
    c:right:=col+len(str)

    if( str[1]==B_SS7 )
        c:type:="fieldset"
        str::=strtran(B_SS7," ")
        str::=strtran(B_HS," ")
        str::=strtran(B_SS9," ")
        title:=str::split("|")
        
        if( len(title)==1 ) //--Legend--
            if( !title[1]::empty  )
                c:text:=title[1]::alltrim
            end
        elseif( len(title)==3 ) // ---|id|-legend---
            c:name:=title[2]::alltrim
            if( !title[3]::empty  )
                c:text:=title[3]::alltrim
            end
        end
    end

    maxrect(c)

    return c


*****************************************************************************
static function maxrect(c)

static rect:={MAXROW,MAXCOL,0,0} //{top,left,bottom,right}

    if( c!=NIL )
        rect[1]:=max(0,min(rect[1],c:top))
        rect[2]:=max(0,min(rect[2],c:left))
        rect[3]:=max(rect[3],c:bottom)
        rect[4]:=max(rect[4],c:right)
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
        type:="select"
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
        if( (p:=at(" ",s))==0 )
            //@name
            name:=substr(s,2)
        else
            //@name text
            name:=substr(s,2,p-2)
            text:=alltrim(substr(s,p+1))
        end

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
static class component(object)

    attrib  type
    attrib  name
    attrib  text
    attrib  forid
    attrib  top
    attrib  left
    attrib  bottom
    attrib  right

    attrib  fieldset

    method  setloc

static function component.setloc(t)
local r:=maxrect()
    t:top    -= (r[1]-1)
    t:left   -= (r[2]-1)
    t:bottom -= (r[1]-1)
    t:right  -= (r[2]-1)


*****************************************************************************
//generating output
*****************************************************************************

#define EOL   endofline()
#define RECT  STR(t)+","+STR(l)+","+STR(b)+","+STR(r)


*****************************************************************************
static function prgoutput(clsname,screen)

local template:=<<TEMPLATE>>
static function xhtmlpage.CLSNAME()
static page:=<<PAGE>>
%CONTENT%
<<PAGE>>
    return page

static function xhtmldom.CLSNAME(legtxt)
local prs:=xmlparser2New(),dom,leg
    prs:createnodeblock:={|type|xhtmlnode.createnode(type)}
    dom:=prs:parsestring(xhtmlpage.CLSNAME())
    leg:=dom:content[1]
    if( legtxt!=NIL )
        leg:addtext(legtxt)
    else
        leg:setstyle("display:none")
    end
    return dom //fieldset
<<TEMPLATE>>


local list:=parsescreen(screen),n
local comp,node,lab
local box,legend
local fieldset:={},fs,i,vc,hc
local table

    template::=strtran("CLSNAME",clsname)


    box:=xhtmlnodeNew("fieldset")
    box:addcontent(xhtmlnodeNew("legend"))
    

    comp:=componentNew()
    comp:top     :=0
    comp:left    :=0
    comp:bottom  :=maxrect()[3]-maxrect()[1]+2
    comp:right   :=maxrect()[4]-maxrect()[2]+1
    
    if( !empty(getenv("MINWIDTH")) )
        ?? " (width:"+comp:right::str::alltrim+")"
        comp:right::=max( getenv("MINWIDTH")::val  )
    end

    setnodeposition(box,comp)
    box:setstyle("position:relative")
    //box:setstyle("border:0px") //elfedné a css-t!


    //először a fieldsetek
    for n:=1 to len(list)
        comp:=list[n]  
        if( comp:type=="fieldset" )
            node:=xhtmlnodeNew("fieldset")
            if( !empty(comp:name) )
                node:setattrib(xhtmlnode.attrib("id",comp:name))
            end
            legend:=xhtmlnodeNew("legend")
            node:addcontent(legend)
            if( !empty(comp:text) )
                legend:addtext(comp:text)
            else
                legend:setstyle("display:none")
            end
            setnodeposition(node,comp)
            box:addcontent(node)

            comp:fieldset:=node  //fieldsethez tartozó xhtmlnode megjegyezve
            aadd(fieldset,comp)  //fieldsetek gyűjtve későbbi felhasználáshoz
        end
    next


    for n:=1 to len(list)
    
        comp:=list[n]

        node:=xhtmlnodeNew()

        if( comp:type=="label" )
            node:type:="label"
            node:addtext(comp:text)
            if( comp:forid!=NIL )
                node:addattrib(xhtmlnode.attrib("for",comp:forid))
            end


        elseif( comp:type=="get" )
            node:type:="input"
            node:addattrib(xhtmlnode.attrib("type","text")) 
        

        elseif( comp:type=="push" )
            node:type:="input"
            node:addattrib(xhtmlnode.attrib("type","button")) 
            node:addattrib(xhtmlnode.attrib("value",if(!empty(comp:text),comp:text,comp:name)))
            node:addattrib(xhtmlnode.attrib("onclick","XCODE.onclick_formdata(this.id)"))


        elseif( comp:type=="radio" )
            node:type:="input"
            node:addattrib(xhtmlnode.attrib("type","radio")) 
            node:addattrib(xhtmlnode.attrib("name",comp:name[1])) 

            if( !empty(comp:text) )
                lab:=componentNew()
                lab:type    :="label"
                lab:name    :=""
                lab:text    :=comp:text
                lab:forid   :=comp:name
                lab:top     :=comp:top
                lab:left    :=comp:left+3
                lab:bottom  :=comp:bottom
                lab:right   :=comp:right
                aadd(list,lab)
            end


        elseif( comp:type=="check" )
            node:type:="input"
            node:addattrib(xhtmlnode.attrib("type","checkbox")) 
            
            if( !empty(comp:text) )
                lab:=componentNew()
                lab:type    :="label"
                lab:name    :=""
                lab:text    :=comp:text
                lab:forid   :=comp:name
                lab:top     :=comp:top
                lab:left    :=comp:left+3
                lab:bottom  :=comp:bottom
                lab:right   :=comp:right
                aadd(list,lab)
            end


        elseif( comp:type=="select" )
            node:type:="select"


        elseif( comp:type=="passw" )
            node:type:="input"
            node:addattrib(xhtmlnode.attrib("type","password")) 


        elseif( comp:type=="textarea" )
            node:type:="textarea"
            node:setstyle("resize:none")


        //az alábbiakból egyelőre div
        elseif( comp:type=="panel" )
            node:type:="div"

        elseif( comp:type=="tabpane" )
            node:type:="div"

        elseif( comp:type=="table" )
            node:type:="div"
            node:setstyle("overflow:auto") //scrolloz
            node:setstyle("border:1px solid lightgrey") //lássuk hol van
            node:setstyle("background-color:white")
            node:addcontent(table:=xhtmltableNew(comp:name))
            if( !empty(comp:name)  )
                comp:name:="div-"+comp:name
            end

        elseif( comp:type=="progbar" )
            node:type:="div"

        elseif( comp:type=="slider" )
            node:type:="div"

        elseif( comp:type=="htmlarea" )
            node:type:="div"

        else
            loop //minden egyéb kihagyva
        end
        
        
        if( !empty(comp:name)  )
            node:addattrib(xhtmlnode.attrib("id",comp:name))
        end
        

        for i:=1 to len(fieldset)
            fs:=list[i]
            if( fs:top>comp:bottom )
                //kívül (esetleg címsor)
            elseif( fs:bottom<=comp:top )
                //kívül
            elseif( fs:left>=comp:right )
                //kívül
            elseif( fs:right<=comp:left )
                //kívül
            else
                //beleesik az fs fieldsetbe
                if( comp:top==fs:top )
                    //fs címsora (kihagy)
                else
                    //fs belseje
                    hc:=0.35
                    vc:=if(fs:text==NIL,0.3,0.1)
                    comp:top-=fs:top+vc
                    comp:left-=fs:left+hc
                    comp:bottom-=fs:top+vc
                    comp:right-=fs:left+hc
                    if( !comp:top==0 )
                        setnodeposition(node,comp)
                        fs:fieldset:addcontent(node)
                    end
                end
                exit
            end
        next

        if( i>len(fieldset) )
            //nincs egy fieldsetben sem
            setnodeposition(node,comp)
            box:addcontent(node)
        end
    next
    
    sort(box)
    
    template::=strtran("%CONTENT%",box:html())
    template:=mkdef(box,clsname)+template
    
    return template


*****************************************************************************
static function setnodeposition(node,comp)
    node:setstyle("position:absolute;")
if( !comp:type=="fieldset" )
    node:setstyle(vpos(comp))
    node:setstyle(hpos(comp))
    node:setstyle(vsiz(comp))
    node:setstyle(hsiz(comp))
else
    node:setstyle(fsvpos(comp))
    node:setstyle(fshpos(comp))
    node:setstyle(fsvsiz(comp))
    node:setstyle(fshsiz(comp))
end

#define HX   9
#define VX  24

static function vpos(comp)
local vcorr:=0
    if( comp:type=="label" )
        vcorr:=0.15 //labeleket egy kicsit lejjebb
    end
    return "top:"+((comp:top+vcorr)*VX)::int::str::alltrim+"px;"


static function hpos(comp)
    return "left:"+(comp:left*HX)::int::str::alltrim+"px;"


static function vsiz(comp)
    if( comp:top==comp:bottom  )
        return ""
    end
    return "height:"+( (1+comp:bottom-comp:top)*VX-2 )::int::str::alltrim+"px;"


static function hsiz(comp)
    if( comp:type=="check" .or. comp:type=="radio" )
        return ""
    end
    return "width:"+( (1+comp:right-comp:left)*HX-2 )::int::str::alltrim+"px;"



*****************************************************************************
static function fsvpos(comp)
local c:=if(comp:text==NIL,0.3,0.1)
    return "top:"+(     (comp:top+c)*VX                  )::int::str::alltrim+"px;"

static function fshpos(comp)
    return "left:"+(    (comp:left+0.15)*HX              )::int::str::alltrim+"px;"

static function fsvsiz(comp)
local c:=if(comp:text==NIL,0.35,0.25)
    return "height:"+(  (comp:bottom+0.2-comp:top-c)*VX  )::int::str::alltrim+"px;"

static function fshsiz(comp)
    return "width:"+(   (comp:right-comp:left-1.5)*HX    )::int::str::alltrim+"px;"

*****************************************************************************
static function mkdef(node,clsname)
local adef,n,define
    mkdef1(node,clsname,adef:={})
    define:=""
    for n:=1 to len(adef)
        define+=adef[n]+crlf()
    next
    return define
    

static function mkdef1(node,clsname,adef)
local n,ntype,type,id,define

    if( valtype(node)!="O" .or. !node:isderivedfrom(xhtmlnodeClass()) )
        return NIL
    end

    if( node:getattrib("id")!=NIL )
        ntype:=node:type
        type:=node:getattrib("type")
        id:=node:getattrib("id")

        define:="#define "+upper(clsname)
        if( !ntype=="input" )
            define+="_"+upper(ntype)
        end
        if( !type==NIL )
            define+="_"+upper(type)
        end
        define+="_"+upper(id)
        define::=strtran("-","_")
        define::=padr(48)
        define+='"'+id+'"'
        aadd(adef,define)
    end

    for n:=1 to len(node:content)
        mkdef1(node:content[n],clsname,adef)
    next

*****************************************************************************
static function sort(node)
    walk(node)

#ifdef NOTDEFINED
  A tabindexet a node-ok content-beli sorrendje határozza meg.
  Ez magától nem jó, mert a kódgenerálás a fieldseteket veszi előre.
  Így most a labelek is rendezve lesznek, korábban a végén voltak.
#endif


static function walk(node)
local n
    if( valtype(node)=="O" .and. node:isderivedfrom(xhtmlnodeClass()) )
        asort(node:content,,,{|x,y| cmpnodepos(x,y)} )
        for n:=1 to len(node:content)
            walk(node:content[n])
        next
    end


static function cmpnodepos(x,y)

local xp,yp
local xid,yid
local xtx,ytx

    //legend előre

    if( x:type=="legend" )
        return .t.
    end
    if( y:type=="legend" )
        return .f.
    end
    
    
    xid:=x:getattrib("id")
    yid:=y:getattrib("id")

    //elore, ha van id-je
    if( xid==NIL .and. yid!=NIL )
        return .f.

    elseif( xid!=NIL .and. yid==NIL )
        return .t.

    elseif( xid!=NIL .and. yid!=NIL )
        xtx:=tabindex[x:getattrib("id")]
        ytx:=tabindex[y:getattrib("id")]

        //elore, ha van indexe    
        if( xtx==NIL .and. ytx!=NIL )
            return .f.
        elseif( xtx!=NIL .and. ytx==NIL )
            return .t.
        elseif( xtx!=NIL .and. ytx!=NIL )
            return xtx<ytx
        end
    end
    
    //minden más felülről lefelé, balról jobbra

    xp:=x:getstyle("top"); xp:=if(xp==NIL,0,xp::val)
    yp:=y:getstyle("top"); yp:=if(yp==NIL,0,yp::val)
    
    if( xp!=yp )
        return xp<yp
    end

    xp:=x:getstyle("left"); xp:=if(xp==NIL,0,xp::val)
    yp:=y:getstyle("left"); yp:=if(yp==NIL,0,yp::val)

    return xp<=yp


*****************************************************************************
static function init_tabindex(msk)
local sor,n

    sor:=msk::strtran(".msk",".sor")    //a sor fajl neve
    sor::=memoread                      //a sor fajl tartalma
    sor::=strtran(","," ")              //, nelkul
    sor::=strtran(chr(10)," ")          //lf nelkul
    sor::=strtran(chr(13)," ")          //cr nelkul
    while("  "$sor)
        sor::=strtran("  "," ")
    end
    sor::=alltrim
    sor::=split(" ")                    //azonositok tombje
    
    for n:=1 to len(sor)
        tabindex[sor[n]]:=n
    next


*****************************************************************************

/* 
ezek vannak

        comp:type:="label"
        comp:type:="get"
        comp:type:="passw"
        comp:type:="check"
        comp:type:="radio"
        comp:type:="push"
        comp:type:="select"
        comp:type:="textarea"

ezekből div lesz

        comp:type:="panel"
        comp:type:="tabpane"
        comp:type:="table"
        comp:type:="progbar"
        comp:type:="slider"
        comp:type:="htmlarea"
*/
