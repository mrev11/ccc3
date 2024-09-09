
#include "box.ch"
#include "inkey.ch"


******************************************************************************************
class popupmenu(object)

    attrib  menu
    attrib  top
    attrib  lef
    attrib  bot
    attrib  rig

    attrib  choice
    attrib  topitem

    attrib  color
    attrib  border

    method  initialize
    method  loop


******************************************************************************************
function popupmenu.initialize(this,menu,top,lef,bot,rig)

local color:=brwColor()

    this:menu:=menu
    this:top:=int(top)
    this:lef:=int(lef)
    this:bot:=bot|maxrow()
    this:rig:=rig|maxcol()

    this:choice:=1
    this:topitem:=1
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
local n,w:=0,screen,key

    for n:=1 to len(this:menu)
        w::=max(this:menu[n]::len)
    next

    this:bot::=min(this:top+this:menu::len+1)
    this:rig::=min(this:lef+w+1)
    screen:=savescreen(this:top,this:lef,this:bot,this:rig)
    draw(this)

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
            if( this:top>0 )
                dispbegin()
                restscreen(this:top,this:lef,this:bot,this:rig,screen)
                this:top--
                this:bot--
                screen:=savescreen(this:top,this:lef,this:bot,this:rig)
                draw(this)
                dispend()
            end

        elseif( key==K_SH_DOWN )
            if( this:bot<maxrow() )
                dispbegin()
                restscreen(this:top,this:lef,this:bot,this:rig,screen)
                this:top++
                this:bot++
                screen:=savescreen(this:top,this:lef,this:bot,this:rig)
                draw(this)
                dispend()
            end

        elseif( key==K_SH_LEFT )
            if( this:lef>0 )
                dispbegin()
                restscreen(this:top,this:lef,this:bot,this:rig,screen)
                this:lef--
                this:rig--
                screen:=savescreen(this:top,this:lef,this:bot,this:rig)
                draw(this)
                dispend()
            end

        elseif( key==K_SH_RIGHT )
            if( this:rig<maxcol() )
                dispbegin()
                restscreen(this:top,this:lef,this:bot,this:rig,screen)
                this:lef++
                this:rig++
                screen:=savescreen(this:top,this:lef,this:bot,this:rig)
                draw(this)
                dispend()
            end


        // LATHATO ELEMEK MAX SZAMA == this:bot-this:top-1
        // this:choice-this:topitem+1 <= LATHATO ELEMEK MAX SZAMA

        elseif( key==K_DOWN )
            if( this:choice<this:menu::len )
                this:choice++
                if( this:choice-this:topitem+1 > this:bot-this:top-1 )
                    this:topitem++
                end
                draw(this)
            end
 
        elseif( key==K_PGDN )
            this:choice+=this:bot-this:top-1
            this:choice::=min(this:menu::len)
            if( this:choice-this:topitem+1 > this:bot-this:top-1 )
                this:topitem:=this:choice+1-this:bot+this:top+1
            end
            draw(this)

        elseif( key==K_END )
            this:choice:=this:menu::len
            this:topitem:=this:choice+1-this:bot+this:top+1
            draw(this)

        elseif( key==K_UP )
            if( this:choice>1 )
                this:choice--
                if( this:choice < this:topitem )
                    this:topitem--
                end
                draw(this)
            end

        elseif( key==K_PGUP )
            this:choice-=this:bot-this:top-1
            this:choice::=max(1)
            if( this:choice<this:topitem )
                this:topitem:=this:choice
            end
            draw(this)

        elseif( key==K_HOME )
            this:choice:=1
            this:topitem:=1
            draw(this)
        end
    end

    restscreen(this:top,this:lef,this:bot,this:rig,screen)
    setcolor(saved_color)
    setcursor(saved_cursor)

    return this:choice


******************************************************************************************
static function draw(this)
local row,col,color,item

    dispbegin()
    color:=this:color::split
    setcolor(color[1])
    drawbox(this:top,this:lef,this:bot,this:rig,this:border)

    col:=this:lef+1
    for row:=this:top+1 to this:bot-1
        item:=this:topitem-1+row-this:top
        if( item==this:choice  )
            @ row,col say this:menu[item]::padr(this:rig-this:lef-1) color color[2]
        else
            @ row,col say this:menu[item]::padr(this:rig-this:lef-1)
        end
    next
    dispend()


******************************************************************************************
