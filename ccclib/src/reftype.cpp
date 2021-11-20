
#include <cccapi.h>

void _clp_reftype(int argno)
{
    CCC_PROLOG("reftype",1);
    _retl( base->type==TYPE_REF );
    CCC_EPILOG();
}    

//  HASZNALAT
//
//      proba(x,@y)
//
//  function proba(x,y)
//      reftype(y)          // ->.f., minden y-ra
//      reftype([x])        // ->.f., mert x nem referencia
//      reftype([y])        // ->.t., mert y referencia
//      reftype(*[2..2])    // ->.t., mert y referencia