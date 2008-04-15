
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

//------------------------------------------------------------------------
void _clp_min(int argno)
{
    CCC_PROLOG("min",2);
    if( ISNUMBER(1) )
    {   
        double n1=base->data.number;
        double n2=_parnd(2);
        base->data.number=min(n1,n2);
        stack=base+1;
    }
    else if( ISDATE(1) )
    {
        long d1=base->data.date;
        long d2=_pard(2);
        base->data.date=min(d1,d2);
        stack=base+1;
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_max(int argno)
{
    CCC_PROLOG("max",2);
    if( ISNUMBER(1) )
    {   
        double n1=base->data.number;
        double n2=_parnd(2);
        base->data.number=max(n1,n2);
        stack=base+1;
    }
    else if( ISDATE(1) )
    {
        long d1=base->data.date;
        long d2=_pard(2);
        base->data.date=max(d1,d2);
        stack=base+1;
    }
    else
    {
        ARGERROR();
    }
    CCC_EPILOG();
}    

//------------------------------------------------------------------------
