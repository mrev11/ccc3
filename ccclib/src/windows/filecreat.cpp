
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

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <errno.h>
#include <stdio.h>
#include <process.h>

#include <fileio.ch>
#include <fileconv.ch>
#include <cccapi.h>

#define DOSNAME_LEN           4
 
static int ccc_defsharemode=0;

 
//---------------------------------------------------------------------------
static int bit_defsharemode()
{
    static int mode[5]={
        SH_DENYNO,      // 0
        SH_DENYRW,      // 1    FO_EXCLUSIVE 
        SH_DENYWR,      // 2    FO_DENYWRITE 
        SH_DENYRD,      // 3    FO_DENYREAD 
        SH_DENYNO };    // 4    FO_DENYNONE 

    return mode[ccc_defsharemode];
}

//---------------------------------------------------------------------------
void _clp_getshare(int argno)
{
    stack-=argno;
    number(ccc_defsharemode);
}

//---------------------------------------------------------------------------
void _clp_setshare(int argno)
{
    CCC_PROLOG("setshare",1);
    unsigned mode=_parnu(1);
    if( mode<5 )
    {
        ccc_defsharemode=mode;
        _retl(1); //elfogadva
    }
    else
    {
        _retl(0); //visszautasitva
    }
    CCC_EPILOG();
}

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
static int startlpr(char *lpr, char *printer)
{
    // Nyomtatas a CCCLPR_CAPTURE=lpr scripttel
    // Visszateres: fd>=0, amibe irni kell, vagy -1

    int p[2];
    if( _pipe(p,0,O_BINARY) )
    {
        return -1;
    }

    int fd0=dup(0); //save
    close(0); dup(p[0]); close(p[0]); //0 helyere p[0]
    int fd=dup_noinherit(p[1]); close(p[1]); //nem oroklodik

    char *argv[3];
    argv[0]=lpr;
    argv[1]=printer;
    argv[2]=0;
    if( -1==spawnv(P_NOWAIT,argv[0],argv) )
    {
        fprintf(stderr,"script not found (CCCLPR_CAPTURE=%s)\n",lpr);
        close(fd);
        fd=-1;
    }
    close(0); dup(fd0); close(fd0); //restore
    return fd;
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

//---------------------------------------------------------------------------
static int open(VALUE *base,int acc, int shr, int att)
{
    int argno=stack-base;
    convertfspec2nativeformat(base);
    bin2str(base);
    CHAR *fs=_parc(1); // CCC3:wchar_t, CCC2:char
    char *capture=0;

    if( DOSCONV&DOSCONV_SPECDOSDEV )
    {
        push(base);
        str2bin(TOP());
        char *name=BINARYPTR(TOP()); //fs with 1-byte char type

        char dnamebuf[DOSNAME_LEN+1];
        char *dname=dosname(name,dnamebuf);
        //printf("DNAME: %s -> %s\n",name,dname);

             if( dname && 0==strcasecmp(dname,"LPT1") && 0!=(capture=getenv("CCCLPR_CAPTURE_LPT1")) ){}
        else if( dname && 0==strcasecmp(dname,"LPT2") && 0!=(capture=getenv("CCCLPR_CAPTURE_LPT2")) ){}
        else if( dname && 0==strcasecmp(dname,"LPT3") && 0!=(capture=getenv("CCCLPR_CAPTURE_LPT3")) ){}
        else if( dname && 0==strcasecmp(dname,"PRN" ) && 0!=(capture=getenv("CCCLPR_CAPTURE_PRN" )) ){}
        else if( dname &&  isdosprinter(dname)        && 0!=(capture=getenv("CCCLPR_CAPTURE"     )) ){}
        
        if( capture && capture==strstr(capture,"pipe:") )
        {
            return startlpr(capture+5,dname);
        }
        else if( capture && capture==strstr(capture,"file:") )
        {
            name=capture+5;
            binaryn(name); bin2str(TOP()); fs=STRINGPTR(TOP());
        }
        else if(capture)
        {
            name=capture;
            binaryn(name); bin2str(TOP()); fs=STRINGPTR(TOP());
        }
    }

    errno=0;

  #ifdef _CCC3_
    return _wsopen(fs,acc,shr,att);
  #else
    return _sopen(fs,acc,shr,att);
  #endif
}

//----------------- ----------------------------------------------------------
void _clp_fopen(int argno) //file nyitas sopen()-nel
{
    CCC_PROLOG("fopen",2);

    int acc=O_RDONLY;
    int shr=bit_defsharemode();
    int att=0777;
    
    if( !ISNIL(2) )
    {
        int fomode=_parni(2);
        
        //access

        if( fomode & FO_WRITE       ) acc  = O_WRONLY;  //1
        if( fomode & FO_READWRITE   ) acc  = O_RDWR;    //2
        if( fomode & FO_CREATE      ) acc |= O_CREAT; 
        if( fomode & FO_TRUNCATE    ) acc |= O_TRUNC; 
        if( fomode & FO_APPEND      ) acc |= O_APPEND;
        if( fomode & FO_NOINHERIT   ) acc |= O_NOINHERIT;
        if( fomode & FO_NONEXISTENT ) acc |= O_EXCL;

        //sharing

        switch( fomode & (    FO_EXCLUSIVE         //16
                            | FO_DENYWRITE         //32
                            | FO_DENYREAD          //48
                            | FO_DENYNONE          //64==FO_SHARED 
                            | FO_COMPAT    ) )     // 0
        {
            case FO_EXCLUSIVE : shr=SH_DENYRW; break;
            case FO_DENYWRITE : shr=SH_DENYWR; break; 
            case FO_DENYREAD  : shr=SH_DENYRD; break; 
            case FO_DENYNONE  : shr=SH_DENYNO; break; 
        }
    }

    _retni( open(base,acc|O_BINARY,shr,att) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_fcreate(int argno) //Clipper (file krealas sopen()-nel)
{
    CCC_PROLOG("fcreate",2);

    int acc=(O_RDWR|O_CREAT|O_TRUNC);
    int shr=bit_defsharemode();
    int att=0777;
    
    if( !ISNIL(2) )
    {
        int fcmode=_parni(2);
        if( fcmode & FC_READONLY    ) att  = 0555;
        if( fcmode & FC_NOTRUNC     ) acc &= ~O_TRUNC;
        if( fcmode & FC_APPEND      ) acc |= O_APPEND;
        if( fcmode & FC_NOINHERIT   ) acc |= O_NOINHERIT;
        if( fcmode & FC_NONEXISTENT ) acc |= O_EXCL;
    }                           

    _retni( open(base,acc|O_BINARY,shr,att) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
