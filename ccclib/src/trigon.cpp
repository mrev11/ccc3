
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

#define CCC_PI  3.14159265358979323846  
 
//--------------------------------------------------------------------------
void _clp_cos(int argno)
{
    CCC_PROLOG("cos",1);
    double x=_parnd(1);
    _retnd( cos(x) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_acos(int argno)
{
    CCC_PROLOG("acos",1);
    double x=_parnd(1);
    _retnd( acos(x) );
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_sin(int argno)
{
    CCC_PROLOG("sin",1);
    double x=_parnd(1);
    _retnd( sin(x) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_asin(int argno)
{
    CCC_PROLOG("asin",1);
    double x=_parnd(1);
    _retnd( asin(x) );
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_tan(int argno)
{
    CCC_PROLOG("tan",1);
    double x=_parnd(1);
    _retnd( tan(x) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_atan(int argno)
{
    CCC_PROLOG("atan",1);
    double x=_parnd(1);
    _retnd( atan(x) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_atn2(int argno)
{
    CCC_PROLOG("atn2",2);
    double y=_parnd(1);
    double x=_parnd(2);
    _retnd( atan2(y,x) );
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_cot(int argno)
{
    CCC_PROLOG("cot",1);
    double x=_parnd(1);
    _retnd( 1.0/tan(x) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_pi(int argno)
{
    CCC_PROLOG("pi",0);
    _retnd( CCC_PI );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_dtor(int argno)
{
    CCC_PROLOG("dtor",1);
    double x=_parnd(1);
    _retnd( x/180*CCC_PI );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_rtod(int argno)
{
    CCC_PROLOG("rtod",1);
    double x=_parnd(1);
    _retnd( x/CCC_PI*180 );
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------


