
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

//------------------------------------------------------------------------
void _clp_int(int argno)
{
    CCC_PROLOG("int",1);
    double d=_parnd(1);
    if( d>0 )
    {
        base->data.number=floor(d);
    }
    else
    {
        base->data.number=-floor(-d);
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_round(int argno)  // optimalizált változat 
{
    CCC_PROLOG("round",2);
    double x=_parnd(1);
    int id=_parni(2);
    static double p[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    if( id>0 )
    {
        if(id>9) id=9;
        x=floor(0.5+x*p[id])/p[id];
    }
    else if( id<0 )
    {
        id=-id; if(id>9) id=9;
        x=floor(0.5+x/p[id])*p[id];
    }
    else
    {
        x=floor(0.5+x);
    }
    _retnd(x);
    CCC_EPILOG();
}

//------------------------------------------------------------------------

