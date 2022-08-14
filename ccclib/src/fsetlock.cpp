
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
#include <flock.h>

//----------------------------------------------------------------------------------------
void _clp_fsetlock(int argno) //lock varakozas nelkul
//
// fsetlock( fd,  start, length, rwtype)          (a)
// fsetlock( fd,  low,   high,   length, rwtype)  (b)
//           1    2      3       4       5
{
    CCC_PROLOG("fsetlock",5);

    int fd=0;
    off_t start=0, low=0, high=0, length=0;
    int rwtype=1;  // writelock

    if( !ISNUMBER(4) )
    {
        // (a) eset
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
        if( !ISNIL(4) )
        {
            rwtype=_parl(4);  // .t.=write, .f.=read, default=.t.
        }
    }
    else
    {
        // (b) eset
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
        if( !ISNIL(5) )
        {
            rwtype=_parl(5); // .t.=write, .f.=read, default=.t.
        }
    }

    _retni( fsetlock(fd,low,high,length,rwtype) );

    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_fwaitlock(int argno) // lock korlatlan varakozassal
//
// fwaitlock( fd,  start, length, rwtype)          (a)
// fwaitlock( fd,  low,   high,   length, rwtype)  (b)
//            1    2      3       4       5
{
    CCC_PROLOG("fwaitlock",5);

    int fd=0;
    off_t start=0, low=0, high=0, length=0;
    int rwtype=1;  // writelock

    if( !ISNUMBER(4) )
    {
        // (a) eset
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
        if( !ISNIL(4) )
        {
            rwtype=_parl(4);  // .t.=write, .f.=read, default=.t.
        }
    }
    else
    {
        // (b) eset
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
        if( !ISNIL(5) )
        {
            rwtype=_parl(5); // .t.=write, .f.=read, default=.t.
        }
    }

    _retni( fwaitlock(fd,low,high,length,rwtype) );

    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_ftimeoutlock(int argno)
//
// ftimeoutlock( fd,  start, length, rwtype, timeout)          (a)
// ftimeoutlock( fd,  low,   high,   length, rwtype, timeout)  (b)
//               1    2      3       4       5       6
//
//  timeout == 0: nem var
//  timeout >  0: a megadott ideig var
//  timeout ==-1: korlatlan ideig var
//
//  ret ==  0: OK
//  ret == -1: sikertelen
{
    CCC_PROLOG("ftimeoutlock",6);
    
    int fd=0;
    off_t start=0, low=0, high=0, length=0;
    int rwtype=1;  // writelock
    int timeout=0; // nowait

    if( !ISNUMBER(4) )
    {
        // (a) eset
        fd     = _parni(1);
        start  = _parnuw(2);
        length = _parnuw(3);
        low    = start&0xffffffff;
        high   = start>>32;
        if( !ISNIL(4) )
        {
            rwtype=_parl(4);  // .t.=write, .f.=read, default=.t.
        }
        if( !ISNIL(5) )
        {
            timeout=_parni(5); // default: 0=nowait
        }
    }
    else
    {
        // (b) eset
        fd     = _parni(1);
        low    = _parnuw(2); 
        high   = _parnuw(3); 
        length = _parnuw(4);
        start  =  high;
        start  =  (start<<32)+low;
        if( !ISNIL(5) )
        {
            rwtype=_parl(5); // .t.=write, .f.=read, default=.t.
        }
        if( !ISNIL(6) )
        {
            timeout=_parni(6);  // default: 0=nowait
        }
    }

    _retni( ftimeoutlock(fd,low,high,length,rwtype,timeout) );
    
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
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

    _retni( funlock(fd,low,high,length) );

    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
