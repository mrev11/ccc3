
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

void _clp_diskfree(int argno)
{
    CCC_PROLOG("diskfree",1);
    str2bin(base);
    char *drive=NULL;
    
    if( ISBINARY(1) )
    {
        number(1);
        _clp_left(2);
        binary(":\\");
        add();
        drive=_parb(1);
    }
    
    DWORD spc=0;
    DWORD bps=0;
    DWORD nfc=0;
    DWORD ntc=0;
    
    GetDiskFreeSpace(drive,&spc,&bps,&nfc,&ntc);
    
    _retni( nfc*bps*spc ); 
    
    CCC_EPILOG();
}

