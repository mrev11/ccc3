
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

void _clp_thread_count(int argno)
{
    stack-=argno;
    number(thread_data::tdata_count);
}

void _clp_pdec(int argno)
{
    CCC_PROLOG("pdec",1);
    void *pp=_parp(1);
    char buf[128];
    buf[0]=0;
    sprintf(buf,"%16ld",(long)pp);
    _retb(buf);
    CCC_EPILOG();
}

void _clp_usleep(int argno)
{
    CCC_PROLOG("usleep",1);
    usleep(_parnu(1));
    _ret();
    CCC_EPILOG();
}
