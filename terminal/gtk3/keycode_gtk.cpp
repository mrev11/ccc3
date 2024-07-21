
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
#include <gdk/gdk.h>

#ifndef GDK_KEY_Up
//compatibility
#define GDK_KEY_Up             GDK_Up            
#define GDK_KEY_Down           GDK_Down          
#define GDK_KEY_Left           GDK_Left          
#define GDK_KEY_Right          GDK_Right         
#define GDK_KEY_Home           GDK_Home          
#define GDK_KEY_End            GDK_End           
#define GDK_KEY_Prior          GDK_Prior         
#define GDK_KEY_Next           GDK_Next          
#define GDK_KEY_Insert         GDK_Insert        
#define GDK_KEY_Delete         GDK_Delete        
                                                 
#define GDK_KEY_KP_Up          GDK_KP_Up         
#define GDK_KEY_KP_Down        GDK_KP_Down       
#define GDK_KEY_KP_Left        GDK_KP_Left       
#define GDK_KEY_KP_Right       GDK_KP_Right      
#define GDK_KEY_KP_Home        GDK_KP_Home       
#define GDK_KEY_KP_End         GDK_KP_End        
#define GDK_KEY_KP_Prior       GDK_KP_Prior      
#define GDK_KEY_KP_Next        GDK_KP_Next       
#define GDK_KEY_KP_Insert      GDK_KP_Insert     
#define GDK_KEY_KP_Delete      GDK_KP_Delete     
                                                 
#define GDK_KEY_Return         GDK_Return        
#define GDK_KEY_Escape         GDK_Escape        
#define GDK_KEY_BackSpace      GDK_BackSpace     
#define GDK_KEY_Tab            GDK_Tab           
                                                 
#define GDK_KEY_F1             GDK_F1            
#define GDK_KEY_F2             GDK_F2            
#define GDK_KEY_F3             GDK_F3            
#define GDK_KEY_F4             GDK_F4            
#define GDK_KEY_F5             GDK_F5            
#define GDK_KEY_F6             GDK_F6            
#define GDK_KEY_F7             GDK_F7            
#define GDK_KEY_F8             GDK_F8            
#define GDK_KEY_F9             GDK_F9            
#define GDK_KEY_F10            GDK_F10           
#define GDK_KEY_F11            GDK_F11           
#define GDK_KEY_F12            GDK_F12           
#endif




#define KEY_UP          GDK_KEY_Up
#define KEY_DOWN        GDK_KEY_Down
#define KEY_LEFT        GDK_KEY_Left
#define KEY_RIGHT       GDK_KEY_Right
#define KEY_HOME        GDK_KEY_Home
#define KEY_END         GDK_KEY_End
#define KEY_PGUP        GDK_KEY_Prior
#define KEY_PGDN        GDK_KEY_Next
#define KEY_INS         GDK_KEY_Insert
#define KEY_DEL         GDK_KEY_Delete

#define KEY_KP_UP       GDK_KEY_KP_Up
#define KEY_KP_DOWN     GDK_KEY_KP_Down
#define KEY_KP_LEFT     GDK_KEY_KP_Left
#define KEY_KP_RIGHT    GDK_KEY_KP_Right
#define KEY_KP_HOME     GDK_KEY_KP_Home
#define KEY_KP_END      GDK_KEY_KP_End
#define KEY_KP_PGUP     GDK_KEY_KP_Prior
#define KEY_KP_PGDN     GDK_KEY_KP_Next
#define KEY_KP_INS      GDK_KEY_KP_Insert
#define KEY_KP_DEL      GDK_KEY_KP_Delete

#define KEY_RETURN      GDK_KEY_Return
#define KEY_ESC         GDK_KEY_Escape
#define KEY_BS          GDK_KEY_BackSpace
#define KEY_TAB         GDK_KEY_Tab

#define KEY_F1          GDK_KEY_F1          
#define KEY_F2          GDK_KEY_F2
#define KEY_F3          GDK_KEY_F3 
#define KEY_F4          GDK_KEY_F4
#define KEY_F5          GDK_KEY_F5
#define KEY_F6          GDK_KEY_F6
#define KEY_F7          GDK_KEY_F7
#define KEY_F8          GDK_KEY_F8
#define KEY_F9          GDK_KEY_F9
#define KEY_F10         GDK_KEY_F10
#define KEY_F11         GDK_KEY_F11
#define KEY_F12         GDK_KEY_F12

#define KEYCODE keycode_gtk
#include <keycode.h>

