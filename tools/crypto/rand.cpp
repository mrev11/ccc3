
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

//interfész az openssl könyvtárhoz

//#include <stdio.h>
//#include <string.h>

#include <openssl/rand.h>

#include <cccapi.h>
 
//---------------------------------------------------------------------------- 
void _clp_crypto_rand_bytes(int argno)
{
    //véletlensorozatot generál,
    //ami kriptográfiailag is erős,
    //azaz nem jósolható

    CCC_PROLOG("crypto_rand_bytes",1);
    int length=_parni(1);
    char *buf=binaryl(length);

    if( 1==RAND_bytes((unsigned char*)buf,length) )
    {
        _retblen(buf,length);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}


//---------------------------------------------------------------------------- 
void _clp_crypto_rand_pseudo_bytes(int argno)
{
    //véletlensorozatot generál,
    //ami esetleg kriptográfiailag nem erős,
    //azaz jósolható

    CCC_PROLOG("crypto_rand_pseudo_bytes",1);
    int length=_parni(1);
    char *buf=binaryl(length);

  //if( 0<=RAND_pseudo_bytes((unsigned char*)buf,length) )  //deprecated
    if( 1==RAND_bytes((unsigned char*)buf,length) )
    {
        _retblen(buf,length);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}
 
//---------------------------------------------------------------------------- 
