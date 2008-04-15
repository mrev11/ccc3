
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

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gtk{
namespace _nsp_status_icon{

//------------------------------------------------------------------------------
void _clp_popup(int argno)
{
    //Kiegészítés a GtkStatusIcon API-hoz:
    //
    //  icon:popup(menu)
    //
    //Pontos pozícionálással jeleníti meg a menüt.
    //Az egyszerű menu:popup a menüt az egérkurzor 
    //helyére teszi, ami elfogadható, de nem profi.

    CCC_PROLOG("gtk.status_icon.popup",2);
    GtkStatusIcon* self=(GtkStatusIcon*)_parp(1);
    GtkMenu* menu=(GtkMenu*)_parp(2);
    GtkWidget* parent_menu_shell=0;
    GtkWidget* parent_menu_item=0;
    GtkMenuPositionFunc func=gtk_status_icon_position_menu;
    gpointer data=self;
    guint button=0;
    guint activate_time=gtk_get_current_event_time();
    gtk_menu_popup(GTK_MENU(menu),
                        parent_menu_shell,parent_menu_item,
                            func,data,button,activate_time);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
}//status_icon
}//gtk
