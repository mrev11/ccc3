
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
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wchar.h>

#include <cccapi.h>

//------------------------------------------------------------------------
void _clp_file(int argno)  //Clipper
{
    CCC_PROLOG("file",1);
    _clp_lstat_st_mode(1);
    PUSH(&NIL);
    neeq();
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_ferase(int argno) //Clipper
{
    CCC_PROLOG("ferase",1);
    _clp_convertfspec2nativeformat(1);
    errno=0;
    #ifdef _UNIX_
        _retni( remove(_parb(1)) );
    #else
        bin2str(base);
        _retni( _wremove(_parc(1)) );
    #endif
    CCC_EPILOG();
}    

//------------------------------------------------------------------------
void _clp_frename(int argno) //Clipper
{
    CCC_PROLOG("frename",2);
    _clp_convertfspec2nativeformat(1); swap();
    _clp_convertfspec2nativeformat(1); swap();
    errno=0;
    #ifdef _UNIX_
        _retni( rename(_parb(1),_parb(2)) );
    #else
        bin2str(base);
        bin2str(base+1);
        _retni( _wrename(_parc(1),_parc(2)) );
    #endif
    CCC_EPILOG();
}    

//------------------------------------------------------------------------
void _clp_deletefile(int argno)  //CA-Tools (==ferase)
{
    CCC_PROLOG("deletefile",1);
    _clp_convertfspec2nativeformat(1);
    errno=0;
    #ifdef _UNIX_
        _retni( remove(_parb(1)) );
    #else
        bin2str(base);
        _retni( _wremove(_parc(1)) );
    #endif
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_filemove(int argno) //CA-Tools (==frename)
{
    CCC_PROLOG("filemove",2);
    _clp_convertfspec2nativeformat(1); swap();
    _clp_convertfspec2nativeformat(1); swap();
    errno=0;
    #ifdef _UNIX_
        _retni( rename(_parb(1),_parb(2)) );
    #else
        bin2str(base);
        bin2str(base+1);
        _retni( _wrename(_parc(1),_parc(2)) );
    #endif
    CCC_EPILOG();
}    

//----------------------------------------------------------------------------

