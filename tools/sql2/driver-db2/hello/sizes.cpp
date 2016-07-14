
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