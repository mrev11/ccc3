
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>

#include <inkey.ch>
#include <inkeymap.h>
#include <utf8conv.h>

#define MSGOUT
#include <msgout.h>


#define WAIT_MILLISEC 100


//---------------------------------------------------------------------------
static termios t0;

static void restore_attr()
{
    tcsetattr(0,TCSANOW,&t0);
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
int __readkey()
{
    set_attr();

    int key=0;

    struct timeval t;
    t.tv_sec=0;
    t.tv_usec=WAIT_MILLISEC*1000;
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(0,&fs);
    if( 0<select(1,&fs,NULL,NULL,&t) )
    {
        char c=0;
        if( 0==read(0,&c,1) )
        {
            //readable but no input
            //e.g. process in background
            exit(0);
        }
        key=0xff&(int)c;
    }

    //printf("<%d>",key);fflush(0);
    return key;
}


//---------------------------------------------------------------------------
int readkey()  //API
{
    int code=0;

    int key=0;
    unsigned int esclen=0;
    unsigned int utflen=0;
    char sequence[32];
    sequence[0]=0;

    while( (key=__readkey())!=0  )
    {
        if( utflen>0 ) // UTF-8 sequence
        {
            code=0;

            sequence[utflen++]=key;
            sequence[utflen]=0;
            if( utflen==utf8_to_ucs(sequence,(unsigned*)&code) ) // unicode?
            {
                if( code )
                {
                    break; // ervenyes UTF-8 karakter
                }
                else
                {
                    continue; // folytatodhat
                }
            }
            else
            {
                // clear input
                code=0;
                while(__readkey()!=0);
                break;
            }
        }

        else if( esclen>0 ) // escape sequence
        {
            code=0;

            sprintf(sequence+esclen,"%02x",(unsigned)key);
            esclen+=2;
            sequence[esclen]=0;

            code=inkeymap_find_sequence(sequence,esclen); //inkey code?

            if( code==MAYBE_A_SEQUENCE  )
            {
                continue; // folytatodhat
            }
            else if( code==NOT_A_SEQUENCE )
            {
                // clear input
                code=0;
                while(__readkey()!=0);
                break;
            }
            else // found a sequence
            {
                break;
            }
        }

        else if( key>0x7f )
        {
            // UTF-8 sequence

            code=key;
            utflen=0;
            sequence[utflen++]=key;
            sequence[utflen]=0;
        }

        else if( key==0x1b  )
        {
            // escape sequence

            code=key;
            esclen=0;
            sprintf(sequence+esclen,"%02x",(unsigned)key);
            esclen+=2;
            sequence[esclen]=0;
        }

        else
        {
            code=(key==127)?K_BS:key;
            break;
        }
    }

    return code;
}

//---------------------------------------------------------------------------

