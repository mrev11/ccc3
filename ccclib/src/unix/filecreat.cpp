
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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
 
#include <cccapi.h>
#include <fileio.ch>  
#include <fileconv.ch>

#define UNIX_FO_SHARED        0
#define UNIX_FO_EXCLUSIVE     1
#define UNIX_FO_NOLOCK        2

#define CCC_FILELOCK_START  ((off_t)(unsigned long)0x80000000)  //2GB
#define CCC_FILELOCK_LEN    ((off_t)(unsigned long)0x1) 

#define DOSNAME_LEN           4
 
static int ccc_defsharemode=0;  //nem kell szinkronizalni
static int unix_defsharemode=UNIX_FO_SHARED;  //nem kell szinkronizalni 

//----------------------------------------------------------------------------
void _clp_getshare(int argno) //CA-tools fopen es fcreate default nyitasi modja
{
    stack-=argno;
    number(ccc_defsharemode);
}

//----------------------------------------------------------------------------
void _clp_setshare(int argno) //CA-tools fopen es fcreate default nyitasi modja 
{
    CCC_PROLOG("setshare",1);
    unsigned int defmod = _parni(1);
 
    static int openmode[]=
    {
        UNIX_FO_SHARED,     // 0
        UNIX_FO_EXCLUSIVE,  // 1
        UNIX_FO_EXCLUSIVE,  // 2
        UNIX_FO_EXCLUSIVE,  // 3
        UNIX_FO_SHARED,     // 4
        UNIX_FO_NOLOCK      // 5  (bovites)
    };
   
    if( defmod < sizeof(openmode)/sizeof(openmode[0]) )
    {
        ccc_defsharemode=defmod;
        unix_defsharemode=openmode[defmod];
        _retl(1);
    }
    else
    {
        _retl(0);
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
static int ulock(int hnd, int unixShareMode) 
{
    // lock a share modok emulalasara
    // Vissza: 0=OK, -1=sikertelen

    if( unixShareMode==UNIX_FO_NOLOCK )
    {
        return 0;
    }

    struct flock fl;
       
    fl.l_whence=SEEK_SET;
    #ifdef _LFS_
      fl.l_start=(unsigned)CCC_FILELOCK_START*512-1;  //1024 GB - 1
    #else
      fl.l_start=(unsigned)CCC_FILELOCK_START-2;      //   2 GB - 2
    #endif
    fl.l_len=CCC_FILELOCK_LEN;

    switch(unixShareMode)
    {
        case UNIX_FO_SHARED:
            fl.l_type=F_RDLCK;
            break;

        case UNIX_FO_EXCLUSIVE:
            fl.l_type=F_WRLCK;
            break;

        default:
            errno=ENOLCK;
            return -1;
    }

    if( (-1==fcntl(hnd,F_SETLK,&fl)) && (errno!=ENOLCK) && (errno!=EACCES) )
    {
        return -1;
    }
    return 0;
}

//----------------------------------------------------------------------------
static int startlpr(char *printer)
{
    // Nyomtatas az CCCLPR_CAPTURE scripttel printer-re
    // Visszateres: fd>=0, amibe irni kell, vagy -1

    char *lpr=getenv("CCCLPR_CAPTURE");
    if( lpr==0 || lpr[0]==0 )
    {
        return -1;
    }

    int p[2];
    if( pipe(p) )
    {
        return -1;
    }

    if( fork()==0 )
    {
        // gyerek processz

        close(p[1]);
        close(0);
        int retval=dup(p[0]);
        close(p[0]);
        
        char *argv[3];
        argv[0]=lpr;
        argv[1]=printer;
        argv[2]=0;

        execv(argv[0],argv);    // abszolut spec vagy workdir
        //execvp(argv[0],argv);   // path-bol is indit

        //ide csak hiba eseten jon 
        fprintf(stderr,"script not found (CCCLPR_CAPTURE=%s)\n",lpr);
        exit(1);     
    }

    // szulo processz
    close(p[0]);
    return p[1];
}

//----------------------------------------------------------------------------
static char *dosname(char *str, char *dnamebuf)
{
    // Ha str 'drive:' alaku akkor a drive-ot adja, 
    // egyebkent a filenevet path es kiterjesztes nelkul.
    // A filespecbol a path-t, a space-eket, a kiterjesztest torli. 
    // Ha a kapott nev ures, vagy  hosszabb, mint 4, akkor NULL-t ad.

    if( str==NULL || str[0]=='\0' )
    {
        return NULL;
    }

    int i,j,ibuf=0;
 
    for( i=strlen(str)-1; i>=0 && isspace(str[i]); i-- );

    if( i<0 )
    {
        return NULL;
    }

    if( str[i]==':' ) // drive: alaku nev. 
    {
        for(j=0; j<i; j++)
        {
            char c=str[j];
            if( isspace(c) )
            {
                //continue
            }
            else if( c==':' || c=='\\' || c=='/' )
            {
                return NULL;
            }
            else if( c=='.' )
            {
                break;
            }

            if( ibuf>=DOSNAME_LEN )
            {
                return NULL;
            }
            dnamebuf[ibuf++]=c;
        }
    }
    else
    {
        // path\file alaku nev.

        for( j=i; j>=0 && !(str[j]==':'||str[j]=='\\'||str[j]=='/'); j-- );

        for( j=j+1; j<=i; j++ )
        {
            char c=str[j];
            if( isspace(c) )
            {
                //continue
            }
            else if( c=='.' )
            {
                break;
            }

            if( ibuf>=DOSNAME_LEN )
            {
                return NULL;
            }
            dnamebuf[ibuf++]=c;
        }
    }

    dnamebuf[ibuf]='\0';
    return dnamebuf;
}

//----------------------------------------------------------------------------
static int isdosprinter(char *str)
{
    static const char *pr[]={"lpt1",  "lpt2",  "lpt3",  "prn", NULL}; 

    int i;
    for(i=0; pr[i]; i++)
    {
        if( 0==strcasecmp(pr[i],str) )
        {
            return 1;
        }
    }
    return 0;     
}

//----------------------------------------------------------------------------
static int uopen(char *name, int shrmod, int accmod, int cremod)
{
    int fd=-1;

    char dnamebuf[DOSNAME_LEN+1];
    char *dname=(DOSCONV&DOSCONV_SPECDOSDEV)?dosname(name,dnamebuf):0;

    if( dname && isdosprinter(dname) )
    {
        fd=startlpr(dname);
    }
    else if( dname && (0==strcasecmp(dname,"con")) )
    {
        fd=dup(1); //stdout
    }
    else if( dname && (0==strcasecmp(dname,"nul")) )
    {
        fd=open("/dev/null",O_RDWR); 
    }
    else if( -1!=(fd=open(name,accmod,cremod)) ) 
    {
        if( DOSCONV & DOSCONV_FILESHARE )
        {
            if( 0>ulock(fd,shrmod) ) 
            {
                close(fd);
                fd=-2;
            }
        }
    }
    
    // fd >= 0, succesfull
    // fd ==-1, open failed
    // fd ==-2, lock failed

    return fd;
}

//----------------------------------------------------------------------------
static int determineUnixShareMode(int fomode)
{
    switch( fomode & (    FO_EXCLUSIVE    //16
                        | FO_DENYWRITE    //32
                        | FO_DENYREAD     //48
                        | FO_DENYNONE     //64==FO_SHARED
                        | FO_NOLOCK       //128
                        | FO_COMPAT ) )   //0
    {
        case FO_EXCLUSIVE : return UNIX_FO_EXCLUSIVE;
        case FO_DENYWRITE : return UNIX_FO_EXCLUSIVE;
        case FO_DENYREAD  : return UNIX_FO_EXCLUSIVE;
        case FO_DENYNONE  : return UNIX_FO_SHARED;
        case FO_NOLOCK    : return UNIX_FO_NOLOCK;
    }
    return unix_defsharemode; 
}

//----------------------------------------------------------------------------
static int determineUnixAccessMode(int fomode)
{
    int unixmode=O_RDONLY;

    if( fomode & FO_WRITE     ) unixmode =  O_WRONLY;  //1
    if( fomode & FO_READWRITE ) unixmode =  O_RDWR;    //2
    if( fomode & FO_CREATE    ) unixmode |= O_CREAT; 
    if( fomode & FO_TRUNCATE  ) unixmode |= O_TRUNC; 
    if( fomode & FO_APPEND    ) unixmode |= O_APPEND;
    #if defined O_CLOEXEC
    if( fomode & FO_NOINHERIT ) unixmode |= O_CLOEXEC;
    #endif

    return unixmode;
}

//----------------------------------------------------------------------------
static void cutUnixSAMode(int *shrmod, int *accmod)
{
    switch( *accmod & (O_RDWR|O_RDONLY|O_WRONLY) )
    {
        case O_RDONLY: //unable to put WRLCK on RDONLY file
            if( *shrmod==UNIX_FO_EXCLUSIVE ) 
            {
                *accmod = (*accmod&~(O_RDONLY|O_WRONLY)) | O_RDWR;
            }
            break;

        case O_WRONLY: //unable to put RDLCK on WRONLY file  
            if( *shrmod==UNIX_FO_SHARED ) 
            {
                *accmod = (*accmod&~(O_RDONLY|O_WRONLY)) | O_RDWR;
            }
            break;
    }
}
 
//----------------------------------------------------------------------------
void _clp_fopen(int argno) //Clipper
{
    CCC_PROLOG("fopen",2);

    convertfspec2nativeformat(base);
    char *fspec=_parb(1);

    int unixShareMode=unix_defsharemode; 
    int unixAccessMode=O_RDONLY; 
    int unixCreateMode=0666;
 
    if( !ISNIL(2) )
    {
        int fomode=_parni(2);
        unixShareMode=determineUnixShareMode(fomode);
        unixAccessMode=determineUnixAccessMode(fomode);
    }

    int origUnixShareMode=unixShareMode;
    int origUnixAccessMode=unixAccessMode;
    cutUnixSAMode(&unixShareMode,&unixAccessMode);

    int fd=uopen( fspec, 
                  unixShareMode,
                  unixAccessMode,
                  unixCreateMode );

    if( (fd<0) &&
        (errno==EROFS) && //readonly filesystem 
        ((origUnixAccessMode&(O_RDWR|O_RDONLY|O_WRONLY))==O_RDONLY) &&
        (origUnixShareMode==UNIX_FO_EXCLUSIVE) )
    {
        fd=uopen( fspec,
                  UNIX_FO_NOLOCK,
                  O_RDONLY,
                  0 );
    }

    _retni( fd<0?-1:fd );
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_fcreate(int argno) //Clipper
{
    CCC_PROLOG("fcreate",2);
    convertfspec2nativeformat(base);
    char *fspec=_parb(1);

    int unixShareMode=unix_defsharemode;
    int unixAccessMode=(O_RDWR|O_CREAT|O_TRUNC);
    int unixCreateMode=0666;

    if( !ISNIL(2) )
    {
        int fcmode=_parni(2);
        if( fcmode & FC_READONLY ) unixCreateMode =  0444; 
        if( fcmode & FC_NOTRUNC  ) unixAccessMode &= ~O_TRUNC; 
        if( fcmode & FC_APPEND   ) unixAccessMode |= O_APPEND; 
    }
 
    int fd=uopen( fspec,
                  unixShareMode,
                  unixAccessMode,
                  unixCreateMode );

    _retni( fd<0?-1:fd );
    CCC_EPILOG();
}

//----------------------------------------------------------------------------

