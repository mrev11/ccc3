
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


#include <termutil.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef _UNIX_
  #include <sys/time.h>
  #include <sys/types.h>
#else
  #include <windows.h>
#endif

#ifdef WINDOWS
  #define THREAD_ENTRY  __stdcall
#else
  #define THREAD_ENTRY  /*nothing*/
#endif


#include <inttypes.h>
#include <netint.h>
#include <termio.h>
#include <termcmd.h>
#include <termapi.h>

#include <signal.ch>
#include <inkey.ch>

#undef min
#undef max
#define min(x,y)   ((x)<(y)?(x):(y))
#define max(x,y)   ((x)>(y)?(x):(y))


static screenbuf *screen=0;

static int display_loop=1;
static int display_now=1;

static int dirty_top=10000;
static int dirty_lef=10000;
static int dirty_bot=-1;
static int dirty_rig=-1;

static int s_curcol=0;
static int s_currow=0;
static int dirty_cursorpos=0;

static int s_cursorstate=1; //a terminál tulajdonsága
static int dirty_cursorstate=0;

static int ctrl_inkey=1;  // 1 -> K_DOWN==^X ... (compatible)

static char*term_message=0;

MUTEX_CREATE(mutex_display);


//----------------------------------------------------------------------------
static void sleep(int ms)
{
#ifdef UNIX
    struct timeval t;
    t.tv_sec=ms/1000;
    t.tv_usec=(ms%1000)*1000;
    select(0,0,0,0,&t);
#else
    Sleep(ms);
#endif
}

//----------------------------------------------------------------------------
static void bye()
{
    display_loop=0;
}

//----------------------------------------------------------------------------
static void sendrect()
{
    int top=dirty_top;
    int lef=dirty_lef;
    int bot=dirty_bot;
    int rig=dirty_rig;

    if( (top<=bot) && (lef<=rig) )
    {
        //printf("r");fflush(0);

        int cells=(rig-lef+1)*(bot-top+1);
        int size1=sizeof(network_uint32_t)*6;
        int size2=sizeof(screencell_term)*cells;
        char *buf=(char*)malloc(size1+size2);
        network_uint32_t *buf1=(network_uint32_t*)buf;
        screencell *buf2=(screencell*)(buf+size1);
        screencell_term *buf3=(screencell_term*)(buf+size1);

        buf1[0].set(TERMCMD_PUTRECT);
        buf1[1].set(size1+size2);
        buf1[2].set(lef);
        buf1[3].set(top);
        buf1[4].set(rig);
        buf1[5].set(bot);

        getrect(lef,top,rig,bot,buf2);

#ifdef _CCC2_
        for(int i=0;i<cells;i++)
        {
            extern int convtab_cwi2lat(int);
            extern int convtab_lat2ucs(int);
            int j=cells-1-i;
            int c=buf2[j].getchar();
            int fg=buf2[j].get_fg();
            int bg=buf2[j].get_bg();
            c=convtab_cwi2lat(c);
            c=convtab_lat2ucs(c);
            buf3[j].setchar(c);
            buf3[j].set_fg(fg);
            buf3[j].set_bg(bg);
        }
#endif

        termio_send(buf,size1+size2);
        free(buf);
    }

    dirty_top=10000;
    dirty_lef=10000;
    dirty_bot=-1;
    dirty_rig=-1;
}

//----------------------------------------------------------------------------
static void sendcursorpos()
{
    //printf("p");fflush(0);

    network_uint32_t buf[4];
    buf[0].set(TERMCMD_GOTOXY);
    buf[1].set(sizeof(buf));
    buf[2].set(s_curcol);
    buf[3].set(s_currow);
    termio_send(buf,sizeof(buf));
    dirty_cursorpos=0;
}

//----------------------------------------------------------------------------
static void sendcursorstate()
{
    //printf("s");fflush(0);

    network_uint32_t buf[2];
    buf[0].set(s_cursorstate?TERMCMD_SETCURSORON:TERMCMD_SETCURSOROFF);
    buf[1].set(sizeof(buf));
    termio_send(buf,sizeof(buf));
    dirty_cursorstate=0;
}

//----------------------------------------------------------------------------
static void sendmessage()
{
    if( term_message )
    {
        int len=strlen(term_message);
        network_uint32_t buf[2];
        buf[0].set(TERMCMD_MESSAGE);
        buf[1].set(sizeof(buf)+len+1);
        termio_send2(buf,sizeof(buf),term_message,len+1); //lezaro 0
    }
    free(term_message);
    term_message=0;
}

//----------------------------------------------------------------------------
static void sendall()
{
    sendrect();

    if(dirty_cursorstate)
    {
        sendcursorstate();
    }
    if(dirty_cursorpos && s_cursorstate)
    {
        sendcursorpos();
    }
    if( term_message )
    {
        sendmessage();
    }
}

//----------------------------------------------------------------------------
THREAD_ENTRY static void *thread_display(void *ptr)
{
    while(display_loop)
    {
        MUTEX_LOCK(mutex_display);
        if( display_now )
        {
            sendall();
        }
        MUTEX_UNLOCK(mutex_display);
        sleep(50);
    }
    //printf("end of thread_display\n"); fflush(0);
    return 0;
}

//----------------------------------------------------------------------------
THREAD_ENTRY static void *thread_message(void *ptr)
{
    char *env=getenv("CCCTERM_MAILSLOT");
    if( !env )
    {
        return 0;
    }
    int fd=open(env,O_RDONLY);
    if( fd<0 )
    {
        return 0;
    }
    lseek(fd,0,SEEK_END);

    char buf[1024];
    while(display_loop)
    {
        int nbyte=read(fd,buf,sizeof(buf)-1);
        if( nbyte>0 )
        {        
            buf[nbyte]=0;
            term_message=strdup(buf);
        }
        lseek(fd,0,SEEK_END);
        sleep(500);
    }
    return 0;
}

//----------------------------------------------------------------------------
void initialize_terminal()
{
    int sizex=0;
    int sizey=0;
    connect_to_terminal();
    getwsize(&sizex,&sizey);
    screen=new screenbuf(sizex,sizey);

    atexit(bye);

#ifdef WINDOWS
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)thread_display,0,0,NULL);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE)thread_message,0,0,NULL);
#else    
    pthread_t t=0;
    if( 0!=pthread_create(&t,0,thread_display,0) )
    {
        fprintf(stderr,"display thread cannot start\n");
        exit(1);
    }
    if( 0!=pthread_create(&t,0,thread_message,0) )
    {
        fprintf(stderr,"message thread cannot start\n");
        exit(1);
    }
#endif
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
void gotoxy(int x, int y)
{
    MUTEX_LOCK(mutex_display);
    x=min(x,maxcol()); x=max(x,0);
    y=min(y,maxrow()); y=max(y,0);
    s_curcol=x;
    s_currow=y;
    dirty_cursorpos=1;
    MUTEX_UNLOCK(mutex_display);
}

//----------------------------------------------------------------------------
void setcursoron()
{
    MUTEX_LOCK(mutex_display);
    if( s_cursorstate==0 )
    {
        s_cursorstate=1;
        dirty_cursorstate=1;
    }
    MUTEX_UNLOCK(mutex_display);
}

//----------------------------------------------------------------------------
void setcursoroff()
{
    MUTEX_LOCK(mutex_display);
    if( s_cursorstate==1 )
    {
        s_cursorstate=0;
        dirty_cursorstate=1;
    }
    MUTEX_UNLOCK(mutex_display);
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
void putrect(int lef, int top, int rig, int bot, screencell *source)
{
    MUTEX_LOCK(mutex_display);

    if( !screen->putrect(lef,top,rig,bot,source) )
    {
        fprintf(stderr,"putrect error: %d %d %d %d\n",lef,top,rig,bot);
        exit(1);
    }

    dirty_top=min(dirty_top,top);
    dirty_lef=min(dirty_lef,lef);
    dirty_bot=max(dirty_bot,bot);
    dirty_rig=max(dirty_rig,rig);
    
    MUTEX_UNLOCK(mutex_display);
}

//----------------------------------------------------------------------------
void dispbegin()
{
    MUTEX_LOCK(mutex_display);
    display_now=1;
    sendall();
    display_now=0;
    MUTEX_UNLOCK(mutex_display);
}

//----------------------------------------------------------------------------
void dispend()
{
    MUTEX_LOCK(mutex_display);
    display_now=1;
    sendall();
    MUTEX_UNLOCK(mutex_display);
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
  
    int code=key.get();
    if( ctrl_inkey )
    {
        switch( code )
        {
            //K_UP==^E
            //K_DOWN==^X ... default mode

            case K_NAV_UP:    code=K_UP;    break;
            case K_NAV_DOWN:  code=K_DOWN;  break;
            case K_NAV_LEFT:  code=K_LEFT;  break;
            case K_NAV_RIGHT: code=K_RIGHT; break;
            case K_NAV_HOME:  code=K_HOME;  break;
            case K_NAV_END:   code=K_END;   break;
            case K_NAV_PGUP:  code=K_PGUP;  break;
            case K_NAV_PGDN:  code=K_PGDN;  break;
            case K_NAV_INS:   code=K_INS;   break;
            case K_NAV_DEL:   code=K_DEL;   break;
        }  
    }

#ifdef _CCC2_
    //CCC3-rol CCC2-re
    extern int convtab_inkey3_to_inkey2(int);
    code=convtab_inkey3_to_inkey2(code);
#endif

    return code; 
}

//----------------------------------------------------------------------------
int get_ctrl_inkey_mode()
{
    return ctrl_inkey;
}

void set_ctrl_inkey_mode(int mode)
{
    ctrl_inkey=mode;
}

//----------------------------------------------------------------------------
void setcaption(char *cap, int len)
{
    network_uint32_t buf[2];
    buf[0].set(TERMCMD_SETCAPTION);
    buf[1].set(sizeof(buf)+len);
    termio_send2(buf,sizeof(buf),cap,len);
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
char *termgetenv(char *env)
{
    int len=strlen(env);

    network_uint32_t buf[2];
    buf[0].set(TERMCMD_GETENV);
    buf[1].set(sizeof(buf)+len+1);
    termio_send2(buf,sizeof(buf),env,len+1);

    termio_recv(buf,sizeof(buf)); //header
    while( buf[0].get()!=TERMCMD_GETENV )
    {
        if( buf[0].get()!=TERMCMD_KEYCODE )
        {
            //ilyen nem lehet
            fprintf(stderr,"termgetenv: unexpected message\n");
            signal_raise(SIG_TERM);
            exit(1);
        }
        termio_drop(buf[1].get()-sizeof(buf)); //dropping rest
        termio_recv(buf,sizeof(buf)); //header
    }

    len=buf[1].get()-sizeof(buf);
    if( len>0 )
    {
        char *val=(char*)malloc(len);
        termio_recv(val,len);
        return val;
    }
    return 0;
}


//----------------------------------------------------------------------------
void termputenv(char *env)
{
    int len=strlen(env);
    network_uint32_t buf[2];
    buf[0].set(TERMCMD_PUTENV);
    buf[1].set(sizeof(buf)+len+1);
    termio_send2(buf,sizeof(buf),env,len+1);
}


//----------------------------------------------------------------------------
int termchdir(char *dir)
{
    int len=strlen(dir);
    network_uint32_t buf[2];
    buf[0].set(TERMCMD_CHDIR);
    buf[1].set(sizeof(buf)+len+1);
    termio_send2(buf,sizeof(buf),dir,len+1);

    termio_recv(buf,sizeof(buf)); //header
    while( buf[0].get()!=TERMCMD_CHDIR )
    {
        if( buf[0].get()!=TERMCMD_KEYCODE )
        {
            //ilyen nem lehet
            fprintf(stderr,"termchdir: unexpected message\n");
            signal_raise(SIG_TERM);
            exit(1);
        }
        termio_drop(buf[1].get()-sizeof(buf)); //dropping rest
        termio_recv(buf,sizeof(buf)); //header
    }

    network_uint32_t result;
    termio_recv(&result,sizeof(result));
    return result.get(); // success==0

}

//----------------------------------------------------------------------------
char *termgetcwd()
{
    network_uint32_t buf[2];
    buf[0].set(TERMCMD_GETCWD);
    buf[1].set(sizeof(buf));
    termio_send(buf,sizeof(buf));

    termio_recv(buf,sizeof(buf)); //header
    while( buf[0].get()!=TERMCMD_GETCWD )
    {
        if( buf[0].get()!=TERMCMD_KEYCODE )
        {
            //ilyen nem lehet
            fprintf(stderr,"termgetcwd: unexpected message\n");
            signal_raise(SIG_TERM);
            exit(1);
        }
        termio_drop(buf[1].get()-sizeof(buf)); //dropping rest
        termio_recv(buf,sizeof(buf)); //header
    }

    int len=buf[1].get()-sizeof(buf);
    if( len>0 )
    {
        char *val=(char*)malloc(len);
        termio_recv(val,len);
        return val;
    }
    return 0;
}

//----------------------------------------------------------------------------

