
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int hopp();
extern int kopp();

int main(int argc, char*argv[])
{
    hopp();
    kopp();
    printf("Hello\n");
    return 0;
}


