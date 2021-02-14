
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


//2016.12.01
//a korabbi program atirva olyan szervezesure,
//ahogy a (jol sikerult) gtk-s terminal mukodik:
//a tcpio szal kizarolag csak letarolja a valtozasokat,
//minden kepernyo muveletet az eventloop szal vegez. 


#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/times.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xft/Xft.h>

#include <keysym2ucs.h>
#include <screenbuf.h>
#include <inkey.ch>

#define THREAD_ENTRY /*nothing*/

static pthread_mutex_t mutex_inv=PTHREAD_MUTEX_INITIALIZER;
static void invalidate_lock(){pthread_mutex_lock(&mutex_inv);}
static void invalidate_unlock(){pthread_mutex_unlock(&mutex_inv);}


screenbuf *screen_buffer;
static int wwidth=80;
static int wheight=25;
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

static int fontwidth,fontheight,fontascent;

Display *display;
Window window;
GC gc;

Colormap colormap;
int screen;
XftDraw *draw;
Visual *visual;
XftColor xft_color[16];
XftColor xft_color_ext[128];
XftFont *xftfont;

extern void tcpio_ini(const char*,int);
extern THREAD_ENTRY void *tcpio_thread(void*);
extern void tcpio_sendkey(int);
extern void xsigset_handlers();

extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);
extern void invalidate(int,int,int,int);
extern void keypress(XEvent event);
extern int  color_palette(int);
extern int  colorext_palette(int);
extern void fontspec(const char *envname, char **fontface, int *fontsize);

//---------------------------------------------------------------------------
static unsigned gettickcount(void)
{
    struct tms buf;
    return (unsigned)times(&buf)*10;
}

//---------------------------------------------------------------------------
static void sleep(int ms)
{
    if(ms>0)
    {
        struct timeval t;
        t.tv_sec=ms/1000;
        t.tv_usec=(ms%1000)*1000;
        select(0,NULL,NULL,NULL,&t);
    }
}

//---------------------------------------------------------------------------
static XftFont *xft_loadfont()
{
    char fontname[1024];
    char *fontface;
    int fontsize;
    fontspec("CCCTERM_XFTFONTSPEC",&fontface,&fontsize); //environment
    sprintf(fontname,"%s-%d",fontface,fontsize);
    //printf("FONT %s\n",fontname);fflush(0);

    XftFont *font=XftFontOpenName(display,screen,fontname);
    if( font==0 )
    {
        fprintf(stderr,"Cannot load Xft font: %s\n",fontname);
        exit(1);
    }
    return font;
}


//---------------------------------------------------------------------------
static XFontStruct *loadfont()
{
    const char *fontname="-misc-console-medium-r-normal--16-160-72-72-c-80-iso10646-1";
    
    if( getenv("CCCTERM_FONTSPEC") )
    {
        //Bármelyik fix, unicode (iso10646) font megfelel.
        //Ilyen unicode fontok vannak a KDE-ben:
        
        //-misc-fixed-medium-r-normal--15-140-75-75-c-90-iso10646-1
        //-misc-console-medium-r-normal--16-160-72-72-c-80-iso10646-1
        //-misc-console-medium-r-normal--8-80-72-72-c-80-iso10646-1
        
        fontname=getenv("CCCTERM_FONTSPEC");
    }

    XFontStruct *font=XLoadQueryFont(display,fontname);
    if( font==0 )
    {
        fprintf(stderr,"Cannot load font: %s\n",fontname);
        exit(1);
    }
    return font;
}

//----------------------------------------------------------------------------
static void paintline(int cx, int cy, wchar_t *txt, int txtlen, int attr, int flag)
{
    //tárolja a képernyőt
    //ha flag==1, akkor mindent kiír
    //ha flag==0, akkor csak a változást írja ki

    static int bufsiz=0;
    static wchar_t *buftext=0;
    static int *bufattr=0;
    if( bufsiz<(wwidth+1)*(wheight+1) )
    {
        bufsiz=(wwidth+1)*(wheight+1);
        buftext=(wchar_t*)realloc(buftext,bufsiz*sizeof(wchar_t));
        bufattr=(int*)realloc(bufattr,bufsiz*sizeof(int));
    }

    int pos0=cy*wwidth+cx,pos;
    int chg=0,lef=0,rig=0;
   
    for(pos=0; pos<txtlen; pos++)
    {
        if( buftext[pos0+pos]!=txt[pos] || bufattr[pos0+pos]!=attr )
        {
            chg=1;  //changed
            rig=0;  //right trim
        }
        else if( flag==0 )
        {
            if( chg==0 )
            {
                lef++; //left trim
            }
            rig++; //right trim
        }
        buftext[pos0+pos]=txt[pos];
        bufattr[pos0+pos]=attr;
    }

    if( flag || chg )
    {
        cx+=lef;       //left trim
        txt+=lef;      //left trim
        txtlen-=lef;   //left trim
        txtlen-=rig;   //right trim

        int x=cx*fontwidth;
        int y=cy*fontheight;//+fontascent;

        XRectangle r;
        r.x = 0;
        r.y = 0;
        r.width = txtlen*fontwidth;
        r.height = fontheight;
        XftDrawSetClipRectangles(draw,x,y,&r,1);

        //az Xft fontok neha kilognak a teglalapjukbol,
        //korabban az elszemetesedes ellen ugy vedekeztem,
        //hogy egy pixellel nagyobb teglalapot toroltem a bg-vel,
        //de nem ez kell, hanem ki-be kell kapcsolgatni a clip-et,
        //ami a kilogo szemeteket levagja

        if( attr&0xff00 )
        {
            int fg=0x7f&(attr>>0); //jelzobit leveve
            int bg=0x7f&(attr>>8); //jelzobit leveve
            XftDrawRect(draw,&xft_color_ext[bg],x,y,txtlen*fontwidth,fontheight);
            XftDrawString32(draw,&xft_color_ext[fg],xftfont,x,y+fontascent,(FcChar32*)txt,txtlen);
        }
        else
        {
            int fg=0xf&(attr>>0);
            int bg=0xf&(attr>>4);
            XftDrawRect(draw,&xft_color[bg],x,y,txtlen*fontwidth,fontheight);
            XftDrawString32(draw,&xft_color[fg],xftfont,x,y+fontascent,(FcChar32*)txt,txtlen);

            //MEGOLDAS: XftDrawSetClipRectangles
            //nem lehet kitalalni, hogy mekkora teglalapot kell torolni,
            //a kulonbozokeppen skalazott fontok kilognak a teglalapjukbol,
            //ha tul kicsit torlok, elszemetesedik a kepernyo,
            //ha tul nagyot torlok, akkor meg hezagos lesz a kepernyo
        }

        XftDrawSetClip(draw, 0);
        //printf("paintline: %d %d %d\n",cy,cx,txtlen); fflush(0);
    }
}

//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig, int flag)
{
    //static int cnt=0;
    //printf("%d (%d,%d,%d,%d)\n",++cnt,top,lef,bot,rig);fflush(0);

    int x,y;
    for( y=top; y<=bot; y++ )
    {
        wchar_t buf[2048];
        int buflen=0;
        wchar_t *bufptr=buf;
        int attr=0,x0=lef;

        for( x=lef; x<=rig; x++ )
        {
            screencell *cell=screen_buffer->cell(x,y);
            if( (buflen>0) && (cell->getattr()!=attr) )
            {
                paintline(x0,y,buf,buflen,attr,flag);
                buflen=0;
                bufptr=buf;
                attr=cell->getattr();
                x0=x;
            }
            attr=cell->getattr();
            int ch=cell->getchar();
            if(ch==0x2018) ch=0x60; //`
            if(ch==0x2019) ch=0x27; //'
            *bufptr++=ch;
            buflen++;
        }
        if( buflen>0 )
        {
            paintline(x0,y,buf,buflen,attr,flag);
        }
    }
    XFlush(display);
}

//----------------------------------------------------------------------------
static void blink(int flag) //bg<->fg váltogatós kurzor
{
    static int prevx=0;
    static int prevy=0;

    if( flag ) 
    {
        if( cursor_state && (prevx!=cursor_x || prevy!=cursor_y) )
        {
            paint(prevy,prevx,prevy,prevx,1);
            cursor_state=0;
        }

        screencell *cell=screen_buffer->cell(cursor_x,cursor_y);
        int attr=cell->getattr();
        if( attr&0xff00 )
        {
            int fg=0xff&(attr>>0);
            int bg=0xff&(attr>>8);
            cell->setattr((fg<<8)+bg);
        }
        else
        {
            int fg=0xf&(attr>>0);
            int bg=0xf&(attr>>4);
            cell->setattr((fg<<4)+bg);
        }
        paint(cursor_y,cursor_x,cursor_y,cursor_x,1);
        cell->setattr(attr);  //rogton vissza

        prevx=cursor_x;
        prevy=cursor_y;
        cursor_state=1;
    }
    else if(cursor_state)
    {
        paint(prevy,prevx,prevy,prevx,1);
        cursor_state=0;
    }

    cursor_tick=gettickcount();
}

//----------------------------------------------------------------------------
void invalidate(int t, int l, int b, int r)
{
    //printf("dirty (%d,%d,%d,%d)\n",t,l,b,r);
    invalidate_lock();
    if(t<invtop) invtop=t;
    if(l<invlef) invlef=l;
    if(b>invbot) invbot=b;
    if(r>invrig) invrig=r;
    dirty_buffer=1;
    invalidate_unlock();
    //printf("!\n");
}

//----------------------------------------------------------------------------
static void invalidate_loop()
{
    invalidate_lock();
    paint(invtop,invlef,invbot,invrig,0);
    invtop=9999;
    invlef=9999;
    invbot=0;
    invrig=0;
    dirty_buffer=0;
    invalidate_unlock();
}

//----------------------------------------------------------------------------
void setcaption(char *cap)
{
    invalidate_lock();
    char buf[256];
    buf[0]='<';
    strncpy(buf+1,cap,200);
    strcat(buf,">");
    free(caption);
    caption=strdup(buf);
    dirty_caption=1;
    invalidate_unlock();
}


//----------------------------------------------------------------------------
static void setcaption_loop()
{
    invalidate_lock();
    XSetStandardProperties(display,window,caption,0,0,0,0,0); 
    dirty_caption=0;
    invalidate_unlock();
}


//----------------------------------------------------------------------------
void setwsize(int x, int y)
{
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
}

//----------------------------------------------------------------------------
static void setwsize_loop()
{
    invalidate_lock();

    //XUnmapWindow(display,window);  //hide window
    static XSizeHints size_hints;
    size_hints.flags = PSize | PMinSize | PMaxSize;
    size_hints.min_width  = wwidth*fontwidth;
    size_hints.max_width  = wwidth*fontwidth;
    size_hints.min_height = wheight*fontheight;
    size_hints.max_height = wheight*fontheight;
    XSetStandardProperties(display,window,0,0,0,0,0,&size_hints); 
    //XMapWindow(display,window);  //show window

    dirty_size=0;

    invalidate_unlock();
}

//----------------------------------------------------------------------------
void setcursor(int x, int y)
{
    //printf("setcursor %d %d\n",x,y);
    invalidate_lock();
    cursor_x=x;
    cursor_y=y;
    dirty_curpos=1;
    invalidate_unlock();
}


//----------------------------------------------------------------------------
static void setcursor_loop()
{
    //printf("setcursor_loop\n");
    invalidate_lock();
    if(cursor_onoff)
    {
        blink(1);
    }
    dirty_curpos=0;
    invalidate_unlock();
}

//----------------------------------------------------------------------------
void setcursoroff()
{
    cursor_onoff=0;
}

//----------------------------------------------------------------------------
void setcursoron()
{
    cursor_onoff=1;
}

//----------------------------------------------------------------------------
static void timeout()
{
    #ifdef NOTDEFINED
    printf("timeout S%d B%d T%d C%d\n", 
            dirty_size, 
            dirty_buffer,
            dirty_caption, 
            dirty_curpos);
    #endif

    if( dirty_size ) //ennek kell elol lenni!
    {
        setwsize_loop();
    }
    else if( dirty_buffer )
    {
        invalidate_loop();
    }
    else if( dirty_caption )
    {
        setcaption_loop();
    }

    if( dirty_curpos )
    {
        setcursor_loop();
    }

    unsigned tick=gettickcount()-cursor_tick;

    if( cursor_state && tick>400  )
    {
        blink(0);
    }
    else if( cursor_onoff && cursor_focus && !cursor_state && tick>200  )
    {
        blink(1);
    }
}

//----------------------------------------------------------------------------
static void eventloop()
{
    while(1)
    {
        XFlush(display);
        while( 0<XPending(display) )
        {
            XEvent event;
            XNextEvent(display,&event);

            if( event.type==Expose ) 
            {
                //xevent->count jelentése:
                //legalább ennyi expose message van még a queue-ban,
                //megvárjuk az utolsót (count==0), és csak akkor rajzolunk,
                //addig gyűjtjük az invalid területet.

                XExposeEvent *xevent=(XExposeEvent*)&event;

                int c=xevent->count;
                int x=xevent->x;
                int y=xevent->y;
                int w=xevent->width;
                int h=xevent->height;

                //printf("E %d (%d %d %d %d)\n",c,x,y,w,h );fflush(0);

                static int top=9999;
                static int lef=9999;
                static int bot=0;
                static int rig=0;

                if( top > y/fontheight     ) top=y/fontheight;     //max
                if( lef > x/fontwidth      ) lef=x/fontwidth;      //max
                if( bot < (y+h)/fontheight ) bot=(y+h)/fontheight; //min
                if( rig < (x+w)/fontwidth  ) rig=(x+w)/fontwidth;  //min
        
                if( xevent->count==0 )
                {   
                    //printf("EXPOSE (%d,%d,%d,%d)\n",top,lef,bot,rig);fflush(0);
                    paint(top,lef,bot,rig,1);
                    top=9999;
                    lef=9999;
                    bot=0;
                    rig=0;
                }
            }
            else if( event.type==KeyPress )
            {
                //printf("K");fflush(0);
                keypress(event);
            }
            else if( event.type==FocusIn )
            {
                //printf("Fi");fflush(0);
                cursor_focus=1;
            }
            else if( event.type==FocusOut )
            {
                //printf("Fo");fflush(0);
                cursor_focus=0;
            }
        }

        timeout();
        sleep(10);
    }
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[]) 
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
    if( getenv("CCCTERM_SIZE") )
    {
        sscanf(getenv("CCCTERM_SIZE"),"%dx%d",&wwidth,&wheight);
    }

    xsigset_handlers();

    screen_buffer=new screenbuf(wwidth,wheight);

    XInitThreads();  //libxcb hiba

    display=XOpenDisplay(NULL);
    if(display==NULL) 
    {
        fprintf(stderr,"Cannot open display\n");
        exit(1);
    }

    screen=DefaultScreen(display);
    colormap=DefaultColormap(display,screen);
    window=XCreateSimpleWindow(display,RootWindow(display,screen),200,100,60,60,0,0,0);
    visual=DefaultVisual(display,screen);
    draw=XftDrawCreate(display,window,visual,colormap);

    XSetWindowColormap(display,window,colormap);

    for(int x=0; x<16; x++)
    {
        int rgb=color_palette(x);

        XftColor xftcol;
        xftcol.color.red   = (0xff&(rgb>> 0))<<8;
        xftcol.color.green = (0xff&(rgb>> 8))<<8;
        xftcol.color.blue  = (0xff&(rgb>>16))<<8;
        xftcol.color.alpha = -1;
        int xftres=XftColorAllocValue(display,visual,colormap,&xftcol.color,&xftcol);
        xft_color[x]=xftcol;
        //printf("XftAllocColor %06x %d %06lx\n",(unsigned)rgb,xftres,(unsigned long)xftcol.pixel);fflush(0);
    }

    for(int x=0; x<128; x++)
    {
        int rgb=colorext_palette(x);

        XftColor xftcol;
        xftcol.color.red   = (0xff&(rgb>>16))<<8;
        xftcol.color.green = (0xff&(rgb>> 8))<<8;
        xftcol.color.blue  = (0xff&(rgb>> 0))<<8;
        xftcol.color.alpha = -1;
        int xftres=XftColorAllocValue(display,visual,colormap,&xftcol.color,&xftcol);
        xft_color_ext[x]=xftcol;
    }
    
    XGCValues values;
    gc=XCreateGC(display,window,0,&values);


    //core X
    //XFontStruct *font=loadfont();
    //XSetFont(display,gc,font->fid);
    //fontwidth=font->max_bounds.width;
    //fontheight=font->max_bounds.ascent+font->max_bounds.descent;
    //fontascent=font->max_bounds.ascent;

    //Xft 
    xftfont=xft_loadfont();
    fontwidth=xftfont->max_advance_width;
    fontheight=xftfont->ascent+xftfont->descent;
    fontascent=xftfont->ascent;


    tcpio_ini(host,port);
    pthread_t t=0;
    pthread_create(&t,0,tcpio_thread,0); 
    sleep(100);

    static XSizeHints size_hints;
    size_hints.flags = PSize | PMinSize | PMaxSize;
    size_hints.min_width  = wwidth*fontwidth;
    size_hints.max_width  = wwidth*fontwidth;
    size_hints.min_height = wheight*fontheight;
    size_hints.max_height = wheight*fontheight;

    XSetStandardProperties(display,window,0,0,0,0,0,&size_hints); 

    XSelectInput(display,window,ExposureMask|KeyPressMask|FocusChangeMask);
    XMapWindow(display,window);

    eventloop();

    XCloseDisplay(display);
    return 0;
}

//----------------------------------------------------------------------------

