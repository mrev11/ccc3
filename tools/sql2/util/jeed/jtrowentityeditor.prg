
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

#define  ICON_EXEC       "icons/16/exec.png" 
#define  ICON_EXIT       "icons/16/exit.png" 
#define  ICON_COMMIT     "icons/16/filesave.png"  
#define  ICON_ROLLBACK   "icons/16/editdelete.png"  
#define  ICON_KEY        "icons/16/2leftarrow.png"  
#define  ICON_NN         "icons/16/1leftarrow.png"  


#define MAXGETWIDTH     72
#define MAXPAGEHEIGHT   25
#define MAXLINEWIDTH   100
#define MINLINEWIDTH    40


*******************************************************************************
class jtrowentityeditor(jtdialog)

    attrib row          //ezt a rowentity objektumot editáljuk
    attrib table        //ebből a tableentityből való row
    attrib connection   //SQL kapcsolat
    attrib getlist      //mezőket editáló getek listája
    attrib uncommitted  //insert/update/delete által módosított rekordok száma
    attrib rowchanged   //.t., ha módosult this:row
    attrib maxlabwid    //labelek szélességének maximuma
    attrib maxgetwid    //getek szélességének maximuma
    attrib sumgethig    //getek összmagassága
    attrib memowid      //memók szélessége
    attrib memohig      //memók magassága
    attrib flags        //milyen gombok legyenek a dialogban
    attrib editable     //editálhatók-e a mezők (default .t.)

    method initialize
    method show

*******************************************************************************
static function jtrowentityeditor.initialize(this,t,l,b,r,row,flags,edit)

#ifdef EMLEKEZTETO //flags tartalma
  c: Commit button
  r: Rollback button
  f: Find button
  i: Insert button
  u: Update button
  d: Delete button
  o: Ok button
  x: Exit button
  
  A betűk sorrendje meghatározza a gombok sorrendjét.
  Nem szabad betűt duplázni.
  Lehet üres is.
  Default "x".
#endif

local wid,hig

    if( valtype(t)=="O" )
        row:=t
        flags:=l
        edit:=b
        t:=l:=b:=r:=NIL
    end

    this:row:=row
    this:flags:=if(flags==NIL,"x",lower(flags))
    this:table:=row:__tableentity__
    this:connection:=this:table:connection
    this:getlist:={}
    this:rowchanged:=.f.
    this:uncommitted:=0
    this:maxlabwid:=0
    this:maxgetwid:=0
    this:sumgethig:=0
    this:memohig:=5         //nem vátoztatható default
    this:memowid:=40        //nem vátoztatható default
    this:editable:=(edit!=.f.)
    
    this:(jtdialog)initialize(t,l,b,r)
    this:layout:="vbox"

    make_dialog(this)
    
    if( b==NIL )
        //automatikus méretezés

        hig:=this:sumgethig+3
        wid:=this:maxlabwid+this:maxgetwid+3

        if( wid>MAXLINEWIDTH )
            wid:=MAXLINEWIDTH
        end

        if( wid<MINLINEWIDTH )
            wid:=MINLINEWIDTH
        end
        
        if( hig>MAXPAGEHEIGHT )
            hig:=MAXPAGEHEIGHT
            wid+=1 //scrollbar
        end

        this:bottom:=this:top+hig
        this:right:=this:left+wid
    end

    return this


*******************************************************************************
static function jtrowentityeditor.show(this)
    this:(jtdialog)show
    while( NIL!=this:getmessage )
    end

*******************************************************************************
static function make_dialog(this)

local bar,but,pnl
local collst:=this:table:columnlist,n
local flags:=this:flags

    if( !empty(flags) )
        bar:=this:add(jttoolbarNew())
    end
    
    while( !empty(flags) )
    
        if( "c"==left(flags,1) .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="commit"
            but:icon:=ICON_COMMIT
            but:text:="Commit"
            but:mnemonic:="C"
            but:tooltip:="Módosítások véglegesítése."
            but:actionblock:={||action_commit(this)}

        elseif( "r"==left(flags,1) .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="rollback"
            but:icon:=ICON_ROLLBACK
            but:text:="Rollback"
            but:mnemonic:="R"
            but:tooltip:="Módosítások visszavétele."
            but:actionblock:={||action_rollback(this)}

        elseif( "f"==left(flags,1) )
            but:=bar:additem(jtpushNew())
            but:name:="find"
            //but:icon:=ICON_EXEC
            but:text:="Find"
            but:mnemonic:="F"
            but:tooltip:="Kulcs alapján keres."
            but:actionblock:={||action_find(this)}

        elseif( "i"==left(flags,1)  .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="insert"
            //but:icon:=ICON_EXEC
            but:text:="Insert"
            but:mnemonic:="I"
            but:tooltip:="Új rekord készítése."
            but:actionblock:={||action_insert(this)}

        elseif( "u"==left(flags,1) .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="update"
            //but:icon:=ICON_EXEC
            but:text:="Update"
            but:mnemonic:="U"
            but:tooltip:="Módosítások kiírása."
            but:actionblock:={||action_update(this)}

        elseif( "d"==left(flags,1) .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="delete"
            //but:icon:=ICON_EXEC
            but:text:="Delete"
            but:mnemonic:="D"
            but:tooltip:="A rekord törlése."
            but:actionblock:={||action_delete(this)}

        elseif( "o"==left(flags,1) .and. this:editable )
            but:=bar:additem(jtpushNew())
            but:name:="ok"
            but:icon:=ICON_EXEC
            but:text:="Ok"
            but:mnemonic:="Q"
            but:tooltip:="Kilép a dialogból, a módosítást megtartja."
            but:actionblock:={||action_ok(this)}

        elseif( "x"==left(flags,1) )
            but:=bar:additem(jtpushNew())
            but:name:="exit"
            but:icon:=ICON_EXIT
            but:text:="Exit"
            but:mnemonic:="X"
            but:tooltip:="Kilép a dialogból, a módosítást nem őrzi meg."
            but:escape:=.t.
            but:actionblock:={||this:close}
        end

        flags:=substr(flags,2)
    end

    maxlabwid(this)

    pnl:=this:add(jtpanelNew())
    pnl:layout:="vbox"
    pnl:vscroll:=.t.

    for n:=1 to len(collst)
        pnl:additem(panel(this,n))
    next


*******************************************************************************
static function action_commit(this)
local e
    begin
        this:connection:sqlcommit
    recover e <sqlerror>
        this:connection:sqlrollback
        //e:list
        alert(e:description)
    end
    this:uncommitted:=0


*******************************************************************************
static function action_rollback(this)
local e
    begin
        this:connection:sqlrollback
    recover e <sqlerror>
        //e:list
        alert(e:description)
    end
    this:uncommitted:=0


*******************************************************************************
static function action_insert(this)
local e,get,col,n
    getdata(this) //data from gets to row

/* 2008.03.31
#ifdef NOT_DEFINED
    //ez a nullokat is kiírja (ez is jó)
    this:table:setdirty(this:row,.t.)
#else
    //ez csak a nemnull értékeket írja ki
    for n:=1 to len(this:getlist)
        col:=this:table:columnlist[n]
        get:=this:getlist[n]
        if( !empty(get:varget) )
            col:setdirty(this:row,.t.)
        end
    next
#endif    
*/
    begin
        this:uncommitted+=this:table:insert(this:row)
    recover e <sqlerror>
        this:connection:sqlrollback
        this:uncommitted:=0
        //e:list
        alert(e:description)
    end

    //A row-nak is van insert metódusa,
    //ezért általában ezt írhatjuk: row:insert.
    //Itt viszont nem ismeretes, hogy nincs-e a táblában 
    //"insert" nevű oszlop, ami felüldefiniálhatja
    //a row-ban levő metódust. Ezt akarjuk elkerülni.

*******************************************************************************
static function action_update(this)
local e
    getdata(this)
    begin
        this:uncommitted+=this:table:update(this:row)
    recover e <sqlerror>
        this:connection:sqlrollback
        this:uncommitted:=0
        //e:list
        alert(e:description)
    end


*******************************************************************************
static function action_delete(this)
local e
    getdata(this)
    begin
        this:uncommitted+=this:table:delete(this:row)
    recover e <sqlerror>
        this:connection:sqlrollback
        this:uncommitted:=0
        //e:list
        alert(e:description)
    end
    this:close

*******************************************************************************
static function action_find(this)
local err,row,col,get,n
    getdata(this)
    begin
        row:=this:table:find(this:row)

        //lásd az insertnél tett megjegyzést,
        //lehetséges, hogy find nevű mező van a táblában,
        //ez volna az egyszerűbb módszer: row:=this:row:find

    recover err <sqlerror>
        alert(err:description)
        return NIL
    end

    if( row==NIL )
        alert("Not found")
        return NIL
    end
    
    this:row:=row
    for n:=1 to len(this:table:columnlist)
        col:=this:table:columnlist[n]
        get:=this:getlist[n]
        if( col:type=="M" )
            get:varput(bin2str(eval(col:block,this:row)))
        else
            get:varput(eval(col:block,this:row))
        end
    next


*******************************************************************************
static function action_ok(this)
    action_update(this)
    this:table:setdirty(this:row,.f.)
    this:close

*******************************************************************************
static function getdata(this) //data from getlist to row

local col,colval,getval,n

    ? "beg----"

    for n:=1 to len(this:getlist)
        col:=this:table:columnlist[n]
        colval:=eval(col:block,this:row)
        getval:=this:getlist[n]:varget

        if( left(col:type,1)=="C" )
            colval:=alltrim(colval)
            getval:=alltrim(getval)
        elseif( left(col:type,1)=="M" )
            colval:=bin2str(alltrim(colval))
            getval:=alltrim(getval)
        end

        if( !colval==getval )
            this:rowchanged:=.t.
            if( col:type=="M" )
                eval(col:block,this:row,str2bin(getval))
            else
                eval(col:block,this:row,getval)
            end
            ? " * "
        else
            ? "   "
        end

        ?? padr(col:name,16),view(colval), "<<<", view(getval)
    next

    ? "end----"

static function view(x)
    x:=any2str(x)
    x:=strtran(x,chr(10),"[A]")
    x:=strtran(x,chr(13),"[D]")
    x:=strtran(x,chr( 9),"[9]")
    return "["+x+"]"

*******************************************************************************
static function panel(this,n) //ret: panel{lab,get}

local pnl,lab,pic,typ,wid,get
local col:=this:table:columnlist[n]
local key:=0<ascan(this:table:__primarykey__,{|x|x:columnid==col:columnid})

    pnl:=jtpanelNew()
    pnl:layout:="hbox"
    pnl:border:="null"
    
    lab:=pnl:additem(jtlabelNew(0,1,0,this:maxlabwid))
    lab:text:=labtxt(col)
    lab:halign:="right"

    pic:=jtbrowseentity.picture(col)
    typ:=left(col:type,1)
    wid:=substr(col:type,2)

    if( typ=="C" )
        wid:=len(pic)-at(" ",pic)
    elseif( typ=="N" )
        wid:=len(pic)-at(" ",pic)
    elseif( typ=="D" )
        wid:=10
    elseif( typ=="L" )
        wid:=1
    elseif( typ=="M" )
        wid:=pic
        pic:=NIL
    end
    
    wid:=min(wid,MAXGETWIDTH)

    if( typ=="M" )
        get:=pnl:additem(jttextareaNew(1,0,this:memohig,0))
        get:linewrap:=.t.
        pnl:additem(jtlabelNew()) //jobb margó
        if( this:maxgetwid<this:memowid )
            this:maxgetwid:=this:memowid
        end
        this:sumgethig+=this:memohig
        get:varput(bin2str(eval(col:block,this:row)))
    else
        get:=pnl:additem(jtgetNew(0,1,0,wid))
        get:picture:=pic
        if( key )
            wid+=4
        elseif( col:notnull )
            wid+=3
        end
        if( this:maxgetwid<wid )
            this:maxgetwid:=wid
        end
        this:sumgethig++
        get:varput(eval(col:block,this:row))
    end

    get:name:="get_"+col:name
    get:tooltip:=col:tooltip

    if( key .and. !("i"$this:flags.or."f"$this:flags) )
        get:enabled:=.f.
    elseif( !key .and. !this:editable )
        get:focusable:=.f.
    end

    if( key )
        pnl:additem(jtlabelNew()):icon:=ICON_KEY
        pnl:additem(jtlabelNew("key"))
    elseif( col:notnull )
        pnl:additem(jtlabelNew()):icon:=ICON_NN
        pnl:additem(jtlabelNew("nn"))
    end

    aadd(this:getlist,get)
    return pnl

*******************************************************************************
static function maxlabwid(this)
local collst:=this:table:columnlist
local wid:=0,n,w
    for n:=1 to len(collst)
        w:=len(labtxt(collst[n]))
        if(w>wid)
            wid:=w
        end
    next
    this:maxlabwid:=wid

*******************************************************************************
static function labtxt(col)
    return ' '+if(col:label==NIL,col:name,col:label)+' '

*******************************************************************************
    