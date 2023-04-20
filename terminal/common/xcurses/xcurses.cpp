
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <xcurses.h>

//#define MSGOUT
//#include <msgout.h>

#include <ansi_colors.h>

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
void attron(int attr)
{
    int fg=0,bg=0;

    int coltrn[]={ 0, 4, 2, 6, 1, 5, 3, 7, 8,12,10,14, 9,13,11,15};
    //             b  r  g  y  b  m  c  w  b  r  g  y  b  m  c  w
    //             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f


    if( attr & 0xff00 )
    {
        //EXTENDED
  
        fg=0x7f&(attr>>0); // jelzobit leveve
        bg=0x7f&(attr>>8); // jelzobit leveve

        //msgout("EXT: %04x bg=%d fg=%d ", attr, bg, fg );
        //fflush(0);

        fg=ansi_colors[fg];    
        bg=ansi_colors[bg];    
    }

    else
    {
        //LEGACY
    
        fg=(attr>>0)&0x0f;
        bg=(attr>>4)&0x0f;

        //msgout("LEG: %04x bg=%d fg=%d ", attr, bg, fg );
        //fflush(0);

        fg=coltrn[fg];
        bg=coltrn[bg];
    }

    //msgout( "-> bg=%d fg=%d\n", bg, fg );


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

