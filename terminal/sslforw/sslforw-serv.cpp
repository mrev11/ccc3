
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
 
extern void serve_client_accept(int trmsck);
extern void serve_client_connect(int trmsck);
extern void start_srvapp(int clnsck);
extern void start_child(char* argv[]);

static int ARGC;
static char **ARGV;

//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    ARGC=argc;
    ARGV=argv;
 
    int trmsck=0;

    const char* sckenv=getenv("CCCTERM_CONNECT");
    if( sckenv==0  )
    {
    }
    else if(  sckenv!=strstr(sckenv,"SOCKET:")   )
    {
    }
    else
    {
        sscanf(sckenv+7,"%d", &trmsck);
    }

    if( trmsck==0 )
    {
        fprintf(stderr, "\nenvironment not set: CCCTERM_CONNECT=<sck>");
        exit(1);
    }

    serve_client_accept(trmsck); //listenertol orokolte: trmsck 
    return 0;
}

//----------------------------------------------------------------------------
void start_srvapp(int sck)
{
    char *argv[1024];
    for( int i=1; i<ARGC; i++ )
    {
        argv[i]=0;
        argv[i-1]=ARGV[i];
    }
    char buf[64];
    sprintf(buf,"CCCTERM_CONNECT=SOCKET:%d",sck);
    putenv(buf);

    start_child(argv);
    //Windowson azonnal visszajön
    //Linuxon csak hiba esetén jön vissza
}

//----------------------------------------------------------------------------
