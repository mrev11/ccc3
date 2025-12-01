
// debug valtozat
// figyeli a deadlockokat

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


#define index(p) (1+((unsigned long long)(p))%prime)


static int aborted=0;
static pthread_mutex_t SYNC=PTHREAD_MUTEX_INITIALIZER;

//----------------------------------------------------------------------------------------
void settimeout(timespec *timeout, unsigned millis )
{
    struct timeval now;
    gettimeofday(&now,0);
    timeout->tv_sec=now.tv_sec;
    timeout->tv_nsec=now.tv_usec*1000;
    timeout->tv_sec+=millis/1000;
    timeout->tv_nsec+=(millis%1000)*1000000;
    if( timeout->tv_nsec>999999999 )
    {
        timeout->tv_sec++;
        timeout->tv_nsec-=1000000000;
    }
}

//----------------------------------------------------------------------------------------
struct varlock
{
    int prime;
    pthread_mutex_t *mutex;
    pid_t *tid;

    void init()
    {
        mutex=(pthread_mutex_t*)malloc((prime+1)*sizeof(pthread_mutex_t));
        tid=(pid_t*)malloc((prime+1)*sizeof(pid_t));
        for( int i=0; i<prime+1; i++  )
        {
            mutex[i]=PTHREAD_MUTEX_INITIALIZER;
            tid[i]=0;
        }
        
    };

    varlock(int len)
    {
        prime=len;
        init();
    };


    int lock(int idx) // egy mutexet megfog  idx=[0,PRIME], 0 specialis
    {
        // pthread_mutex_lock( &mutex[idx] );
        // deadlock figyeles

        struct timespec timeout;
        settimeout(&timeout,60000);
        if( 0==pthread_mutex_timedlock( &mutex[idx], &timeout ) )
        {
            // sikeres
            pthread_mutex_lock( &SYNC );
            tid[idx]=gettid();
            pthread_mutex_unlock( &SYNC );
        }
        else
        {
            // deadlock
            pthread_mutex_lock( &SYNC );
            printf("\n%p %d DEADLOCK[%d] tid=%d\n",this,prime,idx,gettid());
            for(int x=0; x<=prime; x++)
            {
                printf("%p %d mutex[%d] tid=%d\n",this,prime,x,tid[x]);
            }
            fflush(0);
            if(  !aborted )
            {
                aborted=1;
                abort();
            }
            pthread_mutex_unlock( &SYNC );
            sleep(10);
        }
        return idx;
    };


    int lock(void *p) // egy mutexet megfog
    {
        int x=index(p); // x=[1,PRIME]
        lock(x);
        return x;
    };

    int lock(void *p, int x1) // lockol egy plusz mutexet (fogni kell mutex[0]-t)
    {
        int x2=index(p); // x2=[1,PRIME]
        if( x1<x2 )
        {
            lock( x2 );
            return ((x1)<<16)|(x2);
        }
        else if( x1>x2 )
        {
            lock( x2 );
            return ((x2)<<16)|(x1);
        }
        else
        {
            return x1;
        }
    };

    int lock(void *p1, void *p2) // ket mutexet megfog
    {
        int x1=index(p1); // x1=[1,PRIME]
        int x2=index(p2); // x2=[1,PRIME]
                                                     
        if( x1<x2 )
        {
            lock( 0  );
            lock( x1 );
            lock( x2 );
            lock_free(0);
            return ((x1)<<16)|(x2);
        }
        else if( x1>x2 )
        {
            lock( 0 );
            lock( x2 );
            lock( x1 );
            lock_free(0);
            return ((x2)<<16)|(x1);
        }
        else
        {
            lock( x1 );
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
                pthread_mutex_unlock(&mutex[idx]);  // idx=[1,PRIME]
                pthread_mutex_lock(&SYNC);
                tid[idx]=0;
                pthread_mutex_unlock(&SYNC);
            }
            idx=(0x0fff&(x>>16)); // 1 based
            if( idx )
            {
                pthread_mutex_unlock(&mutex[idx]);  // idx=[1,PRIME]
                pthread_mutex_lock(&SYNC);
                tid[idx]=0;
                pthread_mutex_unlock(&SYNC);
            }
        }
        else
        {
            pthread_mutex_unlock( &mutex[0] ); //specialis
            pthread_mutex_lock(&SYNC);
            tid[0]=0;
            pthread_mutex_unlock(&SYNC);
        }
    };


    int lock() // az osszes mutexet lockolja
    {
        for( int x=0; x<=prime; x++ )
        {
            //pthread_mutex_lock( &mutex[x] );
            lock(x);
        }
        return 0;
    };

    void lock_free() // az osszes mutexet elengedi
    {
        for(int i=0; i<=prime; i++)
        {
            //pthread_mutex_unlock(&mutex[i]);
            lock_free(i);
        }
    };


    void deadlock(int id) // ellenorzi, nincs-e deadlock
    {
        struct timespec timeout;
        settimeout(&timeout,2000);

        for( int x=0; x<=prime; x++ )
        {
            if( pthread_mutex_timedlock( &mutex[x], &timeout ) )
            {
                printf("\nDEADLOCK place=%d index=%d\n",id,x);
                fflush(0);
                if( !aborted )
                {
                    aborted=1;
                    abort();
                }
            }
        }
        lock_free();
    }


};

//----------------------------------------------------------------------------------------


