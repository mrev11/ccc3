
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

#include <dirent.h>
#include <cccapi.h>

static DIR *dir=NULL;

//-----------------------------------------------------------------------
void _clp___opendir(int argno) // return: 0/-1
{
    CCC_PROLOG("opendir",1);
    str2bin(base);
    char *dirname=_parb(1);

    if( dir!=NULL )
    {
        closedir(dir);
        dir=NULL;
    }
    dir=opendir(dirname);
    _retni( dir==NULL ? -1:0  );
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp___readdir(int argno)
{
    CCC_PROLOG("readdir",0);
    struct dirent *de;
    if( dir==NULL || NULL==(de=readdir(dir)) )
    {
        _ret();
    }
    else
    {
        _retcb(de->d_name);
    }
    CCC_EPILOG();
}


//-----------------------------------------------------------------------
void _clp___readdirx(int argno) //ua. mint __readdir, csak binary-t ad
{
    CCC_PROLOG("readdir",0);
    struct dirent *de;
    if( dir==NULL || NULL==(de=readdir(dir)) )
    {
        _ret();
    }
    else
    {
        _retb(de->d_name);
    }
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
void _clp___closedir(int argno)
{
    CCC_PROLOG("closedir",0);
    if( dir!=NULL )
    {
        closedir(dir);
        dir=NULL;
    }
    _ret();
    CCC_EPILOG();
}

//-----------------------------------------------------------------------
