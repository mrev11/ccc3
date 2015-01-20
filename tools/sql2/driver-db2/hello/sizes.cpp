
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef NOTDEFINED
    #include <db2/sqlcli1.h>
    #include <db2/sqlutil.h>
    #include <db2/sqlenv.h>
    const char *x="sqlcli1.h";

#else
    #include <db2.h>
    const char *x="db2.h";

#endif

int main()
{

    printf("Sizes %s\n",x);
    printf("SQLINTEGER   %d\n", (int)sizeof(SQLINTEGER) );
    printf("SQLUINTEGER  %d\n", (int)sizeof(SQLUINTEGER) );
    printf("SQLHANDLE    %d\n", (int)sizeof(SQLHANDLE) );
    printf("SQLRETURN    %d\n", (int)sizeof(SQLRETURN) );
    printf("SQLPOINTER   %d\n", (int)sizeof(SQLPOINTER) );
    printf("short        %d\n", (int)sizeof(short));
    printf("int          %d\n", (int)sizeof(int));
    printf("long         %d\n", (int)sizeof(long));
    printf("int          %d\n", (int)sizeof(int));
    printf("void*        %d\n", (int)sizeof(void*));

}