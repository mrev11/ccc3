
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

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>

//---------------------------------------------------------------------------------------
void set_terminal_iconfile(Display *display, Window window)
{
    char *iconfile=getenv("CCCTERM_ICONFILE"); //xpm
    
    if( iconfile==0 || *iconfile==0  )
    {
        return;
    }

    Pixmap icon=0;
    Pixmap shapemask=0;

    int result=XpmReadFileToPixmap( 
            display,
            DefaultRootWindow(display),
            iconfile,
            &icon,
            &shapemask,
            NULL ); 

    if( result!=XpmSuccess ) 
    {
        fprintf(stderr,"XpmReadFileToPixmap failed\n");
        return;
    }

    XWMHints *hints= XGetWMHints(display,window);
    if( !hints )
    {
        hints=XAllocWMHints();
    }
    hints->flags |= IconPixmapHint;
    hints->icon_pixmap=icon;
    if( shapemask ) 
    {
        hints->flags |= IconMaskHint;
        hints->icon_mask=shapemask;
    }

    XSetWMHints(display,window,hints);
    XFree(hints);
}


//---------------------------------------------------------------------------------------
