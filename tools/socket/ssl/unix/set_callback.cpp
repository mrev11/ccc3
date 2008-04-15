
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

//lásd: man 3 threads

#include <pthread.h>
#include <openssl/crypto.h>


static void locking_function(int mode, int n, const char*file, int line)
{
    static pthread_mutex_t *mutex=0;
    
    if( mutex==0 )
    {
        int num=CRYPTO_num_locks(); //ennyi mutex kell
        mutex=(pthread_mutex_t *)malloc(num*sizeof(pthread_mutex_t));
        for(int i=0; i<num; i++)
        {
            pthread_mutex_init(mutex+i,0);
        }
    }
    
    if( mode&CRYPTO_LOCK ) 
    {
        pthread_mutex_lock(mutex+n);
    }
    else
    {
        pthread_mutex_unlock(mutex+n);
    }
    
}

static unsigned long id_function(void)
{
    return (unsigned long)pthread_self();
}

static void* idptr_function(void)
{
    return (void*)pthread_self();
}

void init_locking_callback()
{
    CRYPTO_set_locking_callback(locking_function);
    CRYPTO_set_id_callback(id_function);
    //CRYPTO_set_idptr_callback(idptr_function); //nincs ilyen?
}



