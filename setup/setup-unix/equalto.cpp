
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

#include <string.h>
#include <cccapi.h>


DEFINE_METHOD(args);
DEFINE_METHOD(description);
//DEFINE_METHOD(operation);


//------------------------------------------------------------------------
void eqeq() //stack: a,b --- a==b
{
    logical( equalto() );
}

void neeq() //stack: a,b --- a!=b
{
    logical( notequal() );
}

void lt()  //stack: a,b --- a<b
{
    logical( lessthan() );
}

void gt() //stack: a,b --- a>b
{
    logical( greaterthan() );
}

void lteq() //stack: a,b --- a<=b
{
    logical( !greaterthan() );
}

void gteq() //stack: a,b --- a>=b
{
    logical( !lessthan() );
}


//------------------------------------------------------------------------
void topnot() //stack: f --- !f
{
    logical( !flag() );
}

#if (defined GCC_VERSION) && (GCC_VERSION_MAJOR < 3) && (GCC_VERSION_MINOR < 96) 

void not() // stack: f --- !f
{
    logical( !flag() );
}

#endif 

//------------------------------------------------------------------------
int flag() 

// stack: f ---
// return: 1, ha f==TRUE, 0, ha f==FALSE

{
    VALUE *base=TOP();
    if( base->type==TYPE_FLAG )
    {
        int result=(0!=(base->data.flag));
        POP();
        return result;
    }
    
    _clp_errornew(0);

    DUP();
    PUSH(base);
    array(1);
    _o_method_args.eval(2);
    POP();

    DUP();
    string(L"conditional error");
    _o_method_description.eval(2);
    POP();
        
    _clp_break(1);
    return 0;    
}

//------------------------------------------------------------------------
int equalto()  // szigorú (nem Clipper =, != ...) egyenlőség

// stack: a,b ---
// return: 1, ha a==b, 0, ha !(a==b)

{
    int result=0;

    VALUE *b=TOP();  //teteje
    VALUE *a=TOP2(); //alatta
    
    if( (a->type==TYPE_NIL) || (b->type==TYPE_NIL) )
    {
        // NIL bármivel összehasonlítható,
        // de csak a NIL==NIL ad .T.-t
    
        result=a->type==b->type;
        stack-=2;
        return result;
    }

    else if( a->type==b->type )
    {
        switch( a->type )
        {
            case TYPE_STRING:
            {
                int al=a->data.string.len;
                int bl=b->data.string.len;
             
                if( al!=bl )
                    result=0; // különböző hosszúak --> nem egyenlő
                else if( al==0 )
                    result=1; // üresek --> egyenlő
                else
                {
                    //egyik sem üres
                    CHAR *ap=STRINGPTR(a);
                    CHAR *bp=STRINGPTR(b);
 
                    result=1;
                    while( bl-->0 )
                    {
                        if( *ap++!=*bp++ )
                        {
                            result=0;
                            break;
                        }
                    }
                }

                stack-=2;
                return result;
            }      

            case TYPE_BINARY:
            {
                int al=a->data.binary.len;
                int bl=b->data.binary.len;
             
                if( al!=bl )
                    result=0; // különböző hosszúak --> nem egyenlő
                else if( al==0 )
                    result=1; // üresek --> egyenlő
                else
                {
                    //egyik sem üres
                    BYTE *ap=BINARYPTR(a);
                    BYTE *bp=BINARYPTR(b);
 
                    result=1;
                    while( bl-->0 )
                    {
                        if( *ap++!=*bp++ )
                        {
                            result=0;
                            break;
                        }
                    }
                }

                stack-=2;
                return result;
            }      

            case TYPE_NUMBER:
                result=(a->data.number==b->data.number);
                stack-=2;
                return result;

            case TYPE_DATE:        
                result=(a->data.date==b->data.date);
                stack-=2;
                return result;

            case TYPE_POINTER:        
                result=(a->data.pointer==b->data.pointer);
                stack-=2;
                return result;
 
            case TYPE_FLAG:        
                // vigyázat, a logikai érték
                // TRUE, ha !=0, FALSE, ha ==0
                // a TRUE értékek eltérhetnek
            
                result=((0==a->data.flag)==(0==b->data.flag));
                stack-=2;
                return result;
            
            case TYPE_OBJECT:
                result=((a->data.object.oref)==(b->data.object.oref));
                stack-=2;
                return result;
 
            case TYPE_ARRAY:
                result=((a->data.array.oref)==(b->data.array.oref));
                stack-=2;
                return result;
 
            case TYPE_BLOCK:
                result=((a->data.block.oref)==(b->data.block.oref));
                stack-=2;
                return result;
                
            //default:    
            // más típusra nincs értelmezve, 
            // ezért nincs default érték,
            // hanem rámegy a hibaágra
        }
    }
 
    error_arg("==",TOP2(),2);
    return result;
}


//------------------------------------------------------------------------
int notequal()

// stack: a,b ---
// return: 1, ha a!=b, 0, ha a=b (vigyázat Clipper relációk!)

{
    int result=0;
  
    VALUE *b=TOP();  // jobboldal
    VALUE *a=TOP2(); // baloldal

    if( (a->type==TYPE_NIL) || (b->type==TYPE_NIL) )
    {
        result=(a->type!=b->type);
        stack-=2;
        return result;
    }

    else if( a->type==b->type )
    {
        switch( a->type )
        {
            case TYPE_STRING:
            {
                // a Clipper a relációt a jobboldal hosszában vizsgálja

                int  al=a->data.string.len;
                int  bl=b->data.string.len;

                if( bl==0 )
                {
                    result=0; //a jobboldal hosszában egyezik --> egyenlő
                }
                else if( al<bl )
                {
                    result=1; // a jobboldal hosszabb --> nem egyenlő
                }
                else
                {
                    // itt 0<bl<=al

                    CHAR *ap=STRINGPTR(a);
                    CHAR *bp=STRINGPTR(b);

                    result=0;
                    while( bl-->0 ) // amíg tart a jobboldal
                    {
                        if( *ap++ != *bp++ )
                        {
                            result=1; 
                            break;
                        }
                    }
                }

                stack-=2;
                return result;
            }      

            case TYPE_BINARY:
            {
                // a Clipper a relációt a jobboldal hosszában vizsgálja

                int  al=a->data.binary.len;
                int  bl=b->data.binary.len;

                if( bl==0 )
                {
                    result=0; //a jobboldal hosszában egyezik --> egyenlő
                }
                else if( al<bl )
                {
                    result=1; // a jobboldal hosszabb --> nem egyenlő
                }
                else
                {
                    // itt 0<bl<=al

                    BYTE *ap=BINARYPTR(a);
                    BYTE *bp=BINARYPTR(b);

                    result=0;
                    while( bl-->0 ) // amíg tart a jobboldal
                    {
                        if( *ap++ != *bp++ )
                        {
                            result=1; 
                            break;
                        }
                    }
                }

                stack-=2;
                return result;
            }      

            case TYPE_NUMBER:
                result=(a->data.number!=b->data.number);
                stack-=2;
                return result;
 
            case TYPE_DATE:        
                result=(a->data.date!=b->data.date);
                stack-=2;
                return result;

            case TYPE_POINTER:        
                result=(a->data.pointer!=b->data.pointer);
                stack-=2;
                return result;
 
            case TYPE_FLAG:        
                result=((0==a->data.flag)!=(0==b->data.flag));
                stack-=2;
                return result;
 
            case TYPE_OBJECT:
                result=((a->data.object.oref)!=(b->data.object.oref));
                stack-=2;
                return result;
 
            case TYPE_ARRAY:
                result=((a->data.array.oref)!=(b->data.array.oref));
                stack-=2;
                return result;
 
            case TYPE_BLOCK:
                result=((a->data.block.oref)!=(b->data.block.oref));
                stack-=2;
                return result;
            
            // más típusokra nincs értelmezve, 
            // ezért nincs default érték
            // rámegy a hibaágra
        }
    }

    error_arg("!=",TOP2(),2);
    return 0;    
}

//------------------------------------------------------------------------
int greaterthan()

// stack: a,b ---
// return: 1, ha a>b, 0, ha !(a>b) (vigyázat Clipper relációk!)

{
    int result=0;

    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==b->type )
    {
        switch( a->type )
        {
            case TYPE_STRING:
            {
                int len=min( a->data.string.len, b->data.string.len );
            
                if( len==0 )
                {
                    // ha a hossza 0, akkor nem lehet nagyobb;
                    // ha b hossza 0, akkor a jobboldal hosszúságában
                    // vizsgálva (!) a megint nem lehet nagyobb
                    result=0; 
                }
                else
                {
                    // itt egyik string sem üres

                    CHAR *ap=STRINGPTR(a);
                    CHAR *bp=STRINGPTR(b);
            
                    while( (*ap==*bp) && (--len>0) )
                    {
                        ap++;
                        bp++;
                    }
        
                    if( len==0 )
                    {
                        result=0;
                    }
                    else
                    {
                        result=((unsigned)*ap > (unsigned)*bp);
                    }
            
                    // ha a, vagy b elfogyott, akkor b hosszában
                    // a nem lehet nagyobb, ha előbb van eltérés,
                    // akkor a nagyobb <--> ha *ap nagyobb
                }
 
                stack-=2;
                return result;
            }      

            case TYPE_BINARY:
            {
                int len=min( a->data.binary.len, b->data.binary.len );
            
                if( len==0 )
                {
                    // ha a hossza 0, akkor nem lehet nagyobb;
                    // ha b hossza 0, akkor a jobboldal hosszúságában
                    // vizsgálva (!) a megint nem lehet nagyobb
                    result=0; 
                }
                else
                {
                    // itt egyik string sem üres

                    BYTE *ap=BINARYPTR(a);
                    BYTE *bp=BINARYPTR(b);
            
                    while( (*ap==*bp) && (--len>0) )
                    {
                        ap++;
                        bp++;
                    }
        
                    if( len==0 )
                    {
                        result=0;
                    }
                    else
                    {
                        result=((unsigned)*ap > (unsigned)*bp);
                    }
            
                    // ha a, vagy b elfogyott, akkor b hosszában
                    // a nem lehet nagyobb, ha előbb van eltérés,
                    // akkor a nagyobb <--> ha *ap nagyobb
                }
 
                stack-=2;
                return result;
            }      

            case TYPE_NUMBER:
                result=(a->data.number>b->data.number);
                stack-=2;
                return result;
 
            case TYPE_DATE:        
                result=(a->data.date>b->data.date);
                stack-=2;
                return result;
 
            case TYPE_FLAG:        
                result=((a->data.flag) && (!b->data.flag));
                stack-=2;
                return result;

            // más típusokra nincs értelmezve, 
            // ezért nincs default érték,
            // rámegy a hibaágra
        }
    }

    error_arg(">",TOP2(),2);
    return 0;    
}

//------------------------------------------------------------------------
int lessthan()

// stack: a,b ---
// return: 1, ha a<b, 0, ha !(a<b) (vigyázat Clipper relációk!)

{
    int result=0;

    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==b->type )
    {
        switch( a->type )
        {
            case TYPE_STRING:
            {
                int  al=a->data.string.len;
                int  bl=b->data.string.len;
            
                if( bl==0 )
                {
                    result=0;
                }
                else if( al==0 )
                {
                    result=1;
                }
                else
                {
                    CHAR *ap=STRINGPTR(a);
                    CHAR *bp=STRINGPTR(b);

                    result=0; //ha elfogy a jobboldal
 
                    while( bl-->0 )
                    {
                        unsigned ac,bc;
            
                        if( !(al-->0) )
                        {
                            result=1; //elfogyott a baloldal
                            break;
                        }
                
                        ac=*ap++;
                        bc=*bp++;
              
                        if( ac!=bc )
                        {
                            result=(bc>ac); 
                            break;
                        }
                    }
                }
                stack-=2;
                return result;
            }      

            case TYPE_BINARY:
            {
                int  al=a->data.binary.len;
                int  bl=b->data.binary.len;
            
                if( bl==0 )
                {
                    result=0;
                }
                else if( al==0 )
                {
                    result=1;
                }
                else
                {
                    BYTE *ap=BINARYPTR(a);
                    BYTE *bp=BINARYPTR(b);

                    result=0; //ha elfogy a jobboldal
 
                    while( bl-->0 )
                    {
                        unsigned ac,bc;
            
                        if( !(al-->0) )
                        {
                            result=1; //elfogyott a baloldal
                            break;
                        }
                
                        ac=*ap++;
                        bc=*bp++;
              
                        if( ac!=bc )
                        {
                            result=(bc>ac); 
                            break;
                        }
                    }
                }
                stack-=2;
                return result;
            }      

            case TYPE_NUMBER:
                result=(a->data.number<b->data.number);
                stack-=2;
                return result;
 
            case TYPE_DATE:        
                result=(a->data.date<b->data.date);
                stack-=2;
                return result;
 
            case TYPE_FLAG:        
                result=((!a->data.flag) && (b->data.flag));
                stack-=2;
                return result;
 
            // más típusokra nincs értelmezve, 
            // ezért nincs default érték
            // rámegy a hibaágra
        }
    }

    error_arg("<",TOP2(),2);
    return result;
}

//------------------------------------------------------------------------
void ss() //substring

// stack: a,b --- a $ b

{
    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_STRING && b->type==TYPE_STRING )
    {
        int  al=a->data.string.len;
        int  bl=b->data.string.len;
            
        if( al==0 )
        {
            stack-=2;
            logical(1);
        }
        else if( bl==0 )
        {
            stack-=2;
            logical(0);
        }
        else
        {
            CHAR *ap=STRINGPTR(a);
            CHAR *bp=STRINGPTR(b);

            int i,j;
            for(i=0; i<=bl-al; i++)
            {
                for(j=0; j<al; j++)
                {
                    if( *(bp+i+j)!=*(ap+j) ) break;
                }
                if( j>=al ) 
                {
                    break;
                }
            }
            stack-=2;
            logical( i<=bl-al );
        }

        return;
    }      

    else if( a->type==TYPE_BINARY && b->type==TYPE_BINARY )
    {
        int  al=a->data.binary.len;
        int  bl=b->data.binary.len;
            
        if( al==0 )
        {
            stack-=2;
            logical(1);
        }
        else if( bl==0 )
        {
            stack-=2;
            logical(0);
        }
        else
        {
            BYTE *ap=BINARYPTR(a);
            BYTE *bp=BINARYPTR(b);

            int i,j;
            for(i=0; i<=bl-al; i++)
            {
                for(j=0; j<al; j++)
                {
                    if( *(bp+i+j)!=*(ap+j) ) break;
                }
                if( j>=al ) 
                {
                    break;
                }
            }
            stack-=2;
            logical( i<=bl-al );
        }

        return;
    }      

    error_arg("$",TOP2(),2);
}

//------------------------------------------------------------------------
