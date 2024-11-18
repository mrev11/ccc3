
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

// Rendezettseg elleni vedelem: veletlen pivot valasztas
// Egyenlo elemek elleni vedelem: harom reszre osztas (lt,eq,gt)


#include "qsort.ch"

static depth:=0
static maxdepth:=0

****************************************************************************
function qsort_3(*)
    ?? "qsort_3"::padr(16)
    qsort(*)
    //?? " maxdepth",maxdepth

****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block


local lt,gt

    if( ++depth>maxdepth )
        maxdepth:=depth
    end

    while( p+ISORT_TRESHOLD<r )
        qsplit(a,p,r,@lt,@gt,blk)

        if( lt-p<r-gt )
            qsort(a,p,lt,blk)
            p:=gt
        else
            qsort(a,gt,r,blk)
            r:=lt
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end
    
    --depth


****************************************************************************
static function qsplit(a,p,r,q1,q2,blk)

local lt:=p
local eq:=p
local gt:=r
local pivot 
local cmp

    pivot:=pivot(a,p,r,blk)

    while( eq<=gt)
        cmp:=compare(a[eq],pivot,blk)
        if( cmp<0 )
            swap(a,eq,lt)
            lt++
            eq++
        elseif( cmp>0 )
            swap(a,eq,gt)
            gt--
        else
            eq++
        end
    next

#ifdef XDEBUG
    ? pivot,;
      "lt="+lt::str::alltrim,;
      "eq="+eq::str::alltrim,;
      "gt="+gt::str::alltrim,;
      a[p..lt-1],a[lt..eq-1],a[eq..r]
#endif

    q1:=lt-1   // utolso kisebb
    q2:=eq     // elso nagyobb


****************************************************************************
