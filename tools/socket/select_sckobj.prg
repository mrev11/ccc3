
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

//select socket objektumokra
//(visszavezetve az fd-ken mukodo selectre)

*****************************************************************************
function select_sckobj(rd,wr,ex,wt)

local fdrd,fdwr,fdex,n,x,result

    if( rd!=NIL )
        fdrd:=array(len(rd))
        for n:=1 to len(rd)
            fdrd[n]:=rd[n]:fd
        next
    end

    if( wr!=NIL )
        fdwr:=array(len(wr))
        for n:=1 to len(wr)
            fdwr[n]:=wr[n]:fd
        next
    end

    if( ex!=NIL )
        fdex:=array(len(ex))
        for n:=1 to len(ex)
            fdex[n]:=ex[n]:fd
        next
    end

    result:=select_sckdesc(fdrd,fdwr,fdex,wt)

    n:=1    
    while( n<=len(rd) )
        if( 0>=(x:=ascan(fdrd,rd[n]:fd)) )
            xdel(rd,n)
        else
            n++
        end
    end

    n:=1    
    while( n<=len(wr) )
        if( 0>=(x:=ascan(fdwr,wr[n]:fd)) )
            xdel(wr,n)
        else
            n++
        end
    end

    n:=1    
    while( n<=len(ex) )
        if( 0>=(x:=ascan(fdex,ex[n]:fd)) )
            xdel(ex,n)
        else
            n++
        end
    end
    
    return result

*****************************************************************************
static function xdel(a,x)
    adel(a,x)
    asize(a,len(a)-1)

*****************************************************************************
