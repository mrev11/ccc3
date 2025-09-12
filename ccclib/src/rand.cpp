
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

#include <math.h>
#include <cccapi.h>
 
#define FACTOR        16807.0
#define MODULUS       2147483647.0
#define SEED          7657463.0 

#define DMOD(x,y)     ((x)-floor((x)/(y))*(y))


//---------------------------------------------------------------------------
void _clp_rand(int argno) 
{
    CCC_PROLOG("rand",1);
    static MUTEX_CREATE(mutex);
    static double seed=SEED;

    MUTEX_LOCK(mutex);
    if( ISNUMBER(1) )
    {
        seed=_parnd(1);
    }

    if( seed==0 )
    {
        seed=SEED;
    }
    seed=seed*FACTOR;
    seed=DMOD(seed,MODULUS); 
    _retnd( seed/MODULUS );
    MUTEX_UNLOCK(mutex);

    CCC_EPILOG();
}

//---------------------------------------------------------------------------

