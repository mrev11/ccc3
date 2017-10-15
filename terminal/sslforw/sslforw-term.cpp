
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
 
const char* terminal="terminal-xft.exe"; 

//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    char host[128]; strcpy(host,"127.0.0.1");
    int port=0;
    
    if(argc>1)
    {
        char *p=strchr(argv[1],':');
        if( p==0 )
        {
            sscanf(argv[1],"%d",&port);
        }
        else
        {
            *p=0;
            strncpy(host,argv[1],sizeof(host));
            host[sizeof(host)-1]=0;
            sscanf(p+1,"%d",&port);
            *p=':';
        }
    }
    //printf("argc: %d host:%s port:%d\n",argc,host,port);
    
    if(argc>2)
    {
        terminal=argv[2];
        //printf("terminal: %s\n",terminal);
    }

    int trmsck=socket_new();
    int result=socket_connect(trmsck,host,port);
    if(result!=0)
    {
        fprintf(stderr,"connect failed: host=%s, port=%d, errno=%d\n",host,port,errno);
        exit(1);
    }

    serve_client_connect(trmsck);
    return 0;
}


//----------------------------------------------------------------------------
void start_srvapp(int sck)
{
    char scknum[8];
    sprintf(scknum,"%d",sck); 
    char *argv[8];
    argv[0]=(char*)terminal;
    argv[1]=(char*)"--socket";
    argv[2]=scknum;    
    argv[3]=0;    

    start_child(argv);
    //Windowson azonnal visszajön
    //Linuxon csak hiba esetén jön vissza

}


//----------------------------------------------------------------------------
