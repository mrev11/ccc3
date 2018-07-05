
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

//kulonveve, hogy konnyebb legyen kicserelni

#include <string.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
//#include <openssl/opensslv.h>

#include <cccapi.h>

//--------------------------------------------------------------------------
static void print_cn_name(X509_NAME* const name)
{
    VALUE *cert_info_blk=0;
    if( TOP()->type==TYPE_BLOCK )
    {
        cert_info_blk=TOP();
    }
    else
    {
        return;
    }

    if( !name )
    {
        return;
    }

    int idx=X509_NAME_get_index_by_NID(name,NID_commonName,-1);
    if( idx<0 )
    {
        return;
    }

    X509_NAME_ENTRY* entry=X509_NAME_get_entry(name,idx);
    if( !entry )
    {
        return;
    }

    ASN1_STRING *data=X509_NAME_ENTRY_get_data(entry);
    if( !data )
    {
        return;
    }

    unsigned char *utf8=0;
    int len=ASN1_STRING_to_UTF8(&utf8,data);
    if( len<=0 )
    {
        return;
    }
    
    if( cert_info_blk )
    {
        push(cert_info_blk);
        stringnb((char*)utf8);
        _clp_eval(2);
        pop();
    }

    if( utf8 )
    {
        OPENSSL_free(utf8);
    }
}

//--------------------------------------------------------------------------
static void print_san_name(X509* const cert)
{
    VALUE *cert_info_blk=0;
    if( TOP()->type==TYPE_BLOCK )
    {
        cert_info_blk=TOP();
    }
    else
    {
        return;
    }

    if( !cert )
    {
        return;
    }

    GENERAL_NAMES *names=(GENERAL_NAMES*)X509_get_ext_d2i(cert,NID_subject_alt_name,0,0);
    if( !names )
    {
        return;
    }
    
    int count=sk_GENERAL_NAME_num(names);
    for( int i=0; i<count; ++i )
    {
        GENERAL_NAME *entry=sk_GENERAL_NAME_value(names,i);
        if( !entry )
        { 
            continue;
        }
        else if( GEN_DNS==entry->type )
        {
            unsigned char* utf8=0;
            if( 0<ASN1_STRING_to_UTF8(&utf8,entry->d.dNSName) )
            {
                if( cert_info_blk )
                {
                    push(cert_info_blk);
                    stringnb((char*)utf8);
                    _clp_eval(2);
                    pop();
                }
            }
            if( utf8 ) 
            {
                OPENSSL_free(utf8);
            }
        }
    }

    GENERAL_NAMES_free(names);
}


//--------------------------------------------------------------------------
int sslctx_verifycb(int preverify_ok, X509_STORE_CTX *ctx)
{
    int depth = X509_STORE_CTX_get_error_depth(ctx);
    int err = X509_STORE_CTX_get_error(ctx);

    const char *txt="";
    switch( err )
    {
        case  X509_V_OK:
                txt="OK";
                break;

        case  X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
                txt="ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY";
                break;

        case  X509_V_ERR_CERT_UNTRUSTED:
                txt="ERR_CERT_UNTRUSTED";
                break;

        case  X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
                txt="ERR_SELF_SIGNED_CERT_IN_CHAIN";
                break;

        case  X509_V_ERR_CERT_NOT_YET_VALID:
                txt="ERR_CERT_NOT_YET_VALID";
                break;

        case  X509_V_ERR_CERT_HAS_EXPIRED:
                txt="ERR_CERT_HAS_EXPIRED";
                break;
    }

    fprintf(stderr,"\nverify (depth=%d)",depth);
    fprintf(stderr," error=%d %s",err,txt);


    X509* cert = X509_STORE_CTX_get_current_cert(ctx);
    if( cert )
    {
        char buf[1024]; 
        buf[0]=0; X509_NAME_oneline(X509_get_issuer_name(cert),buf,1000);  fprintf(stderr,"\n  i: %s",buf);
        buf[0]=0; X509_NAME_oneline(X509_get_subject_name(cert),buf,1000); fprintf(stderr,"\n  s: %s",buf);

        if( depth==0 ) 
        {
            //server certificate

            X509_NAME *sname=X509_get_subject_name(cert);
            print_cn_name(sname);
            print_san_name(cert);
        }
    }

    return preverify_ok;
}

//--------------------------------------------------------------------------
