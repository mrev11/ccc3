
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
 

stvar::stvar()
{
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(&NIL);
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
}

stvar::stvar(BYTE const *bin)
{
    binary(bin);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvar::stvar(BYTE const *bin, unsigned len)
{
    binarys(bin,len);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvar::stvar(CHAR const *str)
{
    string(str);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvar::stvar(CHAR const *str, unsigned len)
{
    strings(str,len);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvar::stvar(double d)
{
    number(d);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}
 
stvar::stvar( void (*inicode)() )
{
    inicode();
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvar::stvar( VALUE *v )
{
    push_symbol(v);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

stvarloc::stvarloc( void (*inicode)(VALUE*),VALUE*base )
{
    inicode(base);
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    ptr=ststack;
    STPUSH(TOP());
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    POP();
}

