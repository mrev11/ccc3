
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

#include <sys/types.h>
#include <unistd.h>
#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_chown(int argno)
{
    CCC_PROLOG("chown",3);
    convertfspec2nativeformat(base); 
    BYTE *fname=_parb(1);
    int owner=_parni(2);
    int group=_parni(3);
    _retni( chown(fname,owner,group) );  //0, ha OK
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_fchown(int argno)
{
    CCC_PROLOG("fchown",3);
    int fdesc=_parni(1);
    int owner=_parni(2);
    int group=_parni(3);
    _retni( fchown(fdesc,owner,group) );  //0, ha OK
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_lchown(int argno)
{
    CCC_PROLOG("lchown",3);
    convertfspec2nativeformat(base); 
    BYTE *fname=_parb(1);
    int owner=_parni(2);
    int group=_parni(3);
    _retni( lchown(fname,owner,group) );  //0, ha OK
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
