
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
#include <stdio.h>
#include <errno.h>

#include <fileio.ch>  //Clipper
#include <cccapi.h>

//---------------------------------------------------------------------------
void _clp_fseek(int argno)
{
    CCC_PROLOG("fseek",3);

    int fd=_parni(1);
    long offset=_parnl(2);
    int from=ISNUMBER(3)?_parni(3):0;
 
    if( from==FS_RELATIVE )
    {
        from=SEEK_CUR;
    }
    else if( from==FS_END )
    {
        from=SEEK_END;
    }
    else
    {
        from=SEEK_SET;
    }

    errno=0;
    _retni( lseek(fd,offset,from) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
