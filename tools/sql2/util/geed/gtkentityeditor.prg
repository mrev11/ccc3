
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

******************************************************************************
class gtkentityeditor(object)
    attrib window
    attrib data
    attrib table
    attrib rowset
    attrib select
    attrib maxrow
    attrib bindval
    attrib bindent
    attrib bindlab
    attrib uncommitted
   
    method initialize
    method show

******************************************************************************
static function gtkentityeditor.initialize(this,table)

    this:data:={}
    this:table:=table
    this:bindval:={}
    this:bindlab:={}
    this:bindent:={}

    this:window:=gladeloadgui("gtkentityeditor.glade")
    this:window:signal_connect("destroy",{||gtk.main_quit()})
    this:maxrow:=16
    this:uncommitted:=0

    make_browse(this)

    return this

******************************************************************************
static function gtkentityeditor.show(this,select,bind)

local x
local combo_select
local button_top
local n,bindseg

    if( select!=NIL )
        if( 0<(x:=ascan(this:table:__filterlist__,{|s|s[1]==select})) )
            combo_select:=this:window:lookup("combo_select")
            combo_select:set_active(x-1) 
            //itt végrehajtódott cb_combo_select_changed
            if( bind!=NIL )
                for n:=1 to len(bind)
                    bindseg:=sqlval(bind[n])
                    aadd(this:bindval,bindseg)
                    this:bindent[n]:set_text(bindseg)
                next
            end
            button_top:=this:window:lookup("button_top")
            cb_button_top_clicked(button_top,this)
        end
    end

    this:window:show_all()
    this:window:lookup("statusbar1"):push(0,this:table:connection:version)
    
    gtk.main()


static function sqlval(x)
    if( valtype(x)=="C" )
    elseif( valtype(x)=="L" )
        x:=if(x,"1","0")
    elseif( valtype(x)=="D" )
        x:=dtoc(x)
    elseif( valtype(x)=="N" )
        x:=alltrim(str(x))
    end
    return x

   
******************************************************************************
static function make_browse(this)

local window:=this:window
local treeview:=window:lookup("treeview")
local button_top:=window:lookup("button_top")
local button_down:=window:lookup("button_down")
local button_commit:=window:lookup("button_commit")
local button_rollback:=window:lookup("button_rollback")
local hbox_bind:=window:lookup("hbox_bind")
local combo_select:=window:lookup("combo_select")
local table:=this:table
local n,col

    for n:=1 to len(table:__filterlist__)
         combo_select:append_text(table:__filterlist__[n][1])
    next
    combo_select:set_active(0) //0-tól indul
    
    treeview:set_model(gtkliststoreNew_array_index(this:data))
    treeview:set_rules_hint(.t.)  //ettől lesz sávos

    for n:=1 to len(table:columnlist)
        col:=table:columnlist[n]
        treeview:append_column:=create_column(this:data,col)
    next
    
    button_top:signal_connect("clicked",{|w|cb_button_top_clicked(w,this)})
    button_down:signal_connect("clicked",{|w|cb_button_down_clicked(w,this)})
    button_commit:signal_connect("clicked",{|w|cb_button_commit_clicked(w,this)})
    button_rollback:signal_connect("clicked",{|w|cb_button_rollback_clicked(w,this)})
    combo_select:signal_connect("changed",{|w|cb_combo_select_changed(w,this)})

    window:signal_connect("destroy",{||if(this:rowset==NIL,NIL,this:rowset:close)})


******************************************************************************
static function create_column(data,col)

local column:=gtktreeviewcolumnNew()
local renderer,num,wid,dec

    if( col:type=="L" )
        renderer:=gtkcellrenderertoggleNew()
        renderer:set_property("xpad",8)

        //a default az avtivatable állapot
        //renderer:set_property("activatable",.t.)
        renderer:signal_connect("toggled",{|r,p|cb_toggled(r,p,data,col)})

    elseif( "N"$col:type )
        renderer:=gtkcellrenderertextNew()
        renderer:set_property("xalign",1)
        renderer:set_property("xpad",4)

        if( col:picture==NIL )
            num:=val(substr(col:type,2))

            wid:=int(num)
            wid:=replicate("9",wid)+","
            while( "99999,"$wid )
                wid:=strtran(wid,"99999,","99,999,")
            end
            wid:=left(wid,len(wid)-1)

            dec:=(num%1)*10
            if( dec==0 )
                dec:=""
            else
                dec:="."+replicate("9",dec)
            end
            col:picture:=wid+dec
        end

        renderer:set_property("editable",.t.)
        renderer:signal_connect("edited",{|r,p,t|cb_edited(r,p,t,data,col)})

    else
        renderer:=gtkcellrenderertextNew()
        renderer:set_property("xpad",4)

        renderer:set_property("editable",.t.)
        renderer:signal_connect("edited",{|r,p,t|cb_edited(r,p,t,data,col)})
    end

    //column:set_title(col:name)
    column:set_title(strtran(col:name,"_","__"))
    column:pack_start(renderer)
    column:set_cell_data_func(renderer,{|c,r,m,i|get_column_data(c,r,m,i,data,col)})

    return column

****************************************************************************** 
static function cb_toggled(r,p,data,col)

// r: a renderer
// p: a sor pozíciója (0-tól indul) szövegesen

local row:=data[val(p)+1]
local val:=col:eval(row)

    col:eval(row,!val)

****************************************************************************** 
static function cb_edited(r,p,t,data,col)

// r: a renderer
// p: a sor pozíciója (0-tól indul)  szövegesen
// t: az új szöveg

local row:=data[val(p)+1]
local type:=col:type
local orig:=col:eval(row),edited

    if( "L"$type )
        //ilyen nem lehet

    elseif( "N"$type )
        edited:=val(strtran(t,",",""))
        if( orig!=edited  )
            col:eval(row,edited)
        end

    elseif( "D"$type )
        edited:=ctod(t)
        if( orig!=edited  )
            col:eval(row,edited)
        end

    elseif( "C"$type )
        edited:=t

        //Sajnos ez itt nem jó,
        //nélkülözhetetlen az igazi picture
        //(amit most nem tudok megcsinálni)!
        //? "'"+orig+"'","'"+edited+"'"

        if( col:picture!=NIL )
            orig:=transform(orig,col:picture)
            //kibányászni az templateből az adatot
            //ahogy azt a get:untransform csinálja
            //picture renderer kellene
        end

        if( !orig==edited )
            col:eval(row,edited)
        end
    else
        ? "Unknown type:", type
    end
    
    //? r,p,t


****************************************************************************** 
static function get_column_data(column,renderer,model,iter,data,col)
local idx:=gtk.tree_model.get(model,iter)[1] //datarow[1]
local val:=col:eval(data[idx])
    if( col:type=="L" )
        renderer:set_property("active",val)
    elseif( NIL!=col:picture )
        renderer:set_property("text",transform(val,col:picture))
    else
        renderer:set_property("text",any2str(val))
    end

****************************************************************************** 
static function cb_button_top_clicked(w,this)

local treeview:=w:lookup("treeview")
local n,selblk,row

    update(this)

    ? "cb_button_top_clicked"
    //gc()

    if( this:rowset!=NIL )
        this:rowset:close
    end

    asize(this:data,0)
    if( this:select==NIL )
        this:rowset:=this:table:select
    else
        if( !empty(this:bindent) )
            asize(this:bindval,0)
            for n:=1 to len(this:bindent)
                if( this:bindent[n]==NIL )
                    aadd(this:bindval,NIL)
                else
                    aadd(this:bindval,alltrim(this:bindent[n]:get_text))
                end
            next
        end
        selblk:=getmethod(getclassid(this:table),this:select)
        this:rowset:=eval(selblk,this:table,this:bindval)
    end

    while( len(this:data)<this:maxrow .and.  NIL!=(row:=this:rowset:next) )
        aadd(this:data,row)
    end
    
    treeview:get_model:unref //enélkül gyorsan eszi a memóriát
    treeview:set_model(gtkliststoreNew_array_index(this:data))

****************************************************************************** 
static function cb_button_down_clicked(w,this)

local treeview:=w:lookup("treeview"),row
static count:=0

    update(this)

    if( gtk.main_depth()>1 )
        //ne legyen rekurzív
        return NIL
    end

    ? "cb_button_down_clicked", ++count
    //gc()

    if( this:rowset==NIL )
        return NIL
    end

    asize(this:data,0)
    while( len(this:data)<this:maxrow .and. NIL!=(row:=this:rowset:next) )
        aadd(this:data,row)
    end

    treeview:get_model:unref 
    treeview:set_model(gtkliststoreNew_array_index(this:data))
    gtk.main_stabilize()
    
    //ha a modell nincs unrefelve, akkor gyorsan eszi a memóriát
    //ha a modell nincs cserélve, akkor nem fest, és nem eszi a memóriát
    //egyébként lassan eszi a memóriát
    //ha a get_column_data törzse üres, akkor is eszi
    //ha a postgres teljesen ki van iktatva, akkor is eszi


****************************************************************************** 
static function cb_button_commit_clicked(w,this)
    ? "cb_button_commit_clicked"
    update(this)
    this:table:connection:sqlcommit
    this:uncommitted:=0
    status(this)

****************************************************************************** 
static function cb_button_rollback_clicked(w,this)
    ? "cb_button_rollback_clicked"
    this:table:connection:sqlrollback
    this:uncommitted:=0
    status(this)

****************************************************************************** 
static function cb_combo_select_changed(w,this)

local hbox_bind:=w:lookup("hbox_bind")
local sel,whr,ord
local n,x,lab,ent,ent1

    ? "cb_combo_select_changed"

    sel:=w:get_active_text
    whr:=this:table:__filterlist__[w:get_active+1][2]
    ord:=this:table:__filterlist__[w:get_active+1][3]
    
    this:select:=sel
    
    asize(this:bindval,0)
    asize(this:bindent,0)
    for n:=1 to len(this:bindlab)
        this:bindlab[n]:destroy
    next
    asize(this:bindlab,0)
    
    x:=""
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
            lab:=gtklabelNew(x[n])
            hbox_bind:pack_start(lab,.f.,.f.,2)
            aadd(this:bindlab,lab) //ezeket kell megszüntetni
            lab:show
        else
            if( len(this:bindent)<x[n] )
                asize(this:bindent,x[n])
            end
            ent:=gtkentryNew()
            ent:set_size_request(100,-1)
            hbox_bind:pack_start(ent,.f.,.f.,2)
            aadd(this:bindlab,ent) //ezeket kell megszüntetni

            if( this:bindent[x[n]]==NIL )
                this:bindent[x[n]]:=ent //első előfordulás
            else
                ent1:=this:bindent[x[n]] //már volt ilyen
                ent1:signal_connect("key-release-event",mkblk_repeat(ent))
                ent:set_editable:=.f.
            end
            ent:show
        end
    next

****************************************************************************** 
static function mkblk_repeat(ent)
    return {|w|cb_entry_key_release_event(w,ent)}

****************************************************************************** 
static function cb_entry_key_release_event(w,ent)
    ent:set_text(w:get_text)

****************************************************************************** 
static function update(this)
local n
    for n:=1 to len(this:data)
        //if( this:data[n]:update ) //ütközhet a metósudnév
        if( this:data[n]:tableentity:update(this:data[n]) ) //ugyanaz kerülővel
            this:uncommitted++
        end
    next
    status(this)

****************************************************************************** 
static function status(this)
local statusbar:=this:window:lookup("statusbar1")

    statusbar:pop(0)
    if( this:uncommitted>0 )
        statusbar:push(0,"Uncommitted updates:"+str(this:uncommitted))
    else
        statusbar:push(0,this:table:connection:version)
    end

****************************************************************************** 
