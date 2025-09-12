
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_


#define NEWTHRDATA()  (new thread_data())
#define DELTHRDATA(d) (delete (thread_data*)(d))
 
class thread_data
{
  public:

    static int tdata_count;
    static thread_data *tdata_first;
    static thread_data *tdata_last;
    static pthread_mutex_t mutex;
 
    thread_data *prev; 
    thread_data *next; 
 
    TRACE   _tracebuf[TRACE_SIZE];          // stack a trace infónak
    VALUE   _stackbuf[STACK_SIZE];          // stack a local változóknak
    SEQJMP  _seqjmpbuf[SEQJMP_SIZE];        // stack a longjump-oknak
    VALUE   _usingstkbuf[USINGSTK_SIZE];    // stack a using typeinfo-nak

    TRACE  *_trace;
    VALUE  *_stack;
    SEQJMP *_seqjmp;
    VALUE  *_usingstk;
 
    static void lock(){ MUTEX_LOCK(mutex); }
    static void unlock(){ MUTEX_UNLOCK(mutex); }
    
    thread_data *init()
    {
        ++tdata_count;

        if( 1==tdata_count )
        {
            prev=0;
            next=0;
            tdata_first=this;
            tdata_last=this;
        }
        else
        {
            prev=tdata_last;
            next=0;
            tdata_last->next=this;
            tdata_last=this;
        }
    
        _trace=_tracebuf;
        _stack=_stackbuf;
        _seqjmp=_seqjmpbuf;
        _usingstk=_usingstkbuf;
        
        return this;
    }

    thread_data()
    {
        pthread_mutex_lock(&mutex);
        init();
        pthread_mutex_unlock(&mutex);
    }
    
    thread_data *cleanup()
    {
        --tdata_count;
        if( prev!=0 )
        {
            prev->next=next;
        }
        if( next!=0 )
        {
            next->prev=prev;
        }
        
        if( this==tdata_first )
        {
            tdata_first=next;
        }
        if( this==tdata_last )
        {
            tdata_last=prev;
        }
        return this;
    }

    ~thread_data()
    {
        pthread_mutex_lock(&mutex);
        cleanup();
        pthread_mutex_unlock(&mutex);
    }
};

 
#endif

