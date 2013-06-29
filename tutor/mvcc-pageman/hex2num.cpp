
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

namespace _nsp_pageman {

//----------------------------------------------------------------------------
void _clp_hex2num(int argno)  // hexa (binary)stringből szám
{
    CCC_PROLOG("hex2num",1);
    char *p=_parb(1);
    unsigned long x;
    sscanf(p,"%lx",&x);
    _retnl(x);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_num2hex(int argno)  // számból hexa (binary)string 
{
    CCC_PROLOG("num2hex",2);
    unsigned long x=_parnu(1);
    int w=_parnu(2);
    char buf[32];
    sprintf(buf,"%0*lx",w,x);
    _retblen(buf,w);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_hexinc(int argno)  // hexa (binary)stringben megadott számot növel
{
    CCC_PROLOG("hexinc",1);
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


} //namespace
