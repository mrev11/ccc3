
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "netint.h"
#include "termio.h"
#include "termcmd.h"
#include "termutil.h"

#include <signal.ch>


int remoteio_enabled=1;

//-----------------------------------------------------------------------------
int remopen(int fp, char *fname, int additive)
{
    if( remoteio_enabled==0 )
    {
        return 0;
    }
    
    int len=strlen(fname);
    network_uint32_t request[4];
    request[0].set(TERMCMD_OPEN);
    request[1].set(sizeof(request)+len);
    request[2].set(fp);
    request[3].set(additive);
    termio_send(request,sizeof(request));
    termio_send(fname,len);

    network_uint32_t response[2];
    termio_recv(response,sizeof(response)); //header
    while( response[0].get()!=TERMCMD_OPEN )
    {
        if( response[0].get()!=TERMCMD_KEYCODE )
        {
            //ilyen nem lehet
            fprintf(stderr,"remopen: unexpected message\n");
            signal_raise(SIG_TERM);
            exit(1);
        }
        termio_drop(response[1].get()-sizeof(response)); //dropping rest
        termio_recv(response,sizeof(response)); //header
    }

    network_uint32_t result;
    termio_recv(&result,sizeof(result));
    return result.get();
}

//-----------------------------------------------------------------------------
void remclose(int fp)
{
    network_uint32_t buf[3];
    buf[0].set(TERMCMD_CLOSE);
    buf[1].set(sizeof(buf));
    buf[2].set(fp);
    termio_send(buf,sizeof(buf));
}

//-----------------------------------------------------------------------------
void remwrite(int fp, char *data, int datalen)
{
    int sentlen=0;
    while( sentlen<datalen )
    {
        int len=4096;
        if( datalen-sentlen<len )
        {
            len=datalen-sentlen;
        }
   
        network_uint32_t buf[3];
        buf[0].set(TERMCMD_WRITE);
        buf[1].set(sizeof(buf)+len);
        buf[2].set(fp);
        termio_send(buf,sizeof(buf));
        termio_send(data+sentlen,len);
        
        sentlen+=len;
    }
}

//-----------------------------------------------------------------------------
