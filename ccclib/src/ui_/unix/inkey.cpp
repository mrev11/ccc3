
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

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>

#include <cccapi.h>

//--------------------------------------------------------------------------- 
static int readkey(int wait)  //wait: millisec
{
    int key=0;

    int fd=0;
    termios t0,t1;
    tcgetattr(fd,&t0);
    tcgetattr(fd,&t1);
    t1.c_lflag &= ~ICANON;
    t1.c_lflag &= ~ECHO;
    t1.c_lflag |=  ISIG;
    t1.c_iflag = 0;
    t1.c_cc[VMIN] = 1;
    t1.c_cc[VTIME] = 0;
    tcsetattr(fd,TCSANOW,&t1);

    struct timeval t;
    if( wait<0 )
    {
        t.tv_sec=3600*24; //1nap
        t.tv_usec=0;
    }
    else
    {
        t.tv_sec=wait/1000;
        t.tv_usec=(wait%1000)*1000;
    }
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(0,&fs);
    if( 0<select(1,&fs,NULL,NULL,&t) )
    {
        char c;
        read(fd,&c,1);
        key=0xff&(int)c;
    }
 
    tcsetattr(fd,TCSANOW,&t0); //restore
    return key; 
}

//--------------------------------------------------------------------------- 
void _clp_inkey(int argno) 
{
    CCC_PROLOG("inkey",1);
    int key;
    double wait;
    if( ISNIL(1) )
    {
        key=readkey(0); //várakozás nélkül
    }
    else if( (wait=_parnd(1))<=0 )
    {
        key=readkey(-1); //végtelen várakozással
    }
    else
    {
        key=readkey( (int)(wait*1000) ); //várakozással
    }
    _retni(key);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------- 
void _clp___keyboard(int argno)
{
    stack-=argno;
    PUSH(&NIL);
}    

//--------------------------------------------------------------------------- 

