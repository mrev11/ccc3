

#include <sckcompat.h>
#include <cccapi.h>

DEFINE_METHOD(operation);
DEFINE_METHOD(oscode);
DEFINE_METHOD(description);

//------------------------------------------------------------------------
void _clp_unix_socketpair(int argno)
{
    CCC_PROLOG("unix_socketpair",0);

    int sv[2]={-1,-1}; 
    if( 0==socketpair(AF_LOCAL,SOCK_STREAM,0,sv) )
    {
        number(sv[0]);
        number(sv[1]);
        array(2);
        _rettop();
    }
    else 
    {
        _clp_socketerrornew(0);

        DUP();
        stringn(L"unix_socketpair");
        _o_method_operation.eval(2);
        POP();

        DUP();
        number(errno);
        _o_method_oscode.eval(2);
        POP();

        DUP();
        stringn(L"unix_socketpair failed");
        _o_method_description.eval(2);
        POP();

        _clp_break(1);
        _ret(); //NIL
    }

    CCC_EPILOG();
}

//------------------------------------------------------------------------
