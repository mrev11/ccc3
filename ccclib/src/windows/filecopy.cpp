
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

#include <errno.h>
#include <cccapi.h>

//---------------------------------------------------------------------------
void _clp_filecopy(int argno) //CA-Tools
{
    CCC_PROLOG("filecopy",2);
    _clp_convertfspec2nativeformat(1); swap();
    _clp_convertfspec2nativeformat(1); swap();
    bin2str(base);
    bin2str(base+1);
    CHAR *src=_parc(1);
    CHAR *trg=_parc(2);
    int result=CopyFileW(src,trg,0); //Win API
    if( result )
    {
        push_symbol(base+1);
        extern void _clp_stat_st_size(int);
        _clp_stat_st_size(1); //size/NIL
        if( TOP()->type==TYPE_NUMBER )
        {
            errno=0;
        }
        else
        {
            pop();
            number(-1);
        }
    }
    else
    {
        number(-1);
        errno=GetLastError();
    }
    _rettop(); //filesize
    CCC_EPILOG();
 
} 

//---------------------------------------------------------------------------
