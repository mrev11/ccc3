
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

#define VERSION "CCC Terminal 2.0.00"

#define UNICODE

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <screenbuf.h>
#include <ansi_rgb.h>

#define THREAD_ENTRY __stdcall

extern void keychar(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
extern void keydown(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
extern void keyup(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
extern void tcpio_ini(const char *ip, int port); 
extern THREAD_ENTRY void *tcpio_thread(void*); 
extern HFONT font();

static int wwidth=80;
static int wheight=25;
static int fwidth=0;
static int fheight=0;

static int focus_onoff=1;
static int caret_onoff=1;
static int caret_x=0;
static int caret_y=0;

static HFONT term_font=0;
static HWND term_window=0;

screenbuf *screen_buffer=0;


#define RWID(r) (r.right-r.left)
#define RHIG(r) (r.bottom-r.top)

#define NEWTHREAD(t) CreateThread(0,0,(LPTHREAD_START_ROUTINE)t,0,0,NULL);


#undef min
#undef max
#define min(x,y)   ((x)<(y)?(x):(y))
#define max(x,y)   ((x)>(y)?(x):(y))

 
//---------------------------------------------------------------------------
static void setcaret(HWND hwnd)
{
    static int create=0;
    static int status=0;

    if( caret_onoff && focus_onoff )
    {
        int x=caret_x;
        int y=caret_y;
        int fw=fwidth;       
        int fh=fheight;       

        if( create==0 )
        {
            int r=CreateCaret(hwnd,NULL,fw,fh/5); 
            if( !r )
            {
                printf("CREATECARET %d %d\n",r,GetLastError());fflush(0);
            }
            create=1;
        }

        SetCaretPos(x*fw,(y+1)*fh-fh/5); 
        
        if( status==0 )
        {
            int r=ShowCaret(hwnd);
            if( !r )
            {
                printf("SHOWCARET %d %d\n",r,GetLastError());fflush(0);
            }
            status=1;
        }
    }
    else
    {
        if( status==1 )
        {
            int r=HideCaret(hwnd);
            if( !r )
            {
                printf("HIDECARET %d %d\n",r,GetLastError());fflush(0);
            }
            status=0;
        }
    }
}


//---------------------------------------------------------------------------
void setwsize(int x, int y)
{
    wwidth=x;
    wheight=y;
    
    screenbuf *sb=screen_buffer;
    screen_buffer=new screenbuf(wwidth,wheight);
    if( sb )
    {
        delete sb;
    }
    
    HWND hwnd=term_window;

    RECT rect; GetWindowRect(hwnd,&rect);
    RECT crect; GetClientRect(hwnd,&crect);
 
    SetWindowPos( hwnd,
                  HWND_TOP,
                  rect.left,
                  rect.top,
                  RWID(rect)-RWID(crect)+wwidth*fwidth,
                  RHIG(rect)-RHIG(crect)+wheight*fheight,
                  0 );
}

//---------------------------------------------------------------------------
void setcursor(int x, int y)
{
    caret_x=x;       
    caret_y=y;       
    if( caret_onoff && focus_onoff )
    {
        PostMessage(term_window,WM_SETFOCUS,0,0);
    }
}

//---------------------------------------------------------------------------
void setcursoroff()
{
    caret_onoff=0;
    if( focus_onoff )
    {
        PostMessage(term_window,WM_KILLFOCUS,0,0);
        PostMessage(term_window,WM_SETFOCUS,0,0);
    }
}    

//---------------------------------------------------------------------------
void setcursoron()
{
    caret_onoff=1;
    if( focus_onoff )
    {
        PostMessage(term_window,WM_SETFOCUS,0,0);
    }
}

//---------------------------------------------------------------------------
void setcaption(char *cap)
{
    extern wchar_t *utf8_to_wchar(char const*,unsigned,unsigned*);
    wchar_t *txt=utf8_to_wchar(cap,strlen(cap),0);
    SetWindowText(term_window,txt);
    free(txt);
}


//---------------------------------------------------------------------------
void invalidate(int t,int l,int b,int r)
{
    int fw=fwidth; 
    int fh=fheight; 
                
    RECT rect;
    rect.top    = t*fh;
  //rect.left   = l*fw; 
    rect.left   = max(0,l*fw-1); //Windows 2000-en ez nem kellett
    rect.bottom = (b+1)*fh;  
    rect.right  = (r+1)*fw;   
 
    InvalidateRect(term_window,&rect,0);
}


//---------------------------------------------------------------------------
static int ANSIRGB(int x)
{
    int r,g,b;
    ansi_rgb(x,&r,&g,&b);
    return (b<<16)|(g<<8)|r;
    
    // VIGYAZZ
    // egyes helyeken a 'b'
    // mas helyeken  az 'r'
    // a legkisebb helyerteku bit
}

//---------------------------------------------------------------------------
LRESULT CALLBACK WindowProcMain(
    HWND    hwnd,               // handle of window
    UINT    msg,                // message identifier
    WPARAM  wParam,             // first message parameter
    LPARAM  lParam              // second message parameter
)
{
    switch (msg)
    {
        case WM_CREATE:
        {      
            HDC hdc=GetDC(hwnd);            
            SelectObject(hdc,term_font);
            TEXTMETRIC tm;
            GetTextMetrics(hdc,&tm);
            ReleaseDC(hwnd,hdc);
            fwidth=tm.tmAveCharWidth;
            fheight=tm.tmHeight;

            RECT rect; GetWindowRect(hwnd,&rect);
            RECT crect; GetClientRect(hwnd,&crect);
 
            SetWindowPos( hwnd,
                          HWND_TOP,
                          rect.left,
                          rect.top,
                          RWID(rect)-RWID(crect)+wwidth*fwidth,
                          RHIG(rect)-RHIG(crect)+wheight*fheight,
                          0 );
            break;
        }

        case WM_DESTROY:
        {
            DeleteObject(term_font); 
            PostQuitMessage(0);
            break;
        }

        case WM_SYSDEADCHAR:
        case WM_DEADCHAR:
        case WM_SYSCHAR:
        case WM_CHAR:
        {
            keychar(hwnd,msg,wParam,lParam);
            break;
        }

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            keydown(hwnd,msg,wParam,lParam);
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            keyup(hwnd,msg,wParam,lParam);
            break;
        }
 
        case WM_SETFOCUS:
        {
            focus_onoff=1;
            setcaret(hwnd);
            return DefWindowProc(hwnd,msg,wParam,lParam);
        }

        case WM_KILLFOCUS:
        {
            focus_onoff=0;
            setcaret(hwnd);
            return DefWindowProc(hwnd,msg,wParam,lParam);
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hwnd,&ps);

            int fw=fwidth;
            int fh=fheight; 
            int ww=wwidth;
            int wh=wheight; 

            int top    = max((int)ps.rcPaint.top/fh-1,0);
            int left   = max((int)ps.rcPaint.left/fw-1,0);
            int bottom = min((int)ps.rcPaint.bottom/fh+1,wh);
            int right  = min((int)ps.rcPaint.right/fw+1,ww);
            
            //Ha top=0, left=0, bottom=wh, right=ww értékekkel 
            //dolgozunk, akkor mindig az egész ablak kifestődik, 
            //és ez néha villogást okoz.

            //Ha a téglalap méretét nem növelném meg 1-gyel
            //minden irányban, akkor egy másik ablakot elhúzva
            //a terminál fölött, a terminálablak csíkos maradna. 
            //Szerintem a Windows pontatlanul kezeli az update region-t.
           

            SelectObject(hdc,term_font);
            SetBkMode(hdc,OPAQUE);

            int i,j;
            for( i=top; i<bottom; i++ )
            {
                int ifh=i*fh;
            
                for( j=left; j<right; j++ )
                {
                    wchar_t t=(wchar_t)(screen_buffer->cell(j,i)->getchar()); 
                    unsigned c=(unsigned)(screen_buffer->cell(j,i)->getattr()); 
                    
                    int fg=screen_buffer->cell(j,i)->get_fg();
                    int bg=screen_buffer->cell(j,i)->get_bg();
 
                    SetBkColor(hdc,ANSIRGB(bg));
                    SetTextColor(hdc,ANSIRGB(fg));
                    
                    #ifdef NO_OPTIMIZE
                    
                      //ez is működne
                    
                      TextOut(hdc,j*fw,ifh,&t,1);
                    
                    #else

                      //de gyorsabb összegyűjteni az azonos
                      //színű szöveget és egyszerre kiírni
                      
                      int k,k1=0;
                      wchar_t buf1[1024];
                      buf1[0]=t;

                      for( k=j+1; k<right; k++ )
                      {
                          wchar_t t1=(wchar_t)screen_buffer->cell(k,i)->getchar(); 
                          unsigned c1=(unsigned)screen_buffer->cell(k,i)->getattr(); 

                          if( c==c1 )
                          {
                              buf1[++k1]=t1;
                          }
                          else
                          {
                              break;
                          }
                      }
                      TextOut(hdc,j*fw,ifh,(wchar_t*)buf1,1+k1);
                      j+=k1;

                    #endif
                }
            }
            EndPaint(hwnd,&ps);
            break;
        }
 
        default:
        {
            //printf("WM %x %x %lx\n",msg,wParam,lParam);fflush(0);
            //printf("WM %d %x %lx\n",msg,wParam,lParam);fflush(0);
            return DefWindowProc(hwnd,msg,wParam,lParam);
        }
    }
    return 0;
}


//---------------------------------------------------------------------------
ATOM register_main_window(HINSTANCE hInstance) 
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW; 
    wc.lpfnWndProc   = WindowProcMain;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL,IDI_APPLICATION); ;
    wc.hCursor       = LoadCursor(NULL,IDC_ARROW); 
    wc.hbrBackground = NULL; //(HBRUSH)GetStockObject(HOLLOW_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = L"terminal_window";
    
    return RegisterClass(&wc);
}

//---------------------------------------------------------------------------
HWND create_main_window(HINSTANCE hInstance)
{
    DWORD style=WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;

    return  CreateWindow(
    L"terminal_window",   // address of registered class name
    L"",                  // address of window name
    style,                // window style
    CW_USEDEFAULT,        // horizontal position of window
    CW_USEDEFAULT,        // vertical position of window
    CW_USEDEFAULT,        // window width
    CW_USEDEFAULT,        // window height
    (HWND)NULL,           // handle of parent or owner window
    (HMENU)NULL,          // handle of menu or child-window identifier
    hInstance,            // handle of application instance
    NULL                  // address of window-creation data
   );
}

//---------------------------------------------------------------------------
int WINAPI WinMain(
    HINSTANCE  hInstance,       // handle of current instance
    HINSTANCE  hPrevInstance,   // handle of previous instance
    LPSTR      lpszCmdLine,     // pointer to command line
    int        nCmdShow         // show state of window
    )   
{
    //FreeConsole(); //ne zavarjon be CTRL_C (2008.11.13)
    //FreeConsole() kivéve:
    //Konzol nélkül nem látszanak az esetleges hibaüzenetek. 
    //Nem világos, hogy egyáltalán miért van konzol, amikor a doksik
    //azt állítják, attól függ, hogy WinMain vagy main a főprogram.
    //Mindenképpen megjelenik a konzol, mielőtt FreeConsole leszedné.
   

    //Ez allit valamit a rendszerparameterekben,
    //maskepp Win2K-n hatastalan a SetForegroundWindow.
    //Az info az MS knowledgebase-bol szarmazik.
    //Egy gepen csak egyszer kell vegrehajtani, 
    //a hatas megmarad, nem kell hozza admin jogkor.
    //Igy viszont nem is kell a SetForegroundWindow.
    
    //int result=SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, (LPVOID)0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
    int result=SystemParametersInfo(0x2001, 0, (LPVOID)0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
    //printf("\nSystemParametersInfo %d %d\n",result,GetLastError());


    char host[128]; strcpy(host,"127.0.0.1"); 
    int  port=55000;
    
    if( lpszCmdLine && *lpszCmdLine )
    {
        int i;
        for( i=0; i<127; i++ )
        {
            if( (lpszCmdLine[i]==0) || (lpszCmdLine[i]==' ')  )
            {
                 break;   
            }
            host[i]=lpszCmdLine[i];
        }
        host[i]=0;
    
        if( lpszCmdLine[i]==' ' )
        {
            sscanf(lpszCmdLine+i,"%d",&port);
        }
    }
   
    if( getenv("CCCTERM_SIZE") )
    {
        sscanf(getenv("CCCTERM_SIZE"),"%dx%d",&wwidth,&wheight);
    }
    screen_buffer=new screenbuf(wwidth,wheight);

    tcpio_ini(host,port);
    
    term_font=font();
    register_main_window(hInstance);
    term_window=create_main_window(hInstance);

    NEWTHREAD(tcpio_thread);
    Sleep(100);
    ShowWindow(term_window,SW_SHOW);
    SetForegroundWindow(term_window);

    MSG msg;
    while( GetMessage(&msg,NULL,0,0) )
    {     
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ExitProcess(0);
    return 0;
} 


//---------------------------------------------------------------------------
