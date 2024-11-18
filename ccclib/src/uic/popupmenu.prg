
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
#include "inkey.ch"

#ifdef NOTDEFINED

  A popupmenu bal felso sarka (this:top,this:left)-nel lesz.
  Ehhez kepest az egeszet foljebb hozza, ha alul teljesen kilog a terminalbol,
  es lehetoseg szerint balra tolja, ha a menu jobb szele kilog a terminalbol.
  A popupmenu mozgathato a SHIFT-arrow billentyukkel.

  A menuitemek lehetnek:

    1) C: egyszeru text            - a text jelenik meg a menuben
    2) A: array: {text,codeblock}  - a text jelenik meg a menuben
    3) O: popupmenu                - popupmenu:title jelenik meg a menuben

  Navigacio (popup:loop)

    K_ESC       kilep az osszes menubol
    K_LEFT      az utolso menubol visszalep
    K_RIGHT     belep a kivalasztott submenube
    K_ENTER     megvan a vegso eredmeny (kilep), vagy belep a kivalasztott submenube

    K_DOWN      szokasos navigacio
    K_UP        szokasos navigacio
    K_PGDN      szokasos navigacio
    K_PGUP      szokasos navigacio
    K_HOME      szokasos navigacio
    K_END       szokasos navigacio

  Visszateres

    popup:loop == 0    - ha kileptek a  K_ESC vagy K_LEFT billentyukkel
    popup:loop == ch>0 - a kulso menuben kivalasztott elem, ha K_ENTER-rel leptek ki

    Akarhogy is leptek ki, a menukben megmarad az utolso popup:choice attributum.
    Ha K_ENTER egy {text,codeblock} tipusu elemen tortenik, vegrehajtja a blockot.

    Kilepes utan popup:text megadja a kivalasztott elem szoveget.
    Kilepes utan popup:block megadja a kivalasztott elem codeblockjat (ha van).

#endif

******************************************************************************************
class popupmenu(object)

    attrib  title
    attrib  menu
    attrib  top
    attrib  left
    attrib  bottom
    attrib  right

    attrib  upper
    attrib  choice
    attrib  width
    attrib  depth

    attrib  color
    attrib  border

    method  initialize
    method  loop
    method  text
    method  block


******************************************************************************************
function popupmenu.initialize(this,menu:={},top:=0,lef:=0,bot:=9999,rig:=9999)

local color:=brwColor(),n

    this:title  :="*MENU*"
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
    this:width:=0
    this:depth:=0

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

local n,visible,screen,key
local wid,top,lef,bot,rig
local submenu
local shift:=.t.
local result:=0

    if( this:menu::empty )
        return 0
    end

    // foljebb hozza, ha teljesen kilog
    if( this:top>maxrow()-2 )
        this:bottom -= (this:top-maxrow()+2)
        this:top    -= (this:top-maxrow()+2)
    end

    // balrabb hozza, amennyire kell/lehet
    this:width:=0
    for n:=1 to len(this:menu)
        if( this:menu[n]::valtype=="C"  )
            this:width::=max(this:menu[n]::len)
        elseif( this:menu[n]::valtype=="A"  )
            this:width::=max(this:menu[n][1]::len)
        else
            this:width::=max(this:menu[n]:title::len)
        end
    next
    this:width::=min(this:right-this:left-1)
    this:left::=min(maxcol()-this:width-1)
    this:left::=max(0)


    dispbegin()
    while( shift )
        shift:=.f.

        wid:=this:width
        top:=this:top
        lef:=this:left
        bot:=this:bottom
        rig:=this:left+wid+1

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
        rig::=min(lef+wid+1)                        // <= lef+wid+1


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

            if( key==K_ESC )
                // back
                result:=0
                exit

            elseif( key==K_LEFT )
                // back
                result:=0
                exit

            elseif( key==K_RIGHT )
                if( this:menu[this:choice]::valtype$"CA" )
                    // do nothing
                else
                    // enter submenu
                    submenu:=this:menu[this:choice]
                    submenu:top:=top+this:choice-this:upper+2
                    submenu:left:=rig
                    submenu:bottom:=9999
                    submenu:right:=9999
                    submenu:depth:=this:depth+1
                    if( 0<submenu:loop )
                        // done
                        result:=this:choice
                        exit
                    elseif( lastkey()==K_ESC )
                        result:=0
                        exit
                    end
                end

            elseif( key==K_ENTER )
                if( this:menu[this:choice]::valtype$"CA" )
                    // done
                    result:=this:choice
                    exit
                else
                    keyboard(K_RIGHT)
                end



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

    if( this:depth==0 .and. result>0 )
        eval(this:block|{||},this:text)
    end

    return result


******************************************************************************************
static function popupmenu.text(this)
local menuitem
    if( this:choice>0 )
        menuitem:=this:menu[this:choice]
        if(  menuitem::valtype=="C" )
            return menuitem
        elseif(  menuitem::valtype=="A" )
            return menuitem[1]
        else
            return menuitem:text
        end
    end


******************************************************************************************
static function popupmenu.block(this)
local menuitem
    if( this:choice>0 )
        menuitem:=this:menu[this:choice]
        if( menuitem::valtype=="C" )
            return NIL
        elseif( menuitem::valtype=="A" )
            return menuitem[2]
        else
            return menuitem:block
        end
    end


******************************************************************************************
static function draw(this,top,lef,bot,rig)
local row,col,color,item,menuitem,text

#ifdef _CCC3_
local arrow:=chr(0x25b6)
#else
local arrow:=">"
#endif

    dispbegin()
    color:=this:color::split
    setcolor(color[1])
    drawbox(top,lef,bot,rig,this:border)

    col:=lef+1
    for row:=top+1 to bot-1
        item:=this:upper-1+row-top
        menuitem:=this:menu[item]
        if( menuitem::valtype=="C" )
            text:=menuitem::padr(rig-lef-1)
        elseif( menuitem::valtype=="A" )
            text:=menuitem[1]::padr(rig-lef-1)
        else
            text:=menuitem:title::padr(rig-lef-1)+arrow  // arrow beleir a keretbe
        end

        if( item==this:choice  )
            @ row,col say text color color[2]
        else
            @ row,col say text
        end
    next
    dispend()


******************************************************************************************
