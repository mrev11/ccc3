
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


#include <signal.h>
#include <dlfcn.h>

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#include <db.h>
#include <mpool.h>
#include <swap.h>

static void aes_encrypt(unsigned char*, int, unsigned char*, unsigned char*);
static void aes_decrypt(unsigned char*, int, unsigned char*, unsigned char*);
static int mpool_btpasswd(pgno_t pgno, unsigned char *key,unsigned char *iv);


typedef void btpasswd_t(pgno_t, unsigned char*, unsigned char*);

//---------------------------------------------------------------------------
static void *loadproc()
{
    const char *libname=getenv("CCC_BTPASSWD");
    const char *procname="_Z8btpasswdjPhS_";

    if( libname==0 || *libname==0 )
    {
        return 0;
    }

    void *so=dlopen(libname,RTLD_NOW|RTLD_GLOBAL); 
    if( so==0 )
    {
        fprintf(stderr,"ERROR: dlopen failed [%s]\n",libname);
        raise(SIGTERM);
        return 0;
    }
    
    void *proc=dlsym(so,procname);
    if( proc==0 )
    {
        fprintf(stderr,"ERROR: dlsym failed [%s->%s]\n",libname,procname);
        raise(SIGTERM);
        return 0;
    }
    return proc;
}

//---------------------------------------------------------------------------
static int mpool_btpasswd(pgno_t pgno, unsigned char* key,unsigned char* iv)
{
    static void *proc=loadproc();
    if( proc )
    {
        ((btpasswd_t*)proc)(pgno,key,iv);
        return 1;
    }
    return 0;
}

//---------------------------------------------------------------------------
int mpool_enable_crypt(int mode)
{
    // mode==0  titkositas letiltva
    // mode==1  titkositas engedve (ha van btpasswd is)
    // mode==-1 lekerdezes

    static int enabled=1;

    int value=enabled;
    if( mode==0 )
    {
        enabled=0;
    }
    else if( mode==1 )
    {
        enabled=1;
    }
    return value;
}

//---------------------------------------------------------------------------
int mpool_decrypt(MPOOL *mp, pgno_t pgno, char *buf)
{
    // akkor jon ide
    // ha a page titkositva van (vagy hibas)

    unsigned char key[33];
    unsigned char iv[17];

    if(  mpool_btpasswd(pgno,key,iv)  )
    {
        aes_decrypt((unsigned char*)buf,mp->pagesize,key,iv);

        pgno_t code=*(pgno_t*)buf; //uint32
        if( mp->pgin )
        {
            M_32_SWAP(code);
        }
        if( code==CRCPG(buf,mp->pagesize) ) //disk byte order!
        {
            //printf("dec %d\n",pgno);
            return 1; //OK
        }
    }

    // HIBA
    // - nincs titkosito kulcs
    // - aes_decrypt utan a CRC hibas
    return 0;
}


//---------------------------------------------------------------------------
int mpool_encrypt(MPOOL *mp, pgno_t pgno, char *buf)
{
    unsigned char key[33];
    unsigned char iv[17];

    if( mpool_enable_crypt(-1)==0 )
    {
        return 0; // letiltva, nem tortent titkositas
    }
    else if( !mpool_btpasswd(pgno,key,iv) )
    {
        return 0; // nincs megadva kulcs, nem tortent titkositas
    }

    aes_encrypt((unsigned char*)buf,mp->pagesize,key,iv);

    pgno_t code=*(pgno_t*)buf; //uint32
    if( mp->pgin )
    {
        M_32_SWAP(code);
    }

    if( code==pgno || code==CRCPG(buf,mp->pagesize) )
    {
        // ritka eset
        // nem szabad titkositani
        // mert pgno vagy CRC egyezosege miatt
        // visszaolvasaskor titkositatlannak latszana
        // ezert a titkositas vissza

        mpool_btpasswd(pgno,key,iv);
        aes_decrypt((unsigned char*)buf,mp->pagesize,key,iv);
        return 0; // nem tortent titkosites
    }

    return 1; // titkositva
}


//---------------------------------------------------------------------------
static void crypto_error()
{
    ERR_load_crypto_strings();

    unsigned long len;
    const char *file,*data;
    int line,flags;

    if( 0!=(len=ERR_get_error_line_data(&file,&line,&data,&flags)) )
    {
        char buf[1024];
        ERR_error_string_n(len,buf,sizeof(buf));
        fprintf(stderr,"%s:%s(%d)",buf,file,line);
        raise(SIGTERM);
        exit(1);
    }
}

//---------------------------------------------------------------------------
static void aes_decrypt(unsigned char *buffer, int buflen, unsigned char *key, unsigned char *iv )
{
    EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
    if( ctx==0 )
    {
        crypto_error();
    }
    if( 1!=EVP_DecryptInit(ctx,EVP_aes_256_cbc(),key,iv))
    {
        crypto_error();
    }
    EVP_CIPHER_CTX_set_padding(ctx,0);

    int len=0;
    if( 1!=EVP_DecryptUpdate(ctx,buffer,&len,buffer,buflen) )
    {
        crypto_error();
    }

    if( 1!=EVP_DecryptFinal_ex(ctx,buffer+len,&len) )
    {
        crypto_error();
    }

    EVP_CIPHER_CTX_free(ctx);
}

//---------------------------------------------------------------------------
static void aes_encrypt(unsigned char *buffer, int buflen, unsigned char *key, unsigned char *iv)
{
    EVP_CIPHER_CTX *ctx=EVP_CIPHER_CTX_new();
    if( ctx==0 )
    {
        crypto_error();
    }

    if( 1!=EVP_EncryptInit(ctx,EVP_aes_256_cbc(),key,iv))
    {
        crypto_error();
    }
    EVP_CIPHER_CTX_set_padding(ctx,0);

    int len=0;
    if( 1!=EVP_EncryptUpdate(ctx,buffer,&len,buffer,buflen) )
    {
        crypto_error();
    }

    if( 1!=EVP_EncryptFinal_ex(ctx,buffer+len,&len) )
    {
        crypto_error();
    }

    EVP_CIPHER_CTX_free(ctx);
}

//---------------------------------------------------------------------------
