
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

****************************************************************************   
function _zedit_loop(this)

local key

local kmark:={K_ALT_END,K_ALT_HOME,K_ALT_PGDN,K_ALT_PGUP,;
              K_ALT_RIGHT,K_ALT_LEFT,K_ALT_UP,K_ALT_DOWN,;
              K_ALT_C,K_ALT_X,K_ALT_V,;
              K_F3,K_ALT_F3,K_F4,K_ALT_F4,K_F6,K_SH_F6}

local screen              
              
    if( this:actrow>len(this:atxt) )

        //itt újrapozícionáljuk az editort,
        //ez akkor szükséges, ha a history
        //adatai nem érvényesek, mert pl.
        //kicserélődött a filé

        this:ctrlpgup()
    end

    this:display()
    
    while(.t.)

        if( valtype(this:headerblk)=="B" )
            eval(this:headerblk,this)
        end
        
        setpos(this:top+this:winrow,this:left+this:wincol)
        
        key:=inkey(0)
        //key:=inkeyex(0,1,.f.) //wtime,cursor,translation
        
        if( valtype(this:keymapblk)=="B" )
            key:=eval(this:keymapblk,key)
        end
        
        if( this:markflg .and. 0==ascan(kmark,key) )
            this:markflg:=.f.
            this:display()
        end
        

        if( key==K_ESC )
            return K_ESC

        elseif( key==K_F1 )    
            alert(zversion())

        elseif( key==K_F10 )    
            return K_F10

        elseif( key==K_F2 )    
            this:save

        elseif( key==K_F3 )    
            this:search()

        elseif( key==K_ALT_F3 )    
            this:search("i")
 
        elseif( key==K_SH_F3 )    
            this:searchagain()

        elseif( key==K_CTRL_F3 )    
            this:searchagain("p")

        elseif( key==K_F7 )    
            #ifndef _UNIX_
                run ("start z "+this:clipfile+" -r")
            #else
                run ("z "+this:clipfile+" -r &")
            #endif

        elseif( key==K_F9 )    
            this:diff
            
        elseif( key==K_DOWN )    
            this:down()

        elseif( key==K_UP )    
            this:up()

        elseif( key==K_PGDN )    
            this:pagedown()

        elseif( key==K_PGUP )    
            this:pageup()

        elseif( key==K_CTRL_PGDN )    
            this:ctrlpgdn()

        elseif( key==K_CTRL_PGUP )    
            this:ctrlpgup()

        elseif( key==K_RIGHT )  
            this:moveright()  

        elseif( key==K_LEFT )    
            this:moveleft()  

        elseif( key==K_HOME )    
            this:home()  

        elseif( key==K_END )    
            this:end()  


        elseif( key==K_ALT_RIGHT )    
            this:markright()

        elseif( key==K_ALT_LEFT )
            this:markleft() 

        elseif( key==K_ALT_END )    
            this:markend()

        elseif( key==K_ALT_HOME )
            this:markhome() 

        elseif( key==K_ALT_DOWN )    
            this:markdown()

        elseif( key==K_ALT_UP )
            this:markup()

        elseif( key==K_ALT_PGDN )    
            this:markpgdn()

        elseif( key==K_ALT_PGUP )
            this:markpgup() 

        elseif( key==K_ALT_C )    
            this:copy()

        elseif( key==K_ALT_R )    
            this:markmode:="RECT"

        elseif( key==K_ALT_W )    
            this:markmode:="CONT"


        elseif( this:modflg )
     

            if( key==K_DEL )
                this:delete()
                this:changed:=.t.
 
            elseif( key==K_BS )
                this:backspace()
                this:changed:=.t.
 
            elseif( key==K_CTRL_Y )    
                this:delline()
                this:changed:=.t.
 
            elseif( key==K_ENTER )    
                this:enter()
                this:changed:=.t.
 
            elseif( key==K_TAB )
                this:tab()
                this:changed:=.t.
 
            elseif( key==K_ALT_V )    
                this:paste()
                this:changed:=.t.
 
            elseif( key==K_ALT_X )    
                this:cut()
                this:changed:=.t.
 
            elseif( key==K_F6 )    
                this:tolower
                this:changed:=.t.
 
            elseif( key==K_SH_F6 )    
                this:toupper
                this:changed:=.t.

            elseif( key==K_F4 )    
                this:replace()

            elseif( key==K_ALT_F4 )    
                this:replace("i")
 
            elseif( key==K_SH_F4 )    
                this:replaceagain()

            elseif( key==K_CTRL_F4 )    
                this:replaceagain("p")
 
            elseif( 32<=key )
                this:inschar(key)
                this:changed:=.t.
            
            end
        end
    end

    return NIL  


****************************************************************************   

