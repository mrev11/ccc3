
#include <cccapi.h>

extern int termio_socket();

void _clp_sckterm(int argno)
{
    stack-=argno;
    number(termio_socket());
}
