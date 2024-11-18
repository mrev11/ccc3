
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

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <xcurses.h>

//#define MSGOUT
#include <msgout.h>


#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))



// itt olyan fuggvenyek vannak
// amik az ncurses konyvtarban is leteznek
// de az itteni implementaciojuk egyszerubb 
// kozvetlenul esc szekvenciakat irnak a terminalba

//----------------------------------------------------------------------------------------
void curs_set(int onoff)
{
    char buffer[32]; int len;
    len=sprintf(buffer,"%c[?25%c",0x1b,onoff?'h':'l'); addnstr(buffer,len);
}

//----------------------------------------------------------------------------------------
void attron(int fg, int bg)
{
    char buffer[32]; int len;
    len=sprintf(buffer,"%c[38;5;%dm",0x1b,fg); addnstr(buffer,len);
    len=sprintf(buffer,"%c[48;5;%dm",0x1b,bg); addnstr(buffer,len);
}

//----------------------------------------------------------------------------------------
void attroff(int attr)
{
    char buffer[32]; int len;
    len=sprintf(buffer,"%c[m",0x1b); addnstr(buffer,len);
}

//----------------------------------------------------------------------------------------
void move(int y,int x)
{
    char buffer[32]; int len;
    len=sprintf(buffer,"%c[%d;%dH",0x1b,y+1,x+1); addnstr(buffer,len);
}

//----------------------------------------------------------------------------------------
static char buffer[1024];
static unsigned int buflen=0;
static int item=0; // csak debug

//----------------------------------------------------------------------------------------
void addnstr(const char* text , unsigned length)
{
    if( sizeof(buffer)-buflen<length+1 )
    {
        if( buflen>0 )
        {
            printf("%s",buffer);
            buflen=0;
            item=0;
        }

        while( sizeof(buffer)<length+1 )
        {
            memmove(buffer,text,sizeof(buffer)-1);
            buffer[sizeof(buffer)-1]=0;
            printf("%s",text);
            text+=sizeof(buffer)-1;
            length-=sizeof(buffer)-1;
        }
    }
 
    memmove(buffer+buflen,text,length);
    buflen+=length;
    buffer[buflen]=0;
    item++;
}


//----------------------------------------------------------------------------------------
void addch(char ch)
{
    addnstr(&ch, 1);
}

//----------------------------------------------------------------------------------------
void refresh()
{
    msgout("REFRESH len=%d item=%d\n",buflen, item);

    if( buflen>0 )
    {
        printf("%s",buffer);
        buflen=0;
        item=0;
        fflush(0);
    }
}

//----------------------------------------------------------------------------------------

