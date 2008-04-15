
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
#include <string.h>
#include <cccapi.h>
#include <global.h>
#include <termapi.h>

#ifdef WINDOWS
#include <io.h>
#include <fcntl.h>

static void setbinary(int fd)
{
    long oldhandle=_get_osfhandle(fd);
    long newhandle;
    DuplicateHandle( GetCurrentProcess(), 
                     (HANDLE)oldhandle, 
                     GetCurrentProcess(), 
                     (HANDLE*)&newhandle, 
                     0, 
                     1, //inherit
                     DUPLICATE_SAME_ACCESS );
    close(fd);
    int fd1=_open_osfhandle(newhandle,O_BINARY);  //ezért a szenvedés!
    if( fd!=fd1 )
    {
        FILE*out=(fd==1?stderr:stdout);
        fprintf(out,"setbinary failed: fd=%d, fd1=%d, errno=%d\n",fd,fd1,errno); 
        exit(1);
    }
}
#endif
 
//----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    #ifdef WINDOWS
    _fmode=O_BINARY;
    setbinary(1);
    setbinary(2);
    #endif

    if( !setlocale(LC_CTYPE,"") )
    {
        //fprintf(stderr,"setlocale failed\n");
    }

    ARGC=argc;
    ARGV=argv;

    initialize_terminal();
    setcaption(ARGV[0],strlen(ARGV[0]));

    vartab_ini();
 
    setup_signal_handlers();

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
