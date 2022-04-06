
#include <cccapi.h>

void _clp_alarm(int argno)
{
    CCC_PROLOG("alarm",1);
    alarm(_parni(1));
    CCC_EPILOG();
}


// Windows MSYS2-ben nincs alarm()

