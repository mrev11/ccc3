
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
#include <cccapi.h>
#include <cccgtk.h>

#ifdef EMLEKEZTETO
static function  cb_area_event(widget,event,drawingarea)
local handled:=FALSE
    if( gdk.event.get_type(event)==GDK_BUTTON_PRESS )
        handled:=TRUE
        ...
    end
    return handled
#endif

namespace _nsp_gdk {
namespace _nsp_event {

//---------------------------------------------------------------------------
void _clp_get_type(int argno) //kiegészítés (miért nincs ilyen?)
{
    CCC_PROLOG("gdk.event.get_type",1);
    gpointer event=_parp(1);
    _retni( ((GdkEventAny*)event)->type );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_window(int argno) //kiegészítés (miért nincs ilyen?)
{
    CCC_PROLOG("gdk.event.get_window",1);
    gpointer event=_parp(1);
    _retp( ((GdkEventAny*)event)->window );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_coords(int argno)
{
    CCC_PROLOG("gdk.event.get_coord",1);
    gpointer event=_parp(1);
    gdouble x=0;
    gdouble y=0;
    gdk_event_get_coords((GdkEvent*)event,&x,&y);
    number(x);
    number(y);
    array(2);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_send_event(int argno) //kiegészítés (miért nincs ilyen?)
{
    CCC_PROLOG("gdk.event.get_send_event",1);
    gpointer event=_parp(1);
    _retl( ((GdkEventAny*)event)->send_event );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_time(int argno)
{
    CCC_PROLOG("gdk.event.get_time",1);
    gpointer event=_parp(1);
    _retni( gdk_event_get_time((GdkEvent*)event) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
} //event
} //gdk

