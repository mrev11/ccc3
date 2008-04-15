
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
 

#include <sys/wait.h>
 
#include <sckcompat.h>
#include <sckutil.h>

static void zombi();
 
static char *s_interface=0;
static int  s_port=0;
 
//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    if( argc<3 )
    {
        fprintf(stderr, "Usage: jtlisten.exe [if:]port command\n");
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

    int ss=server_socket_new(s_interface,s_port);
    if( ss<0 )
    {
        fprintf(stderr,"server_socket_new failed\n");
        exit(1);
    }

    while( 1 )
    {
        fd_set fdlst;
        FD_ZERO(&fdlst);
        FD_SET(ss,&fdlst);

        struct timeval tv;
        tv.tv_sec=4;
        tv.tv_usec=0;   

        if( 0==select(ss+1, &fdlst, 0, 0, &tv) )
        {
            zombi();
            continue;
        }

        int cs=server_socket_accept(ss);
        if( cs>=0 )
        {
            if( fork() )
            {
                socket_close(cs);
            }
            else
            {
                socket_close(ss);
 
                char sck[32];
                sprintf(sck,"%d",cs);

                char *av[1024];
                int i=0;
                for( ; i<argc-2; i++ )
                {
                    av[i]=argv[2+i];
                }
                av[i++]=(char*)"-jtsocket";
                av[i++]=sck;
                av[i++]=0;
            
                execvp(av[0],av);
            }
        }
    }

    return 0;
}

//----------------------------------------------------------------------------
static void zombi()
{
    int pid, wstat; 
    while( 0<(pid=waitpid(0,&wstat,WNOHANG)) )
    {
        //printf("waitpid %d %d\n",pid,wstat);
    }
}

//----------------------------------------------------------------------------
