
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

//#include <stdio.h>

#include <math.h>
#include <string.h>
#include <wchar.h>
#include <cccapi.h>

//------------------------------------------------------------------------
int sign()
{
// stack:  a --- 
// return: sign(a)

    VALUE *a=TOP(); 

    if( a->type==TYPE_NUMBER )
    { 
        double d=a->data.number;
        
        POP();

        if( d>0. )
        {
            return 1;
        }
        else if(d<0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    error_arg("sign",a,1);
    return 0;
}

//------------------------------------------------------------------------
void signneg()
{
// stack: a  ---  -a

    VALUE *a=TOP(); 

    if( a->type == TYPE_NUMBER )
    {
        a->data.number=-(a->data.number);
        return;
    }
    
    error_arg("-",a,1);
}    

//------------------------------------------------------------------------
void signpos()
{
// stack: a  ---  +a

    VALUE *a=TOP(); 

    if( a->type==TYPE_NUMBER )
    {
        return;
    }

    error_arg("+",a,1);
}    

//------------------------------------------------------------------------
void add()
{
// stack: a,b --- a+b

    VALUE *b=TOP();
    VALUE *a=TOP2();
    
    switch( a->type )
    {
        case TYPE_NUMBER:
            if( b->type==TYPE_NUMBER )
            {
                a->data.number+=b->data.number;
                stack=b;
                return;
            }
            else if( b->type==TYPE_DATE )
            {
                a->type=TYPE_DATE;
                a->data.date=D2LONG(a->data.number)+b->data.date;
                stack=b;
                return;
            }
            break;

        case TYPE_DATE:
            if( b->type==TYPE_NUMBER )
            {
                a->data.date+=D2LONG(b->data.number);
                stack=b;
                return;
            }
            break;

        case TYPE_STRING:

            if( b->type==TYPE_STRING )
            {
                unsigned long la=STRINGLEN(a);
                unsigned long lb=STRINGLEN(b);
                
                if( lb==0 )
                {
                    // OK
                }
                else if( la==0 )
                {
                    *a=*b;
                }
                else
                {
                    // egyik string üres

                    if( la>MAXSTRLEN || lb>MAXSTRLEN )
                    {
                        error_cln("add",a,2);
                    }
  
                    CHAR *sum=stringl(la+lb); 
                    memcpy(sum,STRINGPTR(a),la*sizeof(CHAR));
                    memcpy(sum+la,STRINGPTR(b),lb*sizeof(CHAR));
                    *a=*TOP();
                }

                stack=b;
                return;
            }
            break; 

        case TYPE_BINARY:

            if( b->type==TYPE_BINARY )
            {
                unsigned long la=BINARYLEN(a);
                unsigned long lb=BINARYLEN(b);
                
                if( lb==0 )
                {
                    // OK
                }
                else if( la==0 )
                {
                    *a=*b;
                }
                else
                {
                    // egyik sem üres

                    if( la>MAXBINLEN || lb>MAXBINLEN )
                    {
                        error_bln("add",a,2);
                    }

                    BYTE *sum=binaryl(la+lb); 
                    memcpy(sum,BINARYPTR(a),la*sizeof(BYTE));
                    memcpy(sum+la,BINARYPTR(b),lb*sizeof(BYTE));
                    *a=*TOP();
                }

                stack=b;
                return;
            }
            break; 
    }
    error_arg("add",a,2);
}

//------------------------------------------------------------------------
void addnum(double v)
{
// stack: a --- a+v

    VALUE *a=TOP();
    
    if( a->type==TYPE_NUMBER )
    {
        a->data.number+=v;
        return;
    }
    else if( a->type==TYPE_DATE )
    {
        a->data.date+=D2LONG(v);
        return;
    }

    error_arg("addnum",a,1);
}

//------------------------------------------------------------------------
void mulnum(double v)
{
// stack: a --- a*v

    VALUE *a=TOP();
    
    if( a->type==TYPE_NUMBER )
    {
        a->data.number*=v;
        return;
    }

    error_arg("mulnum",a,1);
}

//------------------------------------------------------------------------
void addneg(double v)
{
// stack: a --- -(a+v)

    VALUE *a=TOP();
    
    if( a->type==TYPE_NUMBER )
    {
        a->data.number=-(a->data.number+v);
        return;
    }
    
    //más típust, pl. DATE-t
    //nem lehet negálni

    error_arg("addneg",a,1);
}

//------------------------------------------------------------------------
void sub()
{
// stack: a,b --- a-b

    VALUE *b=TOP();
    VALUE *a=TOP2();

    switch( a->type )
    {
        case TYPE_NUMBER:
            if( b->type==TYPE_NUMBER )
            {
                a->data.number-=b->data.number;
                stack=b;
                return;
            }
            break;

        case TYPE_DATE:
            if( b->type==TYPE_NUMBER )
            {
                a->data.date-=D2LONG(b->data.number);
                stack=b;
                return;
            }
            else if( b->type==TYPE_DATE )
            {
                long diff=a->data.date-b->data.date;
                stack=a;
                number(diff);
                return;
            }
            break;
    }
    error_arg("sub",a,2);
}

//------------------------------------------------------------------------
void mul()
{
// stack: a,b --- a*b

    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_NUMBER && b->type==TYPE_NUMBER )
    {
        a->data.number*=b->data.number;
        stack=b;
        return;
    }
    error_arg("mul",a,2);
}

//------------------------------------------------------------------------
void div()
{
// stack: a,b --- a/b

    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_NUMBER && b->type==TYPE_NUMBER )
    {
        if( b->data.number!=(double)0 )
        {
            a->data.number/=b->data.number;
            stack=b;
            return;
        }
        error_div("div",a,2);
    }
    error_arg("div",a,2);
}

//------------------------------------------------------------------------
void modulo()
{
// stack: a,b --- a%b

    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_NUMBER && b->type==TYPE_NUMBER )
    {
        // double xb=abs(b->data.number);
        // vigyázni az abs függvénnyel, 
        // nagy számokra rossz, 1-et ad!

        double xb=b->data.number;
        if( xb<0 )
        {
            xb=-xb;
        }
    
        if( xb>0 )
        {
            double xa=a->data.number;
           
           // printf("\n %24.10f",xa);
           // printf("\n %24.10f",xb);
           // printf("\n %24.10f",xa/xb);
           // printf("\n %24.10f",floor(xa/xb));
           // printf("\n %24.10f",xb*floor(xa/xb));
           // printf("\n %24.10f",xa-xb*floor(xa/xb));
            
            a->data.number-=xb*(xa>0?floor(xa/xb):ceil(xa/xb));
            stack=b;
            return;
        }
        error_div("modulo",a,2);
    }
    error_arg("mod",a,2);
}

//------------------------------------------------------------------------
void _clp_mod(int argno)
{
    CCC_PROLOG("mod",2);
    modulo();
    CCC_EPILOG();
}

//------------------------------------------------------------------------
void _clp_abs(int argno)
{
    CCC_PROLOG("abs",1);
    double a=_parnd(1);
    if( a<0 )
    {
        base->data.number=-a;
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------

