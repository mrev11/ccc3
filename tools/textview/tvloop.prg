
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
