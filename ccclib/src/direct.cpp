
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

#ifdef WINDOWS
#include <direct.h>
#undef  getcwd
#define getcwd _getcwd
#endif

#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <cccapi.h>
 
//------------------------------------------------------------------------
#ifdef _UNIX_
static char *cwd() //current working directory
{
    int size=0x100;
    int maxsize=0x4000;
    char *suc=0;
    char *buf=(char*)malloc(size);
    while( 0==(suc=getcwd(buf,size)) && size<maxsize )
    {
        buf=(char*)realloc(buf,size*=2);
    }
    if( suc )
    {
        return buf;
    }
    free(buf);
    return 0;
}

#else
static char *cwd() //current working directory
{
    int size=0x100;
    int maxsize=0x4000;
    CHAR *suc=0;
    CHAR *buf=(CHAR*)malloc(size*sizeof(CHAR));
    while( 0==(suc=_wgetcwd(buf,size)) && size<maxsize )
    {
        buf=(CHAR*)realloc(buf,size*=2);
    }
    if( suc )
    {
        char *utf8=wchar_to_utf8(buf,wcslen(buf),0);
        free(buf);
        return utf8;
    }
    free(buf);
    return 0;
}
#endif

//------------------------------------------------------------------------
void _clp_diskname(int argno) //CA-TOOLS
{
    stack-=argno;
    #ifdef WINDOWS
        char *wd=cwd();
        if( wd )
        {
            stringsb(wd,1);
            free(wd);
            return;
        }
    #endif
    string(L"");
}

//------------------------------------------------------------------------
void _clp_diskchange(int argno) //CA-TOOLS
{
    CCC_PROLOG("diskchange",1);
    errno=0;
    #ifdef _UNIX_
        _retl( 1 ); //sikeres, mivel nincsenek drive-ok
    #else
        _clp_upper(1);
        _clp_asc(1);
        int drv=_parni(1)-'A'+1;
        _retl( 0==_chdrive(drv) );
    #endif    
    CCC_EPILOG();
}

//------------------------------------------------------------------------
static void curdir(VALUE *base, int skip)
{
    int diskchg=0;
    int success=1;

    if( base->type==TYPE_STRING )
    {
        _clp_diskname(0);
        swap();
        _clp_diskchange(1);
        diskchg=1;
        success=flag();
    }

    //stack: "DISK"/NIL
    
    char *wd=cwd();
    if( wd==0 )
    {
        string(L""); //HIBA 
    }
    else if( success )
    {
        stringnb(wd+skip); //OK
        free(wd);
    }
    else
    {
        string(L""); //HIBA 
        free(wd);
    }
    
    if( diskchg && success )
    {
        swap();
        _clp_diskchange(1);
        POP();
    }
    _rettop();
}

//------------------------------------------------------------------------
void _clp_curdir(int argno)
{
    CCC_PROLOG("curdir",1);
    #ifdef WINDOWS
        curdir(base,3); //kihagyva "C:\"
    #else//UNIX
        curdir(base,1); //kihagyva "/"
    #endif
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_dirname(int argno) //NG
{
    CCC_PROLOG("dirname",1);
    #ifdef WINDOWS
        curdir(base,2); //teljes path drive: nélkül  (2007.09.10)
    #else//UNIX
        curdir(base,0); //teljes path
    #endif
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_dirmake(int argno) //CA-tools
{
    CCC_PROLOG("dirmake",1);
    _clp_convertfspec2nativeformat(1);
    errno=0;
    #ifdef _UNIX_
        char *dir=_parb(1);
        _retni( mkdir(dir,0777) );  //0777-et korlátozza umask
    #else
        bin2str(base);
        CHAR *dir=_parc(1);
        _retni( _wmkdir(dir) );
    #endif
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_dirremove(int argno) //CA-tools 
{
    CCC_PROLOG("dirremove",1);
    _clp_convertfspec2nativeformat(1); 
    errno=0;   
    #ifdef _UNIX_
        _retni( rmdir(_parb(1)) );
    #else
        bin2str(base);
        _retni( _wrmdir(_parc(1)) );
    #endif
    CCC_EPILOG();
}    

//------------------------------------------------------------------------
void _clp_dirchange(int argno) //CA-tools  
{
    CCC_PROLOG("dirchange",1);
    _clp_convertfspec2nativeformat(1);
    errno=0;   
    #ifdef _UNIX_
        _retni( chdir(_parb(1)) );
    #else
        bin2str(base);
        _retni( _wchdir(_parc(1)) );
    #endif
    CCC_EPILOG();
}

//------------------------------------------------------------------------


