
#include <cccapi.h>

// compat
// (fork nezi ezeket)


int termio_socket()
{
    return -1;
}

void *thread_display(void *ptr)
{
    return 0;
}


void *thread_message(void *ptr)
{
    return 0;
}

void _clp_sckterm(int argno)
{
    stack-=argno;
    PUSHNIL();
}
