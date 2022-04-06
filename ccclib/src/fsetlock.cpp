
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

// Lock függvények  (fsetlock, funlock)

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include <cccapi.h>
#include <flock.h>


//-----------------------------------------------------------------------------
void _clp_fsetlock(int argno)
{
    // lock varakozas nelkul

    // fsetlock(fd, offset, length [,flag])
    // fsetlock(fd, low, high, length [,flag])
    // flag defaultja: .t. (exclusive)

    CCC_PROLOG("fsetlock",5);

    int xp=0;
    int flags=CCCLK_NOWAIT;
    if( ISFLAG(argno) )
    {
        xp=1;
        flags+=_parl(argno)?CCCLK_WRITE:CCCLK_READ;
    }
    
    int fd=0;
    off_t start=0;
    unsigned low=0,high=0,length=0;

    if( (argno-xp)==3 ) 
    {
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
    }
    else if( (argno-xp)==4 ) //large file support  
    {
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
    }
    else
    {
        ARGERROR();
    }
    
    _retni( _ccc_lock(fd,low,high,length,flags) );

    CCC_EPILOG();
}


//-----------------------------------------------------------------------------
void _clp_fwaitlock(int argno)
{
    // lock varakozassal

    // fwaitlock(fd, offset, length [,flag])
    // fwaitlock(fd, low, high, length [,flag])
    // flag defaultja: .t. (exclusive)

    CCC_PROLOG("fwaitlock",5);

    int xp=0;
    int flags=CCCLK_WAIT;
    if( ISFLAG(argno) )
    {
        xp=1;
        flags+=_parl(argno)?CCCLK_WRITE:CCCLK_READ ;
    }
    
    int fd=0;
    off_t start=0;
    unsigned low=0,high=0,length=0;

    if( (argno-xp)==3 ) 
    {
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
    }
    else if( (argno-xp)==4 ) //large file support  
    {
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
    }
    else
    {
        ARGERROR();
    }
    
    _retni( _ccc_lock(fd,low,high,length,flags) );

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_ftimeoutlock(int argno)
{
    // lock varakozassal timeout-tal

    // ftimeoutlock(fd, offset, length [,flag])
    // ftimeoutlock(fd, low, high, length [,flag])
    // flag defaultja: .t. (exclusive)

    // a timeout merteket igy lehet megadni
    //
    //     export CCCLK_TIMEOUT=seconds
    //
    // ha ez nincs megadva vagy 0, akkor ftimeoutlock = fsetlock
    // windowson mindig ftimeoutlock = fsetlock
    
    CCC_PROLOG("ftimeoutlock",5);

    int xp=0;
    int flags=CCCLK_WAIT|CCCLK_TIMEOUT;
    if( ISFLAG(argno) )
    {
        xp=1;
        flags+=_parl(argno)?CCCLK_WRITE:CCCLK_READ ;
    }
    
    int fd=0;
    off_t start=0;
    unsigned low=0,high=0,length=0;

    if( (argno-xp)==3 ) 
    {
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
    }
    else if( (argno-xp)==4 ) //large file support  
    {
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
    }
    else
    {
        ARGERROR();
    }
    
    _retni( _ccc_lock(fd,low,high,length,flags) );

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_funlock(int argno)
{
    CCC_PROLOG("funlock",4);

    int fd=0;
    off_t start=0,low=0,high=0,length=0;
 
    if( argno==3 ) 
    {
        fd     = _parni(1);
        start  = _parnuw(2); 
        length = _parnuw(3); 
        low    = start&0xffffffff;
        high   = start>>32;
    }
    else if( argno==4 ) //large file support 
    {
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  = high;
        start  = (start<<32)+low;
    }
    else
    {
        ARGERROR();
    }

    _retni( _ccc_unlock(fd,low,high,length) );

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------

