
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
function textview.loop(this)

local key
              
    this:display()
    
    while(.t.)

        if( valtype(this:headerblk)=="B" )
            eval(this:headerblk,this)
        end
        
        setpos(this:top+this:winrow,this:left+this:wincol)
        
        keyboard("")
        key:=inkey(0)
        
        if( key==K_ESC )
            return K_ESC
 
        elseif( key==K_F3 )    
            this:search()

        elseif( key==K_SH_F3 )    
            this:searchagain()

        elseif( key==K_CTRL_F3 )    
            this:searchagain("p")

       
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
        end
    end


****************************************************************************   
