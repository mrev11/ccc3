
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

 
#include <sckcompat.h>
#include <sckutil.h>


void socketpair(int *asck, int *csck)
{
    const char *ifloop="127.0.0.1";
    int pp=0xf000;
    int ss=socket_new();

    while( 0>socket_bind(ss,ifloop,pp) )
    {
        pp++;
        if( (pp&0xfff)==0 )
        {
            fprintf(stderr,"\nno free port");
            exit(1);
        }
    }
    if( 0>socket_listen(ss) )
    {
        fprintf(stderr,"\nlisten failed (%d)",errno);
        exit(1);
    }
    int clnsck=client_socket(ifloop,pp);
    if( 0>clnsck )
    {
        fprintf(stderr,"\nconnect failed (%d)",errno);
        exit(1);
    }
    int appsck=socket_accept(ss); 
    if( 0>appsck )
    {
        fprintf(stderr,"\naccept failed (%d)",errno);
        exit(1);
    }
    socket_close(ss);

    *asck=appsck;
    *csck=clnsck;
}


