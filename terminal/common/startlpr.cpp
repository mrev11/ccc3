
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

#include <string.h>
#include <cccapi.h>


#ifdef _WINDOWS_

#include <io.h>
#include <fcntl.h>
#include <process.h>

//----------------------------------------------------------------------------
static int dup_noinherit(int fd)
{
    HANDLE oldhandle=(HANDLE)_get_osfhandle(fd);    
    HANDLE newhandle;

    DuplicateHandle( GetCurrentProcess(), 
                     oldhandle, 
                     GetCurrentProcess(), 
                     &newhandle, 
                     0, 
                     0, // inheritflag
                     DUPLICATE_SAME_ACCESS );

    return _open_osfhandle((long long)newhandle,0);
}

//----------------------------------------------------------------------------
FILE *startlpr(const char *lpr, const char *dev, const char *locnam)
{
    int p[2];
    if( _pipe(p,0,O_BINARY) )
    {
        return 0;
    }

    int fd0=dup(0); //save
    close(0); dup(p[0]); close(p[0]); //0 helyere p[0]
    int fd=dup_noinherit(p[1]); close(p[1]); //nem oroklodik

    char *argv[3];
    argv[0]=(char*)lpr;
    argv[1]=(char*)dev;
    argv[2]=(char*)locnam;
    argv[3]=0;
    if( -1==spawnv(P_NOWAIT,argv[0],argv) )
    {
        fprintf(stderr,"\nSTARTLPR script not found (CCCTERM_CAPTURE:%s)",lpr);
        close(fd);
        fd=-1;
    }
    close(0); dup(fd0); close(fd0); //restore

    return fdopen(fd,"wb");
}

//----------------------------------------------------------------------------
#endif


#ifdef _UNIX_
//----------------------------------------------------------------------------
FILE *startlpr(const char *lpr, const char *dev, const char *locnam)
{
    int p[2];
    if( pipe(p) )
    {
        return 0;
    }

    if( fork()==0 )
    {
        // gyerek processz

        close(p[1]);
        close(0);
        int retval=dup(p[0]);
        close(p[0]);
        
        char *argv[3];
        argv[0]=strdup(lpr);
        argv[1]=strdup(dev);
        argv[2]=strdup(locnam);
        argv[3]=0;

        execv(argv[0],argv);    // abszolut spec vagy workdir
        //execvp(argv[0],argv);   // path-bol is indit

        //ide csak hiba eseten jon 
        fprintf(stderr,"\nSTARTLPR script not found (CCCTERM_CAPTURE:%s)",lpr);
        exit(1);     
    }

    // szulo processz

    close(p[0]);
    return fdopen(p[1],"wb");
}

//----------------------------------------------------------------------------
#endif
