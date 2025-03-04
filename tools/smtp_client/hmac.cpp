

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
