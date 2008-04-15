
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

function _zedit_clipboard(this,clip)

local tclip,n,n1

    if( clip==NIL )

        tclip:=memoread(this:clipfile)

        if( tclip=="" )
            clip:=NIL
        else
            clip:={}
            tclip:=strtran(tclip,chr(13),"")

            n:=1
            while( 0<(n1:=at(chr(10),tclip,n)) )
                aadd(clip,substr(tclip,n,n1-n))
                n:=n1+1
            end
            aadd(clip,substr(tclip,n))
        end

    elseif( valtype(clip)=="A" )
    
        tclip:=""
        for n:=1 to len(clip)
            if( n>1 )
                tclip+=endofline()
            end
            tclip+=clip[n]
        next

        memowrit(this:clipfile,tclip)

    else
        memowrit(this:clipfile,clip:="") 

    end
    
    return clip

    





    


