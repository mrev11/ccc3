
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
#include <cccapi.h>

//#define push_call(f,b)  (++trace,trace->func=f,trace->base=b,trace->line=0)


static int exit_flag=0;


void push_call(const char *f, VALUE*b)
{
    ++trace;
    trace->func=f;
    trace->base=b;
    trace->line=0;

    
    if( trace-tracebuf>(int)(TRACE_SIZE-16) )
    {
        if( exit_flag==0 )
        {
            exit_flag=1;
            printf("\nCall stack overflow");
            _clp_callstack(0);
            printf("\nCALLSTACK: %d/%d",(int)(trace-tracebuf),TRACE_SIZE);
            printf("\nvarstack : %d/%d",(int)(stack-stackbuf),STACK_SIZE);
            printf("\n");
            fflush(0);
            exit(1);
        }
    }


    if( (stack-stackbuf) > (int)(STACK_SIZE-128) )
    {
        if( exit_flag==0 )
        {
            exit_flag=1;
            printf("\nVariable stack overflow");
            _clp_callstack(0);
            printf("\ncallstack: %d/%d",(int)(trace-tracebuf),TRACE_SIZE);
            printf("\nVARSTACK : %d/%d",(int)(stack-stackbuf),STACK_SIZE);
            printf("\n");
            fflush(0);
            exit(1);
        }
    }
}
