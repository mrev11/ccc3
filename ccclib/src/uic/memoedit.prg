
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

#ifdef MEMOEDIT_DEBUG

#include "box.ch"

function;
   main(fspec,r,c,wr,wc)

local top:=10
local left:=10
local bottom:=maxrow()-5
local right:=maxcol()-15
local screen,txt

    if(fspec==NIL)
        fspec:="proba.txt"
    end

    if( r!=NIL )
        r:=val(r)
    end

    if( c!=NIL )
        c:=val(c)
    end

    if( wr!=NIL )
        wr:=val(wr)
    end

    if( wc!=NIL )
        wc:=val(wc)
    end
    
    screen:=DrawBox(top,left,bottom,right,B_SINGLE_DOUBLE) 

    txt:=memoedit( memoread(fspec),;
                   top+1,left+1,bottom-1,right-1,;
                   .t.,;       //lEditMode
                   NIL,;       //userfunc
                   256,;       //linesize
                   4,;         //tabsize
                   r,c,;       //textbuffer row/col
                   wr,wc)      //window row/col

    restscreen(top,left,bottom,right,screen)
    return NIL

#endif

**********************************************************************   
function memoedit(txt, top,left,bottom,right,;
                       modflg,usrfnc,linsiz,tabsiz,;
                       bufrow,bufcol,winrow,wincol)

local sftrow,sftcol

    if( bufrow==NIL )
        bufrow:=1 //compatibility!
    end        
    if( bufcol==NIL )
        bufcol:=0 
    end        
    if( winrow==NIL )
        winrow:=0 
    end        
    if( wincol==NIL )
        wincol:=0 
    end        
    
    winrow:=max(0,min(winrow,bottom-top))
    wincol:=max(0,min(wincol,right-left))
                     
    sftrow:=bufrow-1-winrow 
    sftcol:=bufcol-wincol 
    
    if( sftrow<0 )
        sftrow:=0
        winrow:=bufrow-1
    end

    if( sftcol<0 )
        sftcol:=0
        wincol:=bufcol
    end
    
    return memoedit1( txt,;
                      top,left,bottom,right,modflg,;
                      sftrow,sftcol,winrow,wincol )


**********************************************************************   
static function memoedit1(txt,top,left,bottom,right,modflg,sftrow,sftcol,currow,curcol)

//local atxt:=split(txt,chr(10)) 
local atxt:=lines(txt) //split a nagy filékre lassú 

local width:=right-left+1
local height:=bottom-top+1
local actrow,actcol,n
local key, line, rlen, sftprv

    if( empty(atxt) )
        atxt:={""}
    end

    while( 1+sftrow+currow>len(atxt) .and. sftrow>0 )
        sftrow--
    end

    while( 1+sftrow+currow>len(atxt) .and. currow>0 )
        currow--
    end


    for n:=1 to len(atxt)
        atxt[n]:=strtran(atxt[n],chr(13),"")
        atxt[n]:=strtran(atxt[n],chr(9),space(4))
    next
    
    if( modflg==NIL )
        modflg:=.t.
    end

    display(atxt,top,left,bottom,right,sftrow,sftcol)
    
    
    while(.t.)

        actrow:=1+sftrow+currow
        actcol:=1+sftcol+curcol

        setpos(top+currow,left+curcol)
        key:=inkey(0)

        if( key==K_ESC )
            return txt


        elseif( key==K_CTRL_W )    
            txt:=""
            if( len(atxt)>1 .or. len(atxt[1])>0 )
                for n:=1 to len(atxt)
                    txt+=atxt[n]+endofline()
                next
            end
            return txt


        elseif( key==K_DOWN )    
            if( actrow<len(atxt) )
                if( currow<height-1 )
                    currow++
                else
                    sftrow++
                    scroll(top,left,bottom,right,1)
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow+1)
                end
            end


        elseif( key==K_PGDN )    
            sftprv:=sftrow

            if( currow<height-1 )
                currow:=height-1
            else
                sftrow+=height
            end
            actrow:=1+sftrow+currow
            if( actrow>len(atxt) )
                sftrow+=len(atxt)-actrow
                if( sftrow<0 )
                    currow+=sftrow
                    sftrow:=0
                end
            end

            if( sftprv!=sftrow )
                display(atxt,top,left,bottom,right,sftrow,sftcol)
            end


        elseif( key==K_UP )    
            if( actrow>1 )
                if( currow>0 )
                    currow--
                else
                    sftrow--
                    scroll(top,left,bottom,right,-1)
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow-1)
                end
            end


        elseif( key==K_PGUP )    
            sftprv:=sftrow

            if( currow>0 )
                currow:=0
            else
                if( sftrow>=height )
                    sftrow-=height
                else
                    sftrow:=0
                end
            end
            if( sftprv!=sftrow )
                display(atxt,top,left,bottom,right,sftrow,sftcol)
            end


        elseif( key==K_RIGHT )    
            if( curcol<width-1 )
                curcol++
            else
                sftcol++
                display(atxt,top,left,bottom,right,sftrow,sftcol)
            end


        elseif( key==K_LEFT )    
            if( actcol>1 )
                if( curcol>0 )
                    curcol--
                else
                    sftcol--
                    display(atxt,top,left,bottom,right,sftrow,sftcol)
                end
            end
            

        elseif( key==K_HOME )    
            curcol:=0
            if( sftcol!=0 )
                sftcol:=0
                display(atxt,top,left,bottom,right,sftrow,sftcol)
            end


        elseif( key==K_END )    
            sftprv:=sftcol
            
            curcol:=len(atxt[actrow])
            actcol:=curcol+1

            if( curcol>width-1 )
                curcol:=width-1
            elseif( curcol<0 )
                curcol:=0
            end
            sftcol:=actcol-1-curcol

            if( sftprv!=sftcol )
                display(atxt,top,left,bottom,right,sftrow,sftcol)
            end


        elseif( modflg )

            if( key==K_DEL )

                if( actcol<len(atxt[actrow]) )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,1,"")
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)

                elseif( actrow<len(atxt) )
                    line:=atxt[actrow+1]
                    adel(atxt,actrow+1)
                    asize(atxt,len(atxt)-1)
                    atxt[actrow]:=padr(atxt[actrow],actcol-1)+line
                    display(atxt,top,left,bottom,right,sftrow,sftcol)

                elseif( actrow==len(atxt) .and. actcol==len(atxt[actrow]) )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,1,"")
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)
                end

            elseif( key==K_BS )

                if( actcol>1 )

                    if( len(atxt[actrow])>=actcol-1 )
                        atxt[actrow]:=stuff(atxt[actrow],actcol-1,1,"")
                    end
                    
                    if( curcol>0 )
                        curcol--
                        displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)
                    else
                        sftcol--
                        display(atxt,top,left,bottom,right,sftrow,sftcol)
                    end

                elseif( actrow>1 )  //actcol==1 sftcol==0 curcol==0

                    line:=atxt[actrow]
                    adel(atxt,actrow)
                    asize(atxt,len(atxt)-1)
                    
                    if( currow>0 )
                        currow--
                    else
                        sftrow--
                    end
                    actrow--
   
                    actcol:=len(atxt[actrow])+1
                    curcol:=actcol-1

                    if( curcol>width-1 )
                        curcol:=width-1
                    elseif( curcol<0 )
                        curcol:=0
                    end

                    sftcol:=actcol-1-curcol
                    atxt[actrow]+=line

                    display(atxt,top,left,bottom,right,sftrow,sftcol)
                end


            elseif( key==K_CTRL_Y )    
                adel(atxt,actrow)
                asize(atxt,len(atxt)-1)
                if( len(atxt)<actrow )
                    aadd(atxt,"")
                end
                display(atxt,top,left,bottom,right,sftrow,sftcol)


            elseif( key==K_ENTER )    
                line:=substr(atxt[actrow],actcol)  //ez lesz az új sor
                atxt[actrow]:=left(atxt[actrow],actcol-1) //ez marad a régi sor
                n:=len(atxt[actrow])-len(ltrim(atxt[actrow])) //indentáláshoz

                aadd(atxt,NIL)
                ains(atxt,actrow+1)
                atxt[actrow+1]:=space(n)+line
                sftcol:=0
                curcol:=n
                if( curcol>width-1 )
                    sftcol:=curcol-width+1
                    curcol:=width-1
                end

                if( currow<height-1 )
                    currow++
                else
                    sftrow++
                end

                display(atxt,top,left,bottom,right,sftrow,sftcol)
            

            elseif( key==K_TAB )

                rlen:=len(atxt[actrow])

                if( actcol<=rlen  )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,0,space(4))
                else
                    atxt[actrow]+=space(actcol-rlen-1)+space(4)
                end

                curcol+=4
                actcol+=4
                if( curcol>width-1 )
                    curcol:=width-1
                    sftcol:=actcol-1-curcol
                    display(atxt,top,left,bottom,right,sftrow,sftcol)
                else
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)
                end


            elseif( dispchar(key) )

                rlen:=len(atxt[actrow])

                if( actcol<=rlen  )
                    atxt[actrow]:=stuff(atxt[actrow],actcol,0,chr(key))
                else
                    atxt[actrow]+=space(actcol-rlen-1)+chr(key)
                end

                if( curcol<width-1 )
                    curcol++
                    displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)
                else
                    sftcol++
                   display(atxt,top,left,bottom,right,sftrow,sftcol)
                end
            end
        end
    end

    return NIL  


**********************************************************************   
static function display(atxt,top,left,bottom,right,sftrow,sftcol)

local width:=right-left+1
local n,idx,ltxt:=len(atxt)
local crs:=setcursor(0) //hogy ne villogjon

    for n:=top to bottom
        idx:=n-top+sftrow+1
        if( 0<idx .and. idx<=ltxt )
            @ n,left say padr(substr(atxt[idx],sftcol+1),width)
        else
            @ n,left say space(width)
        end
    next 
    setcursor(crs)
    return NIL


**********************************************************************   
static function displine(atxt,top,left,bottom,right,sftrow,sftcol,actrow)
local width:=right-left+1
    @ top+actrow-sftrow-1,left say padr(substr(atxt[actrow],sftcol+1),width)
    return NIL


**********************************************************************   
static function dispchar(key)
    return 32<=key //.and. key<256 


**********************************************************************   
static function lines(txt)

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            exit
        end
    end

    return asize(a,i)

 
**********************************************************************   

