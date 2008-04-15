
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

#include "gdk.ch"
#include "gtk.ch"

#include "amoeba.ch"

#define VERSION "Amoeba 1.2.01 for GTK+"

#define BLACK       1
#define GREY        2
#define LTGREY      3
#define YELLOW      4
#define WHITE       5

#define BX          1
#define BO          2
#define SX          3
#define SO          4

static cellsize:=20
static tablesize:=MAXROW
static area
static twostatelabel

*****************************************************************************
function main()
    //printpid()
    //printexe()
    rand(seconds())
    init_cells()
    amoeba_gui()

******************************************************************************
function amoeba_gui()

local window, hbox, align, vbox
local mask, button, combo, check

    gtk.init()

    window:=gtkwindowNew()
    window:set_title(VERSION)
    window:signal_connect("destroy",{||quit()})
    window:set_border_width(16)
    window:set_resizable(.f.)
    window:set_position(1)
    
    hbox:=gtkhboxNew(.f.,0)
    window:add(hbox)
    
    area:=gtkdrawingareaNew()
    area:set_size_request(cellsize*tablesize+1,cellsize*tablesize+1)
    area:signal_connect("expose_event",{|w,e|cb_expose(w,e)})
    area:signal_connect("button_press_event",{|w,e|cb_button_press(w,e)})
  //area:signal_connect("button_release_event",{|w,e|cb_button_release(w,e)})
  //area:signal_connect("motion_notify_event",{|w,e|cb_motion_notify(w,e)})
    mask:=area:get_events
    mask:=numor(mask,GDK_BUTTON_PRESS_MASK)
    mask:=numor(mask,GDK_BUTTON_RELEASE_MASK)
    mask:=numor(mask,GDK_POINTER_MOTION_MASK)
    area:set_events(mask)
    hbox:pack_start(area)
    
    align:=gtkalignmentNew()
    align:set_padding(0,0,12,0)//top,bot,lef,rig
    hbox:pack_start(align)
    
    vbox:=gtkvboxNew(.f.,10)
    align:add(vbox)

    twostatelabel:=gtktwostateimagelabelNew(.t.,"Ready","Thinking")
    vbox:pack_start(twostatelabel)

    //---------------------------------------------
    vbox:pack_start(gtkhseparatorNew())
    //---------------------------------------------
   
    button:=gtkbuttonNew_with_mnemonic_from_stock("_Move","gtk-execute") 
    button:signal_connect("clicked",{|w|cb_move(w)})
    vbox:pack_start(button)

    button:=gtkbuttonNew_with_mnemonic_from_stock("_Back","gtk-go-back") 
    button:signal_connect("clicked",{|w|cb_back(w)})
    vbox:pack_start(button)

    button:=gtkbuttonNew_with_mnemonic_from_stock("_Forward","gtk-go-forward") 
    button:signal_connect("clicked",{|w|cb_forward(w)})
    vbox:pack_start(button)

    //---------------------------------------------
    vbox:pack_start(gtkhseparatorNew())
    //---------------------------------------------

    check:=gtkcheckbuttonNew_with_mnemonic("_Teach") 
    check:set_active(.t.)
    check:signal_connect("clicked",{|w|cb_teach(w)})
    vbox:pack_start(check)

    combo:=gtkcomboboxNew_text() 
    combo:set_size_request(100,-1)
    combo:signal_connect("changed",{|w|cb_power(w)})
    combo:append_text(POW0)
    combo:append_text(POW1)
    combo:append_text(POW2)
    combo:append_text(POW3)
    combo:append_text(POW4)
    combo:append_text(POW5)
    combo:append_text(POW6)
    combo:append_text(POW7)
    combo:append_text(POW8)
    combo:set_active(0)
    vbox:pack_start(combo)

    //---------------------------------------------
    vbox:pack_start(gtkhseparatorNew())
    //---------------------------------------------
    
    button:=gtkbuttonNew_with_mnemonic_from_stock("_New","gtk-new") 
    button:signal_connect("clicked",{|w|cb_new(w,combo)})
    vbox:pack_start(button)

    window:show_all
    gtk.main()
    ?

******************************************************************************
static function cb_move(w)
    //? "cb_move", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end
    game_over()
    twostatelabel:set_state(.f.)
    c_cb_move()
    twostatelabel:set_state(.t.)

******************************************************************************
static function cb_back(w)
    //? "cb_back", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end
    c_cb_back()

******************************************************************************
static function cb_forward(w)
    //? "cb_forward", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end
    c_cb_forward()

******************************************************************************
static function cb_new(w,combo)
    //? "cb_new", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end
    combo:set_active(0)
    c_cb_new()

******************************************************************************
static function cb_teach(w)
    //? "cb_teach", gtk.main_depth()
    //if(gtk.main_depth()>1);return NIL;end
    //engedni kell a rekurziót
    teach(w:get_active)

******************************************************************************
static function cb_power(w)
    //? "cb_power", gtk.main_depth()
    //if(gtk.main_depth()>1);return NIL;end
    //engedni kell a rekurziót
    power(w:get_active_text)

******************************************************************************
static function cb_button_press(area,event)
local x,y,but,c,fm,n

    //? "cb_button_press", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end

    game_over()

    if( validpos(event,@x,@y,@but) )
        if( but==1 )
            twostatelabel:set_state(.f.)
            area:set_sensitive(.f.)
            c:=y*tablesize+x
            c_cb_button_press(c)
            area:set_sensitive(.t.)
            twostatelabel:set_state(.t.)
        elseif( teach() )
            for n:=0 to tablesize**2-1
                draw(n)
            next
            fm:=movegen(9)
            for n:=1 to len(fm)
                draw(fm[n],,n)
            next
            c:=y*tablesize+x
            c_cb_button_press_stat(c)
        end
    end

******************************************************************************
static function cb_button_release(area,event)
    ? "cb_button_release", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end

******************************************************************************
static function cb_motion_notify(area,event)
    ? "cb_motion_notify", gtk.main_depth()
    if(gtk.main_depth()>1);return NIL;end

******************************************************************************
static function cb_expose(area,event)
local x,y

    //? "cb_expose", gtk.main_depth()
    //if(gtk.main_depth()>2);return NIL;end
    //Ez többszörösen rekurzív, engedni kell.

    for x:=0 to tablesize-1
        for y:=0 to tablesize-1
            draw(y*tablesize+x)
        next
    next

    return .f.


******************************************************************************
function draw(x,size,fmx)

local i:=x%tablesize
local j:=int(x/tablesize)
local fig:=figure(x)
local top:=topcell(x)
local under:=undercell(x)
local color

    if( fig==asc(" ") )
        fig:=0
        if( fmx!=NIL )
            fig:=-fmx
        end
        color:=GREY
    elseif( fig==asc("X") )
        fig:=if(empty(size),BX,SX)
        color:=BLACK
    elseif( fig==asc("O") )
        fig:=if(empty(size),BO,SO)
        color:=WHITE
    end
    
    if( x==top )
        color:=YELLOW
        if(under!=NIL)
            draw(under)
        end
    end
    
    drawcell(i,j,fig,color,GREY)


******************************************************************************
static function drawcell(i,j,fig,fg,bg)

static gc:={;
    makegc("#000000"),; //fekete
    makegc("#c0c0c0"),; //szürke
    makegc("#d0d0d0"),; //világosszürke
    makegc("#ffff00"),; //sárga
    makegc("#ffffff"),; //fehér
    NIL}

static lo:={;
    makelayout("<b>X</b>"),;
    makelayout("<b>O</b>"),;
    makelayout("X"),;
    makelayout("O"),;
    NIL}

static lo1:={;
    makelayout("1"),;
    makelayout("2"),;
    makelayout("3"),;
    makelayout("4"),;
    makelayout("5"),;
    makelayout("6"),;
    makelayout("7"),;
    makelayout("8"),;
    makelayout("9"),;
    NIL}

local x:=i*cellsize
local y:=j*cellsize
local draw:=area:get_drawable

    gdk.drawable.draw_rectangle(draw,gc[bg],.t.,x,y,cellsize,cellsize)
    gdk.drawable.draw_rectangle(draw,gc[BLACK],.f.,x,y,cellsize,cellsize)

    if( fig>0)
        gdk.drawable.draw_layout(draw,gc[fg],x+5,y+2,lo[fig])
    elseif( fig<0 )
        gdk.drawable.draw_layout(draw,gc[BLACK],x+6,y+2,lo1[-fig])  //movegen
    end

    if( gtk.main_depth()<=1 )
        gtk.main_stabilize()
    end

******************************************************************************
static function makegc(colorspec)
local color:=gdk.color.new()
local gc:=gdk.gc.new(area:get_drawable)
    gdk.color.parse(colorspec,color)
    gdk.gc.set_rgb_fg_color(gc,color)
    gdk.color.free(color)
    return gc

******************************************************************************
static function makelayout(x)
local label:=gtk.label.new(x)
//Sajnos ezek hatástalanok
//local fontdesc:=pango.font_description.new_from_string("Courier 24")
//  gtk.widget.modify_font(label,fontdesc)
//  pango.font_description.free(fontdesc)
    gtk.label.set_use_markup(label,.t.)
    return gtk.label.get_layout(label)

******************************************************************************
static function validpos(event,x,y,but)

local xy:=gdk.event.get_coords(event)

    x:=xy[1]
    y:=xy[2]
    but:=gdk.event_button.get_button(event) //1,2,3 -- bal,köz,jobb
    
    if( x%cellsize<2 .or. x%cellsize>cellsize-2 )
        return .f.
    elseif( y%cellsize<2 .or. y%cellsize>cellsize-2 )
        return .f.
    end

    x:=int(x/cellsize)
    y:=int(y/cellsize)
    
    if( x>=tablesize )
        return .f.
    elseif( y>=tablesize )
        return .f.
    elseif( figure(y*tablesize+x)!=32 )
        return .f.
    end
    
    return  .t.

******************************************************************************
static function printpid()
    set printer to pid
    set printer on
    ?? getpid()
    set printer to
    set printer off

******************************************************************************
static function printexe()
    set printer to exe
    set printer on
    ?? exename()
    set printer to
    set printer off

******************************************************************************
static function gtkbuttonNew_with_mnemonic_from_stock(label_text,stock_id)
local button,box,label,image
    box:=gtkhboxNew(.f.,0)
    box:set_border_width(2)
    image:=gtkimageNew_from_stock(stock_id,1)
    label:=gtklabelNew(label_text)
    label:set_use_underline(.t.)
    box:pack_start(image, .f., .f., 3)
    box:pack_start(label, .f., .f., 3)
    button:=gtkbuttonNew()
    button:add(box)
    return button


#ifdef NOT_DEFINED

Ez az eset mutatja, hogy a GTK egy katyvasz.
Háromféleképpen lehet buttonokat egymás mellé tenni.

    1) GtkVBox, benne GtkButton-ok.

    2) GtkVButtonBox, benne GtkButton-ok.

    3) GtkToolbar, benne toolitemek (pl. GtkToolButton-ok).

A kevesebb több volna, 
ráadásul ezek közt zavaró eltérések vannak,
az 1. esetben csak nyakatekert módon lehet ikont tenni a buttonba,
a 3. esetben érthetetlen jelenségek vannak,
stb.

#endif

******************************************************************************
class gtktwostateimagelabel(gtkhbox)
    method initialize
    attrib state
    attrib image
    attrib label
    attrib active_state_text
    attrib passive_state_text
    method set_state


static function gtktwostateimagelabel.initialize(this,state,text1,text2)
    this:gobject:=gtk.hbox.new(.f.,0)
    this:state:=state!=.f.
    this:active_state_text:=text1
    this:passive_state_text:=text2
    this:set_state(this:state)
    return this
    

static function gtktwostateimagelabel.set_state(this, state)

    this:state:=state

    if( this:image!=NIL )
        this:remove(this:image)
        this:image:=NIL
    end
    if( this:label!=NIL )
        this:remove(this:label)
        this:label:=NIL
    end

    if( state )
        this:label:=gtklabelNew(this:active_state_text)
        this:image:=gtkimageNew_from_stock("gtk-yes",1)
    else
        this:label:=gtklabelNew(this:passive_state_text)
        this:image:=gtkimageNew_from_stock("gtk-no",1)
    end
    
    this:pack_start(this:image, .f., .f., 3)
    this:pack_start(this:label, .f., .f., 3)
    this:image:show
    this:label:show
    gtk.main_stabilize()

******************************************************************************
