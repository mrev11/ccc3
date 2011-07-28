
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

//jterminálos tableentity browse/edit


//ezek jterminal.jar-beli pathok:

#define  ICON_TOP        "icons/16/top.png" 
#define  ICON_DOWN       "icons/16/down.png" 
#define  ICON_EXEC       "icons/16/exec.png"  
#define  ICON_DETAILS    "icons/16/viewmag.png"  
#define  ICON_COMMIT     "icons/16/filesave.png"  
#define  ICON_ROLLBACK   "icons/16/editdelete.png"  


******************************************************************************
class jtentityeditor(jtdialog)

    attrib table          //tableentity objektum
    attrib select         //tableentity select metódus név
    attrib bindval        //array a select metódus bind értékeivel
    attrib bindget        //array a bind getek neveivel
    attrib uncommitted    //ennyi nem commitolt update történt
    attrib editable
   
    method maxrow         //lapméret beállítás (16)
    method initialize
    method show
    method clear


******************************************************************************
static function jtentityeditor.initialize(this,t,l,b,r,table,edit)

    //? jtversion()

    if( valtype(t)=="O" )
        table:=t
        edit:=l
        t:=l:=b:=r:=NIL
    end

    this:table:=table
    this:bindval:={}
    this:bindget:={}
    this:uncommitted:=0
    this:editable:=(edit!=.f.)
    
    if(t==NIL)
        t:=8
        l:=16
        b:=24
        r:=100
    end

    this:(jtdialog)initialize(t,l,b,r)
    this:layout:="vbox"

    make_browse(this)

    return this


******************************************************************************
static function jtentityeditor.clear(this,e)

local brw:=this:var:brw   //jtbrowseentity objektum
local table:=this:table   //tableentity objektum

    table:connection:sqlrollback
    if( brw:rowset!=NIL )
        brw:rowset:close
    end
    this:uncommitted:=0
    uncommitted_update(this)

    if( e!=NIL )
        alert(e:description)
    end

******************************************************************************
static function jtentityeditor.show(this,select,bind,top)
local n,bval,btyp

    if( select!=NIL )
        this:var:select:selectitem(select)

        action_select_changed(this)

        for n:=1 to len(bind)
            bval:=bind[n]
            btyp:=valtype(bval)

            if( btyp=="C" )
                bval:=alltrim(bval)
            elseif(btyp=="N")
                bval:=alltrim(str(bval))
            elseif(btyp=="D")
                bval:=ctod(bval)
            elseif(btyp=="L")
                bval:=if(bval,"1","0")
            end
            
            this:var:evalmethod(bindgetname(n)):varput(bval)
        next
    end

    this:(jtdialog)show

    if( top==.t. )
        action_top(this) //nem tökéletes!
    end

    while( NIL!=this:getmessage )
    end


******************************************************************************
static function jtentityeditor.maxrow(this,x)
    if( x!=NIL )
        this:var:brw:maxrow:=x
    end
    return this:var:brw:maxrow


******************************************************************************
static function make_browse(this)

local table:=this:table,col
local con:=table:connection
local bar,split,pnl,brw,but,sel,lab,n

    this:caption:=table:classname
    this:layout:="vbox"

    bar:=this:add(jttoolbarNew())

    //split:=this:add(jtsplitpaneNew()) //ez jobbra pakkol, miért??
    split:=this:add(jtpanelNew()):additem(jtsplitpaneNew()) //workaround
    split:divider:=3

    pnl:=split:setitem(1,jtpanelNew())
    pnl:name:="bind"

    brw:=split:setitem(2,jtbrowseentityNew())
    brw:name:="brw"
    brw:addcolumns(table)

    if( this:editable )
        //minden oszlop editálható, kivéve a kulcsok
        for n:=1 to len(table:columnlist)
            col:=table:columnlist[n]
            if(0==ascan(table:__primarykey__,{|x|x:columnid==col:columnid}))
                brw:getcolumn(n):editable:=.t.
            end
        next
    end
    
    but:=bar:additem(jtpushNew())
    but:name:="top"
    but:icon:=ICON_TOP
    but:tooltip:="Első lap (újrakezdi a lapozást)"
    but:actionblock:={||action_top(this)}

    but:=bar:additem(jtpushNew())
    but:name:="next"
    but:icon:=ICON_DOWN
    but:tooltip:="Következő lap"
    but:actionblock:={||action_next(this)}

    but:=bar:additem(jtpushNew())
    but:name:="details"
    but:icon:=ICON_DETAILS
    but:text:="Details"
    but:tooltip:="Rekord editálás külön dialogban"
    but:mnemonic:="INSERT" //ALT-INSERT
    but:actionblock:={||action_details(this)}

    if( this:editable )
        but:=bar:additem(jtpushNew())
        but:name:="commit"
        but:icon:=ICON_COMMIT
        but:text:="Commit"
        but:tooltip:="Módosítások véglegesítése"
        but:actionblock:={||action_commit(this)}

        but:=bar:additem(jtpushNew())
        but:name:="rollback"
        but:icon:=ICON_ROLLBACK
        but:text:="Rollback"
        but:tooltip:="Módosítások érvénytelenítése"
        but:actionblock:={||action_rollback(this)}
    end

    sel:=bar:additem(jtcomboNew()) 
    sel:name:="select"
    sel:tooltip:="Beállítja a szűrő metódust"
    for n:=1 to len(table:__filterlist__)
        sel:additem(table:__filterlist__[n][1])
    next
    sel:selectedindex:=0
    sel:actionblock:={||action_select_changed(this)}
    
    lab:=bar:additem(jtlabelNew()) 
    lab:name:="uncommitted"
    lab:tooltip:="Nem commitolt update utasítások száma"
    
    this:varinst("x")

    return this


******************************************************************************
static function action_top(this)

local brw:=this:var:brw   //jtbrowseentity objektum
local table:=this:table   //tableentity objektum
local select:=this:select //az aktuális select metódus neve
local bv,n,e

    if( !empty(select) )

        asize(this:bindval,len(this:bindget))
        for n:=1 to len(this:bindget)
            if( this:bindget[n]!=NIL )
                bv:=this:var:evalmethod(this:bindget[n]):varget
                bv:=alltrim(bv)
                //q/d megoldás (a,b,c) alakú bind változókra
                //sqlliteral ilyen alakra hozza az array-ket
                if( left(bv,1)=="(" .and. right(bv,1)==")" )
                    bv:=bv[2..len(bv)-1]::strtran(" ","")::split
                end
                this:bindval[n]:=bv
            end
        next

        begin
            //? select, this:bindval
            update(this)
            brw:rowset:=table:evalmethod(select,{this:bindval})
            brw:next
        recover e <sqlerror>
            this:clear(e)
        end
    end

******************************************************************************
static function action_next(this)
local brw:=this:var:brw, e
    begin
        update(this)
        if( brw:rowset!=NIL )
            brw:next
        end
    recover e <sqlerror>
        this:clear(e)
    end

******************************************************************************
static function action_details(this)

local brw:=this:var:brw
local row:=brw:currentrow
local row1
local dlg,top,lef,bot,rig

    top:=this:top+2
    lef:=this:left+32
    //bot:=this:bottom+2 //NIL: automatikus méretezés
    //rig:=this:right+1  //NIL: automatikus méretezés

    if( row==NIL )
        row1:=this:table:instance
        dlg:=jtrowentityeditorNew(top,lef,bot,rig,row1,"fiudx",this:editable)
    else
        dlg:=jtrowentityeditorNew(top,lef,bot,rig,row,"dox",this:editable)
    end

    dlg:show

    if( dlg:uncommitted>0 )
        this:uncommitted+=dlg:uncommitted
        uncommitted_update(this)
    end
    
    if( row!=NIL .and. dlg:rowchanged )
        brw:rowrefresh //csak a legegyszerűbb esetben jó

        //Az eredeti helyén mutatja a módosított sort,
        //noha lehet, hogy a selectet újra végrehajtva
        //a sor kikerülne a táblából, vagy máshova kerülne.
        //Az insert/delete eredménye a browse-ban nem látszik,
        //nem ismert, hogyan kellene frissíteni a browse-t e célból.
    end

******************************************************************************
static function action_commit(this)
local e
    begin
        update(this,.f.)
        this:table:connection:sqlcommit
    recover e <sqlerror>
    end
    this:clear(e)

******************************************************************************
static function action_rollback(this)
    this:clear

******************************************************************************
static function action_select_changed(this)

local com:=this:var:select //combobox
local pnl:=this:var:bind //bind panel
local sel,frm,whr,ord
local n,x,lab,get,pnl1:=jtpanelNew()

    sel:=com:selecteditem
    frm:=this:table:__tabjoin__
    whr:=this:table:__filterlist__[com:selectedindex][2]
    ord:=this:table:__filterlist__[com:selectedindex][3]
    
    this:select:=sel

    asize(this:bindval,0)
    asize(this:bindget,0)

    x:=""
    if( !empty(frm) )
        x+=frm+" "
    end
    if( !empty(whr) )
        x+=whr
    end
    if( !empty(ord) )
        x+=" order by "+ord
    end

    while( "  "$x )
        x:=strtran(x,"  "," ")
    end

    x:=tdsutil.sqlplaceholders(x)

    for n:=1 to len(x)
        if( valtype(x[n])=="C" )
            lab:=jtlabelNew(x[n])
            pnl1:additem(lab)

        else
            if( len(this:bindget)<x[n] )
                asize(this:bindget,x[n])
            end

            if( this:bindget[x[n]]==NIL )
                // első előfordulás, új get

                get:=jtgetNew() 
                get:name:=bindgetname(x[n])
                get:right:=16
                get:actionblock:={||action_top(this)}                
                pnl1:additem(get)
                this:bindget[x[n]]:=get:name
            else
                // többedik előfordulás
                // nem csinálunk neki új getet (csak labelt) 
                // a gtv-ben egy nem editálható entry automatikusan ismétli 
                // az első példány tartalmát (ez itt nem megoldható)

                lab:=jtlabelNew(" :"+alltrim(str(x[n]))+" ")
                pnl1:additem(lab)
            end
        end
    next

    pnl1:name:="bind"
    pnl1:layout:="flow"
    pnl:changeitem(pnl1)
    this:varinst(this:select) //új osztályt csinál


******************************************************************************
static function update(this,flag)

local brw:=this:var:brw   //jtbrowseentity objektum
local table:=this:table   //tableentity objektum
local upd:=this:uncommitted
local row,n,e

    for n:=1 to len(brw:_array_)
        row:=brw:_array_[n]
        begin
            //row:update //ütközhet a metódusnév
            this:uncommitted+=table:update(row) //ugyanaz kerülővel
            table:setdirty(row,.f.) //ne írja ki többször
        recover e <sqlerror>
            this:clear(e)
        end
    next

    if( upd<this:uncommitted .and. flag!=.f. )
        uncommitted_update(this)
    end

******************************************************************************
static function uncommitted_update(this)
local lab:=this:var:uncommitted  //jtlabel objektum
local txt:=if(this:uncommitted>0,"Uncommitted:"+str(this:uncommitted,4),"")
    txt:='<html><font face="ariel" color="red"><b>'+txt
    lab:changetext(txt)

******************************************************************************
static function bindgetname(n)
    return "bindget:"+alltrim(str(n))

******************************************************************************
