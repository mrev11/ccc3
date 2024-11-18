
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

#include <cccapi.h>

//----------------------------------------------------------------------------------------
void _clp_realpath(int argno)
{
    CCC_PROLOG("realpath",1);
    convertfspec2nativeformat(base);

    #ifdef _CCC3_    
        bin2str(base);
        CHAR *path=_parc(1);
        CHAR *fpath=_wfullpath(0,path,0);
    #else
        char *path=_parc(1);
        char *fpath=_fullpath(0,path,0);
    #endif

    if( fpath )
    {
        _retc(fpath);
        free(fpath);
    }
    else
    {
        _ret();
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------

