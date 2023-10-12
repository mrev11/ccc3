
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

#ifdef WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <signal.h>

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#include <db.h>
#include <mpool.h>

typedef void btpasswd_t(unsigned, pgno_t, unsigned char*, unsigned char*);

static void btpasswd(unsigned salt, pgno_t pgno, unsigned char *key,unsigned char *iv);
static void aes_encrypt(unsigned char*, int, unsigned char*, unsigned char*);
static void aes_decrypt(unsigned char*, int, unsigned char*, unsigned char*);


//========================================================================================
#ifdef WINDOWS
//----------------------------------------------------------------------------------------
static HINSTANCE load_crypto_dll()
{
    HINSTANCE dll=LoadLibraryEx("libcrypto-3-x64.dll",NULL,0); // ELTERES!
    if( dll==0 )
    {
        fprintf(stderr,"\nERROR: cannot load crypto library (errorcode=%lu)\n",GetLastError());
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return dll;
}

//----------------------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static HINSTANCE dll=load_crypto_dll();

    void *proc=(void*)GetProcAddress(dll,entryname);
    if( proc==0 )
    {
        fprintf(stderr,"\nERROR: cannot get crypto function [%s]\n",entryname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    else
    {
        //printf("LOADED [%s]\n",entryname);
        //fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------------------
static void *load_crypto_so()
{
    void *so=dlopen("libcrypto.so",RTLD_NOW|RTLD_GLOBAL);
    if( so==0 )
    {
        fprintf(stderr,"\nERROR: cannot load libcrypto.so\n");
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return so;
}

//----------------------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_crypto_so();

    void *proc=dlsym(so,entryname);
    if( proc==0 )
    {
        fprintf(stderr,"\nERROR: cannot get crypto function [%s]\n",entryname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    else
    {
        //printf("LOADED [%s]\n",entryname);
        //fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------
typedef int                 OPENSSL_init_crypto_t(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings);
typedef void                ERR_load_crypto_strings_t(void);
typedef unsigned long       ERR_get_error_line_data_t(const char **file, int *line, const char **data, int *flags);
typedef void                ERR_error_string_n_t(unsigned long e, char *buf, size_t len);

typedef EVP_CIPHER_CTX*     EVP_CIPHER_CTX_new_t(void);
typedef void                EVP_CIPHER_CTX_free_t(EVP_CIPHER_CTX *c);
typedef int                 EVP_CIPHER_CTX_set_padding_t(EVP_CIPHER_CTX *c, int pad);
typedef const EVP_CIPHER*   EVP_aes_256_cbc_t(void);

typedef int                 EVP_DecryptInit_t(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, const unsigned char *key, const unsigned char *iv);
typedef int                 EVP_DecryptUpdate_t(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl);
typedef int                 EVP_DecryptFinal_ex_t(EVP_CIPHER_CTX *ctx, unsigned char *outm, int *outl);

typedef int                 EVP_EncryptInit_t(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, const unsigned char *key, const unsigned char *iv);
typedef int                 EVP_EncryptUpdate_t(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl);
typedef int                 EVP_EncryptFinal_ex_t(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl);

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// static int _x_OPENSSL_init_crypto(uint64_t opts, const OPENSSL_INIT_SETTINGS *settings)
// {
//     static void *p=getproc("OPENSSL_init_crypto");
//     return ((OPENSSL_init_crypto_t*)p)(opts,settings);
// }

//----------------------------------------------------------------------------------------
// static void _x_ERR_load_crypto_strings()
// {
//     static void *p=getproc("ERR_load_crypto_strings");
//     ((ERR_load_crypto_strings_t*)p)();
// }

//----------------------------------------------------------------------------------------
static unsigned long _x_ERR_get_error_line_data(const char **file, int *line, const char **data, int *flags)
{
    static void *p=getproc("ERR_get_error_line_data");
    return ((ERR_get_error_line_data_t*)p)(file,line,data,flags);
}

//----------------------------------------------------------------------------------------
static void _x_ERR_error_string_n(unsigned long e, char *buf, size_t len)
{
    static void *p=getproc("ERR_error_string_n");
    return ((ERR_error_string_n_t*)p)(e, buf, len);
}



//----------------------------------------------------------------------------------------
static EVP_CIPHER_CTX *_x_EVP_CIPHER_CTX_new()
{
    static void *p=getproc("EVP_CIPHER_CTX_new");
    return ((EVP_CIPHER_CTX_new_t*)p)();
}

//----------------------------------------------------------------------------------------
static void  _x_EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *c)
{
    static void *p=getproc("EVP_CIPHER_CTX_free");
    return ((EVP_CIPHER_CTX_free_t*)p)(c);
}

//----------------------------------------------------------------------------------------
static int _x_EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *c, int pad)
{
    static void *p=getproc("EVP_CIPHER_CTX_set_padding");
    return ((EVP_CIPHER_CTX_set_padding_t*)p)(c,pad);
}

//----------------------------------------------------------------------------------------
static const EVP_CIPHER* _x_EVP_aes_256_cbc(void)
{
    static void *p=getproc("EVP_aes_256_cbc");
    return ((EVP_aes_256_cbc_t*)p)();
}



//----------------------------------------------------------------------------------------
static int _x_EVP_DecryptInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, const unsigned char *key, const unsigned char *iv)
{
    static void *p=getproc("EVP_DecryptInit");
    return ((EVP_DecryptInit_t*)p)(ctx,cipher,key,iv);
}

//----------------------------------------------------------------------------------------
static int _x_EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl)
{
    static void *p=getproc("EVP_DecryptUpdate");
    return ((EVP_DecryptUpdate_t*)p)(ctx,out,outl,in,inl);
}

//----------------------------------------------------------------------------------------
static int _x_EVP_DecryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *outm, int *outl)
{
    static void *p=getproc("EVP_DecryptFinal_ex");
    return ((EVP_DecryptFinal_ex_t*)p)(ctx, outm, outl);
}


//----------------------------------------------------------------------------------------
static int _x_EVP_EncryptInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *cipher, const unsigned char *key, const unsigned char *iv)
{
    static void *p=getproc("EVP_EncryptInit");
    return ((EVP_EncryptInit_t*)p)(ctx,cipher,key,iv);
}

//----------------------------------------------------------------------------------------
static int _x_EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl, const unsigned char *in, int inl)
{
    static void *p=getproc("EVP_EncryptUpdate");
    return ((EVP_EncryptUpdate_t*)p)(ctx,out,outl,in,inl);
}

//----------------------------------------------------------------------------------------
static int  _x_EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out, int *outl)
{
    static void *p=getproc("EVP_EncryptFinal_ex");
    return ((EVP_EncryptFinal_ex_t*)p)(ctx,out,outl);
}


//========================================================================================
#ifdef WINDOWS
//----------------------------------------------------------------------------------------
static HINSTANCE load_btpasswd_dll()
{
    const char *libname=getenv("CCC_BTPASSWD");
    HINSTANCE dll=0;
    if( libname==0 || *libname==0 || (dll=LoadLibraryEx(libname,NULL,0))==0 )
    {
        fprintf(stderr,"\nERROR: cannot load passwd library [%s]\n",libname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return dll;
}

//----------------------------------------------------------------------------------------
static void *load_btpasswd_proc()
{
    static HINSTANCE dll=load_btpasswd_dll();

    const char *procname="btpasswd"; // ELTERES! 
    void *proc=(void*)GetProcAddress(dll,procname);
    if( proc==0 )
    {
        fprintf(stderr,"\nERROR: cannot load passwd procedure [%s]\n",procname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return proc;
}

//----------------------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------------------
static void *load_btpasswd_so()
{
    const char *libname=getenv("CCC_BTPASSWD");
    void *so=0;
    if( libname==0 || *libname==0 || (so=dlopen(libname,RTLD_NOW|RTLD_GLOBAL))==0 )
    {
        fprintf(stderr,"\nERROR: cannot load passwd library [%s]\n",libname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return so;
}

//----------------------------------------------------------------------------------------
static void *load_btpasswd_proc()
{
    static void *so=load_btpasswd_so();

    const char *procname="_Z8btpasswdjjPhS_";
    void *proc=dlsym(so,procname);
    if( proc==0 )
    {
        fprintf(stderr,"\nERROR: cannot load passwd procedure [%s]\n",procname);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
    return proc;
}

//----------------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------------
static void btpasswd(unsigned salt, pgno_t pgno, unsigned char* key,unsigned char* iv)
{
    static void *proc=load_btpasswd_proc();
    ((btpasswd_t*)proc)(salt,pgno,key,iv);
}

//----------------------------------------------------------------------------------------
void mpool_decrypt(MPOOL *mp, pgno_t pgno, char *buf)
{
    unsigned char key[33];
    unsigned char iv[17];
    btpasswd(mp->salt,pgno,key,iv);
    aes_decrypt((unsigned char*)buf,mp->pagesize,key,iv);
}


//----------------------------------------------------------------------------------------
void mpool_encrypt(MPOOL *mp, pgno_t pgno, char *buf)
{
    unsigned char key[33];
    unsigned char iv[17];
    btpasswd(mp->salt,pgno,key,iv);
    aes_encrypt((unsigned char*)buf,mp->pagesize,key,iv);
}


//----------------------------------------------------------------------------------------
static void crypto_error()
{
    //_x_ERR_load_crypto_strings(); (nem kell, nem letezik?)

    unsigned long len;
    const char *file,*data;
    int line,flags;

    if( 0!=(len=_x_ERR_get_error_line_data(&file,&line,&data,&flags)) )
    {
        char buf[1024];
        _x_ERR_error_string_n(len,buf,sizeof(buf));
        fprintf(stderr,"\nERROR: %s:%s(%d)",buf,file,line);
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }
}

//----------------------------------------------------------------------------------------
static void aes_decrypt(unsigned char *buffer, int buflen, unsigned char *key, unsigned char *iv )
{
    EVP_CIPHER_CTX *ctx=_x_EVP_CIPHER_CTX_new();
    if( ctx==0 )
    {
        crypto_error();
    }
    if( 1!=_x_EVP_DecryptInit(ctx,_x_EVP_aes_256_cbc(),key,iv))
    {
        crypto_error();
    }
    _x_EVP_CIPHER_CTX_set_padding(ctx,0);

    int len=0;
    if( 1!=_x_EVP_DecryptUpdate(ctx,buffer,&len,buffer,buflen) )
    {
        crypto_error();
    }

    if( 1!=_x_EVP_DecryptFinal_ex(ctx,buffer+len,&len) )
    {
        crypto_error();
    }

    _x_EVP_CIPHER_CTX_free(ctx);
}

//----------------------------------------------------------------------------------------
static void aes_encrypt(unsigned char *buffer, int buflen, unsigned char *key, unsigned char *iv)
{
    EVP_CIPHER_CTX *ctx=_x_EVP_CIPHER_CTX_new();
    if( ctx==0 )
    {
        crypto_error();
    }

    if( 1!=_x_EVP_EncryptInit(ctx,_x_EVP_aes_256_cbc(),key,iv))
    {
        crypto_error();
    }
    _x_EVP_CIPHER_CTX_set_padding(ctx,0);

    int len=0;
    if( 1!=_x_EVP_EncryptUpdate(ctx,buffer,&len,buffer,buflen) )
    {
        crypto_error();
    }

    if( 1!=_x_EVP_EncryptFinal_ex(ctx,buffer+len,&len) )
    {
        crypto_error();
    }

    _x_EVP_CIPHER_CTX_free(ctx);
}

//----------------------------------------------------------------------------------------
