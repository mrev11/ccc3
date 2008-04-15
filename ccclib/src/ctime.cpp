
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

//POSIX ctime
//Pl. ctime(ostime())  -->  szöveges dátumidő
//Pl. ctime(dati2ostime(da,ti))  -->  szöveges dátumidő

 
#include <signal.h>
#include <time.h>
#include <cccapi.h>

MUTEX_CREATE(mutex);
 
//-------------------------------------------------------------------------
void _clp_ctime(int argno)
{
    CCC_PROLOG("ctime",1);
    time_t t=_parnl(1);

    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);

    stringnb(ctime(&t));

    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
 
    _rettop();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------

