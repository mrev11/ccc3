

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>




extern void message(char const *msg, ...);



void message(char const *msg, ...)
{
    static FILE *term=0;
    if( term==0  )
    {
        term=stderr;

        char *envmsg=getenv("MESSAGE");  //export MESSAGE=/dev/pts/10
                                         //export MESSAGE=msgfile
        if( envmsg && *envmsg )
        {
            term=fopen(envmsg,"a");
            if( term==0 )
            {
                fprintf(stderr,"cant open %s\n",envmsg);
                exit(1);
            }
            else
            {
                fprintf(term,"\n-------------------------------------------------------\n");
            }
        }
    }

    va_list argp;
    va_start(argp, msg);
    vfprintf(term, msg, argp);
    va_end(argp);
}




