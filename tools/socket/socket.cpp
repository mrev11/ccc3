
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

//Az sckutil.cpp-ben definialt egyszerusitett 
//fuggvenykeszletre epulo Clipper szintu interfesz.
//Itt mar nincs kulonbseg a UNIX es Windows kozott,
//ezert nem kell sckcompat.h-t inkludalni

#include <string.h> 

#include <sckutil.h> 
#include <cccapi.h> 

 
//---------------------------------------------------------------------------
void _clp_socket(int argno)
{
    CCC_PROLOG("socket",0);
    _retni( socket_new() );
    CCC_EPILOG();
} 

//---------------------------------------------------------------------------
void _clp_bind(int argno)
{
    CCC_PROLOG("bind",3);
    int  s=_parni(1);  //socket number
    int  p=0;          //port number
    char *a=0;         //ip address (opcionalis)
    
    //a korabbi valtozatban az ip cim nem volt megadhato,
    //a kompatibilitas kedveert most minden kombinacioban
    //elfogadjuk az ip, port parametereket a 2-3 pozicion 

    if( ISNIL(2) )
    {
        p=_parni(3);  //port
    }
    else if( ISNIL(3) )
    {
        p=_parni(2);  //port
    }
    else if( ISNUMBER(3) )
    {
        str2bin(base+1);
        a=_parb(2);   //if
        p=_parni(3);  //port
    }
    else 
    {
        str2bin(base+2);
        a=_parb(3);   //if
        p=_parni(2);  //port
    }
 
    _retni( socket_bind(s,a,p) ); 

    CCC_EPILOG();
} 
 
//---------------------------------------------------------------------------
void _clp_listen(int argno)
{
    CCC_PROLOG("listen",2);
    int s=_parni(1);                  //socket number
    int lq=ISNUMBER(2)?_parni(2):1;   //length of queue

    _retni( socket_listen(s,lq) );

    CCC_EPILOG();
}    

//---------------------------------------------------------------------------
void _clp_accept(int argno)
{
    CCC_PROLOG("accept",1);
    int s=_parni(1); //server socket number

    _retni( socket_accept(s) );

    CCC_EPILOG();
}    
 
//---------------------------------------------------------------------------
void _clp_connect(int argno)
{
    CCC_PROLOG("connect",3);

    str2bin(base+1);

    int   s = _parni(1);   //socket number
    char *h = _parb(2);    //host address
    int   p = _parni(3);   //port number

    //Ez itt nem szukseges,
    //mert a socket_connect is
    //tartalmazza a nevfeloldast.
    //
    //push_symbol(base+1);
    //extern void _clp_gethostbyname(int);
    //_clp_gethostbyname(1);
    //a=BINARYPTR(TOP());

    _retni( socket_connect(s,h,p) ); //-1 error, 0 success
    CCC_EPILOG();
} 

//---------------------------------------------------------------------------
void _clp_setsockopt(int argno)
{
    CCC_PROLOG("setsockopt",3);
    int sck = _parni(1);      //socket number
    int opt = 0;              //option (string/number)
    int val = 0;              //value (logical/number)
    
    if( ISSTRING(2) )
    {
        str2bin(base+1);
        char *name=_parb(2);

             if( 0==strcmp(name,"NODELAY") )      opt=SOCKOPT_NODELAY;
        else if( 0==strcmp(name,"NONBLOCKING") )  opt=SOCKOPT_NONBLOCKING;
        else if( 0==strcmp(name,"REUSEADDR") )    opt=SOCKOPT_REUSEADDR;
    }
    else if( ISNUMBER(2) ) 
    {
        opt=_parni(2);
    }
    else
    {
        ARGERROR();
    }
    
    
    if( ISFLAG(3) )
    {
        val=_parl(3);
    }
    else if( ISNUMBER(3) )
    {
        val=_parni(3);
    }
    else
    {
        ARGERROR();
    }

    _retni( socket_setoption(sck,opt,val) );

    CCC_EPILOG();
} 
 
//---------------------------------------------------------------------------
void _clp_swrite(int argno)
{
#if 0 //atirva 3 parameteresre fwrite mintajara
    CCC_PROLOG("swrite",2);
    str2bin(base+1);
    int s     = _parni(1);      //socket number
    char *buf = _parb(2);       //buffer to write 
    int blen  = _parblen(2);    //number of bytes to write
    _retni( socket_write(s,buf,blen) );
    CCC_EPILOG();
#endif

    CCC_PROLOG("swrite",3);
    int s=_parni(1); //socket number

    if( ISSTRING(2) )
    {
        //Ha a C tipust irunk,
        //es meg van adva a hossz,
        //akkor a hosszt nem byte-ban, 
        //hanem karakterben szamoljuk.

        if( !ISNIL(3) )
        {
            //Ha hossz is meg van adva,
            //akkor az str2bin elott csonkitunk,
            //majd a hosszt atallitjuk NIL-re.

            double dlen=_parnd(3);
            unsigned long len=min(STRINGLEN(base+1),dlen<0?0:D2ULONG(dlen));
            STRINGLEN(base+1)=len;
            (base+2)->type=TYPE_NIL;
        }
        str2bin(base+1);
    }

    char *buf = _parb(2); //buffer to write
    binarysize_t cnt = _parblen(2); //number of bytes to write

    if( ISNUMBER(3) )
    {
        double dcnt=_parnd(3);
        cnt=min(cnt, D2ULONGX(dcnt) );
    }

    _retni( socket_write(s,buf,cnt) );
    CCC_EPILOG();

    //Az egyszeru eset, amikor a bemenet bytearray ("X").
    //Ha a bemenet "C" string, akkor azt konvertalja "X"-re.
    //Ha ilyenkor meg van adva a hossz is , azzal az str2bin 
    //elott csonkit, majd a konvertalt bytearray egeszet irja ki.

}    
 
//---------------------------------------------------------------------------
void _clp_sread(int argno)
{
    //result:=sread(socket,nbyte,wtime)
    //
    //socket-bol beolvas nbyte darab byteot
    //
    //akkor ter vissza, ha
    //
    //  ready   : result == nbyte hosszusagu bynary string (bytearray)
    //
    //  timeout : result == nbyte-nal rovidebb bynary string (bytearray)
    //
    //  error   : result == NIL, ha semmit sem lehetett olvasni
    //            result == nemures, nbyte-nal rovidebb bytearray

    CCC_PROLOG("sread",3);
    
    int s     = _parni(1);                 //socket number
    int nbyte = _parni(2);                 //number of bytes to read
    int wtime = ISNUMBER(3)?_parni(3):-1;  //wait time in msec 

    if( (unsigned)nbyte>MAXBINLEN )
    {
        error_bln("sread",base,argno);
    }

    char *buf=binaryl(nbyte);
    int recvlen=socket_read(s,buf,nbyte,wtime);
    
    if( recvlen<0 )
    {
        push(&NIL);
    }
    else if( recvlen<nbyte )
    {
        binarys(buf,recvlen);
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_sready(int argno)
{
    //megadja a socketbol azonnal olvashato byteok szamat
    //NEM jelzi a vonal szakadasat (ilyenkor is 0-at ad)

    CCC_PROLOG("sready",1);
    int s=_parni(1); //socket number
    _retni( socket_available(s) );
    CCC_EPILOG();
}    

//---------------------------------------------------------------------------
void _clp_sclose(int argno)
{
    CCC_PROLOG("sclose",1);
    int s=_parni(1); //socket number
    _retni( socket_close(s) );
    CCC_EPILOG();
}    
 
//---------------------------------------------------------------------------
void _clp_serror(int argno)
{
    CCC_PROLOG("serror",0);
    _retni( socket_error() );
    CCC_EPILOG();
}    

//---------------------------------------------------------------------------
