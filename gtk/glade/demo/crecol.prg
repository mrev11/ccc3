
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

//egy viszonylag általános column kreáló utility

#define PRINT(x) //? #x, x

**************************************************************************** 
function create_column(title,colidx,picture)

local column:=gtktreeviewcolumnNew()
local renderer:=gtkcellrenderertextNew()
    column:set_title(title)
    column:pack_start(renderer)
    column:set_cell_data_func(renderer,{|c,r,m,i|get_column_data(c,r,m,i,colidx,picture)})
    return column

**************************************************************************** 
static function get_column_data(column,renderer,model,iter,colidx,picture)
local data

    PRINT(column)
    PRINT(renderer)
    PRINT(model)
    PRINT(iter)
    PRINT(colidx)
    PRINT(picture )

    data:=gtk.tree_model.get_value(model,iter,colidx-1)

    if( valtype(data)=="N" )
        renderer:set_property("xalign",1) //jobbra igazít
    else
        renderer:set_property("xalign",0) //balra igazít (default)
    end

    if( picture!=NIL )
        data:=transform(data,picture)
    end

    renderer:set_property("text",data)

**************************************************************************** 
