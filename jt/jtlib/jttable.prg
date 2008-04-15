
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
#include "jtelem.ch"
 
#ifdef MEGJEGYZESEK

1. Hogyan működik a jttable objektum?

  A jttable NEM TARTALMAZ közvetlen MEGJELENÍTÉST VÉGZŐ KÓDOT,
  csak tárolja a megjelenítendő adatokat, és vezérli a terminált.

2. Hogyan kell felparaméterezni egy jttable objektumot?

  a) Öt kódblokkot kell beállítani:

    classAttrib(clid,"skipblock") 
    classAttrib(clid,"gotopblock") 
    classAttrib(clid,"gobottomblock") 
    classAttrib(clid,"saveposblock") 
    classAttrib(clid,"restposblock") 

  Az első három blokk szerepe ugyanaz, mint a Clipper tbrowse-ban.
  Az utolsó kettő összekapcsolja a terminálnak átadott lap sorindexeit
  az eredeti adatforrás soraival. 
 
  b) Oszlopokat kell hozzáadni browsehoz az addcolumn metódussal.
  Az oszlopok hozzáadásának ugyanaz a logikája, mint a tbrowse-hoz
  használt brwColumn függvénynek.

3. Hol van példa a navigáló kódblokkok beállítására?

  A jttable-nak van két közvetlen leszármazottja:
  
  jtbrowsearray : felkészítve array browseolására
  jtbrowsetable : felkészítve táblaobjektum browseolására
  
  Ezek a gyakorlatban előforduló esetek 90%-ában közvetlenül
  és egyszerűen alkalmazhatók, illetve ki lehet nézni belőlük
  a kódblokkok használatát (nem különösebben bonyolult).

4. Mi van a korábbi jtbrowse osztállyal?

  A jtbrowse osztály UGYANAZT tudja, mint a jttable, de mivel
  a Clipper tbrowse leszármazottja, lokálisan is meg lehet jeleníteni. 
  Előnye, hogy ugyanazzal a függvénykészlettel manipulálható,
  mint amit korábban használtunk: brwShow, brwLoop, brwHide, brwColumn, 
  brwArray, brwArrayPos, stb. Ugyanakkor ez nagy hátrány is,
  mivel feleslegesen belegyökerezik a régi könyvtárakba.
  
  Jelenleg a jtbrowse osztály státusza "compatibility", ami azt
  jelenti, hogy nincs befordítva a jtlib könyvtárba, hanem akinek
  éppen erre van szüksége, elviheti a forrását.
  
  A jtbrowse a jövőben nem lesz karbantartva, ezért ajánlatosabb
  a jttable, jtbrowsetable, jtbrowsearray osztályokra áttérni.

5. Van-e különség a különféle browseok megjelenítésében?

  Nincs. Minden browset ugyanaz a Jáva jttable osztály jelenít meg,
  ui. a szerver oldali browseok az üzenetek szintjén már egyformák.

#endif
 
****************************************************************************
class jttable(jtelem) 

    method  initialize

    attrib  skipblock
    attrib  gotopblock
    attrib  gobottomblock
    attrib  saveposblock
    attrib  restposblock
 
    attrib  column          //oszlopok listája
    attrib  maxrow          //max ennyi sor lehet
    attrib  row2pos         //a sorok pozíciói az adatforrásban

    attrib  colortable      //{{r,g,b},{255,0,0},...}
     
    method  savepos
    method  restpos

    method  colcount        {|this|len(this:column)}
    method  addcolumn
    method  getcolumn       {|this,n|this:column[n]}
 
    method  pageprev
    method  pagenext
    method  pagefirst
    method  pagelast
    method  pagereload
    method  pagecurrent
    method  pagerefresh
    method  rowrefresh
 
    method  rowcount        {|this|len(this:row2pos)}
    method  empty           {|this|empty(this:row2pos)}
    method  mktoolbar
        
    method  xmladd
    method  xmlput
    method  xmlget
    method  xmlpage
    method  xmlrow
 
    method  changed         {|this|!this:laststate==this:selectedindices} //oref!
    method  savestate       {|this|this:laststate:=this:selectedindices} //oref!
    method  varput          {|this,x|this:selectedindices:=x}
    method  varget          {|this|this:selectedindices}
 
    attrib  selectedindices

****************************************************************************
static function jttable.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:column:={}
    this:maxrow:=16
    this:row2pos:={}
    this:saveposblock:={||NIL}
    this:restposblock:={||.t.}
    return this
    

****************************************************************************
static function jttable.savepos(this,p) 
    this:row2pos[p]:=eval(this:saveposblock)
    return NIL
 

****************************************************************************
static function jttable.restpos(this,p) 
local x
    if( p>0 .and. len(this:row2pos)>=p .and. NIL!=(x:=this:row2pos[p]) )
        return eval(this:restposblock,x)
    end
    return .f.


****************************************************************************
static function jttable.addcolumn(this,h,b,p,w)
local c
    if( valtype(h)=="O" )
        c:=h
    else
        c:=jtcolumnNew(h,b,p,w) 
    end
    aadd(this:column,c)
    return c

 
****************************************************************************
static function jttable.pagefirst(this) 

local page:="",n,ok

    this:row2pos:=array(this:maxrow)
 
    for n:=1 to this:maxrow
    
        if( n==1 )
            ok:=eval(this:gotopblock) 
        else
            ok:=(1==eval(this:skipblock,1))
        end

        if( !ok )
            asize(this:row2pos,n-1)
            exit
        end

        this:savepos(n)
        page+=jttable.row_xmlout(this)
    next

    this:xmlpage(page)
    return NIL


****************************************************************************
static function jttable.pagenext(this) 

local page:="",n

    if( empty(this:row2pos) )
        return NIL
    end

    this:restpos( len(this:row2pos) )
    this:row2pos:=array(this:maxrow)
 
    for n:=1 to this:maxrow
        if( 1!=eval(this:skipblock,1) )
            asize(this:row2pos,n-1)
            exit
        end
        this:savepos(n)
        page+=jttable.row_xmlout(this)
    next

    this:xmlpage(page)
    return NIL


****************************************************************************
static function jttable.pageprev(this) 

local page:="",n

    if( empty(this:row2pos) )
        return NIL
    end
 
    this:restpos(1) 
    this:row2pos:=array(this:maxrow)
 
    for n:=1 to this:maxrow
        if( -1!=eval(this:skipblock,-1) )
            asize(this:row2pos,n-1)
            exit
        end
        this:savepos(n)
        page:=jttable.row_xmlout(this)+page
    next

    areverse(this:row2pos)
    this:xmlpage(page)
    return NIL
 

 
****************************************************************************
static function jttable.pagelast(this) 

local page:="",n,ok

    this:row2pos:=array(this:maxrow)
 
    for n:=1 to this:maxrow
    
        if(n==1)
            ok:=eval(this:gobottomblock) 
        else
            ok:=(-1==eval(this:skipblock,-1))
        end

        if( !ok )
            asize(this:row2pos,n-1)
            exit
        end

        this:savepos(n)
        page:=jttable.row_xmlout(this)+page
    next

    areverse(this:row2pos)
    this:xmlpage(page)
    return NIL

****************************************************************************
static function jttable.pagereload(this) //újraküldi a lapot

local page:="",n,ok
 
    ok:=this:restpos(1)  
    this:row2pos:=array(this:maxrow) 

    for n:=1 to this:maxrow
    
        if( n>1 )
            ok:=(1==eval(this:skipblock,1))
        end

        if( !ok )
            asize(this:row2pos,n-1)
            exit
        end

        this:savepos(n)
        page+=jttable.row_xmlout(this)
    next

    this:xmlpage(page)
    return NIL
 

****************************************************************************
static function jttable.pagecurrent(this) 
    this:row2pos:={NIL}
    this:savepos(1)
    this:pagereload
    return NIL
 

****************************************************************************
static function jttable.pagerefresh(this)
local x:=this:selectedindices
    if( len(x)==1 )
        eval(this:skipblock,1-x[1])
    end
    return this:pagecurrent
 

****************************************************************************
static function jttable.rowrefresh(this,n) //újraküldi az n-edik sort
local sel
    if( n==NIL )
        sel:=this:selectedindices
        if( len(sel)==1 )
            n:=sel[1]
        end
    end
    if( n!=NIL .and. this:restpos(n) )
        this:xmlrow(n,jttable.row_xmlout(this))
    end
    return NIL

 
****************************************************************************
static function areverse(a)
local l:=len(a),n,x
    for n:=1 to l/2
        x:=a[n]
        a[n]:=a[l-n+1]
        a[l-n+1]:=x
    next
    return a


****************************************************************************
static function jttable.xmladd(this)
local x:=EOL, n, i, c, t
    if(!empty(this:colortable))
        x+='<colortable>'
        for n:=1 to len(this:colortable)
            x+='<color>'
            x+='<r>'+alltrim(str(this:colortable[n][1]))+'</r>'
            x+='<g>'+alltrim(str(this:colortable[n][2]))+'</g>'
            x+='<b>'+alltrim(str(this:colortable[n][3]))+'</b>'
            x+='</color>'
        next
        x+='</colortable>'+EOL
    end
    for n:=1 to this:colcount
        x+=this:column[n]:xmlout+EOL
    next
    if( !empty(this:selectedindices) )
        x+="<sel>"+this:xmlget+"</sel>"+EOL
    end
    return x


****************************************************************************
static function jttable.xmlput(this,x)      
local c,n,i
    c:=x:content
    for n:=1 to len(c)
        if( c[n]:type=="sel" )
            this:selectedindices:=split(c[n]:gettext) 
            for i:=1 to len(this:selectedindices)
                this:selectedindices[i]:=val(this:selectedindices[i])
            next
        elseif( c[n]:type=="change" )
            jttable.chngcell(this,c[n])
        end
    next

    return this:selectedindices 
    
 
****************************************************************************
static function jttable.xmlget(this)
local x:="",n
    for n:=1 to len(this:selectedindices)
        if( n>1 )
            x+=","
        end
        x+=alltrim(str(this:selectedindices[n]))
    next
    return x


****************************************************************************
static function jttable.xmlpage(this,page)
local x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"+EOL
    x+="<setpage>"+EOL
    x+=page
    x+="</setpage>"+EOL
    x+="</jtmessage>"
    this:send(x)
    return NIL


****************************************************************************
static function jttable.xmlrow(this,n,row)
local x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"+EOL
    x+="<setrow><index>"+alltrim(str(n))+"</index>"+EOL
    x+=row
    x+="</setrow>"+EOL
    x+="</jtmessage>"
    this:send(x)
    return NIL


****************************************************************************
#define  ICON_TOP        "icons/22/top.png" 
#define  ICON_BOTTOM     "icons/22/bottom.png"
#define  ICON_DOWN       "icons/22/down.png" 
#define  ICON_UP         "icons/22/up.png"  
#define  ICON_RELOAD     "icons/22/reload.png"  
 
****************************************************************************
static function jttable.mktoolbar( this, panel )

local button, name

    if( panel==NIL  )
        panel:=jttoolbarNew()
    end

    name:=this:name

    button:=panel:additem(jtpushNew()) 
    button:name:=name+"top"
    button:actionblock:={||this:pagefirst}
  //button:text:=@"Home" //"Elejére"
    button:icon:=ICON_TOP
    button:tooltip:=@"Go top" //"A tábla elejére pozícionál."
    button:mnemonic:="home"
    button:border:="null"
 
    button:=panel:additem(jtpushNew()) 
    button:name:=name+"nxt"
    button:actionblock:={||this:pagenext}
  //button:text:=@"Next" //"Következő"
    button:icon:=ICON_DOWN
    button:tooltip:=@"Next page" //"Előre lapoz."
    button:mnemonic:="page_down"
    button:border:="null"
 
    button:=panel:additem(jtpushNew()) 
    button:name:=name+"prv"
    button:actionblock:={||this:pageprev}
  //button:text:=@"Prev" //"Előző"
    button:icon:=ICON_UP
    button:tooltip:=@"Previous page" //"Hátra lapoz."
    button:mnemonic:="page_up"
    button:border:="null"
 
    button:=panel:additem(jtpushNew()) 
    button:name:=name+"bot"
    button:actionblock:={||this:pagelast}
  //button:text:=@"Bottom" //"Végére"
    button:icon:=ICON_BOTTOM
    button:tooltip:=@"Go bottom" //"A tábla végére pozícionál."
    button:mnemonic:="end"
    button:border:="null"
 
    button:=panel:additem(jtpushNew()) 
    button:name:=name+"rel"
    button:actionblock:={||this:pagereload}
  //button:text:=@"Reload" //"Újraolvas"
    button:icon:=ICON_RELOAD
    button:tooltip:=@"Reload current page" //"Újraolvassa a lapot."
    button:border:="null"
    
    return panel


****************************************************************************
static function  jttable.chngcell(this,x)
 
local e, c, n
local row, col, valold, valnew
local column

    c:=x:content

    for n:=1 to len(c)
        if( c[n]:type=="r" )
            row:=val(c[n]:gettext)
        elseif( c[n]:type=="c" )
            col:=val(c[n]:gettext)
        elseif( c[n]:type=="from" )
            valold:=c[n]:gettext
        elseif( c[n]:type=="to" )
            valnew:=c[n]:gettext
        end
    next
        
    if( !this:restpos(row) )
        e:=apperrorNew()
        e:operation:="jttable.chngcell"
        e:description:="restpos failed"
        break(e)
    end

    //Ez a megoldás nem ellenőrzi valcur==valold fennállását,
    //ehelyett továbbadja valold-ot az oszlopblocknak, ami azután
    //elvégezheti az ellenőrzést, ha akarja.
    //
    //Az browse oszlopblockját a szokásos eval(blk,x) helyett
    //eggyel több paraméterrel hívjuk: eval(blk,x,xold), ahol
    //xold a terminálnak átadott korábbi érték, ezt a block
    //kódja ellenőrizheti (az adatforrás lockolása után).
 
    column:=this:getcolumn(col)

    if( column:type=="C" )
        eval(column:block,valnew,valold)

    elseif( column:type=="N" )
        eval(column:block,val(valnew),val(valold))

    elseif( column:type=="D" )
        //az üres dátum ""-ként jön!
        valold:=if(empty(valold),ctod(""),stod(valold))
        valnew:=if(empty(valnew),ctod(""),stod(valnew))
        eval(column:block,valnew,valold)

    elseif( column:type=="L" )
        eval(column:block,valnew=="true",valold=="true")
    end

    return NIL
 

****************************************************************************
static function jttable.row_xmlout(this)

// koncepció VÁLTOZÁS:
// nem az adat, hanem az oszlop típusát nézzük,
// ui. más nyelvekben nem lehet felismerni a típusokat, 
// pl. Pythonban nehéz felismerni a dátum és logikai típust

local x:="", i, d, t
local cb,cx,fg,bg,sty,fam

    x+="<r>"
    for i:=1 to this:colcount
        t:=this:column[i]:type
        d:=eval(this:column[i]:block) 
        
        sty:=''
        fam:=''
        if( (cb:=this:column[i]:fontblock)!=NIL .and. NIL!=(cx:=eval(cb,d)) )

            // fontblock visszatérése:
            //
            // fs      -> font style beállítva
            // {ff,fs} -> font family és font style beállítva
            //
            // fs értékei: NIL, 0, STY konstans
            // ff értékei: NIL, 0, FAM konstans
            //
            // empty értéket nem küld a terminálnak

            if( valtype(cx)=="N" )
                if( !empty(cx) )
                    sty:=' sty="'+alltrim(str(cx))+'"'
                end
            else
                if( !empty(cx[1]) )
                    fam:=' fam="'+alltrim(str(cx[1]))+'"'
                end
                if( !empty(cx[2]) )
                    sty:=' sty="'+alltrim(str(cx[2]))+'"'
                end
            end
        end

        fg:=''
        bg:=''
        if( (cb:=this:column[i]:colorblock)!=NIL .and. NIL!=(cx:=eval(cb,d)) )
            if( valtype(cx)=="N" )
                if(!empty(cx))
                    fg:=' fg="'+alltrim(str(cx))+'"' //color index: 1,2,...
                end
            else
                if(!empty(cx[1]))
                    fg:=' fg="'+alltrim(str(cx[1]))+'"'
                end
                if(!empty(cx[2]))
                    bg:=' bg="'+alltrim(str(cx[2]))+'"'
                end
            end
        end

        if( t=="C" )
            d:=cdataif(alltrim(d))
        elseif( t=="N" )
            d:=alltrim(str(d))
        elseif( t=="D" )
            d:=dtos(d)
        elseif( t=="L" )
            d:=if(d,"t","f")
        else
            d:=""
        end
        x+="<c"+fam+sty+fg+bg+">"+d+"</c>" 
    next
    x+="</r>"+EOL
    return x
 

 
****************************************************************************
 
