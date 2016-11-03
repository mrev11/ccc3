
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

#include <inkey3.ch>

#ifdef _GTK_

#include <gdk/gdkkeysyms.h>

#define KEY_UP          GDK_KEY_Up
#define KEY_DOWN        GDK_KEY_Down
#define KEY_LEFT        GDK_KEY_Left
#define KEY_RIGHT       GDK_KEY_Right
#define KEY_HOME        GDK_KEY_Home
#define KEY_END         GDK_KEY_End
#define KEY_PGUP        GDK_KEY_Prior
#define KEY_PGDN        GDK_KEY_Next

#define KEY_KP_UP       GDK_KEY_KP_Up
#define KEY_KP_DOWN     GDK_KEY_KP_Down
#define KEY_KP_LEFT     GDK_KEY_KP_Left
#define KEY_KP_RIGHT    GDK_KEY_KP_Right
#define KEY_KP_HOME     GDK_KEY_KP_Home
#define KEY_KP_END      GDK_KEY_KP_End
#define KEY_KP_PGUP     GDK_KEY_KP_Prior
#define KEY_KP_PGDN     GDK_KEY_KP_Next

#define KEY_RETURN      GDK_KEY_Return
#define KEY_ESC         GDK_KEY_Escape
#define KEY_INS         GDK_KEY_Insert
#define KEY_DEL         GDK_KEY_Delete
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

#endif

static int  v2i[48][5]={
{KEY_UP         ,K_NAV_UP       ,K_SH_UP    ,K_CTRL_UP      ,K_ALT_UP},
{KEY_DOWN       ,K_NAV_DOWN     ,K_SH_DOWN  ,K_CTRL_DOWN    ,K_ALT_DOWN},
{KEY_LEFT       ,K_NAV_LEFT     ,K_SH_LEFT  ,K_CTRL_LEFT    ,K_ALT_LEFT},
{KEY_RIGHT      ,K_NAV_RIGHT    ,K_SH_RIGHT ,K_CTRL_RIGHT   ,K_ALT_RIGHT},
{KEY_HOME       ,K_NAV_HOME     ,K_SH_HOME  ,K_CTRL_HOME    ,K_ALT_HOME},
{KEY_END        ,K_NAV_END      ,K_SH_END   ,K_CTRL_END     ,K_ALT_END},
{KEY_PGUP       ,K_NAV_PGUP     ,K_SH_PGUP  ,K_CTRL_PGUP    ,K_ALT_PGUP},
{KEY_PGDN       ,K_NAV_PGDN     ,K_SH_PGDN  ,K_CTRL_PGDN    ,K_ALT_PGDN},
{KEY_KP_UP      ,K_NAV_UP       ,K_SH_UP    ,K_CTRL_UP      ,K_ALT_UP},
{KEY_KP_DOWN    ,K_NAV_DOWN     ,K_SH_DOWN  ,K_CTRL_DOWN    ,K_ALT_DOWN},
{KEY_KP_LEFT    ,K_NAV_LEFT     ,K_SH_LEFT  ,K_CTRL_LEFT    ,K_ALT_LEFT},
{KEY_KP_RIGHT   ,K_NAV_RIGHT    ,K_SH_RIGHT ,K_CTRL_RIGHT   ,K_ALT_RIGHT},
{KEY_KP_HOME    ,K_NAV_HOME     ,K_SH_HOME  ,K_CTRL_HOME    ,K_ALT_HOME},
{KEY_KP_END     ,K_NAV_END      ,K_SH_END   ,K_CTRL_END     ,K_ALT_END},
{KEY_KP_PGUP    ,K_NAV_PGUP     ,K_SH_PGUP  ,K_CTRL_PGUP    ,K_ALT_PGUP},
{KEY_KP_PGDN    ,K_NAV_PGDN     ,K_SH_PGDN  ,K_CTRL_PGDN    ,K_ALT_PGDN},
{KEY_RETURN     ,K_RETURN       ,K_RETURN   ,K_RETURN       ,K_RETURN},
{KEY_ESC        ,K_ESC          ,K_ESC      ,K_ESC          ,K_ESC},
{KEY_INS        ,K_NAV_INS      ,K_INS      ,K_INS          ,K_INS},
{KEY_DEL        ,K_NAV_DEL      ,K_DEL      ,K_DEL          ,K_DEL},
{KEY_BS         ,K_BS           ,K_BS       ,K_BS           ,K_BS},
{KEY_TAB        ,K_TAB          ,K_TAB      ,K_TAB          ,K_TAB},
{KEY_F1         ,K_F1           ,K_SH_F1    ,K_CTRL_F1      ,K_ALT_F1},
{KEY_F2         ,K_F2           ,K_SH_F2    ,K_CTRL_F2      ,K_ALT_F2},
{KEY_F3         ,K_F3           ,K_SH_F3    ,K_CTRL_F3      ,K_ALT_F3},
{KEY_F4         ,K_F4           ,K_SH_F4    ,K_CTRL_F4      ,K_ALT_F4},
{KEY_F5         ,K_F5           ,K_SH_F5    ,K_CTRL_F5      ,K_ALT_F5},
{KEY_F6         ,K_F6           ,K_SH_F6    ,K_CTRL_F6      ,K_ALT_F6},
{KEY_F7         ,K_F7           ,K_SH_F7    ,K_CTRL_F7      ,K_ALT_F7},
{KEY_F8         ,K_F8           ,K_SH_F8    ,K_CTRL_F8      ,K_ALT_F8},
{KEY_F9         ,K_F9           ,K_SH_F9    ,K_CTRL_F9      ,K_ALT_F9},
{KEY_F10        ,K_F10          ,K_SH_F10   ,K_CTRL_F10     ,K_ALT_F10},
{KEY_F11        ,K_F11          ,K_SH_F11   ,K_CTRL_F11     ,K_ALT_F11},
{KEY_F12        ,K_F12          ,K_SH_F12   ,K_CTRL_F12     ,K_ALT_F12},
{0,0,0,0,0}};

//----------------------------------------------------------------------------
int keycode_gtk(int vkey, int state)
{
    int i;
    for( i=0; 1; i++ )
    {
        if( 0==v2i[i][0] )
        {
            break;
        }
        else if( vkey==v2i[i][0] )
        {
            if( state==0 )
            {
                return v2i[i][1];
            }
            else if( state & 1 )
            {
                return v2i[i][2];//shift
            }
            else if( state & 2 )
            {
                return v2i[i][3];//ctrl
            }
            else if( state & 4 )
            {
                return v2i[i][4];//alt
            }
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
