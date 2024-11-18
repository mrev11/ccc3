
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

// Hoare-fele particionalas
// hasonlo a stackre atirt rekurziohoz
// de stack helyett a threadpool queue-jaba teszi a jobot

#include "qsort.ch"


static pool:=threadpoolNew(8)
static sort:=(|*|qsort(*))


****************************************************************************
function qsort_mt(*)
     ?? "qsort_mt"::padr(16)
   qsort1(*)


static function qsort1(*)
    pool:addjob({sort,*})
    pool:wait

// mukodik, de lassabb, mint egy szalu valtozat


****************************************************************************
static function qsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block


local q

    while( p+ISORT_TRESHOLD<r )
        q:=qsplit(a,p,r,blk)

        if( q-p>r-q)
            pool:addjob( {sort,a,p,q,blk} )
            p:=q+1
        else
            pool:addjob( {sort,a,q+1,r,blk} )
            r:=q
        end
    end

    if( p<r )
        isort(a,p,r,blk)
    end

****************************************************************************
static function qsplit(a,p,r,blk)

local i:=p-1
local j:=r+1
local pivot:=pivot(a,p,r-1,blk) // utolso kihagyva!

    while( .t. )
        while( 0>compare(a[++i],pivot,blk) ); end
        while( 0<compare(a[--j],pivot,blk) ); end
        if( i>=j )
            return j
        end
        swap(a,i,j)
    next


****************************************************************************
