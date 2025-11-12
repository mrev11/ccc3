
#include <stdlib.h>
#include <pthread.h>

//----------------------------------------------------------------------------------------
struct varlock
{
    int prime;
    pthread_mutex_t *mutex;

    void init()
    {
        for( int i=0; i<prime+1; i++  )
        {
            mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        }
    };

    varlock(int len)
    {
        prime=len;
        mutex=(pthread_mutex_t*)malloc((prime+1)*sizeof(pthread_mutex_t));
        init();
    };


    int lock(int idx) // egy mutexet megfog  idx=[0,prime], 0 specialis
    {
        pthread_mutex_lock( &mutex[idx] );
        return idx;
    };


    int lock(void *p) // egy mutexet megfog
    {
        int x=1+((unsigned long long)p)%prime; // x=[1,prime]
        pthread_mutex_lock( &mutex[x] );
        return x;
    };

    int lock(void *p1, void *p2) // ket mutexet megfog
    {
        int x1=1+((unsigned long long)p1)%prime; // x1=[1,prime]
        int x2=1+((unsigned long long)p2)%prime; // x2=[1,prime]
                                                     
        if( x1<x2 )
        {
            pthread_mutex_lock( &mutex[x1] );
            pthread_mutex_lock( &mutex[x2] );
            return ((x1)<<16)|(x2);
        }
        else if( x1>x2 )
        {
            pthread_mutex_lock( &mutex[x2] );
            pthread_mutex_lock( &mutex[x1] );
            return ((x2)<<16)|(x1);
        }
        else
        {
            pthread_mutex_lock( &mutex[x1] );
            return x1;
        }
    };


    void lock_free(int x) // egy vagy ket mutexet elenged
    {
        if( x )
        {
            int idx=(0x0fff&x); // 1 based
            if( idx )
            {
                pthread_mutex_unlock(&mutex[idx]);  // idx=[1,prime]
            }
            idx=(0x0fff&(x>>16)); // 1 based
            if( idx )
            {
                pthread_mutex_unlock(&mutex[idx]);  // idx=[1,prime]
            }
        }
        else
        {
            pthread_mutex_unlock( &mutex[0] ); //specialis
        }
    };


    int lock() // az osszes mutexet lockolja
    {
        for( int x=0; x<=prime; x++ )
        {
            pthread_mutex_lock( &mutex[x] );
        }
        return 0;
    };

    void lock_free() // az osszes mutexet elengedi
    {
        for(int i=0; i<=prime; i++)
        {
            pthread_mutex_unlock(&mutex[i]);
        }
    };
};

//----------------------------------------------------------------------------------------


