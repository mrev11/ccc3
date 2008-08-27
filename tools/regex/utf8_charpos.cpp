
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

#define H1 0x80  //1000 0000
#define H2 0xc0  //1100 0000

#define CONT(x)  (((x)&H2)==H1) //continuing char


//Ezek UTF-8 kódolású stringben karaktereket számolnak,
//eközben NEM elleőrzik az UTF-8 kódolás helyességét.
//charpos: bpos byteot megy előre közben számolja a karaktereket (->cpos).
//bytepos: addig megy előre, amíg cpos karakter nem talál (->bpos).


namespace _nsp_utf8{
//----------------------------------------------------------------------------
void _clp_charpos(int argno)
{
    //charpos(x,bpos) -> cpos
    //x egy UTF-8 kódolású string (bytesorozat)
    //ebben a bpos byte-pozíción a cpos-adik karakter kezdődik
    //
    //cpos==0
    //  ha bpos<1
    //  ha bpos>len(x)
    //  ha bpos-on nem kezdődik karakter

    CCC_PROLOG("charpos",2);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    unsigned bpos=_parnu(2);
    unsigned cpos=0;
    
    if( 0<bpos && bpos<=blen && !CONT(*(p+bpos-1)) )
    {
        unsigned i;
        for( i=0; i<bpos; i++ )
        {
            if( !CONT(*(p+i)) ) //not continuing
            {
                cpos++;
            }
        }
    }
    _retni(cpos);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_bytepos(int argno)
{
    //bytepos(x,cpos) -> bpos
    //x egy UTF-8 kódolású string (bytesorozat)
    //ebben a cpos-adik karakter a bpos byte-pozíción kezdődik
    //
    //bpos==0
    //  ha x-ben kevesebb, mint cpos karakter van

    CCC_PROLOG("charpos",2);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    unsigned cpos=_parnu(2);
    unsigned clen=0;
    unsigned bpos=0;

    if( 0<cpos && cpos<=blen )
    {
        unsigned i;
        for( i=0; i<blen; i++ )
        {
            if( !CONT(*(p+i)) ) //not continuing
            {
                if( ++clen>=cpos )
                {
                    bpos=i+1;
                    break;
                }
            }
        }
    }
    _retni(bpos);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
}//namespace _nsp_utf8
