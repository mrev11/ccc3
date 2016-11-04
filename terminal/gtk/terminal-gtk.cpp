
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>

#include <pango/pango.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include <screenbuf.h>
//#include <inkey.ch>


static pthread_mutex_t mutex_inv=PTHREAD_MUTEX_INITIALIZER;
static void invalidate_lock(){pthread_mutex_lock(&mutex_inv);}
static void invalidate_unlock(){pthread_mutex_unlock(&mutex_inv);}

static pthread_mutex_t mutex_blink=PTHREAD_MUTEX_INITIALIZER;
static void blink_lock(){pthread_mutex_lock(&mutex_blink);}
static void blink_unlock(){pthread_mutex_unlock(&mutex_blink);}

//static pthread_mutex_t mutex_paint=PTHREAD_MUTEX_INITIALIZER;
//static void paint_lock(){pthread_mutex_lock(&mutex_paint);}
//static void paint_unlock(){pthread_mutex_unlock(&mutex_paint);}


screenbuf *screen_buffer=0;
static int wwidth=80;
static int wheight=25;
static int invtop=9999,invlef=9999,invbot=0,invrig=0;
static int dirty_buffer=0;

static GtkWidget *gtkwindow;
static GtkWidget *gtkview;
static GtkTextBuffer *gtkbuffer;


static int cursor_x=0;
static int cursor_y=0;
static int cursor_onoff=1;
static int cursor_state=0;
static unsigned cursor_tick=0;
static int cursor_focus=0;


extern void tcpio_ini(const char*,int);
extern void *tcpio_thread(void*);
extern void tcpio_sendkey(int);

extern void setcursor(int x,int y);
extern void setcursoroff(void);
extern void setcursoron(void);
extern void invalidate(int,int,int,int);
extern int  keycode_gtk(int,int);
extern int  color_palette(int);


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
PangoFontDescription *pangofont()
{
    const char *fontname="Monospace 14"; //FONTSPEC (space!)
    
    if( getenv("CCCTERM_GTKFONTSPEC") )
    {
        fontname=getenv("CCCTERM_GTKFONTSPEC");
    }

    PangoFontDescription *font=pango_font_description_from_string(fontname);
    return font;
}


//---------------------------------------------------------------------------
void setcaption(char *cap)
{
    //printf("%s\n",cap);
    gdk_threads_enter();
    gtk_window_set_title(GTK_WINDOW(gtkwindow),cap);
    gdk_threads_leave();
}

//---------------------------------------------------------------------------------
static int color_palette_rev(int x)
{
    //gtk-nak forditva kell
    int c=color_palette(x);
    int rr = c & 0x0000ff;
    int gg = c & 0x00ff00;
    int bb = c & 0xff0000;
    return (rr<<16) | gg | (bb>>16);
}

//---------------------------------------------------------------------------------
GtkTextTag *lookup_tag(int fg, int bg)
{
    GtkTextTagTable *tagtable=gtk_text_buffer_get_tag_table(gtkbuffer);

    char name[32];
    sprintf(name,"tag_%x_%x",fg,bg);
    GtkTextTag *t=gtk_text_tag_table_lookup(tagtable,name);
    if( t )
    {
        //printf("found: %s\n",name);
        return t;
    }
    char rgb_fg[128]; sprintf(rgb_fg,"#%06x",color_palette_rev(fg));
    char rgb_bg[128]; sprintf(rgb_bg,"#%06x",color_palette_rev(bg));
    //printf("fg %d %s bg %d %s \n", fg, rgb_fg, bg, rgb_bg);
    return gtk_text_buffer_create_tag(gtkbuffer,name,"foreground",rgb_fg,"background",rgb_bg,NULL); 
}

//----------------------------------------------------------------------------
static void setattr(int y, int x1, int x, int attr)  //beallit [x1,x) attr
{
    int fg=0xf&(attr>>0);
    int bg=0xf&(attr>>4);  
    GtkTextTag *tag=lookup_tag(fg,bg);

    GtkTextIter iter1, iter2;
    gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter1,y,x1);
    gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter2,y,x);
    gtk_text_buffer_apply_tag(gtkbuffer,tag,&iter1,&iter2);
}

//----------------------------------------------------------------------------
static void set_attrs_line(int y)
{
    GtkTextIter iter1,iter2;

    //elobb minden tagot torol
    gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter1,y,0);
    gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter2,y,wwidth);
    gtk_text_buffer_remove_all_tags(gtkbuffer,&iter1,&iter2);

    //minden tagot ujra beallit
    int x1=0,x;
    screencell *cell=screen_buffer->cell(x1,y);
    int attr=cell->getattr();
    for(x=1; x<wwidth; x++)
    {
        cell=screen_buffer->cell(x,y);
        if( cell->getattr()!=attr )
        {
            setattr(y,x1,x,attr); //[x1,x)-be attr
            x1=x;
            attr=cell->getattr();
        }
    }
    setattr(y,x1,x,attr); //[x1,x)-be attr
}

//----------------------------------------------------------------------------
static void paint(int top, int lef, int bot, int rig)
{
    gdk_threads_enter();

    int x,y;
    for( y=top; y<=bot; y++) //ciklus a dirty rect soraira
    {
        //1) magvaltozott szoveg csereje

        int i=0;
        wchar_t buf[1024];
        for(x=lef; x<=rig; x++)
        {
            screencell *cell=screen_buffer->cell(x,y);
            int c=cell->getchar();
            if( !g_unichar_validate(c) || c<32 )
            {
                c='@';
            }
            buf[i++]=c;
        }
        unsigned reslen;
        extern char* wchar_to_utf8(wchar_t const*, unsigned, unsigned *);
        char *p_utf8=wchar_to_utf8(buf,rig-lef+1,&reslen);

        GtkTextIter iter1,iter2;
        gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter1,y,lef);
        gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter2,y,rig+1);
        gtk_text_buffer_delete(gtkbuffer,&iter1,&iter2);
        gtk_text_buffer_insert(gtkbuffer,&iter2,p_utf8,reslen);
        free(p_utf8);

        //2) attributumok beallitasa az egesz sorban

        set_attrs_line(y);
    }

    gdk_threads_leave();
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

    //terminal-xft eventloop-bol inditja paint-et,
    //itt nincs eventloop (gtk_main belsejeben van), 
    //ugyhogy innnen indul a paint
    //az invtop,...,dirty_buffer nyilvantartas felesleges
    //az invalidate_lock() vedelem is felesleges

    paint(invtop,invlef,invbot,invrig);

    invtop=9999;
    invlef=9999;
    invbot=0;
    invrig=0;
    dirty_buffer=0;

    invalidate_unlock();
}


//----------------------------------------------------------------------------
static void blink(int flag)
{
    static int prevx=0;
    static int prevy=0;
    
    blink_lock();
    gdk_threads_enter();

    if( cursor_state )
    {
        set_attrs_line(prevy);
        cursor_state=0;
    }

    if( flag ) //bg<->fg váltogatós kurzor
    {
        screencell *cell=screen_buffer->cell(cursor_x,cursor_y);
        int attr=cell->getattr();
        int fg=0xf&(attr>>0);
        int bg=0xf&(attr>>4);
        cell->setattr((fg<<4)+bg);
        set_attrs_line(cursor_y);
        cell->setattr(attr);  //rogton vissza

        cursor_state=1;
        prevx=cursor_x;
        prevy=cursor_y;
    }

    cursor_tick=gettickcount();

    gdk_threads_leave();
    blink_unlock();
}

//----------------------------------------------------------------------------
void setwsize(int x, int y)
{
    gdk_threads_enter();

    wwidth=x;
    wheight=y;
    cursor_x=0;
    cursor_y=0;

    free(screen_buffer);
    screen_buffer=new screenbuf(wwidth,wheight);

    //ablakmeret:
    //a meretet az hatarozza meg, hogy mennyi text van benne
    //elore feltoltjuk annyi szoveggel, amekkoranak lennie kell,
    //es kesobb nem engedjuk valtoztatni a szoveg mennyiseget

    GtkTextIter iter1,iter2;
    gtk_text_buffer_get_iter_at_offset(gtkbuffer,&iter1,0);
    gtk_text_buffer_get_iter_at_offset(gtkbuffer,&iter2,-1);
    gtk_text_buffer_delete(gtkbuffer,&iter1,&iter2);
    
    int i;
    char *buf=(char*)malloc(wwidth);
    for(i=0;i<wwidth;i++)buf[i]=' ';
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(gtkbuffer,&iter,0);
    GtkTextTag *tag=lookup_tag(7,0); // w/n
    for( i=0; i<wheight-1; i++ )
    {
        gtk_text_buffer_insert_with_tags(gtkbuffer,&iter,buf,wwidth,tag,NULL);
        gtk_text_buffer_insert(gtkbuffer,&iter,"\n",1);
    }
    gtk_text_buffer_insert_with_tags(gtkbuffer,&iter,buf,wwidth,tag,NULL); //utolso sor \n nelkul
    free(buf);

    //kezdo kurzor pozicio
    gtk_text_iter_set_line(&iter,cursor_y);
    gtk_text_iter_set_line_offset(&iter,cursor_x);
    gtk_text_buffer_place_cursor(gtkbuffer,&iter);

    gdk_threads_leave();
}

//----------------------------------------------------------------------------
void setcursor(int x, int y)
{
    blink_lock();
    cursor_x=x;
    cursor_y=y;
    blink_unlock();

    if( cursor_onoff )
    {
        blink(1);
    }

    gdk_threads_enter();
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_line_offset(gtkbuffer,&iter,cursor_y,cursor_x);
    gtk_text_buffer_place_cursor(gtkbuffer,&iter);
    gdk_threads_leave();
}

//----------------------------------------------------------------------------
void setcursoroff()
{
    blink(cursor_onoff=0);
}

//----------------------------------------------------------------------------
void setcursoron()
{
    blink(cursor_onoff=1);
}


//----------------------------------------------------------------------------
static int cb_key_press_event(GtkWidget *widget, GdkEventKey*event, gpointer data)
{
    int keyval=event->keyval;
    int hwkeycode=event->hardware_keycode;
    int length=event->length;   //string hossza: 0,1,2
    char *string=event->string; //karakter UTF-8 kodolassal
    int asc=length?string[0]:0;

    int state=0;
    if(event->state & GDK_SHIFT_MASK)   state|=1;
    if(event->state & GDK_CONTROL_MASK) state|=2;
    if(event->state & GDK_MOD1_MASK)    state|=4; //Alt
    if(event->state & GDK_MOD2_MASK)    state|=8; //NumLock

    int code=0;
    
    //printf("%s %x %x\n", gdk_keyval_name(keyval), keyval, hwkeycode);
    
    if( keyval==GDK_KEY_Delete )
    {
        //ez jon a normal delete-re is
        //es a KP delete-re is NumLock-tol fuggetlenul
        //csak a hwkeycode mutatja a KP delete esetet

        if( (hwkeycode!=0x5b) )
        {
            //nem KP_Delete
            code=keycode_gtk(GDK_KEY_Delete,state);
        }
        else if( (state&8)==0 )
        {
            //KP_Delete, de nem NumLock
            code=keycode_gtk(GDK_KEY_KP_Delete,state);
        }
        else
        {
            //KP_Delete + NumLock
            code='.';
        }
    }
    else if( length==0 )
    {
        extern int keycode_gtk(int keyval,int state);
        code=keycode_gtk(keyval,state);
    }
    else if( asc>=128 )
    {
        extern int utf8_to_ucs(const char*string, int*);
        utf8_to_ucs(string,&code);
    }
    else
    {
        if( (state&4) && 'a'<=asc  && asc<='z' )
        {
            code=-(asc-'a'+1); //ALT_A,...,ALT_Z
        }
        else
        {
            code=asc;
        }
    }

    //printf("code=%d state=%d keyval=%x length=%d string=[%s] asc=%d\n", code,state,keyval,length,string,asc);

    if( code )
    {
        tcpio_sendkey(code);
    }

    return 1;
}

//----------------------------------------------------------------------------
static int cb_focus_in_event()
{
    //printf( "focus IN\n");
    cursor_focus=1;
    return 0;
}

//----------------------------------------------------------------------------
static int cb_focus_out_event()
{
    //printf( "focus OUT\n");
    cursor_focus=0;
    return 0;
}

//----------------------------------------------------------------------------
static int cb_timeout(void*data)
{
    unsigned tick=gettickcount()-cursor_tick;

    if( cursor_state && tick>400  )
    {
        blink(0);
    }
    else if( cursor_onoff && cursor_focus && !cursor_state && tick>200  )
    {
        blink(1);
    }
    return 1;
}

//----------------------------------------------------------------------------
int main(int argc, char *argv[]) 
{
    gdk_threads_init();
    gtk_init(&argc, &argv);

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

    //gtkwindow > vbox > gtkview > gtkbuffer
    gtkwindow=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *vbox=gtk_vbox_new(FALSE,0); gtk_container_add(GTK_CONTAINER(gtkwindow),vbox);
    gtkview=gtk_text_view_new(); gtk_box_pack_start(GTK_BOX(vbox), gtkview, TRUE, TRUE, 0);
    gtkbuffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkview));

    g_signal_connect(G_OBJECT(gtkwindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(gtkwindow),"key_press_event",G_CALLBACK(cb_key_press_event),NULL);
    g_signal_connect(G_OBJECT(gtkwindow),"focus-in-event",G_CALLBACK(cb_focus_in_event),NULL);
    g_signal_connect(G_OBJECT(gtkwindow),"focus-out-event",G_CALLBACK(cb_focus_out_event),NULL);

    //agybaj, ahogy magatol pozicional
    //gtk_window_set_position(GTK_WINDOW(gtkwindow),GTK_WIN_POS_NONE);
    //gtk_window_set_position(GTK_WINDOW(gtkwindow),GTK_WIN_POS_CENTER);
    int dx=gettickcount()%300;
    int dy=gettickcount()%100;
    gtk_window_move(GTK_WINDOW(gtkwindow),80+dx,60+dy);

    gtk_window_set_resizable(GTK_WINDOW(gtkwindow),0);
    gtk_window_set_title(GTK_WINDOW(gtkwindow),"terminal-gtk");

    gtk_text_view_set_editable(GTK_TEXT_VIEW(gtkview),0);
    gtk_widget_modify_font(gtkview,pangofont());

    setwsize(wwidth,wheight);

    gdk_threads_enter();

    tcpio_ini(host,port);
    pthread_t t=0;
    pthread_create(&t,0,tcpio_thread,0); 
    sleep(100);

    gtk_widget_show_all(gtkwindow);
    gtk_timeout_add(50,cb_timeout,NULL);
    gtk_main();

    gdk_threads_leave();
    return 0;
}

//----------------------------------------------------------------------------

