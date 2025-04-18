
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

******************************************************************************************
function hsort(*)
    ?? "hsort"::padr(16)
    heapsort(*)

******************************************************************************************
function hsort_b(*)
    ?? "hsort_b"::padr(16)
    heapsort_with_bounce(*)


******************************************************************************************
static function heapsort_with_bounce(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local count:=r-p+1
local start:=int(count/2)
local final:=count

    while( final>1 )
        if( start>0 )
            --start
        else
            --final
            swap(a,final+p,p)
        end
        shiftdown(a, start, final, blk)
    end


function shiftdown(a, start, final, blk)
local j:=leafsearch(a,start,final,blk)
    while( 0<compare(a[start+1],a[j+1],blk) )
        j:=parent(j)
    end
    while( j>start )
        swap(a,start+1,j+1)
        j:=parent(j)
    end


function leafsearch(a,start,final,blk)
local j:=start
    while( rightchild(j)<final )
        if( 0<compare(a[rightchild(j)+1],a[leftchild(j)+1],blk) )
            j:=rightchild(j)
        else
            j:=leftchild(j)
        end
    end
    if( leftchild(j)<final )
        j:=leftchild(j)
    end
    return j



******************************************************************************************
static function heapsort(a,p:=1,r:=len(a),blk)

// a    : array to sort
// p    : start index
// r    : final index
// blk  : compare block

local count:=r-p+1
local start:=int(count/2)
local final:=count
local root,child

    while( final>1 )
        if( start>0 )
            --start
        else
            --final
            swap(a,final+p,p)
        end

        root:=start
        while( leftchild(root)<final )
            child:=leftchild(root)
            if( child+1<final .and. 0>compare(a[child+p],a[child+p+1],blk) )
                ++child
            end

            if( 0>compare(a[root+p],a[child+p],blk) )
                swap(a,p+root,p+child)
                root:=child
            else
                exit
            end
        end
    end

// 0 based indexekkel szamolunk
// amikor azonban tenylegesen indexelunk
// akkor mindig hozzaadunk az indexhez p-t



******************************************************************************************
static function leftchild(x)
    return 2*x+1

static function rightchild(x)
    return 2*x+2

static function parent(x)
    return int((x-1)/2)

******************************************************************************************
