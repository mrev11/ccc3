
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
#include <string.h>
#include <cccapi.h>

//------------------------------------------------------------------------
void power() // erre fordul az a**x kifejezes
{
// stack: a,x --- a^x

    VALUE *x=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_NUMBER && x->type==TYPE_NUMBER )
    {
        double da=a->data.number;
        double dx=x->data.number;

        if( da>0 || (da==0&&dx>0)  )
        {
            a->data.number=pow(da,dx);
            stack=x;
            return;
        }
    }
    error_arg("power",a,2);
}

//------------------------------------------------------------------------
void _clp_power(int argno)  // CCC-bol hivhato: power(a,x)
{
    CCC_PROLOG("power",2);
    double a=_parnd(1);
    double x=_parnd(2);
    if( a<0 || (a==0&&x<=0) )
    {
        error_arg("power",base,2);
    }
    _retnd(pow(a,x));
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_exp(int argno)
{
    CCC_PROLOG("exp",1);
    double x=_parnd(1);
    _retnd(exp(x));
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_log(int argno)
{
    CCC_PROLOG("log",1);
    double x=_parnd(1);
    if( x<=0 )
    {
        error_arg("log",base,1);
    }
    _retnd(log(x));
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_sqrt(int argno)
{
    CCC_PROLOG("sqrt",1);
    double x=_parnd(1);
    if( x<0 )
    {
        error_arg("sqrt",base,1);
    }
    _retnd(sqrt(x));
    CCC_EPILOG();
}

//------------------------------------------------------------------------
