
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

//sajat alert

#include "inkey.ch"

#define MAXW  (maxcol()-10)
#define MAXH  (maxrow()-8)

*****************************************************************************    
function alert(argtxt,argalt)     

local txt, alt:={}
local wtxt:=0,walt:=0
local s,w,a,n,i
local savscr,top,lef,bot,rig
local color,cursor
local key,choice,keyexit


    //txt meretezese
    
    if( empty(argtxt) )
        return 0
    end

    txt:=split(argtxt,";")
    
    for n:=1 to len(txt)
  
        s:=alltrim(txt[n])
        w:=len(s)

        if( w>MAXW )
            a:=wrap(s)
            txt[n]:=atail(a)
 
            for i:=len(a)-1 to 1 step -1
                asize(txt,len(txt)+1)  
                ains(txt,n)  
                txt[n]:=a[i]
            next

            s:=alltrim(txt[n]) 
            w:=len(s)
        end

        if( wtxt<w )
            wtxt:=w
        end

        txt[n]:=s
    next

    if( len(txt)>MAXH )
        asize(txt,MAXH)
    end
    
    //most txt-nek legfeljebb MAXH-sora van,
    //es egyik sora sem hosszabb MAXW-nel



    //alt meretezese
    
    if( argalt!=NIL )
        for n:=1 to len(argalt)   
    
            a:=alltrim(argalt[n])
            w:=len(a)+if(n==1,6,4)  //__*alt*__*alt*__*alt*__*alt*__
                
            if( walt+w>MAXW )
                exit
            else
                walt+=w
                aadd(alt,a) 
            end
        next
    end

    if( empty(alt) )
        alt:={"OK"}
        walt:=8
    end     

    //most alt-nak van legalabb 1 alternativaja,
    //a megmaradt alternativak osszhossza nem tobb MAXW-nel
    

    
    //doboz pozicionalas
    
    top:=int((maxrow()-len(txt)-3)/2)
    bot:=top+len(txt)+3
    lef:=int((maxcol()-max(wtxt,walt)-4)/2)
    rig:=lef+max(wtxt,walt)+4
    
    color:=setcolor(zcolor_1())
    cursor:=setcursor(0)
    savscr:=drawbox(top,lef,bot,rig,2)
    
    tdisp(top,lef,bot,rig,txt)    
    choice:=1
    keyexit:=.f.

    while( !keyexit )

        choice:=max(min(choice,len(alt)),1)
        adisp(top,lef,bot,rig,alt,walt,choice)    

        key:=inkey(0)
        
        if( key==K_ESC )
            choice:=0
            keyexit:=.t.

        elseif( key==K_ENTER )
            keyexit:=.t.

        elseif( key==K_SPACE )
            keyexit:=.t.

        elseif( key==K_LEFT )
            choice--

        elseif( key==K_RIGHT )
            choice++

        else
            for n:=1 to len(alt)
            
                if( upper(left(alt[n],1))==upper(chr(key)) )
                    choice:=n
                    keyexit:=.t.
                    exit
                end
            next
        end
    end
    
    setcursor(cursor)
    setcolor(color)
    restscreen(top,lef,bot,rig,savscr)

    return choice


*****************************************************************************    
static function tdisp(top,lef,bot,rig,txt)
local w:=rig-lef-2,n
    
    for n:=1 to len(txt)
        @ top+n,lef+2 say padc(txt[n],w)
    next
    return NIL


*****************************************************************************    
static function adisp(top,lef,bot,rig,alt,walt,x) 
local n, s:=(rig-lef-walt)/2

    for n:=1 to len(alt) 
        @ bot-1,lef+2+s say  " "+alt[n]+" " color if(n==x,zcolor_3(),zcolor_1())
        s+=len(alt[n])+4
    next
    return NIL

 
*****************************************************************************    
static function wrap(s) 

local a:={}, x:="", n

    s:=split(s," ") 
    
    for n:=1 to len(s)
                
        if( len(x)+1+len(s[n])<MAXW )
            x+=" "+s[n]
        else
            if( !empty(x) )
                aadd(a,x)
            end
            x:=left(s[n],MAXW) 
        end
    next

    if( !empty(x) )
        aadd(a,x)
    end
    
    return a


*****************************************************************************    
 