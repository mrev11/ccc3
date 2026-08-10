
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

#include <stdio.h>
#include <unistd.h>
#include <cccapi.h>
#include <fork.ch>

extern  int termio_socket();
extern  void *vartab_collector(void *ptr);
extern  void *thread_display(void *ptr);
extern  void *thread_message(void *ptr);


//--------------------------------------------------------------------------
void _clp_fork(int argno) 
{
    CCC_PROLOG("fork",1);
    int forkflag=ISNIL(1)?0:_parni(1);

    logical(0);
    _clp_setsignal(1); // disable (level)
    pop();

    pid_t pid=fork();
    
    if( pid==0 ) // CHILD
    {
        thread_data::mutex=PTHREAD_MUTEX_INITIALIZER; // lockolt allapotban lehet

        if( thread_data::tdata_count<=1 )
        {
            // egyszalu program forkolt
            // az orokolt thread_data lista megfelel
            // nincs tennivalo
        }
        else
        {
            // tobbszalu program egyik szala forkolt
            // most a child egyetlen szalaban vagyunk
            // csak a sajat thread_data-t kell megtartani
            // ki kell tisztitani thread_data listat

            thread_data *td=thread_data::tdata_first;
            while( td!=0 )
            {
                thread_data *td1=td;
                td=td->next;
                if( td1!=thread_data_ptr )
                {
                    DELTHRDATA(td1);
                }
            }
        }
        
        if( forkflag & FORK_GC )
        {
            // gc thread
            pthread_t t=0;
            pthread_create(&t,0,vartab_collector,0);
            #ifdef _LINUX_
                pthread_setname_np(t,"collector");
            #endif
            pthread_detach(t);
        }
        
        if( forkflag & FORK_SIG )
        {
            // sigwait thread
            setup_signal_handlers();
        }

        if( (forkflag & FORK_TERM)!=0 && 0<=termio_socket() )
        {
            // terminal thread

            pthread_t t=0;

            if( 0!=pthread_create(&t,0,thread_display,0) )
            {
                fprintf(stderr,"display thread cannot start\n");
                exit(1);
            }
            #ifdef _LINUX_
                pthread_setname_np(t,"display");
            #endif
            pthread_detach(t);

            if( 0!=pthread_create(&t,0,thread_message,0) )
            {
                fprintf(stderr,"message thread cannot start\n");
                exit(1);
            }
            #ifdef _LINUX_
                pthread_setname_np(t,"message");
            #endif
            pthread_detach(t);
        }
    }

    logical(1);
    _clp_setsignal(1); // enable (level)
    pop();
    
    _retni(pid);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

