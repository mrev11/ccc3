
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
#include <inttypes.h>

#include <cccapi.h>


//-----------------------------------------------------------------------------------
static void set_inetaddr(SOCKADDR_IN *addr, const char *host, int port)
{
    memset(addr,0,sizeof(SOCKADDR_IN));

    addr->sin_family       = AF_INET;
    addr->sin_addr.s_addr  = htonl(INADDR_ANY);
    addr->sin_port         = htons((unsigned short)port);

    struct hostent *he=0;
    if( host )
    {
        he=gethostbyname(host);
    }
    if( he!=0 )
    {
        memcpy((void*)&addr->sin_addr, he->h_addr_list[0], he->h_length);
    }
}


//-----------------------------------------------------------------------------------
void _clp_socket_inetaddr(int argno) // inetaddr:=socket_inetaddr(host,port)
{
    CCC_PROLOG("socket_inetaddr",2);
    str2bin(base+0); 
    char *host=_parb(1);
    int port=_parni(2);
    SOCKADDR_IN inetaddr;
    set_inetaddr(&inetaddr,host,port);
    binarys((char*)&inetaddr,sizeof(inetaddr));
    _rettop();
    CCC_EPILOG();
} 


//-----------------------------------------------------------------------------------
void _clp_sendto(int argno)  //sendto(sck,buffer,@inetaddr,host,port)
{
    CCC_PROLOG("sendto",5);

    SOCKADDR_IN server_addr;

    // param-1
    int sck=_parni(1);

    // param-2
    str2bin(base+1);
    char *message=_parb(2);
    size_t length=_parblen(2);

    // param-3
    push_symbol(base+2); // inetaddr derefelve a topon -> param-6

    //_clp_varstack(0);
    //pop();
  
                                   
    if( ISNIL(6) )
    {
        // param-4
        str2bin(base+3); 
        char *host=_parb(4);

        // param-5
        int port=_parni(5);

        set_inetaddr(&server_addr,host,port);
    }
    else
    {
        // param-6
        char *inetaddr=_parb(6);
        if( sizeof(server_addr)!=_parblen(6) )
        {
            ARGERROR();
        }
        memmove(&server_addr,inetaddr,sizeof(server_addr));
    }

    int nbyte=sendto(sck,message,length,0,(LPSOCKADDR)&server_addr,sizeof(server_addr));

    if( ISREF(3) && ISNIL(6) )
    {
        binarys((char*)&server_addr,sizeof(server_addr));
        assign(base+2); //inetaddr
    }
    
    _retni(nbyte);
    CCC_EPILOG();
}


//-----------------------------------------------------------------------------------
void _clp_recvfrom(int argno)  // message:=recvfrom(sck,maxlen,@inetaddr)
{
    CCC_PROLOG("recvfrom",3);
    
    int sck=_parni(1);
    int maxlen=_parni(2);

    char *buffer=(char*)malloc(maxlen);
    SOCKADDR_IN client_addr;
    SOCKLEN_T addrlen=sizeof(client_addr);
    int nbyte=recvfrom(sck,buffer,maxlen,0,(LPSOCKADDR)&client_addr,&addrlen);

    if( nbyte<0 )
    {
        _ret();
    }
    else
    {
        if( ISREF(3) )
        {
            binarys((char*)&client_addr,sizeof(client_addr));
            assign(base+2); //inetaddr
        }
        binarys(buffer,nbyte);
        _rettop();
    }

    free(buffer);
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------------

