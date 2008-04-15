
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
 

// 2006.11.16
// eval(errorblock,e) helyett break(e)
// cryptoerror osztályú hibát dob
// beállítja subsystem-et (crypto)

#include <stdio.h>
#include <openssl/err.h>
#include <cccapi.h>

//DEFINE_METHOD(operation);
DEFINE_METHOD(description);

extern void _clp_cryptoerrornew(int argno);
 
//-------------------------------------------------------------------------- 
void crypto_error(const char *op)
{
    char desc[256]="failed";

    #ifdef WIN32
        ERR_load_CRYPTO_strings();
    #else
        ERR_load_crypto_strings();
    #endif
    //ERR_print_errors_fp(stderr);
    
    unsigned long l;
    const char *file,*data;
    int line,flags;
 
    if( 0!=(l=ERR_get_error_line_data(&file,&line,&data,&flags)) )
    {
        char buf[200];
        ERR_error_string_n(l,buf,sizeof(buf));
        sprintf(desc,"%s:%s(%d)",buf,file,line);
    }

    stringnb(op); 
    _clp_cryptoerrornew(1);

    dup(); 
    stringnb(desc); 
    _o_method_description.eval(2); 
    pop();

    _clp_break(1);
    pop();
}

//-------------------------------------------------------------------------- 
