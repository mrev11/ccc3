
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

function game_over()

local glade:=<<glade>>
<glade-interface>

<widget class="GtkWindow" id="window_gameover">
  <property name="width_request">150</property>
  <property name="height_request">60</property>
  <property name="visible">True</property>
  <property name="title" translatable="yes">Amoeba</property>
  <property name="type">1</property>
  <property name="window_position">2</property>
  <property name="modal">True</property>
  <property name="resizable">False</property>
  <property name="destroy_with_parent">False</property>
  <property name="decorated">True</property>
  <property name="skip_taskbar_hint">False</property>
  <property name="skip_pager_hint">False</property>
  <property name="type_hint">GDK_WINDOW_TYPE_HINT_NORMAL</property>
  <property name="gravity">GDK_GRAVITY_NORTH_WEST</property>
  <property name="focus_on_map">True</property>
  <property name="urgency_hint">False</property>

  <child>
    <widget class="GtkButton" id="button1">
      <property name="visible">True</property>
      <property name="can_focus">True</property>
      <property name="relief">GTK_RELIEF_NORMAL</property>
      <property name="focus_on_click">True</property>

      <child>
        <widget class="GtkAlignment" id="alignment1">
          <property name="visible">True</property>
          <property name="xalign">0.5</property>
          <property name="yalign">0.5</property>
          <property name="xscale">0</property>
          <property name="yscale">0</property>
          <property name="top_padding">0</property>
          <property name="bottom_padding">0</property>
          <property name="left_padding">0</property>
          <property name="right_padding">0</property>

          <child>
            <widget class="GtkHBox" id="hbox1">
              <property name="visible">True</property>
              <property name="homogeneous">False</property>
              <property name="spacing">2</property>

              <child>
                <widget class="GtkImage" id="image1">
                  <property name="visible">True</property>
                  <property name="stock">gtk-dialog-error</property>
                  <property name="icon_size">4</property>
                  <property name="xalign">0.5</property>
                  <property name="yalign">0.5</property>
                  <property name="xpad">0</property>
                  <property name="ypad">0</property>
                </widget>
                <packing>
                  <property name="padding">0</property>
                  <property name="expand">False</property>
                  <property name="fill">False</property>
                </packing>
              </child>

              <child>
                <widget class="GtkLabel" id="label1">
                  <property name="visible">True</property>
                  <property name="label" translatable="yes">Game Over</property>
                  <property name="use_underline">True</property>
                  <property name="use_markup">False</property>
                  <property name="justify">GTK_JUSTIFY_LEFT</property>
                  <property name="wrap">False</property>
                  <property name="selectable">False</property>
                  <property name="xalign">0.5</property>
                  <property name="yalign">0.5</property>
                  <property name="xpad">0</property>
                  <property name="ypad">0</property>
                  <property name="ellipsize">PANGO_ELLIPSIZE_NONE</property>
                  <property name="width_chars">-1</property>
                  <property name="single_line_mode">False</property>
                  <property name="angle">0</property>
                </widget>
                <packing>
                  <property name="padding">0</property>
                  <property name="expand">False</property>
                  <property name="fill">False</property>
                </packing>
              </child>
            </widget>
          </child>
        </widget>
      </child>
    </widget>
  </child>
</widget>

</glade-interface>
<<glade>>

local window

    if( winner()!=32 )
        window:=gladeloadgui_from_string(glade)
        window:signal_connect("destroy",{||gtk.main_quit()})
        window:lookup("button1"):signal_connect("clicked",{||window:destroy})
        window:show_all()
        gtk.main()
    end
