


#ifdef MSGOUT

#include <stdlib.h>
#include <stdio.h>

static FILE *msgout_fp()
{
    static FILE *fp=0;
    if( !fp )
    {
        char *name=getenv("MSGOUT");
        if( name && *name )
        {
            fp=fopen(name,"a");
        }
        if( !fp )
        {
            fprintf(stderr,"MSGOUT variable not set\n");
            exit(1);
        }
    }
    return fp;
}

#define msgout(...)  fprintf(msgout_fp(),__VA_ARGS__)


#else

#define msgout(...)

#endif
