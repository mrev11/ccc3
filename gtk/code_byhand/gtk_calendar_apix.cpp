
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
namespace _nsp_calendar{

//------------------------------------------------------------------------------
void _clp_get_date(int argno)
{
   CCC_PROLOG("gtk.calendar.get_date",1);
   gpointer self = _parp(1);
   guint year,month,day;
   gtk_calendar_get_date(GTK_CALENDAR(self),&year,&month,&day);

   //number(year);
   //number(month);
   //number(day);
   //array(3);
   
   //helyette dátum
   char *buf=binaryl(8);
   sprintf(buf,"%04d%02d%02d",year,month+1,day);
   bin2str(TOP());
   _clp_stod(1);

   _rettop();
   CCC_EPILOG();
}

//------------------------------------------------------------------------------
}//calendar
}//gtk
