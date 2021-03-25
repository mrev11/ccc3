

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
