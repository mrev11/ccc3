
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

//----------------------------------------------------------------------------
#if defined LINUX

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

char* termicon()
{
    char *iconfile=getenv("CCCTERM_ICONFILE");
    struct stat buf;
    if( iconfile  &&  stat(iconfile,&buf)==0 )
    {
        return strdup(iconfile);
    }
    else
    {
        char path[PATH_MAX+32]={0};
        readlink("/proc/self/exe",path,sizeof(path));
        char *ds=strrchr(path,'/');
        if( ds )
        {
            strcpy(ds+1,"terminal.xpm");
            if( stat(path,&buf)==0 )
            {
                return strdup(path);
            }
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
#elif defined WINDOWS

#include <stdio.h>
#include <sys/stat.h>
#include <windows.h>

char* termicon()
{
    char *iconfile=getenv("CCCTERM_ICONFILE");
    struct _stat buf;
    if( iconfile  && _stat(iconfile,&buf)==0 )
    {
        return strdup(iconfile);
    }
    else
    {
        char path[PATH_MAX+32]={0};
        unsigned nchar=GetModuleFileNameA(0,path,sizeof(path));
        char *ds=strrchr(path,'\\');
        if( ds )
        {
            strcpy(ds+1,"terminal.ico");
            if( _stat(path,&buf)==0 )
            {
                return strdup(path);
            }
        }
    }
    return 0;
}

// csak ASCII fajlnevekkel mukodik
// ott kezdodik a baj, hogy mit ad a getenv
// fuggvenyek szazainak van ascii es unicode valtozata

//----------------------------------------------------------------------------
#else

char* termicon()
{
    return 0;
}

//----------------------------------------------------------------------------
#endif

