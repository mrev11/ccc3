
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


// Ugyanaz a program, mint a cterm.cpp,  kiveve,
// hogy a Windowson hasznalhatatlanul lassu virtual terminal API helyett
// a regebbi (mar nem ajanlott) WriteConsoleOutput-tal irja a kepernyot.
// A paint() fuggveny implementaciojan kivul minden mas egyezik.


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

screenbuf *screen_buffer;

static int wwidth=80;
static int wheight=25;

static int rgb[16]={0,4,2,6,1,5,3,7,8,12,10,14,9,13,11,15}; // ANSI index -> rgb



//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{              
    static HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

    static int sizeofbuffer=(wwidth+1)*(wheight+1);
    static CHAR_INFO *buffer=(CHAR_INFO*)malloc(sizeofbuffer*sizeof(CHAR_INFO));

    if( (bot-top+1)*(rig-lef+1)>sizeofbuffer )
    {
        sizeofbuffer=(bot-top+1)*(rig-lef+1);
        buffer=(CHAR_INFO*)realloc(buffer,sizeofbuffer*sizeof(CHAR_INFO));
    }

    int x,y;
    for( y=top; y<=bot; y++ )
    {
        for( x=lef; x<=rig; x++ )
        {
            screencell *cell=screen_buffer->cell(x,y);
            unsigned ch=cell->getchar();

            if( ch<32      ){ ch='.';  }
            if( ch==0x2018 ){ ch=0x60; }
            if( ch==0x2019 ){ ch=0x27; }

            int fg=rgb[ LEGACY(cell->get_fg()) ];  // ANSI[0,255] -> ANSI[0,15]
            int bg=rgb[ LEGACY(cell->get_bg()) ];  // ANSI[0,255] -> ANSI[0,15]
            int at=bg<<4|fg;

            int idx=(y-top)*(rig-lef+1)+(x-lef);
            buffer[idx].Char.UnicodeChar=ch;
            buffer[idx].Attributes=at;
        }
    }

    COORD buffersize={(SHORT)(rig-lef+1),(SHORT)(bot-top+1)};
    COORD buffercoord={0,0};
    SMALL_RECT writeregion={(SHORT)lef,(SHORT)top,(SHORT)rig,(SHORT)bot};
    WriteConsoleOutputW(hConsole,buffer,buffersize,buffercoord,&writeregion);
}

//---------------------------------------------------------------------------
void invalidate(int top, int lef, int bot, int rig)
{
    invalidate_lock();

    static int maxcol=0;
    if( rig>maxcol )
    {
        maxcol=rig;
    }
    if( rig==maxcol-1 ) 
    {
        if( lef<rig )
        {
            paint(top,lef,bot,rig-1);
        }
        paint(top,rig,bot,maxcol);
        
        // Ez egy hack a terminal hibajanak javitasara:
        // Ha egy sor utolso karaktere maxcol()-1-re esik,
        // akkor a terminal elrontja a maxcol() poziciot.
        // (Emiatt romlott el a browse-ok jobb oldali kerete.)
        // Ezert a maxcol()-1-re vegzodo teglalapokat ket
        // reszletben frissitjuk:
        //  1) lef -> rig-1
        //  2) rig -> maxcol
        // Tehat a masodik resz egy oszloppal nagyobb:
        // hozzavesszuk a maxcol() oszlopot (ami elromlana).
        // Ezen a helyen nem tudjuk mekkora a terminal ablak,
        // ezert az addigi legnagyobb rig-et vesszuk.
    }
    else
    {
        paint(top,lef,bot,rig);
    }
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
    }
    screen_buffer=new screenbuf(wwidth,wheight);
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

    printf("%c[?1036h",0x1b);    // meta send escape
    printf("%c[?1049h",0x1b);    // ca mode on
    printf("%c[?25h",0x1b);      // cursor on

  //printf("%c[1 q",0x1b);       // cursor shape  blinking block (do not blink)
  //printf("%c[2 q",0x1b);       // cursor shape  steady block (nem mukodik: kiir egy 'q'-t)
  //printf("%c[3 q",0x1b);       // cursor shape  blinking underline
  //printf("%c[4 q",0x1b);       // cursor shape  steady underline
  //printf("%c[5 q",0x1b);       // cursor shape  blinking bar
  //printf("%c[6 q",0x1b);       // cursor shape  steady bar
    printf("\n");

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

