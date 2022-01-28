
#include <cccapi.h>

// ezzel eldontheto, hogy azonos-e ket memoriaobjektum

void _clp_oref(int argno)
{
    CCC_PROLOG("oref",1);
    VALUE *v=base;
    if( v->type==TYPE_REF )
    {
        v=&(v->data.vref->value);
    }
    if( v->type>TYPE_POINTER )
    {
        _retp( v->data.array.oref );
    }
    else
    {
        _retp( (void*)0 );
    }
    CCC_EPILOG();
}

