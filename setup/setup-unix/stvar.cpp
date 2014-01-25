
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

#include <cccapi.h>


MUTEX_CREATE(mutex);

 
static void verify_overflow()
{
    //printf("\nststack_size %ld",ststack-ststackbuf);fflush(0);
    
    static int exit_flag=0;
    if( exit_flag==0 && ststack-ststackbuf>STSTACK_SIZE-10 )
    {
        exit_flag=1;
        printf("\nStatic stack overflow");
        _clp_varstack(0);
        pop();
        printf("\n");
        fflush(0);
        exit(1);
    }
}


stvar::stvar()
{
    verify_overflow();

    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(&NIL);
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    //printf("\n%lx stvar::stvar()",(long unsigned)ptr);fflush(0);
}

stvar::stvar(BYTE const *bin)
{
    verify_overflow();

    binary(bin);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar(BYTE const *bin)",(long unsigned)ptr);fflush(0);
}

stvar::stvar(BYTE const *bin, unsigned len)
{
    verify_overflow();

    binarys(bin,len);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar(BYTE const *bin, unsigned len)",(long unsigned)ptr);fflush(0);
}

stvar::stvar(CHAR const *str)
{
    verify_overflow();

    string(str);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar(CHAR const *str)",(long unsigned)ptr);fflush(0);
}

stvar::stvar(CHAR const *str, unsigned len)
{
    verify_overflow();

    strings(str,len);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar(CHAR const *str, unsigned len)",(long unsigned)ptr);fflush(0);
}

stvar::stvar(double d)
{
    verify_overflow();

    number(d);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar(double d)",(long unsigned)ptr);fflush(0);
}
 
stvar::stvar( void (*inicode)() )
{
    verify_overflow();

    inicode();
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar( void (*inicode)() )",(long unsigned)ptr);fflush(0);
}

stvar::stvar( VALUE *v )
{
    verify_overflow();

    push_symbol(v);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
    //printf("\n%lx stvar::stvar( VALUE *v )",(long unsigned)ptr);fflush(0);
}

stvarloc::stvarloc( void (*inicode)(VALUE*),VALUE*base )
{
    inicode(base);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);

    //ptr=ststack;
    //STPUSH(TOP());
    //Itt már végrehajtódott a baseclass stvar::stvar() konstruktora.
    //Ha az inicalizálást itt is STPUSH(TOP())-pal csináljuk, 
    //akkor egy helyett két elemet teszünk az ststackre.
    //Egyszerűen használni kell a már előkészített ptr-t:

    *ptr=*TOP();

    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();

    //printf("\n%lx stvarloc::stvarloc( void (*inicode)(VALUE*),VALUE*base ) ",(long unsigned)ptr);fflush(0);
}

