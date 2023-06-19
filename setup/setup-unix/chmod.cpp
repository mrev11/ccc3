
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
#include <io.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_chmod(int argno)
{
    CCC_PROLOG("chmod",2);
    convertfspec2nativeformat(base);
    #ifdef _UNIX_
        _retni( chmod(_parb(1),_parni(2)) );  //0, ha OK
    #else
        bin2str(base);
        _retni( _wchmod(_parc(1),_parni(2)) ); //Windows: wide char names
    #endif
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
#ifdef UNIX

void _clp_fchmod(int argno)
{
    CCC_PROLOG("fchmod",2);
    int fdesc=_parni(1);
    int mode=_parni(2);
    _retni( fchmod(fdesc,mode) );  //0, ha OK
    CCC_EPILOG();
}

#endif
 
//--------------------------------------------------------------------------
