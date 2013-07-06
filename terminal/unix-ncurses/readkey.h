
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

#define WAIT_MILLISEC 25 //lokálisan 25, távolról 100
#define ISESCAPE(k)  ((k)==0x1b || (k)==0xc2 || (k)==0xc3)
 
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>


static termios t0;

static void restore_attr()
{
    tcsetattr(0,TCSANOW,&t0);
    //0==system("aplay /home/vermes/bin/signal.wav &");
    //fprintf(stderr,"restore_attr\n");
}

static void set_attr()
{
    static int init=1;
    if(init)
    {
        init=0;

        tcgetattr(0,&t0);
        atexit(restore_attr);

        termios t1;
        tcgetattr(0,&t1);
        t1.c_lflag &= ~ICANON;
        t1.c_lflag &= ~ECHO;
        t1.c_lflag |=  ISIG;
        t1.c_iflag = 0;
        t1.c_cc[VMIN] = 1;
        t1.c_cc[VTIME] = 0;
        tcsetattr(0,TCSANOW,&t1);
    }
}

//---------------------------------------------------------------------------
static int __readkey()
{
    set_attr();

    static int esc=0;
    int key=0;
    
    if( esc )
    {
        key=esc;
        esc=0;
        return key; 
    }

    int fd=0;
    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=WAIT_MILLISEC*1000;
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(0,&fs);
    if( 0<select(1,&fs,NULL,NULL,&t) )
    {
        char c=0;
        if( 0==read(fd,&c,1) )
        {
            //readable but no input
            //e.g. process in background 
            exit(0);
        }
        
        key=0xff&(int)c;

        if( ISESCAPE(key) )
        {
            //esc elé beszúrunk egy plusz 0-t.

            esc=key;
            key=0;
        }
    }

    return key; 
}
 
//---------------------------------------------------------------------------
