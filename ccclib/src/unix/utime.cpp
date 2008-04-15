
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
#include <utime.h>
#include <cccapi.h>

//--------------------------------------------------------------------
void _clp_utime(int argno) //utime(fspec, actime, modtime)
{              
    CCC_PROLOG("utime",3);
    convertfspec2nativeformat(base);
    struct utimbuf u;
    char *fname=_parb(1);
    u.actime =_parnl(2);
    u.modtime=_parnl(3);
    _retni( utime(fname,&u) );
    CCC_EPILOG();   
}

//--------------------------------------------------------------------
void _clp_touch(int argno) //touch(fspec)
{              
    CCC_PROLOG("touch",1);
    _clp_convertfspec2nativeformat(1);
    char *fspec=_parb(1);
    _retni( utime(fspec,0) );
    CCC_EPILOG();   
}
 
//--------------------------------------------------------------------

