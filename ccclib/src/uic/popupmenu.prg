
#include "box.ch"
#include "inkey.ch"


******************************************************************************************
class popupmenu(object)

    attrib  menu
    attrib  top
    attrib  left
    attrib  bottom
    attrib  right

    attrib  upper
    attrib  choice

    attrib  color
    attrib  border

    method  initialize
    method  loop


******************************************************************************************
function popupmenu.initialize(this,menu,top,lef,bot:=9999,rig:=9999)

local color:=brwColor()

    this:menu   :=menu
    this:top    :=int(top)
    this:left   :=int(lef)
    this:bottom :=int(bot)
    this:right  :=int(rig)

    this:top::=max(0)
    this:top::=min(maxrow()-2)
    this:left::=max(0)
    this:left::=min(maxcol()-2)

    this:upper:=1
    this:choice:=1
    this:color:=color::logcolor(2)+","+color::logcolor(4)
    this:border:=B_SINGLE

    return this

//# BRWCOLOR=w/n,n/rg,n/355,w+/022
//# szinek:
//# 1 - a browse alapszine
//# 2 - a popup menuk alapszine               (default: 1 inverze)
//# 3 - a browse kiemelt soranak szine        (default: 1 inverze)
//# 4 - a popup menuk kiemelt soranak szine   (default: 1)


******************************************************************************************
function popupmenu.loop(this)

local saved_color:=setcolor()
local saved_cursor:=setcursor(0)
local saved_pos:={row(),col()}

local n,width,visible,screen,key
local top,lef,bot,rig
local shift:=.t.

    if( this:menu::empty )
        return 0
    end

    width:=0
    for n:=1 to len(this:menu)
        width::=max(this:menu[n]::len)
    next
    width::=min(this:right-this:left-1)
    this:left::=min(maxcol()-width-1)
    this:left::=max(0)

    dispbegin()
    while( shift )
        shift:=.f.

        top:=this:top
        lef:=this:left
        bot:=this:bottom
        rig:=this:left+width+1

        // TOP
        top::=max(0)                                // >= 0
        top::=min(maxrow()-2)                       // <= maxrow()-2

        // BOTTOM
        bot::=max(top+2)                            // >= top+2
        bot::=min(maxrow())                         // <= maxrow()
        bot::=min(top+this:menu::len+1)             // <= top+this:menu::len+1

        // LEFT
        lef::=max(0)                                // >= 0
        lef::=min(maxcol()-2)                       // <= maxcol()-2

        // RIGHT
        rig::=max(lef+2)                            // >= lef+2
        rig::=min(maxcol())                         // <= maxcol()
        rig::=min(lef+width+1)                      // <= lef+width+1

        
        visible:=bot-top-1                          // LATHATO ELEMEK MAX SZAMA

        this:choice::=max(1)                        // >= 1
        this:choice::=min(len(this:menu))           // <= len(this:menu)

        this:upper::=min(this:choice)               // <= this:choice
        this:upper::=max(this:choice-visible+1)     // >= this:choice   -visible+1
        this:upper::=min(this:menu::len-visible+1)  // <= this:menu::len-visible+1

        screen:=savescreen(top,lef,bot,rig)
        draw(this,top,lef,bot,rig)
        dispend()

        while(.t.)
            key:=inkey(0)

            if( key==K_ESC  )
                this:choice:=0
                exit

            elseif( key==K_LEFT )
                this:choice:=0
                exit

            elseif( key==K_RIGHT )
                this:choice:=0
                exit

            elseif( key==K_ENTER )
                exit

            elseif( key==K_SH_UP )
                if( top>0 )
                    this:top--
                    this:bottom--
                    shift:=.t.
                    exit
                end

            elseif( key==K_SH_DOWN )
                if( top<maxrow()-2 )
                    this:top++
                    this:bottom++
                    shift:=.t.
                    exit
                end

            elseif( key==K_SH_LEFT )
                if( lef>0 )
                    this:left--
                    this:right--
                    shift:=.t.
                    exit
                end

            elseif( key==K_SH_RIGHT )
                if( lef<maxcol()-2 )
                    this:left++
                    this:right++
                    shift:=.t.
                    exit
                end

            elseif( key==K_DOWN )
                if( this:choice<this:menu::len )
                    this:choice++
                    if( this:choice-this:upper+1 > visible )
                        this:upper++
                    end
                    draw(this,top,lef,bot,rig)
                end

            elseif( key==K_PGDN )
                this:choice+=visible
                this:choice::=min(this:menu::len)
                if( this:choice-this:upper+1 > visible )
                    this:upper:=this:choice-visible+1
                end
                draw(this,top,lef,bot,rig)

            elseif( key==K_END )
                this:choice:=this:menu::len
                if( this:choice-this:upper+1 > visible )
                    this:upper:=this:choice-visible+1
                end
                draw(this,top,lef,bot,rig)


            elseif( key==K_UP )
                if( this:choice>1 )
                    this:choice--
                    if( this:choice < this:upper )
                        this:upper--
                    end
                    draw(this,top,lef,bot,rig)
                end

            elseif( key==K_PGUP )
                this:choice-=visible
                this:choice::=max(1)
                if( this:choice<this:upper )
                    this:upper:=this:choice
                end
                draw(this,top,lef,bot,rig)

            elseif( key==K_HOME )
                this:choice:=1
                this:upper:=1
                draw(this,top,lef,bot,rig)
            end
        end

        dispbegin()
        restscreen(top,lef,bot,rig,screen)
    end
    dispend()

    setcolor(saved_color)
    setcursor(saved_cursor)
    setpos(saved_pos[1],saved_pos[2])

    return this:choice


******************************************************************************************
static function draw(this,top,lef,bot,rig)
local row,col,color,item

    //?  "  cho="+this:choice::str::alltrim
    //?? "  upr="+this:upper::str::alltrim 
    //?? "  top="+top::str::alltrim 
    //?? "  bot="+bot::str::alltrim

    dispbegin()
    color:=this:color::split
    setcolor(color[1])
    drawbox(top,lef,bot,rig,this:border)

    col:=lef+1
    for row:=top+1 to bot-1
        item:=this:upper-1+row-top
        if( item==this:choice  )
            @ row,col say this:menu[item]::padr(rig-lef-1) color color[2]
        else
            @ row,col say this:menu[item]::padr(rig-lef-1)
        end
    next
    dispend()


******************************************************************************************
