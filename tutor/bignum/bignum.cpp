
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

//Aritmetikai műveletek nagy számokkal.
//Abszolút elemi (iskolás) algoritmus.
//Csak természetes számokkal dolgozik.

//using bignum;
//    bignum;
//    cmp add sub mul div mod pow inv;
//    tostr


#include <string.h>
#include <cccapi.h>

namespace _nsp_bignum{

#define LEN(v)      ((v)->data.binary.len)
#define DIG(v,i)    ((v)->data.binary.oref->ptr.binptr[i])

//---------------------------------------------------------------------------
static void normalize(VALUE *v)
{
    while( LEN(v)>0 &&  0==DIG(v,LEN(v)-1) )
    {
        LEN(v)--;
    }
}

//---------------------------------------------------------------------------
static int cmp(VALUE *a, VALUE *b, int k=0)  // a/(k^256) <> b
{
    int i=LEN(a);
    while( i>0 && DIG(a,i-1)==0 )
    {
        i--;
    }
    int j=LEN(b);
    while( j>0 && DIG(b,j-1)==0  )
    {
        j--;
    }

    if( i-k>j )
    { 
        //printf("%d>%d\n",i-k,j);
        return 1;
    }
    else if( i-k<j )
    { 
        //printf("%d<%d\n",i-k,j);
        return -1;
    }
    else
    {
        for( ; i>k && j>0; i--, j--)
        {
            if( DIG(a,i-1)>DIG(b,j-1) )
            {
                //printf("[%d]>[%d]\n",DIG(a,i-1),DIG(b,j-1));
                return 1;
            }
            else if( DIG(a,i-1)<DIG(b,j-1) )
            {
                //printf("[%d]<[%d]\n",DIG(a,i-1),DIG(b,j-1));
                return -1;
            }
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
void _clp_cmp(int argno)
{
    CCC_PROLOG("bignum.cmp",2);
    char *a=_parb(1);
    char *b=_parb(2);
    number(cmp(base,base+1));
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
static void add1(VALUE *a, int b) //a+=b helyben, b egyjegyű
{ 
    int i=0;
    int atv=b;
    while( atv )
    {
        int d=DIG(a,i)+atv;
        DIG(a,i)=d%256;
        atv=d/256;
        i++;
    }
}

//---------------------------------------------------------------------------
void _clp_add(int argno)
{
    CCC_PROLOG("bignum.add",2);

    char *a=_parb(1);
    char *b=_parb(2);
    int lena=_parblen(1);
    int lenb=_parblen(2);
    int lenx=max(lena,lenb)+1;  //+1 az átvitelnek
    char *x=binaryl(lenx);
    memset(x,0,lenx); 
    memcpy(x,a,lena); 
    
    int i;
    int atv=0;
    for( i=0; i<lenb; i++ )
    {
        int d=x[i]+b[i]+atv;
        x[i]=d%256;
        atv=d/256;
    }
    while( atv )
    {
        int d=x[i]+atv;
        x[i]=d%256;
        atv=d/256;
        i++;
    }
    normalize(TOP());
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
static void sub2(VALUE *a, VALUE *b, int k=0) //a-=(b*256^k) helyben
{
    unsigned i;
    int atv=0;
    for( i=0; i<LEN(b); i++ )
    {
        int d=DIG(a,i+k)-(DIG(b,i)+atv);
        atv=0;
        while( d<0 )
        {
            atv++;
            d+=256;
        }
        DIG(a,i+k)=d%256;
    }

    while( atv )
    {
        int d=DIG(a,i+k)-(atv);
        atv=0;
        while( d<0 )
        {
            atv++;
            d+=256;
        }
        DIG(a,i+k)=d%256;
        i++;
    }
}

//---------------------------------------------------------------------------
void _clp_sub(int argno)
{
    CCC_PROLOG("bignum.sub",2);
    char *a=_parb(1);
    char *b=_parb(2);
    if( cmp(base,base+1)<=0 )
    {
        _retb("");
    }
    else
    {
        binarys(a,_parblen(1));
        sub2(TOP(),base+1);
        normalize(TOP());
        _rettop();
    }

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
static void mul1(VALUE *r, int b) //r*=b helyben, b egyjegyű
{
    int atv=0;
    for( unsigned i=0; i<LEN(r); i++ )
    {
        int d=DIG(r,i)*b+atv;
        DIG(r,i)=d%256;
        atv=d/256;
    }
}

//---------------------------------------------------------------------------
void _clp_mul(int argno)
{
    CCC_PROLOG("bignum.mul",2);

    char *a=_parb(1); //base
    char *b=_parb(2); //base+1
    int lena=_parblen(1);
    int lenb=_parblen(2);

    char *r=binaryl(lena+1); //base+2
    char *x=binaryl(lena+lenb+2); //base+3
    memset(x,0,lena+lenb+2); 

    VALUE *A=base;
    VALUE *B=(base+1);
    VALUE *R=(base+2);
    VALUE *X=(base+3);

    for( int i=0; i<lenb; i++ )
    {
        memcpy(r,a,lena); 
        r[lena]=0;
        mul1(R,b[i]); //r-ben részletszorzat

        int j;
        int atv=0;
        for( j=0; j<=lena; j++)
        {
            int d=x[i+j]+r[j]+atv;
            x[i+j]=d%256;
            atv=d/256;
        }
        while( atv )
        {
            int d=x[i+j]+atv;
            x[i+j]=d%256;
            atv=d/256;
            j++;
        }
    }
    normalize(TOP());
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
static void mul256(VALUE *v)
{
    memmove(&DIG(v,1), &DIG(v,0), LEN(v)-1);
    DIG(v,0)=0;
}

//---------------------------------------------------------------------------
static void sub1(VALUE *a, VALUE *b, int x, int k) //a-=b*x*(256^k) helyben
{
    binarys(&DIG(b,0),LEN(b)+1);
    mul1(TOP(),x);
    sub2(a,TOP(),k);
    pop();
}

//---------------------------------------------------------------------------
static void div2(VALUE *A, VALUE *B)
{
    //stack: -- R,Q

    VALUE *base=stack;
    char *a=&DIG(A,0); normalize(A); int lena=LEN(A);
    char *b=&DIG(B,0); normalize(B); int lenb=LEN(B);

    char *r=binaryl(lena); memcpy(r,a,lena); //maradék (kezdetben a)
    char *q=binaryl(lena); memset(q,0,lena); //hányados (kezdetben 0)
    
    VALUE *R=(base);
    VALUE *Q=(base+1);

    if( 0<lenb && cmp(A,B)>=0 ) // 0<b<=a, 0-val osztás kizárva
    {
        int k=lena-lenb;

        while(1)
        {
            while( cmp(R,B,k)>=0 ) //r>=b
            {
                normalize(R);

                int b1=b[lenb-1];
                int r1=r[LEN(R)-1];
                int r2;
                int x;

                if( r1>b1 )
                {
                    x=r1/(b1+1);
                    sub1(R,B,x,k);
                }
                else if( (int)LEN(R)>lenb+k ) // => létezik r2
                {
                    r2=r[LEN(R)-2];
                    x=(r1*256+r2)/(b1+1);
                    sub1(R,B,x,k);
                }
                else
                {
                    sub2(R,B,k);
                    x=1;
                }
                add1(Q,x);
            }

            if( k>0 )
            {
                mul256(Q);
                k--;
            }
            else
            {
                break;
            }
        }
    }
    normalize(R); //maradék
    normalize(Q); //TOP=hányados
}


//---------------------------------------------------------------------------
void _clp_div(int argno)
{
    CCC_PROLOG("bignum.div",3);
    char *a=_parb(1);
    char *b=_parb(2);

    // A base
    // B (base+1)
    // ref
    // R (base+3)
    // Q (base+4)

    div2(base,base+1);  //stack: A,B,ref,R,Q
    if( ISREF(3) )
    {
        *REFVALUE(3)=*(base+3); //R
    }
    _rettop(); //Q
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_mod(int argno)
{
    CCC_PROLOG("bignum.mod",2);
    char *a=_parb(1);
    char *b=_parb(2);

    // A base
    // B (base+1)
    // R (base+2)
    // Q (base+3)

    div2(base,base+1);  //stack: A,B,R,Q
    pop();
    _rettop(); //R
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_pow(int argno)
{
    CCC_PROLOG("bignum.pow",3);

    char *a=_parb(1);
    char *b=_parb(2);
    char *m=ISNIL(3)?0:_parb(3);
    int lena=_parblen(1);
    int lenb=_parblen(2);
    int lenm=ISNIL(3)?0:_parblen(3);

    char *x=binaryl(1); *x=1; //bignum 1

    VALUE *A=base;
    VALUE *B=(base+1);
    VALUE *M=(base+2);
    VALUE *X=(base+3);

    for(int n=lenb-1; n>=0; n-- )
    {
        int bb=b[n];
        for(int i=0; i<8; i++)  
        {
            //ciklus b minden bitjére
            
            dup();_clp_mul(2);
            if(m){push(M);_clp_mod(2);}
            
            if( bb&0x80 )
            {
                push(A);_clp_mul(2);
                if(m){push(M);_clp_mod(2);}
            }
            bb=bb<<1;
        }
    }
    normalize(X);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_bignum(int argno)
{
    CCC_PROLOG("bignum.bignum",1);

    if( ISSTRING(1) )
    {
        CHAR *s=_parc(1);
        int len=_parclen(1);
        char *x=binaryl(len);
        memset(x,0,len);
        
        if( *s=='x' || *s=='X' )
        {
            int i=0;
            while(1)
            {
                i++;
               
                if( '0'<=s[i] && s[i]<='9' )
                {
                    mul1(TOP(),16);
                    add1(TOP(),s[i]-'0');
                }
                else if( 'a'<=s[i] && s[i]<='f' )
                {
                    mul1(TOP(),16);
                    add1(TOP(),s[i]-'a'+10);
                }
                else if( 'A'<=s[i] && s[i]<='F' )
                {
                    mul1(TOP(),16);
                    add1(TOP(),s[i]-'A'+10);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            int i=0;
            while( '0'<=s[i] && s[i]<='9' )
            {
                mul1(TOP(),10);
                add1(TOP(),s[i]-'0');
                i++;
            }
        }
    }
    else
    {
        ARGERROR();
    }
    normalize(TOP());
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_tostr(int argno)
{
    CCC_PROLOG("bignum.tostr",2);
    char *x=_parb(1);
    int len=_parblen(1);
    int radix=ISNIL(2)?10:_parni(2);
    
    if( len<=0 )
    {
        stringn(L"0");
    }
    else
    {
        char *buf=0;
        int buflen=0;
        int bufpos=0;

        char *p=binaryl(len); //TOP
        memcpy(p,x,len);

        while( LEN(TOP())>0 ) 
        {
            int i=0,r=0,d;
            while( i<len )
            {
                r=r*256+p[len-i-1];
                d=r/radix;
                r=r%radix;
                p[len-i-1]=d;
                i++;
            }

            if( bufpos>=buflen )
            {
                buf=(char*)realloc(buf,buflen+=128);
            }
            if( r<10 )
            {
                buf[bufpos]=r+'0';
            }
            else
            {
                buf[bufpos]=r-10+'a';
            }
            bufpos++;
            normalize(TOP());
        }

        for(int i=0; i<bufpos/2; i++ ) 
        {
            char c1=buf[i];
            char c2=buf[bufpos-1-i];
            buf[i]=c2;
            buf[bufpos-1-i]=c1;
        }

        stringsb(buf,bufpos);
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
static void print(char *txt, VALUE *x) //teszteléshez
{
    stringn(L">>");
    stringnb(txt);add();
    stringn(L": ");add();
    stringn(L"'");add();
    push(x);_clp_tostr(1);add();
    stringn(L"'");add();
    number(LEN(x));_clp_str(1);_clp_alltrim(1);add();
    stringn(L"\n");add();
    _clp_qqout(1);
    pop();
}

//---------------------------------------------------------------------------

} //namespace _nsp_bignum
