

//----------------------------------------------------------------------------------------
#ifdef CURSES    // (probalom kihagyni az ncurses konyvtarat)
//----------------------------------------------------------------------------------------

#if  defined _LINUX_
    #include <ncursesw/ncurses.h>
#elif defined _NETBSD_
    #include <ncursesw/ncurses.h>
    extern "C" int  waddnwstr(WINDOW*,wchar_t*,int);
#elif defined _FREEBSD_
    #include <ncurses/cursesw.h>
    extern "C" int  waddnwstr(WINDOW*,wchar_t*,int);
#else
    #include <ncursesw/ncurses.h>
#endif


void screensize(int *y, int*x)  // lekerdezi a terminal meretet
{
    int wheight=0;
    int wwidth=0;

    initscr();
    getmaxyx(stdscr,wheight,wwidth); // ncurses macro
    endwin();

    *y=wheight;
    *x=wwidth;
}

//----------------------------------------------------------------------------------------
#else // ioctl  (egyszerubbnek tunik, de mukodik-e mindig)
//----------------------------------------------------------------------------------------

#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


void screensize(int *y, int *x)  // lekerdezi a terminal meretet
{
    struct winsize ws;

    if ( ioctl( 0, TIOCGWINSZ, &ws ) != 0 &&
         ioctl( 1, TIOCGWINSZ, &ws ) != 0 &&
         ioctl( 2, TIOCGWINSZ, &ws ) != 0 )
    {
        fprintf( stderr,"ioctl() failed (%d): %s\n", errno, strerror(errno));

        *y=80;
        *x=25;
    }
    else
    {
        *y=ws.ws_row;
        *x=ws.ws_col;
    }
}

//----------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------


