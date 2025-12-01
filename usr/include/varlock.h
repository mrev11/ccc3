
#include <stdlib.h>
#include <pthread.h>

//----------------------------------------------------------------------------------------
struct varlock
{
    int prime;
    pthread_mutex_t *mutex;

    void init()
    {
        mutex=(pthread_mutex_t*)malloc((prime+1)*sizeof(pthread_mutex_t));
        for( int i=0; i<prime+1; i++  )
        {
            mutex[i]=PTHREAD_MUTEX_INITIALIZER;
        }
    };

    varlock(int len)
    {
        prime=len;
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

    int lock(void *p, int x1) // lockol egy plusz mutexet (fogni kell mutex[0]-t)
    {
        int x2=1+((unsigned long long)p)%prime; // x2=[1,prime]
        if( x1<x2 )
        {
            pthread_mutex_lock( &mutex[x2] );
            return ((x1)<<16)|(x2);
        }
        else if( x1>x2 )
        {
            pthread_mutex_lock( &mutex[x2] );
            return ((x2)<<16)|(x1);
        }
        else
        {
            return x1;
        }
    };

    int lock(void *p1, void *p2) // ket mutexet megfog
    {
        int x1=1+((unsigned long long)p1)%prime; // x1=[1,prime]
        int x2=1+((unsigned long long)p2)%prime; // x2=[1,prime]
                                                     
        if( x1<x2 )
        {
            pthread_mutex_lock(&mutex[0]);
            pthread_mutex_lock( &mutex[x1] );
            pthread_mutex_lock( &mutex[x2] );
            pthread_mutex_unlock(&mutex[0]);
            return ((x1)<<16)|(x2);
        }
        else if( x1>x2 )
        {
            pthread_mutex_lock(&mutex[0]);
            pthread_mutex_lock( &mutex[x2] );
            pthread_mutex_lock( &mutex[x1] );
            pthread_mutex_unlock(&mutex[0]);
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
        //printf(".");fflush(0);
        for( int x=0; x<=prime; x++ )
        {
            //printf("%d",x);fflush(0);
            pthread_mutex_lock( &mutex[x] );
            //printf(".");fflush(0);
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


    void deadlock(int id) // ellenorzi, nincs-e deadlock
    {
        unsigned millis=2000;
    
        struct timeval now;
        struct timespec timeout;
        gettimeofday(&now,0);
        timeout.tv_sec=now.tv_sec;
        timeout.tv_nsec=now.tv_usec*1000;
        timeout.tv_sec+=millis/1000;
        timeout.tv_nsec+=(millis%1000)*1000000;
        if( timeout.tv_nsec>999999999 )
        {
            timeout.tv_sec++;
            timeout.tv_nsec-=1000000000;
        }

        for( int x=0; x<=prime; x++ )
        {
            if( pthread_mutex_timedlock( &mutex[x], &timeout ) )
            {
                printf("\nDEADLOCK place=%d index=%d\n",id,x);
                fflush(0);
                abort();
            }
        }
        lock_free();
    }


};

//----------------------------------------------------------------------------------------


