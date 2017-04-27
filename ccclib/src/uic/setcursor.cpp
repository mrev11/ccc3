
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

#include <stdio.h>
#include <cccapi.h>
#include <termapi.h>

//----------------------------------------------------------------------------
void _clp_setcursor(int argno)
{
    static int state=1;

    CCC_PROLOG("setcursor",1);
    int prevstate=state;
    if( !ISNIL(1) )
    {
        state=_parni(1);
        if( state==prevstate )
        {
            //ok
        }
        if( state  )
        {
            setcursoron();
        }
        else
        {
            setcursoroff();
        }
    }
    _retni(prevstate);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_row(int argno)
{
    stack-=argno;
    number(wherey());
}

//----------------------------------------------------------------------------
void _clp_col(int argno)
{
    stack-=argno;
    number(wherex());
}

//----------------------------------------------------------------------------
void _clp_maxrow(int argno)
{
    stack-=argno;
    number(maxrow());
}

//----------------------------------------------------------------------------
void _clp_maxcol(int argno)
{
    stack-=argno;
    number(maxcol());
}

//----------------------------------------------------------------------------
void _clp_settermsize(int argno) //settermsize(rows,cols)
{
    CCC_PROLOG("settermsize",2);
    _clp_dispbegin(0);pop();
    setwsize(_parni(2),_parni(1)); //setwsize(x,y);
    _clp_dispend(0);pop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
