
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

#include <stdint.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gtk {
namespace _nsp_frame {

//---------------------------------------------------------------------------
void _clp_get_label_align(int argno)
{
    CCC_PROLOG("gtk.frame.get_label_align",3);
    gpointer frame=_parp(1);
    gfloat xalign;
    gfloat yalign;
    gtk_frame_get_label_align(GTK_FRAME(frame),&xalign,&yalign);
    number(xalign); assign(base+1);
    number(yalign); assign(base+2);
    array(2);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //frame
} //gtk
