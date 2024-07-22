
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

//---------------------------------------------------------------------------
void _clp_init(int argno)
{
    gtk_init(&ARGC, &ARGV);
    stack-=argno;
    push(&NIL);
}

//---------------------------------------------------------------------------
void _clp_main(int argno)
{
    gtk_main();
    stack-=argno;
    push(&NIL);
}

//---------------------------------------------------------------------------
void _clp_main_quit(int argno)
{
    gtk_main_quit();
    stack-=argno;
    push(&NIL);
}

//---------------------------------------------------------------------------
void _clp_main_depth(int argno)
{
    stack-=argno;
    number(g_main_depth());
}

//---------------------------------------------------------------------------
void _clp_events_pending(int argno)
{
    stack-=argno;
    logical(gtk_events_pending());
}

//---------------------------------------------------------------------------
void _clp_main_iteration(int argno)
{
    gtk_main_iteration();
    stack-=argno;
    push(&NIL);
}

//---------------------------------------------------------------------------
void _clp_main_stabilize(int argno)
{
    while( gtk_events_pending() )
    {
        gtk_main_iteration();
    }
    stack-=argno;
    push(&NIL);
}

//---------------------------------------------------------------------------

} //gtk
