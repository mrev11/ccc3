
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

#include <string.h>
#include <stdint.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

DEFINE_METHOD(gobject);
//DEFINE_METHOD(classname);

//A C szintű interfészben a _parp makró le van cserélve
//gtk::_parp_object-re. Ezzel az API függvények hívásakor
//a pointerek helyén mindenhol állhat olyan objektum,
//aminek van gobject attribútuma. A függvények automatikusan
//a gobject-ben tárolt pointert fogják használni.

namespace _nsp_gtk {

//----------------------------------------------------------------------------
void *_parp_object(int paridx, VALUE*base, int argno)
{
    if( ISOBJECT(paridx) )
    {
        push(base+paridx-1);
        _o_method_gobject.eval(1);
        *(base+paridx-1)=*TOP();
        pop();
    }

    if( !ISPOINTER(paridx) )
    {
        ARGERROR();
    }

    return PARP(paridx);
}

//----------------------------------------------------------------------------

} //gtk

