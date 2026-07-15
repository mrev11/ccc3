
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/hmac.h>

#include <cccapi.h>

//----------------------------------------------------------------------------------------
void _clp_hmac(int argno)
{
    CCC_PROLOG("hmac",2);

    char *key=_parb(1);
    int key_len=_parblen(1);

    char *challenge=_parb(2);
    int challenge_len=_parblen(2);

    unsigned char hmac[EVP_MAX_MD_SIZE];
    unsigned int hmac_len;

    char *hmac_ret = (char*)HMAC(
                EVP_md5(),
                key,
                key_len,
                (const unsigned char*)challenge,
                challenge_len,
                hmac,
                &hmac_len);

    if( hmac_ret==0 )
    {
        _ret(); // hiba
    }
    else
    {
       _retblen(hmac_ret,hmac_len);
    }
    
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
