
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
#include <unistd.h>
#include <cccapi.h>
#include <errno.h>
#include <stat.ch>

#if defined _CCC2_
  #define STAT stat
#elif defined _UNIX_    
  #define STAT stat
#else // CCC3-WINDOWS
  #define STAT _stat
#endif

extern int lstat(const char *fspec, struct stat *buf);
extern int _wlstat(const wchar_t *fspec, struct stat *buf);

//----------------------------------------------------------------------
static void createStatEntry(struct stat *buf)
{
    number(buf->st_dev);
    number(buf->st_ino);
    number(buf->st_mode);
    number(buf->st_nlink);
    number(buf->st_uid);
    number(buf->st_gid);
    number(buf->st_rdev);
    number(buf->st_size);

    #ifdef UNIX
        number(buf->st_blksize);
    #else
        number(0); //Windowson nincs 
    #endif

    #ifdef UNIX
        number(buf->st_blocks);
    #else
        number(0); //Windowson nincs
    #endif

    number((double)buf->st_atime);
    number((double)buf->st_mtime);
    number((double)buf->st_ctime);

    array(N_STAT);
}


#ifdef _CCC3_
#ifdef WINDOWS
static void createStatEntry(struct _stat *buf)
{
    number(buf->st_dev);
    number(buf->st_ino);
    number(buf->st_mode);
    number(buf->st_nlink);
    number(buf->st_uid);
    number(buf->st_gid);
    number(buf->st_rdev);
    number(buf->st_size);

    #ifdef UNIX
        number(buf->st_blksize);
    #else
        number(0); //Windowson nincs 
    #endif

    #ifdef UNIX
        number(buf->st_blocks);
    #else
        number(0); //Windowson nincs
    #endif

    number((double)buf->st_atime);
    number((double)buf->st_mtime);
    number((double)buf->st_ctime);

    array(N_STAT);
}
#endif
#endif

//----------------------------------------------------------------------
void _clp_stat(int argno) // stat array (see stat.ch), or NIL
{
    CCC_PROLOG("stat",1);
    _clp_convertfspec2nativeformat(1); 
    struct STAT buf;

#if defined _CCC2_  
    char *fspec=_parc(1);
    if( 0!=stat(fspec,&buf) )

#elif defined _UNIX_ //CCC3-UNIX
    char *fspec=_parb(1);
    if( 0!=stat(fspec,&buf) )

#else //CCC3-WINDOWS
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wstat(fspec,&buf) )
#endif
    {
        _ret();
    }
    else
    {
        createStatEntry(&buf);
        _rettop();
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp_stat_st_mode(int argno) // leggyakrabban csak ez kell
{
    CCC_PROLOG("stat_st_mode",1);
    _clp_convertfspec2nativeformat(1); 
    struct STAT buf;

#if defined _CCC2_
    char *fspec=_parc(1);
    if( 0!=stat(fspec,&buf) )

#elif defined _UNIX_    
    char *fspec=_parb(1);
    if( 0!=stat(fspec,&buf) )

#else //CCC3-WINDOWS
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wstat(fspec,&buf) )
#endif
    {
        _ret();
    }
    else
    {
        _retni(buf.st_mode);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_stat_st_size(int argno) // ez is gyakran kell
{
    CCC_PROLOG("stat_st_size",1);
    _clp_convertfspec2nativeformat(1); 
    struct STAT buf;

#if defined _CCC2_
    char *fspec=_parc(1);
    if( 0!=stat(fspec,&buf) )

#elif defined _UNIX_    
    char *fspec=_parb(1);
    if( 0!=stat(fspec,&buf) )

#else
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wstat(fspec,&buf) )
#endif
    {
        _ret();
    }
    else
    {
        _retni(buf.st_size);
    }

    CCC_EPILOG();
}
 
//----------------------------------------------------------------------
void _clp_lstat(int argno)
{
    CCC_PROLOG("lstat",1);
    _clp_convertfspec2nativeformat(1);
    struct stat buf;

#if defined _CCC2_
    char *fspec=_parc(1);
    if( 0!=lstat(fspec, &buf) )

#elif defined _UNIX_
    char *fspec=_parb(1);
    if( 0!=lstat(fspec, &buf) )

#else
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wlstat(fspec,&buf) )
#endif    
    {
        _ret();
    }
    else
    {
        createStatEntry(&buf);
        _rettop();
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_lstat_st_mode(int argno)
{
    CCC_PROLOG("lstat_st_mode",1);
    _clp_convertfspec2nativeformat(1);
    struct stat buf;

#if defined _CCC2_
    char *fspec=_parc(1);
    if( 0!=lstat(fspec, &buf) )

#elif defined _UNIX_
    char *fspec=_parb(1);
    if( 0!=lstat(fspec, &buf) )

#else    
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wlstat(fspec,&buf) )
#endif    
    {
        _ret();
    }
    else
    {
        _retni(buf.st_mode);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_lstat_st_size(int argno)
{
    CCC_PROLOG("lstat_st_size",1);
    _clp_convertfspec2nativeformat(1);
    struct stat buf;

#if defined _CCC2_
    char *fspec=_parc(1);
    if( 0!=lstat(fspec, &buf) )

#elif defined _UNIX_
    char *fspec=_parb(1);
    if( 0!=lstat(fspec, &buf) )

#else    
    bin2str(base);
    CHAR *fspec=_parc(1);
    if( 0!=_wlstat(fspec,&buf) )
#endif    
    {
        _ret();
    }
    else
    {
        _retni(buf.st_size);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_fstat(int argno)
{
    CCC_PROLOG("fstat",1);

    struct stat buf;
    if( 0!=fstat(_parni(1), &buf) )
    {
        _ret();
    }
    else
    {
        createStatEntry(&buf);
        _rettop();
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_fstat_st_mode(int argno)
{
    CCC_PROLOG("fstat_st_mode",1);

    struct stat buf;
    if( 0!=fstat(_parni(1), &buf) )
    {
        _ret();
    }
    else
    {
        _retni(buf.st_mode);
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------
void _clp_fstat_st_size(int argno)
{
    CCC_PROLOG("fstat_st_size",1);

    struct stat buf;
    if( 0!=fstat(_parni(1), &buf) )
    {
        _ret();
    }
    else
    {
        _retni(buf.st_size);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_islnk(int argno)  // CCC version of S_ISLNK macro
{
    CCC_PROLOG("s_islnk",1);
    _retl(S_ISLNK(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_isreg(int argno) // CCC version of S_ISREG macro
{
    CCC_PROLOG("s_isreg",1);
    _retl(S_ISREG(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_isdir(int argno) // CCC version of S_ISDIR macro
{
    CCC_PROLOG("s_isdir",1);
    _retl(S_ISDIR(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_ischr(int argno) // CCC version of S_ISCHR macro
{
    CCC_PROLOG("s_ischr",1);
    _retl(S_ISCHR(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_isblk(int argno) // CCC version of S_ISBLK macro
{
    CCC_PROLOG("s_isblk",1);
    _retl(S_ISBLK(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_isfifo(int argno) // CCC version of S_ISFIFO macro
{
    CCC_PROLOG("s_isfifo",1);
    _retl(S_ISFIFO(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp_s_issock(int argno) // CCC version of S_ISSOCK macro
{
    CCC_PROLOG("s_issock",1);
    _retl(S_ISSOCK(_parni(1)));
    CCC_EPILOG();
}

//----------------------------------------------------------------------

