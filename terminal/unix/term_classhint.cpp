

//#include <stdio.h>
//#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/xpm.h>

//---------------------------------------------------------------------------------------
void set_terminal_classhint(Display *display, Window window)
{
    XClassHint *class_hint=XAllocClassHint();
    class_hint->res_name=class_hint->res_class=(char*)"CTerm"; // ascii
    XSetClassHint(display,window,class_hint);
    XFree(class_hint);
}

//---------------------------------------------------------------------------------------
