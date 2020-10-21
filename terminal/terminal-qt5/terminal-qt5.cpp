
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


#ifdef _UNIX_
  #include <sys/times.h>
  #include <pthread.h>
#else
  #include <windows.h>
#endif

#ifdef WINDOWS
  #define THREAD_ENTRY  __stdcall
#else
  #define THREAD_ENTRY  /*nothing*/
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include <QObject>
#include <QGuiApplication>
#include <QRasterWindow>
#include <QPainter>
#include <QPaintEvent>


#include <screenbuf.h>
#include <utf8conv.h>

#ifdef _UNIX_
  static pthread_mutex_t mutex_inv=PTHREAD_MUTEX_INITIALIZER;
  static void invalidate_lock(){pthread_mutex_lock(&mutex_inv);}
  static void invalidate_unlock(){pthread_mutex_unlock(&mutex_inv);}
#else
  static HANDLE mutex_inv=CreateMutex(0,0,0);
  static void invalidate_lock(){WaitForSingleObject(mutex_inv,INFINITE);}
  static void invalidate_unlock(){ReleaseMutex(mutex_inv);}
#endif

screenbuf *screen_buffer=0;

static int wwidth=0;
static int wheight=0;
static int dirty_size=0;

static int invtop=9999,invlef=9999,invbot=0,invrig=0;
static int dirty_buffer=0;

static int cursor_x=0;
static int cursor_y=0;
static int cursor_onoff=1;
static int cursor_state=0;
static int cursor_focus=0;
static int dirty_curpos=0;
static unsigned cursor_tick=0;

static char *caption=0;
static int dirty_caption=0;

static int dirty_blink=0;


struct TerminalWindow;
static TerminalWindow *qtwindow;


//kozos forras
extern void tcpio_ini(const char*,int);
extern THREAD_ENTRY void *tcpio_thread(void*);
extern void tcpio_sendkey(int);
extern int  color_palette(int);
extern int  colorext_palette(int);
extern int  colorext_palette_rev(int);
extern void fontspec(const char *envname, char **fontface, int *fontsize);

//lokalis segedfuggvenyek
static unsigned gettickcount(void);
static void sleep(int ms);
static void paint_cell(int x, int y, int inv);
static void paint_line(int y, int lef, int rig);
static void paint(int top, int lef, int bot, int rig);
static void blink(int flag);
static void invalidate_qt();
static void setcaption_qt();
static void setwsize_qt();
static void setcursor_qt();

//ezeket szolgaltatja
extern void invalidate(int t, int l, int b, int r);
extern void setcaption(char *cap);
extern void setwsize(int w, int h);
extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);


#define BLINK_UP  1
#define BLINK_DN  2

#define POSX(x)  ((x)*fwidth)
#define POSY(y)  ((y)*fheight)

//------------------------------------------------------------------------------------------
struct TerminalWindow : public QRasterWindow
{
    double fwidth;      //font width (pixel)
    double fheight;     //font height (pixel)

    int fontsize;
    char *fontname;
    QFont font;

    QPainter *painter;

    TerminalWindow()
    {
        fontsize=12;
        //fontname=strdup("Monospace");
        fontspec("CCCTERM_QTFONTSPEC",&fontname,&fontsize); //environment
        font=QFont(fontname);
        font.setPointSize(fontsize);

        QFontMetrics fm(font);
        int buflen=10000;
        char *buf=(char*)malloc(buflen+1);
        memset(buf,'X',buflen);
        buf[buflen]=0;
        fwidth=(double)fm.horizontalAdvance(buf)/buflen;
        free(buf);
        fheight=fm.height();
        //printf("fontsize: %d %d %f\n",fm.height(),fm.averageCharWidth(),fwidth);

        wwidth=0;
        wheight=0;
        if( getenv("CCCTERM_SIZE") )
        {
            sscanf(getenv("CCCTERM_SIZE"),"%dx%d",&wwidth,&wheight);
        }
        if( wwidth==0 || wheight==0 )
        {
            wwidth=80;
            wheight=25;
        }
        initsize();

        int posx=80+gettickcount()%300;
        int posy=60+gettickcount()%100;
        setPosition(posx,posy);
        setTitle("terminal-qt5");
        setFlags( Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint );
        screen_buffer=new screenbuf(wwidth,wheight);
        startTimer(10);
    }

    void initsize()
    {
        int w=POSX(wwidth);
        int h=POSY(wheight);
        setMinimumSize(QSize(w,h));
        setMaximumSize(QSize(w,h));
        //printf("initsize: %d %d \n",w,h);
    }


    void timerEvent(QTimerEvent *ev)
    {
        if( dirty_size )
        {
            setwsize_qt();
        }

        if( dirty_caption )
        {
            setcaption_qt();
        }

        if( dirty_curpos )
        {
            setcursor_qt();
        }

        if( dirty_buffer )
        {
            update(); // -> invalidate_qt()
        }
        
        unsigned tick=gettickcount()-cursor_tick;

        if( dirty_blink )
        {
            //folyamatban
        }        
        else if( cursor_state && tick>400  )
        {
            dirty_blink=BLINK_DN;
            update(); // -> blink(2)
        }
        else if( cursor_onoff && cursor_focus && !cursor_state && tick>200  )
        {
            dirty_blink=BLINK_UP;
            update(); // -> blink(1)
        }
    }


    void paint_begin()
    {
        painter=new QPainter(this);
        painter->setFont(font);
        painter->setBackgroundMode(Qt::OpaqueMode);
    }

    void paint_end()
    {
        painter->end();
        delete this->painter;
        painter=0;
    }
    

    void drawCells(int row, int col, wchar_t *ucs, int len, int attr)
    {
        int fg,bg,r,g,b;

        if( attr&0xff00 )
        {
            fg=colorext_palette_rev( 0x7f&(attr>>0) ); // jelzobit leveve
            bg=colorext_palette_rev( 0x7f&(attr>>8) ); // jelzobit leveve
        }
        else
        {
            fg=color_palette( 0xf&(attr>>0) );
            bg=color_palette( 0xf&(attr>>4) );
        }
        
        b = (fg & 0xff0000)>>16;
        g = (fg & 0x00ff00)>>8;
        r = (fg & 0x0000ff)>>0;
        QPen pen(QColor(r,g,b)); painter->setPen(pen);

        b = (bg & 0xff0000)>>16;
        g = (bg & 0x00ff00)>>8;
        r = (bg & 0x0000ff)>>0;
        QBrush brush(QColor(r,g,b)); painter->setBackground(brush);

        QRectF rect(POSX(col),POSY(row),POSX(col+len)-POSX(col),POSY(1));
        unsigned txtlen;
        char *txt=wchar_to_utf8(ucs,len,&txtlen);
        painter->fillRect(rect,brush);
        painter->drawText(rect,0,txt);
        free(txt);
    }

    void drawCell(int row, int col, unsigned ucs, unsigned attr, int inv=0)
    {
        QRectF rect(POSX(col), POSY(row), POSX(col+1)-POSX(col), POSY(1));

        int fg,bg,r,g,b;

        if( attr&0xff00 )
        {
            fg=colorext_palette_rev( 0x7f&(attr>>0) ); // jelzobit leveve
            bg=colorext_palette_rev( 0x7f&(attr>>8) ); // jelzobit leveve
        }
        else
        {
            fg=color_palette( 0xf&(attr>>0) );
            bg=color_palette( 0xf&(attr>>4) );
        }
        
        if(inv)
        {
            int fg1=fg;
            int bg1=bg;
            fg=bg1;
            bg=fg1;
        }

        b = (fg & 0xff0000)>>16;
        g = (fg & 0x00ff00)>>8;
        r = (fg & 0x0000ff)>>0;
        QPen pen(QColor(r,g,b)); painter->setPen(pen);

        b = (bg & 0xff0000)>>16;
        g = (bg & 0x00ff00)>>8;
        r = (bg & 0x0000ff)>>0;
        QBrush brush(QColor(r,g,b)); painter->setBackground(brush);

        char utf8[32];
        ucs_to_utf8(ucs,utf8);
        painter->fillRect(rect,brush);
        painter->drawText(rect,0,utf8);
    }


    void paintEvent(QPaintEvent *ev)
    {
        //QRect r=ev->rect();
        //printf("paintEvent: %d %d %d %d\n", r.top(),r.left(),r.bottom(),r.right());

        paint_begin();
        
        if( dirty_blink ) //elore
        {
            //printf("paint blink %d\n",dirty_blink);
            blink(dirty_blink);
            dirty_blink=0;
        }

        else if( dirty_buffer )
        {
            //printf("paint dirty\n");
            invalidate_qt();
            dirty_buffer=0;
        }

        else
        {
            //printf("paint whole\n");
            invalidate(0,0,wheight-1,wwidth-1);
            invalidate_qt();
        }
        
        paint_end();
    }
    

    void keyPressEvent(QKeyEvent *ev)
    {
        extern void key_press(QKeyEvent *ev);
        key_press(ev);
        //printf( "KeyPressEvent\n"); 
    }

    void keyReleaseEvent(QKeyEvent *ev)
    {
        extern void key_release(QKeyEvent *ev); 
        key_release(ev);
        //printf( "keyReleaseEvent\n"); 
    }

    void resizeEvent(QResizeEvent *ev)
    {
        //printf("resizeEvent\n");
    }

    void focusInEvent(QFocusEvent *ev)
    {
        cursor_focus=1;
        //printf("focusInEvent\n");
    }

    void focusOutEvent(QFocusEvent *ev)
    {
        cursor_focus=0;
        //printf("focusOutEvent\n");
    }
};


//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
static unsigned gettickcount(void)
{
  #ifdef _UNIX_
    struct tms buf;
    return (unsigned)times(&buf)*10;
  #else
    return GetTickCount();
  #endif
}

//------------------------------------------------------------------------------------------
static void sleep(int ms)
{
    if(ms>0)
    {
      #ifdef _UNIX_
        struct timeval t;
        t.tv_sec=ms/1000;
        t.tv_usec=(ms%1000)*1000;
        select(0,NULL,NULL,NULL,&t);
      #else
        Sleep( ms );
      #endif
    }
}

//------------------------------------------------------------------------------------------
static void paint_cell(int x, int y, int inv=0)
{
    screencell *cell=screen_buffer->cell(x,y);
    int ucs=cell->getchar();
    int attr=cell->getattr();
    qtwindow->drawCell(y,x,ucs,attr,inv);
}


//------------------------------------------------------------------------------------------
static void paint_line(int y, int lef, int rig)
{
    int attr=0, i=0;
    wchar_t buf[wwidth];

    for( int x=lef; x<=rig; x++ )
    {
        screencell *cell=screen_buffer->cell(x,y);
        if( i>0 && attr!=cell->getattr() )
        {
            qtwindow->drawCells(y,lef,buf,i,attr);
            lef+=i;
            i=0;
        }
        buf[i++]=cell->getchar();
        attr=cell->getattr();
    }
    if(i>0)
    {
        qtwindow->drawCells(y,lef,buf,i,attr);
    }
}


#define SORONKENT
#ifdef  SORONKENT
//------------------------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    int y;
    for( y=top; y<=bot; y++) //ciklus a dirty rect soraira
    {
        paint_line(y,lef,rig);
    }
}


#else
//------------------------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    int x,y;
    for( y=top; y<=bot; y++) //ciklus a dirty rect soraira
    {
        for( x=lef; x<=rig; x++) //ciklus a dirty rect oszlopaira
        {
            paint_cell(x,y);
        }
    }
}
#endif

//------------------------------------------------------------------------------------------
static void blink(int flag)  //bg<->fg valtogatos kurzor
{
    static int prevx=0;
    static int prevy=0;

    if( flag==BLINK_UP ) 
    {
        if( cursor_state && (prevx!=cursor_x || prevy!=cursor_y) )
        {
            paint_cell(prevx,prevy);
        }
        paint_cell(cursor_x,cursor_y,1);

        prevx=cursor_x;
        prevy=cursor_y;
        cursor_state=1;
    }

    else if(cursor_state)
    {  
        //flag==BLINK_DN

        paint_cell(prevx,prevy);
        cursor_state=0;
    }
    
    cursor_tick=gettickcount();
}


//------------------------------------------------------------------------------------------
void invalidate(int t, int l, int b, int r)
{
    //printf("invalidate(%d,%d,%d,%d)",t,l,b,r);
    invalidate_lock();
    if(t<invtop) invtop=t;
    if(l<invlef) invlef=l;
    if(b>invbot) invbot=b;
    if(r>invrig) invrig=r;
    dirty_buffer=1;
    invalidate_unlock();
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
static void invalidate_qt()
{
    //printf("invalidate_qt()");
    invalidate_lock();
    paint(invtop,invlef,invbot,invrig);
    invtop=9999;
    invlef=9999;
    invbot=0;
    invrig=0;
    dirty_buffer=0;
    invalidate_unlock();
    //printf("!\n");
}


//------------------------------------------------------------------------------------------
void setcaption(char *cap)
{
    //printf("setcaption(%s)",cap);
    invalidate_lock();
    char buf[256];
    buf[0]='{';
    strncpy(buf+1,cap,200);
    strcat(buf,"}");
    free(caption);
    caption=strdup(buf);
    dirty_caption=1;
    invalidate_unlock();
    //printf("!\n");
}


//------------------------------------------------------------------------------------------
static void setcaption_qt()
{
    //printf("setcaption_qt()");
    invalidate_lock();
    qtwindow->setTitle(caption);
    dirty_caption=0;
    invalidate_unlock();
    //printf("!\n");
}


//------------------------------------------------------------------------------------------
void setwsize(int x, int y)
{
    //printf("setwsize(%d,%d)",x,y);
    invalidate_lock();
    wwidth=x;
    wheight=y;
    cursor_x=0;
    cursor_y=0;

    if(screen_buffer)
    {
        delete screen_buffer;
    }
    screen_buffer=new screenbuf(wwidth,wheight);

    invtop=0;
    invlef=0;
    invbot=wheight-1;
    invrig=wwidth-1;
    cursor_focus=1;
    dirty_buffer=1;
    dirty_size=1;

    invalidate_unlock();
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
static void setwsize_qt()
{
    //printf("setwsize_qt()");
    invalidate_lock();
    qtwindow->initsize();
    dirty_size=0;
    invalidate_unlock();
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
void setcursor(int x, int y)
{
    //printf("setcursor(%d,%d)",x,y);
    invalidate_lock();
    cursor_x=x;
    cursor_y=y;
    dirty_curpos=1;
    invalidate_unlock();
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
static void setcursor_qt()
{
    //printf("setcursor_qt()");
    invalidate_lock();
    if(cursor_onoff)
    {
        dirty_blink=BLINK_UP;
        qtwindow->update();
    }
    dirty_curpos=0;
    invalidate_unlock();
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
void setcursoroff()
{
    //printf("setcursoroff()");
    cursor_onoff=0;
    //printf("!\n");
}

//------------------------------------------------------------------------------------------
void setcursoron()
{
    //printf("setcursoron()");
    cursor_onoff=1;
    //printf("!\n");
}


//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int main (int argc, char **argv)
{
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

    QGuiApplication app(argc, argv);
    qtwindow=new TerminalWindow();

    tcpio_ini(host,port);
    #ifdef _UNIX_
      pthread_t t=0;
      pthread_create(&t,0,tcpio_thread,0); 
    #else
      DWORD threadid=0;
      CreateThread(0,0,(LPTHREAD_START_ROUTINE)tcpio_thread,0,0,&threadid);
    #endif
    sleep(100);

    qtwindow->show();
    return app.exec();
}

//------------------------------------------------------------------------------------------


