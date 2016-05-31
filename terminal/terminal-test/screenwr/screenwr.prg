
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

*****************************************************************************
function screen_worm(wait_time:=120,text)
local key
    rand(seconds())
    if( (key:=inkey(wait_time))==0 )
        key:=screen(text)
    end
    keyboard (chr(key))

*****************************************************************************
static function screen(text)
local screen:=savescreen(0,0,maxrow(),maxcol())
local cursor:=setcursor(0)
local logo:=tail(2)+if(text==NIL,"",text)+" "
local r,p:=random()%8
local s:=random()%maxrow(),o:=random()%maxcol()
local x:={{s,o}},n,key

    cls

    while( (key:=inkey(0.2))==0 )

        for n:=len(x) to 1 step -1
            @ x[n][1],x[n][2] say substr(logo,n,1)
        next

        while(.t.)
            if( 7<(r:=random()%100) )
                r:=p
            end
            if( (r+4)%8==p )
                loop
            end
        
            s:=x[1][1]
            o:=x[1][2]
       
            if( r==0 )    ;o++    
            elseif( r==1 );s--;o++
            elseif( r==2 );s--
            elseif( r==3 );s--;o--
            elseif( r==4 );o--    
            elseif( r==5 );s++;o--
            elseif( r==6 );s++
            elseif( r==7 );s++;o++
            end

            if( s<0 .or. maxrow()<s .or. o<0 .or. maxcol()<o )
                loop
            end  
    
            p:=r
            exit
        end


        if( len(x)<len(logo) )
            aadd(x,{NIL,NIL})
        end

        for n:=len(x) to 2 step -1
            x[n][1]:=x[n-1][1]
            x[n][2]:=x[n-1][2]
        next

        x[1]:={s,o}  
    end

    setcursor(cursor)
    restscreen(0,0,maxrow(),maxcol(),screen)
    return key
        

*****************************************************************************

#ifdef _CCC3_
static function tail(n)        
    return  replicate(chr(0x2588),n)+;
            replicate(chr(0x2593),n)+;
            replicate(chr(0x2592),n)+;
            replicate(chr(0x2591),n)
#endif


#ifdef _CCC2_
static function tail(n)        
    return  replicate(chr(254),n)+;
            replicate(chr(249),n)+;
            replicate(chr(159),n)+;
            replicate(chr(157),n)
#endif
 

*****************************************************************************
