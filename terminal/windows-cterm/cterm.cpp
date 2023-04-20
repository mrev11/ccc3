
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

extern void tcpio_ini(const char*,int);
extern THREAD_ENTRY void *tcpio_thread(void*);
extern void tcpio_sendkey(int);
extern int  readkey();
extern int  colorext_extidx2legidx(int);
extern void message(char const *msg, ...);

screenbuf *screen_buffer;
//screenbuf *shadow_buffer;

static int wwidth=80;
static int wheight=25;

//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    unsigned attr=-1;

    int x,y;
    for( y=top; y<=bot; y++ )
    {
        //for( x=lef; x<=rig; x++ )
        //{
        //    if( shadow_buffer->cell(x,y)!=screen_buffer->cell(x,y) )
        //    {
        //        break;
        //    }
        //}
        //if( x>rig )
        //{
        //    continue;
        //}

        move(y,lef);

        for( x=lef; x<=rig; x++ )
        {
            screencell *cell=screen_buffer->cell(x,y);
            unsigned ch=cell->getchar();
            unsigned at=cell->getattr();
            //shadow_buffer->cell(x,y)->setchar(ch);
            //shadow_buffer->cell(x,y)->setattr(at);

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
                attron(attr=at);
            }

            char buf[10];
            int len=ucs_to_utf8(ch,buf);
            addnstr(buf,len);
        }
    }

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
    printf("%c[m",0x1b);         // clear attrs
    printf("%c[?1049h",0x1b);    // ca mode off
    printf("%c[?47l",0x1b);      // restore screen
    printf("%c8",0x1b);          // restore cursor pos
    printf("%c[?25h",0x1b);      // cursor on
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    SetConsoleCP(6500); // 65001 UTF-8
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

    screensize(&wheight,&wwidth);
    screen_buffer=new screenbuf(wwidth,wheight);
    //shadow_buffer=new screenbuf(wwidth,wheight);

    printf("%c7",0x1b);          // save cursor pos
    printf("%c[?47h",0x1b);      // save screen
    printf("%c[?1049h",0x1b);    // ca mode on
    printf("%c[?25h",0x1b);      // cursor on

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

