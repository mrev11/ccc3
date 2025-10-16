
#include <pthread.h>

//----------------------------------------------------------------------------------------
struct varsync
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    
    unsigned *var;

    varsync()
    {
        mutex=PTHREAD_MUTEX_INITIALIZER;
        cond=PTHREAD_COND_INITIALIZER; 
        var=0;
    };

    varsync(unsigned *p)
    {
        mutex=PTHREAD_MUTEX_INITIALIZER;
        cond=PTHREAD_COND_INITIALIZER; 
        var=p;
    };

    ~varsync()
    {
        // kilepeskor beragad ezekbe
        // pthread_mutex_destroy(&mutex);
        // pthread_cond_destroy(&cond);
    };
    
    
    void lock()
    {
        pthread_mutex_lock(&mutex);
        //printf("LOCK:%d\n",gettid());
        //fflush(0);
    }

    void lock_free()
    {
        pthread_mutex_unlock(&mutex);
    }

    int lock_try()
    {
       return  pthread_mutex_trylock(&mutex); // -> 0, ha sikerult lockolni
    }

    void signal()
    {
       pthread_cond_signal(&cond);
    }

    void broadcast()
    {
       pthread_cond_broadcast(&cond);
    }

    int wait()
    {
       return pthread_cond_wait(&cond,&mutex);
    }

    int wait(unsigned millis)
    {
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
        return pthread_cond_timedwait(&cond,&mutex,&timeout);  // -> 0 vagy ETIMEOUT
    }

    unsigned read()
    {
        pthread_mutex_lock(&mutex); 
        unsigned x=*var; 
        pthread_mutex_unlock(&mutex); 
        return x;
    }

    unsigned write(unsigned x)
    {
        pthread_mutex_lock(&mutex); 
        *var=x; 
        pthread_mutex_unlock(&mutex); 
        return x;
    }

    unsigned inc()
    {
        pthread_mutex_lock(&mutex); 
        unsigned x=++(*var); 
        pthread_mutex_unlock(&mutex); 
        return x;
    }

    unsigned dec()
    {
        pthread_mutex_lock(&mutex); 
        unsigned x=--(*var); 
        pthread_mutex_unlock(&mutex); 
        return x;
    }
};

//----------------------------------------------------------------------------------------
