
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

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <screenbuf.h>
#include <inkey.ch>
#include <inkeymap.h>


extern void tcpio_ini(const char*,int);
extern void *tcpio_thread(void*);
extern void tcpio_sendkey(int);
extern int  readkey();


screenbuf *screen_buffer;

static int* coltrans;
static int wwidth=80;
static int wheight=25;
static int cursor_x=0;
static int cursor_y=0;


static int rgb[] = {
   COLOR_BLACK,
   COLOR_BLUE,
   COLOR_GREEN,
   COLOR_CYAN,
   COLOR_RED,
   COLOR_MAGENTA,
   COLOR_YELLOW,
   COLOR_WHITE
};

//----------------------------------------------------------------------------
static void initcoltrans(void)
{
    coltrans=(int*)malloc(256*sizeof(int));

    int i,j,x;
    for( i=0; i<8; i++ )
    {
        for( j=0; j < 8; j++ )
        {
            init_pair((i*8+j),rgb[j],rgb[i]);
            int idx=i*16+j;
            x=COLOR_PAIR(i*8+j); 
               
            *(coltrans+(idx+  0+0)) = x; 
            *(coltrans+(idx+  0+8)) = x | WA_BOLD; //foreground+ negyed 
            *(coltrans+(idx+128+0)) = x;  //background+ negyed
            *(coltrans+(idx+128+8)) = x;
        }
    }
}

//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    int x,y;
    for( y=top; y<=bot; y++ )
    {
        for( x=lef; x<=rig; x++ )
        {
            screencell *cell=screen_buffer->cell(x,y);
            int ch=cell->getchar();
            int at=cell->getattr();

            if(ch==0x2018) ch=0x60; //`
            if(ch==0x2019) ch=0x27; //'
            
            move(y,x);
            attron(coltrans[255&at]);
            addnwstr((wchar_t*)(void*)&ch,1);
            attroff(coltrans[255&at]);
        }
    }
    move(cursor_y,cursor_x);
    refresh();
}

//---------------------------------------------------------------------------
void invalidate(int top, int lef, int bot, int rig)
{
    paint(top,lef,bot,rig);
}

//----------------------------------------------------------------------------
void setwsize(int x, int y)
{
}

//----------------------------------------------------------------------------
void setcaption(char *p)
{
}

//----------------------------------------------------------------------------
void setcursor(int x, int y)
{
    cursor_x=x;
    cursor_y=y;
    move(cursor_y,cursor_x);
    refresh();
}

//----------------------------------------------------------------------------
void setcursoroff()
{
    curs_set(0);
    refresh();
}

//----------------------------------------------------------------------------
void setcursoron()
{
    curs_set(1);
    refresh();
}

//----------------------------------------------------------------------------
void bye(void)
{
    endwin();
}

//----------------------------------------------------------------------------
void sighandler(int signum)
{
    //ezek elnyomva
    signal(SIGINT,sighandler);
    signal(SIGHUP,sighandler);
    signal(SIGPIPE,sighandler);
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[]) 
{
    sighandler(0);

    char host[256]; strcpy(host,"127.0.0.1"); 
    int port=55000;

    if( argc>=2 )
    {
        strcpy(host,argv[1]); 
    }
    if( argc>=3 )
    {
        sscanf(argv[2],"%d",&port); 
    }

    setlocale(LC_ALL,"");
    
    inkeymap_init();

    initscr();
    atexit(bye);
    cbreak();
    noecho();
    getmaxyx(stdscr,wheight,wwidth);
    start_color();
    initcoltrans();

    screen_buffer=new screenbuf(wwidth,wheight);

    tcpio_ini(host,port);
    pthread_t t=0;
    pthread_create(&t,0,tcpio_thread,0); 

    while(1)
    {
        int ch=readkey();
        if( ch )
        {
            tcpio_sendkey(ch);
        }
    }
}

//----------------------------------------------------------------------------
