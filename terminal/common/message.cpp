
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




