
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
            strcpy(ds+1,"terminal.xpm");
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

