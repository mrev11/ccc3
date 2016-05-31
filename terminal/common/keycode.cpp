
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

#ifdef _UNIX_

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define KEY_UP          XK_Up
#define KEY_DOWN        XK_Down
#define KEY_LEFT        XK_Left
#define KEY_RIGHT       XK_Right
#define KEY_HOME        XK_Home
#define KEY_END         XK_End
#define KEY_PGUP        XK_Prior
#define KEY_PGDN        XK_Next

#define KEY_KP_UP       XK_KP_Up
#define KEY_KP_DOWN     XK_KP_Down
#define KEY_KP_LEFT     XK_KP_Left
#define KEY_KP_RIGHT    XK_KP_Right
#define KEY_KP_HOME     XK_KP_Home
#define KEY_KP_END      XK_KP_End
#define KEY_KP_PGUP     XK_KP_Prior
#define KEY_KP_PGDN     XK_KP_Next

#define KEY_RETURN      XK_Return
#define KEY_ESC         XK_Escape
#define KEY_INS         XK_Insert
#define KEY_DEL         XK_Delete
#define KEY_BS          XK_BackSpace
#define KEY_TAB         XK_Tab

#define KEY_F1          XK_F1          
#define KEY_F2          XK_F2
#define KEY_F3          XK_F3 
#define KEY_F4          XK_F4
#define KEY_F5          XK_F5
#define KEY_F6          XK_F6
#define KEY_F7          XK_F7
#define KEY_F8          XK_F8
#define KEY_F9          XK_F9
#define KEY_F10         XK_F10
#define KEY_F11         XK_F11
#define KEY_F12         XK_F12

#else //WINDOWS

#include <windows.h>

#define KEY_UP          VK_UP
#define KEY_DOWN        VK_DOWN
#define KEY_LEFT        VK_LEFT
#define KEY_RIGHT       VK_RIGHT
#define KEY_HOME        VK_HOME
#define KEY_END         VK_END
#define KEY_PGUP        VK_PRIOR
#define KEY_PGDN        VK_NEXT

#define KEY_KP_UP
#define KEY_KP_DOWN
#define KEY_KP_LEFT
#define KEY_KP_RIGHT
#define KEY_KP_HOME
#define KEY_KP_END
#define KEY_KP_PGUP
#define KEY_KP_PGDN

#define KEY_RETURN      VK_RETURN
#define KEY_ESC         VK_ESCAPE
#define KEY_INS         VK_INSERT
#define KEY_DEL         VK_DELETE
#define KEY_BS          VK_BACK
#define KEY_TAB         VK_TAB

#define KEY_F1          VK_F1
#define KEY_F2          VK_F2
#define KEY_F3          VK_F3
#define KEY_F4          VK_F4
#define KEY_F5          VK_F5
#define KEY_F6          VK_F6
#define KEY_F7          VK_F7
#define KEY_F8          VK_F8
#define KEY_F9          VK_F9
#define KEY_F10         VK_F10
#define KEY_F11         VK_F11
#define KEY_F12         VK_F12
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
#ifdef _UNIX_
{KEY_KP_UP      ,K_NAV_UP       ,K_SH_UP    ,K_CTRL_UP      ,K_ALT_UP},
{KEY_KP_DOWN    ,K_NAV_DOWN     ,K_SH_DOWN  ,K_CTRL_DOWN    ,K_ALT_DOWN},
{KEY_KP_LEFT    ,K_NAV_LEFT     ,K_SH_LEFT  ,K_CTRL_LEFT    ,K_ALT_LEFT},
{KEY_KP_RIGHT   ,K_NAV_RIGHT    ,K_SH_RIGHT ,K_CTRL_RIGHT   ,K_ALT_RIGHT},
{KEY_KP_HOME    ,K_NAV_HOME     ,K_SH_HOME  ,K_CTRL_HOME    ,K_ALT_HOME},
{KEY_KP_END     ,K_NAV_END      ,K_SH_END   ,K_CTRL_END     ,K_ALT_END},
{KEY_KP_PGUP    ,K_NAV_PGUP     ,K_SH_PGUP  ,K_CTRL_PGUP    ,K_ALT_PGUP},
{KEY_KP_PGDN    ,K_NAV_PGDN     ,K_SH_PGDN  ,K_CTRL_PGDN    ,K_ALT_PGDN},
#endif
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
int keycode(int vkey, int state)
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
