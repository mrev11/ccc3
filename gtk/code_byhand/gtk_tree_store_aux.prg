
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

namespace gtk.tree_store

*******************************************************************************
function new_array_index(a)  //array-indexeket tárol

//Ez NEM TUD interaktívan KERESNI.

local iter:=gtk.tree_iter.new()
local store:=gtk.tree_store.new("I")
local i,length:=if(valtype(a)=="A",len(a),a)
    for i:=1 to length
        gtk.tree_store.append(store,iter)
        gtk.tree_store.set(store,iter,i)
    end
    gtk.tree_iter.free(iter)
    return store
    
*******************************************************************************
function new_array_data(a)  //array-adatokat tárol

//Ez TUD interaktívan KERESNI.
//Amúgy nem különösebben hasznos,
//mert minek másolatot csinálni az adatokból,
//mindenesetre mutatja, mit tárol egy tree_store.

local iter:=gtk.tree_iter.new()
local store//:=gtk.tree_store.new("I")
local i,length:=len(a)
local types:="",t

    for i:=1 to len(a[1])
        t:=valtype(a[1][i])
        if( t=="N" )
            types+="I" //lehetne "D", de nem tudjuk megkülönböztetni
        elseif( t=="C" )
            types+="S" //string
        elseif( t=="L" )
            types+="B" //boolean
        elseif( t=="P" )
            types+="O" //gobject
        elseif( t=="O" )
            types+="O" //gobject
        else
            types+="S" //hiba?
        end
    next
    
    store:=gtk.tree_store.new(types)
    for i:=1 to length
        gtk.tree_store.append(store,iter)
        gtk.tree_store.set(store,iter,a[i])
    end
    gtk.tree_iter.free(iter)
    return store
    
*******************************************************************************

