
#include <windows.h>
#include <stdio.h>

void screensize(int *y, int *x)  // lekerdezi a terminal meretet
{
    HANDLE hnd=GetStdHandle( STD_OUTPUT_HANDLE );
    if( hnd==NULL )
    {
        fprintf(stderr,"OUTPUT CONSOLE NOT FOUND\n");
        exit(1);
    }

    CONSOLE_SCREEN_BUFFER_INFO scrbuf;
    GetConsoleScreenBufferInfo(hnd,&scrbuf);
    *x=scrbuf.dwSize.X;
    *y=scrbuf.dwSize.Y;

    //printf("%d\n",scrbuf.dwMaximumWindowSize.X);
    //printf("%d\n",scrbuf.dwMaximumWindowSize.Y);
}



