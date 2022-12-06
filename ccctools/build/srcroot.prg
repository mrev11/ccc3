
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


****************************************************************************
function srcroot()

local srcroot,d,n
 
    if( !empty(srcroot:=buildenv_src()) )

        if( !right(srcroot,1)$"/\"  )
            srcroot+=dirsep()
        end
        
        if( s_srcdir()==NIL )
            s_srcdir(".")
        end

        d:=xsplit(s_srcdir(),",;")
        
        s_srcdir("")
        for n:=1 to len(d)
            if( left(d[n],1) $ "/\" )
                s_srcdir(s_srcdir()+d[n]+";") //abszolút path 1.2.17
            else
                s_srcdir(s_srcdir()+srcroot+d[n]+";")
            end
        next
        

        if( s_incdir()!=NIL )

            d:=xsplit(s_incdir(),",;")
        
            s_incdir("")
            for n:=1 to len(d)
                if( left(d[n],1) $ "/\" )
                    s_incdir(s_incdir()+d[n]+";") //abszolút path 1.2.17
                else
                    s_incdir(s_incdir()+srcroot+d[n]+";")
                end
            next
        end
    end
    
    return NIL
 

****************************************************************************
