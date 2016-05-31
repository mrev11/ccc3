
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

#ifdef HASZNALAT

    jtlisten.exe [if:]port <command>
    
    A program figyel a megadott porton. Ha a portra kapcsolódnak, 
    akkor elindítja <command>-ot úgy, hogy kiegészíti azt a 
        
        -jtsocket <sck>
        
    opcióval, ahol <sck> az accept-ben létrejött socket.
    A <command>-nak spawnvp-vel, vagy execvp-vel indítható 
    filéspecifikációval kell kezdődnie.

#endif    

#include <process.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sckutil.h>

//extern int socket_pair( int sp[2] );
extern int socket_dupinherit(int socket, int inherit);
 
static char *s_interface=0;
static int  s_port=0;
 
//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    if( argc<3 )
    {
        fprintf(stderr, "Usage: jtlisten.exe [if:]port <command>\n");
        exit(1);
    }
    
    char *a=argv[1];
    char *p=strchr(a,':');

    if( p==0 )
    {
        s_interface=0;
        sscanf(a,"%d",&s_port);
    }
    else
    {
        *p=0;
        s_interface=strdup(a);
        sscanf(p+1,"%d",&s_port);
        *p=':';
    }

    int s0,ss;
    if( (s0=server_socket_new(s_interface,s_port))<0 )
    {
        fprintf(stderr,"server_socket_new failed\n");
        exit(1);
    }
    ss=socket_dupinherit(s0,0); //nem öröklődik
    socket_close(s0);
 
    while( 1 )
    {
        int cs=server_socket_accept(ss);
        
        if( cs>=0 )
        {
            char sck[32];
            sprintf(sck,"%d",cs);

            char *av[1024];
            int i=0;
            for( ; i<argc-2; i++ )
            {
                av[i]=argv[2+i];
            }
            av[i++]="-jtsocket";
            av[i++]=sck;
            av[i++]=0;
            
            spawnvp(P_NOWAIT,av[0],av);

            socket_close(cs);
        }
    }
    return 0;
}


//----------------------------------------------------------------------------
 