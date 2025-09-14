
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

#include <locale.h>
#include <stdio.h>
#include <cccapi.h>
#include <global.h>


#ifdef WINDOWS
#include <io.h>
#include <fcntl.h>
#endif


int vartab_is_ready=0;


//----------------------------------------------------------------------------
static void delete_thread_data(void *p)
{
    delete (thread_data*)p;
}

//----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    setup_signal_handlers();

    #ifdef WINDOWS
    _fmode=O_BINARY;
    _setmode(0,O_BINARY);
    _setmode(1,O_BINARY);
    _setmode(2,O_BINARY);
    #endif

    if( !setlocale(LC_CTYPE,"") )
    {
        //fprintf(stderr,"setlocale failed\n");
    }

    if( getenv("CPPSTANDARD") )
    {
        fprintf(stderr, "%s (c++%ld) %s\n",__VERSION__,__cplusplus, argv[0]);
        exit(0);
    }

    ARGC=argc;
    ARGV=argv;

    vartab_ini();
    pthread_key_create(&thread_key,&delete_thread_data);
    pthread_setspecific(thread_key,new thread_data());

    vartab_is_ready=1;

    for(int i=1; i<argc; i++)
    {
        stringnb(argv[i]);
    }

    extern void _clp_main(int);
    _clp_main(argc-1);POP();
    _clp___quit(0);POP();
    return 0;
}



//----------------------------------------------------------------------------
