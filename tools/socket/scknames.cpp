
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

#include <inttypes.h>
#include <sckcompat.h>
#include <sckutil.h>
#include <cccapi.h>

static int wsa=socket_wsastartup();

//---------------------------------------------------------------------------
void _clp_getpeername(int argno)
{
    CCC_PROLOG("getpeername",1);
    SOCKET s=(SOCKET)_parni(1); //socket number

    char sa[32];
    SOCKLEN_T namelen=sizeof(sa);
    char *addr;

    if( (0==getpeername(s,(SOCKADDR*)sa,&namelen)) &&
        (0!=(addr=inet_ntoa(((IN_ADDR*)sa)[1]))) )
    {
        binarys(addr,strlen(addr));
    }
    else
    {
        binaryn("");
    }
    _rettop();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_gethostbyname(int argno)
{
    CCC_PROLOG("gethostbyname",1);
    str2bin(base);
    char *hostname=_parb(1);

    struct hostent* he;
    he=gethostbyname(hostname);

    if( he==NULL )
    {
        PUSH(&NIL);
    }
    else
    {
        char buf[32];
        c_uint32_t ip=ntohl(*((c_uint32_t*)he->h_addr_list[0]));
        sprintf(buf,"%d.%d.%d.%d", 0xff&(ip>>24), 0xff&(ip>>16), 0xff&(ip>>8), 0xff&(ip>>0) );
        binaryn(buf);
    }
    _rettop();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_gethostname(int argno)
{
    CCC_PROLOG("gethostname",0);
    char empty[]="";
    char name[256];
    _retb( gethostname(name,256) ? empty : name );
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_getdomainname(int argno)
{
    CCC_PROLOG("getdomainname",0);
    //char name[256];
    //_retc( getdomainname(name,256)?"":name );  //mindig ures ???
    _retb(""); 
    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------- 

