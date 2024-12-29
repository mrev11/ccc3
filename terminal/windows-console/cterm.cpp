
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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <locale.h>

#include <xcurses.h>

//#define MSGOUT
//#include <msgout.h>

#include <screenbuf.h>
#include <utf8conv.h>
#include <inkey.ch>

#define THREAD_ENTRY /*nothing*/

static pthread_mutex_t mutex_inv=PTHREAD_MUTEX_INITIALIZER;
static void invalidate_lock(){pthread_mutex_lock(&mutex_inv);}
static void invalidate_unlock(){pthread_mutex_unlock(&mutex_inv);}

extern void tcpio_ini(const char*,int);
extern THREAD_ENTRY void *tcpio_thread(void*);
extern void tcpio_sendkey(int);
extern int  readkey();
extern int  colorext_extidx2legidx(int);
extern void message(char const *msg, ...);

screenbuf *screen_buffer=0;
screenbuf *screen_shadow=0;

static int wwidth=80;
static int wheight=25;
static int cursor_x=0;
static int cursor_y=0;

//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    unsigned attr=-1;   // aktualis attributum
    int posflag=1;      // kell-e pozicionalni

    int x,y;
    for( y=top; y<=bot; y++ )
    {
        posflag=1;

        for( x=lef; x<=rig; x++ )
        {
            screencell *cell=screen_buffer->cell(x,y);
            screencell *shdw=screen_shadow->cell(x,y);
            unsigned ch=cell->getchar();
            unsigned at=cell->getattr();
            unsigned sch=shdw->getchar();
            unsigned sat=shdw->getattr();
            
            if( ch==sch && at==sat )
            {
                posflag=1;
                continue;
            }  

            shdw->setchar(ch);
            shdw->setattr(at);

            if( ch<32 )
            {
                ch='.';
            }
            else if(ch==0x2018)
            {
                ch=0x60; //`
            }
            else if(ch==0x2019)
            {
                ch=0x27; //'
            }


            if( attr!=at )
            {
                attr=at;
                attron(cell->get_fg(),cell->get_bg());
            }

            if( posflag )
            {
                posflag=0;
                move(y,x);
            }

            char buf[10];
            int len=ucs_to_utf8(ch,buf);
            addnstr(buf,len);
        }
    }
    move(cursor_y,cursor_x);
    refresh();
}

//---------------------------------------------------------------------------
void invalidate(int top, int lef, int bot, int rig)
{
    invalidate_lock();
    paint(top,lef,bot,rig);
    invalidate_unlock();
}

//----------------------------------------------------------------------------
void setwsize(int x, int y)
{
    invalidate_lock();
    printf("%c[8;%d;%dt",0x1b,y,x);
    wwidth=x;
    wheight=y;
    if(screen_buffer)
    {
        delete screen_buffer;
        delete screen_shadow;
    }
    screen_buffer=new screenbuf(wwidth,wheight);
    screen_shadow=new screenbuf(wwidth,wheight,-1);
    invalidate_unlock();
}

//----------------------------------------------------------------------------
void setcaption(char *p)
{
    printf("%c]2;%s%c",0x1b,p,0x07);
}

//----------------------------------------------------------------------------
void setcursor(int x, int y)
{
    cursor_x=x;
    cursor_y=y;
    move(y,x);
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
    printf("%c[?1049l",0x1b);    // ca mode off
    printf("%c[?25h",0x1b);      // cursor on
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    SetConsoleCP(65001); // 65001 UTF-8
    SetConsoleOutputCP(65001); // 65001 UTF-8

    //printf("input codepage: %d\n", GetConsoleCP());
    //printf("output codepage: %d\n", GetConsoleOutputCP());


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

    atexit(bye);

    screensize(&wwidth,&wheight);
    screen_buffer=new screenbuf(wwidth,wheight);
    screen_shadow=new screenbuf(wwidth,wheight,-1);

    printf("%c[?1036h",0x1b);    // meta send escape
    printf("%c[?1049h",0x1b);    // ca mode on
    printf("%c[?25h",0x1b);      // cursor on

  //printf("%c[1 q",0x1b);       // cursor shape  blinking block (do not blink)
  //printf("%c[2 q",0x1b);       // cursor shape  steady block (nem mukodik: kiir egy 'q'-t)
  //printf("%c[3 q",0x1b);       // cursor shape  blinking underline
  //printf("%c[4 q",0x1b);       // cursor shape  steady underline
  //printf("%c[5 q",0x1b);       // cursor shape  blinking bar
  //printf("%c[6 q",0x1b);       // cursor shape  steady bar

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

