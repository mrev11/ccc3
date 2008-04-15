
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
#include <btree.h>
 
//--------------------------------------------------------------------------- 
void store16(char *buf, u_int32_t n)
{
    //n   machine order
    //buf big endian

    u_int32_t x=1;
    if( !*(char*)&x )  //3210
    {
        buf[0]=((char*)&n)[2];
        buf[1]=((char*)&n)[3]; 
    }
    else //0123
    {
        buf[0]=((char*)&n)[1]; 
        buf[1]=((char*)&n)[0]; 
    }
}

//--------------------------------------------------------------------------- 
void store32(char *buf, u_int32_t n)
{
    //n   machine order
    //buf big endian

    u_int32_t x=1;
    if( !*(char*)&x )  //3210
    {
        buf[0]=((char*)&n)[0];
        buf[1]=((char*)&n)[1]; 
        buf[2]=((char*)&n)[2];
        buf[3]=((char*)&n)[3]; 
    }
    else //0123
    {
        buf[0]=((char*)&n)[3]; 
        buf[1]=((char*)&n)[2]; 
        buf[2]=((char*)&n)[1]; 
        buf[3]=((char*)&n)[0]; 
    }
}

//--------------------------------------------------------------------------- 
u_int32_t load16(char *buf)
{
    //buf big endian
    //ret machine order

    u_int32_t x=1;
    if( !*(char*)&x )  //3210
    {
        x=0;
        ((char*)&x)[2]=buf[0];
        ((char*)&x)[3]=buf[1];
    }
    else //0123
    {
        x=0;
        ((char*)&x)[1]=buf[0];
        ((char*)&x)[0]=buf[1];
    }
    return x;
}

//--------------------------------------------------------------------------- 
u_int32_t load32(char *buf)
{
    //buf big endian
    //ret machine order

    u_int32_t x=1;
    if( !*(char*)&x )  //3210
    {
        ((char*)&x)[0]=buf[0];
        ((char*)&x)[1]=buf[1];
        ((char*)&x)[2]=buf[2];
        ((char*)&x)[3]=buf[3];
    }
    else //0123
    {
        ((char*)&x)[3]=buf[0];
        ((char*)&x)[2]=buf[1];
        ((char*)&x)[1]=buf[2];
        ((char*)&x)[0]=buf[3];
    }
    return x;
}

//--------------------------------------------------------------------------- 



