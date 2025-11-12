
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


    int lock(int idx) // egy mutexet megfog (1 based index alapjan)
    {
        pthread_mutex_lock( &mutex[idx-1] );
        return idx;
    };


    int lock(void *p) // egy mutexet megfog
    {
        int x=((unsigned long long)p)%prime;
        pthread_mutex_lock( &mutex[x] );
        return x+1; // 1 based
    };

    int lock(void *p1, void *p2) // ket mutexet megfog
    {
        int x1=((unsigned long long)p1)%prime;
        int x2=((unsigned long long)p2)%prime;

        if( x1<x2 )
        {
            pthread_mutex_lock( &mutex[x1] );
            pthread_mutex_lock( &mutex[x2] );
            return ((x1+1)<<16)|(x2+1); // 1 based
        }
        else if( x1>x2 )
        {
            pthread_mutex_lock( &mutex[x2] );
            pthread_mutex_lock( &mutex[x1] );
            return ((x2+1)<<16)|(x1+1); // 1 based
        }
        else
        {
            pthread_mutex_lock( &mutex[x1] );
            return x1+1; // 1 based
        }
    };


    void lock_free(int x) // egy vagy ket mutexet elenged
    {
        int idx=(0x0fff&x); // 1 based
        if( idx )
        {
            pthread_mutex_unlock(&mutex[idx-1]);
        }
        idx=(0x0fff&(x>>16)); // 1 based
        if( idx )
        {
            pthread_mutex_unlock(&mutex[idx-1]);
        }
    };


    int lock() // az osszes mutexet lockolja
    {
        for( int x=0; x<prime; x++ )
        {
            pthread_mutex_lock( &mutex[x] );
        }
        return 0;
    };

    void lock_free() // az osszes mutexet elengedi
    {
        for(int i=0; i<prime; i++)
        {
            pthread_mutex_unlock(&mutex[i]);
        }
    };
};

//----------------------------------------------------------------------------------------


