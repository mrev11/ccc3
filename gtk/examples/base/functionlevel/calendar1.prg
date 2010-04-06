
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

#include "gtk.ch"


******************************************************************************
function main()

local window, cal, flags

    set date format "yyyy-mm-dd"

    gtk.init()
    
    window:=gtkwindowNew()
    window:set_title("Calendar Example")
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_size_request(300,300)
    window:set_border_width(10)

    window:add(cal:=gtkcalendarNew())

    cal:signal_connect("day_selected",{||cb_day_selected(cal)})
    cal:signal_connect("day-selected-double-click",{||cb_day_selected_double_click(cal)})
    cal:signal_connect("month-changed",{||cb_month_changed(cal)})
    cal:signal_connect("prev-month",{||cb_prev_month(cal)})
    cal:signal_connect("next-month",{||cb_next_month(cal)})
    cal:signal_connect("prev-year",{||cb_prev_year(cal)})
    cal:signal_connect("next-year",{||cb_next_year(cal)})

    cal:liststruct

    #ifdef NOT_DEFINED
        //egyféleképpen
        //mindent megváltoztat

        cal:set_property("no-month-change",.t.)
        cal:set_property("show-heading",.f.)
        cal:set_property("show-day-names",.f.)
        cal:set_property("show-week-numbers",.t.)

        cal:set_property("year",2010)
        cal:set_property("month",1) //feb
        cal:set_property("day",28)
   
        ? flags:=cal:get_display_options    

    #else
        //másféleképpen
        //mindent megváltoztat

        cal:set_display_options(12)
        cal:select_month(1,2010) //feb,2010 (hónap,év)
        cal:select_day(10)
    #endif

    cal:mark_day(20)    //bold-dal mutatja
    cal:mark_day(21)
    cal:mark_day(22)
    cal:mark_day(23)
    cal:mark_day(24)
    cal:unmark_day(22)  //vissza
    //cal:clear_marks   //mindet vissza

    window:show_all
    gtk.main()
    ?

******************************************************************************
static function cb_day_selected(w)
    ? "day_selected",  w:get_date(w)

******************************************************************************
static function cb_day_selected_double_click(w)
    ? "day_selected_double_click", w:get_date(w)

******************************************************************************
static function cb_month_changed(w)
    ? "month_changed", w:get_date(w)

******************************************************************************
static function cb_prev_month(w)
    ? "prev_month", w:get_date(w)

static function cb_next_month(w)
    ? "next_month", w:get_date(w)

******************************************************************************
static function cb_prev_year(w)
    ? "prev_year", w:get_date(w)

static function cb_next_year(w)
    ? "next_year", w:get_date(w)

******************************************************************************
    