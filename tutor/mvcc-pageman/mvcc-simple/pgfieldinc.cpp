
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


//----------------------------------------------------------------------------
void _clp_pgfield_increment(int argno)  // hexában megadtott számot növel
{
    CCC_PROLOG("pgfield_increment",1);
    char *p=_parb(1);
    int w=_parblen(1);
    char buf[32];
    unsigned long x;
    sscanf(p,"%lx",&x);
    sprintf(buf,"%0*lx",w,x+1);
    _retblen(buf,w);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------


