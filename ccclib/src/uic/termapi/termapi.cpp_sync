
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
#include <stdio.h>
#include <string.h>

#include <inttypes.h>
#include <netint.h>
#include <termio.h>
#include <termcmd.h>
#include <termapi.h>

#include <signal.ch>


static screenbuf *screen=0;

static int s_curcol=0;
static int s_currow=0;

static int display_now=1;

static int dirty_top=10000;
static int dirty_lef=10000;
static int dirty_bot=-1;
static int dirty_rig=-1;

static int dirty_cursorpos=0;
static int dirty_cursorstate=0;
static int s_cursorstate=1; //a terminál tulajdonsága

//----------------------------------------------------------------------------
void initialize_terminal()
{
    int sizex=0;
    int sizey=0;
    connect_to_terminal();
    getwsize(&sizex,&sizey);
    screen=new screenbuf(sizex,sizey);
}

//----------------------------------------------------------------------------
int maxcol()
{
    return screen->sizex-1;
}

//----------------------------------------------------------------------------
int maxrow()
{
    return screen->sizey-1;
}

//----------------------------------------------------------------------------
int wherex()
{
    return s_curcol;  //0,...,maxcol==sizex-1
}

//----------------------------------------------------------------------------
int wherey()
{
    return s_currow;  //0,...,maxrow==sizey-1
}

//----------------------------------------------------------------------------
static void sendcursorpos(int x, int y)
{
    network_uint32_t buf[4];
    buf[0].set(TERMCMD_GOTOXY);
    buf[1].set(sizeof(buf));
    buf[2].set(x);
    buf[3].set(y);
    termio_send(buf,sizeof(buf));
    dirty_cursorpos=0;
}

//----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    x=min(x,maxcol()); x=max(x,0);
    y=min(y,maxrow()); y=max(y,0);
    s_curcol=x;
    s_currow=y;
    
    if( display_now )
    {
        sendcursorpos(x,y);
    }
    else
    {
        dirty_cursorpos=1;
    }
}

//----------------------------------------------------------------------------
static void sendcursorstate(int state)
{
    network_uint32_t buf[2];
    buf[0].set(state?TERMCMD_SETCURSORON:TERMCMD_SETCURSOROFF);
    buf[1].set(sizeof(buf));
    termio_send(buf,sizeof(buf));
    dirty_cursorstate=0;
}

//----------------------------------------------------------------------------
void setcursoron()
{
    s_cursorstate=1;

    if( display_now )
    {
        sendcursorstate(1);
    }
    else
    {
        dirty_cursorstate=1;
    }
}

//----------------------------------------------------------------------------
void setcursoroff()
{
    s_cursorstate=0;

    if( display_now )
    {
        sendcursorstate(0);
    }
    else
    {
        dirty_cursorstate=1;
    }
}

//----------------------------------------------------------------------------
void getrect(int lef, int top, int rig, int bot, screencell *destin)
{
    if( !screen->getrect(lef,top,rig,bot,destin) )
    {
        fprintf(stderr,"getrect error: %d %d %d %d\n",lef,top,rig,bot);
        exit(1);
    }
}

//----------------------------------------------------------------------------
static void sendrect(int lef, int top, int rig, int bot)
{
    if( (top<=bot) && (lef<=rig) )
    {
        //printf("sendrect\n");

        int cells=(rig-lef+1)*(bot-top+1);
        int size1=sizeof(network_uint32_t)*6;
        int size2=sizeof(screencell)*cells;
        char *buf=(char*)malloc(size1+size2);
        network_uint32_t *buf1=(network_uint32_t*)buf;
        screencell *buf2=(screencell*)(buf+size1);

        buf1[0].set(TERMCMD_PUTRECT);
        buf1[1].set(size1+size2);
        buf1[2].set(lef);
        buf1[3].set(top);
        buf1[4].set(rig);
        buf1[5].set(bot);

        getrect(lef,top,rig,bot,buf2);

        termio_send(buf,size1+size2);
        free(buf);
    }

    dirty_top=10000;
    dirty_lef=10000;
    dirty_bot=-1;
    dirty_rig=-1;
}

//----------------------------------------------------------------------------
void putrect(int lef, int top, int rig, int bot, screencell *source)
{
    if( !screen->putrect(lef,top,rig,bot,source) )
    {
        fprintf(stderr,"putrect error: %d %d %d %d\n",lef,top,rig,bot);
        exit(1);
    }
    
    if( display_now )
    {
        sendrect(lef,top,rig,bot);
    }
    else
    {
        dirty_top=min(dirty_top,top);
        dirty_lef=min(dirty_lef,lef);
        dirty_bot=max(dirty_bot,bot);
        dirty_rig=max(dirty_rig,rig);
    }
}

//----------------------------------------------------------------------------
void dispbegin()
{
    //printf("dispbegin\n");

    dirty_top=10000;
    dirty_lef=10000;
    dirty_bot=-1;
    dirty_rig=-1;
    dirty_cursorpos=0;
    dirty_cursorstate=0;
    display_now=0;
}

//----------------------------------------------------------------------------
void dispend()
{
    sendrect(dirty_lef,dirty_top,dirty_rig,dirty_bot);
    if( dirty_cursorstate ) sendcursorstate(s_cursorstate);
    if( dirty_cursorpos ) sendcursorpos(s_curcol,s_currow);
    display_now=1;

    //printf("dispend\n");
}

//----------------------------------------------------------------------------
int getkey(int timeout)
{
    //A KEYCODE uzenetek keres nelkul jonnek.
    //Minden mas terminal -> program iranyu uzenet keresre jon, 
    //amit a program megvar, ezert KEYCODE-ra varas kozben nem johet 
    //mas uzenet, mig mas valaszra varas kozben (mint GETWSIZE, OPEN)
    //johet varatlan KEYCODE (amit eldobunk).

    network_uint32_t key; key.set(0);
    network_uint32_t buf[2];
    int nbyte=termio_recv(buf,sizeof(buf),timeout,0);
    
    if( nbyte==0 )
    {
        //nincs leutes
    }
    else if( nbyte==sizeof(buf) && buf[0].get()==TERMCMD_KEYCODE )
    {
        termio_recv(&key,sizeof(key),-1);
    }
    else
    {
        //pl. megszakadt a kapcsolat a terminállal
        fprintf(stderr,"getkey: unexpected message (nbyte=%d code=%x)\n",nbyte,buf[0].get());
        signal_raise(SIG_TERM);
        exit(1);
    }
    return key.get();
}

//----------------------------------------------------------------------------
void setcaption(char *cap, int len)
{
    network_uint32_t buf[2];
    buf[0].set(TERMCMD_SETCAPTION);
    buf[1].set(sizeof(buf)+len);
    termio_send(buf,sizeof(buf));
    termio_send(cap,len);
}

//----------------------------------------------------------------------------
void getwsize(int *sizex, int *sizey)
{
    //A KEYCODE uzenetek keres nelkul jonnek.
    //Minden mas terminal -> program iranyu uzenet keresre jon, 
    //amit a program megvar, ezert KEYCODE-ra varas kozben nem johet 
    //mas uzenet, mig mas valaszra varas kozben (mint GETWSIZE, OPEN)
    //johet varatlan KEYCODE (amit eldobunk).

    network_uint32_t buf[2];

    buf[0].set(TERMCMD_GETWSIZE);
    buf[1].set(sizeof(buf));
    termio_send(buf,sizeof(buf));

    termio_recv(buf,sizeof(buf)); //header
    while( buf[0].get()!=TERMCMD_GETWSIZE )
    {
        if( buf[0].get()!=TERMCMD_KEYCODE )
        {
            //ilyen nem lehet
            fprintf(stderr,"getwsize: unexpected message\n");
            signal_raise(SIG_TERM);
            exit(1);
        }

        termio_drop(buf[1].get()-sizeof(buf)); //dropping rest
        termio_recv(buf,sizeof(buf)); //header
    }

    termio_recv(buf,sizeof(buf)); //params
    *sizex=buf[0].get();
    *sizey=buf[1].get();
}


//----------------------------------------------------------------------------
void setwsize(int sizex, int sizey)
{
    network_uint32_t buf[4];

    buf[0].set(TERMCMD_SETWSIZE);
    buf[1].set(sizeof(buf));
    buf[2].set(sizex);
    buf[3].set(sizey);
    termio_send(buf,sizeof(buf));

    getwsize(&sizex,&sizey);
    if( screen )
    {
        delete screen;
    }
    screen=new screenbuf(sizex,sizey);

    s_curcol=0;
    s_currow=0;
    dirty_top=0;
    dirty_lef=0;
    dirty_bot=sizey-1;
    dirty_rig=sizex-1;
    dirty_cursorpos=1;
    dirty_cursorstate=1;
}

//----------------------------------------------------------------------------

