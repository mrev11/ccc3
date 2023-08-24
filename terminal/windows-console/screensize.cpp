
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------
static void lock_term_size()
{
    HWND hwnd=GetConsoleWindow();
    LONG wlng=GetWindowLong(hwnd,GWL_STYLE);
    SetWindowLong(hwnd,GWL_STYLE, wlng & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX );
}

//----------------------------------------------------------------------------------------
static void unlock_term_size()
{
    HWND hwnd=GetConsoleWindow();
    LONG wlng=GetWindowLong(hwnd,GWL_STYLE);
    SetWindowLong(hwnd,GWL_STYLE, wlng | WS_MAXIMIZEBOX | WS_SIZEBOX );
}

//----------------------------------------------------------------------------------------
void screensize(int *x, int *y)  // lekerdezi a terminal meretet
{
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    if( hOut==INVALID_HANDLE_VALUE )
    {
        printf("GetStdHandle failed %d\n",(int)GetLastError());
        getchar();
        exit(1);
    }

    CONSOLE_SCREEN_BUFFER_INFO info;
    if( !GetConsoleScreenBufferInfo(hOut,&info) )
    {
        printf("GetConsoleScreeBufferInfo failed %d\n",(int)GetLastError());
        getchar();
        exit(1);
    }
    int width = (info.srWindow.Right-info.srWindow.Left+1);
    int heigh = (info.srWindow.Bottom-info.srWindow.Top+1);
    if( !SetConsoleScreenBufferSize(hOut,{(SHORT)width,(SHORT)heigh}) )
    {
        printf("SetConsoleScreeBufferSize failed %d\n",(int)GetLastError());
        getchar();
        exit(1);
    }

    DWORD mode=0;
    if( !GetConsoleMode(hOut,&mode) )
    {
        printf("GetConsoleMode failed %d\n",(int)GetLastError());
        getchar();
        exit(1);
    }
    if( !SetConsoleMode(hOut,mode|ENABLE_VIRTUAL_TERMINAL_PROCESSING) )
    {
        printf("SetConsoleMode failed %d\n",(int)GetLastError());
        getchar();
        exit(1);
    }

    //printf("lef=%d top=%d rig=%d bot=%d\n",
    //        info.srWindow.Left,  info.srWindow.Top,
    //        info.srWindow.Right, info.srWindow.Bottom );
    //printf("w=%d h=%d\n",width,heigh);    
    //getchar();

    lock_term_size();
    atexit(unlock_term_size);

    *x=width;
    *y=heigh;
}



//----------------------------------------------------------------------------------------




