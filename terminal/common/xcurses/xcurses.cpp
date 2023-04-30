
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <xcurses.h>

//#define MSGOUT
//#include <msgout.h>


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
static char buffer[1024*32];
static unsigned int buflen=0;
static int item=0; // csak debug

//----------------------------------------------------------------------------------------
void addnstr(const char* text , unsigned length)
{
    if( sizeof(buffer)-buflen<length+1 )
    {
        printf("%s",buffer);
        buflen=0;
        item=0;
    }
    if( sizeof(buffer)-buflen<length+1 )
    {
        printf("%s",text);
    }
    else
    {
        memmove(buffer+buflen,text,length);
        buflen+=length;
        buffer[buflen]=0;
        item++;
    }
}


//----------------------------------------------------------------------------------------
void addch(char ch)
{
    addnstr(&ch, 1);
}

//----------------------------------------------------------------------------------------
void refresh()
{
    //msgout("REFRESH len=%d item=%d\n",buflen, item);

    printf("%s",buffer);
    buflen=0;
    item=0;
    fflush(0);
}

//----------------------------------------------------------------------------------------

