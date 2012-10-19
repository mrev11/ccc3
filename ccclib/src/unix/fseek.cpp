
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

#include <fcntl.h>

#include <cccapi.h>
#include <fileio.ch>    //Clipper

//----------------------------------------------------------------------------
void _clp_fseek(int argno) //Clipper
{
    CCC_PROLOG("fseek",4);
    
    int fd=_parni(1);
    off_t offs=0; //előjeles
    int mode=0;

    if( argno==2 ) 
    {
        offs = _parnlw(2); //előjeles
        mode = FS_SET;
    }
    else if( argno==3 ) 
    {
        offs = _parnlw(2); //előjeles
        mode = _parni(3);
    }
    else if( argno==4 ) //large file support 
    {
        off_t low,high;
        low  = _parnlw(2); 
        high = _parnlw(3); 
        mode = _parni(4);
        offs = (high<<32)+low;
    }
    else
    {
        ARGERROR();
    }
    
    if( mode==FS_SET )
    {
        mode=SEEK_SET;
    }
    else if( mode==FS_RELATIVE )
    {
        mode=SEEK_CUR;
    }
    else if( mode==FS_END )
    {
        mode=SEEK_END;
    }
    else
    {
        ARGERROR();
    }

    _retnd( (double) lseek(fd,offs,mode) );  //offset OK, -1 error

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
