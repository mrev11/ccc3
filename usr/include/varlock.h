
#include <stdlib.h>
#include <pthread.h>

//----------------------------------------------------------------------------------------
struct varlock
{
    int prime;
    pthread_mutex_t *mutex;

    void init()
    {
        for( int i=0; i<prime; i++  )
        {
            mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        }
    };

    varlock(int len)
    {
        prime=len;
        mutex=(pthread_mutex_t*)malloc(prime*sizeof(pthread_mutex_t));
        init();
    };

    int lock(void *p)
    {
        int x=((unsigned long)p)%prime;
        pthread_mutex_lock( &mutex[x] );
        return x;
    };

    int lock_try(void *p)
    {
        int x=((unsigned long)p)%prime;
        if( pthread_mutex_trylock(&mutex[x]) ) // -> 0 vagy errno
        {
            return -1;
        }
        return x;
    };

    void lock_free(int x)
    {
        pthread_mutex_unlock(&mutex[x]);
    };

    void clear()
    {
        for(int i=0; i<prime; i++)
        {
            pthread_mutex_unlock(&mutex[i]);
        }
    };

};

//----------------------------------------------------------------------------------------


