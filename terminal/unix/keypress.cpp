
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

//#include <wchar.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <pthread.h>
//#include <sys/times.h>

//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/keysym.h>
#include <X11/Xft/Xft.h>

#include <keysym2ucs.h>

extern void tcpio_sendkey(int);
extern int  keycode_x(int,int);
extern void keypress(XEvent event);

//----------------------------------------------------------------------------
void keypress(XEvent event)
{
    char buffer[32];
    int bufsize=sizeof(buffer);
    KeySym key;
    XComposeStatus compose;
    int leng=XLookupString(&event.xkey,buffer,bufsize,&key,&compose);

    buffer[leng]=0;
    int asc=buffer[0];
    int ucs=keysym2ucs(key);
    int code=0;

    int state=0;
    if(event.xkey.state & ShiftMask)    state|=1;
    if(event.xkey.state & ControlMask)  state|=2;
    if(event.xkey.state & Mod1Mask)     state|=4; //Alt
    if(event.xkey.state & Mod2Mask)     state|=8; //NumLock

    if( ucs>127 )
    {
        code=ucs;
    }
    else if( asc==127 ) //delete
    {
        if( event.xkey.keycode!=0x5b  )
        {
            //nem KP_Delete
            code=keycode_x(XK_Delete,state);
        }
        else if( (state&8)==0 ) 
        {
            //KP_Delete, de nem NumLock
            code=keycode_x(XK_KP_Delete,state);
        }
        else
        {
            //KP_Delete + NumLock
            code='.';
        }
    }
    else if( asc )
    {
        if( (state&4) && 'a'<=asc  && asc<='z' )
        {
            code=-(asc-'a'+1); //ALT_A,...,ALT_Z
        }
        else
        {
            code=asc;
        }
    }
    else
    {
        code=keycode_x((int)key,state);
    }

    //printf("code=%d state=%d key=%x leng=%d buffer=[%s] asc=%d\n", code,state,(int)key,leng,leng>0?buffer:"",asc);

    if( code )
    {
        tcpio_sendkey(code);
    }
}


//----------------------------------------------------------------------------

