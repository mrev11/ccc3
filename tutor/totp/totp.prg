
#define DIGITS      6

#clang
#define INTERVAL   30
#include <stdint.h>
#include <time.h>
#include <cccapi.h>
#cend

******************************************************************************************
function main(secret)

local token,err
local len,ki,ko,h,x

    if( secret==NIL )
        ? "Usage: totp.exe <base32_encoded_secret>";?
        quit
    end

    begin
        secret::=base32_decode
    recover err <invalidformaterror>
        ? err:description, err:args;?
        quit
    end

    len:=len(secret)
    ki:=secret::padr(64+ 8,x"00")
    ko:=secret::padr(64+20,x"00")

#clang
    char *pki=BINARYPTR(LOCAL_ki);
    char *pko=BINARYPTR(LOCAL_ko);
    for( int i=0; i<64; i++ )
    {
        pki[i]^=0x36;
        pko[i]^=0x5c;
    }
    uint64_t t=((uint64_t)time(0))/INTERVAL;
    // store big endian
    pki[64+7]=(t&0xff); t=t>>8;
    pki[64+6]=(t&0xff); t=t>>8;
    pki[64+5]=(t&0xff); t=t>>8;
    pki[64+4]=(t&0xff); t=t>>8;
    pki[64+3]=(t&0xff); t=t>>8;
    pki[64+2]=(t&0xff); t=t>>8;
    pki[64+1]=(t&0xff); t=t>>8;
    pki[64+0]=(t&0xff); t=t>>8;
#cend    

    xvputbin(ko,64,20,crypto_sha1(ki))
    h:=crypto_sha1(ko)
    x:=1+h[20]::bin2hex[2]::hex2l

    // load big endian
    token:=0
    token:=token*256+h[x+0]::bin2hex::hex2l
    token:=token*256+h[x+1]::bin2hex::hex2l
    token:=token*256+h[x+2]::bin2hex::hex2l
    token:=token*256+h[x+3]::bin2hex::hex2l

    token::=numand(0x7fffffff)
    token%=(10**DIGITS)
    token::=str::alltrim::padl(DIGITS,"0")
    ? token
    ?

******************************************************************************************

    