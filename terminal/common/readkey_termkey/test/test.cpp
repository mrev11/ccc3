
#include <stdio.h>

extern int readkey();


int main()
{
    while(1)
    {
        int ch=readkey();
        if( ch )
        {
            printf("inkey %d\n", ch);
        }
        if( ch==27 )
        {
            break;
        }
    }
    return 0;
}

