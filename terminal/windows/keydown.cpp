
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


#include <windows.h>
#include <stdio.h>
  
extern int keycode(int i,int j);

static int state_shift=0;  //1
static int state_ctrl=0;   //2
static int state_lalt=0;   //4
static int state_ralt=0;   //4

static int wm_char_enabled=1;

extern void tcpio_sendkey(int inkeycode);


//--------------------------------------------------------------------------- 
void keyup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //printf("keyup   %d %08x\n",wParam,lParam);

    if( wParam==16 )//shift
    {
        state_shift=0;
        return;
    }
    else if( wParam==17 )//ctrl
    {
        state_ctrl=0;
        return;
    }
    else if( wParam==18 )//alt
    {
        if( lParam & 0x01000000L )
        {
            state_ralt=0;
        }
        else
        {
            state_lalt=0;
        }
        return;
    }
}


//--------------------------------------------------------------------------- 
void keydown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //printf("keydown %d %08x\n",wParam,lParam);

    if( wParam==16 )//shift
    {
        state_shift=1;
        return;
    }
    else if( wParam==17 )//ctrl
    {
        state_ctrl=1;
        return;
    }
    else if( wParam==18 )//alt
    {
        if( lParam & 0x01000000L )
        {
            state_ralt=1;
        }
        else
        {
            state_lalt=1;
        }
        return;
    }


    int key=(int)wParam; 
    
    int state=0;
    if( state_shift ) state|=1;
    if( state_ctrl )  state|=2;
    if( state_lalt )  state|=4;
    if( state_ralt )  state|=4;

    int inkeycode=keycode(key,state);

    if( inkeycode )
    {
        //printf("inkey %3d %08x\n",inkeycode,lParam);
        tcpio_sendkey(inkeycode);
        wm_char_enabled=0;
    }
    else
    {
        wm_char_enabled=1;
    }

    return;
}

//--------------------------------------------------------------------------- 
void keychar(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if( wm_char_enabled )
    {
        //printf("keychar %d %08x\n",wParam,lParam);

        int key=wParam;

        int state=0;
        if( state_shift ) state|=1;
        if( state_ctrl )  state|=2;
        if( state_lalt )  state|=4;
        if( state_ralt )  state|=4;

        if( (state&4) && 'a'<=key && key<='z' )
        {
            key=-(key-'a'+1); //ALT_A,...,ALT_Z
        }

        tcpio_sendkey(key);
    }
}

//--------------------------------------------------------------------------- 

