
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

#include "xtrans.ch"

*****************************************************************************
function define(line)

local toklist:=tokenize(alltrim(line))
local lentok:=len(toklist),n,i
local left,right
local ll,lr,tt,token
local strflag:=.f.

    if( lentok<1 ) //ez mi?
        error(@"Invalid #define")
    
    elseif( lentok==1 ) //szimbólum definíció
        left:={toklist[1]}
        right:={} 
        
    elseif( toklist[2]==a"("  ) //paraméteres makró
        //baloldal

        left:={toklist[1],a"("}
        for n:=3 to lentok
            if( toklist[n]==a" " )
                //kihagyjuk
            elseif( toklist[n]==a")" ) 
                aadd(left,a")")
                exit
            else
                aadd(left,toklist[n])
            end
        next

        if( n>lentok )  
            //nem záródott le a paraméterlista 
            error(@"Invalid #define")
        end

        if( n<lentok .and. toklist[n+1]==a" " )
            //paraméterlista utáni esetleges blank
            n++
        end
        
        //jobboldal

        right:=array(lentok-n)
        for i:=n+1 to lentok
            right[i-n]:=toklist[i]
        next

        ll:=len(left)
        lr:=len(right)
        
        for n:=1 to lr
            token:=right[n]
            tt:=left(token,1)

            if( isalpha(tt) .or. tt==a"_" )
                for i:=3 to ll step 2
                    if( token==left[i] )
                        if( strflag )
                            right[n-1]:=a" "
                            right[n]:=markervalue(RESULT_NORMALSTR,i)
                        else
                            right[n]:=markervalue(RESULT_REGULAR,i)
                        end
                        exit
                    end
                next
            end
            strflag:=token==a"#"
        next
        
        for n:=3 to ll-1 step 2
            left[n]:=markervalue(MATCH_REGULAR,0) 
        next

    else //nem paraméteres makró 

        left:={toklist[1]}

        n:=if(!toklist[2]==a" ",2,3) //jobboldal első tokene 

        right:=array(lentok-n+1)
        for i:=n to lentok
            right[i-n+1]:=toklist[i]
        next
    end

    rule_df_add({left,right,NIL})
    return NIL    


*****************************************************************************

 