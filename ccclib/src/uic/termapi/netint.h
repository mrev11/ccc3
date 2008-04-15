
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

#ifndef _NETINT_H_
#define _NETINT_H_

#include <inttypes.h>

class network_uint32_t
{
  private:

    unsigned char b0; //low
    unsigned char b1;
    unsigned char b2;
    unsigned char b3; //high

  public:

    c_uint32_t get()
    {
        c_uint32_t v=0;
        v|=b3; v=v<<8; 
        v|=b2; v=v<<8; 
        v|=b1; v=v<<8; 
        v|=b0;
        return v;
    }  

    void set(c_uint32_t v)
    {
        b0=0xff&v; v=v>>8;
        b1=0xff&v; v=v>>8;
        b2=0xff&v; v=v>>8;
        b3=0xff&v;
    }
};

#endif// _NETINT_H_

